#include "FWCore/Framework/interface/EDFilter.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Utilities/interface/InputTag.h"
class BaseLineSingleTopFilter : public edm::EDFilter{
 public:

  BaseLineSingleTopFilter(const edm::ParameterSet& conf);

  virtual ~BaseLineSingleTopFilter(){};

  virtual void beginJob();
  virtual void endJob();
  virtual bool filter(edm::Event & e, edm::EventSetup const& c);
 private:
  double jetPtCut;
  double muPtCut;
  double jetEtaCut;
  double muEtaCut;
  int nSelectedJets;
  int nSelectedMu;
  bool applyMTcut;
  double MTCut; 
  edm::InputTag muonTag;
  edm::InputTag jetTag;
  edm::InputTag METTag;
 };
