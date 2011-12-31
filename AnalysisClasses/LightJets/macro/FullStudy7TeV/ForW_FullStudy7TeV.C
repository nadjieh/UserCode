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
    double doJES = 1.;

    
    double extFdata = -1.;
    
    for (int f = 1; f < argc; f++) {
        std::string arg_fth(*(argv + f));
//        cout<<"-------- "<< arg_fth<<endl;
        if (arg_fth == "out") {
          f++;
          std::string out(*(argv + f));
          anaName = string(out);
        }else if (arg_fth == "Fdata") {
          f++;
          std::string out(*(argv + f));
          extFdata = atof(out.c_str());
        }else if (arg_fth == "input") {
          f++;
          std::string in(*(argv + f));
          if(in == "Signal.root" || in == "OtherTtBar.root" || in == "0.9/FS_Signal_0.9.root" ||
             in == "1.1/FS_Signal_1.1.root" ||in == "0.9/FS_OtherTt_0.9.root" ||in == "1.1/FS_OtherTt_1.1.root")
              isTtBar = true;
          IsTtBar.push_back(isTtBar);
//          in ="/home/ajafari/rootfiles/TopTrees/7TeV/July10/SystematicSamples/FullSelection/JES"+in;
          in ="/home/ajafari/rootfiles/TopTrees/7TeV/July10/Skimmed/FullSelection/FS_ECalDriven_"+in;
//          in ="/tmp/ajafari/FullSelection/FS_ECalDriven_"+in;
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
          if(in == "Signal.root" || in == "OtherTtBar.root" || in == "0.9/FS_Signal_0.9.root" ||
             in == "1.1/FS_Signal_1.1.root" ||in == "0.9/FS_OtherTt_0.9.root" ||in == "1.1/FS_OtherTt_1.1.root")
            isTtBar = true;
          IsTtBar.push_back(isTtBar);
          in ="/home/ajafari/rootfiles/TopTrees/7TeV/July10/Skimmed/FullSelection/FS_ECalDriven_"+in;
//          in ="/tmp/ajafari/FullSelection/FS_ECalDriven_"+in;
//          in ="/home/ajafari/rootfiles/TopTrees/7TeV/July10/SystematicSamples/FullSelection/JES"+in;
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
//
    MassAndResolution myMassResolution;
    myMassResolution.topMass = 180.6;
    myMassResolution.topRes = 3.462;
    myMassResolution.wMass = 88.76;
    myMassResolution.wRes = 10.73;
    if(myMassResolution.topMass == -1 ||myMassResolution.wRes == -1 ||myMassResolution.wMass == -1 ||myMassResolution.topRes == -1 )
        return -1;
    cout<<myMassResolution.topMass <<"\t"<<myMassResolution.topRes<<"\t"<<myMassResolution.wMass<<"\t"<<myMassResolution.wRes<<endl;
    bool ExtJets = true;
//
//// NoW
    PtWeightEffHandler * WeightHandler_30 = new PtWeightEffHandler("expo_30",30);
    WeightHandler_30->Condition = FunctionBtag_MC;
    WeightHandler_30->ResetConditionForAllProps();
    WeightHandler_30->set2Ds();
////
    PtWeightEffHandler * WeightHandler_31 = new PtWeightEffHandler("landau_31",31);
    WeightHandler_31->Condition = FunctionBtag_MC;
    WeightHandler_31->ResetConditionForAllProps();
    WeightHandler_31->set2Ds();
//// 11%
    PtWeightEffHandler * WeightHandler_32 = new PtWeightEffHandler("expo_32",32);
    WeightHandler_32->Condition = FunctionBtag_MC;
    WeightHandler_32->ResetConditionForAllProps();
    WeightHandler_32->set2Ds();
////
    PtWeightEffHandler * WeightHandler_33 = new PtWeightEffHandler("landau_33",33);
    WeightHandler_33->Condition = FunctionBtag_MC;
    WeightHandler_33->ResetConditionForAllProps();
    WeightHandler_33->set2Ds();
///
    PtWeightEffHandler * WeightHandler_34 = new PtWeightEffHandler("landau_34",34);
    WeightHandler_34->Condition = FunctionBtag_MC;
    WeightHandler_34->ResetConditionForAllProps();
    WeightHandler_34->set2Ds();
//21%
    PtWeightEffHandler * WeightHandler_35 = new PtWeightEffHandler("expo_35",35);
    WeightHandler_35->Condition = FunctionBtag_MC;
    WeightHandler_35->ResetConditionForAllProps();
    WeightHandler_35->set2Ds();
    
    PtWeightEffHandler * WeightHandler_36 = new PtWeightEffHandler("expo_36",36);
    WeightHandler_36->Condition = FunctionBtag_MC;
    WeightHandler_36->ResetConditionForAllProps();
    WeightHandler_36->set2Ds();
////
    PtWeightEffHandler * WeightHandler_37 = new PtWeightEffHandler("landau_37",37);
    WeightHandler_37->Condition = FunctionBtag_MC;
    WeightHandler_37->ResetConditionForAllProps();
    WeightHandler_37->set2Ds();
///
    PtWeightEffHandler * WeightHandler_38 = new PtWeightEffHandler("landau_38",38);
    WeightHandler_38->Condition = FunctionBtag_MC;
    WeightHandler_38->ResetConditionForAllProps();
    WeightHandler_38->set2Ds();

//31%
    PtWeightEffHandler * WeightHandler_39 = new PtWeightEffHandler("expo_39",39);
    WeightHandler_39->Condition = FunctionBtag_MC;
    WeightHandler_39->ResetConditionForAllProps();
    WeightHandler_39->set2Ds();

    PtWeightEffHandler * WeightHandler_40 = new PtWeightEffHandler("expo_40",40);
    WeightHandler_40->Condition = FunctionBtag_MC;
    WeightHandler_40->ResetConditionForAllProps();
    WeightHandler_40->set2Ds();
////
    PtWeightEffHandler * WeightHandler_41 = new PtWeightEffHandler("landau_41",41);
    WeightHandler_41->Condition = FunctionBtag_MC;
    WeightHandler_41->ResetConditionForAllProps();
    WeightHandler_41->set2Ds();
//41%
    PtWeightEffHandler * WeightHandler_42 = new PtWeightEffHandler("expo_42",42);
    WeightHandler_42->Condition = FunctionBtag_MC;
    WeightHandler_42->ResetConditionForAllProps();
    WeightHandler_42->set2Ds();
////
    PtWeightEffHandler * WeightHandler_43 = new PtWeightEffHandler("landau_43",43);
    WeightHandler_43->Condition = FunctionBtag_MC;
    WeightHandler_43->ResetConditionForAllProps();
    WeightHandler_43->set2Ds();
//51%
    PtWeightEffHandler * WeightHandler_44 = new PtWeightEffHandler("expo_44",44);
    WeightHandler_44->Condition = FunctionBtag_MC;
    WeightHandler_44->ResetConditionForAllProps();
    WeightHandler_44->set2Ds();
////
    PtWeightEffHandler * WeightHandler_45 = new PtWeightEffHandler("landau_45",45);
    WeightHandler_45->Condition = FunctionBtag_MC;
    WeightHandler_45->ResetConditionForAllProps();
    WeightHandler_45->set2Ds();
//100%
    PtWeightEffHandler * WeightHandler_46 = new PtWeightEffHandler("expo_46",46);
    WeightHandler_46->Condition = FunctionBtag_MC;
    WeightHandler_46->ResetConditionForAllProps();
    WeightHandler_46->set2Ds();
////
    PtWeightEffHandler * WeightHandler_47 = new PtWeightEffHandler("landau_47",47);
    WeightHandler_47->Condition = FunctionBtag_MC;
    WeightHandler_47->ResetConditionForAllProps();
    WeightHandler_47->set2Ds();

        
//    MCAnalysis * myMCAnalysis = new MCAnalysis("FmcMC_Chi2Cut10000",50., 160.,160.,280.,/*chi2Cut*/10000.,/*topPtcut*/0.,
//    /*ExtJets*/ExtJets);
//    DataAnalysis * myDataAnalysis = new DataAnalysis(("FdataData_"+anaName), b1, b2,b2,b3,/*chi2cut*/100000.,/*topPtcut*/0.,
//    /*doAntiTag*/false,/*AntiTagCut*/1000.);
    MCAnalysis * myMCAnalysis_noW = new MCAnalysis(string("FmcMC_noW"), 50, 160,160,280,/*chi2cut*/100000.,/*topPtcut*/0.);
    myMCAnalysis_noW->AddWeighedHandlersToRightRegion(WeightHandler_30);
    myMCAnalysis_noW->AddWeighedHandlersToRightRegion(WeightHandler_31);
    MCAnalysis * myMCAnalysis_2 = new MCAnalysis(string("FmcMC_2"), 50, 160,160,280,/*chi2cut*/100000.,/*topPtcut*/0.);
    myMCAnalysis_2->AddWeighedHandlersToRightRegion(WeightHandler_46);
    myMCAnalysis_2->AddWeighedHandlersToRightRegion(WeightHandler_47);
    MCAnalysis * myMCAnalysis_51 = new MCAnalysis(string("FmcMC_51"), 50, 160,160,280,/*chi2cut*/100000.,/*topPtcut*/0.);
    myMCAnalysis_51->AddWeighedHandlersToRightRegion(WeightHandler_44);
    myMCAnalysis_51->AddWeighedHandlersToRightRegion(WeightHandler_45);
    MCAnalysis * myMCAnalysis_41 = new MCAnalysis(string("FmcMC_41"), 50, 160,160,280,/*chi2cut*/100000.,/*topPtcut*/0.);
    myMCAnalysis_41->AddWeighedHandlersToRightRegion(WeightHandler_42);
    myMCAnalysis_41->AddWeighedHandlersToRightRegion(WeightHandler_43);
    MCAnalysis * myMCAnalysis_31 = new MCAnalysis(string("FmcMC_31"), 50, 160,160,280,/*chi2cut*/100000.,/*topPtcut*/0.);
    myMCAnalysis_31->AddWeighedHandlersToRightRegion(WeightHandler_39);
    myMCAnalysis_31->AddWeighedHandlersToRightRegion(WeightHandler_40);
    myMCAnalysis_31->AddWeighedHandlersToRightRegion(WeightHandler_41);
    MCAnalysis * myMCAnalysis_21 = new MCAnalysis(string("FmcMC_21"), 50, 160,160,280,/*chi2cut*/100000.,/*topPtcut*/0.);
    myMCAnalysis_21->AddWeighedHandlersToRightRegion(WeightHandler_35);
    myMCAnalysis_21->AddWeighedHandlersToRightRegion(WeightHandler_36);
    myMCAnalysis_21->AddWeighedHandlersToRightRegion(WeightHandler_37);
    myMCAnalysis_21->AddWeighedHandlersToRightRegion(WeightHandler_38);
    MCAnalysis * myMCAnalysis_11 = new MCAnalysis(string("FmcMC_11"), 50, 160,160,280,/*chi2cut*/100000.,/*topPtcut*/0.);
    myMCAnalysis_11->AddWeighedHandlersToRightRegion(WeightHandler_32);
    myMCAnalysis_11->AddWeighedHandlersToRightRegion(WeightHandler_33);
    myMCAnalysis_11->AddWeighedHandlersToRightRegion(WeightHandler_34);
    AnalysisHandler Fullanalysis("",/*dobTag*/false,/*doBtagDataLike*/false,/*ExtJets*/true,/*Lumi*/100.,
    myMassResolution,myElecCuts,myJetCuts,"minChi2");

    


    Fullanalysis.AddAnalysis(myMCAnalysis_noW);
    Fullanalysis.AddAnalysis(myMCAnalysis_2);
    Fullanalysis.AddAnalysis(myMCAnalysis_51);
    Fullanalysis.AddAnalysis(myMCAnalysis_41);
    Fullanalysis.AddAnalysis(myMCAnalysis_31);
    Fullanalysis.AddAnalysis(myMCAnalysis_21);
    Fullanalysis.AddAnalysis(myMCAnalysis_11);
    Fullanalysis.setVerbosity(0);
    Fullanalysis.doDifferentweights = false;
    
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
//            i++;
////            cout<<"event number : "<<i<<endl;
//            cout<<"Weight is "<<weight<<endl;
            Fullanalysis.resetMinChi2Top();
            if(fname == "/home/ajafari/rootfiles/TopTrees/7TeV/July10/Skimmed/FullSelection/FS_ECalDriven_WJets.root"){
                Fullanalysis.doDifferentweights = true;
                Fullanalysis.Weights.clear();
                Fullanalysis.Weights.push_back(0);
                Fullanalysis.Weights.push_back(2*weight);
                Fullanalysis.Weights.push_back(0.837*weight);
                Fullanalysis.Weights.push_back(0.673*weight);
                Fullanalysis.Weights.push_back(0.509*weight);
                Fullanalysis.Weights.push_back(0.345*weight);
                Fullanalysis.Weights.push_back(0.18*weight);
                Fullanalysis.Analyze(pracEvt,weight,doJES);
            }
            
                Fullanalysis.Analyze(pracEvt,weight,doJES);
                Fullanalysis.doDifferentweights = false;
                Fullanalysis.Weights.clear();


//            if(i == 10000)
//                break;
        }
    }
//    double Fmc = myMCAnalysis->getF();
//    double Fdata = myDataAnalysis->getF();
//    if(extFdata != -1.){
//        Fullanalysis.setAnalysisNonTrivialF(1,extFdata);
//        Fdata = extFdata;
//    }
    Fullanalysis.End();
    cout<<"\t\t--------------------------------"<<endl;
//    cout<<"\t\tFmc = "<<Fmc<<endl;
//    cout<<"\t\tFdata = "<<Fdata<<endl;
//    cout<<"\t\tFdata_RW = "<<Fullanalysis.f.at(0)<<endl;
    cout<<"\t\t--------------------------------"<<endl;

    return 0;
};


