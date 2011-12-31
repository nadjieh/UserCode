CLIBS=-L/usr/lib -lstdc++

ROOTINC=-I$(shell root-config --incdir)

ROOTFLAGS=$(shell root-config --libs)

TROOTLIBS = -L/user/ajafari/lib -lTRoot
BASELIBS = -L../../../../../lib/slc5_ia32_gcc434 -lBaseBaseAnalysis
CHISLIB = -L/user/ajafari/lib -lChiSquared361P3
EVTSELECLIB = -L/user/ajafari/lib -lEventSelection361P3
LJETSLIB = -L/user/ajafari/lib -lLightJets361P3


TROOTINCLUDES = -I../../../../AnalysisDataFormats/TopTree/interface
CHISHEADERS=-I../../../../AnalysisClasses/ChiSquared/interface
LIGHTHEADERS=-I../../../../AnalysisClasses/LightJets/interface
SELECTIONHEADERS=-I../../../../AnalysisClasses/EventSelection/interface
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
	$(CXX) $(CXXFLAGS) $(HEADERS) FullStudy7TeV.C

	@echo "Link all shared objects..."


	gcc -o StudySysSignal $(CLIBS) $(LIBS)  FullStudy7TeV.o

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


