/* 
 * File:   WhelFitChiSquared.h
 * Author: nadjieh
 *
 * Created on February 22, 2013, 4:27 PM
 */

#ifndef WHELFITCHISQUARED_H
#define	WHELFITCHISQUARED_H
#include "UsefullStructsForCombination.h"
#include "../../ToyAnalysis/interface/ToyFitter.h"
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include "TROOT.h"
#include "TRandom.h"
#include "TFile.h"
#include "TCanvas.h"
using namespace std;

class ChiSquaredCaculatorAndPlotter {
public:
    //NOTE:

    /* Input:
     * Signal should contains only the reweighted part
     * WTemplate should be normalized
     */
    ChiSquaredCaculatorAndPlotter(string Name, std::vector<double> pars, WTempForCombination3D hists, double syst0, double systl) : name(Name),
    WeightFunc(WeightFunctionCreator::getWeightFunction("WeightFunc" + name, pars[0], pars[1])),
    WeightFuncUD(WeightFunctionCreator::getWeightFunction("WeightFuncUD" + name, pars[0] + syst0, pars[1] - systl)),
    WeightFuncDU(WeightFunctionCreator::getWeightFunction("WeightFuncDU" + name, pars[0] - syst0, pars[1] + systl)),
    F_0(pars[0]), F_L(pars[1]), rec_gen(pars[2]), nW(pars[3]) {

        ndf = hists.rest.data->GetXaxis()->GetNbins() - 4;

        cout << ndf << endl;

        systUD = this->Get2DRW(hists.rest.signalIID, 1);
        cout << "..... 3D size is ";
        cout << hists.rest.signalIIID.size() << endl;
        systUD->Add(this->Get3DRW(hists.rest.signalIIID, 1));
        cout << "systUD is made: ";
        cout << systUD->GetXaxis()->GetNbins() << endl;

        systDU = this->Get2DRW(hists.rest.signalIID, 2);
        systDU->Add(this->Get3DRW(hists.rest.signalIIID, 2));

        signal = this->GetSignal1D(hists.rest.signalIID, hists.rest.signalIIID, string("mySignal"));

        this->SetHistograms(hists);
        cout << "I am done with constructor " << this->name << endl;
    }

    virtual ~ChiSquaredCaculatorAndPlotter() {
    }

    double GetChiSquared() {
        double chi = 0;
        //        TH1* mySig = this->Get1DRW();
        //        TH1* UD = this->Get1DRW(1);
        //        TH1* DU = this->Get1DRW(2);
        for (int iBin = 0; iBin < input.data->GetXaxis()->GetNbins(); iBin++) {
            double nData = input.data->GetBinContent(iBin + 1);
            double eData = input.data->GetBinError(iBin + 1);
            double nMC = input.nonRWs->GetBinContent(iBin + 1) + input.signalID->GetBinContent(iBin + 1);
            double eMCUD = fabs(systUD->GetBinContent(iBin + 1) - signal->GetBinContent(iBin + 1));
            double eMCDU = fabs(systDU->GetBinContent(iBin + 1) - signal->GetBinContent(iBin + 1));
            //            double nMC = input.nonRWs->GetBinContent(iBin + 1) + mySig->GetBinContent(iBin + 1);
            //            double eMCUD = fabs(UD->GetBinContent(iBin + 1) - signal->GetBinContent(iBin + 1));
            //            double eMCDU = fabs(DU->GetBinContent(iBin + 1) - signal->GetBinContent(iBin + 1));
            double eMC = (eMCUD + eMCDU) / 2.;
            chi += (pow((nData - nMC), 2) / (pow(eData, 2) + pow(eMC, 2)));
        }
        return chi;
    }

    double GetNormalizedChiSquared() {
        return this->GetChiSquared() / (double) this->ndf;
    }

    TH1* GetBand() {
        TH1* res = (TH1*) input.signalID->Clone("forBand");
        res->Add(input.nonRWs);
        for (int iBin = 0; iBin < input.data->GetXaxis()->GetNbins(); iBin++) {
            double eMCUD = fabs(systUD->GetBinContent(iBin + 1) - signal->GetBinContent(iBin + 1));
            double eMCDU = fabs(systDU->GetBinContent(iBin + 1) - signal->GetBinContent(iBin + 1));
            double eMC = (eMCUD + eMCDU) / 2.;
            res->SetBinError(iBin + 1, eMC);
        }
        return res;
    }

    TH1* GetData()const {
        return input.data;
    }

    virtual void WriteInfo() {
        TH1* band = this->GetBand();
        TFile * f = new TFile(string(this->name + "_band.root").c_str(), "recreate");
        f->cd();
        band->Write();
        input.data->Write();
        f->Write();
        f->Close();
    }

    void PrintOut() {
        cout << "In " << this->name << " ======================================= " << endl;
        cout << "==========  " << F_0 << "\t" << F_L << endl;
        cout << "==========  " << rec_gen << "\t" << nW << endl;
        cout << "==========  " << ndf << endl;
        cout << "==========  nBins signal         : " << signal->GetXaxis()->GetNbins() << endl;
        cout << "==========  signal integral      : " << signal->Integral() << endl;
        cout << "==========  nBins signal RW      : " << input.signalID->GetXaxis()->GetNbins() << endl;
        cout << "==========  signalRW integral    : " << input.signalID->Integral() << endl;
        cout << "==========  nBins background     : " << input.nonRWs->GetXaxis()->GetNbins() << endl;
        cout << "==========  background integral  : " << input.nonRWs->Integral() << endl;
        cout << "==========  nBins data           : " << input.data->GetXaxis()->GetNbins() << endl;
        cout << "==========  data integral        : " << input.data->Integral() << endl;
        cout << "==========  nBins signal up      : " << systUD->GetXaxis()->GetNbins() << endl;
        cout << "==========  signal up integral   : " << systUD->Integral() << endl;
        cout << "==========  nBins signal down    : " << systDU->GetXaxis()->GetNbins() << endl;
        cout << "==========  signal down integral : " << systDU->Integral() << endl;
        cout << "======================================================= " << endl;
    }

    InputForCombination1D GetInput() const {
        return input;
    }

    TH1* GetSystUD() const {
        return systUD;
    }

    TH1* GetSystDU() const {
        return systDU;
    }

    TH1* GetSignalDef() const {
        return signal;
    }

    int GetNDF() const {
        return ndf;
    }
protected:
    string name;
    std::pair<TF1, WeightFunctionCreator*> WeightFunc;
    std::pair<TF1, WeightFunctionCreator*> WeightFuncUD;
    std::pair<TF1, WeightFunctionCreator*> WeightFuncDU;
    double F_0;
    double F_L;
    double rec_gen; //nW7
    double nW; //nW8
    InputForCombination1D input;
    int ndf;
    TH1* systUD; //0-L
    TH1* systDU; //0-L
    TH1* signal; //0-L

    void SetHistograms(WTempForCombination3D hists) {
        input.name = this->name;
        input.data = (TH1*) hists.rest.data->Clone(string(name + "_data").c_str());
        input.nonRWs = (TH1*) hists.rest.nonRWs->Clone(string(name + "_bkg").c_str());
        hists.Wtemplate->Scale(this->nW);
        input.nonRWs->Add(hists.Wtemplate);
        input.signalID = this->Get3DRW(hists.rest.signalIIID);
        input.signalID->Add(this->Get2DRW(hists.rest.signalIID));
    }

    TH1* Get3DRW(std::vector<TH3*> signals3D, int syst = 0) {
        gROOT->cd();
        cout << "nBins3: " << signals3D[0]->GetYaxis()->GetNbins() << endl;
        TH1* res = 0;
        if (syst == 0)
            res = new TH1D(string(this->name + "_res3D").c_str(), string(this->name + "_res3D").c_str(),
                signals3D[0]->GetYaxis()->GetNbins(), signals3D[0]->GetYaxis()->GetXmin(),
                signals3D[0]->GetYaxis()->GetXmax());
        else if (syst == 1)
            res = new TH1D(string(this->name + "_UDres3D").c_str(), string(this->name + "_UDres3D").c_str(),
                signals3D[0]->GetYaxis()->GetNbins(), signals3D[0]->GetYaxis()->GetXmin(),
                signals3D[0]->GetYaxis()->GetXmax());
        else if (syst == 2)
            res = new TH1D(string(this->name + "_DUres3D").c_str(), string(this->name + "_DUres3D").c_str(),
                signals3D[0]->GetYaxis()->GetNbins(), signals3D[0]->GetYaxis()->GetXmin(),
                signals3D[0]->GetYaxis()->GetXmax());
        TH1* biasH = 0;
        stringstream s;
        for (int bin = 1; bin < res->GetXaxis()->GetNbins() + 1; bin++) {
            double nSignal = 0;
            for (unsigned int p = 0; p < signals3D.size(); p++) {
                s.str("");
                s << this->name << p << "_pZ";
                TH1D * coefficients = new TH1D("coefficients", "coefficients",
                        signals3D.at(p)->GetXaxis()->GetNbins(), signals3D.at(p)->GetXaxis()->GetXmin(),
                        signals3D.at(p)->GetXaxis()->GetXmax());
                for (int genBin = 0; genBin < signals3D.at(p)->GetXaxis()->GetNbins(); genBin++) {
                    biasH = (TH1*) signals3D.at(p)->ProjectionZ(s.str().c_str(), genBin + 1, genBin + 1, bin, bin, "o");

                    if (syst == 0)
                        biasH->Multiply(&(WeightFunc.first), 1);
                    else if (syst == 1) //UD
                        biasH->Multiply(&(WeightFuncUD.first), 1);
                    else if (syst == 2) //DU
                        biasH->Multiply(&(WeightFuncDU.first), 1);

                    coefficients->SetBinContent(genBin + 1, biasH->Integral());
                    delete biasH;
                }

                if (syst == 0)
                    coefficients->Multiply(&(WeightFunc.first), this->rec_gen);
                else if (syst == 1) //UD
                    coefficients->Multiply(&(WeightFuncUD.first), this->rec_gen);
                else if (syst == 2) //DU
                    coefficients->Multiply(&(WeightFuncDU.first), this->rec_gen);

                nSignal += (coefficients->Integral());
                delete coefficients;
            }
            res->SetBinContent(bin, nSignal);
        }
        return res;
    }

    TH1* Get2DRW(std::vector<TH2*> signals2D, int syst = 0) {
        cout << "nBins2: " << signals2D[0]->GetYaxis()->GetNbins() << endl;
        TRandom r;
        TH1* res = 0;
        if (syst == 0)
            res = new TH1D(string(this->name + "_res2D").c_str(), string(this->name + "_res2D").c_str(),
                signals2D[0]->GetYaxis()->GetNbins(), signals2D[0]->GetYaxis()->GetXmin(),
                signals2D[0]->GetYaxis()->GetXmax());
        else if (syst == 1)
            res = new TH1D(string(this->name + "_UDres2D").c_str(), string(this->name + "_UDres2D").c_str(),
                signals2D[0]->GetYaxis()->GetNbins(), signals2D[0]->GetYaxis()->GetXmin(),
                signals2D[0]->GetYaxis()->GetXmax());
        else if (syst == 2)
            res = new TH1D(string(this->name + "_DUres2D").c_str(), string(this->name + "_DUres2D").c_str(),
                signals2D[0]->GetYaxis()->GetNbins(), signals2D[0]->GetYaxis()->GetXmin(),
                signals2D[0]->GetYaxis()->GetXmax());
        TH1* hithrecbin = 0;
        stringstream s;
        for (int bin = 1; bin < res->GetXaxis()->GetNbins() + 1; bin++) {
            double nSignal = 0;
            for (unsigned int p = 0; p < signals2D.size(); p++) {
                s.str("");
                s << this->name << p << "_pX";
                hithrecbin = signals2D.at(p)->ProjectionX(s.str().c_str(), bin, bin, "o");

                if (syst == 0)
                    hithrecbin->Multiply(&(WeightFunc.first), rec_gen);
                else if (syst == 1) //UD
                    hithrecbin->Multiply(&(WeightFuncUD.first), rec_gen);
                else if (syst == 2) //DU
                    hithrecbin->Multiply(&(WeightFuncDU.first), rec_gen);

                nSignal += hithrecbin->Integral();
                delete hithrecbin;
            }
            res->SetBinContent(bin, nSignal);
        }
        return res;
    }

    TH1* Get1DRW(int syst = 0) {
        cout << "nBins1: " << this->signal->GetXaxis()->GetNbins() << endl;
        TH1* res = 0;
        if (syst == 0) {
            res = (TH1*)this->signal->Clone(string(this->name + "_res1D").c_str());
            res->Multiply(&(WeightFunc.first), rec_gen);
        } else if (syst == 1) {
            res = (TH1*)this->signal->Clone(string(this->name + "_UDres1D").c_str());
            res->Multiply(&(WeightFuncUD.first), rec_gen);
        } else if (syst == 2) {
            res = (TH1*)this->signal->Clone(string(this->name + "_DUres1D").c_str());
            res->Multiply(&(WeightFuncDU.first), rec_gen);
        }
        return res;
    }

    TH1* GetSignal1D(std::vector<TH2*> IID, std::vector<TH3*> IIID, string nameSig) {
        cout << string(this->name + "_" + nameSig) << endl;
        stringstream s;
        s << string(this->name + "_" + nameSig);
        TH1* res = IID[0]->ProjectionY(s.str().c_str());
        for (unsigned int iHist = 1; iHist < IID.size(); iHist++) {
            s.str("");
            s << res->GetName() << "_IID" << iHist;
            res->Add(IID[iHist]->ProjectionY(s.str().c_str()));
        }
        for (unsigned int iHist = 0; iHist < IIID.size(); iHist++) {
            s.str("");
            s << res->GetName() << "_IIID" << iHist;
            res->Add(IIID[iHist]->ProjectionY(s.str().c_str()));
        }
        return res;
    }

};

class CombinedChiSquaredCaculatorAndPlotter : public ChiSquaredCaculatorAndPlotter {
public:

    CombinedChiSquaredCaculatorAndPlotter(string Name, std::vector<double> pars7, double NW8, WTempForCombination3D hists7,
            WTempForCombination3D hists8, double syst0, double systl) :
    ChiSquaredCaculatorAndPlotter(string(Name + "_7TeV"), pars7, hists7, syst0, systl) {
        std::vector<double> pars8;
        pars8.push_back(pars7[0]);
        pars8.push_back(pars7[1]);
        pars8.push_back(1.);
        pars8.push_back(NW8);
        plotter8 = new ChiSquaredCaculatorAndPlotter(string(Name + "_8TeV"), pars8, hists8, syst0, systl);
        combinedInput.data = this->CombineHistogramsID(ChiSquaredCaculatorAndPlotter::input.data, plotter8->GetInput().data,
                string("comb_data"));
        combinedInput.nonRWs = this->CombineHistogramsID(ChiSquaredCaculatorAndPlotter::input.nonRWs, plotter8->GetInput().nonRWs,
                string("comb_bkg"));
        combinedInput.signalID = this->CombineHistogramsID(ChiSquaredCaculatorAndPlotter::input.signalID, plotter8->GetInput().signalID,
                string("comb_signal"));
        combinedInput.name = Name;
        ChiSquaredCaculatorAndPlotter::input = combinedInput;
        TH1 * myUD = this->CombineHistogramsID(ChiSquaredCaculatorAndPlotter::systUD, plotter8->GetSystUD(), string("comb_UD"));
        TH1 * myDU = this->CombineHistogramsID(ChiSquaredCaculatorAndPlotter::systDU, plotter8->GetSystDU(), string("comb_DU"));
        TH1 * mySig = this->CombineHistogramsID(ChiSquaredCaculatorAndPlotter::signal, plotter8->GetSignalDef(), string("comb_SigDef"));
        int myNDF = ChiSquaredCaculatorAndPlotter::ndf + plotter8->GetNDF() + 3;
        ChiSquaredCaculatorAndPlotter::systUD = myUD;
        ChiSquaredCaculatorAndPlotter::systDU = myDU;
        ChiSquaredCaculatorAndPlotter::signal = mySig;
        ChiSquaredCaculatorAndPlotter::ndf = myNDF;

    }

    virtual ~CombinedChiSquaredCaculatorAndPlotter() {

    }

    virtual void WriteInfo() {
        TH1* band = ChiSquaredCaculatorAndPlotter::GetBand();
        TH1D* hData7 = new TH1D(string(this->name + "hData7").c_str(), "data", 100, -1., 1.);
        TH1D* hBand7 = new TH1D(string(this->name + "hBand7").c_str(), "band", 100, -1., 1.);
        for (int iBin = 0; iBin < 100; iBin++) {
            hData7->SetBinContent(iBin + 1, ChiSquaredCaculatorAndPlotter::input.data->GetBinContent(iBin + 11));
            hData7->SetBinError(iBin + 1, ChiSquaredCaculatorAndPlotter::input.data->GetBinError(iBin + 11));
            hBand7->SetBinContent(iBin + 1, band->GetBinContent(iBin + 11));
            hBand7->SetBinError(iBin + 1, band->GetBinError(iBin + 11));
        }
        hBand7->Rebin(10);
        hData7->Rebin(10);
        TH1D* hDataC = new TH1D(string(this->name + "hDataC").c_str(), "data", 20, -1., 3.);
        hDataC->SetStats(kFALSE);
        hDataC->GetXaxis()->SetTitle("cos(#theta_{l}*)");
        TH1D* hBandC = new TH1D(string(this->name + "hBandC").c_str(), "band", 20, -1., 3.);
        hBandC->SetStats(kFALSE);
        hBandC->GetXaxis()->SetTitle("cos(#theta_{l}*)");
        for (int iBin = 0; iBin < 10; iBin++) {
            hDataC->SetBinContent(iBin + 1, ChiSquaredCaculatorAndPlotter::input.data->GetBinContent(iBin + 1));
            hDataC->SetBinError(iBin + 1, ChiSquaredCaculatorAndPlotter::input.data->GetBinError(iBin + 1));
            hBandC->SetBinContent(iBin + 1, band->GetBinContent(iBin + 1));
            hBandC->SetBinError(iBin + 1, band->GetBinError(iBin + 1));
        }
        for (int iBin = 0; iBin < 10; iBin++) {
            hDataC->SetBinContent(iBin + 11, hData7->GetBinContent(iBin + 1));
            hDataC->SetBinError(iBin + 11, hData7->GetBinError(iBin + 1));
            hBandC->SetBinContent(iBin + 11, hBand7->GetBinContent(iBin + 1));
            hBandC->SetBinError(iBin + 11, hBand7->GetBinError(iBin + 1));
        }
        hBandC->SetFillColor(5);
        hBandC->SetLineColor(5);
        hBandC->SetMarkerColor(5);
        hBandC->GetYaxis()->SetRangeUser(0,1000);
        hDataC->SetMarkerStyle(20);
        TFile * f = new TFile(string(this->name + "_band.root").c_str(), "recreate");
        f->cd();
        hBandC->Write();
        hDataC->Write();
        f->Write();
        f->Close();
        double W = 600;
        double H = 600;
        TCanvas * c1 = new TCanvas(this->name.c_str(), "c", W, H);
        c1->SetWindowSize(W + (W - c1->GetWw()), H + (H - c1->GetWh()));
        c1->SetFillColor(0);
        c1->SetRightMargin(0.01);
        c1->SetLeftMargin(0.12);
        c1->SetTopMargin(0.04);
        c1->SetBottomMargin(0.1);
        c1->cd();
        hBandC->Draw("e2");
        hDataC->Draw("esames");
        c1->SaveAs(string(this->name + "_band.C").c_str());
    }
private:
    ChiSquaredCaculatorAndPlotter * plotter8;
    InputForCombination1D combinedInput;

    TH1* CombineHistogramsID(TH1* input7, TH1* input8, std::string outName) {
        TH1* tmpCombinedID = 0;
        int bins7 = input7->GetXaxis()->GetNbins();
        int bins8 = input8->GetXaxis()->GetNbins();
        cout << bins7 + bins8 << endl;
        double xbins[bins7 + bins8 + 1];
        for (int i = 0; i < bins8; i++) {
            xbins[i] = -1 + (i * 0.2);
        }
        for (int i = 0; i < (bins7 + 1); i++) {
            xbins[i + bins8] = 1 + (i * 0.02);
        }
        if (xbins[bins7 + bins8] != 3) {
            cout << "Very bad! " << xbins[bins7 + bins8] << " is not what I want" << endl;
            return tmpCombinedID;
        }

        tmpCombinedID = new TH1D(string(this->name + "_" + outName + "tmpCombinedID").c_str(), "tmpCombinedID", bins7 + bins8, xbins);
        for (int iBin = 0; iBin < bins8; iBin++) {
            tmpCombinedID->SetBinContent(iBin + 1, input8->GetBinContent(iBin + 1));
        }
        for (int iBin = 0; iBin < bins7; iBin++) {
            tmpCombinedID->SetBinContent(iBin + 1 + bins8, input7->GetBinContent(iBin + 1));
        }
        return tmpCombinedID;
    }


};

#endif	/* WHELFITCHISQUARED_H */

