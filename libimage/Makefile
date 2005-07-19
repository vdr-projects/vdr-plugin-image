#
# Makefile for a Video Disk Recorder plugin
#
# $Id$

VDRDIR = ../../../..

### The C++ compiler and options:

CXX      ?= g++
CXXFLAGS ?= -O0 -g -Wall -Woverloaded-virtual

-include $(VDRDIR)/Make.config

### The directory environment:


INCLUDES += -I$(VDRDIR)/include 

DEFINES  += -D_GNU_SOURCE

LIBS +=

### The object files (add further files here):

OBJS = pnm.o xpm.o

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

all: libimage.a

libimage.a : $(OBJS)
	$(AR) $(ARFLAGS) $@ $(OBJS)
#	$(CXX) $(CXXFLAGS) -shared $(OBJS) $(LIBS) -o $@ 

clean:
	@-rm -f $(OBJS) $(DEPFILE) *.a *.so *.tgz core* *~
