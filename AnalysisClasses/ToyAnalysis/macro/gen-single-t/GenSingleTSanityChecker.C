/*
 * For the moment I use the event selection chain in explicitly
 * It comes from AnalysisClasses/EventSelection/macro/t-SingleTopSelection/SelectAndSave.C
 */
/* 
 * File:   SelectAndSave.c
 * Author: ajafari
 *
 * Created on January 29, 2012, 8:18 PM
 */



#include "../../../../TopBrussels/TopTreeProducer/interface/TRootGenEvent.h"

#include "../../../EventSelection/interface/PracticalEvent.h"
#include "../../../PhysicsObjects/interface/SemiLepTopQuark.h"
#include "../../interface/GenSingleTopMaker.h"
#include "../../interface/CosThetaWeighter.h"
#include "../../interface/CosThetaWeightHandler.h"
#include "../../interface/DataPointsChiSquared.h"





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

int main(int argc, char** argv) {
    std::vector<string> inFiles;
    string outFile;
    int nSteps;
    double f0;
    double fminus;
    bool f0Fixed = false;
    bool fminusFixed = true;
    for (int f = 1; f < argc; f++) {
        std::string arg_fth(*(argv + f));

        if (arg_fth == "out") {
            f++;
            std::string out(*(argv + f));
            outFile = string(out);
        } else if (arg_fth == "input") {
            f++;
            std::string in(*(argv + f));
            inFiles.push_back(string("~/work/samples/" + in));
        } else if (arg_fth == "nSteps") {
            f++;
            std::string in(*(argv + f));
            nSteps = (int) atof(in.c_str());
        } else if (arg_fth == "f0") {
            f++;
            std::string in(*(argv + f));
            f0 = atof(in.c_str());
        } else if (arg_fth == "fminus") {
            f++;
            std::string in(*(argv + f));
            fminus = atof(in.c_str());
        } else if (arg_fth == "isFixed") {
            f++;
            std::string in(*(argv + f));
            if (in == string("f0")) {
                f0Fixed = true;
                fminusFixed = false;
            } else if (in == string("fminus")) {
                f0Fixed = false;
                fminusFixed = true;
            }
        }
    }


    TApplication theApp("App", &argc, argv);


    TH1D * cosThetaGen = new TH1D("cosThetaGen", "cos(#theta)_{gen}", 1000, -1, 1);
    TH1D * cosThetaGenII = new TH1D("cosThetaGenII", "cos(#theta)_{gen}", 1000, -1, 1);
    TH1D * topMass = new TH1D("topMass", "m_{top}", 150, 0, 300);
    TH1D * topMassII = new TH1D("topMassII", "m_{top}", 150, 0, 300);
    TH1D * Wmass = new TH1D("Wmass", "m_{W}", 75, 0, 150);
    TH1D * WmassII = new TH1D("WmassII", "m_{W}", 75, 0, 150);
    TH1D * eventType = new TH1D("eventType", "eventType", 3, 0, 3);
    eventType->GetXaxis()->SetBinLabel(1, "ttbar");
    eventType->GetXaxis()->SetBinLabel(2, "tW");
    eventType->GetXaxis()->SetBinLabel(3, "sORt");
    TH1D * channel = new TH1D("channel", "channel", 10, 0, 10);
    channel->GetXaxis()->SetBinLabel(1, "diMu");
    channel->GetXaxis()->SetBinLabel(2, "diE");
    channel->GetXaxis()->SetBinLabel(3, "diTau");
    channel->GetXaxis()->SetBinLabel(4, "ETau");
    channel->GetXaxis()->SetBinLabel(5, "MuTau");
    channel->GetXaxis()->SetBinLabel(6, "MuE");
    channel->GetXaxis()->SetBinLabel(7, "SemiE");
    channel->GetXaxis()->SetBinLabel(8, "SemiMu");
    channel->GetXaxis()->SetBinLabel(9, "SemiTau");
    channel->GetXaxis()->SetBinLabel(10, "FullHad");
    TH1D * top1_channel = new TH1D("top1_channel", "top1_channel", 4, 0, 4);
    top1_channel->GetXaxis()->SetBinLabel(1, "Mu");
    top1_channel->GetXaxis()->SetBinLabel(2, "E");
    top1_channel->GetXaxis()->SetBinLabel(3, "Tau");
    top1_channel->GetXaxis()->SetBinLabel(4, "Had");
    TH1D * top2_channel = (TH1D*) top1_channel->Clone("top2_channel");
    top2_channel->SetTitle("top2_channel");
    TH1D * nonTopWChannel = (TH1D*) top1_channel->Clone("nonTopWChannel");
    nonTopWChannel->SetTitle("nonTopWChannel");
    TH2D * top_W_channel = new TH2D("top_W_channel", "top_W_channel", 4, 0, 4, 4, 0, 4);
    top_W_channel->GetXaxis()->SetBinLabel(1, "top-Mu");
    top_W_channel->GetXaxis()->SetBinLabel(2, "top-E");
    top_W_channel->GetXaxis()->SetBinLabel(3, "top-Tau");
    top_W_channel->GetXaxis()->SetBinLabel(4, "top-Had");
    top_W_channel->GetYaxis()->SetBinLabel(1, "W-Mu");
    top_W_channel->GetYaxis()->SetBinLabel(2, "W-E");
    top_W_channel->GetYaxis()->SetBinLabel(3, "W-Tau");
    top_W_channel->GetYaxis()->SetBinLabel(4, "W-Had");
    TH2D * top_top_channel = new TH2D("top_top_channel", "top_top_channel", 4, 0, 4, 4, 0, 4);
    top_top_channel->GetXaxis()->SetBinLabel(1, "top-Mu");
    top_top_channel->GetXaxis()->SetBinLabel(2, "top-E");
    top_top_channel->GetXaxis()->SetBinLabel(3, "top-Tau");
    top_top_channel->GetXaxis()->SetBinLabel(4, "top-Had");
    top_top_channel->GetYaxis()->SetBinLabel(1, "top-Mu");
    top_top_channel->GetYaxis()->SetBinLabel(2, "top-E");
    top_top_channel->GetYaxis()->SetBinLabel(3, "top-Tau");
    top_top_channel->GetYaxis()->SetBinLabel(4, "top-Had");

    //    CosThetaWeighter myWeighter(6.64263e-01,3.03734e-01,0.1);
    TFile * f = 0;
    for (unsigned int fNumber = 0; fNumber < inFiles.size(); fNumber++) {
        cout << "RunNumber|\tEventNumber|\tLumiBlock|\tptLepton|\trelIso|\tptjet1|\tptjet2|\tMET|\tMT|\tbtagjet1|\tbtagjet2" << endl;
        f = TFile::Open(inFiles.at(fNumber).c_str());
        //        cout<<"nFiles: "<<toy_inputFileNames.size()<<endl;

        TTree* runTree = (TTree*) f->Get("runTree");
        TTree* eventTree = (TTree*) f->Get("eventTree");

        PracticalEvent * pracEvt = new PracticalEvent(eventTree, runTree);
        pracEvt->eventTree->SetBranchStatus("*", 1);

        int ievt = 0;

        while (pracEvt->Next()) {
            ievt++;
            //            if(ievt > 10)
            //                break;
            cout << "Event Number " << ievt << "--------------------" << endl;
            GenSingleTopMaker myGenStMaker((TRootNPGenEvent*) pracEvt->NPGenEvtCollection()->At(0));

            if (myGenStMaker.nonTopWs.size() == 1) {
                eventType->Fill(1);
                if (myGenStMaker.isSemiMuSingleTop && myGenStMaker.nonTopWs[0] == 2) {
                    channel->Fill(0);
                    top_W_channel->Fill(0., 0.);
                }
                if (myGenStMaker.isSemiElecTt && myGenStMaker.nonTopWs[0] == 1) {
                    channel->Fill(1);
                    top_W_channel->Fill(1., 1.);
                }
                if (myGenStMaker.isSemiTauTt && myGenStMaker.nonTopWs[0] == 3) {
                    channel->Fill(2);
                    top_W_channel->Fill(2., 2.);
                }
                if (myGenStMaker.isSemiElecTt && myGenStMaker.nonTopWs[0] == 3) {
                    channel->Fill(3);
                    top_W_channel->Fill(1., 2.);
                }
                if (myGenStMaker.isSemiTauTt && myGenStMaker.nonTopWs[0] == 1) {
                    channel->Fill(3);
                    top_W_channel->Fill(2., 1.);
                }
                if (myGenStMaker.isSemiMuSingleTop && myGenStMaker.nonTopWs[0] == 3) {
                    channel->Fill(4);
                    top_W_channel->Fill(0., 2.);
                }
                if (myGenStMaker.isSemiTauTt && myGenStMaker.nonTopWs[0] == 2) {
                    channel->Fill(4);
                    top_W_channel->Fill(2., 0.);
                }
                if (myGenStMaker.isSemiMuSingleTop && myGenStMaker.nonTopWs[0] == 1) {
                    channel->Fill(5);
                    top_W_channel->Fill(0., 1.);
                }
                if (myGenStMaker.isSemiElecTt && myGenStMaker.nonTopWs[0] == 2) {
                    channel->Fill(5);
                    top_W_channel->Fill(1., 0.);
                }
                if (myGenStMaker.isSemiElecTt && myGenStMaker.nonTopWs[0] == 4) {
                    channel->Fill(6);
                    top_W_channel->Fill(1., 3.);
                }
                if (myGenStMaker.isHadSingleTop && myGenStMaker.nonTopWs[0] == 1) {
                    channel->Fill(6);
                    top_W_channel->Fill(3., 1.);
                }
                if (myGenStMaker.isSemiMuSingleTop && myGenStMaker.nonTopWs[0] == 4) {
                    channel->Fill(7);
                    top_W_channel->Fill(0., 3.);
                }
                if (myGenStMaker.isHadSingleTop && myGenStMaker.nonTopWs[0] == 2) {
                    channel->Fill(7);
                    top_W_channel->Fill(3., 0.);
                }
                if (myGenStMaker.isSemiTauTt && myGenStMaker.nonTopWs[0] == 4) {
                    channel->Fill(8);
                    top_W_channel->Fill(2., 3.);
                }
                if (myGenStMaker.isHadSingleTop && myGenStMaker.nonTopWs[0] == 3) {
                    channel->Fill(8);
                    top_W_channel->Fill(3., 2.);
                }
                if (myGenStMaker.isHadSingleTop && myGenStMaker.nonTopWs[0] == 4) {
                    channel->Fill(9);
                    top_W_channel->Fill(3., 3.);
                }

                if (myGenStMaker.isSemiElecTt) top1_channel->Fill(1);
                if (myGenStMaker.isSemiMuSingleTop) top1_channel->Fill(0);
                if (myGenStMaker.isSemiTauTt) top1_channel->Fill(2);
                if (myGenStMaker.isHadSingleTop) top1_channel->Fill(3);

                if (myGenStMaker.nonTopWs[0] == 1) nonTopWChannel->Fill(1);
                if (myGenStMaker.nonTopWs[0] == 2) nonTopWChannel->Fill(0);
                if (myGenStMaker.nonTopWs[0] == 3) nonTopWChannel->Fill(2);
                if (myGenStMaker.nonTopWs[0] == 4) nonTopWChannel->Fill(3);

                if (myGenStMaker.isHadSingleTop && myGenStMaker.nonTopWs[0] == 2) {
                    cosThetaGen->Fill(myGenStMaker.genSingleTop.cosThetaStar(0), 1);
                    TLorentzVector q = myGenStMaker.genSingleTop.top(0);
                    topMass->Fill(q.M(), 1);
                    if (q.M() < 150)
                        cout << "WHATTTTT?" << endl;
                    Wmass->Fill(myGenStMaker.genSingleTop.W(0).M(), 1);
                } else if (myGenStMaker.isSemiMuSingleTop && myGenStMaker.nonTopWs[0] == 4) {
                    cosThetaGenII->Fill(myGenStMaker.genSingleTop.cosThetaStar(0), 1);
                    topMassII->Fill(myGenStMaker.genSingleTop.top(0).M(), 1);
                    WmassII->Fill(myGenStMaker.genSingleTop.W(0).M(), 1);
                    //                myGenStMaker.genSingleTop.printContent();
                }
            } else if (myGenStMaker.nonTopWs.size() == 0 && myGenStMaker.ntops == 2) {
                eventType->Fill(0);
                if (myGenStMaker.isDiMuTt) {
                    channel->Fill(0);
                }
                if (myGenStMaker.isDiETt) {
                    channel->Fill(1);
                }
                if (myGenStMaker.isDiTauTt) {
                    channel->Fill(2);
                }
                if (myGenStMaker.isETauTt) {
                    channel->Fill(3);
                }
                if (myGenStMaker.isMuTauTt) {
                    channel->Fill(4);
                }
                if (myGenStMaker.isMuETt) {
                    channel->Fill(5);
                }
                if (myGenStMaker.isSemiElecTt) {
                    channel->Fill(6);
                }
                if (myGenStMaker.isSemiMuSingleTop) {
                    channel->Fill(7);
                }
                if (myGenStMaker.isSemiTauTt) {
                    channel->Fill(8);
                }
                if (myGenStMaker.isFullHadTt) {
                    channel->Fill(9);
                }

                if (myGenStMaker.isSemiElecTt) {
                    top1_channel->Fill(1);
                    top2_channel->Fill(3);
                    top_top_channel->Fill(1., 3.);
                }
                if (myGenStMaker.isSemiMuSingleTop) {
                    top1_channel->Fill(0);
                    top2_channel->Fill(3);
                    top_top_channel->Fill(0., 3.);
                }
                if (myGenStMaker.isSemiTauTt) {
                    top1_channel->Fill(2);
                    top2_channel->Fill(3);
                    top_top_channel->Fill(2., 3.);
                }
                if (myGenStMaker.isDiMuTt) {
                    top1_channel->Fill(0);
                    top2_channel->Fill(0);
                    top_top_channel->Fill(0., 0.);
                }
                if (myGenStMaker.isDiETt) {
                    top1_channel->Fill(1);
                    top2_channel->Fill(1);
                    top_top_channel->Fill(1., 1.);
                }
                if (myGenStMaker.isDiTauTt) {
                    top1_channel->Fill(2);
                    top2_channel->Fill(2);
                    top_top_channel->Fill(2., 2.);
                }
                if (myGenStMaker.isMuETt) {
                    top1_channel->Fill(0);
                    top2_channel->Fill(1);
                    top_top_channel->Fill(0., 1.);
                }
                if (myGenStMaker.isMuTauTt) {
                    top1_channel->Fill(0);
                    top2_channel->Fill(2);
                    top_top_channel->Fill(0., 2.);
                }
                if (myGenStMaker.isETauTt) {
                    top1_channel->Fill(1);
                    top2_channel->Fill(2);
                    top_top_channel->Fill(1., 2.);
                }
                if (myGenStMaker.isFullHadTt) {
                    top1_channel->Fill(3);
                    top2_channel->Fill(3);
                    top_top_channel->Fill(3., 3.);
                }


                if (myGenStMaker.isSemiMuSingleTop) {
                    cosThetaGen->Fill(myGenStMaker.genSingleTop.cosThetaStar(0), 1);
                    TLorentzVector q = myGenStMaker.genSingleTop.top(0);
                    topMass->Fill(q.M(), 1);
                    if (q.M() < 150)
                        cout << "WHATTTTT?" << endl;
                    Wmass->Fill(myGenStMaker.genSingleTop.W(0).M(), 1);
                    cosThetaGenII->Fill(myGenStMaker.genSingleTopSecond.cosThetaStar(0), 1);
                    topMassII->Fill(myGenStMaker.genSingleTopSecond.top(0).M(), 1);
                    WmassII->Fill(myGenStMaker.genSingleTopSecond.W(0).M(), 1);
                    //                myGenStMaker.genSingleTop.printContent();
                }


            } else if (myGenStMaker.isSemiMuSingleTop) {
                cosThetaGen->Fill(myGenStMaker.genSingleTop.cosThetaStar(0), 1);
                TLorentzVector q = myGenStMaker.genSingleTop.top(0);
                topMass->Fill(q.M(), 1);
                if (q.M() < 150)
                    cout << "WHATTTTT?" << endl;
                Wmass->Fill(myGenStMaker.genSingleTop.W(0).M(), 1);
            }
        }
        f->Close();
        delete f;
    }
    TFile * myFile = new TFile(string("cosTheta_" + outFile).c_str(), "recreate");
    myFile->cd();
    cosThetaGen->Write();
    Wmass->Write();
    topMass->Write();
    cosThetaGenII->Write();
    WmassII->Write();
    topMassII->Write();
    channel->Write();
    eventType->Write();
    top1_channel->Write();
    top2_channel->Write();
    nonTopWChannel->Write();
    top_W_channel->Write();
    top_top_channel->Write();
    myFile->Write();
    myFile->Close();
    return 0;
}
