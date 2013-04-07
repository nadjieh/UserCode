#define GenInfoMuonTree_cxx
#include <bitset>

#include "../interface/GenInfoMuonTree.h"

std::vector<TRootMCParticle> GenInfoMuonTree::GetAllQuarks(std::vector<TopTree::TRootGenTop> tops) {
    std::vector<TRootMCParticle> res;
    int nWquark = 0;
    if (tops.size() > 0)
        if (tops[0].isHadronic())
            nWquark += 2;
    if (tops.size() > 1)
        if (tops[1].isHadronic())
            nWquark += 2;
    if (WdecayInTW == 4)
        nWquark += 2;
    int nQ = 0;
    if (this->MCQuark_1_Pt != -999) {

        TLorentzVector p4;
        p4.SetPtEtaPhiE(this->MCQuark_1_Pt, this->MCQuark_1_Eta, this->MCQuark_1_Phi,
                this->MCQuark_1_E);
        float charge = -1000.;

        if (this->MCQuark_1_PdgId == 2 || this->MCQuark_1_PdgId == 4)
            charge = (2. / 3.);
        if (this->MCQuark_1_PdgId == -2 || this->MCQuark_1_PdgId == -4)
            charge = (-2. / 3.);
        if (this->MCQuark_1_PdgId == 1 || this->MCQuark_1_PdgId == 3)
            charge = (-1. / 3.);
        if (this->MCQuark_1_PdgId == -1 || this->MCQuark_1_PdgId == -3)
            charge = (1. / 3.);

        TRootMCParticle ret(p4.Px(), p4.Py(), p4.Pz(), p4.E(), 0., 0., 0.,
                this->MCQuark_1_PdgId, charge);
        if (fabs(ret.type()) < 5) nQ++;
        ret.setStatus(3);
        if (nQ <= nWquark && fabs(ret.type()) < 5)
            ret.setMotherType(24);
        else
            ret.setMotherType(100);
        res.push_back(ret);
    }
    if (this->MCQuark_2_Pt != -999) {

        TLorentzVector p4;
        p4.SetPtEtaPhiE(this->MCQuark_2_Pt, this->MCQuark_2_Eta, this->MCQuark_2_Phi,
                this->MCQuark_2_E);
        float charge = -1000.;

        if (this->MCQuark_2_PdgId == 2 || this->MCQuark_2_PdgId == 4)
            charge = (2. / 3.);
        if (this->MCQuark_2_PdgId == -2 || this->MCQuark_2_PdgId == -4)
            charge = (-2. / 3.);
        if (this->MCQuark_2_PdgId == 1 || this->MCQuark_2_PdgId == 3)
            charge = (-1. / 3.);
        if (this->MCQuark_2_PdgId == -1 || this->MCQuark_2_PdgId == -3)
            charge = (1. / 3.);

        TRootMCParticle ret(p4.Px(), p4.Py(), p4.Pz(), p4.E(), 0., 0., 0.,
                this->MCQuark_2_PdgId, charge);
        if (fabs(ret.type()) < 5) nQ++;
        ret.setStatus(3);
        if (nQ <= nWquark && fabs(ret.type()) < 5)ret.setMotherType(24);
        else ret.setMotherType(100);
        res.push_back(ret);
    }
    if (this->MCQuark_3_Pt != -999) {

        TLorentzVector p4;
        p4.SetPtEtaPhiE(this->MCQuark_3_Pt, this->MCQuark_3_Eta, this->MCQuark_3_Phi,
                this->MCQuark_3_E);
        float charge = -1000.;

        if (this->MCQuark_3_PdgId == 2 || this->MCQuark_3_PdgId == 4)
            charge = (2. / 3.);
        if (this->MCQuark_3_PdgId == -2 || this->MCQuark_3_PdgId == -4)
            charge = (-2. / 3.);
        if (this->MCQuark_3_PdgId == 1 || this->MCQuark_3_PdgId == 3)
            charge = (-1. / 3.);
        if (this->MCQuark_3_PdgId == -1 || this->MCQuark_3_PdgId == -3)
            charge = (1. / 3.);

        TRootMCParticle ret(p4.Px(), p4.Py(), p4.Pz(), p4.E(), 0., 0., 0.,
                this->MCQuark_3_PdgId, charge);
        if (fabs(ret.type()) < 5) nQ++;
        ret.setStatus(3);
        if (nQ <= nWquark && fabs(ret.type()) < 5)ret.setMotherType(24);
        else ret.setMotherType(100);
        res.push_back(ret);
    }
    if (this->MCQuark_4_Pt != -999) {

        TLorentzVector p4;
        p4.SetPtEtaPhiE(this->MCQuark_4_Pt, this->MCQuark_4_Eta, this->MCQuark_4_Phi,
                this->MCQuark_4_E);
        float charge = -1000.;

        if (this->MCQuark_4_PdgId == 2 || this->MCQuark_4_PdgId == 4)
            charge = (2. / 3.);
        if (this->MCQuark_4_PdgId == -2 || this->MCQuark_4_PdgId == -4)
            charge = (-2. / 3.);
        if (this->MCQuark_4_PdgId == 1 || this->MCQuark_4_PdgId == 3)
            charge = (-1. / 3.);
        if (this->MCQuark_4_PdgId == -1 || this->MCQuark_4_PdgId == -3)
            charge = (1. / 3.);

        TRootMCParticle ret(p4.Px(), p4.Py(), p4.Pz(), p4.E(), 0., 0., 0.,
                this->MCQuark_4_PdgId, charge);
        if (fabs(ret.type()) < 5) nQ++;
        ret.setStatus(3);
        if (nQ <= nWquark && fabs(ret.type()) < 5)ret.setMotherType(24);
        else ret.setMotherType(100);
        res.push_back(ret);
    }
    if (this->MCQuark_5_Pt != -999) {

        TLorentzVector p4;
        p4.SetPtEtaPhiE(this->MCQuark_5_Pt, this->MCQuark_5_Eta, this->MCQuark_5_Phi,
                this->MCQuark_5_E);
        float charge = -1000.;

        if (this->MCQuark_5_PdgId == 2 || this->MCQuark_5_PdgId == 4)
            charge = (2. / 3.);
        if (this->MCQuark_5_PdgId == -2 || this->MCQuark_5_PdgId == -4)
            charge = (-2. / 3.);
        if (this->MCQuark_5_PdgId == 1 || this->MCQuark_5_PdgId == 3)
            charge = (-1. / 3.);
        if (this->MCQuark_5_PdgId == -1 || this->MCQuark_5_PdgId == -3)
            charge = (1. / 3.);

        TRootMCParticle ret(p4.Px(), p4.Py(), p4.Pz(), p4.E(), 0., 0., 0.,
                this->MCQuark_5_PdgId, charge);
        if (fabs(ret.type()) < 5) nQ++;
        ret.setStatus(3);
        if (nQ <= nWquark && fabs(ret.type()) < 5)ret.setMotherType(24);
        else ret.setMotherType(100);
        res.push_back(ret);
    }
    if (this->MCQuark_6_Pt != -999) {

        TLorentzVector p4;
        p4.SetPtEtaPhiE(this->MCQuark_6_Pt, this->MCQuark_6_Eta, this->MCQuark_6_Phi,
                this->MCQuark_6_E);
        float charge = -1000.;

        if (this->MCQuark_6_PdgId == 2 || this->MCQuark_6_PdgId == 4)
            charge = (2. / 3.);
        if (this->MCQuark_6_PdgId == -2 || this->MCQuark_6_PdgId == -4)
            charge = (-2. / 3.);
        if (this->MCQuark_6_PdgId == 1 || this->MCQuark_6_PdgId == 3)
            charge = (-1. / 3.);
        if (this->MCQuark_6_PdgId == -1 || this->MCQuark_6_PdgId == -3)
            charge = (1. / 3.);

        TRootMCParticle ret(p4.Px(), p4.Py(), p4.Pz(), p4.E(), 0., 0., 0.,
                this->MCQuark_6_PdgId, charge);
        if (fabs(ret.type()) < 5) nQ++;
        ret.setStatus(3);
        if (nQ <= nWquark && fabs(ret.type()) < 5)ret.setMotherType(24);
        else ret.setMotherType(100);
        res.push_back(ret);
    }
    if (this->MCQuark_7_Pt != -999) {

        TLorentzVector p4;
        p4.SetPtEtaPhiE(this->MCQuark_7_Pt, this->MCQuark_7_Eta, this->MCQuark_7_Phi,
                this->MCQuark_7_E);
        float charge = -1000.;

        if (this->MCQuark_7_PdgId == 2 || this->MCQuark_7_PdgId == 4)
            charge = (2. / 3.);
        if (this->MCQuark_7_PdgId == -2 || this->MCQuark_7_PdgId == -4)
            charge = (-2. / 3.);
        if (this->MCQuark_7_PdgId == 1 || this->MCQuark_7_PdgId == 3)
            charge = (-1. / 3.);
        if (this->MCQuark_7_PdgId == -1 || this->MCQuark_7_PdgId == -3)
            charge = (1. / 3.);

        TRootMCParticle ret(p4.Px(), p4.Py(), p4.Pz(), p4.E(), 0., 0., 0.,
                this->MCQuark_7_PdgId, charge);
        if (fabs(ret.type()) < 5) nQ++;
        ret.setStatus(3);
        if (nQ <= nWquark && fabs(ret.type()) < 5)ret.setMotherType(24);
        else ret.setMotherType(100);
        res.push_back(ret);
    }
    if (this->MCQuark_8_Pt != -999) {

        TLorentzVector p4;
        p4.SetPtEtaPhiE(this->MCQuark_8_Pt, this->MCQuark_8_Eta, this->MCQuark_8_Phi,
                this->MCQuark_8_E);
        float charge = -1000.;

        if (this->MCQuark_8_PdgId == 2 || this->MCQuark_8_PdgId == 4)
            charge = (2. / 3.);
        if (this->MCQuark_8_PdgId == -2 || this->MCQuark_8_PdgId == -4)
            charge = (-2. / 3.);
        if (this->MCQuark_8_PdgId == 1 || this->MCQuark_8_PdgId == 3)
            charge = (-1. / 3.);
        if (this->MCQuark_8_PdgId == -1 || this->MCQuark_8_PdgId == -3)
            charge = (1. / 3.);

        TRootMCParticle ret(p4.Px(), p4.Py(), p4.Pz(), p4.E(), 0., 0., 0.,
                this->MCQuark_8_PdgId, charge);
        if (fabs(ret.type()) < 5) nQ++;
        ret.setStatus(3);
        if (nQ <= nWquark && fabs(ret.type()) < 5)ret.setMotherType(24);
        else ret.setMotherType(100);
        res.push_back(ret);
    }
    if (this->MCQuark_9_Pt != -999) {

        TLorentzVector p4;
        p4.SetPtEtaPhiE(this->MCQuark_9_Pt, this->MCQuark_9_Eta, this->MCQuark_9_Phi,
                this->MCQuark_9_E);
        float charge = -1000.;

        if (this->MCQuark_9_PdgId == 2 || this->MCQuark_9_PdgId == 4)
            charge = (2. / 3.);
        if (this->MCQuark_9_PdgId == -2 || this->MCQuark_9_PdgId == -4)
            charge = (-2. / 3.);
        if (this->MCQuark_9_PdgId == 1 || this->MCQuark_9_PdgId == 3)
            charge = (-1. / 3.);
        if (this->MCQuark_9_PdgId == -1 || this->MCQuark_9_PdgId == -3)
            charge = (1. / 3.);

        TRootMCParticle ret(p4.Px(), p4.Py(), p4.Pz(), p4.E(), 0., 0., 0.,
                this->MCQuark_9_PdgId, charge);
        if (fabs(ret.type()) < 5) nQ++;
        ret.setStatus(3);
        if (nQ <= nWquark && fabs(ret.type()) < 5)ret.setMotherType(24);
        else ret.setMotherType(100);
        res.push_back(ret);
    }
    if (this->MCQuark_10_Pt != -999) {

        TLorentzVector p4;
        p4.SetPtEtaPhiE(this->MCQuark_10_Pt, this->MCQuark_10_Eta, this->MCQuark_10_Phi,
                this->MCQuark_10_E);
        float charge = -1000.;

        if (this->MCQuark_10_PdgId == 2 || this->MCQuark_10_PdgId == 4)
            charge = (2. / 3.);
        if (this->MCQuark_10_PdgId == -2 || this->MCQuark_10_PdgId == -4)
            charge = (-2. / 3.);
        if (this->MCQuark_10_PdgId == 1 || this->MCQuark_10_PdgId == 3)
            charge = (-1. / 3.);
        if (this->MCQuark_10_PdgId == -1 || this->MCQuark_10_PdgId == -3)
            charge = (1. / 3.);

        TRootMCParticle ret(p4.Px(), p4.Py(), p4.Pz(), p4.E(), 0., 0., 0.,
                this->MCQuark_10_PdgId, charge);
        if (fabs(ret.type()) < 5) nQ++;
        ret.setStatus(3);
        if (nQ <= nWquark && fabs(ret.type()) < 5)ret.setMotherType(24);
        else ret.setMotherType(100);
        res.push_back(ret);
    }
    if (this->MCQuark_11_Pt != -999) {

        TLorentzVector p4;
        p4.SetPtEtaPhiE(this->MCQuark_11_Pt, this->MCQuark_11_Eta, this->MCQuark_11_Phi,
                this->MCQuark_11_E);
        float charge = -1000.;

        if (this->MCQuark_11_PdgId == 2 || this->MCQuark_11_PdgId == 4)
            charge = (2. / 3.);
        if (this->MCQuark_11_PdgId == -2 || this->MCQuark_11_PdgId == -4)
            charge = (-2. / 3.);
        if (this->MCQuark_11_PdgId == 1 || this->MCQuark_11_PdgId == 3)
            charge = (-1. / 3.);
        if (this->MCQuark_11_PdgId == -1 || this->MCQuark_11_PdgId == -3)
            charge = (1. / 3.);

        TRootMCParticle ret(p4.Px(), p4.Py(), p4.Pz(), p4.E(), 0., 0., 0.,
                this->MCQuark_11_PdgId, charge);
        if (fabs(ret.type()) < 5) nQ++;
        ret.setStatus(3);
        if (nQ <= nWquark && fabs(ret.type()) < 5)ret.setMotherType(24);
        else ret.setMotherType(100);
        res.push_back(ret);
    }
    if (this->MCQuark_12_Pt != -999) {

        TLorentzVector p4;
        p4.SetPtEtaPhiE(this->MCQuark_12_Pt, this->MCQuark_12_Eta, this->MCQuark_12_Phi,
                this->MCQuark_12_E);
        float charge = -1000.;

        if (this->MCQuark_12_PdgId == 2 || this->MCQuark_12_PdgId == 4)
            charge = (2. / 3.);
        if (this->MCQuark_12_PdgId == -2 || this->MCQuark_12_PdgId == -4)
            charge = (-2. / 3.);
        if (this->MCQuark_12_PdgId == 1 || this->MCQuark_12_PdgId == 3)
            charge = (-1. / 3.);
        if (this->MCQuark_12_PdgId == -1 || this->MCQuark_12_PdgId == -3)
            charge = (1. / 3.);

        TRootMCParticle ret(p4.Px(), p4.Py(), p4.Pz(), p4.E(), 0., 0., 0.,
                this->MCQuark_12_PdgId, charge);
        if (fabs(ret.type()) < 5) nQ++;
        ret.setStatus(3);
        if (nQ <= nWquark && fabs(ret.type()) < 5)ret.setMotherType(24);
        else ret.setMotherType(100);
        res.push_back(ret);
    }
    return res;
}

void GenInfoMuonTree::DealWithTW(std::vector<TopTree::TRootGenTop> tops, std::vector<TopTree::TRootMCParticle> leptons) {// Assuming there is only one top and one W
    if(tops.size() > 1)
        return;
    TopTree::TRootGenTop top = tops[0];
    //    if (!top.isLeptonicMu()) {
//    cout<<"lepton size: "<<leptons.size()<<endl;
//    cout<<"top is ";
//    if(top.isLeptonicTau()){
//        cout<<"tau"<<endl;
//    }
//    if(top.isLeptonicMu()){
//        cout<<"mu"<<endl;
//    }
//    if(top.isLeptonicEl()){
//        cout<<"e"<<endl;
//    }
//    if(top.isHadronic()){
//        cout<<"had"<<endl;
//    }
    if (leptons.size() == 1) {
        WdecayInTW = this->typeConvertor(fabs(leptons[0].type()));
        if (top.isLeptonicEl() || top.isLeptonicTau() || top.isLeptonicMu())
            WdecayInTW = 4;
    }
    if (leptons.size() == 2) {
        if (top.isLeptonicEl() && fabs(leptons[0].type()) == 11)
            WdecayInTW = this->typeConvertor(fabs(leptons[1].type()));
        else
            WdecayInTW = this->typeConvertor(fabs(leptons[0].type()));
        if (top.isLeptonicTau() && fabs(leptons[0].type()) == 15)
            WdecayInTW = this->typeConvertor(fabs(leptons[1].type()));
        else
            WdecayInTW = this->typeConvertor(fabs(leptons[0].type()));
    }
    if (leptons.size() == 0)
        WdecayInTW = 4;
    //    }
}