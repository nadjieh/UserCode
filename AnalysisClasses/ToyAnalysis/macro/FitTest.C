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

 

int main(int argc, char** argv){
//    sleep(60);

    TH1*  data;
    TH1*  signal;
    TH1*  bkg;
    TFile * file = 0;
    for (int f = 1; f < argc; f++) {
        std::string arg_fth(*(argv + f));
        if (arg_fth == "signal") {
          f++;
          std::string out(*(argv + f));
          file = new TFile(out.c_str(),"read");
          signal = ((TH1*)file->Get("cosTheta"));
        }else if(arg_fth == "data"){
          f++;
          std::string out(*(argv + f));
          file = new TFile(out.c_str(),"read");
          data = ((TH1*)file->Get("cosTheta"));
        }else if (arg_fth == "bkg") {
            f++;
            std::string out(*(argv + f));
            file = new TFile(out.c_str(),"read");
            bkg = ((TH1*)file->Get("cosTheta"));
        }
    }
    cout<<bkg <<"\t"<<signal<<"\t"<<data<<endl;
    std::pair<TF3,LikelihoodFunction*>  myLL = LikelihoodFunction::getLLFunction("LL" , bkg , data , signal);
//    std::pair<TF3,ChiSquaredFunction*> myChi2 = ChiSquaredFunction::getChiSquaredFunction("Chi2" , bkg , data , signal);
    double x[3] = {-1.,-1.,-1};
    double xerr[3] = {-1.,-1.,-1};
//    myChi2.first.GetMinimumXYZ(x_m , y_m , z_m);
    myLL.first.GetMinimumXYZ(x[0] , x[1] , x[2]);
    
    cout<<"simple getMin: "<<x[0]<<"  "<<x[1]<<"  "<<x[2]<<endl;
    double correlation;
    GetMinimum(myLL.first,x,xerr,correlation);
    cout<<"my getMin-vals: "<<x[0]<<"  "<<x[1]<<"  "<<x[2]<<endl;
    cout<<"my getMin-err: "<<xerr[0]<<"  "<<xerr[1]<<"  "<<xerr[2]<<endl;
    cout<<"F0_FNeg correlation: "<<correlation/(double)(xerr[0]*xerr[1])<<endl;
    
//    delete myChi2.second;
    delete myLL.second;
    return 0;
}