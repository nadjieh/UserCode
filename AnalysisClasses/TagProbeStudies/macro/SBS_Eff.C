/* 
 * File:   SBS_Eff.C
 * Author: ajafari
 *
 * Created on December 21, 2010, 5:21 PM
 */
#include "TFile.h"
#include "TDirectory.h"
#include "TList.h"
#include "TH1.h"
#include <string>
#include <vector>
#include <TTree.h>

#include "../../../Base/BaseAnalysis/interface/EfficiencyHandler.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootTagProbeObject.h"
using namespace std;
using namespace TopTree;

/*
 * 
 */
int main(int argc, char** argv) {
    std::vector<std::string> inFileName;
    std::string outFileName;
    for (int f = 1; f < argc; f++) {
        std::string arg_fth(*(argv + f));
//        cout<<"-------- "<< arg_fth<<endl;
        if (arg_fth == "out") {
          f++;
          outFileName = std::string(*(argv + f));
        }else if (arg_fth == "input") {
          f++;
//          inFileName.push_back( std::string("/home/ajafari/rootfiles/TopTrees/7TeV/July10/TagAndProbe/106._76._"+string(*(argv + f))));
//          inFileName.push_back( std::string("/home/ajafari/rootfiles/TopTrees/7TeV/December10/TagAndProbe/106._76._"+string(*(argv + f))));
          inFileName.push_back( std::string(string(*(argv + f))));
        }
    }

    TFile * subVal = new TFile(inFileName.at(0).c_str(), "read");
    TFile * main = new TFile(inFileName.at(1).c_str(), "read");

    TDirectory * subVal_ID = (TDirectory*)subVal->Get("ExtIdentification");
    TDirectory * subVal_ISO = (TDirectory*)subVal->Get("ExtIsolation");

    TDirectory * main_ID = (TDirectory*)main->Get("Identification");
    TDirectory * main_ISO = (TDirectory*)main->Get("Isolation");
    
    TList * propertyNamesList = subVal_ID->GetListOfKeys();

    
    TList * tmp = 0;
    std::vector<TH1D*> propsAll_ID;
    std::vector<TH1D*> propsPass_ID;
    std::vector<TH1D*> propsAll_ISO;
    std::vector<TH1D*> propsPass_ISO;
    for(int i = 0; i<propertyNamesList->GetSize(); i++){
        tmp = ((TDirectory*)main_ID->Get(propertyNamesList->At(i)->GetName()))->GetListOfKeys();
        TH1D * main_pass_ID = (TH1D*)((TDirectory*)main_ID->Get(propertyNamesList->At(i)->GetName()))->Get(tmp->At(1)->GetName());
        TH1D * main_all_ID = (TH1D*)((TDirectory*)main_ID->Get(propertyNamesList->At(i)->GetName()))->Get(tmp->At(0)->GetName());


        tmp = ((TDirectory*)main_ISO->Get(propertyNamesList->At(i)->GetName()))->GetListOfKeys();
        TH1D * main_pass_ISO = (TH1D*)((TDirectory*)main_ISO->Get(propertyNamesList->At(i)->GetName()))->Get(tmp->At(1)->GetName());
        TH1D * main_all_ISO = (TH1D*)((TDirectory*)main_ISO->Get(propertyNamesList->At(i)->GetName()))->Get(tmp->At(0)->GetName());



        tmp = ((TDirectory*)(((TDirectory*)subVal_ID->Get(propertyNamesList->At(i)->GetName()))->Get("ToBeSubtracted")))->GetListOfKeys();
//        cout<<tmp->At(1)->GetName()<<endl;
        TH1D * subVal_pass_ID =(TH1D*)(((TDirectory*)(((TDirectory*)subVal_ID->Get(propertyNamesList->At(i)->GetName()))->Get("ToBeSubtracted")))->Get(tmp->At(1)->GetName()));
        TH1D * subVal_all_ID = (TH1D*)(((TDirectory*)(((TDirectory*)subVal_ID->Get(propertyNamesList->At(i)->GetName()))->Get("ToBeSubtracted")))->Get(tmp->At(0)->GetName()));
//        cout<<subVal_pass_ID->GetName()<<endl;

        tmp = ((TDirectory*)(((TDirectory*)subVal_ISO->Get(propertyNamesList->At(i)->GetName()))->Get("ToBeSubtracted")))->GetListOfKeys();
        TH1D * subVal_pass_ISO =(TH1D*)(((TDirectory*)(((TDirectory*)subVal_ISO->Get(propertyNamesList->At(i)->GetName()))->Get("ToBeSubtracted")))->Get(tmp->At(1)->GetName()));
        TH1D * subVal_all_ISO = (TH1D*)(((TDirectory*)(((TDirectory*)subVal_ISO->Get(propertyNamesList->At(i)->GetName()))->Get("ToBeSubtracted")))->Get(tmp->At(0)->GetName()));
        cout<<propertyNamesList->At(i)->GetName()<<endl;
        if(string(propertyNamesList->At(i)->GetName()) == "ProbeEta"){
            for(int k =0 ; k <5; k++){
                cout<<"subVal:\n";
                cout<<"\tALL_ID: "<<subVal_all_ID->GetBinContent(k+1)<<"\tPass_ID: "<<subVal_pass_ID->GetBinContent(k+1)<<endl;
                cout<<"mainVal:\n";
                cout<<"\tALL_ID: "<<main_all_ID->GetBinContent(k+1)<<"\tPass_ID: "<<main_pass_ID->GetBinContent(k+1)<<endl;
            }
        }

        subVal_pass_ID->Scale(-1);
        subVal_all_ID->Scale(-1);
        subVal_pass_ISO->Scale(-1);
        subVal_all_ISO->Scale(-1);

        TH1D * mainPassId = new TH1D(*main_pass_ID);
        mainPassId->SetName("mainPassId");
        TH1D * mainPassIso = new TH1D(*main_pass_ISO);
        mainPassIso->SetName("mainPassIso");

        TH1D * mainAllId = new TH1D(*main_all_ID);
        mainAllId->SetName("mainAllId");
        TH1D * mainAllIso = new TH1D(*main_all_ISO);
        mainAllIso->SetName("mainAllIso");

        main_pass_ID->Add(subVal_pass_ID);
        main_all_ID->Add(subVal_all_ID);
        main_pass_ISO->Add(subVal_pass_ISO);
        main_all_ISO->Add(subVal_all_ISO);

//        if(string(propertyNamesList->At(i)->GetName()) == "ProbeEta"){
//            for(int k =0 ; k <5; k++){
//                cout<<"mainVal After SUbtraction:\n";
//                cout<<"\tALL_ID: "<<main_all_ID->GetBinContent(k+1)<<"\tPass_ID: "<<main_pass_ID->GetBinContent(k+1)<<endl;
//            }
//        }
        for(int k = 0; k<5; k++){
            if(main_pass_ID->GetBinContent(k+1) > main_all_ID->GetBinContent(k+1)){
                main_pass_ID->SetBinContent(k+1,mainPassId->GetBinContent(k+1));
                main_pass_ID->SetBinError(k+1,mainPassId->GetBinError(k+1));
                main_all_ID->SetBinContent(k+1,mainAllId->GetBinContent(k+1));
                main_all_ID->SetBinError(k+1,mainAllId->GetBinError(k+1));
            }
            if(main_pass_ISO->GetBinContent(k+1) > main_all_ISO->GetBinContent(k+1)){
                main_pass_ISO->SetBinContent(k+1,mainPassIso->GetBinContent(k+1));
                main_pass_ISO->SetBinError(k+1,mainPassIso->GetBinError(k+1));
                main_all_ISO->SetBinContent(k+1,mainAllIso->GetBinContent(k+1));
                main_all_ISO->SetBinError(k+1,mainAllIso->GetBinError(k+1));
            }
        }
        propsPass_ID.push_back(new TH1D(*main_pass_ID));
        propsAll_ID.push_back(new TH1D(*main_all_ID));

        propsPass_ISO.push_back(new TH1D(*main_pass_ISO));
        propsAll_ISO.push_back(new TH1D(*main_all_ISO));

        delete main_pass_ID;
        delete main_all_ID;

        delete main_pass_ISO;
        delete main_all_ISO;

        delete subVal_pass_ID;
        delete subVal_all_ID;

        delete subVal_pass_ISO;
        delete subVal_all_ISO;

        delete mainAllId;
        delete mainAllIso;
        delete mainPassId;
        delete mainPassIso;

        
    }

    EfficiencyHandler<TRootTagProbeObject> id("ExtIdentification",propsPass_ID,propsAll_ID);
    id.setVerbosity(0);
    EfficiencyHandler<TRootTagProbeObject> iso("ExtIsolation",propsPass_ISO,propsAll_ISO);
    iso.setVerbosity(0);
    id.setSelfEff(false);
    iso.setSelfEff(false);

    TFile * out = new TFile(outFileName.c_str(),"recreate");
    id.WriteAll(out);
    iso.WriteAll(out);
    out->Close();
    return 0;
}

