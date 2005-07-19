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

#include <errno.h>
#include "menu-commands.h"
#include "i18n.h"

cImageMenuCommands::cImageMenuCommands(const char *szTitle, cImageCommands *pCmds, const char *szFileName /*= NULL*/)
: cOsdMenu(m_szTitle = strdup(szTitle))
, m_pCmds( pCmds )
, m_szFileName(NULL)
, m_bImageChanged(false)
{
    SetHasHotkeys();
    if(szFileName)
        m_szFileName = strdup(szFileName);

    int i = 0;
    cImageCommand *p = NULL;
    for(;NULL != (p = m_pCmds->Get(i));++i)
    {
        Add(new cOsdItem(hk(p->Title())));
    }
    SetHelp(tr("Execute"), NULL, NULL, tr("Back"));
    Display();
}

cImageMenuCommands::~cImageMenuCommands()
{
    if(m_szTitle)
        free(m_szTitle);
    if(m_szFileName)
        free(m_szFileName);
    
    if(m_pCmds)
        delete m_pCmds;
}

eOSState cImageMenuCommands::Execute(void)
{
  errno = 0; // unset error
  char *sz = NULL;
  cImageCommand *p;
  struct stat stFile,stChanged;
  if(0 == stat(m_szFileName, &stFile) 
    && NULL != (p = m_pCmds->Get(Current())))
  {    
     bool bConfirmed = true;
     if (p->Confirm()) {
        asprintf(&sz, "%s?", p->Title());
        bConfirmed = Interface->Confirm(sz);
        free(sz);
        }
     if (bConfirmed) {
        asprintf(&sz, "%s...", p->Title());
        OSD_InfoMsg(sz);
        free(sz);
        const char *szResult = p->Execute(m_szFileName);
        if(0 == stat(m_szFileName, &stChanged))
        {
          m_bImageChanged = stFile.st_mtime != stChanged.st_mtime;
        }
        if (szResult)
           return AddSubMenu(new cImageMenuResult(p->Title(), szResult, fontFix));
        return osEnd;
    }
    return osContinue;
  }
  const char* szErr = errno?strerror(errno):tr("Operation failed");
  asprintf(&sz, "%s (%s)", szErr,m_szFileName);
  OSD_ErrorMsg(sz);
  free(sz);
  return osContinue;
}

eOSState cImageMenuCommands::ProcessKey(eKeys nKey)
{
  eOSState state = cOsdMenu::ProcessKey(nKey);

  if (state == osUnknown) {
     switch (nKey) {
       case kRed:
       case kOk:  return Execute();
       case kMenu:
       case kBack:
       case kBlue:
                  return osBack;
       default:   break;
       }
     }
  return state;
}



cImageMenuResult::cImageMenuResult(const char *szTitle, const char *szText, eDvbFont Font)
: cOsdMenu(szTitle)
, m_szText(szText)
{
#if VDRVERSNUM < 10307
  Add(new cMenuTextItem(szText, 1, 2, Setup.OSDwidth - 2, MAXOSDITEMS, clrWhite, clrBackground, Font));
#endif
  SetHelp(NULL, NULL, NULL, tr("Back"));
}


eOSState cImageMenuResult::ProcessKey(eKeys nKey)
{
#if VDRVERSNUM >= 10307
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
#endif

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

#if VDRVERSNUM >= 10307
void cImageMenuResult::Display(void)
{
  cOsdMenu::Display();
  DisplayMenu()->SetText(m_szText, true);
}
#endif
