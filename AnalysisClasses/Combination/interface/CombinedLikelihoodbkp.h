/* 
 * File:   CombinedLikelihood.h
 * Author: nadjieh
 *
 * Created on January 9, 2013, 11:12 AM
 */

#ifndef COMBINEDLIKELIHOOD_H
#define	COMBINEDLIKELIHOOD_H
#include "UsefullStructsForCombination.h" 
#include "../../BackgroundStudies/interface/MultiDimensionalFit.h" 
#include "/opt/root/math/mathmore/inc/Math/GSLMinimizer.h"
#include "/opt/root/math/mathmore/inc/Math/GSLSimAnMinimizer.h"
#include "/opt/root/math/minuit2/inc/Minuit2/Minuit2Minimizer.h"
#include "/opt/root/math/mathcore/inc/Math/Functor.h"
#include <string>
#include <iostream>
#include <sstream>
using namespace std;

class CombinedLikelihood : public MultiDimensionalFitLiklihood {
public:

    
    
    CombinedLikelihood(string name, WTempForCombination3D input7, WTempForCombination3D input8) :
    MultiDimensionalFitLiklihood(input7.rest.name, input7.rest.nonRWs, input7.rest.data, input7.rest.signalIID, input7.rest.signalIIID, input7.Wtemplate),
    MDFLL8(input8.rest.name, input8.rest.nonRWs, input8.rest.data, input8.rest.signalIID, input8.rest.signalIIID, input8.Wtemplate) {
    };
    virtual ~CombinedLikelihood(){};

    double operator()(const double * x) {
        //        x[0] = f_0
        //        x[1] = f_Neg
        //        x[2] = rec_gen factor 7TeV
        //        x[3] = nWjets7
        //        x[4] = rec_gen factor 8TeV
        //        x[5] = nWjets8


        double LL = 0.0;
        int nbins = this->data->GetXaxis()->GetNbins();
        for (int i = 0; i < nbins; i++) {
            std::pair<double, double> numbers7 = this->getNdataNmcMD(i + 1, x[0], x[1], x[2], x[3]);
            std::pair<double, double> numbers8 = this->MDFLL8.getNdataNmcMD( i + 1, x[0], x[1], x[4], x[5]);
            LL += this->logLikelihood(numbers7.first, numbers7.second);
            LL += this->logLikelihood(numbers8.first, numbers8.second);
        }
        return LL;
    }

    static std::pair<ROOT::Math::Functor, CombinedLikelihood*> getCombinedLikelihoodForBias(
            string name, WTempForCombination3D input7, WTempForCombination3D input8) {
        CombinedLikelihood * functor = new CombinedLikelihood(name, input7, input8);
        cout << "I am in bias CombinedLikelihood" << endl;
        ROOT::Math::Functor ret(*functor, 6);
        return make_pair(ret, functor);
    }

private:
    
    MultiDimensionalFitLiklihood MDFLL8;
};

void GetMinimumCombined(ROOT::Math::Functor f, double * x, double * xerr, double & corr12, bool CalcError = true) {
    ROOT::Minuit2::Minuit2Minimizer * min = new ROOT::Minuit2::Minuit2Minimizer(ROOT::Minuit2::kMigrad);
    min->SetMaxFunctionCalls(1000000);
    min->SetMaxIterations(100000);
    min->SetTolerance(0.0001);
    if (CalcError)
        min->ProvidesError();
    //        x[0] = f_0
    //        x[1] = f_Neg
    //        x[2] = rec_gen factor7
    //        x[3] = n W+jets7
    //        x[4] = rec_gen factor8
    //        x[5] = n W+jets8

    double step[6] = {0.001, 0.001, 0.001, 0.01, 0.001, 0.01};
    double A[6] = {x[0], x[1], x[2], x[3], x[4], x[5]};

    min->SetFunction(f);

    // Set the free variables to be minimized!
    min->SetVariable(0, "f0", A[0], step[0]);
    min->SetVariable(1, "f_", A[1], step[1]);
    min->SetVariable(2, "recgenS", A[2], step[2]);
    min->SetFixedVariable(2, "recgenS", 1.);
    min->SetVariable(3, "WJetS", A[3], step[3]);
    min->SetVariable(4, "recgenE", A[4], step[4]);
    min->SetFixedVariable(4, "recgenE", 1.);
    min->SetVariable(5, "WJetS", A[5], step[5]);

    min->Minimize();
    x[0] = min->X()[0];
    x[1] = min->X()[1];
    x[2] = min->X()[2];
    x[3] = min->X()[3];
    x[4] = min->X()[4];
    x[5] = min->X()[5];
    if (!CalcError)
        return;
    corr12 = min->Correlation(0, 1);
    xerr[0] = min->Errors()[0];
    xerr[1] = min->Errors()[1];
    xerr[2] = min->Errors()[2];
    xerr[3] = min->Errors()[3];
    xerr[4] = min->Errors()[4];
    xerr[5] = min->Errors()[5];

    cout << "f0              : " << x[0] << "\t+/-\t" << xerr[0] << endl;
    cout << "f_              : " << x[1] << "\t+/-\t" << xerr[1] << endl;
    cout << "reg_gen factor 7: " << x[2] << "\t+/-\t" << xerr[2] << endl;
    cout << "n_{W+jets}     7: " << x[3] << "\t+/-\t" << xerr[3] << endl;
    cout << "reg_gen factor 8: " << x[4] << "\t+/-\t" << xerr[4] << endl;
    cout << "n_{W+jets}     8: " << x[5] << "\t+/-\t" << xerr[5] << endl;
    cout << "f0-f_ correlation: " << corr12 << endl;
}


#endif	/* COMBINEDLIKELIHOOD_H */

