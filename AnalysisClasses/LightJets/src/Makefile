ObjSuf        = o
SrcSuf        = cc
ExeSuf        = 
DllSuf        = so
OutPutOpt     = -o
HeadSuf       = h

ROOTCFLAGS    = $(shell root-config --cflags)
ROOTLIBS      = $(shell root-config --libs) -lMinuit
ROOTGLIBS     = $(shell root-config --glibs) -lMinuit
TROOTLIBS = -L$(HOMELIB) -lTotoData
CHISLIB = -L$(HOMELIB) -lChiSquared385P3
EVTSELEC = -L$(HOMELIB) -lEventSelection385P3
BASELIB = -L../../../../lib/slc5_ia32_gcc434 -lBaseBaseAnalysis
TROOTINCLUDES = -I../../../TopBrussels/TopTreeProducer/interface
#BASEINCLUDE = 
# Linux with egcs
DEFINES 	= -DNO_ORCA_CLASSES
CXX		= g++
CXXFLAGS	= -O -Wall -fPIC $(DEFINES)
LD		= g++
LDFLAGS 	= -g
SOFLAGS 	= -shared

CXXFLAGS	+= $(ROOTCFLAGS)
LIBS		= $(ROOTLIBS) -lRFIO -lEG
GLIBS		= $(ROOTGLIBS)
LIBS		+= $(TROOTLIBS)
LIBS		+=$(BASELIB)
LIBS		+=$(EVTSELEC)
LIBS		+=$(CHISLIB)
#------------------------------------------------------------------------------
SOURCES 	= $(wildcard ../../../AnalysisClasses/LightJets/src/*.cc)
HEADERS 	= $(wildcard ../../../AnalysisClasses/LightJets/interface/*.h)
OBJECTS 	= $(SOURCES:.$(SrcSuf)=.$(ObjSuf))
DEPENDS 	= $(SOURCES:.$(SrcSuf)=.d)
SOBJECTS	= $(SOURCES:.$(SrcSuf)=.$(DllSuf))
HOMELIB		= /user/ajafari/lib
MV = mv -f *.o ../../../AnalysisClasses/LightJets/src/
#PROGRAMS	=  $(SOBJECTS)

all:delete libLightJets385P3.so  clean; mv libLightJets385P3.so $(HOMELIB)
delete:
	@echo "removing the old version of libLightJets385P3.so ..."
	@rm -f libLightJets385P3.so
	@echo "removed from here ..."
	@rm -f $(HOMELIB)/libLightJets385P3.so
	@echo "removed from " $(HOMELIB) " ..."
clean:
	@echo "Cleaning..."
	@rm -f *.o


.SUFFIXES: .$(SrcSuf) .C .o .so

####


.$(SrcSuf).$(ObjSuf):
	$(CXX) $(CXXFLAGS) -c $<

libLightJets385P3.so: $(OBJECTS)
	$(LD) $(LIBS) $(SOFLAGS) $(LDFLAGS) $+ -o $@
	@echo "$@ done"
