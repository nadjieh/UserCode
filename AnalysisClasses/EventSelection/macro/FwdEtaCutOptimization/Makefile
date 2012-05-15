ROOTINC		=-I$(shell root-config --incdir)
ROOTLIBS	=$(shell root-config --libs) -lMinuit
ROOTCFLAGS	=$(shell root-config --cflags)
ROOTGLIBS	=$(shell root-config --glibs) -lMinuit
HOMELIB		= $(HOME)/lib
TROOTLIBS	= -L$(HOMELIB) -lToto
ESLIBS 		= -L$(HOMELIB) -lEventSelection
PULIBS		= -L$(HOMELIB) -lLumi3DRW
JETTOOLS	= -L$(HOMELIB) -lTools
RECOLIBS	= -L$(HOMELIB) -lReco
PHYSOBJLIBS	= -L$(HOMELIB) -lPhysObj
TOYLIBS		= -L$(HOMELIB) -lToyAnalysis
BASELIB		=-L$(HOMELIB) -lBaseBaseAnalysis

TROOTINCLUDES   = -I../../../../TopBrussels/TopTreeProducer/interface
PUINCLUDES	=-I../../../../TopBrussels/TopTreeAnalysis/MCInformation/interface/
JETINCLUDES	=-I../../../../TopBrussels/TopTreeAnalysis/Tools/interface/
RECOINCLUDES	=-I../../../../TopBrussels/TopTreeAnalysis/Reconstruction/interface/
PHYSOBJINCS	=-I../../../PhysicsObjects/interface/
ESINCLUDES	=-I../../../EventSelection/interface/
BASEINC		=-I../../../../Base/BaseAnalysis/interface


MYHEADERS=-I../../interface

CXX=g++


#LIBS		= $(ROOTLIBS)
LIBS		= $(TROOTLIBS)
LIBS		+= $(ESLIBS)
LIBS		+= $(PULIBS)
LIBS		+= $(JETTOOLS)
LIBS		+= $(RECOLIBS)
LIBS		+= $(PHYSOBJLIBS)
LIBS		+=$(BASELIB)

HEADERS 	=$(TROOTINCLUDES)
HEADERS		+=$(PUINCLUDES)
HEADERS		+=$(JETINCLUDES)
HEADERS 	+=$(RECOINCLUDES)
HEADERS 	+=$(ESINCLUDES)
HEADERS 	+=$(PHYSOBJINCS)
HEADERS		+= $(BASEINC)
all:  FWD clean


FWD:
	@echo "Compiling the CutOptimizer .... \n"
	$(CXX) CutOptimizer.C -c -o CutOptimizer.o -O0 $(ROOTCFLAGS) -fPIC $(HEADERS)
	@echo "Linking ...... \n"
	g++ CutOptimizer.o -o GetOptimization $(ROOTGLIBS) -lEG $(LIBS) -g -fPIC -O0 -I/opt/root/include -m64 -pthread $(HEADERS)
clean:
	@echo "Cleaning..."
	@rm -f *.o
	@rm -f *~
	@rm -f ../../interface/*.gch
