#include "/afs/cern.ch/user/a/ajafari/scratch0/CMSSW_3_6_1_patch3/src/AnalysisClasses/ChiSquared/interface/Combinator.h"
#include "/afs/cern.ch/user/a/ajafari/scratch0/CMSSW_3_6_1_patch3/src/AnalysisClasses/ChiSquared/interface/TopEvent.h"
#include "/afs/cern.ch/user/a/ajafari/scratch0/CMSSW_3_6_1_patch3/src/AnalysisClasses/ChiSquared/interface/ChiSquaredAnalysisHandler.h"
#include "/afs/cern.ch/user/a/ajafari/scratch0/CMSSW_3_6_1_patch3/src/AnalysisClasses/EventSelection/interface/PracticalEvent.h"
#include "/afs/cern.ch/user/a/ajafari/scratch0/CMSSW_3_6_1_patch3/src/AnalysisClasses/EventSelection/interface/Event.h"
#include "/afs/cern.ch/user/a/ajafari/scratch0/CMSSW_3_6_1_patch3/src/AnalysisClasses/EventSelection/interface/GoodObjects.h"
#include "/afs/cern.ch/user/a/ajafari/scratch0/CMSSW_3_6_1_patch3/src/AnalysisClasses/ChiSquared/interface/TwoDObjectPropertyCreator.h"




#include<iostream>
#include "TFile.h"
#include "TTree.h"

using namespace std;
int main(int argc, char** argv){
    std::string anaName;
    std::string inputName;
    double Luminosity = 0;
    double intialBeforePresel = 0;
    double XSec = 0;
    bool isTtBar = false;
    for (int f = 1; f < argc; f++) {
        std::string arg_fth(*(argv + f));
        if (arg_fth == "out") {
          f++;
          std::string out(*(argv + f));
          anaName = string(out);
        }else if (arg_fth == "input") {
          f++;
          std::string in(*(argv + f));
          if(in == "Signal.root" || in == "OtherTtBar.root")
              isTtBar = true;
          in ="/home/ajafari/rootfiles/TopTrees/7TeV/July10/Skimmed/FullSelection/FS_ECalDriven_"+in;
          inputName = in;
        }else if(arg_fth == "XSec"){
          f++;
          std::string Xsec(*(argv + f));
          XSec = atof(Xsec.c_str());
        }else if(arg_fth == "Lumi"){
          f++;
          std::string Lumi(*(argv + f));
          Luminosity = atof(Lumi.c_str());
        }else if(arg_fth == "Initial"){
          f++;
          std::string intialBeforePresel_(*(argv + f));
          intialBeforePresel = atof(intialBeforePresel_.c_str());
        }
    }
    TFile * F = new TFile(inputName.c_str(),"read");
    TTree* runTree = (TTree*) F->Get("runTree");
    TTree* eventTree = (TTree*) F->Get("eventTree");

    double weight = (double)(XSec*Luminosity)/(double)intialBeforePresel;
    cout<<inputName<<"\n\tWeight: "<<weight<<endl;
    ElectronCuts myElecCuts;
    myElecCuts.Pt = 30;
    myElecCuts.eta = 2.4; myElecCuts.ExLow = 1.442; myElecCuts.ExHigh = 1.56;
    myElecCuts.Id = "VBTF70"; myElecCuts.IdSecond = "VBTF95";
    myElecCuts.IsoType = "";
    myElecCuts.D0 = 0.02; 
    myElecCuts.IsoCut = 0.1;

    JetCuts myJetCuts;
    myJetCuts.bTagAlgo = "TCHE"; myJetCuts.Pt = 30.; myJetCuts.eta = 2.4;
    myJetCuts.nCaloTower = 5;
    myJetCuts.EmfUp = 0.9; myJetCuts.EmfLow = 0.05;
    myJetCuts.fhpd = 1000.; myJetCuts.N90 = -1;
    myJetCuts.bTagCut = 4.;

    MassAndResolution myMassResolution;
    myMassResolution.topMass = 180.6;
    myMassResolution.topRes = 3.462;
    myMassResolution.wMass = 88.76;
    myMassResolution.wRes = 10.73;

    PracticalEvent pracEvt(eventTree,runTree,isTtBar);

    ChiSquaredAnalysisHandler myAnalysis(anaName,/*dobtag*/false, /*datalike*/false,/*extJetOk*/true, Luminosity
    ,myMassResolution,myElecCuts,myJetCuts,"minChi2");
    
//    myAnalysis.setChi2Cut(100.);
//    myAnalysis.setTopPtCut(200.);

    myAnalysis.setVerbosity(0);
//    myAnalysis.setVerbosity(6);

    int i = 1;

    while (pracEvt.Next()){
//        cout<<"----------------------------------------------------------------------event number : "<<i<<endl;
//        if(i<1220)
//            continue;
        myAnalysis.Analyze(&pracEvt,weight);
//        if(i == 100)
//            break;
        i++;
    }

    myAnalysis.End();
    cout<<i<<endl;
    return 0;
};


