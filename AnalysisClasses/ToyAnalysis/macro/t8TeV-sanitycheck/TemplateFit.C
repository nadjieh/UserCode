#include<iostream>
#include<vector>
#include<string>
#include "TFile.h"
#include "TTree.h"
#ifndef __CINT__
#include "RooGlobalFunc.h"
#endif
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooGaussian.h"
#include "TCanvas.h"
#include "RooPlot.h"
#include "RooHistPdf.h"
#include "RooDataHist.h"
#include "RooAddPdf.h"

#include "TH1.h"
#include "TH2.h"
#include "TF1.h"
#include "../../interface/TemplateFitArrayCreator.h"

using namespace std;

int main(int argc, char** argv){
    std::string histAdd;
    std::string inputFile;
    for (int f = 1; f < argc; f++) {
        std::string arg_fth(*(argv + f));
        if (arg_fth == "inputFile") {
            f++;
            std::string in(*(argv + f));
            inputFile = string("~/"+in);
        }else if(arg_fth == "histAddress"){
            f++;
            std::string Xsec(*(argv + f));
            histAdd = Xsec;
        }
    }
    
    
    
    TemplateFitArrayCreator zero("zero","1-(x*x)");
    TemplateFitArrayCreator negative("negative","(1-x)*(1-x)");
    TemplateFitArrayCreator positive("positive","(1+x)*(1+x)");
    
   
    TH1D * h1 = zero.GetHistogram();
    TH1D * h2 = negative.GetHistogram();
    TH1D * h3 = positive.GetHistogram();
    
    RooRealVar cosTheta("cosTheta","cosTheta",-1.,1.);
    
    RooDataHist zeroDataHist("zeroDataHist","zeroDataHist",cosTheta,h1);
    RooHistPdf zeroPDF("zeroPDF","zeroPDF",cosTheta,zeroDataHist);

    RooDataHist negDataHist("negDataHist","negDataHist",cosTheta,h2);
    RooHistPdf negPDF("negPDF","negPDF",cosTheta,negDataHist);

    RooDataHist posDataHist("posDataHist","posDataHist",cosTheta,h3);
    RooHistPdf posPDF("posPDF","posPDF",cosTheta,posDataHist);

    RooRealVar F0("F0","F_{0}",0.7,0.,1.);
    RooRealVar Fneg( "Fneg", "F_{-}",0.3,0.,1.);
//    RooRealVar Fpos = 1-F0-Fneg;

    RooAddPdf model("model","model",RooArgList(zeroPDF,negPDF,posPDF),RooArgList(F0,Fneg));
    TFile * f = TFile::Open(inputFile.c_str());
    TH1D * data = (TH1D*)f->Get(histAdd.c_str());
    cout<<data<<"  "<<histAdd.c_str()<<endl;
    data->Rebin(20);
    
    cout<<"before modeling"<<endl;
    RooDataHist dataHist("dataHist","dataHist",cosTheta,data);
    model.fitTo(dataHist);
    cout<<"F0: "<<F0.getVal()<<" +- "<<F0.getError()<<endl;
    cout<<"Fneg: "<<Fneg.getVal()<<" +- "<<Fneg.getError()<<endl;
    cout<<"Fpos: "<<1-(F0.getVal()+Fneg.getVal())<<" +- "
            <<sqrt((F0.getError()*F0.getError())+(Fneg.getError()*Fneg.getError()))<<endl;
    
    
    return 0;
};

