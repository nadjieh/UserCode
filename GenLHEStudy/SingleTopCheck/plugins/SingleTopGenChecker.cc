// -*- C++ -*-
//

// Class:      SingleTopGenChecker
//
/**\class SingleTopGenChecker 
*/

// user include files
#include "../interface/SingleTopGenChecker.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/HepMCCandidate/interface/GenParticleFwd.h"

#include <string>
#include <vector>
#include "TMath.h"
#include "TFile.h"
#include "TH1F.h"
#include "TH1I.h"
#include "TH2F.h"
#include "TProfile.h"
#include "TTree.h"
#include <iostream>

using namespace reco;
using namespace edm;
using namespace std;
SingleTopGenChecker::SingleTopGenChecker(const edm::ParameterSet& conf)
 {
  outputFile_ = conf.getParameter<std::string>("outputFile");
  histfile_ = new TFile(outputFile_.c_str(),"RECREATE");
  mcTruthCollection_ = conf.getParameter<edm::InputTag>("mcTruthCollection");

 }

void SingleTopGenChecker::beginJob(){

  histfile_->cd();

  // mc truth
  top_pt = new TH1F("top_pt","top_pt",100,0,300);

  top_y = new TH1F("top_y","top_y",100,-5,5);

  W_pt = new TH1F("W_pt","W_pt",100,0,300);

  W_y = new TH1F("W_y","W_y",100,-5,5);

  q_pt = new TH1F("q_pt","q_pt",100,0,300);

  q_y = new TH1F("q_y","q_y",100,-5,5);

  qasso_pt = new TH1F("qasso_pt","qasso_pt",100,0,300);

  qasso_y = new TH1F("qasso_y","qasso_y",100,-5,5);

  qlight_pt = new TH1F("qlight_pt","qlight_pt",100,0,300);

  qlight_y = new TH1F("qlight_y","qlight_y",100,-6,6);
  channels = new TH1F("WDecays","W-Decays",4,0,4);
  channels->GetXaxis()->SetBinLabel(1, "ud");
  channels->GetXaxis()->SetBinLabel(2, "cs");
  channels->GetXaxis()->SetBinLabel(3, "cd");
  channels->GetXaxis()->SetBinLabel(4, "us");
  Kanals = new TH1F("Channels","Channels",3,0,3);
  Kanals->GetXaxis()->SetBinLabel(1, "kanal1");
  Kanals->GetXaxis()->SetBinLabel(2, "kanal2");
  Kanals->GetXaxis()->SetBinLabel(3, "kanal3");

  kanal1=0;

  kanal2=0;

  kanal3=0;




  ud=0;

  cs=0;

  cd=0;

  us=0;



  n_ev=0;

}

void
SingleTopGenChecker::endJob(){

  histfile_->cd();

  top_pt->Write();

  top_y->Write();

  W_pt->Write();

  W_y->Write();

  q_pt->Write();

  q_y->Write();

  qasso_pt->Write();

  qasso_y->Write();

  qlight_pt->Write();

  qlight_y->Write(); 
  channels->SetBinContent(1,ud);
  channels->SetBinContent(2,cs);
  channels->SetBinContent(3,cd);
  channels->SetBinContent(4,us);
  channels->Write(); 
  Kanals->SetBinContent(1,kanal1);
  Kanals->SetBinContent(2,kanal2);
  Kanals->SetBinContent(3,kanal3);
  Kanals->Write();


}

SingleTopGenChecker::~SingleTopGenChecker()
{

  // do anything here that needs to be done at desctruction time
  // (e.g. close files, deallocate resources etc.)
  histfile_->Write();
  histfile_->Close();

}


//=========================================================================
// Main method
//=========================================================================

void
SingleTopGenChecker::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{


 
  edm::Handle<GenParticleCollection> genParticles;
  iEvent.getByLabel(mcTruthCollection_, genParticles);

  int top_charge=0;

  std::vector<int> W_daughters;
  int asso_index=-1;
  int myIndex = 0;
  for (reco::GenParticleCollection::const_iterator mcIter=genParticles->begin(); mcIter != genParticles->end(); mcIter++, myIndex++ ) {
	int pdgId = fabs(mcIter->pdgId());
	int motherId = fabs(mcIter->mother()->pdgId());
	int motherIdII = -1;
	if(mcIter->numberOfMothers() > 1 )
	        motherIdII=fabs(mcIter->mother(1)->pdgId());
	if(pdgId == 6){
		top_pt->Fill(mcIter->pt());

	  	top_y->Fill(mcIter->rapidity());

	  	if(mcIter->pdgId()>0)

	    		top_charge=1;

	  	else top_charge=-1;
	}
	if(pdgId == 24 && (motherId == 6 || motherIdII == 6)){ 

	  	W_pt->Fill(mcIter->pt());

	  	W_y->Fill(mcIter->rapidity());	

	}

	if(pdgId <6 && (motherId == 6 || motherIdII == 6)){ 
		q_pt->Fill(mcIter->pt());

		q_y->Fill(mcIter->rapidity());	

	}
	if(pdgId == 5 /*&& some condition*/){ 
		qasso_pt->Fill(mcIter->pt());

		qasso_y->Fill(mcIter->rapidity());
		asso_index = myIndex;			

	}
	if(motherId == 24 || motherIdII == 24){

		W_daughters.push_back(pdgId);

	}

  } // loop over mc particle

      //zaehle W-Toechter

	if(W_daughters.size()!=2){

		cerr<<"Bloedes W!!!"<<endl;

        }else{

		if(W_daughters[0]==1 && W_daughters[1]==2) ud++;

		if(W_daughters[0]==2 && W_daughters[1]==1) ud++;

		if(W_daughters[0]==3 && W_daughters[1]==4) cs++;

		if(W_daughters[0]==4 && W_daughters[1]==3) cs++;

		if(W_daughters[0]==1 && W_daughters[1]==4) cd++;

		if(W_daughters[0]==4 && W_daughters[1]==1) cd++;

		if(W_daughters[0]==2 && W_daughters[1]==3) us++;

		if(W_daughters[0]==3 && W_daughters[1]==2) us++;

	}



	//finde leichtes Quark fuer Ereignisse mit second "b"
      myIndex = 0;

      if(asso_index>=0){

	kanal1++;

	for(reco::GenParticleCollection::const_iterator mcIter=genParticles->begin(); mcIter != genParticles->end(); mcIter++, myIndex++){

	  if(myIndex==asso_index) continue;



	  if(abs(mcIter->pdgId())<6 /*&& some condition*/){

	    qlight_pt->Fill(mcIter->pt());

	    qlight_y->Fill(mcIter->rapidity());	

	  }

	}

      }

      //leichtes Quark in 2->2

	else { 
		reco::GenParticleCollection::const_iterator myItr = genParticles->begin();
		if(myItr->pdgId() != 21 && (myItr++)->pdgId() != 21){

			kanal2++;
			myIndex = 0;

			for(reco::GenParticleCollection::const_iterator mcIter=genParticles->begin(); 
			mcIter != genParticles->end(); mcIter++, myIndex++){

				if(abs(mcIter->pdgId())<6 /*&& some condition*/){

					qlight_pt->Fill(mcIter->pt());

					qlight_y->Fill(mcIter->rapidity());	

				}

			}

	      	}else{
                	kanal3++;
        	}
	}
}


DEFINE_FWK_MODULE(SingleTopGenChecker);
