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
#include "../../../../AnalysisClasses/EventSelection/interface/DifferentHistogramsTwb.h"
#include "../../../../AnalysisClasses/ToyAnalysis/interface/GenSingleTopMaker.h"
#include "../../../../TopBrussels/TopTreeAnalysis/MCInformation/interface/Lumi3DReWeighting.h"




#include <sstream>
#include <string>

#include <TApplication.h>
#include <TRandom.h>
#include <TFile.h>
#include <TH1.h>
#include <TH2.h>
#include <TCanvas.h>
#include <TBranch.h>
#include <TTree.h>
#include <TSystem.h>
#include <vector>
#define BTAGWEIGHT_HLTWEIGHT
#define PUWEIGHT
using namespace std;
using namespace TopTree;

/*
 * 
 */




int main(int argc, char** argv) {

    PVHists atLeastOnGPV("final_PV");
    JetHists Jets("final_Jet", 2);
    JetHists BJets("final_BJet", 2);
    JetHists nonBJets("final_nonBJet", 2);
    JetHists Light("final_Light", 2);
    MuonHists GoldenFinalMuons("final_Muon");
    MetHists MetHist("finalMet");
    PVHists atLeastOnGPV_allW("allW_PV");
    JetHists Jets_allW("allW_Jet", 2);
    JetHists BJets_allW("allW_BJet", 2);
    JetHists nonBJets_allW("allW_nonBJet", 2);
    JetHists FwDJet_allW("allW_FwD", 2);
    MuonHists GoldenFinalPUMuons_allW("allW_Muon");
    MetHists MetHist_allW("allW_Met");
    WtemplateHistograms RandomB("RandomB");
    WtemplateHistograms PtOrderedB("PtOrderedB");
    WtemplateHistograms BtagOrderedB("BtagOrderedB");
    WtemplateHistograms RandomBTrue("RandomBTrue");
    WtemplateHistograms PtOrderedBTrue("PtOrderedBTrue");
    WtemplateHistograms BtagOrderedBTrue("BtagOrderedBTrue");
    WtemplateHistograms EtaCutRandomB("EtaCutRandomB");
    WtemplateHistograms EtaCutPtOrderedB("EtaCutPtOrderedB");
    WtemplateHistograms EtaCutBtagOrderedB("EtaCutBtagOrderedB");
    WtemplateHistograms EtaCutRandomBTrue("EtaCutRandomBTrue");
    WtemplateHistograms EtaCutPtOrderedBTrue("EtaCutPtOrderedBTrue");
    WtemplateHistograms EtaCutBtagOrderedBTrue("EtaCutBtagOrderedBTrue");


    TH1D * HT = new TH1D("HT", "H_{T};H_{T}(GeV)", 500, 0., 500.);
    TH1D * finalMT = new TH1D("finalMT", "final-W-neutrino transverse mass", 100, 0., 200.);
    finalMT->GetXaxis()->SetTitle("M_{T}(W,#nu)");
    TH1D * delNu = new TH1D("delNu", "delNu", 100, 0., 100.);
    delNu->GetXaxis()->SetTitle("#Delta#nu");
    TH1D * delNuII = new TH1D("delNuMET", "delNuMET", 100, 0., 100.);
    delNuII->GetXaxis()->SetTitle("#Delta#nu");
    std::vector<std::string> inputFileNames;
    std::string plotFileName;
    int verbosity = 0;
    TH1D * METResolutions = 0;
    std::string HLTname = "HLT_IsoMu17_v*";
    bool pu3D = false; //true;
    string PUWeightFileName = "";
    double XSec = 1;
    double Luminosity = 1;
    double PreSelEff = 1;
    double doJES = 1;
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
        } else if (arg_fth == "smearingSkim") {
            f++;
            std::string in(*(argv + f));

            smearingSkim = atof(in.c_str());
        } else if (arg_fth == "puOption") {
            f++;
            std::string in(*(argv + f));
            MCpuFile = in;
        }
    }
    TFile * HLTweights = TFile::Open("~/work/AnalysisClasses/EventSelection/macro/HLT_IsoMu17_W.root");
    TH1D * HLTWeights = (TH1D*) HLTweights->Get("weight");
    MCpuFile = puAddress + MCpuFile;
    DataPuFile = puAddress + DataPuFile;
    TFile* f = 0;
    TApplication theApp("App", &argc, argv);
    double nInit = 0;
    double nFinal = 0;
    double nHLTrunB = 0;
    double nMt = 0;
    Lumi3DReWeighting Lumi3DWeights;
    TRandom SeedGenerator(1726367);
#ifdef PUWEIGHT
    if (!isData) {
        Lumi3DWeights.weight3D_set(MCpuFile, DataPuFile, "pileup", "pileup");
        Lumi3DWeights.setWFileName(PUWeightFileName);
        Lumi3DWeights.weight3D_init(1.0);
    }
#endif /*PUWEIGHT*/

    for (unsigned int fNumber = 0; fNumber < inputFileNames.size(); fNumber++) {
        cout << "file number " << fNumber + 1 << ": " << inputFileNames.at(fNumber) << endl;
        f = TFile::Open(inputFileNames.at(fNumber).c_str());

        TTree* runTree = (TTree*) f->Get("runTree");
        TTree* eventTree = (TTree*) f->Get("eventTree");

        PracticalEvent * pracEvt = new PracticalEvent(eventTree, runTree);
        pracEvt->eventTree->SetBranchStatus("*", 1);

        std::cout << "beforeLoop" << std::endl;

        int ievt = 0;
        GenSingleTopMaker* genSingleTop = 0;
        while (pracEvt->Next()) {

            if (!isData && pracEvt->NPGenEvtCollection() != 0) {
                //                cout<<"I am here"<<endl;
                genSingleTop = new GenSingleTopMaker((TRootNPGenEvent*) pracEvt->NPGenEvtCollection()->At(0), verbosity);
            }
            //                continue;
            double lumiWeight3D = 1;

            //            cout<<lumiWeight3D<<endl;
            nInit += lumiWeight3D;
            //            nInit++;
            ievt++;
            if (verbosity > 0)
                cout << "*******************************************************************  " << ievt << endl;

            std::vector<TRootPFJet> myJets_;
            myJets_.clear();
            pracEvt->setDefaultMET(*(TRootPFMET*) pracEvt->METCollection()->At(0));
            //            cout << "I am going to Jet Correction " << isData << endl;
            myJets_ = pracEvt->ScaledPFJetCollection(1, isData);

            Event myEvent_tmp(myJets_, *pracEvt->ElectronCollection()
                    , pracEvt->TypeICorrMET(), *pracEvt->MuonCollection(), *pracEvt->VertexCollection());
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
            myEvent_tmp.MuonMaker();
            /*
             * pt = 20.,  eta = 2.1, chi2 = 10,  D0 = 0.02,  nvh = 10, isoCut_ = 0.15,  doGL = false,  
             * nPixWithMeasuredHits = 1,  nSegM = 1
             */
            TRootMuon muon = myEvent_tmp.Dmuons.at(0);
            double iso = (muon.chargedHadronIso() + muon.neutralHadronIso() + muon.photonIso()) / muon.Pt();
            double mt = 0;
            double metT = sqrt((myEvent_tmp.mets.at(0).Px() * myEvent_tmp.mets.at(0).Px())+
                    (myEvent_tmp.mets.at(0).Py() * myEvent_tmp.mets.at(0).Py()));

            double muT = sqrt((myEvent_tmp.Dmuons.at(0).Px() * myEvent_tmp.Dmuons.at(0).Px())+
                    (myEvent_tmp.Dmuons.at(0).Py() * myEvent_tmp.Dmuons.at(0).Py()));
            mt = sqrt(pow(muT + metT, 2) - pow(myEvent_tmp.mets.at(0).Px() + myEvent_tmp.Dmuons.at(0).Px(), 2)
                    - pow(myEvent_tmp.mets.at(0).Py() + myEvent_tmp.Dmuons.at(0).Py(), 2));

            //            nFinal++;
            nFinal += lumiWeight3D;
            SemiLepTopQuark myLeptonicTopFirst(myEvent_tmp.GPFJets.at(0), myEvent_tmp.mets.at(0), myEvent_tmp.Dmuons.at(0),
                    myEvent_tmp.GPFJets.at(1), myEvent_tmp.GPFJets.at(0), METResolutions);

            SemiLepTopQuark myLeptonicTopSecond(myEvent_tmp.GPFJets.at(1), myEvent_tmp.mets.at(0), myEvent_tmp.Dmuons.at(0),
                    myEvent_tmp.GPFJets.at(0), myEvent_tmp.GPFJets.at(0), METResolutions);
#ifdef BTAGWEIGHT_HLTWEIGHT
            if (!isData) {
                double sf, eff;
                BTagWeight myBtagWeight;
                vector< vector<BTagWeight::JetInfo> > jInfosToReWeight(myEvent_tmp.GPFJets.size());
                for (int iJet = 0; iJet < myEvent_tmp.GPFJets.size(); iJet++) {
                    BTagWeight::GetEffSF_TCHPT(myEvent_tmp.GPFJets[iJet].Pt(),
                            myEvent_tmp.GPFJets[iJet].Eta(),
                            myEvent_tmp.GPFJets[iJet].btag_trackCountingHighPurBJetTags(),
                            myEvent_tmp.GPFJets[iJet].partonFlavour(),
                            eff, sf, 0);
                    BTagWeight::JetInfo jinfo(eff, sf);
                    jInfosToReWeight[iJet].push_back(jinfo);
                }
                lumiWeight3D *= myBtagWeight.weight(jInfosToReWeight);
            }
            double hltW = 1.;
            if (!isData) {
                int bin = HLTWeights->GetXaxis()->FindBin(myEvent_tmp.Dmuons.at(0).Eta());
                if (bin > 0 && bin < 13)
                    hltW = HLTWeights->GetBinContent(bin);
                else
                    hltW = 1.;
            }
            lumiWeight3D *= hltW;
#endif /*BTAGWEIGHT_HLTWEIGHT*/
#ifdef PUWEIGHT
            if (!isData) {
                lumiWeight3D *= Lumi3DWeights.weight3D(pracEvt->Event());
            }
#endif /*PUWEIGHT*/
            TRandom myRand(SeedGenerator.Integer(10000000));
            int index = myRand.Integer(2);

            if (index == 0) {
                RandomB.Fill(myLeptonicTopFirst, lumiWeight3D, iso);
                if (myLeptonicTopFirst.hasNeutrinoSolution())
                    RandomBTrue.Fill(myLeptonicTopFirst, lumiWeight3D, iso);
            } else if (index == 1) {
                RandomB.Fill(myLeptonicTopSecond, lumiWeight3D, iso);
                if (myLeptonicTopSecond.hasNeutrinoSolution())
                    RandomBTrue.Fill(myLeptonicTopSecond, lumiWeight3D, iso);
            } else
                cout << "BAD RANDOM NUMBER" << endl;

            double btag1 = myEvent_tmp.GPFJets.at(0).btag_simpleSecondaryVertexHighPurBJetTags();
            double btag2 = myEvent_tmp.GPFJets.at(1).btag_simpleSecondaryVertexHighPurBJetTags();

            if (btag1 > btag2) {
                BtagOrderedB.Fill(myLeptonicTopFirst, lumiWeight3D, iso);
                if (myLeptonicTopFirst.hasNeutrinoSolution())
                    BtagOrderedBTrue.Fill(myLeptonicTopFirst, lumiWeight3D, iso);
            } else {
                BtagOrderedB.Fill(myLeptonicTopSecond, lumiWeight3D, iso);
                if (myLeptonicTopSecond.hasNeutrinoSolution())
                    BtagOrderedBTrue.Fill(myLeptonicTopSecond, lumiWeight3D, iso);
            }

            if (myEvent_tmp.GPFJets.at(0).Pt() > myEvent_tmp.GPFJets.at(1).Pt()) {
                PtOrderedB.Fill(myLeptonicTopFirst, lumiWeight3D, iso);
                if (myLeptonicTopFirst.hasNeutrinoSolution())
                    PtOrderedBTrue.Fill(myLeptonicTopFirst, lumiWeight3D, iso);
            } else {
                PtOrderedB.Fill(myLeptonicTopSecond, lumiWeight3D, iso);
                if (myLeptonicTopSecond.hasNeutrinoSolution())
                    PtOrderedBTrue.Fill(myLeptonicTopSecond, lumiWeight3D, iso);
            }

            double ht = myEvent_tmp.GPFJets.at(0).Pt() + myEvent_tmp.GPFJets.at(1).Pt();


            ht += myEvent_tmp.Dmuons.at(0).Pt();
            ht += myEvent_tmp.mets.at(0).Pt();
            HT->Fill(ht, lumiWeight3D);


            Jets.FillPFJets(myEvent_tmp.GPFJets, myEvent_tmp.GPFJets.size(), myEvent_tmp.BPFJets.size(), false, lumiWeight3D);
            MetHist.Fill(&myEvent_tmp.mets.at(0), lumiWeight3D);
            finalMT->Fill(mt, lumiWeight3D);
            if (fabs(myEvent_tmp.GPFJets.at(0).Eta()) > fabs(myEvent_tmp.GPFJets.at(1).Eta()) &&
                    fabs(myEvent_tmp.GPFJets.at(0).Eta()) <= 1.5)
                continue;
            if (fabs(myEvent_tmp.GPFJets.at(1).Eta()) > fabs(myEvent_tmp.GPFJets.at(0).Eta()) &&
                    fabs(myEvent_tmp.GPFJets.at(1).Eta()) <= 1.5)
                continue;
            if (index == 0) {
                EtaCutRandomB.Fill(myLeptonicTopFirst, lumiWeight3D, iso);
                if (myLeptonicTopFirst.hasNeutrinoSolution())
                    EtaCutRandomBTrue.Fill(myLeptonicTopFirst, lumiWeight3D, iso);
            } else if (index == 1) {
                EtaCutRandomB.Fill(myLeptonicTopSecond, lumiWeight3D, iso);
                if (myLeptonicTopSecond.hasNeutrinoSolution())
                    EtaCutRandomBTrue.Fill(myLeptonicTopSecond, lumiWeight3D, iso);
            } else
                cout << "BAD RANDOM NUMBER" << endl;
            if (btag1 > btag2) {
                EtaCutBtagOrderedB.Fill(myLeptonicTopFirst, lumiWeight3D, iso);
                if (myLeptonicTopFirst.hasNeutrinoSolution())
                    EtaCutBtagOrderedBTrue.Fill(myLeptonicTopFirst, lumiWeight3D, iso);
            } else {
                EtaCutBtagOrderedB.Fill(myLeptonicTopSecond, lumiWeight3D, iso);
                if (myLeptonicTopSecond.hasNeutrinoSolution())
                    EtaCutBtagOrderedBTrue.Fill(myLeptonicTopSecond, lumiWeight3D, iso);
            }

            if (myEvent_tmp.GPFJets.at(0).Pt() > myEvent_tmp.GPFJets.at(1).Pt()) {
                EtaCutPtOrderedB.Fill(myLeptonicTopFirst, lumiWeight3D, iso);
                if (myLeptonicTopFirst.hasNeutrinoSolution())
                    EtaCutPtOrderedBTrue.Fill(myLeptonicTopFirst, lumiWeight3D, iso);
            } else {
                EtaCutPtOrderedB.Fill(myLeptonicTopSecond, lumiWeight3D, iso);
                if (myLeptonicTopSecond.hasNeutrinoSolution())
                    EtaCutPtOrderedBTrue.Fill(myLeptonicTopSecond, lumiWeight3D, iso);
            }

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
    Jets.WriteAll(fout);

    RandomB.Write(fout);
    PtOrderedB.Write(fout);
    BtagOrderedB.Write(fout);
    RandomBTrue.Write(fout);
    PtOrderedBTrue.Write(fout);
    BtagOrderedBTrue.Write(fout);
    EtaCutRandomB.Write(fout);
    EtaCutPtOrderedB.Write(fout);
    EtaCutBtagOrderedB.Write(fout);
    EtaCutRandomBTrue.Write(fout);
    EtaCutPtOrderedBTrue.Write(fout);
    EtaCutBtagOrderedBTrue.Write(fout);
    atLeastOnGPV_allW.WriteAll(fout);
    GoldenFinalPUMuons_allW.WriteAll(fout);
    Jets_allW.WriteAll(fout);
    BJets_allW.WriteAll(fout);
    nonBJets_allW.WriteAll(fout);
    FwDJet_allW.WriteAll(fout);
    MetHist_allW.WriteAll(fout);
    fout->cd();
    finalMT->Write();
    HT->Write();
    fout->Write();
    fout->Close();

    cout << nInit << "\n" << nHLTrunB << "\n" << nMt << "\n" << nFinal << endl;
    return 0;
}

