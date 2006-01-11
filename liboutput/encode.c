/***************************************************************************
 * encode.c
 *
 * (C) Copyright  2004 Andreas Brachold    <vdr04-at-deltab.de>
 *  Created: Thu Aug  5 2004
 * 
 ****************************************************************************/

/*
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Library General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "encode.h"
#include <vdr/device.h>
#include <vdr/tools.h>

/*******************************************************************************

*/
cEncode::cEncode()
: m_pavCodec(NULL)
, m_pImageFilled(NULL)
, m_pImageYUV(NULL)
, m_nNumberOfFramesToEncode(4)
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

    m_pavCodec = avcodec_find_encoder(CODEC_ID_MPEG2VIDEO);
    if (!m_pavCodec) {
        esyslog("imageplugin: Failed to find CODEC_ID_MPEG2VIDEO.");
	return;
    }
}

bool cEncode::Register()
{
    avcodec_init();
    register_avcodec(&mpeg2video_encoder);
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
    delete m_pFrameSizes;
}

/*******************************************************************************

*/
bool cEncode::Encode()
{
    bool bSuccess = false;

    AVCodecContext  *pAVCC = NULL;
    AVFrame         *pAVF = NULL;

    pAVCC = avcodec_alloc_context();
    if (! pAVCC) 
    {
        esyslog("imageplugin: Failed to alloc memory for AVCodecContext.");
    }
    else
    {
        pAVF = avcodec_alloc_frame();
        if (! pAVF)
        {
            esyslog("imageplugin: Failed to alloc memory for AVFrame.");
        }
        else
        {
            SetupEncodingParameters(pAVCC);

            if (avcodec_open(pAVCC, m_pavCodec) < 0) 
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
        context->time_base=(AVRational){1, GetFrameRate()};
    #else
        context->frame_rate=GetFrameRate();
        context->frame_rate_base=1;
    #endif

    //IPB //1 => Encode only I-Frames, bigger 
    context->gop_size=m_nNumberOfFramesToEncode-1;

    context->max_b_frames=1;
    context->flags |= CODEC_FLAG_QSCALE;
    context->pix_fmt = PIX_FMT_YUV420P;
}

bool cEncode::ConvertImageToFrame(AVFrame *frame)
{
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
                                    PIX_FMT_RGB24, m_nWidth, m_nHeight)) 
    {
        esyslog("imageplugin: failed avpicture_fill");
        return false;
    }
    else
    {
        if(img_convert((AVPicture*)frame->data, PIX_FMT_YUV420P, 
                       (AVPicture*)m_pImageFilled, PIX_FMT_RGB24, 
                        m_nWidth, m_nHeight))  
        {
            esyslog("imageplugin: failed convert RGB to YUV");
            return false;
        }
    }
    return true;
}

bool cEncode::EncodeFrames(AVCodecContext *context, AVFrame *frame)
{
    unsigned int i;
    
    m_nMPEGSize = 0;

    // Encode m_nNumberOfFramesToEncode number of frames
    for(i=0; (i < m_nNumberOfFramesToEncode) && (m_nMPEGSize < m_nMaxMPEGSize);
      ++i)
    {
        int nFrameSize = avcodec_encode_video(context, m_pMPEG + m_nMPEGSize,
                                              m_nMaxMPEGSize - m_nMPEGSize, frame);
        if(nFrameSize < 0)
        {
            esyslog("imageplugin: Failed to add frame %d, insufficient memory.",
              i);
            return false;
        }
        m_nMPEGSize += nFrameSize;
        *(m_pFrameSizes + i) = nFrameSize;
    }

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
        free(m_pImageYUV);
  
    if(m_pImageFilled)
        free(m_pImageFilled);
  
    if(m_pImageRGB)
        free(m_pImageRGB);

    if(m_pMPEG)
        free(m_pMPEG);
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
  if(m_pMPEG && m_nData)
  {  
	  FILE * outf=fopen(szFileName, "w");
    if(outf) {
      fwrite(m_pMPEG, 1, m_nData, outf);
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
