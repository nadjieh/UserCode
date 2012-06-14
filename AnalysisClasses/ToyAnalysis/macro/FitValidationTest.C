/*
 * Aimed to run on selected events
 * 
 */
/* 
 * File:   SelectAndSave.c
 * Author: ajafari
 *
 * Created on January 29, 2012, 8:18 PM
 */

#include "../../EventSelection/interface/ElectronSelector.h"

#include "../../EventSelection/interface/Event.h"

#include "../../EventSelection/interface/ElectronHists.h"
#include "../../EventSelection/interface/MuonHists.h"
#include "../../EventSelection/interface/PVHists.h"
#include "../../EventSelection/interface/JetHists.h"
#include "../../EventSelection/interface/JetSelector.h"
#include "../../EventSelection/interface/MuonVetoSelector.h"

#include "../../EventSelection/interface/PrimaryVertexSelector.h"

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
#include "../../PhysicsObjects/interface/SemiLepTopQuark.h"
#include "../interface/GenSingleTopMaker.h"
#include "../interface/CosThetaWeighter.h"
#include "../interface/CosThetaWeightHandler.h"
#include "../interface/DataPointsChiSquared.h"
#include "../interface/ToyFitter.h"
#include "../interface/FitValidator.h"
#include "../interface/ValidatorExecuter.h"
#include "../../../TopBrussels/TopTreeAnalysis/MCInformation/interface/Lumi3DReWeighting.h"





#include <sstream>
#include <string>

#include <TApplication.h>
#include <TFile.h>
#include <TH1.h>
#include <TF3.h>
#include <TH2.h>
#include <TCanvas.h>
#include <TBranch.h>
#include <TTree.h>
#include <TSystem.h>
#include <TGraph.h>
#include <map>
#include <vector>

using namespace std;

 

int main(int argc, char** argv){
//    sleep(60);

    TH1D  data;
    TH1D  signal;
    TH1D  bkg;
    TFile * file = 0;
    int StartPEX=-1;
    int LPEX=0;
    int StartPEXPull=-1;
    int LPEXPull = 0;
    double Lumi = 0;
    string prefix;
    string suffix;
    string histName;
    for (int f = 1; f < argc; f++) {
        std::string arg_fth(*(argv + f));
        if (arg_fth == "StartPEX") {
          f++;
          std::string out(*(argv + f));
          StartPEX = atof(out.c_str());
        }else if(arg_fth == "LPEX"){
          f++;
          std::string out(*(argv + f));
          LPEX = atof(out.c_str());
        }else if (arg_fth == "StartPEXPull") {
            f++;
            std::string out(*(argv + f));
            StartPEXPull = atof(out.c_str());
        }else if (arg_fth == "LPEXPull") {
            f++;
            std::string out(*(argv + f));
            LPEXPull = atof(out.c_str());            
        }else if (arg_fth == "Lumi") {
            f++;
            std::string out(*(argv + f));
            Lumi = atof(out.c_str());            
        }else if (arg_fth == "prefix") {
            f++;
            std::string out(*(argv + f));
            prefix = out;            
        }else if (arg_fth == "suffix") {
            f++;
            std::string out(*(argv + f));
            suffix = out;            
        }else if (arg_fth == "histName") {
            f++;
            std::string out(*(argv + f));
            histName = out;            
        }
    }

    RunFitValidation(StartPEX, LPEX, StartPEXPull, LPEXPull,prefix,suffix,histName);
    return 0;
}