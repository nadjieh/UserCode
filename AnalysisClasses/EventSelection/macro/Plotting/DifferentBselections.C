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
using namespace std;
using namespace TopTree;
/*
 * 
 */
//class SingleTopHistograms{
//public:
//    SingleTopHistograms(string name):Name(name){
//        Wmass = new TH1D(string(name+"_Wmass").c_str(),string(name+": final-W-mass").c_str(),50, 0.,200.);
//        Wmass->GetXaxis()->SetTitle("M_{W}");
//        WmassII = new TH1D(string(name+"_WmassMET").c_str(),string(name+": final-W-mass (MET)").c_str(),50, 0.,200.);
//        WmassII->GetXaxis()->SetTitle("M_{W}");
//        topMass = new TH1D(string(name+"_topMass").c_str(),string(name+": final-top-mass").c_str(),50, 50.,500.);
//        topMass->GetXaxis()->SetTitle("M_{top}");
//        topMassII = new TH1D(string(name+"_topMassMET").c_str(),string(name+": final-top-mass (MET)").c_str(),50, 50.,500.);
//        topMassII->GetXaxis()->SetTitle("M_{top}");
//        cosTheta = new TH1D(string(name+"cosTheta").c_str(),string(name+": cos(#theta)").c_str(),50, -1.,1.);
//        cosTheta->GetXaxis()->SetTitle("cos(#theta*)");
//        cosThetaII = new TH1D(string(name+"cosTheta_MET").c_str(),string(name+": cos(#theta) (MET)").c_str(),50, -1.,1.);
//        cosThetaII->GetXaxis()->SetTitle("cos(#theta*)");
//    };
//    ~SingleTopHistograms(){};
//    void Fill(SemiLepTopQuark myLeptonicTop, double  lumiWeight3D = 1){
//        cosTheta->Fill(myLeptonicTop.cosThetaStar(),lumiWeight3D);
//        cosThetaII->Fill(myLeptonicTop.cosThetaStar(2),lumiWeight3D);
//        Wmass->Fill(myLeptonicTop.W().M(),lumiWeight3D);
//        topMass->Fill(myLeptonicTop.top().M(),lumiWeight3D);
//        WmassII->Fill(myLeptonicTop.W(2).M(),lumiWeight3D);
//        topMassII->Fill(myLeptonicTop.top(2).M(),lumiWeight3D);
//    }
//    void Write(TDirectory * dir){
//        (dir->mkdir(Name.c_str()))->cd();
//        cosTheta->Write();
//        Wmass->Write();
//        topMass->Write();
//        cosThetaII->Write();
//        WmassII->Write();
//        topMassII->Write();
//        dir->cd();
//    }
//    string Name;
//    TH1D * Wmass;
//    TH1D * WmassII;
//    TH1D * topMass;
//    TH1D * topMassII;
//    TH1D * cosTheta;
//    TH1D * cosThetaII;
//};

//class SingleTopHistograms {
//public:
//
//    SingleTopHistograms(string name) : Name(name) {
//        Wmass = new TH1D(string(name + "_Wmass").c_str(), string(name + ": final-W-mass").c_str(), 50, 0., 200.);
//        Wmass->GetXaxis()->SetTitle("M_{W}");
//        WmassII = new TH1D(string(name + "_WmassMET").c_str(), string(name + ": final-W-mass (MET)").c_str(), 50, 0., 200.);
//        WmassII->GetXaxis()->SetTitle("M_{W}");
//        topMass = new TH1D(string(name + "_topMass").c_str(), string(name + ": final-top-mass").c_str(), 50, 50., 500.);
//        topMass->GetXaxis()->SetTitle("M_{top}");
//        topMassII = new TH1D(string(name + "_topMassMET").c_str(), string(name + ": final-top-mass (MET)").c_str(), 50, 50., 500.);
//        topMassII->GetXaxis()->SetTitle("M_{top}");
//        cosTheta = new TH1D(string(name + "cosTheta").c_str(), string(name + ": cos(#theta)").c_str(), 50, -1., 1.);
//        cosTheta->GetXaxis()->SetTitle("cos(#theta*)");
//        cosThetaII = new TH1D(string(name + "cosTheta_MET").c_str(), string(name + ": cos(#theta) (MET)").c_str(), 50, -1., 1.);
//        cosThetaII->GetXaxis()->SetTitle("cos(#theta*)");
//        cosTheta2D = new TH2D(string(name + "cosTheta2D").c_str(), string(name + ": cos(#theta); cos(#theta)_{gen}; cos(#theta)_{rec}").c_str(), 50, -1., 1., 50, -1., 1.);
//        cosTheta2DII = new TH2D(string(name + "cosTheta2D_MET").c_str(), string(name + ": cos(#theta) (MET); cos(#theta)_{gen}; cos(#theta)_{rec}").c_str(), 50, -1., 1., 50, -1., 1.);
//        semiEcosTheta = new TH1D(string(name + "semiEcosTheta").c_str(), string(name + ": cos(#theta)").c_str(), 50, -1., 1.);
//        semiEcosTheta->GetXaxis()->SetTitle("cos(#theta*)");
//        semiTaucosTheta = new TH1D(string(name + "semiTaucosTheta").c_str(), string(name + ": cos(#theta)").c_str(), 50, -1., 1.);
//        semiTaucosTheta->GetXaxis()->SetTitle("cos(#theta*)");
//        diTaucosTheta = new TH1D(string(name + "diTaucosTheta").c_str(), string(name + ": cos(#theta)").c_str(), 50, -1., 1.);
//        diTaucosTheta->GetXaxis()->SetTitle("cos(#theta*)");
//        diEcosTheta = new TH1D(string(name + "diEcosTheta").c_str(), string(name + ": cos(#theta)").c_str(), 50, -1., 1.);
//        diEcosTheta->GetXaxis()->SetTitle("cos(#theta*)");
//        diMucosTheta = new TH1D(string(name + "diMucosTheta").c_str(), string(name + ": cos(#theta)").c_str(), 50, -1., 1.);
//        diMucosTheta->GetXaxis()->SetTitle("cos(#theta*)");
//        MuEcosTheta = new TH1D(string(name + "MuEcosTheta").c_str(), string(name + ": cos(#theta)").c_str(), 50, -1., 1.);
//        MuEcosTheta->GetXaxis()->SetTitle("cos(#theta*)");
//        TauEcosTheta = new TH1D(string(name + "TauEcosTheta").c_str(), string(name + ": cos(#theta)").c_str(), 50, -1., 1.);
//        TauEcosTheta->GetXaxis()->SetTitle("cos(#theta*)");
//        MuTaucosTheta = new TH1D(string(name + "MuTaucosTheta").c_str(), string(name + ": cos(#theta)").c_str(), 50, -1., 1.);
//        MuTaucosTheta->GetXaxis()->SetTitle("cos(#theta*)");
//        fullHadcosTheta = new TH1D(string(name + "fullHadcosTheta").c_str(), string(name + ": cos(#theta)").c_str(), 50, -1., 1.);
//        fullHadcosTheta->GetXaxis()->SetTitle("cos(#theta*)");
//        IsoCosTheta = new TH2D(string(name + "IsoCosTheta").c_str(), string(name + ";isolation; cos(#theta)").c_str(), 50, -1., 1., 15, 0, 0.15);
//        //        IsoCosTheta->GetXaxis()->SetTitle("cos(#theta*)");
//
//    };
//
//    ~SingleTopHistograms() {
//    };
//
//    void Fill(SemiLepTopQuark myLeptonicTop, double lumiWeight3D = 1, double iso = 0, GenSingleTopMaker* genTop = 0) {
//        Wmass->Fill(myLeptonicTop.W().M(), lumiWeight3D);
//        topMass->Fill(myLeptonicTop.top().M(), lumiWeight3D);
//        WmassII->Fill(myLeptonicTop.W(2).M(), lumiWeight3D);
//        topMassII->Fill(myLeptonicTop.top(2).M(), lumiWeight3D);
//        if (genTop == 0) {
//            //            cout<<"I am data like!!!"<<endl;
//            cosTheta->Fill(myLeptonicTop.cosThetaStar(), lumiWeight3D);
//            cosThetaII->Fill(myLeptonicTop.cosThetaStar(2), lumiWeight3D);
//            IsoCosTheta->Fill(myLeptonicTop.cosThetaStar(), iso, lumiWeight3D);
//        } else if (!genTop->isSemiMuSingleTop) {//Other top decays
//            cosTheta->Fill(myLeptonicTop.cosThetaStar(), lumiWeight3D);
//            cosThetaII->Fill(myLeptonicTop.cosThetaStar(2), lumiWeight3D);
//            IsoCosTheta->Fill(myLeptonicTop.cosThetaStar(), iso, lumiWeight3D);
//        } else if (genTop->genSingleTop.MuCharge() != myLeptonicTop.MuCharge()) {// fake muons
//            cosTheta->Fill(myLeptonicTop.cosThetaStar(), lumiWeight3D);
//            cosThetaII->Fill(myLeptonicTop.cosThetaStar(2), lumiWeight3D);
//            IsoCosTheta->Fill(myLeptonicTop.cosThetaStar(), iso, lumiWeight3D);
//        } else {
//            cosTheta2D->Fill(genTop->genSingleTop.cosThetaStar(0), myLeptonicTop.cosThetaStar(), lumiWeight3D);
//            cosTheta2DII->Fill(genTop->genSingleTop.cosThetaStar(0), myLeptonicTop.cosThetaStar(2), lumiWeight3D);
//        }
//        if (genTop != 0) {
//            if (genTop->isDiETt)
//                diEcosTheta->Fill(myLeptonicTop.cosThetaStar(), lumiWeight3D);
//            else if (genTop->isDiMuTt)
//                diMucosTheta->Fill(myLeptonicTop.cosThetaStar(), lumiWeight3D);
//            else if (genTop->isDiTauTt)
//                diTaucosTheta->Fill(myLeptonicTop.cosThetaStar(), lumiWeight3D);
//            else if (genTop->isSemiTauTt)
//                semiTaucosTheta->Fill(myLeptonicTop.cosThetaStar(), lumiWeight3D);
//            else if (genTop->isSemiElecTt)
//                semiEcosTheta->Fill(myLeptonicTop.cosThetaStar(), lumiWeight3D);
//            else if (genTop->isMuETt)
//                MuEcosTheta->Fill(myLeptonicTop.cosThetaStar(), lumiWeight3D);
//            else if (genTop->isMuTauTt)
//                MuTaucosTheta->Fill(myLeptonicTop.cosThetaStar(), lumiWeight3D);
//            else if (genTop->isETauTt)
//                TauEcosTheta->Fill(myLeptonicTop.cosThetaStar(), lumiWeight3D);
//            else if (genTop->isFullHadTt)
//                fullHadcosTheta->Fill(myLeptonicTop.cosThetaStar(), lumiWeight3D);
//        }
//    }
//
//    void Write(TDirectory * dir) {
//        TDirectory * inDir = dir->mkdir(Name.c_str());
//        inDir->cd();
//        cosTheta->Write();
//        Wmass->Write();
//        topMass->Write();
//        cosThetaII->Write();
//        WmassII->Write();
//        topMassII->Write();
//        cosTheta2D->Write();
//        cosTheta2DII->Write();
//        (inDir->mkdir("ttDecayModes"))->cd();
//        semiEcosTheta->Write();
//        semiTaucosTheta->Write();
//        diTaucosTheta->Write();
//        diEcosTheta->Write();
//        diMucosTheta->Write();
//        MuEcosTheta->Write();
//        TauEcosTheta->Write();
//        MuTaucosTheta->Write();
//        fullHadcosTheta->Write();
//        IsoCosTheta->Write();
//        inDir->cd();
//        dir->cd();
//    }
//    string Name;
//    TH1D * Wmass;
//    TH1D * WmassII;
//    TH1D * topMass;
//    TH1D * topMassII;
//    TH1D * cosTheta;
//    TH1D * cosThetaII;
//    TH2D * cosTheta2D;
//    TH2D * cosTheta2DII;
//    TH1D * semiEcosTheta;
//    TH1D * semiTaucosTheta;
//    TH1D * diTaucosTheta;
//    TH1D * diEcosTheta;
//    TH1D * diMucosTheta;
//    TH1D * MuEcosTheta;
//    TH1D * TauEcosTheta;
//    TH1D * MuTaucosTheta;
//    TH1D * fullHadcosTheta;
//    TH2D * IsoCosTheta;
//
//};

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
        IsoCosTheta = new TH2D(string(name+"IsoCosTheta").c_str(),string(name+";isolation; cos(#theta)").c_str(),100, -1.,1.,15,0,0.15);
        //        cosThetaII = new TH1D(string(name+"cosTheta_MET").c_str(),string(name+": cos(#theta) (MET)").c_str(),10000,-1.,1.);
        //        cosThetaII->GetXaxis()->SetTitle("cos(#theta*)");
        cosTheta2D = new TH2D(string(name + "cosTheta2D").c_str(), string(name + ": cos(#theta); cos(#theta)_{gen}; cos(#theta)_{rec}").c_str(), 10000, -1., 1., 100, -1., 1.);
        //        cosTheta2DII = new TH2D(string(name+"cosTheta2D_MET").c_str(),string(name+": cos(#theta) (MET); cos(#theta)_{gen}; cos(#theta)_{rec}").c_str(),10000,-1.,1.,10000,-1.,1.);
        //        semiEcosTheta = new TH1D(string(name+"semiEcosTheta").c_str(),string(name+": cos(#theta)").c_str(),10000,-1.,1.);
        //        semiEcosTheta->GetXaxis()->SetTitle("cos(#theta*)");
        //        semiTaucosTheta = new TH1D(string(name+"semiTaucosTheta").c_str(),string(name+": cos(#theta)").c_str(),10000,-1.,1.);
        //        semiTaucosTheta->GetXaxis()->SetTitle("cos(#theta*)");
        //        diTaucosTheta = new TH1D(string(name+"diTaucosTheta").c_str(),string(name+": cos(#theta)").c_str(),10000,-1.,1.);
        //        diTaucosTheta->GetXaxis()->SetTitle("cos(#theta*)");
        //        diEcosTheta = new TH1D(string(name+"diEcosTheta").c_str(),string(name+": cos(#theta)").c_str(),10000,-1.,1.);
        //        diEcosTheta->GetXaxis()->SetTitle("cos(#theta*)");
        //        diMucosTheta = new TH1D(string(name+"diMucosTheta").c_str(),string(name+": cos(#theta)").c_str(),10000,-1.,1.);
        //        diMucosTheta->GetXaxis()->SetTitle("cos(#theta*)");
        //        MuEcosTheta = new TH1D(string(name+"MuEcosTheta").c_str(),string(name+": cos(#theta)").c_str(),10000,-1.,1.);
        //        MuEcosTheta->GetXaxis()->SetTitle("cos(#theta*)");
        //        TauEcosTheta = new TH1D(string(name+"TauEcosTheta").c_str(),string(name+": cos(#theta)").c_str(),10000,-1.,1.);
        //        TauEcosTheta->GetXaxis()->SetTitle("cos(#theta*)");
        //        MuTaucosTheta = new TH1D(string(name+"MuTaucosTheta").c_str(),string(name+": cos(#theta)").c_str(),10000,-1.,1.);
        //        MuTaucosTheta->GetXaxis()->SetTitle("cos(#theta*)");
        //        fullHadcosTheta = new TH1D(string(name+"fullHadcosTheta").c_str(),string(name+": cos(#theta)").c_str(),10000,-1.,1.);
        //        fullHadcosTheta->GetXaxis()->SetTitle("cos(#theta*)");

    };

    ~SingleTopHistograms() {
    };

    void Fill(SemiLepTopQuark myLeptonicTop, double lumiWeight3D = 1, double iso = 0, GenSingleTopMaker* genTop = 0) {
        Wmass->Fill(myLeptonicTop.W().M(), lumiWeight3D);
        topMass->Fill(myLeptonicTop.top().M(), lumiWeight3D);
        WmassII->Fill(myLeptonicTop.W(2).M(), lumiWeight3D);
        topMassII->Fill(myLeptonicTop.top(2).M(), lumiWeight3D);
        if (genTop != 0)
            cout << genTop->isSemiMuSingleTop << endl;
        if (genTop == 0) {
            //            cout<<"I am data like!!!"<<endl;
            cosTheta->Fill(myLeptonicTop.cosThetaStar(), lumiWeight3D);
            //            cosThetaII->Fill(myLeptonicTop.cosThetaStar(2),lumiWeight3D);
            IsoCosTheta->Fill(myLeptonicTop.cosThetaStar(),iso,lumiWeight3D);
        } else if (!genTop->isSemiMuSingleTop) {//cout<<"//Other top decays"<<endl;
            cosTheta->Fill(myLeptonicTop.cosThetaStar(), lumiWeight3D);
            //            cosThetaII->Fill(myLeptonicTop.cosThetaStar(2),lumiWeight3D);
            IsoCosTheta->Fill(myLeptonicTop.cosThetaStar(),iso,lumiWeight3D);
        } else if (genTop->genSingleTop.MuCharge() != myLeptonicTop.MuCharge()) {//cout<<"// fake muons"<<endl;
            cosTheta->Fill(myLeptonicTop.cosThetaStar(), lumiWeight3D);
            //            cosThetaII->Fill(myLeptonicTop.cosThetaStar(2),lumiWeight3D);
            IsoCosTheta->Fill(myLeptonicTop.cosThetaStar(),iso,lumiWeight3D);
        } else {
            //cout<<"// OK"<<endl;
            cosTheta2D->Fill(genTop->genSingleTop.cosThetaStar(0), myLeptonicTop.cosThetaStar(), lumiWeight3D);
            //            cosTheta2DII->Fill(genTop->genSingleTop.cosThetaStar(0),myLeptonicTop.cosThetaStar(2), lumiWeight3D);
        }
        //        if(genTop != 0){
        //            if(genTop->isDiETt)
        //                diEcosTheta->Fill(myLeptonicTop.cosThetaStar(),lumiWeight3D);
        //            else if(genTop->isDiMuTt)
        //                diMucosTheta->Fill(myLeptonicTop.cosThetaStar(),lumiWeight3D);
        //            else if(genTop->isDiTauTt)
        //                diTaucosTheta->Fill(myLeptonicTop.cosThetaStar(),lumiWeight3D);
        //            else if(genTop->isSemiTauTt)
        //                semiTaucosTheta->Fill(myLeptonicTop.cosThetaStar(),lumiWeight3D);
        //            else if(genTop->isSemiElecTt)
        //                semiEcosTheta->Fill(myLeptonicTop.cosThetaStar(),lumiWeight3D);
        //            else if(genTop->isMuETt)
        //                MuEcosTheta->Fill(myLeptonicTop.cosThetaStar(),lumiWeight3D);
        //            else if(genTop->isMuTauTt)
        //                MuTaucosTheta->Fill(myLeptonicTop.cosThetaStar(),lumiWeight3D);
        //            else if(genTop->isETauTt)
        //                TauEcosTheta->Fill(myLeptonicTop.cosThetaStar(),lumiWeight3D);
        //            else if(genTop->isFullHadTt)
        //                fullHadcosTheta->Fill(myLeptonicTop.cosThetaStar(),lumiWeight3D);
        //        }
    }

    void Write(TDirectory * dir) {
        TDirectory * inDir = dir->mkdir(Name.c_str());
        inDir->cd();
        cosTheta->Write();
        Wmass->Write();
        topMass->Write();
        //        cosThetaII->Write();
        WmassII->Write();
        topMassII->Write();
        cosTheta2D->Write();
        IsoCosTheta->Write();
        //        cosTheta2DII->Write();
        //        (inDir->mkdir("ttDecayModes"))->cd();
        //        semiEcosTheta->Write();
        //        semiTaucosTheta->Write();
        //        diTaucosTheta->Write();
        //        diEcosTheta->Write();
        //        diMucosTheta->Write();
        //        MuEcosTheta->Write();
        //        TauEcosTheta->Write();
        //        MuTaucosTheta->Write();
        //        fullHadcosTheta->Write();
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
    TH2D * IsoCosTheta;

};

int main(int argc, char** argv) {

    PVHists atLeastOnGPV("final_PV");
    JetHists Jets("final_Jet", 2);
    JetHists BJets("final_BJet", 2);
    JetHists nonBJets("final_nonBJet", 2);
    JetHists Light("final_Light", 2);
    MuonHists GoldenFinalMuons("final_Muon");
    MetHists MetHist("finalMet");

    SingleTopHistograms RandomB("RandomB");
    SingleTopHistograms PtOrderedB("PtOrderedB");
    SingleTopHistograms BtagOrderedB("BtagOrderedB");
    SingleTopHistograms RandomBTrue("RandomBTrue");
    SingleTopHistograms PtOrderedBTrue("PtOrderedBTrue");
    SingleTopHistograms BtagOrderedBTrue("BtagOrderedBTrue");
    SingleTopHistograms EtaCutRandomB("EtaCutRandomB");
    SingleTopHistograms EtaCutPtOrderedB("EtaCutPtOrderedB");
    SingleTopHistograms EtaCutBtagOrderedB("EtaCutBtagOrderedB");
    SingleTopHistograms EtaCutRandomBTrue("EtaCutRandomBTrue");
    SingleTopHistograms EtaCutPtOrderedBTrue("EtaCutPtOrderedBTrue");
    SingleTopHistograms EtaCutBtagOrderedBTrue("EtaCutBtagOrderedBTrue");


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

    TFile* f = 0;
    TApplication theApp("App", &argc, argv);
    double nInit = 0;
    double nFinal = 0;
    double nHLTrunB = 0;
    double nMt = 0;
    TRandom SeedGenerator(1726367);

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
                cout << "*******************************************************************" << endl;

            std::vector<TRootPFJet> myJets_;
            myJets_.clear();
            //            cout<<"I am going to Jet Correction "<<isData<<endl;
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
    fout->cd();
    finalMT->Write();
    HT->Write();
    fout->Write();
    fout->Close();

    cout << nInit << "\n" << nHLTrunB << "\n" << nMt << "\n" << nFinal << endl;
    return 0;
}

