CLIBS=-L/usr/lib -lstdc++

ROOTINC=-I$(shell root-config --incdir)

ROOTFLAGS=$(shell root-config --libs)

TROOTLIBS = -L/afs/cern.ch/user/a/ajafari/lib -lTRoot
BASELIBS = -L/afs/cern.ch/user/a/ajafari/scratch0/CMSSW_3_6_1_patch3/lib/slc5_ia32_gcc434 -lBaseBaseAnalysis
CHISLIB = -L/afs/cern.ch/user/a/ajafari/lib -lChiSquared361P3
EVTSELECLIB = -L/afs/cern.ch/user/a/ajafari/lib -lEventSelection361P3



TROOTINCLUDES = -I/afs/cern.ch/user/a/ajafari/scratch0/CMSSW_3_6_1_patch3/src/TopBrussels/TopTreeProducer/interface
CHISHEADERS=-I/afs/cern.ch/user/a/ajafari/scratch0/CMSSW_3_6_1_patch3/src/AnalysisClasses/ChiSquared/interface
SELECTIONHEADERS=-I/afs/cern.ch/user/a/ajafari/scratch0/CMSSW_3_6_1_patch3/src/AnalysisClasses/EventSelection/interface
CXX=g++

ROOFITROOT = $(ROOFIT_ROOT)

CFLAGS= $(shell root-config --cflags) -I$(ROOFITROOT)/include/
LDFLAGS=$(shell root-config --ldflags --glibs) -L$(ROOFITROOT)/lib/  -lRooFit -lRooFitCore

CXXFLAGS=-ggdb -O0 -Wall -fPIC -DNO_ORCA_CLASSES -pthread -g -c
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
	@echo "Compiling RooFitTest.C..."
	$(CXX) $(CXXFLAGS) $(CFLAGS) $(HEADERS) Xsec.C

	@echo "Link all shared objects..."


	gcc -o Xsec $(CLIBS) $(LDFLAGS) $(LIBS)  Xsec.o

	@echo "Cleaning up..."
	@rm -f *.o



