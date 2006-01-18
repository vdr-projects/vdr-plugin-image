/*
 * Image plugin to VDR (C++)
 *
 * (C) 2006 Andreas Brachold    <anbr at users.berlios.de>
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

#ifndef __MENU_EXIF_H
#define __MENU_EXIF_H

#include "image.h"
#include <vdr/menuitems.h>
#include <vdr/interface.h>
#include <string>


class cImageMenuExif : public cOsdMenu 
{
	std::string m_strText;
protected:
	virtual void Display(void);
public:
  cImageMenuExif(const char *szFileName);
  virtual eOSState ProcessKey(eKeys Key);
};

enum ImageExifOrientation { 
	IMAGE_EXIF_ORIENTATION_NONE = 0,
	IMAGE_EXIF_ORIENTATION_TOP_LEFT,
	IMAGE_EXIF_ORIENTATION_TOP_RIGHT,
	IMAGE_EXIF_ORIENTATION_BOTTOM_RIGHT,
	IMAGE_EXIF_ORIENTATION_BOTTOM_LEFT,
	IMAGE_EXIF_ORIENTATION_LEFT_TOP,
	IMAGE_EXIF_ORIENTATION_RIGHT_TOP,
	IMAGE_EXIF_ORIENTATION_RIGHT_BOTTOM,
	IMAGE_EXIF_ORIENTATION_LEFT_BOTTOM
};

enum ImageMirror { 
	NONE = 0,
	MIRROR,
	FLIP
};

ImageExifOrientation GetRotationFromExifData (const char *filename, int& rotate, ImageMirror& mirror);

#endif //__MENU_EXIF_H
