ROOTINC		=-I$(shell root-config --incdir)
ROOTLIBS	=$(shell root-config --libs) -lMinuit
ROOTCFLAGS	=$(shell root-config --cflags)
ROOTGLIBS	=$(shell root-config --glibs) -lMinuit
HOMELIB		= $(HOME)/lib
TROOTLIBS	= -L$(HOMELIB) -lToto.2011
ESLIBS 		= -L$(HOMELIB) -lEventSelection.2011
PULIBS		= -L$(HOMELIB) -lLumi3DRW.2011
JETTOOLS	= -L$(HOMELIB) -lTools.2011
RECOLIBS	= -L$(HOMELIB) -lReco.2011
PHYSOBJLIBS	= -L$(HOMELIB) -lPhysObj.2011
TOYLIBS		= -L$(HOMELIB) -lToyAnalysis.2011
TROOTINCLUDES   = -I../../../TopBrussels/TopTreeProducer/interface
PUINCLUDES	=-I../../../TopBrussels/TopTreeAnalysis/MCInformation/interface/
JETINCLUDES	=-I../../../TopBrussels/TopTreeAnalysis/Tools/interface/
RECOINCLUDES	=-I../../../TopBrussels/TopTreeAnalysis/Reconstruction/interface/
PHYSOBJINCS	=-I../../../AnalysisClasses/PhysicsObjects/interface/
ESINCLUDES	=-I../../../AnalysisClasses/EventSelection/interface/
MYHEADERS=-I../../interface

CXX=g++


#LIBS		= $(ROOTLIBS)
LIBS		= $(TROOTLIBS)
LIBS		+= $(ESLIBS)
LIBS		+= $(PULIBS)
LIBS		+= $(JETTOOLS)
LIBS		+= $(RECOLIBS)
LIBS		+= $(PHYSOBJLIBS)
HEADERS 	=$(TROOTINCLUDES)
HEADERS		+=$(PUINCLUDES)
HEADERS		+=$(JETINCLUDES)
HEADERS 	+=$(RECOINCLUDES)
HEADERS 	+=$(ESINCLUDES)
HEADERS 	+=$(PHYSOBJINCS)

all:  pl clean


pl:
	@echo "Compiling the Plotting .... \n"
	$(CXX) Plotting.C -c -o Plotting.o -O0 $(ROOTCFLAGS) -fPIC $(HEADERS) -g
	@echo "Linking ...... \n"
	g++ Plotting.o -o Plot $(ROOTGLIBS) -lEG -lHist $(LIBS) -g -fPIC -O0 -I/opt/root/include -m64 -pthread $(HEADERS) 

clean:
	@echo "Cleaning..."
	@rm -f *.o
	@rm -f *~
	@rm -f ../../interface/*.gch
