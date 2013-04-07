/* 
 * File:   OrsoHistogramCreator.C
 * Author: nadjieh
 *
 * Created on October 12, 2012, 12:34 PM
 */
#define ISDATA
#define QCD
//#define Wtemplate
#include "TDirectory.h"

#include "../../../../AnalysisClasses/EventSelection/interface/ElectronSelector.h"

#include "../../../../AnalysisClasses/EventSelection/interface/Event.h"

#include "../../../../AnalysisClasses/EventSelection/interface/ElectronHists.h"
#include "../../../../AnalysisClasses/EventSelection/interface/MuonHists.h"
#include "../../../../AnalysisClasses/EventSelection/interface/PVHists.h"
#include "../../../../AnalysisClasses/EventSelection/interface/JetHists.h"
#include "../../../../AnalysisClasses/EventSelection/interface/JetSelector.h"
#include "../../../../AnalysisClasses/EventSelection/interface/MuonVetoSelector.h"
#include "../../../../AnalysisClasses/EventSelection/interface/MetHists.h"
#include "../../../../AnalysisClasses/EventSelection/interface/PrimaryVertexSelector.h"
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
#include "../../../../AnalysisClasses/ToyAnalysis/interface/GenSingleTopMaker.h"
#include "../../../../AnalysisClasses/PhysicsObjects/interface/SemiLepTopQuark.h"
#include "../../../../AnalysisClasses/ChiSquared/interface/DR.h"
#include "../../../../AnalysisClasses/EventSelection/interface/DifferentHistogramsTwb.h"
#include "../../../interface/MuonTree.h"
#include "../../../interface/GenInfoMuonTree.h"
#include "../../../interface/TRootGenEventMaker.h"


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
    BJET.setBtag_combinedSecondaryVertexBJetTags(input->highBTag);
    TRootPFJet nonBJET(input->GetFJet());
    nonBJET.setBtag_combinedSecondaryVertexBJetTags(input->lowBTag);
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
    BJET.setBtag_combinedSecondaryVertexBJetTags(input->highBTag);
    TRootPFJet nonBJET(input->GetFJet());
    nonBJET.setBtag_combinedSecondaryVertexBJetTags(input->lowBTag);
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

bool TakeQCDEvent(MuonTree* myMuonTree, int isolation = 0) {
    if (isolation == 1) {//central
        return (myMuonTree->leptonDeltaCorrectedRelIso > 0.2 && myMuonTree->leptonDeltaCorrectedRelIso < 0.5);
    } else if (isolation == 2) {//shrink
        return (myMuonTree->leptonDeltaCorrectedRelIso > 0.2 && myMuonTree->leptonDeltaCorrectedRelIso < 0.4);
    } else if (isolation == 3) {//enlarge
        return (myMuonTree->leptonDeltaCorrectedRelIso > 0.2 && myMuonTree->leptonDeltaCorrectedRelIso < 0.6);
    } else if (isolation == 4) {//shift
        return (myMuonTree->leptonDeltaCorrectedRelIso > 0.3 && myMuonTree->leptonDeltaCorrectedRelIso < 0.6);
    }
    return true;
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

    SingleTopHistograms Default_Def("Default_Def", true);
    SingleTopHistograms EtaCut_Def("EtaFwD_Def", true);
    SingleTopHistograms HtCut_Def("HtCut_Def", true);
    SingleTopHistograms AntiEtaCut_Def("antiEtaFwD_Def", true);
    SingleTopHistograms AntiHtCut_Def("antiHtCut_Def", true);

    SingleTopHistograms DefaultTrue_Def("DefaultTrue_Def", true);
    SingleTopHistograms EtaCutTrue_Def("EtaFwDTrue_Def", true);
    SingleTopHistograms HtCutTrue_Def("HtCutTrue_Def", true);
    SingleTopHistograms AntiEtaCutTrue_Def("antiEtaFwDTrue_Def", true);
    SingleTopHistograms AntiHtCutTrue_Def("antiHtCutTrue_Def", true);

    SingleTopHistograms Default_PuW("Default_PuW", true);
    SingleTopHistograms Default_BtagPuW("Default_BtagPuW", true);
    SingleTopHistograms Default_allW("Default_allW", true);

    SingleTopHistograms EtaCut_PuW("EtaFwD_PuW", true);
    SingleTopHistograms EtaCut_BtagPuW("EtaFwD_BtagPuW", true);
    SingleTopHistograms EtaCut_allW("EtaFwD_allW", true);

    SingleTopHistograms DefaultTrue_PuW("DefaultTrue_PuW", true);
    SingleTopHistograms DefaultTrue_BtagPuW("DefaultTrue_BtagPuW", true);
    SingleTopHistograms DefaultTrue_allW("DefaultTrue_allW", true);

    SingleTopHistograms EtaCutTrue_PuW("EtaFwDTrue_PuW", true);
    SingleTopHistograms EtaCutTrue_BtagPuW("EtaFwDTrue_BtagPuW", true);
    SingleTopHistograms EtaCutTrue_allW("EtaFwDTrue_allW", true);

    DiLeptonHistograms DiLep_Default_Def("Default_Def", true);
    DiLeptonHistograms DiLep_EtaCut_Def("EtaFwD_Def", true);
    DiLeptonHistograms DiLep_HtCut_Def("HtCut_Def", true);
    DiLeptonHistograms DiLep_AntiEtaCut_Def("antiEtaFwD_Def", true);
    DiLeptonHistograms DiLep_AntiHtCut_Def("antiHtCut_Def", true);

    DiLeptonHistograms DiLep_DefaultTrue_Def("DefaultTrue_Def", true);
    DiLeptonHistograms DiLep_EtaCutTrue_Def("EtaFwDTrue_Def", true);
    DiLeptonHistograms DiLep_HtCutTrue_Def("HtCutTrue_Def", true);
    DiLeptonHistograms DiLep_AntiEtaCutTrue_Def("antiEtaFwDTrue_Def", true);
    DiLeptonHistograms DiLep_AntiHtCutTrue_Def("antiHtCutTrue_Def", true);

    DiLeptonHistograms DiLep_Default_PuW("Default_PuW", true);
    DiLeptonHistograms DiLep_Default_BtagPuW("Default_BtagPuW", true);
    DiLeptonHistograms DiLep_Default_allW("Default_allW", true);

    DiLeptonHistograms DiLep_EtaCut_PuW("EtaFwD_PuW", true);
    DiLeptonHistograms DiLep_EtaCut_BtagPuW("EtaFwD_BtagPuW", true);
    DiLeptonHistograms DiLep_EtaCut_allW("EtaFwD_allW", true);

    DiLeptonHistograms DiLep_DefaultTrue_PuW("DefaultTrue_PuW", true);
    DiLeptonHistograms DiLep_DefaultTrue_BtagPuW("DefaultTrue_BtagPuW", true);
    DiLeptonHistograms DiLep_DefaultTrue_allW("DefaultTrue_allW", true);

    DiLeptonHistograms DiLep_EtaCutTrue_PuW("EtaFwDTrue_PuW", true);
    DiLeptonHistograms DiLep_EtaCutTrue_BtagPuW("EtaFwDTrue_BtagPuW", true);
    DiLeptonHistograms DiLep_EtaCutTrue_allW("EtaFwDTrue_allW", true);


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
    TH2D * nVtx_cosTheta = new TH2D("nVtxcosTheta", "nVtxcosTheta;N_{vtx};cos(#theta_{l}*)", 100, 0, 100, 100, -1., 1.);
    nVtx_cosTheta->Sumw2();
    std::vector<std::string> inputFileNames;
    std::string plotFileName;
    TH1D * METResolutions = 0;
    double doJES = 1;
    bool isData = false;
    int smearingSkim = 1;
    string sample = "";
    string ttDecayMode = "";
    string prefix = "";
    int nWM = 0;
    int nWP = 0;
    int isolation = 0;
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
        } else if (arg_fth == "JES") {
            f++;
            std::string in(*(argv + f));
            doJES = atof(in.c_str());
        } else if (arg_fth == "ISO") {
            f++;
            std::string in(*(argv + f));
            isolation = atof(in.c_str());
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
#ifdef ISDATA
#if !defined QCD && !defined Wtemplate
        myMuonTree = new MuonTree(eventTree, f, sample + "_2J_1T_noSyst");
#endif /*QCD*/
#ifdef QCD
        myMuonTree = new MuonTree(eventTree, f, sample + "_2J_1T_QCD_noSyst");
#endif /*QCD*/
#ifdef Wtemplate
        myMuonTree = new MuonTree(eventTree, f, sample + "_2J_0T_noSyst");
#endif /*Wtemplate*/
#endif /*ISDATA*/
#ifndef ISDATA
        if (prefix != string("")) {
            cout << "sample name has _" << endl;
            myMuonTree = new GenInfoMuonTree(eventTree, f, sample + "_2J_1T_noSyst", true);
        } else {
            cout << "sample name does not have _" << endl;
            myMuonTree = new GenInfoMuonTree(eventTree, f, sample + "_2J_1T_noSyst");
        }
#endif /*ISDATA*/

        if (string(myMuonTree->fChain->GetName()) == string("Data_2J_1T_QCD_noSyst")) {
            if (isolation == 0)
                plotFileName = "QCD_plots.root";
            else {
                stringstream isostr;
                isostr<<"QCD"<<isolation<<"_plots.root"; 
                plotFileName = isostr.str();
            }
        }
        if (string(myMuonTree->fChain->GetName()) == string("Data_2J_0T_noSyst")) {
            plotFileName = "WTemplateDefFormat_plots.root";
        }
        for (int eventNumber = 0; eventNumber < myMuonTree->fChain->GetEntriesFast(); eventNumber++) {
            //            cout << "New event: " << eventNumber << "--------------------" << endl;
            myMuonTree->GetEntry(eventNumber);
            nFinal++;
            if (!TakeQCDEvent(myMuonTree, isolation))
                continue;
            if (!myMuonTree->passExtraSelection())
                continue;
#if defined Wtemplate && defined ISDATA
            //            if(!myMuonTree->jetsForWtemplate()){
            //                continue;
            //            }
#endif /*Wtemplate*/
            bool isLeptonicTop = false;
            bool isHadronicTop = false;
            std::vector<int> nonTopW;
#ifndef ISDATA
            if (myMuonTree->SampleRecognizer(sample) > 0) {
                //                    cout << "I am a top-contained sample :-)" << endl;
                genEvtMaker = new TRootGenEventMaker(myMuonTree, sample);
                genSingleTop = new GenSingleTopMaker(&(genEvtMaker->output));
                isLeptonicTop = genEvtMaker->output.tops()[0].isLeptonicMu();
                isHadronicTop = genEvtMaker->output.tops()[0].isHadronic();
                nonTopW = genEvtMaker->output.getNonTopWList();
                delete genEvtMaker;
            } else {
                //                    cout << "I am not a top-contained sample :-(\t" << genEvtMaker << "\t" << genSingleTop << endl;
            }
#endif /*ISDATA*/

            //            cout << "Number of tops at analysis level: " << genSingleTop->ntops << endl;
            Event myEvent_tmp = myEventPreparation(myMuonTree);

            double mt = myMuonTree->GetMTW();
            TLorentzVector fwdJet = myMuonTree->GetMostFwDJet();
            double eta = fabs(fwdJet.Eta());
            double ht = myMuonTree->GetHT();

            if (string(myMuonTree->fChain->GetName()) == string("Data_2J_1T_QCD_noSyst")) {
                //                cout << "QCD template" << endl;
                DR<TLorentzVector> dr;
                dr.SetVectors(myEvent_tmp.Dmuons[0], myEvent_tmp.BPFJets[0]);
                if (dr.getValue() < 0.3)
                    continue;
                //                dr.SetVectors(myEvent_tmp.Dmuons[0], myEvent_tmp.GPFJets[1]);
                //                if (dr.getValue() < 0.3)
                //                    continue;
            }
            double puOnlyW = 1;
            double btagpuW = 1;
            double lumiWeight3D = 1;
            if (!isData) {
                //                GetWeightsNoPu(myMuonTree, lumiWeight3D, puOnlyW, btagpuW);
                GetWeights(myMuonTree, lumiWeight3D, puOnlyW, btagpuW);
            }

            SemiLepTopQuark myLeptonicTop(myEvent_tmp.BPFJets[0], myEvent_tmp.mets[0], myEvent_tmp.Dmuons[0],
                    myEvent_tmp.GPFJets[1], fwdJet, METResolutions);
            myLeptonicTop.setMuCharge((int) myMuonTree->charge);
            HT->Fill(ht, lumiWeight3D);
            //            cout << "Before CosTheta Fill" << endl;
            if (myMuonTree->charge > 0)
                nWP++;
            if (myMuonTree->charge < 0)
                nWM++;
            /*
             * Filling CosTheta Histograms
             */
            if (ttDecayMode == "") {
                if (myLeptonicTop.hasNeutrinoSolution()) {
                    nGoodSolution++;
                    nVtx_cosTheta->Fill(myMuonTree->nGoodVertices, myLeptonicTop.cosThetaStar());
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
            //            cout << "After CosTheta Fill" << endl;

            if (genSingleTop != NULL) {
                //                cout << "genSingleTop: " << genSingleTop << endl;
                delete genSingleTop;
            }

            /*
             * Filling Event Histograms
             */
            //            cout << "Before Event Fill" << endl;
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
    nVtx_cosTheta->Write();
    fout->Write();
    fout->Close();

    cout << nInit << "\n" << nHLTrunB << "\n" << nMt << "\n" << nFinal << "\n" << nGoodSolution << endl;
    cout << "nW+: " << nWP << "\tnW-: " << nWM << endl;
    return 0;
}

