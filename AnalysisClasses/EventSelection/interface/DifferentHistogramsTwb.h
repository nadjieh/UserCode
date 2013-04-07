/* 
 * File:   DifferentHistogramsTwb.h
 * Author: nadjieh
 *
 * Created on October 21, 2012, 12:26 PM
 */

#ifndef DIFFERENTHISTOGRAMSTWB_H
#define	DIFFERENTHISTOGRAMSTWB_H
//#define DecayChanTest

#include "../../PhysicsObjects/interface/SemiLepTopQuark.h"


#include "../../ToyAnalysis/interface/GenSingleTopMaker.h"




#include <sstream>
#include <string>

#include <TApplication.h>
#include <TDirectory.h>
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

class SingleTopHistograms {
public:

    SingleTopHistograms(string name, bool sumw2 = false) : Name(name), setSumW2(sumw2) {
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
        cosTheta2D = new TH2D(string(name + "cosTheta2D").c_str(),
                string(name + ": cos(#theta); cos(#theta)_{gen}; cos(#theta)_{rec}").c_str(),
                10000, -1., 1., 100, -1., 1.);
        if (setSumW2) {
            Wmass->Sumw2();
            topMass->Sumw2();
            cosTheta->Sumw2();
            cosTheta2D->Sumw2();
        }
        //        cosTheta3D = new TH3D(string(name + "cosTheta3D").c_str(),
        //                string(name + ": cos(#theta); cos(#theta)_{gen-lep}; cos(#theta)_{rec};cos(#theta)_{gen-d};").c_str(),
        //                100, -1., 1., 100, -1., 1., 100, -1., 1.);
        cosTheta3D = new TH3D(string(name + "cosTheta3D").c_str(),
                string(name + ": cos(#theta); cos(#theta)_{gen-lep}; cos(#theta)_{rec};cos(#theta)_{gen-d};").c_str(),
                10, -1., 1., 100, -1., 1., 1000, -1., 1.);
        top_W_channel1 = new TH2D("top_W_channel1", "top_W_channel", 4, 0, 4, 4, 0, 4);
        top_W_channel1->GetXaxis()->SetBinLabel(1, "top-Mu");
        top_W_channel1->GetXaxis()->SetBinLabel(2, "top-E");
        top_W_channel1->GetXaxis()->SetBinLabel(3, "top-Tau");
        top_W_channel1->GetXaxis()->SetBinLabel(4, "top-Had");
        top_W_channel1->GetYaxis()->SetBinLabel(1, "W-Mu");
        top_W_channel1->GetYaxis()->SetBinLabel(2, "W-E");
        top_W_channel1->GetYaxis()->SetBinLabel(3, "W-Tau");
        top_W_channel1->GetYaxis()->SetBinLabel(4, "W-Had");
        top_W_channel2 = (TH2D*) top_W_channel1->Clone("top_W_channel2");
        top_W_channel2->SetTitle("top_W_channel2");
        top_W_channel3 = (TH2D*) top_W_channel1->Clone("top_W_channel3");
        top_W_channel3->SetTitle("top_W_channel3");

    };

    virtual ~SingleTopHistograms() {
    };

    virtual void Fill(SemiLepTopQuark myLeptonicTop, double lumiWeight3D = 1, GenSingleTopMaker* genTop = 0) {
        //        cout<<"In Fill Method: "<<genTop->ntops<<endl;
        Wmass->Fill(myLeptonicTop.W().M(), lumiWeight3D);
        topMass->Fill(myLeptonicTop.top().M(), lumiWeight3D);
        WmassII->Fill(myLeptonicTop.W(2).M(), lumiWeight3D);
        topMassII->Fill(myLeptonicTop.top(2).M(), lumiWeight3D);
        if (genTop == 0) {
            cosTheta->Fill(myLeptonicTop.cosThetaStar(), lumiWeight3D);
        } else {
            /*
             * Assuming that tW is differentiated based on the final state:
             * 1- W to muon + top to hadrons || W to muon + top to tau || W to muon + top to electron
             * 2- the rest (!1)
             */
            if (genTop->ntops == 1 && genTop->nonTopWs.size() != 0) {
                //                cout << "first step: "<<genTop->ntops <<"\t"<<genTop->nonTopWs.size() << endl;
                if (genTop->nonTopWs[0] == 2) {
                    if (genTop->isHadSingleTop || genTop->isSemiElecTt || genTop->isSemiTauTt) {
                        //                    cout << "third step: " << genTop->genSingleTop.MuCharge() << "\t" << myLeptonicTop.MuCharge() << endl;
                        if (genTop->genSingleTop.MuCharge() != myLeptonicTop.MuCharge()) {
                            cosTheta2D->Fill(genTop->genSingleTop.cosThetaStar(0),
                                    myLeptonicTop.cosThetaStar(), lumiWeight3D);
                            return;
                        }
                    }
                } /*else {
                    cout << "bad top" << endl;
                }*/
            } /*else {
                cout << "sth wrong!" << endl;
            }*/
            if (!genTop->isSemiMuSingleTop) {
                cosTheta->Fill(myLeptonicTop.cosThetaStar(), lumiWeight3D);
#ifdef DecayChanTest
                cout << "1- " << genTop->isSemiMuSingleTop << endl;

                if (genTop->nonTopWs.size() != 0) {
                    if (genTop->isSemiElecTt && genTop->nonTopWs[0] == 1) {
                        top_W_channel1->Fill(1., 1.);
                    }
                    if (genTop->isSemiTauTt && genTop->nonTopWs[0] == 3) {
                        top_W_channel1->Fill(2., 2.);
                    }
                    if (genTop->isSemiElecTt && genTop->nonTopWs[0] == 3) {
                        top_W_channel1->Fill(1., 2.);
                    }
                    if (genTop->isSemiTauTt && genTop->nonTopWs[0] == 1) {
                        top_W_channel1->Fill(2., 1.);
                    }
                    if (genTop->isSemiTauTt && genTop->nonTopWs[0] == 2) {
                        top_W_channel1->Fill(2., 0.);
                    }
                    if (genTop->isSemiElecTt && genTop->nonTopWs[0] == 2) {
                        top_W_channel1->Fill(1., 0.);
                    }
                    if (genTop->isSemiElecTt && genTop->nonTopWs[0] == 4) {
                        top_W_channel1->Fill(1., 3.);
                    }
                    if (genTop->isHadSingleTop && genTop->nonTopWs[0] == 1) {
                        top_W_channel1->Fill(3., 1.);
                    }
                    if (genTop->isHadSingleTop && genTop->nonTopWs[0] == 2) {
                        top_W_channel1->Fill(3., 0.);
                    }
                    if (genTop->isSemiTauTt && genTop->nonTopWs[0] == 4) {
                        top_W_channel1->Fill(2., 3.);
                    }
                    if (genTop->isHadSingleTop && genTop->nonTopWs[0] == 3) {
                        top_W_channel1->Fill(3., 2.);
                    }
                    if (genTop->isHadSingleTop && genTop->nonTopWs[0] == 4) {
                        top_W_channel1->Fill(3., 3.);
                    }
                }
#endif /*DecayChanTest*/
            } else if (genTop->genSingleTop.MuCharge() != myLeptonicTop.MuCharge()) {
                cosTheta->Fill(myLeptonicTop.cosThetaStar(), lumiWeight3D);
#ifdef DecayChanTest
                cout << "2- " << genTop->isSemiMuSingleTop << endl;
                if (genTop->nonTopWs.size() != 0) {
                    if (genTop->isSemiMuSingleTop && genTop->nonTopWs[0] == 2) {
                        top_W_channel2->Fill(0., 0.);
                    }
                    if (genTop->isSemiMuSingleTop && genTop->nonTopWs[0] == 3) {
                        top_W_channel2->Fill(0., 2.);
                    }
                    if (genTop->isSemiMuSingleTop && genTop->nonTopWs[0] == 1) {
                        top_W_channel2->Fill(0., 1.);
                    }
                    if (genTop->isSemiMuSingleTop && genTop->nonTopWs[0] == 4) {
                        top_W_channel2->Fill(0., 3.);
                    }
                }
#endif /*DecayChanTest*/
            } else {
                cosTheta2D->Fill(genTop->genSingleTop.cosThetaStar(0), myLeptonicTop.cosThetaStar(), lumiWeight3D);
#ifdef DecayChanTest
                cout << "3- " << genTop->isSemiMuSingleTop << endl;
                if (genTop->nonTopWs.size() != 0) {
                    if (genTop->isSemiMuSingleTop && genTop->nonTopWs[0] == 2) {
                        top_W_channel3->Fill(0., 0.);
                    }
                    if (genTop->isSemiMuSingleTop && genTop->nonTopWs[0] == 3) {
                        top_W_channel3->Fill(0., 2.);
                    }
                    if (genTop->isSemiMuSingleTop && genTop->nonTopWs[0] == 1) {
                        top_W_channel3->Fill(0., 1.);
                    }
                    if (genTop->isSemiMuSingleTop && genTop->nonTopWs[0] == 4) {
                        top_W_channel3->Fill(0., 3.);
                    }
                }
#endif /*DecayChanTest*/
                if (genTop->ntops == 2) {
                    cosTheta3D->Fill(genTop->genSingleTop.cosThetaStar(0), myLeptonicTop.cosThetaStar(),
                            genTop->genSingleTopSecond.cosThetaStar(0), lumiWeight3D);
                }
            }
        }
    }

    virtual void Write(TDirectory * dir) {
        TDirectory * inDir = dir->mkdir(Name.c_str());
        inDir->cd();
        cosTheta->Write();
        Wmass->Write();
        topMass->Write();
        WmassII->Write();
        topMassII->Write();
        cosTheta2D->Write();
        cosTheta3D->Write();
#ifdef DecayChanTest
        top_W_channel1->Write();
        top_W_channel2->Write();
        top_W_channel3->Write();
#endif /*DecayChanTest*/
        inDir->cd();
        dir->cd();
    }
    string Name;
    bool setSumW2;
    TH1D * Wmass;
    TH1D * WmassII;
    TH1D * topMass;
    TH1D * topMassII;
    TH1D * cosTheta;
    TH1D * cosThetaII;
    TH2D * cosTheta2D;
    TH3D * cosTheta3D;
    TH2D * cosTheta2DII;
    TH2D * top_W_channel1;
    TH2D * top_W_channel2;
    TH2D * top_W_channel3;


};

class DiLeptonHistograms : public SingleTopHistograms {
public:

    DiLeptonHistograms(string name, bool sumw2 = false) : SingleTopHistograms(name, sumw2) {
    }

    virtual ~DiLeptonHistograms() {
    }

    virtual void Write(TDirectory * d) {
        SingleTopHistograms::Write(d);
    }

    virtual void Fill(SemiLepTopQuark myLeptonicTop, double lumiWeight3D = 1, GenSingleTopMaker* genTop = 0) {
        SingleTopHistograms::Wmass->Fill(myLeptonicTop.W().M(), lumiWeight3D);
        SingleTopHistograms::topMass->Fill(myLeptonicTop.top().M(), lumiWeight3D);
        SingleTopHistograms::WmassII->Fill(myLeptonicTop.W(2).M(), lumiWeight3D);
        SingleTopHistograms::topMassII->Fill(myLeptonicTop.top(2).M(), lumiWeight3D);
        //        if (genTop != 0)
        //            cout << genTop->isSemiMuSingleTop << endl;
        if (genTop->isMuTauTt || genTop->isMuETt) {//cout<<"//Other top decays"<<endl;
            if (genTop->genSingleTop.MuCharge() != myLeptonicTop.MuCharge())
                SingleTopHistograms::cosTheta->Fill(myLeptonicTop.cosThetaStar(), lumiWeight3D);
            else {
                SingleTopHistograms::cosTheta2D->Fill(genTop->genSingleTop.cosThetaStar(0),
                        myLeptonicTop.cosThetaStar(), lumiWeight3D);
                SingleTopHistograms::cosTheta3D->Fill(genTop->genSingleTop.cosThetaStar(0),
                        myLeptonicTop.cosThetaStar(), genTop->genSingleTopSecond.cosThetaStar(0), lumiWeight3D);
            }
            //            cosThetaII->Fill(myLeptonicTop.cosThetaStar(2),lumiWeight3D);
        } else if (genTop->isDiMuTt) {
            if (genTop->genSingleTop.MuCharge() == myLeptonicTop.MuCharge()) {
                SingleTopHistograms::cosTheta2D->Fill(genTop->genSingleTop.cosThetaStar(0), myLeptonicTop.cosThetaStar(), lumiWeight3D);
                SingleTopHistograms::cosTheta3D->Fill(genTop->genSingleTop.cosThetaStar(0), myLeptonicTop.cosThetaStar(),
                        genTop->genSingleTopSecond.cosThetaStar(0), lumiWeight3D);
            } else if (genTop->genSingleTopSecond.MuCharge() == myLeptonicTop.MuCharge()) {
                SingleTopHistograms::cosTheta2D->Fill(genTop->genSingleTopSecond.cosThetaStar(0), myLeptonicTop.cosThetaStar(), lumiWeight3D);
                SingleTopHistograms::cosTheta3D->Fill(genTop->genSingleTopSecond.cosThetaStar(0), myLeptonicTop.cosThetaStar(),
                        genTop->genSingleTop.cosThetaStar(0), lumiWeight3D);
            } else {
                cout << "What a hell is that?!!" << endl;
                return;
            }

        } else SingleTopHistograms::Fill(myLeptonicTop, lumiWeight3D, genTop);
    }
};

class WtemplateHistograms {
public:

    WtemplateHistograms(string name) : Name(name) {
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
        IsoCosTheta = new TH2D(string(name + "IsoCosTheta").c_str(), string(name + ";isolation; cos(#theta)").c_str(), 100, -1., 1., 15, 0, 0.15);
        //        cosThetaII = new TH1D(string(name+"cosTheta_MET").c_str(),string(name+": cos(#theta) (MET)").c_str(),10000,-1.,1.);
        //        cosThetaII->GetXaxis()->SetTitle("cos(#theta*)");
        cosTheta2D = new TH2D(string(name + "cosTheta2D").c_str(), string(name + ": cos(#theta); cos(#theta)_{gen}; cos(#theta)_{rec}").c_str(), 10000, -1., 1., 100, -1., 1.);

    };

    ~WtemplateHistograms() {
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
            IsoCosTheta->Fill(myLeptonicTop.cosThetaStar(), iso, lumiWeight3D);
        } else if (!genTop->isSemiMuSingleTop) {//cout<<"//Other top decays"<<endl;
            cosTheta->Fill(myLeptonicTop.cosThetaStar(), lumiWeight3D);
            //            cosThetaII->Fill(myLeptonicTop.cosThetaStar(2),lumiWeight3D);
            IsoCosTheta->Fill(myLeptonicTop.cosThetaStar(), iso, lumiWeight3D);
        } else if (genTop->genSingleTop.MuCharge() != myLeptonicTop.MuCharge()) {//cout<<"// fake muons"<<endl;
            cosTheta->Fill(myLeptonicTop.cosThetaStar(), lumiWeight3D);
            //            cosThetaII->Fill(myLeptonicTop.cosThetaStar(2),lumiWeight3D);
            IsoCosTheta->Fill(myLeptonicTop.cosThetaStar(), iso, lumiWeight3D);
        } else {
            //cout<<"// OK"<<endl;
            cosTheta2D->Fill(genTop->genSingleTop.cosThetaStar(0), myLeptonicTop.cosThetaStar(), lumiWeight3D);
            //            cosTheta2DII->Fill(genTop->genSingleTop.cosThetaStar(0),myLeptonicTop.cosThetaStar(2), lumiWeight3D);
        }
    }

    void Write(TDirectory * dir) {
        TDirectory * inDir = dir->mkdir(Name.c_str());
        inDir->cd();
        cosTheta->Write();
        Wmass->Write();
        topMass->Write();
        WmassII->Write();
        topMassII->Write();
        cosTheta2D->Write();
        IsoCosTheta->Write();
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


#endif	/* DIFFERENTHISTOGRAMSTWB_H */

