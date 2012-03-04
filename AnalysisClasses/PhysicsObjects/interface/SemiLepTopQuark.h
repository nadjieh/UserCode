/* 
 * File:   SemiLepTopQuark.h
 * Author: nadjieh
 *
 * Created on February 21, 2012, 6:03 PM
 */

#ifndef SEMILEPTOPQUARK_H
#define	SEMILEPTOPQUARK_H
#include "TLorentzVector.h"
#include "TRandom.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootMuon.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootMET.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootPFMET.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootPFJet.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootJet.h"
using namespace TopTree;
class SemiLepTopQuark{
public:
    
    SemiLepTopQuark(TRootJet b, TRootMET mis, TRootMuon Mu):
    bJet(b),met(mis),mu(Mu){
        TLorentzVector nu = this->neutrino();
        met.SetPxPyPzE(nu.Px(),nu.Py(),nu.Pz(),sqrt(nu.Px()*nu.Px()+nu.Py()*nu.Py()+nu*nu));    
    };
    SemiLepTopQuark(TLorentzVector b, TLorentzVector mis, TLorentzVector Mu):
    bJet(b),met(mis),mu(Mu){
        TLorentzVector nu = this->neutrino();
        met.SetPxPyPzE(nu.Px(),nu.Py(),nu.Pz(),sqrt(nu.Px()*nu.Px()+nu.Py()*nu.Py()+nu*nu));    
    };
    ~SemiLepTopQuark(){};
    
    TLorentzVector neutrino(){
        double mw = 80.44;
        float solution = -10000;
        float A = mw*mw/2+(mu.Px()*met.Px()+mu.Py()*met.Py());
        float Delta = mu.E()*mu.E()*(A*A-mu.Pt()*mu.Pt()*met.Pt()*met.Pt());
        float pz1,pz2;
        if(Delta >= 0.0){
            pz1 = (A*mu.Pz()+sqrt(Delta))/pow(mu.Pt(),2);
            pz2 = (A*mu.Pz()-sqrt(Delta))/pow(mu.Pt(),2);
            if(fabs(pz1) < fabs(pz2)) solution = pz1;
            if(fabs(pz2) < fabs(pz1)) solution = pz2;
        }else{
            TRandom r;
            for(int i =0; i < 1000; i++)
            {
                mw = r.BreitWigner(80.44,2.1);
                Delta = mu.E()*mu.E()*(A*A-mu.Pt()*mu.Pt()*met.Pt()*met.Pt());
                if(Delta > 0.0){
                    pz1 = (A*mu.Pz()+sqrt(Delta))/pow(mu.Pt(),2);
                    pz2 = (A*mu.Pz()-sqrt(Delta))/pow(mu.Pt(),2);
                    if(fabs(pz1) < fabs(pz2)) solution = pz1;
                    if(fabs(pz2) < fabs(pz1)) solution = pz2;
                    break;
                }
            }
            if(solution == -10000)// MET resolution to be implemented
                solution = (A*mu.Pz())/pow(mu.Pt(),2);
        }
 
        TLorentzVector nut;
        nut.SetPxPyPzE(met.Px(),met.Py(),solution,sqrt(met.Px()*met.Px()+met.Py()*met.Py()+solution*solution));
        return nut;
    }
    TLorentzVector W(){
        return (met + mu);
    }
    TLorentzVector top(){
        return (this->W()+bJet);
    }
    double cosThetaStar(){
        //To be completed
        return -1000.;
    }
    //May be N and T directions ....
    TRootMET getMET()const{return met;}
    TRootJet getbJet()const{return bJet;}
    TRootMuon getMuon()const{return mu;}
private:
    TRootJet bJet;
    TRootMET met;
    TRootMuon mu;
    
};


#endif	/* SEMILEPTOPQUARK_H */
