/* 
 * File:   HistogramCreator.C
 * Author: nadjieh
 *
 * Created on March 12, 2012, 2:51 PM
 */
//same as SelectAndSave with less complexities. Aimed to run on selected samples.

#include "TDirectory.h"
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
#include "../../interface/BTagWeight.h"

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
#include "../../../../AnalysisClasses/EventSelection/interface/UnclusteredMETUncertainty.h"
#include "../../../../AnalysisClasses/EventSelection/interface/DifferentHistogramsTwb.h"
#include "../../../../AnalysisClasses/ToyAnalysis/interface/GenSingleTopMaker.h"
#include "../../../../TopBrussels/TopTreeAnalysis/MCInformation/interface/Lumi3DReWeighting.h"




#include <sstream>
#include <string>

#include <TApplication.h>
#include <TFile.h>
#include <TH1.h>
#include <TH2.h>
#include <TH3.h>
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

    PVHists atLeastOnGPV("DefW_PV");
    JetHists Jets("DefW_Jet", 2);
    JetHists BJets("DefW_BJet", 2);
    JetHists nonBJets("DefW_nonBJet", 2);
    JetHists FwDJet("DefW_FwD", 2);
    MuonHists GoldenFinalPUMuons("DefW_Muon");
    MetHists MetHist("DefW_Met");

    PVHists atLeastOnGPV_PuW("PuW_PV");
    JetHists Jets_PuW("PuW_Jet", 2);
    JetHists BJets_PuW("PuW_BJet", 2);
    JetHists nonBJets_PuW("PuW_nonBJet", 2);
    JetHists FwDJet_PuW("PuW_FwD", 2);
    MuonHists GoldenFinalPUMuons_PuW("PuW_Muon");
    MetHists MetHist_PuW("PuW_Met");

    PVHists atLeastOnGPV_BtagPuW("BtagPuW_PV");
    JetHists Jets_BtagPuW("BtagPuW_Jet", 2);
    JetHists BJets_BtagPuW("BtagPuW_BJet", 2);
    JetHists nonBJets_BtagPuW("BtagPuW_nonBJet", 2);
    JetHists FwDJet_BtagPuW("BtagPuW_FwD", 2);
    MuonHists GoldenFinalPUMuons_BtagPuW("BtagPuW_Muon");
    MetHists MetHist_BtagPuW("BtagPuW_Met");

    PVHists atLeastOnGPV_allW("allW_PV");
    JetHists Jets_allW("allW_Jet", 2);
    JetHists BJets_allW("allW_BJet", 2);
    JetHists nonBJets_allW("allW_nonBJet", 2);
    JetHists FwDJet_allW("allW_FwD", 2);
    MuonHists GoldenFinalPUMuons_allW("allW_Muon");
    MetHists MetHist_allW("allW_Met");

    SingleTopHistograms Default_Def("Default_Def");
    SingleTopHistograms EtaCut_Def("EtaFwD_Def");
    SingleTopHistograms HtCut_Def("HtCut_Def");
    SingleTopHistograms AntiEtaCut_Def("antiEtaFwD_Def");
    SingleTopHistograms AntiHtCut_Def("antiHtCut_Def");

    SingleTopHistograms DefaultTrue_Def("DefaultTrue_Def");
    SingleTopHistograms EtaCutTrue_Def("EtaFwDTrue_Def");
    SingleTopHistograms HtCutTrue_Def("HtCutTrue_Def");
    SingleTopHistograms AntiEtaCutTrue_Def("antiEtaFwDTrue_Def");
    SingleTopHistograms AntiHtCutTrue_Def("antiHtCutTrue_Def");

    SingleTopHistograms Default_PuW("Default_PuW");
    SingleTopHistograms Default_BtagPuW("Default_BtagPuW");
    SingleTopHistograms Default_allW("Default_allW");

    SingleTopHistograms EtaCut_PuW("EtaFwD_PuW");
    SingleTopHistograms EtaCut_BtagPuW("EtaFwD_BtagPuW");
    SingleTopHistograms EtaCut_allW("EtaFwD_allW");

    SingleTopHistograms DefaultTrue_PuW("DefaultTrue_PuW");
    SingleTopHistograms DefaultTrue_BtagPuW("DefaultTrue_BtagPuW");
    SingleTopHistograms DefaultTrue_allW("DefaultTrue_allW");

    SingleTopHistograms EtaCutTrue_PuW("EtaFwDTrue_PuW");
    SingleTopHistograms EtaCutTrue_BtagPuW("EtaFwDTrue_BtagPuW");
    SingleTopHistograms EtaCutTrue_allW("EtaFwDTrue_allW");

    DiLeptonHistograms DiLep_Default_Def("Default_Def");
    DiLeptonHistograms DiLep_EtaCut_Def("EtaFwD_Def");
    DiLeptonHistograms DiLep_HtCut_Def("HtCut_Def");
    DiLeptonHistograms DiLep_AntiEtaCut_Def("antiEtaFwD_Def");
    DiLeptonHistograms DiLep_AntiHtCut_Def("antiHtCut_Def");

    DiLeptonHistograms DiLep_DefaultTrue_Def("DefaultTrue_Def");
    DiLeptonHistograms DiLep_EtaCutTrue_Def("EtaFwDTrue_Def");
    DiLeptonHistograms DiLep_HtCutTrue_Def("HtCutTrue_Def");
    DiLeptonHistograms DiLep_AntiEtaCutTrue_Def("antiEtaFwDTrue_Def");
    DiLeptonHistograms DiLep_AntiHtCutTrue_Def("antiHtCutTrue_Def");

    DiLeptonHistograms DiLep_Default_PuW("Default_PuW");
    DiLeptonHistograms DiLep_Default_BtagPuW("Default_BtagPuW");
    DiLeptonHistograms DiLep_Default_allW("Default_allW");

    DiLeptonHistograms DiLep_EtaCut_PuW("EtaFwD_PuW");
    DiLeptonHistograms DiLep_EtaCut_BtagPuW("EtaFwD_BtagPuW");
    DiLeptonHistograms DiLep_EtaCut_allW("EtaFwD_allW");

    DiLeptonHistograms DiLep_DefaultTrue_PuW("DefaultTrue_PuW");
    DiLeptonHistograms DiLep_DefaultTrue_BtagPuW("DefaultTrue_BtagPuW");
    DiLeptonHistograms DiLep_DefaultTrue_allW("DefaultTrue_allW");

    DiLeptonHistograms DiLep_EtaCutTrue_PuW("EtaFwDTrue_PuW");
    DiLeptonHistograms DiLep_EtaCutTrue_BtagPuW("EtaFwDTrue_BtagPuW");
    DiLeptonHistograms DiLep_EtaCutTrue_allW("EtaFwDTrue_allW");


    TH1D * HT = new TH1D("HT", "H_{T};H_{T}(GeV)", 500, 0., 500.);
    TH1D * def_finalMT = new TH1D("def_finalMT", "final-W-neutrino transverse mass", 100, 0., 200.);
    def_finalMT->GetXaxis()->SetTitle("M_{T}(W,#nu)");
    TH1D * PuW_finalMT = new TH1D("PuW_finalMT", "final-W-neutrino transverse mass", 100, 0., 200.);
    PuW_finalMT->GetXaxis()->SetTitle("M_{T}(W,#nu)");
    TH1D * BtagPuW_finalMT = new TH1D("BtagPuW_finalMT", "final-W-neutrino transverse mass", 100, 0., 200.);
    BtagPuW_finalMT->GetXaxis()->SetTitle("M_{T}(W,#nu)");
    TH1D * allW_finalMT = new TH1D("allW_finalMT", "final-W-neutrino transverse mass", 100, 0., 200.);
    allW_finalMT->GetXaxis()->SetTitle("M_{T}(W,#nu)");
    TH1D * delNu = new TH1D("delNu", "delNu", 100, 0., 100.);
    delNu->GetXaxis()->SetTitle("#Delta#nu");
    TH1D * delNuII = new TH1D("delNuMET", "delNuMET", 100, 0., 100.);
    delNuII->GetXaxis()->SetTitle("#Delta#nu");
    std::vector<std::string> inputFileNames;
    std::string plotFileName;
    int verbosity = 0;
    TH1D * METResolutions = 0;
    std::string HLTname = "HLT_IsoMu17_v*";
    bool pu3D = true;
    string PUWeightFileName = "";
    double XSec = 1;
    double Luminosity = 1;
    double PreSelEff = 1;
    double doJES = 0;
    double doUnclMET = 0;
    string ttDecayMode = "";
    int btagSyst = 0;
    bool isData = false;
    int smearingSkim = 1;
    string puAddress = "~/work/TopBrussels/TopTreeAnalysis/macros/PileUpReweighting/";
    string MCpuFile = "";
    string DataPuFile = "Central-unps_paper_finebin_Pileup.root";
    for (int f = 1; f < argc; f++) {
        std::string arg_fth(*(argv + f));

        if (arg_fth == "out") {
            f++;
            std::string out(*(argv + f));
            plotFileName = out;
        } else if (arg_fth == "input") {
            f++;
            std::string in(*(argv + f));
            inputFileNames.push_back(string("~/work/samples/" + in));
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
        } else if (arg_fth == "METResolFileName") {
            f++;
            std::string in(*(argv + f));
            TFile * METResolFileName = TFile::Open(in.c_str());
            METResolutions = (TH1D*) METResolFileName->Get("METresolutions");
        } else if (arg_fth == "HLTname") {
            f++;
            std::string in(*(argv + f));
            HLTname = in;
            std::cout << HLTname << endl;
        } else if (arg_fth == "PUWeightFileName") {
            f++;
            std::string in(*(argv + f));
            PUWeightFileName = in;
            std::cout << HLTname << endl;
        } else if (arg_fth == "dataPUoption") {
            f++;
            std::string in(*(argv + f));
            DataPuFile = in;
        } else if (arg_fth == "puOption") {
            f++;
            std::string in(*(argv + f));
            MCpuFile = in;
        } else if (arg_fth == "smearingSkim") {
            f++;
            std::string in(*(argv + f));
            smearingSkim = atof(in.c_str());
        } else if (arg_fth == "unclMET") {
            f++;
            std::string in(*(argv + f));
            doUnclMET = atof(in.c_str());
        } else if (arg_fth == "ttDecayMode") {
            f++;
            std::string in(*(argv + f));
            ttDecayMode = in;
        } else if (arg_fth == "bTag") {
            f++;
            std::string in(*(argv + f));
            btagSyst = atof(in.c_str());
        }
    }
    MCpuFile = puAddress + MCpuFile;
    DataPuFile = puAddress + DataPuFile;
    TFile* f = 0;
    TApplication theApp("App", &argc, argv);
    double nInit = 0;
    double nFinalPU = 0;
    double nFinalHLT = 0;
    double nFinalbTag = 0;
    double nFinal = 0;
    double nHLTrunB = 0;
    double nMt = 0;
    double nGoodSolution = 0;
    Lumi3DReWeighting Lumi3DWeights;
    cout << "=====================================================================" << endl;
    cout << "Parameters:\n\tInput: " << inputFileNames.at(0);
    if (isData)
        cout << "\tis data" << endl;
    else
        cout << "\tis MC" << endl;
    cout << "\tOutput: " << plotFileName << endl;
    cout << "\tTop decay mode: " << ttDecayMode << endl;
    cout << "\tJES: " << doJES << "\t\t";
    if (doJES == 0)
        cout << "No JES systematics" << endl;
    else if (doJES > 0)
        cout << "UP JES systematics" << endl;
    else
        cout << "DOWN JES systematics" << endl;
    cout << "\tData pile-up: " << DataPuFile << "\n\t\t";
    if (DataPuFile.find("Low") > 0 && DataPuFile.find("Low") < DataPuFile.size())
        cout << "DOWN pile-up systematics" << endl;
    else if (DataPuFile.find("High") > 0 && DataPuFile.find("High") < DataPuFile.size())
        cout << "UP pile-up systematics" << endl;
    else
        cout << "No pile-up systematics" << endl;
    cout << "\tMC pile-up: " << MCpuFile;
    if (MCpuFile.find("Fall") > 0 && MCpuFile.find("Fall") < MCpuFile.size())
        cout << "\n\t\tFall11 pile-up" << endl;
    else
        cout << "\n\t\tSummer11 pile-up" << endl;
    cout << "\tunclMET: " << doUnclMET << "\n\t\t";
    if (doUnclMET == 0)
        cout << "No unclMET systematics" << endl;
    else if (doUnclMET > 0)
        cout << "UP unclMET systematics" << endl;
    else
        cout << "DOWN unclMET systematics" << endl;
    cout << "\tbTag: " << btagSyst << "\n\t\t";
    if (btagSyst == 0)
        cout << "No bTag systematics" << endl;
    else if (btagSyst > 0)
        cout << "UP bTag systematics" << endl;
    else
        cout << "DOWN bTag systematics" << endl;
    cout << "=====================================================================" << endl;

    if (pu3D && !isData) {
        //        Lumi3DWeights.weight3D_set("../../../../TopBrussels/TopTreeAnalysis/macros/PileUpReweighting//MC_Fall11.root",
        //    "../../../../TopBrussels/TopTreeAnalysis/macros/PileUpReweighting/RunAB.root", "pileup", "pileup");
        Lumi3DWeights.weight3D_set(MCpuFile, DataPuFile, "pileup", "pileup");
        Lumi3DWeights.setWFileName(PUWeightFileName);
        Lumi3DWeights.weight3D_init(1.0);
        //    Lumi3DWeights.weight3D_init(PUWeightFileName);
    }
    TFile * HLTweights = TFile::Open("~/work/AnalysisClasses/EventSelection/macro/HLT_IsoMu17_W.root");
    TH1D * HLTWeights = (TH1D*) HLTweights->Get("weight");
    GenSingleTopMaker* genSingleTop = 0;
    UnclusteredEnergyUnc* myUnclMET = 0;
    for (unsigned int fNumber = 0; fNumber < inputFileNames.size(); fNumber++) {
        cout << "file number " << fNumber + 1 << ": " << inputFileNames.at(fNumber) << endl;
        f = TFile::Open(inputFileNames.at(fNumber).c_str());

        TTree* runTree = (TTree*) f->Get("runTree");
        TTree* eventTree = (TTree*) f->Get("eventTree");



        PracticalEvent * pracEvt = new PracticalEvent(eventTree, runTree);
        pracEvt->eventTree->SetBranchStatus("*", 1);

        std::cout << "beforeLoop" << std::endl;

        int ievt = 0;

        while (pracEvt->Next()) {

            ievt++;

            /* for single top genAnalysis
             * not to be used for real one
             */
            if (!isData && pracEvt->NPGenEvtCollection() != 0) {
                //                cout<<"I am here"<<endl;
                genSingleTop = new GenSingleTopMaker((TRootNPGenEvent*) pracEvt->NPGenEvtCollection()->At(0), verbosity);
            }
            double puOnlyW = 1;
            double btagpuW = 1;
            double lumiWeight3D = 1;
            if (pu3D) {
                if (!isData) {
                    //            cout<<"here I am ... "<<pracEvt->Event()<<endl;
                    lumiWeight3D = Lumi3DWeights.weight3D(pracEvt->Event());
                } else lumiWeight3D = 1;
            }
            puOnlyW = lumiWeight3D;
            //            cout<<lumiWeight3D<<endl;
            nInit += lumiWeight3D;
            //            nInit++;
            if (verbosity > 0)
                cout << ievt << "*******************************************************************" << endl;

            if (doUnclMET != 0) {
                myUnclMET = new UnclusteredEnergyUnc(pracEvt, 0.1);
                pracEvt->setDefaultMET(myUnclMET->getChangedUncEnergyMET(doUnclMET));
                delete myUnclMET;
            } else {
                pracEvt->setDefaultMET(*(TRootPFMET*) pracEvt->METCollection()->At(0));
            }
            std::vector<TRootPFJet> myJets_;
            myJets_.clear();
            //            cout<<"I am going to Jet Correction "<<isData<<endl;
            myJets_ = pracEvt->ScaledPFJetCollection(1, isData, doJES);

            Event myEvent_tmp(myJets_, *pracEvt->ElectronCollection()
                    , pracEvt->TypeICorrMET(), *pracEvt->MuonCollection(), *pracEvt->VertexCollection());
            //            Event myEvent_tmp(myJets_, *pracEvt->ElectronCollection()
            //                    , *pracEvt->Ty(), *pracEvt->MuonCollection(), *pracEvt->VertexCollection());


            if (verbosity > 0)
                cout << "PV size: " << myEvent_tmp.pvs.size() << "\n"
                << "Muon size: " << myEvent_tmp.muons.size() << "\n"
                << "Electron size: " << myEvent_tmp.electrons.size() << "\n"
                << "Jet size: " << myEvent_tmp.PFJets.size() << "\n" << endl;
            myEvent_tmp.verbose(verbosity);
            if (verbosity > 0)
                cout << "ScrapFilterMaker-------------------------------------------------------------------" << endl;
            double scrapFilterer = (double) (pracEvt->Event()->nHighPurityTracks()) / (double) (pracEvt->Event()->nTracks());
            if (verbosity > 0)
                cout << "HBHEnoiseFilterMaker-------------------------------------------------------------------" << endl; //?????
            if (verbosity > 0)
                cout << "Vertex Makers ---------------------------------------------------------------------" << endl;
            myEvent_tmp.VertexMaker();
            if (verbosity > 0)
                cout << "Electron Maker ---------------------------------------------------------------------" << endl;
            myEvent_tmp.ElectronMaker();
            /*pt = 30., eta = 2.5,  Exc_Low = 1.4442 , Exc_High = 1.5660, Id = "VBTF70", IdSecond = "VBTF95" (not applied),
             * D0 = 0.02, IsoCut = 0.125, drToPV = 10000.,  secondEIso = 0.2, secPt=15 GeV 
             */


            if (verbosity > 0)
                cout << "Jet Makers ---------------------------------------------------------------------" << endl;
            myEvent_tmp.PFJetMaker(/*bTagAlgo*/"TCHP", /*pt*/30., /*eta*/4.5);
            if (verbosity > 0)
                cout << "Muon Maker ---------------------------------------------------------------------" << endl;
            //            myEvent_tmp.MuonMaker(20, 2.1, 10, 1000, 10, 0.5);
            myEvent_tmp.MuonMaker();
            /*
             * pt = 20.,  eta = 2.1, chi2 = 10,  D0 = 0.02,  nvh = 10, isoCut_ = 0.15,  doGL = false,  
             * nPixWithMeasuredHits = 1,  nSegM = 1
             */
            if (verbosity > 0)
                cout << "START TO SELECT : " << endl;
            if (scrapFilterer > 0.2) {
                if (verbosity > 0)
                    cout << "\tPassed!! scrapFilterer is " << scrapFilterer << endl;
            } else
                continue;

            if (myEvent_tmp.passPVsel) {
                if (verbosity > 0)
                    cout << "\tPVCut Passed" << endl;
            } else
                continue;

            if (myEvent_tmp.Dmuons.size() == 1) {
                if (verbosity > 0)
                    cout << "\tMu selection Passed" << endl;
            } else
                continue;

            if (myEvent_tmp.looseMuons.size() == 0) {
                if (verbosity > 0)
                    cout << "\tlooseMuVeto is passed" << endl;
            } else
                continue;

            if (myEvent_tmp.Gelectrons.size() == 0 && myEvent_tmp.Secondelectrons.size() == 0) {
                if (verbosity > 0)
                    cout << "\tlooseEVeto is passed" << endl;
            } else
                continue;

            if (myEvent_tmp.GPFJets.size() == 2) {
                if (verbosity > 0) {
                    cout << "\t==2 Jet Passed" << endl;
                }
            } else
                continue;
            double mt = 0;
            double metT = sqrt((myEvent_tmp.mets.at(0).Px() * myEvent_tmp.mets.at(0).Px())+
                    (myEvent_tmp.mets.at(0).Py() * myEvent_tmp.mets.at(0).Py()));

            double muT = sqrt((myEvent_tmp.Dmuons.at(0).Px() * myEvent_tmp.Dmuons.at(0).Px())+
                    (myEvent_tmp.Dmuons.at(0).Py() * myEvent_tmp.Dmuons.at(0).Py()));
            mt = sqrt(pow(muT + metT, 2) - pow(myEvent_tmp.mets.at(0).Px() + myEvent_tmp.Dmuons.at(0).Px(), 2)
                    - pow(myEvent_tmp.mets.at(0).Py() + myEvent_tmp.Dmuons.at(0).Py(), 2));
            if (mt > 40) {
                //                nMt++;
                nMt += lumiWeight3D;
                if (verbosity > 0)
                    cout << "\tM_T cut is passed" << endl;
            } else
                continue;

            if (myEvent_tmp.BPFJets.size() == 1) {
                if (verbosity > 0)
                    cout << "\t== 1bTag Passed" << endl;
            } else
                continue;
            /*btag sf*/
            nFinalPU += lumiWeight3D;
            //            cout<<"pu: "<<lumiWeight3D<<"\t";
            double bw = 1;
            if (!isData) {
                double sf, eff;
                BTagWeight myBtagWeight;
                vector< vector<BTagWeight::JetInfo> > jInfosToReWeight(myEvent_tmp.GPFJets.size());
                for (int iJet = 0; iJet < myEvent_tmp.GPFJets.size(); iJet++) {
                    BTagWeight::GetEffSF_TCHPT(myEvent_tmp.GPFJets[iJet].Pt(),
                            myEvent_tmp.GPFJets[iJet].Eta(),
                            myEvent_tmp.GPFJets[iJet].btag_trackCountingHighPurBJetTags(),
                            myEvent_tmp.GPFJets[iJet].partonFlavour(),
                            eff, sf, btagSyst);
                    BTagWeight::JetInfo jinfo(eff, sf);
                    jInfosToReWeight[iJet].push_back(jinfo);
                }
                bw *= myBtagWeight.weight(jInfosToReWeight);
            }
            //            cout<<"bw: "<<bw<<"\t";
            btagpuW = puOnlyW*bw;
            lumiWeight3D *= bw;

            nFinalbTag += bw;
            /*HLT sf*/
            double hltW = 1;
            if (!isData) {
                int bin = HLTWeights->GetXaxis()->FindBin(myEvent_tmp.Dmuons.at(0).Eta());
                if (bin > 0 && bin < 13)
                    hltW = HLTWeights->GetBinContent(bin);
                else
                    hltW = 1.;
            }
            lumiWeight3D *= hltW;
            //            cout<<"hlt: "<<hltW<<endl;
            nFinalHLT += hltW;

            nFinal += lumiWeight3D;

            int mySecondJetIndex = 0;
            if (mySecondJetIndex == myEvent_tmp.firstBtagIndex)
                mySecondJetIndex = 1;
            std::vector<TRootPFJet> nonBs;
            nonBs.push_back(myEvent_tmp.GPFJets.at(mySecondJetIndex));
            std::vector<TRootPFJet> sortedJetsbyEta;
            sortedJetsbyEta.push_back(myEvent_tmp.SortedJetsByEta().at(0));
            //Reweighting process
            if (myEvent_tmp.BPFJets.size() == 0) {
                myEvent_tmp.BPFJets.clear();
                if ((ievt % 2) == 0)
                    myEvent_tmp.BPFJets.push_back(myEvent_tmp.GPFJets.at(0));
                else
                    myEvent_tmp.BPFJets.push_back(myEvent_tmp.GPFJets.at(1));
            }
            SemiLepTopQuark myLeptonicTop(myEvent_tmp.BPFJets.at(0), myEvent_tmp.mets.at(0), myEvent_tmp.Dmuons.at(0),
                    myEvent_tmp.GPFJets.at(mySecondJetIndex), sortedJetsbyEta.at(0), METResolutions);
            myLeptonicTop.setMuCharge((int) myEvent_tmp.Dmuons.at(0).charge());
            double eta = fabs(sortedJetsbyEta.at(0).Eta());
            double ht = myEvent_tmp.GPFJets.at(0).Pt() + myEvent_tmp.GPFJets.at(1).Pt();


            ht += myEvent_tmp.Dmuons.at(0).Pt();
            ht += myEvent_tmp.mets.at(0).Pt();
            HT->Fill(ht, lumiWeight3D);
            if (ttDecayMode == "") {
                if (myLeptonicTop.hasNeutrinoSolution()) {
                    nGoodSolution++;
                    DefaultTrue_Def.Fill(myLeptonicTop, 1, genSingleTop);

                    DefaultTrue_PuW.Fill(myLeptonicTop, puOnlyW, genSingleTop);
                    DefaultTrue_BtagPuW.Fill(myLeptonicTop, btagpuW, genSingleTop);
                    DefaultTrue_allW.Fill(myLeptonicTop, lumiWeight3D, genSingleTop);

                    if (ht >= 180)
                        HtCutTrue_Def.Fill(myLeptonicTop, 1, genSingleTop);
                    else
                        AntiHtCutTrue_Def.Fill(myLeptonicTop, 1, genSingleTop);
                    if (eta > 1.5) {
                        EtaCutTrue_Def.Fill(myLeptonicTop, 1, genSingleTop);

                        EtaCutTrue_PuW.Fill(myLeptonicTop, puOnlyW, genSingleTop);
                        EtaCutTrue_BtagPuW.Fill(myLeptonicTop, btagpuW, genSingleTop);
                        EtaCutTrue_allW.Fill(myLeptonicTop, lumiWeight3D, genSingleTop);
                    } else
                        AntiEtaCutTrue_Def.Fill(myLeptonicTop, 1, genSingleTop);
                }
                Default_Def.Fill(myLeptonicTop, 1, genSingleTop);

                Default_PuW.Fill(myLeptonicTop, puOnlyW, genSingleTop);
                Default_BtagPuW.Fill(myLeptonicTop, btagpuW, genSingleTop);
                Default_allW.Fill(myLeptonicTop, lumiWeight3D, genSingleTop);

                if (ht >= 180)
                    HtCut_Def.Fill(myLeptonicTop, 1, genSingleTop);
                else
                    AntiHtCut_Def.Fill(myLeptonicTop, 1, genSingleTop);
                if (eta > 1.5) {
                    EtaCut_Def.Fill(myLeptonicTop, 1, genSingleTop);

                    EtaCut_PuW.Fill(myLeptonicTop, puOnlyW, genSingleTop);
                    EtaCut_BtagPuW.Fill(myLeptonicTop, btagpuW, genSingleTop);
                    EtaCut_allW.Fill(myLeptonicTop, lumiWeight3D, genSingleTop);
                } else
                    AntiEtaCut_Def.Fill(myLeptonicTop, 1, genSingleTop);
            } else {//Dimuon, muTau, muE TtBar
                if (myLeptonicTop.hasNeutrinoSolution()) {
                    nGoodSolution++;
                    DiLep_DefaultTrue_Def.Fill(myLeptonicTop, 1, genSingleTop);

                    DiLep_DefaultTrue_PuW.Fill(myLeptonicTop, puOnlyW, genSingleTop);
                    DiLep_DefaultTrue_BtagPuW.Fill(myLeptonicTop, btagpuW, genSingleTop);
                    DiLep_DefaultTrue_allW.Fill(myLeptonicTop, lumiWeight3D, genSingleTop);

                    if (ht >= 180)
                        DiLep_HtCutTrue_Def.Fill(myLeptonicTop, 1, genSingleTop);
                    else
                        DiLep_AntiHtCutTrue_Def.Fill(myLeptonicTop, 1, genSingleTop);
                    if (eta > 1.5) {
                        DiLep_EtaCutTrue_Def.Fill(myLeptonicTop, 1, genSingleTop);

                        DiLep_EtaCutTrue_PuW.Fill(myLeptonicTop, puOnlyW, genSingleTop);
                        DiLep_EtaCutTrue_BtagPuW.Fill(myLeptonicTop, btagpuW, genSingleTop);
                        DiLep_EtaCutTrue_allW.Fill(myLeptonicTop, lumiWeight3D, genSingleTop);
                    } else
                        DiLep_AntiEtaCutTrue_Def.Fill(myLeptonicTop, 1, genSingleTop);
                }
                DiLep_Default_Def.Fill(myLeptonicTop, 1, genSingleTop);

                DiLep_Default_PuW.Fill(myLeptonicTop, puOnlyW, genSingleTop);
                DiLep_Default_BtagPuW.Fill(myLeptonicTop, btagpuW, genSingleTop);
                DiLep_Default_allW.Fill(myLeptonicTop, lumiWeight3D, genSingleTop);

                if (ht >= 180)
                    DiLep_HtCut_Def.Fill(myLeptonicTop, 1, genSingleTop);
                else
                    DiLep_AntiHtCut_Def.Fill(myLeptonicTop, 1, genSingleTop);
                if (eta > 1.5) {
                    DiLep_EtaCut_Def.Fill(myLeptonicTop, 1, genSingleTop);

                    DiLep_EtaCut_PuW.Fill(myLeptonicTop, puOnlyW, genSingleTop);
                    DiLep_EtaCut_BtagPuW.Fill(myLeptonicTop, btagpuW, genSingleTop);
                    DiLep_EtaCut_allW.Fill(myLeptonicTop, lumiWeight3D, genSingleTop);
                } else
                    DiLep_AntiEtaCut_Def.Fill(myLeptonicTop, 1, genSingleTop);
            }

            if (genSingleTop != NULL)
                delete genSingleTop;

            atLeastOnGPV.Fill(myEvent_tmp.Gpvs, myEvent_tmp.Gpvs.size(), 1);
            GoldenFinalPUMuons.Fill(myEvent_tmp.Dmuons, myEvent_tmp.Dmuons.size(), 1);
            Jets.FillPFJets(myEvent_tmp.GPFJets, myEvent_tmp.GPFJets.size(), myEvent_tmp.BPFJets.size(), false, 1);
            BJets.FillPFJets(myEvent_tmp.BPFJets, myEvent_tmp.BPFJets.size(), myEvent_tmp.BPFJets.size(), false, 1);
            nonBJets.FillPFJets(nonBs, nonBs.size(), myEvent_tmp.BPFJets.size(), false, 1);
            FwDJet.FillPFJets(sortedJetsbyEta, sortedJetsbyEta.size(), myEvent_tmp.BPFJets.size(), false, 1);
            MetHist.Fill(&myEvent_tmp.mets.at(0), 1);
            def_finalMT->Fill(mt, 1);

            atLeastOnGPV_PuW.Fill(myEvent_tmp.Gpvs, myEvent_tmp.Gpvs.size(), puOnlyW);
            GoldenFinalPUMuons_PuW.Fill(myEvent_tmp.Dmuons, myEvent_tmp.Dmuons.size(), puOnlyW);
            Jets_PuW.FillPFJets(myEvent_tmp.GPFJets, myEvent_tmp.GPFJets.size(), myEvent_tmp.BPFJets.size(), false, puOnlyW);
            BJets_PuW.FillPFJets(myEvent_tmp.BPFJets, myEvent_tmp.BPFJets.size(), myEvent_tmp.BPFJets.size(), false, puOnlyW);
            nonBJets_PuW.FillPFJets(nonBs, nonBs.size(), myEvent_tmp.BPFJets.size(), false, puOnlyW);
            FwDJet_PuW.FillPFJets(sortedJetsbyEta, sortedJetsbyEta.size(), myEvent_tmp.BPFJets.size(), false, puOnlyW);
            MetHist_PuW.Fill(&myEvent_tmp.mets.at(0), puOnlyW);
            PuW_finalMT->Fill(mt, puOnlyW);

            atLeastOnGPV_BtagPuW.Fill(myEvent_tmp.Gpvs, myEvent_tmp.Gpvs.size(), btagpuW);
            GoldenFinalPUMuons_BtagPuW.Fill(myEvent_tmp.Dmuons, myEvent_tmp.Dmuons.size(), btagpuW);
            Jets_BtagPuW.FillPFJets(myEvent_tmp.GPFJets, myEvent_tmp.GPFJets.size(), myEvent_tmp.BPFJets.size(), false, btagpuW);
            BJets_BtagPuW.FillPFJets(myEvent_tmp.BPFJets, myEvent_tmp.BPFJets.size(), myEvent_tmp.BPFJets.size(), false, btagpuW);
            nonBJets_BtagPuW.FillPFJets(nonBs, nonBs.size(), myEvent_tmp.BPFJets.size(), false, btagpuW);
            FwDJet_BtagPuW.FillPFJets(sortedJetsbyEta, sortedJetsbyEta.size(), myEvent_tmp.BPFJets.size(), false, btagpuW);
            MetHist_BtagPuW.Fill(&myEvent_tmp.mets.at(0), btagpuW);
            BtagPuW_finalMT->Fill(mt, btagpuW);

            atLeastOnGPV_allW.Fill(myEvent_tmp.Gpvs, myEvent_tmp.Gpvs.size(), lumiWeight3D);
            GoldenFinalPUMuons_allW.Fill(myEvent_tmp.Dmuons, myEvent_tmp.Dmuons.size(), lumiWeight3D);
            Jets_allW.FillPFJets(myEvent_tmp.GPFJets, myEvent_tmp.GPFJets.size(), myEvent_tmp.BPFJets.size(), false, lumiWeight3D);
            BJets_allW.FillPFJets(myEvent_tmp.BPFJets, myEvent_tmp.BPFJets.size(), myEvent_tmp.BPFJets.size(), false, lumiWeight3D);
            nonBJets_allW.FillPFJets(nonBs, nonBs.size(), myEvent_tmp.BPFJets.size(), false, lumiWeight3D);
            FwDJet_allW.FillPFJets(sortedJetsbyEta, sortedJetsbyEta.size(), myEvent_tmp.BPFJets.size(), false, lumiWeight3D);
            MetHist_allW.Fill(&myEvent_tmp.mets.at(0), lumiWeight3D);
            allW_finalMT->Fill(mt, lumiWeight3D);

        }

        cout << "before closing file input " << f->GetName() << endl;
        f->Close();
        delete f;

    }
    cout << "before endjob" << endl;
    TFile * fout = new TFile(plotFileName.c_str(), "recreate");
    fout->cd();

    atLeastOnGPV.WriteAll(fout);
    GoldenFinalPUMuons.WriteAll(fout);
    Jets.WriteAll(fout);
    BJets.WriteAll(fout);
    nonBJets.WriteAll(fout);
    FwDJet.WriteAll(fout);
    MetHist.WriteAll(fout);
    def_finalMT->Write();

    atLeastOnGPV_PuW.WriteAll(fout);
    GoldenFinalPUMuons_PuW.WriteAll(fout);
    Jets_PuW.WriteAll(fout);
    BJets_PuW.WriteAll(fout);
    nonBJets_PuW.WriteAll(fout);
    FwDJet_PuW.WriteAll(fout);
    MetHist_PuW.WriteAll(fout);
    PuW_finalMT->Write();

    atLeastOnGPV_BtagPuW.WriteAll(fout);
    GoldenFinalPUMuons_BtagPuW.WriteAll(fout);
    Jets_BtagPuW.WriteAll(fout);
    BJets_BtagPuW.WriteAll(fout);
    nonBJets_BtagPuW.WriteAll(fout);
    FwDJet_BtagPuW.WriteAll(fout);
    MetHist_BtagPuW.WriteAll(fout);
    BtagPuW_finalMT->Write();

    atLeastOnGPV_allW.WriteAll(fout);
    GoldenFinalPUMuons_allW.WriteAll(fout);
    Jets_allW.WriteAll(fout);
    BJets_allW.WriteAll(fout);
    nonBJets_allW.WriteAll(fout);
    FwDJet_allW.WriteAll(fout);
    MetHist_allW.WriteAll(fout);
    allW_finalMT->Write();
    if (ttDecayMode == "") {
        Default_Def.Write(fout);

        Default_PuW.Write(fout);
        Default_BtagPuW.Write(fout);
        Default_allW.Write(fout);

        EtaCut_Def.Write(fout);
        EtaCut_PuW.Write(fout);
        EtaCut_BtagPuW.Write(fout);
        EtaCut_allW.Write(fout);

        AntiEtaCut_Def.Write(fout);
        HtCut_Def.Write(fout);
        AntiHtCut_Def.Write(fout);
        DefaultTrue_Def.Write(fout);
        EtaCutTrue_Def.Write(fout);
        DefaultTrue_allW.Write(fout);
        EtaCutTrue_allW.Write(fout);
        AntiEtaCutTrue_Def.Write(fout);
        HtCutTrue_Def.Write(fout);
        AntiHtCutTrue_Def.Write(fout);
    } else {
        DiLep_Default_Def.Write(fout);

        DiLep_Default_PuW.Write(fout);
        DiLep_Default_BtagPuW.Write(fout);
        DiLep_Default_allW.Write(fout);

        DiLep_EtaCut_Def.Write(fout);
        DiLep_EtaCut_PuW.Write(fout);
        DiLep_EtaCut_BtagPuW.Write(fout);
        DiLep_EtaCut_allW.Write(fout);

        DiLep_AntiEtaCut_Def.Write(fout);
        DiLep_HtCut_Def.Write(fout);
        DiLep_AntiHtCut_Def.Write(fout);
        DiLep_DefaultTrue_Def.Write(fout);
        DiLep_EtaCutTrue_Def.Write(fout);
        DiLep_DefaultTrue_allW.Write(fout);
        DiLep_EtaCutTrue_allW.Write(fout);
        DiLep_AntiEtaCutTrue_Def.Write(fout);
        DiLep_HtCutTrue_Def.Write(fout);
        DiLep_AntiHtCutTrue_Def.Write(fout);
    }
    HT->Write();
    fout->Write();
    fout->Close();

    cout << nInit << "\n" << nHLTrunB << "\n" << nMt << "\n" << nFinal << endl;
    cout << "only pu weight:\t" << nFinalPU << "\n" << "only btag sf:\t" << nFinalbTag << endl;
    cout << "only HLT weight:\t" << nFinalHLT << "\n" << "all sf's:\t" << nFinal << endl;
    return 0;
}

