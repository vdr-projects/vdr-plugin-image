/*
 * Image plugin to VDR (C++)
 *
 * (C) Copyright  2004-2008 Andreas Brachold    <anbr at users.berlios.de>
 *  Created: Thu Aug  5 2004
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
 
#ifndef STILLIMAGEPLAYER_H
#define STILLIMAGEPLAYER_H

#include <vdr/thread.h>
#include <vdr/player.h>

#include "stillimage.h"

class cStillImagePlayer
  : public cPlayer {
  friend class cStillImage;
protected:  
  cStillImage m_StillImage;
public:
  cStillImagePlayer(ePlayMode PlayMode,bool bUseDeviceStillPicture);
  virtual ~cStillImagePlayer();

  inline unsigned int UseWidth() const           
    { return m_StillImage.GetWidth() - (m_StillImage.GetBorderWidth()*2);  } 
  inline unsigned int UseHeight() const          
    { return m_StillImage.GetHeight() - (m_StillImage.GetBorderHeight()*2); } 
protected:
  virtual void Activate(bool On);
  void Play(const uchar *Data, int Length);
  bool Wait();
  
  virtual bool Worker(bool bDoIt) = 0;
};


#endif
