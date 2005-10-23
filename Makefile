#
# Makefile for a Video Disk Recorder plugin
#
# $Id$

# The official name of this plugin.
# This name will be used in the '-P...' option of VDR to load the plugin.
# By default the main source file also carries this name.
#
PLUGIN = image

### The version number of this plugin (taken from the main source file):

VERSION = $(shell grep 'static const char \*VERSION *=' $(PLUGIN).c | awk '{ print $$6 }' | sed -e 's/[";]//g')

### The C++ compiler and options:

CXX      ?= g++
CXXFLAGS ?= -fPIC -O2 -Wall -Woverloaded-virtual

### The directory environment:

DVBDIR = ../../../../DVB
VDRDIR = ../../..
LIBDIR = ../../lib
TMPDIR = /tmp
#FFMDIR = ../../../../ffmpeg

### Allow user defined options to overwrite defaults:

-include $(VDRDIR)/Make.config

### The version number of VDR (taken from VDR's "config.h"):

VDRVERSION = $(shell grep 'define VDRVERSION ' $(VDRDIR)/config.h | awk '{ print $$3 }' | sed -e 's/"//g')

### The name of the distribution archive:

ARCHIVE = $(PLUGIN)-$(VERSION)
PACKAGE = vdr-$(ARCHIVE)

### The version number of ffmpeg (taken from "libavcodec/avcodec.h" or "ffmpeg/avcodec.h" ):

ifdef FFMDIR
FFMVERSION = $(shell grep "\#define FFMPEG_VERSION_INT " $(FFMDIR)/libavcodec/avcodec.h | \
                    cut -d "x" -f 2 )
else
ifeq (,$(findstring 000,$(FFMVERSION)))
FFMVERSION = $(shell grep "\#define FFMPEG_VERSION_INT " /usr/include/ffmpeg/avcodec.h 2>/dev/null | \
                    cut -d "x" -f 2 )
endif
ifeq (,$(findstring 000,$(FFMVERSION)))
FFMVERSION = $(shell grep "\#define FFMPEG_VERSION_INT " /usr/local/include/ffmpeg/avcodec.h 2>/dev/null | \
                    cut -d "x" -f 2 )
endif
endif

### Includes and Defines (add further entries here):

INCLUDES += -I$(VDRDIR)/include -I$(DVBDIR)/include -I.
ifdef FFMDIR
INCLUDES += -I$(FFMDIR)/libavcodec -I$(FFMDIR)/libavutil
endif

DEFINES  += -DPLUGIN_NAME_I18N='"$(PLUGIN)"'
DEFINES  += -D_GNU_SOURCE
LIBS += liboutput/liboutput.a libimage/libimage.a


ifdef FFMDIR
LIBS += -L$(FFMDIR)/libavcodec
ifneq ($(FFMVERSION),000408)
LIBS += -L$(FFMDIR)/libavformat -L$(FFMDIR)/libavutil
endif
endif

LIBS += -lavcodec
ifneq ($(FFMVERSION),000408)
LIBS += -lavformat -lavutil
endif

LIBS += -lz

ifdef FFMDIR
DEFINES += -DFFMDIR
endif

### The object files (add further files here):

OBJS = ${PLUGIN}.o 
OBJS += i18n.o
OBJS += data.o
OBJS += menu.o
OBJS += data-image.o
OBJS += menu-image.o
OBJS += setup-image.o
OBJS += player-image.o
OBJS += control-image.o
OBJS += commands.o
OBJS += menu-commands.o
OBJS += list.o

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
	@cp $@ $(LIBDIR)/$@.$(VDRVERSION)


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
