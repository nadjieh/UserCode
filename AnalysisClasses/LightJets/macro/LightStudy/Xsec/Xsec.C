#include "/afs/cern.ch/user/a/ajafari/scratch0/CMSSW_3_6_1_patch3/src/AnalysisClasses/ChiSquared/interface/BaseRegion.h"
#include "/afs/cern.ch/user/a/ajafari/scratch0/CMSSW_3_6_1_patch3/src/AnalysisClasses/ChiSquared/interface/TopEvent.h"
#include "/afs/cern.ch/user/a/ajafari/scratch0/CMSSW_3_6_1_patch3/src/AnalysisClasses/ChiSquared/interface/Combinator.h"
#include "/afs/cern.ch/user/a/ajafari/scratch0/CMSSW_3_6_1_patch3/src/AnalysisClasses/ChiSquared/interface/DataRegion.h"
#include "/afs/cern.ch/user/a/ajafari/scratch0/CMSSW_3_6_1_patch3/src/AnalysisClasses/ChiSquared/interface/MCRegion.h"
#include "/afs/cern.ch/user/a/ajafari/scratch0/CMSSW_3_6_1_patch3/src/AnalysisClasses/ChiSquared/interface/EtaOnPtWeightJetEffHandler.h"
#include "/afs/cern.ch/user/a/ajafari/scratch0/CMSSW_3_6_1_patch3/src/AnalysisClasses/ChiSquared/interface/PtWeightJetEffHandler.h"
#include "/afs/cern.ch/user/a/ajafari/scratch0/CMSSW_3_6_1_patch3/src/AnalysisClasses/ChiSquared/interface/TwoDWeightJetEffHandler.h"
#include "/afs/cern.ch/user/a/ajafari/scratch0/CMSSW_3_6_1_patch3/src/AnalysisClasses/ChiSquared/interface/SpecificEffHandler.h"
#include "/afs/cern.ch/user/a/ajafari/scratch0/CMSSW_3_6_1_patch3/src/AnalysisClasses/EventSelection/interface/PracticalEvent.h"
#include "/afs/cern.ch/user/a/ajafari/scratch0/CMSSW_3_6_1_patch3/src/AnalysisClasses/EventSelection/interface/Event.h"
#include "/afs/cern.ch/user/a/ajafari/scratch0/CMSSW_3_6_1_patch3/src/AnalysisClasses/EventSelection/interface/GoodObjects.h"
#include "/afs/cern.ch/user/a/ajafari/scratch0/CMSSW_3_6_1_patch3/src/AnalysisClasses/LightJets/interface/DataAnalysis.h"
#include "/afs/cern.ch/user/a/ajafari/scratch0/CMSSW_3_6_1_patch3/src/AnalysisClasses/LightJets/interface/MCAnalysis.h"
#include "/afs/cern.ch/user/a/ajafari/scratch0/CMSSW_3_6_1_patch3/src/AnalysisClasses/LightJets/interface/AnalysisHandler.h"

#include "/afs/cern.ch/user/a/ajafari/scratch0/CMSSW_3_6_1_patch3/src/TopBrussels/TopTreeProducer/interface/TRootMuon.h"

#include<iostream>
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
using namespace std;

using namespace TopTree;
struct PsedoExps{
    int WJetsStartPoint;
    int WJetsNevt;
    int ZJetsStartPoint;
    int ZJetsNevt;
    int SingleTopSStartPoint;
    int SingleTopSNevt;
    int SingleTopTStartPoint;
    int SingleTopTNevt;
    int SingleTopTWStartPoint;
    int SingleTopTWNevt;
    int VqqStartPoint;
    int VqqNevt;
    int SignalStartPoint;
    int SignalNevt;
    int OtherTtStartPoint;
    int OtherTtNevt;
    double Fdata;
    double Fmc;
};

int main(int argc, char** argv){


    std::vector<double> MWPeff;
    std::vector<double> MWPerr;
    std::vector<double> ntt;
    std::vector<double> ntt_c;
    std::vector<double> nV;
    std::vector<double> nV_c;
    stringstream fname;
    stringstream fname2;
    double effBar = 0;
    TList * l4;
    TList * L4;
    TDirectory * d5;
    TDirectory * d4;
    TDirectory * D4;
    TDirectory * d3;
    TDirectory * D3;
    TList * l3;
    TList * L3;
    TDirectory * d2;
    TDirectory * D2;
    TList * l2;
    TList * L2;
    TDirectory * d1;
    TDirectory * D1;
    TList * l1;
    TList * L1;
    TFile * inputFile_;
    TFile * inputFile_2;
    double ca_RW_Norm[50] = {1.26087e-05,0.0117328,0.0404848,0.0722836,0.101307,0.11683,0.109291,0.0950369,0.0744794,0.060312,0.0573984,0.0427373,0.0394494,0.0358349,0.0250627,0.0214218,0.0187399,0.0115029,0.0101449,0.010041,0.00725569,0.00575815,0.00319622,0.00379776,0.00368341,0.0033968,0.00146264,0.00247753,0.00270098,0.00267213,0.000849756,0.00174373,0.000513274,0.000297602,0.00206405,0.00175918,0.000243157,0.000416442,0.000524607,0.000226006,0.00027011,4.13299e-05,3.1158e-05,2.88745e-07,0.000272085,5.40954e-05,0,1.52218e-05,0,0.000173765};
    double sb_Norm[50] = {0,0.00911213,0.0474827,0.0754031,0.0825761,0.116489,0.091014,0.0989207,0.0829298,0.0496147,0.0422182,0.0358901,0.0346756,0.0308648,0.0250151,0.0273172,0.0173349,0.0223039,0.015793,0.0140887,0.012247,0.00655694,0.00845007,0.00699062,0.00601957,0.00357449,0.00354058,0.00799015,0.00355714,0.00243215,0.00241565,0.00021665,0.00231686,0.00119451,0.00328279,0.00119316,0.00232515,4.94308e-05,0.00210966,3.29289e-05,3.88364e-05,0,0.00110863,2.47154e-05,1.4121e-05,0.00213437,8.21352e-06,0.00110727,0,2.47154e-05};
    double ss_Norm[50] = {0,0.0105541,0.0510743,0.099113,0.141241,0.166106,0.138844,0.0875078,0.0571648,0.0452196,0.0373458,0.0300976,0.0245233,0.0199297,0.0156649,0.0138059,0.0104158,0.00869346,0.00675206,0.00606885,0.00486606,0.00412732,0.00366328,0.00270636,0.00254212,0.00188599,0.00133933,0.00150358,0.00106612,0.000929455,0.000847455,0.000683456,0.000409999,0.000437332,0.000546913,0.000245999,0.000601332,0.000273333,0.000109333,8.19998e-05,8.19998e-05,0.000246123,5.46665e-05,0.000109333,0.000136666,8.19998e-05,5.46665e-05,8.19998e-05,0.000109333,5.46665e-05};
    TH1D * CA_RW_NORM = new TH1D("ca_RW_Norm","ca_RW_Norm",50, 0., 1000.);
    TH1D * SB_NORM = new TH1D("sb_Norm","ca_Norm",50, 0., 1000.);
    TH1D * SS_NORM = new TH1D("ss_Norm","ss_Norm",50, 0., 1000.);
    for(int i=0; i<SB_NORM->GetNbinsX(); i++){
        CA_RW_NORM->SetBinContent(i+1,ca_RW_Norm[i]);
        SB_NORM->SetBinContent(i+1,sb_Norm[i]);
        SS_NORM->SetBinContent(i+1,ss_Norm[i]);
    }
    RooRealVar mlb("mlb","mlb",0.,1000.);
    RooDataHist ttDataHist("ttDataHist","ttDataHist",mlb,SS_NORM);
    RooHistPdf ttPDF("ttPDF","ttPDF",mlb,ttDataHist);

    RooDataHist VDataHist("VDataHist","VDataHist",mlb,SB_NORM);
    RooHistPdf VPDF("VPDF","VPDF",mlb,VDataHist);

    RooDataHist VDataHist_control("VDataHist_control","VDataHist_control",mlb,CA_RW_NORM);
    RooHistPdf VPDF_control("VPDF_control","VPDF_control",mlb,VDataHist_control);

    RooRealVar Ntt("Ntt","N_{t#bar{t}-like}",1000,0,100000);
    RooRealVar NV( "NV", "N_{V-like}",1000,0,100000);

    RooRealVar Ntt_control("Ntt_control","N_{t#bar{t}-like}_control",1000,0,100000);
    RooRealVar NV_control( "NV_control", "N_{V-like}_control",1000,0,100000);

    RooAddPdf model("model","model",RooArgList(ttPDF,VPDF),RooArgList(Ntt,NV));
    RooAddPdf model_control("model","model",RooArgList(ttPDF,VPDF_control),RooArgList(Ntt_control,NV_control));

    //efficiency loop
    for(unsigned int j = 0; j<500/*PEs.size()*/; j++){
        fname.str("");
        fname<<"/home/ajafari/Pseudo_100/"<<j+1<<"/FullStudy_FdataData__"<<j+1<<"_minChi2.root";
        cout<<fname.str()<<endl;
        inputFile_ = TFile::Open(fname.str().c_str());
        l1 = inputFile_->GetListOfKeys();
	d1 = (TDirectory*)inputFile_->Get(l1->At(0)->GetName());
	l2 = d1->GetListOfKeys();
	d2 = (TDirectory*)d1->Get(l2->At(0)->GetName());
	l3 = d2->GetListOfKeys();
	d3 =  (TDirectory*)d2->Get(l3->At(8)->GetName());
	d4 =  (TDirectory*)d3->Get("Btag");
	d5 =  (TDirectory*)d4->Get("Integrated");
	l4 = d5->GetListOfKeys();
	TGraphAsymmErrors * tga = (TGraphAsymmErrors*)d5->Get(l4->At(4)->GetName());
        double y = 1000.;
	double x = 1000.;
	double minDif50 = 100000.;
	double xminDif50 = 1000.;
	double yminDif50 = 1000.;
        int i50 = -1999;
        for(int i = 400; i<520;i++){
            tga->GetPoint(i,x,y);
            if(fabs(y-0.50) < minDif50){
                    minDif50 = fabs(y-0.5);
                    xminDif50 = x;
                    yminDif50 = y;
                    i50 = i;
            }
            x = 1000;
            y = 1000;
        }
//        cout<<fabs(yminDif50)<<endl;
                fname2.str("");
        fname2<<"/home/ajafari/Pseudo_100/"<<j+1<<"/PE100_"<<j+1<<"_minChi2.root";
        cout<<fname2.str()<<endl;
        inputFile_2 = TFile::Open(fname2.str().c_str());
        L1 = inputFile_2->GetListOfKeys();
	D1 = (TDirectory*)inputFile_2->Get(L1->At(0)->GetName());
	L2 = D1->GetListOfKeys();
        D2 = (TDirectory*)D1->Get(L2->At(3)->GetName());
        L3 = D2->GetListOfKeys();
	D3 =  (TDirectory*)D2->Get(L3->At(2)->GetName());
        D4 = (TDirectory*)D3->Get("JetBasedMLJ");
        L4 = D4->GetListOfKeys();
        TH1D * SA = (TH1D*) D4->Get(L4->At(0)->GetName());
        RooDataHist dataHist("dataHist","dataHist",mlb,SA);
        model.fitTo(dataHist);
        model_control.fitTo(dataHist);
        
        if(yminDif50 != 1000.){
            MWPeff.push_back(fabs(yminDif50));
            effBar += fabs(yminDif50);
//            cout<<effBar<<endl;
            MWPerr.push_back(fabs(tga->GetErrorYhigh(i50)));
            ntt.push_back(Ntt.getVal());
            ntt_c.push_back(Ntt_control.getVal());
            nV.push_back(NV.getVal());
            nV_c.push_back(NV_control.getVal());
        }
        delete tga;
        delete d5;
        delete d4;
        delete d3;
        delete d2;
        delete d1;
        delete inputFile_;

        delete SA;
        delete D4;
        delete D3;
        delete D2;
        delete D1;
        delete inputFile_2;
    }

    cout<<"Fit has ended --------------------------"<<endl;

    TH2D * Xsec_bTagEff = new TH2D("XSec_bTagEff","TtBar cross section ratio vs bTagEff M",1000,0.,1.,10000,-5.,5.);
    TH1D * Xsec_control = new TH1D("TtBar_control_XS","ttbar Xsec estimation from control sample",2000,0.,400.);
    TH1D * Xsec = new TH1D("TtBar_XS","ttbar Xsec estimation from signal sample",2000,0.,400.);
    TH1D * V_control = new TH1D("V_control_XS","Bkg estimation from control sample",2000,0.,400.);
    TH1D * V = new TH1D("V_XS","Bkg estimation from signal sample",2000,0.,400.);
    TH1D * VoverVc = new TH1D("VoverVc","Bkg ratio",10000,-5.,5.);
    TH1D * ToverTc = new TH1D("ToverTc","Tt ratio",10000,-5.,5.);
    for(unsigned int j = 0; j<MWPeff.size()/*PEs.size()*/; j++){
        Xsec_bTagEff->Fill(MWPeff.at(j),((double)ntt_c.at(j)/(double)ntt.at(j)));
        Xsec_control->Fill(ntt_c.at(j));
        Xsec->Fill(ntt.at(j));
        V_control->Fill(nV_c.at(j));
        V->Fill(nV.at(j));
        VoverVc->Fill((double)nV_c.at(j)/(double)nV.at(j));
        ToverTc->Fill((double)ntt_c.at(j)/(double)ntt.at(j));
    }
    TFile * fout = new TFile("XSecInfo.root","recreate");
    fout->cd();
    Xsec_bTagEff->Write();
    Xsec_control->Write();
    Xsec->Write();
    V_control->Write();
    V->Write();
    VoverVc->Write();
    ToverTc->Write();
    fout->Close();
    return 0;
};


