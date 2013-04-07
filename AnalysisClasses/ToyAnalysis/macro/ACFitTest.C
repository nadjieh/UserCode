/*
 * Aimed to run on selected events
 * 
 */
/* 
 * File:   SelectAndSave.c
 * Author: ajafari
 *
 * Created on January 29, 2012, 8:18 PM
 */
//#define DIAGONALIT_CHECK
#include "../../EventSelection/interface/ElectronSelector.h"

#include "../../EventSelection/interface/Event.h"

#include "../../EventSelection/interface/ElectronHists.h"
#include "../../EventSelection/interface/MuonHists.h"
#include "../../EventSelection/interface/PVHists.h"
#include "../../EventSelection/interface/JetHists.h"
#include "../../EventSelection/interface/JetSelector.h"
#include "../../EventSelection/interface/MuonVetoSelector.h"

#include "../../EventSelection/interface/PrimaryVertexSelector.h"

#include "../../../TopBrussels/TopTreeProducer/interface/TRootMuon.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootElectron.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootJet.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootCaloJet.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootPFJet.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootMET.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootGenEvent.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootNPGenEvent.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootEvent.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootRun.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootParticle.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootMCParticle.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootVertex.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootHLTInfo.h"
#include "../../../AnalysisClasses/EventSelection/interface/PracticalEvent.h"
#include "../../PhysicsObjects/interface/SemiLepTopQuark.h"
#include "../interface/GenSingleTopMaker.h"
#include "../interface/CosThetaWeighter.h"
#include "../interface/CosThetaWeightHandler.h"
#include "../interface/DataPointsChiSquared.h"
#include "../interface/ToyFitter.h"
#include "../../../TopBrussels/TopTreeAnalysis/MCInformation/interface/Lumi3DReWeighting.h"
#include "../../../Orso8TeV/macro/AnomalousCouplings/Coefficients.h"





#include <sstream>
#include <string>

#include <TApplication.h>
#include <TFile.h>
#include <TH1.h>
#include <TF3.h>
#include <TH2.h>
#include <TH3.h>
#include <TCanvas.h>
#include <TBranch.h>
#include <TTree.h>
#include <TSystem.h>
#include <TGraph.h>
#include <map>
#include <vector>
#include "../interface/ValidatorExecuter.h"

using namespace std;

int main(int argc, char** argv) {
    //    sleep(60);

    TH1* data = 0;
    TH1* bkginsignal = 0; //for t-processes other than munub
    TH1* bkg = 0; // for non-t processes
    std::vector<TH1*> signalID; // for AC t-processes
    std::vector<TH2*> signalIID; // for munub t-processes
    std::vector<TH3*> signalIIID; // for munub t-processes
    TH1* signal = 0; // for dij = delta_ij rec-gen matrix.
    TFile * file = 0;
    bool singleMatrix = false;
    bool is2Drecgen = false;
    bool do3D = false;
    bool doHist = false;
    double nSignal = 0;
    double nBkg = 0;
    double nData = 0;
    double VR = 0;
    for (int f = 1; f < argc; f++) {
        std::string arg_fth(*(argv + f));
        if (arg_fth == "signal") {
            f++;
            std::string out(*(argv + f));
            file = new TFile(out.c_str(), "read");
            cout << "signal: " << out << endl;

            signalID.push_back(((TH1*) file->Get("Default_Def/Default_DefcosTheta"))->Rebin(10));

        } else if (arg_fth == "data") {
            f++;
            std::string out(*(argv + f));
            file = new TFile(out.c_str(), "read");
            data = ((TH1*) file->Get("Default_Def/Default_DefcosTheta"))->Rebin(10);
            //            cout << data->GetNbinsX() << endl;
            data->Add((((TH2*) file->Get("Default_Def/Default_DefcosTheta2D"))->ProjectionY())->Rebin(10));
        } else if (arg_fth == "bkg") {
            f++;
            std::string out(*(argv + f));
            file = new TFile(out.c_str(), "read");
            if (bkg == NULL)
                bkg = ((TH1*) file->Get("Default_Def/Default_DefcosTheta"))->Rebin(10);
            else
                bkg->Add(((TH1*) file->Get("Default_Def/Default_DefcosTheta"))->Rebin(10));
            //            cout << "bkg integral: " << bkg->Integral() << endl;
        } else if (arg_fth == "singleMatrix") {
            f++;
            std::string out(*(argv + f));
            if (out == "true")
                singleMatrix = true;
        } else if (arg_fth == "is2Drecgen") {
            f++;
            std::string out(*(argv + f));
            if (out == "yes" || out == "Yes" || out == "Y" || out == "y"
                    || out == "YES")
                is2Drecgen = true;
        } else if (arg_fth == "do3D") {
            f++;
            std::string out(*(argv + f));
            if (out == "yes" || out == "Yes" || out == "Y" || out == "y"
                    || out == "YES")
                do3D = true;
        } else if (arg_fth == "doHist") {
            f++;
            std::string out(*(argv + f));
            if (out == "yes" || out == "Yes" || out == "Y" || out == "y"
                    || out == "YES")
                doHist = true;
        } else if (arg_fth == "VR") {
            f++;
            std::string out(*(argv + f));
            VR = atof(out.c_str());
        }
    }

    double x[3] = {-1., -1., -1};
    double xerr[3] = {-1., -1., -1};
    double correlation = 0;
    //respect the sequence 0: sm, 1: unphys, 2: r
    if (!doHist)
        cout << "Here Just to check on single top" << endl;
    TH1* Signal1D = 0;
    stringstream s;
    Coefficients composition = Weights(1, VR);

    if (!doHist)
        cout << signalID.size() << endl;
    signalID[0]->Scale(composition.m * signalID[0]->GetEntries());
    signalID[1]->Scale(composition.n * signalID[1]->GetEntries());
    signalID[2]->Scale(composition.k * signalID[2]->GetEntries());
    Signal1D = (TH1*) signalID[0]->Clone("sm");
    Signal1D->Scale(composition.m * signalID[0]->GetEntries());
    Signal1D->Add(signalID[1]);
    Signal1D->Add(signalID[2]);
    data = (TH1*) Signal1D->Clone("data");
    bkg = new TH1D("bkg", "bkg", data->GetXaxis()->GetNbins(), data->GetXaxis()->GetXmin()
            , data->GetXaxis()->GetXmax());

    Coefficients fs = GetFs(1,VR,0,0);
    cout<<fs.n<<endl;
    cout<<fs.m<<endl;
    if (!doHist)
        cout << "Data: " << data->Integral() << "\tSignal: " << Signal1D->Integral() << "\tbkg: " << bkg->Integral() << endl;
    std::pair<TF3, LikelihoodFunction*> myLL = LikelihoodFunction::getLLFunction("LL", bkg, data, Signal1D);
    myLL.first.GetMinimumXYZ(x[0], x[1], x[2]);
    if (!doHist) {
        cout << "simple getMin: " << x[0] << "  " << x[1] << "  " << x[2] << endl;
        cout << "simple getMin: " << xerr[0] << "  " << xerr[1] << "  " << xerr[2] << endl;
        cout << "simple correlation: " << correlation << endl;
    }
    GetMinimum(myLL.first, x, xerr, correlation);
    delete myLL.second;

    if (!doHist) {
        cout << "F0_FNeg correlation: " << correlation / (double) (xerr[0] * xerr[1]) << endl;
        cout << "my getMin-vals: " << x[0] << "  " << x[1] << "  " << x[2] << endl;
        cout << "my getMin-err: " << xerr[0] << "  " << xerr[1] << "  " << xerr[2] << endl;
    }

    //    delete myChi2.second;
    return 0;
}






