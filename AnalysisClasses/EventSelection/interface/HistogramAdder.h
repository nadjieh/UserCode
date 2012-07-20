/* 
 * File:   HistogramAdder.h
 * Author: nadjieh
 *
 * Created on May 15, 2012, 12:22 PM
 */

#ifndef HISTOGRAMADDER_H
#define	HISTOGRAMADDER_H

#include "TFile.h"
#include "TDirectory.h"
#include "TH1.h"
#include "TH2.h"
#include "TGraphAsymmErrors.h"
#include "TList.h"
#include "THStack.h"
#include "TCanvas.h"
#include <string>
#include <vector>
#include <iostream>
#include "TColor.h"
#include "TColorWheel.h"
#include "TKey.h"
#include "TClass.h"
#include "TROOT.h"
#include "TSystem.h"
#include "HistogramPlotter.h"

using namespace std;


class HistogramAdder{
public:
    HistogramAdder( bool print = false):doPrint(print){};
    ~HistogramAdder(){};

    void StructureFinder_(TDirectory * f){
        TList * l = f->GetListOfKeys();
        TDirectory * dir = 0;
        TList * l2 = 0;
        for(int i = 1; i<l->GetSize(); i++){
            FolderContent tmp;
            tmp.mainName = string(l->At(i)->GetName());
            dir = (TDirectory*)f->Get(tmp.mainName.c_str());
            l2 = dir->GetListOfKeys();
            tmp.content.clear();
            for(int  j=0; j<l2->GetSize(); j++){
                tmp.content.push_back(string(l2->At(j)->GetName()));
            }
            structure.push_back(tmp);
            delete dir;
        }
    }
    void StructureFinder(TDirectory * f){
        cout<<f->GetName()<<"--------------------------"<<endl;
	TKey *key;
	TIter nextkey(f->GetListOfKeys());
        TDirectory * dir = 0;
        TList * l2 = 0;
	directHists.clear();
	while ((key = (TKey*)nextkey())) {
	    const char *classname = key->GetClassName();
	    TClass *cl = gROOT->GetClass(classname);
            if (!cl) continue;
            if (cl->InheritsFrom(TDirectory::Class())) {
		 FolderContent tmp;
                 tmp.mainName = string(key->GetName());
                 dir = (TDirectory*)f->Get(tmp.mainName.c_str());
                 l2 = dir->GetListOfKeys();
                 tmp.content.clear();
                 for(int  j=0; j<l2->GetSize(); j++){
                     if(string(l2->At(j)->GetName()) == "ttDecayModes")
                         continue;
     	             tmp.content.push_back(string(l2->At(j)->GetName()));
                 }
                 structure.push_back(tmp);
                 delete dir;
	    }else{
		directHists.push_back(string(key->GetName()));
	    }
	}
   }
    void plot(vector<TFile*> files, vector<double> weights,TFile * out){
        for(unsigned int q = 0; q<structure.size(); q++){
            bool mkdir = false;
            TDirectory * tmpdir = 0;

            if(doPrint){
                cout<<"Part "<<q<<", "<<structure.at(q).mainName<<endl;
            }
            for(unsigned int w = 0; w<structure.at(q).content.size(); w++){
                if(doPrint){
                    cout<<"\t"<<w<<", "<<structure.at(q).content.at(w)<<endl;
                }
//                THStack stack(structure.at(q).content.at(w).c_str(),structure.at(q).content.at(w).c_str());
                TH1D * h = 0;
                TH1D * Res = 0;
                for(unsigned int e = 0; e<files.size(); e++){
		    if(doPrint){
                        cout<<"File number "<<e<<": "<<files.at(e)->GetName()<<endl;
                    }
                    TDirectory * d = (TDirectory*)(files.at(e))->Get(structure.at(q).mainName.c_str());
                    if(doPrint){
                        cout<<"Directory number "<<q<<": "<<d->GetName()<<endl;
                    }
//                    d->ls();
//                    
//                    cout<<structure.at(q).content.at(w)<<endl;
                    h = (TH1D*)d->Get(structure.at(q).content.at(w).c_str());
                    h->Sumw2();
                    if(doPrint){
                        cout<<"\tHistogram number "<<w<<": "<<h->Class_Name()<<endl;
                        cout<<h->GetName()<<endl;
                    }
//                    cout<<weights.at(e)<<endl;
		    h->Scale(weights.at(e));
		   
                    if(e == 0){
//                        Res = (TH1D*)h->Clone();
                        Res = h;
                        Res->Sumw2();
                    }
                    else{
                        Res->Add(h);
                        Res->Sumw2();
                    }

                }

                out->cd();
                if(doPrint){
                    cout<<"\tIn outFile "<<out->GetName()<<endl;
                }
                if(!mkdir){
		    mkdir = true;
                    tmpdir = ((TDirectory*)out)->mkdir(structure.at(q).mainName.c_str());
                    tmpdir->cd();
//                    cout<<"I made"<<endl;
                }
                else
                    tmpdir->cd();
//                cout<<"cd success"<<endl;
                if(Res != NULL){
                    Res->Write();
//                    cout<<"I wrote "<<Res->GetName()<<" in "<<tmpdir->GetName()  <<endl;
                }
                if(doPrint){
                    cout<<"\tCanvas is written .... "<<endl;
                }



                if(doPrint){
                    cout<<"\tdirectories deleted ... "<<endl;
                }
            }
        }

        for(unsigned int g = 0; g<directHists.size(); g++){
            TH1D * Res = 0;
	
            for(unsigned int e = 0; e<files.size(); e++){
		cout<<" --- "<<files.at(e)->GetName()<<endl;
     	        TH1D * cf = (TH1D*)files.at(e)->Get(directHists.at(g).c_str());
                cf->Scale(weights.at(e));

                if(e == 0)
                    Res = (TH1D*)cf->Clone();
                else
                    Res->Add(cf);
	    }
	    
	    out->cd();
	    Res->Write();
        }
        out->Write();
        out->Close();
    }
    void printStructure(){
	for(unsigned int i = 0; i<structure.size(); i++){
	    cout<<"Part "<<i<<", "<<structure.at(i).mainName<<endl;
	    for(unsigned int j =0 ;  j<structure.at(i).content.size(); j++){
		cout<<"\t"<<structure.at(i).content.at(j)<<endl;
	    }
	}
	for(unsigned int i = 0; i<directHists.size(); i++){
	    cout<<"Hist "<<i<<", "<<directHists.at(i)<<endl;
        }
	
    }
private:
    vector<FolderContent> structure;
    vector<string> directHists;
//    double Lumi;
    bool doPrint;
};


#endif	/* HISTOGRAMADDER_H */

