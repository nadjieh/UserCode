/* 
 * File:   HistogramPlotter.h
 * Author: ajafari
 *
 * Created on February 10, 2011, 12:08 PM
 */

#ifndef HISTOGRAMPLOTTER_H
#define	HISTOGRAMPLOTTER_H

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
#include <sstream>
#include "TColor.h"
#include "TColorWheel.h"
#include "TKey.h"
#include "TClass.h"
#include "TROOT.h"
#include "TSystem.h"

using namespace std;

struct FolderContent {
    string mainName;
    vector<string> content;
};

class HistogramPlotter {
public:

    HistogramPlotter(bool print = false) : doPrint(print) {
    };

    ~HistogramPlotter() {
    };

    void StructureFinder_(TDirectory * f) {
        TList * l = f->GetListOfKeys();
        TDirectory * dir = 0;
        TList * l2 = 0;
        for (int i = 1; i < l->GetSize(); i++) {
            FolderContent tmp;
            tmp.mainName = string(l->At(i)->GetName());
            dir = (TDirectory*) f->Get(tmp.mainName.c_str());
            l2 = dir->GetListOfKeys();
            tmp.content.clear();
            for (int j = 0; j < l2->GetSize(); j++) {
                tmp.content.push_back(string(l2->At(j)->GetName()));
            }
            structure.push_back(tmp);
            delete dir;
        }
    }

    void StructureFinder(TDirectory * f) {
        TKey *key;
        TIter nextkey(f->GetListOfKeys());
        TDirectory * dir = 0;
        //        TDirectory * dir2 = 0;
        TList * l2 = 0;
        //        TList * l3 = 0;
        directHists.clear();
        while ((key = (TKey*) nextkey())) {
            const char *classname = key->GetClassName();
            TClass *cl = gROOT->GetClass(classname);
            if (!cl) continue;
            if (cl->InheritsFrom(TDirectory::Class())) {
                FolderContent tmp;
                tmp.mainName = string(key->GetName());
                dir = (TDirectory*) f->Get(tmp.mainName.c_str());
                l2 = dir->GetListOfKeys();
                tmp.content.clear();
                for (int j = 0; j < l2->GetSize(); j++) {
                    bool is3D = string(l2->At(j)->GetName()).find("3D") < string(l2->At(j)->GetName()).size();
                    is3D = (is3D && string(l2->At(j)->GetName()).find("3D") > 0);
                    if (string(l2->At(j)->GetName()) != string("ttDecayModes") && !is3D)
                        tmp.content.push_back(string(l2->At(j)->GetName()));
                }
                structure.push_back(tmp);
                delete dir;
            } else {
                directHists.push_back(string(key->GetName()));
            }
        }
    }

    void plot(vector<TFile*> files, vector<double> weights, vector<Color_t> colors, vector<string> MCnames, TFile * out, TFile * data) {
        for (unsigned int q = 0; q < structure.size(); q++) {
            bool mkdir = false;
            TDirectory * tmpdir = 0;

            if (doPrint) {
                cout << "Part " << q << ", " << structure.at(q).mainName << endl;
            }
            for (unsigned int w = 0; w < structure.at(q).content.size(); w++) {
                if (doPrint) {
                    cout << "\t" << w << ", " << structure.at(q).content.at(w) << endl;
                }
                THStack stack(structure.at(q).content.at(w).c_str(), structure.at(q).content.at(w).c_str());
                //                cout<<"stack name: "<<stack.GetName()<<endl;
                TH1D * h = 0;
                for (unsigned int e = 0; e < files.size(); e++) {
                    if (doPrint) {
                        cout << "File number " << e << ": " << files.at(e)->GetName() << endl;
                    }
                    TDirectory * d = (TDirectory*) (files.at(e))->Get(structure.at(q).mainName.c_str());
                    if (doPrint) {
                        cout << "Directory number " << q << ": " << d->GetName() << endl;
                    }
                    if (structure.at(q).content.at(w).find("2D") != 0 &&
                            structure.at(q).content.at(w).find("2D") < structure.at(q).content.at(w).size()) {
                        //                        cout << "*****////**** histName  " << structure.at(q).content.at(w) << endl;
                        continue;
                    }
                    h = (TH1D*) d->Get(structure.at(q).content.at(w).c_str());
                    if (doPrint) {
                        cout << "\tHistogram number " << w << ": " << h->GetName() << "\n";
                    }
                    cout << "-----" << endl;
                    h->SetFillColor(colors.at(e));
                    h->SetLineColor(colors.at(e));
                    h->SetTitle(MCnames.at(e).c_str());
                    //                    if (MCnames[e] == "QCD" && h->Integral() != 0)
                    //                        h->Scale(weights.at(e) / h->Integral());
                    //                    else
                    h->Scale(weights.at(e));
                    h->SetStats(kFALSE);
                    string tmpName(h->GetName());
                    //		    if((tmpName.find("__Eta") != 0 && tmpName.find("__Eta")<= tmpName.size()) || (tmpName.find("_Pt") != 0 && tmpName.find("_Pt") <= tmpName.size()))
                    //			h->Rebin(4);
                    if (tmpName.find("topMass") != 0 && tmpName.find("topMass") < tmpName.size())
                        h->Rebin(2);
                    if (tmpName == string(structure.at(q).mainName + "cosTheta")) {
                        //                        cout << "\n" << tmpName << "****************************************************" << endl;
                        //                        h->Rebin(2);
                        cout << "Directory number " << q << ": " << d->GetName() << endl;
                        cout<<MCnames[e] <<": weight = "<<weights[e]<<", Integral = "<< h->Integral()<<endl;
                        h->Rebin(5);
                        TH1D * h2d = ((TH2D*) d->Get(string(structure.at(q).mainName + "cosTheta2D").c_str()))->ProjectionY();
                        //                        h2d->Rebin(2);
                        h2d->Rebin(5);
                        h2d->Scale(weights.at(e));
                        h->Add(h2d);
                        cout<<MCnames[e] <<": weight = "<<weights[e]<<", Integral = "<< h2d->Integral()<<endl;
                        cout<<MCnames[e] <<": weight = "<<weights[e]<<", Integral = "<< h->Integral()<<endl;
                        delete h2d;
                    }
                    if (tmpName == string(structure.at(q).mainName + "cosTheta_MET")) {
                        //                        cout << "\n" << tmpName << "****************************************************" << endl;
                        //                        h->Rebin(2);
                        h->Rebin(5);
                        TH1D * h2d = ((TH2D*) d->Get(string(structure.at(q).mainName + "cosTheta2D_MET").c_str()))->ProjectionY();
                        //                        h2d->Rebin(2);
                        h2d->Rebin(5);
                        h2d->Scale(weights.at(e));
                        h->Add(h2d);
                        delete h2d;
                    }
                    if (tmpName.find("Pt") != 0 && tmpName.find("Pt") < tmpName.size())
                        h->Rebin(2);
                    if (tmpName.find("_Eta") != 0 && tmpName.find("_Eta") < tmpName.size())
                        h->Rebin(5);
                    if (tmpName.find("topMass") != 0 && tmpName.find("topMass") < tmpName.size())
                        cout << "Number of " << MCnames[e] << " is:\t" << h->Integral() << endl;
                    stack.Add(h);
                    //		    stack.ls();
                    //delete d;
                }

                TDirectory * d2 = (TDirectory*) (data)->Get(structure.at(q).mainName.c_str());
                if (doPrint) {
                    cout << "Directory in data: " << d2->GetName() << endl;
                }
                if (structure.at(q).content.at(w).find("2D") != 0 &&
                        structure.at(q).content.at(w).find("2D") < structure.at(q).content.at(w).size())
                    continue;
                TH1D * hdata = (TH1D*) d2->Get(structure.at(q).content.at(w).c_str());
                if (doPrint) {
                    cout << "\tHistogram in data: " << hdata->GetName() << endl;
                    cout << "\t\tIntegral: " << hdata->Integral() << "\tPeak: " << hdata->GetMaximum() << endl;
                }
                hdata->SetTitle("data");
                hdata->SetStats(kFALSE);
                string datatmpName(hdata->GetName());
                //                if((datatmpName.find("__Eta") != 0 && datatmpName.find("__Eta")<= datatmpName.size()) || (datatmpName.find("_Pt") != 0 && datatmpName.find("_Pt") <= datatmpName.size()))
                //                    hdata->Rebin(4);
                if (datatmpName.find("topMass") != 0 && datatmpName.find("topMass") < datatmpName.size()) {
                    cout << "data has " << hdata->Integral() << " entries ..." << endl;
                    hdata->Rebin(2);
                }
                if (datatmpName.find("cosTheta") != 0 && datatmpName.find("cosTheta") < datatmpName.size())
                    //                    hdata->Rebin(2);
                    hdata->Rebin(5);
                if (datatmpName.find("Pt") != 0 && datatmpName.find("Pt") < datatmpName.size())
                    hdata->Rebin(2);
                if (datatmpName.find("_Eta") != 0 && datatmpName.find("_Eta") < datatmpName.size())
                    hdata->Rebin(5);

                hdata->SetMarkerStyle(20);
                TCanvas s;
                s.SetName(structure.at(q).content.at(w).c_str());
                s.cd();
                stack.Draw();
                s.cd();
                hdata->Draw("PE1sames");
                //		hdata->Draw();
                out->cd();
                if (doPrint) {
                    cout << "\tIn outFile " << out->GetName() << endl;
                }
                if (!mkdir) {
                    mkdir = true;
                    tmpdir = ((TDirectory*) out)->mkdir(structure.at(q).mainName.c_str());
                    tmpdir->cd();
                } else
                    tmpdir->cd();
                s.Draw();
                s.Write();
                if (doPrint) {
                    cout << "\tCanvas is written .... " << endl;
                }

                //delete h;
                //delete hdata;
                delete d2;
                if (doPrint) {
                    cout << "\tdirectories deleted ... " << endl;
                }
            }
        }

        for (unsigned int g = 0; g < directHists.size(); g++) {
            THStack cutFlow(directHists.at(g).c_str(), directHists.at(g).c_str());

            for (unsigned int e = 0; e < files.size(); e++) {
                cout << " --- " << files.at(e)->GetName() << endl;
                TH1D * cf = (TH1D*) files.at(e)->Get(directHists.at(g).c_str());
                if (directHists.at(g).find("topMass") != 0 && directHists.at(g).find("topMass") < directHists.at(g).size())
                    cf->Rebin(2);
                if (directHists.at(g).find("cosTheta") != 0 && directHists.at(g).find("cosTheta") < directHists.at(g).size())
                    cf->Rebin(5);
                //                    cf->Rebin(2);
                if (directHists.at(g).find("MT") != 0 && directHists.at(g).find("MT") < directHists.at(g).size())
                    cf->Rebin(4);
                if (directHists.at(g).find("Pt") != 0 && directHists.at(g).find("Pt") < directHists.at(g).size())
                    cf->Rebin(2);
                if (directHists.at(g).find("_Eta") != 0 && directHists.at(g).find("_Eta") < directHists.at(g).size())
                    cf->Rebin(5);
                if (directHists.at(g) == "HT")
                    cf->Rebin(20);
                cf->SetFillColor(colors.at(e));
                cf->SetLineColor(colors.at(e));
                cf->SetTitle(MCnames.at(e).c_str());
                if (directHists.at(g) == "CutFlow") {
                    cout << "CutFlowContent" << endl;
                    cout << "Before scaling: " << endl;
                    for (int nad = 0; nad < cf->GetNbinsX(); nad++)
                        cout << "\t" << cf->GetBinContent(nad + 1) << endl;
                }
                //		cf->Sumw2();	
                //                if (MCnames.at(e) == "QCD" && cf->Integral() != 0)
                //                    cf->Scale(weights[e] / cf->Integral());
                //                else
                cf->Scale(weights.at(e));

                if (directHists.at(g) == "CutFlow") {
                    cout << "After scaling: " << endl;
                    for (int nad = 0; nad < cf->GetNbinsX(); nad++) {
                        cout << "\t" << cf->GetBinContent(nad + 1) << " +/- " << cf->GetBinError(nad + 1) << endl;
                    }
                    if (MCnames.at(e) == "QCD") {
                        cout << "===================================================" << endl;
                        for (int nad = 0; nad < cf->GetNbinsX(); nad++)
                            cout << cf->GetBinContent(nad + 1) << endl;
                        for (int nad = 0; nad < cf->GetNbinsX(); nad++)
                            cout << cf->GetBinError(nad + 1) * cf->GetBinError(nad + 1) << endl;

                        cout << "___________________________________________________" << endl;

                    }
                    cf->GetYaxis()->SetRangeUser(0, 100000200);
                }
                cf->SetStats(kFALSE);
                //                stringstream myname;
                //                myname << cf->GetName() << e << endl;
                //		if(directHists.at(g) != "CutFlow")
                //		    cf->Rebin(4);
                //                cf->SetName(myname.str().c_str());
                cutFlow.Add(cf);
            }
            TCanvas s2;
            s2.cd();
            cutFlow.Draw();
            TH1D * cf = (TH1D*) data->Get(directHists.at(g).c_str());
            if (directHists.at(g).find("topMass") != 0 && directHists.at(g).find("topMass") < directHists.at(g).size())
                cf->Rebin(2);
            if (directHists.at(g).find("cosTheta") != 0 && directHists.at(g).find("cosTheta") < directHists.at(g).size())
                cf->Rebin(5);
            //                cf->Rebin(2);
            if (directHists.at(g).find("Pt") != 0 && directHists.at(g).find("Pt") < directHists.at(g).size())
                cf->Rebin(2);
            if (directHists.at(g).find("_Eta") != 0 && directHists.at(g).find("_Eta") < directHists.at(g).size())
                cf->Rebin(5);
            if (directHists.at(g).find("MT") != 0 && directHists.at(g).find("MT") < directHists.at(g).size())
                cf->Rebin(4);
            if (directHists.at(g) == "HT")
                cf->Rebin(20);
            //	    cf->Sumw2();
            if (directHists.at(g) == "CutFlow") {
                //        cout<<"After scaling: "<<endl;
                for (int nad = 0; nad < cf->GetNbinsX(); nad++)
                    cout << "\t" << cf->GetBinContent(nad + 1) << " +/- " << cf->GetBinError(nad + 1) << endl;
                cf->GetYaxis()->SetRangeUser(0, 100000200);
            }

            cf->SetTitle("data");
            cf->SetStats(kFALSE);
            cf->SetMarkerStyle(20);
            //            if(directHists.at(g) != "CutFlow")
            //                cf->Rebin(4);

            s2.cd();
            cf->Draw("PE1sames");
            out->cd();
            s2.Write(directHists.at(g).c_str());
        }
        out->Write();
        out->Close();
    }

    void printStructure() {
        for (unsigned int i = 0; i < structure.size(); i++) {
            cout << "Part " << i << ", " << structure.at(i).mainName << endl;
            for (unsigned int j = 0; j < structure.at(i).content.size(); j++) {
                cout << "\t" << structure.at(i).content.at(j) << endl;
            }
        }
        for (unsigned int i = 0; i < directHists.size(); i++) {
            cout << "Hist " << i << ", " << directHists.at(i) << endl;
        }

    }
private:
    vector<FolderContent> structure;
    vector<string> directHists;
    //    double Lumi;
    bool doPrint;
    double nQCD;
    double erQCD;
};

#endif	/* HISTOGRAMPLOTTER_H */

