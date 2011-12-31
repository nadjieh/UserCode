#include <complex>

#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TDirectory.h"
#include "TCanvas.h"
#include "TProfile.h"
#include <iostream>
#include <string>
#include <sstream>
#include <TColor.h>
#include <TColorWheel.h>
using namespace std;
string Info2D(std::string fname, std::string THName){
	TFile * f = new TFile(fname.c_str(),"read");
	TH2D * h = (TH2D*)f->Get(THName.c_str());
	int nBinsEta = h->GetNbinsX();
	double MinEta = h->GetXaxis()->GetXmin();
	double MaxEta = h->GetXaxis()->GetXmax();
	double etaStep = (double)(MaxEta - MinEta)/(double)nBinsEta;
	int nBinsPt = h->GetNbinsY();
	double MinPt = h->GetYaxis()->GetXmin();
	double MaxPt = h->GetYaxis()->GetXmax();
	double ptStep = (double)(MaxPt - MinPt)/(double)nBinsPt;
	stringstream res;
	for(int  i = 0; i<nBinsEta; i++){
            if((MinEta + (i * etaStep)) > 2.4)
                break;
            if(i == 0)
		res << "if(fabs(eta) >= "<<MinEta + (i * etaStep)<<" && fabs(eta) < "<<
		MinEta + ((i+1) * etaStep)<<" ){\n";
            else
		res << "else if(fabs(eta) >= "<<MinEta + (i * etaStep)<<" && fabs(eta) < "<<
		MinEta + ((i+1) * etaStep)<<" ){\n";
		for(int  j = 0; j<nBinsPt; j++){
                    if((MinPt + (j * ptStep)) < 20.)
                        continue;
			res<<"\tif( pt >= "<<MinPt + (j * ptStep)<<" && pt < "<<MinPt + ((j+1) * ptStep)<<" )\n\t\t"
			<<"return(W0 * "<<h->GetBinContent(i+1,j+1)<<");\n";
		}
            res<<"}";
	}
	return res.str();


}
int main(int argc, char** argv){
    std::string histName = "Division";
    std::string input;
    

    for (int f = 1; f < argc; f++) {
        std::string arg_fth(*(argv + f));
//        cout<<"-------- "<< arg_fth<<endl;
        if (arg_fth == "input") {
          f++;
          std::string out(*(argv + f));
          input = string(out);
        }else if (arg_fth == "histName") {
          f++;
          std::string out(*(argv + f));
          histName = string(out);
        }
    }
    
    cout<<"double stupid2D(double W0, double pt, double eta){//LepLight\n"<<Info2D(input,histName)
    <<"\nreturn W0;\n}\n#endif	/* _REWEITHINGFUNCTIONS_H */"<<endl;
    return 1;
}