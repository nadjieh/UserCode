ROOTINC		=-I$(shell root-config --incdir)
ROOTLIBS	=$(shell root-config --libs) -lMinuit
ROOTCFLAGS	=$(shell root-config --cflags)
ROOTGLIBS	=$(shell root-config --glibs) -lMinuit
HOMELIB		= $(HOME)/lib
TRIGLIB		= -L$(HOMELIB) -lTriggerTool
MYHEADERS=-I../interface

CXX=g++


#LIBS		= $(ROOTLIBS)
LIBS		= $(TRIGLIB)

HEADERS 	=$(MYHEADERS)



all:  HAD clean

lep: LEP clean

HAD:
	@echo "Compiling the Example_HadronLeg .... \n"
	$(CXX) Example_HadronLeg.C -c -o Example_HadronLeg.o -O0 $(ROOTCFLAGS) -fPIC $(HEADERS)
	@echo "Linking ...... \n"
	g++ Example_HadronLeg.o -o doHadronLegExample $(ROOTGLIBS) -lEG $(LIBS) -g -fPIC -O0 -I/opt/root/include -m64 -pthread $(HEADERS)

LEP:
	@echo "Compiling the Example_LeptonLeg .... \n"
	$(CXX) Example_LeptonLeg.C -c -o Example_LeptonLeg.o -O0 $(ROOTCFLAGS) -fPIC $(HEADERS)
	@echo "Linking ...... \n"
	g++ Example_LeptonLeg.o -o doLeptonLegExample $(ROOTGLIBS) -lEG $(LIBS) -g -fPIC -O0 -I/opt/root/include -m64 -pthread $(HEADERS)

clean:
	@echo "Cleaning..."
	@rm -f *.o
	@rm -f *~


