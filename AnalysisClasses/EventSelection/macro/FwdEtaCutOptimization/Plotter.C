#include <TFile.h>
#include <TH1.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <string>
#include <vector>
#include <iostream>
using namespace std;

std::vector<TFile*> files(std::vector<std::string> names){
	std::vector<TFile*> fs;
	for(unsigned int n = 0; n<names.size(); n++){
		fs.push_back(TFile::Open(string("OptEta_"+names.at(n)+"_plots.root").c_str()));
		cout<<fs.at(fs.size()-1)->GetName()<<endl;
	}
	return fs;
}
void DrawPlots(TFile* fs,TFile* fs2, std::string address, std::string cname){
	TCanvas c;
	TH1D * ht = (TH1D*)fs->Get(address.c_str());
	TH1D * hb = (TH1D*)fs2->Get(address.c_str());
	int bin = ht->GetXaxis()->GetNbins();
	double t[bin];
	double b[bin];
	for(int i =0; i<bin; i++){
		t[i] = ht->GetBinContent(i+1);
		b[i] = hb->GetBinContent(i+1);
	}
	TGraph * g = new TGraph(bin,t,b);
	g->SetName(cname.c_str());

	c.cd();
	g->Draw("ap");

	c.SaveAs(string(cname+".C").c_str());
}

void Plotter(){
std::vector<std::string> names;
names.push_back("t");
names.push_back("tW");
names.push_back("s");
//names.push_back("tbar");
//names.push_back("tWbar");
//names.push_back("sbar");
names.push_back("dy");
names.push_back("w");
names.push_back("tt");
//names.push_back("qcd");
std::vector<TFile*> fs = files(names);

DrawPlots(fs.at(0),fs.at(1),"nonBEff/JetEta/Integrated/nonBEff_Integrated_JetEta_Iinf_Poisson","tW_t_nonBEff");
DrawPlots(fs.at(0),fs.at(1),"BEff/JetEta/Integrated/BEff_Integrated_JetEta_Iinf_Poisson","tW_t_BEff");
DrawPlots(fs.at(0),fs.at(1),"FwDEff/JetEta/Integrated/FwDEff_Integrated_JetEta_Iinf_Poisson","tW_t_FwDEff");

DrawPlots(fs.at(0),fs.at(2),"nonBEff/JetEta/Integrated/nonBEff_Integrated_JetEta_Iinf_Poisson","s_t_nonBEff");
DrawPlots(fs.at(0),fs.at(2),"BEff/JetEta/Integrated/BEff_Integrated_JetEta_Iinf_Poisson","s_t_BEff");
DrawPlots(fs.at(0),fs.at(2),"FwDEff/JetEta/Integrated/FwDEff_Integrated_JetEta_Iinf_Poisson","s_t_FwDEff");

DrawPlots(fs.at(0),fs.at(3),"nonBEff/JetEta/Integrated/nonBEff_Integrated_JetEta_Iinf_Poisson","dy_t_nonBEff");
DrawPlots(fs.at(0),fs.at(3),"BEff/JetEta/Integrated/BEff_Integrated_JetEta_Iinf_Poisson","dy_t_BEff");
DrawPlots(fs.at(0),fs.at(3),"FwDEff/JetEta/Integrated/FwDEff_Integrated_JetEta_Iinf_Poisson","dy_t_FwDEff");

DrawPlots(fs.at(0),fs.at(4),"nonBEff/JetEta/Integrated/nonBEff_Integrated_JetEta_Iinf_Poisson","w_t_nonBEff");
DrawPlots(fs.at(0),fs.at(4),"BEff/JetEta/Integrated/BEff_Integrated_JetEta_Iinf_Poisson","w_t_BEff");
DrawPlots(fs.at(0),fs.at(4),"FwDEff/JetEta/Integrated/FwDEff_Integrated_JetEta_Iinf_Poisson","w_t_FwDEff");

DrawPlots(fs.at(0),fs.at(5),"nonBEff/JetEta/Integrated/nonBEff_Integrated_JetEta_Iinf_Poisson","tt_t_nonBEff");
DrawPlots(fs.at(0),fs.at(5),"BEff/JetEta/Integrated/BEff_Integrated_JetEta_Iinf_Poisson","tt_t_BEff");
DrawPlots(fs.at(0),fs.at(5),"FwDEff/JetEta/Integrated/FwDEff_Integrated_JetEta_Iinf_Poisson","tt_t_FwDEff");


}
