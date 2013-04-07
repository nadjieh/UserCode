HOMELIB		= $(HOME)/lib
ROOTINC		=-I$(shell root-config --incdir)
ROOTLIBS	=$(shell root-config --libs) -lMinuit
ROOTCFLAGS	=$(shell root-config --cflags)
ROOTGLIBS	=$(shell root-config --glibs) -lMinuit
TROOTLIBS	= -L$(HOMELIB) -lToto.2011
ESLIBS 		= -L$(HOMELIB) -lEventSelection.2011
PHYSOBJLIB	=-L$(HOMELIB) -lPhysObj.2011
TOYLIB	=-L$(HOMELIB) -lToyAnalysis.2011
ORSOLIB = -L$(HOMELIB) -lOrsoNtuples.2012
TROOTINCLUDES = -I../../../../TopBrussels/TopTreeProducer/interface
PHYSOBJINC = -I../../../AnalysisClasses/PhysicsObjects/interface/
TOYINCLUDES = -I../../../AnalysisClasses/ToyAnalysis/interface/
MYHEADERS=-I../../interface

CXX=g++

GLIBS		=$(ROOTGLIBS) 
LIBS		= $(ROOTLIBS)
LIBS		+= $(TROOTLIBS)
LIBS		+= $(ESLIBS)
LIBS		+= $(PHYSOBJLIB)
LIBS		+= $(TOYLIB)
LIBS		+= $(ORSOLIB)


HEADERS 	+=$(TROOTINCLUDES)
HEADERS 	+= $(PHYSOBJINC)
HEADERS 	+= $(TOYINCLUDES)
HEADERS 	+= $(MYHEADERS)


all:  qcd clean

gen: GEN clean

qcd:
	@echo "Compiling the NPGenEvent .... \n"
	$(CXX) NPGenEvent.C -c -o NPGenEvent.o -O0 $(ROOTCFLAGS) -fPIC $(HEADERS) -g
	@echo "Linking ...... \n"
	g++ NPGenEvent.o -o NPGenEvent $(ROOTGLIBS) $(LIBS) -g -fPIC -O0 -I/opt/root/include -m64 -pthread $(HEADERS)
GEN:
	@echo "Compiling the GenCosTheta .... \n"
	$(CXX) GenCosTheta.C -c -o GenCosTheta.o -O0 $(ROOTCFLAGS) -fPIC $(HEADERS) -g
	@echo "Linking ...... \n"
	g++ GenCosTheta.o -o GenCosTheta $(ROOTGLIBS) $(LIBS) -g -fPIC -O0 -I/opt/root/include -m64 -pthread $(HEADERS)

clean:
	@echo "Cleaning..."
	@rm -f *.o


