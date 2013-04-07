/* 
 * File:   Combinator.C
 * Author: nadjieh
 *
 * Created on January 9, 2013, 5:55 PM
 */

#include "../interface/CombinedLikelihood.h"
#include "../interface/UsefullStructsForCombination.h"
#include "/opt/root/math/mathcore/inc/Math/Functor.h"
#include "TH1.h"
#include "TFile.h"
#include <string>
#include <iostream>
using namespace std;
//#define Syst
//#define IJES

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
    bool singleMatrix = false;
    bool is2Drecgen = false;
    bool do3D = false;
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

            //            if (bkg7 == NULL) {
            //                cout << "here .." << endl;
            //                bkg7 = ((TH1*) file->Get("Default_allW/Default_allWcosTheta"))->Rebin(1);
            //            } else {
            //                bkg7->Add(((TH1*) file->Get("Default_allW/Default_allWcosTheta"))->Rebin(1));
            //            }
            bool myQCD = (out.find("_QCD.root") > 0 && fabs(out.find("_QCD.root")) < out.size());
            cout << file->GetName() << "\tmyQCD: " << myQCD << endl;
            TH1 * tmpQCD = 0;
            if (myQCD) {
                tmpQCD = ((TH1*) file->Get("Default_allW/Default_allWcosTheta"))->Rebin(1);
                cout << "tmpQCD: " << tmpQCD << endl;
                tmpQCD->Scale(107.5 / tmpQCD->Integral());
                cout << out << "\thas " << tmpQCD->GetEntries() << " entries but " << tmpQCD->Integral() << " integral" << endl;
            }
            if (bkg7 == NULL) {
                cout << "here .." << endl;
                if (myQCD)
                    bkg7 = tmpQCD;
                else
                    bkg7 = ((TH1*) file->Get("Default_allW/Default_allWcosTheta"))->Rebin(1);
            } else {
                if (myQCD)
                    bkg7->Add(tmpQCD);
                else
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
        } else if (arg_fth == "singleMatrix") {
            f++;
            cout << "singleMatrix" << endl;
            std::string out(*(argv + f));
            if (out == "true")
                singleMatrix = true;
        } else if (arg_fth == "is2Drecgen") {
            f++;
            cout << "is2Drecgen" << endl;
            std::string out(*(argv + f));
            if (out == "yes" || out == "Yes" || out == "Y" || out == "y"
                    || out == "YES")
                is2Drecgen = true;
        } else if (arg_fth == "do3D") {
            f++;
            cout << "do3D" << endl;
            std::string out(*(argv + f));
            if (out == "yes" || out == "Yes" || out == "Y" || out == "y"
                    || out == "YES")
                do3D = true;
        }
    }
#ifndef Syst
    cout << "7: " << bkg7 << "\t" << input7.rest.data << "\t" << input7.Wtemplate << endl;
    cout << "8: " << bkg8 << "\t" << input8.rest.data << "\t" << input8.Wtemplate << endl;
    input7.Wtemplate->Sumw2();
    input7.Wtemplate->Scale((double) 1. / (double) input7.Wtemplate->Integral());
    input8.Wtemplate->Sumw2();
    input8.Wtemplate->Scale((double) 1. / (double) input8.Wtemplate->Integral());

    double x[6] = {0.7, 0.3, 1., 1., 1., 1.};
    double xerr[6] = {-1., -1., -1., -1., -1., -1.};
    double correlation;
    if (is2Drecgen && !singleMatrix && do3D) {
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
        std::pair<ROOT::Math::Functor, CombinedLikelihood*> myLL =
                CombinedLikelihood::getCombinedLikelihoodForBias("LL", input7, input8, false);
        cout << "before get minimum simple: " << endl;
        cout << "bkg bins 7: " << input7.rest.nonRWs->GetNbinsX() << endl;
        cout << "bkg bins 8: " << input8.rest.nonRWs->GetNbinsX() << endl;
        cout << "w bins 7: " << input7.Wtemplate->GetNbinsX() << endl;
        cout << "w bins 8: " << input8.Wtemplate->GetNbinsX() << endl;
        cout << "data bins 7: " << input7.rest.data->GetNbinsX() << endl;
        cout << "data bins 8: " << input8.rest.data->GetNbinsX() << endl;
        GetMinimumCombined(myLL.first, x, xerr, correlation);
        delete myLL.second;
    } else {
        cout << "Not implemented yet!" << endl;
    }
#endif
#ifdef Syst
    cout << "7: " << bkg7 << "\t" << input7.rest.data << "\t" << input7.Wtemplate << endl;
    cout << "8: " << bkg8 << "\t" << input8.rest.data << "\t" << input8.Wtemplate << endl;
    input7.Wtemplate->Sumw2();
    input7.Wtemplate->Scale((double) 1. / (double) input7.Wtemplate->Integral());
    double x[5] = {0.7, 0.3, 1., 1., 1.,};
    double xerr[5] = {-1., -1., -1., -1., -1.,};
    double correlation;
    cout << "In Syst fit: \n\tsize of 2D signal at 7 TeV is " << input7.rest.signalIID.size() <<
            "\n\tsize of 3D signal at 7 TeV is " << input7.rest.signalIIID.size() << endl;
    cout << "In Syst fit: \n\tsize of 2D signal at 8 TeV is " << input8.rest.signalIID.size() <<
            "\n\tsize of 3D signal at 8 TeV is " << input8.rest.signalIIID.size() << endl;
    cout << "nbin signal 7: " << input7.rest.signalIID[0]->GetYaxis()->GetNbins() << endl;
    cout << "nbin signal 8: " << input8.rest.signalIID[0]->GetYaxis()->GetNbins() << endl;
    TH1* Signal1D7 = 0;
    TH1* Signal1D8 = 0;
    stringstream s;
    for (unsigned int p = 0; p < input7.rest.signalIID.size(); p++) {
        s.str("");
        s << p << "7_pY";
        if (Signal1D7 == 0)
            Signal1D7 = (TH1*) input7.rest.signalIID.at(p)->ProjectionY(s.str().c_str());
        else
            Signal1D7->Add((TH1*) input7.rest.signalIID.at(p)->ProjectionY(s.str().c_str()));
    }
    s.str("");
    for (unsigned int p = 0; p < input8.rest.signalIID.size(); p++) {
        s.str("");
        s << p << "8_pY";
        if (Signal1D8 == 0)
            Signal1D8 = (TH1*) input8.rest.signalIID.at(p)->ProjectionY(s.str().c_str());
        else
            Signal1D8->Add((TH1*) input8.rest.signalIID.at(p)->ProjectionY(s.str().c_str()));
    }
    cout << "signal done" << endl;
#ifndef IJES
    cout << "-- " << bkginsignal8->Integral() << endl;
    cout << "-- " << bkg8->Integral() << endl;
    if (bkginsignal8 != NULL) {
        if (bkg8 != NULL) {
            bkg8->Add(bkginsignal8);
        } else {
            bkg8 = bkginsignal8;
        }
    }
#endif
#ifdef IJES
    if (bkginsignal8 != NULL)
        //            bkg->Add(bkginsignal8);        
        Signal1D8->Add(bkginsignal8);
#endif
    if (bkginsignal7 != NULL)
        //            bkg->Add(bkginsignal7);        
        Signal1D7->Add(bkginsignal7);

    InputForCombination1D IDin8;
    IDin8.name = "IDin8";
    IDin8.data = input8.rest.data;
    IDin8.nonRWs = bkg8;
    IDin8.signalID = Signal1D8;
    WTempForCombination1D IDin7;
    IDin7.rest.name = "IDin7";
    IDin7.rest.data = input7.rest.data;
    IDin7.rest.nonRWs = bkg7;
    IDin7.rest.signalID = Signal1D7;
    IDin7.Wtemplate = input7.Wtemplate;
    cout << "8TeV Info: \n\tnData: " << IDin8.data->Integral() << "\n\tnSignal: " << IDin8.signalID->Integral()
            << "\n\tnBkg: " << IDin8.nonRWs->Integral() << endl;
    cout << "7TeV Info: \n\tnData: " << IDin7.rest.data->Integral() << "\n\tnSignal: " << IDin7.rest.signalID->Integral()
            << "\n\tnBkg: " << IDin7.rest.nonRWs->Integral() << endl;
    std::pair<ROOT::Math::Functor, CombinedLikelihood*> myLL =
            CombinedLikelihood::getCombinedLikelihoodForSyst("LL", IDin7, IDin8, true);
    GetMinimumSystCombined(myLL.first, x, xerr, correlation, true);

    cout << "----- systematics: " << endl;
    double f00 = 0.713279;
    double fl0 = 0.293116;

    double f0n = 0.707345;
    double fln = 0.296289;
    cout << "\nDelF0 = " << x[0] - f0n << " +/- " << xerr[0]* 0.114023 / 0.0217699 << endl;
    cout << "\nDelFL = " << x[1] - fln << " +/- " << xerr[1]* 0.0687606 / 0.0207235 << endl;

    cout << "\nF0 = " << x[0] - f0n + f00 << " +/- " << xerr[0]* 0.114023 / 0.0217699 << endl;
    cout << "\nFL = " << x[1] - fln + fl0 << " +/- " << xerr[1]* 0.0687606 / 0.0207235 << endl;

    delete myLL.second;

#endif

    return 0;
}

