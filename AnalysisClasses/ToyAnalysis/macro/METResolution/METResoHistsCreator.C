/*
 * For the moment I use the event selection chain in explicitly
 * It comes from AnalysisClasses/EventSelection/macro/t-SingleTopSelection/SelectAndSave.C
 */
/* 
 * File:   METResolHistCreator.C
 * Author: ajafari
 *
 * Created on January 29, 2012, 8:18 PM
 */


#include "../../interface/GenSingleTopMaker.h"
#include "../../interface/METResolutionSingleTop.h"


#include "../../../../TopBrussels/TopTreeProducer/interface/TRootNPGenEvent.h"
#include "../../../EventSelection/interface/PracticalEvent.h"
#include "../../../PhysicsObjects/interface/SemiLepTopQuark.h"





#include <sstream>
#include <string>

#include <TApplication.h>
#include <TLorentzVector.h>
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


int main(int argc, char** argv){
//    sleep(60);
    std::string outFile;
    std::vector<std::string> inFile;
    for (int f = 1; f < argc; f++) {
        std::string arg_fth(*(argv + f));

        if (arg_fth == "out") {
          f++;
          std::string out(*(argv + f));
          outFile = string(out+".root");
        }else if (arg_fth == "input") {
          f++;
          std::string in(*(argv + f));
          inFile.push_back(string("~/"+in));
        }
    }
    TApplication theApp("App", &argc, argv);
    METResolutionHistograms myMEThistos;
    for(unsigned int fnumber = 0; fnumber < inFile.size(); fnumber++){
        TFile * f = TFile::Open(inFile.at(fnumber).c_str());
        TTree* runTree = (TTree*) f->Get("runTree");
        TTree* eventTree = (TTree*) f->Get("eventTree");
        PracticalEvent * pracEvt = new PracticalEvent(eventTree,runTree);
        pracEvt->eventTree->SetBranchStatus("*", 1);
        while (pracEvt->Next()) {
            METResolutionSingleTop myMETResol((TRootNPGenEvent*)(pracEvt->NPGenEvtCollection()->At(0)),
            (TLorentzVector*)(pracEvt->METCollection()->At(0)));
            myMEThistos.Fill(myMETResol.getMETRes());
        }
        f->Close();
    }
    TFile * out = new TFile(outFile.c_str(),"recreate");
    myMEThistos.Write(out);
    out->Write();
    out->Close();
    return 0;
}

