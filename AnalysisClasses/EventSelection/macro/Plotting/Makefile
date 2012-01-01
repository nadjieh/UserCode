ObjSuf        = o
SrcSuf        = cc
ExeSuf        = 
DllSuf        = so
OutPutOpt     = -o
HeadSuf       = h
CLIBS		=-L/usr/lib -lstdc++
ROOTINC		=-I$(shell root-config --incdir)
ROOTLIBS	=$(shell root-config --libs) -lMinuit
ROOTCFLAGS	=$(shell root-config --cflags)
ROOTGLIBS	=$(shell root-config --glibs) -lMinuit
TROOTLIBS	= -L$(HOMELIB) -lTotoData
ESLIBS 		= -L$(HOMELIB) -lEventSelection385P3
BASELIBS	= -L$(HOMELIB) -lBaseBaseAnalysis
BASEINCLUDES	=-I../../../../Base/BaseAnalysis/interface
TROOTINCLUDES = -I../../../TopBrussels/TopTreeProducer/interface

MYHEADERS=-I../../interface
MYSOURCES= ../../src
CXX=g++
CXXFLAGS	= -ggdb -O0 -DDEBUG -Wall -fPIC -DNO_ORCACLASSES -g -c
LD		= g++
LDFLAGS 	= -g
SOFLAGS 	= -shared

CXXFLAGS	+= $(ROOTCFLAGS)
LIBS		= $(ROOTFLAGS)
LIBS		+= $(TROOTLIBS)
LIBS		+= $(ESLIBS)

HEADERS 	=$(TROOTINCLUDES)
HEADERS 	+=$(MYHEADERS)



# Linux with egcs



CXXFLAGS	+= $(ROOTCFLAGS)
GLIBS		=$(ROOTGLIBS) 
LIBS		= $(ROOTLIBS)
#LIBS		+= $(TROOTLIBS)
#LIBS		+= $(ESLIBS)
#------------------------------------------------------------------------------
SOURCES 	= $(wildcard $(MYSOURCES)/*.cc)
HEADERS 	= $(wildcard ../interface/*.h)
OBJECTS 	= $(SOURCES:.$(SrcSuf)=.$(ObjSuf))
DEPENDS 	= $(SOURCES:.$(SrcSuf)=.d)
SOBJECTS	= $(SOURCES:.$(SrcSuf)=.$(DllSuf))
HOMELIB		= $(HOME)/lib
OPTLIBS		= $(LIBS)
OPTLIBS		+=$(BASELIBS)
OPTHEADER	=$(HEADERS)
OPTHEADER	+=$(BASEINCLUDES)

#PROGRAMS	=  $(SOBJECTS)

all: 
	@echo "Compiling the Macro ...."
	$(CXX) $(CXXFLAGS) $(MYHEADERS)  Plotting.C
	@echo "Linking \n\n\n\t"
	gcc -o plot $(CLIBS) $(LIBS)  Plotting.o
	@rm -f *.o
	@rm -f ../../interface/*.gch


