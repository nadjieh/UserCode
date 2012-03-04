#include "../interface/BaseLineSingleTopFilter.h"
#include <iostream>
#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/MuonReco/interface/Muon.h"
#include "DataFormats/JetReco/interface/PFJet.h"
#include "DataFormats/METReco/interface/PFMET.h"
BaseLineSingleTopFilter::BaseLineSingleTopFilter(const edm::ParameterSet& ps){
  jetPtCut=ps.getParameter<double>("jetPtCut");
  muPtCut=ps.getParameter<double>("muPtCut");
  jetEtaCut=ps.getParameter<double>("jetEtaCut");
  muEtaCut=ps.getParameter<double>("muEtaCut");
  nSelectedJets=ps.getParameter<int>("nSelectedJets");
  nSelectedMu=ps.getParameter<int>("nSelectedMu");
  applyMTcut=ps.getParameter<bool>("applyMTcut");
  MTCut=ps.getParameter<double>("MTCut");
  muonTag=ps.getParameter<edm::InputTag>("muons");
  jetTag=ps.getParameter<edm::InputTag>("jets");
  METTag=ps.getParameter<edm::InputTag>("met");


}
void BaseLineSingleTopFilter::beginJob(){} 
void BaseLineSingleTopFilter::endJob(){} 
bool BaseLineSingleTopFilter::filter(edm::Event & e, edm::EventSetup const& c){
	edm::Handle< edm::View<reco::Muon> > muHandle;
	e.getByLabel(muonTag,muHandle);
	edm::View<reco::Muon> muons = *muHandle;

	edm::Handle< edm::View<reco::PFJet> > jetHandle;
	e.getByLabel(jetTag,jetHandle);
	edm::View<reco::PFJet> jets = *jetHandle;

	edm::Handle< edm::View<reco::PFMET> > metHandle;
	e.getByLabel(METTag,metHandle);
	edm::View<reco::PFMET> met = *metHandle;

	int nMu = 0;
	edm::View<reco::Muon>::const_iterator selectedMuon;
	for (edm::View<reco::Muon>::const_iterator iMuon = muons.begin(); iMuon != muons.end(); ++iMuon) {
	//	std::cout<<"mu pt: "<<iMuon->pt()<<", mu eta: "<<fabs(iMuon->eta())<<std::endl;
		if(iMuon->pt() > muPtCut && fabs(iMuon->eta()) < muEtaCut){
	//		std::cout<<"Selected muon number "<<nMu+1<<std::endl;
			selectedMuon =iMuon;
			nMu++;
		}
	}

	if(nMu != nSelectedMu){
	//	std::cout<<"fail mu selection"<<std::endl;
		return false;
	}//else{std::cout<<"pass mu selection"<<std::endl;}
	int nJet = 0;
	for (edm::View<reco::PFJet>::const_iterator iJet = jets.begin(); iJet != jets.end(); ++iJet) {
		if(iJet->pt() > jetPtCut && fabs(iJet->eta()) < jetEtaCut)
			nJet++;
	}

	if(nJet != nSelectedJets)
		return false;

	double MT = 10000;
        if(applyMTcut){
        	edm::View<reco::PFMET>::const_iterator iMET = met.begin(); 
		double metT = sqrt(iMET->px()*iMET->px()+iMET->py()*iMET->py());
		double muT = sqrt(selectedMuon->px()*selectedMuon->px()+selectedMuon->py()*selectedMuon->py());
		MT = sqrt(pow(muT+metT,2)-pow((selectedMuon->px()+iMET->px()),2)-pow((selectedMuon->py()+iMET->py()),2));
		if( MT < MTCut)
			return false;
	}
	return true;
}

DEFINE_FWK_MODULE(BaseLineSingleTopFilter); 
