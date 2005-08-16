/***************************************************************************
 * stillimage-player.c
 * (C) Copyright  2004-2005 Andreas Brachold    <vdr04-at-deltab.de>
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
 , m_StillImage(this) 
{
}

cStillImagePlayer::~cStillImagePlayer()
{
   Detach();
}

void cStillImagePlayer::Activate(bool bOn) {
   if (bOn) {
      m_StillImage.Start();
   } else {
      m_StillImage.Stop();
   }
}

void cStillImagePlayer::Play(const uchar *Data, int Length) {
   PlayPes(Data, Length,true);
}

bool cStillImagePlayer::Wait() {
   cPoller Poller;
   return DevicePoll(Poller, 100);
}
