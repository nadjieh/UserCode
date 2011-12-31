#include <iostream>
#include <sstream>
#include <string>
#include <TFile.h>
#include <TSystem.h>
#include <TProfile.h>
#include <TH1.h>
#include <TH2.h>
#include <bits/stl_vector.h>
#include <TCanvas.h>
#include <TDirectory.h>
#include <TBranch.h>
#include <TTree.h>
#include <vector>
#include <TLorentzVector.h>
#include <TGraphAsymmErrors.h>
#include <TString.h>
#include <TColor.h>
#include <iostream>
#include <TFile.h>
using namespace std;

void sub(TFile * f,TGraphAsymmErrors * method,TGraphAsymmErrors * truth){
//    cout<<"In the sub method"<<endl;
    if(method == NULL || truth == NULL){
        cout<<"NULL reference"<<endl;
        return;
    }
  TH1D * h = new TH1D(method->GetName(),string("#epsilon_{"+ string(method->GetName())+"} - #epsilon_{truth}").c_str(),520,-200.,60.);
//    cout<<"\th defined"<<endl;
//    cout<<"\tgo to loop:"<<endl;
  for(int j = 0; j<method->GetN(); j++){
//    cout<<"\t\t"<<j<<"'th point"<<endl;
    double x,y,xT,yT;
    int tmp = method->GetPoint(j+1,x,y);
    tmp = truth->GetPoint(j+1,xT,yT);
    double delEff = y - yT;
//    cout<<"\tTrue (x,y): "<<"("<<xT<<","<<yT<<")"<<endl;
    double e2 = ((method->GetErrorYhigh(j+1))*(method->GetErrorYhigh(j+1)));
    double eMC2 = (truth->GetErrorYhigh(j+1)*truth->GetErrorYhigh(j+1));
    double err = sqrt(e2 + eMC2);
    h->SetBinContent(j+1,delEff);
    h->SetBinError(j+1,err);
    
  }
  f->cd();
  h->Write();
}

void doSubtraction(string input, string output = "MethodError.root",std::string folder = ""){
    string fName = folder+input + "_minChi2.root";
    cout<<fName<<endl;
    TFile * in = TFile::Open(fName.c_str());
    in->ls();
    cout<<"nnnnnn "<<input<<endl;
    TDirectory * main = (TDirectory*)in->Get(input.c_str());
    cout<<main<<endl;
    TList * l1 = main->GetListOfKeys();
    main->ls();
    TDirectory * Left = (TDirectory*)main->Get(string(input+"_LeftRegion_").c_str());
    TDirectory * NbbMain = (TDirectory*)Left->Get(string(input+"_LeftRegion__B").c_str());
    TDirectory * NbbBtag = (TDirectory*)NbbMain->Get("Btag");
    TDirectory * NbbBtagInteg = (TDirectory*)NbbBtag->Get("Integrated");
    TGraphAsymmErrors * truth = (TGraphAsymmErrors*)NbbBtagInteg->Get(string(input+"_LeftRegion__B_Integrated_Btag_Iinf").c_str());
    truth->SetName("truth");
    TList * LeftRegionList = Left->GetListOfKeys();
    TFile * f = new TFile(output.c_str(),"recreate");
    for(int i = 8; i<LeftRegionList->GetSize(); i += 2){
        int mySize = string(input+"_LeftRegion__NBB_").size();
        TDirectory * fitMain = (TDirectory*)Left->Get(LeftRegionList->At(i)->GetName());
        TDirectory * fitBtag = (TDirectory*)fitMain->Get("Btag");
        TDirectory * fitBtagInteg = (TDirectory*)fitBtag->Get("Integrated");
//        cout<<fitBtagInteg<<endl;
//        fitBtagInteg->ls();
        string tmp = string(fitMain->GetName()).erase((mySize - 1) , 1)+"_Integrated_Btag_Iinf";
//        cout<<tmp<<endl;
        TGraphAsymmErrors * method = (TGraphAsymmErrors*)fitBtagInteg->Get(tmp.c_str());
//        cout<<method<<endl;
        cout<<"source\t"<<string(fitMain->GetName())<<endl;
        string methodName = string(fitMain->GetName()).erase(0,mySize);
        cout<<"at first\t"<<methodName<<endl;
        mySize = methodName.size();
        mySize -=15;
        methodName.erase(mySize);
        cout<<"at the end\t"<<methodName<<"\tSize\t"<<mySize<<endl;
        method->SetName(methodName.c_str());
        if(i == 8)
            method->SetName("bare");
        sub(f,method,truth);
    }


}












void doFdataSubtraction(string inputFmc, string inputFdata, string output = "MethodError.root"){
    string fName = inputFmc + "_minChi2.root";
    TFile * in = TFile::Open(fName.c_str());
    TDirectory * main = (TDirectory*)in->Get(inputFmc.c_str());
    TDirectory * Left = (TDirectory*)main->Get(string(inputFmc+"_LeftRegion_").c_str());
    TDirectory * NbbMain = (TDirectory*)Left->Get(string(inputFmc+"_LeftRegion__B").c_str());
    TDirectory * NbbBtag = (TDirectory*)NbbMain->Get("Btag");
    TDirectory * NbbBtagInteg = (TDirectory*)NbbBtag->Get("Integrated");
    TGraphAsymmErrors * truth = (TGraphAsymmErrors*)NbbBtagInteg->Get(string(inputFmc+"_LeftRegion__B_Integrated_Btag_Iinf").c_str());
    cout<<truth->GetName()<<endl;
    truth->SetName("truth");


    fName.clear();
    fName = inputFdata +  "_minChi2.root";
    in = new TFile(fName.c_str(),"read");
    TDirectory * mainData = (TDirectory*)in->Get(inputFdata.c_str());
    TDirectory * LeftData = (TDirectory*)mainData->Get(string(inputFdata+"_LeftRegion_").c_str());
    TList * LeftRegionList = LeftData->GetListOfKeys();
    TFile * f = new TFile(output.c_str(),"recreate");
    
    for(int i = 8; i<LeftRegionList->GetSize(); i += 2){
        int mySize = string(inputFdata+"_LeftRegion__LepB_").size();
        TDirectory * fitMain = (TDirectory*)LeftData->Get(LeftRegionList->At(i)->GetName());
        TDirectory * fitBtag = (TDirectory*)fitMain->Get("Btag");
        TDirectory * fitBtagInteg = (TDirectory*)fitBtag->Get("Integrated");
//        cout<<fitBtagInteg<<endl;
//        fitBtagInteg->ls();
        string tmp = string(fitMain->GetName()).erase((mySize - 1) , 1)+"_Integrated_Btag_Iinf";
//        cout<<tmp<<endl;
        TGraphAsymmErrors * method = (TGraphAsymmErrors*)fitBtagInteg->Get(tmp.c_str());
//        cout<<method<<endl;
        cout<<"source\t"<<string(fitMain->GetName())<<endl;
        string methodName = string(fitMain->GetName()).erase(0,mySize);
        cout<<"at first\t"<<methodName<<endl;
        mySize = methodName.size();
        mySize -=15;
        methodName.erase(mySize);
        cout<<"at the end\t"<<methodName<<"\tSize\t"<<mySize<<endl;
        method->SetName(methodName.c_str());
        if(i == 8)
            method->SetName("bare");
        sub(f,method,truth);
    }


}
int main(int argc, char** argv){
    std::string inStringMC;
    std::string inStringData;
    std::string foldername;
    bool data = false;
    cout<<"========"<<endl;
    for (int f = 1; f < argc; f++) {
        std::string arg_fth(*(argv + f));
//        cout<<"-------- "<< arg_fth<<endl;
        if (arg_fth == "inputMC") {
          f++;
          std::string out(*(argv + f));
          inStringMC = string(out);
        }else if (arg_fth == "isData") {
          f++;
          std::string in(*(argv + f));
          data = (in == "yes");
          cout<<data<<endl;
        }else if (arg_fth == "inputData") {
          f++;
          std::string out(*(argv + f));
          inStringData = string(out);
        }else if (arg_fth == "folder") {
          f++;
          std::string out(*(argv + f));
          foldername = string(out);
          cout<<foldername<<endl;
        }
    }
    if(data)
        doFdataSubtraction(inStringMC,inStringData,std::string(inStringData+"_MethodErr.root"));
    else
        doSubtraction(inStringMC,std::string(inStringMC+"_MethodErr.root"),foldername);
    return 1;
}
