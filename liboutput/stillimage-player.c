/***************************************************************************
 * stillimage-player.c
 * (C) Copyright  2004 Andreas Brachold    <vdr04-at-deltab.de>
 *  Created: Thu Aug  5 2004
 * 
 ****************************************************************************/

/*
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Library General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#include "stillimage-player.h"
#include "stillimage.h"

cStillImagePlayer::cStillImagePlayer(ePlayMode PlayMode)
 : cPlayer(PlayMode)
 , m_bActive(false)
 , m_StillImage(this) 
{
}

cStillImagePlayer::~cStillImagePlayer()
{
   Detach();
}

void cStillImagePlayer::Activate(bool On) {
   if (On) {
      m_bActive=m_StillImage.Init();
   } else {
      if (m_bActive) {
         m_StillImage.Stop();
         m_bActive=false;
      }
   }
}

void cStillImagePlayer::Play(const uchar *Data, int Length) {
#if VDRVERSNUM < 10318
   PlayVideo(Data, Length);
#else
   PlayPes(Data, Length,true);
#endif
}

bool cStillImagePlayer::Wait() {
   cPoller Poller;
   return DevicePoll(Poller, 100);
}
