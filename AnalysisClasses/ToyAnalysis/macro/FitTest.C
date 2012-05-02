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
using namespace TopTree;




    


    

int main(int argc, char** argv){
//    sleep(60);

    TH1D  data;
    TH1D  signal;
    TH1D  bkg;
    TFile * file = 0;
    for (int f = 1; f < argc; f++) {
        std::string arg_fth(*(argv + f));
        if (arg_fth == "signal") {
          f++;
          std::string out(*(argv + f));
          file = new TFile(out.c_str(),"read");
          signal = *((TH1D*)file->Get("cosTheta"));
        }else if(arg_fth == "data"){
          f++;
          std::string out(*(argv + f));
          file = new TFile(out.c_str(),"read");
          data = *((TH1D*)file->Get("cosTheta"));
        }else if (arg_fth == "bkg") {
            f++;
            std::string out(*(argv + f));
            file = new TFile(out.c_str(),"read");
            bkg = *((TH1D*)file->Get("cosTheta"));
        }
    }

//    TF3 myLL = LikelihoodFunction::getLLFunction("LL" , bkg , data , signal);
    TF3 myChi2 = ChiSquaredFunction::getChiSquaredFunction("Chi2" , bkg , data , signal);
    double x_m = -1.;
    double y_m = -1.;
    double z_m = -1.;
    myChi2.GetMinimumXYZ(x_m , y_m , z_m);
    
    cout<<x_m<<"  "<<y_m<<"  "<<z_m<<endl;
    return 0;
}