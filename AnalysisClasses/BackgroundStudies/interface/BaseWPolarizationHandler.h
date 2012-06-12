/* 
 * File:   BaseWPolarizationHandler.h
 * Author: nadjieh
 *
 * Created on June 6, 2012, 12:55 PM
 */

#ifndef BASEWPOLARIZATIONHANDLER_H
#define	BASEWPOLARIZATIONHANDLER_H
#include "../../ToyAnalysis/interface/MyObjectProperties.h"
#include "../../PhysicsObjects/interface/SemiLepTopQuark.h"
#include "../../../Base/BaseAnalysis/interface/TH1Ext.h"
#include "../../../Base/BaseAnalysis/interface/TH2Ext.h"
#include "../../../Base/BaseAnalysis/interface/EfficiencyHandler.h"
#include <string>
#include <iostream>
using namespace std;
class BaseWPolarizationHandler : public EfficiencyHandler <SemiLepTopQuark> {
public:
    typedef EfficiencyHandler<SemiLepTopQuark> BASE_;

    BaseWPolarizationHandler(string name, bool doEff = false):BASE_(name), doEfficiency(doEff){
        BASE_::AllCondition = 0;
        if(doEfficiency){
            BASE_::AddProp(new HT());
            BASE_::AddProp(new FwDJetEta());
            BASE_::AddProp(new CosThetaStarMET());
            BASE_::AddProp(new CosThetaStarW());
        }
        HT * ht = new HT();
        FwDJetEta * fwdEta = new FwDJetEta();
        Histograms2D.push_back(ht->GetH2(fwdEta,"",""));
    };
    virtual ~BaseWPolarizationHandler(){};
    virtual std::string WhoAmI()const{
        return "BaseWPolarizationHandler";
    }
    virtual void Fill(const SemiLepTopQuark* theObject, double weight = 1) {
        if(doEfficiency)
            BASE_::Fill(theObject,weight);
        for(unsigned int i = 0; i < Histograms2D.size(); i++){
            Histograms2D.at(i)->Fill(theObject, weight);
        }
        for(unsigned int i = 0; i < Histograms1D.size(); i++){
            Histograms1D.at(i)->Fill(theObject, weight);
        }
    }

    virtual void WriteAll(TDirectory* dir){
        if(dir == NULL)
            cout<<"Bad Directory in SpecificHandler"<<endl;
        if(doEfficiency)
            BASE_::WriteAll(dir);
        dir->cd();
        dir->mkdir("Hist2D")->cd();
        for(unsigned int i = 0; i < Histograms2D.size(); i++){
            Histograms2D.at(i)->Write();
        }
        dir->cd();
        dir->mkdir("Hist1D")->cd();
        for(unsigned int i = 0; i < Histograms1D.size(); i++){
            Histograms1D.at(i)->Write();
        }

    }
    void ResetConditionForAllProps(){
        if(!doEfficiency)
            return;
        for(uint i = 0 ; i < EfficiencyHandler<SemiLepTopQuark>::GetProperties() ; i++){
            EfficiencyHandler<SemiLepTopQuark>::GetEffH1(i)->Condition = EfficiencyHandler<SemiLepTopQuark>::Condition;
            EfficiencyHandler<SemiLepTopQuark>::GetEffH1(i)->AllCondition = EfficiencyHandler<SemiLepTopQuark>::AllCondition;
        }
    }
//       .
//      .|.
//       |      |
//       |  A   |  B
//  y-cut|------|-------
//       |  C   |  D
//       |------|------->
//             x-cut
    
    double Fac(unsigned int n, double x_cut, double y_cut)const{
        int XbinCut = Histograms2D.at(n)->GetXaxis()->FindBin(x_cut);
        int XbinFirst= Histograms2D.at(n)->GetXaxis()->GetFirst();
        int YbinCut = Histograms2D.at(n)->GetYaxis()->FindBin(y_cut);
        int YbinEnd = Histograms2D.at(n)->GetYaxis()->GetLast();
        int YbinFirst = Histograms2D.at(n)->GetYaxis()->GetFirst();
        
        double nA = Histograms2D.at(n)->Integral(XbinFirst,XbinCut-1,YbinCut,YbinEnd);
        double nC = Histograms2D.at(n)->Integral(XbinFirst,XbinCut-1,YbinFirst,YbinCut-1);
        
        return (double)nA/(double)nC;
    }
    double Fca(unsigned int n, double x_cut, double y_cut)const{
        double ret = this->Fac(n,x_cut,y_cut);
        if(ret != 0)
            return (double)1/(double)ret;
        return -10000;
    }
    
//       .
//      .|.
//       |      |
//       |  A   |  B
//  y-cut|------|-------
//       |  C   |  D
//       |------|------->
//             x-cut
    
    double Fbd(unsigned int n, double x_cut, double y_cut)const{
        int XbinCut = Histograms2D.at(n)->GetXaxis()->FindBin(x_cut);
        int XbinEnd= Histograms2D.at(n)->GetXaxis()->GetLast();
        int YbinCut = Histograms2D.at(n)->GetYaxis()->FindBin(y_cut);
        int YbinEnd = Histograms2D.at(n)->GetYaxis()->GetLast();
        int YbinFirst = Histograms2D.at(n)->GetYaxis()->GetFirst();
        
        double nB = Histograms2D.at(n)->Integral(XbinCut,XbinEnd,YbinCut,YbinEnd);
        double nD = Histograms2D.at(n)->Integral(XbinCut,XbinEnd,YbinFirst,YbinCut-1);
        
        return (double)nB/(double)nD;
    }
    double Fdb(unsigned int n, double x_cut, double y_cut)const{
        double ret = this->Fbd(n,x_cut,y_cut);
        if(ret != 0)
            return (double)1/(double)ret;
        return -10000;
    }
    
//       .
//      .|.
//       |      |
//       |  A   |  B
//  y-cut|------|-------
//       |  C   |  D
//       |------|------->
//             x-cut
    
    double Fab(unsigned int n, double x_cut, double y_cut)const{
        int XbinCut = Histograms2D.at(n)->GetXaxis()->FindBin(x_cut);
        int XbinEnd= Histograms2D.at(n)->GetXaxis()->GetLast();
        int XbinFirst= Histograms2D.at(n)->GetXaxis()->GetLast();
        int YbinCut = Histograms2D.at(n)->GetYaxis()->FindBin(y_cut);
        int YbinEnd = Histograms2D.at(n)->GetYaxis()->GetLast();
                
        double nA = Histograms2D.at(n)->Integral(XbinFirst,XbinCut-1,YbinCut,YbinEnd);
        double nB = Histograms2D.at(n)->Integral(XbinCut,XbinEnd,YbinCut,YbinEnd);
        
        return (double)nA/(double)nB;
    }
    double Fba(unsigned int n, double x_cut, double y_cut)const{
        double ret = this->Fab(n,x_cut,y_cut);
        if(ret != 0)
            return (double)1/(double)ret;
        return -10000;
    }  
    
//       .
//      .|.
//       |      |
//       |  A   |  B
//  y-cut|------|-------
//       |  C   |  D
//       |------|------->
//             x-cut
    
    double Fcd(unsigned int n, double x_cut, double y_cut)const{
        int XbinCut = Histograms2D.at(n)->GetXaxis()->FindBin(x_cut);
        int XbinEnd= Histograms2D.at(n)->GetXaxis()->GetLast();
        int XbinFirst= Histograms2D.at(n)->GetXaxis()->GetLast();
        int YbinCut = Histograms2D.at(n)->GetYaxis()->FindBin(y_cut);
        int YbinEnd = Histograms2D.at(n)->GetYaxis()->GetLast();
        int YbinFirst= Histograms2D.at(n)->GetXaxis()->GetFirst();
                
        double nC = Histograms2D.at(n)->Integral(XbinFirst,XbinCut-1,YbinFirst,YbinCut-1);
        double nD = Histograms2D.at(n)->Integral(XbinCut,XbinEnd,YbinFirst,YbinEnd);
        
        return (double)nC/(double)nD;
    }
    double Fdc(unsigned int n, double x_cut, double y_cut)const{
        double ret = this->Fcd(n,x_cut,y_cut);
        if(ret != 0)
            return (double)1/(double)ret;
        return -10000;
    }
//       .
//      .|.
//       |      |
//       |  A   |  B
//  y-cut|------|-------
//       |  C   |  D
//       |------|------->
//             x-cut
    
    double Fud(unsigned int n, double x_cut, double y_cut)const{
        int XbinEnd= Histograms2D.at(n)->GetXaxis()->GetLast();
        int XbinFirst= Histograms2D.at(n)->GetXaxis()->GetLast();
        int YbinCut = Histograms2D.at(n)->GetYaxis()->FindBin(y_cut);
        int YbinEnd = Histograms2D.at(n)->GetYaxis()->GetLast();
        int YbinFirst= Histograms2D.at(n)->GetXaxis()->GetFirst();
                
        double nU = Histograms2D.at(n)->Integral(XbinFirst,XbinEnd,YbinCut,YbinEnd);
        double nD = Histograms2D.at(n)->Integral(XbinFirst,XbinEnd,YbinFirst,YbinCut-1);
        
        return (double)nU/(double)nD;
    }
    double Fdu(unsigned int n, double x_cut, double y_cut)const{
        double ret = this->Fud(n,x_cut,y_cut);
        if(ret != 0)
            return (double)1/(double)ret;
        return -10000;
    }
    
//       .
//      .|.
//       |      |
//       |  A   |  B
//  y-cut|------|-------
//       |  C   |  D
//       |------|------->
//             x-cut
    
    double Flr(unsigned int n, double x_cut, double y_cut)const{
        int XbinCut = Histograms2D.at(n)->GetXaxis()->FindBin(x_cut);
        int XbinEnd= Histograms2D.at(n)->GetXaxis()->GetLast();
        int XbinFirst= Histograms2D.at(n)->GetXaxis()->GetLast();
        int YbinEnd = Histograms2D.at(n)->GetYaxis()->GetLast();
        int YbinFirst= Histograms2D.at(n)->GetXaxis()->GetFirst();
                
        double nL = Histograms2D.at(n)->Integral(XbinFirst,XbinCut-1,YbinFirst,YbinEnd);
        double nR = Histograms2D.at(n)->Integral(XbinCut,XbinEnd,YbinFirst,YbinEnd);
        
        return (double)nL/(double)nR;
    }
    double Frl(unsigned int n, double x_cut, double y_cut)const{
        double ret = this->Flr(n,x_cut,y_cut);
        if(ret != 0)
            return (double)1/(double)ret;
        return -10000;
    }
    

    
    std::vector<TH2Ext<SemiLepTopQuark>* > Histograms2D;
    std::vector<TH1Ext<SemiLepTopQuark>* > Histograms1D;
    bool doEfficiency;
};

#endif	/* BASEWPOLARIZATIONHANDLER_H */

