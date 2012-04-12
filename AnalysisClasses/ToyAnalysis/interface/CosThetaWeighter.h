/* 
 * File:   CosThetaWeighter.h
 * Author: nadjieh
 *
 * Created on March 3, 2012, 2:45 PM
 */

#ifndef COSTHETAWEIGHTER_H
#define	COSTHETAWEIGHTER_H
#include "TF1.h"
#include "TMath.h"

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
class CosThetaWeighter{
public:
    CosThetaWeighter(double f0, double fminus){
        pars[0] = f0;
        pars[1] = fminus;
        pars[2] = f0-0.25;
        pars[3] = fminus+0.25;
        weights = new TF1("weights",Weights,-1,1,4);
        weights->SetParameters(pars);        
    };
    ~CosThetaWeighter(){delete weights;};
    double getWeight(double cosThetaStar){return weights->Eval(cosThetaStar);};
private:
    
    TF1 * weights;
    Double_t pars[4];
};

#endif	/* COSTHETAWEIGHTER_H */


