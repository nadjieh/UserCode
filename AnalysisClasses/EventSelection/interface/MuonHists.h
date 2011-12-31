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
#include "../../../TopBrussels/TopTreeProducer/interface/TRootSignalEvent.h"
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
	  relIso = new TH1D((Name+"_relIso").c_str(),(Name+"_relIso").c_str(),10,0.,2.);
	  relIso->GetXaxis()->SetTitle("#mu relative isolation");
	  nMV = new TH1D((Name+"_nMV").c_str(),(Name+"_nMu").c_str(),5,0.,5.);
	  nMV->GetXaxis()->SetTitle("N_{muons} for veto");
     }
    virtual ~MuonHists(){};
    virtual void Fill(std::vector<TRootMuon> mu, int nVM = -1){
	for(unsigned int i = 0; i<mu.size(); i++){
            kinHists->Fill(&(mu.at(i)));
	    isGood->Fill(mu.at(i).isGlobalMuon());
	    relIso->Fill((mu.at(i).isoR03_sumPt()+mu.at(i).isoR03_emEt()+mu.at(i).isoR03_hadEt())/mu.at(i).Pt());
	}
        nMV->Fill(nVM);
    }
    virtual void WriteAll(TDirectory * dir){
        if (dir == 0)
            return;
        TDirectory* my_dir = dir->mkdir((Name+"_Electron").c_str());
        my_dir->cd();
	relIso->Write();
	isGood->Write();
	nMV->Write();
        kinHists->Write();

        dir->cd();
    }
  private:
     int isoCone;
     std::string Name;
     TH1D * isGood;
     TH1D * relIso;
     TH1D * nMV;
     KinematicHists<TRootMuon> * kinHists;
};
#endif


