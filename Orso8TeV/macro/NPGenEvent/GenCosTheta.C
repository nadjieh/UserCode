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
            inputFileNames.push_back(string("~/work/samples/Orso8TeV/Nov/" + in + ".root"));
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

    TH1D * cosTheta = new TH1D("cosTheta","cosTheta",100, -1.,1.);
    TRandom3 tr(154456);
    for (unsigned int fNumber = 0; fNumber < inputFileNames.size(); fNumber++) {
        cout << "file number " << fNumber + 1 << ": " << inputFileNames.at(fNumber) << endl;
        TFile* f = TFile::Open(inputFileNames.at(fNumber).c_str());
        //        myMuonTree = new MuonTree(eventTree, f, sample + "_2J_1T_noSyst");
        myMuonTree = new GenInfoMuonTree(eventTree, f, sample + "_2J_1T_noSyst");

        for (int eventNumber = 0; eventNumber < myMuonTree->fChain->GetEntriesFast(); eventNumber++) {
            cout << "event number " << eventNumber << " -------------------" << endl;
            myMuonTree->GetEntry(eventNumber);

            TRootGenEventMaker NPGenMaker(myMuonTree);
            genSingleTop = new GenSingleTopMaker(NPGenMaker.output);
            if(!genSingleTop->isSemiMuSingleTop)
                continue;
            
        }

        cout << "before closing file input " << f->GetName() << endl;
        f->Close();
        delete f;

    }
    cout << "before endjob" << endl;
    TFile * fout = new TFile(plotFileName.c_str(), "recreate");
    fout->cd();
    cosTheta->Write();

    fout->Write();
    fout->Close();

    cout << nInit << "\n" << nHLTrunB << "\n" << nMt << "\n" << nFinal << "\n" << nGoodSolution << endl;
    return 0;
}

