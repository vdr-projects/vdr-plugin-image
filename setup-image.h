/*
 * Image plugin to VDR (C++)
 *
 * (C) 2003 Kai Tobias Burwieck <kai@burwieck.net>
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

class cImageSetup 
{
public:
  int SlideShow;
  int SSsec;
  char TempDir[260];
#if VDRVERSNUM < 10307
  int ShowDate;
#endif
  int AutoRepeat;
  int ShowNumbers;
#if VDRVERSNUM >= 10308
  int m_bLiveAudio;
#endif 
  int m_bHousekeeping;

  /** Minimum Value for Slideshow */
  static const int m_cSSMin;
  /** Maximum Value for Slideshow */
  static const int m_cSSMax;

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
