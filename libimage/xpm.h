/***************************************************************************
 * xpm.h
 *
 * (C) Copyright  2004 Andreas Brachold    <anbr at users.berlios.de>
 *  Created: Thu Aug  11 2004
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

 
#ifndef _xpm_h
#define _xpm_h

class cXPM 
{

  char **m_pXPM;
  unsigned int m_nWidth;
  unsigned int m_nHeight;
  unsigned int m_nColors;

  struct colormap
  {
    unsigned int color;
    unsigned int rgb;
  } *m_Colors;
protected:
  bool GetColor(unsigned int color,unsigned int& rgb) const;
public:
  cXPM(char* pXPM[]);
  virtual ~cXPM();

  enum ePlacement
  {
    TopLeft,
    TopRight,
    Center,
    BottomLeft,
    BottomRight
  };

  bool Overlay(unsigned char* pRGBMem,unsigned int nMemWidth,unsigned int nMemHeight,unsigned int OffLeft,unsigned int OffTop) const;
  static bool Overlay(const char sz,unsigned char* pRGBMem,
                      unsigned int nMemWidth,unsigned int nMemHeight,
                      cXPM::ePlacement place, unsigned int nOffLeft,unsigned int nOffTop,
                      unsigned int nWidth,unsigned int nHeight);
  static bool Error(unsigned char* pRGBMem,unsigned int nMemWidth,unsigned int nMemHeight);
};

#endif /* _xpm_h */
