#include "JetMETCorrections/Objects/interface/JetCorrectionsRecord.h"
#include "DataFormats/JetReco/interface/CaloJet.h"
#include "DataFormats/BTauReco/interface/JetTag.h"
#include "DataFormats/JetReco/interface/PFJet.h"
#include "DQM/Physics/src/TopSingleLeptonTriggerObjectDQM.h"
#include "DataFormats/Math/interface/deltaR.h"
#include <iostream>
#include "FWCore/Common/interface/TriggerNames.h"
#include "FWCore/Common/interface/TriggerResultsByName.h"
#include <cassert>

  using namespace std;
  using namespace edm;
  using namespace reco;
  using namespace trigger;
namespace TopSingleLepton {

  // maximal number of leading jets 
  // to be used for top mass estimate
  static const unsigned int MAXJETS = 4;
  // nominal mass of the W boson to 
  // be used for the top mass estimate
  static const double WMASS = 80.4;

  TOMonitorEnsemble::TOMonitorEnsemble(const char* label, const edm::ParameterSet& cfg) : 
    label_(label), elecIso_(0), elecSelect_(0), pvSelect_(0), muonIso_(0), muonSelect_(0), jetIDSelect_(0), includeBTag_(false), lowerEdge_(-1.), upperEdge_(-1.), logged_(0)
  {
    // sources have to be given; this PSet is not optional
    edm::ParameterSet sources=cfg.getParameter<edm::ParameterSet>("sources");
    muons_= sources.getParameter<edm::InputTag>("muons");
    elecs_= sources.getParameter<edm::InputTag>("elecs");
    jets_ = sources.getParameter<edm::InputTag>("jets" );
    mets_ = sources.getParameter<std::vector<edm::InputTag> >("mets" );
    pvs_ = sources.getParameter<edm::InputTag>("pvs" );
    if( cfg.existsAs<edm::ParameterSet>("triggerInputs") ){
      edm::ParameterSet triggerInputs=cfg.getParameter<edm::ParameterSet>("triggerInputs");
      triggerTable_=triggerInputs.getParameter<edm::InputTag>("triggerResults");
      triggerEvent_=triggerInputs.getParameter<edm::InputTag>("triggerEvent");
      triggerPaths_=triggerInputs.getParameter<std::string>("paths");
      processName_=triggerInputs.getParameter<std::string>("processName");
    }

    // setup the verbosity level for booking histograms;
    // per default the verbosity level will be set to 
    // STANDARD. This will also be the chosen level in
    // the case when the monitoring PSet is not found
    verbosity_=STANDARD;
    if( cfg.existsAs<edm::ParameterSet>("monitoring") ){
      edm::ParameterSet monitoring=cfg.getParameter<edm::ParameterSet>("monitoring");
      if(monitoring.getParameter<std::string>("verbosity") == "DEBUG"   )
	verbosity_= DEBUG;
      if(monitoring.getParameter<std::string>("verbosity") == "VERBOSE" )
	verbosity_= VERBOSE;
      if(monitoring.getParameter<std::string>("verbosity") == "STANDARD")
	verbosity_= STANDARD;
    }
    // and don't forget to do the histogram booking
    book(cfg.getParameter<std::string>("directory"));
  }

  void 
  TOMonitorEnsemble::book(std::string directory)
  {
    //set up the current directory path
    std::string current(directory); current+=label_;
    store_=edm::Service<DQMStore>().operator->();
    store_->setCurrentFolder(current);

    // determine number of bins for trigger monitoring
//    unsigned int nPaths=triggerPaths_.size();
    unsigned int nPaths=1;

    // --- [STANDARD] --- //
    // pt of the trigger objects 
    hists_["triggerMuonPt_"] = store_->book1D("triggerMuonPt", "p^{#mu}_{T}",     50,     0.,    250.);  
    hists_["triggerJetPt_"] = store_->book1D("triggerJetPt", "p^{jet}_{T}",     50,     0.,    250.);  
    hists_["triggerElectronPt_"] = store_->book1D("triggerElectronPt", "p^{e}_{T}",     50,     0.,    250.);  
    // trigger efficiency for different input paths
    hists_["triggerEff_" ] = store_->book1D("TriggerEff" , "Eff(trigger)"     , nPaths,     0.,  nPaths);
    // monitored trigger occupancy for single lepton triggers
    hists_["triggerMon_" ] = store_->book1D("TriggerMon" , "Mon(trigger)"     , nPaths,     0.,  nPaths);

    // set bin labels for trigger monitoring
    triggerBinLabels(std::string("trigger"), triggerPaths_);

    if( verbosity_==STANDARD) return;

    // --- [VERBOSE] --- //
    // eta of the trigger object for the first trigger path
    hists_["triggerMuonEta_"] = store_->book1D("triggerMuonEta", "#eta(#mu)",     50,     0.,    250.);  
    hists_["triggerJetEta_"] = store_->book1D("triggerJetEta", "#eta(jet)",     50,     0.,    250.);  
    hists_["triggerElectronEta_"] = store_->book1D("triggerElectronEta", "#eta(e)",     50,     0.,    250.);  
    if( verbosity_==VERBOSE) return;

   
  }
TriggerObjectCollection TOMonitorEnsemble::getTriggerObjectCollection(const edm::Handle<edm::TriggerResults> triggerResultsHandle_, const edm::Handle<trigger::TriggerEvent> triggerEventHandle_ , const unsigned int triggerIndex) {





  TriggerObjectCollection results;

  // modules on this trigger path
  const unsigned int m(hltConfig_.size(triggerIndex));
  const vector<string>& moduleLabels(hltConfig_.moduleLabels(triggerIndex));
  // Results from TriggerResults product
  const unsigned int moduleIndex(triggerResultsHandle_->index(triggerIndex));
  assert (moduleIndex<m);
  // Results from TriggerEvent product - Attention: must look only for
  // modules actually run in this path for this event!
    int j = moduleIndex; //needed to be the last active module
    const string& moduleLabel1(moduleLabels[j]);
    if(moduleLabel1 == "hltBoolEnd")
	j = moduleIndex-1;
    const string& moduleLabel( moduleLabels[j]);
    
    const string  moduleType(hltConfig_.moduleType(moduleLabel));
    // check whether the module is packed up in TriggerEvent product
    const unsigned int filterIndex(triggerEventHandle_->filterIndex(InputTag(moduleLabel,"",processName_)));
    if (filterIndex<triggerEventHandle_->sizeFilters()) {
      const Vids& VIDS (triggerEventHandle_->filterIds(filterIndex));
      const Keys& KEYS(triggerEventHandle_->filterKeys(filterIndex));
      const size_type nI(VIDS.size());
      const size_type nK(KEYS.size());
      assert(nI==nK);
      const size_type n(max(nI,nK));
      const TriggerObjectCollection& TOC(triggerEventHandle_->getObjects());
      for (size_type i=0; i!=n; ++i) {
        const TriggerObject& TO(TOC[KEYS[i]]);
//        cout << "   " << i << " " << VIDS[i] << "/" << KEYS[i] << ": "
//             << TO.id() << " " << TO.pt() << " " << TO.eta() << " " << TO.phi() << " " << TO.mass()
//             << endl;
	results.push_back(TO);
      }
    }

   return results;
 
}
  void 
  TOMonitorEnsemble::fill(const edm::Event& event, const edm::EventSetup& setup)
  {

  // fetch trigger event if configured such 
    edm::Handle<edm::TriggerResults> triggerTable;
    if(!triggerTable_.label().empty()) {
      if( !event.getByLabel(triggerTable_, triggerTable) ) {
        cout << "HLTEventAnalyzerAOD::analyze: Error in getting TriggerResults product from Event!" << endl;
        return;
      }
    }
    edm::Handle<trigger::TriggerEvent> triggerEvent;
    if(!triggerEvent_.label().empty()) {
       if(!event.getByLabel(triggerEvent_,triggerEvent)){
        cout << "HLTEventAnalyzerAOD::analyze: Error in getting TriggerEvent product from Event!" << endl;
        return;
       }
    }
    // sanity check
    assert(triggerTable->size()==hltConfig_.size());

    const unsigned int n(hltConfig_.size());
    const unsigned int triggerIndex(hltConfig_.triggerIndex(triggerPaths_));
    assert(triggerIndex==event.triggerNames(*triggerTable).triggerIndex(triggerPaths_));

    // abort on invalid trigger name
    if (triggerIndex>=n) {
       cout << "HLTEventAnalyzerAOD::analyzeTrigger: path "
         << triggerPaths_ << " - not found! " << endl;
       return ;
    }
  

    /* 
    ------------------------------------------------------------

    Trigger Object Monitoring

    ------------------------------------------------------------
    */

    // finding the trigger object of the desired path
    TriggerObjectCollection TOS = getTriggerObjectCollection(triggerTable,triggerEvent,triggerIndex);
    for(unsigned int i =0; i<TOS.size(); i++){
	if(fabs(TOS[i].id()) == 13){
            fill("triggerMuonPt_",  TOS[i].pt()   );
            fill("triggerMuonEta",  TOS[i].eta()  );
	}else if(fabs(TOS[i].id()) < 6 && fabs(TOS[i].id()) > 0){
            fill("triggerJetPt_",  TOS[i].pt()   );
            fill("triggerJetEta",  TOS[i].eta()  );
	}else if(fabs(TOS[i].id()) == 11){
            fill("triggerElectronPt_",  TOS[i].pt()   );
            fill("triggerElectronEta",  TOS[i].eta()  );
	}
    }
    

    /* 
    ------------------------------------------------------------

    Event Monitoring for trigger efficiency

    ------------------------------------------------------------
    */
    if((lowerEdge_==-1. && upperEdge_==-1.)) {
        if(!triggerTable_.label().empty()) fill(event, *triggerTable, "trigger", triggerPaths_);
    }

  }
  
}


TopSingleLeptonTriggerObjectDQM::TopSingleLeptonTriggerObjectDQM(const edm::ParameterSet& cfg): triggerTable_(""), vertexSelect_(0), beamspot_(""), beamspotSelect_(0)
{ 
  // configuration for HLTconfig based on HLT path and the process name
  if( cfg.existsAs<edm::ParameterSet>("setup") ){
      edm::ParameterSet setup=cfg.getParameter<edm::ParameterSet>("setup");
      if( setup.existsAs<edm::ParameterSet>("triggerInputs") ){
          edm::ParameterSet triggerInputs=setup.getParameter<edm::ParameterSet>("triggerInputs");
          triggerTable_=triggerInputs.getParameter<edm::InputTag>("triggerResults");
          triggerEvent_=triggerInputs.getParameter<edm::InputTag>("triggerEvent");
          triggerPaths_=triggerInputs.getParameter<std::string>("paths");
          processName_=triggerInputs.getParameter<std::string>("processName");
      }
  }
  // configure preselection
  edm::ParameterSet presel=cfg.getParameter<edm::ParameterSet>("preselection");
  if( presel.existsAs<edm::ParameterSet>("vertex" ) ){
    edm::ParameterSet vertex=presel.getParameter<edm::ParameterSet>("vertex");
    vertex_= vertex.getParameter<edm::InputTag>("src");
    vertexSelect_= new StringCutObjectSelector<reco::Vertex>(vertex.getParameter<std::string>("select"));
  }
  if( presel.existsAs<edm::ParameterSet>("beamspot" ) ){
    edm::ParameterSet beamspot=presel.getParameter<edm::ParameterSet>("beamspot");
    beamspot_= beamspot.getParameter<edm::InputTag>("src");
    beamspotSelect_= new StringCutObjectSelector<reco::BeamSpot>(beamspot.getParameter<std::string>("select"));
  }

  // conifgure the selection
  std::vector<edm::ParameterSet> sel=cfg.getParameter<std::vector<edm::ParameterSet> >("selection");
  for(unsigned int i=0; i<sel.size(); ++i){
    selectionOrder_.push_back(sel.at(i).getParameter<std::string>("label"));
    selection_[selectionStep(selectionOrder_.back())] = std::make_pair(sel.at(i), new TopSingleLepton::TOMonitorEnsemble(selectionStep(selectionOrder_.back()).c_str(), cfg.getParameter<edm::ParameterSet>("setup")));
  }
}
  
void TopSingleLeptonTriggerObjectDQM::beginRun(edm::Run const & iRun, edm::EventSetup const& iSetup)
{
  using namespace std;
  using namespace edm;

  bool changed(true);
  if (hltConfig_.init(iRun,iSetup,processName_,changed)) {
    if (changed) {
      // check if trigger name in (new) config
      if (triggerPaths_!="@") { // "@" means: analyze all triggers in config
        const unsigned int n(hltConfig_.size());
        const unsigned int triggerIndex(hltConfig_.triggerIndex(triggerPaths_));
        if (triggerIndex>=n) {
          cout << "HLTEventAnalyzerAOD::analyze:"
               << " TriggerName " << triggerPaths_
               << " not available in (new) config!" << endl;
          cout << "Available TriggerNames are: " << endl;
          hltConfig_.dump("Triggers");
        }
      }
//        hltConfig_.dump("Triggers");
  //    hltConfig_.dump("Streams");
  //    hltConfig_.dump("Datasets");
  //    hltConfig_.dump("PrescaleTable");
  //    hltConfig_.dump("ProcessPSet");
    }
  } else {
    cout << "HLTEventAnalyzerAOD::analyze:"
         << " config extraction failure with process name "
         << processName_ << endl;
  }
}


void 
TopSingleLeptonTriggerObjectDQM::analyze(const edm::Event& event, const edm::EventSetup& setup)
{ 


  if(!beamspot_.label().empty()){
    edm::Handle<reco::BeamSpot> beamspot;
    if( !event.getByLabel(beamspot_, beamspot) ) return;
    if(!(*beamspotSelect_)(*beamspot)) return;
  }
  // apply selection steps
  unsigned int passed=0;
  for(std::vector<std::string>::const_iterator selIt=selectionOrder_.begin(); selIt!=selectionOrder_.end(); ++selIt){
    std::string key = selectionStep(*selIt), type = objectType(*selIt);
    if(selection_.find(key)!=selection_.end()){
      selection_[key].second->setInitiatedHLTConfig(TopSingleLeptonTriggerObjectDQM::getInitiatedHLTConfig());
      if(type=="empty"){
	selection_[key].second->fill(event, setup);
      }
      if(type=="muons"){
	SelectionStep<reco::Muon> step(selection_[key].first);
	if(step.select(event)){ ++passed;
	  selection_[key].second->fill(event, setup);
	} else break;
      }
      if(type=="elecs"){
	SelectionStep<reco::GsfElectron> step(selection_[key].first);
	if(step.select(event)){ ++passed;
	  selection_[key].second->fill(event, setup);
	} else break;
      }
      if(type=="pvs" ){
	SelectionStep<reco::Vertex> step(selection_[key].first);
	if(step.selectVertex(event)){ ++passed;
	  selection_[key].second->fill(event, setup);
	} else break;
      }
      if(type=="jets" ){
	SelectionStep<reco::Jet> step(selection_[key].first);
	if(step.select(event, setup)){ ++passed;
	  selection_[key].second->fill(event, setup);
	} else break;
      }
      if(type=="jets/pf" ){
	SelectionStep<reco::PFJet> step(selection_[key].first);
	if(step.select(event, setup)){ ++passed;
	  selection_[key].second->fill(event, setup);
	} else break;
      }
      if(type=="jets/calo" ){
	SelectionStep<reco::CaloJet> step(selection_[key].first);
	if(step.select(event, setup)){ ++passed;
	  selection_[key].second->fill(event, setup);
	} else break;
      }
      if(type=="met" ){
	SelectionStep<reco::MET> step(selection_[key].first);
	if(step.select(event)){ ++passed;
	  selection_[key].second->fill(event, setup);
	} else break;
      }
    }
  }
}


