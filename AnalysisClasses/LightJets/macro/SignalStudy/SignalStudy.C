#include "../../../../AnalysisClasses/ChiSquared/interface/BaseRegion.h"
#include "../../../../AnalysisClasses/ChiSquared/interface/TopEvent.h"
#include "../../../../AnalysisClasses/ChiSquared/interface/Combinator.h"
#include "../../../../AnalysisClasses/ChiSquared/interface/DataRegion.h"
#include "../../../../AnalysisClasses/ChiSquared/interface/MCRegion.h"
#include "../../../../AnalysisClasses/ChiSquared/interface/EtaOnPtWeightJetEffHandler.h"
#include "../../../../AnalysisClasses/ChiSquared/interface/PtWeightJetEffHandler.h"
#include "../../../../AnalysisClasses/ChiSquared/interface/TwoDWeightJetEffHandler.h"
#include "../../../../AnalysisClasses/ChiSquared/interface/SpecificEffHandler.h"
#include "../../../../AnalysisClasses/EventSelection/interface/PracticalEvent.h"
#include "../../../../AnalysisClasses/EventSelection/interface/Event.h"
#include "../../../../AnalysisClasses/EventSelection/interface/GoodObjects.h"
#include "../../../../AnalysisClasses/LightJets/interface/DataAnalysis.h"
#include "../../../../AnalysisClasses/LightJets/interface/MCAnalysis.h"

#include "../../../../TopBrussels/TopTreeProducer/interface/TRootMuon.h"

#include<iostream>
#include "TFile.h"
#include "TTree.h"
#include "../../../../AnalysisClasses/LightJets/interface/AnalysisHandler.h"
using namespace std;
int main(){
    TFile * F = new TFile("/home/ajafari/rootfiles/TopTrees/7TeV/July10/Skimmed/FullSelection/FS_ECalDriven_Signal.root","read");
//    TFile * F = new TFile("/tmp/ajafari/FullSelection/FS_ECalDriven_Signal.root","read");
//    TFile * F = new TFile("/tmp/ajafari/FS_ECalDriven_Signal.root","read");
    TTree* runTree = (TTree*) F->Get("runTree");
    TTree* eventTree = (TTree*) F->Get("eventTree");
    PracticalEvent pracEvt(eventTree,runTree,true);
    
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
    
//    MCAnalysis * myMCAnalysis = new MCAnalysis("FmcMC",50., 160.,160.,280.);
    MCAnalysis * myMCAnalysis = new MCAnalysis("FmcMC",60., 160.,160.,280.);
//    MCAnalysis * myMCAnalysis_Fdata = new MCAnalysis("FdataMC",50., 160.,160.,280.);
    MCAnalysis * myMCAnalysis_Fdata = new MCAnalysis("FdataMC",60., 160.,160.,280.);
//    DataAnalysis * myDataAnalysis = new DataAnalysis("FdataDATA",50., 160.,160.,280.);
    DataAnalysis * myDataAnalysis = new DataAnalysis("FdataDATA",60., 160.,160.,280.);

    AnalysisHandler Signalanalysis("SignalStudy_60-160-280",/*dobtag*/false,/*doBtagDataLike*/false,/*extJetOk_*/true,/*Lumi*/100.,
    myMassResolution,myElecCuts,myJetCuts,/*whichMethod*/"minChi2");
    Signalanalysis.AddAnalysis(myMCAnalysis);
    Signalanalysis.AddAnalysis(myMCAnalysis_Fdata);
    Signalanalysis.AddAnalysis(myDataAnalysis);
    Signalanalysis.setOnly4MatchedJets();
    Signalanalysis.setVerbosity(0);
    
    int i = 1;

    while (pracEvt.Next()){
//        cout<<"-----------------------------------------------------------------------------------event number : "<<i<<endl;
        Signalanalysis.Analyze(&pracEvt,1.);
        i++;
//        if(i == 200)
//            break;
    }
    double Fmc = myMCAnalysis->getF();
    double Fdata = myDataAnalysis->getF();
    Signalanalysis.setAnalysisNonTrivialF(2,2.83644);// no reweighing
//    Signalanalysis.setAnalysisNonTrivialF(2,Fdata);
    Signalanalysis.End();
    cout<<"\t\t--------------------------------"<<endl;
    cout<<"\t\tFmc = "<<Fmc<<endl;
    cout<<"\t\tFdata = "<<Fdata<<endl;
    cout<<"\t\t--------------------------------"<<endl;

    return 0;
};


