#
# Makefile for Image plugin to VDR
#
# (C) 2004-2006 Andreas Brachold    <anbr at users.berlios.de>
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

### uncomment the following line, if you don't have libexif installed
#WITHOUT_LIBEXIF=1

#FFMDIR = ../../../../ffmpeg


### The C++ compiler and options:

CXX      ?= g++
CXXFLAGS ?= -fPIC -O2 -Wall -Woverloaded-virtual

###############################################
###############################################
#
# no user configurable options below this point
#
###############################################
###############################################

### The directory environment:

VDRDIR = ../../..
LIBDIR = ../../lib
TMPDIR = /tmp

### Allow user defined options to overwrite defaults:

-include $(VDRDIR)/Make.config

# The official name of this plugin.
# This name will be used in the '-P...' option of VDR to load the plugin.
# By default the main source file also carries this name.
#
PLUGIN = image

### The version number of this plugin (taken from the main source file):

VERSION = $(shell grep 'static const char \*VERSION *=' $(PLUGIN).c | awk '{ print $$6 }' | sed -e 's/[";]//g')

### The version number of VDR (taken from VDR's "config.h"):

APIVERSION = $(shell grep 'define APIVERSION ' $(VDRDIR)/config.h | awk '{ print $$3 }' | sed -e 's/"//g')

### The name of the distribution archive:

ARCHIVE = $(PLUGIN)-$(VERSION)
PACKAGE = vdr-$(ARCHIVE)

### The version number of ffmpeg (taken from "libavcodec/avcodec.h" ):

ifdef FFMDIR
LIBAVCODECVERSION = $(shell grep "\#define LIBAVCODEC_VERSION " $(FFMDIR)/libavcodec/avcodec.h | \
                    awk '{ print $$3 }' | cut -d "." -f 1 )
endif

### Includes and Defines (add further entries here):


DEFINES  += -DPLUGIN_NAME_I18N='"$(PLUGIN)"'
DEFINES  += -D_GNU_SOURCE
LIBS += liboutput/liboutput.a libimage/libimage.a

INCLUDES += -I$(VDRDIR)/include -I.

ifdef FFMDIR
INCLUDES += -I$(FFMDIR)/libavcodec -I$(FFMDIR)/libavutil
LIBS += -L$(FFMDIR)/libavcodec
ifeq ($(LIBAVCODECVERSION),51)
LIBS += -L$(FFMDIR)/libavformat -L$(FFMDIR)/libavutil
LIBS += -lavformat -lavutil
endif
endif

LIBS += -lavcodec
LIBS += -lz

ifdef FFMDIR
DEFINES += -DFFMDIR
endif

ifndef WITHOUT_LIBEXIF
  LIBS    += -lexif
  DEFINES += -DHAVE_LIBEXIF
endif

### The object files (add further files here):

OBJS = ${PLUGIN}.o i18n.o data.o menu.o data-image.o menu-image.o \
 setup-image.o player-image.o control-image.o commands.o menu-commands.o \
 list.o


ifndef WITHOUT_LIBEXIF
  OBJS    += exif.o
endif

### The subdirectories:

SUBDIRS = liboutput libimage

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

all: subdirs libvdr-$(PLUGIN).so 

libvdr-$(PLUGIN).so: $(OBJS)
	$(CXX) $(CXXFLAGS) -shared -export-dynamic $(OBJS) $(LIBS) -o $@
	@cp $@ $(LIBDIR)/$@.$(APIVERSION)


subdirs:
	@for i in $(SUBDIRS) ;\
	do \
	    ( cd $$i;\
              $(MAKE) all;\
       ) \
	|| exit 1;\
	done

dist: clean
	@-rm -rf $(TMPDIR)/$(ARCHIVE)
	@mkdir $(TMPDIR)/$(ARCHIVE)
	@cp -a * $(TMPDIR)/$(ARCHIVE)
	@chmod 644 -R $(TMPDIR)/$(ARCHIVE)/*
	@find $(TMPDIR)/$(ARCHIVE) -name "*.sh" -exec chmod 755 {} \;
	@find $(TMPDIR)/$(ARCHIVE) -type d -exec chmod 755 {} \;
	@chown root.root -R $(TMPDIR)/$(ARCHIVE)/*
	@tar czf $(PACKAGE).tar.gz --exclude=.svn -C $(TMPDIR) $(ARCHIVE)
	@-rm -rf $(TMPDIR)/$(ARCHIVE)
	@echo Distribution package created as $(PACKAGE).tar.gz

clean:
	@-rm -f $(OBJS) $(DEPFILE) *.so *.tar.gz core* *~ contrib/*~  examples/*~ scripts/*~
	@for i in $(SUBDIRS) ;\
	do \
	    ( cd $$i;\
              $(MAKE) clean;\
       ) \
	|| exit 1;\
	done
