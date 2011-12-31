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
#include "../../../../AnalysisClasses/LightJets/interface/AnalysisHandler.h"

#include "../../../../TopBrussels/TopTreeProducer/interface/TRootMuon.h"

#include<iostream>
#include "TFile.h"
#include "TTree.h"

using namespace std;

using namespace TopTree;

int main(int argc, char** argv){
    std::vector<std::pair<std::string,double> > myFileWeights;
    std::vector<bool> IsTtBar;
    std::string anaName;
    std::pair<std::string,double> inputNameWeight;
    inputNameWeight.first = "";
    inputNameWeight.second = 0.;
    double Luminosity = 0;
    double intialBeforePresel = 0;
    double XSec = 0;
    bool isTtBar = false;
    for (int f = 1; f < argc; f++) {
        std::string arg_fth(*(argv + f));
//        cout<<"-------- "<< arg_fth<<endl;
        if (arg_fth == "out") {
          f++;
          std::string out(*(argv + f));
          anaName = string(out);
        }else if (arg_fth == "input") {
          f++;
          std::string in(*(argv + f));
          if(in == "Signal.root" || in == "OtherTtBar.root")
              isTtBar = true;
          IsTtBar.push_back(isTtBar);
          in ="/home/ajafari/rootfiles/TopTrees/7TeV/July10/Skimmed/FullSelection/FS_ECalDriven_"+in;
          inputNameWeight.first = in;
//          cout<<inputNameWeight.first<<endl;
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
        }else if(arg_fth == "nextinput"){
          f++;
          inputNameWeight.second = (double)(XSec*Luminosity)/(double)intialBeforePresel;
          myFileWeights.push_back(inputNameWeight);
          intialBeforePresel = 0;
          XSec = 0;
          isTtBar = false;
          std::string in(*(argv + f));
          if(in == "Signal.root" || in == "OtherTtBar.root")
              isTtBar = true;
          IsTtBar.push_back(isTtBar);
          in ="/home/ajafari/rootfiles/TopTrees/7TeV/July10/Skimmed/FullSelection/FS_ECalDriven_"+in;
          inputNameWeight.first = in;
//          cout<<inputNameWeight.first<<endl;
          inputNameWeight.second = 0.;
        }else if(arg_fth == "lastinput"){
          f++;
          inputNameWeight.second = (double)(XSec*Luminosity)/(double)intialBeforePresel;
          myFileWeights.push_back(inputNameWeight);
          break;
        }
    }
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
    
    bool ExtJets = true;
//
//
//    PtWeightEffHandler * WeightHandler_1 = new PtWeightEffHandler("expo_1",1);
//    WeightHandler_1->Condition = FunctionBtag_MC;
//    WeightHandler_1->ResetConditionForAllProps();
//    WeightHandler_1->set2Ds();
////
//    PtWeightEffHandler * WeightHandler_2 = new PtWeightEffHandler("expo_2",2);
//    WeightHandler_2->Condition = FunctionBtag_MC;
//    WeightHandler_2->ResetConditionForAllProps();
//    WeightHandler_2->set2Ds();
////
//    PtWeightEffHandler * WeightHandler_4 = new PtWeightEffHandler("landau_4",4);
//    WeightHandler_4->Condition = FunctionBtag_MC;
//    WeightHandler_4->ResetConditionForAllProps();
//    WeightHandler_4->set2Ds();
////
//    PtWeightEffHandler * WeightHandler_5 = new PtWeightEffHandler("landau_5",5);
//    WeightHandler_5->Condition = FunctionBtag_MC;
//    WeightHandler_5->ResetConditionForAllProps();
//    WeightHandler_5->set2Ds();

        
//    MCAnalysis * myMCAnalysis = new MCAnalysis("FmcMC_Chi2Cut10000",50., 160.,160.,280.,/*chi2Cut*/10000.,/*topPtcut*/0.,
//    /*ExtJets*/ExtJets);
    DataAnalysis * myDataAnalysis = new DataAnalysis(("FdataData_RWLepLight_"+anaName), 50., 160.,160.,280.,
    /*chi2cut*/100000.,/*topPtcut*/0.,/*doAntiTag*/false,/*AntiTagCut*/1000.);
//    MCAnalysis * myMCAnalysis = new MCAnalysis(string("FmcMC_"+anaName), 50., 160.,160.,280.,/*chi2cut*/100000.,/*topPtcut*/0.);
    AnalysisHandler Fullanalysis("FullStudy",/*dobTag*/false,/*doBtagDataLike*/false,/*ExtJets*/true,/*Lumi*/100.,
    myMassResolution,myElecCuts,myJetCuts,"minChi2",/*OtherTtBar*/true);

    
//    myMCAnalysis->AddWeighedHandlersToRightRegion(WeightHandler_6);
//    myDataAnalysis->AddWeighedHandlersToRightRegion(WeightHandler_1);
//    myDataAnalysis->AddWeighedHandlersToRightRegion(WeightHandler_2);
//    myDataAnalysis->AddWeighedHandlersToRightRegion(WeightHandler_4);
//    myDataAnalysis->AddWeighedHandlersToRightRegion(WeightHandler_5);

    
//    Fullanalysis.AddAnalysis(myMCAnalysis);
    Fullanalysis.AddAnalysis(myDataAnalysis);
    Fullanalysis.setVerbosity(0);

    for(uint nf = 0; nf < myFileWeights.size(); nf++){
        std::string fname = myFileWeights.at(nf).first;
        cout<<fname<<endl;
        double weight = myFileWeights.at(nf).second;
        cout<<weight<<endl;
        TFile * F = new TFile(myFileWeights.at(nf).first.c_str(),"read");
        if(F == NULL)
            cout<<"Bad file pointer"<<endl;
        TTree* runTree = (TTree*) F->Get("runTree");
        TTree* eventTree = (TTree*) F->Get("eventTree");
        PracticalEvent * pracEvt = NULL;
        if(IsTtBar.at(nf))
            pracEvt = new PracticalEvent(eventTree,runTree,true);
        else
            pracEvt = new PracticalEvent(eventTree,runTree);
        int i = 0;

        while (pracEvt->Next()){
            i++;
////            cout<<"event number : "<<i<<endl;
            Fullanalysis.Analyze(pracEvt,weight);
//            if(i == 100)
//                break;
        }
    }
//    double Fmc = myMCAnalysis->getF();
    double Fdata = myDataAnalysis->getF();

    Fullanalysis.setAnalysisNonTrivialF(1,1.679);
    Fullanalysis.End();
    cout<<"\t\t--------------------------------"<<endl;
//    cout<<"\t\tFmc = "<<Fmc<<endl;
    cout<<"\t\tFdata = "<<Fdata<<endl;
    cout<<"\t\tFdata_RW = "<<Fullanalysis.f.at(0)<<endl;
    cout<<"\t\t--------------------------------"<<endl;

    return 0;
};


