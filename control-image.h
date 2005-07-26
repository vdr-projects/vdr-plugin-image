/*
 * Image plugin to VDR (C++)
 *
 * (C) 2004-2005 Andreas Brachold <vdr04 -at- deltab.de>
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

// --- cImageControl ---------------------------------------------------------

#ifndef ___DVB_IMAGE_CONTROL_H
#define ___DVB_IMAGE_CONTROL_H

#include <vdr/player.h>
#if VDRVERSNUM >= 10307
#include <vdr/osdbase.h>
#endif

#define memberof(x) (sizeof(x)/sizeof(*x))

class cImagePlayer;    
class cImageMenuCommands;

class cImageControl
 : public cControl 
{
  /** All supported Replaymodes */
  enum ePlayMode { ePlayModeNormal, ePlayModeZoom, ePlayModeJump };
  /** All supported OSD Modes */
  enum eOSDStatusMode { eDisplayNothing, eDisplayModeOnly,
  eDisplayProgress
  };
  /** All move directions to navigate inside zoomed image */
  enum eDirection {eLeft = 1,eRight,eUp,eDown};
  
  /** Our one and only Imageplayer, don't rename it see cControl  */
  cImagePlayer            *player;
  /** Interface to Menu with Usercommands*/
  cImageMenuCommands      *m_pImageMenu;
  /** Current playing mode (Jump <-> Normal <-> Zoom) */
  ePlayMode               m_ePlayMode;
  /** Remember the active Slideshow mode before Jump or Zoom used */
  bool                    m_bSlideShowBefore;
  /** What should on OSD visable (Nothing <-> ModeOnly <-> Progress) */
  eOSDStatusMode          m_eOSDStatusVisable;
  /** Who was OSD Interface open (Nothing <-> ModeOnly <-> Progress) */
  eOSDStatusMode          m_eOSDStatusIsOpen;
  /** View our picture in a slideshow */
  bool                    m_bSlideShowActiv; 
  /** date at image was open*/
  time_t                  m_tStarted;
  /** Last Message for Statusmonitor */
  static char*            m_szLastShowStatusMsg;
#if VDRVERSNUM >= 10307
  /** Display replayprogress*/
  cSkinDisplayReplay *m_pDisplayReplay;
  /** Faked Marks for Images*/
  cMarks m_Marks;
#endif

  /** zoom factor on zoom mode */ 
  int                     m_nZoomFactor;
  /** minimum zoom factor (1... */
  int                     m_nZoomMin;
  /** maximum value move steps on zoom on width */
  int                     m_nMaxStepX;
  /** maximum value move steps on zoom on height */
  int                     m_nMaxStepY;
  /** current value move steps on zoom on width, 0 is center*/
  int m_nMoveStepX;
  /** current value move steps on zoom on height, 0 is center*/
  int m_nMoveStepY;
  /** How may pixel are outside screen after zoom, on width */
  int m_nZoomXMax;
  /** How may pixel are outside screen after zoom, on height */
  int m_nZoomYMax;
  /** real image pixel width*/
  int m_nRealImageWidth;
  /** real image pixel height*/
  int m_nRealImageHeight;
  
  char m_szZoomRotation[32];
  
  static const char* szRotation [];
  /** rotation mode */ 
  unsigned int m_nRotation;

private:  
  void ShowOSD(void);
  void HideOSD(void);
  void ShowMode(void);
#if VDRVERSNUM < 10307
  void DisplayAtBottom(const char *s);
#endif
  void ShowProgress(void);
  /** Send Message if changed to any statusmonitor */
  void ShowStatusMsg();
  
  void PictureZoomInitial(void);
  
  void ProcessKeyBeginJump();
  void ProcessKeyBeginZoom();
  
  /** Deliver the Status of running convert-script */
  bool IsConvertRunning() const;
  /** Deliver the current number of viewed Image */
  int ImageCurrent(void) const;
  /** Deliver the total number of viewed Image */
  int ImageTotal(void) const;
  /** Deliver the filename from the current number of viewed Image */
  const char* FileName() const;
  
  /** Check if key for pluginstop was processed*/
  eOSState ProcessKeyStopped();
  /** Toogle between all supported OSD Modes */
  void ToogleShowMode(void);
  /** Toogle between Play and Stop of the current SlideShow */
  void ToogleSlideShowActiv(void);
  
  /** Zoom inside a image*/
  void ZoomIn();
  /** Zoom outside a image*/
  void ZoomOut();
  /** Navigate inside a zoomed image */
  void MoveZoomWindow(eDirection nDirection);
  
  eOSState ProcessKeyPlayMode(eKeys nKey);
  eOSState ProcessKeyJumpMode(eKeys nKey);
  eOSState ProcessKeyZoomMode(eKeys nKey);
  eOSState ProcessKeyCommands(eKeys nKey);
  
  void NextImage(int Step);
  void PrevImage(int Step);
  void GotoImage(int Pict);
  void RFlipImage(void);
  void LFlipImage(void);
  void OriginalImage(bool bCached);
  void ConvertZoom();
  void ConvertJump(int Step);
  
  void IncSlideTime(void);
  void DecSlideTime(void);
  
  bool CheckAccess() const;
private:
  cImageControl(cSlideShow * pNewSlideShow);
public:
  virtual ~ cImageControl();

  static void SetSlideShow(cSlideShow * pNewSlideShow);

  virtual eOSState ProcessKey(eKeys Key);
  virtual void Hide(void);
  virtual void Show(void);

protected:  
  void SlideImage();
  void Stop(void);
};

#endif				//___DVB_IMAGE_CONTROL_H
