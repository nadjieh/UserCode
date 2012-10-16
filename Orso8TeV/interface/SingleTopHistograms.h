/*
 * File:SingleTopHistograms.h
 * Author: nadjieh
 * Created on October 11, 2012, 12:15 PM
 */
#ifndef _SINGLETOPHISTOGRAMS_H
#define _SINGLETOPHISTOGRAMS_H

#include "TH1.h"
#include "TH2.h"
#include "TDirectory.h"
#include <string>
#include "../../AnalysisClasses/ToyAnalysis/interface/GenSingleTopMaker.h"
#include "../../AnalysisClasses/PhysicsObjects/interface/SemiLepTopQuark.h"
using namespace std;

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
#endif
