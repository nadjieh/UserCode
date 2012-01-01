CLIBS=-L/usr/lib -lstdc++

ROOTINC=-I$(shell root-config --incdir)

ROOTFLAGS=$(shell root-config --libs)
HOMELIB = $(HOME)/lib
TROOTLIBS = -L$(HOMELIB) -lTRoot
BASELIBS = -L$(HOMELIB) -lBaseBaseAnalysis
CHISLIB = -L$(HOMELIB) -lChiSquared361P3
EVTSELECLIB = -L$(HOMELIB) -lEventSelection361P3



TROOTINCLUDES = -I../../../../TopBrussels/TopTreeProducer/interface
CHISHEADERS=-I../../../../AnalysisClasses/ChiSquared/interface
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
HEADERS +=$(SELECTIONHEADERS)


all:
	@echo "Compiling TestNewPackage.C..."
	$(CXX) $(CXXFLAGS) $(HEADERS) LightStudy.C

	@echo "Link all shared objects..."


	gcc -o StudyLightJets_v5 $(CLIBS) $(LIBS)  LightStudy.o

	@echo "Cleaning up..."
	@rm -f *.o
allTogether:
	@echo "Compiling TestNewPackage.C..."
	$(CXX) $(CXXFLAGS) $(HEADERS) Chi2_FullStudy.C

	@echo "Link all shared objects..."


	gcc -o FullStudyAllTogether $(CLIBS) $(LIBS)  Chi2_FullStudy.o

	@echo "Cleaning up..."
	@rm -f *.o
printOut:
	@echo "Compiling PrintOut.C..."
	$(CXX) $(CXXFLAGS) $(ROOTINC) PrintOut.C

	@echo "Link all shared objects..."


	gcc -o printInfo $(CLIBS) $(ROOTFLAGS)  PrintOut.o

	@echo "Cleaning up..."
	@rm -f *.o
divide:
	@echo "Compiling divideCode.C..."
	$(CXX) $(CXXFLAGS) $(ROOTINC) divideCode.C

	@echo "Link all shared objects..."


	gcc -o Divide $(CLIBS) $(ROOTFLAGS)  divideCode.o

	@echo "Cleaning up..."
	@rm -f *.o
clean: 

	@echo "Cleaning up..."

	@rm *.o



