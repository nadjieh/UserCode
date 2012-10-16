/* 
 * File:   Plotting.C
 * Author: ajafari
 *
 * Created on February 10, 2011, 1:31 PM
 */

#include "../../interface/HistogramPlotter.h"
#include "../../interface/HistogramAdder.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "TColor.h"
#include "TColorWheel.h"
using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    vector<TFile*> MCfiles;
    vector<string> MCnames;
    vector<Color_t> Colors;
    vector<double> initials;
    vector<double> weights;
    vector<double> beta;
    string outFileName;
    TFile * data;
    double LumiA = 1;
    double LumiB = 1;
    string prefix = "Summer11_";
    for (int f = 1; f < argc; f++) {
        std::string arg_fth(*(argv + f));

        if (arg_fth == "out") {
            f++;
            std::string out(*(argv + f));
            outFileName = out;
        } else if (arg_fth == "LumiA") {
            f++;
            std::string Xsec(*(argv + f));
            LumiA = atof(Xsec.c_str());
        } else if (arg_fth == "prefix") {
            f++;
            std::string Xsec(*(argv + f));
            prefix = Xsec;
        } else if (arg_fth == "LumiB") {
            f++;
            std::string Xsec(*(argv + f));
            LumiB = atof(Xsec.c_str());
        } else if (arg_fth == "initial") {
            f++;
            std::string Xsec(*(argv + f));
            initials.push_back(atof(Xsec.c_str()));
        } else if (arg_fth == "mcinput") {
            cout << "-------------------------" << endl;
            f++;
            std::string Xsec(*(argv + f));

            //            if (Xsec.find("0") <= Xsec.size() && Xsec.find("0") >= 0) {
            //                //	cout<<"QCD -----"<<endl;
            //                Colors.push_back(kBlue - 6);
            if (Xsec == "137" || Xsec == "1075" || Xsec == "1065") {
                Colors.push_back(kOrange + 3);
            } else if (Xsec == "t" || Xsec == "tbar") {
                Colors.push_back(kRed);
            } else if (Xsec == "s" || Xsec == "sbar") {
                Colors.push_back(kYellow);
            } else if (Xsec == "tW" || Xsec == "tWbar") {
                Colors.push_back(kOrange);
            } else if (Xsec == "tt")
                Colors.push_back(kMagenta - 3);
            else if (Xsec == "w")
                Colors.push_back(kAzure);
            else if (Xsec == "dy") {
                Colors.push_back(kGreen + 1);
            } else if (Xsec == "qcd")
                Colors.push_back(kOrange + 3);


            //          Xsec = "./IsoMu17/TypeIMET/TypeIMET_"+Xsec+"_plots.root";
            //          Xsec = "./IsoMu17/PU3TypeIMET/vNotFlatMC/PU3TypeIMET_"+Xsec+"_plots.root";
            //          Xsec = "./WmassSmeared/CorrPU3TypeIMET/PU3Corr_TypeIMET_"+Xsec+"_plots.root";
            //          Xsec = "./both_newMassPlot/TypeIMETII_"+Xsec+"_plots.root";
            //          Xsec ="~/archive/2012/AnalysisClasses/EventSelection/macro/Plotting/May/Wshape/Wshape_" + Xsec + "_plots.root";
            //          Xsec ="./for2Dfit/WithGenInfo_" + Xsec + "_plots.root";
            //          Xsec ="./for2Dfit/2D_CreateWeighedHists_" + Xsec + "_plots.root";
            cout << "Here I am! " << Xsec << "\t" << (bool)(Xsec == "1025") << endl;
            if (Xsec == "137" || Xsec == "1075" || Xsec == "1065" || Xsec == "1104" || Xsec == "1025" )
                Xsec = "dataDrivenQCD.root";
            else
                Xsec = prefix + Xsec + "_plots.root";
            //          Xsec ="CreateWeighedHists_" + Xsec + "_plots.root";
            //          Xsec ="./Converted/CovertedSel_" + Xsec + "_plots.root";
            TFile * tmp = TFile::Open(Xsec.c_str());
            MCfiles.push_back(tmp);
        } else if (arg_fth == "beta") {
            f++;
            std::string Xsec(*(argv + f));
            beta.push_back(atof(Xsec.c_str()));
        } else if (arg_fth == "mcname") {
            f++;
            std::string Xsec(*(argv + f));

            cout << "process " << Xsec << "\tweight: " << weights.at(weights.size() - 1) << endl;
            cout << "input file " << MCfiles.at(MCfiles.size() - 1)->GetName() << endl;
            MCnames.push_back(Xsec);
        } else if (arg_fth == "data") {
            f++;
            std::string preSelEff(*(argv + f));
            //          preSelEff ="./IsoMu17/TypeIMET/TypeIMET_" + preSelEff + ".root";
            //          preSelEff ="./both_newMassPlot/TypeIMETII_" + preSelEff + "_plots.root";
            //          preSelEff ="~/archive/2012/AnalysisClasses/EventSelection/macro/Plotting/May/Wshape/Wshape_" + preSelEff + "_plots.root";
            //          preSelEff ="./for2Dfit/WithGenInfo_" + preSelEff + "_plots.root";
            preSelEff = prefix + preSelEff + "_plots.root";
//                        preSelEff = "dataDrivenQCD.root";
            //          preSelEff ="./for2Dfit/2D_CreateWeighedHists_" + preSelEff + "_plots.root";
            //          preSelEff ="CreateWeighedHists_" + preSelEff + "_plots.root";
            //          preSelEff ="./Converted/CovertedSel_" + preSelEff + "_plots.root";
            data = TFile::Open(preSelEff.c_str());
        } else if (arg_fth == "xsec") {
            f++;
            std::string preSelEff(*(argv + f));
            double W = atof(preSelEff.c_str());
            W = (LumiA * beta.at(beta.size() - 1) + LumiB) * W / (int) initials.at(initials.size() - 1);
            //	  double o = 0.108*9*0.676*1.5*0.982*0.950;
            //	  if(string(MCfiles.at(MCfiles.size() -1)->GetName()) == "/user/ajafari/FinalSkims/Hists/Histograms_ttbar.root"){
            //		W = o * W;
            //		cout<<"=======   "<<W<<endl;
            //	  }
            //	  else if(string(MCfiles.at(MCfiles.size() -1)->GetName()) == "/user/ajafari/FinalSkims/Hists/Histograms_twChannel.root"){
            //		W = W*0.108*9 * 0.982 * 0.950;
            //	  }
            //	  else
            //		W = W * 0.96; //for lepton id 0.999 is for Summer11
            cout << "Corrected Weight: " << W << endl;
            cout << "Beta Value: " << beta.at(beta.size() - 1) << endl;
            cout << "Normalized for beta: " << W << endl;
            weights.push_back(W);
            //	  weights.push_back(W*beta.at(beta.size()-1));
            //	  weights.push_back(W*beta.at(beta.size()-1)*1.5);
        }
    }
    cout << "Input files: " << MCfiles.size() << endl;
    cout << "Colors: " << Colors.size() << endl;
    cout << "Weights: " << weights.size() << endl;
    cout << "names: " << MCnames.size() << endl;
    cout << "LumiA: " << LumiA << endl;
    cout << "LumiB: " << LumiB << endl;
    //    HistogramPlotter histPlot(Lumi,true);
    for (unsigned int i = 0; i < MCfiles.size(); i++)
        cout << MCnames.at(i) << "\t";
    cout << endl;
    /*    for(unsigned int i = 0; i< MCfiles.size(); i++)
              cout<<((TH1D*)MCfiles.at(i)->Get("finalMT"))->GetEntries()<<"\t";
        cout<<endl;*/
//    HistogramPlotter histPlot(true);
//    histPlot.StructureFinder(data);
//    histPlot.printStructure();
//    TFile * out = new TFile(outFileName.c_str(), "recreate");
//    histPlot.plot(MCfiles, weights, Colors, MCnames, out, data);


        HistogramAdder histPlot(false,true);
        histPlot.StructureFinder(data);
        histPlot.printStructure();
        TFile * out = new TFile(outFileName.c_str(), "recreate");
        histPlot.plot(MCfiles, weights, out);



    return 0;
}

