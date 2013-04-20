// -*- C++ -*-
//
// Package:    SingleTop
// Class:      SingleTop
// 
/**\class SingleTop SingleTop.cc TopQuarkAnalysis/SingleTop/src/SingleTop.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Abideh Jafari
//         Created:  Thu Jun 19 17:34:54 CEST 2008
// $Id: SingleTop.cc,v 1.1 2008/07/31 16:24:36 ajafari Exp $
//
//


// system include files
#include <memory>
#include <vector>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "../interface/SingleTop.h"
#include "PhysicsTools/HepMCCandAlgos/interface/CSA07ProcessId.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/PatCandidates/interface/Particle.h"

using namespace std;
using namespace pat;
using namespace edm;
using namespace reco;

// for sorting muons in decreasing pt:
class PtSort {
public:
  bool operator()(const pat::Muon& lhs, const pat::Muon& rhs) const
  { return ( lhs.pt() > rhs.pt() ); }
};

//
// constructors and destructor
//

SingleTop::SingleTop(const edm::ParameterSet& iConfig) 
{
  singleTopEvent_   = false;
 // GenW = new const reco::GenParticle();
  WLessPzNu = new pat::Particle();
  WMorePzNu = new pat::Particle();
  W = new pat::Particle(); 
  // ----- Get user supplied parameters: -----
  isCSA07Soup_ = iConfig.getParameter<bool> ("isCSA07Soup");
  isFullSim_ = iConfig.getParameter<bool> ("isFullSim");
  verbosity = iConfig.getUntrackedParameter<unsigned int>("verbosity");
  cutPtMinFirstMuon = iConfig.getUntrackedParameter<double>("cutPtMinFirstMuon");
  cutPtMinLeptons = iConfig.getUntrackedParameter<double>("cutPtMinLeptons");
  cutEtaFirstMuon = iConfig.getUntrackedParameter<double>("cutEtaFirstMuon");
  cutEtaLeptons = iConfig.getUntrackedParameter<double>("cutEtaLeptons");
  cutPtMinCentralJets = iConfig.getUntrackedParameter<double>("cutPtMinCentralJets");
  cutPtMinForwardJets = iConfig.getUntrackedParameter<double>("cutPtMinForwardJets");
  btagAlgo = iConfig.getUntrackedParameter<std::string>("btagAlgo");
  cutBtag = iConfig.getUntrackedParameter<double>("cutBtag");
  cutEtaJets = iConfig.getUntrackedParameter<double>("cutEtaJets");
  cutMET = iConfig.getUntrackedParameter<double>("cutMET");
  cutCaloIso = iConfig.getUntrackedParameter<double>("cutCaloIso");
  cutTrackIso = iConfig.getUntrackedParameter<double>("cutTrackIso");
  cutLowMTW = iConfig.getUntrackedParameter<double>("cutLowMTW");
  cutUpMTW = iConfig.getUntrackedParameter<double>("cutUpMTW");

  // ----- Name production branch -----

  std::string alias;
  produces<bool>( alias = "SingleTopEvent" ).setBranchAlias( alias ); // true if event contains at least one 'valid' single top event
  produces<vector<bool> >( alias = "cuts" ).setBranchAlias( alias );
  produces<int>( alias = "id" ).setBranchAlias( alias );
  produces<double>( alias = "weight" ).setBranchAlias( alias );
  produces<double>( alias = "HT" ).setBranchAlias( alias );
  produces<double>( alias = "MTW" ).setBranchAlias( alias );
  produces<double>( alias = "MTWtrueNu" ).setBranchAlias( alias );
  produces<bool>( alias = "hasRealSolutions" ).setBranchAlias( alias );
  
  produces<std::vector<pat::Particle> >( alias ="recoW1030").setBranchAlias( alias ); 
  produces<std::vector<pat::Particle> >( alias ="recoW1040").setBranchAlias( alias ); 
  produces<std::vector<pat::Particle> >( alias ="recoW1050").setBranchAlias( alias ); 
  produces<std::vector<pat::Particle> >( alias ="recoW2030").setBranchAlias( alias ); 
  produces<std::vector<pat::Particle> >( alias ="recoW2040").setBranchAlias( alias ); 
  produces<std::vector<pat::Particle> >( alias ="recoW2050").setBranchAlias( alias ); 
  produces<std::vector<pat::Particle> >( alias ="recoW3030").setBranchAlias( alias ); 
  produces<std::vector<pat::Particle> >( alias ="recoW3040").setBranchAlias( alias ); 
  produces<std::vector<pat::Particle> >( alias ="recoW3050").setBranchAlias( alias ); 
  produces<std::vector<pat::Jet> >( alias = "ForwardJet" ).setBranchAlias( alias );
  produces<std::vector<pat::Jet> >( alias = "PreSelectedCentralJet" ).setBranchAlias( alias );
  //produces<std::vector<pat::Particle> >( alias = "recoWMorePzNu" ).setBranchAlias( alias );
  
 // produces<reco::GenParticle>( alias = "GenW" ).setBranchAlias( alias );
}

SingleTop::~SingleTop() 
{
  delete W;
}

//
// member functions
//

// ------------ method called to for each event  ------------
void SingleTop::produce( edm::Event& iEvent, const edm::EventSetup& iSetup) 
{
  // --------------------------------------------------
  //    Step 0: Retrieve CSA07 info from stream if requested
  // --------------------------------------------------
  int id = -1;
  double weight = 1.;
  if ( isCSA07Soup_ ) {    
    id = csa07::csa07ProcessId(iEvent);
    if ( verbosity > 10 )
      std::cout << "Process Id = " << id << std::endl; // https://twiki.cern.ch/twiki/bin/view/CMS/CSA07ProcessId

    Handle< double> weightHandle;
    iEvent.getByLabel ("csa07EventWeightProducer","weight", weightHandle);
    weight = * weightHandle;
  }

  // --------------------------------------------------
  //    Step 1: Retrieve objects from data stream
  // --------------------------------------------------

  iEvent.getByLabel("selectedLayer1Muons",     muonHandle_);
  iEvent.getByLabel("selectedLayer1Electrons", electronHandle_);
  iEvent.getByLabel("selectedLayer1Jets",      jetHandle_);
  iEvent.getByLabel("selectedLayer1METs",      METHandle_);

  // --------------------------------------------------
  //    Step 2: Analysis
  // --------------------------------------------------
  singleTopEvent_ = true;
  
  std::auto_ptr< std::vector<pat::Particle> > W1030(new std::vector<pat::Particle>);
  std::auto_ptr< std::vector<pat::Particle> > W1040(new std::vector<pat::Particle>);
  std::auto_ptr< std::vector<pat::Particle> > W1050(new std::vector<pat::Particle>);
  std::auto_ptr< std::vector<pat::Particle> > W2030(new std::vector<pat::Particle>);
  std::auto_ptr< std::vector<pat::Particle> > W2040(new std::vector<pat::Particle>);
  std::auto_ptr< std::vector<pat::Particle> > W2050(new std::vector<pat::Particle>);
  std::auto_ptr< std::vector<pat::Particle> > W3030(new std::vector<pat::Particle>);
  std::auto_ptr< std::vector<pat::Particle> > W3040(new std::vector<pat::Particle>);
  std::auto_ptr< std::vector<pat::Particle> > W3050(new std::vector<pat::Particle>);
  
//  std::auto_ptr< std::vector<pat::Particle> > tmpWMore(new std::vector<pat::Particle>);
  std::vector<bool> cuts;
  std::vector<string> cutsDescription;
  cuts.clear();
  cutsDescription.clear();

  std::vector<pat::Muon> mu;
  std::vector<pat::Electron> el;
  std::vector<pat::Jet> bjet;
  std::vector<pat::Jet> ljet;
  std::vector<pat::Jet> fjet;
  double HT=0.;


  // MC truth (TO DO: use patMCTruth tools)
  bool thereIsMuFromW = false;
  math::XYZVector Nu_v;
  edm::Handle<reco::GenParticleCollection> genParticles;
  iEvent.getByLabel("genParticles", genParticles);
  for(size_t i = 0; i < genParticles->size(); ++ i) {
    const Candidate & p = (*genParticles)[i];
    int id = p.pdgId();
    if (abs(id)==24) {
     // GenW = &(*genParticles)[i];  
      if ( verbosity > 100 ) cout << " habemus W!" << endl;
      int nd = p.numberOfDaughters();
      for(int j = 0; j < nd; ++ j) {
	const Candidate * d = p.daughter( j );
	int dauId = d->pdgId();
	if (abs(dauId)==13) {
	  if ( verbosity > 100 ) cout << " habemus W->mu!" << endl;
	  thereIsMuFromW = true;
	} else if (abs(dauId)==14) {
	  if ( verbosity > 100 ) cout << " habemus W->nu_mu!" << endl;
	  Nu_v = d->momentum();
	}
      }
    }
  }

  // trigger info
  bool vg_trigger_HLT1MuonIso=false;
  bool vg_trigger_HLT2MuonNonIso=false;
  bool vg_trigger_HLTXElectronMuonRelaxed=false;
  Handle<TriggerResults> HLTR;
  InputTag tag("TriggerResults","","HLT");
  try {
    iEvent.getByLabel(tag,HLTR);
    if (HLTR->size()>=46) vg_trigger_HLT1MuonIso=HLTR->accept(46);
    if (HLTR->size()>=49) vg_trigger_HLT2MuonNonIso=HLTR->accept(49);
    if (HLTR->size()>=83) vg_trigger_HLTXElectronMuonRelaxed=HLTR->accept(83);
  } catch (...) {;}

  if (!isFullSim_) { // there is no HLT info in FastSim in 1.6.x
    if (verbosity > 100) cout << "remember: there is no HLT info in FastSim in 1.6.x" << endl;
  }

  cuts.push_back(vg_trigger_HLT1MuonIso || vg_trigger_HLT2MuonNonIso || vg_trigger_HLTXElectronMuonRelaxed);
  cutsDescription.push_back("triggered by HLT1MuonIso or HLT2MuonNonIso or HLTXElectronMuonRelaxed");

  for (std::vector<pat::Muon>::const_iterator mu_i = muonHandle_->begin(); mu_i != muonHandle_->end(); mu_i++)
    {
      double pt = (*mu_i).pt();
      HT += pt;
      double eta = (*mu_i).eta();
      if (pt > cutPtMinLeptons && fabs(eta) < cutEtaLeptons) mu.push_back((*mu_i));
    }
  if ( verbosity > 100 ) cout << "number of selected muons: " << mu.size() << endl;
  cuts.push_back(mu.size()>0);
  cutsDescription.push_back("at least 1 loose muon");

  // sort vector, cut on leading muon
  double pt_1mu = -1.;
  double eta_1mu = -999.;
  double caloiso = -1.;
  double trackiso = -1.;
  if (mu.size()>0) {
    sort(mu.begin(),mu.end(),PtSort());
    pt_1mu = mu.at(0).pt();
    eta_1mu = mu.at(0).eta();
    caloiso = mu.at(0).caloIso();
    trackiso = mu.at(0).trackIso();
    if ( verbosity > 100 ) cout << "pt(1st mu) = " << pt_1mu << ", eta(1st mu) = " << eta_1mu << ", caloiso = " << caloiso << ", trackiso = " << trackiso << endl;
  }
  cuts.push_back(pt_1mu > cutPtMinFirstMuon && fabs(eta_1mu) < cutEtaFirstMuon && caloiso < cutCaloIso && trackiso < cutTrackIso);
  cutsDescription.push_back("the muon passes the tight selection");

  cuts.push_back(mu.size()<2);
  cutsDescription.push_back("no other loose muon");

  for (std::vector<pat::Electron>::const_iterator el_i = electronHandle_->begin(); el_i != electronHandle_->end(); el_i++)
    {
      double pt = (*el_i).pt();
      HT += pt;
      double eta = (*el_i).eta();
      if (pt > cutPtMinLeptons && fabs(eta) < cutEtaLeptons) el.push_back((*el_i));
    }
  if ( verbosity > 100 ) cout << "number of selected electrons: " << el.size() << endl;
  cuts.push_back(el.size()==0);
  cutsDescription.push_back("no electron");

  for (std::vector<pat::Jet>::const_iterator j_i = jetHandle_->begin(); j_i != jetHandle_->end(); j_i++)
    {
      double pt = (*j_i).pt();
      HT += pt;
      double eta = (*j_i).eta();
      double btag = (*j_i).bDiscriminator(btagAlgo);
      if (pt > cutPtMinForwardJets && fabs(eta) > cutEtaJets) fjet.push_back((*j_i));
      if (pt > cutPtMinCentralJets && fabs(eta) < cutEtaJets && btag > cutBtag ) bjet.push_back((*j_i));
      if (pt > cutPtMinCentralJets && fabs(eta) < cutEtaJets && btag < cutBtag ) ljet.push_back((*j_i));
    }
  if ( verbosity > 100 ) cout << "number of central b-tagged jets: " << bjet.size() << endl;
  if ( verbosity > 100 ) cout << "number of central anti-b-tagged jets: " << ljet.size() << endl;
  if ( verbosity > 100 ) cout << "number of forward jets: " << fjet.size() << endl;

  cuts.push_back(bjet.size()>0);
  cutsDescription.push_back("at least one b-tagged central jet");
  cuts.push_back(fjet.size()>0);
  cutsDescription.push_back("at least one forward jet");
  cuts.push_back(bjet.size()<2);
  cutsDescription.push_back("no other b-tagged central jet");
  cuts.push_back(ljet.size()==0);
  cutsDescription.push_back("no anti-b-tagged central jet");

  double MET = -1.;
  math::XYZVector MET_v;
  if ( METHandle_->size() == 1 ) {
    MET = ((*METHandle_)[0]).pt();
    MET_v = ((*METHandle_)[0]).momentum();
    HT += MET;
  }
  if ( verbosity > 100 ) cout << "MET = " << MET << endl;
  cuts.push_back(MET > cutMET);
  cutsDescription.push_back("MET above threshold");

  double mtw=-1.;
  double mtw_trueNu=-1.;
  if (cuts[1]) {
    mtw = TransverseWmass(mu.at(0),MET_v);
    mtw_trueNu = TransverseWmass(mu.at(0),Nu_v);
   
    if ( verbosity > 100 ) cout << "Transverse mass: " << mtw << endl;
    if ( verbosity > 100 ) cout << "Transverse mass with true neutrino: " << mtw_trueNu << endl;
  }
   cuts.push_back(mtw>cutLowMTW && mtw<cutUpMTW);
   cutsDescription.push_back("MTW is in signal range");

  // create W:
  double massWn=0.;
  if (cuts[1]) {
    createW(mu.at(0),MET_v,massWn,hasRealSolutions);

  cout << "(produce) first solution: " << WLessPzNu->pz() << ", second solution: " << WMorePzNu->pz() << endl;

    //    createPzNu(mu.at(0),MET_v,pznu1,pznu2,massWn);
    //    if ( verbosity > 100 ) cout << "pznu1 = " << pznu1 << ", pznu2 = " << pznu2;
    //    double pznu = min(fabs(pznu1),fabs(pznu2));
    //    if ( verbosity > 100 ) cout << ", min(|pznu1|,|pznu2|) = " << pznu << endl;
    //    W->setPz(pznu + mu.at(0).pz());

    //    if ( verbosity > 100 ) cout << " Transverse mass (2): " << W->mt() << endl; // it's equal to Pt! why?
    //    W->setMass(80.425);
    //    if ( verbosity > 100 ) cout << " Transverse mass (3): " << W->mt() << endl; // it's equal to Pt! why?
      if (MET>30. && pt_1mu>10.) { W1030->push_back(*WLessPzNu);    W1030->push_back(*WMorePzNu); }
       cout<<"MET>30 && pt_1mu>10"<<endl;
      if (MET>30. && pt_1mu>20.) { W2030->push_back(*WLessPzNu);    W2030->push_back(*WMorePzNu); }
       cout<<"MET>30 && pt_1mu>20"<<endl;
      if (MET>30. && pt_1mu>30.) { W3030->push_back(*WLessPzNu);    W3030->push_back(*WMorePzNu); }
       cout<<"MET>30 && pt_1mu>30"<<endl;
      if (MET>40. && pt_1mu>10.) { W1040->push_back(*WLessPzNu);    W1040->push_back(*WMorePzNu); }
       cout<<"MET>40 && pt_1mu>10"<<endl;
       
      if (MET>40. && pt_1mu>20.) { W2040->push_back(*WLessPzNu);    W2040->push_back(*WMorePzNu); }
       cout<<"MET>40 && pt_1mu>20"<<endl;
      if (MET>40. && pt_1mu>30.) { W3040->push_back(*WLessPzNu);    W3040->push_back(*WMorePzNu); }
       cout<<"MET>40 && pt_1mu>30"<<endl;
      if (MET>50. && pt_1mu>10.) { W1050->push_back(*WLessPzNu);    W1050->push_back(*WMorePzNu); }
       cout<<"MET>50 && pt_1mu>10"<<endl;
      if (MET>50. && pt_1mu>20.) { W2050->push_back(*WLessPzNu);    W2050->push_back(*WMorePzNu); }
       cout<<"MET>50 && pt_1mu>20"<<endl;
      if (MET>50. && pt_1mu>30.) { W3050->push_back(*WLessPzNu);    W3050->push_back(*WMorePzNu); }

   // cout << "(produce) first solution: " << (*W1030).at(0).pz() << ", second solution: " << (*W1030).at(1).pz()<< endl;
  }
  cout<<"Run sho torokhoda!"<<endl;
  if ( verbosity > 10 ) cout << "Summary of cuts:" << endl;
  int firstCutToConsider = 0;
  if (!isFullSim_) firstCutToConsider = 1; // there is no HLT info in FastSim in the 1.6.x series
  for (unsigned int i=firstCutToConsider; i<cuts.size(); i++){
    if ( verbosity > 10 ) cout << " " << cutsDescription.at(i) << ": " << cuts.at(i) << endl;
    singleTopEvent_ *= cuts.at(i);
  }

  if (verbosity > 5) {
    if (singleTopEvent_) { cout << "* selected" << endl; } else { cout << "# rejected" << endl; }
  }  

  iEvent.put(auto_ptr<bool>(new bool(singleTopEvent_)), "SingleTopEvent");
  iEvent.put(auto_ptr<std::vector<bool> >(new std::vector<bool>(cuts)), "cuts");
  iEvent.put(auto_ptr<int>(new int(id)), "id");
  iEvent.put(auto_ptr<double>(new double(weight)), "weight");
  iEvent.put(auto_ptr<double>(new double(HT)), "HT");
  iEvent.put(auto_ptr<double>(new double(mtw)), "MTW");
  iEvent.put(auto_ptr<double>(new double(mtw_trueNu)), "MTWtrueNu");
  iEvent.put(auto_ptr<bool>(new bool(hasRealSolutions)), "hasRealSolutions");
  iEvent.put(W1030,"recoW1030"); 
  iEvent.put(W1040,"recoW1040"); 
  iEvent.put(W1050,"recoW1050"); 
  iEvent.put(W2030,"recoW2030"); 
  iEvent.put(W2040,"recoW2040"); 
  iEvent.put(W2050,"recoW2050"); 
  iEvent.put(W3030,"recoW3030"); 
  iEvent.put(W3040,"recoW3040"); 
  iEvent.put(W3050,"recoW3050"); 
  //iEvent.put(tmpWMore, "recoWMorePzNu"); 
 // iEvent.put(auto_ptr< reco::GenParticle>(new reco::GenParticle (*GenW)), "GenW"); 

  /* TO DO LIST:
     - MC truth: t, W, nu
     - M(top)
  */

}


// ------------ method called once each job just before starting event loop  ------------
void
SingleTop::beginJob(const edm::EventSetup& iSetup)
{
  //  StarterKit::beginJob(iSetup);
}



// ------------ method called once each job just after ending the event loop  ------------
void
SingleTop::endJob() {
  //  StarterKit::endJob();
}



void SingleTop::createW(pat::Muon mu, math::XYZVector met, double & massWn, bool & hasRealSolutions) {
  // create a W with NO LONGITUDINAL COMPONENT:
  W->setCharge(mu.charge());
  math::XYZVector lept_2d(mu.px(),mu.py(),0.);
  math::XYZVector sum_2d = lept_2d + met;
  math::XYZTLorentzVector p4(sum_2d.x(),sum_2d.y(),0,sum_2d.R()); 
  W->setP4(p4);
  if ( verbosity > 100 ) cout << "PtW (2): " << W->pt() << endl;

  // longitudinal component:
  double pznu1=0.;
  double pznu2=0.;
  createPzNu(mu,met,pznu1,pznu2,massWn,hasRealSolutions);
  if ( verbosity > 100 ) cout << "pznu1 = " << pznu1 << ", pznu2 = " << pznu2;
  *WLessPzNu = *W; 
  *WMorePzNu = *W;
  double sumLess =  pznu2 + mu.pz() ;
  double sumMore =   pznu1 + mu.pz();  
  
  math::XYZTLorentzVector p4Less(sum_2d.x(),sum_2d.y(), sumLess, mu.energy() + sqrt(met.R()*met.R() + pznu2*pznu2 ) ); 
  math::XYZTLorentzVector p4More(sum_2d.x(),sum_2d.y(),sumMore, mu.energy() + sqrt(met.R()*met.R() + pznu1*pznu1 ) ); 
  if (fabs(pznu1)>fabs(pznu2)){
        WLessPzNu->setP4(p4Less);
        WMorePzNu->setP4(p4More);
                              } 
  else {
              WLessPzNu->setP4(p4More);
              WMorePzNu->setP4(p4Less);
       }
  
  //WLessPzNu->
  cout << "(SingleTop::createW) first solution: " << pznu1 + mu.pz()<< ", second solution: " << pznu2+ mu.pz() << endl;
  cout << "(SingleTop::createW, bis) first solution: " << WLessPzNu->pz() << ", second solution: " << WMorePzNu->pz() << endl;

  // if ( verbosity > 100 ) cout << ", min(|pznu1|,|pznu2|) = " << pznu << endl;
 
}

double SingleTop::TransverseWmass(pat::Muon mu, math::XYZVector met) {
  double mt = 0.;
  double MassW=80.425;

  double lept_x = mu.px();
  double lept_y = mu.py();
  double lept_z = mu.pz();

  math::XYZVector lept_2d(lept_x,lept_y,0.);
  math::XYZVector sum_2d = lept_2d + met;

  double nu_x = met.x();
  double nu_y = met.y();

  //  bool goodW=true;
  double Elept=mu.p();
  //  double PtW=sqrt((nu_x+lept_x)**2+(nu_y+lept_y)**2);
  double PtW = sum_2d.R(); // see http://root.cern.ch/root/html/ROOT__Math__Cartesian3D_double_.html
  if ( verbosity > 100 ) cout << "PtW: " << PtW << endl;
  //  double PtL=sqrt(lept_x**2+lept_y**2);
  double PtL = lept_2d.R();
  //  double PtN=sqrt(nu_x**2+nu_y**2);
  double PtN = met.R();
  double plm=nu_x*lept_x+nu_y*lept_y;
  double cosLN;
  if (PtL!=0. && PtN!=0.) {
    cosLN=plm/(PtL*PtN);
  } else {
    cosLN=0.;
    if ( verbosity > 10 ) cout << " --- WARNING: PtL = " << PtL << ", PtN = " << PtN << endl;
  }
  mt=sqrt(2*(PtL*PtN-1.*(nu_x*lept_x+nu_y*lept_y)));


  return mt;
}

void  SingleTop::createPzNu(pat::Muon mu, math::XYZVector met, double & pnuz1, double & pnuz2 , double & massWn, bool & hasRealSolutions)
{
  double sol1 = 0.;
  double sol2 = 0.;
  double MassW = 80.425;
  double lept_x = mu.px();
  double lept_y = mu.py();
  double lept_z = mu.pz();
  double lept_e = mu.energy();
  double met_x = met.x();
  double met_y = met.y();
  double met_xy = sqrt(met_x * met_x + met_y * met_y);

  double a = MassW*MassW/2. + lept_x*met_x  + lept_y*met_y;
  double disc = lept_e * lept_e*( a*a - mu.pt() * mu.pt() * met_xy* met_xy);
  if (disc >= 0.)
    {
      hasRealSolutions=true;
      sol1 =  (a*lept_z+sqrt(disc))/( mu.pt()* mu.pt());
      sol2 =  (a*lept_z-sqrt(disc))/( mu.pt()* mu.pt());
      if ( verbosity > 100 ) cout << "solution 1 " << sol1 <<endl;
      if ( verbosity > 100 ) cout << "solution 2 " << sol2 <<endl;
      double recMass1 = 2*( lept_e*sqrt(sol1*sol1+met_xy*met_xy) - (lept_x*met_x  + lept_y*met_y) - sol1*lept_z);
      double recMass2 = 2*( lept_e*sqrt(sol2*sol2+met_xy*met_xy) - (lept_x*met_x  + lept_y*met_y) - sol2*lept_z);
      if ( verbosity > 100 ) cout << " Mass W 1 = " << sqrt(recMass1) << endl;
      if ( verbosity > 100 ) cout << " Mass W 2 = " << sqrt(recMass2) << endl;
    }
  if (disc < 0.)
    {
      hasRealSolutions=false;
      MassW = sqrt(2* met_xy * mu.pt() -  (lept_x*met_x  + lept_y*met_y));
      if ( verbosity > 100 ) cout << "negative disc; new W mass = " << MassW << endl;
      sol1 = (a*lept_z)/( mu.pt()* mu.pt());
      sol2 = sol1;
    }
  pnuz1 = sol1;
  pnuz2 = sol2;
  massWn = MassW;
}






//define this as a plug-in
DEFINE_FWK_MODULE(SingleTop);

