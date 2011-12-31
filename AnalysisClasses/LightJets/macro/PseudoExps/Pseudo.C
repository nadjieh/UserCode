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
struct PsedoExps{
    int WJetsStartPoint;
    int WJetsNevt;
    int ZJetsStartPoint;
    int ZJetsNevt;
    int SingleTopSStartPoint;
    int SingleTopSNevt;
    int SingleTopTStartPoint;
    int SingleTopTNevt;
    int SingleTopTWStartPoint;
    int SingleTopTWNevt;
    int VqqStartPoint;
    int VqqNevt;
    int SignalStartPoint;
    int SignalNevt;
    int OtherTtStartPoint;
    int OtherTtNevt;
    double Fdata;
    double Fmc;
};

int main(int argc, char** argv){
//    std::vector<string>  myFileWeights;
//    std::vector<bool> IsTtBar;
//    std::string anaName;
//
//    std::string address = "/home/ajafari/rootfiles/TopTrees/7TeV/July10/Skimmed/FullSelection/FS_ECalDriven_";
//    myFileWeights.push_back(string(address+"Signal.root"));
//    IsTtBar.push_back(true);
//    myFileWeights.push_back(string(address+"OtherTtBar.root"));
//    IsTtBar.push_back(true);
//    myFileWeights.push_back(string(address+"SingleTopS.root"));
//    IsTtBar.push_back(false);
//    myFileWeights.push_back(string(address+"SingleTopT.root"));
//    IsTtBar.push_back(false);
//    myFileWeights.push_back(string(address+"SingleTopTW.root"));
//    IsTtBar.push_back(false);
//    myFileWeights.push_back(string(address+"Vqq.root"));
//    IsTtBar.push_back(false);
//    myFileWeights.push_back(string(address+"WJets.root"));
//    IsTtBar.push_back(false);
//    myFileWeights.push_back(string(address+"ZJets.root"));
//    IsTtBar.push_back(false);
//
//
//    double b1 = 50.;
//    double b2 = 160.;
//    double b3 = 280.;
//
//    double extFdata = -1.;
//    std::vector<PsedoExps> PEs;
//    PEs.clear();
//    for (int f = 1; f < argc; f++) {
//        PsedoExps myPE;
//        std::string arg_fth(*(argv + f));
////        cout<<"-------- "<< arg_fth<<endl;
//        if (arg_fth == "Fdata") {
//          f++;
//          std::string out(*(argv + f));
//          myPE.Fdata = atof(out.c_str());
//        }else if (arg_fth == "Fmc") {
//          f++;
//          std::string out(*(argv + f));
//          myPE.Fmc = atof(out.c_str());
//        }else if (arg_fth == "Signal") {
//          f++;
//          for(int p = f; p<f+3; p++){
//              string t(*(argv + p));
//              if(t == "nEvt"){
//                  p++;
//                  std::string out(*(argv + p));
//                  myPE.SignalNevt = (int)atof(out.c_str());
//              } else if(t == "startpoint"){
//                  p++;
//                  std::string out(*(argv + p));
//                  myPE.SignalStartPoint = (int)atof(out.c_str());
//              }
//          }
//        }else if (arg_fth == "OtherTtBar") {
//          f++;
//          for(int p = f; p<f+3; p++){
//              string t(*(argv + p));
//              if(t == "nEvt"){
//                  p++;
//                  std::string out(*(argv + p));
//                  myPE.OtherTtNevt = (int)atof(out.c_str());
//              } else if(t == "startpoint"){
//                  p++;
//                  std::string out(*(argv + p));
//                  myPE.OtherTtStartPoint = (int)atof(out.c_str());
//              }
//          }
//        }else if (arg_fth == "SingleTopS") {
//          f++;
//          for(int p = f; p<f+3; p++){
//              string t(*(argv + p));
//              if(t == "nEvt"){
//                  p++;
//                  std::string out(*(argv + p));
//                  myPE.SingleTopSNevt = (int)atof(out.c_str());
//              } else if(t == "startpoint"){
//                  p++;
//                  std::string out(*(argv + p));
//                  myPE.SingleTopSStartPoint = (int)atof(out.c_str());
//              }
//          }
//        }else if (arg_fth == "SingleTopT") {
//          f++;
//          for(int p = f; p<f+3; p++){
//              string t(*(argv + p));
//              if(t == "nEvt"){
//                  p++;
//                  std::string out(*(argv + p));
//                  myPE.SingleTopTNevt = (int)atof(out.c_str());
//              } else if(t == "startpoint"){
//                  p++;
//                  std::string out(*(argv + p));
//                  myPE.SingleTopTStartPoint = (int)atof(out.c_str());
//              }
//          }
//        }else if (arg_fth == "SingleTopTW") {
//          f++;
//          for(int p = f; p<f+3; p++){
//              string t(*(argv + p));
//              if(t == "nEvt"){
//                  p++;
//                  std::string out(*(argv + p));
//                  myPE.SingleTopTWNevt = (int)atof(out.c_str());
//              } else if(t == "startpoint"){
//                  p++;
//                  std::string out(*(argv + p));
//                  myPE.SingleTopTWStartPoint = (int)atof(out.c_str());
//              }
//          }
//        }else if (arg_fth == "Vqq") {
//          f++;
//          for(int p = f; p<f+3; p++){
//              string t(*(argv + p));
//              if(t == "nEvt"){
//                  p++;
//                  std::string out(*(argv + p));
//                  myPE.VqqNevt = (int)atof(out.c_str());
//              } else if(t == "startpoint"){
//                  p++;
//                  std::string out(*(argv + p));
//                  myPE.VqqStartPoint = (int)atof(out.c_str());
//              }
//          }
//        }else if (arg_fth == "WJets") {
//          f++;
//          for(int p = f; p<f+3; p++){
//              string t(*(argv + p));
//              if(t == "nEvt"){
//                  p++;
//                  std::string out(*(argv + p));
//                  myPE.WJetsNevt = (int)atof(out.c_str());
//              } else if(t == "startpoint"){
//                  p++;
//                  std::string out(*(argv + p));
//                  myPE.WJetsStartPoint = (int)atof(out.c_str());
//              }
//          }
//        }else if (arg_fth == "ZJets") {
//          f++;
//          for(int p = f; p<f+3; p++){
//              string t(*(argv + p));
//              if(t == "nEvt"){
//                  p++;
//                  std::string out(*(argv + p));
//                  myPE.ZJetsNevt = (int)atof(out.c_str());
//              } else if(t == "startpoint"){
//                  p++;
//                  std::string out(*(argv + p));
//                  myPE.ZJetsStartPoint = (int)atof(out.c_str());
//              }
//          }
//        }else if (arg_fth == "nextinput") {
//          PEs.push_back(myPE);
//        }else if (arg_fth == "out") {
//          f++;
//          std::string out(*(argv + f));
//          anaName = out;
//        }else if (arg_fth == "lastinput") {
//            break;
//        }
//    }
////    cout<<"out: "<<anaName<<endl;
////    for(unsigned int j = 0; j < PEs.size(); j++){
////        PsedoExps tmp = PEs.at(j);
////        cout<<"------ "<<j<<endl;
////        cout<<"Fdata: "<<tmp.Fdata<<endl;
////        cout<<"Fmc: "<<tmp.Fmc<<endl;
////        cout<<"Signal\tnEvt "<<tmp.SignalNevt<<"\tstartpoint "<<tmp.SignalStartPoint<<endl;
////        cout<<"OtherTt\tnEvt "<<tmp.OtherTtNevt<<"\tstartpoint "<<tmp.OtherTtStartPoint<<endl;
////        cout<<"SingleTopS\tnEvt "<<tmp.SingleTopSNevt<<"\tstartpoint "<<tmp.SingleTopSStartPoint<<endl;
////        cout<<"SingleTopT\tnEvt "<<tmp.SingleTopTNevt<<"\tstartpoint "<<tmp.SingleTopTStartPoint<<endl;
////        cout<<"SingleTopTW\tnEvt "<<tmp.SingleTopTWNevt<<"\tstartpoint "<<tmp.SingleTopTWStartPoint<<endl;
////        cout<<"Vqq\tnEvt "<<tmp.VqqNevt<<"\tstartpoint "<<tmp.VqqStartPoint<<endl;
////        cout<<"WJets\tnEvt "<<tmp.WJetsNevt<<"\tstartpoint "<<tmp.WJetsStartPoint<<endl;
////        cout<<"ZJets\tnEvt "<<tmp.ZJetsNevt<<"\tstartpoint "<<tmp.ZJetsStartPoint<<endl;
////    }
//    ElectronCuts myElecCuts;
//    myElecCuts.Pt = 30;
//    myElecCuts.eta = 2.4; myElecCuts.ExLow = 1.442; myElecCuts.ExHigh = 1.56;
//    myElecCuts.Id = "VBTF70"; myElecCuts.IdSecond = "VBTF95";
//    myElecCuts.IsoType = "";
//    myElecCuts.D0 = 0.02;
//    myElecCuts.IsoCut = 0.1;
//
//    JetCuts myJetCuts;
//    myJetCuts.bTagAlgo = "TCHE"; myJetCuts.Pt = 30.; myJetCuts.eta = 2.4;
//    myJetCuts.nCaloTower = 5;
//    myJetCuts.EmfUp = 0.9; myJetCuts.EmfLow = 0.05;
//    myJetCuts.fhpd = 1000.; myJetCuts.N90 = -1;
//    myJetCuts.bTagCut = 4.;
////
//    MassAndResolution myMassResolution;
//    myMassResolution.topMass = 180.6;
//    myMassResolution.topRes = 3.462;
//    myMassResolution.wMass = 88.76;
//    myMassResolution.wRes = 10.73;
//    if(myMassResolution.topMass == -1 ||myMassResolution.wRes == -1 ||myMassResolution.wMass == -1 ||myMassResolution.topRes == -1 )
//        return -1;
////
//    AnalysisHandler Fullanalysis("FullStudy",/*dobTag*/false,/*doBtagDataLike*/false,/*ExtJets*/true,/*Lumi*/100.,
//    myMassResolution,myElecCuts,myJetCuts,"minChi2");
//
//    for(unsigned int j = 0; j<PEs.size(); j++){
//        stringstream analysisPath; analysisPath<<"/home/ajafari/Pseudo_100/"<<j+1<<"/";
//        stringstream analysisName; analysisName<<"FdataData_"<<anaName<<"_"<<j+1;
//        DataAnalysis * myDataAnalysis = new DataAnalysis(analysisName.str(), b1, b2,b2,b3,/*chi2cut*/100000.,/*topPtcut*/0.,
//        /*doAntiTag*/false,/*AntiTagCut*/1000.);
//        myDataAnalysis->SetPath(analysisPath.str());
//        Fullanalysis.AddAnalysis(myDataAnalysis);
//    }
//    Fullanalysis.setVerbosity(0);
//    for(uint nf = 0; nf < myFileWeights.size(); nf++){
//        TFile * F = new TFile(myFileWeights.at(nf).c_str(),"read");
//        cout<<F->GetName()<<endl;
//        if(F == NULL)
//            cout<<"Bad file pointer"<<endl;
//        TTree* runTree = (TTree*) F->Get("runTree");
//        TTree* eventTree = (TTree*) F->Get("eventTree");
//        PracticalEvent * pracEvt = NULL;
//
//       if(IsTtBar.at(nf))
//            pracEvt = new PracticalEvent(eventTree,runTree,true);
//        else
//            pracEvt = new PracticalEvent(eventTree,runTree);
//       int initialEventNumber = -1;
//       int nEvt = -1;
//        for(unsigned int j = 0; j<PEs.size(); j++){
//           if(nf == 0){
//               initialEventNumber = PEs.at(j).SignalStartPoint;
//               nEvt = PEs.at(j).SignalNevt;
//           }else if(nf == 1){
//               initialEventNumber = PEs.at(j).OtherTtStartPoint;
//               nEvt = PEs.at(j).OtherTtNevt;
//           }else if(nf == 2){
//               initialEventNumber = PEs.at(j).SingleTopSStartPoint;
//               nEvt = PEs.at(j).SingleTopSNevt;
//           }else if(nf == 3){
//               initialEventNumber = PEs.at(j).SingleTopTStartPoint;
//               nEvt = PEs.at(j).SingleTopTNevt;
//           }else if(nf == 4){
//               initialEventNumber = PEs.at(j).SingleTopTWStartPoint;
//               nEvt = PEs.at(j).SingleTopTWNevt;
//           }else if(nf == 5){
//               initialEventNumber = PEs.at(j).VqqStartPoint;
//               nEvt = PEs.at(j).VqqNevt;
//           }else if(nf == 6){
//               initialEventNumber = PEs.at(j).WJetsStartPoint;
//               nEvt = PEs.at(j).WJetsNevt;
//           }else if(nf == 7){
//               initialEventNumber = PEs.at(j).ZJetsStartPoint;
//               nEvt = PEs.at(j).ZJetsNevt;
//           }
////           cout<<"\tnEvt: "<<nEvt<<"\tStartPoint: "<<initialEventNumber<<endl;
//           pracEvt->setInitialEventNumber(initialEventNumber);
//            int i = 0;
//            while (pracEvt->Next(initialEventNumber,initialEventNumber+nEvt)){
////                i++;
////                cout<<"event number : "<<initialEventNumber+i<<endl;
//                Fullanalysis.Analyze(pracEvt,1,1,j);
////                if(i == 10)
////                    break;
//            }
//            Fullanalysis.setAnalysisNonTrivialF(j+1,PEs.at(j).Fdata);
////            cout<<"\t\tFdata_RW = "<<Fullanalysis.f.at(j)<<endl;
//        }
//       delete eventTree;
//       delete runTree;
//       delete pracEvt;
//    }
//    Fullanalysis.ActivateSystem = true;
//    Fullanalysis.End();

    std::vector<double> MWPeff;
    std::vector<double> MWPerr;
    stringstream fname;
    double effBar = 0;
    TList * l4;
    TDirectory * d5;
    TDirectory * d4;
    TDirectory * d3;
    TList * l3;
    TDirectory * d2;
    TList * l2;
    TDirectory * d1;
    TList * l1;
    TFile * inputFile_;
    for(unsigned int j = 0; j<500/*PEs.size()*/; j++){
        fname.str("");
        fname<<"/home/ajafari/Pseudo_100/"<<j+1<<"/FullStudy_FdataData__"<<j+1<<"_minChi2.root";
        cout<<fname.str()<<endl;
        inputFile_ = TFile::Open(fname.str().c_str());
        l1 = inputFile_->GetListOfKeys();
	d1 = (TDirectory*)inputFile_->Get(l1->At(0)->GetName());
	l2 = d1->GetListOfKeys();
	d2 = (TDirectory*)d1->Get(l2->At(0)->GetName());
	l3 = d2->GetListOfKeys();
	d3 =  (TDirectory*)d2->Get(l3->At(8)->GetName());
	d4 =  (TDirectory*)d3->Get("Btag");
	d5 =  (TDirectory*)d4->Get("Integrated");
	l4 = d5->GetListOfKeys();
	TGraphAsymmErrors * tga = (TGraphAsymmErrors*)d5->Get(l4->At(4)->GetName());
        double y = 1000.;
	double x = 1000.;
	double minDif50 = 100000.;
	double xminDif50 = 1000.;
	double yminDif50 = 1000.;
        int i50 = -1999;
        for(int i = 400; i<520;i++){
            tga->GetPoint(i,x,y);
            if(fabs(y-0.50) < minDif50){
                    minDif50 = fabs(y-0.5);
                    xminDif50 = x;
                    yminDif50 = y;
                    i50 = i;
            }
            x = 1000;
            y = 1000;
        }
        cout<<fabs(yminDif50)<<endl;
        if(yminDif50 != 1000.){
            MWPeff.push_back(fabs(yminDif50));
            effBar += fabs(yminDif50);
            cout<<effBar<<endl;
            MWPerr.push_back(fabs(tga->GetErrorYhigh(i50)));
        }
        delete tga;
//        delete l4;
        delete d5;
        delete d4;
        delete d3;
//        delete l3;
        delete d2;
//        delete l2;
        delete d1;
        delete inputFile_;
//        delete l1;
    }
    effBar = (double)effBar/(double)MWPeff.size();
    cout<<effBar<<endl;
//    effBar = (double)effBar/(double)PEs.size();
    TH1D * err = new TH1D("err","err",500,0.,0.5);
    TH1D * eff = new TH1D("eff","eff",1000,0.,1.);
//    TH1D * Fdata = new TH1D("Fdata","Fdata",10000,0.,10.);
//    TH1D * Fmc = new TH1D("Fmc","Fmc",10000,0.,10.);
//    TH1D * relFerror = new TH1D("relFerror","relFerror",2000,-1.,1.);
    TH1D * pull = new TH1D("pull","pull",10000,-5.,5.);
    TFile * FinalOut = new TFile("FinalPE100_2.root","recreate");
    for(unsigned int j = 0; j<MWPeff.size()/*PEs.size()*/; j++){
        err->Fill(MWPerr.at(j));
        eff->Fill(MWPeff.at(j));
//        Fdata->Fill(PEs.at(j).Fdata);
//        Fmc->Fill(PEs.at(j).Fmc);
//        relFerror->Fill((double)(PEs.at(j).Fmc - PEs.at(j).Fdata)/(double)PEs.at(j).Fmc);
//        double p = fabs(MWPeff.at(j) - effBar);
        double p =  effBar - MWPeff.at(j);
        p = p/(double)MWPerr.at(j);
        pull->Fill(p);
    }
    FinalOut->cd();
    err->Write();
    eff->Write();
//    Fdata->Write();
//    Fmc->Write();
//    relFerror->Write();
    pull->Write();
    FinalOut->Write();
    FinalOut->Close();
    cout<<effBar<<endl;
    return 0;
};


