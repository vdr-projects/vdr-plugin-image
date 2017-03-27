/*
 * Image plugin to VDR (C++)
 *
 * (C) 2004-2017 Andreas Brachold    <vdr07 at deltab.de>
 *  Created: Thu Aug  5 2004
 *
 * This code is distributed under the terms and conditions of the
 * GNU GENERAL PUBLIC LICENSE. See the file COPYING for details.
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifdef HAVE_SWSCALER
extern "C" {
#include <libswscale/swscale.h>
}
#endif

#include "encode.h"
#include <vdr/device.h>
#include <vdr/tools.h>

AVCodec *cEncode::m_pavCodec = NULL;

/*******************************************************************************

*/
cEncode::cEncode(unsigned int nNumberOfFramesToEncode)
: m_pImageFilled(NULL)
, m_pImageYUV(NULL)
, m_nNumberOfFramesToEncode(nNumberOfFramesToEncode)
, m_pMPEG(NULL)
, m_pImageRGB(NULL)
{
    m_bUsePAL = (cDevice::PrimaryDevice()->GetVideoSystem() == vsPAL);
    m_nWidth  = 720;
    m_nHeight = m_bUsePAL ? 576 : 480;

    m_pFrameSizes = new unsigned int[m_nNumberOfFramesToEncode]; 

    // Just a wild guess: 3 x output image size should be enough for the MPEG
    m_nMaxMPEGSize = m_nWidth * m_nHeight * 3; 

    AllocateBuffers();
}

bool cEncode::Register()
{
    av_register_all();
    avcodec_register_all();

    m_pavCodec = avcodec_find_encoder(AV_CODEC_ID_MPEG2VIDEO);
    if (!m_pavCodec) {
        esyslog("imageplugin: Failed to find CODEC_ID_MPEG2VIDEO.");
	      return false;
    }
    return true;
}

void cEncode::UnRegister()
{
}

void cEncode::ClearRGBMem()
{
    if(m_pImageRGB)
        memset(m_pImageRGB, 0, m_nWidth * m_nHeight * 3 );
}

/*******************************************************************************

*/
cEncode::~cEncode(void)
{
    ReleaseBuffers();
    if(m_pFrameSizes) {
      delete m_pFrameSizes;
      m_pFrameSizes = NULL;
    }
}

/*******************************************************************************

*/
bool cEncode::Encode()
{
    if(!m_pavCodec)
      return false;

    bool bSuccess = false;

    AVCodecContext  *pAVCC = NULL;
    AVFrame         *pAVF = NULL;

    pAVCC = avcodec_alloc_context3(m_pavCodec);
    if (! pAVCC) 
    {
        esyslog("imageplugin: Failed to alloc memory for AVCodecContext.");
    }
    else
    {
        pAVF = av_frame_alloc();
        if (! pAVF)
        {
            esyslog("imageplugin: Failed to alloc memory for AVFrame.");
        }
        else
        {
            SetupEncodingParameters(pAVCC);

            if (avcodec_open2(pAVCC, m_pavCodec, NULL) < 0)
            {
                esyslog("imageplugin: Couldn't open Codec.");
            }
            else
            {
                if (ConvertImageToFrame(pAVF))
                {
                    bSuccess = EncodeFrames(pAVCC, pAVF); 
                }
                avcodec_close(pAVCC);
            }
            av_free(pAVF);
        }
        av_free(pAVCC);
    }
    return bSuccess;
}

void cEncode::SetupEncodingParameters(AVCodecContext *context)
{
    context->bit_rate=1000000; //1000kbit
    context->width  = m_nWidth;
    context->height = m_nHeight;

    #if LIBAVCODEC_BUILD >= 4754
        context->time_base=(AVRational){1, (int)GetFrameRate()};
    #else
        context->frame_rate=GetFrameRate();
        context->frame_rate_base=1;
    #endif

    //IPB //1 => Encode only I-Frames, bigger 
    context->gop_size=m_nNumberOfFramesToEncode-1;
    if(context->gop_size <= 1) {
      context->gop_size = 1;
    }
    context->max_b_frames=1;
    context->flags |= CODEC_FLAG_QSCALE;
    context->pix_fmt = AV_PIX_FMT_YUV420P;
}

bool cEncode::ConvertImageToFrame(AVFrame *frame)
{
    if(!m_pImageYUV || !m_pImageFilled || !m_pImageRGB || !m_pMPEG) 
    {
        esyslog("imageplugin: Failed to convert MPEG sequence, insufficient memory.");
        return false;
    }

    int nSize = m_nWidth*m_nHeight;

    frame->data[0]=m_pImageYUV;
    frame->data[1]=m_pImageYUV+nSize;
    frame->data[2]=frame->data[1]+nSize/4;
    frame->linesize[0]=m_nWidth;
    frame->linesize[1]=frame->linesize[2]=m_nWidth/2;  
    frame->quality = 1;

    // Convert RGB to YUV 
    if(!avpicture_fill((AVPicture*)m_pImageFilled, 
                                    m_pImageRGB, 
                                    AV_PIX_FMT_RGB24, m_nWidth, m_nHeight))
    {
        esyslog("imageplugin: failed avpicture_fill");
        return false;
    }
    else
    {
        int result;
#ifndef HAVE_SWSCALER
        result=img_convert((AVPicture*)frame->data, AV_PIX_FMT_YUV420P,
                       (AVPicture*)m_pImageFilled, AV_PIX_FMT_RGB24,
                       m_nWidth, m_nHeight);
#else
        SwsContext* convert_ctx = sws_getContext(m_nWidth, m_nHeight, 
                        AV_PIX_FMT_RGB24, m_nWidth, m_nHeight,
                        AV_PIX_FMT_YUV420P, SWS_BICUBIC, NULL, NULL, NULL);

	    if(!convert_ctx) {
            esyslog("imageplugin: failed to initialize swscaler context");
            return false;
    	}

	    result=sws_scale(convert_ctx, ((AVPicture*)m_pImageFilled)->data, 
                                      ((AVPicture*)m_pImageFilled)->linesize, 
                         0, m_nHeight, frame->data, frame->linesize);
	    sws_freeContext(convert_ctx);
#endif
        if(result < 0)
        {
            esyslog("imageplugin: failed convert RGB to YUV: %X", result);
            return false;
        }
    }
    return true;
}

bool cEncode::EncodeFrames(AVCodecContext *context, AVFrame *frame)
{
    AVPacket outpkt;
    if(!m_pFrameSizes)
    { 
        esyslog("imageplugin: Failed to add MPEG sequence, insufficient memory.");
        return false;
    }

    unsigned int i;
    av_init_packet(&outpkt);
    m_nMPEGSize = 0;

    // Encode m_nNumberOfFramesToEncode number of frames
    for(i=0; (i < m_nNumberOfFramesToEncode) && (m_nMPEGSize < m_nMaxMPEGSize);
      ++i)
    {

        int err = avcodec_send_frame(context, frame);
        if(err < 0) {
            esyslog("imageplugin: failed send encoding frame %d at %d %d/%d\n",
                   i,
                   frame ? (int) frame->pts : -1,
                   context->time_base.num,
                   context->time_base.den);
            av_packet_unref(&outpkt);
            return false;
        }

        outpkt.data = ( m_pMPEG + m_nMPEGSize);
        outpkt.size =  m_nMaxMPEGSize - m_nMPEGSize;

        err = avcodec_receive_packet(context, &outpkt);
        if (err == AVERROR(EAGAIN)) { // No more packets for now.
            if (frame == NULL) {
                esyslog("imageplugin: sent flush frame %d, got EAGAIN.", i);
            }
            break;
        }
        if (err == AVERROR_EOF) { // No more packets, ever.
            if (frame != NULL) {
                esyslog("imageplugin: sent image frame %d, got EOF.", i);
            }
            break;
        }
        if(err < 0) {
            esyslog("imageplugin: failed receive encoded frame %d at %d %d/%d\n",
                   i,
                   frame ? (int) frame->pts : -1,
                   context->time_base.num,
                   context->time_base.den);
            break;
        }

        m_nMPEGSize += outpkt.size;
        *(m_pFrameSizes + i) = outpkt.size;
    }
    av_packet_unref(&outpkt);

    // Add four bytes MPEG end sequence
    if ((m_nMaxMPEGSize - m_nMPEGSize) >= 4)
    {
         memcpy(m_pMPEG + m_nMPEGSize,"\0x00\0x00\0x01\0xb7",4);
         m_nMPEGSize += 4;
         *(m_pFrameSizes + i - 1) += 4;
    }
    else
    { 
        esyslog("imageplugin: Failed to add MPEG end sequence, "
          "insufficient memory.");
        return false;
    }

#ifdef TESTCODE
    // Dump generate date to file
    Save("/tmp/imagetest.mpg");
#endif

    return true;
}

void cEncode::AllocateBuffers()
{
    if(NULL == (m_pMPEG=(uint8_t *)malloc(m_nMaxMPEGSize*3)) //~1200kb
      || NULL == (m_pImageRGB=(uint8_t *)malloc(m_nWidth*m_nHeight*3))  //~1200kb
      || NULL == (m_pImageFilled=(uint8_t *)malloc(m_nWidth*m_nHeight*3)) //~1200kb
      || NULL == (m_pImageYUV=(uint8_t *)malloc(m_nWidth*m_nHeight*3/2))) //~600kb
    {
        esyslog("imageplugin: Failed to alloc memory for bitmaps.");
        return;
    }
}

void cEncode::ReleaseBuffers()
{
    if(m_pImageYUV) 
    {
        free(m_pImageYUV);
        m_pImageYUV = NULL;
    }
  
    if(m_pImageFilled) 
    {
        free(m_pImageFilled);
        m_pImageFilled = NULL;  
    } 
    if(m_pImageRGB)
    {
        free(m_pImageRGB);
        m_pImageRGB = NULL;
    }
    if(m_pMPEG)
    {
        free(m_pMPEG);
        m_pMPEG = NULL;
    }
}


#ifdef TESTCODE
/*******************************************************************************
 Load a PNM Bitmap with 24bit 720x576 direct into encoder memory
*/
bool cEncode::Load(const char* szFileName)
{
  int nSize = m_nWidth*m_nHeight;
  FILE *inf=fopen(szFileName, "r");
  if(inf)
  {
    fseek(inf, 15, SEEK_SET);
    fread(m_pImageRGB, 1, nSize*3, inf);
    fclose(inf);
    return true;
  }
  return false;
}

/*******************************************************************************
 Save encoder memory as file for diagnostics
*/
bool cEncode::Save(const char* szFileName) const
{
  if(Data() && Size())
  {  
	  FILE * outf=fopen(szFileName, "w");
    if(outf) {
      fwrite(Data(), 1, Size(), outf);
      fclose(outf);
      return true;
    }
  }
  return false;
}

/*
// Standalone test of encoder
  int main(){
  cEncode e;
  e.Load("test.pnm");
  e.Encode();
  e.Save("test.mpg");
  return 0;
}
*/
#endif
