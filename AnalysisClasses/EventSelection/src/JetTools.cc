#include "../interface/JetTools.h"

JetTools::JetTools(vector<JetCorrectorParameters> vCorrParam, JetCorrectionUncertainty* jecUnc, bool startFromRaw)
{
//  cout<<"In JetTools constructor:\n\t "<<vCorrParam.size()<<endl;
  JEC_ = new FactorizedJetCorrector(vCorrParam);
//  cout<<"JEC_ is assigned"<<endl;
  jecUnc_ = jecUnc;
  startFromRaw_ = startFromRaw;
  //cout <<"all set in JetTools ..."<<endl;
}

JetTools::~JetTools()
{
  if(JEC_) delete JEC_;
}

//_____Jet correctors and uncorrectors_______________________
void JetTools::unCorrectJet(TRootJet* inJet)
{
  float corr = inJet->getJetCorrFactor("L1L2L3");
  inJet->SetPxPyPzE(inJet->Px()/corr, inJet->Py()/corr, inJet->Pz()/corr, inJet->E()/corr);
}

void JetTools::unCorrectJets(vector<TRootJet*> inJets)
{
  for(unsigned int i=0; i<inJets.size(); i++)
    unCorrectJet(inJets[i]);
}

void JetTools::correctJet(TRootJet* inJet, int nPV)
{
  if(startFromRaw_)
    unCorrectJet(inJet);
  JEC_->setJetEta(inJet->Eta());
  JEC_->setJetPt(inJet->Pt());
  if(nPV > -1) // do the L1 correction
  {
    JEC_->setJetE(inJet->E());
    JEC_->setNPV(nPV);
  }
  float corr = JEC_->getCorrection();
  inJet->SetPxPyPzE(inJet->Px()*corr, inJet->Py()*corr, inJet->Pz()*corr, inJet->E()*corr);
//cout<<"000000"<<endl;
}

void JetTools::correctJets(vector<TRootJet*> inJets)
{
  for(unsigned int i=0; i<inJets.size(); i++)
    correctJet(inJets[i]);
}

void JetTools::correctJets(vector<TRootJet*> inJets, vector<TRootVertex*> PVs)
{
  int nPV = 0;
  for(unsigned int i=0; i<PVs.size(); i++)
    if(!PVs[i]->isFake() && PVs[i]->ndof()>4)
      nPV++;
  for(unsigned int j=0; j<inJets.size(); j++)
    correctJet(inJets[j],nPV);
}

void JetTools::correctJets(vector<TRootCaloJet*> inJets, TClonesArray * PVs)
{
  int nPV = 0;
  for(int i=0; i<PVs->GetEntriesFast(); i++){
    TRootVertex * pv = (TRootVertex*)PVs->At(i);
    if(!pv->isFake() && pv->ndof()>4)
      nPV++;
  }
  for(unsigned int j=0; j<inJets.size(); j++)
    correctJet(inJets[j],nPV);
}


void JetTools::correctJetJESUnc(TRootJet* inJet, string direction) // direction = plus or minus
{
  jecUnc_->setJetEta(inJet->Eta());
  jecUnc_->setJetPt(inJet->Pt());
  float unc = jecUnc_->getUncertainty(true);
  unc = sqrt(unc*unc + 0.053*0.053);
  float corr=1;
  if(direction == "plus")
    corr = 1 + unc;
  else if(direction == "minus")
    corr = 1 - unc;
  else cout << "JetTools::correctJetJESUnc  unknown direction: " << direction << endl;
  inJet->SetPxPyPzE(inJet->Px()*corr, inJet->Py()*corr, inJet->Pz()*corr, inJet->E()*corr);
}

void JetTools::correctJetJESUnc(vector<TRootJet*> inJets, string direction)
{
  for(unsigned int i=0; i<inJets.size(); i++)
    correctJetJESUnc(inJets[i],direction);
}

void JetTools::correctJetJESUnc(TRootJet* inJet, TRootMET* inMET, string direction) // direction = plus or minus
{ 
  inMET->SetPx(inMET->Px() + inJet->Px()); 
  inMET->SetPy(inMET->Py() + inJet->Py());  
  correctJetJESUnc(inJet,direction);  
  inMET->SetPx(inMET->Px() - inJet->Px());
  inMET->SetPy(inMET->Py() - inJet->Py());
  inMET->SetE(sqrt(pow(inMET->Px(),2) + pow(inMET->Py(),2)));
}

void JetTools::correctJetJESUnc(vector<TRootJet*> inJets, TRootMET* inMET, string direction)
{
  for(unsigned int i=0; i<inJets.size(); i++)
    correctJetJESUnc(inJets[i],inMET,direction);
}

void JetTools::scaleJet(TRootJet* inJet, float scale)
{
  inJet->SetPxPyPzE(inJet->Px()*scale, inJet->Py()*scale, inJet->Pz()*scale, inJet->E()*scale);
}

void JetTools::scaleJets(vector<TRootJet*> inJets, float scale)
{
  for(unsigned int i=0; i<inJets.size(); i++)
    scaleJet(inJets[i],scale);
}

//_____Jet convertors________________________________________
vector<TRootCaloJet*> JetTools::convertToCaloJets(vector<TRootJet*> init_jets) {
  vector<TRootCaloJet*> jets;
  for (unsigned i=0; i<init_jets.size(); i++)
    if (init_jets[i]->jetType() == 1)
      jets.push_back(static_cast<TRootCaloJet*>(init_jets[i]));
    else
      cout << "ERROR - JetTools: Attempting to convert a TRootJet to TRootCaloJet that was not created from a CaloJet!";
  return jets;
}

vector<TRootPFJet*> JetTools::convertToPFJets(vector<TRootJet*> init_jets) {
  vector<TRootPFJet*> jets;
  for (unsigned i=0; i<init_jets.size(); i++)
    if (init_jets[i]->jetType() == 2)
      jets.push_back(static_cast<TRootPFJet*>(init_jets[i]));
    else
      cout << "ERROR - JetTools: Attempting to convert a TRootJet to TRootPFJet that was not created from a PFJet!";
  return jets;
}

vector<TRootJPTJet*> JetTools::convertToJPTJets(vector<TRootJet*> init_jets) {
  vector<TRootJPTJet*> jets;
  for (unsigned i=0; i<init_jets.size(); i++)
    if (init_jets[i]->jetType() == 3)
      jets.push_back(static_cast<TRootJPTJet*>(init_jets[i]));
    else
      cout << "ERROR - JetTools: Attempting to convert a TRootJet to TRootJPTJet that was not created from a JPTJet!";
  return jets;
}

TRootCaloJet* JetTools::convertToCaloJets(TRootJet* init_jet) {
  std::vector<TRootJet*> init_jets; init_jets.push_back(init_jet);
  std::vector<TRootCaloJet*> jets = convertToCaloJets(init_jets);
  if (jets.size() > 0) return jets[0];
  return NULL;
}

TRootPFJet* JetTools::convertToPFJets(TRootJet* init_jet) {
  std::vector<TRootJet*> init_jets; init_jets.push_back(init_jet);
  std::vector<TRootPFJet*> jets = convertToPFJets(init_jets);
  if (jets.size() > 0) return jets[0];
  return NULL;
}

TRootJPTJet* JetTools::convertToJPTJets(TRootJet* init_jet) {
  std::vector<TRootJet*> init_jets; init_jets.push_back(init_jet);
  std::vector<TRootJPTJet*> jets = convertToJPTJets(init_jets);
  if (jets.size() > 0) return jets[0];
  return NULL;
}
//___________________________________________________________
