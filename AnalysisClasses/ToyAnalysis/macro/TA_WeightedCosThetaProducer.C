/*
 * Aimed to run on selected events
 * 
 */
/* 
 * File:   SelectAndSave.c
 * Author: ajafari
 *
 * Created on January 29, 2012, 8:18 PM
 */

#include "../../EventSelection/interface/ElectronSelector.h"

#include "../../EventSelection/interface/Event.h"

#include "../../EventSelection/interface/ElectronHists.h"
#include "../../EventSelection/interface/MuonHists.h"
#include "../../EventSelection/interface/PVHists.h"
#include "../../EventSelection/interface/JetHists.h"
#include "../../EventSelection/interface/JetSelector.h"
#include "../../EventSelection/interface/MuonVetoSelector.h"

#include "../../EventSelection/interface/PrimaryVertexSelector.h"

#include "../../../TopBrussels/TopTreeProducer/interface/TRootMuon.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootElectron.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootJet.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootCaloJet.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootPFJet.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootMET.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootGenEvent.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootNPGenEvent.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootEvent.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootRun.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootParticle.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootMCParticle.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootVertex.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootHLTInfo.h"
#include "../../../AnalysisClasses/EventSelection/interface/PracticalEvent.h"
#include "../../PhysicsObjects/interface/SemiLepTopQuark.h"
#include "../interface/GenSingleTopMaker.h"
#include "../interface/CosThetaWeighter.h"
#include "../interface/CosThetaWeightHandler.h"
#include "../interface/DataPointsChiSquared.h"
#include "../../../TopBrussels/TopTreeAnalysis/MCInformation/interface/Lumi3DReWeighting.h"




#include <sstream>
#include <string>

#include <TApplication.h>
#include <TFile.h>
#include <TH1.h>
#include <TH2.h>
#include <TCanvas.h>
#include <TBranch.h>
#include <TTree.h>
#include <TSystem.h>
#include <TGraph.h>
#include <map>
#include <vector>

using namespace std;
using namespace TopTree;




    


    
pair <std::vector<TH1D*> , TGraph*>WeightsLoader(TFile * f){
    std::vector<TH1D*> Ws;
    TGraph * g;
    TList * l = f->GetListOfKeys();
    for(int i = 0; i< l->GetSize(); i++){
//        if(string(l->At(i)->GetName()) == "fvarValues" || string(l->At(i)->GetName()) == "fvarValuesG")
//            continue;
        if( string(l->At(i)->GetName()) == "fvarValuesG")
            g = (TGraph*)f->Get(l->At(i)->GetName());
        else
            Ws.push_back((TH1D*)f->Get(l->At(i)->GetName()));
    }
    cout<<Ws.size()<<endl;
    return make_pair(Ws,g);
}
int main(int argc, char** argv){
//    sleep(60);
    double doJES = 1.;
    int nSteps;
    double f0;
    double fminus;
    bool f0Fixed = false;
    bool fminusFixed = true;
    string weightFileName;
    bool pu3D = false;//true;
    double toy_weight = 1;
    double XSec;
    double Luminosity;
    double initial;

    int toy_verbosity = 0;
    TH1D * METResolutions;

    TFile * toy_out;
    TTree * eventTree_f;
    TTree * runTree_f;
    std::string PUWeightFileName;

    std::vector<std::string> toy_inputFileNames;
    std::vector<double> toy_Xsecs;
    std::vector<double> toy_initials;
    std::vector<bool> toy_isData;
    std::vector<bool> toy_realWtb;
    std::string toy_outFileName;
    std::string toy_plotFileName;
    std::string toy_outFileName_FullSelection;
    int SmearingSkim = 1;
    for (int f = 1; f < argc; f++) {
        std::string arg_fth(*(argv + f));
        if (arg_fth == "out") {
          f++;
          std::string out(*(argv + f));
          toy_outFileName_FullSelection = string(out+".root");
	  toy_plotFileName = out;
        }else if(arg_fth == "Lumi"){
          f++;
          std::string Lumi(*(argv + f));
          Luminosity = atof(Lumi.c_str());
        }else if (arg_fth == "METResolFileName") {
            f++;
            std::string in(*(argv + f));
            TFile * METResolFileName = TFile::Open(in.c_str());
            METResolutions = (TH1D*) METResolFileName->Get("METresolutions");
        }else if (arg_fth == "nSteps") {
          f++;
          std::string in(*(argv + f));
          nSteps = (int)atof(in.c_str());
        }else if (arg_fth == "f0") {
          f++;
          std::string in(*(argv + f));
          f0 = atof(in.c_str());
        }else if (arg_fth == "fminus") {
          f++;
          std::string in(*(argv + f));
          fminus = atof(in.c_str());
        }else if (arg_fth == "isFixed") {
          f++;
          std::string in(*(argv + f));
          if(in == string("f0")){
              f0Fixed = true;
              fminusFixed = false;
          }else if(in == string("fminus")){
              f0Fixed = false;
              fminusFixed = true;
          }
        }else if(arg_fth == "WeightFile"){
          f++;
          std::string in(*(argv + f));
          weightFileName = in;            
        }else if (arg_fth == "JES") {
            f++;
            std::string in(*(argv + f));
           doJES = atof(in.c_str());
        }else if (arg_fth == "input") {
          f++;
          std::string in(*(argv + f));
          toy_inputFileNames.push_back(string("~/"+in));
        }else if(arg_fth == "XSec"){
          f++;
          std::string Xsec(*(argv + f));
          toy_Xsecs.push_back(atof(Xsec.c_str()));
        }else if(arg_fth == "Initial"){
          f++;
          std::string in(*(argv + f));
          toy_initials.push_back(atof(in.c_str()));
        }else if (arg_fth == "isData") {
            f++;
            std::string in(*(argv + f));
            if(in == "yes" || in == "YES" || in == "Yes" || in == "y" || in == "Y")
		toy_isData.push_back( true);
	    else
		toy_isData.push_back( false);
        }else if (arg_fth == "hasWtb") {
            f++;
            std::string in(*(argv + f));
            if(in == "yes" || in == "YES" || in == "Yes" || in == "y" || in == "Y")
		toy_realWtb.push_back( true);
	    else
		toy_realWtb.push_back( false);
        }else if (arg_fth == "PUWeightFileName") {
            f++;
            std::string in(*(argv + f));
            PUWeightFileName = in;
        }else if (arg_fth == "SmearingSkim") {
            f++;
            std::string in(*(argv + f));
            SmearingSkim = atof(in.c_str());
        }
    }
//    cout<<doJES<<endl;
    cout << weightFileName << endl;
    TClonesArray* corrMET = 0;
    TApplication theApp("App", &argc, argv);
    TH1D * cosTheta = new TH1D("cosTheta","cos(#theta)",1000, -1, 1 );
    cosTheta->Sumw2();
    CosThetaWeightHandler myHandler(f0,fminus,f0Fixed,fminusFixed,nSteps);
    Lumi3DReWeighting Lumi3DWeights;
    if(pu3D){
////        Lumi3DWeights.weight3D_set("../../../../TopBrussels/TopTreeAnalysis/macros/PileUpReweighting//MC_Fall11.root",
////    "../../../../TopBrussels/TopTreeAnalysis/macros/PileUpReweighting/RunAB.root", "pileup", "pileup");
//        Lumi3DWeights.weight3D_set("../../../../TopBrussels/TopTreeAnalysis/macros/PileUpReweighting//MC_Fall11.root",
//    "../../../../TopBrussels/TopTreeAnalysis/macros/PileUpReweighting/pileup_2011Data_finebin_true.root", "pileup", "pileup");
//        Lumi3DWeights.setWFileName(PUWeightFileName);
//        Lumi3DWeights.weight3D_init(1.0);
        Lumi3DWeights.weight3D_init(PUWeightFileName);
    }
//    CosThetaWeightHandler myHandler(WeightsLoader(TFile::Open(weightFileName.c_str())));
    myHandler.setName(toy_plotFileName);
    std::vector<TH1D*> cosThetaRW;
    for(int i = 0; i<=nSteps; i++){
        stringstream d;
        d<<"cosThetaRW_"<<i;
        cosThetaRW.push_back(new TH1D(d.str().c_str(),d.str().c_str(),1000, -1,1));
        cosThetaRW.at(cosThetaRW.size()-1)->Sumw2();
    }
    if(toy_inputFileNames.size() != toy_Xsecs.size()){
        cout<<"ERROR: Bad file-Xsec assignment!!!"<<endl;
        return 2;
    }
    if(toy_inputFileNames.size() != toy_initials.size()){
        cout<<"ERROR: Bad file-initial assignment!!!"<<endl;
        return 2;
    }
    if(toy_inputFileNames.size() != toy_isData.size()){
        cout<<"ERROR: Bad file-isData assignment!!!"<<endl;
        return 2;
    }
    TFile * f = 0;
    for(unsigned int fNumber = 0; fNumber<toy_inputFileNames.size(); fNumber++){
        bool isData = toy_isData.at(fNumber);
        bool hasWtb = toy_realWtb.at(fNumber);
        f = TFile::Open(toy_inputFileNames.at(fNumber).c_str());
        cout<<"File: "<<toy_inputFileNames.at(fNumber)<<endl;
        cout<<"\tcross section: "<<toy_Xsecs.at(fNumber)<<endl;
        cout<<"\tinitial: "<<toy_initials.at(fNumber)<<endl;
        double lumiWeight3D = (double)(toy_Xsecs.at(fNumber)*Luminosity)/(double)toy_initials.at(fNumber);
        if(isData)
            lumiWeight3D = 1;
        cout<<"\tweight: "<<lumiWeight3D<<endl;
        
        if(isData)
            cout<<"\ta data file"<<endl;
        else
            cout<<"\ta mc file"<<endl;

        TTree* runTree = (TTree*) f->Get("runTree");
        TTree* eventTree = (TTree*) f->Get("eventTree");


        PracticalEvent * pracEvt = new PracticalEvent(eventTree,runTree);
        pracEvt->eventTree->SetBranchStatus("*", 1);

        std::cout<<"beforeLoop"<<std::endl;

        int ievt = 0;
        

        while (pracEvt->Next()) {

//            if(ievt > 100)
//                break;

            if(pu3D){
                if(!isData){
        //            cout<<"here I am ... "<<pracEvt->Event()<<endl;
                    lumiWeight3D *= Lumi3DWeights.weight3D(pracEvt->Event());
                } else lumiWeight3D = 1;
            }

            ievt++;
            if(toy_verbosity > 0)
                cout<<"*******************************************************************"<<endl;

            std::vector<TRootPFJet>  myJets_;
            myJets_.clear();


//            myJets_ = pracEvt->unCorrectedPFJetVector();
            myJets_ = pracEvt->ScaledPFJetCollection(doJES,isData);
//            Event myEvent_tmp( myJets_, *pracEvt->ElectronCollection()
//            ,*pracEvt->METCollection(),*pracEvt->MuonCollection(),*pracEvt->VertexCollection());
            Event myEvent_tmp( myJets_, *pracEvt->ElectronCollection()
            ,pracEvt->TypeICorrMET(),*pracEvt->MuonCollection(),*pracEvt->VertexCollection());
            
            if(toy_verbosity > 0)
                cout<<"PV size: "<<myEvent_tmp.pvs.size()<<"\n"
                    <<"Muon size: "<<myEvent_tmp.muons.size()<<"\n"
                    <<"Electron size: "<<myEvent_tmp.electrons.size()<<"\n"
                    <<"Jet size: "<<myEvent_tmp.PFJets.size()<<"\n"<<endl;
            myEvent_tmp.verbose(toy_verbosity);
                        
                       
            if(toy_verbosity > 0)
                cout<<"Jet Makers ---------------------------------------------------------------------"<<endl;
            myEvent_tmp.PFJetMaker(/*bTagAlgo*/"TCHP",/*pt*/30.,/*eta*/4.5);
            if(toy_verbosity > 0)
                cout<<"Muon Maker ---------------------------------------------------------------------"<<endl;
            myEvent_tmp.MuonMaker();
 
            int mySecondJetIndex = 0;
            if(mySecondJetIndex == myEvent_tmp.firstBtagIndex)
                mySecondJetIndex = 1;
            
            //Reweighting process
            SemiLepTopQuark myLeptonicTop(myEvent_tmp.BPFJets.at(0),myEvent_tmp.mets.at(0),myEvent_tmp.Dmuons.at(0),
                    myEvent_tmp.GPFJets.at(mySecondJetIndex),METResolutions);
            cosTheta->Fill(myLeptonicTop.cosThetaStar(SmearingSkim),lumiWeight3D);
            if(!isData) {
                double W = lumiWeight3D;
//                cout<<W<<endl;
                for(int step = 0; step <= nSteps; step++){
                    if(hasWtb)
//                        W = myHandler.getCosThetaWeight(myLeptonicTop.cosThetaStar(),step)*lumiWeight3D;
                        W = myHandler.getCosThetaWeightFunc(myLeptonicTop.cosThetaStar(SmearingSkim),step)*lumiWeight3D;
//                    cout<<W<<endl;
                    cosThetaRW.at(step)->Fill(myLeptonicTop.cosThetaStar(SmearingSkim),W);
                }
            }
        }
        f->Close();
        delete f;
    }
    cout<<"before endjob"<<endl;
    TFile * myFile = new TFile(string("cosTheta_"+toy_plotFileName).c_str(), "recreate");
    myFile->cd();
    cosTheta->Write();
    myFile->mkdir("CosThetaRW")->cd();
    for(int step = 0; step <= nSteps; step++){
        cosThetaRW.at(step)->Write();
    }
    myFile->cd();
    myFile->Write();
    myFile->Close();
    return 0;
}