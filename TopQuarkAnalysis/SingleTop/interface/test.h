#ifndef SingleTop_h
#define SingleTop_h

// -*- C++ -*-
//
// Package:    SingleTop
// Class:      SingleTop
//


// Original Author:  Andrea Giammanco



// system include files
#include <memory>
#include <fstream>

// user include files
#include "DataFormats/PatCandidates/interface/Particle.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"

using namespace std;
using namespace pat;
using namespace edm;
using namespace reco;

//
// class declaration
//

class SingleTop : public edm::EDProducer
{
public:
  explicit SingleTop(const edm::ParameterSet&);
  virtual ~SingleTop();
    
protected:
  virtual void beginJob(const edm::EventSetup&) ;
  virtual void produce( edm::Event&, const edm::EventSetup&);
  virtual void endJob() ;

  // ----------member data ---------------------------
  
  bool singleTopEvent_;  // true if event contains the right topology
  bool hasRealSolutions;

  unsigned int verbosity;
  double cutPtMinFirstMuon,cutPtMinLeptons,cutEtaFirstMuon,cutEtaLeptons,cutUpMTW;
  double cutPtMinCentralJets,cutPtMinForwardJets,cutBtag,cutEtaJets,cutMET,cutLowMTW;
  std::string btagAlgo;
  double cutCaloIso,cutTrackIso;
  double TransverseWmass(pat::Muon mu, math::XYZVector met);
  void createW(pat::Muon mu, math::XYZVector met, double & massWn, bool & hasRealSolutions );
  void createPzNu(pat::Muon mu, math::XYZVector met,double & pznu1, double & pznu2 , double & massWn, bool & hasRealSolutions );
  //const reco::GenParticle* GenW;
  pat::Particle* W;
  pat::Particle* WLessPzNu;
  pat::Particle* WMorePzNu;
  
  bool isCSA07Soup_;
  bool isFullSim_;
  // Physics objects handles
  edm::Handle<std::vector<pat::Muon> >     muonHandle_;
  edm::Handle<std::vector<pat::Electron> > electronHandle_;
  edm::Handle<std::vector<pat::Jet> >      jetHandle_;
  edm::Handle<std::vector<pat::MET> >      METHandle_;
};


#endif
