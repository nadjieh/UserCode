#include "../../../../../AnalysisClasses/ChiSquared/interface/Combinator.h"
#include "../../../../../AnalysisClasses/ChiSquared/interface/TopEvent.h"
#include "../../../../../AnalysisClasses/ChiSquared/interface/LightStudyAnalysisHandler.h"
#include "../../../../../AnalysisClasses/ChiSquared/interface/LightStudyJetHandler.h"
#include "../../../../../AnalysisClasses/EventSelection/interface/PracticalEvent.h"
#include "../../../../../AnalysisClasses/EventSelection/interface/Event.h"
#include "../../../../../AnalysisClasses/EventSelection/interface/GoodObjects.h"
#include "../../../../../AnalysisClasses/ChiSquared/interface/TwoDWeightJetEffHandler.h"
#include "../../../../../AnalysisClasses/LightJets/interface/LightAnalysis.h"




#include<iostream>
#include "TFile.h"
#include "TTree.h"

using namespace std;
int main(int argc, char** argv){
    std::vector<std::pair<string, std::pair<int,int> > >  myFileWeights;
    std::vector<bool> IsTtBar;
    std::string anaName;
    std::vector<string> barenames;
    std::pair<std::string,std::pair<int , int > > inputNameWeight;
    inputNameWeight.first = "";
    inputNameWeight.second.first = 0.;
    inputNameWeight.second.second = -1.;
    bool isTtBar = false;
    
    MassAndResolution myMassResolution;
    myMassResolution.topMass = 180.6;
    myMassResolution.topRes = 3.462 ;
    myMassResolution.wMass =  88.76;
    myMassResolution.wRes = 10.73;

    double doJES = 1.;


    double b1 = 50.;
    double b2 = 160.;
    double b3 = 280.;
    
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
          if(in == "Signal.root" || in == "OtherTtBar.root" || in == "0.9/FS_Signal_0.9.root" ||
             in == "1.1/FS_Signal_1.1.root" ||in == "0.9/FS_OtherTt_0.9.root" ||in == "1.1/FS_OtherTt_1.1.root")
              isTtBar = true;
          IsTtBar.push_back(isTtBar);
          barenames.push_back(in);
          in ="/home/ajafari/rootfiles/TopTrees/7TeV/July10/Skimmed/FullSelection/FS_ECalDriven_"+in;
//          in ="/tmp/ajafari/FullSelection/FS_ECalDriven_"+in;
          inputNameWeight.first = in;
//          cout<<inputNameWeight.first<<endl;
        }else if(arg_fth == "nEvt"){
          f++;
          std::string Xsec(*(argv + f));
          inputNameWeight.second.first = (int)atof(Xsec.c_str()); //nEvt
        }else if(arg_fth == "startpoint"){
          f++;
          std::string Lumi(*(argv + f));
          inputNameWeight.second.second = (int)atof(Lumi.c_str()); // START
        }else if(arg_fth == "nextinput"){
          f++;
          myFileWeights.push_back(inputNameWeight);
          isTtBar = false;
          std::string in(*(argv + f));
          if(in == "Signal.root" || in == "OtherTtBar.root" || in == "0.9/FS_Signal_0.9.root" ||
             in == "1.1/FS_Signal_1.1.root" ||in == "0.9/FS_OtherTt_0.9.root" ||in == "1.1/FS_OtherTt_1.1.root")
              isTtBar = true;
          IsTtBar.push_back(isTtBar);
          barenames.push_back(in);
          in ="/home/ajafari/rootfiles/TopTrees/7TeV/July10/Skimmed/FullSelection/FS_ECalDriven_"+in;
          inputNameWeight.first = in;
//          cout<<inputNameWeight.first<<endl;
          inputNameWeight.second.first = 0.;
          inputNameWeight.second.second = -1.;
        }else if(arg_fth == "lastinput"){
          f++;
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
    if(myMassResolution.topMass == -1 ||myMassResolution.wRes == -1 ||myMassResolution.wMass == -1 ||myMassResolution.topRes == -1 )
        return -1;
//    cout<<myMassResolution.topMass <<"\t"<<myMassResolution.topRes<<"\t"<<myMassResolution.wMass<<"\t"<<myMassResolution.wRes<<endl;
//    cout<<b1 <<"\t"<<b2<<"\t"<<b3<<"\t"<<endl;
//
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

    LightAnalysis * myLightAnalysis = new LightAnalysis("Global","Light",-1.,10000.);
    myLightAnalysis->AddHandler(StupidTwoD);
    LightAnalysis * myLightAnalysisRight = new LightAnalysis("RightRegion","Light",b2,b3);
    myLightAnalysisRight->AddHandler(StupidTwoDRight);
    LightAnalysis * myLightAnalysisLeft = new LightAnalysis("LeftRegion","Light",b1,b2);
    myLightAnalysisLeft->AddHandler(StupidTwoDLeft);

    LightAnalysis * myLepAnalysis = new LightAnalysis("Global","LepB",-1.,10000.);
    LightAnalysis * myLepAnalysisRight = new LightAnalysis("RightRegion","LepB",b2,b3);
    LightAnalysis * myLepAnalysisLeft = new LightAnalysis("LeftRegion","LepB",b1,b2);

    LightStudyAnalysisHandler myAnalysis(string(anaName),/*doBtag*/false,/*dataLike*/ false,
    /*extJet*/true ,100,myMassResolution,myElecCuts,myJetCuts,"minChi2",100000., 0.,/*othreTt*/false);
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
        pracEvt->setInitialEventNumber(myFileWeights.at(nf).second.second);
        while (pracEvt->Next(myFileWeights.at(nf).second.second,myFileWeights.at(nf).second.second+myFileWeights.at(nf).second.first)){
            i++;
////            cout<<"event number : "<<i<<endl;
            myAnalysis.Analyze(pracEvt,1,1);
//            if(i == 100)
//                break;
        }
    }
    double R_nRW = myLightAnalysisRight->getIntegral(1);
    double R_RW = myLightAnalysisRight->getIntegral((myLightAnalysisRight->handlers.size() - 1));
    double L_nRW =  myLightAnalysisLeft->getIntegral(1);
    double L_RW =   myLightAnalysisLeft->getIntegral((myLightAnalysisLeft->handlers.size() - 1));
//    cout<<"\tLight Integral Right : "<< R_nRW<<endl;
//    cout<<"\tWeighed Light Integral Right: "<<R_RW<<endl;
//    cout<<"\tLight Integral Left : "<< L_nRW<<endl;
//    cout<<"\tWeighed Light Integral Left: "<<L_RW<<endl;
//    cout<<"Fdata_NoRW:\n\t"<<(double)L_nRW/(double)R_nRW<<endl;
      double Fdata_RW = (double)L_RW/(double)R_RW;
//    cout<<"Fdata_RW:\n\t"<<(double)L_RW/(double)R_RW<<endl;
//
    double MCleftTot = myLepAnalysisLeft->getIntegral(1);
    double MCleftB = myLepAnalysisLeft->handlers.at(1)->GetEffH1(0)->Integral();
//
    double MCrightTot = myLepAnalysisRight->getIntegral(1);
    double MCrightB = myLepAnalysisRight->handlers.at(1)->GetEffH1(0)->Integral();
//
    double Fmc = (double)(MCleftTot - MCleftB)/(double)(MCrightTot - MCrightB);
//
////    cout<<"\tLep Integral : "<< myLepAnalysis->getIntegral(1)<<endl;
////    cout<<"\tLight Integral : "<< myLightAnalysis->getIntegral(1)<<endl;
////    cout<<"\tWeighed Light Integral : "<< myLightAnalysis->getIntegral((myLightAnalysis->handlers.size() - 1))<<endl;
    myAnalysis.End();
//
      stringstream o;
    o<<" Fdata "<<Fdata_RW<<"   Fmc "<<Fmc<<"\t";
    for(unsigned int d = 0; d < myFileWeights.size(); d++){
        if(d == 0)
            o<<"input\t";
        else
            o<<"nextinput\t";
        o<<barenames.at(d)<<"\tnEvt "<<myFileWeights.at(d).second.first<<"\tstartpoint "<<myFileWeights.at(d).second.second<<"\t";
    }
    o<<"\tlastinput\n";
    cout<<o.str();
    return 0;
};


