#include "ACcalculator.C"
#include "TH2.h"
#include "TFile.h"
void plot(){
	int nFStep = 100;
	TH2D * fR = new TH2D("FR","F_{R}",100,0.,1.,100,0,0.2);
	TH2D * fL = new TH2D("fL","F_{L}",100,0,1.,100,0,1.);
	TH2D * f0 = new TH2D("f0","F_{0}",100,0,1.,100,0.5,1.);
	//Coefficients Q = GetFs(1,0,0,0,172.5);
	//cout<< Q.n <<" "<< Q.m <<" "<< Q.k <<endl;
	for(int i = 0; i < nFStep; i++){
		double vr = ((float(i)) / (float) nFStep); 
		double vl = 1; 
		Coefficients c = GetFs(vl,vr,0,0,172.5); 
		cout<<"FL: "<<c.m<<",\tF0: "<<c.n<<",\tFR: "<<c.k<<"\tVR: "<<vr<<endl; 
		f0->Fill(vr,c.n);
		fL->Fill(vr,c.m); 
		fR->Fill(vr,c.k);
		TFile * f = new TFile("WHel-VL1-VRvar.root","recreate");
		f->cd();
		f0->Write();
		fL->Write();
		fR->Write();
		f->Save();
		f->Close();
	}
};

//VR = 0.55: FL = 0.22, FR = 0.0711659, F0 = 0.706695
