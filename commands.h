/*
 * Image plugin to VDR (C++)
 *
 * (C) 2004 Andreas Brachold    <anbr at users.berlios.de>
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

// --- cImageCommands ---------------------------------------------------------

#ifndef __COMMANDS_H
#define __COMMANDS_H

#include <vdr/tools.h>

class cImageCommand
: public cListObject 
{
  char *m_szTitle;
  char *m_szCommand;
  bool m_bConfirm;
  static char *m_szLastResult;
public:
  cImageCommand(void);
  virtual ~ cImageCommand();

  bool Parse(const char *s);

  const char *Title(void) const  { return m_szTitle;  } 
  bool Confirm(void) const       { return m_bConfirm; }
  const char *Command(void) const{ return m_szCommand;}

  const char *Execute(const char *szFileName = NULL);
};

class cImageCommands
: public cList < cImageCommand > 
{
  char *m_szFileName;
  bool m_bAllowComments;
protected:
  void Clear(void);
public:
  cImageCommands(void);
  virtual ~ cImageCommands();

  const char *FileName(void) const { return m_szFileName; }
  bool Load(const char *szFileName = NULL, bool bAllowComments = true, bool bMustExist = false);
};

#endif				//__COMMANDS_H
