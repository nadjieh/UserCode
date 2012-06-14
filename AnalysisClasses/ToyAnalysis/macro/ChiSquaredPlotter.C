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



typedef std::vector<TH1D*> Histograms;
    


    

int main(int argc, char** argv){
//    sleep(60);
    string weightFileName;
    string toy_plotFileName;
    double toy_weight = 1;


    int toy_verbosity = 0;



    std::string mcInput;
    std::string dataInput;

    
    for (int f = 1; f < argc; f++) {
        std::string arg_fth(*(argv + f));
        if (arg_fth == "out") {
          f++;
          std::string out(*(argv + f));
	  toy_plotFileName = out;
        }else if(arg_fth == "WeightFile"){
          f++;
          std::string in(*(argv + f));
          weightFileName = in;            
        }else if (arg_fth == "mcinput") {
          f++;
          std::string in(*(argv + f));
          mcInput = string("./cosTheta_"+in+"_METsmeared.root");
//          mcInput = string("./cosTheta_"+in+".root");
        }else if (arg_fth == "datainput") {
          f++;
          std::string in(*(argv + f));
//          dataInput = string("./cosTheta_"+in+".root");
          dataInput = string("./cosTheta_"+in+"_METsmeared.root");
//          dataInput = string(in);
        }
    }
//    cout<<doJES<<endl;
    cout << weightFileName << endl;
    TFile * WF = TFile::Open(weightFileName.c_str());
    TList* list = WF->GetListOfKeys();
    TGraph * g = new TGraph(*(TGraph*)WF->Get(list->At(1)->GetName()));
    cout<<g->GetName()<<endl;
    int n = g->GetN();
    cout<<n<<endl;
    double fvar[n+1];
//    double fvar[n];
    fvar[0]= 3.03734e-01;//SM
    double tmpY;
    for(int i = 0; i<n; i++)
        g->GetPoint(i,fvar[i+1],tmpY);
//        g->GetPoint(i,fvar[i],tmpY);
    if(toy_verbosity > 0){
        for(int i = 0; i<n+1; i++)
//        for(int i = 0; i<n; i++)
            cout<<fvar[i]<<endl;
    }
    TApplication theApp("App", &argc, argv);
    TFile * fmc = TFile::Open(mcInput.c_str());
    TFile * fdata = TFile::Open(dataInput.c_str());
    TH1D * data = (TH1D*)fdata->Get("cosTheta");
//    TH1D * data = (TH1D*)fdata->Get("cosTheta_PsuedoData");
    Histograms MCs;
    MCs.push_back((TH1D*)fmc->Get("cosTheta"));
    for(int i = 0; i< n; i++){
        stringstream s;
        s<<"CosThetaRW/cosThetaRW_"<<i;
        MCs.push_back((TH1D*)(fmc->Get(s.str().c_str())));
        cout<<MCs.at(i)<<endl;
    }

    

    cout<<"before endjob"<<endl;
    
    TFile * myFile = new TFile(string("ChiSquaredFunc_"+toy_plotFileName).c_str(), "recreate");
    myFile->cd();
    DataPointChiSquaredHandler myChiSquaredHandler("recoChi2",data,MCs,
                               fvar, 1000, "Both", 5);
    myChiSquaredHandler.Write(myFile);
    myFile->Write();
    myFile->Close();
    return 0;
}
