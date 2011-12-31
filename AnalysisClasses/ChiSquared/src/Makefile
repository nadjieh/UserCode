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
BASELIB = -L/user/ajafari/CMSSW_3_8_5_patch3/lib/slc5_ia32_gcc434/ -lBaseBaseAnalysis
TROOTINCLUDES = -I/user/ajafari/CMSSW_3_8_5_patch3/src/TopBrussels/TopTreeProducer/interface
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
#------------------------------------------------------------------------------
SOURCES 	= $(wildcard /user/ajafari/CMSSW_3_8_5_patch3/src/AnalysisClasses/ChiSquared/src/*.cc)
HEADERS 	= $(wildcard /user/ajafari/CMSSW_3_8_5_patch3/src/AnalysisClasses/ChiSquared/interface/*.h)
OBJECTS 	= $(SOURCES:.$(SrcSuf)=.$(ObjSuf))
DEPENDS 	= $(SOURCES:.$(SrcSuf)=.d)
SOBJECTS	= $(SOURCES:.$(SrcSuf)=.$(DllSuf))
HOMELIB		= /user/ajafari/lib
MV = mv -f *.o /user/ajafari/CMSSW_3_8_5_patch3/src/AnalysisClasses/ChiSquared/src/
#PROGRAMS	=  $(SOBJECTS)

all: delete libChiSquared385P3.so clean ; cp libChiSquared385P3.so $(HOMELIB)
delete:
	@echo "removing the previous version of libChiSquared385P3.so ..."
	@rm -f libChiSquared385P3.so
	@rm -f $(HOMELIB)/libChiSquared385P3.so
clean:
	@echo "Cleaning..."
	@rm -f $(OBJECTS) $(DEPENDS) *Dict.* core
	@rm -f ../../../AnalysisDataFormats/TopTree/src/*.o

.SUFFIXES: .$(SrcSuf) .C .o .so

###


.$(SrcSuf).$(ObjSuf):
	$(CXX) $(CXXFLAGS) -c $<

libChiSquared385P3.so: $(OBJECTS)
	$(LD) $(LIBS) $(SOFLAGS) $(LDFLAGS) $+ -o $@
	@echo "$@ done"
