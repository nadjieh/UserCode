/* 
 * File:   CosThetaWeighter.h
 * Author: nadjieh
 *
 * Created on March 3, 2012, 2:45 PM
 */

#ifndef COSTHETAWEIGHTER_H
#define	COSTHETAWEIGHTER_H
#include "TF1.h"
#include "TH1.h"
#include "TMath.h"
#include "TRandom1.h"
#include <string>
#include <iostream>
using namespace std;
Double_t Weights(double *x, double *par)
 /*--------------------------------------------------------------------*/
{
    //par[0]: F01
    //par[1]: F-1
    //par[2]: F02
    //par[3]: F-2
    //F+ = 1- F-i - F0i
    Double_t firstTerm1 = (1-par[0]-par[1])*(1+x[0])*(1+x[0]);
    Double_t secondTerm1 = par[1]*(1-x[0])*(1-x[0]);
    Double_t thirdTerm1 = par[0]*(1-x[0]*x[0]);
    Double_t First = (3.0/8.0)*(firstTerm1+secondTerm1)+(3.0/4.0)*thirdTerm1;

    Double_t firstTerm2 = (1-par[2]-par[3])*(1+x[0])*(1+x[0]);
    Double_t secondTerm2 = par[3]*(1-x[0])*(1-x[0]);
    Double_t thirdTerm2 = par[2]*(1-x[0]*x[0]);
    Double_t Second = (3.0/8.0)*(firstTerm2+secondTerm2)+(3.0/4.0)*thirdTerm2;

    return ((Double_t)Second/(Double_t)First);
};
Double_t cosThetaHistMaker(double *x, double *par)
 /*--------------------------------------------------------------------*/
{
    //par[0]: F01
    //par[1]: F-1
    //F+ = 1- F-i - F0i
    Double_t firstTerm1 = (1-par[0]-par[1])*(1+x[0])*(1+x[0]);
    Double_t secondTerm1 = par[1]*(1-x[0])*(1-x[0]);
    Double_t thirdTerm1 = par[0]*(1-x[0]*x[0]);
    Double_t First = (3.0/8.0)*(firstTerm1+secondTerm1)+(3.0/4.0)*thirdTerm1;
    return First;
};
class CosThetaWeighter{
public:
    CosThetaWeighter(double f0, double fminus, double deviation = 0.25, std::string name = "weighter"){
        pars[0] = f0;
        pars[1] = fminus;
        pars[2] = f0-deviation;
        pars[3] = fminus+deviation;
        weights = new TF1("weights",Weights,-1,1,4);
        weights->SetParameters(pars);     
        histWeights = histWeightMaker(pars[2],pars[3],string(name+"_num"));
        TH1D * Den = histWeightMaker(pars[0],pars[1],string(name+"_den"));
        histWeights->Divide(Den);
        delete Den;
    };
    CosThetaWeighter(double f0SM, double fminusSM, double f0, double fminus, std::string name = "weighter"){
        pars[0] = f0SM;
        pars[1] = fminusSM;
        pars[2] = f0;
        pars[3] = fminus;
        weights = new TF1("weights",Weights,-1,1,4);
        weights->SetParameters(pars);     
        histWeights = histWeightMaker(pars[2],pars[3],string(name+"_num"));
        TH1D * Den = histWeightMaker(pars[0],pars[1],string(name+"_den"));
        histWeights->Divide(Den);
        delete Den;
    };
    ~CosThetaWeighter(){delete weights; delete histWeights;};
    double getWeight(double cosThetaStar){return weights->Eval(cosThetaStar);};
    double getHistWeight(double cosThetaStar){
        if(histWeights == NULL){
            std::cout<<"Weight hist is not initialized"<<std::endl;
            return 0.0;
        }
        return (histWeights->GetBinContent(histWeights->FindBin(cosThetaStar)));
    };
    TH1D * getWeightHistogram()const{return histWeights;};
private:
    TH1D * histWeights;
    TF1 * weights;
    Double_t pars[4];
    TH1D * histWeightMaker(Double_t f0, Double_t fminus, string name){
        TF1 * f = new TF1("f",cosThetaHistMaker,-1,1,2);
        f->SetParameter(0,f0);
        f->SetParameter(1,fminus);
        TH1D * res = new TH1D(name.c_str(),name.c_str(), 10, -1, 1);
        res->FillRandom("f",10000);
        delete f;
        return res;
    }
};

#endif	/* COSTHETAWEIGHTER_H */

