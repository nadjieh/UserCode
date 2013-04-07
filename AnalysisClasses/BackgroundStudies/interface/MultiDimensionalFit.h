/* 
 * File:   MultiDimensionalFit.h
 * Author: nadjieh
 *
 * Created on June 9, 2012, 11:12 AM
 */

#ifndef MULTIDIMENSIONALFIT_H
#define	MULTIDIMENSIONALFIT_H
#include "TH1.h"
#include "TH3.h"
#include "TH2.h"
#include <ctime>
#include "TCanvas.h"
#include "TGraph.h"
#include "TRandom.h"
#include <iostream>
#include "/opt/root/math/mathmore/inc/Math/GSLMinimizer.h"
#include "/opt/root/math/mathmore/inc/Math/GSLSimAnMinimizer.h"
#include "/opt/root/math/minuit2/inc/Minuit2/Minuit2Minimizer.h"
#include "/opt/root/math/mathcore/inc/Math/Functor.h"
#include "../../ToyAnalysis/interface/ToyFitter.h"

using namespace std;

class MultiDimensionalFitLiklihood : public LikelihoodFunction {
public:

    MultiDimensionalFitLiklihood(string name, TH1* nonWtbNoWSum, TH1* hData, TH1* WtbSum,
            TH1* Wtemplate, TH1* tt = 0) : LikelihoodFunction(name, nonWtbNoWSum, hData, WtbSum) {
        wtemplate = Wtemplate;
        toptemplate = tt;
    }

    MultiDimensionalFitLiklihood(string name, TH1* nonWtbNoWSum, TH1* hData, TH2* WtbSum, TH1* Wtemplate,
            TH1* tt = 0, std::string mksure = "mksure") : LikelihoodFunction(name, nonWtbNoWSum, hData, WtbSum, mksure) {
        wtemplate = Wtemplate;
        toptemplate = tt;
    }

    MultiDimensionalFitLiklihood(string name, TH1* nonWtbNoWSum, TH1* hData, std::vector<TH2*> WtbSum,
            TH1* Wtemplate, TH1* tt = 0) : LikelihoodFunction(name, nonWtbNoWSum, hData, WtbSum) {
        wtemplate = Wtemplate;
        toptemplate = tt;
    }

    MultiDimensionalFitLiklihood(string name, TH1* nonWtbNoWSum, TH1* hData, std::vector<TH2*> restOfSignal,
            std::vector<TH3*> DiW, TH1* Wtemplate, TH1* tt = 0) : LikelihoodFunction(name, nonWtbNoWSum, hData,
    restOfSignal, DiW) {
        wtemplate = Wtemplate;
        toptemplate = tt;
    }

    ~MultiDimensionalFitLiklihood() {
    }

    virtual double operator()(const double * x) {
        //        x[0] = f_0
        //        x[1] = f_Neg
        //        x[2] = rec_gen factor
        //        x[3] = nWjets
        //        x[4] = nTt

        //        no parameter is needed
        //        cout<<"operator is called"<<endl;
        double LL = 0.0;
        int nbins = data->GetXaxis()->GetNbins();
        for (int i = 0; i < nbins; i++) {
            //            std::pair<double, double>  numbers = this->getNdataNmcMD(i+1, x[0],x[1],x[2],x[3],x[4]);
            std::pair<double, double> numbers = this->getNdataNmcMD(i + 1, x[0], x[1], x[2], x[3]);
            //            cout<<"in LL: "<<numbers.first << "\t"<<numbers.second<<endl;
            LL += LikelihoodFunction::logLikelihood(numbers.first, numbers.second);
        }
        //        cout<<"LL: "<<LL<<endl;
        return LL;
    }

    static std::pair<ROOT::Math::Functor, MultiDimensionalFitLiklihood*> getMDLLFunction(string name,
            TH1* nonWtbSum, TH1* hData, TH1* WtbSum, TH1* Wtemplate, bool is2D = false, TH1* tt = 0) {
        MultiDimensionalFitLiklihood * functor = 0;
        if (!is2D) {
            functor = new MultiDimensionalFitLiklihood(name, nonWtbSum,
                    hData, WtbSum, Wtemplate, tt);
        } else {
            functor = new MultiDimensionalFitLiklihood(name, nonWtbSum,
                    hData, (TH2*) WtbSum, Wtemplate, tt, "");
        }
        ROOT::Math::Functor ret(*functor, 4);
        return make_pair(ret, functor);
    }

    static std::pair<ROOT::Math::Functor, MultiDimensionalFitLiklihood*> getMDLLFunctionGeneralized(
            string name, TH1* nonWtbSum, TH1* hData, std::vector<TH2*> WtbSum, TH1* Wtemplate, TH1* tt = 0) {
        MultiDimensionalFitLiklihood * functor = new MultiDimensionalFitLiklihood(name, nonWtbSum,
                hData, WtbSum, Wtemplate, tt);
        ROOT::Math::Functor ret(*functor, 4);
        return make_pair(ret, functor);
    }

    static std::pair<ROOT::Math::Functor, MultiDimensionalFitLiklihood*> getMDLLFunctionForBias(
            string name, TH1* nonWtbSum, TH1* hData, std::vector<TH2*> WtbSum, std::vector<TH3*> DiW, TH1* Wtemplate,
            TH1* tt = 0) {
        MultiDimensionalFitLiklihood * functor = new MultiDimensionalFitLiklihood(name, nonWtbSum,
                hData, WtbSum, DiW, Wtemplate, tt);
        cout << "I am in bias Likelihood" << endl;

        ROOT::Math::Functor ret(*functor, 4);
        return make_pair(ret, functor);
    }

    std::pair<double, double> getNdataNmcMD(int bin, double f0 = F0,
            double f_ = FL, double rec_gen = 1., double nWjets = 1.) {

        int nbins = data->GetXaxis()->GetNbins();
        if (bin > nbins || nbins < 0) {
            cout << "No value for this cos(theta) bin" << endl;
            return make_pair(-100, -100);
        }
        double nData = data->GetBinContent(bin);
        double costheta = data->GetBinCenter(bin);
        double nSignal = LikelihoodFunction::nSignalRW(costheta, bin, f0, f_, rec_gen);
        double nMC = bkg->GetBinContent(bin)+ (nWjets * wtemplate->GetBinContent(bin)) + nSignal;
        return make_pair(nData, nMC);
    }
private:
    TH1* toptemplate;
    TH1* wtemplate;


};
// MultiDimensional minimum

void GetMinimumMD(ROOT::Math::Functor f, double * x, double * xerr, double & corr12, bool CalcError = true) {
    ROOT::Minuit2::Minuit2Minimizer * min = new ROOT::Minuit2::Minuit2Minimizer(ROOT::Minuit2::kMigrad);
    min->SetMaxFunctionCalls(1000000);
    min->SetMaxIterations(100000);
    min->SetTolerance(0.0001);
    if (CalcError)
        min->ProvidesError();
    //        x[0] = f_0
    //        x[1] = f_Neg
    //        x[2] = rec_gen factor
    //        x[3] = n W+jets
    //        x[4] = n tT
    //    double step[5] = {0.001,0.001,0.001,0.01,0.01};
    //    double A[5] = {x[0],x[1],x[2],x[3],x[4]};
    double step[4] = {0.001, 0.001, 0.001, 0.01};
    double A[4] = {x[0], x[1], x[2], x[3]};

    min->SetFunction(f);

    // Set the free variables to be minimized!
    min->SetVariable(0, "x", A[0], step[0]);
    //    min->SetFixedVariable(0,"x",0.564462);
    min->SetVariable(1, "y", A[1], step[1]);
    //    min->SetFixedVariable(1,"y",0.3159);
    min->SetVariable(2, "z", A[2], step[2]);
    min->SetFixedVariable(2, "z", 1.);
    min->SetVariable(3, "t", A[3], step[3]);
    //    min->SetFixedVariable(3, "t", 1955.93);
    //min->SetFixedVariable(3,"t",6200.);
    //    min->SetFixedVariable(3,"t",1952.72);
    //    min->SetFixedVariable(3,"t",2883.8);
    //    min->SetVariable(4,"r",A[4], step[4]); 
    min->Minimize();
    x[0] = min->X()[0];
    x[1] = min->X()[1];
    x[2] = min->X()[2];
    x[3] = min->X()[3];
    //    x[4] = min->X()[4];
    if (!CalcError)
        return;
    corr12 = min->Correlation(0, 1);
    xerr[0] = min->Errors()[0];
    xerr[1] = min->Errors()[1];
    xerr[2] = min->Errors()[2];
    xerr[3] = min->Errors()[3];
    //    xerr[4] = min->Errors()[4]; 

    cout << "f0            : " << x[0] << "\t+/-\t" << xerr[0] << endl;
    cout << "f_            : " << x[1] << "\t+/-\t" << xerr[1] << endl;
    cout << "reg_gen factor: " << x[2] << "\t+/-\t" << xerr[2] << endl;
    cout << "n_{W+jets}    : " << x[3] << "\t+/-\t" << xerr[3] << endl;

    cout << "Df0 Syst       : " << x[0] - 0.747787 + 0.78 << endl;
    cout << "DfL Syst       : " << x[1] - 0.254466 + 0.24 << endl;
    cout << "Df0            : " << x[0] - 0.747787 << endl;
    cout << "DfL            : " << x[1] - 0.254466 << endl;
    cout << "ErrF0          : " << xerr[0] *(0.17 / 0.0329229) << endl;
    cout << "ErrFL          : " << xerr[1] *(0.11 / 0.0323328) << endl;
    //    cout<<"n_{t#bar{t}}    : "<<x[4]<<"\t+/-\t"<<xerr[4]<<endl;

    cout << "f0-f_ correlation: " << corr12 << endl;
    //    double contX0[100];
    //    double contX1[100];
    //    unsigned int nPoints = 100;
    //    bool isCont = min->Contour(0,1,nPoints,contX0,contX1);
    //    TCanvas myCan;
    //    myCan.cd();
    //    TGraph *gr12 = new TGraph(nPoints,contX0,contX1);
    //    gr12->Draw("alf");
    //    myCan.SaveAs("myGraph.C");
    //    nPoints = 100;
    //    double scanX0[100];
    //    double scanX1[100];
    //    bool isScan = min->Scan(0,nPoints,scanX0,scanX1,0.5,1);
    //    TCanvas myCan2;
    //    myCan2.cd();
    //    TGraph *gr1 = new TGraph(nPoints,scanX0,scanX1);
    //    gr1->Draw("alf");
    //    myCan2.SaveAs("myGraph2.C");
}


#endif	/* MULTIDIMENSIONALFIT_H */

