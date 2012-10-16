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

PHYSOBJINC = -I../../AnalysisClasses/PhysicsObjects/interface/
TOYINCLUDES = -I../../AnalysisClasses/ToyAnalysis/interface/

CXX=g++
CXXFLAGS	= -O -Wall -fPIC
LD		= g++
LDFLAGS 	= -g
SOFLAGS 	= -shared

HEADERS 	=$(ORSOINCLUDES)

PHYSOBJLIB	=-L$(HOMELIB) -lPhysObj.2011
TOYLIB	=-L$(HOMELIB) -lToyAnalysis.2011

# Linux with egcs



CXXFLAGS	+= $(ROOTCFLAGS)
GLIBS		=$(ROOTGLIBS) 
LIBS		= $(ROOTLIBS) 
LIBS		+= $(PHYSOBJLIB)
LIBS		+= $(TOYLIB)
#------------------------------------------------------------------------------
SOURCES 	= $(wildcard $(ORSOSOURCES)/*.cc)
HEADERS 	= $(wildcard $(ORSOINCLUDES)/*.h)
OBJECTS 	= $(SOURCES:.$(SrcSuf)=.$(ObjSuf))
DEPENDS 	= $(SOURCES:.$(SrcSuf)=.d)
SOBJECTS	= $(SOURCES:.$(SrcSuf)=.$(DllSuf))


HEADERS 	+= $(PHYSOBJINC)
HEADERS 	+= $(TOYINCLUDES)
#PROGRAMS	=  $(SOBJECTS)

all: libOrsoNtuples.2012.so clean ; cp libOrsoNtuples.2012.so $(HOMELIB)

clean:
	@echo "Cleaning..."
	@rm -f $(OBJECTS) $(DEPENDS) *Dict.* core

.SUFFIXES: .$(SrcSuf) .C .o .so

###


.$(SrcSuf).$(ObjSuf):
	$(CXX) $(CXXFLAGS) -c $<

tst:
	echo $(LD) $(LIBS) $(SOFLAGS) $(LDFLAGS) $+ -o $@

libOrsoNtuples.2012.so: $(OBJECTS)
	$(LD) $(LIBS) $(SOFLAGS) $(LDFLAGS) $+ -o $@
	@echo "$@ done"
