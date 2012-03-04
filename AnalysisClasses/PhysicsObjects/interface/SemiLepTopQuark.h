/* 
 * File:   SemiLepTopQuark.h
 * Author: nadjieh
 *
 * Created on February 21, 2012, 6:03 PM
 */

#ifndef SEMILEPTOPQUARK_H
#define	SEMILEPTOPQUARK_H
#include <iostream>
#include "TLorentzVector.h"
#include "TRandom1.h"
#include "TVector3.h"
#include "TH1.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootMuon.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootMET.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootPFMET.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootPFJet.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootJet.h"
using namespace TopTree;
using namespace std;
class SemiLepTopQuark{
public:
    
    SemiLepTopQuark(TRootPFJet b, TRootPFMET mis, TRootMuon Mu, TRootPFJet b2,TH1D * res ,int v = 0):
    bJet(b),lightJet(b2),met(mis),mu(Mu),resolutions(res),verbosity(v){        
//        cout<<"MET: "<<met.Px()<<"\t"<<met.Py()<<endl;
//        cout<<"Muon: "<<mu.Px()<<"\t"<<mu.Py()<<"\t"<<mu.Pz()<<endl;
//        cout<<"bjet: "<<bJet.Px()<<"\t"<<bJet.Py()<<"\t"<<bJet.Pz()<<endl;
//        cout<<"bjet: "<<lightJet.Px()<<"\t"<<lightJet.Py()<<"\t"<<lightJet.Pz()<<endl;
        TLorentzVector nu = this->neutrino();
        met.SetPxPyPzE(nu.Px(),nu.Py(),nu.Pz(),sqrt(nu.Px()*nu.Px()+nu.Py()*nu.Py()+nu.Pz()*nu.Pz()));    
    };
    SemiLepTopQuark(TLorentzVector b, TLorentzVector mis, TLorentzVector Mu, TLorentzVector b2, TH1D * res ,int v = 0):
    bJet(b),lightJet(b2),met(mis),mu(Mu),resolutions(res),verbosity(v){
        TLorentzVector nu = this->neutrino();
        met.SetPxPyPzE(nu.Px(),nu.Py(),nu.Pz(),sqrt(nu.Px()*nu.Px()+nu.Py()*nu.Py()+nu*nu));    
    };
    SemiLepTopQuark():
    bJet(-1,-1,-1,-1),lightJet(-1,-1,-1,-1),met(-1,-1,-1,-1),mu(-1,-1,-1,-1),resolutions(0),verbosity(0){};
    ~SemiLepTopQuark(){};
    
   
    TLorentzVector neutrino(){
        double mw = 80.44;
        float solution = -10000;
        double Delta = delta(mw,mu,met);
        TLorentzVector nut;
        if(verbosity > 0)
            cout<<"The first delta value is "<<Delta<<endl;
        if(Delta >= 0.0){
            if(verbosity > 0)
                cout<<"so I immediately calculate pz.";
            solution = pZNeutrino(mw,mu,met);
            if(verbosity > 0)
                cout<<"\n\tsolution = "<<solution<<endl;
            nut.SetPxPyPzE(met.Px(),met.Py(),solution,sqrt(met.Px()*met.Px()+met.Py()*met.Py()+solution*solution));
            return nut;
        }
//        if(verbosity > 0)
//            cout<<"so I try first the MET smearing ..."<<endl;
        for(int i =0; i < 1000; i++)
        {
            mw = 80.44;
//            TLorentzVector tmpMet = smearedMET();
//            if(verbosity > 0)
//                cout<<"after MET smearing\n\t"<<tmpMet.Px()<<"\t"<<tmpMet.Py()<<endl;
//            Delta = delta(mw,mu,tmpMet);
//            if(verbosity > 0)
//                cout<<"after MET smearing\n\tDelta: "<<Delta<<endl;
//            if(Delta >= 0.0){
//                if(verbosity > 0)
//                    cout<<"The delta from MET smearing becomes "<<Delta<<endl;
//                solution = pZNeutrino(mw,mu,tmpMet);
//                if(verbosity > 0)
//                    cout<<"\n\tsolution = "<<solution<<endl;
//                nut.SetPxPyPzE(tmpMet.Px(),tmpMet.Py(),solution,sqrt(tmpMet.Px()*tmpMet.Px()+tmpMet.Py()*tmpMet.Py()+solution*solution));
//                break;
//            }
            mw = smearedWmass();
            Delta = delta(mw,mu,met);
            if(verbosity > 0)
                cout<<"MET smearing did not help. Now Wmass smearing ... Wmass is "<<mw<<"\n\tDelta is"<<Delta<<endl;
            if(Delta >= 0.0){
                if(verbosity > 0)
                    cout<<"The delta from Wmass smearing becomes "<<Delta<<endl;
                solution = pZNeutrino(mw,mu,met);
                if(verbosity > 0)
                    cout<<"\n\tsolution = "<<solution<<endl;
                nut.SetPxPyPzE(met.Px(),met.Py(),solution,sqrt(met.Px()*met.Px()+met.Py()*met.Py()+solution*solution));
                break;
            }
            
            if(verbosity > 0)
                cout<<"mW smearing did not help either. Once again ..."<<endl;
                
        }
        if(solution == -10000){
            std::cout<<"MET does not have solution event after MET and mW smearing.\n";
            std::cout<<"The solution is returned as if Delta was zero ..."<<std::endl;
            mw = 80.44;
            solution = (A(mw,mu,met)*mu.Pz())/pow(mu.Pt(),2);
            nut.SetPxPyPzE(met.Px(),met.Py(),solution,sqrt(met.Px()*met.Px()+met.Py()*met.Py()+solution*solution));
        }
        return nut;
    }
    TLorentzVector W(){
        return (met + mu);
    }
    TLorentzVector top(){
        return (this->W()+bJet);
    }
    double cosThetaStar(){
        TLorentzVector w = this->W();
        if(verbosity>0){
            cout<<"W boson:"<<w.Px()<<", "<<w.Py()<<", "<<w.Pz()<<endl;
        }
        TLorentzVector muClone = mu;
        TLorentzVector Top = this->top();
        if(verbosity>0){
            cout<<"top quark:"<<Top.Px()<<", "<<Top.Py()<<", "<<Top.Pz()<<endl;
        }
        muClone.Boost(- w.BoostVector());
        w.Boost(-Top.BoostVector());
        if(verbosity>0){
            cout<<"Boosted mu:"<<muClone.Px()<<", "<<muClone.Py()<<", "<<muClone.Pz()<<endl;
            cout<<"Boosted W:"<<w.Px()<<", "<<w.Py()<<", "<<w.Pz()<<endl;
        }
        if(ROOT::Math::VectorUtil::CosTheta(w,muClone)>1.0)
            cout<<"=================== what a hell!!! "<<endl;
        return ROOT::Math::VectorUtil::CosTheta(w,muClone);
        /*const TVector3 w3 = w.Vect(); const TVector3 mu3 = muClone.Vect(); 
        double res = (double)(w3.Dot(mu3))/(double)(w3.Mag()*mu3.Mag());      
        return res;*/
    }

    //May be N and T directions ....
    TLorentzVector getMET()const{return met;}
    TLorentzVector getbJet()const{return bJet;}
    TLorentzVector getlightJet()const{return lightJet;}
    TLorentzVector getMuon()const{return mu;}
    
    void setMET(TLorentzVector MET){ met = MET;}
    void setbJet(TLorentzVector jet){ bJet = jet;}
    void setlightJet(TLorentzVector jet){ lightJet = jet;}
    void setMuon(TLorentzVector muon){ mu = muon;}
    void setVerbosity(int v){ verbosity = v;}
    void printContent(){
        cout<<"lepton: "<<mu.Px()<<", "<<mu.Py()<<", "<<mu.Pz()<<", "<<mu.Pt()<<endl;
        cout<<"b: "<<bJet.Px()<<", "<<bJet.Py()<<", "<<bJet.Pz()<<", "<<bJet.Pt()<<endl;
        cout<<"light b: "<<lightJet.Px()<<", "<<lightJet.Py()<<", "<<lightJet.Pz()<<", "<<lightJet.Pt()<<endl;
        cout<<"neutrino: "<<met.Px()<<", "<<met.Py()<<", "<<met.Pz()<<", "<<met.Pt()<<endl;
    }
private:
    double A(double mw, TLorentzVector muon, TLorentzVector Emis){
//        cout<<"mw*mw/2: "<<mw*mw/2<<"\nmuon.Px()*Emis.Px()+muon.Py()*Emis.Py(): "<<muon.Px()*Emis.Px()+muon.Py()*Emis.Py()<<endl;
//        cout<<"A: "<<mw*mw/2+(muon.Px()*Emis.Px()+muon.Py()*Emis.Py())<<endl;
         return (mw*mw/2+(muon.Px()*Emis.Px()+muon.Py()*Emis.Py()));        
    }
    double delta(double mw, TLorentzVector muon, TLorentzVector Emis){
//        cout<<"Delta: "<<(muon.E()*muon.E()*A(mw,muon,Emis)*A(mw,muon,Emis)
//                -muon.Pt()*muon.Pt()*Emis.Pt()*Emis.Pt()*muon.E()*muon.E())<<endl;
        return (muon.E()*muon.E()*A(mw,muon,Emis)*A(mw,muon,Emis)
                -muon.Pt()*muon.Pt()*Emis.Pt()*Emis.Pt()*muon.E()*muon.E());
    }
    double pZ(double mw, TLorentzVector muon, TLorentzVector Emis, bool plusSolution){
        double a = A(mw,muon,Emis);
        double Delta = delta(mw,muon,Emis);
        double res = -1000;
        if(plusSolution)
            res = (a*mu.Pz()+sqrt(Delta))/pow(mu.Pt(),2);
        else
            res = (a*mu.Pz()-sqrt(Delta))/pow(mu.Pt(),2);
        return res;
    }
    double pZNeutrino(double mw, TLorentzVector muon, TLorentzVector Emis){
        double pplus = fabs(pZ(mw,muon,Emis,true));
        double pminus = fabs(pZ(mw,muon,Emis,false));
        if(verbosity > 0){
            cout<<"\n\tpZ1 = "<<pplus<<"\n\tpZ2 = "<<pminus;
        }
        if(pplus >= pminus )
            return pminus;
        else
            return pplus;
    }
    TLorentzVector smearedMET(){
        double resolution;
        if(met.Pt() < 30){
            resolution = resolutions->GetBinContent(1)*met.Pt();
            if(verbosity > 0){
                cout<<"MET: "<<met.Pt()<<", resoution: "<<resolutions->GetBinContent(1)<<endl;
            }
        }else if(met.Pt() >= 30 && met.Pt() < 40){
            resolution = resolutions->GetBinContent(2)*met.Pt();            
            if(verbosity > 0){
                cout<<"MET: "<<met.Pt()<<", resoution: "<<resolutions->GetBinContent(2)<<endl;
            }
        }else if(met.Pt() >= 40 && met.Pt() < 50){
            resolution = resolutions->GetBinContent(3)*met.Pt();            
            if(verbosity > 0){
                cout<<"MET: "<<met.Pt()<<", resoution: "<<resolutions->GetBinContent(3)<<endl;
            }
        }else if(met.Pt() >= 50 && met.Pt() < 60){
            resolution = resolutions->GetBinContent(4)*met.Pt();            
            if(verbosity > 0){
                cout<<"MET: "<<met.Pt()<<", resoution: "<<resolutions->GetBinContent(4)<<endl;
            }
        }else if(met.Pt() >= 60 && met.Pt() < 80){
            resolution = resolutions->GetBinContent(5)*met.Pt();            
            if(verbosity > 0){
                cout<<"MET: "<<met.Pt()<<", resoution: "<<resolutions->GetBinContent(5)<<endl;
            }
        }else if(met.Pt() >= 80 && met.Pt() < 100){
            resolution = resolutions->GetBinContent(6)*met.Pt();            
            if(verbosity > 0){
                cout<<"MET: "<<met.Pt()<<", resoution: "<<resolutions->GetBinContent(6)<<endl;
            }
        }else {
            resolution = resolutions->GetBinContent(7)*met.Pt();
            if(verbosity > 0){
                cout<<"MET: "<<met.Pt()<<", resoution: "<<resolutions->GetBinContent(7)<<endl;
            }
        }
        TRandom1 r1;
        double metX = r1.Gaus(met.Px(),resolution);
        double metY = r1.Gaus(met.Py(),resolution);
        TLorentzVector tmpMet(metX,metY,0,sqrt(metX*metX+metY*metY));
        return tmpMet;
    }
    double smearedWmass(){
        TRandom1 r;
        return r.BreitWigner(80.44,2.1);
    }

    TLorentzVector bJet;
    TLorentzVector lightJet;
    TLorentzVector met;
    TLorentzVector mu;
    TH1D * resolutions;
    int verbosity;
};


#endif	/* SEMILEPTOPQUARK_H */

	
