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
class GenSingleTopMaker{
public:
    GenSingleTopMaker(TRootNPGenEvent * genEvt, int v = 0){
        std::vector<TRootGenTop> tops = genEvt->tops();
        isSemiMuSingleTop = false;
        isSemiElecTt      = false;
        isSemiTauTt       = false;
        isFullHadTt       = false;
        isDiMuTt          = false;
        isDiETt           = false;
        isMuETt           = false;
        isDiTauTt         = false;
        isMuTauTt         = false;
        isETauTt          = false;
        isDiLep           = false;
        if(tops.size() == 1 && tops.at(0).isLeptonicMu()){
            isSemiMuSingleTop = true;
            if(isSemiMuSingleTop){
                genSingleTop.setMuon(tops.at(0).lepton());
                genSingleTop.setMET(tops.at(0).neutrino());
                genSingleTop.setbJet(tops.at(0).bquark());
                genSingleTop.setMuCharge(tops.at(0).lepton().charge());
                genSingleTop.setVerbosity(v);
                if(genEvt->leptons().size() > 1){
                    int nLep = 0;
                    for(unsigned int p = 0; p <genEvt->leptons().size(); p++ ){
                        if(fabs(genEvt->leptons().at(p).motherType()) == 24 && fabs(genEvt->leptons().at(p).status()) == 3)
                            nLep++;
                    }
                    if(nLep > 0)
                        isSemiMuSingleTop = false;
                }
            }
        }else if(tops.size() == 2){
            if((tops.at(0).isLeptonicMu() && tops.at(1).isHadronic()) ||
               (tops.at(1).isLeptonicMu() && tops.at(0).isHadronic())){
                isSemiMuSingleTop = true;
                TRootGenTop myTop = tops.at(0);
                if(!myTop.isLeptonicMu())
                    myTop = tops.at(1);
                genSingleTop.setMuon(myTop.lepton());
                genSingleTop.setMET(myTop.neutrino());
                genSingleTop.setbJet(myTop.bquark());
                genSingleTop.setMuCharge(myTop.lepton().charge());
                genSingleTop.setVerbosity(v);
            }
            isSemiElecTt = ((tops.at(0).isLeptonicEl() && tops.at(1).isHadronic())||
                            (tops.at(1).isLeptonicEl() && tops.at(0).isHadronic()));
            isSemiTauTt = ((tops.at(0).isLeptonicTau() && tops.at(1).isHadronic())||
                           (tops.at(1).isLeptonicTau() && tops.at(0).isHadronic()));
            isETauTt  = ((tops.at(0).isLeptonicEl() && tops.at(1).isLeptonicTau())||
                         (tops.at(1).isLeptonicEl() && tops.at(0).isLeptonicTau()));
            isMuTauTt = ((tops.at(0).isLeptonicMu() && tops.at(1).isLeptonicTau())||
                         (tops.at(1).isLeptonicMu() && tops.at(0).isLeptonicTau()));
            isMuETt   = ((tops.at(0).isLeptonicMu() && tops.at(1).isLeptonicEl())||
                         (tops.at(1).isLeptonicMu() && tops.at(0).isLeptonicEl()));
            isDiTauTt = (tops.at(0).isLeptonicTau() && tops.at(1).isLeptonicTau());
            isDiMuTt  = (tops.at(0).isLeptonicMu() && tops.at(1).isLeptonicMu());
            isDiETt   = (tops.at(0).isLeptonicEl() && tops.at(1).isLeptonicEl());
            isFullHadTt = (tops.at(0).isHadronic() && tops.at(1).isHadronic());
        }
    }
    GenSingleTopMaker(TRootGenEvent * genEvt, int v = 0){
        if(genEvt->isSemiLeptonic(TopTree::TRootGenEvent::kMuon)){
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
           
            
        }else{
            isSemiMuSingleTop = false;
        }
    }
    ~GenSingleTopMaker(){}
    SemiLepTopQuark genSingleTop;
    bool isSemiMuSingleTop;
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
};

#endif	/* GENSINGLETOPMAKER_H */

