#include <TH1.h>
#include <TFile.h>
#include <TDirectory.h>
#include <string>
#include <iostream>
#include <math.h>




void Subtract( const TH1D& Total, TH1D& Result){
  // Total Means signal plus background

  double Peak = 91.1;
  double SD = 1.0;

  const double BinWidth  = Total.GetXaxis()->GetBinWidth(1);
  const int nbins = Total.GetNbinsX();
  const double xmin = Total.GetXaxis()->GetXmin();

  const int PeakBin = (int)((Peak - xmin)/BinWidth + 1); // Peak
  const double SDBin = (SD/BinWidth); // Standard deviation
  const int I = (int)((3.0*SDBin > 1.0)  ?  3.0*SDBin  : 1 ); // Interval
  const int D = (int)((10.0*SDBin > 1.0) ?  10.0*SDBin : 1 );  // Distance from peak

  const double IntegralRight = Total.Integral(PeakBin + D, PeakBin + D + I);
  const double IntegralLeft = Total.Integral(PeakBin - D - I, PeakBin - D);

  double SubValue = 0.0;
  double NewValue = 0.0;

  const double Slope     = (IntegralRight - IntegralLeft)/
    (double)((2*D + I )*(I+1));
  const double Intercept = IntegralLeft/(double)(I+1) - 
    ((double)PeakBin - (double)D - (double)I/2.0)*Slope;

  for(int bin = 1; bin < (nbins + 1); bin++){
    SubValue = Slope*bin + Intercept;
    if(SubValue < 0)
      SubValue = 0;

    NewValue = Total.GetBinContent(bin)-SubValue;
    if(NewValue > 0){
      Result.SetBinContent(bin, NewValue);
    }
  }
  Result.SetEntries(Result.Integral());
}

void SBS(std::string fname){
    TFile * f = TFile::Open(fname.c_str());
    TDirectory * iso = (TDirectory*)f->Get("Isolation");
    TDirectory * id = (TDirectory*)f->Get("Identification");

    TDirectory * iso_InvMass = (TDirectory*)iso->Get("TagProbInvMass");
    TDirectory * id_InvMass = (TDirectory*)id->Get("TagProbInvMass");

    TH1D * all = (TH1D*)iso_InvMass->Get("Isolation_ALL_TPO_TagProbInvMass");
    TH1D res_all("resAll","resAll",all->GetXaxis()->GetNbins(), all->GetXaxis()->GetXmin(),all->GetXaxis()->GetXmax());

    TH1D * iso_pass = (TH1D*)iso_InvMass->Get("Isolation_PASSED_TPO_TagProbInvMass");
    TH1D res_iso_pass("resIsoPass","resIsoPass",iso_pass->GetXaxis()->GetNbins(), iso_pass->GetXaxis()->GetXmin(),iso_pass->GetXaxis()->GetXmax());

    TH1D * id_pass = (TH1D*)id_InvMass->Get("Identification_PASSED_TPO_TagProbInvMass");
    TH1D res_id_pass("residPass","residPass",id_pass->GetXaxis()->GetNbins(), id_pass->GetXaxis()->GetXmin(),id_pass->GetXaxis()->GetXmax());

    Subtract(*all,res_all);
    Subtract(*iso_pass,res_iso_pass);
    Subtract(*id_pass,res_id_pass);

    double all_ = res_all.Integral();
    double idPass_ = res_id_pass.Integral();
    double isoPass_ = res_iso_pass.Integral();

    std::cout<<"Id Eff: "<<(double)idPass_/(double)all_<<std::endl;
    std::cout<<"Iso Eff: "<<(double)isoPass_/(double)all_<<std::endl;
}