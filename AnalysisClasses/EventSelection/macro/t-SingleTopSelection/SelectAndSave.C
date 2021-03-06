/* 
 * File:   SelectAndSave.c
 * Author: ajafari
 *
 * Created on January 29, 2012, 8:18 PM
 */

#include "../../interface/ElectronSelector.h"

#include "../../interface/Event.h"

#include "../../interface/ElectronHists.h"
#include "../../interface/MuonHists.h"
#include "../../interface/PVHists.h"
#include "../../interface/JetHists.h"
#include "../../interface/JetSelector.h"
#include "../../interface/MuonVetoSelector.h"

#include "../../interface/PrimaryVertexSelector.h"

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


PVHists sin_atLeastOnGPV("before_PV_selection");
MuonHists sin_MuSelection("before_Mu_selection");
MuonHists sin_LMuVeto("before_LmuVeto_Selection");
ElectronHists sin_LEVeto("before_LeVeto_Selection");
JetHists sin_Jets("before_Jet_selection",2);
JetHists sin_BJets("before_BJet_selection",2);
MuonHists sin_AllFinalMuons("before_BJet_AllFinalMu");
MuonHists sin_GoldenFinalMuons("before_BJet_GoldenFinalMu");
JetHists sin_GoldenFinalJets("before_BJet_FinalGoldenFinalMu");





int sin_n0;
int sin_nScrapFilter;
bool sin_doScrapFilter;
int sin_nHCALnoiseFilter;
bool sin_doHCALnoiseFilter;
int sin_nHlt;
bool sin_doHLT;
int sin_nPV;
bool sin_doPV;
int sin_nMu;
bool sin_doMuon;
int sin_nNoLMu;
bool sin_doLMuVeto;
int sin_nNoLE;
bool sin_doLEVeto;
int sin_nConv_a;
int sin_nConv_b;
int  sin_nConv;
bool sin_doConv;
bool sin_doEcalDriven;
int sin_nEcalDriven;
int sin_nJet;
bool sin_dojet;
int sin_nMT ;
bool sin_doMT;
int sin_nBtag;
bool sin_doBtag;
double XSec;
double Luminosity;
double PreSelEff;
bool pu3D;
bool saveTypeIMET;

bool isData;
double sin_weight;

int sin_verbosity;
TH1D * MT;
TH1D * finalMT;

bool fillTree;
bool fillHists;
TFile * sin_out;
TTree * eventTree_f;
TTree * runTree_f;


std::vector<std::string> sin_inputFileNames;
std::string sin_outFileName;
std::string sin_plotFileName;
std::string sin_outFileName_FullSelection;

void beginJob(){
     sin_n0 = 0;
     sin_nScrapFilter = 0;
     sin_doScrapFilter = true;
     sin_nHCALnoiseFilter = 0;
     sin_doHCALnoiseFilter = true;
     sin_nHlt = 0;
     sin_doHLT = true;
     sin_nPV = 0;
     sin_doPV = true;//
     sin_nMu = 0;
     sin_doMuon = true;//
     sin_nNoLMu = 0;
     sin_doLMuVeto =  true;//
     sin_nNoLE = 0;
     sin_doLEVeto = true;//
     sin_doConv = false;// Specific to electron selection.
     sin_nConv_a= 0;
     sin_nConv_b= 0;
     sin_nEcalDriven = 0;
     sin_doEcalDriven =false;// Specific to electron selection.   
     sin_nJet= 0;
     sin_dojet = true;//
     sin_nMT = 0;
     sin_doMT = true;//
     sin_nBtag= 0;
     sin_doBtag = true;// Specific to electron selection.  
     sin_verbosity = 0;
     fillTree = true;//false;
     pu3D = false;
     fillHists = true;
     saveTypeIMET=true;
     MT = new TH1D("MT","W-neutrino transverse mass",100, 0.,200.);
     MT->GetXaxis()->SetTitle("M_{T}(W,#nu)");
     finalMT = new TH1D("finalMT","final-W-neutrino transverse mass",100, 0.,200.);
     finalMT->GetXaxis()->SetTitle("M_{T}(W,#nu)");
     
     sin_weight = 1;
}



void endJob(){
    TFile * plots = new TFile(sin_plotFileName.c_str(),"recreate");
    TH1D * CutFlowHist = new TH1D("CutFlow","",12,0,12);
    CutFlowHist->GetXaxis()->SetBinLabel(1,"Initial");
    CutFlowHist->GetXaxis()->SetBinLabel(2,"Scrap");
    CutFlowHist->GetXaxis()->SetBinLabel(3,"HBHE");
    CutFlowHist->GetXaxis()->SetBinLabel(4,"HLT");
    CutFlowHist->GetXaxis()->SetBinLabel(5,"primaryVertex");
    CutFlowHist->GetXaxis()->SetBinLabel(6,"mu-selection");
    CutFlowHist->GetXaxis()->SetBinLabel(7,"muonVeto");
    CutFlowHist->GetXaxis()->SetBinLabel(8,"elecVeto");
    CutFlowHist->GetXaxis()->SetBinLabel(9,"jet-selection");
    CutFlowHist->GetXaxis()->SetBinLabel(10,"M_{T}");
    CutFlowHist->GetXaxis()->SetBinLabel(11,"b-tag");
    

    CutFlowHist->SetBinContent(1,sin_n0);
    CutFlowHist->SetBinContent(2,sin_nScrapFilter);
    CutFlowHist->SetBinContent(3,sin_nHCALnoiseFilter);
    CutFlowHist->SetBinContent(4,sin_nHlt);
    CutFlowHist->SetBinContent(5,sin_nPV);
    CutFlowHist->SetBinContent(6,sin_nMu);
    CutFlowHist->SetBinContent(7,sin_nNoLMu);
    CutFlowHist->SetBinContent(8,sin_nNoLE);
    CutFlowHist->SetBinContent(9,sin_nJet);
    CutFlowHist->SetBinContent(10,sin_nMT);
    CutFlowHist->SetBinContent(11,sin_nBtag);


    plots->cd();
    if(sin_doScrapFilter){
        CutFlowHist->Write();
    }
    if(fillHists){
        if(sin_doPV){
            sin_atLeastOnGPV.WriteAll(plots);
        }
    //    cout<<"PV is done"<<endl;
        if(sin_doMuon)
            sin_MuSelection.WriteAll(plots);
    //    cout<<"Musel is done"<<endl;
        if(sin_doLMuVeto)
            sin_LMuVeto.WriteAll(plots);
    //    cout<<"LM is done"<<endl;
        if(sin_doLEVeto)
            sin_LEVeto.WriteAll(plots);
    //    cout<<"LE is done"<<endl;
        if(sin_dojet)
            sin_Jets.WriteAll(plots);
    //    cout<<"jet is done"<<endl;

        if(sin_doMT){
            plots->cd();
            MT->Write();
        }
    //    cout<<"MT is done"<<endl;


        if(sin_doBtag){
            sin_BJets.WriteAll(plots);
            sin_AllFinalMuons.WriteAll(plots);
            sin_GoldenFinalMuons.WriteAll(plots);
        }
        plots->cd();
        finalMT->Write();
    }
    plots->Write();
    plots->Close();
    
    
    double intialBeforePresel = (double)sin_n0/(double)PreSelEff;
//    double weight = (double)(XSec*Luminosity)/(double)intialBeforePresel;
    double weight = sin_weight;
    cout<<"Cut flow in "<<Luminosity<<" pb-1 , Weight is "<<weight<<endl;
        
    cout<<"\n\nInitial\tScrap\tHEHB\tTrigger\tPV\tMuon\tLMVeto\tLEVeto\tJet\tMT\tbTag\n"<<endl;
    cout<<sin_n0*weight<<"\t"<<sin_nScrapFilter*weight<<"\t"<<sin_nHCALnoiseFilter*weight<<"\t"<<sin_nHlt*weight<<"\t"
            <<sin_nPV*weight<<"\t"<<sin_nMu*weight<<"\t"<<sin_nNoLMu*weight<<"\t"<<sin_nNoLE*weight<<"\t"
            <<sin_nJet*weight<<"\t"<<sin_nMT*weight<<"\t"<<sin_nBtag*weight<<endl;
    
    cout<<sin_n0*weight<<"\n"<<sin_nScrapFilter*weight<<"\n"<<sin_nHCALnoiseFilter*weight<<"\n"<<sin_nHlt*weight<<"\n"
            <<sin_nPV*weight<<"\n"<<sin_nMu*weight<<"\n"<<sin_nNoLMu*weight<<"\n"<<sin_nNoLE*weight<<"\n"
            <<sin_nJet*weight<<"\n"<<sin_nMT*weight<<"\n"<<sin_nBtag*weight<<endl;
    

}

int main(int argc, char** argv){
//    sleep(60);
    double doJES = 1.;
    for (int f = 1; f < argc; f++) {
        std::string arg_fth(*(argv + f));

        if (arg_fth == "out") {
          f++;
          std::string out(*(argv + f));
          sin_outFileName_FullSelection = string(out+".root");
	  sin_plotFileName = out;
        }else if (arg_fth == "input") {
          f++;
          std::string in(*(argv + f));
          sin_inputFileNames.push_back(string("~/"+in));
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

        }
    }
//    cout<<doJES<<endl;
    cout << sin_inputFileNames.at(0).c_str() << endl;

    TFile* f = 0;
    TClonesArray* corrMET = 0;

    beginJob();
    TApplication theApp("App", &argc, argv);
//    gSystem->Load("libTree.so");
//    string tmp = "NadjiehV*";
//    cout<<tmp.find("*")<<"  "<<tmp.size()<<endl;
//    cout<<tmp.substr(0,tmp.find("*"))<<endl;
//    string tmp3 = tmp.substr(0,tmp.find("*"));
//    string tmp2 = "NadjiehV27";
//    cout<<tmp3.size()<<endl;
//    cout<<tmp2.substr(0,tmp.find("*"))<<endl;
//    cout<<<<endl;
    
    for(unsigned int fNumber = 0; fNumber<sin_inputFileNames.size(); fNumber++){
        cout<<"RunNumber|\tEventNumber|\tLumiBlock|\tptLepton|\trelIso|\tptjet1|\tptjet2|\tMET|\tMT|\tbtagjet1|\tbtagjet2"<<endl;
        f = TFile::Open(sin_inputFileNames.at(fNumber).c_str());
//        cout<<"nFiles: "<<sin_inputFileNames.size()<<endl;

        TTree* runTree = (TTree*) f->Get("runTree");
        TTree* eventTree = (TTree*) f->Get("eventTree");
        
//        cout<<runTree->GetName()<<"????"<<endl;

        PracticalEvent * pracEvt = new PracticalEvent(eventTree,runTree);
        pracEvt->eventTree->SetBranchStatus("*", 1);


        if(fillTree ){
            stringstream s("");
            s<<(fNumber+1)<<"_"<<sin_outFileName_FullSelection;
            sin_out = new TFile(s.str().c_str(), "recreate");
            sin_out->cd();
            eventTree_f = pracEvt->eventTree->CloneTree(0);
            runTree_f = pracEvt->runTree->CloneTree(0);
            if(saveTypeIMET){
                if(sin_verbosity > 0)
                    cout<<"corrMET initiating ... "<<endl;
                corrMET = new TClonesArray("TopTree::TRootPFMET", 1000);
                eventTree_f->Branch ("PFMET_TypeICorrected", "TClonesArray", &corrMET);
            }
                
        }

        std::cout<<"beforeLoop"<<std::endl;

        int ievt = 0;
        

        while (pracEvt->Next()) {
            if(ievt > 1)
                break;
            if(sin_verbosity > 0){
                cout<<"JES: "<<doJES<<endl;
            }
            double lumiWeight3D = 1;
            if(pu3D){
                Lumi3DReWeighting Lumi3DWeights = 
                Lumi3DReWeighting("../../../../TopBrussels/TopTreeAnalysis/macros/PileUpReweighting/pileup_MC_Flat10PlusTail.root",
                "../../../../TopBrussels/TopTreeAnalysis/macros/PileUpReweighting/pileup_FineBin_2011Data_UpToRun180252.root", "pileup", "pileup");
                Lumi3DWeights.weight3D_init(1.0);


                if(!isData){
        //            cout<<"here I am ... "<<pracEvt->Event()<<endl;
                    lumiWeight3D = Lumi3DWeights.weight3D(pracEvt->Event());
                } else lumiWeight3D = 1;
            }

            ievt++;
            if(sin_verbosity > 0)
                cout<<"*******************************************************************"<<endl;

            std::vector<TRootPFJet>  myJets_;
            myJets_.clear();
//            cout<<"I am going to Jet Correction "<<isData<<endl;
            myJets_ = pracEvt->ScaledPFJetCollection(1,false);
            Event myEvent_tmp( myJets_, *pracEvt->ElectronCollection()
            ,*pracEvt->METCollection(),*pracEvt->MuonCollection(),*pracEvt->VertexCollection());
            if(sin_verbosity > 0)
                cout<<"PV size: "<<myEvent_tmp.pvs.size()<<"\n"
                    <<"Muon size: "<<myEvent_tmp.muons.size()<<"\n"
                    <<"Electron size: "<<myEvent_tmp.electrons.size()<<"\n"
                    <<"Jet size: "<<myEvent_tmp.PFJets.size()<<"\n"<<endl;
            myEvent_tmp.verbose(sin_verbosity);
            if(sin_verbosity > 0)
                cout<<"ScrapFilterMaker-------------------------------------------------------------------"<<endl;
            double scrapFilterer = (double)(pracEvt->Event()->nHighPurityTracks())/(double)(pracEvt->Event()->nTracks());
            if(sin_verbosity > 0)
                cout<<"HBHEnoiseFilterMaker-------------------------------------------------------------------"<<endl;//?????
            if(sin_verbosity > 0)
                cout<<"Vertex Makers ---------------------------------------------------------------------"<<endl;
            myEvent_tmp.VertexMaker();
            if(sin_verbosity > 0)
                cout<<"Electron Maker ---------------------------------------------------------------------"<<endl;
            myEvent_tmp.ElectronMaker();
            /*pt = 30., eta = 2.5,  Exc_Low = 1.4442 , Exc_High = 1.5660, Id = "VBTF70", IdSecond = "VBTF95" (not applied),
             * D0 = 0.02, IsoCut = 0.125, drToPV = 10000.,  secondEIso = 0.2, secPt=15 GeV 
             */
            
            /* if(sin_verbosity > 0)
             * cout<<"Jet Cleaning  ---------------------------------------------------------------------"<<endl;
             * myEvent_tmp.JetCleaning();
            *///not needed for PFToPAT
            
            if(sin_verbosity > 0)
                cout<<"Jet Makers ---------------------------------------------------------------------"<<endl;
            myEvent_tmp.PFJetMaker(/*bTagAlgo*/"TCHP",/*pt*/30.,/*eta*/4.5);
            if(sin_verbosity > 0)
                cout<<"Muon Maker ---------------------------------------------------------------------"<<endl;
            myEvent_tmp.MuonMaker();
            /*
             * pt = 20.,  eta = 2.1, chi2 = 10,  D0 = 0.02,  nvh = 10, isoCut_ = 0.15,  doGL = false,  
             * nPixWithMeasuredHits = 1,  nSegM = 1
             */
            if(sin_verbosity > 0)
                cout<<"START TO SELECT : "<<endl;
            sin_n0++;
            if(sin_doScrapFilter){
                if(scrapFilterer > 0.2){
                    sin_nScrapFilter++;
                    if(sin_verbosity>0)
                        cout<<"\tPassed!! scrapFilterer is "<<scrapFilterer<<endl;
                }else
                    continue;
            }
            if(sin_doHCALnoiseFilter){
                if(sin_verbosity>0)
                    cout<<"no Info in TopTrees for this cut :-("<<endl;
            }
            if(sin_doHLT){
                TopTree::TRootHLTInfo hltInfo = pracEvt->RunInfo()->getHLTinfo(pracEvt->Event()->runId());
                int trigID = hltInfo.hltPath("HLT_IsoMu17_v*");
//                cout<<"trigID: "<<trigID<<", hlt: "<<pracEvt->Event()->trigHLT(trigID)<<endl;   
                if(pracEvt->Event()->trigHLT(trigID)){
                    sin_nHlt++;
                    if(sin_verbosity > 0){
                        cout<<hltInfo.hltNames(trigID)<<"\t"<<hltInfo.hltWasRun(trigID)<<
                        "\t"<<hltInfo.hltAccept(trigID)<<endl;
                        cout<<"\tHLT is passed"<<endl;
                    }
                }else 
                    continue;
            }
            if(sin_doPV){
                if(fillHists)
                    sin_atLeastOnGPV.Fill(myEvent_tmp.pvs,myEvent_tmp.Gpvs.size(),lumiWeight3D);
                if(myEvent_tmp.Gpvs.size() > 0){
                    sin_nPV++;
                    if(sin_verbosity > 0)
                        cout<<"\tPVCut Passed"<<endl;
                } else
                    continue;
            }

            if(sin_doMuon){
                if(fillHists)
                    sin_MuSelection.Fill(myEvent_tmp.muons,myEvent_tmp.Dmuons.size(),lumiWeight3D);
                if(myEvent_tmp.Dmuons.size() == 1){
                    sin_nMu++;
                    if(sin_verbosity > 0)
                        cout<<"\tMu selection Passed"<<endl;
                } else
                    continue;
            }
            if(sin_doLMuVeto){
                if(fillHists)
                    sin_LMuVeto.Fill(myEvent_tmp.looseMuons,myEvent_tmp.looseMuons.size(),lumiWeight3D);
                if(myEvent_tmp.looseMuons.size()==0){
                    sin_nNoLMu++;
                    if(sin_verbosity > 0)
                        cout<<"\tlooseMuVeto is passed"<<endl;
                }else 
                    continue;
            }
            TRootMuon myMu = myEvent_tmp.Dmuons.at(0);
            double relIso=(myMu.chargedHadronIso()+myMu.neutralHadronIso()+myMu.photonIso())/myMu.Pt();
//            cout<<pracEvt->Event()->runId()<<"|\t"<<pracEvt->Event()->eventId()<<"|\t"
//            <<pracEvt->Event()->lumiBlockId()<<"|\t"<<myMu.Pt()<<"|\t"<<relIso<<" ("<<myMu.neutralHadronIso()
//            <<", "<<myMu.chargedHadronIso()<<", "<<myMu.photonIso()<<") |\t|\t|\t\t\t\t"<<endl;
            if(sin_doLEVeto){
                if(myEvent_tmp.Gelectrons.size()==0 && myEvent_tmp.Secondelectrons.size()==0){
                    sin_nNoLE++;
                    if(sin_verbosity > 0)
                        cout<<"\tlooseEVeto is passed"<<endl;
                }else 
                    continue;
            }
//            cout<<pracEvt->Event()->runId()<<"|\t"<<pracEvt->Event()->eventId()<<"|\t"
//            <<pracEvt->Event()->lumiBlockId()<<"|\t"<<myMu.Pt()<<"|\t"<<relIso<<" ("<<myMu.neutralHadronIso()
//            <<", "<<myMu.chargedHadronIso()<<", "<<myMu.photonIso()<<") |\t|\t|\t\t\t\t"<<endl;

            if(sin_dojet){
                if(fillHists)
                    sin_Jets.FillPFJets(myEvent_tmp.PFJets,myEvent_tmp.GPFJets.size(),myEvent_tmp.BPFJets.size());
                if(myEvent_tmp.GPFJets.size() == 2){		
                    sin_nJet++;
                    if(sin_verbosity > 0){
                        cout<<"\t==2 Jet Passed"<<endl;
                    }
                } else
                    continue;
            }
            if(fillTree){
                if(saveTypeIMET)
                    if(sin_verbosity>0) cout << endl << "Analyzing ParticleFlow Missing Et..." << endl;
                if(saveTypeIMET)
                    new( (*corrMET)[0] ) TRootPFMET(pracEvt->TypeICorrMET());
                eventTree_f->Fill();
                if(saveTypeIMET) 
                    (*corrMET).Delete();
            }
//            cout<<pracEvt->Event()->runId()<<"|\t"<<pracEvt->Event()->eventId()<<"|\t"
//            <<pracEvt->Event()->lumiBlockId()<<"|\t"<<myMu.Pt()<<"|\t"<<relIso<<" ("<<myMu.neutralHadronIso()
//            <<", "<<myMu.chargedHadronIso()<<", "<<myMu.photonIso()<<") |\t"<<myEvent_tmp.GPFJets.at(0).Pt()
//            <<"|\t"<<myEvent_tmp.GPFJets.at(1).Pt()<<"|\t|\t|\t|\t"<<endl;
            double mt = 0;
            if(sin_doMT){
                double metT = sqrt((myEvent_tmp.mets.at(0).Px()*myEvent_tmp.mets.at(0).Px())+
                               (myEvent_tmp.mets.at(0).Py()*myEvent_tmp.mets.at(0).Py()));
                
                double muT =  sqrt((myEvent_tmp.Dmuons.at(0).Px()*myEvent_tmp.Dmuons.at(0).Px())+
                              (myEvent_tmp.Dmuons.at(0).Py()*myEvent_tmp.Dmuons.at(0).Py()));
                mt = sqrt(pow(muT+metT,2) - pow(myEvent_tmp.mets.at(0).Px()+myEvent_tmp.Dmuons.at(0).Px(),2)
                                                 - pow(myEvent_tmp.mets.at(0).Py()+myEvent_tmp.Dmuons.at(0).Py(),2));
                if(fillHists)
                    MT->Fill(mt,lumiWeight3D);
                if(mt>40){
                    sin_nMT++;
                    if(sin_verbosity>0)
                        cout<<"\tM_T cut is passed"<<endl;
                }else
                    continue;
            }
//            cout<<pracEvt->Event()->runId()<<"|\t"<<pracEvt->Event()->eventId()<<"|\t"
//            <<pracEvt->Event()->lumiBlockId()<<"|\t"<<myMu.Pt()<<"|\t"<<relIso<<" ("<<myMu.neutralHadronIso()
//            <<", "<<myMu.chargedHadronIso()<<", "<<myMu.photonIso()<<") |\t"<<myEvent_tmp.GPFJets.at(0).Pt()
//            <<"|\t"<<myEvent_tmp.GPFJets.at(1).Pt()<<"|\t"<<myEvent_tmp.mets.at(0).Pt()<<"|\t"<<mt<<"|\t|\t"<<endl;
            if(sin_doBtag){
                if(fillHists)
                    sin_BJets.FillPFJets(myEvent_tmp.GPFJets,myEvent_tmp.GPFJets.size(),myEvent_tmp.BPFJets.size(),false,lumiWeight3D);
                if(myEvent_tmp.BPFJets.size() == 1){
                    sin_nBtag++;
                    if(sin_verbosity > 0)
                        cout<<"\t== 1bTag Passed"<<endl;
                } else
                    continue;
            }

            cout<<pracEvt->Event()->runId()<<"|\t"<<pracEvt->Event()->eventId()<<"|\t"
            <<pracEvt->Event()->lumiBlockId()<<"|\t"<<myMu.Pt()<<"|\t"<<relIso<<" ("<<myMu.neutralHadronIso()
            <<", "<<myMu.chargedHadronIso()<<", "<<myMu.photonIso()<<") |\t"<<myEvent_tmp.GPFJets.at(0).Pt()
            <<"|\t"<<myEvent_tmp.GPFJets.at(1).Pt()<<"|\t"<<myEvent_tmp.mets.at(0).Pt()<<"|\t"<<mt<<"|\t"
            <<myEvent_tmp.BPFJets.at(0).btag_trackCountingHighPurBJetTags()<<"|\t"<<endl;
            if(fillHists){
                sin_GoldenFinalMuons.Fill(myEvent_tmp.Dmuons,myEvent_tmp.Dmuons.size(),lumiWeight3D);
                finalMT->Fill(mt,lumiWeight3D);
            }
        }
        runTree_f->Fill();
        cout<<"before closing file input "<<f->GetName()<<endl;
        f->Close();
        delete f;

        if(fillTree){
            sin_out->cd();
            sin_out->Write();
            sin_out->Close();
        }
    }
    cout<<"before endjob"<<endl;
        endJob();
	return 0;
}
