/* 
 * File:   METResolutionSingleTop.h
 * Author: nadjieh
 *
 * Created on March 1, 2012, 12:55 PM
 */

#ifndef METRESOLUTIONSINGLETOP_H
#define	METRESOLUTIONSINGLETOP_H

#include "TProfile.h"
#include "TLorentzVector.h"
#include "TH1D.h"
#include "TFile.h"
#include "../interface/GenSingleTopMaker.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootNPGenEvent.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootMCParticle.h"
#include <vector>

using namespace TopTree;
using namespace std;
class METResolutionSingleTop:public GenSingleTopMaker{
public:
    METResolutionSingleTop(TRootNPGenEvent * genEvents, TLorentzVector * met):GenSingleTopMaker(genEvents){
        if(GenSingleTopMaker::isSemiMuSingleTop){
//            double res = (double)fabs(met->Pt() - GenSingleTopMaker::genSingleTop.neutrino().Pt())
            double res = (double)(met->Pt() - GenSingleTopMaker::genSingleTop.neutrino().Pt())
            /(double)(GenSingleTopMaker::genSingleTop.neutrino().Pt());
            met_res = make_pair(met->Pt(),res);
        }
    };
    ~METResolutionSingleTop(){};
    std::pair<double,double> getMETRes()const{return met_res;};
private:
    std::pair<double, double> met_res;
};
class METResolutionHistograms{
public:
    METResolutionHistograms(){
        histos.push_back(new TH1D("h1","0<pt<30",50,-5,5));
        histos.push_back(new TH1D("h2","30<pt<40",50,-5,5));
        histos.push_back(new TH1D("h3","40<pt<50",50,-5,5));
        histos.push_back(new TH1D("h4","50<pt<60",50,-5,5));
        histos.push_back(new TH1D("h5","60<pt<80",50,-5,5));
        histos.push_back(new TH1D("h6","80<pt<100",50,-5,5));
        histos.push_back(new TH1D("h7","pt>100",50,-5,5));
    };
    ~METResolutionHistograms(){ 
        for(unsigned int i =0; i<histos.size();i++){
            delete histos.at(i);
            histos.clear();
        }
    };
    void Fill(std::pair<double,double> met_res){
        if(met_res.first < 30){
            histos.at(0)->Fill(met_res.second);
        }else if(met_res.first >= 30 && met_res.first < 40){
            histos.at(1)->Fill(met_res.second);            
        }else if(met_res.first >= 40 && met_res.first < 50){
            histos.at(2)->Fill(met_res.second);            
        }else if(met_res.first >= 50 && met_res.first < 60){
            histos.at(3)->Fill(met_res.second);            
        }else if(met_res.first >= 60 && met_res.first < 80){
            histos.at(4)->Fill(met_res.second);            
        }else if(met_res.first >= 80 && met_res.first < 100){
            histos.at(5)->Fill(met_res.second);            
        }else {
            histos.at(6)->Fill(met_res.second);
        }
    }
    void Write(TFile * f){
        if(f != NULL)
            f->cd();
        else{
            cout<<"NULL file ..."<<endl;
            return;
        }
        for(unsigned int i = 0; i<histos.size();i++){
            histos.at(i)->Write();
        }
        f->cd();        
    }
private:
    std::vector<TH1D*> histos;
};
#endif	/* METRESOLUTIONSINGLETOP_H */

