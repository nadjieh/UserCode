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
HEADERS 	=$(TROOTINCLUDES)
HEADERS		+=$(PUINCLUDES)
HEADERS		+=$(JETINCLUDES)
HEADERS 	+=$(RECOINCLUDES)
HEADERS 	+=$(ESINCLUDES)
HEADERS 	+=$(PHYSOBJINCS)


all:  sas clean

met: MET clean

sep: SEP clean

plot: PLOT clean

test: TEST clean

ll: LLTEST clean

val: VALTEST clean

sas:
	@echo "Compiling the ToyAnalysis .... \n"
	$(CXX) ToyAnalysis.C -c -o ToyAnalysis.o -O0 $(ROOTCFLAGS) -fPIC $(HEADERS)
	@echo "Linking ...... \n"
	g++ ToyAnalysis.o -o ToyAnalysis $(ROOTGLIBS) -lEG $(LIBS) -g -fPIC -O0 -I/opt/root/include -m64 -pthread $(HEADERS)

MET:
	@echo "Compiling the ToyAnalysis .... \n"
	$(CXX) ToyAnalysis.C -c -o ToyAnalysis.o -O0 $(ROOTCFLAGS) -fPIC $(HEADERS)
	@echo "Linking ...... \n"
	g++ ToyAnalysis.o -o METToyAnalysis $(ROOTGLIBS) -lEG $(LIBS) -g -fPIC -O0 -I/opt/root/include -m64 -pthread $(HEADERS)

SEP:
	@echo "Compiling the TA_WeightedCosThetaProducer .... \n"
	$(CXX) TA_WeightedCosThetaProducer.C -c -o TA_WeightedCosThetaProducer.o -O0 $(ROOTCFLAGS) -fPIC $(HEADERS)
	@echo "Linking ...... \n"
	g++ TA_WeightedCosThetaProducer.o -o ProduceWeightedCosTheta $(ROOTGLIBS) -lEG $(LIBS) -g -fPIC -O0 -I/opt/root/include -m64 -pthread $(HEADERS)	

tmp:
	@echo "Compiling the Test ...."
	g++ Test.C -c -o test.o -O0  -pthread -m64 -I/opt/root/include -fPIC 
	@echo "Linking \n\n\n\t"
	g++ test.o -o Test $(ROOTGLIBS) -g -fPIC -O0 -I/opt/root/include -m64 -pthread 

PLOT:
	@echo "Compiling the ChiSquaredPlotter .... \n"
	$(CXX) ChiSquaredPlotter.C -c -o ChiSquaredPlotter.o -O0 $(ROOTCFLAGS) -fPIC $(HEADERS)
	@echo "Linking ...... \n"
	g++ ChiSquaredPlotter.o -o PlotChiSquared $(ROOTGLIBS) -lEG $(LIBS) -g -fPIC -O0 -I/opt/root/include -m64 -pthread $(HEADERS)

TEST:
	@echo "Compiling the TA_HistogramOnly .... \n"
	$(CXX) TA_HistogramOnly.C -c -o TA_HistogramOnly.o -O0 $(ROOTCFLAGS) -fPIC $(HEADERS)
	@echo "Linking ...... \n"
	g++ TA_HistogramOnly.o -o doTest $(ROOTGLIBS) -lEG $(LIBS) -g -fPIC -O0 -I/opt/root/include -m64 -pthread $(HEADERS)

LLTEST:
	@echo "Compiling the FitTest .... \n"
	$(CXX) FitTest.C -c -o FitTest.o -O0 $(ROOTCFLAGS) -fPIC $(HEADERS)
	@echo "Linking ...... \n"
	g++ FitTest.o -o doLL $(ROOTGLIBS) -lEG $(LIBS) -g -fPIC -O0 -I/opt/root/include -m64 -pthread $(HEADERS)
VALTEST:
	@echo "Compiling the FitValidationTest .... \n"
	$(CXX) FitValidationTest.C -c -o FitValidationTest.o -O0 $(ROOTCFLAGS) -fPIC $(HEADERS)
	@echo "Linking ...... \n"
	g++ FitValidationTest.o -o doValidation $(ROOTGLIBS) -lEG $(LIBS) -g -fPIC -O0 -I/opt/root/include -m64 -pthread $(HEADERS)
clean:
	@echo "Cleaning..."
	@rm -f *.o
	@rm -f *~


