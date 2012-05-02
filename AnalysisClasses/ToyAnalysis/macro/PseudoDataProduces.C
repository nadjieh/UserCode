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
#include "../../../TopBrussels/TopTreeAnalysis/MCInformation/interface/Lumi3DReWeighting.h"




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
#include <TRandom1.h>
#include <TGraph.h>
#include <map>
#include <vector>

using namespace std;
using namespace TopTree;
using namespace ROOT;




    


    

int main(int argc, char** argv){
//    sleep(60);
    string weightFileName;
    string toy_plotFileName;
    double toy_weight = 1;


    int toy_verbosity = 0;



    std::string mcInput = string("./cosTheta_allMC_METSmeared.root");


    
    for (int f = 1; f < argc; f++) {
        std::string arg_fth(*(argv + f));
        else if (arg_fth == "mcinput") {
          f++;
          std::string in(*(argv + f));
          mcInput = string("./cosTheta_allMC_METSmeared.root");
        }
    }

    TApplication theApp("App", &argc, argv);
    TFile * fmc = TFile::Open(mcInput.c_str());
    TH1D * h = (TH1D*)fmc->Get("cosTheta");
    TH1D * H2 = new TH1D("cosTheta_PsuedoData", "cosTheta_PsuedoData",1000,-1,1);

    for(int j = 0; j<h->GetXaxis()->GetNbins(); j++){
        double mean =h->GetBinContent(j+1);
        TRandom1 s;
        double mean_PD = s.Poisson(mean);
        H2->SetBinContent(j+1,mean_PD);
        H2->SetBinError(j+1, sqrt(mean_PD));
    }
    

    cout<<"before endjob"<<endl;
    
    TFile * myFile = new TFile("PsuedoData_cosThetaSM.root", "recreate");
    myFile->cd();
    H2->Write();
    myFile->Write();
    myFile->Close();
    return 0;
}
