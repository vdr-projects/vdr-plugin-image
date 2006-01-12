/***************************************************************************
 * encode.h
 *
 * (C) Copyright  2004 Andreas Brachold    <anbr at users.berlios.de>
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
 
#ifndef _ENCODE_H
#define _ENCODE_H

#ifdef FFMDIR
#include <avcodec.h>
#else
#include <ffmpeg/avcodec.h>
#endif 

#include "../setup-image.h"
//#define TESTCODE

class cEncode
{
    AVCodec *m_pavCodec;
    unsigned int m_nMaxMPEGSize;
    uint8_t *m_pImageFilled; 
    uint8_t *m_pImageYUV;

protected:
    const unsigned int m_nNumberOfFramesToEncode;
    uint8_t *m_pMPEG; 
    uint8_t *m_pImageRGB;
    bool m_bUsePAL;
    unsigned int m_nMPEGSize;
    unsigned int m_nWidth;
    unsigned int m_nHeight;
    unsigned int *m_pFrameSizes;

public:
    cEncode();
    virtual ~cEncode();

    /*Load Shared Library and Register Codec*/
    static bool Register();
    /*UnLoad Shared*/
    static void UnRegister();

    bool Encode();
    inline const uint8_t *Data() const       { return m_pMPEG; }
    inline unsigned int Size() const         { return m_nMPEGSize; }
    inline unsigned int GetFrames() const    { return m_nNumberOfFramesToEncode; } 
    inline unsigned int GetFrameRate() const { return m_bUsePAL?25:30; } 

    inline unsigned int GetFrameSize(unsigned int nframeNumber) const 
      { return *(m_pFrameSizes + nframeNumber); } 

    inline unsigned int GetHeight() const       { return m_nHeight; } 
    inline unsigned int GetWidth() const        { return m_nWidth;  } 
    inline unsigned int GetBorderHeight() const { return ImageSetup.m_nBorderHeight; } 
    inline unsigned int GetBorderWidth() const  { return ImageSetup.m_nBorderWidth; } 

    inline uint8_t *GetRGBMem() { return m_pImageRGB; }
    void  ClearRGBMem ();

#ifdef TESTCODE
    bool Load(const char* szFileName);
    bool Save(const char* szFileName) const;
#endif

private:
    void AllocateBuffers();
    void ReleaseBuffers();
    void SetupEncodingParameters(AVCodecContext *context);
    bool ConvertImageToFrame(AVFrame *frame);
    bool EncodeFrames(AVCodecContext *context, AVFrame *frame);
};

#endif /* _ENCODE_H */
