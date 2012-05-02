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
#include <TGraph.h>
#include <map>
#include <vector>

using namespace std;
using namespace TopTree;




    


    
pair <std::vector<TH1D*> , TGraph*>WeightsLoader(TFile * f){
    std::vector<TH1D*> Ws;
    TGraph * g;
    TList * l = f->GetListOfKeys();
    for(int i = 0; i< l->GetSize(); i++){
//        if(string(l->At(i)->GetName()) == "fvarValues" || string(l->At(i)->GetName()) == "fvarValuesG")
//            continue;
        if( string(l->At(i)->GetName()) == "fvarValuesG")
            g = (TGraph*)f->Get(l->At(i)->GetName());
        else
            Ws.push_back((TH1D*)f->Get(l->At(i)->GetName()));
    }
    cout<<Ws.size()<<endl;
    return make_pair(Ws,g);
}
int main(int argc, char** argv){
//    sleep(60);
    string input;
    string out;
    int SmearingSkim = 1;
    for (int f = 1; f < argc; f++) {
        std::string arg_fth(*(argv + f));
        if (arg_fth == "fileName") {
          f++;
          std::string out_(*(argv + f));
          input = string(out_+".root");
          out = string(out_ + "_RW.root");
        }
    }
    TApplication theApp("App", &argc, argv);
    TFile * fin = TFile::Open(input.c_str());
    
    TH1D * data = (TH1D*)fin->Get("cosTheta");
    double f0=6.64263e-01;
    double fminus=3.03734e-01;
    bool f0Fixed=true;
    bool fminusFixed=false;
    int nSteps=5;
    //f0 6.64263e-01 fminus 3.03734e-01 isFixed f0
    CosThetaWeightHandler myHandler(f0,fminus,f0Fixed,fminusFixed,nSteps);
    myHandler.CosThetaReweigherFunc(data,1);
    TFile * fout = new TFile(out.c_str(),"recreate");
    fout->cd();
    data->Write();
    fout->Close();
    return 0;
}