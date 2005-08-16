/*
 * Image plugin to VDR (C++)
 *
 * (C) 2004-2005 Andreas Brachold    <vdr04-at-deltab.de>
 * based on (C) 2003 Kai Tobias Burwieck      <kai-at-burwieck.net>
 *
 * This code is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This code is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 * Or, point your browser to http://www.gnu.org/copyleft/gpl.html
 */

#ifndef ___SETUP_IMAGE_H
#define ___SETUP_IMAGE_H

extern const char *g_szConvertScript;

#include <vdr/menuitems.h>

#ifndef MAX_PATH
#define MAX_PATH 4096
#endif

class cImageSetup 
{
public:
  /* It Slideshow activ */
  int m_bSlideShow;
  /* If Slideshow activ, how many seconds between slides */
  int m_nSSsec;
  /* Where stored temp. files */
  char m_szTempDir[MAX_PATH];
  /* Should slideshow automated repeat */
  int m_bAutoRepeat;
  /* Should show overlay numbers on indexdump */
  int m_bShowNumbers;
  /* Don't mute audio, on show images */
  int m_bLiveAudio;
  /* Activate own house keeping system for temp. files, avoid pregenerated images */
  int m_bHousekeeping;

  /** Minimum Value for Slideshow */
  static const int m_cSSMin;
  /** Maximum Value for Slideshow */
  static const int m_cSSMax;

  /** Range for BorderHeight */
  static const int m_cnMinBorderHeight;
  static const int m_cnMaxBorderHeight;
  int m_nBorderHeight;

  /** Range for BorderWidth */
  static const int m_cnMinBorderWidth;
  static const int m_cnMaxBorderWidth;
  int m_nBorderWidth;


public:
  cImageSetup(void);
  void SetEnv(void) const;
  
  bool SetupParse(const char *szName, const char *szValue);
};


// ----------------------------------------------------------------

class cMenuSetupImage
	:public cMenuSetupPage 
{
  cImageSetup m_tmpSetup;
protected:
  virtual void Store(void);
public:
  cMenuSetupImage(void);
};


extern cImageSetup ImageSetup;

#endif				//___SETUP_IMAGE_H
