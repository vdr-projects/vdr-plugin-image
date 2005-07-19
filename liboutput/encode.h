/***************************************************************************
 * encode.h
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
 
#ifndef _ENCODE_H
#define _ENCODE_H

extern "C"
{
#ifdef HAVE_FFMPEG_STATIC
# include <libavcodec/avcodec.h>
#else
# include <ffmpeg/avcodec.h>
//#include <libavcodec/avcodec.h>
#endif
}

//#define TESTCODE

class cEncode
{
  AVCodec         *m_pavCodec;
  unsigned int     m_nMaxMPEGSize;
	uint8_t         *m_pImageFilled; 
	uint8_t         *m_pImageYUV;
protected:
  const unsigned int m_nFrames;
  unsigned int     m_nData;
	uint8_t         *m_pMPEG; 
	uint8_t         *m_pImageRGB;
  bool            m_bUsePAL;
  unsigned int    m_nWidth;
  unsigned int    m_nHeight;
  unsigned int*   m_pFramesSize;

#ifndef HAVE_FFMPEG_STATIC
private:
  static void *m_hLibAvcodec;
protected:
  static bool InitLibAVCodec(void);
  static void CloseLibAVCodec(void);
#endif
  bool m_bLoaded;
public:
  cEncode();
  virtual ~cEncode();

  /*Load Shared Library and Register Codec*/
  static bool Register();
  /*UnLoad Shared*/
  static void UnRegister();

  bool Encode();
  inline const uint8_t *Data() const             { return m_pMPEG; }
  inline unsigned int Size() const               { return m_nData; }
  inline unsigned int GetFrames() const          { return m_nFrames; } 
  inline unsigned int GetFrameRate() const       { return m_bUsePAL?25:30; } 

  inline unsigned int GetHeight() const          { return m_nHeight; } 
  inline unsigned int GetWidth() const           { return m_nWidth;  } 
  inline unsigned int GetBorderHeight() const    { return 16; } 
  inline unsigned int GetBorderWidth() const     { return 16; } 

  inline  uint8_t         *GetRGBMem()           { return m_pImageRGB; }
#ifdef TESTCODE
  bool Load(const char* szFileName);
  bool Save(const char* szFileName) const;
#endif
  void  ClearRGBMem ();
};

#endif /* _ENCODE_H */
