/* 
 * File:   Combinator.C
 * Author: nadjieh
 *
 * Created on January 9, 2013, 5:55 PM
 */

#include "../../interface/CombinedLikelihood.h"
#include "../../interface/WhelFitChiSquared.h"
#include "../../interface/UsefullStructsForCombination.h"
#include "/opt/root/math/mathcore/inc/Math/Functor.h"
#include "TH1.h"
#include "TFile.h"
#include <string>
#include <iostream>
using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    WTempForCombination3D input7;
    WTempForCombination3D input8;
    TH1* bkginsignal7 = 0; //for t-processes other than munub
    TH1* bkg7 = 0; // for non-t processes
    TH1* bkginsignal8 = 0; //for t-processes other than munub
    TH1* bkg8 = 0; // for non-t processes
    bool do3D = true;
    TFile * file = 0;

    for (int f = 1; f < argc; f++) {
        std::string arg_fth(*(argv + f));
        cout << f << " ---- " << arg_fth << endl;
        if (arg_fth == "signal7") {
            f++;
            std::string out(*(argv + f));
            cout << "signal7" << endl;
            file = new TFile(out.c_str(), "read");
            int pos = string(file->GetName()).find("mu");
            bool muonfile = (pos >= 0 && pos < string(file->GetName()).size());
            if (!do3D || (do3D && !muonfile)) {
                input7.rest.signalIID.push_back(((TH2*) file->Get("Default_allW/Default_allWcosTheta2D"))->RebinY(1));
                cout << input7.rest.signalIID.at(input7.rest.signalIID.size() - 1)->GetName() << endl;
                cout << "signal2D integral 7: " << input7.rest.signalIID.at(input7.rest.signalIID.size() - 1)->Integral() << endl;
            }
            if (do3D && muonfile) {
                cout << " in 3D :-)" << endl;
                input7.rest.signalIIID.push_back(((TH3D*) file->Get("Default_allW/Default_allWcosTheta3D"))->Rebin3D(1, 1, 1, "newname"));
                cout << input7.rest.signalIIID.at(input7.rest.signalIIID.size() - 1) << endl;
            }
            if (input7.rest.signalIID.size())
                cout << input7.rest.signalIID.at(input7.rest.signalIID.size() - 1)->GetNbinsY() << endl;
            if (bkginsignal7 == 0)
                bkginsignal7 = (((TH1*) file->Get("Default_allW/Default_allWcosTheta"))->Rebin(1));
            else
                bkginsignal7->Add(((TH1*) file->Get("Default_allW/Default_allWcosTheta"))->Rebin(1));

        } else if (arg_fth == "signal8") {
            f++;
            std::string out(*(argv + f));
            cout << "signal8" << endl;
            file = new TFile(out.c_str(), "read");
            int pos = string(file->GetName()).find("mu");
            bool muonfile = (pos >= 0 && pos < string(file->GetName()).size());
            if (!do3D || (do3D && !muonfile)) {
                input8.rest.signalIID.push_back(((TH2*) file->Get("Default_allW/Default_allWcosTheta2D"))->RebinY(10));
                cout << input8.rest.signalIID.at(input8.rest.signalIID.size() - 1)->GetName() << endl;
                cout << "signal2D integral 8: " << input8.rest.signalIID.at(input8.rest.signalIID.size() - 1)->Integral() << endl;
            }
            if (do3D && muonfile) {
                cout << " in 3D :-)" << endl;
                input8.rest.signalIIID.push_back(((TH3D*) file->Get("Default_allW/Default_allWcosTheta3D"))->Rebin3D(1, 10, 1, "newname"));
                cout << input8.rest.signalIIID.at(input8.rest.signalIIID.size() - 1) << endl;
            }
            if (input8.rest.signalIID.size())
                cout << input8.rest.signalIID.at(input8.rest.signalIID.size() - 1)->GetNbinsY() << endl;
            if (bkginsignal8 == 0)
                bkginsignal8 = (((TH1*) file->Get("Default_allW/Default_allWcosTheta"))->Rebin(10));
            else
                bkginsignal8->Add(((TH1*) file->Get("Default_allW/Default_allWcosTheta"))->Rebin(10));
        } else if (arg_fth == "data7") {
            f++;
            std::string out(*(argv + f));
            cout << "data 7" << endl;
            file = new TFile(out.c_str(), "read");
            input7.rest.data = ((TH1*) file->Get("Default_allW/Default_allWcosTheta"))->Rebin(1);
        } else if (arg_fth == "data8") {
            f++;
            std::string out(*(argv + f));
            cout << "data 8" << endl;
            file = new TFile(out.c_str(), "read");
            input8.rest.data = ((TH1*) file->Get("Default_allW/Default_allWcosTheta"))->Rebin(10);
        } else if (arg_fth == "bkg7") {
            f++;
            std::string out(*(argv + f));
            cout << "bkg 7" << endl;
            file = new TFile(out.c_str(), "read");

            if (bkg7 == NULL) {
                bkg7 = ((TH1*) file->Get("Default_allW/Default_allWcosTheta"))->Rebin(1);
            } else {
                bkg7->Add(((TH1*) file->Get("Default_allW/Default_allWcosTheta"))->Rebin(1));
            }
        } else if (arg_fth == "bkg8") {
            f++;
            std::string out(*(argv + f));
            cout << "bkg 8" << endl;
            file = new TFile(out.c_str(), "read");

            if (bkg8 == NULL) {
                cout << "here .." << endl;
                bkg8 = ((TH1*) file->Get("Default_allW/Default_allWcosTheta"))->Rebin(10);
            } else {
                bkg8->Add(((TH1*) file->Get("Default_allW/Default_allWcosTheta"))->Rebin(10));
            }
        } else if (arg_fth == "wtemplate7") {
            f++;
            std::string out(*(argv + f));
            cout << "w template 7" << endl;
            file = new TFile(out.c_str(), "read");
            input7.Wtemplate = ((TH1*) file->Get("btag10"));
            //            input7.Wtemplate = ((TH1*) file->Get("Default_allW/Default_allWcosTheta"));
            input7.Wtemplate->Rebin(1);
        } else if (arg_fth == "wtemplate8") {
            f++;
            std::string out(*(argv + f));
            cout << "w template 8" << endl;
            file = new TFile(out.c_str(), "read");
            input8.Wtemplate = ((TH1*) file->Get("Default_allW/Default_allWcosTheta"));
            input8.Wtemplate->Rebin(10);
        }
    }

    cout << "7: " << bkg7 << "\t" << input7.rest.data << "\t" << input7.Wtemplate << endl;
    cout << "8: " << bkg8 << "\t" << input8.rest.data << "\t" << input8.Wtemplate << endl;
    input7.Wtemplate->Sumw2();
    input7.Wtemplate->Scale((double) 1. / (double) input7.Wtemplate->Integral());
    input8.Wtemplate->Sumw2();
    input8.Wtemplate->Scale((double) 1. / (double) input8.Wtemplate->Integral());

    double x[6] = {0.7, 0.3, 1., 1., 1., 1.};
    double xerr[6] = {-1., -1., -1., -1., -1., -1.};
    double correlation;

    cout << "In Bias fit: \n\tsize of 2D signal at 7 TeV is " << input7.rest.signalIID.size() <<
            "\n\tsize of 3D signal at 7 TeV is " << input7.rest.signalIIID.size() << endl;
    cout << "In Bias fit: \n\tsize of 2D signal at 8 TeV is " << input8.rest.signalIID.size() <<
            "\n\tsize of 3D signal at 8 TeV is " << input8.rest.signalIIID.size() << endl;
    if (bkg7 != NULL && bkginsignal7 != NULL) {
        bkg7->Add(bkginsignal7);
    } else if (bkg7 == NULL && bkginsignal7 != NULL) {
        bkg7 = (TH1*) bkginsignal7->Clone("myBkg7");
    }
    input7.rest.nonRWs = bkg7;
    if (bkg8 != NULL && bkginsignal8 != NULL) {
        bkg8->Add(bkginsignal8);
    } else if (bkg8 == NULL && bkginsignal8 != NULL) {
        bkg8 = (TH1*) bkginsignal8->Clone("myBkg8");
    }
    input8.rest.nonRWs = bkg8;
    cout << "Reached here" << endl;


    std::vector<double> pars;
    pars.push_back(0.713279);
    pars.push_back(0.293116);
    pars.push_back(1);
    pars.push_back(1961.83);
    double nW8 = 2256.13;
    cout << pars[0] << "\t" << pars[1] << "\t" << pars[2] << "\t" << pars[3] << "\t" << endl;

    double delStatF0 = 0.114023;
    double delStatFL = 0.0687606;

    double delSystF0 = 0.023;
    double delSystFL = 0.033;

    double delTotF0 = sqrt(pow(delSystF0, 2) + pow(delStatF0, 2));
    double delTottFL = sqrt(pow(delSystFL, 2) + pow(delStatFL, 2));

    TH1D * base7 = (TH1D*) input7.Wtemplate->Clone("Wtemp7_base");
    TH1D * base8 = (TH1D*) input8.Wtemplate->Clone("Wtemp8_base");


    CombinedChiSquaredCaculatorAndPlotter myChi2Stat("CombinedChi2Stat", pars, nW8, input7, input8, delStatF0, delStatFL);
    myChi2Stat.PrintOut();
    cout << "ChiSquared: " << myChi2Stat.GetChiSquared() << endl;
    cout << "NormalChiSquared: " << myChi2Stat.GetNormalizedChiSquared() << endl;
    myChi2Stat.WriteInfo();

    input7.Wtemplate = (TH1D*) base7->Clone("Wtemp7_syst");
    input8.Wtemplate = (TH1D*) base8->Clone("Wtemp8_syst");
    CombinedChiSquaredCaculatorAndPlotter myChi2Syst(string("CombinedChi2Syst"), pars, nW8, input7, input8, delSystF0, delSystFL);
    myChi2Syst.PrintOut();
    cout << "ChiSquared: " << myChi2Syst.GetChiSquared() << endl;
    cout << "NormalChiSquared: " << myChi2Syst.GetNormalizedChiSquared() << endl;
    myChi2Syst.WriteInfo();

    input7.Wtemplate = (TH1D*) base7->Clone("Wtemp7_tot");
    input8.Wtemplate = (TH1D*) base8->Clone("Wtemp8_tot");
    CombinedChiSquaredCaculatorAndPlotter myChi2total(string("CombinedChi2total"), pars, nW8, input7, input8, delTotF0, delTottFL);
    myChi2total.PrintOut();
    cout << "ChiSquared: " << myChi2total.GetChiSquared() << endl;
    cout << "NormalChiSquared: " << myChi2total.GetNormalizedChiSquared() << endl;
    myChi2total.WriteInfo();




    return 0;
}

