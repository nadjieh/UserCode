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


TH1F GetCosThetaPlot(string name, int nFinalBin = 10){
    TFile * f = TFile::Open(string("bareFilesFromEvesel/TypeIMET_"+name+"_plots.root").c_str());
    TH1F h = *((TH1F*)f->Get("cosTheta"));
        
    if((h.GetXaxis()->GetNbins()) == nFinalBin)
        return h;
    if((h.GetXaxis()->GetNbins() % nFinalBin) == 0){
        h.Rebin(((h.GetXaxis()->GetNbins())/nFinalBin));
    }else{
        std::cout<<nFinalBin<<" does not count "<<h.GetXaxis()->GetNbins()<<std::endl;
        std::cout<<"I will take the biggest number less than "<<nFinalBin<<"that counts it .."<<std::endl;
        int n = 1;
        for(int i = 2; i<nFinalBin; i++){
            if((h.GetXaxis()->GetNbins() % i) == 0)
                n = i;
        }
        h.Rebin(((h.GetXaxis()->GetNbins())/n));
    }
//    cout<<"Nbins after rebinning: "<<h.GetXaxis()->GetNbins()<<endl;
    return h;
}
void RunFitValidation(int StartPEX, int LPEX, int StartPEXPull , int LPEXPull, double Lumi = 3793){
    stringstream outName;
    outName<<"Linearity_start-"<<StartPEX<<"-length-"<<LPEX<<"_Pull_start-"<<StartPEXPull<<
            "-length-"<<LPEXPull<<".root";
    
    double FposFixed = 0.0009;
    std::pair<TF1,WeightFunctionCreator*> WtbWeightor = WeightFunctionCreator::getWeightFunction("WtbWeightor");
    SamplesInfo mySampleInfo;
    std::map<string,DistributionProducerFromSelected*> bkg_samples;
    std::map<string,DistributionProducerFromSelected*> signal_samples;
    std::map<string, double>::iterator sampleItr = mySampleInfo.Xsections.begin();
    TH1F signal;
    TH1F signalMC;
    TH1F bkg;
    int sampleIndex = 0;
    for(; sampleItr != mySampleInfo.Xsections.end(); sampleItr++){
        if(sampleItr->first == "qcd"){
            sampleIndex++;
            continue;
        }
        if(sampleItr->first == "w" || sampleItr->first == "dy"){
//            cout<<sampleItr->first<<endl;
            TH1F hist = GetCosThetaPlot(sampleItr->first,10);
            hist.Sumw2();
            DistributionProducerFromSelected *myDist = new DistributionProducerFromSelected(hist,string(sampleItr->first),Lumi);
            bkg_samples[sampleItr->first] = myDist;
            hist.Scale(float(Lumi*sampleItr->second)/float(mySampleInfo.N0[sampleItr->first]));
//           if(sampleItr == mySampleInfo.Xsections.begin())
           if(sampleIndex == 0)
                bkg = *((TH1F*)hist.Clone(string("bkg_"+string(hist.GetName())).c_str()));
            else{
                bkg.Add(&hist);                
//                cout<<"Adding bkg with nbins = "<<bkg.GetXaxis()->GetNbins()<<
//                        " and hist with nbins = "<<hist.GetXaxis()->GetNbins()<<endl;
            }
        }else{
//            cout<<sampleItr->first<<endl;
            TH1F hist = GetCosThetaPlot(sampleItr->first,10);
            hist.Sumw2();
            DistributionProducerFromSelected* myDist = new DistributionProducerFromSelected(hist,string(sampleItr->first),Lumi);
            signal_samples[sampleItr->first] = myDist;
            hist.Scale(float(Lumi*sampleItr->second)/float(mySampleInfo.N0[sampleItr->first]));            
//            if(sampleItr == mySampleInfo.Xsections.begin())
            if(sampleIndex == 2)
                signalMC = *((TH1F*)hist.Clone(string("signal_"+string(hist.GetName())).c_str()));
            else{
                signalMC.Add(&hist);
//                cout<<"Adding signal with nbins = "<<signalMC.GetXaxis()->GetNbins()<<
//                " and hist with nbins = "<<hist.GetXaxis()->GetNbins()<<endl;
            }
        }
        sampleIndex++;
    }
    gROOT->cd();
    TH2D hFinalFNeg("hFinalFNeg","Linearirty Check for F_{-};F_{-} input;F_{-} output",300,0.,1.,300,0.,1.);
    TH2D hFinalF0("hFinalF0","Linearirty Check for F_{0};F_{0} input;F_{0} output",300,0.,1.,300,0.,1.);
    TH2D hFinalFPos("hFinalFPos","Linearirty Check for F_{+};nPEX;F_{+} output",300,0.,300., 1000 , -0.5 , 0.5);
    int nFSteps = 300;

    double FNegValueSteps[nFSteps];
    for(int i = 0; i<nFSteps; i++){
        FNegValueSteps[i] = float(i)/(float)nFSteps;
    }
    for (int nPEX = 0;nPEX < 300; nPEX++){
        cout<< "PEX: "<<nPEX<<endl;

        if (nPEX >= (StartPEX + LPEX) ){
            cout<< " ... Skipped"<<endl;
            continue;
        }

        if (nPEX < StartPEX){  
            for(unsigned int i = 0 ; i < mySampleInfo.Xsections.size(); i++)
                SeedGenerator.Integer( 10000 );
            cout<< " ... Skipped"<<endl;
            continue;
        }
         

        stringstream name__ ;
        name__<<"CosTheta_bkg_"<<nPEX;
        stringstream title__;
        title__ << "noWtb cos(#theta) : PEX="<<nPEX;               
        TH1F hSumBGPartial( name__.str().c_str() , title__.str().c_str() , signalMC.GetXaxis()->GetNbins()
                    , signalMC.GetXaxis()->GetXmin() , signalMC.GetXaxis()->GetXmax() );
        hSumBGPartial.Sumw2();
        std::map<string,DistributionProducerFromSelected*>::iterator bkgItr = bkg_samples.begin();
        for (; bkgItr != bkg_samples.end(); bkgItr++){
//            cout<< "..." << bkgItr->first << "..." <<endl;
            TH1F tmp = bkgItr->second->GeneratePartialSample( 1.0/3.0 , nPEX );
            hSumBGPartial.Add( &tmp );
        }
//        for(int mybin = 0; mybin < hSumBGPartial.GetXaxis()->GetNbins(); mybin++)
//            cout<<"hSumBGPartial: "<<hSumBGPartial.GetBinContent(mybin+1)<<endl;
        name__.str(""); title__.str("");
        name__<<"CosTheta_signal_"<<nPEX;
        title__ << "Wtb cos(#theta) : PEX="<<nPEX;                    
        TH1F hSumSIGPartial( name__.str().c_str() , title__.str().c_str() , signalMC.GetXaxis()->GetNbins()
                    , signalMC.GetXaxis()->GetXmin() , signalMC.GetXaxis()->GetXmax() );
        hSumSIGPartial.Sumw2();
        std::map<string,DistributionProducerFromSelected*> ::iterator sigItr = signal_samples.begin();
        for (; sigItr != signal_samples.end(); sigItr++){
//            cout<< "..." << sigItr->first << "..." <<endl;
            TH1F tmp = sigItr->second->GeneratePartialSample( 1.0/3.0 , nPEX );
            hSumSIGPartial.Add(&tmp);
        }

        for ( int i = 0; i< nFSteps; i++){
//            if ((FNegValueSteps[i]*nFSteps) % 50.0 == 0)
//                cout<< "\tFStep: "<<FNegValueSteps[i]<<endl;
            if (FNegValueSteps[i] > ( 1.0-FposFixed))
                continue;

            double F0Value = 1.0 - FposFixed - FNegValueSteps[i];

            WtbWeightor.first.SetParameters( FNegValueSteps[i] , F0Value );
            
            name__.str(""); name__<< hSumBGPartial.GetName()<<"_"<<FNegValueSteps[i];
            title__.str("");title__<< hSumBGPartial.GetTitle()<<" for F_ = "<<FNegValueSteps[i];
            TH1F SIGinPEX = *((TH1F*)hSumSIGPartial.Clone(name__.str().c_str()));
            SIGinPEX.SetTitle(title__.str().c_str());
//            for(int mybin = 0; mybin < SIGinPEX.GetXaxis()->GetNbins(); mybin++)
//                cout<<"SIGinPEX: "<<SIGinPEX.GetBinContent(mybin+1)<<endl;
            SIGinPEX.Multiply(&WtbWeightor.first,1);
            cout<<"-----------------"<<endl;
//            for(int mybin = 0; mybin < SIGinPEX.GetXaxis()->GetNbins(); mybin++)
//                cout<<"SIGinPEX: "<<SIGinPEX.GetBinContent(mybin+1)<<endl;
            SIGinPEX.Add(&hSumBGPartial);
//            cout<<"After addition:"<<endl;
//            for(int mybin = 0; mybin < SIGinPEX.GetXaxis()->GetNbins(); mybin++)
//                cout<<"SIGinPEX: "<<SIGinPEX.GetBinContent(mybin+1)<<endl;
            std::pair<TF3,LikelihoodFunction*> LLinPEXforFNegValueArray= LikelihoodFunction::getLLFunction(
                    string("F_"+name__.str()) , bkg , SIGinPEX, signalMC);
            TF3 LLinPEXforFNegValue = LLinPEXforFNegValueArray.first;
//            for(int as = 0; as <1; as+=0.01)
//                cout<<LLinPEXforFNegValue.Eval(as,1-as,1);
            
            double x[3]={-1.,-1.,-1.};
            double xerr[3]={-1.,-1.,-1.};
            GetMinimum(LLinPEXforFNegValue, x, xerr,false);
            hFinalFNeg.Fill(FNegValueSteps[i],x[1]);
            hFinalF0.Fill(F0Value,x[0]);
            hFinalFPos.Fill(nPEX,1.0-x[0]-x[1]);

            delete LLinPEXforFNegValueArray.second;
        }
    }
    TH1D hPullFNeg("hPullFNeg","Pull distribution for F_{-}",1000,-5,5);
    TH1D hPullF0("hPullF0","Pull distribution for F_{0}",1000,-5,5);
    TH1D hPullFPos("hPullFPos","Pull distribution for F_{+}",1000,-5,5);
    TH1D hPullFResp("hPullFResp","Pull distribution for F_{resp}",1000,-5,5);

    TH1D hResFNeg ("hResFNeg","Residual for F_{-}",1000,-0.5,0.5);
    TH1D hResF0("hResF0","Residual for F_{0}",1000,-0.5,0.5);
    TH1D hResFPos("hResFPos","Residual for F_{+}",1000,-0.5,0.5);
    TH1D hResFResp("hResFResp","Residual for F_{resp}",1000,-0.5,0.5);
    cout<<StartPEXPull <<"  "<<LPEXPull<<endl;
    for (int nPEXPull = 0; nPEXPull < 1000; nPEXPull++){
//        cout<< "PEXPull:"<<nPEXPull<<endl;

        if (nPEXPull >= (StartPEXPull + LPEXPull)) {
            cout<< " ... Skipped pull"<<endl;
            continue;
        }

        if (nPEXPull < StartPEXPull){
            for( unsigned int i = 0; i<mySampleInfo.Xsections.size(); i++)
                SeedGeneratorLumiEQ.Integer( 10000 );
            cout<< " ... Skipped pull"<<endl;
            continue;
        }
         
        cout<< "PEXPull:"<<nPEXPull<<endl;

        stringstream name__; name__<< "CosTheta_Pull_"<<nPEXPull;
        stringstream title__; title__<< "cos(#theta) : PEXPull="<<nPEXPull;
               
        TH1F hData( name__.str().c_str() , title__.str().c_str() , signalMC.GetXaxis()->GetNbins() , 
                signalMC.GetXaxis()->GetXmin() , signalMC.GetXaxis()->GetXmax() );
        hData.Sumw2();
        std::map<string,DistributionProducerFromSelected*>::iterator bkgItr = bkg_samples.begin();
        for( ; bkgItr != bkg_samples.end(); bkgItr++){
//            cout<< "..." << bkgItr->first<< "..." <<endl;
            TH1F tmp = bkgItr->second->GeneratePartialSampleLumiEQ(  nPEXPull );
            hData.Add( &tmp );
        }
        std::map<string,DistributionProducerFromSelected*>::iterator sigItr = signal_samples.begin();
        for( ; sigItr != signal_samples.end(); sigItr++){
//            cout<< "..." << sigItr->first<< "..." <<endl;
            TH1F tmp = sigItr->second->GeneratePartialSampleLumiEQ(  nPEXPull );
            hData.Add( &tmp );
        }

        std::pair<TF3,LikelihoodFunction*> LLinPEXforFNegValueArray= LikelihoodFunction::getLLFunction(
                    string("F_"+name__.str()) , bkg , hData, signalMC);
        TF3 LLinPEXforFNegValue = LLinPEXforFNegValueArray.first;
        double x[3]={-1.,-1.,-1.};
        double xerr[3]={-1.,-1.,-1.};
        GetMinimum(LLinPEXforFNegValue, x, xerr);
        double fneg = x[1];
        double f0 = x[0];
        double fpos = 1.0 - x[1] - x[0];

        double fresponse = x[2];
        double errfrespo = xerr[2];
        double resfresp0 = fresponse - 1.0;
        
        hPullFResp.Fill( (double)resfresp0/(double)errfrespo );
        hResFResp.Fill( resfresp0 );
        
        double errfneg = xerr[1];
        double errf0 = xerr[0];
        double errfpos = sqrt( errf0*errf0 + errfneg * errfneg);

        double resneg = fneg- (3.03734e-01);
        double respos = fpos - FposFixed;
        double resf0 = f0 - (6.64263e-01);

        hPullFNeg.Fill((double)resneg /  (double)errfneg);
        hPullF0.Fill((double)resf0 /(double) errf0);
        hPullFPos.Fill((double)respos / (double)errfpos);

        hResFPos.Fill( respos );
        hResFNeg.Fill( resneg );
        hResF0.Fill( resf0 );

        delete LLinPEXforFNegValueArray.second;
        
    }
    delete WtbWeightor.second;
    TFile * outFile= new TFile(outName.str().c_str(),"recreate");
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
    outFile->Close();
}
#endif	/* VALIDATOREXECUTER_H */

