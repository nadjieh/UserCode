ObjSuf        = o
SrcSuf        = cc
ExeSuf        = 
DllSuf        = so
OutPutOpt     = -o
HeadSuf       = h
CLIBS		=-L/usr/lib -lstdc++
ROOTINC		=-I$(shell root-config --incdir)
ROOTLIBS	=$(shell root-config --libs) -lMinuit
ROOTCFLAGS	=$(shell root-config --cflags)
ROOTGLIBS	=$(shell root-config --glibs) -lMinuit
HOMELIB		= $(HOME)/lib

ORSOINCLUDES = -I../interface
ORSOSOURCES = ../src


CXX=g++
CXXFLAGS	= -O -Wall -fPIC
LD		= g++
LDFLAGS 	= -g
SOFLAGS 	= -shared

HEADERS 	=$(ORSOINCLUDES)


# Linux with egcs



CXXFLAGS	+= $(ROOTCFLAGS)
GLIBS		=$(ROOTGLIBS) 
LIBS		= $(ROOTLIBS) 

#------------------------------------------------------------------------------
SOURCES 	= $(wildcard $(ORSOSOURCES)/*.cc)
HEADERS 	= $(wildcard $(ORSOINCLUDES)/*.h)
OBJECTS 	= $(SOURCES:.$(SrcSuf)=.$(ObjSuf))
DEPENDS 	= $(SOURCES:.$(SrcSuf)=.d)
SOBJECTS	= $(SOURCES:.$(SrcSuf)=.$(DllSuf))




all: libTriggerTool.so clean ; 
clean:
	@echo "Cleaning..."
	@rm -f $(OBJECTS) $(DEPENDS) *Dict.* core

.SUFFIXES: .$(SrcSuf) .C .o .so

###


.$(SrcSuf).$(ObjSuf):
	$(CXX) $(CXXFLAGS) -c $<

tst:
	echo $(LD) $(LIBS) $(SOFLAGS) $(LDFLAGS) $+ -o $@

libTriggerTool.so: $(OBJECTS)
	$(LD) $(LIBS) $(SOFLAGS) $(LDFLAGS) $+ -o $@
	@echo "$@ done"
