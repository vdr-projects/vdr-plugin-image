/*
* Image plugin to VDR (C++)
*
* (C) 2004-2005 Andreas Brachold <anbr at users.berlios.de>
* based on (C) 2003 Kai Tobias Burwieck <kai -at- burwieck.net>
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

#include <time.h>

#include "player-image.h"
#include "control-image.h"
#include "data-image.h"
#include "setup-image.h"
#include "i18n.h"
#include "menu-commands.h"
#include "list.h"

#ifdef HAVE_LIBEXIF
#include "exif.h"
#endif

#include <vdr/status.h>
#include <vdr/tools.h>
#include <vdr/plugin.h>
#include <vdr/eitscan.h>

// --- cImageControl ---------------------------------------------------------

char* cImageControl::m_szLastShowStatusMsg = 0;

void cImageControl::SetSlideShow(cSlideShow * pNewSlideShow)
{
  // Remove old session
  if(cControl::Control())
  	cControl::Shutdown();

  if(pNewSlideShow) {
    cImageControl* pControl = new cImageControl(pNewSlideShow);
    cControl::Launch(pControl);
  }
}
//////////////////////////////////////////////////////////////////////////////
/** C-tor Create for control-object to control the image-player
*/
cImageControl::cImageControl(cSlideShow * pNewSlideShow)
 : cControl(player = new cImagePlayer(pNewSlideShow))
 , m_pCmdMenu(NULL)
#ifdef HAVE_LIBEXIF
 , m_pExifMenu(NULL)
#endif
 , m_pDisplayReplay(NULL)
{
  // Notity all cStatusMonitor
  cStatus::MsgReplaying(this, "image", NULL, true );
  
  m_tStarted = time(NULL);
  
  m_eOSDStatusIsOpen = eDisplayNothing;
  // Depends the Setup of ShowReplayMode is ModeOnly visable
  m_eOSDStatusVisable = Setup.ShowReplayMode?eDisplayModeOnly:eDisplayNothing;
  
  m_ePlayMode = ePlayModeNormal;
  m_bSlideShowActiv = ImageSetup.m_bSlideShow;
  m_bSlideShowBefore = false;
  
  // Support for Zoom
  m_nZoomFactor = 0;
  m_nRealImageWidth = 0;
  m_nRealImageHeight = 0;
}


//////////////////////////////////////////////////////////////////////////////
/** D-tor Destroy control-object to control the image-player
*/
cImageControl::~cImageControl()
{
  if(m_pCmdMenu) {
    delete m_pCmdMenu;
    m_pCmdMenu = NULL; 
  }

#ifdef HAVE_LIBEXIF
  if(m_pExifMenu) {
    delete m_pExifMenu;
    m_pExifMenu = NULL;
  }
#endif

  // Notity cleanup all cStatusMonitor
  cStatus::MsgReplaying(this, "image", NULL, false);
  // Hide OSD
  HideOSD();
  if(m_pDisplayReplay) {
    delete m_pDisplayReplay;
    m_pDisplayReplay = NULL;
  }
  // Stop Playback
  Stop();
  if(player)
	  delete player;
  player = NULL;
  
  if(m_szLastShowStatusMsg)
    free(m_szLastShowStatusMsg);    
  m_szLastShowStatusMsg = 0;
}

void cImageControl::Show(void)
{
  ShowOSD();
}

void cImageControl::Hide(void)
{
  m_eOSDStatusVisable = eDisplayNothing;
  HideOSD();
    
  if(m_szLastShowStatusMsg)
    free(m_szLastShowStatusMsg);
  m_szLastShowStatusMsg = 0;
}

void cImageControl::ShowOSD()
{
  switch(m_eOSDStatusVisable) {
    case eDisplayNothing:	HideOSD();      break;
    case eDisplayModeOnly:	ShowMode();     break;
    case eDisplayProgress:	ShowProgress(); break;
  }
}

void cImageControl::HideOSD(void)
{
  if(eDisplayNothing != m_eOSDStatusIsOpen) {
    if(m_pDisplayReplay) {
		delete m_pDisplayReplay;
		m_pDisplayReplay = NULL;
    }
    m_eOSDStatusIsOpen = eDisplayNothing;
  }

  if (m_pCmdMenu) {
    delete m_pCmdMenu;
    m_pCmdMenu = NULL;
  }

#ifdef HAVE_LIBEXIF
  if(m_pExifMenu) {
    delete m_pExifMenu;
    m_pExifMenu = NULL;
  }
#endif

}
//////////////////////////////////////////////////////////////////////////
/** Send Message if changed to any statusmonitor 
*/
void cImageControl::ShowStatusMsg()
{
  char* sz = 0;
  if(IsConvertRunning())  // Display that convert is running
  {
    asprintf(&sz,"%s",tr("Convert..."));
  }
  else 
  {
    switch(m_ePlayMode)
    {
      case ePlayModeNormal: asprintf(&sz,"%s",FileName());break;
      case ePlayModeJump:   asprintf(&sz,"%s",tr("Select picture via key 1..9!"));break;
      case ePlayModeZoom:   asprintf(&sz,"%s %dx",tr("Zoom"),m_nZoomFactor);break;
    }
  }
  if(sz)
  { 
    if(!m_szLastShowStatusMsg 
      || 0 != strcmp(m_szLastShowStatusMsg,sz))
    {
      if(m_szLastShowStatusMsg)
        free(m_szLastShowStatusMsg);
      m_szLastShowStatusMsg = sz;
      cStatus::MsgReplaying(this, "image" , m_szLastShowStatusMsg, true );
    }
    else 
      free(sz);
  }
}

void cImageControl::ShowMode(void)
{
  if(eDisplayModeOnly != m_eOSDStatusIsOpen)
  {
	m_pDisplayReplay = Skins.Current()->DisplayReplay(m_eOSDStatusVisable==eDisplayModeOnly);  
    m_eOSDStatusIsOpen = eDisplayModeOnly;
  }

  int nMaxCharacter = m_pDisplayReplay->EditableWidth();	//FIXME Get OSD-Display width 
  char *sz = MALLOC(char, nMaxCharacter + 1);
  
  if(IsConvertRunning())  // Display that convert is running
  {
    strn0cpy(sz, tr("Convert..."), nMaxCharacter);
  }
  else                    // else Display depends on current play the status
  {
    switch(m_ePlayMode) 
    {
    // Display normal playstatus
    default:
      case ePlayModeNormal:
      {
		// Get the current activ filename
		const char* szFileName = FileName();
		if(!szFileName)
			return;
		snprintf(sz, nMaxCharacter, "%s", szFileName);	
        break;
      }
      // Display jumpmode playstatus
      case ePlayModeJump:
      {
        strn0cpy(sz, tr("Select picture via key 1..9!"), nMaxCharacter);
        break;
      }
      // Display zoommode playstatus
      case ePlayModeZoom:
      {
        snprintf(sz, nMaxCharacter, "%s %dx",tr("Zoom"),m_nZoomFactor);
      }
    }
  }
  
  m_pDisplayReplay->SetMode(m_ePlayMode == ePlayModeNormal && m_bSlideShowActiv, true, 1);
  if(m_eOSDStatusVisable!=eDisplayModeOnly)  
	  m_pDisplayReplay->SetTitle(sz);
  free(sz);
}

void cImageControl::ShowProgress(void)
{
  // Get the current activ filename
  const char* szFileName = FileName();
  if(!szFileName)
    return;

  if(eDisplayProgress != m_eOSDStatusIsOpen) {
    HideOSD();
    m_pDisplayReplay = Skins.Current()->DisplayReplay(m_eOSDStatusVisable==eDisplayModeOnly);
    m_pDisplayReplay->SetMarks(&m_Marks);
    m_eOSDStatusIsOpen = eDisplayProgress;
  }

  int nMaxCharacter = m_pDisplayReplay->EditableWidth();	//FIXME Get OSD-Display width 
  //********************************************************************
  // build first Line
  char *sz = MALLOC(char, nMaxCharacter + 1);

  if(IsConvertRunning()) // Display that convert is running
  {
      snprintf(sz, nMaxCharacter, "%s", tr("Convert..."));
  } 
  else
  {
    switch(m_ePlayMode) {
      case ePlayModeJump:
        snprintf(sz, nMaxCharacter, "%s",
             tr("Select picture via key 1..9!"));
        break;
      case ePlayModeZoom:
        snprintf(sz, nMaxCharacter, "%s: %dx (%dx%d)",tr("Zoom"),
                      m_nZoomFactor,
                      m_nRealImageWidth * m_nZoomFactor, 
                      m_nRealImageHeight * m_nZoomFactor);
        break;
      case ePlayModeNormal:
        snprintf(sz, nMaxCharacter, "%s", szFileName);
        break;
    }
  }

    m_pDisplayReplay->SetTitle(sz);

  //********************************************************************
  // show on second line the progressbar
  m_pDisplayReplay->SetProgress(ImageCurrent(), ImageTotal());
  
  snprintf(sz, nMaxCharacter, "%3d", ImageCurrent());
  m_pDisplayReplay->SetCurrent(sz);
  snprintf(sz, nMaxCharacter, "%3d", 
    m_ePlayMode==ePlayModeJump?
      std::min(ImageCurrent()+9,ImageTotal())
      :ImageTotal());
  m_pDisplayReplay->SetTotal(sz);

  m_pDisplayReplay->Flush();
  free(sz);
}





//////////////////////////////////////////////////////////////////////////////
/** VDR-Callback entry for Key was processed
@return eOSState
@param eKeys Key - the processed Keycode
*/
eOSState cImageControl::ProcessKey(eKeys nKey)
{
  // Check for next image
  SlideImage();

  // Deny EITScanner on Live Audio
  if(ImageSetup.m_bLiveAudio)
     EITScanner.Activity();

  eOSState eOSRet = osContinue;
  
  if(m_pCmdMenu 
    || (m_ePlayMode != ePlayModeJump && (nKey == kRed)))
  {
    return ProcessKeyCommands(nKey);
  }
#ifdef HAVE_LIBEXIF
  else if(m_pExifMenu
    || (m_ePlayMode != ePlayModeJump && (nKey == kInfo)))
  {
    return ProcessKeyExif(nKey);
  }
#endif
  else
  {
    switch(nKey) 
    {
        //processed global keybindings
        //None key, check for ErrorMsg from Worker
        case kNone:   if(player)player->ErrorMsg();     break;
        case kOk:     ToogleShowMode();                 break;
        // Toggle between Play/Pause
        case kPlay:     
        case kPause:  ToogleSlideShowActiv();           break;
        // Stop Plugin    
        case kStop:     
        case kBlue:    eOSRet = ProcessKeyStopped();    break;
  
        default: //processed PlayMode depends keybindings
        {
            switch(m_ePlayMode)
            {
                case ePlayModeNormal: eOSRet = ProcessKeyPlayMode(nKey); break;
                case ePlayModeZoom:   eOSRet = ProcessKeyZoomMode(nKey); break;
                case ePlayModeJump:   eOSRet = ProcessKeyJumpMode(nKey); break;
            }
        }
    }
  }
  // show current state at OSD
  if(eOSRet == osContinue)
  {
    ShowOSD();
    ShowStatusMsg();
  }
  return eOSRet;
}

//////////////////////////////////////////////////////////////////////////////
/** Handle a Key stroke on normal playmode
@return eOSState
@param eKeys Key - the processed Keycode
*/
eOSState cImageControl::ProcessKeyPlayMode(eKeys Key)
{
  switch (Key)
  {
  // Mode select
  case kBack: return ProcessKeyStopped();
  case k0:    OriginalImage(false);    break;  
  case k8:    ProcessKeyBeginJump();   break;
  case k5:    ProcessKeyBeginZoom();   break;
  
  // Rotate the image
  case k1:    LFlipImage();            break;
  case k3:    RFlipImage();            break;
      
  // Change time how long image is see
  case k4|k_Repeat:
  case k4:    DecSlideTime();          break;
  case k6|k_Repeat:
  case k6:    IncSlideTime();          break;
  
  // Navigate between images
  case kLeft: PrevImage(1);            break;
  case kRight:NextImage(1);            break;
  case kDown: PrevImage(3);            break;
  case kUp:   NextImage(3);            break;
  case k7:    PrevImage(5);            break;
  case k9:    NextImage(5);            break;
   
  default:                             break;
  }
  
  return osContinue;
}

//////////////////////////////////////////////////////////////////////////////
/** Handle a Key stroke on jumpmode
@return eOSState
@param eKeys Key - the processed Keycode
*/
eOSState cImageControl::ProcessKeyJumpMode(eKeys nKey)
{
  switch (nKey)
  {
  case kBack:     // Restore Originalimage
  case k0:	OriginalImage(true);          break;  
  
  case k1...k9:   //Picture select
  {
    const int nPicture = nKey - k1;
    NextImage(nPicture);
    break;
  }
    
  // Navigate between images
  case kLeft:     ConvertJump(-9);         break;
  case kRight:    ConvertJump(9);          break;
  
  default:                                 break;
  }
  
  return osContinue;
}

//////////////////////////////////////////////////////////////////////////////
/** Handle a Key stroke on jumpmode
@return eOSState
@param eKeys Key - the processed Keycode
*/
eOSState cImageControl::ProcessKeyZoomMode(eKeys nKey)
{
  switch (nKey)
  {
  // Mode select
  case k0:    OriginalImage(true);        break;  
  case kBack: 
  case k8:    ZoomOut();                  break;
  case k5:    ZoomIn();                   break;
  
  // Navigate inside image
  case kLeft: MoveZoomWindow(eLeft);      break;
  case kRight:MoveZoomWindow(eRight);     break;
  case kUp:   MoveZoomWindow(eUp);        break;
  case kDown: MoveZoomWindow(eDown);      break;
  
  default:                                break;
  }
  
  return osContinue;
}

//////////////////////////////////////////////////////////////////////////////
/** Zoom inside a image
*/
void cImageControl::ZoomIn()
{
  if(m_nZoomFactor < (m_nZoomMin + 5)) //Allow 5 Zoomlevel
  {
    ++m_nZoomFactor;
    ConvertZoom();
  }
}

//////////////////////////////////////////////////////////////////////////////
/** Zoom outside a image
*/
void cImageControl::ZoomOut()
{
  if(m_nZoomFactor > m_nZoomMin)
  {
    --m_nZoomFactor;
    ConvertZoom();
  } 
  else
  {
    OriginalImage(true);
  }
}

//////////////////////////////////////////////////////////////////////////////
/** Navigate inside a zoomed image
@param eDirection nDirection - the wished navigation direction
*/
void cImageControl::MoveZoomWindow(eDirection nDirection)
{
  bool bReZoomImage = false;
  
  switch(nDirection)
  {
    case eRight:  
      if(m_nZoomXMax > 0 && m_nMoveStepX < (m_nMaxStepX-1))
      {
        ++m_nMoveStepX;
        bReZoomImage = true;
      }      
      break;
    case eLeft:
      if(m_nZoomXMax > 0 && m_nMoveStepX > (m_nMaxStepX-1)*-1)
      {
        --m_nMoveStepX;
        bReZoomImage = true;
      }      
      break;
    case eDown:
      if(m_nZoomYMax > 0 && m_nMoveStepY < (m_nMaxStepY-1))
      {
        ++m_nMoveStepY;
        bReZoomImage = true;
      }      
      break;
    case eUp: 
      if(m_nZoomYMax > 0 && m_nMoveStepY > (m_nMaxStepY-1)*-1)
      {
        --m_nMoveStepY;
        bReZoomImage = true;
      }      
      break;
  }
  if(bReZoomImage)
    ConvertZoom();
}

//////////////////////////////////////////////////////////////////////////////
/** Check if key for pluginstop was processed
@return eOSState
@param eKeys Key - the processed Keycode
*/
eOSState cImageControl::ProcessKeyStopped()
{
  if(player)
  {
    if(ePlayModeNormal != m_ePlayMode)
    {
        OriginalImage(true);
        return osContinue;
    }
  
    if(IsConvertRunning())
        return osContinue;
  }
  
  HideOSD();
  Stop();
  return osEnd;
}


//////////////////////////////////////////////////////////////////////////////
/** Key was processed for Jumpmode
*/
void cImageControl::ProcessKeyBeginJump()
{
  m_bSlideShowBefore = m_bSlideShowActiv;
  
  m_bSlideShowActiv = false;
  
  ConvertJump(0);
  m_ePlayMode = ePlayModeJump;
}

//////////////////////////////////////////////////////////////////////////////
/** Key was processed for Zoommode
*/
void cImageControl::ProcessKeyBeginZoom()
{
  m_bSlideShowBefore = m_bSlideShowActiv;
  
  m_bSlideShowActiv = false;
  PictureZoomInitial();
  m_ePlayMode = ePlayModeZoom;
}

 //////////////////////////////////////////////////////////////////////////////
/** Toogle between all supported OSD Modes 
*/
void cImageControl::ToogleShowMode(void)
{
  switch(m_eOSDStatusVisable)
  {
    case eDisplayNothing:   m_eOSDStatusVisable = eDisplayModeOnly; break;
    case eDisplayModeOnly:  m_eOSDStatusVisable = eDisplayProgress; break;
    case eDisplayProgress:  m_eOSDStatusVisable = eDisplayNothing;  break;
  }
}

//////////////////////////////////////////////////////////////////////////////
/** Toogle between Play and Stop of the current SlideShow 
*/
void cImageControl::ToogleSlideShowActiv(void)
{
  m_nZoomFactor = 0;
  m_bSlideShowActiv = !m_bSlideShowActiv;
  m_ePlayMode = ePlayModeNormal;
}

//////////////////////////////////////////////////////////////////////////////
/** Handle a Key stroke on commandsmenu
@return eOSState
@param eKeys Key - the processed Keycode
*/
eOSState cImageControl::ProcessKeyCommands(eKeys nKey)
{
  if(m_pCmdMenu)
  {
    eOSState eOSRet = m_pCmdMenu->ProcessKey(nKey);
    switch(eOSRet)
    {
      case osEnd:
      case osBack:
        if(m_pCmdMenu->HasImageChanged())
          OriginalImage(false); 
        delete m_pCmdMenu;
        m_pCmdMenu = NULL;
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
  
    cImageCommands* pCmd = new cImageCommands;
    if(!pCmd)
      return osContinue;
      
    // Load additional Commands
    pCmd->Load(AddDirectory(cPlugin::ConfigDirectory(g_szConfigDirectory), "imagecmds.conf"));
  
    if(pCmd->Count() <= 0)  {
      delete pCmd;
      return osContinue;
    }
    
    Hide();
    
    const char* szFileName = FileName(); 
    char* szTitle; 
    asprintf(&szTitle,"%s (%s)",tr("Commands"),basename(szFileName));
    m_pCmdMenu = new cImageMenuCommands(szTitle,pCmd,szFileName);
    free(szTitle);
  
    return osContinue;
  }
}


//////////////////////////////////////////////////////////////////////////////
/** Check to get access for to viewed file
@return bool - false access was denied
*/
bool cImageControl::CheckAccess() const
{
  if(!player) // Playback stopped ?
  {
    errno = EFAULT;
    return false;
  }
  
  errno = 0; // unset error
  const char *szFileName = player->FileName();
  if(szFileName 
    && 0 == access(szFileName,F_OK))
  {
    return true;
  }        
  if(!errno) // if unknown error 
    errno = ENOENT;
  return false;
}

const char* cImageControl::szRotation [] = 
{
    "rotated", //0
    "right",   //1
    "original",//2
    "left",    //3
};

void cImageControl::OriginalImage(bool bCached)
{
  m_nZoomFactor = 0;
  m_nRotation = 2;
  m_ePlayMode = ePlayModeNormal;
  if(!CheckAccess()
    || !player->Convert(bCached?"":szRotation[m_nRotation]))
  {
    OSD_ErrorNumMsg(errno,tr("Operation failed"));
  }
}

void cImageControl::RFlipImage(void)
{
  m_ePlayMode = ePlayModeNormal;
  --m_nRotation;
  m_nRotation %= memberof(szRotation);
  
  if(!CheckAccess()
    || !player->Convert(szRotation[m_nRotation]))
  {
      OSD_ErrorNumMsg(errno,tr("Operation failed"));
  }
}

void cImageControl::LFlipImage(void)
{
  m_ePlayMode = ePlayModeNormal;
  ++m_nRotation;
  m_nRotation %= memberof(szRotation);

  if(!CheckAccess()
    || !player->Convert(szRotation[m_nRotation]))
  {
      OSD_ErrorNumMsg(errno,tr("Operation failed"));
  }
}

void cImageControl::PictureZoomInitial(void)
{
  
  char *szFileName;
  FILE *f;
  char buf[80];

  cImage* pImage = theSlideShow.GetImage();
  if(!pImage)
    return;
  
  asprintf(&szFileName, "%s.par", pImage->NamePNM());
  
  if(!szFileName)
    return;

  strncpy(m_szZoomRotation, szRotation[m_nRotation],sizeof(m_szZoomRotation));

  m_nRealImageWidth = 720;
  m_nRealImageHeight = 576;
  
  if((f = fopen(szFileName, "rt")))
  {
    dsyslog("imageplugin: open file %s", szFileName);
    fgets(buf, sizeof(buf) - 1, f);
    dsyslog("imageplugin: line=%s", buf);
    sscanf(buf, "%d %d %s", &m_nRealImageWidth,&m_nRealImageHeight,m_szZoomRotation);
    fclose(f);
  }
  else
  {
    esyslog("imageplugin: error by open file %s", szFileName);
  }
  
  free(szFileName);

  if(m_nRealImageWidth <= 0 
    || m_nRealImageWidth > 720 
    || m_nRealImageHeight > 576 )
    m_nZoomMin = 1;
  else
  {  
    m_nZoomMin = 800/m_nRealImageWidth;
  }
  if (m_nZoomMin < 0)
      m_nZoomMin = 1;
  
  // Start with minimum zoom
  m_nZoomFactor = m_nZoomMin;
  // Set Move to center
  m_nMoveStepX = 0;
  m_nMoveStepY = 0;
  
  ConvertZoom();
}

void cImageControl::ConvertZoom()
{
  if(!player)
    return;
  
  m_ePlayMode = ePlayModeZoom;

  // How may pixel are outside screen after zoom
  m_nZoomXMax = ((m_nRealImageWidth  * m_nZoomFactor) - player->UseWidth());
  m_nZoomYMax = ((m_nRealImageHeight * m_nZoomFactor) - player->UseHeight());

  // If image bigger than screen, how many step can i'm move in zoomed image
  if(m_nZoomXMax > 0)
  {  
    m_nMaxStepX = (m_nRealImageWidth  * m_nZoomFactor) /  player->UseWidth() * 2;
    if(m_nMoveStepX >= m_nMaxStepX)
      m_nMoveStepX = m_nMaxStepX;
    if(m_nMoveStepX <= -m_nMaxStepX)
      m_nMoveStepX = (m_nMaxStepX)*-1;
  }
  else 
  {
    m_nMoveStepX = 0;
    m_nMaxStepX = 0;
  }

  if(m_nZoomYMax > 0)
  {
    m_nMaxStepY = (m_nRealImageHeight * m_nZoomFactor) /  player->UseHeight() * 2;
    if(m_nMoveStepY >= m_nMaxStepY)
      m_nMoveStepY = m_nMaxStepY-1;
    if(m_nMoveStepY <= -m_nMaxStepY)
      m_nMoveStepY = (m_nMaxStepY)*-1;
  }
  else 
  {
    m_nMoveStepY = 0;
    m_nMaxStepY = 0;
  }

  // Set Offset to center
  int nZoomXoff  = m_nZoomXMax/2;
  int nZoomYoff  = m_nZoomYMax/2;
    
  // Add to offset the moved position
  if(m_nMaxStepX > 0)
    nZoomXoff += (m_nZoomXMax/m_nMaxStepX)*m_nMoveStepX;
  if(m_nMaxStepY > 0)
    nZoomYoff += (m_nZoomYMax/m_nMaxStepY)*m_nMoveStepY;

  // execute
  if(!CheckAccess()
    || !player->ConvertZoom(m_szZoomRotation, m_nZoomFactor, nZoomXoff, nZoomYoff))
  {
    OSD_ErrorNumMsg(errno,tr("Operation failed"));
  }
}

void cImageControl::ConvertJump(int nOffset)
{
  m_ePlayMode = ePlayModeJump;
  if(!CheckAccess() 
    || !player->ConvertJump(nOffset))
  {
    OSD_ErrorNumMsg(errno,tr("Operation failed"));
  }
}

bool cImageControl::IsConvertRunning() const
{
  if(player) 
   return player->IsConvertRunning();
  return false;
}


void cImageControl::NextImage(int Step)
{
  if(!player)
    return;
  if(ePlayModeNormal != m_ePlayMode)
  {
    m_ePlayMode = ePlayModeNormal;
    m_bSlideShowActiv = m_bSlideShowBefore;
  }
  if(player->NextImage(Step))
    OriginalImage(true);
  m_tStarted = time(NULL);
}



void cImageControl::PrevImage(int Step)
{
  if(!player)
    return;
  if(ePlayModeNormal != m_ePlayMode)
  {
    m_ePlayMode = ePlayModeNormal;
    m_bSlideShowActiv = m_bSlideShowBefore;
  }
  if(player->PrevImage(Step))
    OriginalImage(true);
  m_tStarted = time(NULL);
}


void cImageControl::GotoImage(int Pict)
{
  if(!player)
    return;
  if(ePlayModeNormal != m_ePlayMode)
  {
    m_ePlayMode = ePlayModeNormal;
    m_bSlideShowActiv = m_bSlideShowBefore;
  }
  if(player->GotoImage(Pict))
    OriginalImage(true);
  m_tStarted = time(NULL);
}


int cImageControl::ImageTotal(void) const
{
  if(!player)
    return 0;
  return theSlideShow.ImageTotal();
}

int cImageControl::ImageCurrent(void) const
{
  if(!player)
    return 0;
  return theSlideShow.ImageCurrent();
}

const char* cImageControl::FileName(void) const
{
  if(!player)
    return 0;
  return player->FileName();
}



void cImageControl::SlideImage()
{
  if(m_bSlideShowActiv && !IsConvertRunning())
  {
    if(ImageSetup.m_nSSsec <= 
        (time(NULL) - m_tStarted))
    {
      NextImage(1);
    }
  }
}

void cImageControl::Stop(void)
{
  delete player;
  player = NULL;
}

void cImageControl::IncSlideTime(void)
{
  if(ImageSetup.m_nSSsec < cImageSetup::m_cSSMax) {
	    ImageSetup.m_nSSsec++;
	}
}

void cImageControl::DecSlideTime(void)
{
  if(ImageSetup.m_nSSsec > cImageSetup::m_cSSMin) {
	    ImageSetup.m_nSSsec--;
	}
}
