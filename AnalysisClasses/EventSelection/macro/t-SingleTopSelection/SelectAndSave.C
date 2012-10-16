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
#include "../../../../AnalysisClasses/ToyAnalysis/interface/GenSingleTopMaker.h"




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
JetHists sin_Jets("before_Jet_selection", 2);
JetHists sin_BJets("before_BJet_selection", 2);
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
int sin_nConv;
bool sin_doConv;
bool sin_doEcalDriven;
int sin_nEcalDriven;
int sin_nJet;
bool sin_dojet;
int sin_nMT;
bool sin_doMT;
int sin_nBtag;
bool sin_doBtag;
double XSec;
double Luminosity;
double PreSelEff;
bool pu3D;
bool saveTypeIMET;
bool Wtemplate;
bool TopPairtemplate;
int sin_nWlike;
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

bool isWJetLike(Event evt) {
    if (evt.BPFJets.size() != 0)
        return false;
    if (fabs(evt.GPFJets.at(0).Eta()) > 2.4 || fabs(evt.GPFJets.at(1).Eta()) > 2.4)
        return false;
    double b1 = evt.GPFJets.at(0).btag_trackCountingHighPurBJetTags();
    double b2 = evt.GPFJets.at(1).btag_trackCountingHighPurBJetTags();
    if (b1 < -99 || b2 < -99)
        return false;
    if (b1 >= 3.41 || b2 >= 3.41)
        return false;
    return true;
}

bool isTtLike(Event evt, double bdisc = 3.41, int nTagged = 2) {
    if (evt.GPFJets.size() < 3)
        return false;
    int nTag = 0;
    int nJets = 0;
    for (unsigned int i = 0; i < evt.GPFJets.size(); i++) {
        if (fabs(evt.GPFJets.at(i).Eta()) > 2.4)
            continue;
        nJets++;
        if (evt.GPFJets.at(i).btag_trackCountingHighPurBJetTags() > bdisc)
            nTag++;
    }
    if (nJets < 3)
        return false;
    if (nTag < nTagged)
        return false;
    return true;
}

void beginJob() {
    sin_n0 = 0;
    sin_nScrapFilter = 0;
    sin_doScrapFilter = false;
    sin_nHCALnoiseFilter = 0;
    sin_doHCALnoiseFilter = false;
    sin_nHlt = 0;
    sin_doHLT = false;
    sin_nPV = 0;
    sin_doPV = false; //
    sin_nMu = 0;
    sin_doMuon = false; //
    sin_nNoLMu = 0;
    sin_doLMuVeto = false; //
    sin_nNoLE = 0;
    sin_doLEVeto = false; //
    sin_doConv = false; // Specific to electron selection.
    sin_nConv_a = 0;
    sin_nConv_b = 0;
    sin_nEcalDriven = 0;
    sin_doEcalDriven = false; // Specific to electron selection.   
    sin_nJet = 0;
    sin_dojet = false; //
    sin_nMT = 0;
    sin_doMT = false; //
    sin_nBtag = 0;
    sin_doBtag = false; //   
    sin_verbosity = 0;
    fillTree = true;
    pu3D = false; //false;
    fillHists = false; //true;
    saveTypeIMET = false; //true;
    Wtemplate = false; //true;
    TopPairtemplate = false;
    sin_nWlike = 0;
    MT = new TH1D("MT", "W-neutrino transverse mass", 100, 0., 200.);
    MT->GetXaxis()->SetTitle("M_{T}(W,#nu)");
    finalMT = new TH1D("finalMT", "final-W-neutrino transverse mass", 100, 0., 200.);
    finalMT->GetXaxis()->SetTitle("M_{T}(W,#nu)");

    sin_weight = 1;
}

void endJob() {
    TFile * plots = new TFile(sin_plotFileName.c_str(), "recreate");
    TH1D * CutFlowHist = new TH1D("CutFlow", "", 12, 0, 12);
    CutFlowHist->GetXaxis()->SetBinLabel(1, "Initial");
    CutFlowHist->GetXaxis()->SetBinLabel(2, "Scrap");
    CutFlowHist->GetXaxis()->SetBinLabel(3, "HBHE");
    CutFlowHist->GetXaxis()->SetBinLabel(4, "HLT");
    CutFlowHist->GetXaxis()->SetBinLabel(5, "primaryVertex");
    CutFlowHist->GetXaxis()->SetBinLabel(6, "mu-selection");
    CutFlowHist->GetXaxis()->SetBinLabel(7, "muonVeto");
    CutFlowHist->GetXaxis()->SetBinLabel(8, "elecVeto");
    CutFlowHist->GetXaxis()->SetBinLabel(9, "jet-selection");
    CutFlowHist->GetXaxis()->SetBinLabel(10, "M_{T}");
    CutFlowHist->GetXaxis()->SetBinLabel(11, "b-tag");


    CutFlowHist->SetBinContent(1, sin_n0);
    CutFlowHist->SetBinContent(2, sin_nScrapFilter);
    CutFlowHist->SetBinContent(3, sin_nHCALnoiseFilter);
    CutFlowHist->SetBinContent(4, sin_nHlt);
    CutFlowHist->SetBinContent(5, sin_nPV);
    CutFlowHist->SetBinContent(6, sin_nMu);
    CutFlowHist->SetBinContent(7, sin_nNoLMu);
    CutFlowHist->SetBinContent(8, sin_nNoLE);
    CutFlowHist->SetBinContent(9, sin_nJet);
    CutFlowHist->SetBinContent(10, sin_nMT);
    CutFlowHist->SetBinContent(11, sin_nBtag);


    plots->cd();
    if (sin_doScrapFilter) {
        CutFlowHist->Write();
    }
    if (fillHists) {
        if (sin_doPV) {
            sin_atLeastOnGPV.WriteAll(plots);
        }
        //    cout<<"PV is done"<<endl;
        if (sin_doMuon)
            sin_MuSelection.WriteAll(plots);
        //    cout<<"Musel is done"<<endl;
        if (sin_doLMuVeto)
            sin_LMuVeto.WriteAll(plots);
        //    cout<<"LM is done"<<endl;
        if (sin_doLEVeto)
            sin_LEVeto.WriteAll(plots);
        //    cout<<"LE is done"<<endl;
        if (sin_dojet)
            sin_Jets.WriteAll(plots);
        //    cout<<"jet is done"<<endl;

        if (sin_doMT) {
            plots->cd();
            MT->Write();
        }
        //    cout<<"MT is done"<<endl;


        if (sin_doBtag) {
            sin_BJets.WriteAll(plots);
            sin_AllFinalMuons.WriteAll(plots);
            sin_GoldenFinalMuons.WriteAll(plots);
        }
        plots->cd();
        finalMT->Write();
    }
    plots->Write();
    plots->Close();


    double intialBeforePresel = (double) sin_n0 / (double) PreSelEff;
    //    double weight = (double)(XSec*Luminosity)/(double)intialBeforePresel;
    double weight = sin_weight;
    cout << "Cut flow in " << Luminosity << " pb-1 , Weight is " << weight << endl;

    cout << "\n\nInitial\tScrap\tHEHB\tTrigger\tPV\tMuon\tLMVeto\tLEVeto\tJet\tMT\tbTag\n" << endl;
    cout << sin_n0 * weight << "\t" << sin_nScrapFilter * weight << "\t" << sin_nHCALnoiseFilter * weight << "\t" << sin_nHlt * weight << "\t"
            << sin_nPV * weight << "\t" << sin_nMu * weight << "\t" << sin_nNoLMu * weight << "\t" << sin_nNoLE * weight << "\t"
            << sin_nJet * weight << "\t" << sin_nMT * weight << "\t" << sin_nBtag * weight << "\t" << sin_nWlike << endl;

    cout << sin_n0 * weight << "\n" << sin_nScrapFilter * weight << "\n" << sin_nHCALnoiseFilter * weight << "\n" << sin_nHlt * weight << "\n"
            << sin_nPV * weight << "\n" << sin_nMu * weight << "\n" << sin_nNoLMu * weight << "\n" << sin_nNoLE * weight << "\n"
            << sin_nJet * weight << "\n" << sin_nMT * weight << "\n" << sin_nBtag * weight << "\n" << sin_nWlike << endl;


}

int main(int argc, char** argv) {
    //    sleep(60);
    double doJES = 1.;
    bool doTopDiff = true;
    std::string ttDecayMode;
    std::string HLTname = "HLT_IsoMu17_v*"; //"HLT_Mu17_eta2p1_CentralJet30_BTagIP_v1";//
    for (int f = 1; f < argc; f++) {
        std::string arg_fth(*(argv + f));

        if (arg_fth == "out") {
            f++;
            std::string out(*(argv + f));
            sin_outFileName_FullSelection = string(out + ".root");
            sin_plotFileName = string("histograms_"+out + ".root");
        } else if (arg_fth == "input") {
            f++;
            std::string in(*(argv + f));
            sin_inputFileNames.push_back(string("~/work/samples/" + in));
        } else if (arg_fth == "XSec") {
            f++;
            std::string Xsec(*(argv + f));
            XSec = atof(Xsec.c_str());
        } else if (arg_fth == "Lumi") {
            f++;
            std::string Lumi(*(argv + f));
            Luminosity = atof(Lumi.c_str());
        } else if (arg_fth == "preSelEff") {
            f++;
            std::string preSelEff(*(argv + f));
            PreSelEff = atof(preSelEff.c_str());
        } else if (arg_fth == "JES") {
            f++;
            std::string in(*(argv + f));
            doJES = atof(in.c_str());
        } else if (arg_fth == "isData") {
            f++;
            std::string in(*(argv + f));
            if (in == "yes" || in == "YES" || in == "Yes" || in == "y" || in == "Y")
                isData = true;
            else
                isData = false;

        } else if (arg_fth == "HLTname") {
            f++;
            std::string in(*(argv + f));
            HLTname = in;
            std::cout << HLTname << endl;
        } else if (arg_fth == "ttDecayMode") {
            f++;
            std::string in(*(argv + f));
            ttDecayMode = in;
        }
    }
    //    cout<<doJES<<endl;
    cout << sin_inputFileNames.at(0).c_str() << endl;

    TFile* f = 0;
    TClonesArray* corrMET = 0;

    beginJob();
    TApplication theApp("App", &argc, argv);
    GenSingleTopMaker * genSingleTop = 0;
    for (unsigned int fNumber = 0; fNumber < sin_inputFileNames.size(); fNumber++) {
        cout << "file number " << fNumber + 1 << ": " << sin_inputFileNames.at(fNumber) << endl;
        f = TFile::Open(sin_inputFileNames.at(fNumber).c_str());

        TTree* runTree = (TTree*) f->Get("runTree");
        TTree* eventTree = (TTree*) f->Get("eventTree");



        PracticalEvent * pracEvt = new PracticalEvent(eventTree, runTree);
        pracEvt->eventTree->SetBranchStatus("*", 1);


        if (fillTree) {
            stringstream s("");
            s << (fNumber + 1) << "_" << sin_outFileName_FullSelection;
            sin_out = new TFile(s.str().c_str(), "recreate");
            sin_out->cd();
            eventTree_f = pracEvt->eventTree->CloneTree(0);
            runTree_f = pracEvt->runTree->CloneTree(0);
            if (saveTypeIMET) {
                if (sin_verbosity > 0)
                    cout << "corrMET initiating ... " << endl;
                corrMET = new TClonesArray("TopTree::TRootPFMET", 1000);
                eventTree_f->Branch("PFMET_TypeICorrected", "TClonesArray", &corrMET);
            }

        }

        std::cout << "beforeLoop" << std::endl;

        int ievt = 0;


        while (pracEvt->Next()) {
            //            if(ievt > 1)
            //                break;
            if (!isData && pracEvt->NPGenEvtCollection() != 0 && doTopDiff) {
                //                cout<<"I am here"<<endl;
                genSingleTop = new GenSingleTopMaker((TRootNPGenEvent*) pracEvt->NPGenEvtCollection()->At(0), sin_verbosity);
                if(ttDecayMode == "diMu" && !genSingleTop->isDiMuTt)
                    continue;
                if(ttDecayMode == "muE" && !genSingleTop->isMuETt)
                    continue;
                if(ttDecayMode == "muTau" && !genSingleTop->isMuTauTt)
                    continue;
                if(ttDecayMode == "others" && (genSingleTop->isMuTauTt || genSingleTop->isMuETt || genSingleTop->isDiMuTt))
                    continue;
            }
            if (sin_verbosity > 0) {
                cout << "JES: " << doJES << endl;
            }
            double lumiWeight3D = 1;
            if (pu3D) {
                Lumi3DReWeighting Lumi3DWeights =
                        Lumi3DReWeighting("../../../../TopBrussels/TopTreeAnalysis/macros/PileUpReweighting/pileup_MC_Flat10PlusTail.root",
                        "../../../../TopBrussels/TopTreeAnalysis/macros/PileUpReweighting/pileup_FineBin_2011Data_UpToRun180252.root", "pileup", "pileup");
                Lumi3DWeights.weight3D_init(1.0);


                if (!isData) {
                    //            cout<<"here I am ... "<<pracEvt->Event()<<endl;
                    lumiWeight3D = Lumi3DWeights.weight3D(pracEvt->Event());
                } else lumiWeight3D = 1;
            }

            ievt += lumiWeight3D;
            if (sin_verbosity > 0)
                cout << "*******************************************************************" << endl;

            std::vector<TRootPFJet> myJets_;
            myJets_.clear();
            //            cout<<"I am going to Jet Correction "<<isData<<endl;
            myJets_ = pracEvt->ScaledPFJetCollection(1, isData);
            //            Event myEvent_tmp( myJets_, *pracEvt->ElectronCollection()
            //            ,*pracEvt->METCollection(),*pracEvt->MuonCollection(),*pracEvt->VertexCollection());
            Event myEvent_tmp(myJets_, *pracEvt->ElectronCollection()
                    , pracEvt->TypeICorrMET(), *pracEvt->MuonCollection(), *pracEvt->VertexCollection());
            if (sin_verbosity > 0)
                cout << "PV size: " << myEvent_tmp.pvs.size() << "\n"
                << "Muon size: " << myEvent_tmp.muons.size() << "\n"
                << "Electron size: " << myEvent_tmp.electrons.size() << "\n"
                << "Jet size: " << myEvent_tmp.PFJets.size() << "\n" << endl;
            myEvent_tmp.verbose(sin_verbosity);
            if (sin_verbosity > 0)
                cout << "ScrapFilterMaker-------------------------------------------------------------------" << endl;
            double scrapFilterer = (double) (pracEvt->Event()->nHighPurityTracks()) / (double) (pracEvt->Event()->nTracks());
            if (sin_verbosity > 0)
                cout << "HBHEnoiseFilterMaker-------------------------------------------------------------------" << endl; //?????
            if (sin_verbosity > 0)
                cout << "Vertex Makers ---------------------------------------------------------------------" << endl;
            myEvent_tmp.VertexMaker();
            if (sin_verbosity > 0)
                cout << "Electron Maker ---------------------------------------------------------------------" << endl;
            myEvent_tmp.ElectronMaker();
            /*pt = 30., eta = 2.5,  Exc_Low = 1.4442 , Exc_High = 1.5660, Id = "VBTF70", IdSecond = "VBTF95" (not applied),
             * D0 = 0.02, IsoCut = 0.125, drToPV = 10000.,  secondEIso = 0.2, secPt=15 GeV 
             */


            if (sin_verbosity > 0)
                cout << "Jet Makers ---------------------------------------------------------------------" << endl;
            myEvent_tmp.PFJetMaker(/*bTagAlgo*/"TCHP", /*pt*/30., /*eta*/4.5);
            if (sin_verbosity > 0)
                cout << "Muon Maker ---------------------------------------------------------------------" << endl;
            myEvent_tmp.MuonMaker();
            /*
             * pt = 20.,  eta = 2.1, chi2 = 10,  D0 = 0.02,  nvh = 10, isoCut_ = 0.15,  doGL = false,  
             * nPixWithMeasuredHits = 1,  nSegM = 1
             */
            if (sin_verbosity > 0)
                cout << "START TO SELECT : " << endl;
            sin_n0 += lumiWeight3D;
            if (sin_doScrapFilter) {
                if (scrapFilterer > 0.2) {
                    sin_nScrapFilter += lumiWeight3D;
                    if (sin_verbosity > 0)
                        cout << "\tPassed!! scrapFilterer is " << scrapFilterer << endl;
                } else
                    continue;
            }
            if (sin_doHCALnoiseFilter) {
                if (sin_verbosity > 0)
                    cout << "no Info in TopTrees for this cut :-(" << endl;
            }
            if (sin_doHLT) {
                TopTree::TRootHLTInfo hltInfo = pracEvt->RunInfo()->getHLTinfo(pracEvt->Event()->runId());
                int trigID = hltInfo.hltPath(HLTname);
                //                int trigID = hltInfo.hltPath("");

                if (pracEvt->Event()->trigHLT(trigID)) {
                    sin_nHlt += lumiWeight3D;
                    if (sin_verbosity > 0) {
                        cout << hltInfo.hltNames(trigID) << "\t" << hltInfo.hltWasRun(trigID) <<
                                "\t" << hltInfo.hltAccept(trigID) << endl;
                        cout << "\tHLT is passed" << endl;
                    }
                } else
                    continue;
            }
            if (sin_doPV) {
                if (fillHists)
                    sin_atLeastOnGPV.Fill(myEvent_tmp.pvs, myEvent_tmp.Gpvs.size(), lumiWeight3D);
                if (myEvent_tmp.Gpvs.size() > 0) {
                    sin_nPV += lumiWeight3D;
                    if (sin_verbosity > 0)
                        cout << "\tPVCut Passed" << endl;
                } else
                    continue;
            }

            if (sin_doMuon) {
                if (fillHists)
                    sin_MuSelection.Fill(myEvent_tmp.muons, myEvent_tmp.Dmuons.size(), lumiWeight3D);
                if (myEvent_tmp.Dmuons.size() == 1) {
                    sin_nMu += lumiWeight3D;
                    if (sin_verbosity > 0)
                        cout << "\tMu selection Passed" << endl;
                } else
                    continue;
            }
            if (sin_doLMuVeto) {
                if (fillHists)
                    sin_LMuVeto.Fill(myEvent_tmp.looseMuons, myEvent_tmp.looseMuons.size(), lumiWeight3D);
                if (myEvent_tmp.looseMuons.size() == 0) {
                    sin_nNoLMu += lumiWeight3D;
                    if (sin_verbosity > 0)
                        cout << "\tlooseMuVeto is passed" << endl;
                } else
                    continue;
            }
            TRootMuon myMu = myEvent_tmp.Dmuons.at(0);
            double relIso = (myMu.chargedHadronIso() + myMu.neutralHadronIso() + myMu.photonIso()) / myMu.Pt();
            if (sin_doLEVeto) {
                if (myEvent_tmp.Gelectrons.size() == 0 && myEvent_tmp.Secondelectrons.size() == 0) {
                    sin_nNoLE += lumiWeight3D;
                    if (sin_verbosity > 0)
                        cout << "\tlooseEVeto is passed" << endl;
                } else
                    continue;
            }
            if (TopPairtemplate && !isTtLike(myEvent_tmp, 3.41, 2))
                continue;
            //            if(fillTree){
            //                if(saveTypeIMET)
            //                    if(sin_verbosity>0) cout << endl << "Analyzing ParticleFlow Missing Et..." << endl;
            //                if(saveTypeIMET)
            //                    new( (*corrMET)[0] ) TRootPFMET(pracEvt->TypeICorrMET());
            //                eventTree_f->Fill();
            //                if(saveTypeIMET) 
            //                    (*corrMET).Delete();
            //            }
            if (sin_dojet) {
                if (fillHists)
                    sin_Jets.FillPFJets(myEvent_tmp.PFJets, myEvent_tmp.GPFJets.size(), myEvent_tmp.BPFJets.size());
                if (myEvent_tmp.GPFJets.size() == 2) {
                    sin_nJet += lumiWeight3D;
                    if (sin_verbosity > 0) {
                        cout << "\t==2 Jet Passed" << endl;
                    }
                } else
                    continue;
            }
            double mt = 0;
            if (sin_doMT) {
                double metT = sqrt((myEvent_tmp.mets.at(0).Px() * myEvent_tmp.mets.at(0).Px())+
                        (myEvent_tmp.mets.at(0).Py() * myEvent_tmp.mets.at(0).Py()));

                double muT = sqrt((myEvent_tmp.Dmuons.at(0).Px() * myEvent_tmp.Dmuons.at(0).Px())+
                        (myEvent_tmp.Dmuons.at(0).Py() * myEvent_tmp.Dmuons.at(0).Py()));
                mt = sqrt(pow(muT + metT, 2) - pow(myEvent_tmp.mets.at(0).Px() + myEvent_tmp.Dmuons.at(0).Px(), 2)
                        - pow(myEvent_tmp.mets.at(0).Py() + myEvent_tmp.Dmuons.at(0).Py(), 2));
                if (fillHists)
                    MT->Fill(mt, lumiWeight3D);
                if (mt > 40) {
                    sin_nMT += lumiWeight3D;
                    if (sin_verbosity > 0)
                        cout << "\tM_T cut is passed" << endl;
                } else
                    continue;
            }
            if (sin_doBtag) {
                if (fillHists)
                    sin_BJets.FillPFJets(myEvent_tmp.GPFJets, myEvent_tmp.GPFJets.size(), myEvent_tmp.BPFJets.size(), false, lumiWeight3D);
                if (myEvent_tmp.BPFJets.size() == 1) {
                    sin_nBtag += lumiWeight3D;
                    if (sin_verbosity > 0)
                        cout << "\t== 1bTag Passed" << endl;
                } else
                    continue;
            }
            if (Wtemplate && !isWJetLike(myEvent_tmp))
                continue;
            sin_nWlike += lumiWeight3D;
            if (fillTree) {
                if (saveTypeIMET)
                    if (sin_verbosity > 0) cout << endl << "Analyzing ParticleFlow Missing Et..." << endl;
                if (saveTypeIMET)
                    new( (*corrMET)[0]) TRootPFMET(pracEvt->TypeICorrMET());
                eventTree_f->Fill();
                if (saveTypeIMET)
                    (*corrMET).Delete();
            }
            if (fillHists) {
                sin_GoldenFinalMuons.Fill(myEvent_tmp.Dmuons, myEvent_tmp.Dmuons.size(), lumiWeight3D);
                finalMT->Fill(mt, lumiWeight3D);
            }
            if(genSingleTop != NULL)
                delete genSingleTop;
        }
        runTree_f->Fill();
        cout << "before closing file input " << f->GetName() << endl;
        f->Close();
        delete f;

        if (fillTree) {
            sin_out->cd();
            sin_out->Write();
            sin_out->Close();
        }
    }
    cout << "before endjob" << endl;
    endJob();
    return 0;
}
