 /*
 * Author: ajafari                                                                                                                              
 *                                                                                                                                              
 * Created on November 29, 2009, 8:55 PM                                                                                                        
 */


#ifndef _MUONHISTS_H
#define _MUOONHISTS_H

#include <iomanip>
#include "../../../TopBrussels/TopTreeProducer/interface/TRootMuon.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootElectron.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootJet.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootMET.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootGenEvent.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootEvent.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootRun.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootParticle.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootMCParticle.h"
#include <sstream>
    
#include <TFile.h>
#include <TH1.h>
#include <TH2.h> 
#include <TCanvas.h>
#include <TBranch.h>
#include <TString.h>
#include <TDirectory.h>
#include <TTree.h>
#include <TClonesArray.h>
#include <vector>
#include <string>

#include "KinematicHists.h"

using namespace TopTree;

class MuonHists{
 public:
     MuonHists(std::string name, int cone = 3): isoCone(cone){
          Name = name;
          kinHists = new KinematicHists<TRootMuon>(Name);
	  isGood = new TH1D((Name+"_isGlobal").c_str(),(Name+"_isGlobal").c_str(),2,0.,2.);
	  isGood->GetXaxis()->SetTitle("isGlobal");
	  relIso = new TH1D((Name+"_relIso").c_str(),(Name+"_relIso").c_str(),50,0.,2.);
	  relIso->GetXaxis()->SetTitle("#mu relative isolation");
	  nMV = new TH1D((Name+"_nMV").c_str(),(Name+"_nMu").c_str(),5,0.,5.);
	  nMV->GetXaxis()->SetTitle("N_{muons} selected");
	  d0 = new TH1D((Name+"_d0").c_str(),(Name+"_d0").c_str(),50,0.,0.2);
	  d0->GetXaxis()->SetTitle("d0");
     }
    virtual ~MuonHists(){};
    virtual void Fill(std::vector<TRootMuon> mu, int nVM = -1,double weight = 1){
	for(unsigned int i = 0; i<mu.size(); i++){
            kinHists->Fill(&(mu.at(i)),weight);
	    isGood->Fill(mu.at(i).isGlobalMuon(),weight);
            double RelIso=(mu.at(i).chargedHadronIso()+mu.at(i).neutralHadronIso()+mu.at(i).photonIso())/mu.at(i).Pt();
	    relIso->Fill(RelIso,weight);
            d0->Fill(fabs(mu.at(i).d0()));
            
	}
        nMV->Fill(nVM,weight);
    }
    virtual void WriteAll(TDirectory * dir){
        if (dir == 0)
            return;
        TDirectory* my_dir = dir->mkdir((Name+"_Muon").c_str());
        my_dir->cd();
	relIso->Write();
	isGood->Write();
	nMV->Write();
	d0->Write();
        kinHists->Write();

        dir->cd();
    }
  private:
     int isoCone;
     std::string Name;
     TH1D * isGood;
     TH1D * relIso;
     TH1D * nMV;
     TH1D * d0;
     KinematicHists<TRootMuon> * kinHists;
};
#endif


