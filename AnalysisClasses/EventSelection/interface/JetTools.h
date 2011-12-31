#ifndef JetTools_h
#define JetTools_h

#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>

//TopTreeProducer classes
#include "../../../TopBrussels/TopTreeProducer/interface/TRootJet.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootCaloJet.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootPFJet.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootJPTJet.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootMET.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootVertex.h"

#include "FactorizedJetCorrector.h"
#include "JetCorrectorParameters.h"
#include "JetCorrectionUncertainty.h"
#include "TClonesArray.h"
using namespace std;
using namespace TopTree;

class JetTools
{
  public:
    JetTools(vector<JetCorrectorParameters> vCorrParam, JetCorrectionUncertainty* jecUnc, bool startFromRaw = true);
    ~JetTools();
    
    // Jet uncorrectors (back from L2L3 corrected jets to raw jets), input is assumed to be L1L2L3 corrected!!!
    void unCorrectJet(TRootJet* inJet);
    void unCorrectJets(vector<TRootJet*> inJets);
    
    // Jet correctors
    void correctJet(TRootJet* inJet, int nPV = -1);
    void correctJets(vector<TRootJet*> inJets);
    void correctJets(vector<TRootJet*> inJets, vector<TRootVertex*> PVs);
    void correctJets(vector<TRootCaloJet*> inJets, TClonesArray * PVs);

    
    // Jet correctors for JES systematic
    void correctJetJESUnc(TRootJet* inJet, string direction); // direction = plus or minus
    void correctJetJESUnc(vector<TRootJet*> inJets, string direction);
    // Jet in combination with MET correctors for JES systematic
    void correctJetJESUnc(TRootJet* inJet, TRootMET* inMET, string direction); // direction = plus or minus
    void correctJetJESUnc(vector<TRootJet*> inJets, TRootMET*, string direction);
    
    // Jet scalers (with a fixed factor)
    void scaleJet(TRootJet* inJet, float scale=1);
    void scaleJets(vector<TRootJet*> inJets, float scale=1);
    
    // Jet convertors
    vector<TRootCaloJet*> convertToCaloJets(vector<TRootJet*> init_jets);
    vector<TRootPFJet*> convertToPFJets(vector<TRootJet*> init_jets);
    vector<TRootJPTJet*> convertToJPTJets(vector<TRootJet*> init_jets);
    TRootCaloJet* convertToCaloJets(TRootJet* init_jet);
    TRootPFJet* convertToPFJets(TRootJet* init_jet);
    TRootJPTJet* convertToJPTJets(TRootJet* init_jets);
  
  private:
    FactorizedJetCorrector *JEC_;
    JetCorrectionUncertainty* jecUnc_;
    bool startFromRaw_; // true: first correct to raw en then apply the necessary corrections
};

#endif
