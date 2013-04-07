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
TROOTINCLUDES = -I../../../TopBrussels/TopTreeProducer/interface
PHYSOBJINC = -I../../AnalysisClasses/PhysicsObjects/interface/
TOYINCLUDES = -I../../AnalysisClasses/ToyAnalysis/interface/
MYHEADERS=-I../interface

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

w: W clean
	
comb: Comb clean

qcd:
	@echo "Compiling the SelectAndSave .... \n"
	$(CXX) QCDOrsoHistogramCreator.C -c -o QCDOrsoHistogramCreator.o -O0 $(ROOTCFLAGS) -fPIC $(HEADERS) -g
	@echo "Linking ...... \n"
	g++ QCDOrsoHistogramCreator.o -o QCDOrsoHistogramCreator $(ROOTGLIBS) $(LIBS) -g -fPIC -O0 -I/opt/root/include -m64 -pthread $(HEADERS)
GEN:
	@echo "Compiling the GenInfoStudies .... \n"
	$(CXX) GenInfoStudies.C -c -o GenInfoStudies.o -O0 $(ROOTCFLAGS) -fPIC $(HEADERS) -g
	@echo "Linking ...... \n"
	g++ GenInfoStudies.o -o GenInfoStudies $(ROOTGLIBS) $(LIBS) -g -fPIC -O0 -I/opt/root/include -m64 -pthread $(HEADERS)

W:
	@echo "Compiling the WTemplateHistogramCreator .... \n"
	$(CXX) WTemplateHistogramCreator.C -c -o WTemplateHistogramCreator.o -O0 $(ROOTCFLAGS) -fPIC $(HEADERS) -g
	@echo "Linking ...... \n"
	g++ WTemplateHistogramCreator.o -o WTemplateHistogramCreator $(ROOTGLIBS) $(LIBS) -g -fPIC -O0 -I/opt/root/include -m64 -pthread $(HEADERS)

Comb:
	@echo "Compiling the OrsoHistogramCreator_bkp .... \n"
	$(CXX) OrsoHistogramCreator_bkp.C -c -o OrsoHistogramCreator_bkp.o -O0 $(ROOTCFLAGS) -fPIC $(HEADERS) -g
	@echo "Linking ...... \n"
	g++ OrsoHistogramCreator_bkp.o -o CombinationStudy $(ROOTGLIBS) $(LIBS) -g -fPIC -O0 -I/opt/root/include -m64 -pthread $(HEADERS)

clean:
	@echo "Cleaning..."
	@rm -f *.o


