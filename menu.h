/*
 * Image plugin to VDR (C++)
 *
 * (C) 2003 Kai Tobias Burwieck <kai@burwieck.net>
 *
 * based on MP3/MPlayer plugin to VDR (C++)
 * (C) 2001,2002 Stefan Huelswitt <huels@iname.com>
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

#ifndef ___MENU_H
#define ___MENU_H

#include "image.h"
#include "data.h"
// ----------------------------------------------------------------

class cMenuBrowse:public cOsdMenu {
  private:
    eOSState Select(bool isred);
    eOSState Parent(void);
    bool LoadDir(const char *dir);
  protected:
    static cDirItem *lastselect;
    //
    cDirList *list;
    cFileSource *source;
    bool dirselectable;
    char *currentdir, *parent;
//
    bool NewDir(const char *dir);
    void SetSource(cFileSource * Source);
    cDirItem *CurrentItem(void);
    virtual void SetButtons(void);
  public:
     cMenuBrowse(cFileSource * Source, bool Dirselect, const char *title);
    ~cMenuBrowse();
    virtual eOSState ProcessKey(eKeys Key);
    static cDirItem *GetSelected(void) {return lastselect;}
};

// ----------------------------------------------------------------

class cMenuSource:public cOsdMenu {
  private:
    static cFileSource *selected;
    cFileSource *current;
    //
    eOSState Mount(void);
    eOSState Unmount(void);
    eOSState Eject(void);
    eOSState Select(void);
    bool DoMount(cFileSource * src);
    bool CheckMount(void);
  public:
     cMenuSource(cFileSources * Sources, const char *title);
    virtual eOSState ProcessKey(eKeys Key);
    static cFileSource *GetSelected(void) {	return selected;}
};

#endif				//___MENU_H
