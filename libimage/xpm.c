/***************************************************************************
 * xpm.c
 *
 * (C) Copyright  2004 Andreas Brachold    <vdr04-at-deltab.de>
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
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <vdr/tools.h>


#include "img1.xpm"
#include "img2.xpm"
#include "img3.xpm"
#include "img4.xpm"
#include "img5.xpm"
#include "img6.xpm"
#include "img7.xpm"
#include "img8.xpm"
#include "img9.xpm"

#include "error.xpm"
#include "error_small.xpm"

#include "xpm.h"

cXPM gOverlay_Image_1(img1_xpm);
cXPM gOverlay_Image_2(img2_xpm);
cXPM gOverlay_Image_3(img3_xpm);
cXPM gOverlay_Image_4(img4_xpm);
cXPM gOverlay_Image_5(img5_xpm);
cXPM gOverlay_Image_6(img6_xpm);
cXPM gOverlay_Image_7(img7_xpm);
cXPM gOverlay_Image_8(img8_xpm);
cXPM gOverlay_Image_9(img9_xpm);

cXPM gOverlay_Error(error_xpm);
cXPM gOverlay_ErrorSmall(error_small_xpm);

cXPM::cXPM(char* pXPM[])
:m_Colors(NULL)
{
  char **p = pXPM;
  int c;
  if (4 != sscanf(*p, "%d %d %d %d", &m_nWidth, &m_nHeight, &m_nColors, &c)
      || c != 1 ) 
  {
    esyslog("imageplugin: ERROR! faulty 'values' line in XPM: '%s'", *p);
    return;
  }
   
  m_Colors = new colormap[m_nColors];

  for (unsigned int n = 0; n < m_nColors; ++n) {
      bool bColorNone = false;
      const char *s = *++p;
      if (int(strlen(s)) < c) {
         esyslog("imageplugin: ERROR! faulty 'colors' line in XPM: '%s'", s);
         return;
         }
      (m_Colors+n)->color = *s; 
      s = skipspace(s + c);
      if (*s != 'c') {
         esyslog("imageplugin: ERROR! unknown color key in XPM: '%c'", *s);
         return;
         }
      s = skipspace(s + 1);
      if (strcasecmp(s, "none") == 0) {
         s = "#000000";
         bColorNone = true;
         }
      if (*s != '#') {
         esyslog("imageplugin: ERROR! unknown color code in XPM: '%c'", *s);
         return;
         }
      (m_Colors+n)->rgb = strtoul(++s, NULL, 16) | (bColorNone?0xFF000000:0x00000000);
      }
    
  m_pXPM = p;
  for (unsigned int l = 0; l < m_nHeight; l++) {
    const char *s = *++p;
    if (strlen(s) != m_nWidth * c) {
       esyslog("imageplugin: ERROR! faulty pixel line in XPM: %d '%s'", l, s);
       m_pXPM = NULL;
       return;
       }
     }
}

cXPM::~cXPM()
{
  if(m_Colors)
    delete[] m_Colors;
}


bool cXPM::Overlay(unsigned char* pRGBMem,unsigned int nMemWidth,unsigned int nMemHeight,unsigned int OffLeft,unsigned int OffTop) const
{
  if(!m_Colors || !pRGBMem || !m_pXPM)
    return false;
  
  char **p = m_pXPM; 

  for(unsigned int h = 0;
    h < m_nHeight 
    && h+OffTop < nMemHeight;
    ++h)
  {  
    const char *s = *++p;
    for(unsigned int w = 0;w < m_nWidth 
      && w+OffLeft < nMemWidth;
      ++w,++s)
    { 
      unsigned int rgb;
      if(GetColor(*s,rgb))
      {    
        unsigned char* pImageRGB = pRGBMem + 
        ((((h+OffTop)*nMemWidth)+w+OffLeft)*3);
        
        *(pImageRGB + 0) = (unsigned char)(rgb >> 16) & 0xFF;
        *(pImageRGB + 1) = (unsigned char)(rgb >> 8 ) & 0xFF;
        *(pImageRGB + 2) = (unsigned char)(rgb      ) & 0xFF;
      }
    }
  }

  return true;
}



bool cXPM::GetColor(unsigned int color,unsigned int& rgb) const
{
  unsigned int n = 0;
  for(;n<m_nColors;++n)
  {
    if((m_Colors+n)->color == color)
    {  
      rgb = (m_Colors+n)->rgb;
      return (0 == (rgb & 0xFF000000)); // Check for color "none"
    }
  }  
  return false;
}

bool cXPM::Overlay(const char sz,unsigned char* pRGBMem,
                    unsigned int nMemWidth,unsigned int nMemHeight,
                    cXPM::ePlacement place, unsigned int nOffLeft,unsigned int nOffTop,
                    unsigned int nWidth,unsigned int nHeight) 
{ 
  cXPM* p = NULL;
  switch(sz)
  {
    case '1': p=&gOverlay_Image_1;break;
    case '2': p=&gOverlay_Image_2;break;
    case '3': p=&gOverlay_Image_3;break;
    case '4': p=&gOverlay_Image_4;break;
    case '5': p=&gOverlay_Image_5;break;
    case '6': p=&gOverlay_Image_6;break;
    case '7': p=&gOverlay_Image_7;break;
    case '8': p=&gOverlay_Image_8;break;
    case '9': p=&gOverlay_Image_9;break;
    case 's': p=&gOverlay_ErrorSmall;break;
    }
  if(p)
    {
      switch(place)
      {  
        case TopLeft:
          return p->Overlay(pRGBMem,
                      nMemWidth,nMemHeight,
                      nOffLeft,
                      nOffTop);
        case TopRight:
          return p->Overlay(pRGBMem,
                      nMemWidth,nMemHeight,
                      nOffLeft+nWidth-p->m_nWidth-16,
                      nOffTop);
        case Center:
          return p->Overlay(pRGBMem,
                      nMemWidth,nMemHeight,
                      nOffLeft + nWidth/2 - p->m_nWidth/2,
                      nOffTop + nHeight/2 - p->m_nHeight/2);
        case BottomLeft:
          return p->Overlay(pRGBMem,
                      nMemWidth,nMemHeight,
                      nOffLeft,
                      nOffTop+nHeight-p->m_nHeight);
        case BottomRight:
          return p->Overlay(pRGBMem,
                      nMemWidth,nMemHeight,
                      nOffLeft+nWidth-p->m_nWidth-16,
                      nOffTop+nHeight-p->m_nHeight);
       } 
    }
    
  return false;
}

bool cXPM::Error(unsigned char* pRGBMem,unsigned int nMemWidth,unsigned int nMemHeight)
{ 
  return gOverlay_Error.Overlay(pRGBMem,
                  nMemWidth,nMemHeight,
                  (nMemWidth - gOverlay_Error.m_nWidth)/2,
                  (nMemHeight - gOverlay_Error.m_nHeight)/2);
}
