/*
 * Image plugin to VDR (C++)
 *
 * (C) 2004 Andreas Brachold    <vdr04-at-deltab.de>
 * (C) 2003 Kai Tobias Burwieck <kai-at-burwieck.net>
 *
 * based on MP3/MPlayer plugin to VDR (C++)
 * (C) 2001,2002 Stefan Huelswitt <huels-at-iname.com>
 *
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

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <vdr/tools.h>
#include <vdr/config.h>
#include "setup-image.h"
#include "i18n.h"

cImageSetup ImageSetup;

const int cImageSetup::m_cSSMin = 2;
const int cImageSetup::m_cSSMax = 300;

// --- cImageSetup -----------------------------------------------------------

cImageSetup::cImageSetup(void)

{
  SlideShow = 0;
  SSsec = 10;
  strncpy(TempDir, "/tmp/image", sizeof(TempDir));
#if VDRVERSNUM < 10307
  ShowDate = 1;
#endif
  AutoRepeat = 0;
  ShowNumbers = 1;
#if VDRVERSNUM >= 10308
  m_bLiveAudio = 0;
#endif 
  m_bHousekeeping = 1;
}

bool cImageSetup::SetupParse(const char *szName, const char *szValue)
{
        if(!strcasecmp(szName, "SlideShow"))                SlideShow = atoi(szValue);
  else  if(!strcasecmp(szName, "SSsec"))                    
  { 
    SSsec = atoi(szValue); 
    if(SSsec < m_cSSMin) SSsec = cImageSetup::m_cSSMin;
    if(SSsec > m_cSSMax) SSsec = cImageSetup::m_cSSMax;
  } 
  else  if(!strcasecmp(szName, "TempDir"))                  strn0cpy(TempDir,szValue,sizeof(TempDir));
#if VDRVERSNUM < 10307
  else  if(!strcasecmp(szName, "ShowDate"))                 ShowDate = atoi(szValue);
#endif    
  else  if(!strcasecmp(szName, "AutoRepeat"))               AutoRepeat = atoi(szValue);
  else  if(!strcasecmp(szName, "ShowNumbers"))              ShowNumbers = atoi(szValue);
#if VDRVERSNUM >= 10308
  else  if(!strcasecmp(szName, "LiveAudio"))                m_bLiveAudio = atoi(szValue);
#endif   
  else  if(!strcasecmp(szName, "Housekeeping"))             m_bHousekeeping = atoi(szValue);
  else return false;
  return true;
}

// --- cMenuSetupImage --------------------------------------------------------
void cMenuSetupImage::Store(void)
{
  ImageSetup = m_tmpSetup;
  SetupStore("SlideShow",               ImageSetup.SlideShow);
  SetupStore("SSsec",                   ImageSetup.SSsec);
  SetupStore("TempDir",                 ImageSetup.TempDir);
#if VDRVERSNUM < 10307
  SetupStore("ShowDate",                ImageSetup.ShowDate);
#endif
  SetupStore("AutoRepeat",              ImageSetup.AutoRepeat);
  SetupStore("ShowNumbers",             ImageSetup.ShowNumbers);
#if VDRVERSNUM >= 10308
  SetupStore("LiveAudio",               ImageSetup.m_bLiveAudio);
#endif   
  SetupStore("Housekeeping",            ImageSetup.m_bHousekeeping);
}

cMenuSetupImage::cMenuSetupImage(void)
: m_tmpSetup(ImageSetup)
{
  SetSection(tr("Image"));
  Add(new cMenuEditBoolItem(tr("SlideShow ?"),                    &m_tmpSetup.SlideShow,    tr("no"), tr("yes")));
  Add(new cMenuEditIntItem (tr("Slide duration (sec)"),           &m_tmpSetup.SSsec,        cImageSetup::m_cSSMin, cImageSetup::m_cSSMax));
  Add(new cMenuEditBoolItem(tr("Repeat SlideShow"),               &m_tmpSetup.AutoRepeat,   tr("no"), tr("yes")));
#if VDRVERSNUM < 10307
  Add(new cMenuEditBoolItem(tr("Show Filedate on OSD"),           &m_tmpSetup.ShowDate,     tr("no"), tr("yes")));
#endif
  Add(new cMenuEditBoolItem(tr("Show Numbers on index image"),    &m_tmpSetup.ShowNumbers,  tr("no"), tr("yes")));
#if VDRVERSNUM >= 10308
  Add(new cMenuEditBoolItem(tr("Live Audio from primary Device"), &m_tmpSetup.m_bLiveAudio,  tr("no"), tr("yes")));
#endif   
  Add(new cMenuEditStrItem (tr("Directory with temporary files"), m_tmpSetup.TempDir,sizeof(m_tmpSetup.TempDir), "abcdefghijklmopqrstuvwxyz/-"));
  Add(new cMenuEditBoolItem(tr("Remove temporary files"),         &m_tmpSetup.m_bHousekeeping,  tr("no"), tr("yes")));
}





void cImageSetup::SetEnv(void) const
{
  unsigned int i;
  struct cImageCommandEnv { 
    const char* szEnv;  
    const char* szValue;
  } nEnvironTable [] =
  {
    {"ASPECT_RATIO",Setup.VideoFormat?"16:9":"4:3"}, // Get from DVB-Setup
    {"CONVERT_TEMPDIR",TempDir},            
  };

  for(i=0;i < sizeof(nEnvironTable)/sizeof(*nEnvironTable);++i)
  {
    if(nEnvironTable[i].szValue) { 
      if(0!= setenv(nEnvironTable[i].szEnv, nEnvironTable[i].szValue,1))
        esyslog("imageplugin: can't setenv '%s = %s'", nEnvironTable[i].szEnv, nEnvironTable[i].szValue);
    }
    else { 
      if(0!= unsetenv(nEnvironTable[i].szEnv))
        esyslog("imageplugin: can't unsetenv '%s'", nEnvironTable[i].szEnv);
    }
  }
}
