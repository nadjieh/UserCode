/* 
 * File:   OrsoHistogramCreator.C
 * Author: nadjieh
 *
 * Created on October 12, 2012, 12:34 PM
 */
#define ISDATA
//#define Wtemplate
#include "TDirectory.h"

#include "../../AnalysisClasses/EventSelection/interface/ElectronSelector.h"

#include "../../AnalysisClasses/EventSelection/interface/Event.h"

#include "../../AnalysisClasses/EventSelection/interface/ElectronHists.h"
#include "../../AnalysisClasses/EventSelection/interface/MuonHists.h"
#include "../../AnalysisClasses/EventSelection/interface/PVHists.h"
#include "../../AnalysisClasses/EventSelection/interface/JetHists.h"
#include "../../AnalysisClasses/EventSelection/interface/JetSelector.h"
#include "../../AnalysisClasses/EventSelection/interface/MuonVetoSelector.h"
#include "../../AnalysisClasses/EventSelection/interface/MetHists.h"
#include "../../AnalysisClasses/EventSelection/interface/PrimaryVertexSelector.h"
#include "../../TopBrussels/TopTreeProducer/interface/TRootMuon.h"
#include "../../TopBrussels/TopTreeProducer/interface/TRootElectron.h"
#include "../../TopBrussels/TopTreeProducer/interface/TRootJet.h"
#include "../../TopBrussels/TopTreeProducer/interface/TRootCaloJet.h"
#include "../../TopBrussels/TopTreeProducer/interface/TRootPFJet.h"
#include "../../TopBrussels/TopTreeProducer/interface/TRootMET.h"
#include "../../TopBrussels/TopTreeProducer/interface/TRootGenEvent.h"
#include "../../TopBrussels/TopTreeProducer/interface/TRootNPGenEvent.h"
#include "../../TopBrussels/TopTreeProducer/interface/TRootEvent.h"
#include "../../TopBrussels/TopTreeProducer/interface/TRootRun.h"
#include "../../TopBrussels/TopTreeProducer/interface/TRootParticle.h"
#include "../../TopBrussels/TopTreeProducer/interface/TRootMCParticle.h"
#include "../../TopBrussels/TopTreeProducer/interface/TRootVertex.h"
#include "../../TopBrussels/TopTreeProducer/interface/TRootHLTInfo.h"
#include "../../AnalysisClasses/EventSelection/interface/PracticalEvent.h"
#include "../../AnalysisClasses/ToyAnalysis/interface/GenSingleTopMaker.h"
#include "../../AnalysisClasses/PhysicsObjects/interface/SemiLepTopQuark.h"
#include "../../AnalysisClasses/ChiSquared/interface/DR.h"
#include "../../AnalysisClasses/EventSelection/interface/DifferentHistogramsTwb.h"
#include "../interface/MuonTree.h"
#include "../interface/GenInfoMuonTree.h"
#include "../interface/TRootGenEventMaker.h"


#include <sstream>
#include <string>

#include <TApplication.h>
#include <TFile.h>
#include <TH1.h>
#include <TH2.h>
#include <TCanvas.h>
#include <TBranch.h>
#include <TTree.h>
#include <TRandom.h>
#include <TRandom3.h>
#include <TSystem.h>
#include <vector>

using namespace std;
using namespace TopTree;

Event myEventPreparation(GenInfoMuonTree * input) {
    //    cout << "in myEventPreparation" << endl;
    TRootPFJet BJET(input->GetBJet());
    BJET.setBtag_trackCountingHighPurBJetTags(input->highBTag);
    TRootPFJet nonBJET(input->GetFJet());
    nonBJET.setBtag_trackCountingHighPurBJetTags(input->lowBTag);
    TRootMuon MUON(input->GetLepton());
    TRootPFMET MET(input->GetMET());
    TRootVertex VTX;
    Event myEvent_tmp;
    for (int i = 0; i < input->nGoodVertices; i++)
        myEvent_tmp.Gpvs.push_back(VTX);
    myEvent_tmp.Dmuons.push_back(MUON);
    myEvent_tmp.GPFJets.push_back(BJET);
    myEvent_tmp.GPFJets.push_back(nonBJET);
    myEvent_tmp.BPFJets.push_back(BJET);
    myEvent_tmp.mets.push_back(MET);
    return myEvent_tmp;
}

Event myEventPreparation(MuonTree * input) {
    //    cout << "in myEventPreparation" << endl;
    TRootPFJet BJET(input->GetBJet());
    BJET.setBtag_trackCountingHighPurBJetTags(input->highBTag);
    TRootPFJet nonBJET(input->GetFJet());
    nonBJET.setBtag_trackCountingHighPurBJetTags(input->lowBTag);
    TRootMuon MUON(input->GetLepton());
    TRootPFMET MET(input->GetMET());
    TRootVertex VTX;
    Event myEvent_tmp;
    for (int i = 0; i < input->nGoodVertices; i++)
        myEvent_tmp.Gpvs.push_back(VTX);
    myEvent_tmp.Dmuons.push_back(MUON);
    myEvent_tmp.GPFJets.push_back(BJET);
    myEvent_tmp.GPFJets.push_back(nonBJET);
    myEvent_tmp.BPFJets.push_back(BJET);
    myEvent_tmp.mets.push_back(MET);
    return myEvent_tmp;
}

void GetWeights(GenInfoMuonTree* myMuonTree, double& allW, double& puOnly, double& btagPu) {//To be corrected with new weighting recipe
    double defW = myMuonTree->weight * (myMuonTree->leptonEff * 699 + myMuonTree->leptonEffB * 4342);
    puOnly = defW * myMuonTree->PUWeight;
    allW = myMuonTree->GetTotalWeightNoPU();
    allW *= myMuonTree->PUWeight;
    btagPu = allW;
}

void GetWeightsNoPu(GenInfoMuonTree* myMuonTree, double& allW, double& puOnly, double& btagPu) {//To be corrected with new weighting recipe
    puOnly = myMuonTree->weight * (myMuonTree->leptonEff * 699 + myMuonTree->leptonEffB * 4342);
    allW = myMuonTree->GetTotalWeightNoPU();
    btagPu = allW;
}

void GetWeights(MuonTree* myMuonTree, double& allW, double& puOnly, double& btagPu) {//To be corrected with new weighting recipe
    double defW = myMuonTree->weight * (myMuonTree->leptonEff * 699 + myMuonTree->leptonEffB * 4342);
    puOnly = defW * myMuonTree->PUWeight;
    allW = myMuonTree->GetTotalWeightNoPU();
    allW *= myMuonTree->PUWeight;
    btagPu = allW;
}

void GetWeightsNoPu(MuonTree* myMuonTree, double& allW, double& puOnly, double& btagPu) {//To be corrected with new weighting recipe
    puOnly = myMuonTree->weight * (myMuonTree->leptonEff * 699 + myMuonTree->leptonEffB * 4342);
    allW = myMuonTree->GetTotalWeightNoPU();
    btagPu = allW;
}

int main(int argc, char** argv) {

    PVHists atLeastOnGPV("DefW_PV", true);
    JetHists Jets("DefW_Jet", 2, true);
    JetHists BJets("DefW_BJet", 2, true);
    JetHists nonBJets("DefW_nonBJet", 2, true);
    JetHists FwDJet("DefW_FwD", 2, true);
    MuonHists GoldenFinalPUMuons("DefW_Muon", 3, true);
    MetHists MetHist("DefW_Met", true);

    PVHists atLeastOnGPV_PuW("PuW_PV", true);
    JetHists Jets_PuW("PuW_Jet", 2, true);
    JetHists BJets_PuW("PuW_BJet", 2, true);
    JetHists nonBJets_PuW("PuW_nonBJet", 2, true);
    JetHists FwDJet_PuW("PuW_FwD", 2, true);
    MuonHists GoldenFinalPUMuons_PuW("PuW_Muon", 3, true);
    MetHists MetHist_PuW("PuW_Met", true);

    PVHists atLeastOnGPV_BtagPuW("BtagPuW_PV", true);
    JetHists Jets_BtagPuW("BtagPuW_Jet", 2, true);
    JetHists BJets_BtagPuW("BtagPuW_BJet", 2, true);
    JetHists nonBJets_BtagPuW("BtagPuW_nonBJet", 2, true);
    JetHists FwDJet_BtagPuW("BtagPuW_FwD", 2, true);
    MuonHists GoldenFinalPUMuons_BtagPuW("BtagPuW_Muon", 3, true);
    MetHists MetHist_BtagPuW("BtagPuW_Met", true);

    PVHists atLeastOnGPV_allW("allW_PV", true);
    JetHists Jets_allW("allW_Jet", 2, true);
    JetHists BJets_allW("allW_BJet", 2, true);
    JetHists nonBJets_allW("allW_nonBJet", 2, true);
    JetHists FwDJet_allW("allW_FwD", 2, true);
    MuonHists GoldenFinalPUMuons_allW("allW_Muon", 3, true);
    MetHists MetHist_allW("allW_Met", true);

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
    HT->Sumw2();
    TH1D * def_finalMT = new TH1D("def_finalMT", "final-W-neutrino transverse mass", 100, 0., 200.);
    def_finalMT->Sumw2();
    def_finalMT->GetXaxis()->SetTitle("M_{T}(W,#nu)");
    TH1D * PuW_finalMT = new TH1D("PuW_finalMT", "final-W-neutrino transverse mass", 100, 0., 200.);
    PuW_finalMT->Sumw2();
    PuW_finalMT->GetXaxis()->SetTitle("M_{T}(W,#nu)");
    TH1D * BtagPuW_finalMT = new TH1D("BtagPuW_finalMT", "final-W-neutrino transverse mass", 100, 0., 200.);
    BtagPuW_finalMT->GetXaxis()->SetTitle("M_{T}(W,#nu)");
    BtagPuW_finalMT->Sumw2();
    TH1D * allW_finalMT = new TH1D("allW_finalMT", "final-W-neutrino transverse mass", 100, 0., 200.);
    allW_finalMT->GetXaxis()->SetTitle("M_{T}(W,#nu)");
    allW_finalMT->Sumw2();

    std::vector<std::string> inputFileNames;
    std::string plotFileName;
    TH1D * METResolutions = 0;
    bool isData = false;
    int smearingSkim = 1;
    string sample = "";
    string ttDecayMode = "";
    string prefix = "";
    int eventFlavor = 0;
    for (int f = 1; f < argc; f++) {
        std::string arg_fth(*(argv + f));
        if (arg_fth == "prefix") {
            f++;
            std::string in(*(argv + f));
            prefix = in + string("_");
        } else if (arg_fth == "input") {
            f++;
            std::string in(*(argv + f));
            inputFileNames.push_back(string("~/work/samples/Orso8TeV/Nov_53X/" + prefix + in + ".root"));
            sample = in;
            plotFileName = prefix + in + "_plots.root";
        } else if (arg_fth == "eventFlavor") {
            f++;
            std::string in(*(argv + f));
            eventFlavor = atof(in.c_str());
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
        } else if (arg_fth == "smearingSkim") {
            f++;
            std::string in(*(argv + f));
            smearingSkim = atof(in.c_str());
        } else if (arg_fth == "ttDecayMode") {
            f++;
            std::string in(*(argv + f));
            ttDecayMode = in;
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
#ifdef ISDATA
    MuonTree * myMuonTree = 0;
#endif
#ifndef ISDATA
    GenInfoMuonTree * myMuonTree = 0;
#endif
    TTree * eventTree = 0;


    GenSingleTopMaker* genSingleTop = 0;
    TRootGenEventMaker* genEvtMaker = 0;
    TRandom3 tr(154456);
    for (unsigned int fNumber = 0; fNumber < inputFileNames.size(); fNumber++) {
        cout << "file number " << fNumber + 1 << ": " << inputFileNames.at(fNumber) << endl;
        TFile* f = TFile::Open(inputFileNames.at(fNumber).c_str());
#if defined ISDATA && defined Wtemplate
        myMuonTree = new MuonTree(eventTree, f, sample + "_2J_0T_noSyst");
#endif /*ISDATA && Wtemplate*/
#if defined ISDATA && !defined Wtemplate
        myMuonTree = new MuonTree(eventTree, f, sample + "_2J_1T_noSyst");
#endif /*ISDATA && !Wtemplate*/


        if (string(myMuonTree->fChain->GetName()) == string("Data_2J_0T_noSyst")) {
                    plotFileName = "WTemplate_plots.root";
        }
        if (string(myMuonTree->fChain->GetName()) == string("WJets_2J_0T_noSyst")) {
            switch (eventFlavor) {
                case 0:
                    plotFileName = "WTemplate_plots.root";
                    break;
                case 1:
                    plotFileName = "Light_WTemplate_plots.root";
                    break;
                case 2:
                    plotFileName = "C_WTemplate_plots.root";
                    break;
                case 3:
                    plotFileName = "B_WTemplate_plots.root";
                    break;
            }
        }
        if (string(myMuonTree->fChain->GetName()) == string("WJets_2J_1T_noSyst")) {
            switch (eventFlavor) {
                case 0:
                    plotFileName = "Signal_plots.root";
                    break;
                case 1:
                    plotFileName = "Light_Signal_plots.root";
                    break;
                case 2:
                    plotFileName = "C_Signal_plots.root";
                    break;
                case 3:
                    plotFileName = "B_Signal_plots.root";
                    break;
            }
        }
        for (int eventNumber = 0; eventNumber < myMuonTree->fChain->GetEntriesFast(); eventNumber++) {
            //            cout << "New event: " << eventNumber << "--------------------" << endl;
            myMuonTree->GetEntry(eventNumber);
            nFinal++;
            if (eventFlavor != 0) {
                if (eventFlavor == 1 && myMuonTree->eventFlavour != 1)
                    continue;
                if (eventFlavor == 2 && myMuonTree->eventFlavour != 2)
                    continue;
                if (eventFlavor == 3 && myMuonTree->eventFlavour != 3)
                    continue;
            }
            if (!myMuonTree->passExtraSelection())
                continue;
            Event myEvent_tmp = myEventPreparation(myMuonTree);




            double mt = myMuonTree->GetMTW();
            TLorentzVector fwdJet = myMuonTree->GetMostFwDJet();
            double eta = fabs(fwdJet.Eta());
            double ht = myMuonTree->GetHT();

            double puOnlyW = 1;
            double btagpuW = 1;
            double lumiWeight3D = 1;
            if (!isData) {
                //                GetWeightsNoPu(myMuonTree, lumiWeight3D, puOnlyW, btagpuW);
                //                GetWeights(myMuonTree, lumiWeight3D, puOnlyW, btagpuW);
            }
            //            if (!myMuonTree->jetsForWtemplate())
            //                continue;
            //            double rnd = tr.Uniform(0., 1.);
            //            if (rnd < 0.5) {
            //                TLorentzVector tmp = bjet;
            //                bjet = fjet;
            //                fjet = tmp;
            //            }
            //            TLorentzVector tmp = bjet;
            //            if (bjet.Pt() < fjet.Pt()) {
            //                bjet = fjet;
            //                fjet = tmp;
            //            }
            /*
             * Filling Event Histograms
             */

            HT->Fill(ht, lumiWeight3D);
            TRootPFJet FWDJET(fwdJet);
            std::vector<TRootPFJet> sortedJetsbyEta;
            sortedJetsbyEta.push_back(FWDJET);
            std::vector<TRootPFJet> nonBs;
            nonBs.push_back(myMuonTree->GetFJet());


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


            /*
             * Filling CosTheta Histograms
             */

            SemiLepTopQuark myLeptonicTopFirst(myEvent_tmp.GPFJets[0], myEvent_tmp.mets[0], myEvent_tmp.Dmuons[0],
                    myEvent_tmp.GPFJets[1], fwdJet, METResolutions);
            SemiLepTopQuark myLeptonicTopSecond(myEvent_tmp.GPFJets[1], myEvent_tmp.mets[0], myEvent_tmp.Dmuons[0],
                    myEvent_tmp.GPFJets[0], fwdJet, METResolutions);
            TRandom myRand(tr.Integer(10000000));
            int index = myRand.Integer(2);
            double iso = myMuonTree->leptonDeltaCorrectedRelIso;
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


            BtagOrderedB.Fill(myLeptonicTopFirst, lumiWeight3D, iso);
            if (myLeptonicTopFirst.hasNeutrinoSolution())
                BtagOrderedBTrue.Fill(myLeptonicTopFirst, lumiWeight3D, iso);

            if (myEvent_tmp.GPFJets.at(0).Pt() > myEvent_tmp.GPFJets.at(1).Pt()) {
                PtOrderedB.Fill(myLeptonicTopFirst, lumiWeight3D, iso);
                if (myLeptonicTopFirst.hasNeutrinoSolution())
                    PtOrderedBTrue.Fill(myLeptonicTopFirst, lumiWeight3D, iso);
            } else {
                PtOrderedB.Fill(myLeptonicTopSecond, lumiWeight3D, iso);
                if (myLeptonicTopSecond.hasNeutrinoSolution())
                    PtOrderedBTrue.Fill(myLeptonicTopSecond, lumiWeight3D, iso);
            }

            if (fabs(eta) <= 1.5)
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

            EtaCutBtagOrderedB.Fill(myLeptonicTopFirst, lumiWeight3D, iso);
            if (myLeptonicTopFirst.hasNeutrinoSolution())
                EtaCutBtagOrderedBTrue.Fill(myLeptonicTopFirst, lumiWeight3D, iso);



            if (myEvent_tmp.GPFJets.at(0).Pt() > myEvent_tmp.GPFJets.at(1).Pt()) {
                EtaCutPtOrderedB.Fill(myLeptonicTopFirst, lumiWeight3D, iso);
                if (myLeptonicTopFirst.hasNeutrinoSolution())
                    EtaCutPtOrderedBTrue.Fill(myLeptonicTopFirst, lumiWeight3D, iso);
            } else {
                EtaCutPtOrderedB.Fill(myLeptonicTopSecond, lumiWeight3D, iso);
                if (myLeptonicTopSecond.hasNeutrinoSolution())
                    EtaCutPtOrderedBTrue.Fill(myLeptonicTopSecond, lumiWeight3D, iso);
            }

            if (genSingleTop != NULL) {
                //                cout << "genSingleTop: " << genSingleTop << endl;
                delete genSingleTop;
            }

            //            cout << "Before Event Fill" << endl;

            //            cout<<"End of event loop --------------------"<<endl;
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

    HT->Write();
    fout->Write();
    fout->Close();

    cout << nInit << "\n" << nHLTrunB << "\n" << nMt << "\n" << nFinal << "\n" << nGoodSolution << endl;
    return 0;
}

