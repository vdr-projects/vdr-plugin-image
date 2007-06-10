#
# Makefile for a Video Disk Recorder plugin
#
# $Id$

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
else
  INCLUDES += $(shell $(PKG-CONFIG) --cflags libavcodec)
endif

DEFINES  += -D_GNU_SOURCE

ifndef WITHOUT_SWSCALER
  DEFINES += -DHAVE_SWSCALER
  INCLUDES += $(shell $(PKG-CONFIG) --cflags libswscale)
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
