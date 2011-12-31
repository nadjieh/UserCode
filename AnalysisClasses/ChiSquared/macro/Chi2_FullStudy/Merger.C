
#include <sstream>
#include <iostream>
#include <TFile.h>
#include <TDirectory.h>
#include <TString.h>
#include <TH1.h>
#include <TH2.h>
#include <TCanvas.h>
#include <TBranch.h>
#include <TTree.h>
#include <THStack.h>
#include <TList.h>
#include <TLegend.h>
#include <vector>
#include <TLegendEntry.h>
//#include <TIter.h>
#include <TObject.h>
std::vector<TString> fileNames;
std::vector<TFile*> files;
std::vector<double> weight;
std::vector<TString> CutPart;
std::vector<TString> ObjectPart;
std::vector<TString> SampleNames;
std::vector<TString> multiplicity;

void CutPartAssigner(){
	CutPart.push_back("purity_max Top Pt");
	CutPart.push_back("efficiency_max Top Pt");
	CutPart.push_back("purity_min chi2 in max Top Pt");
	CutPart.push_back("efficiency_min chi2 in max Top Pt");
	CutPart.push_back("purity_min chi2");
	CutPart.push_back("efficiency_min chi2");

}
std::vector<TString> forTex;
void ObjectPartAssigner(){
	ObjectPart.push_back("chi2 fine");
	ObjectPart.push_back("chi2 middle");
	ObjectPart.push_back("chi2 rough");
	ObjectPart.push_back("Mlb");
	ObjectPart.push_back("Top Pt");
}
void multiplicityAssigner(){
	multiplicity.push_back("nGoldenElec");
	multiplicity.push_back("nrGoodJets");
	multiplicity.push_back("nDMuon");
	multiplicity.push_back("nrGoodBJets");
	multiplicity.push_back("nrGoodJets");
	multiplicity.push_back("Ht_GJ");
	multiplicity.push_back("WMass_GJ");
	multiplicity.push_back("WMass_Fine_GJ");
	multiplicity.push_back("TopMass_GJ");
	multiplicity.push_back("M3_GJ");
	multiplicity.push_back("nPV");

}
void SampleNamesAssigner(){// for the legend
	SampleNames.clear();
	SampleNames.push_back("otherTt");
	SampleNames.push_back("WJets");
	SampleNames.push_back("SingleTopS");
	SampleNames.push_back("SingleTopT");
	SampleNames.push_back("SingleTopTW");
	SampleNames.push_back("Vqq");
	SampleNames.push_back("ZJets");
	SampleNames.push_back("signal");// signal
}
void FileNameAssigner(){
	fileNames.clear();
	fileNames.push_back("chi2_Chi2_100_OtherTtBar");
	fileNames.push_back("chi2_Chi2_100_WJets");
	fileNames.push_back("chi2_Chi2_100_SingleTopS");
	fileNames.push_back("chi2_Chi2_100_SingleTopT");
	fileNames.push_back("chi2_Chi2_100_SingleTopTW");
	fileNames.push_back("chi2_Chi2_100_Vqq");
	fileNames.push_back("chi2_Chi2_100_ZJets");
	fileNames.push_back("chi2_Chi2_100_Signal");
}

void WeightAssigner(){
	weight.clear();
	/*weight.push_back(0.0106124);
	weight.push_back(0.310694);
	weight.push_back(0.00037999);
	weight.push_back(0.00396228);
	weight.push_back(0.00230467);
	weight.push_back(0.00693501);
	weight.push_back(0.281263);
	weight.push_back(0.0105644);*/
	weight.push_back(1.);
	weight.push_back(1.);
	weight.push_back(1.);
	weight.push_back(1.);
	weight.push_back(1.);
	weight.push_back(1.);
	weight.push_back(1.);
	weight.push_back(1.);
}

TList * ListOfContent(TDirectory * dir){
	return(dir->GetListOfKeys());
}
void Files(std::vector<TString> filenames){
	
	TFile * f;
	for(uint i = 0; i < filenames.size(); i++){
/*		std::string name = string(filenames.at(i));
		name.replace(0,4,"chi2_Chi2_100");*/
		f = new TFile(string(filenames.at(i)+".root").c_str());
		cout<<f->GetName()<<endl;
		files.push_back(f);
	}
}

void MergeInDirs(){
	FileNameAssigner();
	//std::cout<<"FileNameAssigner"<<std::endl;
	Files(fileNames);
	//std::cout<<"Files"<<std::endl;
	WeightAssigner();
	CutPartAssigner();
	SampleNamesAssigner();
	ObjectPartAssigner();
	/*std::cout<<"WeightAssigner"<<std::endl;
	std::cout<<files.at(0)->GetName()<<std::endl;
	std::cout<<files.at(1)->GetName()<<std::endl;*/
	TFile * out = new TFile("res2.root","RECREATE");
	TDirectory * VeryMainDir = (TDirectory*)files.at(0)->Get(fileNames.at(0));
	TList * lists = VeryMainDir->GetListOfKeys();
	//TString option = "";
	for(int i = 0; i </* 1*/lists->GetSize(); i++){
//		if(i<8)
//			continue;
		TString mainDirName = lists->At(i)->GetName();
		std::cout<<"mainDirName: "<<mainDirName<<std::endl;
		TString className = VeryMainDir->Get(mainDirName)->ClassName();
		std::cout<<"ClassName: "<<className<<std::endl;
		if(className != "TDirectoryFile"){
				std::cout<<"this is histogram!!"<<std::endl;
				continue;
		}
		TDirectory * mainDir = (TDirectory*)VeryMainDir->Get(mainDirName);
		if(mainDir == NULL)
			std::cout<<"No mainDir"<<std::endl;
		TList * secondList = mainDir->GetListOfKeys();
		for(int j = 0; j<secondList->GetSize(); j++){
			TString SecondDirName = secondList->At(j)->GetName();
			std::cout<<"SecondDirName: "<<SecondDirName<<std::endl;
			TDirectory * tmpDir  = (TDirectory*)mainDir->Get(SecondDirName);
			std::cout<<"tmpDir Name: "<<tmpDir->GetName()<<std::endl;
			TList * histsLists = (TList*)tmpDir->GetListOfKeys();
			std::cout<<"List size = "<<histsLists->GetSize()<<std::endl;
			if(histsLists == NULL)
				std::cout<<"No histsLists"<<std::endl;
			TString title = "";
			for(int l = 0; l < histsLists->GetSize(); l++){
				TString histName = histsLists->At(l)->GetName();
				//TCanvas * c = new TCanvas();
				className = tmpDir->Get(histName)->ClassName();
				std::cout<<"ClassName: "<<className<<std::endl;
				if(className != "TH1D"){
					std::cout<<"this is not histogram!!"<<std::endl;
					continue;
				}
				std::cout<<histName<<" i: "<<i<<"_"<<CutPart.at(i)<<"   j: "<<j<<"_"<<ObjectPart.at(j)<<std::endl;
				THStack * hs = new THStack(histName,(CutPart.at(i)+"_"+ObjectPart.at(j)));
				std::cout<<"before loop on files: "<<std::endl;
				for(uint k = 0; k < files.size(); k++){
					TDirectory * CVerymainDir = (TDirectory*)files.at(k)->Get(fileNames.at(k));
					TDirectory * CmainDir = (TDirectory*)CVerymainDir->Get(mainDirName);
					TDirectory * CsecondDir = (TDirectory*)CmainDir->Get(SecondDirName);
					std::cout<<"File number "<<k<<" "<<CmainDir->GetName()<<std::endl;
					std::cout<<"\t"<<CsecondDir->GetName()<<std::endl;
					TH1D * tmp = (TH1D*)CsecondDir->Get(histName);
					if(tmp == NULL)
						std::cout<<"================="<<std::endl;
					tmp->Scale(weight.at(k));
					tmp->SetFillColor(k+1);
					tmp->SetLineColor(k+1);	
					title = tmp->GetXaxis()->GetTitle();
					std::cout<<title<<std::endl;
					hs->Add(tmp);
				}
				std::cout<<"before out->cd"<<std::endl;
				out->cd();
				TDirectory * my_main;
				TDirectory * my_second;
				if((TDirectory*)out->Get(mainDirName) == NULL)
					my_main = out->mkdir(mainDirName);
				else 
					my_main = (TDirectory*)out->Get(mainDirName);
				my_main->cd();
				if((TDirectory*)my_main->Get(SecondDirName) == NULL)
					my_second = my_main->mkdir(SecondDirName);
				else 
					my_second = (TDirectory*)my_main->Get(SecondDirName);
				
				my_second->cd();
				TCanvas c;
				c.cd(0);
				hs->Draw();
				TLegend* leg = c.BuildLegend();
				if (leg != NULL) {
					leg->SetX1NDC(0.35);
					leg->SetX2NDC(0.65);
					leg->SetY1NDC(0.9);
					leg->SetY2NDC(0.995);
			                TList *lop = leg->GetListOfPrimitives();
			                TIter next(lop);
			                TObject *o = 0;
					uint s = 0;
                			while ((o = next()))
                    			if (o->InheritsFrom(TLegendEntry::Class())){
	                        		((TLegendEntry*) o)->SetOption("f");
						std::cout << s << ":" << ((TLegendEntry*) o)->GetLabel() << "  " << SampleNames.at(s) << std::endl ;
						((TLegendEntry*) o)->SetLabel(SampleNames.at(s));
						if(s == 8)
							((TLegendEntry*) o)->SetLabel("QCD");
						s++;
					}
            			}
				if(hs->GetXaxis() == NULL)
					std::cout<<"Null Axis"<<std::endl;
				else
					hs->GetXaxis()->SetTitle(title);
				hs->Write();
                                c.SetName(histName+"_Legend");
				c.Write();
			}
		}
	}
	out->Close();
}

void Eff_Pur(TH1D * Signal, TH1D * bkg){
	double allSignal = Signal->Integral();
	double allBkg = bkg->Integral();
	TH1D * SigEff = new TH1D(*Signal);
	SigEff->SetNameTitle("SignalEfficiency","Signal Efficiency");
	TH1D * BKGEff = new TH1D(*Signal);
	BKGEff->SetNameTitle("BkgEfficiency","Bkg Efficiency");
	//TGraph * SignalVsBkg = new TGraph("","",Signal->GetNbinsX(),0.,100.,Signal->GetNbinsX(),0.,100.);
	//SignalVsBkg->SetNameTitle("SignalVsBkg","Signal vs Bkg");
	TH1D * EffTPur = new TH1D(*Signal);
	EffTPur->SetNameTitle("EffTPur","efficiency times purity");
	TH1D * SigPutity = new TH1D(*Signal);
	SigPutity->SetNameTitle("SigPutity","Signal Purity");
	for(int i = 0; i<Signal->GetNbinsX(); i++){
		double nSig = Signal->Integral(1, i+1);
		double nBkg = bkg->Integral(1, i+1);
		double signalEff = (double)nSig/(double)allSignal;
		double bkgEff = (double)nBkg/(double)allBkg;
		double sigPurity = (double)nSig/(double)(nBkg+nSig);
		SigEff->SetBinContent(i+1,signalEff);
		BKGEff->SetBinContent(i+1,bkgEff);
		//SignalVsBkg->SetBinContent(i+1,bkgEff);
		EffTPur->SetBinContent(i+1,signalEff*sigPurity);
		SigPutity->SetBinContent(i+1,sigPurity);
	}
	TFile * out = new TFile("W-Signal.root","recreate");
	out->cd();
	SigEff->Write();
	BKGEff->Write();
	//SignalVsBkg->Write();
	EffTPur->Write();
	SigPutity->Write();
	out->Close();
}
void Sig_bkg_Eff(TH1D * Signal, TH1D * bkg){
	TH2D * SignalVsBkg = new TH2D("","",Signal->GetNbinsX(),0.,1.,Signal->GetNbinsX(),0.,1.);
	SignalVsBkg->SetNameTitle("SignalVsBkg","Signal vs Bkg");
	for(int i = 0; i<Signal->GetNbinsX(); i++){
		double signalEff = Signal->GetBinContent(i+1);
		double bkgEff = bkg->GetBinContent(i+1);
		SignalVsBkg->Fill(bkgEff,signalEff);
	}
	TFile * out = new TFile("minChi2-W-Signal-effs-TopPt.root","recreate");
	out->cd();
	SignalVsBkg->Write();
	out->Close();
}
