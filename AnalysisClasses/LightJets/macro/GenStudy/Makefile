CLIBS=-L/usr/lib -lstdc++

ROOTINC=-I$(shell root-config --incdir)

ROOTFLAGS=$(shell root-config --libs)
HOMELIB=$(HOME)/lib
TROOTLIBS = -L$(HOMELIB) -lTRoot
BASELIBS = -L$(HOMELIB) -lBaseBaseAnalysis
CHISLIB = -L/user/ajafarilib -lChiSquared361P3
EVTSELECLIB = -L$(HOMELIB) -lEventSelection361P3
LJETSLIB = -L$(HOMELIB) -lLightJets361P3


TROOTINCLUDES = -I../../../../AnalysisDataFormats/TopTree/interface
CHISHEADERS=-I../../../../AnalysisClasses/ChiSquared/interface
LIGHTHEADERS=-I../../../../AnalysisClasses/LightJets/interface
SELECTIONHEADERS=-I/user/ajafari/scratch0/CMSSW_3_6_1_patch3/src/AnalysisClasses/EventSelection/interface
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
HEADERS +=$(LIGHTHEADERS)
HEADERS +=$(SELECTIONHEADERS)


all:
	@echo "Compiling TestNewPackage.C..."
	$(CXX) $(CXXFLAGS) $(HEADERS) SignalStudy.C

	@echo "Link all shared objects..."


	gcc -o StudyTheSignal $(CLIBS) $(LIBS)  SignalStudy.o

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


