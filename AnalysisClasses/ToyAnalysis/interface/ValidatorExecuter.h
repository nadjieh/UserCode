/* 
 * File:   ValidatorExecuter.h
 * Author: nadjieh
 *
 * Created on May 3, 2012, 1:55 PM
 */

#ifndef VALIDATOREXECUTER_H
#define	VALIDATOREXECUTER_H
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
//#define TEST_2D_Partial
//#define TEST_CHANGE_SIG_BKG
//#define TEST_DIAGONALITY
#define TEST_DILEPTON_JEANNINE
TH2* DiagonalMaker(TH2* input) {
    TH1* h1 = input->ProjectionY("proY");
    TH2* output = new TH2D((string(input->GetName()) + "_Diagonal").c_str(), (string(input->GetTitle()) + "_Diagonal").c_str(),
            h1->GetXaxis()->GetNbins(), h1->GetXaxis()->GetXmin(), h1->GetXaxis()->GetXmax(),
            h1->GetXaxis()->GetNbins(), h1->GetXaxis()->GetXmin(), h1->GetXaxis()->GetXmax());
    for (int iBin = 0; iBin < h1->GetXaxis()->GetNbins(); iBin++) {
        output->SetBinContent(iBin + 1, iBin + 1, h1->GetBinContent(iBin + 1));
        output->SetBinError(iBin + 1, iBin + 1, h1->GetBinError(iBin + 1));
    }
    delete h1;
    return output;
}

TH1* GetCosThetaPlot(string name, string prefix, string suffix, string histName, string dirName, int nFinalBin = 10, bool is2D = false) {
    TFile * f = TFile::Open(string(prefix + name + suffix).c_str());
    TH1* h = 0;
    if (!is2D) {
        stringstream name;
        name << dirName << "/" << dirName << histName;
        //        name << histName;
        cout << name.str() << endl;
        h = ((TH1*) f->Get(name.str().c_str()));
        cout << h << endl;
        if ((h->GetXaxis()->GetNbins()) == nFinalBin)
            return h;
        if ((h->GetXaxis()->GetNbins() % nFinalBin) == 0) {
            h->Rebin(((h->GetXaxis()->GetNbins()) / nFinalBin));
        } else {
            std::cout << nFinalBin << " does not count " << h->GetXaxis()->GetNbins() << std::endl;
            std::cout << "I will take the biggest number less than " << nFinalBin << "that counts it .." << std::endl;
            int n = 1;
            for (int i = 2; i < nFinalBin; i++) {
                if ((h->GetXaxis()->GetNbins() % i) == 0)
                    n = i;
            }
            h->Rebin(((h->GetXaxis()->GetNbins()) / n));
        }
    } else {
        stringstream name;
        name << dirName << "/" << dirName << histName << "2D";
        h = ((TH2*) f->Get(name.str().c_str()));
        if ((h->GetXaxis()->GetNbins()) == nFinalBin && (h->GetYaxis()->GetNbins()) == nFinalBin)
            return h;
        if ((h->GetXaxis()->GetNbins() % nFinalBin) == 0 && (h->GetYaxis()->GetNbins() % nFinalBin) == 0) {
            ((TH2*) h)->RebinX(((h->GetXaxis()->GetNbins()) / nFinalBin));
            ((TH2*) h)->RebinY(((h->GetYaxis()->GetNbins()) / nFinalBin));
        } else {
            std::cout << nFinalBin << " does not count " << h->GetXaxis()->GetNbins() << std::endl;
            std::cout << nFinalBin << " or does not count " << h->GetYaxis()->GetNbins() << std::endl;
            std::cout << "I will take the biggest number less than " << nFinalBin << "that counts both .." << std::endl;
            int n = 1;
            for (int i = 2; i < nFinalBin; i++) {
                if ((h->GetXaxis()->GetNbins() % i) == 0 && (h->GetYaxis()->GetNbins() % i) == 0)
                    n = i;
            }
            ((TH2*) h)->Rebin2D(((h->GetXaxis()->GetNbins()) / n), ((h->GetYaxis()->GetNbins()) / n));
        }
        cout << h->GetXaxis()->GetNbins() << "\t" << h->GetYaxis()->GetNbins() << endl;
    }

    //    cout<<"Nbins after rebinning: "<<h->GetXaxis()->GetNbins()<<endl;
    return h;
}

void RunFitValidation(int StartPEX, int LPEX, int StartPEXPull, int LPEXPull, string prefix, string suffix,
        string histName, string dirName, double Lumi = 3793, bool is2D = false, std::string outDir = "./") {
    stringstream outName;
    outName <<outDir<< "Linearity_start-" << StartPEX << "-length-" << LPEX << "_Pull_start-" << StartPEXPull <<
            "-length-" << LPEXPull << ".root";
    cout << outName.str().c_str() << endl;
    //    double FposFixed = 0.0009;
    double FposFixed = 1 - (6.64263e-01)-(3.03734e-01);
    std::pair<TF1, WeightFunctionCreator*> WtbWeightor = WeightFunctionCreator::getWeightFunction("WtbWeightor");
    SamplesInfo mySampleInfo;
    std::map<string, DistributionProducerFromSelected*> bkg_samples;
    std::map<string, DistributionProducerFromSelected*> signal_samples;
    std::vector<TH2*> signalIIDPartial;
    std::vector<TH2*> signalIID;
    std::map<string, double>::iterator sampleItr = mySampleInfo.Xsections.begin();
    //    TH1* signal = 0;
    TH1* signalMC = 0;
    TH1* bkg = 0;
    int sampleIndex = 0;
    signalIIDPartial.clear();
    signalIID.clear();
    std::vector<TH2*> tmpVec2DDiLep;
    TH1D * bkgTmpDilep = 0;
    for (; sampleItr != mySampleInfo.Xsections.end(); sampleItr++) {
        cout << sampleItr->first << endl;
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
        } else {
            //            cout<<sampleItr->first<<endl;
            if (!is2D) {
#ifndef TEST_CHANGE_SIG_BKG
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
//                if (sampleIndex == 2)
                if (signalMC == 0)
                    signalMC = ((TH1*) hist1D->Clone(string("signal_" + string(hist1D->GetName())).c_str()));
                else {
                    signalMC->Add(hist1D);
#endif /*TEST_CHANGE_SIG_BKG*/
#ifdef TEST_CHANGE_SIG_BKG
                    /*
                     * Special condition to chack:
                     * 1D + different sig-back composition
                     */
                    TH1* hist1D = GetCosThetaPlot(sampleItr->first, prefix, suffix, histName, dirName, 10);
                    hist1D->Sumw2();
                    DistributionProducerFromSelected* myDist = new DistributionProducerFromSelected(hist1D, string(sampleItr->first), Lumi);
                    bkg_samples[sampleItr->first] = myDist;
                    hist1D->Scale(float(Lumi * sampleItr->second) / float(mySampleInfo.N0[sampleItr->first]));
                    bkg->Add(hist1D);

                    TH2* hist2D = (TH2*) GetCosThetaPlot(sampleItr->first, prefix, suffix, histName, dirName, 10, true);
                    hist2D->Sumw2();
                    TH1* tmph2 = hist2D->ProjectionY();
                    delete hist2D;
                    DistributionProducerFromSelected* myDist2 = new DistributionProducerFromSelected(tmph2, string(sampleItr->first), Lumi);
                    signal_samples[sampleItr->first] = myDist2;
                    tmph2->Scale(float(Lumi * sampleItr->second) / float(mySampleInfo.N0[sampleItr->first]));
//                    if (sampleIndex == 2)
                    if (signalMC == 0)
                        signalMC = ((TH1*) tmph2->Clone(string("signal_" + string(hist1D->GetName())).c_str()));
                    else {
                        signalMC->Add(tmph2);
#endif   /*TEST_CHANGE_SIG_BKG*/  
                    }
                } else {
                    TH1* bkginsignal = GetCosThetaPlot(sampleItr->first, prefix, suffix, histName, dirName, 10);
                    bkginsignal->Sumw2();
                    DistributionProducerFromSelected* myDist = new DistributionProducerFromSelected(bkginsignal
                            , string(sampleItr->first), Lumi);
                    bkg_samples[sampleItr->first] = myDist;
                    bkginsignal->Scale(float(Lumi * sampleItr->second) / float(mySampleInfo.N0[sampleItr->first]));
                    //            if(sampleItr == mySampleInfo.Xsections.begin())
                    if (bkg != 0)
                        bkg->Add(bkginsignal);
                    else {
                        cout << "WARNING: CHECK BKG SCENARIO \n\t first put w, dy, ... in the input list" << endl;
			bkg = (TH1*)bkginsignal->Clone("bkginsig");
//                        return;
                    }
                    cout << "bkginSignal is added " << sampleItr->first << endl;
                    TH2* histIID = (TH2*) GetCosThetaPlot(sampleItr->first, prefix, suffix, histName, dirName, 10, /*is2D*/true);
                    histIID->Sumw2();
#ifdef TEST_DIAGONALITY
                    TH2* diagonal2D = DiagonalMaker(histIID);
                    delete histIID;
                    DistributionProducerFromSelected* myDist2D = new DistributionProducerFromSelected(diagonal2D
                            , string(sampleItr->first), Lumi, true);
                    signal_samples[sampleItr->first] = myDist2D;
                    diagonal2D->Scale(float(Lumi * sampleItr->second) / float(mySampleInfo.N0[sampleItr->first]));
                    signalIID.push_back((TH2*) diagonal2D->Clone((sampleItr->first + "_" + std::string(diagonal2D->GetName())).c_str()));
#endif /*TEST_DIAGONALITY*/
#ifndef TEST_DIAGONALITY
                    DistributionProducerFromSelected* myDist2D = new DistributionProducerFromSelected(histIID
                            , string(sampleItr->first), Lumi, true);
                    signal_samples[sampleItr->first] = myDist2D;
                    histIID->Scale(float(Lumi * sampleItr->second) / float(mySampleInfo.N0[sampleItr->first]));
                    signalIID.push_back((TH2*) histIID->Clone(("MyTwoD_"+sampleItr->first + "_" + std::string(histIID->GetName())).c_str()));

#ifdef TEST_DILEPTON_JEANNINE
                    int position = string(signalIID.at(signalIID.size()-1)->GetName()).find("mu");
		    cout<<"position: "<<position<<"\t"<<signalIID.at(signalIID.size()-1)->GetName()<<endl;
		    bool isDilep = (position != 0 && position < string(signalIID.at(signalIID.size()-1)->GetName()).size());	
		    if(!isDilep)
                    	tmpVec2DDiLep.push_back((TH2*)signalIID.at(signalIID.size()-1)->Clone());
		    if(isDilep){
			if(bkgTmpDilep != 0 )
			    bkgTmpDilep->Add(signalIID.at(signalIID.size()-1)->ProjectionY());
			else
			    bkgTmpDilep = signalIID.at(signalIID.size()-1)->ProjectionY("firstDiLep");
		    }
#endif /*TEST_DILEPTON_JEANNINE*/ 
#endif /*TEST_DIAGONALITY*/
                }
            }
            sampleIndex++;
        }
#ifdef 	TEST_DILEPTON_JEANNINE
	bkgTmpDilep->Add(bkg);
#endif /*TEST_DILEPTON_JEANNINE*/
        gROOT->cd();
        TH2D hFinalFNeg("hFinalFNeg", "Linearirty Check for F_{-};F_{-} input;F_{-} output", 300, 0., 1., 300, 0., 1.);
        TH2D hFinalF0("hFinalF0", "Linearirty Check for F_{0};F_{0} input;F_{0} output", 300, 0., 1., 300, 0., 1.);
        TH2D hFinalFPos("hFinalFPos", "Linearirty Check for F_{+};nPEX;F_{+} output", 300, 0., 300., 1000, -0.5, 0.5);
        int nFSteps = 300;

        double FNegValueSteps[nFSteps];
        for (int i = 0; i < nFSteps; i++) {
            FNegValueSteps[i] = float(i) / (float) nFSteps;
        }
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


            stringstream name__;
            name__ << "CosTheta_bkg_" << nPEX;
            stringstream title__;
            title__ << "noWtb cos(#theta) : PEX=" << nPEX;
            TH1* hSumBGPartial = 0;
            if (!is2D)
                hSumBGPartial = new TH1D(name__.str().c_str(), title__.str().c_str(), signalMC->GetXaxis()->GetNbins()
                    , signalMC->GetXaxis()->GetXmin(), signalMC->GetXaxis()->GetXmax());
            else
                hSumBGPartial = new TH1D(name__.str().c_str(), title__.str().c_str(), signalIID.at(0)->GetYaxis()->GetNbins()
                    , signalIID.at(0)->GetYaxis()->GetXmin(), signalIID.at(0)->GetYaxis()->GetXmax());
            hSumBGPartial->Sumw2();
            std::map<string, DistributionProducerFromSelected*>::iterator bkgItr = bkg_samples.begin();
            cout<<"--------------------"<<endl;
            for (; bkgItr != bkg_samples.end(); bkgItr++) {
                cout<<"background "<< bkgItr->first<<endl;
		TH1* tmp = 0;
		if(string(bkgItr->first) == "w" ){
                    tmp = bkgItr->second->GeneratePartialSample(1.0, nPEX);
		   // tmp->Scale(3.0);
		}
		else
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
            if (!is2D) {
                hSumSIGPartial = new TH1D(name__.str().c_str(), title__.str().c_str(), signalMC->GetXaxis()->GetNbins()
                        , signalMC->GetXaxis()->GetXmin(), signalMC->GetXaxis()->GetXmax());
                hSumSIGPartial->Sumw2();
                std::map<string, DistributionProducerFromSelected*> ::iterator sigItr = signal_samples.begin();
                name__ << "CosTheta_signal_" << nPEX;
#ifdef TEST_2D_Partial
                stringstream fname;
                fname << "1DTEST_" << nPEX << ".root";
                TFile * myf = new TFile(fname.str().c_str(), "recreate");
#endif /*TEST_2D_Partial*/
                for (; sigItr != signal_samples.end(); sigItr++) {
                    TH1* tmp = sigItr->second->GeneratePartialSample(1.0 / 3.0, nPEX);
                    hSumSIGPartial->Add(tmp);
#ifdef TEST_2D_Partial
                    myf->cd();
                    tmp->Write();
#endif /*TEST_2D_Partial*/
                    delete tmp;
                }
#ifdef TEST_2D_Partial  
                myf->Write();
                myf->Close();
#endif /*TEST_2D_Partial*/
            } else {
                hSumSIGPartial = new TH1D(name__.str().c_str(), title__.str().c_str(), signalIID.at(0)->GetYaxis()->GetNbins()
                        , signalIID.at(0)->GetYaxis()->GetXmin(), signalIID.at(0)->GetYaxis()->GetXmax());
                hSumSIGPartial->Sumw2();
                std::map<string, DistributionProducerFromSelected*> ::iterator sigItr = signal_samples.begin();
                name2D__ << "CosTheta_signal_2D_" << nPEX;
                signalIIDPartial.clear();
                for (; sigItr != signal_samples.end(); sigItr++) {
                    TH2* tmp = ((TH2*) sigItr->second->GeneratePartialSample(1.0 / 3.0, nPEX));
                    signalIIDPartial.push_back((TH2*) tmp->Clone(std::string(sigItr->first + "_" + name2D__.str()).c_str()));
                    delete tmp;
                }
#ifdef TEST_2D_Partial
                stringstream fname;
                fname << "2DTEST_" << nPEX << ".root";
                TFile * myf = new TFile(fname.str().c_str(), "recreate");
                cout << "*********************************************************************" << endl;
                cout << myf->GetName() << "**********************************" << endl;
                cout << "*********************************************************************" << endl;
                myf->cd();
                for (unsigned int l = 0; l < signalIIDPartial.size(); l++) {
                    signalIIDPartial.at(l)->Write();
                }
                myf->Write();
                myf->Close();
#endif

            }

            for (int i = 0; i < nFSteps; i++) {
                if (FNegValueSteps[i] > (1.0 - FposFixed))
                    continue;

                double F0Value = 1.0 - FposFixed - FNegValueSteps[i];

                WtbWeightor.first.SetParameters(F0Value, FNegValueSteps[i]);

                name__.str("");
                name__ << hSumBGPartial->GetName() << "_" << FNegValueSteps[i];
                title__.str("");
                title__ << hSumBGPartial->GetTitle() << " for F_ = " << FNegValueSteps[i];
                if (!is2D) {
                    TH1* SIGinPEX = ((TH1*) hSumSIGPartial->Clone(name__.str().c_str()));
                    SIGinPEX->SetTitle(title__.str().c_str());
                    SIGinPEX->Multiply(&WtbWeightor.first, 1);
#ifdef TEST
                    TCanvas c;
                    c.cd();
                    WtbWeightor.first.Draw();
                    stringstream canvNme;
                    canvNme << FNegValueSteps[i] << "_" << F0Value << "_";
                    c.SaveAs(string(canvNme.str() + string(WtbWeightor.first.GetName()) + ".C").c_str());
#endif /*TEST*/
#ifdef TEST_2D_Partial
                    stringstream fname;
                    fname << "1DSIGinPEX_" << nPEX << ".root";
                    TFile * myf = new TFile(fname.str().c_str(), "recreate");

                    myf->cd();

                    SIGinPEX->Write();

#endif
                    SIGinPEX->Add(hSumBGPartial);
#ifdef TEST_2D_Partial

                    TH1D * htmp = (TH1D*) SIGinPEX->Clone("allData");
                    myf->cd();

                    htmp->Write();
                    signalMC->Write();
                    bkg->Write();

                    delete htmp;

                    myf->Close();
#endif                   
                    std::pair<TF3, LikelihoodFunction*> LLinPEXforFNegValueArray = LikelihoodFunction::getLLFunction(
                            string("F_" + name__.str()), bkg, SIGinPEX, signalMC);
                    TF3 LLinPEXforFNegValue = LLinPEXforFNegValueArray.first;

                    double x[3] = {-1., -1., -1.};
                    double xerr[3] = {-1., -1., -1.};
                    double correlation12 = -1000;
                    GetMinimum(LLinPEXforFNegValue, x, xerr, correlation12, false);
                    hFinalFNeg.Fill(FNegValueSteps[i], x[1]);
                    hFinalF0.Fill(F0Value, x[0]);
                    hFinalFPos.Fill(nPEX, 1.0 - x[0] - x[1]);
                    delete SIGinPEX;
                    delete LLinPEXforFNegValueArray.second;
                } else {
                    TH1* SIGinPEX = ((TH1*) hSumSIGPartial->Clone(name__.str().c_str()));
                    SIGinPEX->SetTitle(title__.str().c_str());
                    for (int iBin = 0; iBin < SIGinPEX->GetXaxis()->GetNbins(); iBin++) {
                        double iContent = 0;
                        for (unsigned int iSample = 0; iSample < signalIIDPartial.size(); iSample++) {
                            name2D__.str("");
                            name2D__ << signalIIDPartial.at(iSample)->GetName() << "_" << FNegValueSteps[i] << "_" << iBin;
                            TH1* sigProjectionX = signalIIDPartial.at(iSample)->ProjectionX(name2D__.str().c_str(), iBin + 1, iBin + 1);
                            sigProjectionX->SetTitle(title__.str().c_str());
                            sigProjectionX->Multiply(&WtbWeightor.first, 1);
                            iContent += sigProjectionX->Integral();
                            delete sigProjectionX;
                        }
                        SIGinPEX->SetBinContent(iBin + 1, iContent);
                    }
#ifdef TEST
                    TCanvas c;
                    c.cd();
                    WtbWeightor.first.Draw();
                    stringstream canvNme;
                    canvNme << FNegValueSteps[i] << "_" << F0Value << "_";
                    c.SaveAs(string(canvNme.str() + string(WtbWeightor.first.GetName()) + ".C").c_str());
#endif /*TEST*/
#ifdef TEST_2D_Partial
                    stringstream fname;
                    fname << "2DSIGinPEX_" << nPEX << ".root";
                    TFile * myf = new TFile(fname.str().c_str(), "recreate");


                    myf->cd();
                    SIGinPEX->Write();


#endif
                    SIGinPEX->Add(hSumBGPartial);
#ifdef TEST_2D_Partial

                    TH1D * signaltoTest = signalIID.at(0)->ProjectionY((string(signalIID.at(0)->GetName()) + "_toTest").c_str());
                    for (unsigned int iSigTest = 1; iSigTest < signalIID.size(); iSigTest++) {
                        signaltoTest->Add(signalIID.at(iSigTest)->ProjectionY((string(signalIID.at(iSigTest)->GetName()) + "_toTest").c_str()));
                    }
                    TH1D * htmp = (TH1D*) SIGinPEX->Clone("allData");
                    myf->cd();

                    htmp->Write();
                    signaltoTest->Write();
                    bkg->Write();

                    delete htmp;
                    delete signaltoTest;
                    myf->Close();
#endif  
#ifdef TEST_DILEPTON_JEANNINE
                    std::pair<TF3, LikelihoodFunction*> LLinPEXforFNegValueArray = LikelihoodFunction::getLLFunctionGeneralized(
                            string("F_" + name__.str()), bkgTmpDilep, SIGinPEX, tmpVec2DDiLep);
#endif /*TEST_DILEPTON_JEANNINE*/
#ifndef TEST_DILEPTON_JEANNINE
                    std::pair<TF3, LikelihoodFunction*> LLinPEXforFNegValueArray = LikelihoodFunction::getLLFunctionGeneralized(
                            string("F_" + name__.str()), bkg, SIGinPEX, signalIID);
#endif /*TEST_DILEPTON_JEANNINE*/
                    TF3 LLinPEXforFNegValue = LLinPEXforFNegValueArray.first;
                    //            for(int as = 0; as <1; as+=0.01)
                    //                cout<<LLinPEXforFNegValue.Eval(as,1-as,1);

                    double x[3] = {-1., -1., -1.};
                    double xerr[3] = {-1., -1., -1.};
                    double correlation12 = -1000;
                    GetMinimum(LLinPEXforFNegValue, x, xerr, correlation12, false);
                    hFinalFNeg.Fill(FNegValueSteps[i], x[1]);
                    hFinalF0.Fill(F0Value, x[0]);
                    //            hFinalFNeg.Fill(FNegValueSteps[i],x[0]);
                    //            hFinalF0.Fill(F0Value,x[1]);
                    hFinalFPos.Fill(nPEX, 1.0 - x[0] - x[1]);
                    delete SIGinPEX;
                    delete LLinPEXforFNegValueArray.second;
                }
            }//for loop
            delete hSumBGPartial;
            delete hSumSIGPartial;
        }
        TH1D hPullFNeg("hPullFNeg", "Pull distribution for F_{-}", 1000, -5, 5);
        TH1D hPullF0("hPullF0", "Pull distribution for F_{0}", 1000, -5, 5);
        TH1D hPullFPos("hPullFPos", "Pull distribution for F_{+}", 1000, -5, 5);
        TH1D hPullFResp("hPullFResp", "Pull distribution for F_{resp}", 1000, -5, 5);

        TH1D hResFNeg("hResFNeg", "Residual for F_{-}", 1000, -0.5, 0.5);
        TH1D hResF0("hResF0", "Residual for F_{0}", 1000, -0.5, 0.5);
        TH1D hResFPos("hResFPos", "Residual for F_{+}", 1000, -0.5, 0.5);
        TH1D hResFResp("hResFResp", "Residual for F_{resp}", 1000, -0.5, 0.5);
        cout << StartPEXPull << "  " << LPEXPull << endl;
        for (int nPEXPull = 0; nPEXPull < 1000; nPEXPull++) {
            //        cout<< "PEXPull:"<<nPEXPull<<endl;

            if (nPEXPull >= (StartPEXPull + LPEXPull)) {
                cout << " ... Skipped pull" << endl;
                continue;
            }

            if (nPEXPull < StartPEXPull) {
                for (unsigned int i = 0; i < mySampleInfo.Xsections.size(); i++)
                    SeedGeneratorLumiEQ.Integer(10000);
                cout << " ... Skipped pull" << endl;
                continue;
            }

            cout << "PEXPull:" << nPEXPull << endl;

            stringstream name__;
            name__ << "CosTheta_Pull_" << nPEXPull;
            stringstream title__;
            title__ << "cos(#theta) : PEXPull=" << nPEXPull;

            TH1* hData = 0;
            if (!is2D)
                hData = new TH1D(name__.str().c_str(), title__.str().c_str(), signalMC->GetXaxis()->GetNbins(),
                    signalMC->GetXaxis()->GetXmin(), signalMC->GetXaxis()->GetXmax());
            else
                hData = new TH1D(name__.str().c_str(), title__.str().c_str(), signalIID.at(0)->GetYaxis()->GetNbins(),
                    signalIID.at(0)->GetYaxis()->GetXmin(), signalIID.at(0)->GetYaxis()->GetXmax());
            hData->Sumw2();
            std::map<string, DistributionProducerFromSelected*>::iterator bkgItr = bkg_samples.begin();
            for (; bkgItr != bkg_samples.end(); bkgItr++) {
                //            cout<< "..." << bkgItr->first<< "..." <<endl;
                TH1* tmp = bkgItr->second->GeneratePartialSampleLumiEQ(nPEXPull);
                hData->Add(tmp);
                delete tmp;
            }

            std::map<string, DistributionProducerFromSelected*>::iterator sigItr = signal_samples.begin();
            if (!is2D) {
                for (; sigItr != signal_samples.end(); sigItr++) {
                    //            cout<< "..." << sigItr->first<< "..." <<endl;
                    TH1* tmp = sigItr->second->GeneratePartialSampleLumiEQ(nPEXPull);
                    hData->Add(tmp);
                    delete tmp;
                }
                std::pair<TF3, LikelihoodFunction*> LLinPEXforFNegValueArray = LikelihoodFunction::getLLFunction(
                        string("F_" + name__.str()), bkg, hData, signalMC);
                TF3 LLinPEXforFNegValue = LLinPEXforFNegValueArray.first;
                double x[3] = {-1., -1., -1.};
                double xerr[3] = {-1., -1., -1.};
                double correlation12 = -1000;
                GetMinimum(LLinPEXforFNegValue, x, xerr, correlation12);
                double fneg = x[1];
                double f0 = x[0];
                double fpos = 1.0 - x[1] - x[0];

                double fresponse = x[2];
                double errfrespo = xerr[2];
                double resfresp0 = fresponse - 1.0;

                hPullFResp.Fill((double) resfresp0 / (double) errfrespo);
                hResFResp.Fill(resfresp0);

                double errfneg = xerr[1];
                double errf0 = xerr[0];
                double errfpos = sqrt(errf0 * errf0 + errfneg * errfneg + (2 * correlation12));

                double resneg = fneg - (3.03734e-01);
                double respos = fpos - FposFixed;
                double resf0 = f0 - (6.64263e-01);

                hPullFNeg.Fill((double) resneg / (double) errfneg);
                hPullF0.Fill((double) resf0 / (double) errf0);
                hPullFPos.Fill((double) respos / (double) errfpos);

                hResFPos.Fill(respos);
                hResFNeg.Fill(resneg);
                hResF0.Fill(resf0);

                delete hData;
                delete LLinPEXforFNegValueArray.second;
            } else {
                for (; sigItr != signal_samples.end(); sigItr++) {
                    //            cout<< "..." << sigItr->first<< "..." <<endl;
                    TH2* tmp1 = (TH2*) sigItr->second->GeneratePartialSampleLumiEQ(nPEXPull);
                    TH1* tmp = tmp1->ProjectionY("tmp");
                    hData->Add(tmp);
                    delete tmp1;
                    delete tmp;
                }
#ifndef TEST_DILEPTON_JEANNINE 
                std::pair<TF3, LikelihoodFunction*> LLinPEXforFNegValueArray = LikelihoodFunction::getLLFunctionGeneralized(
                        string("F_" + name__.str()), bkg, hData, signalIID);
#endif /*TEST_DILEPTON_JEANNINE*/
#ifdef TEST_DILEPTON_JEANNINE 
                std::pair<TF3, LikelihoodFunction*> LLinPEXforFNegValueArray = LikelihoodFunction::getLLFunctionGeneralized(
                        string("F_" + name__.str()), bkgTmpDilep, hData, tmpVec2DDiLep);
#endif /*TEST_DILEPTON_JEANNINE*/
                TF3 LLinPEXforFNegValue = LLinPEXforFNegValueArray.first;
                double x[3] = {-1., -1., -1.};
                double xerr[3] = {-1., -1., -1.};
                double correlation12 = -1000;
                GetMinimum(LLinPEXforFNegValue, x, xerr, correlation12);
                double fneg = x[1];
                double f0 = x[0];
                double fpos = 1.0 - x[1] - x[0];

                double fresponse = x[2];
                double errfrespo = xerr[2];
                double resfresp0 = fresponse - 1.0;

                hPullFResp.Fill((double) resfresp0 / (double) errfrespo);
                hResFResp.Fill(resfresp0);

                double errfneg = xerr[1];
                double errf0 = xerr[0];
                double errfpos = sqrt(errf0 * errf0 + errfneg * errfneg + (2 * correlation12));

                double resneg = fneg - (3.03734e-01);
                double respos = fpos - FposFixed;
                double resf0 = f0 - (6.64263e-01);

                hPullFNeg.Fill((double) resneg / (double) errfneg);
                hPullF0.Fill((double) resf0 / (double) errf0);
                hPullFPos.Fill((double) respos / (double) errfpos);

                hResFPos.Fill(respos);
                hResFNeg.Fill(resneg);
                hResF0.Fill(resf0);

                delete hData;
                delete LLinPEXforFNegValueArray.second;
            }
        }
        delete WtbWeightor.second;
        TFile * outFile = new TFile(outName.str().c_str(), "recreate");
        outFile->cd();
        hFinalF0.Write();
        hFinalFNeg.Write();
        hFinalFPos.Write();
        hPullFNeg.Write();
        hPullF0.Write();
        hPullFPos.Write();
        hPullFResp.Write();
        hResFNeg.Write();
        hResF0.Write();
        hResFPos.Write();
        hResFResp.Write();
        std::map<string, DistributionProducerFromSelected*>::iterator bkgItr = bkg_samples.begin();
        for (; bkgItr != bkg_samples.end(); bkgItr++) 
		bkgItr->second->WriteChecks(outFile);
        outFile->Close();
    }
#endif	/* VALIDATOREXECUTER_H */

