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
	$(CXX) $(CXXFLAGS) $(HEADERS) Pseudo.C

	@echo "Link all shared objects..."


	gcc -o Psuedo $(CLIBS) $(LIBS)  Pseudo.o

	@echo "Cleaning up..."
	@rm -f *.o
Asymm:
	@echo "Compile Asymm ..."
	$(CXX) $(CXXFLAGS) $(ROOTINC) AsymmSub.C
	@echo "Link all shared objects..."
	gcc -o doMethodError $(CLIBS) $(ROOTFLAGS)  AsymmSub.o
	@echo "Cleaning up..."
	@rm -f *.o
