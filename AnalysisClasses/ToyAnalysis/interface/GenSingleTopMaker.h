/* 
 * File:   GenSingleTopMaker.h
 * Author: nadjieh
 *
 * Created on February 29, 2012, 12:49 PM
 */

#ifndef GENSINGLETOPMAKER_H
#define	GENSINGLETOPMAKER_H

#include <vector>
#include "TLorentzVector.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootNPGenEvent.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootGenEvent.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootMCParticle.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootGenTop.h"
#include "../../PhysicsObjects/interface/SemiLepTopQuark.h"
using namespace TopTree;

class GenSingleTopMaker {
public:

    GenSingleTopMaker(TRootNPGenEvent * genEvt, int v = 0) {
        genEvt->topChargeBassigner();
        std::vector<TRootGenTop> tops = genEvt->tops();
        ntops = tops.size();
//        cout<<"Number of tops: "<<ntops<<endl;
        nonTopWs = genEvt->getNonTopWList();
        //        cout<<tops.size()<<endl;
        isSemiMuSingleTop = false;
        isHadSingleTop = false;
        isSemiElecTt = false;
        isSemiTauTt = false;
        isFullHadTt = false;
        isDiMuTt = false;
        isDiETt = false;
        isMuETt = false;
        isDiTauTt = false;
        isMuTauTt = false;
        isETauTt = false;
        isDiLep = false;



        if (ntops == 1 && tops.at(0).isLeptonic()) {
            isSemiMuSingleTop = tops.at(0).isLeptonicMu();
            isSemiElecTt = tops.at(0).isLeptonicEl();
            isSemiTauTt = tops.at(0).isLeptonicTau();
            if (isSemiMuSingleTop) {
                //                cout << "here I am! " << endl;
                genSingleTop.setMuon(tops.at(0).lepton());
                genSingleTop.setMET(tops.at(0).neutrino());
                genSingleTop.setbJet(tops.at(0).bquark());
                genSingleTop.setMuCharge(tops.at(0).lepton().charge());
                genSingleTop.setVerbosity(v);
            }
            if (nonTopWs.size() == 1) {
                if ((isSemiElecTt || isSemiTauTt) && nonTopWs[0] == 2) {
                    //                    cout << "here I am not!!!! " << endl;
                    genSingleTop.setMuon(tops.at(0).lepton());
                    genSingleTop.setMET(tops.at(0).neutrino());
                    genSingleTop.setbJet(tops.at(0).bquark());
                    genSingleTop.setMuCharge(tops.at(0).W().charge());
                    genSingleTop.setVerbosity(v);
                }
            }

            /*
             * for tW-channel
             */
        } else if (ntops == 1 && tops.at(0).isHadronic()) {//single t t-channel
            isHadSingleTop = true;
            if (nonTopWs.size() == 1) {
                if (isHadSingleTop) {
//                    cout<< "b: "<< tops.at(0).bquark().type()<<"\t"<<tops.at(0).bquark().motherType()<<"\t"<<tops.at(0).bquark().Pt()<<endl;
//                    cout<< "q: "<< tops.at(0).quark().type()<<"\t"<<tops.at(0).quark().motherType()<<"\t"<<tops.at(0).quark().Pt()<<endl;
//                    cout<< "qbar: "<< tops.at(0).quarkBar().type()<<"\t"<<tops.at(0).quarkBar().motherType()<<"\t"<<tops.at(0).quarkBar().Pt()<<endl;
                    TRootMCParticle trueGenb = tops.at(0).bquark();
                    if (tops.at(0).isDownQBar()) {
                        genSingleTop.setMuon(tops.at(0).quarkBar());
                        genSingleTop.setMET(tops.at(0).quark());
                    } else {
                        genSingleTop.setMET(tops.at(0).quarkBar());
                        genSingleTop.setMuon(tops.at(0).quark());
                    }

                    genSingleTop.setbJet(trueGenb);
//                    cout<< "b: "<< tops.at(0).bquark().type()<<"\t"<<tops.at(0).bquark().motherType()<<"\t"<<tops.at(0).bquark().Pt()<<endl;
                    genSingleTop.setMuCharge(tops.at(0).W().charge());
                    genSingleTop.setVerbosity(v);

                    TLorentzVector q = genSingleTop.top(0);
                    if (fabs(q.M() - tops.at(0).M()) > 0.001) {
                        cout << "top mass difference: " << q.M() - tops.at(0).M() << endl;
                        cout << "q mass: " << q.M() << "\ttop mass:" << tops.at(0).M() << endl;
                    }
                }
            }

        } else if (ntops == 2) {
            if ((tops.at(0).isLeptonicMu() && tops.at(1).isHadronic()) ||
                    (tops.at(1).isLeptonicMu() && tops.at(0).isHadronic())) {
                isSemiMuSingleTop = true;
                TRootGenTop myTopLep = tops.at(0);
                TRootGenTop myTopHad = tops.at(1);
                if (!myTopLep.isLeptonicMu()) {
                    myTopLep = tops.at(1);
                    myTopHad = tops.at(0);
                }

                genSingleTop.setMuon(myTopLep.lepton());
                genSingleTop.setMET(myTopLep.neutrino());
                genSingleTop.setbJet(myTopLep.bquark());
                genSingleTop.setMuCharge(myTopLep.lepton().charge());
                genSingleTop.setVerbosity(v);

                if (myTopHad.isDownQBar()) {
                    genSingleTopSecond.setMuon(myTopHad.quarkBar());
                    genSingleTopSecond.setMET(myTopHad.quark());
                } else {
                    genSingleTopSecond.setMuon(myTopHad.quark());
                    genSingleTopSecond.setMET(myTopHad.quarkBar());
                }
                genSingleTopSecond.setbJet(myTopHad.bquark());
                genSingleTopSecond.setMuCharge(myTopHad.lepton().charge());
                genSingleTopSecond.setVerbosity(v);
            }
            isSemiElecTt = ((tops.at(0).isLeptonicEl() && tops.at(1).isHadronic()) ||
                    (tops.at(1).isLeptonicEl() && tops.at(0).isHadronic()));
            isSemiTauTt = ((tops.at(0).isLeptonicTau() && tops.at(1).isHadronic()) ||
                    (tops.at(1).isLeptonicTau() && tops.at(0).isHadronic()));
            isETauTt = ((tops.at(0).isLeptonicEl() && tops.at(1).isLeptonicTau()) ||
                    (tops.at(1).isLeptonicEl() && tops.at(0).isLeptonicTau()));
            isMuTauTt = ((tops.at(0).isLeptonicMu() && tops.at(1).isLeptonicTau()) ||
                    (tops.at(1).isLeptonicMu() && tops.at(0).isLeptonicTau()));
            isMuETt = ((tops.at(0).isLeptonicMu() && tops.at(1).isLeptonicEl()) ||
                    (tops.at(1).isLeptonicMu() && tops.at(0).isLeptonicEl()));
            isDiTauTt = (tops.at(0).isLeptonicTau() && tops.at(1).isLeptonicTau());
            isDiMuTt = (tops.at(0).isLeptonicMu() && tops.at(1).isLeptonicMu());
            isDiETt = (tops.at(0).isLeptonicEl() && tops.at(1).isLeptonicEl());
            isFullHadTt = (tops.at(0).isHadronic() && tops.at(1).isHadronic());

            if (isMuTauTt) {
                TRootGenTop myTopMu = tops.at(0);
                TRootGenTop myTopTau = tops.at(1);
                if (!myTopMu.isLeptonicMu()) {
                    myTopMu = tops.at(1);
                    myTopTau = tops.at(0);
                }
                genSingleTop.setMuon(myTopMu.lepton());
                genSingleTop.setMET(myTopMu.neutrino());
                genSingleTop.setbJet(myTopMu.bquark());
                genSingleTop.setMuCharge(myTopMu.lepton().charge());
                genSingleTop.setVerbosity(v);

                genSingleTopSecond.setMuon(myTopTau.lepton());
                genSingleTopSecond.setMET(myTopTau.neutrino());
                genSingleTopSecond.setbJet(myTopTau.bquark());
                genSingleTopSecond.setMuCharge(myTopTau.lepton().charge());
                genSingleTopSecond.setVerbosity(v);

            } else if (isMuETt) {
                TRootGenTop myTopMu = tops.at(0);
                TRootGenTop myTopE = tops.at(1);
                if (!myTopMu.isLeptonicMu()) {
                    myTopMu = tops.at(1);
                    myTopE = tops.at(0);
                }
                genSingleTop.setMuon(myTopMu.lepton());
                genSingleTop.setMET(myTopMu.neutrino());
                genSingleTop.setbJet(myTopMu.bquark());
                genSingleTop.setMuCharge(myTopMu.lepton().charge());
                genSingleTop.setVerbosity(v);

                genSingleTopSecond.setMuon(myTopE.lepton());
                genSingleTopSecond.setMET(myTopE.neutrino());
                genSingleTopSecond.setbJet(myTopE.bquark());
                genSingleTopSecond.setMuCharge(myTopE.lepton().charge());
                genSingleTopSecond.setVerbosity(v);

            } else if (isDiMuTt) {

                TRootGenTop myTop = tops.at(0);

                genSingleTop.setMuon(myTop.lepton());
                genSingleTop.setMET(myTop.neutrino());
                genSingleTop.setbJet(myTop.bquark());
                genSingleTop.setMuCharge(myTop.lepton().charge());
                genSingleTop.setVerbosity(v);

                myTop = tops.at(1);
                genSingleTopSecond.setMuon(myTop.lepton());
                genSingleTopSecond.setMET(myTop.neutrino());
                genSingleTopSecond.setbJet(myTop.bquark());
                genSingleTopSecond.setMuCharge(myTop.lepton().charge());
                genSingleTopSecond.setVerbosity(v);
            }
        }
    }


    GenSingleTopMaker(TRootGenEvent * genEvt, int v = 0) {
        if (genEvt->isSemiLeptonic(TopTree::TRootGenEvent::kMuon)) {
            isSemiMuSingleTop = true;
            //            cout<<"my event :-)"<<endl;
            //            cout<<"lepton: "<<muons.at(0).Px()<<", "<<muons.at(0).Py()<<", "<<muons.at(0).Pz()<<", "<<muons.at(0).Pt()<<endl;
            //            cout<<"b: "<<bQuarks.at(0).Px()<<", "<<bQuarks.at(0).Py()<<", "<<bQuarks.at(0).Pz()<<", "<<bQuarks.at(0).Pt()<<endl;
            //            cout<<"light b: "<<quarks.at(0).Px()<<", "<<quarks.at(0).Py()<<", "<<quarks.at(0).Pz()<<", "<<quarks.at(0).Pt()<<endl;
            //            cout<<"neutrino: "<<neutrinos.at(0).Px()<<", "<<neutrinos.at(0).Py()<<", "<<neutrinos.at(0).Pz()<<", "<<neutrinos.at(0).Pt()<<endl;

            genSingleTop.setMET(genEvt->neutrino());
            genSingleTop.setMuon(genEvt->lepton());
            genSingleTop.setbJet(genEvt->leptonicDecayB());
            genSingleTop.setVerbosity(v);


        } else {

            isSemiMuSingleTop = false;
        }
    }

    GenSingleTopMaker(TRootGenEvent * genEvt, bool s) {
        if (genEvt->isSemiLeptonic(TopTree::TRootGenEvent::kMuon)) {
            isSemiMuSingleTop = true;
            //            cout<<"my event :-)"<<endl;
            //            cout<<"lepton: "<<muons.at(0).Px()<<", "<<muons.at(0).Py()<<", "<<muons.at(0).Pz()<<", "<<muons.at(0).Pt()<<endl;
            //            cout<<"b: "<<bQuarks.at(0).Px()<<", "<<bQuarks.at(0).Py()<<", "<<bQuarks.at(0).Pz()<<", "<<bQuarks.at(0).Pt()<<endl;
            //            cout<<"light b: "<<quarks.at(0).Px()<<", "<<quarks.at(0).Py()<<", "<<quarks.at(0).Pz()<<", "<<quarks.at(0).Pt()<<endl;
            //            cout<<"neutrino: "<<neutrinos.at(0).Px()<<", "<<neutrinos.at(0).Py()<<", "<<neutrinos.at(0).Pz()<<", "<<neutrinos.at(0).Pt()<<endl;

            genSingleTop.setMET(genEvt->hadronicDecayQuark());
            genSingleTop.setMuon(genEvt->hadronicDecayQuarkBar());
            genSingleTop.setbJet(genEvt->hadronicDecayB());
            genSingleTop.setVerbosity(0);


        } else {

            isSemiMuSingleTop = false;
        }
    }

    ~GenSingleTopMaker() {
    }
    SemiLepTopQuark genSingleTop;
    SemiLepTopQuark genSingleTopSecond;
    bool isSemiMuSingleTop;
    bool isHadSingleTop;
    bool isSemiElecTt;
    bool isSemiTauTt;
    bool isFullHadTt;
    bool isDiMuTt;
    bool isDiETt;
    bool isMuETt;
    bool isDiTauTt;
    bool isMuTauTt;
    bool isETauTt;
    bool isDiLep;
    int ntops;

    std::vector<int > nonTopWs;

};

#endif	/* GENSINGLETOPMAKER_H */

