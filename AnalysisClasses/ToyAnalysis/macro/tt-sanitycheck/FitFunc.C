#include <TMath.h>
#include <TF1.h>
#include <TH1.h>
#include <TFile.h>
#include <TCanvas.h>
 /*--------------------------------------------------------------------*/
 Double_t cosTheta(Double_t *x, Double_t *par)
 /*--------------------------------------------------------------------*/
 {
//par[0]: F0
//par[1]: F-
//par[2]: Norm
//F+ = 1- F- - F0
	Double_t firstTerm = (1-par[0]-par[1])*(1+x[0])*(1+x[0]);
	Double_t secondTerm = par[1]*(1-x[0])*(1-x[0]);
	Double_t thirdTerm = par[0]*(1-x[0]*x[0]);
	return (par[2]*((3.0/8.0)*(firstTerm+secondTerm)+(3.0/4.0)*thirdTerm));
 }
 
  /*--------------------------------------------*/
 void FitCosTheta()
 /*--------------------------------------------*/
 {

//TH1F *brgauss = new TH1F("breitg","", 131, 0, 130);
/*TFile * file = new TFile("cosTheta.root","READ");
 TH1D * h = (TH1D*)file->Get("cosThetaGen");*/
//h->Scale(1./h->Integral());


TFile * file= new TFile("WPol_SelectedTTBars.root","read");
TH1D* h = (TH1D*)file->Get("costheta_mm/hCosThetaPosLepton_Gen");
h->Rebin(20);
 TF1 *f = new TF1("f",cosTheta, -1, 1 ,3);
 Double_t par[3];
 par[0] = 1;
 par[1] = 1;
 par[2] = 12947;//h->GetEntries();
 


 f->SetParameters(par);
 
 h->Fit(f, "RBO");
 h->Fit(f, "RBO");
 h->Fit(f, "RBO");
 h->Fit(f, "RBO");
 h->Fit(f, "RBO");

 }
//costheta_mm/hCosThetaPosLepton_Gen


