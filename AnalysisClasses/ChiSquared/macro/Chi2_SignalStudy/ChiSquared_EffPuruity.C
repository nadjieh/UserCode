#include "../../../../AnalysisClasses/ChiSquared/interface/Combinator.h"
#include "../../../../AnalysisClasses/ChiSquared/interface/TopEvent.h"
#include "../../../../AnalysisClasses/ChiSquared/interface/ChiSquaredAnalysisHandler.h"
#include "../../../../AnalysisClasses/EventSelection/interface/PracticalEvent.h"
#include "../../../../AnalysisClasses/EventSelection/interface/Event.h"
#include "../../../../AnalysisClasses/EventSelection/interface/GoodObjects.h"




#include<iostream>
#include "TFile.h"
#include "TTree.h"

using namespace std;
int main(){
    TFile * F = new TFile("/home/ajafari/rootfiles/TopTrees/7TeV/July10/Skimmed/FullSelection/FS_ECalDriven_Signal.root","read");
    TTree* runTree = (TTree*) F->Get("runTree");
    TTree* eventTree = (TTree*) F->Get("eventTree");

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

    PracticalEvent pracEvt(eventTree,runTree,true);
    ChiSquaredAnalysisHandler myAnalysis("ChiSquared_Efficiency_Purity",false, true, 100.,myMassResolution,
            myElecCuts,myJetCuts,"maxPtinminChi2s",100000.,0.);
    myAnalysis.setOnly4MatchedJets();
    myAnalysis.setVerbosity(0);
//    myAnalysis.setVerbosity(5);

    int i = 1;

    while (pracEvt.Next()){
//        cout<<"----------------------------------------------------------------------event number : "<<i<<endl;
        i++;
//        if(i<10)
//            continue;
        myAnalysis.Analyze(&pracEvt,1.);
//        if(i == 12)
//            break;
    }

    myAnalysis.End();

    return 0;
};


