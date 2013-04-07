ObjSuf        = o
SrcSuf        = cc
ExeSuf        = 
DllSuf        = so
OutPutOpt     = -o
HeadSuf       = h
CLIBS		=-L/usr/lib -lstdc++
ROOTINC		=-I$(shell root-config --incdir)
ROOTLIBS	=$(shell root-config --libs) -lMinuit  -lRooFit -lMinuit2
ROOTCFLAGS	=$(shell root-config --cflags)
ROOTGLIBS	=$(shell root-config --glibs) -lMinuit  -lRooFit -lMinuit2
HOMELIB		= $(HOME)/lib
TROOTINC	=-I../../../TopBrussels/TopTreeProducer/interface
PHYSOBJINC	=-I../../PhysicsObjects/interface
TOYANAINC	=-I../../ToyAnalysis/interface
BASEINC		=-I../../../Base/BaseAnalysis/interface

MYHEADERS=-I../interface
MYSOURCES= ../src
CXX=g++
CXXFLAGS	= -O -Wall -fPIC
LD		= g++
LDFLAGS 	= -g
SOFLAGS 	= -shared

CXXFLAGS	+= $(ROOTCFLAGS)
TROOTLIB	=-L$(HOMELIB) -lToto.2011
PHYSOBJLIB	=-L$(HOMELIB) -lPhysObj.2011
TOYANLIB	=-L$(HOMELIB) -lToyAnalysis.2011
BASELIB		=-L$(HOMELIB) -lBaseBaseAnalysis.2011

HEADERS 	=$(MYHEADERS)



# Linux with egcs



CXXFLAGS	+= $(ROOTCFLAGS)
GLIBS		=$(ROOTGLIBS) 
LIBS		= $(ROOTLIBS) 
LIBS		+=$(TROOTLIB)
LIBS		+=$(PHYSOBJLIB)
LIBS		+=$(TOYANLIB)
LIBS		+=$(BASELIB)
#------------------------------------------------------------------------------
SOURCES 	= $(wildcard $(MYSOURCES)/*.cc)
HEADERS 	= $(wildcard ../interface/*.h)
OBJECTS 	= $(SOURCES:.$(SrcSuf)=.$(ObjSuf))
DEPENDS 	= $(SOURCES:.$(SrcSuf)=.d)
SOBJECTS	= $(SOURCES:.$(SrcSuf)=.$(DllSuf))

HEADERS		+=$(TROOTINC)
HEADERS		+=$(PHYSOBJINC)
HEADERS		+=$(TOYANAINC)
HEADERS		+=$(BASEINC)

all: libBkgStudies.2011.so clean ; cp libBkgStudies.2011.so $(HOMELIB)

clean:
	@echo "Cleaning..."
	@rm -f $(OBJECTS) $(DEPENDS) *Dict.* core

.SUFFIXES: .$(SrcSuf) .C .o .so

###


.$(SrcSuf).$(ObjSuf):
	$(CXX) $(CXXFLAGS) -c $<

libBkgStudies.2011.so: $(OBJECTS)
	$(LD) $(LIBS) $(SOFLAGS) $(LDFLAGS) $+ -o $@
	@echo "$@ done"
