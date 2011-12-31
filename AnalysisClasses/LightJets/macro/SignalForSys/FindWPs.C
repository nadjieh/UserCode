#include "TGraphAsymmErrors.h"
#include <iostream>
#include <string>
#include <sstream>
#include "TFile.h"
#include "TList.h"
#include "TDirectory.h"

using namespace std;
TGraphAsymmErrors * myGraph(std::string fname){
	TFile * f = TFile::Open(fname.c_str());
	TList * l1 = f->GetListOfKeys();
	cout<<l1->At(0)->GetName()<<endl;
	TDirectory * d1 = (TDirectory*)f->Get(l1->At(0)->GetName());
	TList * l2 = d1->GetListOfKeys();
	cout<<l2->At(0)->GetName()<<endl;
	TDirectory * d2 = (TDirectory*)d1->Get(l2->At(0)->GetName());
	TList * l3 = d2->GetListOfKeys();
	cout<<l3->GetSize()<<endl;
	cout<<l3->At(8)->GetName()<<endl;
	TDirectory * d3 =  (TDirectory*)d2->Get(l3->At(8)->GetName());
	TDirectory * d4 =  (TDirectory*)d3->Get("Btag");
	TDirectory * d5 =  (TDirectory*)d4->Get("Integrated");
	TList * l4 = d5->GetListOfKeys();
	cout<<l4->At(4)->GetName()<<endl;
	TGraphAsymmErrors * tga = (TGraphAsymmErrors*)d5->Get(l4->At(4)->GetName());
	return tga;
}


std::string finWP(TGraphAsymmErrors * tga){
	double minDif75 = 100000.;
	double xminDif75 = 1000.;
	double yminDif75 = 1000.;
	double y = 1000.;
	double x = 1000.;
	double minDif50 = 100000.;
	double xminDif50 = 1000.;
	double yminDif50 = 1000.;
	double minDif25 = 100000.;
	double xminDif25 = 1000.;
	double yminDif25 = 1000.;
	int i75 = -1999;
	int i25 = -1999;
	int i50 = -1999;
	for(int i = 400; i<520;i++){
		tga->GetPoint(i,x,y);
		if(fabs(y-0.75) < minDif75){
			minDif75 = fabs(y-0.75);
			xminDif75 = x;
			yminDif75 = y;
			i75 = i;
		}
		if(fabs(y-0.50) < minDif50){
			minDif50 = fabs(y-0.5);
			xminDif50 = x;
			yminDif50 = y;
			i50 = i;
		}
		if(fabs(y-0.25) < minDif25){
			minDif25 = fabs(y-0.25);
			xminDif25 = x;
			yminDif25 = y;
			i25 = i;
		}
		x = 1000;
		y = 1000;
	}
	stringstream s; s<<"WP75%\n\tefficiency: "<<yminDif75<<"\tError: "<<tga->GetErrorYhigh(i75)<<"\n\tPointNumber: "<<i75<<endl<<"WP50%\n\tefficiency: "<<yminDif50<<"\tError: "<<tga->GetErrorYhigh(i50)<<"\n\tPointNumber: "<<i50<<endl<<"WP25%\n\tefficiency: "<<yminDif25<<"\tError: "<<tga->GetErrorYhigh(i25)<<"\n\tPointNumber: "<<i25<<endl;
	return s.str();
}

string getPoint(TGraphAsymmErrors * tga,int i75,int i50,int i25){
	double x;
	double y;
	stringstream s;

	tga->GetPoint(i75,x,y);
	s<<"WP75%\n\tefficiency: "<<y<<"\tError: "<<tga->GetErrorYhigh(i75)<<"\n\tPointNumber: "<<i75<<endl;
	tga->GetPoint(i50,x,y);
	s<<"WP50%\n\tefficiency: "<<y<<"\tError: "<<tga->GetErrorYhigh(i50)<<"\n\tPointNumber: "<<i50<<endl;
	tga->GetPoint(i25,x,y);
	s<<"WP25%\n\tefficiency: "<<y<<"\tError: "<<tga->GetErrorYhigh(i25)<<"\n\tPointNumber: "<<i25<<endl;
	return s.str();
}

