ROOTINC		=-I$(shell root-config --incdir)
ROOTLIBS	=$(shell root-config --libs) -lMinuit  -lRooFitCore -lRooFit -lRooStats
ROOTCFLAGS	=$(shell root-config --cflags)
ROOTGLIBS	=$(shell root-config --glibs) -lMinuit  -lRooFitCore -lRooFit -lRooStats
HOMELIB		= $(HOME)/lib
TROOTLIBS	= -L$(HOMELIB) -lToto
ESLIBS 		= -L$(HOMELIB) -lEventSelection
PULIBS		= -L$(HOMELIB) -lLumi3DRW
JETTOOLS	= -L$(HOMELIB) -lTools
RECOLIBS	= -L$(HOMELIB) -lReco
PHYSOBJLIBS	= -L$(HOMELIB) -lPhysObj
TOYLIBS		= -L$(HOMELIB) -lToyAnalysis
TROOTINCLUDES   = -I../../../TopBrussels/TopTreeProducer/interface
PUINCLUDES	=-I../../../TopBrussels/TopTreeAnalysis/MCInformation/interface/
JETINCLUDES	=-I../../../TopBrussels/TopTreeAnalysis/Tools/interface/
RECOINCLUDES	=-I../../../TopBrussels/TopTreeAnalysis/Reconstruction/interface/
PHYSOBJINCS	=-I../../PhysicsObjects/interface/
ESINCLUDES	=-I../../EventSelection/interface/
MYHEADERS=-I../interface

CXX=g++


#LIBS		= $(ROOTLIBS)
LIBS		= $(TROOTLIBS)
LIBS		+= $(ESLIBS)
LIBS		+= $(PULIBS)
LIBS		+= $(JETTOOLS)
LIBS		+= $(RECOLIBS)
LIBS		+= $(PHYSOBJLIBS)
LIBS		+= $(TOYLIBS)
HEADERS 	=$(TROOTINCLUDES)
HEADERS		+=$(PUINCLUDES)
HEADERS		+=$(JETINCLUDES)
HEADERS 	+=$(RECOINCLUDES)
HEADERS 	+=$(ESINCLUDES)
HEADERS 	+=$(PHYSOBJINCS)


all:  sas clean

sas:
	@echo "Compiling the TTJetsCosThetaSanityChecker .... \n"
	$(CXX) TTJetsCosThetaSanityChecker.C -c -o TTJetsCosThetaSanityChecker.o -O0 $(ROOTCFLAGS) -fPIC $(HEADERS)
	@echo "Linking ...... \n"
	g++ TTJetsCosThetaSanityChecker.o -o CheckCosThetaInTt $(ROOTGLIBS) -lEG $(LIBS) -g -fPIC -O0 -I/opt/root/include -m64 -pthread $(HEADERS)

template: TEMPLATE clean
	
tmp:
	@echo "Compiling the Test ...."
	g++ Test.C -c -o test.o -O0  -pthread -m64 -I/opt/root/include -fPIC 
	@echo "Linking \n\n\n\t"
	g++ test.o -o Test $(ROOTGLIBS) -g -fPIC -O0 -I/opt/root/include -m64 -pthread 
	
TEMPLATE:
	@echo "Compiling the TemplateFit.C .... \n"
	$(CXX) TemplateFit.C -c -o TemplateFit.o -O0 $(ROOTCFLAGS) -fPIC $(HEADERS)
	@echo "Linking ...... \n"
	g++ TemplateFit.o -o doTemplateFit $(ROOTGLIBS) -lEG $(LIBS) -g -fPIC -O0 -I/opt/root/include -m64 -pthread $(HEADERS)
clean:
	@echo "Cleaning..."
	@rm -f *.o
	@rm -f *~


