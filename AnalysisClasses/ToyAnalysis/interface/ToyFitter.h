/* 
 * File:   LikelihoodFunction.h
 * Author: nadjieh
 *
 * Created on May 1, 2012, 7:06 PM
 */

#ifndef LikelihoodFunction_H
#define	LikelihoodFunction_H
#include "TF1.h"
#include "TF3.h"
#include "TH1.h"
#include "TMath.h"
#include "TCanvas.h"
#include "TRandom1.h"
#include <string>
#include <iostream>
using namespace std;


Double_t CosTheta(double *x, double *par)
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

class LikelihoodFunction{
public:
    LikelihoodFunction(string name , TH1D nonWtbSum , TH1D hData , TH1D WtbSum)
    :Name(name), bkg(nonWtbSum), data(hData), signal(WtbSum){
        data.Sumw2();
        bkg.Sumw2();
        signal.Sumw2();
        smCosTheta = new TF1(string("smCosTheta_"+Name).c_str(),CosTheta,-1.,1.,2);
        smCosTheta->SetParName(0, "f_{0}");
        smCosTheta->SetParName(1, "f_{neg}");
        smCosTheta->SetParameters(6.64263e-01,3.03734e-01);
        smCosTheta->SetParLimits(0,0.,1.);
        smCosTheta->SetParLimits(1,0.,1.);
    }
    ~LikelihoodFunction(){ delete smCosTheta;}
    Double_t operator()(double * x, double * par = 0){
        //        x[0] = f_0
//        x[1] = f_Neg
//        x[2] = rec_gen factor
//        no parameter is needed

        double LL = 0.0;
        int nbins = data.GetXaxis()->GetNbins();
        for(int i = 0; i<nbins; i++){
            std::pair<double, double>  numbers = this->getNdataNmc(i+1, x[0],x[1],x[2]);
            LL += this->logLikelihood(numbers.first, numbers.second);
        }
        return LL;
    }
    static TF3 getLLFunction(string name , TH1D nonWtbSum , TH1D hData , TH1D WtbSum){
        LikelihoodFunction * functor = new LikelihoodFunction(name , nonWtbSum , hData , WtbSum);
        TF3 ret(name.c_str(), functor, 0.0 , 1.0 , 0.0 , 0.1 , 0.0 , 2.0 , 0,"LikelihoodFunction" );
        ret.SetRange( 0.0 , 0.0 , 0.000001 , 1.0 , 1.0 , 2.0);
        return ret;
    }
private:
    string Name;
    TH1D bkg;
    TH1D data;
    TH1D signal;
    TF1 * smCosTheta;

    std::pair<double, double> getNdataNmc(int bin, double f0 = 6.64263e-01, double f_ = 3.03734e-01, double rec_gen = 1.){
        int nbins = data.GetXaxis()->GetNbins();
        if(bin > nbins || nbins < 0){
            cout<<"No value for this cos(theta) bin"<<endl;
            return make_pair(-100,-100);
        }
        double nData = data.GetBinContent(bin);
        double costheta = data.GetBinCenter(bin);
        double weight = getWeight(costheta,f0,f_)*rec_gen;
        double nSignal = weight*signal.GetBinContent(bin);
        double nMC = bkg.GetBinContent(bin) + nSignal;
        return make_pair(nData,nMC);        
    }
    
    double getWeight(double costheta,double f0 = 6.64263e-01, double f_= 3.03734e-01){
        this->smCosTheta->SetParameter("f_{0}",6.64263e-01);
        this->smCosTheta->SetParameter("f_{neg}",3.03734e-01);
        double SM = smCosTheta->Eval(costheta);
        this->smCosTheta->SetParameter("f_{0}",f0);
        this->smCosTheta->SetParameter("f_{neg}",f_);
        double nonSM = smCosTheta->Eval(costheta);
        return (double)nonSM/(double)SM;
    }
    
    double logLikelihood(double nData, double nMC){
        double x_mean = nMC;
        double x = nData;
        if (x_mean <= 0.0)
            return 0.0;
        double log_pow_1 = x*log(x_mean);
        double log_exp_1 = -x_mean;
        double log_factoral =  x*log(x) - x + ( log(x*(1+4*x*(1+2*x))) / 6 ) + log(M_PI)/2 ;

        return log_factoral - log_exp_1 - log_pow_1;
    }
    
};

class ChiSquaredFunction{
public:
    ChiSquaredFunction(string name , TH1D nonWtbSum , TH1D hData , TH1D WtbSum)
    :Name(name), bkg(nonWtbSum), data(hData), signal(WtbSum){
        data.Sumw2();
        bkg.Sumw2();
        signal.Sumw2();
        smMC = *((TH1D*)signal.Clone("smMC"));
        smMC.Sumw2();
        smMC.Add(&bkg);
        smCosTheta = new TF1(string("smCosTheta_"+Name).c_str(),CosTheta,-1.,1.,2);
        smCosTheta->SetParName(0, "f_{0}");
        smCosTheta->SetParName(1, "f_{neg}");
        smCosTheta->SetParameters(6.64263e-01,3.03734e-01);
        smCosTheta->SetParLimits(0,0.,1.);
        smCosTheta->SetParLimits(1,0.,1.);
    }
    ~ChiSquaredFunction(){ delete smCosTheta;}
    Double_t operator()(double * x, double * par = 0){
//        x[0] = f_0
//        x[1] = f_Neg
//        x[2] = rec_gen factor
//        no parameter is needed
        double chi2 = 0.0;
        int nbins = data.GetXaxis()->GetNbins();
        for(int i = 0; i<nbins; i++){
            std::pair<double,pair<double,double> > numbers = this->getNdataNmc(i+1, x[0],x[1],x[2]);
            double Data[2]={numbers.first, sqrt(numbers.first)};
            double MC[2]={numbers.second.first, numbers.second.second};
            chi2 += this->chiSquared(Data,MC);
        }
        return chi2;
    }
    static std::pair<TF3,ChiSquaredFunction *> getChiSquaredFunction(string name , TH1D nonWtbSum , TH1D hData , TH1D WtbSum){
        ChiSquaredFunction * functor = new ChiSquaredFunction(name , nonWtbSum , hData , WtbSum);
        TF3 ret(name.c_str(), functor, 0.0 , 1.0 , 0.0 , 0.1 , 0.0 , 2.0 , 0,"ChiSquaredFunction" );
//        TF3 ret(name.c_str(), "(x*x)+(y*y)+(z*z)", 0.0 , 1.0 , 0.0 , 0.1 , 0.0 , 2.0 );
        ret.SetRange( 0.0 , 0.0 , 0.000001 , 1.0 , 1.0 , 2.0);
        return make_pair(ret,functor);
    }
private:
    string Name;
    TH1D bkg;
    TH1D data;
    TH1D signal;
    TH1D smMC;
    TF1 * smCosTheta;

    std::pair<double, std::pair<double,double> > getNdataNmc(int bin, double f0 = 6.64263e-01, double f_ = 3.03734e-01, double rec_gen = 1.){
        int nbins = data.GetXaxis()->GetNbins();
        if(bin > nbins || nbins < 0){
            cout<<"No value for this cos(theta) bin"<<endl;
            return make_pair(-100,make_pair(-100,-100));
        }
        double nData = data.GetBinContent(bin);
        double costheta = data.GetBinCenter(bin);
        double weight = getWeight(costheta,f0,f_)*rec_gen;
        double nSignal = weight*signal.GetBinContent(bin);
        double sigErr = weight*signal.GetBinError(bin);
        double nMC = bkg.GetBinContent(bin) + nSignal;
        double errMC = sqrt((sigErr*sigErr) + (bkg.GetBinError(bin)*bkg.GetBinError(bin)));
        return make_pair(nData,make_pair(nMC,errMC));        
    }
    
    double getWeight(double costheta,double f0 = 6.64263e-01, double f_= 3.03734e-01){
        this->smCosTheta->SetParameter("f_{0}",6.64263e-01);
        this->smCosTheta->SetParameter("f_{neg}",3.03734e-01);
        double SM = smCosTheta->Eval(costheta);
        this->smCosTheta->SetParameter("f_{0}",f0);
        this->smCosTheta->SetParameter("f_{neg}",f_);
        double nonSM = smCosTheta->Eval(costheta);
        return (double)nonSM/(double)SM;
    }
    
   
    double chiSquared(double* Data, double* MC){ //[0]: value , [1]: uncertainty
        double x_mean = MC[0];
        double x = Data[0];
        if (x + x_mean < 0)
            return 0.0;
        double sigma = sqrt( (MC[1]*MC[1]) + (Data[1]*Data[1]) );

        return (x-x_mean)*(x-x_mean) / (2*sigma*sigma);
    }    
};


#endif	/* LikelihoodFunction_H */
