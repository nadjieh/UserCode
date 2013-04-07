/* 
 * File:   OrsoHistogramCreator.C
 * Author: nadjieh
 *
 * Created on October 12, 2012, 12:34 PM
 */
//#define Syst2J1T

#include "TDirectory.h"

#include "../../../AnalysisClasses/EventSelection/interface/ElectronSelector.h"

#include "../../../AnalysisClasses/EventSelection/interface/Event.h"

#include "../../../AnalysisClasses/EventSelection/interface/ElectronHists.h"
#include "../../../AnalysisClasses/EventSelection/interface/MuonHists.h"
#include "../../../AnalysisClasses/EventSelection/interface/PVHists.h"
#include "../../../AnalysisClasses/EventSelection/interface/JetHists.h"
#include "../../../AnalysisClasses/EventSelection/interface/JetSelector.h"
#include "../../../AnalysisClasses/EventSelection/interface/MuonVetoSelector.h"
#include "../../../AnalysisClasses/EventSelection/interface/MetHists.h"
#include "../../../AnalysisClasses/EventSelection/interface/PrimaryVertexSelector.h"
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
#include "../../../AnalysisClasses/ToyAnalysis/interface/GenSingleTopMaker.h"
#include "../../../AnalysisClasses/PhysicsObjects/interface/SemiLepTopQuark.h"
#include "../../../AnalysisClasses/ChiSquared/interface/DR.h"
#include "../../../AnalysisClasses/EventSelection/interface/DifferentHistogramsTwb.h"
#include "../../interface/MuonTree.h"
#include "../../interface/GenInfoMuonTree.h"
#include "../../interface/TRootGenEventMaker.h"
#include "../../interface/WeightHelper.h"


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

int main(int argc, char** argv) {


    SingleTopHistograms Default_Def("Default_Def");
    SingleTopHistograms DefaultTrue_Def("DefaultTrue_Def");
    SingleTopHistograms Default_PuW("Default_PuW");
    SingleTopHistograms Default_BtagPuW("Default_BtagPuW");
    SingleTopHistograms Default_allW("Default_allW");
    SingleTopHistograms DefaultTrue_PuW("DefaultTrue_PuW");
    SingleTopHistograms DefaultTrue_BtagPuW("DefaultTrue_BtagPuW");
    SingleTopHistograms DefaultTrue_allW("DefaultTrue_allW");

    DiLeptonHistograms DiLep_Default_Def("Default_Def");
    DiLeptonHistograms DiLep_DefaultTrue_Def("DefaultTrue_Def");
    DiLeptonHistograms DiLep_Default_PuW("Default_PuW");
    DiLeptonHistograms DiLep_Default_BtagPuW("Default_BtagPuW");
    DiLeptonHistograms DiLep_Default_allW("Default_allW");
    DiLeptonHistograms DiLep_DefaultTrue_PuW("DefaultTrue_PuW");
    DiLeptonHistograms DiLep_DefaultTrue_BtagPuW("DefaultTrue_BtagPuW");
    DiLeptonHistograms DiLep_DefaultTrue_allW("DefaultTrue_allW");
    std::vector<std::string> inputFileNames;
    std::string plotFileName;
    TH1D * METResolutions = 0;
    int doJES = 0;
    int doJER = 0;
    int doMET = 0;
    int dobtag = 0;
    int domistag = 0;
    int dopu = 0;
    int dopdf = 0;
    int dolumi = 0;
    bool isData = false;
    int smearingSkim = 1;
    string sample = "";
    string ttDecayMode = "";
    string prefix = "";
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
        } else if (arg_fth == "btag") {
            f++;
            std::string in(*(argv + f));
            dobtag = atof(in.c_str());
        } else if (arg_fth == "mistag") {
            f++;
            std::string in(*(argv + f));
            domistag = atof(in.c_str());
        } else if (arg_fth == "pileup") {
            f++;
            std::string in(*(argv + f));
            dopu = atof(in.c_str());
        } else if (arg_fth == "JER") {
            f++;
            std::string in(*(argv + f));
            doJER = atof(in.c_str());
        } else if (arg_fth == "MET") {
            f++;
            std::string in(*(argv + f));
            doMET = atof(in.c_str());
        } else if (arg_fth == "dopdf") {
            f++;
            std::string in(*(argv + f));
            dopdf = atof(in.c_str());
        } else if (arg_fth == "dolumi") {
            f++;
            std::string in(*(argv + f));
            dolumi = atof(in.c_str());
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
    TH1D* WeightAll = new TH1D("weight", "weight", 1000, 0, 0.1);
    cout << "**************************" << endl;
    cout << "SYSTEMATIC SITUATION: " << endl;
    cout << "**************************" << endl;
    if (doJES > 0)
        cout << "JESUP SYST" << endl;
    if (doJES < 0)
        cout << "JESDOWN SYST" << endl;
    if (doJER > 0)
        cout << "JERUP SYST" << endl;
    if (doJER < 0)
        cout << "JERDOWN SYST" << endl;
    if (doMET > 0)
        cout << "METUP SYST" << endl;
    if (doMET < 0)
        cout << "METDOWN SYST" << endl;
    if (dobtag > 0)
        cout << "btagUP SYST" << endl;
    if (dobtag < 0)
        cout << "dobtagDOWN SYST" << endl;
    if (domistag > 0)
        cout << "mistagUP SYST" << endl;
    if (domistag < 0)
        cout << "domistagDOWN SYST" << endl;
    if (dopu > 0)
        cout << "pileupUP SYST" << endl;
    if (dopu < 0)
        cout << "pileupDOWN SYST" << endl;
    if (dolumi > 0)
        cout << "lumiUP SYST" << endl;
    if (dolumi < 0)
        cout << "lumiDOWN SYST" << endl;
    if (dopdf != 0 && (dopdf % 2) == 1)
        cout << "pdfUP SYST with parameter " << dopdf << endl;
    if (dopdf != 0 && (dopdf % 2) == 0)
        cout << "pdfDown SYST with parameter " << dopdf - 1 << endl;
    cout << "**************************" << endl;


    TApplication theApp("App", &argc, argv);
    double nGoodSolution = 0;
#ifndef Syst2J1T
    MuonTree * myMuonTree = 0;
#endif /*Syst2J1T*/
#ifdef Syst2J1T
    GenInfoMuonTree * myMuonTree = 0;
#endif /*Syst2J1T*/
    TTree * eventTree = 0;
    GenSingleTopMaker* genSingleTop = 0;
    TRootGenEventMaker* genEvtMaker = 0;
    TRandom3 tr(154456);
    for (unsigned int fNumber = 0; fNumber < inputFileNames.size(); fNumber++) {
        cout << "file number " << fNumber + 1 << ": " << inputFileNames.at(fNumber) << endl;
        TFile* f = TFile::Open(inputFileNames.at(fNumber).c_str());
#ifndef Syst2J1T
        if (doJES > 0)
            myMuonTree = new MuonTree(eventTree, f, sample + "_2J_1T_JESUp");
        if (doJES < 0)
            myMuonTree = new MuonTree(eventTree, f, sample + "_2J_1T_JESDown");
        if (doJER > 0)
            myMuonTree = new MuonTree(eventTree, f, sample + "_2J_1T_JERUp");
        if (doJER < 0)
            myMuonTree = new MuonTree(eventTree, f, sample + "_2J_1T_JERDown");
        if (doMET > 0)
            myMuonTree = new MuonTree(eventTree, f, sample + "_2J_1T_UnclusteredMETUp");
        if (doMET < 0)
            myMuonTree = new MuonTree(eventTree, f, sample + "_2J_1T_UnclusteredMETDown");
#endif /*Syst2J1T*/
#ifdef Syst2J1T
        if (prefix != string("")) {
            cout << "sample name has _" << endl;
            myMuonTree = new GenInfoMuonTree(eventTree, f, sample + "_2J_1T_noSyst", true);
        } else {
            cout << "sample name does not have _" << endl;
            myMuonTree = new GenInfoMuonTree(eventTree, f, sample + "_2J_1T_noSyst");
        }
#endif /*Syst2J1T*/
        cout<<myMuonTree->fChain->GetName()<<endl;
        cout<<myMuonTree->fChain->GetEntries()<<endl;
        for (int eventNumber = 0; eventNumber < myMuonTree->fChain->GetEntriesFast(); eventNumber++) {
            //            cout << "New event: " << eventNumber << "--------------------" << endl;
            myMuonTree->GetEntry(eventNumber);
            //            if (eventNumber > 10)
            //                break;
            if (!myMuonTree->passExtraSelection()) {
                //                cout << "failing" << endl;
                continue;
            }
#ifdef Syst2J1T
            if (myMuonTree->SampleRecognizer(sample) > 0) {
                //                    cout << "I am a top-contained sample :-)" << endl;
                genEvtMaker = new TRootGenEventMaker(myMuonTree, sample);
                genSingleTop = new GenSingleTopMaker(&(genEvtMaker->output));
                delete genEvtMaker;
            } else {
                //                    cout << "I am not a top-contained sample :-(\t" << genEvtMaker << "\t" << genSingleTop << endl;
            }
#endif /*Syst2J1T*/

            //            cout << "Number of tops at analysis level: " << genSingleTop->ntops << endl;
            Event myEvent_tmp = myEventPreparation(myMuonTree);
            TLorentzVector fwdJet = myMuonTree->GetMostFwDJet();
            double puOnlyW = 1;
            double btagpuW = 1;
            double lumiWeight3D = 1;
            if (!isData) {
                GetWeights(myMuonTree, lumiWeight3D, puOnlyW, btagpuW);
            }
#ifdef Syst2J1T
            if (dobtag != 0) {
                puOnlyW = 1;
                btagpuW = 1;
                lumiWeight3D = 1;
                GetWeightsSysBTag(myMuonTree, lumiWeight3D, puOnlyW, btagpuW, dobtag);
            } else if (domistag != 0) {
                puOnlyW = 1;
                btagpuW = 1;
                lumiWeight3D = 1;
                GetWeightsSysMisTag(myMuonTree, lumiWeight3D, puOnlyW, btagpuW, domistag);
            } else if (dopu != 0) {
                puOnlyW = 1;
                btagpuW = 1;
                lumiWeight3D = 1;
                GetWeightsSysPU(myMuonTree, lumiWeight3D, puOnlyW, btagpuW, dopu);
            } else if (dopdf != 0) {
                double W = GetPDFWeight(myMuonTree, dopdf);
                puOnlyW *= W;
                btagpuW *= W;
                lumiWeight3D *= W;
            } else if (dolumi != 0) {
                puOnlyW = 1;
                btagpuW = 1;
                lumiWeight3D = 1;
                GetWeightsSysLumi(myMuonTree, lumiWeight3D, puOnlyW, btagpuW, dolumi);
            }
            WeightAll->Fill(lumiWeight3D);
#endif /*Syst2J1T*/
            SemiLepTopQuark myLeptonicTop(myEvent_tmp.BPFJets[0], myEvent_tmp.mets[0], myEvent_tmp.Dmuons[0],
                    myEvent_tmp.GPFJets[1], fwdJet, METResolutions);
            myLeptonicTop.setMuCharge((int) myMuonTree->charge);

            /*
             * Filling CosTheta Histograms
             */
            if (ttDecayMode == "") {
                if (myLeptonicTop.hasNeutrinoSolution()) {
                    nGoodSolution++;
                    DefaultTrue_Def.Fill(myLeptonicTop, 1, genSingleTop);
                    DefaultTrue_PuW.Fill(myLeptonicTop, puOnlyW, genSingleTop);
                    DefaultTrue_BtagPuW.Fill(myLeptonicTop, btagpuW, genSingleTop);
                    DefaultTrue_allW.Fill(myLeptonicTop, lumiWeight3D, genSingleTop);
                }
                Default_Def.Fill(myLeptonicTop, 1, genSingleTop);
                Default_PuW.Fill(myLeptonicTop, puOnlyW, genSingleTop);
                Default_BtagPuW.Fill(myLeptonicTop, btagpuW, genSingleTop);
                Default_allW.Fill(myLeptonicTop, lumiWeight3D, genSingleTop);
            } else {//Dimuon, muTau, muE TtBar
                if (myLeptonicTop.hasNeutrinoSolution()) {
                    nGoodSolution++;
                    DiLep_DefaultTrue_Def.Fill(myLeptonicTop, 1, genSingleTop);

                    DiLep_DefaultTrue_PuW.Fill(myLeptonicTop, puOnlyW, genSingleTop);
                    DiLep_DefaultTrue_BtagPuW.Fill(myLeptonicTop, btagpuW, genSingleTop);
                    DiLep_DefaultTrue_allW.Fill(myLeptonicTop, lumiWeight3D, genSingleTop);
                }
                DiLep_Default_Def.Fill(myLeptonicTop, 1, genSingleTop);

                DiLep_Default_PuW.Fill(myLeptonicTop, puOnlyW, genSingleTop);
                DiLep_Default_BtagPuW.Fill(myLeptonicTop, btagpuW, genSingleTop);
                DiLep_Default_allW.Fill(myLeptonicTop, lumiWeight3D, genSingleTop);
            }
            if (genSingleTop != NULL) {
                //                cout << "genSingleTop: " << genSingleTop << endl;
                delete genSingleTop;
            }
        }
        cout << "before closing file input " << f->GetName() << endl;
        f->Close();
        delete f;

    }
    cout << "before endjob" << endl;
    TFile * fout = new TFile(plotFileName.c_str(), "recreate");
    fout->cd();

    if (ttDecayMode == "") {
        Default_Def.Write(fout);
        Default_PuW.Write(fout);
        Default_BtagPuW.Write(fout);
        Default_allW.Write(fout);
    } else {
        DiLep_Default_Def.Write(fout);
        DiLep_Default_PuW.Write(fout);
        DiLep_Default_BtagPuW.Write(fout);
        DiLep_Default_allW.Write(fout);
    }
    //    WeightAll->Write();
    fout->Write();
    fout->Close();


    return 0;
}

