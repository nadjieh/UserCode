/* 
 * File:   EfficiencyExt.h
 * Author: ajafari
 * Each instance of this class is to fill the bins of passed and all 
 * Histograms (which are to used for efficiency) by some integral on 
 * another property of ....
 * Created on January 30, 2009, 6:28 PM
 */

#ifndef _EFFICIENCYEXT_H
#define	_EFFICIENCYEXT_H

#include "EfficiencyH1.h"
#include "ObjectProperty.h"
#include "string"
#include "vector"
#include "TH1D.h"
#include <sstream>
#include <cmath>
#include "TF1.h"
#include "TStyle.h"
#include "TPaveText.h"

#include "Math/Functor.h"
#include "Math/WrappedFunction.h"
#include "Math/IFunction.h"
#include "Math/Integrator.h"

#include <iosfwd>
#include <stdlib.h>

using namespace std;

class TF1Wrapper {
public:
    static TF1* F;
    static double Get(double x);
};

template<class T>
class EfficiencyExt : public EfficiencyH1<T> {
public:
    typedef EfficiencyH1<T> BASE;

    BASE EffSideBand;
    BASE EffFit;

    EfficiencyExt(ObjectProperty<T>* main, ObjectProperty<T>* inside, TF1* _fitFunc, double xmin, double xmax, string name) : BASE(main, name),
    EffSideBand(main, "SideBand"),
    EffFit(main, "Fit"),
    InsideProp(inside),
    fitFunc(_fitFunc),
    xMin(xmin),
    xMax(xmax) {
        binSize = (this->theProperty->MaxValue - this->theProperty->MinValue) / this->theProperty->NumberOfBins;
        for (int i = 0; i < main->NumberOfBins; i++) {
            TH1D ip;

            ostringstream ss_name;
            ostringstream ss_title;
            ss_name << inside->PropertyName << "_" << i << "_P_main_" << main->PropertyName;
            ss_title << inside->PropertyTitle << " (" << i << "th bin of " << main->PropertyName << ") passed";
            ip.SetNameTitle(ss_name.str().c_str(), ss_title.str().c_str());
            ip.SetBins(inside->NumberOfBins, inside->MinValue, inside->MaxValue);
            innerHPassed.push_back(ip);

            ostringstream ss_name2;
            ostringstream ss_title2;
            ss_name2 << inside->PropertyName << "_" << i << "_A_main_" << main->PropertyName;
            ss_title2 << inside->PropertyTitle << " (" << i << "th bin of " << main->PropertyName << ") All";
            TH1D* ia = (TH1D*) (ip.Clone(ss_name2.str().c_str()));
            ia->SetTitle(ss_title2.str().c_str());
            innerHAll.push_back(*ia);
        }
    };

    virtual ~EfficiencyExt() {
    };

    virtual int Fill(const T* theObject, double weight = 1) {
        if (this->theProperty == 0) {
            cout << "NULL !!!";
            throw std::exception();
        } else {
            bool allPassed = true;
            if (this->AllCondition != 0)
                allPassed = this->AllCondition(theObject);

            if (allPassed) {
                double main_val = this->theProperty->ReadValue(theObject).at(0);
                if (main_val > this->theProperty->MinValue && main_val < this->theProperty->MaxValue) {
                    int bin_number(floor((main_val - this->theProperty->MinValue) / binSize));

                    double inside_val = this->InsideProp->ReadValue(theObject).at(0);
                    innerHAll.at(bin_number).Fill(inside_val, weight);

                    if (this->Condition(theObject))
                        return innerHPassed.at(bin_number).Fill(inside_val, weight);
                }
            }
        }
        return -10;

    };

    virtual void WriteAll(TDirectory* dir, bool mkdir = true) {

        TDirectory* my_dir = dir->mkdir(this->theProperty->PropertyName.c_str());
        TDirectory* in_dir = my_dir->mkdir(InsideProp->PropertyName.c_str());
        in_dir->cd();

#ifdef DEBUG__
        cout << this->Name << " is being started" << endl;
#endif


        int old_fit = gStyle->GetOptFit();
        gStyle->SetOptFit(1111);
        for (unsigned int i = 0; i < innerHAll.size(); i++) {
            ostringstream ss;
            ss << "bin_" << i;
            in_dir->mkdir(ss.str().c_str())->cd();

            double bin_i_all = 0;
            TH1D hAllI = innerHAll[i];
            TF1* f_ret = GetIntegral(&hAllI, bin_i_all);

            TCanvas cA;
            cA.cd();
            hAllI.Draw();
            f_ret->Draw("same");

            TPaveText * t = new TPaveText(0.05, 0.85, 0.25, 0.95, "brNDC");
            ostringstream int_A;
            int_A << "Integral = " << bin_i_all;
            t->AddText(int_A.str().c_str());
            t->Draw();

            cA.Write(hAllI.GetName());

#ifdef DEBUG__
            cout << "\tAll " << i << " has been integrated" << endl;
#endif

            double bin_i_pss = 0;
            TH1D hPssI = innerHPassed[i];
            f_ret = GetIntegral(&hPssI, bin_i_pss);

            TCanvas cP;
            cP.cd();
            hPssI.Draw();
            f_ret->Draw("same");

            t = new TPaveText(0.05, 0.85, 0.25, 0.95, "brNDC");
            ostringstream int_P;
            int_P << "Integral = " << bin_i_pss;
            t->AddText(int_P.str().c_str());
            t->Draw();

            cP.Write(hPssI.GetName());
#ifdef DEBUG__
            cout << "\tPass " << i << " has been integrated" << endl;
#endif

            this->EffFit.GetHAll()->SetBinContent(i + 1, bin_i_all);
            EffFit.SetBinContent(i + 1, bin_i_pss);


            //Side Band starts from here
            this->SideBandSubtraction(&hAllI, bin_i_all);
            this->SideBandSubtraction(&hPssI, bin_i_pss);

            this->EffSideBand.GetHAll()->SetBinContent(i + 1, bin_i_all);
            EffSideBand.SetBinContent(i + 1, bin_i_pss);
        }
        gStyle->SetOptFit(old_fit);

        //BASE::WriteAll(my_dir, false);
        my_dir->cd();
        this->EffFit.WriteAll(my_dir->mkdir("EffFit"), false);

        this->EffSideBand.WriteAll(my_dir->mkdir("EffSideBand"), false);

        dir->cd();
    };

    TH1D* SideBandSubtraction(const TH1D* Total, double& res) {
        // Total Means signal plus background
        string newName = Total->GetName();
        newName += "_SBS";
        TH1D* Result = new TH1D(newName.c_str(), Total->GetTitle(), Total->GetNbinsX(), Total->GetXaxis()->GetXmin(), Total->GetXaxis()->GetXmax());

        double Peak = 91.18;
        double SD = 1.4;

        const double BinWidth = Total->GetXaxis()->GetBinWidth(1);
        const int nbins = Total->GetNbinsX();
        const double xmin = Total->GetXaxis()->GetXmin();

        const int PeakBin = (int) ((Peak - xmin) / BinWidth + 1); // Peak
        const double SDBin = (SD / BinWidth); // Standard deviation
        const int I = (int) ((3.0 * SDBin > 1.0) ? 3.0 * SDBin : 1); // Interval
        const int D = (int) ((10.0 * SDBin > 1.0) ? 10.0 * SDBin : 1); // Distance from peak

        const double IntegralRight = Total->Integral(PeakBin + D, PeakBin + D + I);
        const double IntegralLeft = Total->Integral(PeakBin - D - I, PeakBin - D);

        double SubValue = 0.0;
        double NewValue = 0.0;

        const double Slope = (IntegralRight - IntegralLeft) /
                (double) ((2 * D + I)*(I + 1));
        const double Intercept = IntegralLeft / (double) (I + 1) -
                ((double) PeakBin - (double) D - (double) I / 2.0) * Slope;

        for (int bin = 1; bin < (nbins + 1); bin++) {
            SubValue = Slope * bin + Intercept;
            if (SubValue < 0)
                SubValue = 0;

            NewValue = Total->GetBinContent(bin) - SubValue;
            if (NewValue > 0) {
                Result->SetBinContent(bin, NewValue);
            }
        }
        Result->SetEntries(Result->Integral());

        res = Result->Integral();

        Result->Write();

        return Result;
    };

    TF1* GetIntegral(TH1D* h, double& res) {

//        Double_t all = h->GetEntries(); //Integral();
        Double_t all = h->Integral(); //Integral();
        double par0 = fitFunc->GetParameter(2);
        par0 = (all) * 1.0;

        std::stringstream fName;
        fName << "fff" << rand();

        TF1* fAfterFit = (TF1*) (fitFunc); //->Clone(fName.str().c_str()));
        fAfterFit->SetParameter(2, par0);

        if (all == 0.0) {
            res = 0.0;
            return fAfterFit;
        }

        //        cout << fitFunc->GetParameter(2) << " - " << fAfterFit->GetParameter(2) << " --- ";
        //        cout << fitFunc->GetParameter(1) << " - " << fAfterFit->GetParameter(1) << " --- ";
        //        cout << fitFunc->GetParameter(0) << " - " << fAfterFit->GetParameter(0) << endl;
#ifdef DEBUG__
        cout << "\tFit Started ";
#endif
        std::stringstream canvName;
        canvName << "canv" << rand();
        TCanvas* ccc = new TCanvas(canvName.str().c_str());
        fAfterFit->Draw();
        ccc->Write("funcBefore");

        h->Fit(fAfterFit, "Q"); //RMELOQ
        h->Fit(fAfterFit, "Q");
        h->Fit(fAfterFit, "Q");

        std::stringstream canv2Name;
        canv2Name << "canv2" << rand();

        TCanvas* ccc2 = new TCanvas(canv2Name.str().c_str());
        fAfterFit->Draw();
        ccc2->Write("funcAfter");

#ifdef DEBUG__
        cout << "\tFit Finished ";
#endif

        TF1Wrapper::F = fAfterFit;
        ROOT::Math::WrappedFunction<> f1(TF1Wrapper::Get);

#ifdef DEBUG__
        cout << "\tIntegral Started ";
#endif
        ROOT::Math::Integrator ig(f1);

        res = ig.Integral(xMin, xMax);
        return fAfterFit;
    };
protected:
    vector<TH1D> innerHPassed;
    vector<TH1D> innerHAll;
    ObjectProperty<T>* InsideProp;
    TF1* fitFunc;
    double xMin, xMax;
    double binSize;
};

#endif	/* _EFFICIENCYEXT_H */

