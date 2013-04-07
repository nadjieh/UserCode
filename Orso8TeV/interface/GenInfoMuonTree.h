//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Oct 11 11:16:05 2012 by ROOT version 5.32/00
// from TTree Data_2J_1T_noSyst/Data_2J_1T_noSyst
// found on file: Data.root
//////////////////////////////////////////////////////////

#ifndef GenInfoMuonTree_h
#define GenInfoMuonTree_h
#include "../../TopBrussels/TopTreeProducer/interface/TRootNPGenEvent.h"
#include "../../TopBrussels/TopTreeProducer/interface/TRootGenTop.h"
#include "../../TopBrussels/TopTreeProducer/interface/TRootMCParticle.h"
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TString.h>
#include <TLorentzVector.h>
#include <TMath.h>
#include <iostream>
#include <string>
using namespace std;
using namespace TopTree;
// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

class GenInfoMuonTree {
public:
    TTree *fChain; //!pointer to the analyzed TTree or TChain
    Int_t fCurrent; //!current Tree number in a TChain

    // Declaration of leaf types
    Double_t eta;
    Double_t costhetalj;
    Double_t costhetalbl;
    Double_t mtwMass;
    Int_t charge;
    Int_t runid;
    Int_t lumiid;
    Int_t eventid;
    Double_t weight;
    Double_t totalWeight;
    Double_t bWeight;
    Double_t bWeightBTagUp;
    Double_t bWeightBTagDown;
    Double_t bWeightMisTagUp;
    Double_t bWeightMisTagDown;
    Double_t PUWeight;
    Double_t PUWeightPUUp;
    Double_t PUWeightPUDown;
    Double_t turnOnWeight;
    Double_t turnOnReWeight;
    Double_t turnOnWeightJetTrig1Up;
    Double_t turnOnWeightJetTrig1Down;
    Double_t turnOnWeightJetTrig2Up;
    Double_t turnOnWeightJetTrig2Down;
    Double_t turnOnWeightJetTrig3Up;
    Double_t turnOnWeightJetTrig3Down;
    Double_t turnOnWeightBTagTrig1Up;
    Double_t turnOnWeightBTagTrig1Down;
    Double_t turnOnWeightBTagTrig2Up;
    Double_t turnOnWeightBTagTrig2Down;
    Double_t turnOnWeightBTagTrig3Up;
    Double_t turnOnWeightBTagTrig3Down;
    Double_t leptonPt;
    Double_t leptonEta;
    Double_t leptonPhi;
    Double_t leptonDeltaCorrectedRelIso;
    Double_t leptonRhoCorrectedRelIso;
    Double_t leptonEff;
    Double_t leptonEffB;
    Double_t fJetPt;
    Double_t fJetE;
    Double_t fJetEta;
    Double_t fJetPhi;
    Double_t fJetBtag;
    Int_t fJetFlavour;
    Double_t fJetPUID;
    Double_t fJetPUWP;
    Double_t fJetBeta;
    Double_t fJetDZ;
    Double_t fJetRMS;
    Double_t bJetBeta;
    Double_t bJetDZ;
    Double_t bJetRMS;
    Double_t bJetPt;
    Double_t bJetE;
    Double_t bJetEta;
    Double_t bJetPhi;
    Double_t bJetBtag;
    Int_t bJetFlavour;
    Double_t bJetPUID;
    Double_t bJetPUWP;
    Double_t firstJetPt;
    Double_t firstJetEta;
    Double_t firstJetPhi;
    Double_t firstJetE;
    Int_t firstJetFlavour;
    Double_t secondJetPt;
    Double_t secondJetEta;
    Double_t secondJetPhi;
    Double_t secondJetE;
    Int_t secondJetFlavour;
    Int_t eventFlavour;
    Double_t metPt;
    Double_t metPhi;
    Double_t HT;
    Double_t topMass;
    Double_t topMtw;
    Double_t topPt;
    Double_t topPhi;
    Double_t topEta;
    Double_t topE;
    Int_t ID;
    Int_t nVertices;
    Int_t nGoodVertices;
    Double_t totalEnergy;
    Double_t totalMomentum;
    Double_t lowBTag;
    Double_t highBTag;
    Int_t nMCTruthLeptons;
    Float_t MCTop_1_Pt;
    Float_t MCTop_1_Phi;
    Float_t MCTop_1_Eta;
    Float_t MCTop_1_E;
    Float_t MCTop_1_PdgId;
    Float_t MCTopLepton_1_Pt;
    Float_t MCTopLepton_1_Phi;
    Float_t MCTopLepton_1_Eta;
    Float_t MCTopLepton_1_E;
    Float_t MCTopLepton_1_PdgId;
    Float_t MCTopLepton_1_MotherId;
    Float_t MCTopNeutrino_1_Pt;
    Float_t MCTopNeutrino_1_Phi;
    Float_t MCTopNeutrino_1_Eta;
    Float_t MCTopNeutrino_1_E;
    Float_t MCTopNeutrino_1_PdgId;
    Float_t MCTopNeutrino_1_MotherId;
    Float_t MCTopQuark_1_Pt;
    Float_t MCTopQuark_1_Phi;
    Float_t MCTopQuark_1_Eta;
    Float_t MCTopQuark_1_E;
    Float_t MCTopQuark_1_PdgId;
    Float_t MCTopQuark_1_MotherId;
    Float_t MCTopQuarkBar_1_Pt;
    Float_t MCTopQuarkBar_1_Phi;
    Float_t MCTopQuarkBar_1_Eta;
    Float_t MCTopQuarkBar_1_E;
    Float_t MCTopQuarkBar_1_PdgId;
    Float_t MCTopQuarkBar_1_MotherId;
    Float_t MCTopBQuark_1_Pt;
    Float_t MCTopBQuark_1_Phi;
    Float_t MCTopBQuark_1_Eta;
    Float_t MCTopBQuark_1_E;
    Float_t MCTopBQuark_1_PdgId;
    Float_t MCTopBQuark_1_MotherId;
    Float_t MCTopW_1_Pt;
    Float_t MCTopW_1_Phi;
    Float_t MCTopW_1_Eta;
    Float_t MCTopW_1_E;
    Float_t MCTopW_1_PdgId;
    Float_t MCTopW_1_DauOneId;
    //   Int_t           nMCTruthLeptons;
    Float_t MCTop_2_Pt;
    Float_t MCTop_2_Phi;
    Float_t MCTop_2_Eta;
    Float_t MCTop_2_E;
    Float_t MCTop_2_PdgId;
    Float_t MCTopLepton_2_Pt;
    Float_t MCTopLepton_2_Phi;
    Float_t MCTopLepton_2_Eta;
    Float_t MCTopLepton_2_E;
    Float_t MCTopLepton_2_PdgId;
    Float_t MCTopLepton_2_MotherId;
    Float_t MCTopNeutrino_2_Pt;
    Float_t MCTopNeutrino_2_Phi;
    Float_t MCTopNeutrino_2_Eta;
    Float_t MCTopNeutrino_2_E;
    Float_t MCTopNeutrino_2_PdgId;
    Float_t MCTopNeutrino_2_MotherId;
    Float_t MCTopQuark_2_Pt;
    Float_t MCTopQuark_2_Phi;
    Float_t MCTopQuark_2_Eta;
    Float_t MCTopQuark_2_E;
    Float_t MCTopQuark_2_PdgId;
    Float_t MCTopQuark_2_MotherId;
    Float_t MCTopQuarkBar_2_Pt;
    Float_t MCTopQuarkBar_2_Phi;
    Float_t MCTopQuarkBar_2_Eta;
    Float_t MCTopQuarkBar_2_E;
    Float_t MCTopQuarkBar_2_PdgId;
    Float_t MCTopQuarkBar_2_MotherId;
    Float_t MCTopBQuark_2_Pt;
    Float_t MCTopBQuark_2_Phi;
    Float_t MCTopBQuark_2_Eta;
    Float_t MCTopBQuark_2_E;
    Float_t MCTopBQuark_2_PdgId;
    Float_t MCTopBQuark_2_MotherId;
    Float_t MCTopW_2_Pt;
    Float_t MCTopW_2_Phi;
    Float_t MCTopW_2_Eta;
    Float_t MCTopW_2_E;
    Float_t MCTopW_2_PdgId;
    Float_t MCTopW_2_DauOneId;
    Float_t MCQuark_1_Pt;
    Float_t MCQuark_1_Phi;
    Float_t MCQuark_1_Eta;
    Float_t MCQuark_1_E;
    Float_t MCQuark_1_PdgId;
    Float_t MCQuark_2_Pt;
    Float_t MCQuark_2_Phi;
    Float_t MCQuark_2_Eta;
    Float_t MCQuark_2_E;
    Float_t MCQuark_2_PdgId;
    Float_t MCQuark_3_Pt;
    Float_t MCQuark_3_Phi;
    Float_t MCQuark_3_Eta;
    Float_t MCQuark_3_E;
    Float_t MCQuark_3_PdgId;
    Float_t MCQuark_4_Pt;
    Float_t MCQuark_4_Phi;
    Float_t MCQuark_4_Eta;
    Float_t MCQuark_4_E;
    Float_t MCQuark_4_PdgId;
    Float_t MCQuark_5_Pt;
    Float_t MCQuark_5_Phi;
    Float_t MCQuark_5_Eta;
    Float_t MCQuark_5_E;
    Float_t MCQuark_5_PdgId;
    Float_t MCQuark_6_Pt;
    Float_t MCQuark_6_Phi;
    Float_t MCQuark_6_Eta;
    Float_t MCQuark_6_E;
    Float_t MCQuark_6_PdgId;
    Float_t MCQuark_7_Pt;
    Float_t MCQuark_7_Phi;
    Float_t MCQuark_7_Eta;
    Float_t MCQuark_7_E;
    Float_t MCQuark_7_PdgId;
    Float_t MCQuark_8_Pt;
    Float_t MCQuark_8_Phi;
    Float_t MCQuark_8_Eta;
    Float_t MCQuark_8_E;
    Float_t MCQuark_8_PdgId;
    Float_t MCQuark_9_Pt;
    Float_t MCQuark_9_Phi;
    Float_t MCQuark_9_Eta;
    Float_t MCQuark_9_E;
    Float_t MCQuark_9_PdgId;
    Float_t MCQuark_10_Pt;
    Float_t MCQuark_10_Phi;
    Float_t MCQuark_10_Eta;
    Float_t MCQuark_10_E;
    Float_t MCQuark_10_PdgId;
    Float_t MCQuark_11_Pt;
    Float_t MCQuark_11_Phi;
    Float_t MCQuark_11_Eta;
    Float_t MCQuark_11_E;
    Float_t MCQuark_11_PdgId;
    Float_t MCQuark_12_Pt;
    Float_t MCQuark_12_Phi;
    Float_t MCQuark_12_Eta;
    Float_t MCQuark_12_E;
    Float_t MCQuark_12_PdgId;
    Float_t MCBQuark_1_Pt;
    Float_t MCBQuark_1_Phi;
    Float_t MCBQuark_1_Eta;
    Float_t MCBQuark_1_E;
    Float_t MCBQuark_1_PdgId;
    Float_t MCLepton_1_Pt;
    Float_t MCLepton_1_Phi;
    Float_t MCLepton_1_Eta;
    Float_t MCLepton_1_E;
    Float_t MCLepton_1_PdgId;
    Float_t MCNeutrino_1_Pt;
    Float_t MCNeutrino_1_Phi;
    Float_t MCNeutrino_1_Eta;
    Float_t MCNeutrino_1_E;
    Float_t MCNeutrino_1_PdgId;
    Float_t MCBQuark_2_Pt;
    Float_t MCBQuark_2_Phi;
    Float_t MCBQuark_2_Eta;
    Float_t MCBQuark_2_E;
    Float_t MCBQuark_2_PdgId;
    Float_t MCLepton_2_Pt;
    Float_t MCLepton_2_Phi;
    Float_t MCLepton_2_Eta;
    Float_t MCLepton_2_E;
    Float_t MCLepton_2_PdgId;
    Float_t MCNeutrino_2_Pt;
    Float_t MCNeutrino_2_Phi;
    Float_t MCNeutrino_2_Eta;
    Float_t MCNeutrino_2_E;
    Float_t MCNeutrino_2_PdgId;
    Float_t MCBQuark_3_Pt;
    Float_t MCBQuark_3_Phi;
    Float_t MCBQuark_3_Eta;
    Float_t MCBQuark_3_E;
    Float_t MCBQuark_3_PdgId;
    Float_t MCLepton_3_Pt;
    Float_t MCLepton_3_Phi;
    Float_t MCLepton_3_Eta;
    Float_t MCLepton_3_E;
    Float_t MCLepton_3_PdgId;
    Float_t MCNeutrino_3_Pt;
    Float_t MCNeutrino_3_Phi;
    Float_t MCNeutrino_3_Eta;
    Float_t MCNeutrino_3_E;
    Float_t MCNeutrino_3_PdgId;
    Float_t MCBQuark_4_Pt;
    Float_t MCBQuark_4_Phi;
    Float_t MCBQuark_4_Eta;
    Float_t MCBQuark_4_E;
    Float_t MCBQuark_4_PdgId;
    Float_t MCLepton_4_Pt;
    Float_t MCLepton_4_Phi;
    Float_t MCLepton_4_Eta;
    Float_t MCLepton_4_E;
    Float_t MCLepton_4_PdgId;
    Float_t MCNeutrino_4_Pt;
    Float_t MCNeutrino_4_Phi;
    Float_t MCNeutrino_4_Eta;
    Float_t MCNeutrino_4_E;
    Float_t MCNeutrino_4_PdgId;
    Float_t PDFWeight1;
    Float_t PDFWeight2;
    Float_t PDFWeight3;
    Float_t PDFWeight4;
    Float_t PDFWeight5;
    Float_t PDFWeight6;
    Float_t PDFWeight7;
    Float_t PDFWeight8;
    Float_t PDFWeight9;
    Float_t PDFWeight10;
    Float_t PDFWeight11;
    Float_t PDFWeight12;
    Float_t PDFWeight13;
    Float_t PDFWeight14;
    Float_t PDFWeight15;
    Float_t PDFWeight16;
    Float_t PDFWeight17;
    Float_t PDFWeight18;
    Float_t PDFWeight19;
    Float_t PDFWeight20;
    Float_t PDFWeight21;
    Float_t PDFWeight22;
    Float_t PDFWeight23;
    Float_t PDFWeight24;
    Float_t PDFWeight25;
    Float_t PDFWeight26;
    Float_t PDFWeight27;
    Float_t PDFWeight28;
    Float_t PDFWeight29;
    Float_t PDFWeight30;
    Float_t PDFWeight31;
    Float_t PDFWeight32;
    Float_t PDFWeight33;
    Float_t PDFWeight34;
    Float_t PDFWeight35;
    Float_t PDFWeight36;
    Float_t PDFWeight37;
    Float_t PDFWeight38;
    Float_t PDFWeight39;
    Float_t PDFWeight40;
    Float_t PDFWeight41;
    Float_t PDFWeight42;
    Float_t PDFWeight43;
    Float_t PDFWeight44;
    Float_t PDFWeight45;
    Float_t PDFWeight46;
    Float_t PDFWeight47;
    Float_t PDFWeight48;
    Float_t PDFWeight49;
    Float_t PDFWeight50;
    Float_t PDFWeight51;
    Float_t PDFWeight52;
    Float_t PDFWeight_Alternate_Set_1;
    Float_t PDFWeight_Alternate_Set_2;


    // List of branches
    TBranch *b_eta; //!
    TBranch *b_costhetalj; //!
    TBranch *b_costhetalbl; //!
    TBranch *b_mtwMass; //!
    TBranch *b_charge; //!
    TBranch *b_runid; //!
    TBranch *b_lumiid; //!
    TBranch *b_eventid; //!
    TBranch *b_weight; //!
    TBranch *b_totalWeight; //!
    TBranch *b_bWeight; //!
    TBranch *b_bWeightBTagUp; //!
    TBranch *b_bWeightBTagDown; //!
    TBranch *b_bWeightMisTagUp; //!
    TBranch *b_bWeightMisTagDown; //!
    TBranch *b_PUWeight; //!
    TBranch *b_PUWeightPUUp; //!
    TBranch *b_PUWeightPUDown; //!
    TBranch *b_turnOnWeight; //!
    TBranch *b_turnOnReWeight; //!
    TBranch *b_turnOnWeightJetTrig1Up; //!
    TBranch *b_turnOnWeightJetTrig1Down; //!
    TBranch *b_turnOnWeightJetTrig2Up; //!
    TBranch *b_turnOnWeightJetTrig2Down; //!
    TBranch *b_turnOnWeightJetTrig3Up; //!
    TBranch *b_turnOnWeightJetTrig3Down; //!
    TBranch *b_turnOnWeightBTagTrig1Up; //!
    TBranch *b_turnOnWeightBTagTrig1Down; //!
    TBranch *b_turnOnWeightBTagTrig2Up; //!
    TBranch *b_turnOnWeightBTagTrig2Down; //!
    TBranch *b_turnOnWeightBTagTrig3Up; //!
    TBranch *b_turnOnWeightBTagTrig3Down; //!
    TBranch *b_leptonPt; //!
    TBranch *b_leptonEta; //!
    TBranch *b_leptonPhi; //!
    TBranch *b_leptonDeltaCorrectedRelIso; //!
    TBranch *b_leptonRhoCorrectedRelIso; //!
    TBranch *b_leptonEff; //!
    TBranch *b_leptonEffB; //!
    TBranch *b_fJetPt; //!
    TBranch *b_fJetE; //!
    TBranch *b_fJetEta; //!
    TBranch *b_fJetPhi; //!
    TBranch *b_fJetBtag; //!
    TBranch *b_fJetFlavour; //!
    TBranch *b_fJetPUID; //!
    TBranch *b_fJetPUWP; //!
    TBranch *b_fJetBeta; //!
    TBranch *b_fJetDZ; //!
    TBranch *b_fJetRMS; //!
    TBranch *b_bJetBeta; //!
    TBranch *b_bJetDZ; //!
    TBranch *b_bJetRMS; //!
    TBranch *b_bJetPt; //!
    TBranch *b_bJetE; //!
    TBranch *b_bJetEta; //!
    TBranch *b_bJetPhi; //!
    TBranch *b_bJetBtag; //!
    TBranch *b_bJetFlavour; //!
    TBranch *b_bJetPUID; //!
    TBranch *b_bJetPUWP; //!
    TBranch *b_firstJetPt; //!
    TBranch *b_firstJetEta; //!
    TBranch *b_firstJetPhi; //!
    TBranch *b_firstJetE; //!
    TBranch *b_firstJetFlavour; //!
    TBranch *b_secondJetPt; //!
    TBranch *b_secondJetEta; //!
    TBranch *b_secondJetPhi; //!
    TBranch *b_secondJetE; //!
    TBranch *b_secondJetFlavour; //!
    TBranch *b_eventFlavour; //!
    TBranch *b_metPt; //!
    TBranch *b_metPhi; //!
    TBranch *b_HT; //!
    TBranch *b_topMass; //!
    TBranch *b_topMtw; //!
    TBranch *b_topPt; //!
    TBranch *b_topPhi; //!
    TBranch *b_topEta; //!
    TBranch *b_topE; //!
    TBranch *b_ID; //!
    TBranch *b_nVertices; //!
    TBranch *b_nGoodVertices; //!
    TBranch *b_totalEnergy; //!
    TBranch *b_totalMomentum; //!
    TBranch *b_lowBTag; //!
    TBranch *b_highBTag; //!
    TBranch *b_nMCTruthLeptons; //!
    TBranch *b_MCTop_1_Pt; //!
    TBranch *b_MCTop_1_Phi; //!
    TBranch *b_MCTop_1_Eta; //!
    TBranch *b_MCTop_1_E; //!
    TBranch *b_MCTop_1_PdgId; //!
    TBranch *b_MCTopLepton_1_Pt; //!
    TBranch *b_MCTopLepton_1_Phi; //!
    TBranch *b_MCTopLepton_1_Eta; //!
    TBranch *b_MCTopLepton_1_E; //!
    TBranch *b_MCTopLepton_1_PdgId; //!
    TBranch *b_MCTopLepton_1_MotherId; //!
    TBranch *b_MCTopNeutrino_1_Pt; //!
    TBranch *b_MCTopNeutrino_1_Phi; //!
    TBranch *b_MCTopNeutrino_1_Eta; //!
    TBranch *b_MCTopNeutrino_1_E; //!
    TBranch *b_MCTopNeutrino_1_PdgId; //!
    TBranch *b_MCTopNeutrino_1_MotherId; //!
    TBranch *b_MCTopQuark_1_Pt; //!
    TBranch *b_MCTopQuark_1_Phi; //!
    TBranch *b_MCTopQuark_1_Eta; //!
    TBranch *b_MCTopQuark_1_E; //!
    TBranch *b_MCTopQuark_1_PdgId; //!
    TBranch *b_MCTopQuark_1_MotherId; //!
    TBranch *b_MCTopQuarkBar_1_Pt; //!
    TBranch *b_MCTopQuarkBar_1_Phi; //!
    TBranch *b_MCTopQuarkBar_1_Eta; //!
    TBranch *b_MCTopQuarkBar_1_E; //!
    TBranch *b_MCTopQuarkBar_1_PdgId; //!
    TBranch *b_MCTopQuarkBar_1_MotherId; //!
    TBranch *b_MCTopBQuark_1_Pt; //!
    TBranch *b_MCTopBQuark_1_Phi; //!
    TBranch *b_MCTopBQuark_1_Eta; //!
    TBranch *b_MCTopBQuark_1_E; //!
    TBranch *b_MCTopBQuark_1_PdgId; //!
    TBranch *b_MCTopBQuark_1_MotherId; //!
    TBranch *b_MCTopW_1_Pt; //!
    TBranch *b_MCTopW_1_Phi; //!
    TBranch *b_MCTopW_1_Eta; //!
    TBranch *b_MCTopW_1_E; //!
    TBranch *b_MCTopW_1_PdgId; //!
    TBranch *b_MCTopW_1_DauOneId; //!
    //   TBranch        *b_nMCTruthLeptons;   //!
    TBranch *b_MCTop_2_Pt; //!
    TBranch *b_MCTop_2_Phi; //!
    TBranch *b_MCTop_2_Eta; //!
    TBranch *b_MCTop_2_E; //!
    TBranch *b_MCTop_2_PdgId; //!
    TBranch *b_MCTopLepton_2_Pt; //!
    TBranch *b_MCTopLepton_2_Phi; //!
    TBranch *b_MCTopLepton_2_Eta; //!
    TBranch *b_MCTopLepton_2_E; //!
    TBranch *b_MCTopLepton_2_PdgId; //!
    TBranch *b_MCTopLepton_2_MotherId; //!
    TBranch *b_MCTopNeutrino_2_Pt; //!
    TBranch *b_MCTopNeutrino_2_Phi; //!
    TBranch *b_MCTopNeutrino_2_Eta; //!
    TBranch *b_MCTopNeutrino_2_E; //!
    TBranch *b_MCTopNeutrino_2_PdgId; //!
    TBranch *b_MCTopNeutrino_2_MotherId; //!
    TBranch *b_MCTopQuark_2_Pt; //!
    TBranch *b_MCTopQuark_2_Phi; //!
    TBranch *b_MCTopQuark_2_Eta; //!
    TBranch *b_MCTopQuark_2_E; //!
    TBranch *b_MCTopQuark_2_PdgId; //!
    TBranch *b_MCTopQuark_2_MotherId; //!
    TBranch *b_MCTopQuarkBar_2_Pt; //!
    TBranch *b_MCTopQuarkBar_2_Phi; //!
    TBranch *b_MCTopQuarkBar_2_Eta; //!
    TBranch *b_MCTopQuarkBar_2_E; //!
    TBranch *b_MCTopQuarkBar_2_PdgId; //!
    TBranch *b_MCTopQuarkBar_2_MotherId; //!
    TBranch *b_MCTopBQuark_2_Pt; //!
    TBranch *b_MCTopBQuark_2_Phi; //!
    TBranch *b_MCTopBQuark_2_Eta; //!
    TBranch *b_MCTopBQuark_2_E; //!
    TBranch *b_MCTopBQuark_2_PdgId; //!
    TBranch *b_MCTopBQuark_2_MotherId; //!
    TBranch *b_MCTopW_2_Pt; //!
    TBranch *b_MCTopW_2_Phi; //!
    TBranch *b_MCTopW_2_Eta; //!
    TBranch *b_MCTopW_2_E; //!
    TBranch *b_MCTopW_2_PdgId; //!
    TBranch *b_MCTopW_2_DauOneId; //!
    TBranch *b_MCQuark_1_Pt; //!
    TBranch *b_MCQuark_1_Phi; //!
    TBranch *b_MCQuark_1_Eta; //!
    TBranch *b_MCQuark_1_E; //!
    TBranch *b_MCQuark_1_PdgId; //!
    TBranch *b_MCQuark_2_Pt; //!
    TBranch *b_MCQuark_2_Phi; //!
    TBranch *b_MCQuark_2_Eta; //!
    TBranch *b_MCQuark_2_E; //!
    TBranch *b_MCQuark_2_PdgId; //!
    TBranch *b_MCQuark_3_Pt; //!
    TBranch *b_MCQuark_3_Phi; //!
    TBranch *b_MCQuark_3_Eta; //!
    TBranch *b_MCQuark_3_E; //!
    TBranch *b_MCQuark_3_PdgId; //!
    TBranch *b_MCQuark_4_Pt; //!
    TBranch *b_MCQuark_4_Phi; //!
    TBranch *b_MCQuark_4_Eta; //!
    TBranch *b_MCQuark_4_E; //!
    TBranch *b_MCQuark_4_PdgId; //!
    TBranch *b_MCQuark_5_Pt; //!
    TBranch *b_MCQuark_5_Phi; //!
    TBranch *b_MCQuark_5_Eta; //!
    TBranch *b_MCQuark_5_E; //!
    TBranch *b_MCQuark_5_PdgId; //!
    TBranch *b_MCQuark_6_Pt; //!
    TBranch *b_MCQuark_6_Phi; //!
    TBranch *b_MCQuark_6_Eta; //!
    TBranch *b_MCQuark_6_E; //!
    TBranch *b_MCQuark_6_PdgId; //!
    TBranch *b_MCQuark_7_Pt; //!
    TBranch *b_MCQuark_7_Phi; //!
    TBranch *b_MCQuark_7_Eta; //!
    TBranch *b_MCQuark_7_E; //!
    TBranch *b_MCQuark_7_PdgId; //!
    TBranch *b_MCQuark_8_Pt; //!
    TBranch *b_MCQuark_8_Phi; //!
    TBranch *b_MCQuark_8_Eta; //!
    TBranch *b_MCQuark_8_E; //!
    TBranch *b_MCQuark_8_PdgId; //!
    TBranch *b_MCQuark_9_Pt; //!
    TBranch *b_MCQuark_9_Phi; //!
    TBranch *b_MCQuark_9_Eta; //!
    TBranch *b_MCQuark_9_E; //!
    TBranch *b_MCQuark_9_PdgId; //!
    TBranch *b_MCQuark_10_Pt; //!
    TBranch *b_MCQuark_10_Phi; //!
    TBranch *b_MCQuark_10_Eta; //!
    TBranch *b_MCQuark_10_E; //!
    TBranch *b_MCQuark_10_PdgId; //!
    TBranch *b_MCQuark_11_Pt; //!
    TBranch *b_MCQuark_11_Phi; //!
    TBranch *b_MCQuark_11_Eta; //!
    TBranch *b_MCQuark_11_E; //!
    TBranch *b_MCQuark_11_PdgId; //!
    TBranch *b_MCQuark_12_Pt; //!
    TBranch *b_MCQuark_12_Phi; //!
    TBranch *b_MCQuark_12_Eta; //!
    TBranch *b_MCQuark_12_E; //!
    TBranch *b_MCQuark_12_PdgId; //!
    TBranch *b_MCBQuark_1_Pt; //!
    TBranch *b_MCBQuark_1_Phi; //!
    TBranch *b_MCBQuark_1_Eta; //!
    TBranch *b_MCBQuark_1_E; //!
    TBranch *b_MCBQuark_1_PdgId; //!
    TBranch *b_MCLepton_1_Pt; //!
    TBranch *b_MCLepton_1_Phi; //!
    TBranch *b_MCLepton_1_Eta; //!
    TBranch *b_MCLepton_1_E; //!
    TBranch *b_MCLepton_1_PdgId; //!
    TBranch *b_MCNeutrino_1_Pt; //!
    TBranch *b_MCNeutrino_1_Phi; //!
    TBranch *b_MCNeutrino_1_Eta; //!
    TBranch *b_MCNeutrino_1_E; //!
    TBranch *b_MCNeutrino_1_PdgId; //!
    TBranch *b_MCBQuark_2_Pt; //!
    TBranch *b_MCBQuark_2_Phi; //!
    TBranch *b_MCBQuark_2_Eta; //!
    TBranch *b_MCBQuark_2_E; //!
    TBranch *b_MCBQuark_2_PdgId; //!
    TBranch *b_MCLepton_2_Pt; //!
    TBranch *b_MCLepton_2_Phi; //!
    TBranch *b_MCLepton_2_Eta; //!
    TBranch *b_MCLepton_2_E; //!
    TBranch *b_MCLepton_2_PdgId; //!
    TBranch *b_MCNeutrino_2_Pt; //!
    TBranch *b_MCNeutrino_2_Phi; //!
    TBranch *b_MCNeutrino_2_Eta; //!
    TBranch *b_MCNeutrino_2_E; //!
    TBranch *b_MCNeutrino_2_PdgId; //!
    TBranch *b_MCBQuark_3_Pt; //!
    TBranch *b_MCBQuark_3_Phi; //!
    TBranch *b_MCBQuark_3_Eta; //!
    TBranch *b_MCBQuark_3_E; //!
    TBranch *b_MCBQuark_3_PdgId; //!
    TBranch *b_MCLepton_3_Pt; //!
    TBranch *b_MCLepton_3_Phi; //!
    TBranch *b_MCLepton_3_Eta; //!
    TBranch *b_MCLepton_3_E; //!
    TBranch *b_MCLepton_3_PdgId; //!
    TBranch *b_MCNeutrino_3_Pt; //!
    TBranch *b_MCNeutrino_3_Phi; //!
    TBranch *b_MCNeutrino_3_Eta; //!
    TBranch *b_MCNeutrino_3_E; //!
    TBranch *b_MCNeutrino_3_PdgId; //!
    TBranch *b_MCBQuark_4_Pt; //!
    TBranch *b_MCBQuark_4_Phi; //!
    TBranch *b_MCBQuark_4_Eta; //!
    TBranch *b_MCBQuark_4_E; //!
    TBranch *b_MCBQuark_4_PdgId; //!
    TBranch *b_MCLepton_4_Pt; //!
    TBranch *b_MCLepton_4_Phi; //!
    TBranch *b_MCLepton_4_Eta; //!
    TBranch *b_MCLepton_4_E; //!
    TBranch *b_MCLepton_4_PdgId; //!
    TBranch *b_MCNeutrino_4_Pt; //!
    TBranch *b_MCNeutrino_4_Phi; //!
    TBranch *b_MCNeutrino_4_Eta; //!
    TBranch *b_MCNeutrino_4_E; //!
    TBranch *b_MCNeutrino_4_PdgId; //!
    TBranch *b_PDFWeight1; //!
    TBranch *b_PDFWeight2; //!
    TBranch *b_PDFWeight3; //!
    TBranch *b_PDFWeight4; //!
    TBranch *b_PDFWeight5; //!
    TBranch *b_PDFWeight6; //!
    TBranch *b_PDFWeight7; //!
    TBranch *b_PDFWeight8; //!
    TBranch *b_PDFWeight9; //!
    TBranch *b_PDFWeight10; //!
    TBranch *b_PDFWeight11; //!
    TBranch *b_PDFWeight12; //!
    TBranch *b_PDFWeight13; //!
    TBranch *b_PDFWeight14; //!
    TBranch *b_PDFWeight15; //!
    TBranch *b_PDFWeight16; //!
    TBranch *b_PDFWeight17; //!
    TBranch *b_PDFWeight18; //!
    TBranch *b_PDFWeight19; //!
    TBranch *b_PDFWeight20; //!
    TBranch *b_PDFWeight21; //!
    TBranch *b_PDFWeight22; //!
    TBranch *b_PDFWeight23; //!
    TBranch *b_PDFWeight24; //!
    TBranch *b_PDFWeight25; //!
    TBranch *b_PDFWeight26; //!
    TBranch *b_PDFWeight27; //!
    TBranch *b_PDFWeight28; //!
    TBranch *b_PDFWeight29; //!
    TBranch *b_PDFWeight30; //!
    TBranch *b_PDFWeight31; //!
    TBranch *b_PDFWeight32; //!
    TBranch *b_PDFWeight33; //!
    TBranch *b_PDFWeight34; //!
    TBranch *b_PDFWeight35; //!
    TBranch *b_PDFWeight36; //!
    TBranch *b_PDFWeight37; //!
    TBranch *b_PDFWeight38; //!
    TBranch *b_PDFWeight39; //!
    TBranch *b_PDFWeight40; //!
    TBranch *b_PDFWeight41; //!
    TBranch *b_PDFWeight42; //!
    TBranch *b_PDFWeight43; //!
    TBranch *b_PDFWeight44; //!
    TBranch *b_PDFWeight45; //!
    TBranch *b_PDFWeight46; //!
    TBranch *b_PDFWeight47; //!
    TBranch *b_PDFWeight48; //!
    TBranch *b_PDFWeight49; //!
    TBranch *b_PDFWeight50; //!
    TBranch *b_PDFWeight51; //!
    TBranch *b_PDFWeight52; //!
    TBranch *b_PDFWeight_Alternate_Set_1; //!
    TBranch *b_PDFWeight_Alternate_Set_2; //!

    GenInfoMuonTree(TTree *tree = 0, TFile * f = 0, TString treeName = "", bool isDirect = false) : fChain(0) {
        // if parameter tree is not specified (or zero), connect the file
        // used to generate this class and read the Tree.
        if (tree == 0) {
            cout << "I am in tree = 0" << endl;
            // TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("Data.root");
            // if (!f || !f->IsOpen()) {
            //    f = new TFile("Data.root");
            // }
            if (!isDirect) {
                cout<<"inDirect"<<endl;
                TDirectory * dir = (TDirectory*) f->Get("TreesMu");
                cout<<"treeName: "<<treeName<<endl;
                if (treeName == string("TChannel_Q2Down_2J_1T_noSyst") )
                    treeName = "TbarChannel_Q2Down_2J_1T_noSyst";
                if (treeName == string("TChannel_Q2Up_2J_1T_noSyst") )
                    treeName = "TbarChannel_Q2Up_2J_1T_noSyst";
                dir->GetObject(treeName, tree);
                cout<<tree<<endl;
            } else {
                f->ls();
                tree = (TTree*) f->Get(treeName);
            }
            cout << tree << " tree afterward" << endl;

        }
        Init(tree);
    }

    virtual ~GenInfoMuonTree() {
        if (!fChain) return;
        delete fChain->GetCurrentFile();
    };

    virtual Int_t Cut(Long64_t entry) {
        return 1;
    };

    virtual Int_t GetEntry(Long64_t entry) {
        // Read contents of entry.
        if (!fChain) return 0;
        return fChain->GetEntry(entry);
    };

    virtual Long64_t LoadTree(Long64_t entry) {
        // Set the environment to read one entry
        if (!fChain) return -5;
        Long64_t centry = fChain->LoadTree(entry);
        if (centry < 0) return centry;
        if (fChain->GetTreeNumber() != fCurrent) {
            fCurrent = fChain->GetTreeNumber();
            Notify();
        }
        return centry;
    };

    virtual Bool_t Notify() {
        return kTRUE;
    };

    virtual void Show(Long64_t entry = -1) {
        if (!fChain) return;
        fChain->Show(entry);
    };

    virtual void Init(TTree *tree) {
        // The Init() function is called when the selector needs to initialize
        // a new tree or chain. Typically here the branch addresses and branch
        // pointers of the tree will be set.
        // It is normally not necessary to make changes to the generated
        // code, but the routine can be extended by the user if needed.
        // Init() will be called many times when running on PROOF
        // (once per file to be processed).

        // Set branch addresses and branch pointers
        if (!tree) {
            cout << "It was not tree" << endl;
            return;
        }
        fChain = tree;
        cout << "chain: " << fChain << endl;
        fCurrent = -1;
        fChain->SetMakeClass(1);

        fChain->SetBranchAddress("eta", &eta, &b_eta);
        fChain->SetBranchAddress("costhetalj", &costhetalj, &b_costhetalj);
        fChain->SetBranchAddress("costhetalbl", &costhetalbl, &b_costhetalbl);
        fChain->SetBranchAddress("mtwMass", &mtwMass, &b_mtwMass);
        fChain->SetBranchAddress("charge", &charge, &b_charge);
        fChain->SetBranchAddress("runid", &runid, &b_runid);
        fChain->SetBranchAddress("lumiid", &lumiid, &b_lumiid);
        fChain->SetBranchAddress("eventid", &eventid, &b_eventid);
        fChain->SetBranchAddress("weight", &weight, &b_weight);
        fChain->SetBranchAddress("totalWeight", &totalWeight, &b_totalWeight);
        fChain->SetBranchAddress("bWeight", &bWeight, &b_bWeight);
        fChain->SetBranchAddress("bWeightBTagUp", &bWeightBTagUp, &b_bWeightBTagUp);
        fChain->SetBranchAddress("bWeightBTagDown", &bWeightBTagDown, &b_bWeightBTagDown);
        fChain->SetBranchAddress("bWeightMisTagUp", &bWeightMisTagUp, &b_bWeightMisTagUp);
        fChain->SetBranchAddress("bWeightMisTagDown", &bWeightMisTagDown, &b_bWeightMisTagDown);
        fChain->SetBranchAddress("PUWeight", &PUWeight, &b_PUWeight);
        fChain->SetBranchAddress("PUWeightPUUp", &PUWeightPUUp, &b_PUWeightPUUp);
        fChain->SetBranchAddress("PUWeightPUDown", &PUWeightPUDown, &b_PUWeightPUDown);
        fChain->SetBranchAddress("turnOnWeight", &turnOnWeight, &b_turnOnWeight);
        fChain->SetBranchAddress("turnOnReWeight", &turnOnReWeight, &b_turnOnReWeight);
        fChain->SetBranchAddress("turnOnWeightJetTrig1Up", &turnOnWeightJetTrig1Up, &b_turnOnWeightJetTrig1Up);
        fChain->SetBranchAddress("turnOnWeightJetTrig1Down", &turnOnWeightJetTrig1Down, &b_turnOnWeightJetTrig1Down);
        fChain->SetBranchAddress("turnOnWeightJetTrig2Up", &turnOnWeightJetTrig2Up, &b_turnOnWeightJetTrig2Up);
        fChain->SetBranchAddress("turnOnWeightJetTrig2Down", &turnOnWeightJetTrig2Down, &b_turnOnWeightJetTrig2Down);
        fChain->SetBranchAddress("turnOnWeightJetTrig3Up", &turnOnWeightJetTrig3Up, &b_turnOnWeightJetTrig3Up);
        fChain->SetBranchAddress("turnOnWeightJetTrig3Down", &turnOnWeightJetTrig3Down, &b_turnOnWeightJetTrig3Down);
        fChain->SetBranchAddress("turnOnWeightBTagTrig1Up", &turnOnWeightBTagTrig1Up, &b_turnOnWeightBTagTrig1Up);
        fChain->SetBranchAddress("turnOnWeightBTagTrig1Down", &turnOnWeightBTagTrig1Down, &b_turnOnWeightBTagTrig1Down);
        fChain->SetBranchAddress("turnOnWeightBTagTrig2Up", &turnOnWeightBTagTrig2Up, &b_turnOnWeightBTagTrig2Up);
        fChain->SetBranchAddress("turnOnWeightBTagTrig2Down", &turnOnWeightBTagTrig2Down, &b_turnOnWeightBTagTrig2Down);
        fChain->SetBranchAddress("turnOnWeightBTagTrig3Up", &turnOnWeightBTagTrig3Up, &b_turnOnWeightBTagTrig3Up);
        fChain->SetBranchAddress("turnOnWeightBTagTrig3Down", &turnOnWeightBTagTrig3Down, &b_turnOnWeightBTagTrig3Down);
        fChain->SetBranchAddress("leptonPt", &leptonPt, &b_leptonPt);
        fChain->SetBranchAddress("leptonEta", &leptonEta, &b_leptonEta);
        fChain->SetBranchAddress("leptonPhi", &leptonPhi, &b_leptonPhi);
        fChain->SetBranchAddress("leptonDeltaCorrectedRelIso", &leptonDeltaCorrectedRelIso, &b_leptonDeltaCorrectedRelIso);
        fChain->SetBranchAddress("leptonRhoCorrectedRelIso", &leptonRhoCorrectedRelIso, &b_leptonRhoCorrectedRelIso);
        fChain->SetBranchAddress("leptonEff", &leptonEff, &b_leptonEff);
        fChain->SetBranchAddress("leptonEffB", &leptonEffB, &b_leptonEffB);
        fChain->SetBranchAddress("fJetPt", &fJetPt, &b_fJetPt);
        fChain->SetBranchAddress("fJetE", &fJetE, &b_fJetE);
        fChain->SetBranchAddress("fJetEta", &fJetEta, &b_fJetEta);
        fChain->SetBranchAddress("fJetPhi", &fJetPhi, &b_fJetPhi);
        fChain->SetBranchAddress("fJetBtag", &fJetBtag, &b_fJetBtag);
        fChain->SetBranchAddress("fJetFlavour", &fJetFlavour, &b_fJetFlavour);
        fChain->SetBranchAddress("fJetPUID", &fJetPUID, &b_fJetPUID);
        fChain->SetBranchAddress("fJetPUWP", &fJetPUWP, &b_fJetPUWP);
        fChain->SetBranchAddress("fJetBeta", &fJetBeta, &b_fJetBeta);
        fChain->SetBranchAddress("fJetDZ", &fJetDZ, &b_fJetDZ);
        fChain->SetBranchAddress("fJetRMS", &fJetRMS, &b_fJetRMS);
        fChain->SetBranchAddress("bJetBeta", &bJetBeta, &b_bJetBeta);
        fChain->SetBranchAddress("bJetDZ", &bJetDZ, &b_bJetDZ);
        fChain->SetBranchAddress("bJetRMS", &bJetRMS, &b_bJetRMS);
        fChain->SetBranchAddress("bJetPt", &bJetPt, &b_bJetPt);
        fChain->SetBranchAddress("bJetE", &bJetE, &b_bJetE);
        fChain->SetBranchAddress("bJetEta", &bJetEta, &b_bJetEta);
        fChain->SetBranchAddress("bJetPhi", &bJetPhi, &b_bJetPhi);
        fChain->SetBranchAddress("bJetBtag", &bJetBtag, &b_bJetBtag);
        fChain->SetBranchAddress("bJetFlavour", &bJetFlavour, &b_bJetFlavour);
        fChain->SetBranchAddress("bJetPUID", &bJetPUID, &b_bJetPUID);
        fChain->SetBranchAddress("bJetPUWP", &bJetPUWP, &b_bJetPUWP);
        fChain->SetBranchAddress("firstJetPt", &firstJetPt, &b_firstJetPt);
        fChain->SetBranchAddress("firstJetEta", &firstJetEta, &b_firstJetEta);
        fChain->SetBranchAddress("firstJetPhi", &firstJetPhi, &b_firstJetPhi);
        fChain->SetBranchAddress("firstJetE", &firstJetE, &b_firstJetE);
        fChain->SetBranchAddress("firstJetFlavour", &firstJetFlavour, &b_firstJetFlavour);
        fChain->SetBranchAddress("secondJetPt", &secondJetPt, &b_secondJetPt);
        fChain->SetBranchAddress("secondJetEta", &secondJetEta, &b_secondJetEta);
        fChain->SetBranchAddress("secondJetPhi", &secondJetPhi, &b_secondJetPhi);
        fChain->SetBranchAddress("secondJetE", &secondJetE, &b_secondJetE);
        fChain->SetBranchAddress("secondJetFlavour", &secondJetFlavour, &b_secondJetFlavour);
        fChain->SetBranchAddress("eventFlavour", &eventFlavour, &b_eventFlavour);
        fChain->SetBranchAddress("metPt", &metPt, &b_metPt);
        fChain->SetBranchAddress("metPhi", &metPhi, &b_metPhi);
        fChain->SetBranchAddress("HT", &HT, &b_HT);
        fChain->SetBranchAddress("topMass", &topMass, &b_topMass);
        fChain->SetBranchAddress("topMtw", &topMtw, &b_topMtw);
        fChain->SetBranchAddress("topPt", &topPt, &b_topPt);
        fChain->SetBranchAddress("topPhi", &topPhi, &b_topPhi);
        fChain->SetBranchAddress("topEta", &topEta, &b_topEta);
        fChain->SetBranchAddress("topE", &topE, &b_topE);
        fChain->SetBranchAddress("ID", &ID, &b_ID);
        fChain->SetBranchAddress("nVertices", &nVertices, &b_nVertices);
        fChain->SetBranchAddress("nGoodVertices", &nGoodVertices, &b_nGoodVertices);
        fChain->SetBranchAddress("totalEnergy", &totalEnergy, &b_totalEnergy);
        fChain->SetBranchAddress("totalMomentum", &totalMomentum, &b_totalMomentum);
        fChain->SetBranchAddress("lowBTag", &lowBTag, &b_lowBTag);
        fChain->SetBranchAddress("highBTag", &highBTag, &b_highBTag);
        fChain->SetBranchAddress("nMCTruthLeptons", &nMCTruthLeptons, &b_nMCTruthLeptons);
        fChain->SetBranchAddress("MCTop_1_Pt", &MCTop_1_Pt, &b_MCTop_1_Pt);
        fChain->SetBranchAddress("MCTop_1_Phi", &MCTop_1_Phi, &b_MCTop_1_Phi);
        fChain->SetBranchAddress("MCTop_1_Eta", &MCTop_1_Eta, &b_MCTop_1_Eta);
        fChain->SetBranchAddress("MCTop_1_E", &MCTop_1_E, &b_MCTop_1_E);
        fChain->SetBranchAddress("MCTop_1_PdgId", &MCTop_1_PdgId, &b_MCTop_1_PdgId);
        fChain->SetBranchAddress("MCTopLepton_1_Pt", &MCTopLepton_1_Pt, &b_MCTopLepton_1_Pt);
        fChain->SetBranchAddress("MCTopLepton_1_Phi", &MCTopLepton_1_Phi, &b_MCTopLepton_1_Phi);
        fChain->SetBranchAddress("MCTopLepton_1_Eta", &MCTopLepton_1_Eta, &b_MCTopLepton_1_Eta);
        fChain->SetBranchAddress("MCTopLepton_1_E", &MCTopLepton_1_E, &b_MCTopLepton_1_E);
        fChain->SetBranchAddress("MCTopLepton_1_PdgId", &MCTopLepton_1_PdgId, &b_MCTopLepton_1_PdgId);
        fChain->SetBranchAddress("MCTopLepton_1_MotherId", &MCTopLepton_1_MotherId, &b_MCTopLepton_1_MotherId);
        fChain->SetBranchAddress("MCTopNeutrino_1_Pt", &MCTopNeutrino_1_Pt, &b_MCTopNeutrino_1_Pt);
        fChain->SetBranchAddress("MCTopNeutrino_1_Phi", &MCTopNeutrino_1_Phi, &b_MCTopNeutrino_1_Phi);
        fChain->SetBranchAddress("MCTopNeutrino_1_Eta", &MCTopNeutrino_1_Eta, &b_MCTopNeutrino_1_Eta);
        fChain->SetBranchAddress("MCTopNeutrino_1_E", &MCTopNeutrino_1_E, &b_MCTopNeutrino_1_E);
        fChain->SetBranchAddress("MCTopNeutrino_1_PdgId", &MCTopNeutrino_1_PdgId, &b_MCTopNeutrino_1_PdgId);
        fChain->SetBranchAddress("MCTopNeutrino_1_MotherId", &MCTopNeutrino_1_MotherId, &b_MCTopNeutrino_1_MotherId);
        fChain->SetBranchAddress("MCTopQuark_1_Pt", &MCTopQuark_1_Pt, &b_MCTopQuark_1_Pt);
        fChain->SetBranchAddress("MCTopQuark_1_Phi", &MCTopQuark_1_Phi, &b_MCTopQuark_1_Phi);
        fChain->SetBranchAddress("MCTopQuark_1_Eta", &MCTopQuark_1_Eta, &b_MCTopQuark_1_Eta);
        fChain->SetBranchAddress("MCTopQuark_1_E", &MCTopQuark_1_E, &b_MCTopQuark_1_E);
        fChain->SetBranchAddress("MCTopQuark_1_PdgId", &MCTopQuark_1_PdgId, &b_MCTopQuark_1_PdgId);
        fChain->SetBranchAddress("MCTopQuark_1_MotherId", &MCTopQuark_1_MotherId, &b_MCTopQuark_1_MotherId);
        fChain->SetBranchAddress("MCTopQuarkBar_1_Pt", &MCTopQuarkBar_1_Pt, &b_MCTopQuarkBar_1_Pt);
        fChain->SetBranchAddress("MCTopQuarkBar_1_Phi", &MCTopQuarkBar_1_Phi, &b_MCTopQuarkBar_1_Phi);
        fChain->SetBranchAddress("MCTopQuarkBar_1_Eta", &MCTopQuarkBar_1_Eta, &b_MCTopQuarkBar_1_Eta);
        fChain->SetBranchAddress("MCTopQuarkBar_1_E", &MCTopQuarkBar_1_E, &b_MCTopQuarkBar_1_E);
        fChain->SetBranchAddress("MCTopQuarkBar_1_PdgId", &MCTopQuarkBar_1_PdgId, &b_MCTopQuarkBar_1_PdgId);
        fChain->SetBranchAddress("MCTopQuarkBar_1_MotherId", &MCTopQuarkBar_1_MotherId, &b_MCTopQuarkBar_1_MotherId);
        fChain->SetBranchAddress("MCTopBQuark_1_Pt", &MCTopBQuark_1_Pt, &b_MCTopBQuark_1_Pt);
        fChain->SetBranchAddress("MCTopBQuark_1_Phi", &MCTopBQuark_1_Phi, &b_MCTopBQuark_1_Phi);
        fChain->SetBranchAddress("MCTopBQuark_1_Eta", &MCTopBQuark_1_Eta, &b_MCTopBQuark_1_Eta);
        fChain->SetBranchAddress("MCTopBQuark_1_E", &MCTopBQuark_1_E, &b_MCTopBQuark_1_E);
        fChain->SetBranchAddress("MCTopBQuark_1_PdgId", &MCTopBQuark_1_PdgId, &b_MCTopBQuark_1_PdgId);
        fChain->SetBranchAddress("MCTopBQuark_1_MotherId", &MCTopBQuark_1_MotherId, &b_MCTopBQuark_1_MotherId);
        fChain->SetBranchAddress("MCTopW_1_Pt", &MCTopW_1_Pt, &b_MCTopW_1_Pt);
        fChain->SetBranchAddress("MCTopW_1_Phi", &MCTopW_1_Phi, &b_MCTopW_1_Phi);
        fChain->SetBranchAddress("MCTopW_1_Eta", &MCTopW_1_Eta, &b_MCTopW_1_Eta);
        fChain->SetBranchAddress("MCTopW_1_E", &MCTopW_1_E, &b_MCTopW_1_E);
        fChain->SetBranchAddress("MCTopW_1_PdgId", &MCTopW_1_PdgId, &b_MCTopW_1_PdgId);
        fChain->SetBranchAddress("MCTopW_1_DauOneId", &MCTopW_1_DauOneId, &b_MCTopW_1_DauOneId);
        //    fChain->SetBranchAddress("nMCTruthLeptons", &nMCTruthLeptons, &b_nMCTruthLeptons);
        fChain->SetBranchAddress("MCTop_2_Pt", &MCTop_2_Pt, &b_MCTop_2_Pt);
        fChain->SetBranchAddress("MCTop_2_Phi", &MCTop_2_Phi, &b_MCTop_2_Phi);
        fChain->SetBranchAddress("MCTop_2_Eta", &MCTop_2_Eta, &b_MCTop_2_Eta);
        fChain->SetBranchAddress("MCTop_2_E", &MCTop_2_E, &b_MCTop_2_E);
        fChain->SetBranchAddress("MCTop_2_PdgId", &MCTop_2_PdgId, &b_MCTop_2_PdgId);
        fChain->SetBranchAddress("MCTopLepton_2_Pt", &MCTopLepton_2_Pt, &b_MCTopLepton_2_Pt);
        fChain->SetBranchAddress("MCTopLepton_2_Phi", &MCTopLepton_2_Phi, &b_MCTopLepton_2_Phi);
        fChain->SetBranchAddress("MCTopLepton_2_Eta", &MCTopLepton_2_Eta, &b_MCTopLepton_2_Eta);
        fChain->SetBranchAddress("MCTopLepton_2_E", &MCTopLepton_2_E, &b_MCTopLepton_2_E);
        fChain->SetBranchAddress("MCTopLepton_2_PdgId", &MCTopLepton_2_PdgId, &b_MCTopLepton_2_PdgId);
        fChain->SetBranchAddress("MCTopLepton_2_MotherId", &MCTopLepton_2_MotherId, &b_MCTopLepton_2_MotherId);
        fChain->SetBranchAddress("MCTopNeutrino_2_Pt", &MCTopNeutrino_2_Pt, &b_MCTopNeutrino_2_Pt);
        fChain->SetBranchAddress("MCTopNeutrino_2_Phi", &MCTopNeutrino_2_Phi, &b_MCTopNeutrino_2_Phi);
        fChain->SetBranchAddress("MCTopNeutrino_2_Eta", &MCTopNeutrino_2_Eta, &b_MCTopNeutrino_2_Eta);
        fChain->SetBranchAddress("MCTopNeutrino_2_E", &MCTopNeutrino_2_E, &b_MCTopNeutrino_2_E);
        fChain->SetBranchAddress("MCTopNeutrino_2_PdgId", &MCTopNeutrino_2_PdgId, &b_MCTopNeutrino_2_PdgId);
        fChain->SetBranchAddress("MCTopNeutrino_2_MotherId", &MCTopNeutrino_2_MotherId, &b_MCTopNeutrino_2_MotherId);
        fChain->SetBranchAddress("MCTopQuark_2_Pt", &MCTopQuark_2_Pt, &b_MCTopQuark_2_Pt);
        fChain->SetBranchAddress("MCTopQuark_2_Phi", &MCTopQuark_2_Phi, &b_MCTopQuark_2_Phi);
        fChain->SetBranchAddress("MCTopQuark_2_Eta", &MCTopQuark_2_Eta, &b_MCTopQuark_2_Eta);
        fChain->SetBranchAddress("MCTopQuark_2_E", &MCTopQuark_2_E, &b_MCTopQuark_2_E);
        fChain->SetBranchAddress("MCTopQuark_2_PdgId", &MCTopQuark_2_PdgId, &b_MCTopQuark_2_PdgId);
        fChain->SetBranchAddress("MCTopQuark_2_MotherId", &MCTopQuark_2_MotherId, &b_MCTopQuark_2_MotherId);
        fChain->SetBranchAddress("MCTopQuarkBar_2_Pt", &MCTopQuarkBar_2_Pt, &b_MCTopQuarkBar_2_Pt);
        fChain->SetBranchAddress("MCTopQuarkBar_2_Phi", &MCTopQuarkBar_2_Phi, &b_MCTopQuarkBar_2_Phi);
        fChain->SetBranchAddress("MCTopQuarkBar_2_Eta", &MCTopQuarkBar_2_Eta, &b_MCTopQuarkBar_2_Eta);
        fChain->SetBranchAddress("MCTopQuarkBar_2_E", &MCTopQuarkBar_2_E, &b_MCTopQuarkBar_2_E);
        fChain->SetBranchAddress("MCTopQuarkBar_2_PdgId", &MCTopQuarkBar_2_PdgId, &b_MCTopQuarkBar_2_PdgId);
        fChain->SetBranchAddress("MCTopQuarkBar_2_MotherId", &MCTopQuarkBar_2_MotherId, &b_MCTopQuarkBar_2_MotherId);
        fChain->SetBranchAddress("MCTopBQuark_2_Pt", &MCTopBQuark_2_Pt, &b_MCTopBQuark_2_Pt);
        fChain->SetBranchAddress("MCTopBQuark_2_Phi", &MCTopBQuark_2_Phi, &b_MCTopBQuark_2_Phi);
        fChain->SetBranchAddress("MCTopBQuark_2_Eta", &MCTopBQuark_2_Eta, &b_MCTopBQuark_2_Eta);
        fChain->SetBranchAddress("MCTopBQuark_2_E", &MCTopBQuark_2_E, &b_MCTopBQuark_2_E);
        fChain->SetBranchAddress("MCTopBQuark_2_PdgId", &MCTopBQuark_2_PdgId, &b_MCTopBQuark_2_PdgId);
        fChain->SetBranchAddress("MCTopBQuark_2_MotherId", &MCTopBQuark_2_MotherId, &b_MCTopBQuark_2_MotherId);
        fChain->SetBranchAddress("MCTopW_2_Pt", &MCTopW_2_Pt, &b_MCTopW_2_Pt);
        fChain->SetBranchAddress("MCTopW_2_Phi", &MCTopW_2_Phi, &b_MCTopW_2_Phi);
        fChain->SetBranchAddress("MCTopW_2_Eta", &MCTopW_2_Eta, &b_MCTopW_2_Eta);
        fChain->SetBranchAddress("MCTopW_2_E", &MCTopW_2_E, &b_MCTopW_2_E);
        fChain->SetBranchAddress("MCTopW_2_PdgId", &MCTopW_2_PdgId, &b_MCTopW_2_PdgId);
        fChain->SetBranchAddress("MCTopW_2_DauOneId", &MCTopW_2_DauOneId, &b_MCTopW_2_DauOneId);
        fChain->SetBranchAddress("MCQuark_1_Pt", &MCQuark_1_Pt, &b_MCQuark_1_Pt);
        fChain->SetBranchAddress("MCQuark_1_Phi", &MCQuark_1_Phi, &b_MCQuark_1_Phi);
        fChain->SetBranchAddress("MCQuark_1_Eta", &MCQuark_1_Eta, &b_MCQuark_1_Eta);
        fChain->SetBranchAddress("MCQuark_1_E", &MCQuark_1_E, &b_MCQuark_1_E);
        fChain->SetBranchAddress("MCQuark_1_PdgId", &MCQuark_1_PdgId, &b_MCQuark_1_PdgId);
        fChain->SetBranchAddress("MCQuark_2_Pt", &MCQuark_2_Pt, &b_MCQuark_2_Pt);
        fChain->SetBranchAddress("MCQuark_2_Phi", &MCQuark_2_Phi, &b_MCQuark_2_Phi);
        fChain->SetBranchAddress("MCQuark_2_Eta", &MCQuark_2_Eta, &b_MCQuark_2_Eta);
        fChain->SetBranchAddress("MCQuark_2_E", &MCQuark_2_E, &b_MCQuark_2_E);
        fChain->SetBranchAddress("MCQuark_2_PdgId", &MCQuark_2_PdgId, &b_MCQuark_2_PdgId);
        fChain->SetBranchAddress("MCQuark_3_Pt", &MCQuark_3_Pt, &b_MCQuark_3_Pt);
        fChain->SetBranchAddress("MCQuark_3_Phi", &MCQuark_3_Phi, &b_MCQuark_3_Phi);
        fChain->SetBranchAddress("MCQuark_3_Eta", &MCQuark_3_Eta, &b_MCQuark_3_Eta);
        fChain->SetBranchAddress("MCQuark_3_E", &MCQuark_3_E, &b_MCQuark_3_E);
        fChain->SetBranchAddress("MCQuark_3_PdgId", &MCQuark_3_PdgId, &b_MCQuark_3_PdgId);
        fChain->SetBranchAddress("MCQuark_4_Pt", &MCQuark_4_Pt, &b_MCQuark_4_Pt);
        fChain->SetBranchAddress("MCQuark_4_Phi", &MCQuark_4_Phi, &b_MCQuark_4_Phi);
        fChain->SetBranchAddress("MCQuark_4_Eta", &MCQuark_4_Eta, &b_MCQuark_4_Eta);
        fChain->SetBranchAddress("MCQuark_4_E", &MCQuark_4_E, &b_MCQuark_4_E);
        fChain->SetBranchAddress("MCQuark_4_PdgId", &MCQuark_4_PdgId, &b_MCQuark_4_PdgId);
        fChain->SetBranchAddress("MCQuark_5_Pt", &MCQuark_5_Pt, &b_MCQuark_5_Pt);
        fChain->SetBranchAddress("MCQuark_5_Phi", &MCQuark_5_Phi, &b_MCQuark_5_Phi);
        fChain->SetBranchAddress("MCQuark_5_Eta", &MCQuark_5_Eta, &b_MCQuark_5_Eta);
        fChain->SetBranchAddress("MCQuark_5_E", &MCQuark_5_E, &b_MCQuark_5_E);
        fChain->SetBranchAddress("MCQuark_5_PdgId", &MCQuark_5_PdgId, &b_MCQuark_5_PdgId);
        fChain->SetBranchAddress("MCQuark_6_Pt", &MCQuark_6_Pt, &b_MCQuark_6_Pt);
        fChain->SetBranchAddress("MCQuark_6_Phi", &MCQuark_6_Phi, &b_MCQuark_6_Phi);
        fChain->SetBranchAddress("MCQuark_6_Eta", &MCQuark_6_Eta, &b_MCQuark_6_Eta);
        fChain->SetBranchAddress("MCQuark_6_E", &MCQuark_6_E, &b_MCQuark_6_E);
        fChain->SetBranchAddress("MCQuark_6_PdgId", &MCQuark_6_PdgId, &b_MCQuark_6_PdgId);
        fChain->SetBranchAddress("MCQuark_7_Pt", &MCQuark_7_Pt, &b_MCQuark_7_Pt);
        fChain->SetBranchAddress("MCQuark_7_Phi", &MCQuark_7_Phi, &b_MCQuark_7_Phi);
        fChain->SetBranchAddress("MCQuark_7_Eta", &MCQuark_7_Eta, &b_MCQuark_7_Eta);
        fChain->SetBranchAddress("MCQuark_7_E", &MCQuark_7_E, &b_MCQuark_7_E);
        fChain->SetBranchAddress("MCQuark_7_PdgId", &MCQuark_7_PdgId, &b_MCQuark_7_PdgId);
        fChain->SetBranchAddress("MCQuark_8_Pt", &MCQuark_8_Pt, &b_MCQuark_8_Pt);
        fChain->SetBranchAddress("MCQuark_8_Phi", &MCQuark_8_Phi, &b_MCQuark_8_Phi);
        fChain->SetBranchAddress("MCQuark_8_Eta", &MCQuark_8_Eta, &b_MCQuark_8_Eta);
        fChain->SetBranchAddress("MCQuark_8_E", &MCQuark_8_E, &b_MCQuark_8_E);
        fChain->SetBranchAddress("MCQuark_8_PdgId", &MCQuark_8_PdgId, &b_MCQuark_8_PdgId);
        fChain->SetBranchAddress("MCQuark_9_Pt", &MCQuark_9_Pt, &b_MCQuark_9_Pt);
        fChain->SetBranchAddress("MCQuark_9_Phi", &MCQuark_9_Phi, &b_MCQuark_9_Phi);
        fChain->SetBranchAddress("MCQuark_9_Eta", &MCQuark_9_Eta, &b_MCQuark_9_Eta);
        fChain->SetBranchAddress("MCQuark_9_E", &MCQuark_9_E, &b_MCQuark_9_E);
        fChain->SetBranchAddress("MCQuark_9_PdgId", &MCQuark_9_PdgId, &b_MCQuark_9_PdgId);
        fChain->SetBranchAddress("MCQuark_10_Pt", &MCQuark_10_Pt, &b_MCQuark_10_Pt);
        fChain->SetBranchAddress("MCQuark_10_Phi", &MCQuark_10_Phi, &b_MCQuark_10_Phi);
        fChain->SetBranchAddress("MCQuark_10_Eta", &MCQuark_10_Eta, &b_MCQuark_10_Eta);
        fChain->SetBranchAddress("MCQuark_10_E", &MCQuark_10_E, &b_MCQuark_10_E);
        fChain->SetBranchAddress("MCQuark_10_PdgId", &MCQuark_10_PdgId, &b_MCQuark_10_PdgId);
        fChain->SetBranchAddress("MCQuark_11_Pt", &MCQuark_11_Pt, &b_MCQuark_11_Pt);
        fChain->SetBranchAddress("MCQuark_11_Phi", &MCQuark_11_Phi, &b_MCQuark_11_Phi);
        fChain->SetBranchAddress("MCQuark_11_Eta", &MCQuark_11_Eta, &b_MCQuark_11_Eta);
        fChain->SetBranchAddress("MCQuark_11_E", &MCQuark_11_E, &b_MCQuark_11_E);
        fChain->SetBranchAddress("MCQuark_11_PdgId", &MCQuark_11_PdgId, &b_MCQuark_11_PdgId);
        fChain->SetBranchAddress("MCQuark_12_Pt", &MCQuark_12_Pt, &b_MCQuark_12_Pt);
        fChain->SetBranchAddress("MCQuark_12_Phi", &MCQuark_12_Phi, &b_MCQuark_12_Phi);
        fChain->SetBranchAddress("MCQuark_12_Eta", &MCQuark_12_Eta, &b_MCQuark_12_Eta);
        fChain->SetBranchAddress("MCQuark_12_E", &MCQuark_12_E, &b_MCQuark_12_E);
        fChain->SetBranchAddress("MCQuark_12_PdgId", &MCQuark_12_PdgId, &b_MCQuark_12_PdgId);
        fChain->SetBranchAddress("MCBQuark_1_Pt", &MCBQuark_1_Pt, &b_MCBQuark_1_Pt);
        fChain->SetBranchAddress("MCBQuark_1_Phi", &MCBQuark_1_Phi, &b_MCBQuark_1_Phi);
        fChain->SetBranchAddress("MCBQuark_1_Eta", &MCBQuark_1_Eta, &b_MCBQuark_1_Eta);
        fChain->SetBranchAddress("MCBQuark_1_E", &MCBQuark_1_E, &b_MCBQuark_1_E);
        fChain->SetBranchAddress("MCBQuark_1_PdgId", &MCBQuark_1_PdgId, &b_MCBQuark_1_PdgId);
        fChain->SetBranchAddress("MCLepton_1_Pt", &MCLepton_1_Pt, &b_MCLepton_1_Pt);
        fChain->SetBranchAddress("MCLepton_1_Phi", &MCLepton_1_Phi, &b_MCLepton_1_Phi);
        fChain->SetBranchAddress("MCLepton_1_Eta", &MCLepton_1_Eta, &b_MCLepton_1_Eta);
        fChain->SetBranchAddress("MCLepton_1_E", &MCLepton_1_E, &b_MCLepton_1_E);
        fChain->SetBranchAddress("MCLepton_1_PdgId", &MCLepton_1_PdgId, &b_MCLepton_1_PdgId);
        fChain->SetBranchAddress("MCNeutrino_1_Pt", &MCNeutrino_1_Pt, &b_MCNeutrino_1_Pt);
        fChain->SetBranchAddress("MCNeutrino_1_Phi", &MCNeutrino_1_Phi, &b_MCNeutrino_1_Phi);
        fChain->SetBranchAddress("MCNeutrino_1_Eta", &MCNeutrino_1_Eta, &b_MCNeutrino_1_Eta);
        fChain->SetBranchAddress("MCNeutrino_1_E", &MCNeutrino_1_E, &b_MCNeutrino_1_E);
        fChain->SetBranchAddress("MCNeutrino_1_PdgId", &MCNeutrino_1_PdgId, &b_MCNeutrino_1_PdgId);
        fChain->SetBranchAddress("MCBQuark_2_Pt", &MCBQuark_2_Pt, &b_MCBQuark_2_Pt);
        fChain->SetBranchAddress("MCBQuark_2_Phi", &MCBQuark_2_Phi, &b_MCBQuark_2_Phi);
        fChain->SetBranchAddress("MCBQuark_2_Eta", &MCBQuark_2_Eta, &b_MCBQuark_2_Eta);
        fChain->SetBranchAddress("MCBQuark_2_E", &MCBQuark_2_E, &b_MCBQuark_2_E);
        fChain->SetBranchAddress("MCBQuark_2_PdgId", &MCBQuark_2_PdgId, &b_MCBQuark_2_PdgId);
        fChain->SetBranchAddress("MCLepton_2_Pt", &MCLepton_2_Pt, &b_MCLepton_2_Pt);
        fChain->SetBranchAddress("MCLepton_2_Phi", &MCLepton_2_Phi, &b_MCLepton_2_Phi);
        fChain->SetBranchAddress("MCLepton_2_Eta", &MCLepton_2_Eta, &b_MCLepton_2_Eta);
        fChain->SetBranchAddress("MCLepton_2_E", &MCLepton_2_E, &b_MCLepton_2_E);
        fChain->SetBranchAddress("MCLepton_2_PdgId", &MCLepton_2_PdgId, &b_MCLepton_2_PdgId);
        fChain->SetBranchAddress("MCNeutrino_2_Pt", &MCNeutrino_2_Pt, &b_MCNeutrino_2_Pt);
        fChain->SetBranchAddress("MCNeutrino_2_Phi", &MCNeutrino_2_Phi, &b_MCNeutrino_2_Phi);
        fChain->SetBranchAddress("MCNeutrino_2_Eta", &MCNeutrino_2_Eta, &b_MCNeutrino_2_Eta);
        fChain->SetBranchAddress("MCNeutrino_2_E", &MCNeutrino_2_E, &b_MCNeutrino_2_E);
        fChain->SetBranchAddress("MCNeutrino_2_PdgId", &MCNeutrino_2_PdgId, &b_MCNeutrino_2_PdgId);
        fChain->SetBranchAddress("MCBQuark_3_Pt", &MCBQuark_3_Pt, &b_MCBQuark_3_Pt);
        fChain->SetBranchAddress("MCBQuark_3_Phi", &MCBQuark_3_Phi, &b_MCBQuark_3_Phi);
        fChain->SetBranchAddress("MCBQuark_3_Eta", &MCBQuark_3_Eta, &b_MCBQuark_3_Eta);
        fChain->SetBranchAddress("MCBQuark_3_E", &MCBQuark_3_E, &b_MCBQuark_3_E);
        fChain->SetBranchAddress("MCBQuark_3_PdgId", &MCBQuark_3_PdgId, &b_MCBQuark_3_PdgId);
        fChain->SetBranchAddress("MCLepton_3_Pt", &MCLepton_3_Pt, &b_MCLepton_3_Pt);
        fChain->SetBranchAddress("MCLepton_3_Phi", &MCLepton_3_Phi, &b_MCLepton_3_Phi);
        fChain->SetBranchAddress("MCLepton_3_Eta", &MCLepton_3_Eta, &b_MCLepton_3_Eta);
        fChain->SetBranchAddress("MCLepton_3_E", &MCLepton_3_E, &b_MCLepton_3_E);
        fChain->SetBranchAddress("MCLepton_3_PdgId", &MCLepton_3_PdgId, &b_MCLepton_3_PdgId);
        fChain->SetBranchAddress("MCNeutrino_3_Pt", &MCNeutrino_3_Pt, &b_MCNeutrino_3_Pt);
        fChain->SetBranchAddress("MCNeutrino_3_Phi", &MCNeutrino_3_Phi, &b_MCNeutrino_3_Phi);
        fChain->SetBranchAddress("MCNeutrino_3_Eta", &MCNeutrino_3_Eta, &b_MCNeutrino_3_Eta);
        fChain->SetBranchAddress("MCNeutrino_3_E", &MCNeutrino_3_E, &b_MCNeutrino_3_E);
        fChain->SetBranchAddress("MCNeutrino_3_PdgId", &MCNeutrino_3_PdgId, &b_MCNeutrino_3_PdgId);
        fChain->SetBranchAddress("MCBQuark_4_Pt", &MCBQuark_4_Pt, &b_MCBQuark_4_Pt);
        fChain->SetBranchAddress("MCBQuark_4_Phi", &MCBQuark_4_Phi, &b_MCBQuark_4_Phi);
        fChain->SetBranchAddress("MCBQuark_4_Eta", &MCBQuark_4_Eta, &b_MCBQuark_4_Eta);
        fChain->SetBranchAddress("MCBQuark_4_E", &MCBQuark_4_E, &b_MCBQuark_4_E);
        fChain->SetBranchAddress("MCBQuark_4_PdgId", &MCBQuark_4_PdgId, &b_MCBQuark_4_PdgId);
        fChain->SetBranchAddress("MCLepton_4_Pt", &MCLepton_4_Pt, &b_MCLepton_4_Pt);
        fChain->SetBranchAddress("MCLepton_4_Phi", &MCLepton_4_Phi, &b_MCLepton_4_Phi);
        fChain->SetBranchAddress("MCLepton_4_Eta", &MCLepton_4_Eta, &b_MCLepton_4_Eta);
        fChain->SetBranchAddress("MCLepton_4_E", &MCLepton_4_E, &b_MCLepton_4_E);
        fChain->SetBranchAddress("MCLepton_4_PdgId", &MCLepton_4_PdgId, &b_MCLepton_4_PdgId);
        fChain->SetBranchAddress("MCNeutrino_4_Pt", &MCNeutrino_4_Pt, &b_MCNeutrino_4_Pt);
        fChain->SetBranchAddress("MCNeutrino_4_Phi", &MCNeutrino_4_Phi, &b_MCNeutrino_4_Phi);
        fChain->SetBranchAddress("MCNeutrino_4_Eta", &MCNeutrino_4_Eta, &b_MCNeutrino_4_Eta);
        fChain->SetBranchAddress("MCNeutrino_4_E", &MCNeutrino_4_E, &b_MCNeutrino_4_E);
        fChain->SetBranchAddress("MCNeutrino_4_PdgId", &MCNeutrino_4_PdgId, &b_MCNeutrino_4_PdgId);
        fChain->SetBranchAddress("PDFWeight1", &PDFWeight1, &b_PDFWeight1);
        fChain->SetBranchAddress("PDFWeight2", &PDFWeight2, &b_PDFWeight2);
        fChain->SetBranchAddress("PDFWeight3", &PDFWeight3, &b_PDFWeight3);
        fChain->SetBranchAddress("PDFWeight4", &PDFWeight4, &b_PDFWeight4);
        fChain->SetBranchAddress("PDFWeight5", &PDFWeight5, &b_PDFWeight5);
        fChain->SetBranchAddress("PDFWeight6", &PDFWeight6, &b_PDFWeight6);
        fChain->SetBranchAddress("PDFWeight7", &PDFWeight7, &b_PDFWeight7);
        fChain->SetBranchAddress("PDFWeight8", &PDFWeight8, &b_PDFWeight8);
        fChain->SetBranchAddress("PDFWeight9", &PDFWeight9, &b_PDFWeight9);
        fChain->SetBranchAddress("PDFWeight10", &PDFWeight10, &b_PDFWeight10);
        fChain->SetBranchAddress("PDFWeight11", &PDFWeight11, &b_PDFWeight11);
        fChain->SetBranchAddress("PDFWeight12", &PDFWeight12, &b_PDFWeight12);
        fChain->SetBranchAddress("PDFWeight13", &PDFWeight13, &b_PDFWeight13);
        fChain->SetBranchAddress("PDFWeight14", &PDFWeight14, &b_PDFWeight14);
        fChain->SetBranchAddress("PDFWeight15", &PDFWeight15, &b_PDFWeight15);
        fChain->SetBranchAddress("PDFWeight16", &PDFWeight16, &b_PDFWeight16);
        fChain->SetBranchAddress("PDFWeight17", &PDFWeight17, &b_PDFWeight17);
        fChain->SetBranchAddress("PDFWeight18", &PDFWeight18, &b_PDFWeight18);
        fChain->SetBranchAddress("PDFWeight19", &PDFWeight19, &b_PDFWeight19);
        fChain->SetBranchAddress("PDFWeight20", &PDFWeight20, &b_PDFWeight20);
        fChain->SetBranchAddress("PDFWeight21", &PDFWeight21, &b_PDFWeight21);
        fChain->SetBranchAddress("PDFWeight22", &PDFWeight22, &b_PDFWeight22);
        fChain->SetBranchAddress("PDFWeight23", &PDFWeight23, &b_PDFWeight23);
        fChain->SetBranchAddress("PDFWeight24", &PDFWeight24, &b_PDFWeight24);
        fChain->SetBranchAddress("PDFWeight25", &PDFWeight25, &b_PDFWeight25);
        fChain->SetBranchAddress("PDFWeight26", &PDFWeight26, &b_PDFWeight26);
        fChain->SetBranchAddress("PDFWeight27", &PDFWeight27, &b_PDFWeight27);
        fChain->SetBranchAddress("PDFWeight28", &PDFWeight28, &b_PDFWeight28);
        fChain->SetBranchAddress("PDFWeight29", &PDFWeight29, &b_PDFWeight29);
        fChain->SetBranchAddress("PDFWeight30", &PDFWeight30, &b_PDFWeight30);
        fChain->SetBranchAddress("PDFWeight31", &PDFWeight31, &b_PDFWeight31);
        fChain->SetBranchAddress("PDFWeight32", &PDFWeight32, &b_PDFWeight32);
        fChain->SetBranchAddress("PDFWeight33", &PDFWeight33, &b_PDFWeight33);
        fChain->SetBranchAddress("PDFWeight34", &PDFWeight34, &b_PDFWeight34);
        fChain->SetBranchAddress("PDFWeight35", &PDFWeight35, &b_PDFWeight35);
        fChain->SetBranchAddress("PDFWeight36", &PDFWeight36, &b_PDFWeight36);
        fChain->SetBranchAddress("PDFWeight37", &PDFWeight37, &b_PDFWeight37);
        fChain->SetBranchAddress("PDFWeight38", &PDFWeight38, &b_PDFWeight38);
        fChain->SetBranchAddress("PDFWeight39", &PDFWeight39, &b_PDFWeight39);
        fChain->SetBranchAddress("PDFWeight40", &PDFWeight40, &b_PDFWeight40);
        fChain->SetBranchAddress("PDFWeight41", &PDFWeight41, &b_PDFWeight41);
        fChain->SetBranchAddress("PDFWeight42", &PDFWeight42, &b_PDFWeight42);
        fChain->SetBranchAddress("PDFWeight43", &PDFWeight43, &b_PDFWeight43);
        fChain->SetBranchAddress("PDFWeight44", &PDFWeight44, &b_PDFWeight44);
        fChain->SetBranchAddress("PDFWeight45", &PDFWeight45, &b_PDFWeight45);
        fChain->SetBranchAddress("PDFWeight46", &PDFWeight46, &b_PDFWeight46);
        fChain->SetBranchAddress("PDFWeight47", &PDFWeight47, &b_PDFWeight47);
        fChain->SetBranchAddress("PDFWeight48", &PDFWeight48, &b_PDFWeight48);
        fChain->SetBranchAddress("PDFWeight49", &PDFWeight49, &b_PDFWeight49);
        fChain->SetBranchAddress("PDFWeight50", &PDFWeight50, &b_PDFWeight50);
        fChain->SetBranchAddress("PDFWeight51", &PDFWeight51, &b_PDFWeight51);
        fChain->SetBranchAddress("PDFWeight52", &PDFWeight52, &b_PDFWeight52);
        fChain->SetBranchAddress("PDFWeight_Alternate_Set_1", &PDFWeight_Alternate_Set_1, &b_PDFWeight_Alternate_Set_1);
        fChain->SetBranchAddress("PDFWeight_Alternate_Set_2", &PDFWeight_Alternate_Set_2, &b_PDFWeight_Alternate_Set_2);
        Notify();
    }

    virtual void Loop() {
        if (fChain == 0) return;

        Long64_t nentries = fChain->GetEntriesFast();

        Long64_t nbytes = 0, nb = 0;
        for (Long64_t jentry = 0; jentry < nentries; jentry++) {
            Long64_t ientry = LoadTree(jentry);
            if (ientry < 0) break;
            nb = fChain->GetEntry(jentry);
            nbytes += nb;
        }
    }

    bool passExtraSelection() {
        bool passed = true;
//        passed = (passed && (this->GetMTW() > 40));
        passed = (passed && (this->GetMTW() > 50));
        passed = (passed && (this->secondJetPt > 60));
        passed = (passed && (this->fJetRMS < 0.025));

        return passed;
    }

    bool jetsForWtemplate() {
        bool istagable1 = (lowBTag > -99);
        bool istagable2 = (highBTag > -99);
        return (fabs(fJetEta) < 2.5 && fabs(bJetEta) < 2.5 && istagable1 && istagable2);
    }

    TLorentzVector GetBJet() {
        TLorentzVector ret(-1, -1, -1, -1);
        ret.SetPtEtaPhiE(this->bJetPt, this->bJetEta, this->bJetPhi, this->bJetE);
        return ret;
    }

    TLorentzVector GetFJet() {
        TLorentzVector ret(-1, -1, -1, -1);
        ret.SetPtEtaPhiE(this->fJetPt, this->fJetEta, this->fJetPhi, this->fJetE);
        return ret;
    }

    TLorentzVector GetMET() {
        TLorentzVector ret(-1, -1, -1, -1);
        ret.SetPtEtaPhiE(this->metPt, 0, this->metPhi, this->metPt);
        return ret;
    }

    /*
     *	inline void TLorentzVector::SetPtEtaPhiE(Double_t pt, Double_t eta, Double_t phi, Double_t e) {
     *		pt = TMath::Abs(pt);
     *		SetXYZT(pt*TMath::Cos(phi), pt*TMath::Sin(phi), pt*sinh(eta) ,e);
     *	}
     *  E = pt*cosh(eta)
     */

    TLorentzVector GetLepton() {
        TLorentzVector ret(-1, -1, -1, -1);
        ret.SetXYZT(this->leptonPt * TMath::Cos(this->leptonPhi),
                this->leptonPt * TMath::Sin(this->leptonPhi),
                this->leptonPt * sinh(this->leptonEta),
                this->leptonPt * cosh(this->leptonEta));
        return ret;
    }

    double GetMTW() {
        double mt = 0;
        TLorentzVector met = this->GetMET();
        TLorentzVector muon = this->GetLepton();
        double metT = sqrt((met.Px() * met.Px())+(met.Py() * met.Py()));
        double muT = sqrt((muon.Px() * muon.Px())+(muon.Py() * muon.Py()));
        mt = sqrt(pow(muT + metT, 2) - pow(met.Px() + muon.Px(), 2) - pow(met.Py() + muon.Py(), 2));
        return mt;
    }

    TLorentzVector GetMostFwDJet() {
        if (fabs(this->bJetEta) > fabs(this->fJetEta))
            return this->GetBJet();
        return this->GetFJet();
    }

    inline double GetHT() {
        return (this->bJetPt + this->fJetPt + this->leptonPt + this->metPt);
    }

    inline double GetTotalWeightNoPU() {
        //        return (this->weight * this->bWeight * (this->leptonEff * 699 + this->leptonEffB * 4342));
        return (this->weight * this->bWeight * (this->leptonEff * 890 + this->leptonEffB * 4428));//5.32
    }

    inline double GetTotalWeight() {
        return (this->GetTotalWeightNoPU() * this->PUWeight);
    }

    int CorrectedTopBQuarkMotherId(int i = 1) {
        if (i == 1) {
            if (this->MCTop_1_PdgId == this->MCTopBQuark_1_MotherId)
                return this->MCTop_1_PdgId;
            else {
                if (this->MCTopBQuark_1_PdgId < 0)
                    return -6;
                else
                    return 6;
            }
        }
        if (i == 2) {
            if (this->MCTop_2_PdgId == this->MCTopBQuark_2_MotherId)
                return this->MCTop_2_PdgId;
            else {
                if (this->MCTopBQuark_2_PdgId < 0)
                    return -6;
                else
                    return 6;
            }
        }
        cout << "CorrectedTopBQuarkMotherId: FATAL Error!!! " << endl;
        return -1000;
    }

    int CorrectedTopPdgId(int i = 1) {
        if (this->MCTop_1_PdgId == this->MCTop_2_PdgId) {
            if (this->MCTop_1_PdgId * this->MCTopLepton_1_MotherId == (-6 * 24)) {
                this->MCTop_1_PdgId *= (int) (fabs(this->MCTopLepton_1_MotherId) / this->MCTopLepton_1_MotherId);
            } else if (this->MCTop_1_PdgId * this->MCTopQuark_1_MotherId == (-6 * 24)) {
                this->MCTop_1_PdgId *= (int) (fabs(this->MCTopQuark_1_MotherId) / this->MCTopQuark_1_MotherId);
            } else if (this->MCTop_2_PdgId * this->MCTopLepton_2_MotherId == (-6 * 24)) {
                this->MCTop_2_PdgId *= (int) (fabs(this->MCTopLepton_2_MotherId) / this->MCTopLepton_2_MotherId);
            } else if (this->MCTop_2_PdgId * this->MCTopQuark_2_MotherId == (-6 * 24)) {
                this->MCTop_2_PdgId *= (int) (fabs(this->MCTopQuark_2_MotherId) / this->MCTopQuark_2_MotherId);
            }
            if (this->MCTopBQuark_1_PdgId == this->MCTopBQuark_2_PdgId) {
                this->MCTopBQuark_1_PdgId *= (int) (fabs(this->MCTop_1_PdgId) / this->MCTop_1_PdgId);
                this->MCTopBQuark_2_PdgId *= (int) (fabs(this->MCTop_2_PdgId) / this->MCTop_2_PdgId);
            }
            if (this->MCTopBQuark_1_MotherId == this->MCTopBQuark_2_MotherId) {
                this->MCTopBQuark_1_MotherId = this->MCTop_1_PdgId;
                this->MCTopBQuark_2_MotherId = this->MCTop_2_PdgId;
            }

            cout << "Same Sign top event:\n\ttop 1: " << this->MCTop_1_PdgId << "\ttop 2: " << this->MCTop_2_PdgId << endl;
            cout << "\tb1 mother: " << this->MCTopBQuark_1_MotherId
                    << "\tb2 mother: " << this->MCTopBQuark_2_MotherId << endl;
            cout << "\tb1 : " << this->MCTopBQuark_1_PdgId
                    << "\tb2 : " << this->MCTopBQuark_2_PdgId << endl;
            cout << "\tl1 mother: " << this->MCTopLepton_1_MotherId
                    << "\tl2 mother: " << this->MCTopLepton_2_MotherId << "\tl2 pt: " << this->MCTopLepton_2_Pt << endl;
            cout << "\tl1 : " << this->MCTopLepton_1_PdgId
                    << "\tl2 : " << this->MCTopLepton_2_PdgId << endl;
            cout << "\tnu1 mother: " << this->MCTopNeutrino_1_MotherId
                    << "\tnu2 mother: " << this->MCTopNeutrino_2_MotherId << endl;
            cout << "\tnu1 : " << this->MCTopNeutrino_1_PdgId
                    << "\tnu2 : " << this->MCTopNeutrino_2_PdgId << endl;
            cout << "\tq1 mother: " << this->MCTopQuark_1_MotherId
                    << "\tq2 mother: " << this->MCTopQuark_2_MotherId << endl;
            cout << "\tq1 : " << this->MCTopQuark_1_PdgId
                    << "\tq2 : " << this->MCTopQuark_2_PdgId << endl;
            cout << "\tqbar1 mother: " << this->MCTopQuarkBar_1_MotherId
                    << "\tqbar2 mother: " << this->MCTopQuarkBar_2_MotherId << endl;
            cout << "\tqbar1 : " << this->MCTopQuarkBar_1_PdgId
                    << "\tqbar2 : " << this->MCTopQuarkBar_2_PdgId << endl;
        }
        if (i == 1) {
            return this->MCTop_1_PdgId;
        }
        if (i == 2) {
            return this->MCTop_2_PdgId;
        }

        cout << "Give the correct Index! The id is now -1000!!" << endl;
        return -1000;
    }

    TRootMCParticle GetMCTop1() {
        TLorentzVector p4;
        p4.SetPtEtaPhiE(this->MCTop_1_Pt, this->MCTop_1_Eta, this->MCTop_1_Phi,
                this->MCTop_1_E);
        float charge = -1000.;
        this->MCTopBQuark_1_MotherId = this->CorrectedTopBQuarkMotherId(1);
        int topId = CorrectedTopPdgId(1);
        if (fabs(p4.Pt()) != 999) {
            if (topId == -6)
                charge = (-2. / 3.);
            if (topId == 6)
                charge = (2. / 3.);
        }
        TRootMCParticle ret(p4.Px(), p4.Py(), p4.Pz(), p4.E(), 0., 0., 0.,
                this->MCTop_1_PdgId, charge);
        ret.setStatus(3);
        //        ret.setMotherType((int) this->MCTop_1_MotherId);
        return ret;
    };

    TRootMCParticle GetMCTop2() {
        TLorentzVector p4;
        p4.SetPtEtaPhiE(this->MCTop_2_Pt, this->MCTop_2_Eta, this->MCTop_2_Phi,
                this->MCTop_2_E);
        float charge = -1000.;
        this->MCTopBQuark_2_MotherId = this->CorrectedTopBQuarkMotherId(2);
        int topId = CorrectedTopPdgId(2);
        if (fabs(p4.Pt()) != 999) {
            if (topId == -6)
                charge = (-2. / 3.);
            if (topId == 6)
                charge = (2. / 3.);
        }
        TRootMCParticle ret(p4.Px(), p4.Py(), p4.Pz(), p4.E(), 0., 0., 0.,
                this->MCTop_2_PdgId, charge);
        ret.setStatus(3);
        //        ret.setMotherType((int) this->MCTop_2_MotherId);
        return ret;
    };

    TRootMCParticle GetMCW1() {
        TLorentzVector p4;
        p4.SetPtEtaPhiE(this->MCTopW_1_Pt, this->MCTopW_1_Eta, this->MCTopW_1_Phi,
                this->MCTopW_1_E);
        float charge = -1000.;
        if (fabs(p4.Pt()) != 999) {
            if (this->MCTopW_1_PdgId == -24)
                charge = (-1);
            if (this->MCTopW_1_PdgId == 24)
                charge = (1);
        }
        TRootMCParticle ret(p4.Px(), p4.Py(), p4.Pz(), p4.E(), 0., 0., 0.,
                this->MCTopW_1_PdgId, charge);
        ret.setStatus(3);
        //        ret.setMotherType((int) this->MCTopW_1_MotherId);
        ret.setDauOneId(this->MCTopW_1_DauOneId);
        return ret;
    };

    TRootMCParticle GetMCW2() {
        TLorentzVector p4;
        p4.SetPtEtaPhiE(this->MCTopW_2_Pt, this->MCTopW_2_Eta, this->MCTopW_2_Phi,
                this->MCTopW_2_E);
        float charge = -1000.;
        if (fabs(p4.Pt()) != 999) {
            if (this->MCTopW_2_PdgId == -24)
                charge = (-1);
            if (this->MCTopW_2_PdgId == 24)
                charge = (1);
        }
        TRootMCParticle ret(p4.Px(), p4.Py(), p4.Pz(), p4.E(), 0., 0., 0.,
                this->MCTopW_2_PdgId, charge);
        ret.setStatus(3);
        //        ret.setMotherType((int) this->MCTopW_2_MotherId);
        ret.setDauOneId(this->MCTopW_2_DauOneId);
        return ret;
    };

    TRootMCParticle GetMCb1() {
        TLorentzVector p4;
        p4.SetPtEtaPhiE(this->MCTopBQuark_1_Pt, this->MCTopBQuark_1_Eta, this->MCTopBQuark_1_Phi,
                this->MCTopBQuark_1_E);
        float charge = -1000.;
        if (fabs(p4.Pt()) != 999) {
            if (this->MCTopBQuark_1_PdgId == 5)
                charge = (-1. / 3.);
            if (this->MCTopBQuark_1_PdgId == -5)
                charge = (1. / 3.);
        }
        TRootMCParticle ret(p4.Px(), p4.Py(), p4.Pz(), p4.E(), 0., 0., 0.,
                this->MCTopBQuark_1_PdgId, charge);
        ret.setStatus(3);
        ret.setMotherType((int) this->MCTopBQuark_1_MotherId);
        return ret;
    };

    TRootMCParticle GetMCb2() {
        TLorentzVector p4;
        p4.SetPtEtaPhiE(this->MCTopBQuark_2_Pt, this->MCTopBQuark_2_Eta, this->MCTopBQuark_2_Phi,
                this->MCTopBQuark_2_E);
        float charge = -1000.;
        if (fabs(p4.Pt()) != 999) {
            if (this->MCTopBQuark_2_PdgId == 5)
                charge = (-1. / 3.);
            if (this->MCTopBQuark_2_PdgId == -5)
                charge = (1. / 3.);
        }
        TRootMCParticle ret(p4.Px(), p4.Py(), p4.Pz(), p4.E(), 0., 0., 0.,
                this->MCTopBQuark_2_PdgId, charge);
        ret.setStatus(3);
        ret.setMotherType((int) this->MCTopBQuark_2_MotherId);
        return ret;
    };

    TRootMCParticle GetMCQ1() {
        TLorentzVector p4;
        p4.SetPtEtaPhiE(this->MCTopQuark_1_Pt, this->MCTopQuark_1_Eta, this->MCTopQuark_1_Phi,
                this->MCTopQuark_1_E);
        //        cout << "********* " << this->MCTopQuark_1_E << endl;
        //        cout << "********* " << this->MCTopQuark_1_Pt << endl;
        //        cout << "********* " << this->MCTopQuark_1_Eta << endl;
        //        cout << "********* " << this->MCTopQuark_1_Phi << endl;
        //        cout << "********* " << p4.Pz() << endl;

        float charge = -1000.;
        //        cout << "quark pt: " << p4.Pt() << endl;
        if (fabs(p4.Pt()) != 999 && fabs(this->MCTopQuark_1_PdgId) < 5) {
            if (this->MCTopQuark_1_PdgId == 1 || this->MCTopQuark_1_PdgId == 3)
                charge = (-1. / 3.);
            if (this->MCTopQuark_1_PdgId == 2 || this->MCTopQuark_1_PdgId == 4)
                charge = (2. / 3.);
        }
        TRootMCParticle ret(p4.Px(), p4.Py(), p4.Pz(), p4.E(), 0., 0., 0.,
                this->MCTopQuark_1_PdgId, charge);
        ret.setStatus(3);
        ret.setMotherType((int) this->MCTopQuark_1_MotherId);
        return ret;
    };

    TRootMCParticle GetMCQBar1() {
        TLorentzVector p4;
        p4.SetPtEtaPhiE(this->MCTopQuarkBar_1_Pt, this->MCTopQuarkBar_1_Eta, this->MCTopQuarkBar_1_Phi,
                this->MCTopQuarkBar_1_E);
        //        cout << "********* " << this->MCTopQuarkBar_1_E << endl;
        float charge = -1000.;
        if (fabs(p4.Pt()) != 999 && fabs(this->MCTopQuarkBar_1_PdgId) < 5) {
            if (this->MCTopQuarkBar_1_PdgId == -1 || this->MCTopQuarkBar_1_PdgId == -3)
                charge = (1. / 3.);
            if (this->MCTopQuarkBar_1_PdgId == -2 || this->MCTopQuarkBar_1_PdgId == -4)
                charge = (-2. / 3.);
        }
        TRootMCParticle ret(p4.Px(), p4.Py(), p4.Pz(), p4.E(), 0., 0., 0.,
                this->MCTopQuarkBar_1_PdgId, charge);
        ret.setStatus(3);
        ret.setMotherType((int) this->MCTopQuarkBar_1_MotherId);
        return ret;
    };

    TRootMCParticle GetMCQ2() {
        TLorentzVector p4;
        p4.SetPtEtaPhiE(this->MCTopQuark_2_Pt, this->MCTopQuark_2_Eta, this->MCTopQuark_2_Phi,
                this->MCTopQuark_2_E);
        //        cout << "********* " << this->MCTopQuark_2_E << endl;
        float charge = -1000.;
        if (fabs(p4.Pt()) != 999 && fabs(this->MCTopQuark_2_PdgId) < 5) {
            if (this->MCTopQuark_2_PdgId == 1 || this->MCTopQuark_2_PdgId == 3)
                charge = (-1. / 3.);
            if (this->MCTopQuark_2_PdgId == 2 || this->MCTopQuark_2_PdgId == 4)
                charge = (2. / 3.);
        }
        TRootMCParticle ret(p4.Px(), p4.Py(), p4.Pz(), p4.E(), 0., 0., 0.,
                this->MCTopQuark_2_PdgId, charge);
        ret.setStatus(3);
        ret.setMotherType((int) this->MCTopQuark_2_MotherId);
        return ret;
    };

    TRootMCParticle GetMCQBar2() {
        TLorentzVector p4;
        p4.SetPtEtaPhiE(this->MCTopQuarkBar_2_Pt, this->MCTopQuarkBar_2_Eta, this->MCTopQuarkBar_2_Phi,
                this->MCTopQuarkBar_2_E);
        //        cout << "********* " << this->MCTopQuarkBar_2_E << endl;
        float charge = -1000.;
        if (fabs(p4.Pt()) != 999 && fabs(this->MCTopQuarkBar_2_PdgId) < 5) {
            if (this->MCTopQuarkBar_2_PdgId == -1 || this->MCTopQuarkBar_2_PdgId == -3)
                charge = (1. / 3.);
            if (this->MCTopQuarkBar_2_PdgId == -2 || this->MCTopQuarkBar_2_PdgId == -4)
                charge = (-2. / 3.);
        }
        TRootMCParticle ret(p4.Px(), p4.Py(), p4.Pz(), p4.E(), 0., 0., 0.,
                this->MCTopQuarkBar_2_PdgId, charge);
        ret.setStatus(3);
        ret.setMotherType((int) this->MCTopQuarkBar_2_MotherId);
        return ret;
    };

    TRootMCParticle GetMCLepton1() {
        TLorentzVector p4;
        p4.SetPtEtaPhiE(this->MCTopLepton_1_Pt, this->MCTopLepton_1_Eta, this->MCTopLepton_1_Phi,
                this->MCTopLepton_1_E);
        float charge = -1000.;
        if (fabs(p4.Pt()) != 999) {
            if (this->MCTopLepton_1_PdgId == 11 || this->MCTopLepton_1_PdgId == 13 ||
                    this->MCTopLepton_1_PdgId == 15)
                charge = (-1.);
            if (this->MCTopLepton_1_PdgId == -11 || this->MCTopLepton_1_PdgId == -13 ||
                    this->MCTopLepton_1_PdgId == -15)
                charge = (1.);
        }
        TRootMCParticle ret(p4.Px(), p4.Py(), p4.Pz(), p4.E(), 0., 0., 0.,
                this->MCTopLepton_1_PdgId, charge);
        ret.setStatus(3);
        ret.setMotherType((int) this->MCTopLepton_1_MotherId);
        return ret;
    };

    TRootMCParticle GetMCLepton2() {
        TLorentzVector p4;
        p4.SetPtEtaPhiE(this->MCTopLepton_2_Pt, this->MCTopLepton_2_Eta, this->MCTopLepton_2_Phi,
                this->MCTopLepton_2_E);
        float charge = -1000.;
        if (fabs(p4.Pt()) != 999) {
            if (this->MCTopLepton_2_PdgId == 11 || this->MCTopLepton_2_PdgId == 13 ||
                    this->MCTopLepton_2_PdgId == 15)
                charge = (-1.);
            if (this->MCTopLepton_2_PdgId == -11 || this->MCTopLepton_2_PdgId == -13 ||
                    this->MCTopLepton_2_PdgId == -15)
                charge = (1.);
        }
        TRootMCParticle ret(p4.Px(), p4.Py(), p4.Pz(), p4.E(), 0., 0., 0.,
                this->MCTopLepton_2_PdgId, charge);
        ret.setStatus(3);
        ret.setMotherType((int) this->MCTopLepton_2_MotherId);
        return ret;
    };

    TRootMCParticle GetMCNeutrino1() {
        TLorentzVector p4;
        p4.SetPtEtaPhiE(this->MCTopNeutrino_1_Pt, this->MCTopNeutrino_1_Eta, this->MCTopNeutrino_1_Phi,
                this->MCTopNeutrino_1_E);
        float charge = -1000.;
        if (fabs(p4.Pt()) != 999) {
            charge = (0);
        }
        TRootMCParticle ret(p4.Px(), p4.Py(), p4.Pz(), p4.E(), 0., 0., 0.,
                this->MCTopNeutrino_1_PdgId, charge);
        ret.setStatus(3);
        ret.setMotherType((int) this->MCTopNeutrino_1_MotherId);
        return ret;
    };

    TRootMCParticle GetMCNeutrino2() {
        TLorentzVector p4;
        p4.SetPtEtaPhiE(this->MCTopNeutrino_2_Pt, this->MCTopNeutrino_2_Eta, this->MCTopNeutrino_2_Phi,
                this->MCTopNeutrino_2_E);
        float charge = -1000.;
        if (fabs(p4.Pt()) != 999) {
            charge = (0);
        }
        TRootMCParticle ret(p4.Px(), p4.Py(), p4.Pz(), p4.E(), 0., 0., 0.,
                this->MCTopNeutrino_2_PdgId, charge);
        ret.setStatus(3);
        ret.setMotherType((int) this->MCTopNeutrino_2_MotherId);
        return ret;
    };

    int GetNMCLeptons() {
        int pdgId1 = this->GetMCLepton1().type();
        int pdgId2 = this->GetMCLepton2().type();
        if (pdgId1 != -1000 && pdgId2 != -1000)
            return 2;
        else if (pdgId1 == -1000 && pdgId2 == -1000)
            return 0;
        else return 1;
    }

    TRootGenTop GetGenTop(int i) {
        if (i == 1) {
            TRootMCParticle Top = this->GetMCTop1();
            TRootMCParticle W = this->GetMCW1();
            TRootMCParticle b = this->GetMCb1();
            Top.SetPxPyPzE((W + b).Px(), (W + b).Py(), (W + b).Pz(), (W + b).E());
            //            cout << "in getGenTop1: " << this->GetMCLepton1().type() << endl;
            const bool isLeptonic = (this->GetMCLepton1().type() != -999.);
            if (isLeptonic) {
                TRootMCParticle lepton = this->GetMCLepton1();
                TRootMCParticle neutrino = this->GetMCNeutrino1();
                if (this->MCTopLepton_1_E == -999 || this->MCTopLepton_1_Eta == -999 ||
                        this->MCTopLepton_1_Phi == -999) {
                    cout << "FATAL ERROR ON LEPTON 1" << endl;
                    lepton = Top - b - neutrino;
                }
                if (this->MCTopNeutrino_1_E == -999 || this->MCTopNeutrino_1_Eta == -999 ||
                        this->MCTopNeutrino_1_Phi == -999) {
                    cout << "FATAL ERROR ON Neutrino 1" << endl;
                    neutrino = Top - b - lepton;
                }
                TRootGenTop top(isLeptonic, Top, W, b, lepton, neutrino);
                return top;
            } else {
                //                cout << "The top is not leptonic! " << endl;
                TRootMCParticle q = this->GetMCQ1();
                TRootMCParticle qbar = this->GetMCQBar1();
                if (this->MCTopQuark_1_E == -999 || this->MCTopQuark_1_Eta == -999 ||
                        this->MCTopQuark_1_Phi == -999) {
                    cout << "FATAL ERROR ON Quark 1:\n\tE: " << this->MCTopQuark_1_E
                            << "\tEta: " << this->MCTopQuark_1_Eta << "\tPhi: " << this->MCTopQuark_1_Phi << endl;
                    q = (Top - qbar - b);
                    cout << "AFTER REASSIGNEMET OF Quark 1:\n\tE: " << q.E()
                            << "\tEta: " << q.Eta() << "\tPhi: " << q.Phi() << endl;
                    
                }
                if (this->MCTopQuarkBar_1_E == -999 || this->MCTopQuarkBar_1_Eta == -999 ||
                        this->MCTopQuarkBar_1_Phi == -999) {
                    cout << "FATAL ERROR ON QuarkBar 1:\n\tE: " << this->MCTopQuarkBar_1_E
                            << "\tEta: " << this->MCTopQuarkBar_1_Eta << "\tPhi: " << this->MCTopQuarkBar_1_Phi << endl;
                    qbar = (Top - q - b);
                    cout << "AFTER REASSIGNEMET OF QuarkBar 1:\n\tE: " << qbar.E()
                            << "\tEta: " << qbar.Eta() << "\tPhi: " << qbar.Phi() << endl;
                }
                TRootGenTop top(isLeptonic, Top, W, b, q, qbar);
                return top;
            }
        }
        if (i == 2) {
            TRootMCParticle Top = this->GetMCTop2();
            TRootMCParticle W = this->GetMCW2();
            TRootMCParticle b = this->GetMCb2();
            Top.SetPxPyPzE((W + b).Px(), (W + b).Py(), (W + b).Pz(), (W + b).E());
            //            cout << "in getGenTop2: " << this->GetMCLepton2().type() << endl;
            const bool isLeptonic = (this->GetMCLepton2().type() != -999.);
            if (isLeptonic) {
                TRootMCParticle lepton = this->GetMCLepton2();
                TRootMCParticle neutrino = this->GetMCNeutrino2();
                if (this->MCTopLepton_2_E == -999 || this->MCTopLepton_2_Eta == -999 ||
                        this->MCTopLepton_2_Phi == -999) {
                    cout << "FATAL ERROR ON LEPTON 2" << endl;
                    lepton = Top - b - neutrino;
                }
                if (this->MCTopNeutrino_2_E == -999 || this->MCTopNeutrino_2_Eta == -999 ||
                        this->MCTopNeutrino_2_Phi == -999) {
                    cout << "FATAL ERROR ON Neutrino 2" << endl;
                    neutrino = Top - b - lepton;
                }
                TRootGenTop top(isLeptonic, Top, W, b, lepton, neutrino);
                return top;
            } else {
                //                cout << "The top is not leptonic! " << endl;
                TRootMCParticle q = this->GetMCQ2();
                TRootMCParticle qbar = this->GetMCQBar2();
                if (this->MCTopQuark_2_E == -999 || this->MCTopQuark_2_Eta == -999 ||
                        this->MCTopQuark_2_Phi == -999) {
                    cout << "FATAL ERROR ON Quark 2:\n\tE: " << this->MCTopQuark_2_E
                            << "\tEta: " << this->MCTopQuark_2_Eta << "\tPhi: " << this->MCTopQuark_2_Phi << endl;
                    q = (Top - qbar - b);
                }
                if (this->MCTopQuarkBar_2_E == -999 || this->MCTopQuarkBar_2_Eta == -999 ||
                        this->MCTopQuarkBar_2_Phi == -999) {
                    cout << "FATAL ERROR ON QuarkBar 2:\n\tE: " << this->MCTopQuarkBar_2_E
                            << "\tEta: " << this->MCTopQuarkBar_2_Eta << "\tPhi: " << this->MCTopQuarkBar_2_Phi << endl;
                    qbar = (Top - q - b);
                }
                TRootGenTop top(isLeptonic, Top, W, b, q, qbar);
                return top;
            }
        }
        cout << "FATAL ERROR: Bad Top Id" << endl;
    };

    bool isTopConsistentID(TRootGenTop gentop) {
        if (fabs(gentop.type()) != 6) {
            cout << "Bad type for top!" << endl;
            return false;
        }
        if (fabs(gentop.W().type()) != 24) {
            cout << "Bad type for top W!" << endl;
            return false;
        }
        if (gentop.W().type() * gentop.type() < 0) {
            cout << "top-W inconsistency" << endl;
            return false;
        }
        if (gentop.type() * gentop.bquark().type() < 0) {
            cout << "top-b inconsistency" << endl;
            return false;
        }
        bool isWok = false;
        if (gentop.isLeptonic()) {
            isWok = ((gentop.lepton().type() * gentop.W().type()) < 0);
            if (!isWok) {
                cout << "W-lepton inconsistency" << endl;
                return false;
            }
            if (fabs(gentop.lepton().type()) == 11 && fabs(gentop.neutrino().type()) == 12) {
                isWok = true;
            }
            if (fabs(gentop.lepton().type()) == 13 && fabs(gentop.neutrino().type()) == 14) {
                isWok = true;
            }
            if (fabs(gentop.lepton().type()) == 15 && fabs(gentop.neutrino().type()) == 16) {
                isWok = true;
            }
            //            cout << "lepton: " << gentop.lepton().type() << "\tneutrino: " << gentop.neutrino().type() << endl;
            //            cout << "isE: " << gentop.isLeptonicEl() << "\tisMu: " << gentop.isLeptonicMu() << "\tisTau: " <<
            //                    gentop.isLeptonicTau() << "\tisWok: " << isWok << endl;
        } else {
            isWok = ((gentop.quark().type() * gentop.quarkBar().type()) < 0);
            if (!isWok) {
                cout << "W constituents are not correctly assigned" << endl;
                cout << "\t" << gentop.quark().type() << "\t" << gentop.quarkBar().type() << endl;
                cout << "\t" << this->MCTopBQuark_1_PdgId << "\t" << this->MCTopBQuark_2_PdgId << endl;
                return false;
            }
            if (fabs(gentop.quark().type()) == 1 && fabs(gentop.quarkBar().type()) == 2) {
                isWok = true;
            }
            if (fabs(gentop.quark().type()) == 3 && fabs(gentop.quarkBar().type()) == 4) {
                isWok = true;
            }
            //            cout << "quark: " << gentop.quark().type() << "\tquarkBar: " <<
            //                    gentop.quarkBar().type() << "\tisWok: " << isWok << endl;
        }

        return isWok;

    }

    int GetTopDecayChannel(TRootGenTop gentop) {
        if (gentop.isHadronic())
            return 1;
        if (gentop.isLeptonicEl())
            return 2;
        if (gentop.isLeptonicMu())
            return 3;
        if (gentop.isLeptonicTau())
            return 4;
        return -1;
    }

    bool isTopConsistentCharge(TRootGenTop gentop) {
        bool isWconsistentCharge = false;
        if (gentop.isLeptonic()) {
            //            cout << "charge in lepton part:\n\tW: " << gentop.W().charge() << "\n\tlepton: "
            //                    << gentop.lepton().charge() << "\n\tneutrino: " << gentop.neutrino().charge()
            //                    << endl;
            isWconsistentCharge = ((gentop.W().charge() - gentop.lepton().charge() -
                    gentop.neutrino().charge()) == 0);
        } else {
            //            cout << "charge in hadron part:\n\tW: " << gentop.W().charge() << "\n\tquark: "
            //                    << gentop.quark().charge() << "\n\tquarkBar: " << gentop.quarkBar().charge()
            //                    << endl;
            double chargeSum = (gentop.W().charge() - gentop.quark().charge() -
                    gentop.quarkBar().charge());
            if (fabs(chargeSum) < (1. / 3.))
                chargeSum = 0;
            isWconsistentCharge = (chargeSum == 0);
        }
        double chargeSum = (gentop.charge() - gentop.W().charge() -
                gentop.bquark().charge());
        if (fabs(chargeSum) < (1. / 3.))
            chargeSum = 0;

        //                cout << "final charge:\n\ttop: " << gentop.charge() << "\n\tW: " << gentop.W().charge()
        //                << "\n\tb: " << gentop.bquark().charge() << endl;

        //                cout << "final type:\n\ttop: " << gentop.type() << "\n\tW: " << gentop.W().type()
        //                << "\n\tb: " << gentop.bquark().type() << endl;
        //                cout << "\tisWconsistentCharge: " << isWconsistentCharge << "\n\tfinal charge sum: " <<
        //                gentop.charge() - gentop.W().charge() - gentop.bquark().charge() << "\n\t" <<
        //                (isWconsistentCharge && (chargeSum == 0)) << endl;
        return (isWconsistentCharge && (chargeSum == 0));
    }

    std::vector<TRootMCParticle> GetAllLeptons() {
        std::vector<TRootMCParticle> res;
        if (this->MCLepton_1_Pt != -999) {
            TLorentzVector p4;
            p4.SetPtEtaPhiE(this->MCLepton_1_Pt, this->MCLepton_1_Eta, this->MCLepton_1_Phi,
                    this->MCLepton_1_E);
            float charge = -1000.;

            if (this->MCLepton_1_PdgId == 11 || this->MCLepton_1_PdgId == 13 ||
                    this->MCLepton_1_PdgId == 15)
                charge = (-1.);
            if (this->MCLepton_1_PdgId == -11 || this->MCLepton_1_PdgId == -13 ||
                    this->MCLepton_1_PdgId == -15)
                charge = (1.);

            TRootMCParticle ret(p4.Px(), p4.Py(), p4.Pz(), p4.E(), 0., 0., 0.,
                    this->MCLepton_1_PdgId, charge);
            ret.setStatus(3);
            ret.setMotherType(24 * charge);
            res.push_back(ret);
        }
        if (this->MCLepton_2_Pt != -999) {
            TLorentzVector p4;
            p4.SetPtEtaPhiE(this->MCLepton_2_Pt, this->MCLepton_2_Eta, this->MCLepton_2_Phi,
                    this->MCLepton_2_E);
            float charge = -1000.;

            if (this->MCLepton_2_PdgId == 11 || this->MCLepton_2_PdgId == 13 ||
                    this->MCLepton_2_PdgId == 15)
                charge = (-1.);
            if (this->MCLepton_2_PdgId == -11 || this->MCLepton_2_PdgId == -13 ||
                    this->MCLepton_2_PdgId == -15)
                charge = (1.);

            TRootMCParticle ret(p4.Px(), p4.Py(), p4.Pz(), p4.E(), 0., 0., 0.,
                    this->MCLepton_2_PdgId, charge);
            ret.setStatus(3);
            ret.setMotherType(24 * charge);
            res.push_back(ret);
        }
        return res;
    }

    std::vector<TRootMCParticle> GetAllQuarks(std::vector<TopTree::TRootGenTop>);
    void DealWithTW(std::vector<TopTree::TRootGenTop> tops, std::vector<TopTree::TRootMCParticle> leptons);
    int WdecayInTW;

    int typeConvertor(int i) {
        if (i == 11)
            return 1;
        else if (i == 13)
            return 2;
        else if (i == 15)
            return 3;
        return 4;
    }

    int SampleRecognizer(std::string sampleType) {
        int ntop = 0;
        if ((sampleType.find("Channel") > 0 && fabs(sampleType.find("Channel")) < sampleType.size()) ||
                sampleType == string("TTBar") || sampleType == string("TTBar_Q2Up") || sampleType == string("TTBar_Q2Down") ||
                (sampleType.find("TTBar") > 0 && fabs(sampleType.find("TTBar")) < sampleType.size())) {
//            cout<<"I recognize the sample"<<endl;
            if (fabs(this->MCTop_1_PdgId) == 6) {
                //                cout << this->MCTop_1_PdgId << endl;
                ntop++;
            }
            if (fabs(this->MCTop_2_PdgId) == 6) {
                //                cout << this->MCTop_2_PdgId << endl;
                ntop++;
            }
        }
        return ntop;
    }
};
#endif

