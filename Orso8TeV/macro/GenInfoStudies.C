/* 
 * File:   OrsoHistogramCreator.C
 * Author: nadjieh
 *
 * Created on October 12, 2012, 12:34 PM
 */

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
#include "../interface/MuonTree.h"
#include "../interface/GenInfoMuonTree.h"
#include "../interface/SingleTopHistograms.h"

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

int main(int argc, char** argv) {
    std::vector<std::string> inputFileNames;
    std::string plotFileName;
    int verbosity = 0;
    TH1D * METResolutions = 0;
    bool pu3D = false; //true;
    double doJES = 1;
    bool isData = false;
    int smearingSkim = 1;
    TString sample = "";
    for (int f = 1; f < argc; f++) {
        std::string arg_fth(*(argv + f));

        if (arg_fth == "input") {
            f++;
            std::string in(*(argv + f));
            inputFileNames.push_back(string("~/work/samples/Orso8TeV/Nov_53X/" + in + ".root"));
            sample = in;
            plotFileName = in + "_plots.root";
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
        } else if (arg_fth == "smearingSkim") {
            f++;
            std::string in(*(argv + f));
            smearingSkim = atof(in.c_str());
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

    //    MuonTree * myMuonTree = 0;
    GenInfoMuonTree * myMuonTree = 0;
    TTree * eventTree = 0;


    GenSingleTopMaker* genSingleTop = 0;

    TH1D * TopBQuark_1 = new TH1D("TopBQuark_1", "TopBQuark_1", 1500, -1200, 300);
    TH1D * TopBQuark_2 = new TH1D("TopBQuark_2", "TopBQuark_2", 1500, -1200, 300);
    TH1D * TopQuark_1 = new TH1D("TopQuark_1", "TopQuark_1", 1500, -1200, 300);
    TH1D * TopQuark_2 = new TH1D("TopQuark_2", "TopQuark_2", 1500, -1200, 300);
    TH1D * TopQuarkBar_1 = new TH1D("TopQuarkBar_1", "TopQuarkBar_1", 1500, -1200, 300);
    TH1D * TopQuarkBar_2 = new TH1D("TopQuarkBar_2", "TopQuarkBar_2", 1500, -1200, 300);
    TH1D * TopLepton_1 = new TH1D("TopLepton_1", "TopLepton_1", 1500, -1200, 300);
    TH1D * TopLepton_2 = new TH1D("TopLepton_2", "TopLepton_2", 1500, -1200, 300);
    TH1D * TopNeutrino_1 = new TH1D("TopNeutrino_1", "TopNeutrino_1", 1500, -1200, 300);
    TH1D * TopNeutrino_2 = new TH1D("TopNeutrino_2", "TopNeutrino_2", 1500, -1200, 300);
    TH1D * Top_1 = new TH1D("Top_1", "Top_1", 1500, -1200, 300);
    TH1D * Top_2 = new TH1D("Top_2", "Top_2", 1500, -1200, 300);
    TH1D * Top_1_Mass = new TH1D("Top_1_Mass", "Top_1_Mass", 200, 0, 200);
    TH1D * Top_2_Mass = new TH1D("Top_2_Mass", "Top_2_Mass", 200, 0, 200);
    TH1D * W_1_Mass = new TH1D("W_1_Mass", "W_1_Mass", 100, 0, 100);
    TH1D * W_2_Mass = new TH1D("W_2_Mass", "W_2_Mass", 100, 0, 100);
    TH2D * Top_1_IdCharge = new TH2D("Top_1_IdCharge", "Top_1_IdCharge; charge; id", 2, 0, 2, 2, 0, 2);
    TH2D * Top_2_IdCharge = new TH2D("Top_2_IdCharge", "Top_2_IdCharge; charge; id", 2, 0, 2, 2, 0, 2);
    TH2D * Top_12_decayChannel = new TH2D("Top_12_decayChannel", "Top_12_decayChannel; top 1; top 2",
            5, 0, 5, 5, 0, 5);
    Top_12_decayChannel->GetXaxis()->SetBinLabel(2, "hadronic");
    Top_12_decayChannel->GetXaxis()->SetBinLabel(3, "leptonic e");
    Top_12_decayChannel->GetXaxis()->SetBinLabel(4, "leptonic #mu");
    Top_12_decayChannel->GetXaxis()->SetBinLabel(5, "leptonic #tau");
    Top_12_decayChannel->GetYaxis()->SetBinLabel(2, "hadronic");
    Top_12_decayChannel->GetYaxis()->SetBinLabel(3, "leptonic e");
    Top_12_decayChannel->GetYaxis()->SetBinLabel(4, "leptonic #mu");
    Top_12_decayChannel->GetYaxis()->SetBinLabel(5, "leptonic #tau");
    TRandom3 tr(154456);
    for (unsigned int fNumber = 0; fNumber < inputFileNames.size(); fNumber++) {
        cout << "file number " << fNumber + 1 << ": " << inputFileNames.at(fNumber) << endl;
        TFile* f = TFile::Open(inputFileNames.at(fNumber).c_str());
        //        myMuonTree = new MuonTree(eventTree, f, sample + "_2J_1T_noSyst");
        myMuonTree = new GenInfoMuonTree(eventTree, f, sample + "_2J_1T_noSyst");
        double lumiWeight3D = 1;
        for (int eventNumber = 0; eventNumber < myMuonTree->fChain->GetEntriesFast(); eventNumber++) {
            myMuonTree->GetEntry(eventNumber);
            TopQuark_1->Fill(myMuonTree->MCTopQuark_1_PdgId);
            TopQuark_2->Fill(myMuonTree->MCTopQuark_2_PdgId);
            TopQuarkBar_1->Fill(myMuonTree->MCTopQuarkBar_1_PdgId);
            TopQuarkBar_2->Fill(myMuonTree->MCTopQuarkBar_2_PdgId);
            TopBQuark_1->Fill(myMuonTree->MCTopBQuark_1_PdgId);
            TopBQuark_2->Fill(myMuonTree->MCTopBQuark_2_PdgId);
            //            cout<<myMuonTree->MCTopBQuark_2_MotherId<<endl;
            TopLepton_1->Fill(myMuonTree->MCTopLepton_1_PdgId);
//            cout<<"my lepton: "<<myMuonTree->MCTopLepton_1_PdgId<<endl;
            TopLepton_2->Fill(myMuonTree->MCTopLepton_2_PdgId);
            Top_1->Fill(myMuonTree->MCTop_1_PdgId);
            Top_2->Fill(myMuonTree->MCTop_2_PdgId);
            TopNeutrino_1->Fill(myMuonTree->MCTopNeutrino_1_PdgId);
            TopNeutrino_2->Fill(myMuonTree->MCTopNeutrino_2_PdgId);
            Top_1_Mass->Fill(myMuonTree->GetGenTop(1).M());
            //            Top_2_Mass->Fill(myMuonTree->GetGenTop(2).M());
            //            Top_1_Mass->Fill((myMuonTree->GetMCW1() + myMuonTree->GetMCb1()).M());
            Top_2_Mass->Fill(myMuonTree->GetGenTop(2).M());
            //            cout<<myMuonTree->GetGenTop(2).M()<<endl;

            W_1_Mass->Fill(myMuonTree->GetGenTop(1).W().M());
            W_2_Mass->Fill(myMuonTree->GetGenTop(2).W().M());
            //            cout<<"top 1:"<<endl;
            Top_1_IdCharge->Fill(myMuonTree->isTopConsistentCharge(myMuonTree->GetGenTop(1)),
                    myMuonTree->isTopConsistentID(myMuonTree->GetGenTop(1)));
            //            cout<<"top 2:"<<endl;
            Top_2_IdCharge->Fill(myMuonTree->isTopConsistentCharge(myMuonTree->GetGenTop(2)),
                    myMuonTree->isTopConsistentID(myMuonTree->GetGenTop(2)));
            Top_12_decayChannel->Fill(myMuonTree->GetTopDecayChannel(myMuonTree->GetGenTop(1)),
//                    1);
                    myMuonTree->GetTopDecayChannel(myMuonTree->GetGenTop(2)));


            if (myMuonTree->isTopConsistentCharge(myMuonTree->GetGenTop(1)) &&
                    !myMuonTree->isTopConsistentID(myMuonTree->GetGenTop(1))) {
                cout << myMuonTree->isTopConsistentCharge(myMuonTree->GetGenTop(1)) << "\tllll " <<
                        myMuonTree->isTopConsistentID(myMuonTree->GetGenTop(1)) << endl;
                cout << "------------------------------------------------------ " << eventNumber << endl;
                cout << "------------------------------------------------------ " << eventNumber << endl;
            }

            //            if(myMuonTree->MCTop_1_PdgId == myMuonTree->MCTop_2_PdgId){
            //                cout<<"What is it?!!"<<eventNumber<<endl;
            //                break;
            //            }

        }

        cout << "before closing file input " << f->GetName() << endl;
        f->Close();
        delete f;

    }
    cout << "before endjob" << endl;
    TFile * fout = new TFile(plotFileName.c_str(), "recreate");
    fout->cd();
    Top_1->Write();
    Top_2->Write();
    TopBQuark_1->Write();
    TopBQuark_2->Write();
    TopQuark_1->Write();
    TopQuark_2->Write();
    TopQuarkBar_1->Write();
    TopQuarkBar_2->Write();
    TopLepton_1->Write();
    TopLepton_2->Write();
    TopNeutrino_1->Write();
    TopNeutrino_2->Write();
    Top_12_decayChannel->Write();
    Top_1_IdCharge->Write();
    Top_1_Mass->Write();
    W_1_Mass->Write();
    Top_2_IdCharge->Write();
    Top_2_Mass->Write();
    W_2_Mass->Write();

    fout->Write();
    fout->Close();

    cout << nInit << "\n" << nHLTrunB << "\n" << nMt << "\n" << nFinal << "\n" << nGoodSolution << endl;
    return 0;
}

