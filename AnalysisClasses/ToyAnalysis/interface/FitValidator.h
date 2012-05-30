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

TRandom SeedGenerator = TRandom( 1928374 );
TRandom SeedGeneratorLumiEQ = TRandom( 874546620 );



class SamplesInfo{
public:
    SamplesInfo(){
        Xsections["t"]= 41.9;//0
        Xsections["tbar"]= 22.6;//1
        Xsections["tW"]= 7.9;//2
        Xsections["tWbar"]= 7.9;//3
        Xsections["tt"]= 165;//4
        Xsections["s"]= 3.19;//5
        Xsections["sbar"]= 1.44;//6
        Xsections["w"]= 31314;//7
        Xsections["dy"]= 3048;//8
        Xsections["qcd"]= 84679;//9
        N0["t"]= 3857900;
        N0["tbar"]= 1943627;
        N0["tW"]= 813134;
        N0["tWbar"]= 689462;
        N0["tt"]=3698723;
        N0["s"]= 259777;
        N0["sbar"]= 137889;
        N0["w"]= 80388662;
        N0["dy"]= 35526705;
        N0["qcd"]= 25026537;

        NSelected["t"]= 35223;
        NSelected["tbar"]= 19903;
        NSelected["tW"]= 7016;
        NSelected["tWbar"]= 5980;
        NSelected["tt"]=17068;
        NSelected["s"]= 2503;
        NSelected["sbar"]= 1414;
        NSelected["w"]= 4196;
        NSelected["dy"]= 1873;
        NSelected["qcd"]= 24;

//        NHt["t"]= 31180;
//        NHt["tbar"]= 17232;
//        NHt["tW"]= 6416;
//        NHt["tWbar"]= 5468;
//        NHt["tt"]=16225;
//        NHt["s"]= 1186;
//        NHt["sbar"]= 1242;
//        NHt["w"]= 2995;
//        NHt["dy"]= 1112;
//        NHt["qcd"]= 7;
//
//        NFwdEta["t"]= 27003;
//        NFwdEta["tbar"]= 14398;
//        NFwdEta["tW"]= 2309;
//        NFwdEta["tWbar"]= 2022;
//        NFwdEta["tt"]=5796;
//        NFwdEta["s"]= 2209;
//        NFwdEta["sbar"]= 619;
//        NFwdEta["w"]= 2043;
//        NFwdEta["dy"]= 924;
//        NFwdEta["qcd"]= 12;
    }
    ~SamplesInfo(){};
    
    std::map<string, double> Xsections;//pb
    std::map<string, double> N0;
    std::map<string, double> NSelected;

//    std::map<string, double> NHt;
//    std::map<string, double> NFwdEta;

    
};

//CHECK for max_size
class DistributionProducerFromSelected{
public:
    DistributionProducerFromSelected(TH1* hSelected , string MCName , double lumi):
    hInput(hSelected), mcName(MCName), Lumi(lumi){
        
        TRandom RandomGenerator( SeedGenerator.Integer(10000000) );
        for(int iBin = 0; iBin<hSelected->GetXaxis()->GetNbins(); iBin++){
            double cosTheta = hSelected->GetBinCenter(iBin+1);
//            double cosTheta = hSelected->GetBinCenter(iBin);
//            cout<<"cosTheta is "<<cosTheta<<endl;
//            cout<<"BinContents of "<<iBin<<" is "<<hSelected->GetBinContent( iBin+1 )<<endl;
            for(int eventID = 0; eventID < hSelected->GetBinContent( iBin+1 ); eventID++){
                int evtRndId = RandomGenerator.Integer( 1000000000  );
                while (sampleContent.count(evtRndId) > 0){
                    evtRndId = RandomGenerator.Integer( 1000000000  );                       
                }
                sampleContent[evtRndId] = cosTheta;
            }
        }
#ifdef TEST
        TH1* h2 = (TH1*)hSelected->Clone(string("second_"+string(hSelected->GetName())).c_str());
        std::map<int, double>::iterator tmpItr = sampleContent.begin();
        cout<<"***** "<<mcName<<endl;
        for(; tmpItr != sampleContent.end(); tmpItr++)
            h2->Fill(tmpItr->second);
        TFile * test = new TFile (string(mcName+"_test.root").c_str(),"recreate");
        test->cd();
        hSelected->Write();
        h2->Write();
        test->Close();
#endif /*TEST*/
        SamplesInfo mySampleInfo;
        Xsec = mySampleInfo.Xsections[MCName];
        N0 = mySampleInfo.N0[MCName];
//        selEff = (double)mySampleInfo.NSelected[MCName]/(double)N0;
        selEff = (double)(hInput->GetEntries())/(double)N0;
    }
    ~DistributionProducerFromSelected(){}
        
    TH1* GeneratePartialSample(double fraction, int nPEX){
        TRandom RandomGenerator( SeedGenerator.Integer(10000000) );
        std::vector<double> selectedValues;
        std::map<int,double>::iterator evtIter = sampleContent.begin();  
        for (; evtIter != sampleContent.end(); evtIter++){
            if (RandomGenerator.Uniform() < fraction)
                selectedValues.push_back( evtIter->second );
        }
//        cout<<"------------ "<<selectedValues.size()<<endl;
//        cout<<"------------ "<<selectedValues.at(0)<<endl;
//        cout<<"------------ "<<selectedValues.at(1)<<endl;
        double Weight = 0.0;
        if (selectedValues.size() !=0) {           
            Weight = (double)(Lumi*Xsec) / (double)(fraction*N0);
//            cout<<"Weight: "<<Weight<<endl;
        }
        stringstream s;
        s<<mcName<<"_"<<hInput->GetName()<<"_"<<nPEX;
        string hName = s.str();
        s.str("");
        s<<mcName<<"_"<<hInput->GetTitle()<<"_"<<nPEX;
        string hTitle = s.str();
        gROOT->cd();
        TH1* hRet = new TH1D( hName.c_str() , hTitle.c_str() , hInput->GetXaxis()->GetNbins()
                   , hInput->GetXaxis()->GetXmin() , hInput->GetXaxis()->GetXmax() );
        hRet->Sumw2();
        for ( unsigned int i = 0; i < selectedValues.size(); i++)
            hRet->Fill( selectedValues.at(i) , Weight );

        return hRet;
    }
    TH1* GeneratePartialSampleLumiEQ(int nPEX){        
        TRandom RandomGenerator( SeedGeneratorLumiEQ.Integer(10000000) );
        double nSelectedEventsInLumi_ = Lumi*Xsec*selEff;
        double nSelectedEventsInLumi = RandomGenerator.Gaus(nSelectedEventsInLumi_, sqrt(nSelectedEventsInLumi_));
        unsigned int EventIndices = sampleContent.size();
        std::vector<double> selectedValues;
        std::map<int,double>::iterator evtIter = sampleContent.begin();  
      
        for (int nEvt = 0; nEvt < int(nSelectedEventsInLumi); nEvt++ ){
            int EvtID = RandomGenerator.Integer( EventIndices );
            evtIter = sampleContent.begin();
            for(int i = 0; i < EvtID; i++ )
                evtIter++;
            selectedValues.push_back(evtIter->second );
        }
              
        stringstream s;
        s<<mcName<<"_"<<hInput->GetName()<<"_"<<nPEX;
        string hName = s.str();
        s.str("");
        s<<mcName<<"_"<<hInput->GetTitle()<<"_"<<nPEX;
        string hTitle = s.str();
        gROOT->cd();
        TH1* hRet = new TH1D( hName.c_str() , hTitle.c_str() , hInput->GetXaxis()->GetNbins()
                   , hInput->GetXaxis()->GetXmin() , hInput->GetXaxis()->GetXmax() );
        hRet->Sumw2();
        for ( unsigned int i = 0; i < selectedValues.size(); i++)
            hRet->Fill( selectedValues.at(i) );

        return hRet;
    }
private:
    TH1* hInput;
    string mcName;
    double Lumi;
    std::map<int,double> sampleContent;
    double Xsec;
    int N0;
    double selEff;
};
#endif	/* FITVALIDATOR_H */

