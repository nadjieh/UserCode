ROOTINC		=-I$(shell root-config --incdir)
ROOTLIBS	=$(shell root-config --libs) -lMinuit
ROOTCFLAGS	=$(shell root-config --cflags)
ROOTGLIBS	=$(shell root-config --glibs) -lMinuit
TROOTLIBS	= -L$(HOMELIB) -lToto
ESLIBS 		= -L$(HOMELIB) -lEventSelection
BASELIBS	= -L$(HOMELIB) -lBaseBaseAnalysis
TROOTINCLUDES = -I../../../TopBrussels/TopTreeProducer/interface

MYHEADERS=-I../interface

CXX=g++

GLIBS		=$(ROOTGLIBS) 
LIBS		= $(ROOTLIBS)
LIBS		+= $(TROOTLIBS)
LIBS		+= $(ESLIBS)
HEADERS 	=$(TROOTINCLUDES)
HEADERS 	+= $(MYHEADERS)
HOMELIB		= $(HOME)/lib

all:  sas clean

sas:
	@echo "Compiling the SelectAndSave .... \n"
	$(CXX) SelectAndSave.C -c -o SelectAndSave.o -O0 $(ROOTCFLAGS) -fPIC $(HEADERS)
	@echo "Linking ...... \n"
	g++ SelectAndSave.o -o SelectAndSave $(ROOTGLIBS) $(LIBS) -g -fPIC -O0 -I/opt/root/include -m64 -pthread $(HEADERS)
	
tmp:
	@echo "Compiling the Test ...."
	g++ Test.C -c -o test.o -O0  -pthread -m64 -I/opt/root/include -fPIC 
	@echo "Linking \n\n\n\t"
	g++ test.o -o Test $(ROOTGLIBS) -g -fPIC -O0 -I/opt/root/include -m64 -pthread 
	
clean:
	@echo "Cleaning..."
	@rm -f *.o


