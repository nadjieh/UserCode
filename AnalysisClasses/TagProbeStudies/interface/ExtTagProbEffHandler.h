/* 
 * File:   TagProbEffHandler.h
 * Author: ajafari
 *
 * Created on October 28, 2010, 5:50 PM
 */

#ifndef EXTTAGPROBEFFHANDLER_H
#define	EXTTAGPROBEFFHANDLER_H
using namespace std;
using namespace TopTree;
#include "/afs/cern.ch/user/a/ajafari/scratch0/CMSSW_3_8_5_patch3/src/AnalysisClasses/TagProbeStudies/interface/TagProbeObjectPropertis.h"
#include "TH2.h"

class ExtTagProbeEffHandler : public EfficiencyHandler<TRootTagProbeObject> {
public:
    typedef EfficiencyHandler<TRootTagProbeObject> BASE_;


    ExtTagProbeEffHandler(std::string name, bool fillSubVal_ = false, double minSub = -1, double maxSub = -1,
    bool twoD = false, bool isZ = false) :
    BASE_(name, new Zmass(), NULL,76.,106.,fillSubVal_,minSub,maxSub), //BASE_(name),
    twoD_(twoD)
    {


        TF1 *f = new TF1("f",breitgausfun, 76., 106. ,4);
        Double_t par[4];
        par[0] = 0.002;
        par[1] = 91.18;
        par[2] = 1.;
        par[3] = 10000;
//        par[4] = -0.5;
//        par[5] = 0.1;
        f->SetParameters(par);



        BASE_::setExtfitFunc(f);

        v.clear();
        BASE_::AllCondition = 0;
        BASE_::AddProp(new ProbeEta());
        v.push_back(new ProbeEta());
        BASE_::AddProp(new ProbePt());
        v.push_back(new ProbePt());
        BASE_::AddProp(new ProbePhi());
        v.push_back(new ProbePhi());
        BASE_::AddProp(new minRJetProbe());
        v.push_back(new minRJetProbe());
        BASE_::AddProp(new nJet());
        v.push_back(new nJet());





        twoDHists.clear();
        for (uint i = 0; i < v.size(); i++) {
            for (uint j = i + 1; j < v.size(); j++) {
                twoDHists.push_back(new TH2D(*(TH2D*) (v.at(i)->GetH2(v.at(j), "", ""))));
            }
        }
    }
    bool twoD_;
    std::vector<TH2D*> twoDHists;

    virtual void Fill(TRootTagProbeObject* t, double weight = 1) {
        BASE_::Fill(t, weight);
        //        cout<<twoDHists.size()<<endl;
        int n = 0;
        for (uint i = 0; i < v.size(); i++) {
            for (uint j = i + 1; j < v.size(); j++) {
                twoDHists.at(n)->Fill(v.at(i)->ReadValue(t).at(0), v.at(j)->ReadValue(t).at(0), weight);
                n++;
                //                cout<<n<<endl;
            }
        }
    }

    virtual void WriteAll(TDirectory * dir) {
        cout<<"In "<<this->getName()<<" ___________________________________________"<<endl;
        BASE_::WriteAll(dir);
        if (twoDHists.size() != 0) {
            dir->mkdir(string(BASE_::getName() + "_2D").c_str())->cd();
            for (uint j = 0; j < twoDHists.size(); j++) {
                twoDHists.at(j)->Write();
            }
        }

    }

    void ResetConditionForAllProps() {
        for (uint i = 0; i < BASE_::GetProperties(); i++) {
            BASE_::GetEffH1(i)->Condition = BASE_::Condition;
            BASE_::GetEffH1(i)->AllCondition = BASE_::AllCondition;
        }
    }
private:
    std::vector<ObjectProperty<TRootTagProbeObject> * > v;

    static Double_t myBreight(Double_t *x, Double_t *par)
    /*--------------------------------------------------------------------*/ {
        //par[0]: mean
        //par[1]: sigma
        //par[2]: normalization
        return(par[2]*TMath::BreitWigner(x[0], par[1], par[0]));
    }

    /*--------------------------------------------------------------------*/
   static Double_t breitgausfun(Double_t *x, Double_t *par)
    /*--------------------------------------------------------------------*/ {

        //Fit parameters:
        //par[0]=Width (scale) Breit-Wigner
        //par[1]=Most Probable (MP, location) Breit mean
        //par[2]=Total area (integral -inf to inf, normalization constant)
        //par[3]=Width (sigma) of convoluted Gaussian function
        //
        //In the Landau distribution (represented by the CERNLIB approximation),
        //the maximum is located at x=-0.22278298 with the location parameter=0.
        //This shift is corrected within this function, so that the actual
        //maximum is identical to the MP parameter.

        // Numeric constants
        Double_t invsq2pi = 0.3989422804014; // (2 pi)^(-1/2)
        Double_t twoPi = 6.2831853071795; //2Pi

        // Control constants
        Double_t np = 100.0; // number of convolution steps
        Double_t sc = 4; // convolution extends to +-sc Gaussian sigmas

        // Variables
        Double_t xx;
        Double_t fland;
        Double_t sum = 0.0;
        Double_t xlow, xupp;
        Double_t step;
        Double_t i;


        // Range of convolution integral
        xlow = x[0] - sc * par[3];
        xupp = x[0] + sc * par[3];

        step = (xupp - xlow) / np;

        // Convolution integral of Breit and Gaussian by sum
        for (i = 1.0; i <= np / 2; i++) {
            xx = xlow + (i - .5) * step;
            fland = TMath::BreitWigner(xx, par[1], par[0]);
            sum += fland * TMath::Gaus(x[0], xx, par[3]);

            xx = xupp - (i - .5) * step;
            fland = TMath::BreitWigner(xx, par[1], par[0]);
            sum += fland * TMath::Gaus(x[0], xx, par[3]);
        }
        return (par[2] * step * sum * invsq2pi / par[3]);
    }
    /*--------------------------------------------------------------------*/
   static Double_t breitgausfunPlusLine(Double_t *x, Double_t *par)
    /*--------------------------------------------------------------------*/ {

        //Fit parameters:
        //par[0]=Width (scale) Breit-Wigner
        //par[1]=Most Probable (MP, location) Breit mean
        //par[2]=Total area (integral -inf to inf, normalization constant)
        //par[3]=Width (sigma) of convoluted Gaussian function
        //par[4]=slop of the line
        //par[5]=interception of the line
        //
        //In the Landau distribution (represented by the CERNLIB approximation),
        //the maximum is located at x=-0.22278298 with the location parameter=0.
        //This shift is corrected within this function, so that the actual
        //maximum is identical to the MP parameter.

        // Numeric constants
        Double_t invsq2pi = 0.3989422804014; // (2 pi)^(-1/2)


        // Control constants
        Double_t np = 100.0; // number of convolution steps
        Double_t sc = 4; // convolution extends to +-sc Gaussian sigmas

        // Variables
        Double_t xx;
        Double_t fland;
        Double_t sum = 0.0;
        Double_t xlow, xupp;
        Double_t step;
        Double_t i;


        // Range of convolution integral
        xlow = x[0] - sc * par[3];
        xupp = x[0] + sc * par[3];

        step = (xupp - xlow) / np;

        // Convolution integral of Breit and Gaussian by sum
        for (i = 1.0; i <= np / 2; i++) {
            xx = xlow + (i - .5) * step;
            fland = TMath::BreitWigner(xx, par[1], par[0]);
            sum += fland * TMath::Gaus(x[0], xx, par[3]);

            xx = xupp - (i - .5) * step;
            fland = TMath::BreitWigner(xx, par[1], par[0]);
            sum += fland * TMath::Gaus(x[0], xx, par[3]);
        }
        return (par[2] * step * sum * invsq2pi / par[3] + (par[4] * x[0]+par[5]));
    }


};


#endif	/* EXTTAGPROBEFFHANDLER_H */

