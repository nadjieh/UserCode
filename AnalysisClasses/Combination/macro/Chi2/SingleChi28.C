/* 
 * File:   MultiDimFitTest.C
 * Author: nadjieh
 *
 * Created on June 9, 2012, 1:11 PM
 */
#include "../../../BackgroundStudies/interface/MultiDimensionalFit.h"
#include "/opt/root/math/mathcore/inc/Math/Functor.h"
#include "TH1.h"
#include "TFile.h"
#include "../../interface/UsefullStructsForCombination.h"
#include <string>
#include <iostream>
#include "TRandom.h"
#include "../../interface/WhelFitChiSquared.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    TH1* data;
    std::vector<TH2*> signalIID; // for munub t-processes
    std::vector<TH3*> signalIIID; // for munub t-processes
    TH1* bkginsignal = 0; //for t-processes other than munub
    TH1* bkg = 0; // for non-t processes
    TH1* wtemplate = 0;
    bool do3D = true;
    int nReBin = 10;
    TFile * file = 0;
    for (int f = 1; f < argc; f++) {
        std::string arg_fth(*(argv + f));
        cout << f << " ---- " << arg_fth << endl;
        if (arg_fth == "signal") {
            f++;
            std::string out(*(argv + f));
            //            cout << "signal: ";
            file = new TFile(out.c_str(), "read");
            cout << file->GetName();
            int pos = string(file->GetName()).find("mu");

            bool muonfile = (pos >= 0 && pos < string(file->GetName()).size());

            if (!do3D || (do3D && !muonfile)) {
                signalIID.push_back(((TH2*) file->Get("Default_allW/Default_allWcosTheta2D"))->RebinY(nReBin));
            }
            if (do3D && muonfile) {
                signalIIID.push_back(((TH3D*) file->Get("Default_allW/Default_allWcosTheta3D"))->Rebin3D(1, nReBin, 1, "newname"));
            }
            if (bkginsignal == 0)
                bkginsignal = (((TH1*) file->Get("Default_allW/Default_allWcosTheta"))->Rebin(nReBin));
            else
                bkginsignal->Add(((TH1*) file->Get("Default_allW/Default_allWcosTheta"))->Rebin(nReBin));

            TH1 * myTemp = (TH1*) (((TH1*) file->Get("Default_allW/Default_allWcosTheta")))->Clone("myTemp");
            if (!muonfile)
                cout << " : " << signalIID.at(signalIID.size() - 1)->Integral() << " + " << myTemp->Integral()
                << " = " << signalIID.at(signalIID.size() - 1)->Integral() + myTemp->Integral() << endl;
            else if (do3D)
                cout << " : " << signalIIID.at(signalIIID.size() - 1)->Integral() << " + " << myTemp->Integral()
                << " = " << signalIIID.at(signalIIID.size() - 1)->Integral() + myTemp->Integral() << endl;
            delete myTemp;

        } else if (arg_fth == "data") {
            f++;
            std::string out(*(argv + f));
            cout << "data" << endl;
            file = new TFile(out.c_str(), "read");
            data = ((TH1*) file->Get("Default_allW/Default_allWcosTheta"))->Rebin(nReBin);
            cout << data << endl;
        } else if (arg_fth == "bkg") {
            f++;
            std::string out(*(argv + f));
            cout << "bkg" << endl;
            file = new TFile(out.c_str(), "read");
            if (bkg == NULL) {
                cout << "here .." << endl;
                bkg = ((TH1*) file->Get("Default_allW/Default_allWcosTheta"))->Rebin(nReBin);
            } else {
                bkg->Add(((TH1*) file->Get("Default_allW/Default_allWcosTheta"))->Rebin(nReBin));
            }
        } else if (arg_fth == "wtemplate") {
            f++;
            std::string out(*(argv + f));
            cout << "w template" << endl;
            file = new TFile(out.c_str(), "read");
            cout << out << "\t";
            wtemplate = ((TH1*) file->Get("Default_allW/Default_allWcosTheta"));
            cout << wtemplate << endl;
            wtemplate->Rebin(nReBin);
        }
    }
    cout << bkg << "\t" << data << "\t" << wtemplate << endl;
    wtemplate->Sumw2();
    wtemplate->Scale((double) 1. / (double) wtemplate->Integral());
    data->Print();

    cout << "In Bias fit: \n\tsize of 2D signal is " << signalIID.size() <<
            "\n\tsize of 3D signal is " << signalIIID.size() << endl;
    cout << "bkginsignal: " << bkginsignal->Integral() << " bkg: " << bkg->Integral() << endl;
    if (bkg != NULL && bkginsignal != NULL) {
        bkg->Add(bkginsignal);
    } else if (bkg == NULL && bkginsignal != NULL) {
        bkg = (TH1*) bkginsignal->Clone("myBkg");
    }
    //        bkg->Scale(ratio);
    cout << "bkg: " << bkg->Integral() << " data: " << data->Integral() << " signal: ";
    double nSignal = 0;
    for (unsigned int p = 0; p < signalIID.size(); p++) {
        nSignal += signalIID[p]->Integral();
        //            cout << signalIID[p]->Integral() << endl;
    }
    for (unsigned int p = 0; p < signalIIID.size(); p++) {
        nSignal += signalIIID[p]->Integral();
        //            cout << signalIIID[p]->Integral() << endl;
    }
    cout << nSignal << endl;
    WTempForCombination3D my3DInput;
    my3DInput.Wtemplate = (TH1*)wtemplate->Clone("Wtemp_Syst"); //normal
    my3DInput.rest.data = data;
    my3DInput.rest.nonRWs = bkg;
    my3DInput.rest.signalIID = signalIID;
    my3DInput.rest.signalIIID = signalIIID;
    std::vector<double> pars;
    pars.push_back(0.667767);
    pars.push_back(0.326762);
    pars.push_back(1);
    pars.push_back(2276.97);

    double delStatF0 = 0.149025;
    double delStatFL = 0.0891012;

    double delSystF0 = 0.026;
    double delSystFL = 0.024;

    double delTotF0 = sqrt(pow(delStatF0,2)+pow(delSystF0,2));
    double delTotFL = sqrt(pow(delStatFL,2)+pow(delSystFL,2));

    ChiSquaredCaculatorAndPlotter myChi2Syst(string("8TeVChi2Syst"), pars, my3DInput, delSystF0, delSystFL);
    myChi2Syst.PrintOut();
    cout << "ChiSquared: " << myChi2Syst.GetChiSquared() << endl;
    cout << "NormalChiSquared: " << myChi2Syst.GetNormalizedChiSquared() << endl;
    myChi2Syst.WriteInfo();

    my3DInput.Wtemplate = (TH1*)wtemplate->Clone("Wtemp_Stat"); //normal
    ChiSquaredCaculatorAndPlotter myChi2Stat(string("8TeVChi2Stat"), pars, my3DInput, delStatF0, delStatFL);
    myChi2Stat.PrintOut();    
    cout << "ChiSquared: " << myChi2Stat.GetChiSquared() << endl;
    cout << "NormalChiSquared: " << myChi2Stat.GetNormalizedChiSquared() << endl;
    myChi2Stat.WriteInfo();

    my3DInput.Wtemplate = (TH1*)wtemplate->Clone("Wtemp_total"); //normal
    ChiSquaredCaculatorAndPlotter myChi2total(string("8TeVChi2total"), pars, my3DInput, delTotF0, delTotFL);
    myChi2total.PrintOut();    
    cout << "ChiSquared: " << myChi2total.GetChiSquared() << endl;
    cout << "NormalChiSquared: " << myChi2total.GetNormalizedChiSquared() << endl;
    myChi2total.WriteInfo();



    return 0;
}

