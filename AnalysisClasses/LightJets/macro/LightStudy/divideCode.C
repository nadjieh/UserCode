#include <complex>

#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TDirectory.h"
#include "TCanvas.h"
#include "TProfile.h"
#include <iostream>
#include <string>
#include <TColor.h>
#include <TColorWheel.h>
using namespace std;

TH1D * subtract(TH1D* all, TH1D* pass, double L, double R){
	TH1D * res = new TH1D(*all);
	res->SetNameTitle("res","res");
	double coefficient = (double)L/(double)R;
	double relErrL = ((double)sqrt(L)/(double)L);
	double relErrR = ((double)sqrt(R)/(double)R);
	double coefficientErr = coefficient * sqrt((relErrL*relErrL) + (relErrR*relErrR));
	
	for(int i = 0; i<all->GetNbinsX(); i++){
		double erroOnPassValue = (coefficient * sqrt(pass->GetBinContent(i+1))) + (coefficientErr * pass->GetBinContent(i+1)) + (coefficientErr * sqrt(pass->GetBinContent(i+1)));
		double error = sqrt(all->GetBinContent(i+1)) + erroOnPassValue;
		double sub = all->GetBinContent(i+1) - (coefficient * pass->GetBinContent(i+1));
		if(fabs(sub) < error){
			//cout<<"subtraction value: "<< sub<<endl;
			//cout<<"error value: "<< error<<endl;
			sub = error;
			//cout<<"============================="<<endl;
		}
	if(sub < 0){
		cout<<"=============================////////////////////////////"<<endl;
		cout<<"All: "<<all->GetBinContent(i+1) <<", error 1: "<<sqrt(all->GetBinContent(i+1))<<endl;
		cout<<"Pass: "<<pass->GetBinContent(i+1)<<", zarib: "<<coefficient<<", error2:" << sqrt(pass->GetBinContent(i+1))<<endl;
		cout<<"Pass with zarib: "<<coefficient * pass->GetBinContent(i+1)<<", errorWithZarib: "<<erroOnPassValue<<endl;
		cout<<"sub: "<<sub<<", error"<<error<<endl;
	}
		res->SetBinContent(i+1,sub);
	}
	return res;
}

//Left: 1.64167892386143376e+03
//Right: 7.12430859382262497e+02
double divisionError(double Num, double Den){
    if(Num<0 || Den < 0)
        cout<<"======================== Less than zero"<<endl;
    Num = Num * (1.64167892386143376e+03);
    Den = Den * (7.12430859382262497e+02);
    double NumErr = (double)1./(double)sqrt(Num);
    double DenErr = (double)1./(double)sqrt(Den);
    double div = (double)Num/(double)Den;
    double NumErrRel = (double)NumErr/(double)Num;
    double DenErrRel = (double)DenErr/(double)Den;
    return(div*sqrt(NumErrRel*NumErrRel+DenErrRel*DenErrRel));
}
TH1D * divide(TH1D * passed, TH1D * all){
    TH1D * h = new TH1D(*passed);
    h->SetNameTitle("res","res");
    cout<<h->GetNbinsX()<<endl;
    for(int i = 0 ; i<passed->GetNbinsX(); i++){
        if(all->GetBinContent(i+1) != 0 || passed->GetBinContent(i+1) != 0){
            h->SetBinContent(i+1,((double)passed->GetBinContent(i+1)/(double)all->GetBinContent(i+1)));
            h->SetBinError(i+1,divisionError(passed->GetBinContent(i+1),all->GetBinContent(i+1)));
        }
        else
            h->SetBinError(i+1,0.);
    }

//    h->Draw();
    return h;
}

void divide(TString fname, TH1D * passed, TH1D * all){
    TH1D * h = new TH1D(*passed);
    h->SetNameTitle("res","res");
    cout<<h->GetNbinsX()<<endl;
    for(int i = 0 ; i<passed->GetNbinsX(); i++){
        if(all->GetBinContent(i+1) != 0 && passed->GetBinContent(i+1) != 0){
            cout<<"GOOD"<<endl;
            cout<<"=== passed: "<<passed->GetBinContent(i+1)<<", === all: "<<all->GetBinContent(i+1)<<endl;
            cout<<"=== divide: "<<((double)passed->GetBinContent(i+1)/(double)all->GetBinContent(i+1))<<endl;
            h->SetBinContent(i+1,((double)passed->GetBinContent(i+1)/(double)all->GetBinContent(i+1)));
            h->SetBinError(i+1,divisionError(passed->GetBinContent(i+1),all->GetBinContent(i+1)));
        }
        else{
            cout<<"BAD"<<endl;
            h->SetBinContent(i+1,0.);
            h->SetBinError(i+1,0.);
        }
        cout<<"value: "<<h->GetBinContent(i+1)<<", err: "<<h->GetBinError(i+1)<<endl;
    }
    TCanvas c;
    c.cd();
    h->Draw();

    TFile * f = new TFile(fname,"recreate");
    f->cd();
    h->Write();
    f->Save();
    f->Close();
}
void divide(TString fname, TH2D * passed, TH2D * all){
    TH2D * h = new TH2D(*passed);
    h->SetNameTitle("res2D","res2D");
    cout<<h->GetNbinsX()<<endl;
    cout<<h->GetNbinsY()<<endl;
    for(int j = 0 ; j<passed->GetNbinsY(); j++){
	for(int i = 0 ; i<passed->GetNbinsX(); i++){
            if(all->GetBinContent(i+1,j+1) != 0 && passed->GetBinContent(i+1,j+1) != 0){
                cout<<"GOOD"<<endl;
                cout<<"=== passed: "<<passed->GetBinContent(i+1,j+1)<<", === all: "<<all->GetBinContent(i+1,j+1)<<endl;
                cout<<"=== divide: "<<((double)passed->GetBinContent(i+1,j+1)/(double)all->GetBinContent(i+1,j+1))<<endl;
                h->SetBinContent(i+1,j+1,((double)passed->GetBinContent(i+1,j+1)/(double)all->GetBinContent(i+1,j+1)));
                h->SetBinError(i+1,j+1,divisionError(passed->GetBinContent(i+1,j+1),all->GetBinContent(i+1,j+1)));
            }
            else{
                cout<<"BAD"<<endl;
                h->SetBinContent(i+1,j+1,0.);
                h->SetBinError(i+1,j+1,100000.);
            }
            cout<<"value: "<<h->GetBinContent(i+1,j+1)<<", err: "<<h->GetBinError(i+1,j+1)<<endl;
        }
    }
    TCanvas c;
    c.cd();
    h->Draw();

    TFile * f = new TFile(fname,"recreate");
    f->cd();
    h->Write();
    f->Save();
    f->Close();
}
void divide( TH1D * res, TH1D * passed, TH1D * all){
    
    cout<<res->GetNbinsX()<<endl;
    for(int i = 0 ; i<passed->GetNbinsX(); i++){
        if(all->GetBinContent(i+1) != 0 && passed->GetBinContent(i+1) != 0){
            cout<<"GOOD"<<endl;
            cout<<"=== passed: "<<passed->GetBinContent(i+1)<<", === all: "<<all->GetBinContent(i+1)<<endl;
            cout<<"=== divide: "<<((double)passed->GetBinContent(i+1)/(double)all->GetBinContent(i+1))<<endl;
            res->SetBinContent(i+1,((double)passed->GetBinContent(i+1)/(double)all->GetBinContent(i+1)));
            res->SetBinError(i+1,divisionError(passed->GetBinContent(i+1),all->GetBinContent(i+1)));
        }
        else{
            cout<<"BAD"<<endl;
            res->SetBinContent(i+1,0.);
            res->SetBinError(i+1,0.);
        }
        cout<<"value: "<<res->GetBinContent(i+1)<<", err: "<<res->GetBinError(i+1)<<endl;
    }
}
void Divide(string input, string output = "TESTPts.root"){
    string fName = input + "_minChi2.root";
    TFile * in = TFile::Open(fName.c_str());
    TDirectory * main = (TDirectory*)in->Get(input.c_str());
    TDirectory * Left = (TDirectory*)main->Get(string(input+"_LeftRegion_").c_str());
    TList * LeftL = (TList*)Left->GetListOfKeys();
    TDirectory * Right = (TDirectory*)main->Get(string(input+"_RightRegion_").c_str());
    TList * RightL = (TList*)Right->GetListOfKeys();
    TDirectory * NbbMainL = (TDirectory*)Left->Get(LeftL->At(4)->GetName());
    TDirectory * NbbMainR = (TDirectory*)Right->Get(RightL->At(4)->GetName());
    TDirectory * NbbBtagL = (TDirectory*)NbbMainL->Get("Pt");
    TDirectory * NbbBtagR = (TDirectory*)NbbMainR->Get("Pt");

    TH1D * NBBL = (TH1D*)NbbBtagL->Get(string(string(NbbMainL->GetName()) + "_ALL_TRootCaloJet_Pt").c_str());
    TH1D * NBBR = (TH1D*)NbbBtagR->Get(string(string(NbbMainR->GetName()) + "_ALL_TRootCaloJet_Pt").c_str());
    NBBL->SetNameTitle("NBBL","NBBL");
    NBBL->SetLineColor(kMagenta);
    NBBR->SetNameTitle("NBBR","NBBR");
    double LInteg = NBBL->Integral();
    double RInteg = NBBR->Integral();
    NBBL->Scale((double)1./(double)LInteg);
    NBBR->Scale((double)1./(double)RInteg);
    NBBL->Rebin(10);
    NBBR->Rebin(10);
    TH1D * res = new TH1D(*NBBL);
    res->SetNameTitle("PtDivision","P_{T}^{L}/P_{T}^{R}");
    divide(res, NBBL, NBBR);
    TFile * f = new TFile(output.c_str(),"recreate");
    f->cd();
    NBBL->Write();
    NBBR->Write();
    res->Write();
    f->Close();
}

void divide(TH2D * h, TH2D * passed, TH2D * all){
	int nBinsEta = h->GetNbinsX();
	double MinEta = h->GetXaxis()->GetXmin();
	double MaxEta = h->GetXaxis()->GetXmax();
	double etaStep = (double)(MaxEta - MinEta)/(double)nBinsEta;
	int nBinsPt = h->GetNbinsY();
	double MinPt = h->GetYaxis()->GetXmin();
	double MaxPt = h->GetYaxis()->GetXmax();
	double ptStep = (double)(MaxPt - MinPt)/(double)nBinsPt;
    for(int j = 0 ; j<passed->GetNbinsY(); j++){
	for(int i = 0 ; i<passed->GetNbinsX(); i++){
	    cout<<"Pt ("<<j+1<<")= "<<MinPt + (j * ptStep)<<"\tEta ("<<i+1<<") = "<<MinEta + (i * etaStep)<<endl;
            if(all->GetBinContent(i+1,j+1) != 0 && passed->GetBinContent(i+1,j+1) != 0){
                cout<<"\tpassed: "<<passed->GetBinContent(i+1,j+1)<<", === all: "<<all->GetBinContent(i+1,j+1)<<endl;
                cout<<"\tdivide: "<<((double)passed->GetBinContent(i+1,j+1)/(double)all->GetBinContent(i+1,j+1))<<endl;
                h->SetBinContent(i+1,j+1,((double)passed->GetBinContent(i+1,j+1)/(double)all->GetBinContent(i+1,j+1)));
                h->SetBinError(i+1,j+1,divisionError(passed->GetBinContent(i+1,j+1),all->GetBinContent(i+1,j+1)));
            }
            else{
                cout<<"BAD"<<endl;
                h->SetBinContent(i+1,j+1,0.);
                h->SetBinError(i+1,j+1,100000.);
            }
            cout<<"value: "<<h->GetBinContent(i+1,j+1)<<", err: "<<h->GetBinError(i+1,j+1)<<endl;
        }
    }
}

void Divide2D(string input, string output = "TESTPts.root"){
    string fName = input + "_minChi2.root";
    TFile * in = TFile::Open(fName.c_str());
    TDirectory * main = (TDirectory*)in->Get(input.c_str());
    TDirectory * Left = (TDirectory*)main->Get(string(input+"_LeftRegion_").c_str());
    TList * LeftL = (TList*)Left->GetListOfKeys();
    TDirectory * Right = (TDirectory*)main->Get(string(input+"_RightRegion_").c_str());
    TList * RightL = (TList*)Right->GetListOfKeys();
    TDirectory * NbbMainL = (TDirectory*)Left->Get(LeftL->At(3)->GetName());
    TDirectory * NbbMainR = (TDirectory*)Right->Get(RightL->At(3)->GetName());
    
    TH2D * NBBL = (TH2D*)NbbMainL->Get(NbbMainL->GetListOfKeys()->At(2)->GetName());
    TH2D * NBBR = (TH2D*)NbbMainR->Get(NbbMainR->GetListOfKeys()->At(2)->GetName());

    NBBL->SetNameTitle("EtaPtLightL","EtaPtLightL");
    NBBL->SetLineColor(kMagenta);
    NBBR->SetNameTitle("EtaPtLightR","EtaPtLightR");
    double LInteg = NBBL->Integral();
    double RInteg = NBBR->Integral();
    NBBL->Scale((double)1./(double)LInteg);
    NBBR->Scale((double)1./(double)RInteg);
    NBBL->RebinY(10);
    NBBR->RebinY(10);
    TH2D * res = new TH2D(*NBBL);
    res->SetNameTitle("EtatDivision","#eta-P_{T}^{L}/#eta-P_{T}^{R}");
    divide(res, NBBL, NBBR);
    TFile * f = new TFile(output.c_str(),"recreate");
    f->cd();
    NBBL->Write();
    NBBR->Write();
    res->Write();
    f->Close();
}
void Divide2D_LepLight(string input, string output = "EtaPts.root"){
    string fName = input + "_minChi2.root";
    TFile * in = TFile::Open(fName.c_str());

    TDirectory * main = (TDirectory*)in->Get(input.c_str());
    cout<<main->GetName()<<endl;
    main->ls();
    TDirectory * Lep = (TDirectory*)main->Get("Global_LepB");
    cout<<Lep->GetName()<<endl;
    TDirectory * Light = (TDirectory*)main->Get("Global_Light");
    cout<<Light->GetName()<<endl;
    TDirectory * Lep2D = (TDirectory*)Lep->Get("BMatched_2D");
    TDirectory * Light2D = (TDirectory*)Light->Get("BMatched_2D");
    cout<<Light2D->GetName()<<endl;   
    cout<<Lep2D->GetName()<<endl;
    TH2D * Lep2D_ = (TH2D*)Lep2D->Get(Lep2D->GetListOfKeys()->At(2)->GetName());
    TH2D * Light2D_ = (TH2D*)Light2D->Get(Light2D->GetListOfKeys()->At(2)->GetName());
	cout<<Lep2D_->GetName()<<endl;
	cout<<Light2D_->GetName()<<endl;
    
    Light2D_->SetNameTitle("Light","Light");
    double LightInteg = Light2D_->Integral();
    Light2D_->Scale((double)1./(double)LightInteg);
    Light2D_->RebinY(10);

    
    Lep2D_->SetNameTitle("Lep","Lep");
    double LepLInteg = Lep2D_->Integral();
    Lep2D_->Scale((double)1./(double)LepLInteg);
    Lep2D_->RebinY(10);


    TH2D * res = new TH2D(*Lep2D_);

    res->SetNameTitle("Division","#eta-P_{T}^{Lep}/#eta-P_{T}^{Light}");
    cout<<"Lep2D: "<<Lep2D_->GetBinContent(1,2)<<endl;
    divide(res, Lep2D_, Light2D_);
    TFile * f = new TFile(output.c_str(),"recreate");
    f->cd();
    Light2D_->Write();
    Lep2D_->Write();
    res->Write();
    f->Close();
}
int main(int argc, char** argv){
    std::string anaName;
    std::string input;
    std::string Dim = "2D";
    std::string WhichByWhich = "LepLight";

    for (int f = 1; f < argc; f++) {
        std::string arg_fth(*(argv + f));
//        cout<<"-------- "<< arg_fth<<endl;
        if (arg_fth == "out") {
          f++;
          std::string out(*(argv + f));
          anaName = string(out+"_EtaPt.root");
        }else if (arg_fth == "input") {
          f++;
          std::string out(*(argv + f));
          input = string(out);
        }else if (arg_fth == "Dim") {
          f++;
          std::string out(*(argv + f));
          Dim = string(out);
        }else if (arg_fth == "WhichByWhich") {
          f++;
          std::string out(*(argv + f));
          WhichByWhich = string(out);
        }
    }
    if(Dim == "2D" && WhichByWhich == "LepLight")
        Divide2D_LepLight(input,anaName);
    return 1;
}