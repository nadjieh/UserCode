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
#include "TH2.h"
#include "TMath.h"
#include "TCanvas.h"
#include "TRandom1.h"
#include "TVirtualFitter.h"
#include "TROOT.h"
#include <string>
#include <iostream>
#include <sstream>

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
class WeightFunctionCreator{
public:
    WeightFunctionCreator(double std_f0 = 6.64263e-01, double std_fneg = 3.03734e-01):
    f0Std(std_f0),f_Std(std_fneg){
        func = new TF1("WeightFunctionCreator", CosTheta, -1,1,2);
       func->SetParameters(f0Std,f_Std);
    }
    ~WeightFunctionCreator(){
        delete func;
    }
    Double_t operator()(double * x, double * par ){
        func->SetParameters(f0Std,f_Std);
//	cout<<"SM: "<< func->GetParameter(0)<<"  "<<func->GetParameter(1)<<endl;
        double stdVal = func->Eval(x[0]);
        func->SetParameters(par);
//	cout<<func->GetParameter(0)<<"  "<<func->GetParameter(1)<<endl;
        double nonstdVal = func->Eval(x[0]);
        return ((double)nonstdVal/(double)stdVal);
    }
    static std::pair<TF1,WeightFunctionCreator*> getWeightFunction(string name,double std_f0 = 6.64263e-01, double std_fneg = 3.03734e-01){
        WeightFunctionCreator * functor = new WeightFunctionCreator(6.64263e-01, 3.03734e-01);
        TF1 ret( name.c_str() , functor , -1.0 , 1.0 , 2);

        ret.SetParName(0 , "F0" );
        ret.SetParName(1 , "FNeg" );

//        ret.SetParLimits(0 , 0.0 , 1.0);
//        ret.SetParLimits(1 , 0.0 , 1.0);
            
        ret.SetParameters(std_f0, std_fneg );
            
        return make_pair(ret,functor);
    }
private:
    TF1 * func;
    double f0Std;
    double f_Std;
        
    
};
class LikelihoodFunction{
public:
    LikelihoodFunction(string name , TH1* nonWtbSum , TH1* hData , TH1* WtbSum, double f0gen = 6.64263e-01, double fneggen = 3.03734e-01)
    :Name(name), bkg(nonWtbSum), data(hData), signal(WtbSum),
     WeightFunc(WeightFunctionCreator::getWeightFunction("WeightFunc" + name, f0gen, fneggen)){
        data->Sumw2(); //cout<<"---"<<endl;
        bkg->Sumw2();//cout<<"----"<<endl;
        signal->Sumw2();//cout<<"-----"<<endl;
        signal2D = 0;
        signals2D.clear();
    }
    LikelihoodFunction(string name , TH1* nonWtbSum , TH1* hData , TH2* WtbSum, std::string mksure = "mksure",
                       double f0gen = 6.64263e-01, double fneggen = 3.03734e-01):Name(name), bkg(nonWtbSum), data(hData),
                       signal2D(WtbSum),WeightFunc(WeightFunctionCreator::getWeightFunction("WeightFunc" + name, f0gen, fneggen)){
        data->Sumw2(); //cout<<"---"<<endl;
        bkg->Sumw2();//cout<<"----"<<endl;
        signal2D->Sumw2();//cout<<"-----"<<endl;
        signal = 0;
        signals2D.clear();
    }
    LikelihoodFunction(string name , TH1* nonWtbSum , TH1* hData , std::vector<TH2*> WtbSum, double f0gen = 6.64263e-01,
    double fneggen = 3.03734e-01):Name(name), bkg(nonWtbSum), data(hData),
    WeightFunc(WeightFunctionCreator::getWeightFunction("WeightFunc" + name, f0gen, fneggen)){
        data->Sumw2(); //cout<<"---"<<endl;
        bkg->Sumw2();//cout<<"----"<<endl;
        for(unsigned int p = 0; p < WtbSum.size(); p++){
//            cout<<"==== "<<WtbSum.at(p)->GetEntries()<<endl;
            WtbSum.at(p)->Sumw2();
            signals2D.push_back(WtbSum.at(p));
        }
        signal = 0;
        signal2D = 0;
    }

    ~LikelihoodFunction(){}
    virtual Double_t operator()(double * x, double * par = 0){
//        x[0] = f_0
//        x[1] = f_Neg
//        x[2] = rec_gen factor
//        no parameter is needed

        double LL = 0.0;
        int nbins = data->GetXaxis()->GetNbins();
        for(int i = 0; i<nbins; i++){
            std::pair<double, double>  numbers = this->getNdataNmc(i+1, x[0],x[1],x[2]);
            LL += this->logLikelihood(numbers.first, numbers.second);
        }
        return LL;
    }
    static std::pair<TF3,LikelihoodFunction*> getLLFunction(string name , TH1* nonWtbSum , TH1* hData , 
    TH1* WtbSum, bool is2D = false){
        LikelihoodFunction * functor = 0;
        if(!is2D)
            functor = new LikelihoodFunction(name , nonWtbSum , hData , WtbSum);
        else
            functor = new LikelihoodFunction(name , nonWtbSum , hData , (TH2*)WtbSum, "");
                
        TF3 ret(name.c_str(), functor, 0.0 , 1.0 , 0.0 , 0.1 , 0.0 , 2.0 , 0,"LikelihoodFunction" );
        ret.SetRange( 0.0 , 0.0 , 0.000001 , 1.0 , 1.0 , 2.0);
        return make_pair(ret, functor);
    }
    static std::pair<TF3,LikelihoodFunction*> getLLFunctionGeneralized(string name , TH1* nonWtbSum , TH1* hData ,
    std::vector<TH2*> WtbSum){
        LikelihoodFunction * functor = 0;
        functor = new LikelihoodFunction(name , nonWtbSum , hData , WtbSum);
        
        TF3 ret(name.c_str(), functor, 0.0 , 1.0 , 0.0 , 0.1 , 0.0 , 2.0 , 0,"LikelihoodFunctionGeneralized" );
        ret.SetRange( 0.0 , 0.0 , 0.000001 , 1.0 , 1.0 , 2.0);
        return make_pair(ret, functor);
    }
    
protected:
    string Name;
    TH1* bkg;
    TH1* data;
    TH1* signal;
    TH2* signal2D;
    std::pair<TF1, WeightFunctionCreator*> WeightFunc;
    std::vector<TH2*> signals2D;

    std::pair<double, double> getNdataNmc(int bin, double f0 = 6.64263e-01, double f_ = 3.03734e-01, double rec_gen = 1.){
        int nbins = data->GetXaxis()->GetNbins();
        if(bin > nbins || nbins < 0){
            cout<<"No value for this cos(theta) bin"<<endl;
            return make_pair(-100,-100);
        }
        double nData = data->GetBinContent(bin);
        double costheta = data->GetBinCenter(bin);
        double nSignal = -100.;
        if(signal != 0 && signal2D == 0 && signals2D.size() == 0){
            double weight = getWeight(costheta,f0,f_)*rec_gen;
            nSignal = weight*signal->GetBinContent(bin);
        }else if(signal == 0 && signal2D != 0 && signals2D.size() == 0){
            nSignal = 0;
            WeightFunc.first.SetParameters(f0, f_);
            gROOT->cd();
            TH1* hithrecbin = this->signal2D->ProjectionX("_pX" , bin , bin , "o");
            hithrecbin->Multiply( &(WeightFunc.first) , rec_gen);
            nSignal = hithrecbin->Integral();
            if(hithrecbin != NULL)
                delete hithrecbin;
        }else if(signal == 0 && signal2D == 0 && signals2D.size() != 0){
//            cout<<"In general: "<<endl;
            nSignal = 0;
            WeightFunc.first.SetParameters(f0, f_);
            gROOT->cd();
            TH1* hithrecbin = 0;
            stringstream s;
            for(unsigned int p = 0; p < signals2D.size(); p++){
                s.str("");
                s<<p<<"_pX";
                hithrecbin = signals2D.at(p)->ProjectionX(s.str().c_str() , bin , bin , "o");
//                cout<<"In general: "<<hithrecbin->GetName()<<endl;
                hithrecbin->Multiply( &(WeightFunc.first) , rec_gen);
                nSignal += hithrecbin->Integral();
            }
            if(hithrecbin != NULL)
                delete hithrecbin;
        }
        if(nSignal == -100.){cout<<"************** FATAL ERROR: nSignal is not set ...."<<endl;}
        double nMC = bkg->GetBinContent(bin) + nSignal;
//        cout<<"****** "<<nData<<"\t"<<nMC<<endl;
        return make_pair(nData,nMC);        
    }
    
    double getWeight(double costheta,double f0 = 6.64263e-01, double f_= 3.03734e-01){
        WeightFunc.first.SetParameters(f0, f_);
        return  WeightFunc.first.Eval(costheta);
    }
    
    double logLikelihood(double nData, double nMC){
        double x_mean = nMC;
        double x = nData;
        if (x_mean <= 0.0)
            return 0.0;
        if (x <= 0.0)
            return 0.0;
        double log_pow_1 = x*log(x_mean);
        double log_exp_1 = -x_mean;
        double log_factoral =  x*log(x) - x + ( log(x*(1+4*x*(1+2*x))) / 6 ) + log(M_PI)/2 ;

        return log_factoral - log_exp_1 - log_pow_1;
    }
    
};

class ChiSquaredFunction{
public:
    ChiSquaredFunction(string name , TH1* nonWtbSum , TH1* hData , TH1* WtbSum, double f0gen = 6.64263e-01, double fneggen = 3.03734e-01)
    :Name(name), bkg(nonWtbSum), data(hData), signal(WtbSum), 
     WeightFunc(WeightFunctionCreator::getWeightFunction("WeightFunc" + name, f0gen, fneggen)){ 
        
        data->Sumw2();
        bkg->Sumw2();
        signal->Sumw2();
        signal2D = 0;
    }
    ChiSquaredFunction(string name , TH1* nonWtbSum , TH1* hData , TH2* WtbSum, std::string mksure = "",double f0gen = 6.64263e-01, 
    double fneggen = 3.03734e-01):Name(name), bkg(nonWtbSum), data(hData), signal2D(WtbSum), 
     WeightFunc(WeightFunctionCreator::getWeightFunction("WeightFunc" + name, f0gen, fneggen)){ 
        
        data->Sumw2();
        bkg->Sumw2();
        signal2D->Sumw2();
        signal = 0;
    }
    ~ChiSquaredFunction(){}
    Double_t operator()(double * x, double * par = 0){
//        x[0] = f_0
//        x[1] = f_Neg
//        x[2] = rec_gen factor
//        no parameter is needed
        double chi2 = 0.0;
        int nbins = data->GetXaxis()->GetNbins();
        for(int i = 0; i<nbins; i++){
            std::pair<double,pair<double,double> > numbers = this->getNdataNmc(i+1, x[0],x[1],x[2]);
            double Data[2]={numbers.first, sqrt(numbers.first)};
            double MC[2]={numbers.second.first, numbers.second.second};
            chi2 += this->chiSquared(Data,MC);
        }
        return chi2;
    }
    static std::pair<TF3,ChiSquaredFunction *> getChiSquaredFunction(string name , TH1* nonWtbSum , TH1* hData , TH1* WtbSum){
        ChiSquaredFunction * functor = new ChiSquaredFunction(name , nonWtbSum , hData , WtbSum);
        TF3 ret(name.c_str(), functor, 0.0 , 1.0 , 0.0 , 0.1 , 0.0 , 2.0 , 0,"ChiSquaredFunction" );
        ret.SetRange( 0.0 , 0.0 , 0.000001 , 1.0 , 1.0 , 2.0);
        return make_pair(ret,functor);
    }
private:
    string Name;
    TH1* bkg;
    TH1* data;
    TH1* signal;
    TH2* signal2D;
    std::pair<TF1, WeightFunctionCreator*> WeightFunc;

    std::pair<double, std::pair<double,double> > getNdataNmc(int bin, double f0 = 6.64263e-01, double f_ = 3.03734e-01, 
    double rec_gen = 1.){
        int nbins = data->GetXaxis()->GetNbins();
        if(bin > nbins || nbins < 0){
            cout<<"No value for this cos(theta) bin"<<endl;
            return make_pair(-100,make_pair(-100,-100));
        }
        double nData = data->GetBinContent(bin);
        double costheta = data->GetBinCenter(bin);
        double nSignal = -100.;
        double sigErr = -100.;
        if(signal2D == 0 && signal != 0){
            double weight = getWeight(costheta,f0,f_)*rec_gen;
            nSignal = weight*signal->GetBinContent(bin);
            sigErr = weight*signal->GetBinError(bin);
        }else if(signal2D != 0 && signal == 0){
            WeightFunc.first.SetParameters(f0,f_);
            gROOT->cd();
            TH1* hithrecbin = this->signal2D->ProjectionX("_pX" , bin , bin , "o");
//            cout<<"It was here!!!!"<<endl;
            hithrecbin->Sumw2();
            hithrecbin->Multiply( &(WeightFunc.first) , rec_gen);
            nSignal = hithrecbin->Integral();
            sigErr = 0;
            for(int s = 0; s < hithrecbin->GetXaxis()->GetNbins(); s++){
                sigErr+=pow(hithrecbin->GetBinError(s+1),2);
            }
            sigErr=sqrt(sigErr)*rec_gen;
        }
        if(nSignal == -100. || sigErr == -100.)
            cout<<"************** FATAL ERROR: nSignal or sigErr is not set ...."<<endl;
        double nMC = bkg->GetBinContent(bin) + nSignal;
        double errMC = sqrt((sigErr*sigErr) + (bkg->GetBinError(bin)*bkg->GetBinError(bin)));
        return make_pair(nData,make_pair(nMC,errMC));        
    }
    
    double getWeight(double costheta,double f0 = 6.64263e-01, double f_= 3.03734e-01){
        WeightFunc.first.SetParameters(f0, f_);
        return  WeightFunc.first.Eval(costheta);
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

void GetMinimum(TF3 F,double * x, double * xerr,double & corr12 ,bool CalcError = true){
    //    based on the documentation of TF3::GetMinimumXYZ from
    //    http://root.cern.ch/root/html532/src/TF3.cxx.html#QUjxjE
//    F.Print("all");
    F.GetMinimumXYZ(x[0] , x[1] , x[2]);
//    cout<<x[0]<<"\t"<<x[1]<<"\t"<<x[2]<<endl;
    if(!CalcError)
        return;
    //    go to minuit for the final minimization
    
    TVirtualFitter * minuit = TVirtualFitter::Fitter(&F,3);
    minuit->Clear();
    minuit->SetFitMethod("F3Minimizer");
    double arg_list[10] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
    int nNargs = 1;
    minuit->ExecuteCommand("SET PRINT" , arg_list, nNargs);
    double xl = 0.0;    double xu = 0.0;
    double yl = 0.0;    double yu = 0.0;
    double zl = 0.0;    double zu = 0.0;
    minuit->SetParameter(0, "x", x[0], 0.1, xl , xu );
    minuit->SetParameter(1, "y", x[1], 0.1, yl , yu );
    minuit->SetParameter(2, "z", x[2], 0.1, zl , zu );
//    minuit->SetParameter(2, "z", 1, 0.1, zl , zu );
//    minuit->FixParameter(2      );
    for(int i = 0; i<10; i++)
        arg_list[i] = 1.;
    Int_t fitResult = minuit->ExecuteCommand("MIGRAD", arg_list, 0);
    if (fitResult != 0){
        cout<< "Abnormal termination of minimization"<<endl;
        x[0] = -1.0;
        x[1] = -1.0;
        x[2] = -1.0;
        delete minuit;
        return;
    }

    x[0] = minuit->GetParameter(0);
    x[1] = minuit->GetParameter(1);
    x[2] = minuit->GetParameter(2);

    double globcc = 0.0;
    minuit->GetErrors( 0 , xu , xl , xerr[0] , globcc );
    minuit->GetErrors( 1 , yu , yl , xerr[1] , globcc );
    minuit->GetErrors( 2 , zu , zl , xerr[2] , globcc );
    corr12 = minuit->GetCovarianceMatrixElement(0,1);
    delete minuit;
}

#endif	/* LikelihoodFunction_H */

