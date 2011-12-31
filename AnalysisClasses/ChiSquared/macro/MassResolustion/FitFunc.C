#include <TMath.h>
#include <TF1.h>
#include <TH1.h>
#include <TFile.h>

 /*--------------------------------------------------------------------*/
 Double_t myGauss(Double_t *x, Double_t *par)
 /*--------------------------------------------------------------------*/
 {
//par[0]: mean
//par[1]: sigma
//par[2]: normalization
	Double_t coeff = (double)par[2]/(double)sqrt(2 * M_PI * par[1]);
	Double_t power = (-1)*(double)((x[0]-par[0])*(x[0]-par[0]))/(double)(2*par[1]*par[1]);
	return (coeff*exp(power));
 }
 /*--------------------------------------------------------------------*/
 Double_t breitgausfun(Double_t *x, Double_t *par)
 /*--------------------------------------------------------------------*/
 {

 //Fit parameters:
 //par[0]=Width (scale) Breit-Wigner
 //par[1]=Most Probable (MP, location) Breit mean
 //par[2]=Total area (integral -inf to inf, normalization constant)
 //par[3]=Width (sigma) of convoluted Gaussian function
 //
 //In the Landau distribution (represented by the CERNLIB approximation),
 //the maximum is located at x=-0.22278298 with the location parameter=0.
 //This shift is corrected within this function, so that the actual
 //maximum is identical to the MP parameter.

 // Numeric constants
Double_t invsq2pi = 0.3989422804014; // (2 pi)^(-1/2)
 Double_t twoPi = 6.2831853071795;//2Pi

 // Control constants
 Double_t np = 100.0; // number of convolution steps
 Double_t sc = 4; // convolution extends to +-sc Gaussian sigmas

 // Variables
 Double_t xx;
 Double_t fland;
 Double_t sum = 0.0;
 Double_t xlow,xupp;
 Double_t step;
 Double_t i;


 // Range of convolution integral
 xlow = x[0] - sc * par[3];
 xupp = x[0] + sc * par[3];

 step = (xupp-xlow) / np;

// Convolution integral of Breit and Gaussian by sum
 for(i=1.0; i<=np/2; i++) {
 xx = xlow + (i-.5) * step;
 fland = TMath::BreitWigner(xx,par[1],par[0]);
 sum += fland * TMath::Gaus(x[0],xx,par[3]);

 xx = xupp - (i-.5) * step;
 fland = TMath::BreitWigner(xx,par[1],par[0]);
 sum += fland * TMath::Gaus(x[0],xx,par[3]);
 }
 return (par[2] * step * sum * invsq2pi / par[3]);
 }

 /*--------------------------------------------*/
 void Genbreitgaus()
 /*--------------------------------------------*/
 {
//TH1F *brgauss = new TH1F("breitg","", 131, 0, 130);
 TFile * file = new TFile("masses_.root","READ");
// TH1D * h = (TH1D*)file->Get("TopMassDr");
  TH1D * h = (TH1D*)file->Get("WMassDr");
// h->Rebin(3);
 //h->GetXaxis()->SetRangeUser(20.,180.);
//TF1 *f = new TF1("f",breitgausfun, 20, 300 ,4);
TF1 *f = new TF1("f",breitgausfun, 20, 160 ,4);
//TF1 *f = new TF1("f",myGauss, 50, 450 ,3);
 Double_t par[4];
 par[0] = 2.5;
 par[1] = 80.;
 par[2] = 12455.;
 par[3] = 10;

 f->SetParameters(par);
 //f->FixParameter(0, 180.9);
// f->FixParameter(0, 2.495);
 //f->FixParameter(1, 178.5);
// f->FixParameter(3, 10.0);


 //brgauss->FillRandom("f", 1000);
 h->Fit(f, "RBO");
 h->Fit(f, "RBO");
 h->Fit(f, "RBO");
 h->Fit(f, "RBO");
 h->Fit(f, "RBO");

 }

// 282.6/186
//225.94
//199.8/61
