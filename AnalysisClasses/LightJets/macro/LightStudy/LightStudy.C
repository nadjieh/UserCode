#include "../../../../AnalysisClasses/ChiSquared/interface/Combinator.h"
#include "../../../../AnalysisClasses/ChiSquared/interface/TopEvent.h"
#include "../../../../AnalysisClasses/ChiSquared/interface/LightStudyAnalysisHandler.h"
#include "../../../../AnalysisClasses/ChiSquared/interface/LightStudyJetHandler.h"
#include "../../../../AnalysisClasses/EventSelection/interface/PracticalEvent.h"
#include "../../../../AnalysisClasses/EventSelection/interface/Event.h"
#include "../../../../AnalysisClasses/EventSelection/interface/GoodObjects.h"
#include "../../../../AnalysisClasses/ChiSquared/interface/TwoDWeightJetEffHandler.h"
#include "../../../../AnalysisClasses/LightJets/interface/LightAnalysis.h"




#include<iostream>
#include "TFile.h"
#include "TTree.h"

using namespace std;
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
    
    MassAndResolution myMassResolution;
    myMassResolution.topMass = -1;
    myMassResolution.topRes = -1;
    myMassResolution.wMass = -1;
    myMassResolution.wRes = -1;

    double doJES = 1.;


    double b1 = 1000.;
    double b2 = 100.;
    double b3 = 10.;
    
    for (int f = 1; f < argc; f++) {
        std::string arg_fth(*(argv + f));
//        cout<<"-------- "<< arg_fth<<endl;
        if (arg_fth == "out") {
          f++;
          std::string out(*(argv + f));
          anaName = string(out);
        }else if (arg_fth == "JES") {
          f++;
          std::string out(*(argv + f));
          doJES = atof(out.c_str());
        }else if (arg_fth == "WMass") {
          f++;
          std::string out(*(argv + f));
          myMassResolution.wMass = atof(out.c_str());
        }else if (arg_fth == "WRes") {
          f++;
          std::string out(*(argv + f));
          myMassResolution.wRes = atof(out.c_str());
        }else if (arg_fth == "TopMass") {
          f++;
          std::string out(*(argv + f));
          myMassResolution.topMass = atof(out.c_str());
        }else if (arg_fth == "TopRes") {
          f++;
          std::string out(*(argv + f));
          myMassResolution.topRes = atof(out.c_str());
        }else if (arg_fth == "b1") {
          f++;
          std::string out(*(argv + f));
          b1 = atof(out.c_str());
        }else if (arg_fth == "b2") {
          f++;
          std::string out(*(argv + f));
          b2 = atof(out.c_str());
        }else if (arg_fth == "b3") {
          f++;
          std::string out(*(argv + f));
          b3 = atof(out.c_str());
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

    if(myMassResolution.topMass == -1 ||myMassResolution.wRes == -1 ||myMassResolution.wMass == -1 ||myMassResolution.topRes == -1 )
        return -1;
    cout<<myMassResolution.topMass <<"\t"<<myMassResolution.topRes<<"\t"<<myMassResolution.wMass<<"\t"<<myMassResolution.wRes<<endl;
    cout<<b1 <<"\t"<<b2<<"\t"<<b3<<"\t"<<endl;
    
    TwoDWeightLightEffHandler *  StupidTwoD = new TwoDWeightLightEffHandler("BMatched_LepLight_EtaPt", "", true);
    StupidTwoD->Condition = isBJet;
    StupidTwoD->ResetConditionForAllProps();
    StupidTwoD->set2Ds();

    TwoDWeightLightEffHandler *  StupidTwoDLeft = new TwoDWeightLightEffHandler("BMatched_LepLight_EtaPt", "", true);
    StupidTwoDLeft->Condition = isBJet;
    StupidTwoDLeft->ResetConditionForAllProps();
    StupidTwoDLeft->set2Ds();

    TwoDWeightLightEffHandler *  StupidTwoDRight = new TwoDWeightLightEffHandler("BMatched_LepLight_EtaPt", "", true);
    StupidTwoDRight->Condition = isBJet;
    StupidTwoDRight->ResetConditionForAllProps();
    StupidTwoDRight->set2Ds();

    LightAnalysis * myLightAnalysis = new LightAnalysis("Global","Light",-1.,10000.,3.);
    myLightAnalysis->AddHandler(StupidTwoD);
    LightAnalysis * myLightAnalysisRight = new LightAnalysis("RightRegion","Light",b2,b3,3.);
    myLightAnalysisRight->AddHandler(StupidTwoDRight);
    LightAnalysis * myLightAnalysisLeft = new LightAnalysis("LeftRegion","Light",b1,b2,3.);
    myLightAnalysisLeft->AddHandler(StupidTwoDLeft);
    
    LightAnalysis * myLepAnalysis = new LightAnalysis("Global","LepB",-1.,10000.,3.);
    LightAnalysis * myLepAnalysisRight = new LightAnalysis("RightRegion","LepB",b2,b3,3.);
    LightAnalysis * myLepAnalysisLeft = new LightAnalysis("LeftRegion","LepB",b1,b2,3.);
    
    LightStudyAnalysisHandler myAnalysis(string(anaName),/*doBtag*/false,/*dataLike*/ false,
    /*extJet*/true ,Luminosity,myMassResolution,myElecCuts,myJetCuts,"minChi2",100000., 0.,/*othreTt*/false);
    myAnalysis.AddAnalysis(myLightAnalysisRight);
    myAnalysis.AddAnalysis(myLightAnalysisLeft);
    myAnalysis.AddAnalysis(myLightAnalysis);
    myAnalysis.AddAnalysis(myLepAnalysis);
    myAnalysis.AddAnalysis(myLepAnalysisLeft);
    myAnalysis.AddAnalysis(myLepAnalysisRight);
//    myAnalysis.setVerbosity(0);
//    myAnalysis.setChi2Cut(100.);
//    myAnalysis.setTopPtCut(200.);

    myAnalysis.setVerbosity(0);
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
            myAnalysis.Analyze(pracEvt,weight,doJES);
//            if(i == 100)
//                break;
        }
    }
    double R_nRW = myLightAnalysisRight->getIntegral(1);
    double R_RW = myLightAnalysisRight->getIntegral((myLightAnalysisRight->handlers.size() - 1));
    double L_nRW =  myLightAnalysisLeft->getIntegral(1);
    double L_RW =   myLightAnalysisLeft->getIntegral((myLightAnalysisLeft->handlers.size() - 1));
    cout<<"\tLight Integral Right : "<< R_nRW<<endl;
    cout<<"\tWeighed Light Integral Right: "<<R_RW<<endl;
    cout<<"\tLight Integral Left : "<< L_nRW<<endl;
    cout<<"\tWeighed Light Integral Left: "<<L_RW<<endl;
    cout<<"Fdata_NoRW:\n\t"<<(double)L_nRW/(double)R_nRW<<endl;
    cout<<"Fdata_RW:\n\t"<<(double)L_RW/(double)R_RW<<endl;

    double MCleftTot = myLepAnalysisLeft->getIntegral(1);
    double MCleftB = myLepAnalysisLeft->handlers.at(1)->GetEffH1(0)->Integral();

    double MCrightTot = myLepAnalysisRight->getIntegral(1);
    double MCrightB = myLepAnalysisRight->handlers.at(1)->GetEffH1(0)->Integral();

    cout<<"Fmc:\n\t"<<(double)(MCleftTot - MCleftB)/(double)(MCrightTot - MCrightB)<<endl;

//    cout<<"\tLep Integral : "<< myLepAnalysis->getIntegral(1)<<endl;
//    cout<<"\tLight Integral : "<< myLightAnalysis->getIntegral(1)<<endl;
//    cout<<"\tWeighed Light Integral : "<< myLightAnalysis->getIntegral((myLightAnalysis->handlers.size() - 1))<<endl;
    myAnalysis.End();
    
    return 0;
};


