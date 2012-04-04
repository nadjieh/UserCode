/* 
 * File:   HistogramCreator.C
 * Author: nadjieh
 *
 * Created on March 12, 2012, 2:51 PM
 */
//same as SelectAndSave with less complexities. Aimed to run on selected samples.


#include "../../interface/ElectronSelector.h"

#include "../../interface/Event.h"

#include "../../interface/ElectronHists.h"
#include "../../interface/MuonHists.h"
#include "../../interface/PVHists.h"
#include "../../interface/JetHists.h"
#include "../../interface/JetSelector.h"
#include "../../interface/MuonVetoSelector.h"
#include "../../interface/MetHists.h"
#include "../../interface/PrimaryVertexSelector.h"

#include "../../../PhysicsObjects/interface/SemiLepTopQuark.h"

#include "../../../../TopBrussels/TopTreeProducer/interface/TRootMuon.h"
#include "../../../../TopBrussels/TopTreeProducer/interface/TRootElectron.h"
#include "../../../../TopBrussels/TopTreeProducer/interface/TRootJet.h"
#include "../../../../TopBrussels/TopTreeProducer/interface/TRootCaloJet.h"
#include "../../../../TopBrussels/TopTreeProducer/interface/TRootPFJet.h"
#include "../../../../TopBrussels/TopTreeProducer/interface/TRootMET.h"
#include "../../../../TopBrussels/TopTreeProducer/interface/TRootGenEvent.h"
#include "../../../../TopBrussels/TopTreeProducer/interface/TRootNPGenEvent.h"
#include "../../../../TopBrussels/TopTreeProducer/interface/TRootEvent.h"
#include "../../../../TopBrussels/TopTreeProducer/interface/TRootRun.h"
#include "../../../../TopBrussels/TopTreeProducer/interface/TRootParticle.h"
#include "../../../../TopBrussels/TopTreeProducer/interface/TRootMCParticle.h"
#include "../../../../TopBrussels/TopTreeProducer/interface/TRootVertex.h"
#include "../../../../TopBrussels/TopTreeProducer/interface/TRootHLTInfo.h"
#include "../../../../AnalysisClasses/EventSelection/interface/PracticalEvent.h"
#include "../../../../TopBrussels/TopTreeAnalysis/MCInformation/interface/Lumi3DReWeighting.h"




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
#include <vector>
using namespace std;
using namespace TopTree;
/*
 * 
 */
int main(int argc, char** argv) {
    PVHists atLeastOnGPV("final_PV");
    JetHists Jets("final_Jet",2);
    JetHists BJets("final_BJet",2);
    MuonHists GoldenFinalMuons("final_Muon");
    MetHists MetHist("finalMet");
    TH1D * finalMT = new TH1D("finalMT","final-W-neutrino transverse mass",100, 0.,200.);
    finalMT->GetXaxis()->SetTitle("M_{T}(W,#nu)");
    TH1D * Wmass = new TH1D("Wmass","final-W-mass",100, 0.,200.);
    Wmass->GetXaxis()->SetTitle("M_{W}");
    TH1D * topMass = new TH1D("topMass","final-top-mass",100, 50.,250.);
    topMass->GetXaxis()->SetTitle("M_{top}");
    TH1D * cosTheta = new TH1D("cosTheta","cos(#theta)",50, -1.,1.);
    cosTheta->GetXaxis()->SetTitle("cos(#theta*)");
    std::vector<std::string> inputFileNames;
    std::string plotFileName;
    int verbosity = 0;
    TH1D * METResolutions = 0;
    std::string HLTname = "HLT_IsoMu17_v*";
    bool pu3D = true;
    string PUWeightFileName="";
    double XSec = 1; double Luminosity = 1; double PreSelEff = 1; double doJES = 1;
    bool isData = false;
    for (int f = 1; f < argc; f++) {
        std::string arg_fth(*(argv + f));

        if (arg_fth == "out") {
          f++;
          std::string out(*(argv + f));
	  plotFileName = out;
        }else if (arg_fth == "input") {
          f++;
          std::string in(*(argv + f));
          inputFileNames.push_back(string("~/work/samples/"+in));
        }else if(arg_fth == "XSec"){
          f++;
          std::string Xsec(*(argv + f));
          XSec = atof(Xsec.c_str());
        }else if(arg_fth == "Lumi"){
          f++;
          std::string Lumi(*(argv + f));
          Luminosity = atof(Lumi.c_str());
        }else if(arg_fth == "preSelEff"){
          f++;
          std::string preSelEff(*(argv + f));
          PreSelEff = atof(preSelEff.c_str());
        }else if (arg_fth == "JES") {
            f++;
            std::string in(*(argv + f));
           doJES = atof(in.c_str());
        }else if (arg_fth == "isData") {
            f++;
            std::string in(*(argv + f));
            if(in == "yes" || in == "YES" || in == "Yes" || in == "y" || in == "Y")
		isData = true;
	    else
		isData = false;
        }else if (arg_fth == "METResolFileName") {
            f++;
            std::string in(*(argv + f));
            TFile * METResolFileName = TFile::Open(in.c_str());
            METResolutions = (TH1D*) METResolFileName->Get("METresolutions");
        }else if (arg_fth == "HLTname") {
            f++;
            std::string in(*(argv + f));
            HLTname = in;
            std::cout<<HLTname<<endl;
        }else if (arg_fth == "PUWeightFileName") {
            f++;
            std::string in(*(argv + f));
            PUWeightFileName = in;
            std::cout<<HLTname<<endl;
        }
    }
    
    TFile* f = 0;
    TApplication theApp("App", &argc, argv);
    int nInit = 0;
    int nFinal = 0;
    int nHLTrunB = 0;
    int nMt = 0;
    Lumi3DReWeighting Lumi3DWeights = 
    Lumi3DReWeighting("../../../../TopBrussels/TopTreeAnalysis/macros/PileUpReweighting/pileup_MC_Flat10PlusTail.root",
    "../../../../TopBrussels/TopTreeAnalysis/macros/PileUpReweighting/pileup_FineBin_2011Data_UpToRun180252.root", "pileup", "pileup");
    Lumi3DWeights.setWFileName(PUWeightFileName);
    Lumi3DWeights.weight3D_init(1.0);
    for(unsigned int fNumber = 0; fNumber<inputFileNames.size(); fNumber++){
        cout<<"file number "<<fNumber+1<<": "<<inputFileNames.at(fNumber)<<endl;
        f = TFile::Open(inputFileNames.at(fNumber).c_str());
        
        TTree* runTree = (TTree*) f->Get("runTree");
        TTree* eventTree = (TTree*) f->Get("eventTree");
        
        PracticalEvent * pracEvt = new PracticalEvent(eventTree,runTree);
        pracEvt->eventTree->SetBranchStatus("*", 1);

        std::cout<<"beforeLoop"<<std::endl;

        int ievt = 0;
        
        while (pracEvt->Next()) {
            nInit++;
//
//            if(ievt > 10)
//                break;
            double lumiWeight3D = 1;
            if(pu3D){


                if(!isData){
        //            cout<<"here I am ... "<<pracEvt->Event()<<endl;
                    lumiWeight3D = Lumi3DWeights.weight3D(pracEvt->Event());
                } else lumiWeight3D = 1;
            }
//            cout<<lumiWeight3D<<endl;
            ievt++;
            if(verbosity > 0)
                cout<<"*******************************************************************"<<endl;

            std::vector<TRootPFJet>  myJets_;
            myJets_.clear();
//            cout<<"I am going to Jet Correction "<<isData<<endl;
            myJets_ = pracEvt->ScaledPFJetCollection(1,isData);
//            Event myEvent_tmp( myJets_, *pracEvt->ElectronCollection()
//            ,*pracEvt->METCollection(),*pracEvt->MuonCollection(),*pracEvt->VertexCollection());
            //Sweitch to typeIMET
//            cout<<"Bare MET: "<<((TRootMET*)(pracEvt->METCollection()->At(0)))->Pt()<<endl;
//            cout<<"TypeI Corr MET: "<<pracEvt->TypeICorrMET().Pt()<<endl;
            Event myEvent_tmp( myJets_, *pracEvt->ElectronCollection()
            ,pracEvt->TypeICorrMET(),*pracEvt->MuonCollection(),*pracEvt->VertexCollection());
            if(verbosity > 0)
                cout<<"PV size: "<<myEvent_tmp.pvs.size()<<"\n"
                    <<"Muon size: "<<myEvent_tmp.muons.size()<<"\n"
                    <<"Electron size: "<<myEvent_tmp.electrons.size()<<"\n"
                    <<"Jet size: "<<myEvent_tmp.PFJets.size()<<"\n"<<endl;
            myEvent_tmp.verbose(verbosity);
            if(verbosity > 0)
                cout<<"ScrapFilterMaker-------------------------------------------------------------------"<<endl;
            double scrapFilterer = (double)(pracEvt->Event()->nHighPurityTracks())/(double)(pracEvt->Event()->nTracks());
            if(verbosity > 0)
                cout<<"HBHEnoiseFilterMaker-------------------------------------------------------------------"<<endl;//?????
            if(verbosity > 0)
                cout<<"Vertex Makers ---------------------------------------------------------------------"<<endl;
            myEvent_tmp.VertexMaker();
            if(verbosity > 0)
                cout<<"Electron Maker ---------------------------------------------------------------------"<<endl;
            myEvent_tmp.ElectronMaker();
            /*pt = 30., eta = 2.5,  Exc_Low = 1.4442 , Exc_High = 1.5660, Id = "VBTF70", IdSecond = "VBTF95" (not applied),
             * D0 = 0.02, IsoCut = 0.125, drToPV = 10000.,  secondEIso = 0.2, secPt=15 GeV 
             */
            
                  
            if(verbosity > 0)
                cout<<"Jet Makers ---------------------------------------------------------------------"<<endl;
            myEvent_tmp.PFJetMaker(/*bTagAlgo*/"TCHP",/*pt*/30.,/*eta*/4.5);
            if(verbosity > 0)
                cout<<"Muon Maker ---------------------------------------------------------------------"<<endl;
            myEvent_tmp.MuonMaker();
            /*
             * pt = 20.,  eta = 2.1, chi2 = 10,  D0 = 0.02,  nvh = 10, isoCut_ = 0.15,  doGL = false,  
             * nPixWithMeasuredHits = 1,  nSegM = 1
             */
            if(verbosity > 0)
                cout<<"START TO SELECT : "<<endl;
            if(scrapFilterer > 0.2){
                if(verbosity>0)
                    cout<<"\tPassed!! scrapFilterer is "<<scrapFilterer<<endl;
            }else
                continue;

            TopTree::TRootHLTInfo hltInfo = pracEvt->RunInfo()->getHLTinfo(pracEvt->Event()->runId());
            int trigID = hltInfo.hltPath(HLTname);

            if(pracEvt->Event()->trigHLT(trigID)){
		nHLTrunB++;
                if(verbosity > 0){
                    cout<<hltInfo.hltNames(trigID)<<"\t"<<hltInfo.hltWasRun(trigID)<<
                    "\t"<<hltInfo.hltAccept(trigID)<<endl;
                    cout<<"\tHLT is passed"<<endl;
                }
            }else 
                continue;
            
            if(myEvent_tmp.Gpvs.size() > 0){
                if(verbosity > 0)
                    cout<<"\tPVCut Passed"<<endl;
            } else
                continue;

            if(myEvent_tmp.Dmuons.size() == 1){
                if(verbosity > 0)
                    cout<<"\tMu selection Passed"<<endl;
            } else
                continue;

            if(myEvent_tmp.looseMuons.size()==0){
                if(verbosity > 0)
                    cout<<"\tlooseMuVeto is passed"<<endl;
            }else 
                continue;

            if(myEvent_tmp.Gelectrons.size()==0 && myEvent_tmp.Secondelectrons.size()==0){
                if(verbosity > 0)
                    cout<<"\tlooseEVeto is passed"<<endl;
            }else 
                continue;

            if(myEvent_tmp.GPFJets.size() == 2){		
                if(verbosity > 0){
                        cout<<"\t==2 Jet Passed"<<endl;
                }
            } else
                continue;
            double mt = 0;
            double metT = sqrt((myEvent_tmp.mets.at(0).Px()*myEvent_tmp.mets.at(0).Px())+
                            (myEvent_tmp.mets.at(0).Py()*myEvent_tmp.mets.at(0).Py()));

            double muT =  sqrt((myEvent_tmp.Dmuons.at(0).Px()*myEvent_tmp.Dmuons.at(0).Px())+
                            (myEvent_tmp.Dmuons.at(0).Py()*myEvent_tmp.Dmuons.at(0).Py()));
            mt = sqrt(pow(muT+metT,2) - pow(myEvent_tmp.mets.at(0).Px()+myEvent_tmp.Dmuons.at(0).Px(),2)
                                                - pow(myEvent_tmp.mets.at(0).Py()+myEvent_tmp.Dmuons.at(0).Py(),2));
            if(mt>40){
                nMt++;
                if(verbosity>0)
                    cout<<"\tM_T cut is passed"<<endl;
            }else
                continue;

            if(myEvent_tmp.BPFJets.size() == 1){
                if(verbosity > 0)
                    cout<<"\t== 1bTag Passed"<<endl;
            } else
                continue;
            nFinal++;
            
            int mySecondJetIndex = 0;
            if(mySecondJetIndex == myEvent_tmp.firstBtagIndex)
                mySecondJetIndex = 1;
            
            //Reweighting process
            SemiLepTopQuark myLeptonicTop(myEvent_tmp.BPFJets.at(0),myEvent_tmp.mets.at(0),myEvent_tmp.Dmuons.at(0),
                    myEvent_tmp.GPFJets.at(mySecondJetIndex),METResolutions);

            atLeastOnGPV.Fill(myEvent_tmp.Gpvs,myEvent_tmp.Gpvs.size(),lumiWeight3D);
            GoldenFinalMuons.Fill(myEvent_tmp.Dmuons,myEvent_tmp.Dmuons.size(),lumiWeight3D);
            Jets.FillPFJets(myEvent_tmp.GPFJets,myEvent_tmp.GPFJets.size(),myEvent_tmp.BPFJets.size(),false,lumiWeight3D);
            BJets.FillPFJets(myEvent_tmp.BPFJets,myEvent_tmp.BPFJets.size(),myEvent_tmp.BPFJets.size(),false,lumiWeight3D);
            MetHist.Fill(&myEvent_tmp.mets.at(0),lumiWeight3D);
            finalMT->Fill(mt,lumiWeight3D);
            cosTheta->Fill(myLeptonicTop.cosThetaStar(),lumiWeight3D);
            Wmass->Fill(myLeptonicTop.W().M(),lumiWeight3D);
            topMass->Fill(myLeptonicTop.top().M(),lumiWeight3D);
            

        }

        cout<<"before closing file input "<<f->GetName()<<endl;
        f->Close();
        delete f;

    }
    cout<<"before endjob"<<endl;
    TFile * fout = new TFile(plotFileName.c_str(),"recreate");
    fout->cd();
    atLeastOnGPV.WriteAll(fout);
    GoldenFinalMuons.WriteAll(fout);
    Jets.WriteAll(fout);
    BJets.WriteAll(fout);
    MetHist.WriteAll(fout);  
    finalMT->Write();
    cosTheta->Write();
    Wmass->Write();
    topMass->Write();
    fout->Write();
    fout->Close();
    
    cout<<nInit<<"\n"<<nHLTrunB<<"\n"<<nMt<<"\n"<<nFinal<<endl;
    return 0;
}

