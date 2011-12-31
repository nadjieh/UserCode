#include <complex>
#include <iomanip>
#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TDirectory.h"
#include "TCanvas.h"
#include "TProfile.h"
#include <iostream>
#include <utility>
#include <algorithm>
#include <string>
#include <vector>
#include <TColor.h>
#include <TColorWheel.h>
#include <TGraphAsymmErrors.h>
#include <TBranch.h>
using namespace std;
struct mySortByValue{
    bool operator() (std::pair<string,double> comb1, std::pair<string,double> comb2) { return (comb1.second > comb2.second);}
} SortByValue;
void divideSamples(std::vector<std::string> input,std::vector<TFile*> inputFile, std::string anaName){

    TDirectory * Wmain = (TDirectory*)inputFile.at(1)->Get(input.at(1).c_str());
    if(Wmain == NULL){
        cout<<"No file like "<<inputFile.at(1)<<endl;
        return ;
    }else{
        cout<<inputFile.at(1)->GetName()<<endl;
    }

    TDirectory * Signalmain = (TDirectory*)inputFile.at(0)->Get(input.at(0).c_str());
    if(Signalmain == NULL){
        cout<<"No file like "<<inputFile.at(0)<<endl;
        return ;
    }else{
        cout<<inputFile.at(0)->GetName()<<endl;
    }
    TDirectory * WEff = (TDirectory*)Wmain->Get("Efficiency");
    if(WEff == NULL){
        cout<<"No Efficiency directory in "<<Wmain->GetName()<<endl;
        Wmain->ls();
        return ;
    }
    TDirectory * SignalEff = (TDirectory*)Signalmain->Get("Efficiency");
    if(SignalEff == NULL){
        cout<<"No Efficiency directory in "<<Signalmain->GetName()<<endl;
        Signalmain->ls();
        return ;
    }
    TList * EffList = SignalEff->GetListOfKeys();
    TFile * f = new TFile(anaName.c_str(), "recreate");
    for(int i = 1; i<EffList->GetSize(); i++){
        TDirectory * WProp = (TDirectory*)WEff->Get(EffList->At(i)->GetName());
        if(WProp == NULL){
            cout<<"No property like "<<EffList->At(i)->GetName()<<endl;
            WEff->ls();
            return ;
        }
        TDirectory * SignalProp = (TDirectory*)SignalEff->Get(EffList->At(i)->GetName());
        if(SignalProp == NULL){
            cout<<"No property like "<<EffList->At(i)->GetName()<<endl;
            SignalEff->ls();
            return ;
        }
        TDirectory * WInteg = (TDirectory*)WProp->Get("Integrated");
        TDirectory * SignalInteg = (TDirectory*)SignalProp->Get("Integrated");
        TList * l = WInteg->GetListOfKeys();
        TH1D * WIinf = (TH1D*)WInteg->Get(l->At(6)->GetName());
        if(WIinf == NULL){
            cout<<"No histogram like "<<l->At(6)->GetName()<<endl;
            WInteg->ls();
            return ;
        }
        if(string(WIinf->ClassName()) != string("TH1D")){
            cout<<WIinf->GetName()<<" is not TH1D but is "<<WIinf->ClassName()<<endl;
            return ;
        }
        WIinf->SetName("WIinf");
        TH1D * W0I = (TH1D*)WInteg->Get(l->At(2)->GetName());
        if(W0I == NULL){
            cout<<"No histogram like "<<l->At(2)->GetName()<<endl;
            WInteg->ls();
            return ;
        }
        if(string(W0I->ClassName()) != string("TH1D")){
            cout<<W0I->GetName()<<" is not TH1D but is "<<W0I->ClassName()<<endl;
            return ;
        }
        W0I->SetName("W0I");
        TH1D * SignalIinf = (TH1D*)SignalInteg->Get(l->At(6)->GetName());
        if(SignalIinf == NULL){
            cout<<"No histogram like "<<l->At(6)->GetName()<<endl;
            SignalInteg->ls();
            return ;
        }
        if(string(SignalIinf->ClassName()) != string("TH1D")){
            cout<<SignalIinf->GetName()<<" is not TH1D but is "<<SignalIinf->ClassName()<<endl;
            return ;
        }
        SignalIinf->SetName("SignalIinf");
        TH1D * Signal0I = (TH1D*)SignalInteg->Get(l->At(2)->GetName());
        if(Signal0I == NULL){
            cout<<"No histogram like "<<l->At(6)->GetName()<<endl;
            SignalInteg->ls();
            return ;
        }
        if(string(Signal0I->ClassName()) != string("TH1D")){
            cout<<Signal0I->GetName()<<" is not TH1D but is "<<Signal0I->ClassName()<<endl;
            return ;
        }
        Signal0I->SetName("Signal0I");
        TGraphAsymmErrors * Iinf = new TGraphAsymmErrors(WIinf,SignalIinf);
        Iinf->SetNameTitle(string(string(WProp->GetName())+"_Iinf").c_str(),string(string(WProp->GetName())+"_Iinf").c_str());
        Iinf->GetXaxis()->SetTitle(WProp->GetName());
        TGraphAsymmErrors * OI = new TGraphAsymmErrors(W0I,Signal0I);
        OI->SetNameTitle(string(string(WProp->GetName())+"_0I").c_str(),string(string(WProp->GetName())+"_0I").c_str());
        OI->GetXaxis()->SetTitle(WProp->GetName());
        f->cd();
        TDirectory * g = f->mkdir(WProp->GetName());
        g->cd();
        WIinf->Write();
        W0I->Write();
        SignalIinf->Write();
        Signal0I->Write();
        Iinf->Write();
        OI->Write();
        f->cd();
    }
    f->Close();
}
void CD(TCanvas& s, std::string name){
    if(name == "DPhiHadBLepton")
        s.cd(1);
    if(name == "DPhiHadWHadB")
        s.cd(2);
    if(name == "DPhiHadWLepB")
        s.cd(3);
    if(name == "DPhiTopHadB")
        s.cd(4);
    if(name == "DPhiTopLepB")
        s.cd(5);

    if(name == "DPhiTopW")
        s.cd(6);
    
    if(name == "DThetaHadBLepton")
        s.cd(7);
    if(name == "DThetaHadWHadB")
        s.cd(8);
    if(name == "DThetaHadWLepB")
        s.cd(9);
    if(name == "DThetaTopHadB")
        s.cd(10);
    if(name == "DThetaTopLepB")
        s.cd(11);
    if(name == "DThetaTopW")
        s.cd(12);

    if(name == "DrHadBLepton")
        s.cd(13);
    if(name == "DrHadWHadB")
        s.cd(14);
    if(name == "DrHadWLepB")
        s.cd(15);
    if(name == "DrTopHadB")
        s.cd(16);
    if(name == "DrTopLepB")
        s.cd(17);
    if(name == "DrTopW")
        s.cd(18);

    if(name == "ExtChi2")
        s.cd(19);
    if(name == "Mlb")
        s.cd(20);
    if(name == "Mll")
        s.cd(21);
    if(name == "RelTopPt")
        s.cd(22);
    if(name == "TopEta")
        s.cd(23);
    if(name == "TopPt")
        s.cd(24);
    if(name == "TopQuarkPt")
        s.cd(25);
}
void distributionsPlotter(std::vector<std::string> input,std::vector<TFile*> inputFile){

    TDirectory * Wmain = (TDirectory*)inputFile.at(1)->Get(input.at(1).c_str());
    if(Wmain == NULL){
        cout<<"No file like "<<inputFile.at(1)<<endl;
        return ;
    }else{
        cout<<inputFile.at(1)->GetName()<<endl;
    }

    TDirectory * Signalmain = (TDirectory*)inputFile.at(0)->Get(input.at(0).c_str());
    if(Signalmain == NULL){
        cout<<"No file like "<<inputFile.at(0)<<endl;
        return ;
    }else{
        cout<<inputFile.at(0)->GetName()<<endl;
    }
    TDirectory * WEff = (TDirectory*)Wmain->Get("Efficiency");
    if(WEff == NULL){
        cout<<"No Efficiency directory in "<<Wmain->GetName()<<endl;
        Wmain->ls();
        return ;
    }
    TDirectory * SignalEff = (TDirectory*)Signalmain->Get("Efficiency");
    if(SignalEff == NULL){
        cout<<"No Efficiency directory in "<<Signalmain->GetName()<<endl;
        Signalmain->ls();
        return ;
    }
    TList * EffList = SignalEff->GetListOfKeys();
    TCanvas c;
    c.SetFillColor(kWhite);
    c.SetBorderSize(0);
    c.Divide(8,5);
    for(int i = 1; i<EffList->GetSize(); i++){
        TDirectory * WProp = (TDirectory*)WEff->Get(EffList->At(i)->GetName());
        if(WProp == NULL){
            cout<<"No property like "<<EffList->At(i)->GetName()<<endl;
            WEff->ls();
            return ;
        }
        TDirectory * SignalProp = (TDirectory*)SignalEff->Get(EffList->At(i)->GetName());
        if(SignalProp == NULL){
            cout<<"No property like "<<EffList->At(i)->GetName()<<endl;
            SignalEff->ls();
            return ;
        }
        TH1D * signal = (TH1D*)SignalProp->Get(string("Efficiency_ALL_TopEvent_"+string(SignalProp->GetName())).c_str());
        signal->SetNameTitle("signal","signal");
        signal->SetLineColor(kRed);
        signal->SetLineWidth(2);
        signal->SetFillColor(kWhite);
        signal->Scale((double)1./(double)signal->Integral());
        TH1D * w = (TH1D*)WProp->Get(string("Efficiency_ALL_TopEvent_"+string(WProp->GetName())).c_str());
        w->SetNameTitle("wjets","wjets");
        w->SetLineColor(kAzure);
        w->SetLineWidth(2);
        w->SetFillColor(kWhite);
        w->Scale((double)1./(double)w->Integral());
        double m = max<double> (w->GetMaximum(),signal->GetMaximum()) ;
        w->GetYaxis()->SetRangeUser(0,(m+0.01));
        w->SetStats(kFALSE);
        signal->SetStats(kFALSE);
        signal->GetYaxis()->SetRangeUser(0,(m+0.01));
        c.cd(i)->SetFillColor(kWhite);
        c.cd(i);
        signal->Draw();
        w->Draw("sames");
    }
    c.SaveAs("distributions.png");
    c.SaveAs("distributions.C");
}
void efficiencyPlotter(std::vector<TFile*> inputFile){
    TList * PropLis = inputFile.at(0)->GetListOfKeys();
    TCanvas c;
    TCanvas c2;
    c.SetFillColor(kWhite);
    c2.SetFillColor(kWhite);
    c.Divide(5,4);
    c2.Divide(5,4);
    for(int i = 0; i<PropLis->GetSize(); i++){
        TDirectory * prop = (TDirectory*)inputFile.at(0)->Get(PropLis->At(i)->GetName());
        TGraphAsymmErrors * OI = (TGraphAsymmErrors*)prop->Get(string(string(prop->GetName())+"_0I").c_str());
        OI->SetFillColor(kWhite);
        OI->SetLineColor(kOrange);
        TGraphAsymmErrors * Iinf = (TGraphAsymmErrors*)prop->Get(string(string(prop->GetName())+"_Iinf").c_str());
        Iinf->SetFillColor(kWhite);
        Iinf->SetLineColor(kMagenta);
        c.cd(i+1)->SetFillColor(kWhite);
        c.cd(i+1)->SetBorderSize(0);
        c.cd(i+1)->SetBorderMode(0);
        c.cd(i+1);
        OI->Draw("ap");
//        CD(c2,string(prop->GetName()));
        c2.cd(i+1)->SetFillColor(kWhite);
        c2.cd(i+1)->SetBorderSize(0);
        c2.cd(i+1)->SetBorderMode(0);
        c2.cd(i+1);
        Iinf->Draw("ap");
    }
    c.SaveAs("OI.C");
    c2.SaveAs("Iinf.C");
}
void TwoDOverlay(std::string input1, std::string input2, std::string out){
    TFile * Signal = TFile::Open(string(input1+"_minChi2.root").c_str());
    TFile * w = TFile::Open(string(input2+"_minChi2.root").c_str());
    TDirectory * mainSig = (TDirectory *)Signal->Get(input1.c_str());
    TDirectory * mainW = (TDirectory *)w->Get(input2.c_str());
    TDirectory * Sig2Ddir  = (TDirectory *)mainSig->Get("DiscrimW_2Ds");
    TDirectory * W2Ddir  = (TDirectory *)mainW->Get("DiscrimW_2Ds");
    TList * TwoDList = Sig2Ddir->GetListOfKeys();
    TFile * f = new TFile(out.c_str(),"recreate");
    std::vector<std::pair<std::string,double> >corrs;
    corrs.clear();
    cout<<"Variable Pair\t\tDeltaCorr(W,top)\n\n"<<endl;
    for(int i = 0; i<TwoDList->GetSize(); i++){
	TH2D * sig = (TH2D*)Sig2Ddir->Get(TwoDList->At(i)->GetName());
	sig->SetMarkerColor(kRed);
	sig->SetMarkerStyle(kFullCircle);
	sig->SetTitle("signal");
	TH2D * W = (TH2D*)W2Ddir->Get(TwoDList->At(i)->GetName());
	W->SetMarkerColor(kAzure);
	W->SetMarkerStyle(kOpenSquare);
	W->SetTitle("W+jet");
	TCanvas c;
	c.cd();
	c.SetFillColor(kWhite);
        
        corrs.push_back(make_pair(string(sig->GetName()),
        fabs(W->GetCorrelationFactor() - sig->GetCorrelationFactor())));
//        cout<<sig->GetName()<<"\t"<<W->GetCorrelationFactor()<<"\t"<<sig->GetCorrelationFactor()<<endl;
	sig->Draw();
	W->Draw("sames");
	c.SetName(W->GetName());
        c.BuildLegend();
	f->cd();
	c.Write();
    }
    sort(corrs.begin(),corrs.end(),SortByValue);
    for(unsigned int i = 0; i<corrs.size(); i++)
        cout<<corrs.at(i).first<<"\t\t"<<corrs.at(i).second<<endl;
    f->Close();
}
int main(int argc, char** argv){
    std::string anaName;
    std::vector<std::string> input;
    input.clear();
    std::vector<TFile*> inputFile;
    inputFile.clear();

    for (int f = 1; f < argc; f++) {
        std::string arg_fth(*(argv + f));
//        cout<<"-------- "<< arg_fth<<endl;
        if (arg_fth == "out") {
          f++;
          std::string out(*(argv + f));
          anaName = string(out);
        }else if (arg_fth == "input") {
          f++;
          std::string out(*(argv + f));
          input.push_back(string(out));
          inputFile.push_back(new TFile(string(out+"_minChi2.root").c_str(),"read"));
        }
    }

//    divideSamples(input, inputFile,anaName);
//    efficiencyPlotter(inputFile);
     TwoDOverlay(input.at(0), input.at(1), anaName);
    //distributionsPlotter(input, inputFile);
    return 1 ;
}
