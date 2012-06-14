/* 
 * File:   Classification.C
 * Author: nadjieh
 *
 * Created on February 27, 2012, 5:39 PM
 */

#include <cstdlib>
#include <iostream>
#include <map>
#include <string>

#include "TChain.h"
#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TObjString.h"
#include "TSystem.h"
#include "TROOT.h"

#include "/opt/root/tmva/test/TMVAGui.C"

#if not defined(__CINT__) || defined(__MAKECINT__)
// needs to be included when makecint runs (ACLIC)
#include "TMVA/Factory.h"
#include "TMVA/Tools.h"
#endif

using namespace std;

/*
 * 
 */

void TMVAClassification( TString myMethodList = "" )
{
   

  //---------------------------------------------------------------
  // This loads the library
  TMVA::Tools::Instance();

  // Default MVA methods to be trained + tested
  std::map<std::string,int> Use;

  // --- Cut optimisation
  Use["CutsGA"]          = 1;
   
  // 
   
  // --- Friedman's RuleFit method, ie, an optimized series of cuts ("rules")
  Use["RuleFit"]         = 1;
  // ---------------------------------------------------------------

  std::cout << std::endl;
  std::cout << "==> Start TMVAClassification" << std::endl;

  // Select methods (don't look at this code - not of interest)
  if (myMethodList != "") {
    for (std::map<std::string,int>::iterator it = Use.begin(); it != Use.end(); it++) it->second = 0;

    std::vector<TString> mlist = TMVA::gTools().SplitString( myMethodList, ',' );
    for (UInt_t i=0; i<mlist.size(); i++) {
      std::string regMethod(mlist[i]);

      if (Use.find(regMethod) == Use.end()) {
	std::cout << "Method \"" << regMethod << "\" not known in TMVA under this name. Choose among the following:" << std::endl;
	for (std::map<std::string,int>::iterator it = Use.begin(); it != Use.end(); it++) std::cout << it->first << " ";
	std::cout << std::endl;
	return;
      }
      Use[regMethod] = 1;
    }
  }

  // --------------------------------------------------------------------------------------------------

  // --- Here the preparation phase begins

  // Create a ROOT output file where TMVA will store ntuples, histograms, etc.
  TString outfileName( "TMVA.root" );
  TFile* outputFile = TFile::Open( outfileName, "RECREATE" );

  TMVA::Factory *factory = new TMVA::Factory( "Classification", outputFile,
					      "!V:!Silent:Color:DrawProgressBar:Transformations=I;D;P;G,D:AnalysisType=Classification" );

  factory->AddVariable( "MET", 'F' );
  factory->AddVariable( "MT", 'F' );
  factory->AddVariable( "TopBottomInvMass", 'F' );
  //add other mass variables
  factory->AddVariable( "DPhiTopSecondBottom",  'F' );
  factory->AddVariable( "DOmegaTopSecondBottom",  'F' );
  //add whatever angle you want
  /*Other high level variables*/

  // Read training and test data
  // (it is also possible to use ASCII format as input -> see TMVA Users Guide)
  TString fname = "InputForMVA.root";
   
      
  TFile *input = TFile::Open( fname );
   
  std::cout << "--- Classification       : Using input file: " << input->GetName() << std::endl;
   
  // --- Register the training and test trees

  TTree *signal     = (TTree*)input->Get("Signal");
  TTree *background = (TTree*)input->Get("Background");
   
  /*NOTE:
   * If you have added more than one background tree in InputForMVA.C, you will have more lines:
   * TTree *TTbackground = (TTree*)input->Get("TTBackground");
   * TTree *Wbackground = (TTree*)input->Get("WBackground");
   */
   
  // global event weights per tree (see below for setting event-wise weights)
  Double_t signalWeight     = 1.0;
  Double_t backgroundWeight = 1.0;
   
  /*NOTE:
   * The weight for signal and bkg's are in general different.
   * If you have added more than one background tree in InputForMVA.C, you will have more more weights:
   * Double_t TTbackgroundWeight = some number;
   * Double_t WbackgroundWeight = some number;
   */
   
  // You can add an arbitrary number of signal or background trees
  factory->AddSignalTree    ( signal,     signalWeight     );
  factory->AddBackgroundTree( background, backgroundWeight );
  /*NOTE:
   * If you have added more than one background tree in InputForMVA.C, you will have more lines:
   * factory->AddBackgroundTree( TTbackground, TTbackgroundWeight );
   * factory->AddBackgroundTree( Wbackground, WbackgroundWeight );
   */
   
  // --- end of tree registration 


  // Apply additional cuts on the signal and background samples (can be different)
  TCut mycuts = ""; // for example: TCut mycuts = "abs(var1)<0.5 && abs(var2-0.5)<1";
  TCut mycutb = ""; // for example: TCut mycutb = "abs(var1)<0.5";

  // Tell the factory how to use the training and testing events
  //
  // If no numbers of events are given, half of the events in the tree are used 
  // for training, and the other half for testing:
  //    factory->PrepareTrainingAndTestTree( mycut, "SplitMode=random:!V" );
  // To also specify the number of testing events, use:
  //    factory->PrepareTrainingAndTestTree( mycut,
  //                                         "NSigTrain=3000:NBkgTrain=3000:NSigTest=3000:NBkgTest=3000:SplitMode=Random:!V" );
  factory->PrepareTrainingAndTestTree( mycuts, mycutb,
				       "nTrain_Signal=0:nTrain_Background=0:SplitMode=Random:NormMode=NumEvents:!V" );

  // ---- Book MVA methods
  //
  // Please lookup the various method configuration options in the corresponding cxx files, eg:
  // src/MethoCuts.cxx, etc, or here: http://tmva.sourceforge.net/optionRef.html
  // it is possible to preset ranges in the option string in which the cut optimisation should be done:
  // "...:CutRangeMin[2]=-1:CutRangeMax[2]=1"...", where [2] is the third input variable

  // Cut optimization using genetic algorithm 
  
  if (Use["CutsGA"])
    factory->BookMethod( TMVA::Types::kCuts, "CutsGA",
			 "H:!V:FitMethod=GA:CutRangeMin[0]=-10:CutRangeMax[0]=10:VarProp[1]=FMax:EffSel:Steps=30:Cycles=3:PopSize=400:SC_steps=10:SC_rate=5:SC_factor=0.95" );

   
  // RuleFit -- TMVA implementation of Friedman's method
  if (Use["RuleFit"])
    factory->BookMethod( TMVA::Types::kRuleFit, "RuleFit",
			 "H:!V:RuleFitModule=RFTMVA:Model=ModRuleLinear:MinImp=0.001:RuleMinDist=0.001:NTrees=20:fEventsMin=0.01:fEventsMax=0.5:GDTau=-1.0:GDTauPrec=0.01:GDStep=0.01:GDNSteps=10000:GDErrScale=1.02" );


  // ---- Now you can tell the factory to train, test, and evaluate the MVAs

  // Train MVAs using the set of training events
  factory->TrainAllMethods();

  // ---- Evaluate all MVAs using the set of test events
  factory->TestAllMethods();

  // ----- Evaluate and compare performance of all configured MVAs
  factory->EvaluateAllMethods();

  // --------------------------------------------------------------

  // Save the output
  outputFile->Close();

  std::cout << "==> Wrote root file: " << outputFile->GetName() << std::endl;
  std::cout << "==> TMVAClassification is done!" << std::endl;

  delete factory;

  // Launch the GUI for the root macros
  if (!gROOT->IsBatch()) TMVAGui( outfileName );
}
int main(int argc, char** argv) {
  TMVAClassification();
  return 0;
}

