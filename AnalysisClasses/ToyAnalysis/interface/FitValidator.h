/* 
 * File:   FitValidator.h
 * Author: nadjieh
 *
 * Created on May 3, 2012, 11:02 AM
 */

#ifndef FITVALIDATOR_H
#define	FITVALIDATOR_H

//#define TEST
#include "TF1.h"
#include "TF3.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include "TMath.h"
#include "TCanvas.h"
#include "TRandom1.h"
#include "TRandom.h"
#include "TROOT.h"
#include "TVirtualFitter.h"
#include <string>
#include <iostream>
#include <sstream>
#include <map>
#include <vector>
#include "ToyFitter.h"

using namespace std;

TRandom SeedGenerator = TRandom(1928374);
TRandom SeedGeneratorLumiEQ = TRandom(874546620);

class SamplesInfo {
public:

    SamplesInfo() {
        Xsections["t"] = 41.9; //0
        Xsections["tbar"] = 22.6; //1
        //        Xsections["tW"] = 7.9; //2
        //        Xsections["tWbar"] = 7.9; //3
        Xsections["tWHadMu"] = (0.58 * 2); //2
        Xsections["tWbarHadMu"] = (0.58 * 2); //3
        Xsections["tWEMu"] = (0.097 * 2); //2
        Xsections["tWbarEMu"] = (0.097 * 2); //3
        Xsections["tWTauMu"] = (0.097 * 2); //2
        Xsections["tWbarTauMu"] = (0.097 * 2); //3
        Xsections["tWRest"] = (7.3 * 2); //2
        Xsections["tWbarRest"] = (7.3 * 2); //3

        //        Xsections["tt"] = 165; //4
        Xsections["ttdimu"] = 2.04; //4
        Xsections["ttmue"] = 4.07; //4
        Xsections["ttmutau"] = 4.07; //4
        //        Xsections["ttmuhad"] = 24.4; //4
        //        Xsections["ttrest"] = 130.42; //4
        /*
         * for dilepton study
         */
        //        Xsections["dimu"] = 2.04; //4
        //        Xsections["mue"] = 4.07; //4
        //        Xsections["mutau"] = 4.07; //4
        Xsections["ttothers"] = 154.82; //4
        //        Xsections["othersDiLepTau"] = 158.89; //4
        Xsections["s"] = 3.19; //5
        Xsections["sbar"] = 1.44; //6
        Xsections["w"] = 31314; //7
        Xsections["dy"] = 3048; //8
        //        Xsections["qcd"] = 84679; //9
        N0["t"] = 3915598;
        N0["tbar"] = 1711403;
        N0["tW"] = 497658;
        N0["tWbar"] = 493460;
        //        N0["tWHadMu"] = 60232; //2
        //        N0["tWbarHadMu"] = 51071; //3
        //        N0["tWEMu"] = 10039; //2
        //        N0["tWbarEMu"] = 8512; //3
        //        N0["tWTauMu"] = 10039; //2
        //        N0["tWbarTauMu"] = 8512; //3
        //        N0["tWRest"] = 793056; //2
        //        N0["tWbarRest"] = 621367; //3
        //        N0["tt"] = 3698723;
        N0["ttdimu"] = 45663;
        N0["ttmue"] = 91326;
        N0["ttmutau"] = 91326;
        //        N0["ttmuhad"] = 546944;
        //        N0["ttrest"] = 2923463;
        /*
         * for dilepton study
         */
        //        N0["dimu"] = 45663;
        //        N0["mue"] = 91326;
        //        N0["mutau"] = 91326;
        N0["ttothers"] = 3470408;
        //        N0["othersDiLepTau"] = 3470408 + 91326;
        N0["s"] = 3932710;
        N0["sbar"] = 1999667;
        N0["w"] = 75748221;
        N0["dy"] = 30459503;
        //        N0["qcd"] = 25026537;

        NSelected["t"] = 35223;
        NSelected["tbar"] = 19903;
        NSelected["tW"] = 7016;
        NSelected["tWbar"] = 5980;
        NSelected["tWHadMu"] = 2761; //2
        NSelected["tWbarHadMu"] = 2365; //3
        NSelected["tWEMu"] = 181; //2
        NSelected["tWbarEMu"] = 144; //3
        NSelected["tWTauMu"] = 640; //2
        NSelected["tWbarTauMu"] = 502; //3
        NSelected["tWRest"] = 3434; //2
        NSelected["tWbarRest"] = 2969; //3
        //        NSelected["tt"] = 17068;
        NSelected["ttdimu"] = 1450;
        NSelected["ttmue"] = 1506;
        NSelected["ttmutau"] = 4898;
        //        NSelected["ttmuhad"] = 8464;
        //        NSelected["ttrest"] = 750;
        /*
         * for dilepton study
         */
        //        NSelected["dimu"] = 1450;
        //        NSelected["mue"] = 1506;
        //        NSelected["mutau"] = 4898;
        NSelected["ttothers"] = 9214;
        //        NSelected["othersDiLepTau"] = (9214 + 4898);
        NSelected["s"] = 2503;
        NSelected["sbar"] = 1414;
        NSelected["w"] = 4196;
        NSelected["dy"] = 1873;
        //        NSelected["qcd"] = 24;
/*
        NHt["t"] = 31180;
        NHt["tbar"] = 17232;
        NHt["tW"] = 6416;
        NHt["tWbar"] = 5468;
        NHt["tt"] = 16225;
        NHt["s"] = 1186;
        NHt["sbar"] = 1242;
        NHt["w"] = 2995;
        NHt["dy"] = 1112;
        NHt["qcd"] = 7;

        NFwdEta["t"] = 27003;
        NFwdEta["tbar"] = 14398;
        NFwdEta["tW"] = 2309;
        NFwdEta["tWbar"] = 2022;
        NFwdEta["tt"] = 5796;
        NFwdEta["s"] = 2209;
        NFwdEta["sbar"] = 619;
        NFwdEta["w"] = 2043;
        NFwdEta["dy"] = 924;
        NFwdEta["qcd"] = 12;
  */
    }

    ~SamplesInfo() {
    };

    std::map<string, double> Xsections; //pb
    std::map<string, double> N0;
    std::map<string, double> NSelected;

    //    std::map<string, double> NHt;
    //    std::map<string, double> NFwdEta;


};

//CHECK for max_size

class DistributionProducerFromSelected {
public:
    TH1D * hMeanDiff;
    TH1D * hSigmaDiff;
    TH1D * hSkewDiff;
    TH1D * hNDiff;

    DistributionProducerFromSelected(TH1* hSelected, string MCName, double lumi, bool is2D = false,
            bool is3D = false) :
    hInput(hSelected), mcName(MCName), Lumi(lumi), isTwoD(is2D), isThreeD(is3D) {
        gROOT->cd();
        hMeanDiff = new TH1D(string(MCName + "_MeanDiff").c_str(), string(MCName + "_MeanDiff").c_str(), 400, -2., 2.);
        hSigmaDiff = new TH1D(string(MCName + "_SigmaDiff").c_str(), string(MCName + "_SigmaDiff").c_str(), 400, -2., 2.);
        hSkewDiff = new TH1D(string(MCName + "_SkewDiff").c_str(), string(MCName + "_SkewDiff").c_str(), 400, -2., 2.);
        hNDiff = new TH1D(string(MCName + "_NDiff").c_str(), string(MCName + "_NDiff").c_str(), 400, -2., 2.);

        TRandom RandomGenerator(SeedGenerator.Integer(10000000));
        if (!isTwoD && !isThreeD) {
            for (int iBin = 0; iBin < hSelected->GetXaxis()->GetNbins(); iBin++) {
                double cosTheta = hSelected->GetBinCenter(iBin + 1);
                //            double cosTheta = hSelected->GetBinCenter(iBin);
                //            cout<<"cosTheta is "<<cosTheta<<endl;
                //            cout<<"BinContents of "<<iBin<<" is "<<hSelected->GetBinContent( iBin+1 )<<endl;
                for (int eventID = 0; eventID < hSelected->GetBinContent(iBin + 1); eventID++) {
                    int evtRndId = RandomGenerator.Integer(1000000000);
                    while (sampleContent.count(evtRndId) > 0) {
                        evtRndId = RandomGenerator.Integer(1000000000);
                    }
                    sampleContent[evtRndId] = cosTheta;
                }
            }
        } else if (isTwoD && !isThreeD) {
            for (int iBin = 0; iBin < hSelected->GetXaxis()->GetNbins(); iBin++) {
                double cosThetaGen = hSelected->GetBinCenter(iBin + 1);
                for (int jBin = 0; jBin < hSelected->GetYaxis()->GetNbins(); jBin++) {
                    double cosThetaRec = hSelected->GetBinCenter(jBin + 1);
                    //            double cosTheta = hSelected->GetBinCenter(iBin);
                    //            cout<<"cosTheta is "<<cosTheta<<endl;
                    //                    cout<<"In bin "<<iBin<<" gen: genCosTheta: "<<cosThetaGen<<", reco CosTheta: "<<cosThetaRec
                    //                            <<", Entries: "<<hSelected->GetBinContent(iBin + 1, jBin + 1)<<endl;
                    for (int eventID = 0; eventID < hSelected->GetBinContent(iBin + 1, jBin + 1); eventID++) {
                        int evtRndId = RandomGenerator.Integer(1000000000);
                        while (sampleContent.count(evtRndId) > 0) {
                            evtRndId = RandomGenerator.Integer(1000000000);
                        }
                        sampleContent[evtRndId] = cosThetaRec;
                        sampleContentGen[evtRndId] = cosThetaGen;
                    }
                }
            }
        } else if (!isTwoD && isThreeD) {
            for (int iBin = 0; iBin < hSelected->GetXaxis()->GetNbins(); iBin++) {
                double cosThetaGen = hSelected->GetBinCenter(iBin + 1);
                for (int jBin = 0; jBin < hSelected->GetYaxis()->GetNbins(); jBin++) {
                    double cosThetaRec = hSelected->GetBinCenter(jBin + 1);
                    for (int kBin = 0; kBin < hSelected->GetZaxis()->GetNbins(); kBin++) {
                        double cosThetaBias = hSelected->GetBinCenter(kBin + 1);
                        for (int eventID = 0; eventID < hSelected->GetBinContent(iBin + 1, jBin + 1, kBin + 1); eventID++) {
                            int evtRndId = RandomGenerator.Integer(1000000000);
                            while (sampleContent.count(evtRndId) > 0) {
                                evtRndId = RandomGenerator.Integer(1000000000);
                            }
                            sampleContent[evtRndId] = cosThetaRec;
                            sampleContentGen[evtRndId] = cosThetaGen;
                            sampleContentBias[evtRndId] = cosThetaBias;
                        }
                    }
                }
            }
        }
#ifdef TEST
        TH1* h2 = (TH1*) hSelected->Clone(string("second_" + string(hSelected->GetName())).c_str());
        std::map<int, double>::iterator tmpItr = sampleContent.begin();
        cout << "***** " << mcName << endl;
        for (; tmpItr != sampleContent.end(); tmpItr++)
            h2->Fill(tmpItr->second);
        TFile * test = new TFile(string(mcName + "_test.root").c_str(), "recreate");
        test->cd();
        hSelected->Write();
        h2->Write();
        test->Close();
#endif /*TEST*/
        SamplesInfo mySampleInfo;
        Xsec = mySampleInfo.Xsections[MCName];
        N0 = (int) mySampleInfo.N0[MCName];
        //        selEff = (double)mySampleInfo.NSelected[MCName]/(double)N0;
        selEff = (double) (hInput->GetEntries()) / (double) N0;
    }

    ~DistributionProducerFromSelected() {
    }

    TH1* GeneratePartialSample(double fraction, int nPEX) {
        TRandom RandomGenerator(SeedGenerator.Integer(10000000));
        std::vector<int> selectedValues;
        std::map<int, double>::iterator evtIter = sampleContent.begin();
        for (; evtIter != sampleContent.end(); evtIter++) {
            if (RandomGenerator.Uniform() < fraction)
                selectedValues.push_back(evtIter->first);
        }
        //        cout<<"------------ "<<selectedValues.size()<<endl;
        //        cout<<"------------ "<<selectedValues.at(0)<<endl;
        //        cout<<"------------ "<<selectedValues.at(1)<<endl;
        double Weight = 0.0;
        if (selectedValues.size() != 0) {
            Weight = (double) (Lumi * Xsec) / (double) (fraction * N0);
            //            cout<<"Weight: "<<Weight<<endl;
        }
        stringstream s;
        s << mcName << "_" << hInput->GetName() << "_" << nPEX;
        string hName = s.str();
        s.str("");
        s << mcName << "_" << hInput->GetTitle() << "_" << nPEX;
        string hTitle = s.str();
        gROOT->cd();
        TH1* hRet = 0;
        if (!isTwoD && !isThreeD) {
            hRet = new TH1D(hName.c_str(), hTitle.c_str(), hInput->GetXaxis()->GetNbins()
                    , hInput->GetXaxis()->GetXmin(), hInput->GetXaxis()->GetXmax());
            hRet->Sumw2();
            for (unsigned int i = 0; i < selectedValues.size(); i++)
                hRet->Fill(sampleContent[selectedValues.at(i)], Weight);
            hMeanDiff->Fill(hInput->GetMean() - hRet->GetMean());
            hSigmaDiff->Fill(hInput->GetRMS() - hRet->GetRMS());
            hSkewDiff->Fill(hInput->GetSkewness() - hRet->GetSkewness());
            hNDiff->Fill(((double) hInput->GetEntries() - ((double) hRet->GetEntries() / fraction)) / (double) hInput->GetEntries());

        } else if (isTwoD && !isThreeD) {
            hRet = new TH2D(hName.c_str(), hTitle.c_str(), hInput->GetXaxis()->GetNbins()
                    , hInput->GetXaxis()->GetXmin(), hInput->GetXaxis()->GetXmax(),
                    hInput->GetYaxis()->GetNbins(), hInput->GetYaxis()->GetXmin(),
                    hInput->GetYaxis()->GetXmax());
            hRet->Sumw2();
            for (unsigned int i = 0; i < selectedValues.size(); i++)
                ((TH2*) hRet)->Fill(sampleContentGen[selectedValues.at(i)],
                    sampleContent[selectedValues.at(i)], Weight);

        } else if (!isTwoD && isThreeD) {
            hRet = new TH3D(hName.c_str(), hTitle.c_str(), hInput->GetXaxis()->GetNbins()
                    , hInput->GetXaxis()->GetXmin(), hInput->GetXaxis()->GetXmax(),
                    hInput->GetYaxis()->GetNbins(), hInput->GetYaxis()->GetXmin(),
                    hInput->GetYaxis()->GetXmax(), hInput->GetZaxis()->GetNbins(),
                    hInput->GetZaxis()->GetXmin(), hInput->GetZaxis()->GetXmax());
            hRet->Sumw2();
            for (unsigned int i = 0; i < selectedValues.size(); i++)
                ((TH3*) hRet)->Fill(sampleContentGen[selectedValues.at(i)],
                    sampleContent[selectedValues.at(i)], sampleContentBias[selectedValues.at(i)], Weight);
        }
        return hRet;
    }

    void WriteChecks(TDirectory * d) {
        (d->mkdir(string(mcName + "_checks").c_str()))->cd();
        hMeanDiff->Write();
        hSigmaDiff->Write();
        hSkewDiff->Write();
        hNDiff->Write();
        d->cd();
    }

    TH1* GeneratePartialSampleLumiEQ(int nPEX) {
        TRandom RandomGenerator(SeedGeneratorLumiEQ.Integer(10000000));
        double nSelectedEventsInLumi_ = Lumi * Xsec*selEff;
        double nSelectedEventsInLumi = RandomGenerator.Gaus(nSelectedEventsInLumi_, sqrt(nSelectedEventsInLumi_));
        unsigned int EventIndices = sampleContent.size();
        std::vector<int> selectedValues;
        std::map<int, double>::iterator evtIter = sampleContent.begin();

        for (int nEvt = 0; nEvt < int(nSelectedEventsInLumi); nEvt++) {
            int EvtID = RandomGenerator.Integer(EventIndices);
            evtIter = sampleContent.begin();
            for (int i = 0; i < EvtID; i++)
                evtIter++;
            selectedValues.push_back(evtIter->first);
        }

        stringstream s;
        s << mcName << "_" << hInput->GetName() << "_" << nPEX;
        string hName = s.str();
        s.str("");
        s << mcName << "_" << hInput->GetTitle() << "_" << nPEX;
        string hTitle = s.str();
        gROOT->cd();
        TH1* hRet = 0;
        if (!isTwoD && !isThreeD) {
            hRet = new TH1D(hName.c_str(), hTitle.c_str(), hInput->GetXaxis()->GetNbins()
                    , hInput->GetXaxis()->GetXmin(), hInput->GetXaxis()->GetXmax());
            hRet->Sumw2();
            for (unsigned int i = 0; i < selectedValues.size(); i++)
                hRet->Fill(sampleContent[selectedValues.at(i)]);
        } else if (isTwoD && !isThreeD) {
            hRet = new TH2D(hName.c_str(), hTitle.c_str(), hInput->GetXaxis()->GetNbins()
                    , hInput->GetXaxis()->GetXmin(), hInput->GetXaxis()->GetXmax(),
                    hInput->GetYaxis()->GetNbins(), hInput->GetYaxis()->GetXmin(),
                    hInput->GetYaxis()->GetXmax());
            hRet->Sumw2();
            for (unsigned int i = 0; i < selectedValues.size(); i++)
                hRet->Fill(sampleContentGen[selectedValues.at(i)], sampleContent[selectedValues.at(i)]);
        } else if (!isTwoD && isThreeD) {
            hRet = new TH3D(hName.c_str(), hTitle.c_str(), hInput->GetXaxis()->GetNbins()
                    , hInput->GetXaxis()->GetXmin(), hInput->GetXaxis()->GetXmax(),
                    hInput->GetYaxis()->GetNbins(), hInput->GetYaxis()->GetXmin(),
                    hInput->GetYaxis()->GetXmax(), hInput->GetZaxis()->GetNbins(),
                    hInput->GetZaxis()->GetXmin(), hInput->GetZaxis()->GetXmax());
            hRet->Sumw2();
            for (unsigned int i = 0; i < selectedValues.size(); i++)
                ((TH3D*) hRet)->Fill(sampleContentGen[selectedValues.at(i)], sampleContent[selectedValues.at(i)],
                    sampleContentBias[selectedValues.at(i)]);
        }
        return hRet;
    }
private:
    TH1* hInput;
    string mcName;
    double Lumi;
    std::map<int, double> sampleContent;
    std::map<int, double> sampleContentGen;
    std::map<int, double> sampleContentBias;
    double Xsec;
    int N0;
    double selEff;
    bool isTwoD;
    bool isThreeD;

};

bool isDesiredSample(std::string sampleName, std::string characters) {
    int position = sampleName.find(characters);
    cout << "position: " << position << "\t" << sampleName << endl;
    return (position > 0 && position < (int) sampleName.size());
}

TH3 * Make3DRandom(TH2 * input, TF1 * f) {

    stringstream s;
    TH3D * output = new TH3D(string(string(input->GetName()) + "_3D").c_str(),
            string(string(input->GetTitle()) + "_3D").c_str(), input->GetXaxis()->GetNbins(), input->GetXaxis()->GetXmin(),
            input->GetXaxis()->GetXmax(), input->GetYaxis()->GetNbins(), input->GetYaxis()->GetXmin(),
            input->GetYaxis()->GetXmax(), input->GetXaxis()->GetNbins(), input->GetXaxis()->GetXmin(),
            input->GetXaxis()->GetXmax());
    cout << f->GetName() << endl;
    cout << f->GetParameter(0) << endl;
    cout << f->GetParameter(1) << endl;
    for (int iBin = 0; iBin < input->GetXaxis()->GetNbins(); iBin++) {
        for (int jBin = 0; jBin < input->GetYaxis()->GetNbins(); jBin++) {
            int n = input->GetBinContent(iBin + 1, jBin + 1);
            //            cout<<"BinX: "<<iBin+1<<"\tBinY: "<<jBin+1<<"\n\tContent: "<<n<<endl;
            s.str("");
            s << input->GetName() << "_" << iBin << "_" << jBin;
            //            TH1 * h1D = new TH1D(s.str().c_str(), s.str().c_str(), input->GetXaxis()->GetNbins(), input->GetXaxis()->GetXmin(),
            //                    input->GetXaxis()->GetXmax());
            TH1 * h1D = new TH1D(s.str().c_str(), s.str().c_str(), 1000, input->GetXaxis()->GetXmin(),
                    input->GetXaxis()->GetXmax());
            h1D->FillRandom(f->GetName(), n);
            //            h1D->Scale((double)n/(double)h1D->Integral());
            //            cout<<"\tkContent: "<<h1D->Integral()<<endl;
            for (int kBin = 0; kBin < h1D->GetXaxis()->GetNbins(); kBin++) {
                output->SetBinContent(iBin + 1, jBin + 1, kBin + 1, h1D->GetBinContent(kBin + 1));
            }
        }
    }
    return output;
}
#endif	/* FITVALIDATOR_H */

