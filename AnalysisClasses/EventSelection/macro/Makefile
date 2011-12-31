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
JETCORRLIB	= -L$(HOMELIB) -lJetCorrection385P3
BASELIBS	= -L/user/ajafari/CMSSW_3_8_5_patch3/lib/slc5_ia32_gcc434 -lBaseBaseAnalysis
BASEINCLUDES	=-I/user/ajafari/CMSSW_3_8_5_patch3/src/Base/BaseAnalysis/interface
TROOTINCLUDES = -I/user/ajafari/CMSSW_3_8_5_patch3/src/TopBrussels/TopTreeProducer/interface
JETCORRINCLUDES = -I/user/ajafari/CMSSW_3_8_5_patch3/src/AnalysisClasses/JetCorrections/interface

MYHEADERS=-I/user/ajafari/CMSSW_3_8_5_patch3/src/AnalysisClasses/EventSelection/interface
MYSOURCES= /user/ajafari/CMSSW_3_8_5_patch3/src/AnalysisClasses/EventSelection/src
CXX=g++
CXXFLAGS	= -ggdb -O0 -DDEBUG -Wall -fPIC -DNO_ORCACLASSES -g -c
LD		= g++
LDFLAGS 	= -g
SOFLAGS 	= -shared

CXXFLAGS	+= $(ROOTCFLAGS)
LIBS		= $(ROOTFLAGS)
LIBS		+= $(TROOTLIBS)
LIBS		+= $(ESLIBS)
#LIBS            += $(JETCORRLIB)

HEADERS 	=$(TROOTINCLUDES)
HEADERS 	+=$(MYHEADERS)
#HEADERS         +=$(JETCORRINCLUDES)



# Linux with egcs



CXXFLAGS	+= $(ROOTCFLAGS)
GLIBS		=$(ROOTGLIBS) 
LIBS		= $(ROOTLIBS)
LIBS		+= $(TROOTLIBS)
LIBS		+= $(ESLIBS)
#------------------------------------------------------------------------------
SOURCES 	= $(wildcard $(MYSOURCES)/*.cc)
HEADERS 	= $(wildcard ../interface/*.h)
OBJECTS 	= $(SOURCES:.$(SrcSuf)=.$(ObjSuf))
DEPENDS 	= $(SOURCES:.$(SrcSuf)=.d)
SOBJECTS	= $(SOURCES:.$(SrcSuf)=.$(DllSuf))
HOMELIB		= /user/ajafari/lib
OPTLIBS		= $(LIBS)
OPTLIBS		+=$(BASELIBS)
OPTHEADER	=$(HEADERS)
OPTHEADER	+=$(BASEINCLUDES)

#PROGRAMS	=  $(SOBJECTS)

all: 
	@echo "Compiling the Macro ...."
	$(CXX) $(CXXFLAGS) $(HEADERS)  Macro.C
	@echo "Linking \n\n\n\t"
	gcc -o HistsWithEcalDrivenConv $(CLIBS) $(LIBS)  Macro.o
	@rm -f *.o
	@rm -f ../interface/*.gch

otimize:
	@echo "Compiling the OptimizationPtElec ..."
	$(CXX) $(CXXFLAGS) $(OPTHEADERS) OptimizationPtElec.C
	@echo "Linking \n\n\n\t"
	gcc -o OptimizeElecPt $(CLIBS) $(OPTLIBS) OptimizationPtElec.o
	@rm -f *.o
sas:
	@echo "Compiling the SelectAndSave ...."
	$(CXX) $(CXXFLAGS) $(HEADERS) SelectAndSave.C
	@echo "Linking \n\n\n\t"
	gcc -o SelectAndSave $(CLIBS) $(LIBS) SelectAndSave.o
	@rm -f *.o
	@rm -f ../interface/*.gch
tmp:
	@echo "Compiling the SelectAndSave ...."
	$(CXX) $(CXXFLAGS) $(HEADERS) SelectAndSave.C
	@echo "Linking \n\n\n\t"
	gcc -o tmpSelectAndSave $(CLIBS) $(LIBS) SelectAndSave.o
	@rm -f *.o
	@rm -f ../interface/*.gch


otc:
	@echo "Compiling the SelectAndSave ...."
	$(CXX) $(CXXFLAGS) $(HEADERS) OtherTtAnalysis.C
	@echo "Linking \n\n\n\t"
	gcc -o OtherTtAnalysis $(CLIBS) $(LIBS) OtherTtAnalysis.o
	@rm -f *.o
clean:
	@echo "Cleaning..."
	@rm -f *.o

