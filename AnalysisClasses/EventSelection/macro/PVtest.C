/* 
 * File:   SelectAndSave.c
 * Author: ajafari
 *
 * Created on August 6, 2010, 8:18 PM
 */

#include <stdio.h>
#include <stdlib.h>

//#include "../interface/Cut.h"
//#include "../interface/Cut.h"
#include "../interface/ElectronSelector.h"

#include "../interface/Event.h"
//#include "../interface/EventsHists.h"
#include "../interface/ElectronHists.h"
#include "../interface/MuonHists.h"
#include "../interface/PVHists.h"
#include "../interface/JetHists.h"
#include "../interface/JetSelector.h"
#include "../interface/MuonVetoSelector.h"
//#include "../interface/NoSelection.h"
#include "../interface/PrimaryVertexSelector.h"
#include "../interface/EventSelector.h"
#include <iomanip>
#include "/user/ajafari/CMSSW_3_8_5_patch3/src/TopBrussels/TopTreeProducer/interface/TRootMuon.h"
#include "/user/ajafari/CMSSW_3_8_5_patch3/src/TopBrussels/TopTreeProducer/interface/TRootElectron.h"
#include "/user/ajafari/CMSSW_3_8_5_patch3/src/TopBrussels/TopTreeProducer/interface/TRootJet.h"
#include "/user/ajafari/CMSSW_3_8_5_patch3/src/TopBrussels/TopTreeProducer/interface/TRootCaloJet.h"
#include "/user/ajafari/CMSSW_3_8_5_patch3/src/TopBrussels/TopTreeProducer/interface/TRootMET.h"
#include "/user/ajafari/CMSSW_3_8_5_patch3/src/TopBrussels/TopTreeProducer/interface/TRootGenEvent.h"
#include "/user/ajafari/CMSSW_3_8_5_patch3/src/TopBrussels/TopTreeProducer/interface/TRootNPGenEvent.h"
#include "/user/ajafari/CMSSW_3_8_5_patch3/src/TopBrussels/TopTreeProducer/interface/TRootSignalEvent.h"
#include "/user/ajafari/CMSSW_3_8_5_patch3/src/TopBrussels/TopTreeProducer/interface/TRootEvent.h"
#include "/user/ajafari/CMSSW_3_8_5_patch3/src/TopBrussels/TopTreeProducer/interface/TRootRun.h"
#include "/user/ajafari/CMSSW_3_8_5_patch3/src/TopBrussels/TopTreeProducer/interface/TRootParticle.h"
#include "/user/ajafari/CMSSW_3_8_5_patch3/src/TopBrussels/TopTreeProducer/interface/TRootMCParticle.h"
#include "/user/ajafari/CMSSW_3_8_5_patch3/src/TopBrussels/TopTreeProducer/interface/TRootVertex.h"
#include "/user/ajafari/CMSSW_3_8_5_patch3/src/TopBrussels/TopTreeProducer/interface/TRootHLTInfo.h"
#include "/user/ajafari/CMSSW_3_8_5_patch3/src/AnalysisClasses/EventSelection/interface/PracticalEvent.h"
#include "/user/ajafari/CMSSW_3_8_5_patch3/src/AnalysisClasses/EventSelection/interface/EventPropertiesHist.h"



#include <sstream>
#include <string>

#include <TFile.h>
#include <TH1.h>
#include <TH2.h>
#include <TCanvas.h>
#include <TBranch.h>
#include <TTree.h>
#include <vector>

using namespace std;
using namespace TopTree;
//EventHists sas_beforSelection("beforSelection");
//EventHists sas_HLT("HLTSelection");

PVHists sas_atLeastOnGPV("before_PV_selection");
EventPropertiesHist sas_evtProps("before_GE_eventProperties");




int myverbosity;
bool doFill;
TFile * myout;
TTree * myFinalTree;
TH1D * trkRatio;
std::vector<std::string> myinfilenames;
std::string myoutFileName;
std::string myplots;
std::string myoutFileName_FullSelection;

void beginJob(){
     myverbosity = 0;
     doFill = false;

}



void endJob(){
    TFile * plots = new TFile(myplots.c_str(),"recreate");
    plots->cd();
    sas_evtProps.WriteAll(plots);
    sas_atLeastOnGPV.WriteAll(plots);
    trkRatio->Write();
    plots->Write();
    plots->Close();


}

int main(int argc, char** argv){

    for (int f = 1; f < argc; f++) {
        std::string arg_fth(*(argv + f));

        if (arg_fth == "out") {
          f++;
          std::string out(*(argv + f));
          myoutFileName_FullSelection = out;
//	  myplots = "Histograms_"+out;
	  myplots = out;
        }else if (arg_fth == "input") {
          f++;
          std::string in(*(argv + f));
          myinfilenames.push_back(string("~/"+in));

        }
    }

    trkRatio = new TH1D("trkRatio","",100,0.,1.);
    trkRatio->GetXaxis()->SetTitle("High Purity track content of event");

   cout << myinfilenames.at(0).c_str() << endl;


    TFile* f = 0;

    beginJob();


    for(unsigned int fNumber = 0; fNumber<myinfilenames.size(); fNumber++){
    
    f = TFile::Open(myinfilenames.at(fNumber).c_str());

    TTree* runTree = (TTree*) f->Get("runTree");
    TTree* eventTree = (TTree*) f->Get("eventTree");

    PracticalEvent * pracEvt = new PracticalEvent(eventTree,runTree,true);
    pracEvt->eventTree->SetBranchStatus("*", 1);


    if(doFill ){
	stringstream s("");
	s<<(fNumber+1)<<"_"<<myoutFileName_FullSelection;
        myout = new TFile(s.str().c_str(), "recreate");
        myout->cd();
        myFinalTree = pracEvt->eventTree->CloneTree(0);
    }

    std::cout<<"beforeLoop"<<std::endl;

   int ievt = 0;
   bool onepassed = false;
    while (pracEvt->Next()) {
	ievt++;
//        if(ievt>100)
//	    break;
        std::vector<TRootCaloJet>  myJets_;
        myJets_.clear();
        bool isBeamBG = true;
        float nTrk = ( (float) (pracEvt->Event()->nTracks()) );
        float nPureTrk  = ( (float)  (pracEvt->Event()->nHighPurityTracks()) );
       if(nTrk > 10)
       {
         if( ( (float) nPureTrk ) / ( (float)nTrk ) > 0.25 ){
           isBeamBG = false;
	}
       }
       trkRatio->Fill(( (float) nPureTrk ) / ( (float)nTrk ));
       if(isBeamBG) {
	   //cout<<"HERE!\t"<<( (float) nPureTrk ) / ( (float)nTrk )<<"\t"<<nTrk<<"\t"<<ievt<<endl;
         continue;
        }

        Event myEvent_tmp( *pracEvt->VertexCollection());
        myEvent_tmp.verbose(myverbosity);
        if(myverbosity > 0)
            cout<<"Vertex Makers ---------------------------------------------------------------------"<<endl;
        myEvent_tmp.SpecialVertexMaker();
// 	cout<<"All primary vertices: "      <<myEvent_tmp.pvs.size()<<endl;
        if(myverbosity > 0)
            cout<<"START TO SELECT : "<<endl;
        sas_atLeastOnGPV.Fill(myEvent_tmp.Gpvs,myEvent_tmp.Gpvs.size());
        sas_evtProps.Fill(pracEvt->Event());
	if(doFill)
            myFinalTree->Fill();
        onepassed = true;
        
    }

        cout<<"before closing file input "<<f->GetName()<<endl;
        f->Close();
        delete f;

	if(doFill){
            myout->cd();
            myout->Write();
            myout->Close();
        }
    }
        endJob();
	return 0;
}
