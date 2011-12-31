CLIBS=-L/usr/lib -lstdc++

ROOTINC=-I$(shell root-config --incdir)

ROOTFLAGS=$(shell root-config --libs)

TROOTLIBS = -L/user/ajafari/lib -lTotoData
BASELIBS = -L../../../../../lib/slc5_ia32_gcc434 -lBaseBaseAnalysis
CHISLIB = -L/user/ajafari/lib -lChiSquared385P3
EVTSELECLIB = -L/user/ajafari/lib -lEventSelection385P3



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
	$(CXX) $(CXXFLAGS) $(HEADERS) Individual_Chi2_FullStudy.C

	@echo "Link all shared objects..."


	gcc -o doFullChi2EffPur $(CLIBS) $(LIBS)  Individual_Chi2_FullStudy.o

	@echo "Cleaning up..."
	@rm -f *.o
allTogether:
	@echo "Compiling TestNewPackage.C..."
	$(CXX) $(CXXFLAGS) $(HEADERS) Chi2_FullStudy.C

	@echo "Link all shared objects..."


	gcc -o FullStudyAllTogether $(CLIBS) $(LIBS)  Chi2_FullStudy.o

	@echo "Cleaning up..."
	@rm -f *.o

clean: 

	@echo "Cleaning up..."

	@rm *.o


