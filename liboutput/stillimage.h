/*
 * Image plugin to VDR (C++)
 *
 * (C) 2004-2008 Andreas Brachold    <anbr at users.berlios.de>
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
 
#ifndef STILLIMAGE_H
#define STILLIMAGE_H

#include <vdr/thread.h>
#include "encode.h"

class cStillImagePlayer;


class cStillImage 
: public cThread 
, public cEncode {

  cStillImagePlayer *player;
  volatile bool m_bEncodeRequired;
  bool m_bUseDeviceStillPicture;
protected:
  virtual void Action(void);
  void BuildPesPacket(const unsigned char *data, int len, int timestamp);

public:
  cStillImage(cStillImagePlayer *,bool bUseDeviceStillPicture);
  virtual ~cStillImage();
  
  void Stop();
  bool EncodeRequired() const {return m_bEncodeRequired;}
  void EncodeRequired(bool b) {m_bEncodeRequired = b;}
};

#endif
