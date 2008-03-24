#
# Makefile for Image plugin to VDR
#
# (C) 2004-2007 Andreas Brachold    <anbr at users.berlios.de>
#
# This code is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation; either version 2
# of the License, or (at your option) any later version.
#
# This code is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
# Or, point your browser to http://www.gnu.org/copyleft/gpl.html

# You can change the compile options here or create a Make.config
# in the VDR directory an set them there.
#
# $Id$
#

VDRDIR = ../../../..

### The C++ compiler and options:

CXX      ?= g++
CXXFLAGS ?= -O0 -g -Wall -Woverloaded-virtual
PKG-CONFIG ?= pkg-config

-include $(VDRDIR)/Make.config

### The directory environment:


INCLUDES += -I$(VDRDIR)/include -I.
ifdef FFMDIR
INCLUDES += -I$(FFMDIR)/libavcodec -I$(FFMDIR)/libavutil
DEFINES += -DFFMDIR
ifndef WITHOUT_SWSCALER
  DEFINES += -DHAVE_SWSCALER
  INCLUDES += -I$(FFMDIR)/libswscale
endif
else

ifndef WITHOUT_SWSCALER
  DEFINES += -DHAVE_SWSCALER
  PKG-INCLUDES += libswscale
endif

  PKG-INCLUDES += libavcodec
endif

DEFINES  += -D_GNU_SOURCE

ifdef PKG-INCLUDES
INCLUDES += $(shell $(PKG-CONFIG) --cflags $(PKG-INCLUDES))
endif


### The object files (add further files here):

OBJS = encode.o stillimage.o stillimage-player.o

### Implicit rules:

%.o: %.c
	$(CXX) $(CXXFLAGS) -c $(DEFINES) $(INCLUDES) $<

# Dependencies:

MAKEDEP = $(CXX) -MM -MG
DEPFILE = .dependencies
$(DEPFILE): Makefile
	@$(MAKEDEP) $(DEFINES) $(INCLUDES) $(OBJS:%.o=%.c) > $@

-include $(DEPFILE)

### Targets:

all: liboutput.a

liboutput.a : $(OBJS)
	$(AR) $(ARFLAGS) $@ $(OBJS)
#	$(CXX) $(CXXFLAGS) -shared $(OBJS) $(LIBS) -o $@ 

clean:
	@-rm -f $(OBJS) $(DEPFILE) *.a *.so *.tgz core* *~
