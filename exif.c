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

#include <libexif/exif-data.h>
#include <libexif/exif-ifd.h>
#include <libexif/exif-loader.h>

#include <sstream>

#include "player-image.h"
#include "control-image.h"
#include "exif.h"
#include "i18n.h"

static void callbackShowEntry (ExifEntry *e, void *pData)
{
	if (!pData)
		return;

    std::ostream* po = (std::ostream*)pData;

	char v[128];
	ExifIfd ifd = exif_entry_get_ifd (e);

    (*po) <<  exif_tag_get_title_in_ifd (e->tag, ifd);
    (*po) << ":\t";
    (*po) << exif_entry_get_value (e, v, 59);
    (*po) << std::endl;
}

static void callbackShowIFD (ExifContent *content, void *pData)
{
	exif_content_foreach_entry (content, callbackShowEntry, pData);
}

void TagList (std::ostream& o, ExifData *ed)
{
	if (!ed)
		return;

	exif_data_foreach_content (ed, callbackShowIFD, &o);
}

static bool MarkerNodes (std::ostream& o, ExifData *d)
{
	unsigned int i, c;
	char v[1024], *p;
	ExifMnoteData *md;

	md = exif_data_get_mnote_data (d);
	if (!md) {
		o << tr("Could not parse exif maker note!") << std::endl;
		exif_data_unref (d);
		return false;
	}

	c = exif_mnote_data_count (md);
	for (i = 0; i < c; i++) {
		p = exif_mnote_data_get_value (md, i, v, sizeof (v));
		if (p) 
        { 
    		o << exif_mnote_data_get_title (md, i);
            o << ":\t";
            o << v << std::endl;
        }
	}

	return true;
}

cImageMenuExif::cImageMenuExif(const char *szFileName)
: cOsdMenu(tr("Show exif informations from image"))
{
  std::ostringstream o;
  ExifData *d;

  d = exif_data_new_from_file (szFileName);
  if (d) {
      TagList(o, d);
      o << std::endl;

      MarkerNodes (o, d);
      exif_data_unref (d);
  } else
  {
    o << tr("Could not load exif data from image!") << std::endl;
  }

  m_strText = o.str();
  SetHelp(NULL, NULL, NULL, tr("Back"));
  Display();
}


eOSState cImageMenuExif::ProcessKey(eKeys nKey)
{
  switch (nKey) {
    case kUp|k_Repeat:
    case kUp:
    case kDown|k_Repeat:
    case kDown:
    case kLeft|k_Repeat:
    case kLeft:
    case kRight|k_Repeat:
    case kRight:
                  DisplayMenu()->Scroll(NORMALKEY(nKey) == kUp || NORMALKEY(nKey) == kLeft, NORMALKEY(nKey) == kLeft || NORMALKEY(nKey) == kRight);
                  return osContinue;
    default: break;
    }

  eOSState nState = cOsdMenu::ProcessKey(nKey);
  if (nState == osUnknown) {
     switch (nKey) {
       case kOk: 
       case kMenu:
       case kBack:
       case kBlue:
                 return osBack;
       default:  nState = osContinue;
       }
     }
  return nState;
}

void cImageMenuExif::Display(void)
{
  cOsdMenu::Display();
  DisplayMenu()->SetText(m_strText.c_str(),true);
}

//////////////////////////////////////////////////////////////////////////////
/** Handle a Key stroke on exifmenu
@return eOSState
@param eKeys Key - the processed Keycode
*/
eOSState cImageControl::ProcessKeyExif(eKeys nKey)
{
  if(m_pExifMenu)
  {
    eOSState eOSRet = m_pExifMenu->ProcessKey(nKey);
    switch(eOSRet)
    {
      case osEnd:
      case osBack:
        delete m_pExifMenu;
        m_pExifMenu = NULL;
        return osContinue;
      default:
        return eOSRet;
    }
  }
  else
  {
    if(!CheckAccess()) {
      OSD_ErrorNumMsg(errno,tr("Operation failed"));
      return osContinue;
    }
  
    Hide();
    
    m_pExifMenu = new cImageMenuExif(FileName());
  
    return osContinue;
  }
}
