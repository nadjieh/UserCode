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
    std::vector<TH2*>  signalIID; // for munub t-processes
    TH1*  bkginsignal = 0; //for t-processes other than munub
    TH1*  bkg;// for non-t processes
    TH1*  wtemplate;
    TH1*  toptemplate;
    bool singleMatrix = false;
    bool is2Drecgen = false;
    TFile * file = 0;

    for (int f = 1; f < argc; f++) {
        std::string arg_fth(*(argv + f));
	cout<<f<<" ---- "<<arg_fth<<endl;
        if (arg_fth == "signal") {
            f++;
            std::string out(*(argv + f));
		cout<<"signal"<<endl;
            file = new TFile(out.c_str(),"read");
            signalIID.push_back (((TH2*)file->Get("Default_allW/Default_allWcosTheta2D"))->RebinY(1));
            cout<<signalIID.at(signalIID.size()-1)->GetNbinsY()<<endl;
            if (bkginsignal == 0)
                bkginsignal = (((TH1*)file->Get("Default_allW/Default_allWcosTheta"))->Rebin(1));
            else
                bkginsignal->Add(((TH1*)file->Get("Default_allW/Default_allWcosTheta"))->Rebin(1));

        }else if(arg_fth == "data"){
            f++;
            std::string out(*(argv + f));
		cout<<"data"<<endl;
            file = new TFile(out.c_str(),"read");
            data = ((TH1*)file->Get("Default_allW/Default_allWcosTheta"))->Rebin(1);
        }else if (arg_fth == "bkg") {
            f++;
            std::string out(*(argv + f));
		cout<<"bkg"<<endl;
            file = new TFile(out.c_str(),"read");
            if(bkg == NULL)
                bkg = ((TH1*)file->Get("Default_allW/Default_allWcosTheta"))->Rebin(1);
            else
                bkg->Add(((TH1*)file->Get("Default_allW/Default_allWcosTheta"))->Rebin(1));
        }else if (arg_fth == "wtemplate") {
            f++;
            std::string out(*(argv + f));
		cout<<"w template"<<endl;
            file = new TFile(out.c_str(),"read");
            wtemplate = ((TH1*)file->Get("bb05"));
//            cout<<file->GetName()<<endl;
//            file->ls();
//            wtemplate = ((TH1*)file->Get("Default_allW/Default_allWcosTheta"))->Rebin(1);
//            wtemplate = ((TH1*)file->Get("Default_Def/Default_DefcosTheta"));
//            wtemplate = ((TH1*)file->Get("BtagOrderedB/BtagOrderedBcosTheta"));
//            wtemplate = ((TH1*)file->Get("RandomB/RandomBcosTheta"));
//	    wtemplate = ((TH1*)file->Get("PtOrderedB/PtOrderedBcosTheta"));
        }else if (arg_fth == "toptemplate") {
            f++;
            std::string out(*(argv + f));
		cout<<"top template"<<endl;
            file = new TFile(out.c_str(),"read");
            toptemplate = ((TH1*)file->Get("Default_allW/Default_allWcosTheta"));
            //wtemplate = ((TH1*)file->Get("BtagOrderedB/BtagOrderedBcosTheta"));
	    //wtemplate = ((TH1*)file->Get("PtOrderedB/PtOrderedBcosTheta"));
        }else if (arg_fth == "singleMatrix") {
            f++;
                cout<<"singleMatrix"<<endl;
            std::string out(*(argv + f));
            if(out == "true")
                singleMatrix = true;
        }else if (arg_fth == "is2Drecgen") {
            f++;
                cout<<"is2Drecgen"<<endl;
            std::string out(*(argv + f));
            if(out == "yes" || out == "Yes" || out == "Y" || out == "y"
               || out == "YES")
                is2Drecgen = true;
        }
    }
    cout<<bkg <<"\t"<<data<<"\t"<<wtemplate<<"\t"<<toptemplate<<endl;
    wtemplate->Sumw2();
    wtemplate->Scale((double)1./(double)wtemplate->Integral());
    
//    toptemplate->Sumw2();
//    toptemplate->Scale((double)1./(double)toptemplate->Integral());

    data->Print();
    double x[4]    = {0.7,0.3,1.,1.};
    double xerr[4] = {-1.,-1.,-1.,-1.};
    double correlation;
    if(is2Drecgen && !singleMatrix){        
        cout<<"In Generalized fit: \n\tsize of signal is "<<signalIID.size()<<endl;
        if(bkg != NULL && bkginsignal != NULL)
            bkg->Add(bkginsignal); 
        cout<<"bkg bins: "<<bkg->GetNbinsX()<<endl;
        cout<<"w bins: "<<wtemplate->GetNbinsX()<<endl;
        cout<<"data bins: "<<data->GetNbinsX()<<endl;
        std::pair<ROOT::Math::Functor,MultiDimensionalFitLiklihood*>  myLL = 
        MultiDimensionalFitLiklihood::getMDLLFunctionGeneralized("MDLL" , bkg , data , signalIID,wtemplate);
        GetMinimumMD(myLL.first,x,xerr,correlation);
        delete myLL.second;       
    }
    else if(is2Drecgen && singleMatrix){  
        cout<<"single rec_gen matrix fit"<<endl;
        if(bkg != NULL && bkginsignal != NULL)
            bkg->Add(bkginsignal);        
        TH2* SingMSignal = 0;
        for(unsigned int p = 0; p < signalIID.size(); p++ ){
            if(SingMSignal == 0)
                SingMSignal = signalIID.at(p);
            else
                SingMSignal->Add(signalIID.at(p));
        }    
        std::pair<ROOT::Math::Functor,MultiDimensionalFitLiklihood*>  myLL =
        MultiDimensionalFitLiklihood::getMDLLFunction("LL", bkg, data, SingMSignal,wtemplate,true);
        GetMinimumMD(myLL.first,x,xerr,correlation);
        delete myLL.second;
    }
    else if(!is2Drecgen){
        cout<<"no rec_gen matrix fit"<<endl;
        TH1* Signal1D = 0;
        stringstream s;
        for(unsigned int p = 0; p < signalIID.size(); p++ ){
            s.str("");
            s<<p<<"_pY";
            if(Signal1D == 0)
                Signal1D = (TH1*)signalIID.at(p)->ProjectionY(s.str().c_str());
            else
                Signal1D->Add((TH1*)signalIID.at(p)->ProjectionY(s.str().c_str()));
        }
        if(bkginsignal != NULL)
//            bkg->Add(bkginsignal);        
            Signal1D->Add(bkginsignal);
        std::pair<ROOT::Math::Functor,MultiDimensionalFitLiklihood*>  myLL =
        MultiDimensionalFitLiklihood::getMDLLFunction("LL", bkg, data, Signal1D,wtemplate);
        GetMinimumMD(myLL.first,x,xerr,correlation);
        delete myLL.second;
    }
    
//    double x[5]    = {0.7,0.3,1.,1.,1.};
//    double xerr[5] = {-1.,-1.,-1.,-1.,-1.};


    return 0;
}

