/* 
 * File:   ACValidatorExecuter.h
 * Author: nadjieh
 *
 * Created on February 1, 2013, 6:13 PM
 */

#ifndef ACVALIDATOREXECUTER_H
#define	ACVALIDATOREXECUTER_H

using namespace std;
#include "FitValidator.h"
#include "ToyFitter.h"
#include "TF1.h"
#include "TF3.h"
#include "TH1.h"
#include "TH2.h"
#include "TMath.h"
#include "TCanvas.h"
#include "TRandom1.h"
#include "TRandom.h"
#include "TROOT.h"
#include "TFile.h"
#include "TVirtualFitter.h"
#include <string>
#include <iostream>
#include <sstream>
#include <map>
#include <vector>
#include "ValidatorExecuter.h"
//#define TEST_2D_Partial
//#define TEST_CHANGE_SIG_BKG
//#define TEST_DIAGONALITY
//#define TEST_DILEPTON_JEANNINE
//#define TEST_TWBIAS_JEANNINE
//#define TEST_DITOPBIAS_JEANNINE
//#define TEST_3D_CORRELATION

TH1* MixedACHistogram(bool frac, std::map<string, DistributionProducerFromSelected*> acsamples, double VL, double VR, int nPEX,
        double mt = mtop, double mW = MW) {
    std::map<string, DistributionProducerFromSelected*>::iterator sampleItr = acsamples.begin();
    TH1* ret = 0;
    Coefficients coeffs = VLVRCoeffs(VL, VR, 1, mt, mW);
    TH1* tmp = 0;
    for (; sampleItr != acsamples.end(); sampleItr++) {
        if (frac)
            tmp = sampleItr->second->GeneratePartialSample(1.0 / 3.0, nPEX);
        else
            tmp = sampleItr->second->GeneratePartialSampleLumiEQ(nPEX, false);
        cout << "confirmation: " << tmp->GetEntries() << endl;
        if (sampleItr->first == string("sm"))
            tmp->Scale(coeffs.m);
        if (sampleItr->first == string("unphys"))
            tmp->Scale(coeffs.n);
        if (sampleItr->first == string("r"))
            tmp->Scale(coeffs.k);
        if (ret == 0)
            ret = (TH1*) tmp->Clone("TheFirst");
        else
            ret->Add(tmp);
        cout << "confirmation II: " << ret->GetEntries() << endl;
        delete tmp;
    }
    return ret;
}

TH1* MixedACHistogramMC(std::map<string, TH1*> acsamples, double& n0, double VL, double VR, int nPEX,
        double mt = mtop, double mW = MW) {
    SamplesInfo si;
    std::map<string, TH1*>::iterator sampleItr = acsamples.begin();
    TH1* ret = 0;
    Coefficients coeffs = VLVRCoeffs(VL, VR, 1, mt, mW);
    TH1* tmp = 0;
    double selEf = 0;
    for (; sampleItr != acsamples.end(); sampleItr++) {
        tmp = sampleItr->second;

        if (sampleItr->first == string("sm")) {
            tmp->Scale(coeffs.m);
            selEf += (coeffs.m * tmp->GetEntries() / (double) si.N0[sampleItr->first]);
            cout << "confirmation: " << tmp->GetEntries() << " coeff is " << coeffs.m << " and N0 is " << si.N0[sampleItr->first] << endl;
            cout << "selEf is " << selEf << endl;
        }
        if (sampleItr->first == string("unphys")) {
            tmp->Scale(coeffs.n);
            selEf += (coeffs.n * tmp->GetEntries() / (double) si.N0[sampleItr->first]);
            cout << "confirmation: " << tmp->GetEntries() << " coeff is " << coeffs.n << " and N0 is " << si.N0[sampleItr->first] << endl;
            cout << "selEf is " << selEf << endl;
        }
        if (sampleItr->first == string("r")) {
            tmp->Scale(coeffs.k);
            selEf += (coeffs.k * tmp->GetEntries() / (double) si.N0[sampleItr->first]);
            cout << "confirmation: " << tmp->GetEntries() << " coeff is " << coeffs.k << " and N0 is " << si.N0[sampleItr->first] << endl;
            cout << "selEf is " << selEf << endl;
        }
        if (ret == 0)
            ret = (TH1*) tmp->Clone("TheFirstMC");
        else
            ret->Add(tmp);
        cout << "confirmation II: " << ret->GetEntries() << endl;
    }
    n0 = (double) ret->GetEntries() / selEf;
    cout << "n0: " << n0 << endl;
    return ret;
}

void RunACFitValidation(double VL, double VR, int StartPEX, int LPEX, int StartPEXPull, int LPEXPull, string prefix, string suffix,
        string histName, string dirName, double Lumi = 3793, bool is2D = false, std::string outDir = "./", bool is3D = false) {
    stringstream outName;
    outName << outDir << "Linearity_start-" << StartPEX << "-length-" << LPEX << "_Pull_start-" << StartPEXPull <<
            "-length-" << LPEXPull << ".root";
    cout << outName.str().c_str() << endl;

    std::pair<TF1, WeightFunctionCreator*> WtbWeightor = WeightFunctionCreator::getWeightFunction("WtbWeightor");
    SamplesInfo mySampleInfo;

    std::map<string, DistributionProducerFromSelected*> bkg_samples;
    std::map<string, DistributionProducerFromSelected*> signal_samples;
    std::map<string, DistributionProducerFromSelected*> ACsignal_samples;

    std::map<string, double>::iterator sampleItr = mySampleInfo.Xsections.begin();
    std::map<string, TH1*> inputAC;
    //    TH1* signal = 0;
    TH1* signalMC = 0;
    TH1* bkg = 0;
    int sampleIndex = 0;

    for (; sampleItr != mySampleInfo.Xsections.end(); sampleItr++) {
        if (isAC(sampleItr->first)) {
            TH1* hist = GetCosThetaPlot(sampleItr->first, prefix, suffix, histName, dirName, 10);
            hist->Sumw2();
            DistributionProducerFromSelected *myDist = new DistributionProducerFromSelected(hist, string(sampleItr->first), Lumi);
            ACsignal_samples[sampleItr->first] = myDist;
            hist->Scale(float(Lumi * sampleItr->second) / float(mySampleInfo.N0[sampleItr->first]));
            inputAC[sampleItr->first] = (TH1*) hist->Clone((string("cosTheta_") + sampleItr->first).c_str());
            cout << "AC is added " << sampleItr->first << " " << inputAC.size() << endl;
        }
        if (sampleItr->first == "qcd") {
            sampleIndex++;
            continue;
        }
        if (sampleItr->first == "w" || sampleItr->first == "dy") {
            //            cout<<sampleItr->first<<endl;
            TH1* hist = GetCosThetaPlot(sampleItr->first, prefix, suffix, histName, dirName, 10);
            hist->Sumw2();
            DistributionProducerFromSelected *myDist = new DistributionProducerFromSelected(hist, string(sampleItr->first), Lumi);
            bkg_samples[sampleItr->first] = myDist;
            hist->Scale(float(Lumi * sampleItr->second) / float(mySampleInfo.N0[sampleItr->first]));
            //           if(sampleItr == mySampleInfo.Xsections.begin())
            //            if (sampleIndex == 0)
            if (bkg == 0)
                bkg = ((TH1*) hist->Clone(string("bkg_" + string(hist->GetName())).c_str()));
            else {
                bkg->Add(hist);
                //                cout<<"Adding bkg with nbins = "<<bkg->GetXaxis()->GetNbins()<<
                //                        " and hist with nbins = "<<hist->GetXaxis()->GetNbins()<<endl;
            }
            cout << "bkg is added " << sampleItr->first << endl;
        } else if (!isAC(sampleItr->first) && sampleItr->first != string("AC")) {
            cout << sampleItr->first << endl;
            //            cout<<sampleItr->first<<endl;
            if (!is2D && !is3D) {
                TH1* hist1D = GetCosThetaPlot(sampleItr->first, prefix, suffix, histName, dirName, 10);
                hist1D->Sumw2();
                TH2* hist2D = (TH2*) GetCosThetaPlot(sampleItr->first, prefix, suffix, histName, dirName, 10, true);
                hist1D->Sumw2();
                hist2D->Sumw2();
                TH1* tmph2 = hist2D->ProjectionY();
                hist1D->Add(tmph2);
                delete tmph2;
                delete hist2D;
                DistributionProducerFromSelected* myDist = new DistributionProducerFromSelected(hist1D, string(sampleItr->first), Lumi);
                signal_samples[sampleItr->first] = myDist;
                hist1D->Scale(float(Lumi * sampleItr->second) / float(mySampleInfo.N0[sampleItr->first]));
                if (signalMC == 0)
                    signalMC = ((TH1*) hist1D->Clone(string("signal_" + string(hist1D->GetName())).c_str()));
                else {
                    signalMC->Add(hist1D);
                }
            }
        }
        sampleIndex++;
    }
    if (signalMC == NULL) {
        if (inputAC.size() != 0 && inputAC["sm"] != NULL)
            signalMC = new TH1D("tmpSignal", "tmpSignal", inputAC["sm"]->GetXaxis()->GetNbins()
                , inputAC["sm"]->GetXaxis()->GetXmin(), inputAC["sm"]->GetXaxis()->GetXmax());
        else
            cout << "What a hell in signalMC -------------------" << endl;
    }
    if (bkg == NULL) {
        if (signalMC != NULL)
            bkg = new TH1D("myBKG", "myBKG", signalMC->GetXaxis()->GetNbins()
                , signalMC->GetXaxis()->GetXmin(), signalMC->GetXaxis()->GetXmax());
        else
            cout << "What a hell in bkg -------------------" << endl;
    }

    gROOT->cd();

    int nFSteps = 300;
    int nVSteps = 50;
    //            int nFSteps = 5;

    double VRValuesStep[nVSteps];
    double VLFixed = 1;
    double FLValuesData[nVSteps];
    double F0ValuesData[nVSteps];
    double FRValuesData[nVSteps];
    for (int i = 0; i < nVSteps; i++) {
        VRValuesStep[i] = (float(i) / (float) nVSteps);
        Coefficients Fs = GetFs(VLFixed, VRValuesStep[i], 0, 0);
        FLValuesData[i] = Fs.m;
        FRValuesData[i] = Fs.k;
        F0ValuesData[i] = Fs.n;
    }
    double FNegValueSteps[nFSteps];
    for (int i = 0; i < nFSteps; i++) {
        FNegValueSteps[i] = float(i) / (float) nFSteps;
    }
    TH2D hFinalFNeg("hFinalFNeg", "Linearirty Check for F_{-};F_{-} input;F_{-} output", nFSteps, 0., 1., nFSteps, 0., 1.);
    TH2D hFinalF0("hFinalF0", "Linearirty Check for F_{0};V_{R} input;F_{0} output", nFSteps, 0., 1., nFSteps, 0., 1.);
    TH2D hFinalFPos("hFinalFPos", "Linearirty Check for F_{R};F_{R} input;F_{R} output", nFSteps, 0., 1., nFSteps, 0., 1.);
    for (int nPEX = 0; nPEX < 300; nPEX++) {
        cout << "PEX: " << nPEX << endl;

        if (nPEX >= (StartPEX + LPEX)) {
            cout << " ... Skipped" << endl;
            continue;
        }

        if (nPEX < StartPEX) {
            for (unsigned int i = 0; i < mySampleInfo.Xsections.size(); i++)
                SeedGenerator.Integer(10000);
            cout << " ... Skipped" << endl;
            continue;
        }
        F0 = F0ValuesData[nPEX];
        FL = FLValuesData[nPEX];
        double FposFixed = 1 - (F0)-(FL);

        TH1 * ACSingleTopPartial = MixedACHistogram(true, ACsignal_samples, VLFixed, VRValuesStep[nPEX], nPEX);
        stringstream name__;
        name__ << "CosTheta_bkg_" << nPEX;
        stringstream title__;
        title__ << "noWtb cos(#theta) : PEX=" << nPEX;
        TH1* hSumBGPartial = 0;
        if (!is2D && !is3D) {
            if (signalMC != NULL)
                hSumBGPartial = new TH1D(name__.str().c_str(), title__.str().c_str(), signalMC->GetXaxis()->GetNbins()
                    , signalMC->GetXaxis()->GetXmin(), signalMC->GetXaxis()->GetXmax());
            else if (inputAC.size() != 0 && inputAC["sm"] != NULL)
                hSumBGPartial = new TH1D(name__.str().c_str(), title__.str().c_str(), inputAC["sm"]->GetXaxis()->GetNbins()
                    , inputAC["sm"]->GetXaxis()->GetXmin(), inputAC["sm"]->GetXaxis()->GetXmax());
            else
                cout << "What a hell -------------------" << endl;
        } 
        hSumBGPartial->Sumw2();
        std::map<string, DistributionProducerFromSelected*>::iterator bkgItr = bkg_samples.begin();
        cout << "-------------------- bkg_samples.size(): " << bkg_samples.size() << endl;
        for (; bkgItr != bkg_samples.end(); bkgItr++) {
            cout << "background " << bkgItr->first << endl;
            TH1* tmp = 0;
            if (string(bkgItr->first) == "w") {
                tmp = bkgItr->second->GeneratePartialSample(1.0, nPEX);
                // tmp->Scale(3.0);
            } else
                tmp = bkgItr->second->GeneratePartialSample(1.0 / 3.0, nPEX);
            hSumBGPartial->Add(tmp);
            delete tmp;
        }
        stringstream name2D__;
        name2D__.str("");
        name__.str("");
        title__.str("");
        title__ << "Wtb cos(#theta) : PEX=" << nPEX;
        TH1* hSumSIGPartial = 0;
        if (!is2D && !is3D) {
            if (signalMC != NULL)
                hSumSIGPartial = new TH1D(name__.str().c_str(), title__.str().c_str(), signalMC->GetXaxis()->GetNbins()
                    , signalMC->GetXaxis()->GetXmin(), signalMC->GetXaxis()->GetXmax());
            else if (inputAC.size() != 0 && inputAC["sm"] != NULL)
                hSumSIGPartial = new TH1D(name__.str().c_str(), title__.str().c_str(), inputAC["sm"]->GetXaxis()->GetNbins()
                    , inputAC["sm"]->GetXaxis()->GetXmin(), inputAC["sm"]->GetXaxis()->GetXmax());
            else
                cout << "What a hell for bkg -------------------" << endl;

            hSumSIGPartial->Sumw2();
            std::map<string, DistributionProducerFromSelected*> ::iterator sigItr = signal_samples.begin();
            name__ << "CosTheta_signal_" << nPEX;
            for (; sigItr != signal_samples.end(); sigItr++) {
                if (sigItr->first == string("t") || sigItr->first == string("tbar"))
                    continue;
                cout << "signal to add!!!" << endl;
                TH1* tmp = sigItr->second->GeneratePartialSample(1.0 / 3.0, nPEX);
                hSumSIGPartial->Add(tmp);
                delete tmp;
            }
        } 
        cout << "for different polarization values" << endl;
        for (int i = 0; i < nFSteps; i++) {
            if (FNegValueSteps[i] > (1.0 - FposFixed))
                continue;

            double F0Value = 1.0 - FposFixed - FNegValueSteps[i];

            WtbWeightor.first.SetParameters(F0Value, FNegValueSteps[i]);

            name__.str("");
            name__ << hSumBGPartial->GetName() << "_" << VRValuesStep[nPEX] << "_" << FNegValueSteps[i] << endl;
            title__.str("");
            title__ << hSumBGPartial->GetTitle() << " for F_ = " << VRValuesStep[nPEX] << "_" << FNegValueSteps[i] << endl;
            if (!is2D && !is3D) {
                cout << "In 1D method: " << hSumBGPartial << endl;
                TH1* SIGinPEX = ((TH1*) hSumSIGPartial->Clone(name__.str().c_str()));
                SIGinPEX->SetTitle(title__.str().c_str());
                SIGinPEX->Add(ACSingleTopPartial);
                SIGinPEX->Multiply(&WtbWeightor.first, 1);
                SIGinPEX->SetTitle(title__.str().c_str());
                if (hSumBGPartial != NULL)
                    SIGinPEX->Add(hSumBGPartial);
                if (signalMC != NULL && SIGinPEX != NULL && bkg != NULL) {
                    cout << "signal: " << signalMC->GetName() << " " << signalMC->GetNbinsX() << " " << signalMC->Integral() << endl;
                    cout << "pData: " << SIGinPEX->GetName() << " " << SIGinPEX->GetNbinsX() << " " << SIGinPEX->Integral() << endl;
                    cout << "bkg: " << bkg->GetName() << " " << bkg->GetNbinsX() << " " << bkg->Integral() << endl;
                }
                cout << "I am here ..." << endl;
                cout << "ACSingleTopPartial: " << ACSingleTopPartial->Integral() << endl;
                cout << "SIGinPEX: " << SIGinPEX->Integral() << endl;
                cout << "signalMC: " << signalMC->Integral() << endl;
                cout << "bkg: " << bkg->Integral() << endl;
                std::pair<TF3, LikelihoodFunction*> LLinPEXforFNegValueArray = LikelihoodFunction::getLLFunction(
                        string("F_" + name__.str()), bkg, SIGinPEX, signalMC);
                //std::pair<TF3, LikelihoodFunction*> LLinPEXforFNegValueArray = LikelihoodFunction::getLLFunction(
                //        string("F_" + name__.str()), bkg, SIGinPEX, signalMC);
                TF3 LLinPEXforFNegValue = LLinPEXforFNegValueArray.first;
                cout << "after likelihood" << endl;
                double x[3] = {-1., -1., -1.};
                double xerr[3] = {-1., -1., -1.};
                double correlation12 = -1000;
                GetMinimum(LLinPEXforFNegValue, x, xerr, correlation12, false);
                hFinalFNeg.Fill(FNegValueSteps[i], x[1]);
                hFinalF0.Fill(F0Value, x[0]);
                hFinalFPos.Fill(FposFixed, 1.0 - x[0] - x[1]);
                cout << "before deleting" << endl;
                delete SIGinPEX;
                cout << "after deleting" << endl;
                delete LLinPEXforFNegValueArray.second;
            } 
        }//for loop
        delete hSumBGPartial;
        delete hSumSIGPartial;
    }
    
    delete WtbWeightor.second;
    TFile * outFile = new TFile(outName.str().c_str(), "recreate");
    outFile->cd();
    hFinalF0.Write();
    hFinalFNeg.Write();
    hFinalFPos.Write();

    outFile->Close();
}

#endif	/* ACVALIDATOREXECUTER_H */

