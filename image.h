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

#ifndef ___IMAGE_H
#define ___IMAGE_H

#include <vdr/config.h>
#if VDRVERSNUM < 10307
#include <vdr/osd.h>
#else
#include <vdr/osdbase.h>
#include <vdr/skins.h>
#endif
#include <string.h>

inline void OSD_InfoMsg(const char* sz) 
{	
#if VDRVERSNUM < 10307
  Interface->Info(sz); 
  Interface->Flush(); 
#else
  Skins.Message(mtInfo,sz);
  Skins.Flush();
#endif
}

inline void OSD_ErrorMsg(const char* sz) 
{	
#if VDRVERSNUM < 10307
	Interface->Error(sz); 
	Interface->Flush(); 
#else
  Skins.Message(mtError,sz);
  Skins.Flush();
#endif
}

inline void OSD_ErrorNumMsg(int err, const char* szDef) 
{	
    char szErr[128];
    int nErr = err;
    szErr[sizeof(szErr)-1] = '\0';
    if(0 != strerror_r(nErr,szErr,sizeof(szErr)-1)) {
        szErr[0] = '\0';
    } 
    OSD_ErrorMsg(szErr[0] != '\0'?szErr:szDef);
}

#endif				//___IMAGE_H
