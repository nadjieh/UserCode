/* 
 * File:   Plotting.C
 * Author: ajafari
 *
 * Created on February 10, 2011, 1:31 PM
 */

#include "../../../AnalysisClasses/EventSelection/interface/HistogramPlotter.h"
#include "../../../AnalysisClasses/EventSelection/interface/HistogramAdder.h"
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
    vector<double> Uncs;
    vector<double> beta;
    string outFileName;
    TFile * data;

    //    string prefix = "Summer11_";
    string prefix = "";
    for (int f = 1; f < argc; f++) {
        std::string arg_fth(*(argv + f));

        if (arg_fth == "out") {
            cout << "out -------------------------" << endl;
            f++;
            std::string out(*(argv + f));
            outFileName = out;
        } else if (arg_fth == "prefix") {
            cout << "I saw PREFIX" << endl;
            f++;
            std::string Xsec(*(argv + f));
            prefix = Xsec;
        } else if (arg_fth == "mcinput") {
            cout << "mcinput -------------------------" << endl;
            f++;
            std::string Xsec(*(argv + f));
            if (Xsec == "TChannel" || Xsec == "TbarChannel") {
                Colors.push_back(kRed);
            } else if (Xsec == "SChannel" || Xsec == "SbarChannel") {
                Colors.push_back(kYellow);
            } else if (Xsec == "TWChannel" || Xsec == "TbarWChannel") {
                Colors.push_back(kOrange);
            } else if (Xsec == "TTBar")
                Colors.push_back(kMagenta - 3);
            else if (Xsec == "WJets" || Xsec == "WTemplateDefFormat" || Xsec == "Data")
                Colors.push_back(kAzure);
            else if (Xsec == "ZJets") {
                Colors.push_back(kGreen + 1);
            } else if (Xsec == "QCD")
                Colors.push_back(kOrange + 3);
            else if (Xsec == "WW" || Xsec == "WZ" || Xsec == "ZZ") {
                Colors.push_back(kCyan);
            }
            Xsec = prefix + Xsec + "_plots.root";
            //          Xsec ="CreateWeighedHists_" + Xsec + "_plots.root";
            //          Xsec ="./Converted/CovertedSel_" + Xsec + "_plots.root";
            TFile * tmp = TFile::Open(Xsec.c_str());
            MCfiles.push_back(tmp);
        } else if (arg_fth == "beta") {
            cout << "beta -------------------------" << endl;
            f++;
            std::string Xsec(*(argv + f));
            beta.push_back(atof(Xsec.c_str()));
            cout << MCfiles[MCfiles.size() - 1]->GetName() << "\t" << beta[beta.size() - 1] << endl;
        } else if (arg_fth == "mcname") {
            cout << "mcname -------------------------" << endl;
            f++;
            std::string Xsec(*(argv + f));

            //            cout << "process " << Xsec << "\tweight: " << weights.at(weights.size() - 1) << endl;
            //            cout << "input file " << MCfiles.at(MCfiles.size() - 1)->GetName() << endl;
            MCnames.push_back(Xsec);
        } else if (arg_fth == "unc") {
            cout << "Uncertainty on beta -------------------------" << endl;
            f++;
            std::string Xsec(*(argv + f));

            //            cout << "process " << Xsec << "\tweight: " << weights.at(weights.size() - 1) << endl;
            Uncs.push_back(atof(Xsec.c_str()));
            cout << "input file " << MCfiles.at(MCfiles.size() - 1)->GetName() << "\n\tuncertainty: "
                    << Uncs.at(Uncs.size() - 1) << endl;
        } else if (arg_fth == "data") {
            cout << "data -------------------------" << endl;
            f++;
            std::string preSelEff(*(argv + f));
            preSelEff = prefix + preSelEff + "_plots.root";
            data = TFile::Open(preSelEff.c_str());
        }
    }
    cout << "PREFIX: " << prefix << endl;
    cout << "Input files: " << MCfiles.size() << endl;
    cout << "Colors: " << Colors.size() << endl;
    cout << "Betas: " << beta.size() << endl;
    cout << "names: " << MCnames.size() << endl;

    //    HistogramPlotter histPlot(Lumi,true);
    for (unsigned int i = 0; i < MCfiles.size(); i++)
        cout << MCnames.at(i) << "\t";
    cout << endl;
    if (prefix == "../forStack/" || prefix == "../WTemps/plots/WTemp_") {
        HistogramPlotter histPlot(false);
        histPlot.StructureFinder(data);
        histPlot.printStructure();
        TFile * out = new TFile(outFileName.c_str(), "recreate");
        histPlot.plot(MCfiles, beta, Colors, MCnames, out, data);
    } else if (prefix == "../forAdding/" || prefix == "../WTemps/plots/unc/WTemp_") {
        //
        HistogramAdder histPlot(false, false);
        histPlot.StructureFinder(data);
        histPlot.printStructure();
        TFile * out = new TFile(outFileName.c_str(), "recreate");
        histPlot.plot(MCfiles, beta, out, Uncs);
    } else if (prefix != "" ) {
        HistogramAdder histPlot(false, false);
        histPlot.StructureFinder(data);
        histPlot.printStructure();
        TFile * out = new TFile(outFileName.c_str(), "recreate");
        histPlot.plot(MCfiles, beta, out, Uncs);
    }


    return 0;
}

