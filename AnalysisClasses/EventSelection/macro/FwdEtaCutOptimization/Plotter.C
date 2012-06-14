#include <TFile.h>
#include <TH1.h>
#include <TH2.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <map>
using namespace std;
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

        NHt["t"]= -1;
        NHt["tbar"]= -1;
        NHt["tW"]= -1;
        NHt["tWbar"]= -1;
        NHt["tt"]=-1;
        NHt["s"]= -1;
        NHt["sbar"]= -1;
        NHt["w"]= -1;
        NHt["dy"]= -1;
        NHt["qcd"]= -1;
//
        NFwdEta["t"]= -1;
        NFwdEta["tbar"]= -1;
        NFwdEta["tW"]= -1;
        NFwdEta["tWbar"]= -1;
        NFwdEta["tt"]=-1;
        NFwdEta["s"]= -1;
        NFwdEta["sbar"]= -1;
        NFwdEta["w"]= -1;
        NFwdEta["dy"]= -1;
        NFwdEta["qcd"]= -1;
    }
    ~SamplesInfo(){};
    
    std::map<string, double> Xsections;//pb
    std::map<string, double> N0;

    std::map<string, double> NSelected;
    std::map<string, double> NHt;
    std::map<string, double> NFwdEta;

    
};

std::vector<TFile*> files(SamplesInfo s){
	std::vector<TFile*> fs;
	std::map<string, double>::iterator it = s.Xsections.begin();
	for(; it != s.Xsections.end(); it++){
		fs.push_back(TFile::Open(string("OptEta_"+it->first+"_plots.root").c_str()));
		cout<<fs.at(fs.size()-1)->GetName()<<endl;
	}
	return fs;
}
std::vector<TFile*> files(std::vector<std::string> names){
	std::vector<TFile*> fs;
	for(unsigned int n = 0; n<names.size(); n++){
		fs.push_back(TFile::Open(string("OptEta_"+names.at(n)+"_plots.root").c_str()));
		cout<<fs.at(fs.size()-1)->GetName()<<endl;
	}
	return fs;
}
void setNumbersInSamplesInfo(SamplesInfo& s, string histNameEta, string histHt){
	std::map<string, double>::iterator it = s.Xsections.begin();
	for(; it != s.Xsections.end(); it++){
		TFile* f = TFile::Open(string("Wshape/Wshape_"+it->first+"_plots.root").c_str());
		TH1D * h = (TH1D*)f->Get(histNameEta.c_str());
		s.NFwdEta[it->first] = h->GetEntries();
		h = (TH1D*)f->Get(histHt.c_str());
		s.NHt[it->first] = h->GetEntries();
	}
}
SamplesInfo CalculteNExps(SamplesInfo s, double Lumi){
	std::map<string, double>::iterator it = s.Xsections.begin();
	SamplesInfo final;
	for(; it != s.Xsections.end(); it++){
		double NExp0 = it->second*Lumi;
		double weight = (double)NExp0/(double)s.N0[it->first];
		double NExpEta = weight*s.NFwdEta[it->first];
		double NExpHt = weight*s.NHt[it->first];
		double NExp = weight*s.NSelected[it->first];
		final.NFwdEta[it->first]=NExpEta;
		final.NHt[it->first]=NExpHt;
		final.NSelected[it->first]=NExp;
	}
	return final;
}

void WriteTable(string etaName, string htName, double Lumi){
	SamplesInfo in;
	setNumbersInSamplesInfo(in,  etaName,  htName);
	SamplesInfo out = CalculteNExps(in,Lumi);
	stringstream S;
	stringstream Seff;
	S<<out.NFwdEta["t"]+out.NFwdEta["tbar"]<<"\t"<<out.NFwdEta["tW"]+out.NFwdEta["tWbar"]
	<<"\t"<<out.NFwdEta["s"]+out.NFwdEta["sbar"]<<"\t"<<out.NFwdEta["tt"]<<"\t"<<out.NFwdEta["w"]
	<<"\t"<<out.NFwdEta["dy"]<<"\t"<<out.NFwdEta["qcd"];
	Seff<<(double)(out.NFwdEta["t"]+out.NFwdEta["tbar"])/(double)(out.NSelected["t"]+out.NSelected["tbar"])
	<<"\t"<<(double)(out.NFwdEta["tW"]+out.NFwdEta["tWbar"])/(double)(out.NSelected["tW"]+out.NSelected["tWbar"])
	<<"\t"<<(double)(out.NFwdEta["s"]+out.NFwdEta["sbar"])/(double)(out.NSelected["s"]+out.NSelected["sbar"])
	<<"\t"<<(double)(out.NFwdEta["tt"])/(double)(out.NSelected["tt"])
	<<"\t"<<(double)(out.NFwdEta["w"])/(double)(out.NSelected["w"])
	<<"\t"<<(double)(out.NFwdEta["dy"])/(double)(out.NSelected["dy"])
	<<"\t"<<(double)(out.NFwdEta["qcd"])/(double)(out.NSelected["qcd"]);
	cout<<"Eta: -------------------"<<endl;
	cout<<"signal\ttW\ts\ttt\tw\tdy\tqcd"<<endl;
	cout<<S.str().c_str()<<endl;
	cout<<Seff.str()<<endl;
	cout<<"S/B(W): "<<(double)(out.NFwdEta["t"]+out.NFwdEta["tbar"])/(double)out.NFwdEta["w"]<<endl;
	cout<<"S/B(total): "<<(double)(out.NFwdEta["t"]+out.NFwdEta["tbar"])/(double)(out.NFwdEta["w"]+
	out.NFwdEta["tW"]+out.NFwdEta["tWbar"]+out.NFwdEta["s"]+out.NFwdEta["sbar"]+out.NFwdEta["tt"]+
	out.NFwdEta["dy"]+out.NFwdEta["qcd"])<<endl;
	cout<<"------------------------"<<endl;

	S.str("");
	Seff.str("");
	S<<out.NHt["t"]+out.NHt["tbar"]<<"\t"<<out.NHt["tW"]+out.NHt["tWbar"]
	<<"\t"<<out.NHt["s"]+out.NHt["sbar"]<<"\t"<<out.NHt["tt"]<<"\t"<<out.NHt["w"]
	<<"\t"<<out.NHt["dy"]<<"\t"<<out.NHt["qcd"];
	Seff<<(double)(out.NHt["t"]+out.NHt["tbar"])/(double)(out.NSelected["t"]+out.NSelected["tbar"])
	<<"\t"<<(double)(out.NHt["tW"]+out.NHt["tWbar"])/(double)(out.NSelected["tW"]+out.NSelected["tWbar"])
	<<"\t"<<(double)(out.NHt["s"]+out.NHt["sbar"])/(double)(out.NSelected["s"]+out.NSelected["sbar"])
	<<"\t"<<(double)(out.NHt["tt"])/(double)(out.NSelected["tt"])
	<<"\t"<<(double)(out.NHt["w"])/(double)(out.NSelected["w"])
	<<"\t"<<(double)(out.NHt["dy"])/(double)(out.NSelected["dy"])
	<<"\t"<<(double)(out.NHt["qcd"])/(double)(out.NSelected["qcd"]);
	cout<<"\n\nHt: -------------------"<<endl;
	cout<<"signal\ttW\ts\ttt\tw\tdy\tqcd"<<endl;
	cout<<S.str().c_str()<<endl;
	cout<<Seff.str().c_str()<<endl;
	cout<<"S/B(W): "<<(double)(out.NHt["t"]+out.NHt["tbar"])/(double)out.NHt["w"]<<endl;
	cout<<"S/B(total): "<<(double)(out.NHt["t"]+out.NHt["tbar"])/(double)(out.NHt["w"]+
	out.NHt["tW"]+out.NHt["tWbar"]+out.NHt["s"]+out.NHt["sbar"]+out.NHt["tt"]+
	out.NHt["dy"]+out.NHt["qcd"])<<endl;
	cout<<"------------------------"<<endl;


	S.str("");
	S<<out.NSelected["t"]+out.NSelected["tbar"]<<"\t"<<out.NSelected["tW"]+out.NSelected["tWbar"]
	<<"\t"<<out.NSelected["s"]+out.NSelected["sbar"]<<"\t"<<out.NSelected["tt"]<<"\t"<<out.NSelected["w"]
	<<"\t"<<out.NSelected["dy"]<<"\t"<<out.NSelected["qcd"];
	cout<<"\nNSelected: -------------------"<<endl;
	cout<<"signal\ttW\ts\ttt\tw\tdy\tqcd"<<endl;
	cout<<S.str().c_str()<<endl;
	cout<<"S/B(W): "<<(double)(out.NSelected["t"]+out.NSelected["tbar"])/(double)out.NSelected["w"]<<endl;
	cout<<"S/B(total): "<<(double)(out.NSelected["t"]+out.NSelected["tbar"])/(double)(out.NSelected["w"]+
	out.NSelected["tW"]+out.NSelected["tWbar"]+out.NSelected["s"]+out.NSelected["sbar"]+out.NSelected["tt"]+
	out.NSelected["dy"]+out.NSelected["qcd"])<<endl;
	cout<<"------------------------"<<endl;


};


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

void Overlay(std::vector<TFile*> fs, std::vector<std::string> names ,std::string address, std::string cname){
	TCanvas c;
	for(unsigned int i = 0; i < fs.size(); i++ ){
		TH2D * ht2 = (TH2D*)fs.at(i)->Get(address.c_str());
		int bin1 = 0;
		int bin2 = ht2->GetYaxis()->GetNbins();
		TH1D * ht = ht2->ProjectionX(std::string(names.at(i)+"_"+std::string(ht2->GetName())).c_str(), bin1,bin2);
		cout<<ht->GetName()<<endl;
		ht->SetLineColor(i+4);
		ht->SetTitle(names.at(i).c_str());
		ht->Rebin(25);
		c.cd();
		if(i == 0)		
			ht->DrawNormalized();
		else
			ht->DrawNormalized("sames");
	}
	c.SaveAs(string(cname+".C").c_str());
}

void Plotter(){
std::vector<std::string> names;
names.push_back("w");
names.push_back("t");
names.push_back("tt");
names.push_back("tbar");
names.push_back("tWbar");
names.push_back("sbar");
names.push_back("tW");
names.push_back("s");
names.push_back("dy");
names.push_back("qcd");
//std::vector<TFile*> fs = files(names);

/*DrawPlots(fs.at(0),fs.at(1),"nonBEff/JetEta/Integrated/nonBEff_Integrated_JetEta_Iinf_Poisson","tW_t_nonBEff");
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
*/
//Overlay(fs,names,"cosTheta_EtaFwd","EtaFwd");
WriteTable("EtaFwDCut/EtaFwDCutcosTheta", "HtCut/HtCutcosTheta", 3792.4);

}
