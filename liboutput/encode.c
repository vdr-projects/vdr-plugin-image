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

#ifndef HAVE_FFMPEG_STATIC
#include <dlfcn.h>
#endif

#include "encode.h"
#include <vdr/device.h>
#include <vdr/tools.h>

typedef void (*f_avcodec_init)(void);
typedef void (*f_avcodec_register_all)(void);
typedef AVCodec *(*f_avcodec_find_encoder)(enum CodecID id);
typedef AVCodecContext *(*f_avcodec_alloc_context)(void);
typedef AVFrame *(*f_avcodec_alloc_frame)(void);
typedef int (*f_avcodec_open)(AVCodecContext *avctx, AVCodec *codec);
typedef int (*f_avcodec_close)(AVCodecContext *avctx);
typedef int (*f_avcodec_encode_video)(AVCodecContext *avctx, uint8_t *buf, int buf_size,const AVFrame *pict);
typedef int (*f_avpicture_fill)(AVPicture *picture, uint8_t *ptr, int pix_fmt, int width, int height);

#if FFMPEG_VERSION_INT <= 0x000408
typedef int (*f_img_convert)(AVPicture *dst, int dst_pix_fmt,AVPicture *src, int pix_fmt,int width, int height);
#elif FFMPEG_VERSION_INT >= 0x000409
typedef int (*f_img_convert)(AVPicture *dst, int dst_pix_fmt,const AVPicture *src, int pix_fmt,int width, int height);
#else
    #error "there is a unknow ffmpeg version or FFMPEG_VERSION_INT isnt defined"
#endif

#ifdef HAVE_FFMPEG_STATIC

static f_avcodec_init           fn_avcodec_init=avcodec_init;
static f_avcodec_register_all   fn_avcodec_register_all=avcodec_register_all;
static f_avcodec_find_encoder   fn_avcodec_find_encoder=avcodec_find_encoder;
static f_avcodec_alloc_context  fn_avcodec_alloc_context=avcodec_alloc_context;
static f_avcodec_alloc_frame    fn_avcodec_alloc_frame=avcodec_alloc_frame;
static f_avcodec_open           fn_avcodec_open=avcodec_open;
static f_avcodec_close          fn_avcodec_close=avcodec_close;
static f_avcodec_encode_video   fn_avcodec_encode_video=&avcodec_encode_video;
static f_avpicture_fill         fn_avpicture_fill=avpicture_fill;
static f_img_convert            fn_img_convert=img_convert;

#else

static f_avcodec_init           fn_avcodec_init;
static f_avcodec_register_all   fn_avcodec_register_all;
static f_avcodec_find_encoder   fn_avcodec_find_encoder;
static f_avcodec_alloc_context  fn_avcodec_alloc_context;
static f_avcodec_alloc_frame    fn_avcodec_alloc_frame;
static f_avcodec_open           fn_avcodec_open;
static f_avcodec_close          fn_avcodec_close;
static f_avcodec_encode_video   fn_avcodec_encode_video;
static f_avpicture_fill         fn_avpicture_fill;
static f_img_convert            fn_img_convert;


#define DLSYM(cast,sym,func) \
    sym=(cast)dlsym(m_hLibAvcodec, func);  \
		bSuccess &= (sym != NULL); \
    if(sym == NULL) \
      esyslog("imageplugin: Link to function %s failed", func);	

void *cEncode::m_hLibAvcodec = NULL;


/*******************************************************************************

*/
bool cEncode::InitLibAVCodec(void){

	bool bSuccess=false;
  // Let ld.so search the libary
  const char* szLibary = "libavcodec.so";
  m_hLibAvcodec=dlopen(szLibary, RTLD_LAZY);
  if(!m_hLibAvcodec)
  {
    esyslog("imageplugin: Loading %s failed : %s", szLibary,dlerror());	
  }  
	/* map the lib's syms to our wrapper */
	else {

    bSuccess=true;
    DLSYM(f_avcodec_init,fn_avcodec_init,"avcodec_init");
  	DLSYM(f_avcodec_init,fn_avcodec_register_all,"avcodec_register_all");
  	DLSYM(f_avcodec_find_encoder,fn_avcodec_find_encoder,"avcodec_find_encoder");
  	DLSYM(f_avcodec_alloc_context,fn_avcodec_alloc_context,"avcodec_alloc_context");
  	DLSYM(f_avcodec_alloc_frame,fn_avcodec_alloc_frame,"avcodec_alloc_frame");
  	DLSYM(f_avcodec_open,fn_avcodec_open,"avcodec_open");
  	DLSYM(f_avcodec_close,fn_avcodec_close,"avcodec_close");
  	DLSYM(f_avcodec_encode_video,fn_avcodec_encode_video,"avcodec_encode_video");
  	DLSYM(f_avpicture_fill,fn_avpicture_fill,"avpicture_fill");
  	DLSYM(f_img_convert,fn_img_convert,"img_convert");
  }

	return(bSuccess);
}

/*******************************************************************************

*/
void cEncode::CloseLibAVCodec(void){

	if (m_hLibAvcodec) 
    dlclose(m_hLibAvcodec);
  m_hLibAvcodec = NULL; 
}
#endif

/*******************************************************************************

*/
cEncode::cEncode()
: m_pavCodec(NULL)
,	m_pImageFilled(NULL)
,	m_pImageYUV(NULL)
, m_nFrames(4)
, m_nData(0)
,	m_pMPEG(NULL)
,	m_pImageRGB(NULL)
{
  m_bLoaded = false;
  m_pFramesSize = new unsigned int[m_nFrames]; 

  m_bUsePAL = (cDevice::PrimaryDevice()->GetVideoSystem() == vsPAL);
  m_nWidth  = 720;
  m_nHeight = m_bUsePAL ? 576 : 480;


  m_nMaxMPEGSize = m_nWidth*m_nHeight * 3; //It see for me 500kb are enough, therefore should the double really enough memory

	/* Allocate bufers */
  if(NULL == (m_pMPEG=(uint8_t *)malloc(m_nMaxMPEGSize*3)) //~1200kb
    || NULL == (m_pImageRGB=(uint8_t *)malloc(m_nWidth*m_nHeight*3))  //~1200kb
    || NULL == (m_pImageFilled=(uint8_t *)malloc(m_nWidth*m_nHeight*3)) //~1200kb
    || NULL == (m_pImageYUV=(uint8_t *)malloc(m_nWidth*m_nHeight*3/2))) //~600kb
  {
      esyslog("imageplugin: Failed to alloc memory for bitmaps.");
      return;
  }

  m_pavCodec = fn_avcodec_find_encoder(CODEC_ID_MPEG2VIDEO);	
	if (!m_pavCodec) {
		esyslog("imageplugin: Failed to find CODEC_ID_MPEG2VIDEO.");
		return;
	}
  m_bLoaded = true;
}

bool cEncode::Register()
{
  #ifndef HAVE_FFMPEG_STATIC
    if(!InitLibAVCodec()) {
      esyslog("imageplugin: Failed to InitLibAVCodec.");
      return false;
    }
  #endif 
  fn_avcodec_init();
  fn_avcodec_register_all();
  return true;
}

void cEncode::UnRegister()
{
#ifndef HAVE_FFMPEG_STATIC
  CloseLibAVCodec();
#endif
}

void cEncode::ClearRGBMem()
{
  if(m_pImageRGB && m_bLoaded)
    memset(m_pImageRGB,0,m_nWidth*m_nHeight*3 );
}

/*******************************************************************************

*/
cEncode::~cEncode(void)
{
  if(m_pImageYUV)
    free(m_pImageYUV);
  
  if(m_pImageFilled)
    free(m_pImageFilled);
  
  if(m_pImageRGB)
    free(m_pImageRGB);

  if(m_pMPEG)
    free(m_pMPEG);
  delete m_pFramesSize;
}

/*******************************************************************************

*/
bool cEncode::Encode()
{
  m_nData = 0;

  if (!m_bLoaded){
		dsyslog("imageplugin: libavcodec is'nt successful loaded.");
		return false;
	}

  bool bSuccess = false;
  unsigned int i;
  AVCodecContext  *pAVCC = NULL;
  AVFrame         *pAVF = NULL;
	int nSize=m_nWidth*m_nHeight;

  if(NULL == (pAVCC = fn_avcodec_alloc_context())
    || NULL == (pAVF = fn_avcodec_alloc_frame())) {
      esyslog("imageplugin: Failed to alloc memory for AVCODEC and CONTEXT.");
  		goto encexit;
  }

	pAVCC->bit_rate=1000000; //1000kbit
	pAVCC->width  = m_nWidth;
	pAVCC->height = m_nHeight;
	pAVCC->frame_rate=GetFrameRate();
	pAVCC->frame_rate_base=1;
	pAVCC->gop_size=m_nFrames-1; //IPB //1 => Encode only I-Frames, bigger 
	pAVCC->max_b_frames=1;
	pAVCC->flags |= CODEC_FLAG_QSCALE;

	if (fn_avcodec_open(pAVCC, m_pavCodec)<0) {
		esyslog("imageplugin: Coldn't open Codec.");
		goto encexit;
	}
	
	pAVF->data[0]=m_pImageYUV;
	pAVF->data[1]=m_pImageYUV+nSize;
	pAVF->data[2]=pAVF->data[1]+nSize/4;
	pAVF->linesize[0]=m_nWidth;
	pAVF->linesize[1]=pAVF->linesize[2]=m_nWidth/2;  
  pAVF->quality = 1;
 
  // Convert RGB to YUV 
  if(!fn_avpicture_fill((AVPicture*)m_pImageFilled, m_pImageRGB, PIX_FMT_RGB24, 
    m_nWidth, m_nHeight)) {
		esyslog("imageplugin: failed avpicture_fill");
		goto encexit;
	}
  
  if(fn_img_convert((AVPicture*)pAVF->data, PIX_FMT_YUV420P, 
    (AVPicture*)m_pImageFilled, PIX_FMT_RGB24, m_nWidth, m_nHeight)) {
		esyslog("imageplugin: failed convert RGB to YUV");
		goto encexit;
	}
	
  // Encode Frames which defined with m_nFrames 
  for(i=0; i<m_nFrames && m_nData < m_nMaxMPEGSize; ++i)
  {
    int nFrameSize = fn_avcodec_encode_video(pAVCC, m_pMPEG + m_nData, m_nMaxMPEGSize - m_nData, pAVF);
    if(nFrameSize < 0)
    {
      esyslog("imageplugin: Failed add %d frame, insufficient memory.",i);
      bSuccess = false;
      break;
    }
    bSuccess = true;
		m_nData += nFrameSize;
    *(m_pFramesSize + i) = nFrameSize;
	}

  if(bSuccess && m_nData < m_nMaxMPEGSize) // if sufficient place present
  {
  	//add four bytes end sequnce
    memcpy(m_pMPEG + m_nData,"\0x00\0x00\0x01\0xb7",4);
    m_nData += 4;
    *(m_pFramesSize + i - 1) += 4;
  
  }
  else bSuccess = false;

  #ifdef TESTCODE
  if(bSuccess)
    Save("/tmp/imagetest.mpg");
  #endif

encexit:
  if (pAVCC)
  {
    fn_avcodec_close(pAVCC);
    free(pAVCC);
  }
  
  if(pAVF)
  {
    free(pAVF);
  }
  return bSuccess;
}




#ifdef TESTCODE
/*******************************************************************************

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
#endif


#if 0
int main(){
  cEncode e;
  e.Load("test.pnm");
  e.Encode();
  e.Save("test.mpg");
  return 0;
}
#endif
