CLIBS=-L/usr/lib -lstdc++

ROOTINC=-I$(shell root-config --incdir)

ROOTFLAGS=$(shell root-config --libs)

TROOTLIBS = -L/afs/cern.ch/user/a/ajafari/lib -lTotoData
BASELIBS = -L/afs/cern.ch/user/a/ajafari/scratch0/CMSSW_3_6_1_patch3/lib/slc5_ia32_gcc434 -lBaseBaseAnalysis
CHISLIB = -L/afs/cern.ch/user/a/ajafari/lib -lChiSquared385P3
EVTSELECLIB = -L/afs/cern.ch/user/a/ajafari/lib -lEventSelection385P3



TROOTINCLUDES = -I/afs/cern.ch/user/a/ajafari/scratch0/CMSSW_3_6_1_patch3/src/TopBrussels/TopTreeProducer/interface
CHISHEADERS=-I/afs/cern.ch/user/a/ajafari/scratch0/CMSSW_3_6_1_patch3/src/AnalysisClasses/ChiSquared/interface
SELECTIONHEADERS=-I/afs/cern.ch/user/a/ajafari/scratch0/CMSSW_3_6_1_patch3/src/AnalysisClasses/EventSelection/interface
CXX=g++


CXXFLAGS=-ggdb -O0 -DDEBUG -Wall -fPIC -DNO_ORCA_CLASSES -pthread -g -c
LIBS = $(ROOTFLAGS)
LIBS	+=$(TROOTLIBS)
LIBS	+=$(BASELIBS)
LIBS	+=$(EVTSELECLIB)
LIBS	+=$(CHISLIB)
LIBS	+=$(LJETSLIB)

HEADERS = $(ROOTINC)
HEADERS +=$(TROOTINCLUDES)
HEADERS +=$(CHISHEADERS)
HEADERS +=$(SELECTIONHEADERS)


all:
	@echo "Compiling TestNewPackage.C..."
	$(CXX) $(CXXFLAGS) $(HEADERS) MassResolution.C

	@echo "Link all shared objects..."


	gcc -o plotMass $(CLIBS) $(LIBS)  MassResolution.o

	@echo "Cleaning up..."
	@rm -f *.o
Correlation:
	@echo "Compiling Macro.cc..."

	$(CXX) $(CXXFLAGS) $(ROOTINC) $(TROOTLIBS) $(TROOTINCLUDES) DelB_Mlb_Correlation.C
	@echo "Link all shared objects..."
	gcc -o CorrelationLightJets $(CLIBS) $(ROOTFLAGS) $(TROOTLIBS) $(BASELIBS) $(EVENTSELECTIONLIBS)/Event.o $(EVENTSELECTIONLIBS)/EventSelector.o TopQuark.o HadronicW.o TopQuark.o DR.o Combination.o Combinator.o DelB_Mlb_Correlation.o

clean: 

	@echo "Cleaning up..."

	@rm *.o



Test:
	@echo "Compiling TestNewPackage.C ... "
	$(CXX) $(CXXFLAGS) $(ROOTINC) $(TROOTLIBS) $(TROOTINCLUDES) $(MYHEADERS) $(SELECTIONHEADER) $(LIGHTJETSHEADER) TestNewPackage.C
	@echo "Link all shared objects..."
	gcc -o TestNewPackage $(CLIBS) $(ROOTFLAGS) $(TROOTLIBS) $(BASELIBS)   TopQuark.o HadronicW.o TopQuark.o DR.o Combination.o Combinator.o SpecificEffHandler.o TestNewPackage.o


