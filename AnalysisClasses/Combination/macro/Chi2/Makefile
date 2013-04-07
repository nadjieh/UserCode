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
COMBLIBS	= -L$(HOMELIB) -lCombination.2011
BASE		= -L$(HOMELIB) -lBaseBaseAnalysis.2011
TROOTINCLUDES   = -I../../../../TopBrussels/TopTreeProducer/interface
PUINCLUDES	=-I../../../../TopBrussels/TopTreeAnalysis/MCInformation/interface/
JETINCLUDES	=-I../../../../TopBrussels/TopTreeAnalysis/Tools/interface/
RECOINCLUDES	=-I../../../../TopBrussels/TopTreeAnalysis/Reconstruction/interface/
PHYSOBJINCS	=-I../../../PhysicsObjects/interface/
ESINCLUDES	=-I../../../EventSelection/interface/
BASEINCLUDES	=-I../../../../Base/BaseAnalysis/interface/
BKGSTDYINCLUDES	=-I../../../BackgroundStudies/interface/
MYHEADERS	=-I../../interface

CXX=g++


#LIBS		= $(ROOTLIBS)
LIBS		= $(TROOTLIBS)
LIBS		+= $(ESLIBS)
LIBS		+= $(PULIBS)
LIBS		+= $(JETTOOLS)
LIBS		+= $(RECOLIBS)
LIBS		+= $(PHYSOBJLIBS)
LIBS		+= $(BKGSTUDYLIBS)
LIBS		+= $(COMBLIBS)
HEADERS		=$(MYHEADERS)
HEADERS 	+=$(TROOTINCLUDES)
HEADERS		+=$(PUINCLUDES)
HEADERS		+=$(JETINCLUDES)
HEADERS 	+=$(RECOINCLUDES)
HEADERS 	+=$(ESINCLUDES)
HEADERS 	+=$(PHYSOBJINCS)
HEADERS 	+=$(BASEINCLUDES)
HEADERS 	+=$(BKGSTDYINCLUDES)


s: f7 clean

e: f8 clean

c: comb clean

f7:
	@echo "Compiling the SingleChi27.C .... \n"
	$(CXX) SingleChi27.C -c -o SingleChi27.o -O0 $(ROOTCFLAGS) -fPIC $(HEADERS) -g 
	@echo "Linking ...... \n"
	g++ SingleChi27.o -o SevenChiSquared $(ROOTGLIBS) -lEG $(LIBS) -g -fPIC -O0 -I/opt/root/include -m64 -pthread $(HEADERS)

f8:
	@echo "Compiling the SingleChi28.C .... \n"
	$(CXX) SingleChi28.C -c -o SingleChi28.o -O0 $(ROOTCFLAGS) -fPIC $(HEADERS) -g 
	@echo "Linking ...... \n"
	g++ SingleChi28.o -o EightChiSquared $(ROOTGLIBS) -lEG $(LIBS) -g -fPIC -O0 -I/opt/root/include -m64 -pthread $(HEADERS)


comb:
	@echo "Compiling the CombChi2.C .... \n"
	$(CXX) CombChi2.C -c -o CombChi2.o -O0 $(ROOTCFLAGS) -fPIC $(HEADERS) -g 
	@echo "Linking ...... \n"
	g++ CombChi2.o -o CombChiSquared $(ROOTGLIBS) -lEG $(LIBS) -g -fPIC -O0 -I/opt/root/include -m64 -pthread $(HEADERS)

clean:
	@echo "Cleaning..."
	@rm -f *.o
	@rm -f *~


