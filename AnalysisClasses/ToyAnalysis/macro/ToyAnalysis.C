/*
 * For the moment I use the event selection chain in explicitly
 * It comes from AnalysisClasses/EventSelection/macro/t-SingleTopSelection/SelectAndSave.C
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
#include <vector>

using namespace std;
using namespace TopTree;


PVHists toy_atLeastOnGPV("before_PV_selection");
MuonHists toy_MuSelection("before_Mu_selection");
MuonHists toy_LMuVeto("before_LmuVeto_Selection");
ElectronHists toy_LEVeto("before_LeVeto_Selection");
JetHists toy_Jets("before_Jet_selection",2);
JetHists toy_BJets("before_BJet_selection",2);
MuonHists toy_AllFinalMuons("before_BJet_AllFinalMu");
MuonHists toy_GoldenFinalMuons("before_BJet_GoldenFinalMu");
JetHists toy_GoldenFinalJets("before_BJet_FinalGoldenFinalMu");





int toy_n0;
int toy_nScrapFilter;
bool toy_doScrapFilter;
int toy_nHCALnoiseFilter;
bool toy_doHCALnoiseFilter;
int toy_nHlt;
bool toy_doHLT;
int toy_nPV;
bool toy_doPV;
int toy_nMu;
bool toy_doMuon;
int toy_nNoLMu;
bool toy_doLMuVeto;
int toy_nNoLE;
bool toy_doLEVeto;
int toy_nConv_a;
int toy_nConv_b;
int  toy_nConv;
bool toy_doConv;
bool toy_doEcalDriven;
int toy_nEcalDriven;
int toy_nJet;
bool toy_dojet;
int toy_nMT ;
bool toy_doMT;
int toy_nBtag;
bool toy_doBtag;
double XSec;
double Luminosity;
double PreSelEff;
bool pu3D;
bool saveTypeIMET;

bool isData;
double toy_weight;

int toy_verbosity;
TH1D * MT;
TH1D * finalMT;
TH1D * METResolutions;

bool fillTree;
bool fillHists;
TFile * toy_out;
TTree * eventTree_f;
TTree * runTree_f;


std::vector<std::string> toy_inputFileNames;
std::string toy_outFileName;
std::string toy_plotFileName;
std::string toy_outFileName_FullSelection;

void beginJob(){
     toy_n0 = 0;
     toy_nScrapFilter = 0;
     toy_doScrapFilter = true;
     toy_nHCALnoiseFilter = 0;
     toy_doHCALnoiseFilter = true;
     toy_nHlt = 0;
     toy_doHLT = true;
     toy_nPV = 0;
     toy_doPV = true;//
     toy_nMu = 0;
     toy_doMuon = true;//
     toy_nNoLMu = 0;
     toy_doLMuVeto =  true;//
     toy_nNoLE = 0;
     toy_doLEVeto = true;//
     toy_doConv = false;// Specific to electron selection.
     toy_nConv_a= 0;
     toy_nConv_b= 0;
     toy_nEcalDriven = 0;
     toy_doEcalDriven =false;// Specific to electron selection.   
     toy_nJet= 0;
     toy_dojet = true;//
     toy_nMT = 0;
     toy_doMT = true;//
     toy_nBtag= 0;
     toy_doBtag = true;// Specific to electron selection.  
     toy_verbosity = 0 ;
     fillTree = false;//false;
     pu3D = false;
     fillHists = false;
     saveTypeIMET=false;
     MT = new TH1D("MT","W-neutrino transverse mass",100, 0.,200.);
     MT->GetXaxis()->SetTitle("M_{T}(W,#nu)");
     finalMT = new TH1D("finalMT","final-W-neutrino transverse mass",100, 0.,200.);
     finalMT->GetXaxis()->SetTitle("M_{T}(W,#nu)");
     
     toy_weight = 1;
}



void endJob(){
    TFile * plots = new TFile(toy_plotFileName.c_str(),"recreate");
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
    

    CutFlowHist->SetBinContent(1,toy_n0);
    CutFlowHist->SetBinContent(2,toy_nScrapFilter);
    CutFlowHist->SetBinContent(3,toy_nHCALnoiseFilter);
    CutFlowHist->SetBinContent(4,toy_nHlt);
    CutFlowHist->SetBinContent(5,toy_nPV);
    CutFlowHist->SetBinContent(6,toy_nMu);
    CutFlowHist->SetBinContent(7,toy_nNoLMu);
    CutFlowHist->SetBinContent(8,toy_nNoLE);
    CutFlowHist->SetBinContent(9,toy_nJet);
    CutFlowHist->SetBinContent(10,toy_nMT);
    CutFlowHist->SetBinContent(11,toy_nBtag);


    plots->cd();
    if(toy_doScrapFilter){
        CutFlowHist->Write();
    }
    if(fillHists){
        if(toy_doPV){
            toy_atLeastOnGPV.WriteAll(plots);
        }
    //    cout<<"PV is done"<<endl;
        if(toy_doMuon)
            toy_MuSelection.WriteAll(plots);
    //    cout<<"Musel is done"<<endl;
        if(toy_doLMuVeto)
            toy_LMuVeto.WriteAll(plots);
    //    cout<<"LM is done"<<endl;
        if(toy_doLEVeto)
            toy_LEVeto.WriteAll(plots);
    //    cout<<"LE is done"<<endl;
        if(toy_dojet)
            toy_Jets.WriteAll(plots);
    //    cout<<"jet is done"<<endl;

        if(toy_doMT){
            plots->cd();
            MT->Write();
        }
    //    cout<<"MT is done"<<endl;


        if(toy_doBtag){
            toy_BJets.WriteAll(plots);
            toy_AllFinalMuons.WriteAll(plots);
            toy_GoldenFinalMuons.WriteAll(plots);
        }
        plots->cd();
        finalMT->Write();
    }
    plots->Write();
    plots->Close();
    
    
    double intialBeforePresel = (double)toy_n0/(double)PreSelEff;
//    double weight = (double)(XSec*Luminosity)/(double)intialBeforePresel;
    double weight = toy_weight;
    cout<<"Cut flow in "<<Luminosity<<" pb-1 , Weight is "<<weight<<endl;
        
    cout<<"\n\nInitial\tScrap\tHEHB\tTrigger\tPV\tMuon\tLMVeto\tLEVeto\tJet\tMT\tbTag\n"<<endl;
    cout<<toy_n0*weight<<"\t"<<toy_nScrapFilter*weight<<"\t"<<toy_nHCALnoiseFilter*weight<<"\t"<<toy_nHlt*weight<<"\t"
            <<toy_nPV*weight<<"\t"<<toy_nMu*weight<<"\t"<<toy_nNoLMu*weight<<"\t"<<toy_nNoLE*weight<<"\t"
            <<toy_nJet*weight<<"\t"<<toy_nMT*weight<<"\t"<<toy_nBtag*weight<<endl;
    
    cout<<toy_n0*weight<<"\n"<<toy_nScrapFilter*weight<<"\n"<<toy_nHCALnoiseFilter*weight<<"\n"<<toy_nHlt*weight<<"\n"
            <<toy_nPV*weight<<"\n"<<toy_nMu*weight<<"\n"<<toy_nNoLMu*weight<<"\n"<<toy_nNoLE*weight<<"\n"
            <<toy_nJet*weight<<"\n"<<toy_nMT*weight<<"\n"<<toy_nBtag*weight<<endl;
    

}

int main(int argc, char** argv){
//    sleep(60);
    double doJES = 1.;
    for (int f = 1; f < argc; f++) {
        std::string arg_fth(*(argv + f));

        if (arg_fth == "out") {
          f++;
          std::string out(*(argv + f));
          toy_outFileName_FullSelection = string(out+".root");
	  toy_plotFileName = out;
        }else if (arg_fth == "input") {
          f++;
          std::string in(*(argv + f));
          toy_inputFileNames.push_back(string("~/"+in));
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

        }
    }
//    cout<<doJES<<endl;
    cout << toy_inputFileNames.at(0).c_str() << endl;

    TFile* f = 0;
    TClonesArray* corrMET = 0;

    beginJob();
    TApplication theApp("App", &argc, argv);
    TH1D * cosTheta = new TH1D("cosTheta","cos(#theta)",1000, -1, 1 );
    TH1D * cosThetaRW = new TH1D("cosThetaRW","cos(#theta)_{rw}",1000, -1, 1 );
    TH1D * cosThetaGen = new TH1D("cosThetaGen","cos(#theta)_{gen}",1000, -1, 1 );
    TH1D * topMass = new TH1D("topMass","m_{top}",150, 0,300);
    TH1D * Wmass = new TH1D("Wmass","m_{W}",75, 0,150 );
    CosThetaWeighter myWeighter(8.51588e-01,1.19857e-01);
    for(unsigned int fNumber = 0; fNumber<toy_inputFileNames.size(); fNumber++){
        cout<<"RunNumber|\tEventNumber|\tLumiBlock|\tptLepton|\trelIso|\tptjet1|\tptjet2|\tMET|\tMT|\tbtagjet1|\tbtagjet2"<<endl;
        f = TFile::Open(toy_inputFileNames.at(fNumber).c_str());
//        cout<<"nFiles: "<<toy_inputFileNames.size()<<endl;

        TTree* runTree = (TTree*) f->Get("runTree");
        TTree* eventTree = (TTree*) f->Get("eventTree");
        
//        cout<<runTree->GetName()<<"????"<<endl;

        PracticalEvent * pracEvt = new PracticalEvent(eventTree,runTree);
        pracEvt->eventTree->SetBranchStatus("*", 1);


        if(fillTree ){
            stringstream s("");
            s<<(fNumber+1)<<"_"<<toy_outFileName_FullSelection;
            toy_out = new TFile(s.str().c_str(), "recreate");
            toy_out->cd();
            eventTree_f = pracEvt->eventTree->CloneTree(0);
            runTree_f = pracEvt->runTree->CloneTree(0);
            if(saveTypeIMET){
                if(toy_verbosity > 0)
                    cout<<"corrMET initiating ... "<<endl;
                corrMET = new TClonesArray("TopTree::TRootPFMET", 1000);
                eventTree_f->Branch ("PFMET_TypeICorrected", "TClonesArray", &corrMET);
            }
                
        }

        std::cout<<"beforeLoop"<<std::endl;

        int ievt = 0;
        

        while (pracEvt->Next()) {

//            if(ievt > 10)
//                break;
            double lumiWeight3D = 1;

            GenSingleTopMaker myGenStMaker((TRootNPGenEvent*)pracEvt->NPGenEvtCollection()->At(0));
            if(myGenStMaker.isSemiMuSingleTop){
                double W = myWeighter.getWeight(myGenStMaker.genSingleTop.cosThetaStar())*lumiWeight3D;
                cosThetaGen->Fill(myGenStMaker.genSingleTop.cosThetaStar(),W);
                topMass->Fill(myGenStMaker.genSingleTop.top().M(),W);
                Wmass->Fill(myGenStMaker.genSingleTop.W().M(),W);
//                myGenStMaker.genSingleTop.printContent();
            }

            if(toy_verbosity > 0){
                cout<<"JES: "<<doJES<<endl;
            }
            if(pu3D){
                Lumi3DReWeighting Lumi3DWeights = 
                Lumi3DReWeighting("../../../TopBrussels/TopTreeAnalysis/macros/PileUpReweighting/pileup_MC_Flat10PlusTail.root",
                "../../../TopBrussels/TopTreeAnalysis/macros/PileUpReweighting/pileup_FineBin_2011Data_UpToRun180252.root", "pileup", "pileup");
                Lumi3DWeights.weight3D_init(1.0);


                if(!isData){
        //            cout<<"here I am ... "<<pracEvt->Event()<<endl;
                    lumiWeight3D = Lumi3DWeights.weight3D(pracEvt->Event());
                } else lumiWeight3D = 1;
            }

            ievt++;
            if(toy_verbosity > 0)
                cout<<"*******************************************************************"<<endl;

            std::vector<TRootPFJet>  myJets_;
            myJets_.clear();
//            cout<<"I am going to Jet Correction "<<isData<<endl;
/*
            myJets_ = pracEvt->ScaledPFJetCollection(1,false);
*/
            myJets_ = pracEvt->unCorrectedPFJetVector();
            Event myEvent_tmp( myJets_, *pracEvt->ElectronCollection()
            ,*pracEvt->METCollection(),*pracEvt->MuonCollection(),*pracEvt->VertexCollection());
            
            if(toy_verbosity > 0)
                cout<<"PV size: "<<myEvent_tmp.pvs.size()<<"\n"
                    <<"Muon size: "<<myEvent_tmp.muons.size()<<"\n"
                    <<"Electron size: "<<myEvent_tmp.electrons.size()<<"\n"
                    <<"Jet size: "<<myEvent_tmp.PFJets.size()<<"\n"<<endl;
            myEvent_tmp.verbose(toy_verbosity);
            if(toy_verbosity > 0)
                cout<<"ScrapFilterMaker-------------------------------------------------------------------"<<endl;
            double scrapFilterer = (double)(pracEvt->Event()->nHighPurityTracks())/(double)(pracEvt->Event()->nTracks());
            if(toy_verbosity > 0)
                cout<<"HBHEnoiseFilterMaker-------------------------------------------------------------------"<<endl;//?????
            if(toy_verbosity > 0)
                cout<<"Vertex Makers ---------------------------------------------------------------------"<<endl;
            myEvent_tmp.VertexMaker();
            if(toy_verbosity > 0)
                cout<<"Electron Maker ---------------------------------------------------------------------"<<endl;
            myEvent_tmp.ElectronMaker();
            /*pt = 30., eta = 2.5,  Exc_Low = 1.4442 , Exc_High = 1.5660, Id = "VBTF70", IdSecond = "VBTF95" (not applied),
             * D0 = 0.02, IsoCut = 0.125, drToPV = 10000.,  secondEIso = 0.2, secPt=15 GeV 
             */
            
            /* if(toy_verbosity > 0)
             * cout<<"Jet Cleaning  ---------------------------------------------------------------------"<<endl;
             * myEvent_tmp.JetCleaning();
            *///not needed for PFToPAT
            
            if(toy_verbosity > 0)
                cout<<"Jet Makers ---------------------------------------------------------------------"<<endl;
            myEvent_tmp.PFJetMaker(/*bTagAlgo*/"TCHP",/*pt*/30.,/*eta*/4.5);
            if(toy_verbosity > 0)
                cout<<"Muon Maker ---------------------------------------------------------------------"<<endl;
            myEvent_tmp.MuonMaker();
            /*
             * pt = 20.,  eta = 2.1, chi2 = 10,  D0 = 0.02,  nvh = 10, isoCut_ = 0.15,  doGL = false,  
             * nPixWithMeasuredHits = 1,  nSegM = 1
             */
            if(toy_verbosity > 0)
                cout<<"START TO SELECT : "<<endl;
            toy_n0++;
            if(toy_doScrapFilter){
                if(scrapFilterer > 0.2){
                    toy_nScrapFilter++;
                    if(toy_verbosity>0)
                        cout<<"\tPassed!! scrapFilterer is "<<scrapFilterer<<endl;
                }else
                    continue;
            }
            if(toy_doHCALnoiseFilter){
                if(toy_verbosity>0)
                    cout<<"no Info in TopTrees for this cut :-("<<endl;
            }
            if(toy_doHLT){
                TopTree::TRootHLTInfo hltInfo = pracEvt->RunInfo()->getHLTinfo(pracEvt->Event()->runId());
                int trigID = hltInfo.hltPath("HLT_IsoMu17_v*");
//                cout<<"trigID: "<<trigID<<", hlt: "<<pracEvt->Event()->trigHLT(trigID)<<endl;   
                if(pracEvt->Event()->trigHLT(trigID)){
                    toy_nHlt++;
                    if(toy_verbosity > 0){
                        cout<<hltInfo.hltNames(trigID)<<"\t"<<hltInfo.hltWasRun(trigID)<<
                        "\t"<<hltInfo.hltAccept(trigID)<<endl;
                        cout<<"\tHLT is passed"<<endl;
                    }
                }else 
                    continue;
            }
            if(toy_doPV){
                if(fillHists)
                    toy_atLeastOnGPV.Fill(myEvent_tmp.pvs,myEvent_tmp.Gpvs.size(),lumiWeight3D);
                if(myEvent_tmp.Gpvs.size() > 0){
                    toy_nPV++;
                    if(toy_verbosity > 0)
                        cout<<"\tPVCut Passed"<<endl;
                } else
                    continue;
            }

            if(toy_doMuon){
                if(fillHists)
                    toy_MuSelection.Fill(myEvent_tmp.muons,myEvent_tmp.Dmuons.size(),lumiWeight3D);
                if(myEvent_tmp.Dmuons.size() == 1){
                    toy_nMu++;
                    if(toy_verbosity > 0)
                        cout<<"\tMu selection Passed"<<endl;
                } else
                    continue;
            }
            if(toy_doLMuVeto){
                if(fillHists)
                    toy_LMuVeto.Fill(myEvent_tmp.looseMuons,myEvent_tmp.looseMuons.size(),lumiWeight3D);
                if(myEvent_tmp.looseMuons.size()==0){
                    toy_nNoLMu++;
                    if(toy_verbosity > 0)
                        cout<<"\tlooseMuVeto is passed"<<endl;
                }else 
                    continue;
            }
            TRootMuon myMu = myEvent_tmp.Dmuons.at(0);
            double relIso=(myMu.chargedHadronIso()+myMu.neutralHadronIso()+myMu.photonIso())/myMu.Pt();
//            cout<<pracEvt->Event()->runId()<<"|\t"<<pracEvt->Event()->eventId()<<"|\t"
//            <<pracEvt->Event()->lumiBlockId()<<"|\t"<<myMu.Pt()<<"|\t"<<relIso<<" ("<<myMu.neutralHadronIso()
//            <<", "<<myMu.chargedHadronIso()<<", "<<myMu.photonIso()<<") |\t|\t|\t\t\t\t"<<endl;
            if(toy_doLEVeto){
                if(myEvent_tmp.Gelectrons.size()==0 && myEvent_tmp.Secondelectrons.size()==0){
                    toy_nNoLE++;
                    if(toy_verbosity > 0)
                        cout<<"\tlooseEVeto is passed"<<endl;
                }else 
                    continue;
            }
//            cout<<pracEvt->Event()->runId()<<"|\t"<<pracEvt->Event()->eventId()<<"|\t"
//            <<pracEvt->Event()->lumiBlockId()<<"|\t"<<myMu.Pt()<<"|\t"<<relIso<<" ("<<myMu.neutralHadronIso()
//            <<", "<<myMu.chargedHadronIso()<<", "<<myMu.photonIso()<<") |\t|\t|\t\t\t\t"<<endl;

            if(toy_dojet){
                if(fillHists)
                    toy_Jets.FillPFJets(myEvent_tmp.PFJets,myEvent_tmp.GPFJets.size(),myEvent_tmp.BPFJets.size());
                if(myEvent_tmp.GPFJets.size() == 2){		
                    toy_nJet++;
                    if(toy_verbosity > 0){
                        cout<<"\t==2 Jet Passed"<<endl;
                    }
                } else
                    continue;
            }
            
            if(fillTree){
                if(saveTypeIMET)
                    if(toy_verbosity>0) cout << endl << "Analyzing ParticleFlow Missing Et..." << endl;
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
            if(toy_doMT){
                double metT = sqrt((myEvent_tmp.mets.at(0).Px()*myEvent_tmp.mets.at(0).Px())+
                               (myEvent_tmp.mets.at(0).Py()*myEvent_tmp.mets.at(0).Py()));
                
                double muT =  sqrt((myEvent_tmp.Dmuons.at(0).Px()*myEvent_tmp.Dmuons.at(0).Px())+
                              (myEvent_tmp.Dmuons.at(0).Py()*myEvent_tmp.Dmuons.at(0).Py()));
                mt = sqrt(pow(muT+metT,2) - pow(myEvent_tmp.mets.at(0).Px()+myEvent_tmp.Dmuons.at(0).Px(),2)
                                                 - pow(myEvent_tmp.mets.at(0).Py()+myEvent_tmp.Dmuons.at(0).Py(),2));
                if(fillHists)
                    MT->Fill(mt,lumiWeight3D);
                if(mt>40){
                    toy_nMT++;
                    if(toy_verbosity>0)
                        cout<<"\tM_T cut is passed"<<endl;
                }else
                    continue;
            }
//            cout<<pracEvt->Event()->runId()<<"|\t"<<pracEvt->Event()->eventId()<<"|\t"
//            <<pracEvt->Event()->lumiBlockId()<<"|\t"<<myMu.Pt()<<"|\t"<<relIso<<" ("<<myMu.neutralHadronIso()
//            <<", "<<myMu.chargedHadronIso()<<", "<<myMu.photonIso()<<") |\t"<<myEvent_tmp.GPFJets.at(0).Pt()
//            <<"|\t"<<myEvent_tmp.GPFJets.at(1).Pt()<<"|\t"<<myEvent_tmp.mets.at(0).Pt()<<"|\t"<<mt<<"|\t|\t"<<endl;
            if(toy_doBtag){
                if(fillHists)
                    toy_BJets.FillPFJets(myEvent_tmp.GPFJets,myEvent_tmp.GPFJets.size(),myEvent_tmp.BPFJets.size(),false,lumiWeight3D);
                if(myEvent_tmp.BPFJets.size() == 1){
                    toy_nBtag++;
                    if(toy_verbosity > 0)
                        cout<<"\t== 1bTag Passed"<<endl;
                } else
                    continue;
            }
//            cout<<"Event number "<<ievt<<endl;
            int mySecondJetIndex = 0;
            if(mySecondJetIndex == myEvent_tmp.firstBtagIndex)
                mySecondJetIndex = 1;
            SemiLepTopQuark myLeptonicTop(myEvent_tmp.BPFJets.at(0),myEvent_tmp.mets.at(0),myEvent_tmp.Dmuons.at(0),
                    myEvent_tmp.GPFJets.at(mySecondJetIndex),METResolutions);
            cosTheta->Fill(myLeptonicTop.cosThetaStar(),lumiWeight3D);
            double W = myWeighter.getWeight(myGenStMaker.genSingleTop.cosThetaStar())*lumiWeight3D;
            cosThetaRW->Fill(myLeptonicTop.cosThetaStar(),W);
            
            
/*
            cout<<myLeptonicTop.getMET().Px()<<"\t"<<myLeptonicTop.getMET().Py()<<"\t"<<myLeptonicTop.getMET().Pz()<<endl;
            cout<<myEvent_tmp.mets.at(0).Px()<<"\t"<<myEvent_tmp.mets.at(0).Py()<<"\t"<<myEvent_tmp.mets.at(0).Pz()<<endl;
*/

/*
            cout<<pracEvt->Event()->runId()<<"|\t"<<pracEvt->Event()->eventId()<<"|\t"
            <<pracEvt->Event()->lumiBlockId()<<"|\t"<<myMu.Pt()<<"|\t"<<relIso<<" ("<<myMu.neutralHadronIso()
            <<", "<<myMu.chargedHadronIso()<<", "<<myMu.photonIso()<<") |\t"<<myEvent_tmp.GPFJets.at(0).Pt()
            <<"|\t"<<myEvent_tmp.GPFJets.at(1).Pt()<<"|\t"<<myEvent_tmp.mets.at(0).Pt()<<"|\t"<<mt<<"|\t"
            <<myEvent_tmp.BPFJets.at(0).btag_trackCountingHighPurBJetTags()<<"|\t"<<endl;
*/
            if(fillHists){
                toy_GoldenFinalMuons.Fill(myEvent_tmp.Dmuons,myEvent_tmp.Dmuons.size(),lumiWeight3D);
                finalMT->Fill(mt,lumiWeight3D);
            }
        }
        if(fillTree)
            runTree_f->Fill();
        cout<<"before closing file input "<<f->GetName()<<endl;
        f->Close();
        delete f;

        if(fillTree){
            toy_out->cd();
            toy_out->Write();
            toy_out->Close();
        }
    }
    cout<<"before endjob"<<endl;
    TFile * myFile = new TFile("cosTheta.root", "recreate");
    myFile->cd();
    cosTheta->Write();
    cosThetaRW->Write();
    cosThetaGen->Write();
    Wmass->Write();
    topMass->Write();
    myFile->Write();
    myFile->Close();
        endJob();
	return 0;
}

