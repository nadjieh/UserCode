ROOTINC		=-I$(shell root-config --incdir)
ROOTLIBS	=$(shell root-config --libs) -lMinuit -lTMVA
ROOTCFLAGS	=$(shell root-config --cflags)
ROOTGLIBS	=$(shell root-config --glibs) -lMinuit -lTMVA
HOMELIB		= $(HOME)/lib
TROOTLIBS	= -L$(HOMELIB) -lToto
ESLIBS 		= -L$(HOMELIB) -lEventSelection
PULIBS		= -L$(HOMELIB) -lLumi3DRW
JETTOOLS	= -L$(HOMELIB) -lTools
RECOLIBS	= -L$(HOMELIB) -lReco
TROOTINCLUDES   = -I../../../../TopBrussels/TopTreeProducer/interface
PUINCLUDES	=-I../../../../TopBrussels/TopTreeAnalysis/MCInformation/interface/
JETINCLUDES	=-I../../../../TopBrussels/TopTreeAnalysis/Tools/interface/
RECOINCLUDES	=-I../../../../TopBrussels/TopTreeAnalysis/Reconstruction/interface/
MYHEADERS=-I../../interface

CXX=g++


#LIBS		= $(ROOTLIBS)
LIBS		= $(TROOTLIBS)
#LIBS		+= $(ESLIBS)
#LIBS		+= $(PULIBS)
#LIBS		+= $(JETTOOLS)
#LIBS		+= $(RECOLIBS)
HEADERS 	=$(TROOTINCLUDES)
#HEADERS		+=$(PUINCLUDES)
#HEADERS		+=$(JETINCLUDES)
#HEADERS 	+=$(RECOINCLUDES)


all:  input classifier clean

input:
	@echo "Compiling the InputForTMVA.C .... \n"
	$(CXX) InputForTMVA.C -c -o InputForTMVA.o -O0 $(ROOTCFLAGS) -fPIC $(HEADERS)
	@echo "Linking ...... \n"
	g++ InputForTMVA.o -o PrepareInput $(ROOTGLIBS) -lEG $(LIBS) -g -fPIC -O0 -I/opt/root/include -m64 -pthread $(HEADERS)
	
classifier:
	@echo "Compiling the Classification.C ...."
	g++ Classification.C -c -o Classification.o -O0  $(ROOTCFLAGS) -fPIC $(HEADERS)
	@echo "Linking \n\n\n\t"
	g++ Classification.o -o Classify  $(ROOTGLIBS) -lEG $(LIBS) -g -fPIC -O0 -I/opt/root/include -m64 -pthread $(HEADERS)
	
clean:
	@echo "Cleaning..."
	@rm -f *.o
	@rm -f *~

