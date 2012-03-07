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
#include "../../PhysicsObjects/interface/SemiLepTopQuark.h"
using namespace TopTree;
class GenSingleTopMaker{
public:
    GenSingleTopMaker(TRootNPGenEvent * genEvt, int v = 0){
        std::vector<TLorentzVector> bQuarks ;
        std::vector<TLorentzVector> quarks ;
        std::vector<TLorentzVector> muons;
        std::vector<TLorentzVector> neutrinos;
        isSemiMuSingleTop = false;
        for(unsigned int i = 0; i<genEvt->leptons().size();i++){
//            cout<<"Lepton Type: "<<genEvt->leptons().at(i).type()<<"\tStatus: "
//                <<genEvt->leptons().at(i).status()<<"\tMother: "<<genEvt->leptons().at(i).motherType()<<endl;
            if(fabs(genEvt->leptons().at(i).type()) == 13 &&
               fabs(genEvt->leptons().at(i).status()) == 3 &&
               fabs(genEvt->leptons().at(i).motherType()) == 24)
                muons.push_back(genEvt->leptons().at(i));
        }
        for(unsigned int i = 0; i<genEvt->neutrinos().size();i++){
//            cout<<"Nu Type: "<<genEvt->neutrinos().at(i).type()<<"\tStatus: "
//                <<genEvt->neutrinos().at(i).status()<<"\tMother: "<<genEvt->neutrinos().at(i).motherType()<<endl;
            if(fabs(genEvt->neutrinos().at(i).type()) == 14 &&
               fabs(genEvt->neutrinos().at(i).status()) == 3 &&
               fabs(genEvt->neutrinos().at(i).motherType()) == 24)
                neutrinos.push_back(genEvt->neutrinos().at(i));
        }
        for(unsigned int i = 0; i<genEvt->bquarks().size();i++){
//            cout<<"b Type: "<<genEvt->bquarks().at(i).type()<<"\tStatus: "
//                <<genEvt->bquarks().at(i).status()<<"\tMother: "<<genEvt->bquarks().at(i).motherType()<<endl;      
            if(fabs(genEvt->bquarks().at(i).status() == 3) && fabs(genEvt->bquarks().at(i).motherType()) == 6)
                bQuarks.push_back(genEvt->bquarks().at(i));
        }
        for(unsigned int i = 0; i<genEvt->quarks().size();i++){
//            cout<<"q Type: "<<genEvt->quarks().at(i).type()<<"\tStatus: "
//                <<genEvt->quarks().at(i).status()<<"\tMother: "<<genEvt->quarks().at(i).motherType()<<endl;      
            int m = fabs(genEvt->quarks().at(i).motherType());
            int t = fabs(genEvt->quarks().at(i).type());
            if(fabs(genEvt->quarks().at(i).status() == 3) && ( (t == 1 && m == 2) || (t == 2 && m == 1)
                || (t == 3 && m == 4) || (t == 4 && m == 3)) )                    
                quarks.push_back(genEvt->quarks().at(i));
        }
        if(muons.size() == 1 && neutrinos.size() == 1 && bQuarks.size() == 1 /* && quarks.size() == 1*/)
            isSemiMuSingleTop = true;
        if(isSemiMuSingleTop){
//            cout<<"my event :-)"<<endl;
//            cout<<"lepton: "<<muons.at(0).Px()<<", "<<muons.at(0).Py()<<", "<<muons.at(0).Pz()<<", "<<muons.at(0).Pt()<<endl;
//            cout<<"b: "<<bQuarks.at(0).Px()<<", "<<bQuarks.at(0).Py()<<", "<<bQuarks.at(0).Pz()<<", "<<bQuarks.at(0).Pt()<<endl;
//            cout<<"light b: "<<quarks.at(0).Px()<<", "<<quarks.at(0).Py()<<", "<<quarks.at(0).Pz()<<", "<<quarks.at(0).Pt()<<endl;
//            cout<<"neutrino: "<<neutrinos.at(0).Px()<<", "<<neutrinos.at(0).Py()<<", "<<neutrinos.at(0).Pz()<<", "<<neutrinos.at(0).Pt()<<endl;
            genSingleTop.setMET(neutrinos.at(0));
            genSingleTop.setMuon(muons.at(0));
            if(quarks.size() != 0)
                genSingleTop.setlightJet(quarks.at(0));
            genSingleTop.setbJet(bQuarks.at(0));
            genSingleTop.setVerbosity(v);
            
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
};

#endif	/* GENSINGLETOPMAKER_H */

