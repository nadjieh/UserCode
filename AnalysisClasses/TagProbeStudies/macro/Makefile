CLIBS=-L/usr/lib -lstdc++

ROOTINC=-I$(shell root-config --incdir)

ROOTFLAGS=$(shell root-config --libs)
HOMELIB=$(HOME)/lib
TROOTLIBS = -L$(HOMELIB) -lTotoData
BASELIBS = -L$(HOMELIB)- lBaseBaseAnalysis
CHISLIB = -L$(HOMELIB) -lChiSquared385P3
EVTSELECLIB = -L$(HOMELIB) -lEventSelection385P3
LJETSLIB = -L$(HOMELIB) -lLightJets385P3


TROOTINCLUDES = -I../../../AnalysisDataFormats/TopTree/interface
CHISHEADERS=-I../../../AnalysisClasses/ChiSquared/interface
LIGHTHEADERS=-I../../../AnalysisClasses/LightJets/interface
SELECTIONHEADERS=-I../../../AnalysisClasses/EventSelection/interface
TAGPROBEHEADERS=-I../../../AnalysisClasses/TagProbeStudies/interface
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
HEADERS +=$(TAGPROBEHEADERS)

all:
	@echo "Compiling TPObjectProducer.C..."
	$(CXX) $(CXXFLAGS) $(HEADERS) ZTagAndProbeAnalyzer.cc

	@echo "Link all shared objects..."


	gcc -o AnalyzeZ $(CLIBS) $(LIBS)  ZTagAndProbeAnalyzer.o

	@echo "Cleaning up..."
	@rm -f *.o
T:
	@echo "Compiling TPObjectProducer.C..."
	$(CXX) $(CXXFLAGS) $(HEADERS) TTagProbeAnalyzer.cc

	@echo "Link all shared objects..."


	gcc -o AnalyzeTop $(CLIBS) $(LIBS)  TTagProbeAnalyzer.o

	@echo "Cleaning up..."
	@rm -f *.o
SBS:
	@echo "Compiling SBS_Eff.C..."
	$(CXX) $(CXXFLAGS) $(HEADERS) SBS_Eff.C

	@echo "Link all shared objects..."


	gcc -o subtractSB $(CLIBS) $(LIBS)  SBS_Eff.o

	@echo "Cleaning up..."
	@rm -f *.o

test:
	@echo "Compiling TPObjectProducer.C..."
	$(CXX) $(CXXFLAGS) $(HEADERS) my.cc

	@echo "Link all shared objects..."


	gcc -o Test $(CLIBS) $(LIBS)  my.o

	@echo "Cleaning up..."
	@rm -f *.o




#220468
