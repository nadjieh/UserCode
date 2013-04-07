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
#include "../../interface/BTagWeight.h"

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
#include "../../../../AnalysisClasses/EventSelection/interface/UnclusteredMETUncertainty.h"
#include "../../../../AnalysisClasses/EventSelection/interface/DifferentHistogramsTwb.h"
#include "../../../../AnalysisClasses/ToyAnalysis/interface/GenSingleTopMaker.h"
#include "../../../../TopBrussels/TopTreeAnalysis/MCInformation/interface/Lumi3DReWeighting.h"




#include <sstream>
#include <string>

#include <TApplication.h>
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
using namespace TopTree;

/*
 * 
 */




int main(int argc, char** argv) {
    std::vector<std::string> inputFileNames;
    std::string plotFileName;
    int verbosity = 0;
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
        }
    }

    TFile* f = 0;
    TApplication theApp("App", &argc, argv);

    GenSingleTopMaker* genSingleTop = 0;
    TH1D * bquarksMothers = new TH1D("bquarks", "bquarks", 200, -100, 100);
    TH1D * Wquarks = new TH1D("Wquarks", "Wquarks", 12, -6, 6);
    TH1D * nonWquarks = new TH1D("nonWquarks", "nonWquarks", 12, -6, 6);
    TH1D * nbquarks = new TH1D("nbquarks", "nbquarks", 20, 0, 20);
    TH1D * ncquarks = new TH1D("ncquarks", "ncquarks", 20, 0, 20);
    TH1D * nlquarks = new TH1D("nlquarks", "nlquarks", 20, 0, 20);
    TH2D * nbcquarks = new TH2D("nbcquarks", "nbcquarks", 20, 0, 20, 20, 0, 20);
    TH2D * nlcquarks = new TH2D("nlcquarks", "nlcquarks", 20, 0, 20, 20, 0, 20);
    for (unsigned int fNumber = 0; fNumber < inputFileNames.size(); fNumber++) {
        cout << "file number " << fNumber + 1 << ": " << inputFileNames.at(fNumber) << endl;
        f = TFile::Open(inputFileNames.at(fNumber).c_str());

        TTree* runTree = (TTree*) f->Get("runTree");
        TTree* eventTree = (TTree*) f->Get("eventTree");
        PracticalEvent * pracEvt = new PracticalEvent(eventTree, runTree);
        pracEvt->eventTree->SetBranchStatus("*", 1);

        std::cout << "beforeLoop" << std::endl;

        int ievt = 0;

        while (pracEvt->Next()) {

            ievt++;

            /* for single top genAnalysis
             * not to be used for real one
             */
            int nc = 0;
            int nl = 0;
            if (pracEvt->NPGenEvtCollection() != 0) {
                cout << "I am here" << endl;
                
                genSingleTop = new GenSingleTopMaker((TRootNPGenEvent*) pracEvt->NPGenEvtCollection()->At(0), verbosity);
                std::vector<TRootMCParticle> quarks = ((TRootNPGenEvent*) pracEvt->NPGenEvtCollection()->At(0))->quarks();
                std::vector<TRootMCParticle> bquarks = ((TRootNPGenEvent*) pracEvt->NPGenEvtCollection()->At(0))->bquarks();
                nbquarks->Fill(bquarks.size());
                for (unsigned int i = 0; i < bquarks.size(); i++) {
                    bquarksMothers->Fill(bquarks[i].motherType());
                }
                for (unsigned int i = 0; i < quarks.size(); i++) {
                    if (fabs(quarks[i].motherType()) == 24)
                        Wquarks->Fill(quarks[i].type());
                    else {
                        if (fabs(quarks[i].type()) == 4)
                            nc++;
                        if (fabs(quarks[i].type()) < 4)
                            nl++;
                        nonWquarks->Fill(quarks[i].type());
                    }
                }
                ncquarks->Fill(nc);
                nlquarks->Fill(nl);
                nbcquarks->Fill(bquarks.size(), nc);
                nlcquarks->Fill(nl, nc);
            }

            if (genSingleTop != NULL)
                delete genSingleTop;


        }

        cout << "before closing file input " << f->GetName() << endl;
        f->Close();
        delete f;

    }
    cout << "before endjob" << endl;
    TFile * fout = new TFile(plotFileName.c_str(), "recreate");
    fout->cd();
    bquarksMothers->Write();
    Wquarks->Write();
    nonWquarks->Write();
    nbquarks->Write();
    ncquarks->Write();
    nlquarks->Write();
    nlcquarks->Write();
    nbcquarks->Write();
    fout->Write();
    fout->Close();
    return 0;
}

