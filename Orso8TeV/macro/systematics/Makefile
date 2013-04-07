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


all:  sys clean

non: NON clean

write: W clean


sys:
	@echo "Compiling the SystOrsoHistogramCreator .... \n"
	$(CXX) SystOrsoHistogramCreator.C -c -o SystOrsoHistogramCreator.o -O0 $(ROOTCFLAGS) -fPIC $(HEADERS) -g
	@echo "Linking ...... \n"
	g++ SystOrsoHistogramCreator.o -o Syst2J1T $(ROOTGLIBS) $(LIBS) -g -fPIC -O0 -I/opt/root/include -m64 -pthread $(HEADERS)
NON:
	@echo "Compiling the SystOrsoHistogramCreator .... \n"
	$(CXX) SystOrsoHistogramCreator.C -c -o SystOrsoHistogramCreator.o -O0 $(ROOTCFLAGS) -fPIC $(HEADERS) -g
	@echo "Linking ...... \n"
	g++ SystOrsoHistogramCreator.o -o SystNon2J1T $(ROOTGLIBS) $(LIBS) -g -fPIC -O0 -I/opt/root/include -m64 -pthread $(HEADERS)

W:
	@echo "Compiling the WritePDFs .... \n"
	$(CXX) WritePDFs.C -c -o WritePDFs.o -O0 $(ROOTCFLAGS) -fPIC $(HEADERS) -g
	@echo "Linking ...... \n"
	g++ WritePDFs.o -o writePDFs $(ROOTGLIBS) $(LIBS) -g -fPIC -O0 -I/opt/root/include -m64 -pthread $(HEADERS)


clean:
	@echo "Cleaning..."
	@rm -f *.o


