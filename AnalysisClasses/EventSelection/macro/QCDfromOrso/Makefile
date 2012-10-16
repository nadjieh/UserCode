ROOTINC		=-I$(shell root-config --incdir)
ROOTLIBS	=$(shell root-config --libs) -lMinuit
ROOTCFLAGS	=$(shell root-config --cflags)
ROOTGLIBS	=$(shell root-config --glibs) -lMinuit
TROOTLIBS	= -L$(HOMELIB) -lToto.2011
ESLIBS 		= -L$(HOMELIB) -lEventSelection.2011
BASELIBS	= -L$(HOMELIB) -lBaseBaseAnalysis.2011
TROOTINCLUDES = -I../../../TopBrussels/TopTreeProducer/interface

MYHEADERS=-I../interface

CXX=g++

GLIBS		=$(ROOTGLIBS) 
LIBS		= $(ROOTLIBS)
LIBS		+= $(TROOTLIBS)
LIBS		+= $(ESLIBS)
HEADERS 	+=$(TROOTINCLUDES)
HEADERS 	+= $(MYHEADERS)
HOMELIB		= $(HOME)/lib

all:  qcd clean


qcd:
	@echo "Compiling the SelectAndSave .... \n"
	$(CXX) QCDHistogramCreator.C -c -o QCDHistogramCreator.o -O0 $(ROOTCFLAGS) -fPIC $(HEADERS) -g
	@echo "Linking ...... \n"
	g++ QCDHistogramCreator.o -o QCDHistogramCreator $(ROOTGLIBS) $(LIBS) -g -fPIC -O0 -I/opt/root/include -m64 -pthread $(HEADERS)

clean:
	@echo "Cleaning..."
	@rm -f *.o


