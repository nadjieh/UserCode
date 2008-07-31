#include "tdrstyle.C"

void plots(TString var = "ht",TString var2 = "HT")
{
  setTDRStyle();
 /* TH1F* h2 = getHisto("histo_SingleTopSkimQCDpp.root",var);
  TH1F* h1 = getHisto("histo_SingleTopSkimQCDgumbo.root",var);
  TH1F* h3 = getHisto("histo_SingleTopSkimQCDstew.root",var);*/
  TH1F* h5 = getHisto("histo_SingleTopSkimFastMADGRAPH.root",var);
  TH1F* h6 = getHisto("histo_SingleTopSkimFastMADGRAPH.root",var2);
  //TH1F* h4 = getHisto("histo_SingleTopSkimSignalMCatNLO.root",var);

  cout << "I'm plotting the following histogram: " << var << endl;

  h6->SetLineColor(1);
  h5->SetLineColor(2);
  //h3->SetLineColor(3);

  normalize(h6);
  normalize(h5);
//  normalize(h3);
  

  TCanvas c1("c1","Comparison",1);
  c1.SetFillColor(10);
  c1.cd();
  h6->DrawCopy();
  h5->DrawCopy("same");
  //h3->DrawCopy("same");

  TLegend *legend = new TLegend(0.75,0.75,0.95,0.95,"","NDC");
  legend->AddEntry(h6,"MADGRAPH / Less P_{z} of #nu","l");
  legend->AddEntry(h5,"MADGRAPH / More P_{z} of #nu","l");
  //legend->AddEntry(h3,"QCD stew","l");
  legend->Draw();

  c1.Update();

  TString gif("comparison_MADGRAPH_WPt");
  gif+=var;
  gif+=".gif";
  c1.Print(gif);

}

TH1F* getHisto(TString sample, TString var)
{
  TFile *file = new TFile(sample);
  file->ls();
  TH1F *histo = (TH1F*)file->Get(var);
  histo->SetLineWidth(2);
  histo->SetTitle("P_{t} of W using different P_{z} of #nu solutions");
  histo->GetXaxis()->SetTitle("P_{t}");
  histo->GetYaxis()->SetTitle("");
  return histo;
}

void normalize(TH1F* histo)
{
  double scale = 1./(histo->Integral());
  histo->Scale(scale);
}
