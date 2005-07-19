/*
 * Image plugin to VDR (C++)
 *
 * (C) 2004 Andreas Brachold    <vdr04-at-deltab.de>
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

#ifndef __MENU_COMMANDS_H
#define __MENU_COMMANDS_H

#include "image.h"
#include "commands.h"
#include <vdr/menuitems.h>
#include <vdr/interface.h>

class cImageMenuCommands
: public cOsdMenu 
{
  cImageCommands *m_pCmds;
  char *m_szFileName;
  bool m_bImageChanged;
  char *m_szTitle;
protected:
  eOSState Execute(void);
public:
  cImageMenuCommands(const char *szTitle, cImageCommands *Cmds, const char *szFileName = NULL);
  virtual ~cImageMenuCommands();
  virtual eOSState ProcessKey(eKeys Key);
  bool HasImageChanged() const { return m_bImageChanged; } 
};
  

class cImageMenuResult : public cOsdMenu 
{
	const char *m_szText;
protected:
#if VDRVERSNUM >= 10307
	virtual void Display(void);
#endif
public:
    cImageMenuResult(const char *Title, const char *Text, eDvbFont Font = fontOsd);
    virtual eOSState ProcessKey(eKeys Key);
};


#endif //__MENU_COMMANDS_H
