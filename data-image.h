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

#ifndef ___DATA_IMAGE_H
#define ___DATA_IMAGE_H

#include "data.h"

#include <vdr/tools.h>

// ----------------------------------------------------------------

extern cFileSources ImageSources;

class cFileSource;

// ----------------------------------------------------------------

class cImage
: public cListObject {

  cFileSource *m_pSource;
  char        *m_szFileName;
  
  char        *m_szFileNamePNM;
  char        *m_szFileNameIndex;
  char        *m_szFileNameZoom;

protected:
  void Unlink(const char *szName);
  void Clear(void);
public:
  cImage(const char *szName, cFileSource * pSource);
  virtual ~cImage();
  bool CompareBaseDir(const cFileSource * pSource) const;

  inline const char *Name(void) const       
  { 
    return m_szFileName; 
  } 
  const char *NameZoom();
  const char *NamePNM();
  const char *NameIndex();

};

// ----------------------------------------------------------------


class cSlideShow
: public cScanDir 
, public cList < cImage > {

  char* m_szFirstImageName;
  cDirItem m_DirItem;

protected:

  virtual void DoItem(cFileSource * src, const char *subdir, const char *name);

public:
  cSlideShow(cDirItem * Item);
  virtual ~cSlideShow();
  virtual bool Load(void);

  inline const char* FirstImage() const { return m_szFirstImageName; } 
};

#endif				//___DATA_IMAGE_H
