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
TROOTLIBS	= -L$(HOMELIB) -lToto
JETCORRLIB 		= -L$(HOMELIB) -lJetCorrection385P3

TROOTINCLUDES = -I../../../TopBrussels/TopTreeProducer/interface
JETCORRINCLUDES = -I../../JetCorrections/interface

MYHEADERS=-I../interface
MYSOURCES= ../src
CXX=g++
CXXFLAGS	= -O -Wall -fPIC
LD		= g++
LDFLAGS 	= -g
SOFLAGS 	= -shared

CXXFLAGS	+= $(ROOTCFLAGS)
LIBS		= $(ROOTFLAGS)
LIBS		+= $(TROOTLIBS)
#LIBS		+= $(JETCORRLIB)

HEADERS 	=$(TROOTINCLUDES)
HEADERS 	+=$(MYHEADERS)
#HEADERS         +=$(JETCORRINCLUDES)


# Linux with egcs



CXXFLAGS	+= $(ROOTCFLAGS)
GLIBS		=$(ROOTGLIBS) 
LIBS		= $(ROOTLIBS) 
LIBS		+= $(TROOTLIBS)
#LIBS		+= $(ESLIBS)
#------------------------------------------------------------------------------
SOURCES 	= $(wildcard $(MYSOURCES)/*.cc)
HEADERS 	= $(wildcard ../interface/*.h)
OBJECTS 	= $(SOURCES:.$(SrcSuf)=.$(ObjSuf))
DEPENDS 	= $(SOURCES:.$(SrcSuf)=.d)
SOBJECTS	= $(SOURCES:.$(SrcSuf)=.$(DllSuf))
HOMELIB		= $(HOME)/lib

#PROGRAMS	=  $(SOBJECTS)

all: libEventSelection.so clean ; cp libEventSelection.so $(HOMELIB)

clean:
	@echo "Cleaning..."
	@rm -f $(OBJECTS) $(DEPENDS) *Dict.* core

.SUFFIXES: .$(SrcSuf) .C .o .so

###


.$(SrcSuf).$(ObjSuf):
	$(CXX) $(CXXFLAGS) -c $<

libEventSelection.so: $(OBJECTS)
	$(LD) $(LIBS) $(SOFLAGS) $(LDFLAGS) $+ -o $@
	@echo "$@ done"
