//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sat Sep  8 14:05:10 2012 by ROOT version 5.32/00
// from TTree Data_noSystQCD/Data_noSystQCD
// found on file: Mu_May10.root
//////////////////////////////////////////////////////////

#ifndef QCDOrso_h
#define QCDOrso_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <string>
#include <iostream>
#include "TLorentzVector.h"

// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.
using namespace std;

class QCDOrso {
public:
    TTree *fChain; //!pointer to the analyzed TTree or TChain
    Int_t fCurrent; //!current Tree number in a TChain

    // Declaration of leaf types
    Double_t eta;
    Double_t costhetalj;
    Double_t topMass;
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
    Double_t leptonRelIso;
    Double_t fJetPt;
    Double_t fJetE;
    Double_t fJetEta;
    Double_t fJetPhi;
    Double_t fJetBtag;
    Double_t bJetPt;
    Double_t bJetE;
    Double_t bJetEta;
    Double_t bJetPhi;
    Double_t bJetBtag;
    Int_t bJetFlavour;
    Double_t metPt;
    Double_t metPhi;
    Double_t topPt;
    Double_t topPhi;
    Double_t topEta;
    Double_t topE;
    Int_t ID;
    Int_t nVertices;
    Double_t totalEnergy;
    Double_t totalMomentum;
    Double_t lowBTag;
    Double_t highBTag;
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
    TBranch *b_topMass; //!
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
    TBranch *b_leptonRelIso; //!
    TBranch *b_fJetPt; //!
    TBranch *b_fJetE; //!
    TBranch *b_fJetEta; //!
    TBranch *b_fJetPhi; //!
    TBranch *b_fJetBtag; //!
    TBranch *b_bJetPt; //!
    TBranch *b_bJetE; //!
    TBranch *b_bJetEta; //!
    TBranch *b_bJetPhi; //!
    TBranch *b_bJetBtag; //!
    TBranch *b_bJetFlavour; //!
    TBranch *b_metPt; //!
    TBranch *b_metPhi; //!
    TBranch *b_topPt; //!
    TBranch *b_topPhi; //!
    TBranch *b_topEta; //!
    TBranch *b_topE; //!
    TBranch *b_ID; //!
    TBranch *b_nVertices; //!
    TBranch *b_totalEnergy; //!
    TBranch *b_totalMomentum; //!
    TBranch *b_lowBTag; //!
    TBranch *b_highBTag; //!
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

    QCDOrso(TTree *tree = 0, TFile * f = 0, std::string Sample="") : fChain(0) {
        if (tree == 0) {
            cout << "tree = 0!" << endl;
            //            cout<<(gROOT->GetListOfFiles())->At(0)->GetName()<<endl;
            //            TFile *f = (TFile*) gROOT->GetListOfFiles()->FindObject(fName.c_str());
            cout << "file = " << f << endl;

            TDirectory * dir = (TDirectory*) f->Get("TreesMu");
            dir->GetObject(Sample.c_str(), tree);
            //            dir->GetObject("Data_noSystWSample", tree);
            //            dir->GetObject("Data_noSystWSampleQCD", tree);

        }
        Init(tree);
    };

    virtual ~QCDOrso() {
        if (!fChain) return;
        delete fChain->GetCurrentFile();
    };

    virtual Int_t Cut(Long64_t entry) {
        // This function may be called from Loop.
        // returns  1 if entry is accepted.
        // returns -1 otherwise.
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

    virtual void Init(TTree *tree) {
        // The Init() function is called when the selector needs to initialize
        // a new tree or chain. Typically here the branch addresses and branch
        // pointers of the tree will be set.
        // It is normally not necessary to make changes to the generated
        // code, but the routine can be extended by the user if needed.
        // Init() will be called many times when running on PROOF
        // (once per file to be processed).

        // Set branch addresses and branch pointers
        if (!tree) return;
        fChain = tree;
        fCurrent = -1;
        fChain->SetMakeClass(1);

        fChain->SetBranchAddress("eta", &eta, &b_eta);
        fChain->SetBranchAddress("costhetalj", &costhetalj, &b_costhetalj);
        fChain->SetBranchAddress("topMass", &topMass, &b_topMass);
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
        fChain->SetBranchAddress("leptonRelIso", &leptonRelIso, &b_leptonRelIso);
        fChain->SetBranchAddress("fJetPt", &fJetPt, &b_fJetPt);
        fChain->SetBranchAddress("fJetE", &fJetE, &b_fJetE);
        fChain->SetBranchAddress("fJetEta", &fJetEta, &b_fJetEta);
        fChain->SetBranchAddress("fJetPhi", &fJetPhi, &b_fJetPhi);
        fChain->SetBranchAddress("fJetBtag", &fJetBtag, &b_fJetBtag);
        fChain->SetBranchAddress("bJetPt", &bJetPt, &b_bJetPt);
        fChain->SetBranchAddress("bJetE", &bJetE, &b_bJetE);
        fChain->SetBranchAddress("bJetEta", &bJetEta, &b_bJetEta);
        fChain->SetBranchAddress("bJetPhi", &bJetPhi, &b_bJetPhi);
        fChain->SetBranchAddress("bJetBtag", &bJetBtag, &b_bJetBtag);
        fChain->SetBranchAddress("bJetFlavour", &bJetFlavour, &b_bJetFlavour);
        fChain->SetBranchAddress("metPt", &metPt, &b_metPt);
        fChain->SetBranchAddress("metPhi", &metPhi, &b_metPhi);
        fChain->SetBranchAddress("topPt", &topPt, &b_topPt);
        fChain->SetBranchAddress("topPhi", &topPhi, &b_topPhi);
        fChain->SetBranchAddress("topEta", &topEta, &b_topEta);
        fChain->SetBranchAddress("topE", &topE, &b_topE);
        fChain->SetBranchAddress("ID", &ID, &b_ID);
        fChain->SetBranchAddress("nVertices", &nVertices, &b_nVertices);
        fChain->SetBranchAddress("totalEnergy", &totalEnergy, &b_totalEnergy);
        fChain->SetBranchAddress("totalMomentum", &totalMomentum, &b_totalMomentum);
        fChain->SetBranchAddress("lowBTag", &lowBTag, &b_lowBTag);
        fChain->SetBranchAddress("highBTag", &highBTag, &b_highBTag);
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
        //    fChain->SetBranchAddress("PDFWeight_Alternate_Set_1", &PDFWeight_Alternate_Set_1, &b_PDFWeight_Alternate_Set_1);
        //    fChain->SetBranchAddress("PDFWeight_Alternate_Set_2", &PDFWeight_Alternate_Set_2, &b_PDFWeight_Alternate_Set_2);
        Notify();
    };

    virtual void Loop() {
    };

    virtual Bool_t Notify() {
        // The Notify() function is called when a new file is opened. This
        // can be either for a new TTree in a TChain or when when a new TTree
        // is started when using PROOF. It is normally not necessary to make changes
        // to the generated code, but the routine can be extended by the
        // user if needed. The return value is currently not used.

        return kTRUE;
    };

    virtual void Show(Long64_t entry = -1) {
        // Print contents of entry.
        // If entry is not specified, print current entry
        if (!fChain) return;
        fChain->Show(entry);
    };

    TLorentzVector GetLepton() {
        TLorentzVector ret(-1, -1, -1, -1);
        ret.SetXYZT(this->leptonPt * TMath::Cos(this->leptonPhi),
                this->leptonPt * TMath::Sin(this->leptonPhi),
                this->leptonPt * sinh(this->leptonEta),
                this->leptonPt * cosh(this->leptonEta));
        return ret;
    }

    bool isWSelected() {
        bool eta = (fabs(fJetEta) <= 2.4 && fabs(bJetEta) <= 2.4);
        bool btag1 = (highBTag < 3.41 && highBTag >= -99);
        bool btag2 = (lowBTag < 3.41 && lowBTag >= -99);
        return (eta && btag1 && btag2);
    }
};

#endif

