CLIBS=-L/usr/lib -lstdc++

ROOTINC=-I$(shell root-config --incdir)

ROOTFLAGS=$(shell root-config --libs)
HOMELIB=$(HOME)/lib
TROOTLIBS = -L$(HOMELIB) -lTRoot
BASELIBS = -L$(HOMELIB) -lBaseBaseAnalysis
CHISLIB = -L$(HOMELIB) -lChiSquared361P3
EVTSELECLIB = -L$(HOMELIB) -lEventSelection361P3



TROOTINCLUDES = -I../../../../../TopBrussels/TopTreeProducer/interface
CHISHEADERS=-I../../../../../AnalysisClasses/ChiSquared/interface
SELECTIONHEADERS=-I../../../../../AnalysisClasses/EventSelection/interface
CXX=g++


CXXFLAGS=-ggdb -O0 -DDEBUG -Wall -fPIC -DNO_ORCA_CLASSES -pthread -g -c
LIBS = $(ROOTFLAGS)
LIBS	+=$(TROOTLIBS)
LIBS	+=$(BASELIBS)
LIBS	+=$(EVTSELECLIB)
LIBS	+=$(CHISLIB)
LIBS	+=$(LJETSLIB)

HEADERS = $(ROOTINC)
HEADERS +=$(TROOTINCLUDES)
HEADERS +=$(CHISHEADERS)
HEADERS +=$(SELECTIONHEADERS)


all:
	@echo "Compiling TestNewPackage.C..."
	$(CXX) $(CXXFLAGS) $(HEADERS) LightStudy.C

	@echo "Link all shared objects..."


	gcc -o StudyLightJets_PE100_1 $(CLIBS) $(LIBS)  LightStudy.o

	@echo "Cleaning up..."
	@rm -f *.o
rw:
	@echo "Compiling TestNewPackage.C..."
	$(CXX) $(CXXFLAGS) $(HEADERS) LightStudy.C

	@echo "Link all shared objects..."


	gcc -o StudyLightJets_PE100_1_RW $(CLIBS) $(LIBS)  LightStudy.o

	@echo "Cleaning up..."
	@rm -f *.o

1_:
	@echo "Compiling TestNewPackage.C..."
	$(CXX) $(CXXFLAGS) $(HEADERS) 1.C

	@echo "Link all shared objects..."


	gcc -o doRead $(CLIBS) $(LIBS)  1.o

	@echo "Cleaning up..."
	@rm -f *.o
GetData:
	@echo "Compiling TestNewPackage.C..."
	$(CXX) $(CXXFLAGS) $(HEADERS) GetData.C

	@echo "Link all shared objects..."


	gcc -o SeptData $(CLIBS) $(LIBS)  GetData.o

	@echo "Cleaning up..."
	@rm -f *.o
2_:
	@echo "Compiling TestNewPackage.C..."
	$(CXX) $(CXXFLAGS) $(HEADERS) 2.C

	@echo "Link all shared objects..."


	gcc -o doRead_2 $(CLIBS) $(LIBS)  2.o

	@echo "Cleaning up..."
	@rm -f *.o
PE100_1:
	$(CXX) $(CXXFLAGS) $(HEADERS) 1/LightStudy.C
	gcc -o StudyLightJets_PE100_1 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_1:
	$(CXX) $(CXXFLAGS) $(HEADERS) 1/LightStudy.C
	gcc -o StudyLightJets_PE100_1_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_2:
	$(CXX) $(CXXFLAGS) $(HEADERS) 2/LightStudy.C
	gcc -o StudyLightJets_PE100_2 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_2:
	$(CXX) $(CXXFLAGS) $(HEADERS) 2/LightStudy.C
	gcc -o StudyLightJets_PE100_2_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_3:
	$(CXX) $(CXXFLAGS) $(HEADERS) 3/LightStudy.C
	gcc -o StudyLightJets_PE100_3 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_3:
	$(CXX) $(CXXFLAGS) $(HEADERS) 3/LightStudy.C
	gcc -o StudyLightJets_PE100_3_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_4:
	$(CXX) $(CXXFLAGS) $(HEADERS) 4/LightStudy.C
	gcc -o StudyLightJets_PE100_4 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_4:
	$(CXX) $(CXXFLAGS) $(HEADERS) 4/LightStudy.C
	gcc -o StudyLightJets_PE100_4_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_5:
	$(CXX) $(CXXFLAGS) $(HEADERS) 5/LightStudy.C
	gcc -o StudyLightJets_PE100_5 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_5:
	$(CXX) $(CXXFLAGS) $(HEADERS) 5/LightStudy.C
	gcc -o StudyLightJets_PE100_5_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_6:
	$(CXX) $(CXXFLAGS) $(HEADERS) 6/LightStudy.C
	gcc -o StudyLightJets_PE100_6 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_6:
	$(CXX) $(CXXFLAGS) $(HEADERS) 6/LightStudy.C
	gcc -o StudyLightJets_PE100_6_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_7:
	$(CXX) $(CXXFLAGS) $(HEADERS) 7/LightStudy.C
	gcc -o StudyLightJets_PE100_7 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_7:
	$(CXX) $(CXXFLAGS) $(HEADERS) 7/LightStudy.C
	gcc -o StudyLightJets_PE100_7_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_8:
	$(CXX) $(CXXFLAGS) $(HEADERS) 8/LightStudy.C
	gcc -o StudyLightJets_PE100_8 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_8:
	$(CXX) $(CXXFLAGS) $(HEADERS) 8/LightStudy.C
	gcc -o StudyLightJets_PE100_8_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_9:
	$(CXX) $(CXXFLAGS) $(HEADERS) 9/LightStudy.C
	gcc -o StudyLightJets_PE100_9 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_9:
	$(CXX) $(CXXFLAGS) $(HEADERS) 9/LightStudy.C
	gcc -o StudyLightJets_PE100_9_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_10:
	$(CXX) $(CXXFLAGS) $(HEADERS) 10/LightStudy.C
	gcc -o StudyLightJets_PE100_10 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_10:
	$(CXX) $(CXXFLAGS) $(HEADERS) 10/LightStudy.C
	gcc -o StudyLightJets_PE100_10_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_11:
	$(CXX) $(CXXFLAGS) $(HEADERS) 11/LightStudy.C
	gcc -o StudyLightJets_PE100_11 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_11:
	$(CXX) $(CXXFLAGS) $(HEADERS) 11/LightStudy.C
	gcc -o StudyLightJets_PE100_11_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_12:
	$(CXX) $(CXXFLAGS) $(HEADERS) 12/LightStudy.C
	gcc -o StudyLightJets_PE100_12 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_12:
	$(CXX) $(CXXFLAGS) $(HEADERS) 12/LightStudy.C
	gcc -o StudyLightJets_PE100_12_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_13:
	$(CXX) $(CXXFLAGS) $(HEADERS) 13/LightStudy.C
	gcc -o StudyLightJets_PE100_13 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_13:
	$(CXX) $(CXXFLAGS) $(HEADERS) 13/LightStudy.C
	gcc -o StudyLightJets_PE100_13_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_14:
	$(CXX) $(CXXFLAGS) $(HEADERS) 14/LightStudy.C
	gcc -o StudyLightJets_PE100_14 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_14:
	$(CXX) $(CXXFLAGS) $(HEADERS) 14/LightStudy.C
	gcc -o StudyLightJets_PE100_14_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_15:
	$(CXX) $(CXXFLAGS) $(HEADERS) 15/LightStudy.C
	gcc -o StudyLightJets_PE100_15 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_15:
	$(CXX) $(CXXFLAGS) $(HEADERS) 15/LightStudy.C
	gcc -o StudyLightJets_PE100_15_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_16:
	$(CXX) $(CXXFLAGS) $(HEADERS) 16/LightStudy.C
	gcc -o StudyLightJets_PE100_16 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_16:
	$(CXX) $(CXXFLAGS) $(HEADERS) 16/LightStudy.C
	gcc -o StudyLightJets_PE100_16_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_17:
	$(CXX) $(CXXFLAGS) $(HEADERS) 17/LightStudy.C
	gcc -o StudyLightJets_PE100_17 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_17:
	$(CXX) $(CXXFLAGS) $(HEADERS) 17/LightStudy.C
	gcc -o StudyLightJets_PE100_17_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_18:
	$(CXX) $(CXXFLAGS) $(HEADERS) 18/LightStudy.C
	gcc -o StudyLightJets_PE100_18 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_18:
	$(CXX) $(CXXFLAGS) $(HEADERS) 18/LightStudy.C
	gcc -o StudyLightJets_PE100_18_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_19:
	$(CXX) $(CXXFLAGS) $(HEADERS) 19/LightStudy.C
	gcc -o StudyLightJets_PE100_19 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_19:
	$(CXX) $(CXXFLAGS) $(HEADERS) 19/LightStudy.C
	gcc -o StudyLightJets_PE100_19_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_20:
	$(CXX) $(CXXFLAGS) $(HEADERS) 20/LightStudy.C
	gcc -o StudyLightJets_PE100_20 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_20:
	$(CXX) $(CXXFLAGS) $(HEADERS) 20/LightStudy.C
	gcc -o StudyLightJets_PE100_20_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_21:
	$(CXX) $(CXXFLAGS) $(HEADERS) 21/LightStudy.C
	gcc -o StudyLightJets_PE100_21 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_21:
	$(CXX) $(CXXFLAGS) $(HEADERS) 21/LightStudy.C
	gcc -o StudyLightJets_PE100_21_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_22:
	$(CXX) $(CXXFLAGS) $(HEADERS) 22/LightStudy.C
	gcc -o StudyLightJets_PE100_22 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_22:
	$(CXX) $(CXXFLAGS) $(HEADERS) 22/LightStudy.C
	gcc -o StudyLightJets_PE100_22_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_23:
	$(CXX) $(CXXFLAGS) $(HEADERS) 23/LightStudy.C
	gcc -o StudyLightJets_PE100_23 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_23:
	$(CXX) $(CXXFLAGS) $(HEADERS) 23/LightStudy.C
	gcc -o StudyLightJets_PE100_23_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_24:
	$(CXX) $(CXXFLAGS) $(HEADERS) 24/LightStudy.C
	gcc -o StudyLightJets_PE100_24 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_24:
	$(CXX) $(CXXFLAGS) $(HEADERS) 24/LightStudy.C
	gcc -o StudyLightJets_PE100_24_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_25:
	$(CXX) $(CXXFLAGS) $(HEADERS) 25/LightStudy.C
	gcc -o StudyLightJets_PE100_25 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_25:
	$(CXX) $(CXXFLAGS) $(HEADERS) 25/LightStudy.C
	gcc -o StudyLightJets_PE100_25_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_26:
	$(CXX) $(CXXFLAGS) $(HEADERS) 26/LightStudy.C
	gcc -o StudyLightJets_PE100_26 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_26:
	$(CXX) $(CXXFLAGS) $(HEADERS) 26/LightStudy.C
	gcc -o StudyLightJets_PE100_26_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_27:
	$(CXX) $(CXXFLAGS) $(HEADERS) 27/LightStudy.C
	gcc -o StudyLightJets_PE100_27 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_27:
	$(CXX) $(CXXFLAGS) $(HEADERS) 27/LightStudy.C
	gcc -o StudyLightJets_PE100_27_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_28:
	$(CXX) $(CXXFLAGS) $(HEADERS) 28/LightStudy.C
	gcc -o StudyLightJets_PE100_28 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_28:
	$(CXX) $(CXXFLAGS) $(HEADERS) 28/LightStudy.C
	gcc -o StudyLightJets_PE100_28_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_29:
	$(CXX) $(CXXFLAGS) $(HEADERS) 29/LightStudy.C
	gcc -o StudyLightJets_PE100_29 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_29:
	$(CXX) $(CXXFLAGS) $(HEADERS) 29/LightStudy.C
	gcc -o StudyLightJets_PE100_29_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_30:
	$(CXX) $(CXXFLAGS) $(HEADERS) 30/LightStudy.C
	gcc -o StudyLightJets_PE100_30 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_30:
	$(CXX) $(CXXFLAGS) $(HEADERS) 30/LightStudy.C
	gcc -o StudyLightJets_PE100_30_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_31:
	$(CXX) $(CXXFLAGS) $(HEADERS) 31/LightStudy.C
	gcc -o StudyLightJets_PE100_31 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_31:
	$(CXX) $(CXXFLAGS) $(HEADERS) 31/LightStudy.C
	gcc -o StudyLightJets_PE100_31_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_32:
	$(CXX) $(CXXFLAGS) $(HEADERS) 32/LightStudy.C
	gcc -o StudyLightJets_PE100_32 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_32:
	$(CXX) $(CXXFLAGS) $(HEADERS) 32/LightStudy.C
	gcc -o StudyLightJets_PE100_32_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_33:
	$(CXX) $(CXXFLAGS) $(HEADERS) 33/LightStudy.C
	gcc -o StudyLightJets_PE100_33 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_33:
	$(CXX) $(CXXFLAGS) $(HEADERS) 33/LightStudy.C
	gcc -o StudyLightJets_PE100_33_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_34:
	$(CXX) $(CXXFLAGS) $(HEADERS) 34/LightStudy.C
	gcc -o StudyLightJets_PE100_34 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_34:
	$(CXX) $(CXXFLAGS) $(HEADERS) 34/LightStudy.C
	gcc -o StudyLightJets_PE100_34_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_35:
	$(CXX) $(CXXFLAGS) $(HEADERS) 35/LightStudy.C
	gcc -o StudyLightJets_PE100_35 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_35:
	$(CXX) $(CXXFLAGS) $(HEADERS) 35/LightStudy.C
	gcc -o StudyLightJets_PE100_35_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_36:
	$(CXX) $(CXXFLAGS) $(HEADERS) 36/LightStudy.C
	gcc -o StudyLightJets_PE100_36 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_36:
	$(CXX) $(CXXFLAGS) $(HEADERS) 36/LightStudy.C
	gcc -o StudyLightJets_PE100_36_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_37:
	$(CXX) $(CXXFLAGS) $(HEADERS) 37/LightStudy.C
	gcc -o StudyLightJets_PE100_37 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_37:
	$(CXX) $(CXXFLAGS) $(HEADERS) 37/LightStudy.C
	gcc -o StudyLightJets_PE100_37_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_38:
	$(CXX) $(CXXFLAGS) $(HEADERS) 38/LightStudy.C
	gcc -o StudyLightJets_PE100_38 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_38:
	$(CXX) $(CXXFLAGS) $(HEADERS) 38/LightStudy.C
	gcc -o StudyLightJets_PE100_38_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_39:
	$(CXX) $(CXXFLAGS) $(HEADERS) 39/LightStudy.C
	gcc -o StudyLightJets_PE100_39 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_39:
	$(CXX) $(CXXFLAGS) $(HEADERS) 39/LightStudy.C
	gcc -o StudyLightJets_PE100_39_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_40:
	$(CXX) $(CXXFLAGS) $(HEADERS) 40/LightStudy.C
	gcc -o StudyLightJets_PE100_40 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_40:
	$(CXX) $(CXXFLAGS) $(HEADERS) 40/LightStudy.C
	gcc -o StudyLightJets_PE100_40_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_41:
	$(CXX) $(CXXFLAGS) $(HEADERS) 41/LightStudy.C
	gcc -o StudyLightJets_PE100_41 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_41:
	$(CXX) $(CXXFLAGS) $(HEADERS) 41/LightStudy.C
	gcc -o StudyLightJets_PE100_41_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_42:
	$(CXX) $(CXXFLAGS) $(HEADERS) 42/LightStudy.C
	gcc -o StudyLightJets_PE100_42 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_42:
	$(CXX) $(CXXFLAGS) $(HEADERS) 42/LightStudy.C
	gcc -o StudyLightJets_PE100_42_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_43:
	$(CXX) $(CXXFLAGS) $(HEADERS) 43/LightStudy.C
	gcc -o StudyLightJets_PE100_43 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_43:
	$(CXX) $(CXXFLAGS) $(HEADERS) 43/LightStudy.C
	gcc -o StudyLightJets_PE100_43_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_44:
	$(CXX) $(CXXFLAGS) $(HEADERS) 44/LightStudy.C
	gcc -o StudyLightJets_PE100_44 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_44:
	$(CXX) $(CXXFLAGS) $(HEADERS) 44/LightStudy.C
	gcc -o StudyLightJets_PE100_44_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_45:
	$(CXX) $(CXXFLAGS) $(HEADERS) 45/LightStudy.C
	gcc -o StudyLightJets_PE100_45 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_45:
	$(CXX) $(CXXFLAGS) $(HEADERS) 45/LightStudy.C
	gcc -o StudyLightJets_PE100_45_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_46:
	$(CXX) $(CXXFLAGS) $(HEADERS) 46/LightStudy.C
	gcc -o StudyLightJets_PE100_46 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_46:
	$(CXX) $(CXXFLAGS) $(HEADERS) 46/LightStudy.C
	gcc -o StudyLightJets_PE100_46_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_47:
	$(CXX) $(CXXFLAGS) $(HEADERS) 47/LightStudy.C
	gcc -o StudyLightJets_PE100_47 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_47:
	$(CXX) $(CXXFLAGS) $(HEADERS) 47/LightStudy.C
	gcc -o StudyLightJets_PE100_47_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_48:
	$(CXX) $(CXXFLAGS) $(HEADERS) 48/LightStudy.C
	gcc -o StudyLightJets_PE100_48 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_48:
	$(CXX) $(CXXFLAGS) $(HEADERS) 48/LightStudy.C
	gcc -o StudyLightJets_PE100_48_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_49:
	$(CXX) $(CXXFLAGS) $(HEADERS) 49/LightStudy.C
	gcc -o StudyLightJets_PE100_49 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_49:
	$(CXX) $(CXXFLAGS) $(HEADERS) 49/LightStudy.C
	gcc -o StudyLightJets_PE100_49_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_50:
	$(CXX) $(CXXFLAGS) $(HEADERS) 50/LightStudy.C
	gcc -o StudyLightJets_PE100_50 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_50:
	$(CXX) $(CXXFLAGS) $(HEADERS) 50/LightStudy.C
	gcc -o StudyLightJets_PE100_50_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_51:
	$(CXX) $(CXXFLAGS) $(HEADERS) 51/LightStudy.C
	gcc -o StudyLightJets_PE100_51 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_51:
	$(CXX) $(CXXFLAGS) $(HEADERS) 51/LightStudy.C
	gcc -o StudyLightJets_PE100_51_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_52:
	$(CXX) $(CXXFLAGS) $(HEADERS) 52/LightStudy.C
	gcc -o StudyLightJets_PE100_52 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_52:
	$(CXX) $(CXXFLAGS) $(HEADERS) 52/LightStudy.C
	gcc -o StudyLightJets_PE100_52_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_53:
	$(CXX) $(CXXFLAGS) $(HEADERS) 53/LightStudy.C
	gcc -o StudyLightJets_PE100_53 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_53:
	$(CXX) $(CXXFLAGS) $(HEADERS) 53/LightStudy.C
	gcc -o StudyLightJets_PE100_53_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_54:
	$(CXX) $(CXXFLAGS) $(HEADERS) 54/LightStudy.C
	gcc -o StudyLightJets_PE100_54 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_54:
	$(CXX) $(CXXFLAGS) $(HEADERS) 54/LightStudy.C
	gcc -o StudyLightJets_PE100_54_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_55:
	$(CXX) $(CXXFLAGS) $(HEADERS) 55/LightStudy.C
	gcc -o StudyLightJets_PE100_55 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_55:
	$(CXX) $(CXXFLAGS) $(HEADERS) 55/LightStudy.C
	gcc -o StudyLightJets_PE100_55_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_56:
	$(CXX) $(CXXFLAGS) $(HEADERS) 56/LightStudy.C
	gcc -o StudyLightJets_PE100_56 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_56:
	$(CXX) $(CXXFLAGS) $(HEADERS) 56/LightStudy.C
	gcc -o StudyLightJets_PE100_56_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_57:
	$(CXX) $(CXXFLAGS) $(HEADERS) 57/LightStudy.C
	gcc -o StudyLightJets_PE100_57 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_57:
	$(CXX) $(CXXFLAGS) $(HEADERS) 57/LightStudy.C
	gcc -o StudyLightJets_PE100_57_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_58:
	$(CXX) $(CXXFLAGS) $(HEADERS) 58/LightStudy.C
	gcc -o StudyLightJets_PE100_58 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_58:
	$(CXX) $(CXXFLAGS) $(HEADERS) 58/LightStudy.C
	gcc -o StudyLightJets_PE100_58_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_59:
	$(CXX) $(CXXFLAGS) $(HEADERS) 59/LightStudy.C
	gcc -o StudyLightJets_PE100_59 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_59:
	$(CXX) $(CXXFLAGS) $(HEADERS) 59/LightStudy.C
	gcc -o StudyLightJets_PE100_59_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_60:
	$(CXX) $(CXXFLAGS) $(HEADERS) 60/LightStudy.C
	gcc -o StudyLightJets_PE100_60 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_60:
	$(CXX) $(CXXFLAGS) $(HEADERS) 60/LightStudy.C
	gcc -o StudyLightJets_PE100_60_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_61:
	$(CXX) $(CXXFLAGS) $(HEADERS) 61/LightStudy.C
	gcc -o StudyLightJets_PE100_61 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_61:
	$(CXX) $(CXXFLAGS) $(HEADERS) 61/LightStudy.C
	gcc -o StudyLightJets_PE100_61_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_62:
	$(CXX) $(CXXFLAGS) $(HEADERS) 62/LightStudy.C
	gcc -o StudyLightJets_PE100_62 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_62:
	$(CXX) $(CXXFLAGS) $(HEADERS) 62/LightStudy.C
	gcc -o StudyLightJets_PE100_62_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_63:
	$(CXX) $(CXXFLAGS) $(HEADERS) 63/LightStudy.C
	gcc -o StudyLightJets_PE100_63 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_63:
	$(CXX) $(CXXFLAGS) $(HEADERS) 63/LightStudy.C
	gcc -o StudyLightJets_PE100_63_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_64:
	$(CXX) $(CXXFLAGS) $(HEADERS) 64/LightStudy.C
	gcc -o StudyLightJets_PE100_64 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_64:
	$(CXX) $(CXXFLAGS) $(HEADERS) 64/LightStudy.C
	gcc -o StudyLightJets_PE100_64_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_65:
	$(CXX) $(CXXFLAGS) $(HEADERS) 65/LightStudy.C
	gcc -o StudyLightJets_PE100_65 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_65:
	$(CXX) $(CXXFLAGS) $(HEADERS) 65/LightStudy.C
	gcc -o StudyLightJets_PE100_65_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_66:
	$(CXX) $(CXXFLAGS) $(HEADERS) 66/LightStudy.C
	gcc -o StudyLightJets_PE100_66 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_66:
	$(CXX) $(CXXFLAGS) $(HEADERS) 66/LightStudy.C
	gcc -o StudyLightJets_PE100_66_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_67:
	$(CXX) $(CXXFLAGS) $(HEADERS) 67/LightStudy.C
	gcc -o StudyLightJets_PE100_67 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_67:
	$(CXX) $(CXXFLAGS) $(HEADERS) 67/LightStudy.C
	gcc -o StudyLightJets_PE100_67_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_68:
	$(CXX) $(CXXFLAGS) $(HEADERS) 68/LightStudy.C
	gcc -o StudyLightJets_PE100_68 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_68:
	$(CXX) $(CXXFLAGS) $(HEADERS) 68/LightStudy.C
	gcc -o StudyLightJets_PE100_68_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_69:
	$(CXX) $(CXXFLAGS) $(HEADERS) 69/LightStudy.C
	gcc -o StudyLightJets_PE100_69 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_69:
	$(CXX) $(CXXFLAGS) $(HEADERS) 69/LightStudy.C
	gcc -o StudyLightJets_PE100_69_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_70:
	$(CXX) $(CXXFLAGS) $(HEADERS) 70/LightStudy.C
	gcc -o StudyLightJets_PE100_70 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_70:
	$(CXX) $(CXXFLAGS) $(HEADERS) 70/LightStudy.C
	gcc -o StudyLightJets_PE100_70_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_71:
	$(CXX) $(CXXFLAGS) $(HEADERS) 71/LightStudy.C
	gcc -o StudyLightJets_PE100_71 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_71:
	$(CXX) $(CXXFLAGS) $(HEADERS) 71/LightStudy.C
	gcc -o StudyLightJets_PE100_71_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_72:
	$(CXX) $(CXXFLAGS) $(HEADERS) 72/LightStudy.C
	gcc -o StudyLightJets_PE100_72 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_72:
	$(CXX) $(CXXFLAGS) $(HEADERS) 72/LightStudy.C
	gcc -o StudyLightJets_PE100_72_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_73:
	$(CXX) $(CXXFLAGS) $(HEADERS) 73/LightStudy.C
	gcc -o StudyLightJets_PE100_73 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_73:
	$(CXX) $(CXXFLAGS) $(HEADERS) 73/LightStudy.C
	gcc -o StudyLightJets_PE100_73_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_74:
	$(CXX) $(CXXFLAGS) $(HEADERS) 74/LightStudy.C
	gcc -o StudyLightJets_PE100_74 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_74:
	$(CXX) $(CXXFLAGS) $(HEADERS) 74/LightStudy.C
	gcc -o StudyLightJets_PE100_74_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_75:
	$(CXX) $(CXXFLAGS) $(HEADERS) 75/LightStudy.C
	gcc -o StudyLightJets_PE100_75 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_75:
	$(CXX) $(CXXFLAGS) $(HEADERS) 75/LightStudy.C
	gcc -o StudyLightJets_PE100_75_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_76:
	$(CXX) $(CXXFLAGS) $(HEADERS) 76/LightStudy.C
	gcc -o StudyLightJets_PE100_76 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_76:
	$(CXX) $(CXXFLAGS) $(HEADERS) 76/LightStudy.C
	gcc -o StudyLightJets_PE100_76_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_77:
	$(CXX) $(CXXFLAGS) $(HEADERS) 77/LightStudy.C
	gcc -o StudyLightJets_PE100_77 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_77:
	$(CXX) $(CXXFLAGS) $(HEADERS) 77/LightStudy.C
	gcc -o StudyLightJets_PE100_77_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_78:
	$(CXX) $(CXXFLAGS) $(HEADERS) 78/LightStudy.C
	gcc -o StudyLightJets_PE100_78 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_78:
	$(CXX) $(CXXFLAGS) $(HEADERS) 78/LightStudy.C
	gcc -o StudyLightJets_PE100_78_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_79:
	$(CXX) $(CXXFLAGS) $(HEADERS) 79/LightStudy.C
	gcc -o StudyLightJets_PE100_79 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_79:
	$(CXX) $(CXXFLAGS) $(HEADERS) 79/LightStudy.C
	gcc -o StudyLightJets_PE100_79_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_80:
	$(CXX) $(CXXFLAGS) $(HEADERS) 80/LightStudy.C
	gcc -o StudyLightJets_PE100_80 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_80:
	$(CXX) $(CXXFLAGS) $(HEADERS) 80/LightStudy.C
	gcc -o StudyLightJets_PE100_80_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_81:
	$(CXX) $(CXXFLAGS) $(HEADERS) 81/LightStudy.C
	gcc -o StudyLightJets_PE100_81 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_81:
	$(CXX) $(CXXFLAGS) $(HEADERS) 81/LightStudy.C
	gcc -o StudyLightJets_PE100_81_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_82:
	$(CXX) $(CXXFLAGS) $(HEADERS) 82/LightStudy.C
	gcc -o StudyLightJets_PE100_82 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_82:
	$(CXX) $(CXXFLAGS) $(HEADERS) 82/LightStudy.C
	gcc -o StudyLightJets_PE100_82_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_83:
	$(CXX) $(CXXFLAGS) $(HEADERS) 83/LightStudy.C
	gcc -o StudyLightJets_PE100_83 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_83:
	$(CXX) $(CXXFLAGS) $(HEADERS) 83/LightStudy.C
	gcc -o StudyLightJets_PE100_83_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_84:
	$(CXX) $(CXXFLAGS) $(HEADERS) 84/LightStudy.C
	gcc -o StudyLightJets_PE100_84 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_84:
	$(CXX) $(CXXFLAGS) $(HEADERS) 84/LightStudy.C
	gcc -o StudyLightJets_PE100_84_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_85:
	$(CXX) $(CXXFLAGS) $(HEADERS) 85/LightStudy.C
	gcc -o StudyLightJets_PE100_85 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_85:
	$(CXX) $(CXXFLAGS) $(HEADERS) 85/LightStudy.C
	gcc -o StudyLightJets_PE100_85_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_86:
	$(CXX) $(CXXFLAGS) $(HEADERS) 86/LightStudy.C
	gcc -o StudyLightJets_PE100_86 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_86:
	$(CXX) $(CXXFLAGS) $(HEADERS) 86/LightStudy.C
	gcc -o StudyLightJets_PE100_86_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_87:
	$(CXX) $(CXXFLAGS) $(HEADERS) 87/LightStudy.C
	gcc -o StudyLightJets_PE100_87 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_87:
	$(CXX) $(CXXFLAGS) $(HEADERS) 87/LightStudy.C
	gcc -o StudyLightJets_PE100_87_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_88:
	$(CXX) $(CXXFLAGS) $(HEADERS) 88/LightStudy.C
	gcc -o StudyLightJets_PE100_88 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_88:
	$(CXX) $(CXXFLAGS) $(HEADERS) 88/LightStudy.C
	gcc -o StudyLightJets_PE100_88_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_89:
	$(CXX) $(CXXFLAGS) $(HEADERS) 89/LightStudy.C
	gcc -o StudyLightJets_PE100_89 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_89:
	$(CXX) $(CXXFLAGS) $(HEADERS) 89/LightStudy.C
	gcc -o StudyLightJets_PE100_89_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_90:
	$(CXX) $(CXXFLAGS) $(HEADERS) 90/LightStudy.C
	gcc -o StudyLightJets_PE100_90 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_90:
	$(CXX) $(CXXFLAGS) $(HEADERS) 90/LightStudy.C
	gcc -o StudyLightJets_PE100_90_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_91:
	$(CXX) $(CXXFLAGS) $(HEADERS) 91/LightStudy.C
	gcc -o StudyLightJets_PE100_91 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_91:
	$(CXX) $(CXXFLAGS) $(HEADERS) 91/LightStudy.C
	gcc -o StudyLightJets_PE100_91_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_92:
	$(CXX) $(CXXFLAGS) $(HEADERS) 92/LightStudy.C
	gcc -o StudyLightJets_PE100_92 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_92:
	$(CXX) $(CXXFLAGS) $(HEADERS) 92/LightStudy.C
	gcc -o StudyLightJets_PE100_92_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_93:
	$(CXX) $(CXXFLAGS) $(HEADERS) 93/LightStudy.C
	gcc -o StudyLightJets_PE100_93 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_93:
	$(CXX) $(CXXFLAGS) $(HEADERS) 93/LightStudy.C
	gcc -o StudyLightJets_PE100_93_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_94:
	$(CXX) $(CXXFLAGS) $(HEADERS) 94/LightStudy.C
	gcc -o StudyLightJets_PE100_94 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_94:
	$(CXX) $(CXXFLAGS) $(HEADERS) 94/LightStudy.C
	gcc -o StudyLightJets_PE100_94_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_95:
	$(CXX) $(CXXFLAGS) $(HEADERS) 95/LightStudy.C
	gcc -o StudyLightJets_PE100_95 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_95:
	$(CXX) $(CXXFLAGS) $(HEADERS) 95/LightStudy.C
	gcc -o StudyLightJets_PE100_95_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_96:
	$(CXX) $(CXXFLAGS) $(HEADERS) 96/LightStudy.C
	gcc -o StudyLightJets_PE100_96 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_96:
	$(CXX) $(CXXFLAGS) $(HEADERS) 96/LightStudy.C
	gcc -o StudyLightJets_PE100_96_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_97:
	$(CXX) $(CXXFLAGS) $(HEADERS) 97/LightStudy.C
	gcc -o StudyLightJets_PE100_97 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_97:
	$(CXX) $(CXXFLAGS) $(HEADERS) 97/LightStudy.C
	gcc -o StudyLightJets_PE100_97_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_98:
	$(CXX) $(CXXFLAGS) $(HEADERS) 98/LightStudy.C
	gcc -o StudyLightJets_PE100_98 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_98:
	$(CXX) $(CXXFLAGS) $(HEADERS) 98/LightStudy.C
	gcc -o StudyLightJets_PE100_98_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_99:
	$(CXX) $(CXXFLAGS) $(HEADERS) 99/LightStudy.C
	gcc -o StudyLightJets_PE100_99 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_99:
	$(CXX) $(CXXFLAGS) $(HEADERS) 99/LightStudy.C
	gcc -o StudyLightJets_PE100_99_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_100:
	$(CXX) $(CXXFLAGS) $(HEADERS) 100/LightStudy.C
	gcc -o StudyLightJets_PE100_100 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_100:
	$(CXX) $(CXXFLAGS) $(HEADERS) 100/LightStudy.C
	gcc -o StudyLightJets_PE100_100_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_101:
	$(CXX) $(CXXFLAGS) $(HEADERS) 101/LightStudy.C
	gcc -o StudyLightJets_PE100_101 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_101:
	$(CXX) $(CXXFLAGS) $(HEADERS) 101/LightStudy.C
	gcc -o StudyLightJets_PE100_101_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_102:
	$(CXX) $(CXXFLAGS) $(HEADERS) 102/LightStudy.C
	gcc -o StudyLightJets_PE100_102 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_102:
	$(CXX) $(CXXFLAGS) $(HEADERS) 102/LightStudy.C
	gcc -o StudyLightJets_PE100_102_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_103:
	$(CXX) $(CXXFLAGS) $(HEADERS) 103/LightStudy.C
	gcc -o StudyLightJets_PE100_103 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_103:
	$(CXX) $(CXXFLAGS) $(HEADERS) 103/LightStudy.C
	gcc -o StudyLightJets_PE100_103_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_104:
	$(CXX) $(CXXFLAGS) $(HEADERS) 104/LightStudy.C
	gcc -o StudyLightJets_PE100_104 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_104:
	$(CXX) $(CXXFLAGS) $(HEADERS) 104/LightStudy.C
	gcc -o StudyLightJets_PE100_104_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_105:
	$(CXX) $(CXXFLAGS) $(HEADERS) 105/LightStudy.C
	gcc -o StudyLightJets_PE100_105 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_105:
	$(CXX) $(CXXFLAGS) $(HEADERS) 105/LightStudy.C
	gcc -o StudyLightJets_PE100_105_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_106:
	$(CXX) $(CXXFLAGS) $(HEADERS) 106/LightStudy.C
	gcc -o StudyLightJets_PE100_106 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_106:
	$(CXX) $(CXXFLAGS) $(HEADERS) 106/LightStudy.C
	gcc -o StudyLightJets_PE100_106_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_107:
	$(CXX) $(CXXFLAGS) $(HEADERS) 107/LightStudy.C
	gcc -o StudyLightJets_PE100_107 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_107:
	$(CXX) $(CXXFLAGS) $(HEADERS) 107/LightStudy.C
	gcc -o StudyLightJets_PE100_107_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_108:
	$(CXX) $(CXXFLAGS) $(HEADERS) 108/LightStudy.C
	gcc -o StudyLightJets_PE100_108 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_108:
	$(CXX) $(CXXFLAGS) $(HEADERS) 108/LightStudy.C
	gcc -o StudyLightJets_PE100_108_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_109:
	$(CXX) $(CXXFLAGS) $(HEADERS) 109/LightStudy.C
	gcc -o StudyLightJets_PE100_109 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_109:
	$(CXX) $(CXXFLAGS) $(HEADERS) 109/LightStudy.C
	gcc -o StudyLightJets_PE100_109_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_110:
	$(CXX) $(CXXFLAGS) $(HEADERS) 110/LightStudy.C
	gcc -o StudyLightJets_PE100_110 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_110:
	$(CXX) $(CXXFLAGS) $(HEADERS) 110/LightStudy.C
	gcc -o StudyLightJets_PE100_110_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_111:
	$(CXX) $(CXXFLAGS) $(HEADERS) 111/LightStudy.C
	gcc -o StudyLightJets_PE100_111 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_111:
	$(CXX) $(CXXFLAGS) $(HEADERS) 111/LightStudy.C
	gcc -o StudyLightJets_PE100_111_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_112:
	$(CXX) $(CXXFLAGS) $(HEADERS) 112/LightStudy.C
	gcc -o StudyLightJets_PE100_112 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_112:
	$(CXX) $(CXXFLAGS) $(HEADERS) 112/LightStudy.C
	gcc -o StudyLightJets_PE100_112_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_113:
	$(CXX) $(CXXFLAGS) $(HEADERS) 113/LightStudy.C
	gcc -o StudyLightJets_PE100_113 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_113:
	$(CXX) $(CXXFLAGS) $(HEADERS) 113/LightStudy.C
	gcc -o StudyLightJets_PE100_113_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_114:
	$(CXX) $(CXXFLAGS) $(HEADERS) 114/LightStudy.C
	gcc -o StudyLightJets_PE100_114 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_114:
	$(CXX) $(CXXFLAGS) $(HEADERS) 114/LightStudy.C
	gcc -o StudyLightJets_PE100_114_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_115:
	$(CXX) $(CXXFLAGS) $(HEADERS) 115/LightStudy.C
	gcc -o StudyLightJets_PE100_115 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_115:
	$(CXX) $(CXXFLAGS) $(HEADERS) 115/LightStudy.C
	gcc -o StudyLightJets_PE100_115_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_116:
	$(CXX) $(CXXFLAGS) $(HEADERS) 116/LightStudy.C
	gcc -o StudyLightJets_PE100_116 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_116:
	$(CXX) $(CXXFLAGS) $(HEADERS) 116/LightStudy.C
	gcc -o StudyLightJets_PE100_116_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_117:
	$(CXX) $(CXXFLAGS) $(HEADERS) 117/LightStudy.C
	gcc -o StudyLightJets_PE100_117 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_117:
	$(CXX) $(CXXFLAGS) $(HEADERS) 117/LightStudy.C
	gcc -o StudyLightJets_PE100_117_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_118:
	$(CXX) $(CXXFLAGS) $(HEADERS) 118/LightStudy.C
	gcc -o StudyLightJets_PE100_118 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_118:
	$(CXX) $(CXXFLAGS) $(HEADERS) 118/LightStudy.C
	gcc -o StudyLightJets_PE100_118_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_119:
	$(CXX) $(CXXFLAGS) $(HEADERS) 119/LightStudy.C
	gcc -o StudyLightJets_PE100_119 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_119:
	$(CXX) $(CXXFLAGS) $(HEADERS) 119/LightStudy.C
	gcc -o StudyLightJets_PE100_119_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_120:
	$(CXX) $(CXXFLAGS) $(HEADERS) 120/LightStudy.C
	gcc -o StudyLightJets_PE100_120 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_120:
	$(CXX) $(CXXFLAGS) $(HEADERS) 120/LightStudy.C
	gcc -o StudyLightJets_PE100_120_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_121:
	$(CXX) $(CXXFLAGS) $(HEADERS) 121/LightStudy.C
	gcc -o StudyLightJets_PE100_121 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_121:
	$(CXX) $(CXXFLAGS) $(HEADERS) 121/LightStudy.C
	gcc -o StudyLightJets_PE100_121_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_122:
	$(CXX) $(CXXFLAGS) $(HEADERS) 122/LightStudy.C
	gcc -o StudyLightJets_PE100_122 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_122:
	$(CXX) $(CXXFLAGS) $(HEADERS) 122/LightStudy.C
	gcc -o StudyLightJets_PE100_122_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_123:
	$(CXX) $(CXXFLAGS) $(HEADERS) 123/LightStudy.C
	gcc -o StudyLightJets_PE100_123 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_123:
	$(CXX) $(CXXFLAGS) $(HEADERS) 123/LightStudy.C
	gcc -o StudyLightJets_PE100_123_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_124:
	$(CXX) $(CXXFLAGS) $(HEADERS) 124/LightStudy.C
	gcc -o StudyLightJets_PE100_124 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_124:
	$(CXX) $(CXXFLAGS) $(HEADERS) 124/LightStudy.C
	gcc -o StudyLightJets_PE100_124_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_125:
	$(CXX) $(CXXFLAGS) $(HEADERS) 125/LightStudy.C
	gcc -o StudyLightJets_PE100_125 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_125:
	$(CXX) $(CXXFLAGS) $(HEADERS) 125/LightStudy.C
	gcc -o StudyLightJets_PE100_125_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_126:
	$(CXX) $(CXXFLAGS) $(HEADERS) 126/LightStudy.C
	gcc -o StudyLightJets_PE100_126 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_126:
	$(CXX) $(CXXFLAGS) $(HEADERS) 126/LightStudy.C
	gcc -o StudyLightJets_PE100_126_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_127:
	$(CXX) $(CXXFLAGS) $(HEADERS) 127/LightStudy.C
	gcc -o StudyLightJets_PE100_127 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_127:
	$(CXX) $(CXXFLAGS) $(HEADERS) 127/LightStudy.C
	gcc -o StudyLightJets_PE100_127_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_128:
	$(CXX) $(CXXFLAGS) $(HEADERS) 128/LightStudy.C
	gcc -o StudyLightJets_PE100_128 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_128:
	$(CXX) $(CXXFLAGS) $(HEADERS) 128/LightStudy.C
	gcc -o StudyLightJets_PE100_128_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_129:
	$(CXX) $(CXXFLAGS) $(HEADERS) 129/LightStudy.C
	gcc -o StudyLightJets_PE100_129 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_129:
	$(CXX) $(CXXFLAGS) $(HEADERS) 129/LightStudy.C
	gcc -o StudyLightJets_PE100_129_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_130:
	$(CXX) $(CXXFLAGS) $(HEADERS) 130/LightStudy.C
	gcc -o StudyLightJets_PE100_130 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_130:
	$(CXX) $(CXXFLAGS) $(HEADERS) 130/LightStudy.C
	gcc -o StudyLightJets_PE100_130_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_131:
	$(CXX) $(CXXFLAGS) $(HEADERS) 131/LightStudy.C
	gcc -o StudyLightJets_PE100_131 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_131:
	$(CXX) $(CXXFLAGS) $(HEADERS) 131/LightStudy.C
	gcc -o StudyLightJets_PE100_131_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_132:
	$(CXX) $(CXXFLAGS) $(HEADERS) 132/LightStudy.C
	gcc -o StudyLightJets_PE100_132 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_132:
	$(CXX) $(CXXFLAGS) $(HEADERS) 132/LightStudy.C
	gcc -o StudyLightJets_PE100_132_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_133:
	$(CXX) $(CXXFLAGS) $(HEADERS) 133/LightStudy.C
	gcc -o StudyLightJets_PE100_133 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_133:
	$(CXX) $(CXXFLAGS) $(HEADERS) 133/LightStudy.C
	gcc -o StudyLightJets_PE100_133_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_134:
	$(CXX) $(CXXFLAGS) $(HEADERS) 134/LightStudy.C
	gcc -o StudyLightJets_PE100_134 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_134:
	$(CXX) $(CXXFLAGS) $(HEADERS) 134/LightStudy.C
	gcc -o StudyLightJets_PE100_134_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_135:
	$(CXX) $(CXXFLAGS) $(HEADERS) 135/LightStudy.C
	gcc -o StudyLightJets_PE100_135 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_135:
	$(CXX) $(CXXFLAGS) $(HEADERS) 135/LightStudy.C
	gcc -o StudyLightJets_PE100_135_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_136:
	$(CXX) $(CXXFLAGS) $(HEADERS) 136/LightStudy.C
	gcc -o StudyLightJets_PE100_136 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_136:
	$(CXX) $(CXXFLAGS) $(HEADERS) 136/LightStudy.C
	gcc -o StudyLightJets_PE100_136_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_137:
	$(CXX) $(CXXFLAGS) $(HEADERS) 137/LightStudy.C
	gcc -o StudyLightJets_PE100_137 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_137:
	$(CXX) $(CXXFLAGS) $(HEADERS) 137/LightStudy.C
	gcc -o StudyLightJets_PE100_137_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_138:
	$(CXX) $(CXXFLAGS) $(HEADERS) 138/LightStudy.C
	gcc -o StudyLightJets_PE100_138 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_138:
	$(CXX) $(CXXFLAGS) $(HEADERS) 138/LightStudy.C
	gcc -o StudyLightJets_PE100_138_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_139:
	$(CXX) $(CXXFLAGS) $(HEADERS) 139/LightStudy.C
	gcc -o StudyLightJets_PE100_139 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_139:
	$(CXX) $(CXXFLAGS) $(HEADERS) 139/LightStudy.C
	gcc -o StudyLightJets_PE100_139_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_140:
	$(CXX) $(CXXFLAGS) $(HEADERS) 140/LightStudy.C
	gcc -o StudyLightJets_PE100_140 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_140:
	$(CXX) $(CXXFLAGS) $(HEADERS) 140/LightStudy.C
	gcc -o StudyLightJets_PE100_140_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_141:
	$(CXX) $(CXXFLAGS) $(HEADERS) 141/LightStudy.C
	gcc -o StudyLightJets_PE100_141 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_141:
	$(CXX) $(CXXFLAGS) $(HEADERS) 141/LightStudy.C
	gcc -o StudyLightJets_PE100_141_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_142:
	$(CXX) $(CXXFLAGS) $(HEADERS) 142/LightStudy.C
	gcc -o StudyLightJets_PE100_142 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_142:
	$(CXX) $(CXXFLAGS) $(HEADERS) 142/LightStudy.C
	gcc -o StudyLightJets_PE100_142_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_143:
	$(CXX) $(CXXFLAGS) $(HEADERS) 143/LightStudy.C
	gcc -o StudyLightJets_PE100_143 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_143:
	$(CXX) $(CXXFLAGS) $(HEADERS) 143/LightStudy.C
	gcc -o StudyLightJets_PE100_143_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_144:
	$(CXX) $(CXXFLAGS) $(HEADERS) 144/LightStudy.C
	gcc -o StudyLightJets_PE100_144 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_144:
	$(CXX) $(CXXFLAGS) $(HEADERS) 144/LightStudy.C
	gcc -o StudyLightJets_PE100_144_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_145:
	$(CXX) $(CXXFLAGS) $(HEADERS) 145/LightStudy.C
	gcc -o StudyLightJets_PE100_145 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_145:
	$(CXX) $(CXXFLAGS) $(HEADERS) 145/LightStudy.C
	gcc -o StudyLightJets_PE100_145_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_146:
	$(CXX) $(CXXFLAGS) $(HEADERS) 146/LightStudy.C
	gcc -o StudyLightJets_PE100_146 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_146:
	$(CXX) $(CXXFLAGS) $(HEADERS) 146/LightStudy.C
	gcc -o StudyLightJets_PE100_146_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_147:
	$(CXX) $(CXXFLAGS) $(HEADERS) 147/LightStudy.C
	gcc -o StudyLightJets_PE100_147 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_147:
	$(CXX) $(CXXFLAGS) $(HEADERS) 147/LightStudy.C
	gcc -o StudyLightJets_PE100_147_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_148:
	$(CXX) $(CXXFLAGS) $(HEADERS) 148/LightStudy.C
	gcc -o StudyLightJets_PE100_148 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_148:
	$(CXX) $(CXXFLAGS) $(HEADERS) 148/LightStudy.C
	gcc -o StudyLightJets_PE100_148_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_149:
	$(CXX) $(CXXFLAGS) $(HEADERS) 149/LightStudy.C
	gcc -o StudyLightJets_PE100_149 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_149:
	$(CXX) $(CXXFLAGS) $(HEADERS) 149/LightStudy.C
	gcc -o StudyLightJets_PE100_149_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_150:
	$(CXX) $(CXXFLAGS) $(HEADERS) 150/LightStudy.C
	gcc -o StudyLightJets_PE100_150 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_150:
	$(CXX) $(CXXFLAGS) $(HEADERS) 150/LightStudy.C
	gcc -o StudyLightJets_PE100_150_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_151:
	$(CXX) $(CXXFLAGS) $(HEADERS) 151/LightStudy.C
	gcc -o StudyLightJets_PE100_151 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_151:
	$(CXX) $(CXXFLAGS) $(HEADERS) 151/LightStudy.C
	gcc -o StudyLightJets_PE100_151_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_152:
	$(CXX) $(CXXFLAGS) $(HEADERS) 152/LightStudy.C
	gcc -o StudyLightJets_PE100_152 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_152:
	$(CXX) $(CXXFLAGS) $(HEADERS) 152/LightStudy.C
	gcc -o StudyLightJets_PE100_152_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_153:
	$(CXX) $(CXXFLAGS) $(HEADERS) 153/LightStudy.C
	gcc -o StudyLightJets_PE100_153 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_153:
	$(CXX) $(CXXFLAGS) $(HEADERS) 153/LightStudy.C
	gcc -o StudyLightJets_PE100_153_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_154:
	$(CXX) $(CXXFLAGS) $(HEADERS) 154/LightStudy.C
	gcc -o StudyLightJets_PE100_154 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_154:
	$(CXX) $(CXXFLAGS) $(HEADERS) 154/LightStudy.C
	gcc -o StudyLightJets_PE100_154_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_155:
	$(CXX) $(CXXFLAGS) $(HEADERS) 155/LightStudy.C
	gcc -o StudyLightJets_PE100_155 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_155:
	$(CXX) $(CXXFLAGS) $(HEADERS) 155/LightStudy.C
	gcc -o StudyLightJets_PE100_155_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_156:
	$(CXX) $(CXXFLAGS) $(HEADERS) 156/LightStudy.C
	gcc -o StudyLightJets_PE100_156 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_156:
	$(CXX) $(CXXFLAGS) $(HEADERS) 156/LightStudy.C
	gcc -o StudyLightJets_PE100_156_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_157:
	$(CXX) $(CXXFLAGS) $(HEADERS) 157/LightStudy.C
	gcc -o StudyLightJets_PE100_157 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_157:
	$(CXX) $(CXXFLAGS) $(HEADERS) 157/LightStudy.C
	gcc -o StudyLightJets_PE100_157_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_158:
	$(CXX) $(CXXFLAGS) $(HEADERS) 158/LightStudy.C
	gcc -o StudyLightJets_PE100_158 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_158:
	$(CXX) $(CXXFLAGS) $(HEADERS) 158/LightStudy.C
	gcc -o StudyLightJets_PE100_158_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_159:
	$(CXX) $(CXXFLAGS) $(HEADERS) 159/LightStudy.C
	gcc -o StudyLightJets_PE100_159 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_159:
	$(CXX) $(CXXFLAGS) $(HEADERS) 159/LightStudy.C
	gcc -o StudyLightJets_PE100_159_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_160:
	$(CXX) $(CXXFLAGS) $(HEADERS) 160/LightStudy.C
	gcc -o StudyLightJets_PE100_160 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_160:
	$(CXX) $(CXXFLAGS) $(HEADERS) 160/LightStudy.C
	gcc -o StudyLightJets_PE100_160_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_161:
	$(CXX) $(CXXFLAGS) $(HEADERS) 161/LightStudy.C
	gcc -o StudyLightJets_PE100_161 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_161:
	$(CXX) $(CXXFLAGS) $(HEADERS) 161/LightStudy.C
	gcc -o StudyLightJets_PE100_161_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_162:
	$(CXX) $(CXXFLAGS) $(HEADERS) 162/LightStudy.C
	gcc -o StudyLightJets_PE100_162 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_162:
	$(CXX) $(CXXFLAGS) $(HEADERS) 162/LightStudy.C
	gcc -o StudyLightJets_PE100_162_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_163:
	$(CXX) $(CXXFLAGS) $(HEADERS) 163/LightStudy.C
	gcc -o StudyLightJets_PE100_163 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_163:
	$(CXX) $(CXXFLAGS) $(HEADERS) 163/LightStudy.C
	gcc -o StudyLightJets_PE100_163_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_164:
	$(CXX) $(CXXFLAGS) $(HEADERS) 164/LightStudy.C
	gcc -o StudyLightJets_PE100_164 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_164:
	$(CXX) $(CXXFLAGS) $(HEADERS) 164/LightStudy.C
	gcc -o StudyLightJets_PE100_164_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_165:
	$(CXX) $(CXXFLAGS) $(HEADERS) 165/LightStudy.C
	gcc -o StudyLightJets_PE100_165 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_165:
	$(CXX) $(CXXFLAGS) $(HEADERS) 165/LightStudy.C
	gcc -o StudyLightJets_PE100_165_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_166:
	$(CXX) $(CXXFLAGS) $(HEADERS) 166/LightStudy.C
	gcc -o StudyLightJets_PE100_166 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_166:
	$(CXX) $(CXXFLAGS) $(HEADERS) 166/LightStudy.C
	gcc -o StudyLightJets_PE100_166_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_167:
	$(CXX) $(CXXFLAGS) $(HEADERS) 167/LightStudy.C
	gcc -o StudyLightJets_PE100_167 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_167:
	$(CXX) $(CXXFLAGS) $(HEADERS) 167/LightStudy.C
	gcc -o StudyLightJets_PE100_167_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_168:
	$(CXX) $(CXXFLAGS) $(HEADERS) 168/LightStudy.C
	gcc -o StudyLightJets_PE100_168 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_168:
	$(CXX) $(CXXFLAGS) $(HEADERS) 168/LightStudy.C
	gcc -o StudyLightJets_PE100_168_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_169:
	$(CXX) $(CXXFLAGS) $(HEADERS) 169/LightStudy.C
	gcc -o StudyLightJets_PE100_169 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_169:
	$(CXX) $(CXXFLAGS) $(HEADERS) 169/LightStudy.C
	gcc -o StudyLightJets_PE100_169_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_170:
	$(CXX) $(CXXFLAGS) $(HEADERS) 170/LightStudy.C
	gcc -o StudyLightJets_PE100_170 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_170:
	$(CXX) $(CXXFLAGS) $(HEADERS) 170/LightStudy.C
	gcc -o StudyLightJets_PE100_170_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_171:
	$(CXX) $(CXXFLAGS) $(HEADERS) 171/LightStudy.C
	gcc -o StudyLightJets_PE100_171 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_171:
	$(CXX) $(CXXFLAGS) $(HEADERS) 171/LightStudy.C
	gcc -o StudyLightJets_PE100_171_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_172:
	$(CXX) $(CXXFLAGS) $(HEADERS) 172/LightStudy.C
	gcc -o StudyLightJets_PE100_172 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_172:
	$(CXX) $(CXXFLAGS) $(HEADERS) 172/LightStudy.C
	gcc -o StudyLightJets_PE100_172_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_173:
	$(CXX) $(CXXFLAGS) $(HEADERS) 173/LightStudy.C
	gcc -o StudyLightJets_PE100_173 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_173:
	$(CXX) $(CXXFLAGS) $(HEADERS) 173/LightStudy.C
	gcc -o StudyLightJets_PE100_173_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_174:
	$(CXX) $(CXXFLAGS) $(HEADERS) 174/LightStudy.C
	gcc -o StudyLightJets_PE100_174 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_174:
	$(CXX) $(CXXFLAGS) $(HEADERS) 174/LightStudy.C
	gcc -o StudyLightJets_PE100_174_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_175:
	$(CXX) $(CXXFLAGS) $(HEADERS) 175/LightStudy.C
	gcc -o StudyLightJets_PE100_175 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_175:
	$(CXX) $(CXXFLAGS) $(HEADERS) 175/LightStudy.C
	gcc -o StudyLightJets_PE100_175_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_176:
	$(CXX) $(CXXFLAGS) $(HEADERS) 176/LightStudy.C
	gcc -o StudyLightJets_PE100_176 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_176:
	$(CXX) $(CXXFLAGS) $(HEADERS) 176/LightStudy.C
	gcc -o StudyLightJets_PE100_176_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_177:
	$(CXX) $(CXXFLAGS) $(HEADERS) 177/LightStudy.C
	gcc -o StudyLightJets_PE100_177 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_177:
	$(CXX) $(CXXFLAGS) $(HEADERS) 177/LightStudy.C
	gcc -o StudyLightJets_PE100_177_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_178:
	$(CXX) $(CXXFLAGS) $(HEADERS) 178/LightStudy.C
	gcc -o StudyLightJets_PE100_178 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_178:
	$(CXX) $(CXXFLAGS) $(HEADERS) 178/LightStudy.C
	gcc -o StudyLightJets_PE100_178_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_179:
	$(CXX) $(CXXFLAGS) $(HEADERS) 179/LightStudy.C
	gcc -o StudyLightJets_PE100_179 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_179:
	$(CXX) $(CXXFLAGS) $(HEADERS) 179/LightStudy.C
	gcc -o StudyLightJets_PE100_179_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_180:
	$(CXX) $(CXXFLAGS) $(HEADERS) 180/LightStudy.C
	gcc -o StudyLightJets_PE100_180 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_180:
	$(CXX) $(CXXFLAGS) $(HEADERS) 180/LightStudy.C
	gcc -o StudyLightJets_PE100_180_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_181:
	$(CXX) $(CXXFLAGS) $(HEADERS) 181/LightStudy.C
	gcc -o StudyLightJets_PE100_181 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_181:
	$(CXX) $(CXXFLAGS) $(HEADERS) 181/LightStudy.C
	gcc -o StudyLightJets_PE100_181_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_182:
	$(CXX) $(CXXFLAGS) $(HEADERS) 182/LightStudy.C
	gcc -o StudyLightJets_PE100_182 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_182:
	$(CXX) $(CXXFLAGS) $(HEADERS) 182/LightStudy.C
	gcc -o StudyLightJets_PE100_182_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_183:
	$(CXX) $(CXXFLAGS) $(HEADERS) 183/LightStudy.C
	gcc -o StudyLightJets_PE100_183 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_183:
	$(CXX) $(CXXFLAGS) $(HEADERS) 183/LightStudy.C
	gcc -o StudyLightJets_PE100_183_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_184:
	$(CXX) $(CXXFLAGS) $(HEADERS) 184/LightStudy.C
	gcc -o StudyLightJets_PE100_184 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_184:
	$(CXX) $(CXXFLAGS) $(HEADERS) 184/LightStudy.C
	gcc -o StudyLightJets_PE100_184_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_185:
	$(CXX) $(CXXFLAGS) $(HEADERS) 185/LightStudy.C
	gcc -o StudyLightJets_PE100_185 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_185:
	$(CXX) $(CXXFLAGS) $(HEADERS) 185/LightStudy.C
	gcc -o StudyLightJets_PE100_185_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_186:
	$(CXX) $(CXXFLAGS) $(HEADERS) 186/LightStudy.C
	gcc -o StudyLightJets_PE100_186 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_186:
	$(CXX) $(CXXFLAGS) $(HEADERS) 186/LightStudy.C
	gcc -o StudyLightJets_PE100_186_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_187:
	$(CXX) $(CXXFLAGS) $(HEADERS) 187/LightStudy.C
	gcc -o StudyLightJets_PE100_187 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_187:
	$(CXX) $(CXXFLAGS) $(HEADERS) 187/LightStudy.C
	gcc -o StudyLightJets_PE100_187_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_188:
	$(CXX) $(CXXFLAGS) $(HEADERS) 188/LightStudy.C
	gcc -o StudyLightJets_PE100_188 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_188:
	$(CXX) $(CXXFLAGS) $(HEADERS) 188/LightStudy.C
	gcc -o StudyLightJets_PE100_188_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_189:
	$(CXX) $(CXXFLAGS) $(HEADERS) 189/LightStudy.C
	gcc -o StudyLightJets_PE100_189 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_189:
	$(CXX) $(CXXFLAGS) $(HEADERS) 189/LightStudy.C
	gcc -o StudyLightJets_PE100_189_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_190:
	$(CXX) $(CXXFLAGS) $(HEADERS) 190/LightStudy.C
	gcc -o StudyLightJets_PE100_190 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_190:
	$(CXX) $(CXXFLAGS) $(HEADERS) 190/LightStudy.C
	gcc -o StudyLightJets_PE100_190_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_191:
	$(CXX) $(CXXFLAGS) $(HEADERS) 191/LightStudy.C
	gcc -o StudyLightJets_PE100_191 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_191:
	$(CXX) $(CXXFLAGS) $(HEADERS) 191/LightStudy.C
	gcc -o StudyLightJets_PE100_191_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_192:
	$(CXX) $(CXXFLAGS) $(HEADERS) 192/LightStudy.C
	gcc -o StudyLightJets_PE100_192 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_192:
	$(CXX) $(CXXFLAGS) $(HEADERS) 192/LightStudy.C
	gcc -o StudyLightJets_PE100_192_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_193:
	$(CXX) $(CXXFLAGS) $(HEADERS) 193/LightStudy.C
	gcc -o StudyLightJets_PE100_193 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_193:
	$(CXX) $(CXXFLAGS) $(HEADERS) 193/LightStudy.C
	gcc -o StudyLightJets_PE100_193_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_194:
	$(CXX) $(CXXFLAGS) $(HEADERS) 194/LightStudy.C
	gcc -o StudyLightJets_PE100_194 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_194:
	$(CXX) $(CXXFLAGS) $(HEADERS) 194/LightStudy.C
	gcc -o StudyLightJets_PE100_194_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_195:
	$(CXX) $(CXXFLAGS) $(HEADERS) 195/LightStudy.C
	gcc -o StudyLightJets_PE100_195 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_195:
	$(CXX) $(CXXFLAGS) $(HEADERS) 195/LightStudy.C
	gcc -o StudyLightJets_PE100_195_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_196:
	$(CXX) $(CXXFLAGS) $(HEADERS) 196/LightStudy.C
	gcc -o StudyLightJets_PE100_196 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_196:
	$(CXX) $(CXXFLAGS) $(HEADERS) 196/LightStudy.C
	gcc -o StudyLightJets_PE100_196_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_197:
	$(CXX) $(CXXFLAGS) $(HEADERS) 197/LightStudy.C
	gcc -o StudyLightJets_PE100_197 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_197:
	$(CXX) $(CXXFLAGS) $(HEADERS) 197/LightStudy.C
	gcc -o StudyLightJets_PE100_197_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_198:
	$(CXX) $(CXXFLAGS) $(HEADERS) 198/LightStudy.C
	gcc -o StudyLightJets_PE100_198 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_198:
	$(CXX) $(CXXFLAGS) $(HEADERS) 198/LightStudy.C
	gcc -o StudyLightJets_PE100_198_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_199:
	$(CXX) $(CXXFLAGS) $(HEADERS) 199/LightStudy.C
	gcc -o StudyLightJets_PE100_199 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_199:
	$(CXX) $(CXXFLAGS) $(HEADERS) 199/LightStudy.C
	gcc -o StudyLightJets_PE100_199_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_200:
	$(CXX) $(CXXFLAGS) $(HEADERS) 200/LightStudy.C
	gcc -o StudyLightJets_PE100_200 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_200:
	$(CXX) $(CXXFLAGS) $(HEADERS) 200/LightStudy.C
	gcc -o StudyLightJets_PE100_200_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_201:
	$(CXX) $(CXXFLAGS) $(HEADERS) 201/LightStudy.C
	gcc -o StudyLightJets_PE100_201 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_201:
	$(CXX) $(CXXFLAGS) $(HEADERS) 201/LightStudy.C
	gcc -o StudyLightJets_PE100_201_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_202:
	$(CXX) $(CXXFLAGS) $(HEADERS) 202/LightStudy.C
	gcc -o StudyLightJets_PE100_202 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_202:
	$(CXX) $(CXXFLAGS) $(HEADERS) 202/LightStudy.C
	gcc -o StudyLightJets_PE100_202_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_203:
	$(CXX) $(CXXFLAGS) $(HEADERS) 203/LightStudy.C
	gcc -o StudyLightJets_PE100_203 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_203:
	$(CXX) $(CXXFLAGS) $(HEADERS) 203/LightStudy.C
	gcc -o StudyLightJets_PE100_203_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_204:
	$(CXX) $(CXXFLAGS) $(HEADERS) 204/LightStudy.C
	gcc -o StudyLightJets_PE100_204 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_204:
	$(CXX) $(CXXFLAGS) $(HEADERS) 204/LightStudy.C
	gcc -o StudyLightJets_PE100_204_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_205:
	$(CXX) $(CXXFLAGS) $(HEADERS) 205/LightStudy.C
	gcc -o StudyLightJets_PE100_205 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_205:
	$(CXX) $(CXXFLAGS) $(HEADERS) 205/LightStudy.C
	gcc -o StudyLightJets_PE100_205_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_206:
	$(CXX) $(CXXFLAGS) $(HEADERS) 206/LightStudy.C
	gcc -o StudyLightJets_PE100_206 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_206:
	$(CXX) $(CXXFLAGS) $(HEADERS) 206/LightStudy.C
	gcc -o StudyLightJets_PE100_206_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_207:
	$(CXX) $(CXXFLAGS) $(HEADERS) 207/LightStudy.C
	gcc -o StudyLightJets_PE100_207 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_207:
	$(CXX) $(CXXFLAGS) $(HEADERS) 207/LightStudy.C
	gcc -o StudyLightJets_PE100_207_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_208:
	$(CXX) $(CXXFLAGS) $(HEADERS) 208/LightStudy.C
	gcc -o StudyLightJets_PE100_208 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_208:
	$(CXX) $(CXXFLAGS) $(HEADERS) 208/LightStudy.C
	gcc -o StudyLightJets_PE100_208_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_209:
	$(CXX) $(CXXFLAGS) $(HEADERS) 209/LightStudy.C
	gcc -o StudyLightJets_PE100_209 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_209:
	$(CXX) $(CXXFLAGS) $(HEADERS) 209/LightStudy.C
	gcc -o StudyLightJets_PE100_209_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_210:
	$(CXX) $(CXXFLAGS) $(HEADERS) 210/LightStudy.C
	gcc -o StudyLightJets_PE100_210 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_210:
	$(CXX) $(CXXFLAGS) $(HEADERS) 210/LightStudy.C
	gcc -o StudyLightJets_PE100_210_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_211:
	$(CXX) $(CXXFLAGS) $(HEADERS) 211/LightStudy.C
	gcc -o StudyLightJets_PE100_211 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_211:
	$(CXX) $(CXXFLAGS) $(HEADERS) 211/LightStudy.C
	gcc -o StudyLightJets_PE100_211_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_212:
	$(CXX) $(CXXFLAGS) $(HEADERS) 212/LightStudy.C
	gcc -o StudyLightJets_PE100_212 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_212:
	$(CXX) $(CXXFLAGS) $(HEADERS) 212/LightStudy.C
	gcc -o StudyLightJets_PE100_212_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_213:
	$(CXX) $(CXXFLAGS) $(HEADERS) 213/LightStudy.C
	gcc -o StudyLightJets_PE100_213 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_213:
	$(CXX) $(CXXFLAGS) $(HEADERS) 213/LightStudy.C
	gcc -o StudyLightJets_PE100_213_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_214:
	$(CXX) $(CXXFLAGS) $(HEADERS) 214/LightStudy.C
	gcc -o StudyLightJets_PE100_214 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_214:
	$(CXX) $(CXXFLAGS) $(HEADERS) 214/LightStudy.C
	gcc -o StudyLightJets_PE100_214_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_215:
	$(CXX) $(CXXFLAGS) $(HEADERS) 215/LightStudy.C
	gcc -o StudyLightJets_PE100_215 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_215:
	$(CXX) $(CXXFLAGS) $(HEADERS) 215/LightStudy.C
	gcc -o StudyLightJets_PE100_215_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_216:
	$(CXX) $(CXXFLAGS) $(HEADERS) 216/LightStudy.C
	gcc -o StudyLightJets_PE100_216 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_216:
	$(CXX) $(CXXFLAGS) $(HEADERS) 216/LightStudy.C
	gcc -o StudyLightJets_PE100_216_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_217:
	$(CXX) $(CXXFLAGS) $(HEADERS) 217/LightStudy.C
	gcc -o StudyLightJets_PE100_217 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_217:
	$(CXX) $(CXXFLAGS) $(HEADERS) 217/LightStudy.C
	gcc -o StudyLightJets_PE100_217_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_218:
	$(CXX) $(CXXFLAGS) $(HEADERS) 218/LightStudy.C
	gcc -o StudyLightJets_PE100_218 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_218:
	$(CXX) $(CXXFLAGS) $(HEADERS) 218/LightStudy.C
	gcc -o StudyLightJets_PE100_218_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_219:
	$(CXX) $(CXXFLAGS) $(HEADERS) 219/LightStudy.C
	gcc -o StudyLightJets_PE100_219 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_219:
	$(CXX) $(CXXFLAGS) $(HEADERS) 219/LightStudy.C
	gcc -o StudyLightJets_PE100_219_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_220:
	$(CXX) $(CXXFLAGS) $(HEADERS) 220/LightStudy.C
	gcc -o StudyLightJets_PE100_220 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_220:
	$(CXX) $(CXXFLAGS) $(HEADERS) 220/LightStudy.C
	gcc -o StudyLightJets_PE100_220_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_221:
	$(CXX) $(CXXFLAGS) $(HEADERS) 221/LightStudy.C
	gcc -o StudyLightJets_PE100_221 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_221:
	$(CXX) $(CXXFLAGS) $(HEADERS) 221/LightStudy.C
	gcc -o StudyLightJets_PE100_221_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_222:
	$(CXX) $(CXXFLAGS) $(HEADERS) 222/LightStudy.C
	gcc -o StudyLightJets_PE100_222 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_222:
	$(CXX) $(CXXFLAGS) $(HEADERS) 222/LightStudy.C
	gcc -o StudyLightJets_PE100_222_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_223:
	$(CXX) $(CXXFLAGS) $(HEADERS) 223/LightStudy.C
	gcc -o StudyLightJets_PE100_223 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_223:
	$(CXX) $(CXXFLAGS) $(HEADERS) 223/LightStudy.C
	gcc -o StudyLightJets_PE100_223_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_224:
	$(CXX) $(CXXFLAGS) $(HEADERS) 224/LightStudy.C
	gcc -o StudyLightJets_PE100_224 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_224:
	$(CXX) $(CXXFLAGS) $(HEADERS) 224/LightStudy.C
	gcc -o StudyLightJets_PE100_224_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_225:
	$(CXX) $(CXXFLAGS) $(HEADERS) 225/LightStudy.C
	gcc -o StudyLightJets_PE100_225 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_225:
	$(CXX) $(CXXFLAGS) $(HEADERS) 225/LightStudy.C
	gcc -o StudyLightJets_PE100_225_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_226:
	$(CXX) $(CXXFLAGS) $(HEADERS) 226/LightStudy.C
	gcc -o StudyLightJets_PE100_226 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_226:
	$(CXX) $(CXXFLAGS) $(HEADERS) 226/LightStudy.C
	gcc -o StudyLightJets_PE100_226_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_227:
	$(CXX) $(CXXFLAGS) $(HEADERS) 227/LightStudy.C
	gcc -o StudyLightJets_PE100_227 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_227:
	$(CXX) $(CXXFLAGS) $(HEADERS) 227/LightStudy.C
	gcc -o StudyLightJets_PE100_227_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_228:
	$(CXX) $(CXXFLAGS) $(HEADERS) 228/LightStudy.C
	gcc -o StudyLightJets_PE100_228 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_228:
	$(CXX) $(CXXFLAGS) $(HEADERS) 228/LightStudy.C
	gcc -o StudyLightJets_PE100_228_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_229:
	$(CXX) $(CXXFLAGS) $(HEADERS) 229/LightStudy.C
	gcc -o StudyLightJets_PE100_229 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_229:
	$(CXX) $(CXXFLAGS) $(HEADERS) 229/LightStudy.C
	gcc -o StudyLightJets_PE100_229_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_230:
	$(CXX) $(CXXFLAGS) $(HEADERS) 230/LightStudy.C
	gcc -o StudyLightJets_PE100_230 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_230:
	$(CXX) $(CXXFLAGS) $(HEADERS) 230/LightStudy.C
	gcc -o StudyLightJets_PE100_230_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_231:
	$(CXX) $(CXXFLAGS) $(HEADERS) 231/LightStudy.C
	gcc -o StudyLightJets_PE100_231 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_231:
	$(CXX) $(CXXFLAGS) $(HEADERS) 231/LightStudy.C
	gcc -o StudyLightJets_PE100_231_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_232:
	$(CXX) $(CXXFLAGS) $(HEADERS) 232/LightStudy.C
	gcc -o StudyLightJets_PE100_232 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_232:
	$(CXX) $(CXXFLAGS) $(HEADERS) 232/LightStudy.C
	gcc -o StudyLightJets_PE100_232_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_233:
	$(CXX) $(CXXFLAGS) $(HEADERS) 233/LightStudy.C
	gcc -o StudyLightJets_PE100_233 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_233:
	$(CXX) $(CXXFLAGS) $(HEADERS) 233/LightStudy.C
	gcc -o StudyLightJets_PE100_233_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_234:
	$(CXX) $(CXXFLAGS) $(HEADERS) 234/LightStudy.C
	gcc -o StudyLightJets_PE100_234 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_234:
	$(CXX) $(CXXFLAGS) $(HEADERS) 234/LightStudy.C
	gcc -o StudyLightJets_PE100_234_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_235:
	$(CXX) $(CXXFLAGS) $(HEADERS) 235/LightStudy.C
	gcc -o StudyLightJets_PE100_235 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_235:
	$(CXX) $(CXXFLAGS) $(HEADERS) 235/LightStudy.C
	gcc -o StudyLightJets_PE100_235_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_236:
	$(CXX) $(CXXFLAGS) $(HEADERS) 236/LightStudy.C
	gcc -o StudyLightJets_PE100_236 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_236:
	$(CXX) $(CXXFLAGS) $(HEADERS) 236/LightStudy.C
	gcc -o StudyLightJets_PE100_236_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_237:
	$(CXX) $(CXXFLAGS) $(HEADERS) 237/LightStudy.C
	gcc -o StudyLightJets_PE100_237 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_237:
	$(CXX) $(CXXFLAGS) $(HEADERS) 237/LightStudy.C
	gcc -o StudyLightJets_PE100_237_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_238:
	$(CXX) $(CXXFLAGS) $(HEADERS) 238/LightStudy.C
	gcc -o StudyLightJets_PE100_238 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_238:
	$(CXX) $(CXXFLAGS) $(HEADERS) 238/LightStudy.C
	gcc -o StudyLightJets_PE100_238_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_239:
	$(CXX) $(CXXFLAGS) $(HEADERS) 239/LightStudy.C
	gcc -o StudyLightJets_PE100_239 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_239:
	$(CXX) $(CXXFLAGS) $(HEADERS) 239/LightStudy.C
	gcc -o StudyLightJets_PE100_239_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_240:
	$(CXX) $(CXXFLAGS) $(HEADERS) 240/LightStudy.C
	gcc -o StudyLightJets_PE100_240 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_240:
	$(CXX) $(CXXFLAGS) $(HEADERS) 240/LightStudy.C
	gcc -o StudyLightJets_PE100_240_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_241:
	$(CXX) $(CXXFLAGS) $(HEADERS) 241/LightStudy.C
	gcc -o StudyLightJets_PE100_241 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_241:
	$(CXX) $(CXXFLAGS) $(HEADERS) 241/LightStudy.C
	gcc -o StudyLightJets_PE100_241_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_242:
	$(CXX) $(CXXFLAGS) $(HEADERS) 242/LightStudy.C
	gcc -o StudyLightJets_PE100_242 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_242:
	$(CXX) $(CXXFLAGS) $(HEADERS) 242/LightStudy.C
	gcc -o StudyLightJets_PE100_242_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_243:
	$(CXX) $(CXXFLAGS) $(HEADERS) 243/LightStudy.C
	gcc -o StudyLightJets_PE100_243 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_243:
	$(CXX) $(CXXFLAGS) $(HEADERS) 243/LightStudy.C
	gcc -o StudyLightJets_PE100_243_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_244:
	$(CXX) $(CXXFLAGS) $(HEADERS) 244/LightStudy.C
	gcc -o StudyLightJets_PE100_244 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_244:
	$(CXX) $(CXXFLAGS) $(HEADERS) 244/LightStudy.C
	gcc -o StudyLightJets_PE100_244_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_245:
	$(CXX) $(CXXFLAGS) $(HEADERS) 245/LightStudy.C
	gcc -o StudyLightJets_PE100_245 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_245:
	$(CXX) $(CXXFLAGS) $(HEADERS) 245/LightStudy.C
	gcc -o StudyLightJets_PE100_245_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_246:
	$(CXX) $(CXXFLAGS) $(HEADERS) 246/LightStudy.C
	gcc -o StudyLightJets_PE100_246 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_246:
	$(CXX) $(CXXFLAGS) $(HEADERS) 246/LightStudy.C
	gcc -o StudyLightJets_PE100_246_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_247:
	$(CXX) $(CXXFLAGS) $(HEADERS) 247/LightStudy.C
	gcc -o StudyLightJets_PE100_247 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_247:
	$(CXX) $(CXXFLAGS) $(HEADERS) 247/LightStudy.C
	gcc -o StudyLightJets_PE100_247_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_248:
	$(CXX) $(CXXFLAGS) $(HEADERS) 248/LightStudy.C
	gcc -o StudyLightJets_PE100_248 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_248:
	$(CXX) $(CXXFLAGS) $(HEADERS) 248/LightStudy.C
	gcc -o StudyLightJets_PE100_248_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_249:
	$(CXX) $(CXXFLAGS) $(HEADERS) 249/LightStudy.C
	gcc -o StudyLightJets_PE100_249 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_249:
	$(CXX) $(CXXFLAGS) $(HEADERS) 249/LightStudy.C
	gcc -o StudyLightJets_PE100_249_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_250:
	$(CXX) $(CXXFLAGS) $(HEADERS) 250/LightStudy.C
	gcc -o StudyLightJets_PE100_250 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_250:
	$(CXX) $(CXXFLAGS) $(HEADERS) 250/LightStudy.C
	gcc -o StudyLightJets_PE100_250_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_251:
	$(CXX) $(CXXFLAGS) $(HEADERS) 251/LightStudy.C
	gcc -o StudyLightJets_PE100_251 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_251:
	$(CXX) $(CXXFLAGS) $(HEADERS) 251/LightStudy.C
	gcc -o StudyLightJets_PE100_251_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_252:
	$(CXX) $(CXXFLAGS) $(HEADERS) 252/LightStudy.C
	gcc -o StudyLightJets_PE100_252 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_252:
	$(CXX) $(CXXFLAGS) $(HEADERS) 252/LightStudy.C
	gcc -o StudyLightJets_PE100_252_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_253:
	$(CXX) $(CXXFLAGS) $(HEADERS) 253/LightStudy.C
	gcc -o StudyLightJets_PE100_253 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_253:
	$(CXX) $(CXXFLAGS) $(HEADERS) 253/LightStudy.C
	gcc -o StudyLightJets_PE100_253_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_254:
	$(CXX) $(CXXFLAGS) $(HEADERS) 254/LightStudy.C
	gcc -o StudyLightJets_PE100_254 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_254:
	$(CXX) $(CXXFLAGS) $(HEADERS) 254/LightStudy.C
	gcc -o StudyLightJets_PE100_254_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_255:
	$(CXX) $(CXXFLAGS) $(HEADERS) 255/LightStudy.C
	gcc -o StudyLightJets_PE100_255 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_255:
	$(CXX) $(CXXFLAGS) $(HEADERS) 255/LightStudy.C
	gcc -o StudyLightJets_PE100_255_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_256:
	$(CXX) $(CXXFLAGS) $(HEADERS) 256/LightStudy.C
	gcc -o StudyLightJets_PE100_256 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_256:
	$(CXX) $(CXXFLAGS) $(HEADERS) 256/LightStudy.C
	gcc -o StudyLightJets_PE100_256_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_257:
	$(CXX) $(CXXFLAGS) $(HEADERS) 257/LightStudy.C
	gcc -o StudyLightJets_PE100_257 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_257:
	$(CXX) $(CXXFLAGS) $(HEADERS) 257/LightStudy.C
	gcc -o StudyLightJets_PE100_257_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_258:
	$(CXX) $(CXXFLAGS) $(HEADERS) 258/LightStudy.C
	gcc -o StudyLightJets_PE100_258 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_258:
	$(CXX) $(CXXFLAGS) $(HEADERS) 258/LightStudy.C
	gcc -o StudyLightJets_PE100_258_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_259:
	$(CXX) $(CXXFLAGS) $(HEADERS) 259/LightStudy.C
	gcc -o StudyLightJets_PE100_259 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_259:
	$(CXX) $(CXXFLAGS) $(HEADERS) 259/LightStudy.C
	gcc -o StudyLightJets_PE100_259_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_260:
	$(CXX) $(CXXFLAGS) $(HEADERS) 260/LightStudy.C
	gcc -o StudyLightJets_PE100_260 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_260:
	$(CXX) $(CXXFLAGS) $(HEADERS) 260/LightStudy.C
	gcc -o StudyLightJets_PE100_260_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_261:
	$(CXX) $(CXXFLAGS) $(HEADERS) 261/LightStudy.C
	gcc -o StudyLightJets_PE100_261 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_261:
	$(CXX) $(CXXFLAGS) $(HEADERS) 261/LightStudy.C
	gcc -o StudyLightJets_PE100_261_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_262:
	$(CXX) $(CXXFLAGS) $(HEADERS) 262/LightStudy.C
	gcc -o StudyLightJets_PE100_262 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_262:
	$(CXX) $(CXXFLAGS) $(HEADERS) 262/LightStudy.C
	gcc -o StudyLightJets_PE100_262_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_263:
	$(CXX) $(CXXFLAGS) $(HEADERS) 263/LightStudy.C
	gcc -o StudyLightJets_PE100_263 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_263:
	$(CXX) $(CXXFLAGS) $(HEADERS) 263/LightStudy.C
	gcc -o StudyLightJets_PE100_263_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_264:
	$(CXX) $(CXXFLAGS) $(HEADERS) 264/LightStudy.C
	gcc -o StudyLightJets_PE100_264 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_264:
	$(CXX) $(CXXFLAGS) $(HEADERS) 264/LightStudy.C
	gcc -o StudyLightJets_PE100_264_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_265:
	$(CXX) $(CXXFLAGS) $(HEADERS) 265/LightStudy.C
	gcc -o StudyLightJets_PE100_265 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_265:
	$(CXX) $(CXXFLAGS) $(HEADERS) 265/LightStudy.C
	gcc -o StudyLightJets_PE100_265_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_266:
	$(CXX) $(CXXFLAGS) $(HEADERS) 266/LightStudy.C
	gcc -o StudyLightJets_PE100_266 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_266:
	$(CXX) $(CXXFLAGS) $(HEADERS) 266/LightStudy.C
	gcc -o StudyLightJets_PE100_266_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_267:
	$(CXX) $(CXXFLAGS) $(HEADERS) 267/LightStudy.C
	gcc -o StudyLightJets_PE100_267 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_267:
	$(CXX) $(CXXFLAGS) $(HEADERS) 267/LightStudy.C
	gcc -o StudyLightJets_PE100_267_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_268:
	$(CXX) $(CXXFLAGS) $(HEADERS) 268/LightStudy.C
	gcc -o StudyLightJets_PE100_268 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_268:
	$(CXX) $(CXXFLAGS) $(HEADERS) 268/LightStudy.C
	gcc -o StudyLightJets_PE100_268_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_269:
	$(CXX) $(CXXFLAGS) $(HEADERS) 269/LightStudy.C
	gcc -o StudyLightJets_PE100_269 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_269:
	$(CXX) $(CXXFLAGS) $(HEADERS) 269/LightStudy.C
	gcc -o StudyLightJets_PE100_269_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_270:
	$(CXX) $(CXXFLAGS) $(HEADERS) 270/LightStudy.C
	gcc -o StudyLightJets_PE100_270 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_270:
	$(CXX) $(CXXFLAGS) $(HEADERS) 270/LightStudy.C
	gcc -o StudyLightJets_PE100_270_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_271:
	$(CXX) $(CXXFLAGS) $(HEADERS) 271/LightStudy.C
	gcc -o StudyLightJets_PE100_271 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_271:
	$(CXX) $(CXXFLAGS) $(HEADERS) 271/LightStudy.C
	gcc -o StudyLightJets_PE100_271_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_272:
	$(CXX) $(CXXFLAGS) $(HEADERS) 272/LightStudy.C
	gcc -o StudyLightJets_PE100_272 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_272:
	$(CXX) $(CXXFLAGS) $(HEADERS) 272/LightStudy.C
	gcc -o StudyLightJets_PE100_272_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_273:
	$(CXX) $(CXXFLAGS) $(HEADERS) 273/LightStudy.C
	gcc -o StudyLightJets_PE100_273 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_273:
	$(CXX) $(CXXFLAGS) $(HEADERS) 273/LightStudy.C
	gcc -o StudyLightJets_PE100_273_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_274:
	$(CXX) $(CXXFLAGS) $(HEADERS) 274/LightStudy.C
	gcc -o StudyLightJets_PE100_274 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_274:
	$(CXX) $(CXXFLAGS) $(HEADERS) 274/LightStudy.C
	gcc -o StudyLightJets_PE100_274_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_275:
	$(CXX) $(CXXFLAGS) $(HEADERS) 275/LightStudy.C
	gcc -o StudyLightJets_PE100_275 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_275:
	$(CXX) $(CXXFLAGS) $(HEADERS) 275/LightStudy.C
	gcc -o StudyLightJets_PE100_275_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_276:
	$(CXX) $(CXXFLAGS) $(HEADERS) 276/LightStudy.C
	gcc -o StudyLightJets_PE100_276 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_276:
	$(CXX) $(CXXFLAGS) $(HEADERS) 276/LightStudy.C
	gcc -o StudyLightJets_PE100_276_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_277:
	$(CXX) $(CXXFLAGS) $(HEADERS) 277/LightStudy.C
	gcc -o StudyLightJets_PE100_277 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_277:
	$(CXX) $(CXXFLAGS) $(HEADERS) 277/LightStudy.C
	gcc -o StudyLightJets_PE100_277_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_278:
	$(CXX) $(CXXFLAGS) $(HEADERS) 278/LightStudy.C
	gcc -o StudyLightJets_PE100_278 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_278:
	$(CXX) $(CXXFLAGS) $(HEADERS) 278/LightStudy.C
	gcc -o StudyLightJets_PE100_278_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_279:
	$(CXX) $(CXXFLAGS) $(HEADERS) 279/LightStudy.C
	gcc -o StudyLightJets_PE100_279 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_279:
	$(CXX) $(CXXFLAGS) $(HEADERS) 279/LightStudy.C
	gcc -o StudyLightJets_PE100_279_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_280:
	$(CXX) $(CXXFLAGS) $(HEADERS) 280/LightStudy.C
	gcc -o StudyLightJets_PE100_280 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_280:
	$(CXX) $(CXXFLAGS) $(HEADERS) 280/LightStudy.C
	gcc -o StudyLightJets_PE100_280_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_281:
	$(CXX) $(CXXFLAGS) $(HEADERS) 281/LightStudy.C
	gcc -o StudyLightJets_PE100_281 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_281:
	$(CXX) $(CXXFLAGS) $(HEADERS) 281/LightStudy.C
	gcc -o StudyLightJets_PE100_281_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_282:
	$(CXX) $(CXXFLAGS) $(HEADERS) 282/LightStudy.C
	gcc -o StudyLightJets_PE100_282 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_282:
	$(CXX) $(CXXFLAGS) $(HEADERS) 282/LightStudy.C
	gcc -o StudyLightJets_PE100_282_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_283:
	$(CXX) $(CXXFLAGS) $(HEADERS) 283/LightStudy.C
	gcc -o StudyLightJets_PE100_283 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_283:
	$(CXX) $(CXXFLAGS) $(HEADERS) 283/LightStudy.C
	gcc -o StudyLightJets_PE100_283_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_284:
	$(CXX) $(CXXFLAGS) $(HEADERS) 284/LightStudy.C
	gcc -o StudyLightJets_PE100_284 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_284:
	$(CXX) $(CXXFLAGS) $(HEADERS) 284/LightStudy.C
	gcc -o StudyLightJets_PE100_284_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_285:
	$(CXX) $(CXXFLAGS) $(HEADERS) 285/LightStudy.C
	gcc -o StudyLightJets_PE100_285 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_285:
	$(CXX) $(CXXFLAGS) $(HEADERS) 285/LightStudy.C
	gcc -o StudyLightJets_PE100_285_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_286:
	$(CXX) $(CXXFLAGS) $(HEADERS) 286/LightStudy.C
	gcc -o StudyLightJets_PE100_286 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_286:
	$(CXX) $(CXXFLAGS) $(HEADERS) 286/LightStudy.C
	gcc -o StudyLightJets_PE100_286_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_287:
	$(CXX) $(CXXFLAGS) $(HEADERS) 287/LightStudy.C
	gcc -o StudyLightJets_PE100_287 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_287:
	$(CXX) $(CXXFLAGS) $(HEADERS) 287/LightStudy.C
	gcc -o StudyLightJets_PE100_287_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_288:
	$(CXX) $(CXXFLAGS) $(HEADERS) 288/LightStudy.C
	gcc -o StudyLightJets_PE100_288 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_288:
	$(CXX) $(CXXFLAGS) $(HEADERS) 288/LightStudy.C
	gcc -o StudyLightJets_PE100_288_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_289:
	$(CXX) $(CXXFLAGS) $(HEADERS) 289/LightStudy.C
	gcc -o StudyLightJets_PE100_289 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_289:
	$(CXX) $(CXXFLAGS) $(HEADERS) 289/LightStudy.C
	gcc -o StudyLightJets_PE100_289_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_290:
	$(CXX) $(CXXFLAGS) $(HEADERS) 290/LightStudy.C
	gcc -o StudyLightJets_PE100_290 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_290:
	$(CXX) $(CXXFLAGS) $(HEADERS) 290/LightStudy.C
	gcc -o StudyLightJets_PE100_290_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_291:
	$(CXX) $(CXXFLAGS) $(HEADERS) 291/LightStudy.C
	gcc -o StudyLightJets_PE100_291 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_291:
	$(CXX) $(CXXFLAGS) $(HEADERS) 291/LightStudy.C
	gcc -o StudyLightJets_PE100_291_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_292:
	$(CXX) $(CXXFLAGS) $(HEADERS) 292/LightStudy.C
	gcc -o StudyLightJets_PE100_292 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_292:
	$(CXX) $(CXXFLAGS) $(HEADERS) 292/LightStudy.C
	gcc -o StudyLightJets_PE100_292_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_293:
	$(CXX) $(CXXFLAGS) $(HEADERS) 293/LightStudy.C
	gcc -o StudyLightJets_PE100_293 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_293:
	$(CXX) $(CXXFLAGS) $(HEADERS) 293/LightStudy.C
	gcc -o StudyLightJets_PE100_293_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_294:
	$(CXX) $(CXXFLAGS) $(HEADERS) 294/LightStudy.C
	gcc -o StudyLightJets_PE100_294 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_294:
	$(CXX) $(CXXFLAGS) $(HEADERS) 294/LightStudy.C
	gcc -o StudyLightJets_PE100_294_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_295:
	$(CXX) $(CXXFLAGS) $(HEADERS) 295/LightStudy.C
	gcc -o StudyLightJets_PE100_295 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_295:
	$(CXX) $(CXXFLAGS) $(HEADERS) 295/LightStudy.C
	gcc -o StudyLightJets_PE100_295_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_296:
	$(CXX) $(CXXFLAGS) $(HEADERS) 296/LightStudy.C
	gcc -o StudyLightJets_PE100_296 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_296:
	$(CXX) $(CXXFLAGS) $(HEADERS) 296/LightStudy.C
	gcc -o StudyLightJets_PE100_296_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_297:
	$(CXX) $(CXXFLAGS) $(HEADERS) 297/LightStudy.C
	gcc -o StudyLightJets_PE100_297 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_297:
	$(CXX) $(CXXFLAGS) $(HEADERS) 297/LightStudy.C
	gcc -o StudyLightJets_PE100_297_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_298:
	$(CXX) $(CXXFLAGS) $(HEADERS) 298/LightStudy.C
	gcc -o StudyLightJets_PE100_298 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_298:
	$(CXX) $(CXXFLAGS) $(HEADERS) 298/LightStudy.C
	gcc -o StudyLightJets_PE100_298_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_299:
	$(CXX) $(CXXFLAGS) $(HEADERS) 299/LightStudy.C
	gcc -o StudyLightJets_PE100_299 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_299:
	$(CXX) $(CXXFLAGS) $(HEADERS) 299/LightStudy.C
	gcc -o StudyLightJets_PE100_299_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_300:
	$(CXX) $(CXXFLAGS) $(HEADERS) 300/LightStudy.C
	gcc -o StudyLightJets_PE100_300 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_300:
	$(CXX) $(CXXFLAGS) $(HEADERS) 300/LightStudy.C
	gcc -o StudyLightJets_PE100_300_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_301:
	$(CXX) $(CXXFLAGS) $(HEADERS) 301/LightStudy.C
	gcc -o StudyLightJets_PE100_301 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_301:
	$(CXX) $(CXXFLAGS) $(HEADERS) 301/LightStudy.C
	gcc -o StudyLightJets_PE100_301_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_302:
	$(CXX) $(CXXFLAGS) $(HEADERS) 302/LightStudy.C
	gcc -o StudyLightJets_PE100_302 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_302:
	$(CXX) $(CXXFLAGS) $(HEADERS) 302/LightStudy.C
	gcc -o StudyLightJets_PE100_302_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_303:
	$(CXX) $(CXXFLAGS) $(HEADERS) 303/LightStudy.C
	gcc -o StudyLightJets_PE100_303 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_303:
	$(CXX) $(CXXFLAGS) $(HEADERS) 303/LightStudy.C
	gcc -o StudyLightJets_PE100_303_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_304:
	$(CXX) $(CXXFLAGS) $(HEADERS) 304/LightStudy.C
	gcc -o StudyLightJets_PE100_304 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_304:
	$(CXX) $(CXXFLAGS) $(HEADERS) 304/LightStudy.C
	gcc -o StudyLightJets_PE100_304_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_305:
	$(CXX) $(CXXFLAGS) $(HEADERS) 305/LightStudy.C
	gcc -o StudyLightJets_PE100_305 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_305:
	$(CXX) $(CXXFLAGS) $(HEADERS) 305/LightStudy.C
	gcc -o StudyLightJets_PE100_305_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_306:
	$(CXX) $(CXXFLAGS) $(HEADERS) 306/LightStudy.C
	gcc -o StudyLightJets_PE100_306 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_306:
	$(CXX) $(CXXFLAGS) $(HEADERS) 306/LightStudy.C
	gcc -o StudyLightJets_PE100_306_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_307:
	$(CXX) $(CXXFLAGS) $(HEADERS) 307/LightStudy.C
	gcc -o StudyLightJets_PE100_307 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_307:
	$(CXX) $(CXXFLAGS) $(HEADERS) 307/LightStudy.C
	gcc -o StudyLightJets_PE100_307_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_308:
	$(CXX) $(CXXFLAGS) $(HEADERS) 308/LightStudy.C
	gcc -o StudyLightJets_PE100_308 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_308:
	$(CXX) $(CXXFLAGS) $(HEADERS) 308/LightStudy.C
	gcc -o StudyLightJets_PE100_308_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_309:
	$(CXX) $(CXXFLAGS) $(HEADERS) 309/LightStudy.C
	gcc -o StudyLightJets_PE100_309 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_309:
	$(CXX) $(CXXFLAGS) $(HEADERS) 309/LightStudy.C
	gcc -o StudyLightJets_PE100_309_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_310:
	$(CXX) $(CXXFLAGS) $(HEADERS) 310/LightStudy.C
	gcc -o StudyLightJets_PE100_310 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_310:
	$(CXX) $(CXXFLAGS) $(HEADERS) 310/LightStudy.C
	gcc -o StudyLightJets_PE100_310_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_311:
	$(CXX) $(CXXFLAGS) $(HEADERS) 311/LightStudy.C
	gcc -o StudyLightJets_PE100_311 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_311:
	$(CXX) $(CXXFLAGS) $(HEADERS) 311/LightStudy.C
	gcc -o StudyLightJets_PE100_311_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_312:
	$(CXX) $(CXXFLAGS) $(HEADERS) 312/LightStudy.C
	gcc -o StudyLightJets_PE100_312 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_312:
	$(CXX) $(CXXFLAGS) $(HEADERS) 312/LightStudy.C
	gcc -o StudyLightJets_PE100_312_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_313:
	$(CXX) $(CXXFLAGS) $(HEADERS) 313/LightStudy.C
	gcc -o StudyLightJets_PE100_313 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_313:
	$(CXX) $(CXXFLAGS) $(HEADERS) 313/LightStudy.C
	gcc -o StudyLightJets_PE100_313_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_314:
	$(CXX) $(CXXFLAGS) $(HEADERS) 314/LightStudy.C
	gcc -o StudyLightJets_PE100_314 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_314:
	$(CXX) $(CXXFLAGS) $(HEADERS) 314/LightStudy.C
	gcc -o StudyLightJets_PE100_314_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_315:
	$(CXX) $(CXXFLAGS) $(HEADERS) 315/LightStudy.C
	gcc -o StudyLightJets_PE100_315 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_315:
	$(CXX) $(CXXFLAGS) $(HEADERS) 315/LightStudy.C
	gcc -o StudyLightJets_PE100_315_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_316:
	$(CXX) $(CXXFLAGS) $(HEADERS) 316/LightStudy.C
	gcc -o StudyLightJets_PE100_316 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_316:
	$(CXX) $(CXXFLAGS) $(HEADERS) 316/LightStudy.C
	gcc -o StudyLightJets_PE100_316_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_317:
	$(CXX) $(CXXFLAGS) $(HEADERS) 317/LightStudy.C
	gcc -o StudyLightJets_PE100_317 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_317:
	$(CXX) $(CXXFLAGS) $(HEADERS) 317/LightStudy.C
	gcc -o StudyLightJets_PE100_317_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_318:
	$(CXX) $(CXXFLAGS) $(HEADERS) 318/LightStudy.C
	gcc -o StudyLightJets_PE100_318 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_318:
	$(CXX) $(CXXFLAGS) $(HEADERS) 318/LightStudy.C
	gcc -o StudyLightJets_PE100_318_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_319:
	$(CXX) $(CXXFLAGS) $(HEADERS) 319/LightStudy.C
	gcc -o StudyLightJets_PE100_319 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_319:
	$(CXX) $(CXXFLAGS) $(HEADERS) 319/LightStudy.C
	gcc -o StudyLightJets_PE100_319_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_320:
	$(CXX) $(CXXFLAGS) $(HEADERS) 320/LightStudy.C
	gcc -o StudyLightJets_PE100_320 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_320:
	$(CXX) $(CXXFLAGS) $(HEADERS) 320/LightStudy.C
	gcc -o StudyLightJets_PE100_320_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_321:
	$(CXX) $(CXXFLAGS) $(HEADERS) 321/LightStudy.C
	gcc -o StudyLightJets_PE100_321 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_321:
	$(CXX) $(CXXFLAGS) $(HEADERS) 321/LightStudy.C
	gcc -o StudyLightJets_PE100_321_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_322:
	$(CXX) $(CXXFLAGS) $(HEADERS) 322/LightStudy.C
	gcc -o StudyLightJets_PE100_322 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_322:
	$(CXX) $(CXXFLAGS) $(HEADERS) 322/LightStudy.C
	gcc -o StudyLightJets_PE100_322_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_323:
	$(CXX) $(CXXFLAGS) $(HEADERS) 323/LightStudy.C
	gcc -o StudyLightJets_PE100_323 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_323:
	$(CXX) $(CXXFLAGS) $(HEADERS) 323/LightStudy.C
	gcc -o StudyLightJets_PE100_323_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_324:
	$(CXX) $(CXXFLAGS) $(HEADERS) 324/LightStudy.C
	gcc -o StudyLightJets_PE100_324 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_324:
	$(CXX) $(CXXFLAGS) $(HEADERS) 324/LightStudy.C
	gcc -o StudyLightJets_PE100_324_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_325:
	$(CXX) $(CXXFLAGS) $(HEADERS) 325/LightStudy.C
	gcc -o StudyLightJets_PE100_325 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_325:
	$(CXX) $(CXXFLAGS) $(HEADERS) 325/LightStudy.C
	gcc -o StudyLightJets_PE100_325_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_326:
	$(CXX) $(CXXFLAGS) $(HEADERS) 326/LightStudy.C
	gcc -o StudyLightJets_PE100_326 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_326:
	$(CXX) $(CXXFLAGS) $(HEADERS) 326/LightStudy.C
	gcc -o StudyLightJets_PE100_326_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_327:
	$(CXX) $(CXXFLAGS) $(HEADERS) 327/LightStudy.C
	gcc -o StudyLightJets_PE100_327 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_327:
	$(CXX) $(CXXFLAGS) $(HEADERS) 327/LightStudy.C
	gcc -o StudyLightJets_PE100_327_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_328:
	$(CXX) $(CXXFLAGS) $(HEADERS) 328/LightStudy.C
	gcc -o StudyLightJets_PE100_328 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_328:
	$(CXX) $(CXXFLAGS) $(HEADERS) 328/LightStudy.C
	gcc -o StudyLightJets_PE100_328_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_329:
	$(CXX) $(CXXFLAGS) $(HEADERS) 329/LightStudy.C
	gcc -o StudyLightJets_PE100_329 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_329:
	$(CXX) $(CXXFLAGS) $(HEADERS) 329/LightStudy.C
	gcc -o StudyLightJets_PE100_329_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_330:
	$(CXX) $(CXXFLAGS) $(HEADERS) 330/LightStudy.C
	gcc -o StudyLightJets_PE100_330 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_330:
	$(CXX) $(CXXFLAGS) $(HEADERS) 330/LightStudy.C
	gcc -o StudyLightJets_PE100_330_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_331:
	$(CXX) $(CXXFLAGS) $(HEADERS) 331/LightStudy.C
	gcc -o StudyLightJets_PE100_331 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_331:
	$(CXX) $(CXXFLAGS) $(HEADERS) 331/LightStudy.C
	gcc -o StudyLightJets_PE100_331_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_332:
	$(CXX) $(CXXFLAGS) $(HEADERS) 332/LightStudy.C
	gcc -o StudyLightJets_PE100_332 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_332:
	$(CXX) $(CXXFLAGS) $(HEADERS) 332/LightStudy.C
	gcc -o StudyLightJets_PE100_332_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_333:
	$(CXX) $(CXXFLAGS) $(HEADERS) 333/LightStudy.C
	gcc -o StudyLightJets_PE100_333 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_333:
	$(CXX) $(CXXFLAGS) $(HEADERS) 333/LightStudy.C
	gcc -o StudyLightJets_PE100_333_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_334:
	$(CXX) $(CXXFLAGS) $(HEADERS) 334/LightStudy.C
	gcc -o StudyLightJets_PE100_334 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_334:
	$(CXX) $(CXXFLAGS) $(HEADERS) 334/LightStudy.C
	gcc -o StudyLightJets_PE100_334_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_335:
	$(CXX) $(CXXFLAGS) $(HEADERS) 335/LightStudy.C
	gcc -o StudyLightJets_PE100_335 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_335:
	$(CXX) $(CXXFLAGS) $(HEADERS) 335/LightStudy.C
	gcc -o StudyLightJets_PE100_335_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_336:
	$(CXX) $(CXXFLAGS) $(HEADERS) 336/LightStudy.C
	gcc -o StudyLightJets_PE100_336 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_336:
	$(CXX) $(CXXFLAGS) $(HEADERS) 336/LightStudy.C
	gcc -o StudyLightJets_PE100_336_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_337:
	$(CXX) $(CXXFLAGS) $(HEADERS) 337/LightStudy.C
	gcc -o StudyLightJets_PE100_337 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_337:
	$(CXX) $(CXXFLAGS) $(HEADERS) 337/LightStudy.C
	gcc -o StudyLightJets_PE100_337_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_338:
	$(CXX) $(CXXFLAGS) $(HEADERS) 338/LightStudy.C
	gcc -o StudyLightJets_PE100_338 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_338:
	$(CXX) $(CXXFLAGS) $(HEADERS) 338/LightStudy.C
	gcc -o StudyLightJets_PE100_338_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_339:
	$(CXX) $(CXXFLAGS) $(HEADERS) 339/LightStudy.C
	gcc -o StudyLightJets_PE100_339 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_339:
	$(CXX) $(CXXFLAGS) $(HEADERS) 339/LightStudy.C
	gcc -o StudyLightJets_PE100_339_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_340:
	$(CXX) $(CXXFLAGS) $(HEADERS) 340/LightStudy.C
	gcc -o StudyLightJets_PE100_340 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_340:
	$(CXX) $(CXXFLAGS) $(HEADERS) 340/LightStudy.C
	gcc -o StudyLightJets_PE100_340_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_341:
	$(CXX) $(CXXFLAGS) $(HEADERS) 341/LightStudy.C
	gcc -o StudyLightJets_PE100_341 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_341:
	$(CXX) $(CXXFLAGS) $(HEADERS) 341/LightStudy.C
	gcc -o StudyLightJets_PE100_341_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_342:
	$(CXX) $(CXXFLAGS) $(HEADERS) 342/LightStudy.C
	gcc -o StudyLightJets_PE100_342 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_342:
	$(CXX) $(CXXFLAGS) $(HEADERS) 342/LightStudy.C
	gcc -o StudyLightJets_PE100_342_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_343:
	$(CXX) $(CXXFLAGS) $(HEADERS) 343/LightStudy.C
	gcc -o StudyLightJets_PE100_343 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_343:
	$(CXX) $(CXXFLAGS) $(HEADERS) 343/LightStudy.C
	gcc -o StudyLightJets_PE100_343_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_344:
	$(CXX) $(CXXFLAGS) $(HEADERS) 344/LightStudy.C
	gcc -o StudyLightJets_PE100_344 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_344:
	$(CXX) $(CXXFLAGS) $(HEADERS) 344/LightStudy.C
	gcc -o StudyLightJets_PE100_344_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_345:
	$(CXX) $(CXXFLAGS) $(HEADERS) 345/LightStudy.C
	gcc -o StudyLightJets_PE100_345 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_345:
	$(CXX) $(CXXFLAGS) $(HEADERS) 345/LightStudy.C
	gcc -o StudyLightJets_PE100_345_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_346:
	$(CXX) $(CXXFLAGS) $(HEADERS) 346/LightStudy.C
	gcc -o StudyLightJets_PE100_346 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_346:
	$(CXX) $(CXXFLAGS) $(HEADERS) 346/LightStudy.C
	gcc -o StudyLightJets_PE100_346_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_347:
	$(CXX) $(CXXFLAGS) $(HEADERS) 347/LightStudy.C
	gcc -o StudyLightJets_PE100_347 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_347:
	$(CXX) $(CXXFLAGS) $(HEADERS) 347/LightStudy.C
	gcc -o StudyLightJets_PE100_347_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_348:
	$(CXX) $(CXXFLAGS) $(HEADERS) 348/LightStudy.C
	gcc -o StudyLightJets_PE100_348 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_348:
	$(CXX) $(CXXFLAGS) $(HEADERS) 348/LightStudy.C
	gcc -o StudyLightJets_PE100_348_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_349:
	$(CXX) $(CXXFLAGS) $(HEADERS) 349/LightStudy.C
	gcc -o StudyLightJets_PE100_349 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_349:
	$(CXX) $(CXXFLAGS) $(HEADERS) 349/LightStudy.C
	gcc -o StudyLightJets_PE100_349_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_350:
	$(CXX) $(CXXFLAGS) $(HEADERS) 350/LightStudy.C
	gcc -o StudyLightJets_PE100_350 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_350:
	$(CXX) $(CXXFLAGS) $(HEADERS) 350/LightStudy.C
	gcc -o StudyLightJets_PE100_350_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_351:
	$(CXX) $(CXXFLAGS) $(HEADERS) 351/LightStudy.C
	gcc -o StudyLightJets_PE100_351 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_351:
	$(CXX) $(CXXFLAGS) $(HEADERS) 351/LightStudy.C
	gcc -o StudyLightJets_PE100_351_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_352:
	$(CXX) $(CXXFLAGS) $(HEADERS) 352/LightStudy.C
	gcc -o StudyLightJets_PE100_352 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_352:
	$(CXX) $(CXXFLAGS) $(HEADERS) 352/LightStudy.C
	gcc -o StudyLightJets_PE100_352_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_353:
	$(CXX) $(CXXFLAGS) $(HEADERS) 353/LightStudy.C
	gcc -o StudyLightJets_PE100_353 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_353:
	$(CXX) $(CXXFLAGS) $(HEADERS) 353/LightStudy.C
	gcc -o StudyLightJets_PE100_353_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_354:
	$(CXX) $(CXXFLAGS) $(HEADERS) 354/LightStudy.C
	gcc -o StudyLightJets_PE100_354 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_354:
	$(CXX) $(CXXFLAGS) $(HEADERS) 354/LightStudy.C
	gcc -o StudyLightJets_PE100_354_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_355:
	$(CXX) $(CXXFLAGS) $(HEADERS) 355/LightStudy.C
	gcc -o StudyLightJets_PE100_355 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_355:
	$(CXX) $(CXXFLAGS) $(HEADERS) 355/LightStudy.C
	gcc -o StudyLightJets_PE100_355_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_356:
	$(CXX) $(CXXFLAGS) $(HEADERS) 356/LightStudy.C
	gcc -o StudyLightJets_PE100_356 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_356:
	$(CXX) $(CXXFLAGS) $(HEADERS) 356/LightStudy.C
	gcc -o StudyLightJets_PE100_356_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_357:
	$(CXX) $(CXXFLAGS) $(HEADERS) 357/LightStudy.C
	gcc -o StudyLightJets_PE100_357 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_357:
	$(CXX) $(CXXFLAGS) $(HEADERS) 357/LightStudy.C
	gcc -o StudyLightJets_PE100_357_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_358:
	$(CXX) $(CXXFLAGS) $(HEADERS) 358/LightStudy.C
	gcc -o StudyLightJets_PE100_358 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_358:
	$(CXX) $(CXXFLAGS) $(HEADERS) 358/LightStudy.C
	gcc -o StudyLightJets_PE100_358_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_359:
	$(CXX) $(CXXFLAGS) $(HEADERS) 359/LightStudy.C
	gcc -o StudyLightJets_PE100_359 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_359:
	$(CXX) $(CXXFLAGS) $(HEADERS) 359/LightStudy.C
	gcc -o StudyLightJets_PE100_359_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_360:
	$(CXX) $(CXXFLAGS) $(HEADERS) 360/LightStudy.C
	gcc -o StudyLightJets_PE100_360 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_360:
	$(CXX) $(CXXFLAGS) $(HEADERS) 360/LightStudy.C
	gcc -o StudyLightJets_PE100_360_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_361:
	$(CXX) $(CXXFLAGS) $(HEADERS) 361/LightStudy.C
	gcc -o StudyLightJets_PE100_361 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_361:
	$(CXX) $(CXXFLAGS) $(HEADERS) 361/LightStudy.C
	gcc -o StudyLightJets_PE100_361_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_362:
	$(CXX) $(CXXFLAGS) $(HEADERS) 362/LightStudy.C
	gcc -o StudyLightJets_PE100_362 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_362:
	$(CXX) $(CXXFLAGS) $(HEADERS) 362/LightStudy.C
	gcc -o StudyLightJets_PE100_362_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_363:
	$(CXX) $(CXXFLAGS) $(HEADERS) 363/LightStudy.C
	gcc -o StudyLightJets_PE100_363 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_363:
	$(CXX) $(CXXFLAGS) $(HEADERS) 363/LightStudy.C
	gcc -o StudyLightJets_PE100_363_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_364:
	$(CXX) $(CXXFLAGS) $(HEADERS) 364/LightStudy.C
	gcc -o StudyLightJets_PE100_364 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_364:
	$(CXX) $(CXXFLAGS) $(HEADERS) 364/LightStudy.C
	gcc -o StudyLightJets_PE100_364_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_365:
	$(CXX) $(CXXFLAGS) $(HEADERS) 365/LightStudy.C
	gcc -o StudyLightJets_PE100_365 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_365:
	$(CXX) $(CXXFLAGS) $(HEADERS) 365/LightStudy.C
	gcc -o StudyLightJets_PE100_365_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_366:
	$(CXX) $(CXXFLAGS) $(HEADERS) 366/LightStudy.C
	gcc -o StudyLightJets_PE100_366 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_366:
	$(CXX) $(CXXFLAGS) $(HEADERS) 366/LightStudy.C
	gcc -o StudyLightJets_PE100_366_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_367:
	$(CXX) $(CXXFLAGS) $(HEADERS) 367/LightStudy.C
	gcc -o StudyLightJets_PE100_367 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_367:
	$(CXX) $(CXXFLAGS) $(HEADERS) 367/LightStudy.C
	gcc -o StudyLightJets_PE100_367_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_368:
	$(CXX) $(CXXFLAGS) $(HEADERS) 368/LightStudy.C
	gcc -o StudyLightJets_PE100_368 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_368:
	$(CXX) $(CXXFLAGS) $(HEADERS) 368/LightStudy.C
	gcc -o StudyLightJets_PE100_368_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_369:
	$(CXX) $(CXXFLAGS) $(HEADERS) 369/LightStudy.C
	gcc -o StudyLightJets_PE100_369 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_369:
	$(CXX) $(CXXFLAGS) $(HEADERS) 369/LightStudy.C
	gcc -o StudyLightJets_PE100_369_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_370:
	$(CXX) $(CXXFLAGS) $(HEADERS) 370/LightStudy.C
	gcc -o StudyLightJets_PE100_370 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_370:
	$(CXX) $(CXXFLAGS) $(HEADERS) 370/LightStudy.C
	gcc -o StudyLightJets_PE100_370_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_371:
	$(CXX) $(CXXFLAGS) $(HEADERS) 371/LightStudy.C
	gcc -o StudyLightJets_PE100_371 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_371:
	$(CXX) $(CXXFLAGS) $(HEADERS) 371/LightStudy.C
	gcc -o StudyLightJets_PE100_371_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_372:
	$(CXX) $(CXXFLAGS) $(HEADERS) 372/LightStudy.C
	gcc -o StudyLightJets_PE100_372 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_372:
	$(CXX) $(CXXFLAGS) $(HEADERS) 372/LightStudy.C
	gcc -o StudyLightJets_PE100_372_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_373:
	$(CXX) $(CXXFLAGS) $(HEADERS) 373/LightStudy.C
	gcc -o StudyLightJets_PE100_373 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_373:
	$(CXX) $(CXXFLAGS) $(HEADERS) 373/LightStudy.C
	gcc -o StudyLightJets_PE100_373_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_374:
	$(CXX) $(CXXFLAGS) $(HEADERS) 374/LightStudy.C
	gcc -o StudyLightJets_PE100_374 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_374:
	$(CXX) $(CXXFLAGS) $(HEADERS) 374/LightStudy.C
	gcc -o StudyLightJets_PE100_374_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_375:
	$(CXX) $(CXXFLAGS) $(HEADERS) 375/LightStudy.C
	gcc -o StudyLightJets_PE100_375 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_375:
	$(CXX) $(CXXFLAGS) $(HEADERS) 375/LightStudy.C
	gcc -o StudyLightJets_PE100_375_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_376:
	$(CXX) $(CXXFLAGS) $(HEADERS) 376/LightStudy.C
	gcc -o StudyLightJets_PE100_376 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_376:
	$(CXX) $(CXXFLAGS) $(HEADERS) 376/LightStudy.C
	gcc -o StudyLightJets_PE100_376_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_377:
	$(CXX) $(CXXFLAGS) $(HEADERS) 377/LightStudy.C
	gcc -o StudyLightJets_PE100_377 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_377:
	$(CXX) $(CXXFLAGS) $(HEADERS) 377/LightStudy.C
	gcc -o StudyLightJets_PE100_377_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_378:
	$(CXX) $(CXXFLAGS) $(HEADERS) 378/LightStudy.C
	gcc -o StudyLightJets_PE100_378 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_378:
	$(CXX) $(CXXFLAGS) $(HEADERS) 378/LightStudy.C
	gcc -o StudyLightJets_PE100_378_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_379:
	$(CXX) $(CXXFLAGS) $(HEADERS) 379/LightStudy.C
	gcc -o StudyLightJets_PE100_379 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_379:
	$(CXX) $(CXXFLAGS) $(HEADERS) 379/LightStudy.C
	gcc -o StudyLightJets_PE100_379_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_380:
	$(CXX) $(CXXFLAGS) $(HEADERS) 380/LightStudy.C
	gcc -o StudyLightJets_PE100_380 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_380:
	$(CXX) $(CXXFLAGS) $(HEADERS) 380/LightStudy.C
	gcc -o StudyLightJets_PE100_380_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_381:
	$(CXX) $(CXXFLAGS) $(HEADERS) 381/LightStudy.C
	gcc -o StudyLightJets_PE100_381 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_381:
	$(CXX) $(CXXFLAGS) $(HEADERS) 381/LightStudy.C
	gcc -o StudyLightJets_PE100_381_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_382:
	$(CXX) $(CXXFLAGS) $(HEADERS) 382/LightStudy.C
	gcc -o StudyLightJets_PE100_382 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_382:
	$(CXX) $(CXXFLAGS) $(HEADERS) 382/LightStudy.C
	gcc -o StudyLightJets_PE100_382_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_383:
	$(CXX) $(CXXFLAGS) $(HEADERS) 383/LightStudy.C
	gcc -o StudyLightJets_PE100_383 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_383:
	$(CXX) $(CXXFLAGS) $(HEADERS) 383/LightStudy.C
	gcc -o StudyLightJets_PE100_383_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_384:
	$(CXX) $(CXXFLAGS) $(HEADERS) 384/LightStudy.C
	gcc -o StudyLightJets_PE100_384 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_384:
	$(CXX) $(CXXFLAGS) $(HEADERS) 384/LightStudy.C
	gcc -o StudyLightJets_PE100_384_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_385:
	$(CXX) $(CXXFLAGS) $(HEADERS) 385/LightStudy.C
	gcc -o StudyLightJets_PE100_385 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_385:
	$(CXX) $(CXXFLAGS) $(HEADERS) 385/LightStudy.C
	gcc -o StudyLightJets_PE100_385_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_386:
	$(CXX) $(CXXFLAGS) $(HEADERS) 386/LightStudy.C
	gcc -o StudyLightJets_PE100_386 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_386:
	$(CXX) $(CXXFLAGS) $(HEADERS) 386/LightStudy.C
	gcc -o StudyLightJets_PE100_386_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_387:
	$(CXX) $(CXXFLAGS) $(HEADERS) 387/LightStudy.C
	gcc -o StudyLightJets_PE100_387 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_387:
	$(CXX) $(CXXFLAGS) $(HEADERS) 387/LightStudy.C
	gcc -o StudyLightJets_PE100_387_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_388:
	$(CXX) $(CXXFLAGS) $(HEADERS) 388/LightStudy.C
	gcc -o StudyLightJets_PE100_388 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_388:
	$(CXX) $(CXXFLAGS) $(HEADERS) 388/LightStudy.C
	gcc -o StudyLightJets_PE100_388_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_389:
	$(CXX) $(CXXFLAGS) $(HEADERS) 389/LightStudy.C
	gcc -o StudyLightJets_PE100_389 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_389:
	$(CXX) $(CXXFLAGS) $(HEADERS) 389/LightStudy.C
	gcc -o StudyLightJets_PE100_389_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_390:
	$(CXX) $(CXXFLAGS) $(HEADERS) 390/LightStudy.C
	gcc -o StudyLightJets_PE100_390 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_390:
	$(CXX) $(CXXFLAGS) $(HEADERS) 390/LightStudy.C
	gcc -o StudyLightJets_PE100_390_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_391:
	$(CXX) $(CXXFLAGS) $(HEADERS) 391/LightStudy.C
	gcc -o StudyLightJets_PE100_391 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_391:
	$(CXX) $(CXXFLAGS) $(HEADERS) 391/LightStudy.C
	gcc -o StudyLightJets_PE100_391_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_392:
	$(CXX) $(CXXFLAGS) $(HEADERS) 392/LightStudy.C
	gcc -o StudyLightJets_PE100_392 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_392:
	$(CXX) $(CXXFLAGS) $(HEADERS) 392/LightStudy.C
	gcc -o StudyLightJets_PE100_392_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_393:
	$(CXX) $(CXXFLAGS) $(HEADERS) 393/LightStudy.C
	gcc -o StudyLightJets_PE100_393 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_393:
	$(CXX) $(CXXFLAGS) $(HEADERS) 393/LightStudy.C
	gcc -o StudyLightJets_PE100_393_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_394:
	$(CXX) $(CXXFLAGS) $(HEADERS) 394/LightStudy.C
	gcc -o StudyLightJets_PE100_394 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_394:
	$(CXX) $(CXXFLAGS) $(HEADERS) 394/LightStudy.C
	gcc -o StudyLightJets_PE100_394_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_395:
	$(CXX) $(CXXFLAGS) $(HEADERS) 395/LightStudy.C
	gcc -o StudyLightJets_PE100_395 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_395:
	$(CXX) $(CXXFLAGS) $(HEADERS) 395/LightStudy.C
	gcc -o StudyLightJets_PE100_395_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_396:
	$(CXX) $(CXXFLAGS) $(HEADERS) 396/LightStudy.C
	gcc -o StudyLightJets_PE100_396 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_396:
	$(CXX) $(CXXFLAGS) $(HEADERS) 396/LightStudy.C
	gcc -o StudyLightJets_PE100_396_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_397:
	$(CXX) $(CXXFLAGS) $(HEADERS) 397/LightStudy.C
	gcc -o StudyLightJets_PE100_397 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_397:
	$(CXX) $(CXXFLAGS) $(HEADERS) 397/LightStudy.C
	gcc -o StudyLightJets_PE100_397_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_398:
	$(CXX) $(CXXFLAGS) $(HEADERS) 398/LightStudy.C
	gcc -o StudyLightJets_PE100_398 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_398:
	$(CXX) $(CXXFLAGS) $(HEADERS) 398/LightStudy.C
	gcc -o StudyLightJets_PE100_398_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_399:
	$(CXX) $(CXXFLAGS) $(HEADERS) 399/LightStudy.C
	gcc -o StudyLightJets_PE100_399 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_399:
	$(CXX) $(CXXFLAGS) $(HEADERS) 399/LightStudy.C
	gcc -o StudyLightJets_PE100_399_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_400:
	$(CXX) $(CXXFLAGS) $(HEADERS) 400/LightStudy.C
	gcc -o StudyLightJets_PE100_400 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_400:
	$(CXX) $(CXXFLAGS) $(HEADERS) 400/LightStudy.C
	gcc -o StudyLightJets_PE100_400_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_401:
	$(CXX) $(CXXFLAGS) $(HEADERS) 401/LightStudy.C
	gcc -o StudyLightJets_PE100_401 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_401:
	$(CXX) $(CXXFLAGS) $(HEADERS) 401/LightStudy.C
	gcc -o StudyLightJets_PE100_401_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_402:
	$(CXX) $(CXXFLAGS) $(HEADERS) 402/LightStudy.C
	gcc -o StudyLightJets_PE100_402 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_402:
	$(CXX) $(CXXFLAGS) $(HEADERS) 402/LightStudy.C
	gcc -o StudyLightJets_PE100_402_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_403:
	$(CXX) $(CXXFLAGS) $(HEADERS) 403/LightStudy.C
	gcc -o StudyLightJets_PE100_403 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_403:
	$(CXX) $(CXXFLAGS) $(HEADERS) 403/LightStudy.C
	gcc -o StudyLightJets_PE100_403_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_404:
	$(CXX) $(CXXFLAGS) $(HEADERS) 404/LightStudy.C
	gcc -o StudyLightJets_PE100_404 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_404:
	$(CXX) $(CXXFLAGS) $(HEADERS) 404/LightStudy.C
	gcc -o StudyLightJets_PE100_404_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_405:
	$(CXX) $(CXXFLAGS) $(HEADERS) 405/LightStudy.C
	gcc -o StudyLightJets_PE100_405 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_405:
	$(CXX) $(CXXFLAGS) $(HEADERS) 405/LightStudy.C
	gcc -o StudyLightJets_PE100_405_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_406:
	$(CXX) $(CXXFLAGS) $(HEADERS) 406/LightStudy.C
	gcc -o StudyLightJets_PE100_406 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_406:
	$(CXX) $(CXXFLAGS) $(HEADERS) 406/LightStudy.C
	gcc -o StudyLightJets_PE100_406_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_407:
	$(CXX) $(CXXFLAGS) $(HEADERS) 407/LightStudy.C
	gcc -o StudyLightJets_PE100_407 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_407:
	$(CXX) $(CXXFLAGS) $(HEADERS) 407/LightStudy.C
	gcc -o StudyLightJets_PE100_407_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_408:
	$(CXX) $(CXXFLAGS) $(HEADERS) 408/LightStudy.C
	gcc -o StudyLightJets_PE100_408 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_408:
	$(CXX) $(CXXFLAGS) $(HEADERS) 408/LightStudy.C
	gcc -o StudyLightJets_PE100_408_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_409:
	$(CXX) $(CXXFLAGS) $(HEADERS) 409/LightStudy.C
	gcc -o StudyLightJets_PE100_409 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_409:
	$(CXX) $(CXXFLAGS) $(HEADERS) 409/LightStudy.C
	gcc -o StudyLightJets_PE100_409_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_410:
	$(CXX) $(CXXFLAGS) $(HEADERS) 410/LightStudy.C
	gcc -o StudyLightJets_PE100_410 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_410:
	$(CXX) $(CXXFLAGS) $(HEADERS) 410/LightStudy.C
	gcc -o StudyLightJets_PE100_410_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_411:
	$(CXX) $(CXXFLAGS) $(HEADERS) 411/LightStudy.C
	gcc -o StudyLightJets_PE100_411 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_411:
	$(CXX) $(CXXFLAGS) $(HEADERS) 411/LightStudy.C
	gcc -o StudyLightJets_PE100_411_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_412:
	$(CXX) $(CXXFLAGS) $(HEADERS) 412/LightStudy.C
	gcc -o StudyLightJets_PE100_412 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_412:
	$(CXX) $(CXXFLAGS) $(HEADERS) 412/LightStudy.C
	gcc -o StudyLightJets_PE100_412_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_413:
	$(CXX) $(CXXFLAGS) $(HEADERS) 413/LightStudy.C
	gcc -o StudyLightJets_PE100_413 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_413:
	$(CXX) $(CXXFLAGS) $(HEADERS) 413/LightStudy.C
	gcc -o StudyLightJets_PE100_413_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_414:
	$(CXX) $(CXXFLAGS) $(HEADERS) 414/LightStudy.C
	gcc -o StudyLightJets_PE100_414 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_414:
	$(CXX) $(CXXFLAGS) $(HEADERS) 414/LightStudy.C
	gcc -o StudyLightJets_PE100_414_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_415:
	$(CXX) $(CXXFLAGS) $(HEADERS) 415/LightStudy.C
	gcc -o StudyLightJets_PE100_415 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_415:
	$(CXX) $(CXXFLAGS) $(HEADERS) 415/LightStudy.C
	gcc -o StudyLightJets_PE100_415_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_416:
	$(CXX) $(CXXFLAGS) $(HEADERS) 416/LightStudy.C
	gcc -o StudyLightJets_PE100_416 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_416:
	$(CXX) $(CXXFLAGS) $(HEADERS) 416/LightStudy.C
	gcc -o StudyLightJets_PE100_416_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_417:
	$(CXX) $(CXXFLAGS) $(HEADERS) 417/LightStudy.C
	gcc -o StudyLightJets_PE100_417 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_417:
	$(CXX) $(CXXFLAGS) $(HEADERS) 417/LightStudy.C
	gcc -o StudyLightJets_PE100_417_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_418:
	$(CXX) $(CXXFLAGS) $(HEADERS) 418/LightStudy.C
	gcc -o StudyLightJets_PE100_418 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_418:
	$(CXX) $(CXXFLAGS) $(HEADERS) 418/LightStudy.C
	gcc -o StudyLightJets_PE100_418_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_419:
	$(CXX) $(CXXFLAGS) $(HEADERS) 419/LightStudy.C
	gcc -o StudyLightJets_PE100_419 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_419:
	$(CXX) $(CXXFLAGS) $(HEADERS) 419/LightStudy.C
	gcc -o StudyLightJets_PE100_419_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_420:
	$(CXX) $(CXXFLAGS) $(HEADERS) 420/LightStudy.C
	gcc -o StudyLightJets_PE100_420 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_420:
	$(CXX) $(CXXFLAGS) $(HEADERS) 420/LightStudy.C
	gcc -o StudyLightJets_PE100_420_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_421:
	$(CXX) $(CXXFLAGS) $(HEADERS) 421/LightStudy.C
	gcc -o StudyLightJets_PE100_421 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_421:
	$(CXX) $(CXXFLAGS) $(HEADERS) 421/LightStudy.C
	gcc -o StudyLightJets_PE100_421_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_422:
	$(CXX) $(CXXFLAGS) $(HEADERS) 422/LightStudy.C
	gcc -o StudyLightJets_PE100_422 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_422:
	$(CXX) $(CXXFLAGS) $(HEADERS) 422/LightStudy.C
	gcc -o StudyLightJets_PE100_422_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_423:
	$(CXX) $(CXXFLAGS) $(HEADERS) 423/LightStudy.C
	gcc -o StudyLightJets_PE100_423 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_423:
	$(CXX) $(CXXFLAGS) $(HEADERS) 423/LightStudy.C
	gcc -o StudyLightJets_PE100_423_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_424:
	$(CXX) $(CXXFLAGS) $(HEADERS) 424/LightStudy.C
	gcc -o StudyLightJets_PE100_424 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_424:
	$(CXX) $(CXXFLAGS) $(HEADERS) 424/LightStudy.C
	gcc -o StudyLightJets_PE100_424_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_425:
	$(CXX) $(CXXFLAGS) $(HEADERS) 425/LightStudy.C
	gcc -o StudyLightJets_PE100_425 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_425:
	$(CXX) $(CXXFLAGS) $(HEADERS) 425/LightStudy.C
	gcc -o StudyLightJets_PE100_425_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_426:
	$(CXX) $(CXXFLAGS) $(HEADERS) 426/LightStudy.C
	gcc -o StudyLightJets_PE100_426 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_426:
	$(CXX) $(CXXFLAGS) $(HEADERS) 426/LightStudy.C
	gcc -o StudyLightJets_PE100_426_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_427:
	$(CXX) $(CXXFLAGS) $(HEADERS) 427/LightStudy.C
	gcc -o StudyLightJets_PE100_427 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_427:
	$(CXX) $(CXXFLAGS) $(HEADERS) 427/LightStudy.C
	gcc -o StudyLightJets_PE100_427_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_428:
	$(CXX) $(CXXFLAGS) $(HEADERS) 428/LightStudy.C
	gcc -o StudyLightJets_PE100_428 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_428:
	$(CXX) $(CXXFLAGS) $(HEADERS) 428/LightStudy.C
	gcc -o StudyLightJets_PE100_428_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_429:
	$(CXX) $(CXXFLAGS) $(HEADERS) 429/LightStudy.C
	gcc -o StudyLightJets_PE100_429 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_429:
	$(CXX) $(CXXFLAGS) $(HEADERS) 429/LightStudy.C
	gcc -o StudyLightJets_PE100_429_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_430:
	$(CXX) $(CXXFLAGS) $(HEADERS) 430/LightStudy.C
	gcc -o StudyLightJets_PE100_430 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_430:
	$(CXX) $(CXXFLAGS) $(HEADERS) 430/LightStudy.C
	gcc -o StudyLightJets_PE100_430_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_431:
	$(CXX) $(CXXFLAGS) $(HEADERS) 431/LightStudy.C
	gcc -o StudyLightJets_PE100_431 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_431:
	$(CXX) $(CXXFLAGS) $(HEADERS) 431/LightStudy.C
	gcc -o StudyLightJets_PE100_431_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_432:
	$(CXX) $(CXXFLAGS) $(HEADERS) 432/LightStudy.C
	gcc -o StudyLightJets_PE100_432 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_432:
	$(CXX) $(CXXFLAGS) $(HEADERS) 432/LightStudy.C
	gcc -o StudyLightJets_PE100_432_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_433:
	$(CXX) $(CXXFLAGS) $(HEADERS) 433/LightStudy.C
	gcc -o StudyLightJets_PE100_433 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_433:
	$(CXX) $(CXXFLAGS) $(HEADERS) 433/LightStudy.C
	gcc -o StudyLightJets_PE100_433_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_434:
	$(CXX) $(CXXFLAGS) $(HEADERS) 434/LightStudy.C
	gcc -o StudyLightJets_PE100_434 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_434:
	$(CXX) $(CXXFLAGS) $(HEADERS) 434/LightStudy.C
	gcc -o StudyLightJets_PE100_434_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_435:
	$(CXX) $(CXXFLAGS) $(HEADERS) 435/LightStudy.C
	gcc -o StudyLightJets_PE100_435 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_435:
	$(CXX) $(CXXFLAGS) $(HEADERS) 435/LightStudy.C
	gcc -o StudyLightJets_PE100_435_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_436:
	$(CXX) $(CXXFLAGS) $(HEADERS) 436/LightStudy.C
	gcc -o StudyLightJets_PE100_436 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_436:
	$(CXX) $(CXXFLAGS) $(HEADERS) 436/LightStudy.C
	gcc -o StudyLightJets_PE100_436_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_437:
	$(CXX) $(CXXFLAGS) $(HEADERS) 437/LightStudy.C
	gcc -o StudyLightJets_PE100_437 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_437:
	$(CXX) $(CXXFLAGS) $(HEADERS) 437/LightStudy.C
	gcc -o StudyLightJets_PE100_437_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_438:
	$(CXX) $(CXXFLAGS) $(HEADERS) 438/LightStudy.C
	gcc -o StudyLightJets_PE100_438 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_438:
	$(CXX) $(CXXFLAGS) $(HEADERS) 438/LightStudy.C
	gcc -o StudyLightJets_PE100_438_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_439:
	$(CXX) $(CXXFLAGS) $(HEADERS) 439/LightStudy.C
	gcc -o StudyLightJets_PE100_439 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_439:
	$(CXX) $(CXXFLAGS) $(HEADERS) 439/LightStudy.C
	gcc -o StudyLightJets_PE100_439_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_440:
	$(CXX) $(CXXFLAGS) $(HEADERS) 440/LightStudy.C
	gcc -o StudyLightJets_PE100_440 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_440:
	$(CXX) $(CXXFLAGS) $(HEADERS) 440/LightStudy.C
	gcc -o StudyLightJets_PE100_440_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_441:
	$(CXX) $(CXXFLAGS) $(HEADERS) 441/LightStudy.C
	gcc -o StudyLightJets_PE100_441 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_441:
	$(CXX) $(CXXFLAGS) $(HEADERS) 441/LightStudy.C
	gcc -o StudyLightJets_PE100_441_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_442:
	$(CXX) $(CXXFLAGS) $(HEADERS) 442/LightStudy.C
	gcc -o StudyLightJets_PE100_442 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_442:
	$(CXX) $(CXXFLAGS) $(HEADERS) 442/LightStudy.C
	gcc -o StudyLightJets_PE100_442_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_443:
	$(CXX) $(CXXFLAGS) $(HEADERS) 443/LightStudy.C
	gcc -o StudyLightJets_PE100_443 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_443:
	$(CXX) $(CXXFLAGS) $(HEADERS) 443/LightStudy.C
	gcc -o StudyLightJets_PE100_443_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_444:
	$(CXX) $(CXXFLAGS) $(HEADERS) 444/LightStudy.C
	gcc -o StudyLightJets_PE100_444 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_444:
	$(CXX) $(CXXFLAGS) $(HEADERS) 444/LightStudy.C
	gcc -o StudyLightJets_PE100_444_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_445:
	$(CXX) $(CXXFLAGS) $(HEADERS) 445/LightStudy.C
	gcc -o StudyLightJets_PE100_445 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_445:
	$(CXX) $(CXXFLAGS) $(HEADERS) 445/LightStudy.C
	gcc -o StudyLightJets_PE100_445_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_446:
	$(CXX) $(CXXFLAGS) $(HEADERS) 446/LightStudy.C
	gcc -o StudyLightJets_PE100_446 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_446:
	$(CXX) $(CXXFLAGS) $(HEADERS) 446/LightStudy.C
	gcc -o StudyLightJets_PE100_446_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_447:
	$(CXX) $(CXXFLAGS) $(HEADERS) 447/LightStudy.C
	gcc -o StudyLightJets_PE100_447 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_447:
	$(CXX) $(CXXFLAGS) $(HEADERS) 447/LightStudy.C
	gcc -o StudyLightJets_PE100_447_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_448:
	$(CXX) $(CXXFLAGS) $(HEADERS) 448/LightStudy.C
	gcc -o StudyLightJets_PE100_448 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_448:
	$(CXX) $(CXXFLAGS) $(HEADERS) 448/LightStudy.C
	gcc -o StudyLightJets_PE100_448_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_449:
	$(CXX) $(CXXFLAGS) $(HEADERS) 449/LightStudy.C
	gcc -o StudyLightJets_PE100_449 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_449:
	$(CXX) $(CXXFLAGS) $(HEADERS) 449/LightStudy.C
	gcc -o StudyLightJets_PE100_449_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_450:
	$(CXX) $(CXXFLAGS) $(HEADERS) 450/LightStudy.C
	gcc -o StudyLightJets_PE100_450 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_450:
	$(CXX) $(CXXFLAGS) $(HEADERS) 450/LightStudy.C
	gcc -o StudyLightJets_PE100_450_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_451:
	$(CXX) $(CXXFLAGS) $(HEADERS) 451/LightStudy.C
	gcc -o StudyLightJets_PE100_451 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_451:
	$(CXX) $(CXXFLAGS) $(HEADERS) 451/LightStudy.C
	gcc -o StudyLightJets_PE100_451_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_452:
	$(CXX) $(CXXFLAGS) $(HEADERS) 452/LightStudy.C
	gcc -o StudyLightJets_PE100_452 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_452:
	$(CXX) $(CXXFLAGS) $(HEADERS) 452/LightStudy.C
	gcc -o StudyLightJets_PE100_452_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_453:
	$(CXX) $(CXXFLAGS) $(HEADERS) 453/LightStudy.C
	gcc -o StudyLightJets_PE100_453 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_453:
	$(CXX) $(CXXFLAGS) $(HEADERS) 453/LightStudy.C
	gcc -o StudyLightJets_PE100_453_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_454:
	$(CXX) $(CXXFLAGS) $(HEADERS) 454/LightStudy.C
	gcc -o StudyLightJets_PE100_454 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_454:
	$(CXX) $(CXXFLAGS) $(HEADERS) 454/LightStudy.C
	gcc -o StudyLightJets_PE100_454_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_455:
	$(CXX) $(CXXFLAGS) $(HEADERS) 455/LightStudy.C
	gcc -o StudyLightJets_PE100_455 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_455:
	$(CXX) $(CXXFLAGS) $(HEADERS) 455/LightStudy.C
	gcc -o StudyLightJets_PE100_455_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_456:
	$(CXX) $(CXXFLAGS) $(HEADERS) 456/LightStudy.C
	gcc -o StudyLightJets_PE100_456 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_456:
	$(CXX) $(CXXFLAGS) $(HEADERS) 456/LightStudy.C
	gcc -o StudyLightJets_PE100_456_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_457:
	$(CXX) $(CXXFLAGS) $(HEADERS) 457/LightStudy.C
	gcc -o StudyLightJets_PE100_457 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_457:
	$(CXX) $(CXXFLAGS) $(HEADERS) 457/LightStudy.C
	gcc -o StudyLightJets_PE100_457_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_458:
	$(CXX) $(CXXFLAGS) $(HEADERS) 458/LightStudy.C
	gcc -o StudyLightJets_PE100_458 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_458:
	$(CXX) $(CXXFLAGS) $(HEADERS) 458/LightStudy.C
	gcc -o StudyLightJets_PE100_458_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_459:
	$(CXX) $(CXXFLAGS) $(HEADERS) 459/LightStudy.C
	gcc -o StudyLightJets_PE100_459 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_459:
	$(CXX) $(CXXFLAGS) $(HEADERS) 459/LightStudy.C
	gcc -o StudyLightJets_PE100_459_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_460:
	$(CXX) $(CXXFLAGS) $(HEADERS) 460/LightStudy.C
	gcc -o StudyLightJets_PE100_460 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_460:
	$(CXX) $(CXXFLAGS) $(HEADERS) 460/LightStudy.C
	gcc -o StudyLightJets_PE100_460_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_461:
	$(CXX) $(CXXFLAGS) $(HEADERS) 461/LightStudy.C
	gcc -o StudyLightJets_PE100_461 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_461:
	$(CXX) $(CXXFLAGS) $(HEADERS) 461/LightStudy.C
	gcc -o StudyLightJets_PE100_461_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_462:
	$(CXX) $(CXXFLAGS) $(HEADERS) 462/LightStudy.C
	gcc -o StudyLightJets_PE100_462 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_462:
	$(CXX) $(CXXFLAGS) $(HEADERS) 462/LightStudy.C
	gcc -o StudyLightJets_PE100_462_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_463:
	$(CXX) $(CXXFLAGS) $(HEADERS) 463/LightStudy.C
	gcc -o StudyLightJets_PE100_463 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_463:
	$(CXX) $(CXXFLAGS) $(HEADERS) 463/LightStudy.C
	gcc -o StudyLightJets_PE100_463_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_464:
	$(CXX) $(CXXFLAGS) $(HEADERS) 464/LightStudy.C
	gcc -o StudyLightJets_PE100_464 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_464:
	$(CXX) $(CXXFLAGS) $(HEADERS) 464/LightStudy.C
	gcc -o StudyLightJets_PE100_464_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_465:
	$(CXX) $(CXXFLAGS) $(HEADERS) 465/LightStudy.C
	gcc -o StudyLightJets_PE100_465 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_465:
	$(CXX) $(CXXFLAGS) $(HEADERS) 465/LightStudy.C
	gcc -o StudyLightJets_PE100_465_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_466:
	$(CXX) $(CXXFLAGS) $(HEADERS) 466/LightStudy.C
	gcc -o StudyLightJets_PE100_466 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_466:
	$(CXX) $(CXXFLAGS) $(HEADERS) 466/LightStudy.C
	gcc -o StudyLightJets_PE100_466_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_467:
	$(CXX) $(CXXFLAGS) $(HEADERS) 467/LightStudy.C
	gcc -o StudyLightJets_PE100_467 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_467:
	$(CXX) $(CXXFLAGS) $(HEADERS) 467/LightStudy.C
	gcc -o StudyLightJets_PE100_467_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_468:
	$(CXX) $(CXXFLAGS) $(HEADERS) 468/LightStudy.C
	gcc -o StudyLightJets_PE100_468 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_468:
	$(CXX) $(CXXFLAGS) $(HEADERS) 468/LightStudy.C
	gcc -o StudyLightJets_PE100_468_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_469:
	$(CXX) $(CXXFLAGS) $(HEADERS) 469/LightStudy.C
	gcc -o StudyLightJets_PE100_469 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_469:
	$(CXX) $(CXXFLAGS) $(HEADERS) 469/LightStudy.C
	gcc -o StudyLightJets_PE100_469_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_470:
	$(CXX) $(CXXFLAGS) $(HEADERS) 470/LightStudy.C
	gcc -o StudyLightJets_PE100_470 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_470:
	$(CXX) $(CXXFLAGS) $(HEADERS) 470/LightStudy.C
	gcc -o StudyLightJets_PE100_470_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_471:
	$(CXX) $(CXXFLAGS) $(HEADERS) 471/LightStudy.C
	gcc -o StudyLightJets_PE100_471 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_471:
	$(CXX) $(CXXFLAGS) $(HEADERS) 471/LightStudy.C
	gcc -o StudyLightJets_PE100_471_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_472:
	$(CXX) $(CXXFLAGS) $(HEADERS) 472/LightStudy.C
	gcc -o StudyLightJets_PE100_472 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_472:
	$(CXX) $(CXXFLAGS) $(HEADERS) 472/LightStudy.C
	gcc -o StudyLightJets_PE100_472_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_473:
	$(CXX) $(CXXFLAGS) $(HEADERS) 473/LightStudy.C
	gcc -o StudyLightJets_PE100_473 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_473:
	$(CXX) $(CXXFLAGS) $(HEADERS) 473/LightStudy.C
	gcc -o StudyLightJets_PE100_473_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_474:
	$(CXX) $(CXXFLAGS) $(HEADERS) 474/LightStudy.C
	gcc -o StudyLightJets_PE100_474 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_474:
	$(CXX) $(CXXFLAGS) $(HEADERS) 474/LightStudy.C
	gcc -o StudyLightJets_PE100_474_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_475:
	$(CXX) $(CXXFLAGS) $(HEADERS) 475/LightStudy.C
	gcc -o StudyLightJets_PE100_475 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_475:
	$(CXX) $(CXXFLAGS) $(HEADERS) 475/LightStudy.C
	gcc -o StudyLightJets_PE100_475_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_476:
	$(CXX) $(CXXFLAGS) $(HEADERS) 476/LightStudy.C
	gcc -o StudyLightJets_PE100_476 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_476:
	$(CXX) $(CXXFLAGS) $(HEADERS) 476/LightStudy.C
	gcc -o StudyLightJets_PE100_476_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_477:
	$(CXX) $(CXXFLAGS) $(HEADERS) 477/LightStudy.C
	gcc -o StudyLightJets_PE100_477 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_477:
	$(CXX) $(CXXFLAGS) $(HEADERS) 477/LightStudy.C
	gcc -o StudyLightJets_PE100_477_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_478:
	$(CXX) $(CXXFLAGS) $(HEADERS) 478/LightStudy.C
	gcc -o StudyLightJets_PE100_478 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_478:
	$(CXX) $(CXXFLAGS) $(HEADERS) 478/LightStudy.C
	gcc -o StudyLightJets_PE100_478_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_479:
	$(CXX) $(CXXFLAGS) $(HEADERS) 479/LightStudy.C
	gcc -o StudyLightJets_PE100_479 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_479:
	$(CXX) $(CXXFLAGS) $(HEADERS) 479/LightStudy.C
	gcc -o StudyLightJets_PE100_479_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_480:
	$(CXX) $(CXXFLAGS) $(HEADERS) 480/LightStudy.C
	gcc -o StudyLightJets_PE100_480 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_480:
	$(CXX) $(CXXFLAGS) $(HEADERS) 480/LightStudy.C
	gcc -o StudyLightJets_PE100_480_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_481:
	$(CXX) $(CXXFLAGS) $(HEADERS) 481/LightStudy.C
	gcc -o StudyLightJets_PE100_481 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_481:
	$(CXX) $(CXXFLAGS) $(HEADERS) 481/LightStudy.C
	gcc -o StudyLightJets_PE100_481_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_482:
	$(CXX) $(CXXFLAGS) $(HEADERS) 482/LightStudy.C
	gcc -o StudyLightJets_PE100_482 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_482:
	$(CXX) $(CXXFLAGS) $(HEADERS) 482/LightStudy.C
	gcc -o StudyLightJets_PE100_482_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_483:
	$(CXX) $(CXXFLAGS) $(HEADERS) 483/LightStudy.C
	gcc -o StudyLightJets_PE100_483 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_483:
	$(CXX) $(CXXFLAGS) $(HEADERS) 483/LightStudy.C
	gcc -o StudyLightJets_PE100_483_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_484:
	$(CXX) $(CXXFLAGS) $(HEADERS) 484/LightStudy.C
	gcc -o StudyLightJets_PE100_484 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_484:
	$(CXX) $(CXXFLAGS) $(HEADERS) 484/LightStudy.C
	gcc -o StudyLightJets_PE100_484_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_485:
	$(CXX) $(CXXFLAGS) $(HEADERS) 485/LightStudy.C
	gcc -o StudyLightJets_PE100_485 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_485:
	$(CXX) $(CXXFLAGS) $(HEADERS) 485/LightStudy.C
	gcc -o StudyLightJets_PE100_485_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_486:
	$(CXX) $(CXXFLAGS) $(HEADERS) 486/LightStudy.C
	gcc -o StudyLightJets_PE100_486 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_486:
	$(CXX) $(CXXFLAGS) $(HEADERS) 486/LightStudy.C
	gcc -o StudyLightJets_PE100_486_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_487:
	$(CXX) $(CXXFLAGS) $(HEADERS) 487/LightStudy.C
	gcc -o StudyLightJets_PE100_487 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_487:
	$(CXX) $(CXXFLAGS) $(HEADERS) 487/LightStudy.C
	gcc -o StudyLightJets_PE100_487_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_488:
	$(CXX) $(CXXFLAGS) $(HEADERS) 488/LightStudy.C
	gcc -o StudyLightJets_PE100_488 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_488:
	$(CXX) $(CXXFLAGS) $(HEADERS) 488/LightStudy.C
	gcc -o StudyLightJets_PE100_488_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_489:
	$(CXX) $(CXXFLAGS) $(HEADERS) 489/LightStudy.C
	gcc -o StudyLightJets_PE100_489 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_489:
	$(CXX) $(CXXFLAGS) $(HEADERS) 489/LightStudy.C
	gcc -o StudyLightJets_PE100_489_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_490:
	$(CXX) $(CXXFLAGS) $(HEADERS) 490/LightStudy.C
	gcc -o StudyLightJets_PE100_490 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_490:
	$(CXX) $(CXXFLAGS) $(HEADERS) 490/LightStudy.C
	gcc -o StudyLightJets_PE100_490_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_491:
	$(CXX) $(CXXFLAGS) $(HEADERS) 491/LightStudy.C
	gcc -o StudyLightJets_PE100_491 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_491:
	$(CXX) $(CXXFLAGS) $(HEADERS) 491/LightStudy.C
	gcc -o StudyLightJets_PE100_491_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_492:
	$(CXX) $(CXXFLAGS) $(HEADERS) 492/LightStudy.C
	gcc -o StudyLightJets_PE100_492 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_492:
	$(CXX) $(CXXFLAGS) $(HEADERS) 492/LightStudy.C
	gcc -o StudyLightJets_PE100_492_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_493:
	$(CXX) $(CXXFLAGS) $(HEADERS) 493/LightStudy.C
	gcc -o StudyLightJets_PE100_493 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_493:
	$(CXX) $(CXXFLAGS) $(HEADERS) 493/LightStudy.C
	gcc -o StudyLightJets_PE100_493_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_494:
	$(CXX) $(CXXFLAGS) $(HEADERS) 494/LightStudy.C
	gcc -o StudyLightJets_PE100_494 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_494:
	$(CXX) $(CXXFLAGS) $(HEADERS) 494/LightStudy.C
	gcc -o StudyLightJets_PE100_494_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_495:
	$(CXX) $(CXXFLAGS) $(HEADERS) 495/LightStudy.C
	gcc -o StudyLightJets_PE100_495 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_495:
	$(CXX) $(CXXFLAGS) $(HEADERS) 495/LightStudy.C
	gcc -o StudyLightJets_PE100_495_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_496:
	$(CXX) $(CXXFLAGS) $(HEADERS) 496/LightStudy.C
	gcc -o StudyLightJets_PE100_496 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_496:
	$(CXX) $(CXXFLAGS) $(HEADERS) 496/LightStudy.C
	gcc -o StudyLightJets_PE100_496_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_497:
	$(CXX) $(CXXFLAGS) $(HEADERS) 497/LightStudy.C
	gcc -o StudyLightJets_PE100_497 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_497:
	$(CXX) $(CXXFLAGS) $(HEADERS) 497/LightStudy.C
	gcc -o StudyLightJets_PE100_497_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_498:
	$(CXX) $(CXXFLAGS) $(HEADERS) 498/LightStudy.C
	gcc -o StudyLightJets_PE100_498 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_498:
	$(CXX) $(CXXFLAGS) $(HEADERS) 498/LightStudy.C
	gcc -o StudyLightJets_PE100_498_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_499:
	$(CXX) $(CXXFLAGS) $(HEADERS) 499/LightStudy.C
	gcc -o StudyLightJets_PE100_499 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_499:
	$(CXX) $(CXXFLAGS) $(HEADERS) 499/LightStudy.C
	gcc -o StudyLightJets_PE100_499_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
PE100_500:
	$(CXX) $(CXXFLAGS) $(HEADERS) 500/LightStudy.C
	gcc -o StudyLightJets_PE100_500 $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
rw_500:
	$(CXX) $(CXXFLAGS) $(HEADERS) 500/LightStudy.C
	gcc -o StudyLightJets_PE100_500_RW $(CLIBS) $(LIBS)  LightStudy.o
	@rm -f *.o
