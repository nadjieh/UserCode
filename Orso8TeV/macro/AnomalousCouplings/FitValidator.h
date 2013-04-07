/* 
 * File:   FitValidator.h
 * Author: nadjieh
 *
 * Created on May 3, 2012, 11:02 AM
 */

#ifndef FITVALIDATOR_H
#define	FITVALIDATOR_H

//#define TEST
#define mtop 172.5
#define MW 80.39
#define mB 4.8
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

bool isAC(string s) {
    return (s == string("r") || s == string("sm") || s == string("unphys"));
}

class SamplesInfo {
public:

    SamplesInfo() {
        Xsections["sm"] = 9.4206722625; //0
        Xsections["unphys"] = 9.4206722625; //1
        Xsections["r"] = 9.4206722625; //2
        Xsections["t"] = 9.4206722625; //0
        /*Xsections["t"] = 17.496; //0
        Xsections["tbar"] = 9.9468; //1
        Xsections["tW"] = 11.1; //2
        Xsections["tWbar"] = 11.1; //3
        Xsections["ttdimu"] = 2.73; //4
        Xsections["ttmue"] = 5.46; //4
        Xsections["ttmutau"] = 5.46; //4
        Xsections["ttmuhad"] = 34.16; //4
        Xsections["ttrest"] = 68.3; //4
        Xsections["ttrestdilep"] = 10.917; //4
        Xsections["s"] = 1.23; //5
        Xsections["sbar"] = 0.57; //6
        Xsections["w"] = 36257; //7
        Xsections["dy"] = 3503; //8
        Xsections["AC"] = 1; //8*/
        N0["sm"] = 305295; //0
        N0["unphys"] = 375847; //1
        N0["r"] = 277183; //2
        N0["t"] = 305295;
        /*N0["t"] = 3915598;
        N0["tbar"] = 1711403;
        N0["tW"] = 497658;
        N0["tWbar"] = 493460;
        N0["ttdimu"] = 471827; 
        N0["ttmue"] = 943654;
        N0["ttmutau"] = 943654;
        N0["ttmuhad"] = 3743301;
        N0["ttrestdilep"] = 1887308;
        N0["ttrest"] = 7486601;
        N0["s"] = 3932710;
        N0["sbar"] = 1999667;
        N0["w"] = 75748221;
        N0["dy"] = 30459503;
        N0["AC"] = 1;*/
        NSelected["sm"] = 7237;
        NSelected["unphys"] = 6815;
        NSelected["r"] = 10453;
        NSelected["t"] = 7237;
        /*NSelected["dy"] = 224;
        NSelected["sbar"] = 15943;
        NSelected["s"] = 30911;
        NSelected["tbar"] = 13291;
        NSelected["t"] = 32526;
        NSelected["ttdimu"] = 6323;
        NSelected["ttmue"] = 10802;
        NSelected["ttmuhad"] = 59163;
        NSelected["ttmutau"] = 25217;
        NSelected["ttrestdilep"] = 1230;
        NSelected["ttrest"] = 1061;
        NSelected["tWbar"] = 1676;
        NSelected["tW"] = 1700;
        NSelected["w"] = 693;
        NSelected["AC"] = 1;*/
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

    TH1* GeneratePartialSampleLumiEQ(int nPEX, bool isDitop = false) {
        cout << "In EQ RGen" << endl;
        TRandom RandomGenerator(SeedGeneratorLumiEQ.Integer(10000000));
        cout << Lumi << "\t" << Xsec << "\t" << selEff << endl;
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
        cout << "ret declared: " << isTwoD << "\t" << isThreeD << endl;
        if (!isTwoD && !isThreeD) {
            hRet = new TH1D(hName.c_str(), hTitle.c_str(), hInput->GetXaxis()->GetNbins()
                    , hInput->GetXaxis()->GetXmin(), hInput->GetXaxis()->GetXmax());
            hRet->Sumw2();
            for (unsigned int i = 0; i < selectedValues.size(); i++)
                hRet->Fill(sampleContent[selectedValues.at(i)]);
            cout<<"Ret Res: "<<endl;
            cout<<hRet->GetEntries()<<endl;
        } else if (isTwoD && !isThreeD) {
            hRet = new TH2D(hName.c_str(), hTitle.c_str(), hInput->GetXaxis()->GetNbins()
                    , hInput->GetXaxis()->GetXmin(), hInput->GetXaxis()->GetXmax(),
                    hInput->GetYaxis()->GetNbins(), hInput->GetYaxis()->GetXmin(),
                    hInput->GetYaxis()->GetXmax());
            hRet->Sumw2();
            for (unsigned int i = 0; i < selectedValues.size(); i++)
                hRet->Fill(sampleContentGen[selectedValues.at(i)], sampleContent[selectedValues.at(i)]);
        } else if (!isTwoD && isThreeD) {
            cout << "In EQ: right place!" << endl;
            if (isDitop) {
                hRet = new TH3D(hName.c_str(), hTitle.c_str(), hInput->GetXaxis()->GetNbins()
                        , hInput->GetXaxis()->GetXmin(), hInput->GetXaxis()->GetXmax(),
                        hInput->GetYaxis()->GetNbins(), hInput->GetYaxis()->GetXmin(),
                        hInput->GetYaxis()->GetXmax(), hInput->GetZaxis()->GetNbins(),
                        hInput->GetZaxis()->GetXmin(), hInput->GetZaxis()->GetXmax());
                hRet->Sumw2();
                cout << "ditop: hRet has Value " << hRet->GetName() << "\t" << hRet->ClassName() << endl;
                for (unsigned int i = 0; i < selectedValues.size(); i++) {
                    /*	    cout<<"selectedValues.at(i): "<<selectedValues.at(i)<<endl;
                                cout<<"sampleContentGen[selectedValues.at(i)]: "<<sampleContentGen[selectedValues.at(i)]<<endl;
                                cout<<"sampleContent[selectedValues.at(i)]: "<<sampleContent[selectedValues.at(i)]<<endl;
                                cout<<"sampleContentBias[selectedValues.at(i)]: "<<sampleContentBias[selectedValues.at(i)]<<endl;*/
                    ((TH3D*) hRet)->Fill(sampleContentGen[selectedValues.at(i)], sampleContent[selectedValues.at(i)],
                            sampleContentBias[selectedValues.at(i)]);
                }
                cout << "Filling is done" << endl;
            } else {
                hRet = new TH2D(hName.c_str(), hTitle.c_str(), hInput->GetXaxis()->GetNbins()
                        , hInput->GetXaxis()->GetXmin(), hInput->GetXaxis()->GetXmax(),
                        hInput->GetYaxis()->GetNbins(), hInput->GetYaxis()->GetXmin(),
                        hInput->GetYaxis()->GetXmax());
                hRet->Sumw2();
                cout << "not ditop: hRet has Value" << endl;
                for (unsigned int i = 0; i < selectedValues.size(); i++)
                    hRet->Fill(sampleContentGen[selectedValues.at(i)], sampleContent[selectedValues.at(i)]);
            }
        }
        cout << "Lets return!" << endl;
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

struct Coefficients {
    double m;
    double n;
    double k;
};

double MojtabaWidth(double VL, double VR, double gL, double gR, double mt = mtop, double mW = MW/*, double mb = 4.8*/) {
    double r = mt / mW;
    const double Gf = 1.166364 * pow(10., -5);
    double massTerm = mt * pow(mW, 2.);
    const double OtherCoeffs = pow((8 * sqrt(2) * TMath::Pi()), -1);
    double r2 = pow(r, 2);
    double r4 = pow(r, 4);
    double coeff1 = Gf * pow((r2 - 1), 2) * pow(r4, -1) * massTerm * OtherCoeffs;
    double t1 = (r2 + 2)*(pow(VL, 2) + pow(VR, 2));
    double t2 = (2 * r2 + 1)*(pow(gL, 2) + pow(gR, 2));
    double t3 = 6 * r * (VL * gR + VR * gL);
    return (coeff1 * (t1 + t2 + t3));
}

Coefficients VLVRCoeffs(double VL, double VR, double SF = 1, double mt = mtop, double mW = MW/*, double mb = 4.8*/) {
    const double VlVRConst = 1.49 * SF;
    Coefficients ret;
    ret.m = pow(VL, 4) * pow(MojtabaWidth(VL, VR, 0, 0, mt, mW), -1) * VlVRConst; //SM
    ret.n = pow(VL, 2) * pow(VR, 2) * pow(MojtabaWidth(VL, VR, 0, 0, mt, mW), -1) * VlVRConst; //Unphys
    ret.k = pow(VR, 4) * pow(MojtabaWidth(VL, VR, 0, 0, mt, mW), -1) * VlVRConst; //r
    return ret;
}

double q(double mt, double mw, double mb) {
    return (1. / (2 * mt))*sqrt((pow(mt, 4) + pow(mw, 4) + pow(mb, 4))-(2 * pow((mt * mw), 2) + 2 * pow((mt * mb), 2) + 2 * pow((mb * mw), 2)));
}

double Gamma(double * x, double * par) {
    /*
     * x[0]: VL
     * x[1]: VR
     * x[2]: gL
     * x[3]: gR

     * par[0]: mt
     * par[1]: mW
     * par[2]: mb
     */
    double xb = (double) par[2] / (double) par[0];
    double xW = (double) par[1] / (double) par[0];
    double xW2 = pow(xW, 2);
    double xb2 = pow(xb, 2);
    double xW4 = pow(xW2, 2);
    double xb4 = pow(xb2, 2);
    //double q = q(par[0],par[1],par[2]);
    double t1 = (pow(x[0], 2) + pow(x[1], 2))*(1 + xW2 - 2 * xb2 - 2 * xW4 + xW2 * xb2 + xb4);
    double t2 = (12 * xW2 * xb * x[0] * x[1]);
    double t3 = 2 * (pow(x[2], 2) + pow(x[3], 2)) * (1 - (xW2 / 2.) - 2 * xb2 - (xW4 / 2.) - (xW2 * xb2 / 2.) + xb4);
    double t4 = (12 * xW2 * xb * x[2] * x[3]);
    double t5 = 6 * xW * (x[0] * x[3] + x[1] * x[2]) * (1 - xW2 - xb2);
    double t6 = 6 * xW * (x[0] * x[2] + x[1] * x[3]) * (1 + xW2 - xb2);
    return (pow(xW2, -1)*(t1 - t2 + t3 - t4 - t5 + t6));
}

double GammaZero(double * x, double * par) {
    /*
     * x[0]: VL
     * x[1]: VR
     * x[2]: gL
     * x[3]: gR

     * par[0]: mt
     * par[1]: mW
     * par[2]: mb
     */
    double xb = (double) par[2] / (double) par[0];
    double xW = (double) par[1] / (double) par[0];
    double xW2 = pow(xW, 2);
    double xb2 = pow(xb, 2);
    //	double xW4 = pow(xW2,2);
    double xb4 = pow(xb2, 2);
    //double q = q(par[0],par[1],par[2]);
    double t1 = pow(xW2, -1) * (pow(x[0], 2) + pow(x[1], 2))*(1 - xW2 - 2 * xb2 - xW2 * xb2 + xb4);
    double t2 = 4 * xb * x[0] * x[1];
    double t3 = (pow(x[2], 2) + pow(x[3], 2)) * (1 - xW2 + xb2);
    double t4 = 4 * xb * x[2] * x[3];
    double t5 = (2 * pow(xW, -1) * (x[0] * x[3] + x[1] * x[2]) * (1 - xW2 - xb2));
    double t6 = 2 * pow(xW, -1) * xb * (x[1] * x[3] + x[0] * x[2]) * (1 + xW2 - xb2);
    return (t1 - t2 + t3 - t4 - t5 + t6);
}

double commonTerm(double * x, double * par) {
    /*
     * x[0]: VL
     * x[1]: VR
     * x[2]: gL
     * x[3]: gR

     * par[0]: mt
     * par[1]: mW
     * par[2]: mb
     */
    double xb = (double) par[2] / (double) par[0];
    double xW = (double) par[1] / (double) par[0];
    double xW2 = pow(xW, 2);
    double xb2 = pow(xb, 2);
    double xW4 = pow(xW2, 2);
    double xb4 = pow(xb2, 2);
    double Q = q(par[0], par[1], par[2]);
    double coeff1 = 0.5 * pow(Q, -1) * par[0] * pow(xW2, -1);
    double coeff2 = 1 - 2 * xW2 - 2 * xb2 + xW4 - 2 * xW2 * xb2 + xb4;
    double t1 = -1 * xW2 * (pow(x[0], 2) - pow(x[1], 2));
    double t2 = (pow(x[2], 2) - pow(x[3], 2)) * (1 - xb2);
    double t3 = 2 * xW * (x[0] * x[3] - x[1] * x[2]);
    double t4 = 2 * xW * xb * (x[0] * x[1] - x[3] * x[2]);
    return (coeff1 * coeff2 * (t1 + t2 + t3 + t4));
}

double GammaT(double * x, double * par) {
    /*
     * x[0]: VL
     * x[1]: VR
     * x[2]: gL
     * x[3]: gR

     * par[0]: mt
     * par[1]: mW
     * par[2]: mb
     */
    double xb = (double) par[2] / (double) par[0];
    double xW = (double) par[1] / (double) par[0];
    double xW2 = pow(xW, 2);
    double xb2 = pow(xb, 2);
    //	double xW4 = pow(xW2,2);
    double xb4 = pow(xb2, 2);
    //double q = q(par[0],par[1],par[2]);
    double t1 = (pow(x[0], 2) + pow(x[1], 2)) * (1 - xW2 + xb2);
    double t2 = 4 * xb * x[0] * x[1];
    double t3 = pow(xW2, -1) * (pow(x[2], 2) + pow(x[3], 2))*(1 - xW2 - 2 * xb2 - xW2 * xb2 + xb4);
    double t4 = 4 * xb * x[2] * x[3];
    double t5 = 2 * pow(xW, -1) * (x[0] * x[3] + x[1] * x[2]) * (1 - xW2 - xb2);
    double t6 = 2 * pow(xW, -1) * xb * (x[1] * x[3] + x[0] * x[2]) * (1 + xW2 - xb2);
    return (t1 - t2 + t3 - t4 - t5 + t6);
}

double GammaL(double * x, double * par) {
    /*
     * x[0]: VL
     * x[1]: VR
     * x[2]: gL
     * x[3]: gR

     * par[0]: mt
     * par[1]: mW
     * par[2]: mb
     */

    double T = GammaT(x, par);
    double C = commonTerm(x, par);
    return T - C;
}

double GammaR(double * x, double * par) {
    /*
     * x[0]: VL
     * x[1]: VR
     * x[2]: gL
     * x[3]: gR

     * par[0]: mt
     * par[1]: mW
     * par[2]: mb
     */

    double T = GammaT(x, par);
    double C = commonTerm(x, par);
    return T + C;
}

double FZero(double * x, double * par) {
    double G0 = GammaZero(x, par);
    double G = Gamma(x, par);
    return G0 / G;
}

double FNeg(double * x, double * par) {
    double G = Gamma(x, par);
    double GL = GammaL(x, par);
    return GL / G;
}

double FR(double * x, double * par) {
    double G = Gamma(x, par);
    double GR = GammaR(x, par);
    return GR / G;
}

Coefficients GetFs(double VL, double VR, double gL, double gR, double mt = mtop, double mW = MW, double mb = mB) {
    double par[3] = {mt, mW, mb};
    double x[4] = {VL, VR, gL, gR};
    Coefficients ceof;
    ceof.m = FNeg(x, par);
    ceof.n = FZero(x, par);
    ceof.k = FR(x, par);
    //	cout<<"F0 = "<<FZero(x,par)<<endl;
    //	cout<<"FL = "<<FNeg(x,par)<<endl;
    //	cout<<"FR = "<<FR(x,par)<<endl;
    return ceof;
}
#endif	/* FITVALIDATOR_H */

