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

    TH1*  data = 0;
    TH1*  bkginsignal = 0; //for t-processes other than munub
    TH1*  bkg = 0; // for non-t processes
    std::vector<TH2*>  signalIID; // for munub t-processes
    TH1* signal = 0; // for dij = delta_ij rec-gen matrix.
    TFile * file = 0;
    bool singleMatrix = false;
    bool is2Drecgen = false;
    for (int f = 1; f < argc; f++) {
        std::string arg_fth(*(argv + f));
        if (arg_fth == "signal") {
            f++;
            std::string out(*(argv + f));
            file = new TFile(out.c_str(),"read");
//                cout<<"signal: "<<out<<endl;
            signalIID.push_back ((TH2*)file->Get("Default/DefaultcosTheta2D"));
//            signalIID.push_back ((TH2*)file->Get("DefaultTrue/DefaultTruecosTheta2D"));
            cout<<signalIID.at(signalIID.size()-1)->GetEntries()<<endl;
            if (bkginsignal == 0)
                bkginsignal = ((TH1*)file->Get("Default/DefaultcosTheta"));
//                bkginsignal = ((TH1*)file->Get("DefaultTrue/DefaultTruecosTheta"));
            else
                bkginsignal->Add((TH1*)file->Get("Default/DefaultcosTheta"));
//                bkginsignal->Add((TH1*)file->Get("DefaultTrue/DefaultTruecosTheta"));
//            delete file;
        }else if(arg_fth == "data"){
            f++;
            std::string out(*(argv + f));
            file = new TFile(out.c_str(),"read");
                cout<<"data"<<endl;
            data = ((TH1*)file->Get("Default/DefaultcosTheta"));
//            data = ((TH1*)file->Get("DefaultTrue/DefaultTruecosTheta"));
//            delete file;
        }else if (arg_fth == "bkg") {
            f++;
            std::string out(*(argv + f));
            file = new TFile(out.c_str(),"read");
		cout<<"bkg"<<endl;
            bkg = ((TH1*)file->Get("Default/DefaultcosTheta"));
//            bkg = ((TH1*)file->Get("DefaultTrue/DefaultTruecosTheta"));
//            delete file;
        }else if (arg_fth == "singleMatrix") {
            f++;
                cout<<"singleMatrix"<<endl;
            std::string out(*(argv + f));
            if(out == "true")
                singleMatrix = true;
        }else if (arg_fth == "is2Drecgen") {
            f++;
                cout<<"is2Drecgen"<<endl;
            std::string out(*(argv + f));
            if(out == "yes" || out == "Yes" || out == "Y" || out == "y"
               || out == "YES")
                is2Drecgen = true;
        }
    }

    double x[3] = {-1.,-1.,-1};
    double xerr[3] = {-1.,-1.,-1};
    double correlation;
    if(is2Drecgen && !singleMatrix){
        
        cout<<"In Generalized fit: \n\tsize of signal is "<<signalIID.size()<<endl;
        if(bkg != NULL && bkginsignal != NULL)
            bkg->Add(bkginsignal);        
        std::pair<TF3,LikelihoodFunction*>  myLL = LikelihoodFunction::getLLFunctionGeneralized("LL" , bkg , data , signalIID);
        myLL.first.GetMinimumXYZ(x[0] , x[1] , x[2]);
        cout<<"simple getMin: "<<x[0]<<"  "<<x[1]<<"  "<<x[2]<<endl;
        GetMinimum(myLL.first,x,xerr,correlation);
        delete myLL.second;
        
    }else if(is2Drecgen && singleMatrix){
        
        if(bkg != NULL && bkginsignal != NULL)
            bkg->Add(bkginsignal);        
        TH2* SingMSignal = 0;
        for(unsigned int p = 0; p < signalIID.size(); p++ ){
            if(SingMSignal == 0)
                SingMSignal = signalIID.at(p);
            else
                SingMSignal->Add(signalIID.at(p));
        }            
        std::pair<TF3,LikelihoodFunction*> myLL = LikelihoodFunction::getLLFunction("LL", bkg, data, SingMSignal,true);
        myLL.first.GetMinimumXYZ(x[0] , x[1] , x[2]);
        cout<<"simple getMin: "<<x[0]<<"  "<<x[1]<<"  "<<x[2]<<endl;
        GetMinimum(myLL.first,x,xerr,correlation);    
        
        delete myLL.second;
    }else if(!is2Drecgen){
        
        TH1* Signal1D = 0;
        stringstream s;
        for(unsigned int p = 0; p < signalIID.size(); p++ ){
            s.str("");
            s<<p<<"_pY";
            if(Signal1D == 0)
                Signal1D = (TH1*)signalIID.at(p)->ProjectionY(s.str().c_str());
            else
                Signal1D->Add((TH1*)signalIID.at(p)->ProjectionY(s.str().c_str()));
        }
        if(bkginsignal != NULL)
//            bkg->Add(bkginsignal);        
            Signal1D->Add(bkginsignal);        
        std::pair<TF3,LikelihoodFunction*>  myLL = LikelihoodFunction::getLLFunction("LL" , bkg , data , Signal1D);
        myLL.first.GetMinimumXYZ(x[0] , x[1] , x[2]);
        cout<<"simple getMin: "<<x[0]<<"  "<<x[1]<<"  "<<x[2]<<endl;
        GetMinimum(myLL.first,x,xerr,correlation);
        delete myLL.second;
    }
//    std::pair<TF3,ChiSquaredFunction*> myChi2 = ChiSquaredFunction::getChiSquaredFunction("Chi2" , bkg , data , signal);
//    myChi2.first.GetMinimumXYZ(x[0] , x[1] , x[2]);
    
//    GetMinimum(myChi2.first,x,xerr,correlation);
    cout<<"my getMin-vals: "<<x[0]<<"  "<<x[1]<<"  "<<x[2]<<endl;
    cout<<"my getMin-err: "<<xerr[0]<<"  "<<xerr[1]<<"  "<<xerr[2]<<endl;
    cout<<"F0_FNeg correlation: "<<correlation/(double)(xerr[0]*xerr[1])<<endl;
    
//    delete myChi2.second;
    return 0;
}
