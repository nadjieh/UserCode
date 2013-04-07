/* 
 * File:   HistogramCreator.C
 * Author: nadjieh
 *
 * Created on March 12, 2012, 2:51 PM
 */
//same as SelectAndSave with less complexities. Aimed to run on selected samples.

#include "TDirectory.h"
#include "../../../interface/ElectronSelector.h"

#include "../../../interface/Event.h"

#include "../../../interface/ElectronHists.h"
#include "../../../interface/MuonHists.h"
#include "../../../interface/PVHists.h"
#include "../../../interface/JetHists.h"
#include "../../../interface/JetSelector.h"
#include "../../../interface/MuonVetoSelector.h"
#include "../../../interface/MetHists.h"
#include "../../../interface/PrimaryVertexSelector.h"

#include "../../../../PhysicsObjects/interface/SemiLepTopQuark.h"

#include "../../../../../TopBrussels/TopTreeProducer/interface/TRootMuon.h"
#include "../../../../../TopBrussels/TopTreeProducer/interface/TRootElectron.h"
#include "../../../../../TopBrussels/TopTreeProducer/interface/TRootJet.h"
#include "../../../../../TopBrussels/TopTreeProducer/interface/TRootCaloJet.h"
#include "../../../../../TopBrussels/TopTreeProducer/interface/TRootPFJet.h"
#include "../../../../../TopBrussels/TopTreeProducer/interface/TRootMET.h"
#include "../../../../../TopBrussels/TopTreeProducer/interface/TRootGenEvent.h"
#include "../../../../../TopBrussels/TopTreeProducer/interface/TRootNPGenEvent.h"
#include "../../../../../TopBrussels/TopTreeProducer/interface/TRootEvent.h"
#include "../../../../../TopBrussels/TopTreeProducer/interface/TRootRun.h"
#include "../../../../../TopBrussels/TopTreeProducer/interface/TRootParticle.h"
#include "../../../../../TopBrussels/TopTreeProducer/interface/TRootMCParticle.h"
#include "../../../../../TopBrussels/TopTreeProducer/interface/TRootVertex.h"
#include "../../../../../TopBrussels/TopTreeProducer/interface/TRootHLTInfo.h"
#include "../../../../../AnalysisClasses/EventSelection/interface/PracticalEvent.h"
#include "../../../../../AnalysisClasses/ToyAnalysis/interface/GenSingleTopMaker.h"
#include "../../../../../AnalysisClasses/ChiSquared/interface/DR.h"
#include "../../../../../TopBrussels/TopTreeAnalysis/MCInformation/interface/Lumi3DReWeighting.h"
#include "../../../../../AnalysisClasses/EventSelection/interface/QCDOrso.h"





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
#include <TRandom3.h>
#include "../../../interface/DifferentHistogramsTwb.h"

using namespace std;
using namespace TopTree;

/*
 * 
 */

/*
 * central: 0.3-0.45
 * enlarge: 0.3-0.5
 * shrink: 0.3-0.4
 * shift: 0.35-0.5 
 */
bool passIso(QCDOrso * t, int iso = 0) {
    if (iso == 1) {
        return (t->leptonRelIso > 0.3 && t->leptonRelIso < 0.45);
    } else if (iso == 2) {
        return (t->leptonRelIso > 0.3 && t->leptonRelIso < 0.5);
    } else if (iso == 3) {
        return (t->leptonRelIso > 0.3 && t->leptonRelIso < 0.4);
    } else if (iso == 4) {
        return (t->leptonRelIso > 0.35 && t->leptonRelIso < 0.5);
    }
    return true;
}

int main(int argc, char** argv) {
    bool Wtemplate = false;

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
    SingleTopHistograms AntiEtaCut_allW("antiEtaFwD_allW");
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


    TH2D * MT_cosTheta = new TH2D("MTcosTheta", "MTcosTheta", 200, 0, 200, 100, -1., 1.);
    TH2D * MT_cosTheta_true = new TH2D("MTcosTheta_true", "MTcosTheta_true", 200, 0, 200, 100, -1., 1.);

    TH1D * HT = new TH1D("HT", "H_{T};H_{T}(GeV)", 500, 0., 500.);

    TH1D * def_finalMT = new TH1D("def_finalMT", "final-W-neutrino transverse mass", 100, 0., 200.);
    def_finalMT->GetXaxis()->SetTitle("M_{T}(W,#nu)");
    TH1D * PuW_finalMT = new TH1D("PuW_finalMT", "final-W-neutrino transverse mass", 100, 0., 200.);
    PuW_finalMT->GetXaxis()->SetTitle("M_{T}(W,#nu)");
    TH1D * BtagPuW_finalMT = new TH1D("BtagPuW_finalMT", "final-W-neutrino transverse mass", 100, 0., 200.);
    BtagPuW_finalMT->GetXaxis()->SetTitle("M_{T}(W,#nu)");
    TH1D * allW_finalMT = new TH1D("allW_finalMT", "final-W-neutrino transverse mass", 100, 0., 200.);
    allW_finalMT->GetXaxis()->SetTitle("M_{T}(W,#nu)");
    std::vector<std::string> inputFileNames;
    std::string plotFileName;
    int verbosity = 0;
    TH1D * METResolutions = 0;
    std::string HLTname = "HLT_IsoMu17_v*";
    bool pu3D = false; //true;
    string Sample = "";
    double XSec = 1;
    double Luminosity = 1;
    double PreSelEff = 1;
    double doJES = 1;
    bool isData = false;
    int smearingSkim = 1;
    int iso = 0;
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
        } else if (arg_fth == "Sample") {
            f++;
            std::string in(*(argv + f));
            Sample = in;
            std::cout << HLTname << endl;
        } else if (arg_fth == "smearingSkim") {
            f++;
            std::string in(*(argv + f));
            smearingSkim = atof(in.c_str());
        } else if (arg_fth == "iso") {
            f++;
            std::string in(*(argv + f));
            iso = atof(in.c_str());
        }
    }
    cout << "START" << endl;

    TFile* f = 0;
    TApplication theApp("App", &argc, argv);
    double nInit = 0;
    double nFinal = 0;
    double nHLTrunB = 0;
    double nMt = 0;
    double nGoodSolution = 0;

    QCDOrso * myQCD = 0;
    TTree * eventTree = 0;


    GenSingleTopMaker* genSingleTop = 0;
    for (unsigned int fNumber = 0; fNumber < inputFileNames.size(); fNumber++) {
        cout << "file number " << fNumber + 1 << ": " << inputFileNames.at(fNumber) << endl;
        TFile* f = TFile::Open(inputFileNames.at(fNumber).c_str());
        myQCD = new QCDOrso(eventTree, f,string(Sample+"_noSyst"));
        double lumiWeight3D = 1;

        cout << myQCD->fChain->GetName() << endl;
        for (int eventNumber = 0; eventNumber < myQCD->fChain->GetEntriesFast(); eventNumber++) {
            myQCD->GetEntry(eventNumber);
            lumiWeight3D = myQCD->bWeight*myQCD->PUWeight*myQCD->weight*1140.008;
            TLorentzVector muon = myQCD->GetLepton();
            TLorentzVector bjet(-1, -1, -1, -1);
            bjet.SetPtEtaPhiE(myQCD->bJetPt, myQCD->bJetEta, myQCD->bJetPhi, myQCD->bJetE);

            TLorentzVector fjet(-1, -1, -1, -1);
            fjet.SetPtEtaPhiE(myQCD->fJetPt, myQCD->fJetEta, myQCD->fJetPhi, myQCD->fJetE);

            TLorentzVector met(-1, -1, -1, -1);
            met.SetPtEtaPhiE(myQCD->metPt, 0, myQCD->metPhi, myQCD->metPt);
            double mt = 0;
            double metT = sqrt((met.Px() * met.Px())+(met.Py() * met.Py()));

            double muT = sqrt((muon.Px() * muon.Px())+(muon.Py() * muon.Py()));
            mt = sqrt(pow(muT + metT, 2) - pow(met.Px() + muon.Px(), 2) - pow(met.Py() + muon.Py(), 2));
            if (mt > 40) {
                //                nMt++;
                nMt += lumiWeight3D;
                if (verbosity > 0)
                    cout << "\tM_T cut is passed" << endl;
            } else
                continue;
            nFinal += lumiWeight3D;
            TLorentzVector fwdJet = fjet;
            if (fabs(bjet.Eta()) > fabs(fjet.Eta()))
                fwdJet = bjet;

            SemiLepTopQuark myLeptonicTopSecond(fjet, met, muon, bjet, fwdJet, METResolutions);
            myLeptonicTopSecond.setMuCharge((int) myQCD->charge);

            SemiLepTopQuark myLeptonicTop(bjet, met, muon, fjet, fwdJet, METResolutions);
            myLeptonicTop.setMuCharge((int) myQCD->charge);

            double eta = fabs(fwdJet.Eta());
            double ht = myQCD->bJetPt + myQCD->fJetPt + myQCD->leptonPt + myQCD->metPt;
            HT->Fill(ht, lumiWeight3D);

            if (myLeptonicTop.hasNeutrinoSolution()) {
                nGoodSolution++;
                MT_cosTheta_true->Fill(mt, myLeptonicTop.cosThetaStar(), 1);
                DefaultTrue_Def.Fill(myLeptonicTop, lumiWeight3D, genSingleTop);
                DefaultTrue_BtagPuW.Fill(myLeptonicTop, lumiWeight3D, genSingleTop);
                DefaultTrue_allW.Fill(myLeptonicTop, lumiWeight3D, genSingleTop);
                DefaultTrue_PuW.Fill(myLeptonicTop, lumiWeight3D, genSingleTop);
                if (ht >= 180) {
                    HtCutTrue_Def.Fill(myLeptonicTop, lumiWeight3D, genSingleTop);
                } else
                    AntiHtCutTrue_Def.Fill(myLeptonicTop, lumiWeight3D, genSingleTop);
                if (eta > 1.5) {
                    EtaCutTrue_Def.Fill(myLeptonicTop, lumiWeight3D, genSingleTop);
                    EtaCutTrue_BtagPuW.Fill(myLeptonicTop, lumiWeight3D, genSingleTop);
                    EtaCutTrue_PuW.Fill(myLeptonicTop, lumiWeight3D, genSingleTop);
                    EtaCutTrue_allW.Fill(myLeptonicTop, lumiWeight3D, genSingleTop);
                } else
                    AntiEtaCutTrue_Def.Fill(myLeptonicTop, lumiWeight3D, genSingleTop);
            }
            Default_Def.Fill(myLeptonicTop, lumiWeight3D, genSingleTop);
            MT_cosTheta->Fill(mt, myLeptonicTop.cosThetaStar(), 1);
            Default_BtagPuW.Fill(myLeptonicTop, lumiWeight3D, genSingleTop);
            Default_PuW.Fill(myLeptonicTop, lumiWeight3D, genSingleTop);
            Default_allW.Fill(myLeptonicTop, lumiWeight3D, genSingleTop);
            if (ht >= 180)
                HtCut_Def.Fill(myLeptonicTop, lumiWeight3D, genSingleTop);
            else
                AntiHtCut_Def.Fill(myLeptonicTop, lumiWeight3D, genSingleTop);
            if (eta > 1.5) {
                EtaCut_Def.Fill(myLeptonicTop, lumiWeight3D, genSingleTop);
                EtaCut_BtagPuW.Fill(myLeptonicTop, lumiWeight3D, genSingleTop);
                EtaCut_PuW.Fill(myLeptonicTop, lumiWeight3D, genSingleTop);
                EtaCut_allW.Fill(myLeptonicTop, lumiWeight3D, genSingleTop);
            } else
                AntiEtaCut_allW.Fill(myLeptonicTop, lumiWeight3D, genSingleTop);


            if (genSingleTop != NULL)
                delete genSingleTop;
            TRootPFJet BJET(bjet);
            TRootPFJet nonBJET(fjet);
            TRootPFJet FWDJET(fwdJet);
            BJET.setBtag_trackCountingHighPurBJetTags(myQCD->bJetBtag);
            TRootMuon MUON(muon);
            TRootPFMET MET(met);
            TRootVertex VTX;
            Event myEvent_tmp;
            myEvent_tmp.Gpvs.push_back(VTX);
            atLeastOnGPV.Fill(myEvent_tmp.Gpvs, myQCD->nVertices, 1);
            myEvent_tmp.Dmuons.push_back(MUON);
            GoldenFinalPUMuons.Fill(myEvent_tmp.Dmuons, myEvent_tmp.Dmuons.size(), 1);
            myEvent_tmp.GPFJets.push_back(BJET);
            myEvent_tmp.GPFJets.push_back(nonBJET);
            Jets.FillPFJets(myEvent_tmp.GPFJets, myEvent_tmp.GPFJets.size(), myEvent_tmp.BPFJets.size(), false, 1);
            myEvent_tmp.BPFJets.push_back(BJET);
            BJets.FillPFJets(myEvent_tmp.BPFJets, myEvent_tmp.BPFJets.size(), myEvent_tmp.BPFJets.size(), false, 1);
            std::vector<TRootPFJet> nonBs;
            nonBs.push_back(nonBJET);
            nonBJets.FillPFJets(nonBs, nonBs.size(), myEvent_tmp.BPFJets.size(), false, 1);
            std::vector<TRootPFJet> sortedJetsbyEta;
            sortedJetsbyEta.push_back(FWDJET);
            FwDJet.FillPFJets(sortedJetsbyEta, sortedJetsbyEta.size(), myEvent_tmp.BPFJets.size(), false, 1);
            myEvent_tmp.mets.push_back(MET);
            MetHist.Fill(&myEvent_tmp.mets.at(0), 1);
            def_finalMT->Fill(mt, 1);

            atLeastOnGPV_PuW.Fill(myEvent_tmp.Gpvs, myEvent_tmp.Gpvs.size(), 1);
            GoldenFinalPUMuons_PuW.Fill(myEvent_tmp.Dmuons, myEvent_tmp.Dmuons.size(), 1);
            Jets_PuW.FillPFJets(myEvent_tmp.GPFJets, myEvent_tmp.GPFJets.size(), myEvent_tmp.BPFJets.size(), false, 1);
            BJets_PuW.FillPFJets(myEvent_tmp.BPFJets, myEvent_tmp.BPFJets.size(), myEvent_tmp.BPFJets.size(), false, 1);
            nonBJets_PuW.FillPFJets(nonBs, nonBs.size(), myEvent_tmp.BPFJets.size(), false, 1);
            FwDJet_PuW.FillPFJets(sortedJetsbyEta, sortedJetsbyEta.size(), myEvent_tmp.BPFJets.size(), false, 1);
            MetHist_PuW.Fill(&myEvent_tmp.mets.at(0), 1);
            PuW_finalMT->Fill(mt, 1);

            atLeastOnGPV_BtagPuW.Fill(myEvent_tmp.Gpvs, myEvent_tmp.Gpvs.size(), 1);
            GoldenFinalPUMuons_BtagPuW.Fill(myEvent_tmp.Dmuons, myEvent_tmp.Dmuons.size(), 1);
            Jets_BtagPuW.FillPFJets(myEvent_tmp.GPFJets, myEvent_tmp.GPFJets.size(), myEvent_tmp.BPFJets.size(), false, 1);
            BJets_BtagPuW.FillPFJets(myEvent_tmp.BPFJets, myEvent_tmp.BPFJets.size(), myEvent_tmp.BPFJets.size(), false, 1);
            nonBJets_BtagPuW.FillPFJets(nonBs, nonBs.size(), myEvent_tmp.BPFJets.size(), false, 1);
            FwDJet_BtagPuW.FillPFJets(sortedJetsbyEta, sortedJetsbyEta.size(), myEvent_tmp.BPFJets.size(), false, 1);
            MetHist_BtagPuW.Fill(&myEvent_tmp.mets.at(0), 1);
            BtagPuW_finalMT->Fill(mt, 1);

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
    if (iso != 0) {
        stringstream d;
        d << iso << "_" << plotFileName;
        plotFileName = d.str();
    }
    TFile * fout = new TFile(plotFileName.c_str(), "recreate");
    fout->cd();
    if (!Wtemplate) {
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
    }

    atLeastOnGPV_allW.WriteAll(fout);
    GoldenFinalPUMuons_allW.WriteAll(fout);
    Jets_allW.WriteAll(fout);
    BJets_allW.WriteAll(fout);
    nonBJets_allW.WriteAll(fout);
    FwDJet_allW.WriteAll(fout);
    MetHist_allW.WriteAll(fout);
    allW_finalMT->Write();
    if (!Wtemplate) {
        Default_Def.Write(fout);
        Default_BtagPuW.Write(fout);
        Default_PuW.Write(fout);
        Default_allW.Write(fout);
        EtaCut_BtagPuW.Write(fout);
        EtaCut_Def.Write(fout);
        EtaCut_allW.Write(fout);
        EtaCut_PuW.Write(fout);

        AntiEtaCut_allW.Write(fout);
        HtCut_Def.Write(fout);
        AntiHtCut_Def.Write(fout);
        DefaultTrue_BtagPuW.Write(fout);
        DefaultTrue_allW.Write(fout);
        DefaultTrue_PuW.Write(fout);
        DefaultTrue_Def.Write(fout);
        EtaCutTrue_BtagPuW.Write(fout);
        EtaCutTrue_allW.Write(fout);
        EtaCutTrue_Def.Write(fout);
        EtaCutTrue_PuW.Write(fout);
        AntiEtaCutTrue_Def.Write(fout);
        HtCutTrue_Def.Write(fout);
        AntiHtCutTrue_Def.Write(fout);
    } else {
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
    }
    MT_cosTheta->Write();

    MT_cosTheta_true->Write();
    HT->Write();

    //    ntag->Write();
    fout->Write();
    fout->Close();

    cout << nInit << "\n" << nHLTrunB << "\n" << nMt << "\n" << nFinal << "\n" << nGoodSolution << endl;
    return 0;
}

