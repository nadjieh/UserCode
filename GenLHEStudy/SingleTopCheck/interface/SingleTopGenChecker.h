#ifndef SingleTopGenChecker_h
#define SingleTopGenChecker_h

//

//

//

//
//


#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "DataFormats/Common/interface/Handle.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"

#include <vector>

#include <string>
class TFile;
class TH1F;
class TH2F;
class TH1I;
class TProfile;
class TTree;

class SingleTopGenChecker : public edm::EDAnalyzer
{
 public:

  explicit SingleTopGenChecker(const edm::ParameterSet& conf);

  virtual ~SingleTopGenChecker();

  virtual void beginJob();
  virtual void endJob();
  virtual void analyze(const edm::Event& e, const edm::EventSetup& c);

 private:

  TFile * histfile_;
  std::string outputFile_;
  edm::InputTag mcTruthCollection_;
  TH1F * top_pt;

  TH1F * top_y;

  TH1F * W_pt;

  TH1F *  W_y;

  TH1F * q_pt;

  TH1F * q_y;

  TH1F * qasso_pt;

  TH1F * qasso_y;

  TH1F * qlight_pt;

  TH1F * qlight_y;
  TH1F * channels;
  TH1F * Kanals;


  int kanal1;

  int kanal2;

  int kanal3;




  int ud;

  int cs;

  int cd;

  int us;



  int n_ev;

 };

#endif




