#include "TH1.h"
#include "TH2.h"
#include "TProfile.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TString.h"
void makePlot(TFile * f, TString name){
	TProfile * p3 = ((TH2D*)f->Get("hFinalFPos"))->ProfileX();
	p3->SetTitle("Linearity Check for F_{R}");
	p3->GetYaxis()->SetTitle("F_{R} output");
    p3->GetYaxis()->SetLabelFont(42);
    p3->GetYaxis()->SetLabelSize(0.06);
    p3->GetYaxis()->SetTitleSize(0.06);
    p3->GetYaxis()->SetTitleOffset(0.48);
    p3->GetYaxis()->SetTitleFont(42);
	p3->GetXaxis()->SetTitle("nPEX");
    p3->GetXaxis()->SetLabelFont(42);
    p3->GetXaxis()->SetLabelOffset(0.006);
    p3->GetXaxis()->SetLabelSize(0.06);
    p3->GetXaxis()->SetTitleSize(0.06);
    p3->GetXaxis()->SetTitleOffset(0.66);
    p3->GetXaxis()->SetTitleFont(42);

	TProfile * p2 = ((TH2D*)f->Get("hFinalF0"))->ProfileX();
	p2->SetTitle("Linearity Check for F_{0}");
	p2->GetYaxis()->SetTitle("F_{0} output");
    p2->GetYaxis()->SetLabelFont(42);
    p2->GetYaxis()->SetLabelSize(0.06);
    p2->GetYaxis()->SetTitleSize(0.06);
    p2->GetYaxis()->SetTitleOffset(0.48);
    p2->GetYaxis()->SetTitleFont(42);
	p2->GetXaxis()->SetTitle("F0 input");
    p2->GetXaxis()->SetLabelFont(42);
    p2->GetXaxis()->SetLabelOffset(0.006);
    p2->GetXaxis()->SetLabelSize(0.06);
    p2->GetXaxis()->SetTitleSize(0.06);
    p2->GetXaxis()->SetTitleOffset(0.66);
    p2->GetXaxis()->SetTitleFont(42);

	TProfile * p1 = ((TH2D*)f->Get("hFinalFNeg"))->ProfileX();
	p1->SetTitle("Linearity Check for F_{L}");
	p1->GetYaxis()->SetTitle("F_{L} output");
    p1->GetYaxis()->SetLabelFont(42);
    p1->GetYaxis()->SetLabelSize(0.06);
    p1->GetYaxis()->SetTitleSize(0.06);
    p1->GetYaxis()->SetTitleOffset(0.48);
    p1->GetYaxis()->SetTitleFont(42);
	p1->GetXaxis()->SetTitle("FL input");
    p1->GetXaxis()->SetLabelFont(42);
    p1->GetXaxis()->SetLabelOffset(0.006);
    p1->GetXaxis()->SetLabelSize(0.06);
    p1->GetXaxis()->SetTitleSize(0.06);
    p1->GetXaxis()->SetTitleOffset(0.66);
    p1->GetXaxis()->SetTitleFont(42);

    TCanvas *c = new TCanvas("c", "c",205,89,600,602);
    c->Range(0,0,1,1);
    c->SetFillColor(0);
    c->SetBorderMode(0);
    c->SetBorderSize(2);
    c->SetLeftMargin(0.12);
    c->SetRightMargin(0.01);
    c->SetTopMargin(0.04);
    c->SetFrameBorderMode(0);
	c->Divide(1,3);
	
	c->cd(1); p1->Draw();
	c->cd(2); p2->Draw();
	c->cd(3); p3->Draw();

	c->SaveAs(name+".C");

}
