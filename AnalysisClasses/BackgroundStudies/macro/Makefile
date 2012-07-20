ROOTINC		=-I$(shell root-config --incdir)
ROOTLIBS	=$(shell root-config --libs) -lMinuit -lRooFit -lMinuit2 -lRooFitCore
ROOTCFLAGS	=$(shell root-config --cflags)
ROOTGLIBS	=$(shell root-config --glibs) -lMinuit  -lRooFit -lMinuit2 -lRooFitCore
HOMELIB		= $(HOME)/lib
TROOTLIBS	= -L$(HOMELIB) -lToto.2011
ESLIBS 		= -L$(HOMELIB) -lEventSelection.2011
PULIBS		= -L$(HOMELIB) -lLumi3DRW.2011
JETTOOLS	= -L$(HOMELIB) -lTools.2011
RECOLIBS	= -L$(HOMELIB) -lReco.2011
PHYSOBJLIBS	= -L$(HOMELIB) -lPhysObj.2011
TOYLIBS		= -L$(HOMELIB) -lToyAnalysis.2011
BKGSTUDYLIBS	= -L$(HOMELIB) -lBkgStudies.2011
BASE		= -L$(HOMELIB) -lBaseBaseAnalysis.2011
TROOTINCLUDES   = -I../../../TopBrussels/TopTreeProducer/interface
PUINCLUDES	=-I../../../TopBrussels/TopTreeAnalysis/MCInformation/interface/
JETINCLUDES	=-I../../../TopBrussels/TopTreeAnalysis/Tools/interface/
RECOINCLUDES	=-I../../../TopBrussels/TopTreeAnalysis/Reconstruction/interface/
PHYSOBJINCS	=-I../../PhysicsObjects/interface/
ESINCLUDES	=-I../../EventSelection/interface/
BASEINCLUDES	=-I../../../Base/BaseAnalysis/interface/
MYHEADERS	=-I../interface

CXX=g++


#LIBS		= $(ROOTLIBS)
LIBS		= $(TROOTLIBS)
LIBS		+= $(ESLIBS)
LIBS		+= $(PULIBS)
LIBS		+= $(JETTOOLS)
LIBS		+= $(RECOLIBS)
LIBS		+= $(PHYSOBJLIBS)
LIBS		+= $(BKGSTUDYLIBS)
HEADERS		=$(MYHEADERS)
HEADERS 	+=$(TROOTINCLUDES)
HEADERS		+=$(PUINCLUDES)
HEADERS		+=$(JETINCLUDES)
HEADERS 	+=$(RECOINCLUDES)
HEADERS 	+=$(ESINCLUDES)
HEADERS 	+=$(PHYSOBJINCS)
HEADERS 	+=$(BASEINCLUDES)


all:  fit clean

temp: templatefit clean


fit:
	@echo "Compiling the MultiDimFitTest .... \n"
	$(CXX) MultiDimFitTest.C -c -o MultiDimFitTest.o -O0 $(ROOTCFLAGS) -fPIC $(HEADERS)
	@echo "Linking ...... \n"
	g++ MultiDimFitTest.o -o TestMDFit $(ROOTGLIBS) -lEG $(LIBS) -g -fPIC -O0 -I/opt/root/include -m64 -pthread $(HEADERS)

templatefit:
	@echo "Compiling the TemplateFit .... \n"
	$(CXX) TemplateFit.C -c -o TemplateFit.o -O0 $(ROOTCFLAGS) -fPIC $(HEADERS)
	@echo "Linking ...... \n"
	g++ TemplateFit.o -o FitTemplates $(ROOTGLIBS) -lEG $(LIBS) -g -fPIC -O0 -I/opt/root/include -m64 -pthread $(HEADERS)

clean:
	@echo "Cleaning..."
	@rm -f *.o
	@rm -f *~


