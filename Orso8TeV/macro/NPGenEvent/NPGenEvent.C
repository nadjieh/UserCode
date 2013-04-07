/* 
 * File:   OrsoHistogramCreator.C
 * Author: Nadjieh
 *
 * Created on October 12, 2012, 12:34 PM
 */

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
#include "../../interface/TRootGenEventMaker.h"
#include "../../../AnalysisClasses/ChiSquared/interface/DR.h"
#include "../../interface/MuonTree.h"
#include "../../interface/GenInfoMuonTree.h"
#include "../../interface/SingleTopHistograms.h"

#include <sstream>
#include <iostream>
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

    TH1D * TopBQuark_1 = new TH1D("TopBQuark_1_direct", "TopBQuark_1", 1500, -1200, 300);
    TH1D * TopBQuark_2 = new TH1D("TopBQuark_2_direct", "TopBQuark_2", 1500, -1200, 300);
    TH1D * TopQuark_1 = new TH1D("TopQuark_1_direct", "TopQuark_1", 1500, -1200, 300);
    TH1D * TopQuark_2 = new TH1D("TopQuark_2_direct", "TopQuark_2", 1500, -1200, 300);
    TH1D * TopQuarkBar_1 = new TH1D("TopQuarkBar_1_direct", "TopQuarkBar_1", 1500, -1200, 300);
    TH1D * TopQuarkBar_2 = new TH1D("TopQuarkBar_2_direct", "TopQuarkBar_2", 1500, -1200, 300);
    TH1D * TopLepton_1 = new TH1D("TopLepton_1_direct", "TopLepton_1", 1500, -1200, 300);
    TH1D * TopLepton_2 = new TH1D("TopLepton_2_direct", "TopLepton_2", 1500, -1200, 300);
    TH1D * TopNeutrino_1 = new TH1D("TopNeutrino_1_direct_direct", "TopNeutrino_1", 1500, -1200, 300);
    TH1D * TopNeutrino_2 = new TH1D("TopNeutrino_2_direct", "TopNeutrino_2", 1500, -1200, 300);
    TH1D * Top_1 = new TH1D("Top_1_direct", "Top_1", 1500, -1200, 300);
    TH1D * Top_2 = new TH1D("Top_2_direct", "Top_2", 1500, -1200, 300);
    TH1D * Top_1_Mass = new TH1D("Top_1_Mass_direct", "Top_1_Mass", 200, 0, 200);
    TH1D * Top_2_Mass = new TH1D("Top_2_Mass_direct", "Top_2_Mass", 200, 0, 200);
    TH1D * W_1_Mass = new TH1D("W_1_Mass_direct", "W_1_Mass", 100, 0, 100);
    TH1D * W_2_Mass = new TH1D("W_2_Mass_direct", "W_2_Mass", 100, 0, 100);
    TH2D * Top_1_IdCharge = new TH2D("Top_1_IdCharge_direct", "Top_1_IdCharge; charge; id", 2, 0, 2, 2, 0, 2);
    TH2D * Top_2_IdCharge = new TH2D("Top_2_IdCharge_direct", "Top_2_IdCharge; charge; id", 2, 0, 2, 2, 0, 2);
    TH2D * Top_12_decayChannel = new TH2D("Top_12_decayChannel_direct", "Top_12_decayChannel; top 1; top 2",
            5, 0, 5, 5, 0, 5);
    TH1D * TopBQuark_1_viaNPgenEvent = new TH1D("TopBQuark_1_viaNPgenEvent", "TopBQuark_1", 1500, -1200, 300);
    TH1D * TopBQuark_2_viaNPgenEvent = new TH1D("TopBQuark_2_viaNPgenEvent", "TopBQuark_2", 1500, -1200, 300);
    TH1D * TopQuark_1_viaNPgenEvent = new TH1D("TopQuark_1_viaNPgenEvent", "TopQuark_1", 1500, -1200, 300);
    TH1D * TopQuark_2_viaNPgenEvent = new TH1D("TopQuark_2_viaNPgenEvent", "TopQuark_2", 1500, -1200, 300);
    TH1D * TopQuarkBar_1_viaNPgenEvent = new TH1D("TopQuarkBar_1_viaNPgenEvent", "TopQuarkBar_1", 1500, -1200, 300);
    TH1D * TopQuarkBar_2_viaNPgenEvent = new TH1D("TopQuarkBar_2_viaNPgenEvent", "TopQuarkBar_2", 1500, -1200, 300);
    TH1D * TopLepton_1_viaNPgenEvent = new TH1D("TopLepton_1_viaNPgenEvent", "TopLepton_1", 1500, -1200, 300);
    TH1D * TopLepton_2_viaNPgenEvent = new TH1D("TopLepton_2_viaNPgenEvent", "TopLepton_2", 1500, -1200, 300);
    TH1D * TopNeutrino_1_viaNPgenEvent = new TH1D("TopNeutrino_1_viaNPgenEvent_viaNPgenEvent", "TopNeutrino_1", 1500, -1200, 300);
    TH1D * TopNeutrino_2_viaNPgenEvent = new TH1D("TopNeutrino_2_viaNPgenEvent", "TopNeutrino_2", 1500, -1200, 300);
    TH1D * Top_1_viaNPgenEvent = new TH1D("Top_1_viaNPgenEvent", "Top_1", 1500, -1200, 300);
    TH1D * Top_2_viaNPgenEvent = new TH1D("Top_2_viaNPgenEvent", "Top_2", 1500, -1200, 300);
    TH1D * Top_1_Mass_viaNPgenEvent = new TH1D("Top_1_Mass_viaNPgenEvent", "Top_1_Mass", 200, 0, 200);
    TH1D * Top_2_Mass_viaNPgenEvent = new TH1D("Top_2_Mass_viaNPgenEvent", "Top_2_Mass", 200, 0, 200);
    TH1D * W_1_Mass_viaNPgenEvent = new TH1D("W_1_Mass_viaNPgenEvent", "W_1_Mass", 100, 0, 100);
    TH1D * W_2_Mass_viaNPgenEvent = new TH1D("W_2_Mass_viaNPgenEvent", "W_2_Mass", 100, 0, 100);
    TH2D * Top_1_IdCharge_viaNPgenEvent = new TH2D("Top_1_IdCharge_viaNPgenEvent", "Top_1_IdCharge; charge; id", 2, 0, 2, 2, 0, 2);
    TH2D * Top_2_IdCharge_viaNPgenEvent = new TH2D("Top_2_IdCharge_viaNPgenEvent", "Top_2_IdCharge; charge; id", 2, 0, 2, 2, 0, 2);
    TH2D * Top_12_decayChannel_viaNPgenEvent = new TH2D("Top_12_decayChannel_viaNPgenEvent", "Top_12_decayChannel; top 1; top 2",
            5, 0, 5, 5, 0, 5);
    Top_12_decayChannel->GetXaxis()->SetBinLabel(2, "hadronic");
    Top_12_decayChannel->GetXaxis()->SetBinLabel(3, "leptonic e");
    Top_12_decayChannel->GetXaxis()->SetBinLabel(4, "leptonic #mu");
    Top_12_decayChannel->GetXaxis()->SetBinLabel(5, "leptonic #tau");
    Top_12_decayChannel->GetYaxis()->SetBinLabel(2, "hadronic");
    Top_12_decayChannel->GetYaxis()->SetBinLabel(3, "leptonic e");
    Top_12_decayChannel->GetYaxis()->SetBinLabel(4, "leptonic #mu");
    Top_12_decayChannel->GetYaxis()->SetBinLabel(5, "leptonic #tau");
    Top_12_decayChannel_viaNPgenEvent->GetXaxis()->SetBinLabel(2, "hadronic");
    Top_12_decayChannel_viaNPgenEvent->GetXaxis()->SetBinLabel(3, "leptonic e");
    Top_12_decayChannel_viaNPgenEvent->GetXaxis()->SetBinLabel(4, "leptonic #mu");
    Top_12_decayChannel_viaNPgenEvent->GetXaxis()->SetBinLabel(5, "leptonic #tau");
    Top_12_decayChannel_viaNPgenEvent->GetYaxis()->SetBinLabel(2, "hadronic");
    Top_12_decayChannel_viaNPgenEvent->GetYaxis()->SetBinLabel(3, "leptonic e");
    Top_12_decayChannel_viaNPgenEvent->GetYaxis()->SetBinLabel(4, "leptonic #mu");
    Top_12_decayChannel_viaNPgenEvent->GetYaxis()->SetBinLabel(5, "leptonic #tau");
    TRandom3 tr(154456);
    for (unsigned int fNumber = 0; fNumber < inputFileNames.size(); fNumber++) {
        cout << "file number " << fNumber + 1 << ": " << inputFileNames.at(fNumber) << endl;
        TFile* f = TFile::Open(inputFileNames.at(fNumber).c_str());
        //        myMuonTree = new MuonTree(eventTree, f, sample + "_2J_1T_noSyst");
        myMuonTree = new GenInfoMuonTree(eventTree, f, sample + "_2J_1T_noSyst");

        for (int eventNumber = 0; eventNumber < myMuonTree->fChain->GetEntriesFast(); eventNumber++) {
            cout << "event number " << eventNumber << " -------------------" << endl;
            myMuonTree->GetEntry(eventNumber);
            TopQuark_1->Fill(myMuonTree->MCTopQuark_1_PdgId);
            //            TopQuark_2->Fill(myMuonTree->MCTopQuark_2_PdgId);
            TopQuarkBar_1->Fill(myMuonTree->MCTopQuarkBar_1_PdgId);
            //            TopQuarkBar_2->Fill(myMuonTree->MCTopQuarkBar_2_PdgId);
            TopBQuark_1->Fill(myMuonTree->MCTopBQuark_1_PdgId);
            //            TopBQuark_2->Fill(myMuonTree->MCTopBQuark_2_PdgId);
            TopLepton_1->Fill(myMuonTree->MCTopLepton_1_PdgId);
            //            TopLepton_2->Fill(myMuonTree->MCTopLepton_2_PdgId);
            Top_1->Fill(myMuonTree->MCTop_1_PdgId);
            //            Top_2->Fill(myMuonTree->MCTop_2_PdgId);
            TopNeutrino_1->Fill(myMuonTree->MCTopNeutrino_1_PdgId);
            //            TopNeutrino_2->Fill(myMuonTree->MCTopNeutrino_2_PdgId);
            Top_1_Mass->Fill(myMuonTree->GetGenTop(1).M());
            //            Top_2_Mass->Fill(myMuonTree->GetGenTop(2).M());

            W_1_Mass->Fill(myMuonTree->GetGenTop(1).W().M());
            //            W_2_Mass->Fill(myMuonTree->GetGenTop(2).W().M());
            cout << "I am in direct part: " << endl;
            //            if (myMuonTree->GetGenTop(1).isLeptonic())
            Top_1_IdCharge->Fill(myMuonTree->isTopConsistentCharge(myMuonTree->GetGenTop(1)),
                    myMuonTree->isTopConsistentID(myMuonTree->GetGenTop(1)));
            //            Top_2_IdCharge->Fill(myMuonTree->isTopConsistentCharge(myMuonTree->GetGenTop(2)),
            //                    myMuonTree->isTopConsistentID(myMuonTree->GetGenTop(2)));
            Top_12_decayChannel->Fill(myMuonTree->GetTopDecayChannel(myMuonTree->GetGenTop(1)),
                    myMuonTree->WdecayInTW);
            //                    myMuonTree->GetTopDecayChannel(myMuonTree->GetGenTop(2)));


            //            if (myMuonTree->isTopConsistentCharge(myMuonTree->GetGenTop(1)) &&
            //                    !myMuonTree->isTopConsistentID(myMuonTree->GetGenTop(1))) {
            //                cout << myMuonTree->isTopConsistentCharge(myMuonTree->GetGenTop(1)) << "\tllll " <<
            //                        myMuonTree->isTopConsistentID(myMuonTree->GetGenTop(1)) << endl;
            //                cout << "------------------------------------------------------ " << eventNumber << endl;
            //                cout << "------------------------------------------------------ " << eventNumber << endl;
            //            }

            TRootGenEventMaker NPGenMaker(myMuonTree, string(sample), 0);
            TopQuark_1_viaNPgenEvent->Fill((NPGenMaker.output.tops())[0].quark().type());
            TopQuark_2_viaNPgenEvent->Fill((NPGenMaker.output.tops())[1].quark().type());
            TopQuarkBar_1_viaNPgenEvent->Fill((NPGenMaker.output.tops())[0].quarkBar().type());
            TopQuarkBar_2_viaNPgenEvent->Fill((NPGenMaker.output.tops())[1].quarkBar().type());
            TopBQuark_1_viaNPgenEvent->Fill((NPGenMaker.output.tops())[0].bquark().type());
            TopBQuark_2_viaNPgenEvent->Fill((NPGenMaker.output.tops())[1].bquark().type());
            TopLepton_1_viaNPgenEvent->Fill((NPGenMaker.output.tops())[0].lepton().type());
            TopLepton_2_viaNPgenEvent->Fill((NPGenMaker.output.tops())[1].lepton().type());
            Top_1_viaNPgenEvent->Fill((NPGenMaker.output.tops())[0].type());
            Top_2_viaNPgenEvent->Fill((NPGenMaker.output.tops())[1].type());
            TopNeutrino_1_viaNPgenEvent->Fill((NPGenMaker.output.tops())[0].neutrino().type());
            TopNeutrino_2_viaNPgenEvent->Fill((NPGenMaker.output.tops())[1].neutrino().type());
            Top_1_Mass_viaNPgenEvent->Fill((NPGenMaker.output.tops())[0].M());
            Top_2_Mass_viaNPgenEvent->Fill((NPGenMaker.output.tops())[1].M());

            W_1_Mass_viaNPgenEvent->Fill((NPGenMaker.output.tops())[0].W().M());
            W_2_Mass_viaNPgenEvent->Fill((NPGenMaker.output.tops())[1].W().M());
            cout << "I am in indirect part: " << endl;
            //            if (NPGenMaker.output.tops()[0].isLeptonic())
            Top_1_IdCharge_viaNPgenEvent->Fill(myMuonTree->isTopConsistentCharge(NPGenMaker.output.tops()[0]),
                    myMuonTree->isTopConsistentID(NPGenMaker.output.tops()[0]));
            if (NPGenMaker.output.tops().size() > 1)
                Top_2_IdCharge_viaNPgenEvent->Fill(myMuonTree->isTopConsistentCharge(NPGenMaker.output.tops()[1]),
                    myMuonTree->isTopConsistentID(NPGenMaker.output.tops()[1]));

            Top_12_decayChannel_viaNPgenEvent->Fill(myMuonTree->GetTopDecayChannel(NPGenMaker.output.tops()[0]),
                    myMuonTree->WdecayInTW);
            //                    myMuonTree->GetTopDecayChannel(NPGenMaker.output.tops()[1]));
            std::vector<int> nonTopW = NPGenMaker.output.getNonTopWList();
            cout << "Second W status: " << endl;
            for (int s = 0; s < nonTopW.size(); s++) {
                cout << "\t" << nonTopW[s] << endl;
            }
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
    Top_1_viaNPgenEvent->Write();
    Top_2_viaNPgenEvent->Write();
    TopBQuark_1_viaNPgenEvent->Write();
    TopBQuark_2_viaNPgenEvent->Write();
    TopQuark_1_viaNPgenEvent->Write();
    TopQuark_2_viaNPgenEvent->Write();
    TopQuarkBar_1_viaNPgenEvent->Write();
    TopQuarkBar_2_viaNPgenEvent->Write();
    TopLepton_1_viaNPgenEvent->Write();
    TopLepton_2_viaNPgenEvent->Write();
    TopNeutrino_1_viaNPgenEvent->Write();
    TopNeutrino_2_viaNPgenEvent->Write();
    Top_12_decayChannel_viaNPgenEvent->Write();
    Top_1_IdCharge_viaNPgenEvent->Write();
    Top_1_Mass_viaNPgenEvent->Write();
    W_1_Mass_viaNPgenEvent->Write();
    Top_2_IdCharge_viaNPgenEvent->Write();
    Top_2_Mass_viaNPgenEvent->Write();
    W_2_Mass_viaNPgenEvent->Write();

    fout->Write();
    fout->Close();

    cout << nInit << "\n" << nHLTrunB << "\n" << nMt << "\n" << nFinal << "\n" << nGoodSolution << endl;
    return 0;
}

