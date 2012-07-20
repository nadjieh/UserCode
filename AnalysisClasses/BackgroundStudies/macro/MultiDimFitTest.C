/* 
 * File:   MultiDimFitTest.C
 * Author: nadjieh
 *
 * Created on June 9, 2012, 1:11 PM
 */
#include "../interface/MultiDimensionalFit.h"
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
    TH1*  data;
    TH1*  signal;
    TH1*  bkg;
    TH1*  wtemplate;
    TH1*  toptemplate;
    TFile * file = 0;
    for (int f = 1; f < argc; f++) {
        std::string arg_fth(*(argv + f));
	cout<<f<<" ---- "<<arg_fth<<endl;
        if (arg_fth == "signal") {
            f++;
            std::string out(*(argv + f));
		cout<<"signal"<<endl;
            file = new TFile(out.c_str(),"read");
            signal = ((TH1*)file->Get("Default/DefaultcosTheta"));
        }else if(arg_fth == "data"){
            f++;
            std::string out(*(argv + f));
		cout<<"data"<<endl;
            file = new TFile(out.c_str(),"read");
            data = ((TH1*)file->Get("Default/DefaultcosTheta"));
        }else if (arg_fth == "bkg") {
            f++;
            std::string out(*(argv + f));
		cout<<"bkg"<<endl;
            file = new TFile(out.c_str(),"read");
            bkg = ((TH1*)file->Get("Default/DefaultcosTheta"));
        }else if (arg_fth == "wtemplate") {
            f++;
            std::string out(*(argv + f));
		cout<<"w template"<<endl;
            file = new TFile(out.c_str(),"read");
            wtemplate = ((TH1*)file->Get("Default/DefaultcosTheta"));
            //wtemplate = ((TH1*)file->Get("BtagOrderedB/BtagOrderedBcosTheta"));
	    //wtemplate = ((TH1*)file->Get("PtOrderedB/PtOrderedBcosTheta"));
        }else if (arg_fth == "toptemplate") {
            f++;
            std::string out(*(argv + f));
		cout<<"top template"<<endl;
            file = new TFile(out.c_str(),"read");
            toptemplate = ((TH1*)file->Get("Default/DefaultcosTheta"));
            //wtemplate = ((TH1*)file->Get("BtagOrderedB/BtagOrderedBcosTheta"));
	    //wtemplate = ((TH1*)file->Get("PtOrderedB/PtOrderedBcosTheta"));
        }
    }
    cout<<bkg <<"\t"<<signal<<"\t"<<data<<"\t"<<wtemplate<<"\t"<<toptemplate<<endl;
    wtemplate->Sumw2();
    wtemplate->Scale((double)1./(double)wtemplate->Integral());
    
    toptemplate->Sumw2();
    toptemplate->Scale((double)1./(double)toptemplate->Integral());
    double lowHtAll[50] = {0.00682428, 0.00914364, 0.0119189, 0.0149055, 0.0169624, 0.0168313, 0.018781, 0.018375, 
    0.0193246, 0.01926, 0.0187486, 0.016555, 0.0196346, 0.0188182, 0.0244237, 0.0253316, 0.0196833, 0.0172154,
    0.0212007, 0.0256599, 0.0146082, 0.0155231, 0.0191555, 0.0221673, 0.0202544, 0.0159449, 0.0212312, 0.0187745, 
    0.0167624, 0.0188849, 0.0248933, 0.0265374, 0.0255938, 0.0191266, 0.0139624, 0.021782, 0.0173055, 0.0276981, 
    0.0210957, 0.02744, 0.02008, 0.0212001, 0.0177705, 0.0217551, 0.0267376, 0.0204807, 0.0268623, 0.0232656, 
    0.0255695, 0.0279397};
    double lowEtaAll[50] = {0.0212757, 0.0157141, 0.0175201, 0.0205147, 0.0192779, 0.0208134, 0.0203646, 0.018974, 
    0.0205622, 0.0225365, 0.0195325, 0.01884, 0.0201149, 0.0225543, 0.0201032, 0.0223868, 0.022314, 0.0199281, 
    0.0237196, 0.0246584, 0.0196471, 0.0212193, 0.0184966, 0.0211632, 0.0173835, 0.0196656, 0.0192737, 0.0192398, 
    0.0181833, 0.0177309, 0.0204905, 0.0219076, 0.0234067, 0.0186831, 0.0199224, 0.0185756, 0.0191265, 0.0226722, 
    0.0197981, 0.0202729, 0.0209818, 0.0203957, 0.016278, 0.0207976, 0.0173201, 0.0158959, 0.0203487, 0.0191754, 
    0.0190883, 0.0211552};
        
    TH1D * lowHtw = new TH1D("lowHtW","lowHtW",50,-1.,1);
    for(int s = 0; s< 50; s++)
        lowHtw->SetBinContent(s+1,lowHtAll[s]);
    
    std::pair<ROOT::Math::Functor,MultiDimensionalFitLiklihood*>  myLL =
            MultiDimensionalFitLiklihood::getMDLLFunction("MDLL" , bkg , data , signal,wtemplate,toptemplate);
//            MultiDimensionalFitLiklihood::getMDLLFunction("MDLL" , bkg , data , signal,lowHtw);
    
    double x[5]    = {0.7,0.3,1.,1.,1.};
    double xerr[5] = {-1.,-1.,-1.,-1.,-1.};
    double correlation;
    GetMinimumMD(myLL.first,x,xerr,correlation);
    delete myLL.second;

    return 0;
}

