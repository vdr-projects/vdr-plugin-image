/*
 * Image plugin to VDR (C++)
 *
 * (C) 2004 Andreas Brachold    <vdr04-at-deltab.de>
 *     2003 Kai Tobias Burwieck <kai@burwieck.net>
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

#ifndef ___DVB_IMAGE_H
#define ___DVB_IMAGE_H

#include <vector>
#define __STL_CONFIG_H

#include <vdr/thread.h>
#include <vdr/player.h>
#include <liboutput/stillimage-player.h>

class cImage;
class cSlideShow;    

struct cShellWrapper {
    
  char* szCmd;
  char* szPNM;
  char  szNumber;
  bool bClearBackground;
  unsigned int nOffLeft;
  unsigned int nOffTop;
  unsigned int nWidth;
  unsigned int nHeight;

  cShellWrapper()
  : szCmd(NULL)
  , szPNM(NULL)
  , szNumber('\0')
  {
  }

  virtual ~cShellWrapper() {
    if(szPNM)
      free(szPNM);
    if(szCmd)
      free(szCmd);
  }
};

struct cShellWrapperQueue
 : public std::vector<cShellWrapper*>
{
  virtual ~cShellWrapperQueue()
  {
    iterator i = begin();
    const_iterator e = end();
    for(;e!=i;++i)
        delete(*i);
    clear();
  }

  inline size_t max_size() const 
  {
    return 64;
  }

  inline bool add(cShellWrapper* pCmd) {
    if(size()<max_size())
    {
      if(NULL == pCmd->szPNM || !pCmd->bClearBackground) //Pregeneration or Index
        push_back(pCmd);
      else { 
        // Remove all other viewed images from queue
        iterator i = begin();
        while(end()!=i) {
          if((*i)->szPNM) {
            delete(*i);
            erase(i);
            }
          else
            ++i;
          }
        //Place next viewed image at front of the queue
        insert(begin(),pCmd);
      }
      return true;
    }  
    return false;
  }
  
};

class cImagePlayer
: public cStillImagePlayer
{
    
  volatile bool               m_bConvertRunning;

  cMutex                      m_Mutex;
  cShellWrapperQueue          m_queue;
  cMutex                      m_MutexErr;
  char*                       m_szError;
protected:
  void Exec(cShellWrapper* pCmd);

  void LoadImage(cShellWrapper* pShell);
  /** Show Errorimage if operation failed*/
  void ExecFailed(cShellWrapper* pShell,const char* szErr);

  virtual void Activate(bool On);
  virtual bool Worker(bool bDoIt);
public:

  cImagePlayer(cSlideShow *pCurSlideShow);
  virtual ~ cImagePlayer();
  bool IsConvertRunning() const { return m_bConvertRunning; };
  bool NextImage(int Step);
  bool PrevImage(int Step);
  bool GotoImage(unsigned int nNewPictureIndex);
  
  /** Deliver the filename from the current number of viewed Image */
  const char* FileName(void) const;

  bool Convert(const char *szChange);
  bool ConvertZoom(const char *szChange, int nZoomFaktor,
			       int nLeftPos, int nTopPos);
  bool ConvertJump(int Step);
  
  /** Returns the current and total frame index, optionally snapped to the
  nearest I-frame.*/
  virtual bool GetIndex(int &Current, int &Total, bool SnapToIFrame);
  /** ThreadSafe Method to show messages from Worker thread*/
  void ErrorMsg();
};

#endif				//__DVB_IMAGE_H