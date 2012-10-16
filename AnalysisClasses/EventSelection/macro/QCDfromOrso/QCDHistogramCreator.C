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
#include "../../../../AnalysisClasses/ToyAnalysis/interface/GenSingleTopMaker.h"
#include "../../../../AnalysisClasses/ChiSquared/interface/DR.h"
#include "../../../../TopBrussels/TopTreeAnalysis/MCInformation/interface/Lumi3DReWeighting.h"
#include "../../../../AnalysisClasses/EventSelection/interface/QCDOrso.h"





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
class SingleTopHistograms {
public:

    SingleTopHistograms(string name) : Name(name) {
        Wmass = new TH1D(string(name + "_Wmass").c_str(), string(name + ": final-W-mass").c_str(), 50, 0., 200.);
        Wmass->GetXaxis()->SetTitle("M_{W}");
        WmassII = new TH1D(string(name + "_WmassMET").c_str(), string(name + ": final-W-mass (MET)").c_str(), 50, 0., 200.);
        WmassII->GetXaxis()->SetTitle("M_{W}");
        topMass = new TH1D(string(name + "_topMass").c_str(), string(name + ": final-top-mass").c_str(), 50, 50., 500.);
        topMass->GetXaxis()->SetTitle("M_{top}");
        topMassII = new TH1D(string(name + "_topMassMET").c_str(), string(name + ": final-top-mass (MET)").c_str(), 50, 50., 500.);
        topMassII->GetXaxis()->SetTitle("M_{top}");
        cosTheta = new TH1D(string(name + "cosTheta").c_str(), string(name + ": cos(#theta)").c_str(), 100, -1., 1.);
        cosTheta->GetXaxis()->SetTitle("cos(#theta*)");
        cosThetaII = new TH1D(string(name + "cosTheta_MET").c_str(), string(name + ": cos(#theta) (MET)").c_str(), 100, -1., 1.);
        cosThetaII->GetXaxis()->SetTitle("cos(#theta*)");
        cosTheta2D = new TH2D(string(name + "cosTheta2D").c_str(), string(name + ": cos(#theta); cos(#theta)_{gen}; cos(#theta)_{rec}").c_str(), 100, -1., 1., 100, -1., 1.);
        cosTheta2DII = new TH2D(string(name + "cosTheta2D_MET").c_str(), string(name + ": cos(#theta) (MET); cos(#theta)_{gen}; cos(#theta)_{rec}").c_str(), 100, -1., 1., 100, -1., 1.);
        semiEcosTheta = new TH1D(string(name + "semiEcosTheta").c_str(), string(name + ": cos(#theta)").c_str(), 100, -1., 1.);
        semiEcosTheta->GetXaxis()->SetTitle("cos(#theta*)");
        semiTaucosTheta = new TH1D(string(name + "semiTaucosTheta").c_str(), string(name + ": cos(#theta)").c_str(), 100, -1., 1.);
        semiTaucosTheta->GetXaxis()->SetTitle("cos(#theta*)");
        diTaucosTheta = new TH1D(string(name + "diTaucosTheta").c_str(), string(name + ": cos(#theta)").c_str(), 100, -1., 1.);
        diTaucosTheta->GetXaxis()->SetTitle("cos(#theta*)");
        diEcosTheta = new TH1D(string(name + "diEcosTheta").c_str(), string(name + ": cos(#theta)").c_str(), 100, -1., 1.);
        diEcosTheta->GetXaxis()->SetTitle("cos(#theta*)");
        diMucosTheta = new TH1D(string(name + "diMucosTheta").c_str(), string(name + ": cos(#theta)").c_str(), 100, -1., 1.);
        diMucosTheta->GetXaxis()->SetTitle("cos(#theta*)");
        MuEcosTheta = new TH1D(string(name + "MuEcosTheta").c_str(), string(name + ": cos(#theta)").c_str(), 100, -1., 1.);
        MuEcosTheta->GetXaxis()->SetTitle("cos(#theta*)");
        TauEcosTheta = new TH1D(string(name + "TauEcosTheta").c_str(), string(name + ": cos(#theta)").c_str(), 100, -1., 1.);
        TauEcosTheta->GetXaxis()->SetTitle("cos(#theta*)");
        MuTaucosTheta = new TH1D(string(name + "MuTaucosTheta").c_str(), string(name + ": cos(#theta)").c_str(), 100, -1., 1.);
        MuTaucosTheta->GetXaxis()->SetTitle("cos(#theta*)");
        fullHadcosTheta = new TH1D(string(name + "fullHadcosTheta").c_str(), string(name + ": cos(#theta)").c_str(), 100, -1., 1.);
        fullHadcosTheta->GetXaxis()->SetTitle("cos(#theta*)");

    };

    ~SingleTopHistograms() {
    };

    void Fill(SemiLepTopQuark myLeptonicTop, double lumiWeight3D = 1, GenSingleTopMaker* genTop = 0) {
        Wmass->Fill(myLeptonicTop.W().M(), lumiWeight3D);
        topMass->Fill(myLeptonicTop.top().M(), lumiWeight3D);
        WmassII->Fill(myLeptonicTop.W(2).M(), lumiWeight3D);
        topMassII->Fill(myLeptonicTop.top(2).M(), lumiWeight3D);
        if (genTop == 0) {
            //            cout<<"I am data like!!!"<<endl;
            cosTheta->Fill(myLeptonicTop.cosThetaStar(), lumiWeight3D);
            cosThetaII->Fill(myLeptonicTop.cosThetaStar(2), lumiWeight3D);
        } else if (!genTop->isSemiMuSingleTop) {//Other top decays
            cosTheta->Fill(myLeptonicTop.cosThetaStar(), lumiWeight3D);
            cosThetaII->Fill(myLeptonicTop.cosThetaStar(2), lumiWeight3D);
        } else if (genTop->genSingleTop.MuCharge() != myLeptonicTop.MuCharge()) {// fake muons
            cosTheta->Fill(myLeptonicTop.cosThetaStar(), lumiWeight3D);
            cosThetaII->Fill(myLeptonicTop.cosThetaStar(2), lumiWeight3D);
        } else {
            cosTheta2D->Fill(genTop->genSingleTop.cosThetaStar(0), myLeptonicTop.cosThetaStar(), lumiWeight3D);
            cosTheta2DII->Fill(genTop->genSingleTop.cosThetaStar(0), myLeptonicTop.cosThetaStar(2), lumiWeight3D);
        }
        if (genTop != 0) {
            if (genTop->isDiETt)
                diEcosTheta->Fill(myLeptonicTop.cosThetaStar(), lumiWeight3D);
            else if (genTop->isDiMuTt)
                diMucosTheta->Fill(myLeptonicTop.cosThetaStar(), lumiWeight3D);
            else if (genTop->isDiTauTt)
                diTaucosTheta->Fill(myLeptonicTop.cosThetaStar(), lumiWeight3D);
            else if (genTop->isSemiTauTt)
                semiTaucosTheta->Fill(myLeptonicTop.cosThetaStar(), lumiWeight3D);
            else if (genTop->isSemiElecTt)
                semiEcosTheta->Fill(myLeptonicTop.cosThetaStar(), lumiWeight3D);
            else if (genTop->isMuETt)
                MuEcosTheta->Fill(myLeptonicTop.cosThetaStar(), lumiWeight3D);
            else if (genTop->isMuTauTt)
                MuTaucosTheta->Fill(myLeptonicTop.cosThetaStar(), lumiWeight3D);
            else if (genTop->isETauTt)
                TauEcosTheta->Fill(myLeptonicTop.cosThetaStar(), lumiWeight3D);
            else if (genTop->isFullHadTt)
                fullHadcosTheta->Fill(myLeptonicTop.cosThetaStar(), lumiWeight3D);
        }
    }

    void Write(TDirectory * dir) {
        TDirectory * inDir = dir->mkdir(Name.c_str());
        inDir->cd();
        cosTheta->Write();
        Wmass->Write();
        topMass->Write();
        cosThetaII->Write();
        WmassII->Write();
        topMassII->Write();
        cosTheta2D->Write();
        cosTheta2DII->Write();
        (inDir->mkdir("ttDecayModes"))->cd();
        semiEcosTheta->Write();
        semiTaucosTheta->Write();
        diTaucosTheta->Write();
        diEcosTheta->Write();
        diMucosTheta->Write();
        MuEcosTheta->Write();
        TauEcosTheta->Write();
        MuTaucosTheta->Write();
        fullHadcosTheta->Write();
        inDir->cd();
        dir->cd();
    }
    string Name;
    TH1D * Wmass;
    TH1D * WmassII;
    TH1D * topMass;
    TH1D * topMassII;
    TH1D * cosTheta;
    TH1D * cosThetaII;
    TH2D * cosTheta2D;
    TH2D * cosTheta2DII;
    TH1D * semiEcosTheta;
    TH1D * semiTaucosTheta;
    TH1D * diTaucosTheta;
    TH1D * diEcosTheta;
    TH1D * diMucosTheta;
    TH1D * MuEcosTheta;
    TH1D * TauEcosTheta;
    TH1D * MuTaucosTheta;
    TH1D * fullHadcosTheta;

};

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
    string PUWeightFileName = "";
    double XSec = 1;
    double Luminosity = 1;
    double PreSelEff = 1;
    double doJES = 1;
    bool isData = false;
    int smearingSkim = 1;
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
        }
    }
    cout<<"START"<<endl;

    TFile* f = 0;
    TApplication theApp("App", &argc, argv);
    double nInit = 0;
    double nFinal = 0;
    double nHLTrunB = 0;
    double nMt = 0;
    double nGoodSolution = 0;

    QCDOrso * myQCD = 0;
    TTree * eventTree = 0;

    Lumi3DReWeighting Lumi3DWeights;


    GenSingleTopMaker* genSingleTop = 0;
    TH1D * ntag = new TH1D("ntag", "ntag", 10, -0.5, 9.5);
    for (unsigned int fNumber = 0; fNumber < inputFileNames.size(); fNumber++) {
        cout << "file number " << fNumber + 1 << ": " << inputFileNames.at(fNumber) << endl;
        TFile* f = TFile::Open(inputFileNames.at(fNumber).c_str());
        myQCD = new QCDOrso(eventTree, f);
        double lumiWeight3D = 1;
        for (int eventNumber = 0; eventNumber < myQCD->fChain->GetEntriesFast(); eventNumber++) {
            myQCD->GetEntry(eventNumber);

            TLorentzVector muon(-1, -1, -1, -1);
            muon.SetPtEtaPhiE(myQCD->leptonPt, myQCD->leptonEta, myQCD->leptonPhi, myQCD->leptonPt);

            TLorentzVector bjet(-1, -1, -1, -1);
            bjet.SetPtEtaPhiE(myQCD->bJetPt, myQCD->bJetEta, myQCD->bJetPhi, myQCD->bJetE);

            TLorentzVector fjet(-1, -1, -1, -1);
            fjet.SetPtEtaPhiE(myQCD->fJetPt, myQCD->fJetEta, myQCD->fJetPhi, myQCD->fJetE);

            TLorentzVector met(-1, -1, -1, -1);
            met.SetPtEtaPhiE(myQCD->metPt, 0, myQCD->metPhi, myQCD->metPt);

            DR<TLorentzVector> dr;
            dr.SetVectors(muon, bjet);
            if(dr.getValue() < 0.3)
                continue;
//            dr.SetVectors(muon, fjet);
//            if(dr.getValue() < 0.3)
//                continue;
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
            TLorentzVector myB;
            TLorentzVector myF;
//            if(eventNumber%2 == 0){
//                myB = bjet;
//                myF = fjet;
//            }
//            else{
//                myB = fjet;
//                myF = bjet;
//            }
//            SemiLepTopQuark myLeptonicTop(myB, met, muon, myF, fwdJet, METResolutions);
            SemiLepTopQuark myLeptonicTop(bjet, met, muon, fjet, fwdJet, METResolutions);
            myLeptonicTop.setMuCharge((int) myQCD->charge);

            double eta = fabs(fwdJet.Eta());
            double ht = myQCD->bJetPt + myQCD->fJetPt + myQCD->leptonPt + myQCD->metPt;
            HT->Fill(ht, lumiWeight3D);

            if (myLeptonicTop.hasNeutrinoSolution()) {
                nGoodSolution++;
                DefaultTrue_Def.Fill(myLeptonicTop, lumiWeight3D, genSingleTop);
                DefaultTrue_BtagPuW.Fill(myLeptonicTop, lumiWeight3D, genSingleTop);
                DefaultTrue_allW.Fill(myLeptonicTop, lumiWeight3D, genSingleTop);
                DefaultTrue_PuW.Fill(myLeptonicTop, lumiWeight3D, genSingleTop);
                if (ht >= 180){
                    HtCutTrue_Def.Fill(myLeptonicTop, lumiWeight3D, genSingleTop);
                }
                else
                    AntiHtCutTrue_Def.Fill(myLeptonicTop, lumiWeight3D, genSingleTop);
                if (eta > 1.5){
                    EtaCutTrue_Def.Fill(myLeptonicTop, lumiWeight3D, genSingleTop);
                    EtaCutTrue_BtagPuW.Fill(myLeptonicTop, lumiWeight3D, genSingleTop);
                    EtaCutTrue_PuW.Fill(myLeptonicTop, lumiWeight3D, genSingleTop);
                    EtaCutTrue_allW.Fill(myLeptonicTop, lumiWeight3D, genSingleTop);
                }
                else
                    AntiEtaCutTrue_Def.Fill(myLeptonicTop, lumiWeight3D, genSingleTop);
            }
            Default_Def.Fill(myLeptonicTop, lumiWeight3D, genSingleTop);
            Default_BtagPuW.Fill(myLeptonicTop, lumiWeight3D, genSingleTop);
            Default_PuW.Fill(myLeptonicTop, lumiWeight3D, genSingleTop);
            Default_allW.Fill(myLeptonicTop, lumiWeight3D, genSingleTop);
            if (ht >= 180)
                HtCut_Def.Fill(myLeptonicTop, lumiWeight3D, genSingleTop);
            else
                AntiHtCut_Def.Fill(myLeptonicTop, lumiWeight3D, genSingleTop);
            if (eta > 1.5){
                EtaCut_Def.Fill(myLeptonicTop, lumiWeight3D, genSingleTop);
                EtaCut_BtagPuW.Fill(myLeptonicTop, lumiWeight3D, genSingleTop);
                EtaCut_PuW.Fill(myLeptonicTop, lumiWeight3D, genSingleTop);
                EtaCut_allW.Fill(myLeptonicTop, lumiWeight3D, genSingleTop);
            }
            else
                AntiEtaCut_Def.Fill(myLeptonicTop, lumiWeight3D, genSingleTop);

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
            std::vector<TRootPFJet> nonBs; nonBs.push_back(nonBJET);
            nonBJets.FillPFJets(nonBs, nonBs.size(), myEvent_tmp.BPFJets.size(), false, 1);
            std::vector<TRootPFJet> sortedJetsbyEta; sortedJetsbyEta.push_back(FWDJET);
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

            atLeastOnGPV_allW.Fill(myEvent_tmp.Gpvs, myEvent_tmp.Gpvs.size(), 1);
            GoldenFinalPUMuons_allW.Fill(myEvent_tmp.Dmuons, myEvent_tmp.Dmuons.size(), 1);
            Jets_allW.FillPFJets(myEvent_tmp.GPFJets, myEvent_tmp.GPFJets.size(), myEvent_tmp.BPFJets.size(), false, 1);
            BJets_allW.FillPFJets(myEvent_tmp.BPFJets, myEvent_tmp.BPFJets.size(), myEvent_tmp.BPFJets.size(), false, 1);
            nonBJets_allW.FillPFJets(nonBs, nonBs.size(), myEvent_tmp.BPFJets.size(), false, 1);
            FwDJet_allW.FillPFJets(sortedJetsbyEta, sortedJetsbyEta.size(), myEvent_tmp.BPFJets.size(), false, 1);
            MetHist_allW.Fill(&myEvent_tmp.mets.at(0), 1);
            allW_finalMT->Fill(mt, 1);
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
    
    Default_Def.Write(fout);
    Default_BtagPuW.Write(fout);
    Default_PuW.Write(fout);
    Default_allW.Write(fout);
    EtaCut_BtagPuW.Write(fout);
    EtaCut_Def.Write(fout);
    EtaCut_allW.Write(fout);
    EtaCut_PuW.Write(fout);
    
    AntiEtaCut_Def.Write(fout);
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
    HT->Write();
    
    ntag->Write();
    fout->Write();
    fout->Close();

    cout << nInit << "\n" << nHLTrunB << "\n" << nMt << "\n" << nFinal << "\n" << nGoodSolution << endl;
    return 0;
}

