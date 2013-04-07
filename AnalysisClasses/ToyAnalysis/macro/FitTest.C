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
    double ratio = 2870.81/(2.98521000000000004e+03);
    TH1* data = 0;
    TH1* bkginsignal = 0; //for t-processes other than munub
    TH1* bkg = 0; // for non-t processes
    std::vector<TH2*> signalIID; // for munub t-processes
    std::vector<TH3*> signalIIID; // for munub t-processes
    TH1* signal = 0; // for dij = delta_ij rec-gen matrix.
    TFile * file = 0;
    bool singleMatrix = false;
    bool is2Drecgen = false;
    bool do3D = false;
    bool doHist = false;
    double nSignal=0;
    double nBkg=0;
    double nData=0;
    for (int f = 1; f < argc; f++) {
        std::string arg_fth(*(argv + f));
        if (arg_fth == "signal") {
            f++;
            std::string out(*(argv + f));
            file = new TFile(out.c_str(), "read");
            cout << "signal: " << out << endl;
            int pos = string(file->GetName()).find("mu");

            bool muonfile = (pos >= 0 && pos < string(file->GetName()).size());
            if (!do3D || (do3D && !muonfile)) {
                signalIID.push_back(((TH2*) file->Get("Default_allW/Default_allWcosTheta2D"))->RebinY(10));

                cout << "signal2D integral: " << signalIID.at(signalIID.size() - 1)->Integral() << endl;
                signalIID.at(signalIID.size() - 1)->Scale(ratio);
                nSignal+=signalIID.at(signalIID.size() - 1)->Integral();
            }
            if (do3D && muonfile) {
                //                cout << " in 3D :-)" << endl;
                signalIIID.push_back(((TH3D*) file->Get("Default_allW/Default_allWcosTheta3D"))->Rebin3D(1, 10, 1, "newname"));
                signalIIID.at(signalIIID.size() - 1)->Scale(ratio);
                nSignal+=signalIIID.at(signalIIID.size() - 1)->Integral();
            }
            if (bkginsignal == 0)
                bkginsignal = ((TH1*) file->Get("Default_allW/Default_allWcosTheta"))->Rebin(10);
            else
                bkginsignal->Add(((TH1*) file->Get("Default_allW/Default_allWcosTheta"))->Rebin(10));
                        cout << "bkginsignal integral: " << ((TH1*) file->Get("Default_allW/Default_allWcosTheta"))->Integral() << endl;

            //            cout << "3D size: " << signalIIID.size() << endl;
            //            if (!do3D) {
            //                cout << "total signal: " << ((TH1*) file->Get("Default_allW/Default_allWcosTheta"))->Integral() +
            //                        signalIID.at(signalIID.size() - 1)->Integral() << endl;
            //            } else if (muonfile) {
            //                cout << "total signal: " << ((TH1*) file->Get("Default_allW/Default_allWcosTheta"))->Integral() +
            //                        signalIIID.at(signalIIID.size() - 1)->Integral() << endl;
            //            }
        } else if (arg_fth == "data") {
            f++;
            std::string out(*(argv + f));
            file = new TFile(out.c_str(), "read");
            data = ((TH1*) file->Get("Default_allW/Default_allWcosTheta"))->Rebin(10);
            //            cout << data->GetNbinsX() << endl;
            data->Add((((TH2*) file->Get("Default_allW/Default_allWcosTheta2D"))->ProjectionY())->Rebin(10));
        } else if (arg_fth == "bkg") {
            f++;
            std::string out(*(argv + f));
            file = new TFile(out.c_str(), "read");
            if (bkg == NULL)
                bkg = ((TH1*) file->Get("Default_allW/Default_allWcosTheta"))->Rebin(10);
            else
                bkg->Add(((TH1*) file->Get("Default_allW/Default_allWcosTheta"))->Rebin(10));
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
        }
    }
    
    double x[3] = {-1., -1., -1};
    double xerr[3] = {-1., -1., -1};
    double correlation = 0;
    if (is2Drecgen && !singleMatrix && do3D) {
        if (!doHist)
            cout << "In Bias fit: \n\tsize of 2D signal is " << signalIID.size() <<
            "\n\tsize of 3D signal is " << signalIIID.size() << endl;
        cout<<"bkginsignal: "<<bkginsignal->Integral()<<endl;
        if (bkg != NULL && bkginsignal != NULL) {
            bkg->Add(bkginsignal);
        } else if (bkg == NULL && bkginsignal != NULL) {
            bkg = (TH1*) bkginsignal->Clone("myBkg");
        }
        bkg->Scale(ratio);
        cout<<nSignal<<"\t"<<bkg->Integral()<<"\t"<<data->Integral()<<endl;
        std::pair<TF3, LikelihoodFunction*> myLL = LikelihoodFunction::getLLFunctionForBias("LL", bkg, data, signalIID, signalIIID);
        if (!doHist)
            cout << "before get minimum simple: " << endl;
        
        cout << myLL.first.GetNpx() << " " << myLL.first.GetNpy() << " " << myLL.first.GetNpz() << endl;
        myLL.first.SetNpx(5);
        myLL.first.SetNpy(5);
        myLL.first.SetNpz(5);
        if (!doHist)
            cout << myLL.first.GetNpx() << " " << myLL.first.GetNpy() << " " << myLL.first.GetNpz() << endl;
        myLL.first.GetMinimumXYZ(x[0], x[1], x[2]);
        if (!doHist)
            cout << "simple getMin: " << x[0] << "  " << x[1] << "  " << x[2] << endl;
        GetMinimum(myLL.first, x, xerr, correlation);
        delete myLL.second;
    } else if (is2Drecgen && !singleMatrix) {

        if (!doHist)
            cout << "In Generalized fit: \n\tsize of signal is " << signalIID.size() << endl;
        if (bkg != NULL && bkginsignal != NULL) {
            bkg->Add(bkginsignal);
        } else if (bkg == NULL && bkginsignal != NULL) {
            bkg = (TH1*) bkginsignal->Clone("myBkg");
        }
        if (signalIIID.size() != 0) {
            for (unsigned int sig3 = 0; sig3 < signalIIID.size(); sig3++) {
                signalIID.push_back((TH2D*) signalIIID[sig3]->Project3D("yx"));
            }
        }
        cout<<nSignal<<"\t"<<bkg->Integral()<<"\t"<<data->Integral()<<endl;
        TFile * test = new TFile("test2D.root", "recreate");
        test->cd();
        bkg->Write();
        data->Write();
        signalIID.at(0)->Write();
        test->Close();
#ifdef DIAGONALIT_CHECK
        cout << "in diagonal" << endl;
        std::vector<TH2*> diagonalSignal;
        for (unsigned int j = 0; j < signalIID.size(); j++) {
            diagonalSignal.push_back(DiagonalMaker(signalIID.at(j), j));
            delete signalIID.at(j);
        }
        signalIID.clear();
        std::pair<TF3, LikelihoodFunction*> myLL = LikelihoodFunction::getLLFunctionGeneralized("LL", bkg, data, diagonalSignal);
#endif /*DIAGONALIT_CHECK*/
#ifndef DIAGONALIT_CHECK
        std::pair<TF3, LikelihoodFunction*> myLL = LikelihoodFunction::getLLFunctionGeneralized("LL", bkg, data, signalIID);
#endif
        if (!doHist)
            cout << "before get minimum simple: " << endl;
        if (!doHist)
            cout << myLL.first.GetNpx() << " " << myLL.first.GetNpy() << " " << myLL.first.GetNpz() << endl;
        myLL.first.SetNpx(5);
        myLL.first.SetNpy(5);
        myLL.first.SetNpz(5);
        myLL.first.GetMinimumXYZ(x[0], x[1], x[2]);
        if (!doHist)
            cout << "simple getMin: " << x[0] << "  " << x[1] << "  " << x[2] << endl;
        GetMinimum(myLL.first, x, xerr, correlation);
        delete myLL.second;

    } else if (is2Drecgen && singleMatrix) {

        if (bkg != NULL && bkginsignal != NULL)
            bkg->Add(bkginsignal);
        TH2* SingMSignal = 0;
        for (unsigned int p = 0; p < signalIID.size(); p++) {
            if (SingMSignal == 0)
                SingMSignal = signalIID.at(p);
            else
                SingMSignal->Add(signalIID.at(p));
        }
        std::pair<TF3, LikelihoodFunction*> myLL = LikelihoodFunction::getLLFunction("LL", bkg, data, SingMSignal, true);
        myLL.first.GetMinimumXYZ(x[0], x[1], x[2]);
        if (!doHist)
            cout << "simple getMin: " << x[0] << "  " << x[1] << "  " << x[2] << endl;
        GetMinimum(myLL.first, x, xerr, correlation);

        delete myLL.second;
    } else if (!is2Drecgen) {
        if (!doHist)
            cout << "Here Just to check on single top" << endl;
        TH1* Signal1D = 0;
        stringstream s;
        if (!doHist)
            cout << signalIID.size() << endl;
        for (unsigned int p = 0; p < signalIID.size(); p++) {
            s.str("");
            s << p << "_pY";
            if (Signal1D == 0)
                Signal1D = (TH1*) signalIID.at(p)->ProjectionY(s.str().c_str());
            else
                Signal1D->Add((TH1*) signalIID.at(p)->ProjectionY(s.str().c_str()));
        }
//        Signal1D->Add(bkginsignal);
        if (bkginsignal != NULL) {
            if (bkg != NULL) {
                //            cout << "bkginsignal: " << bkginsignal->Integral() << endl;
                if (!doHist) {
                    cout << "bkg: " << bkg->Integral() << endl;
                    cout << "bkginsignal: " << bkginsignal->Integral() << endl;
                }
                bkg->Add(bkginsignal);
            } else {
                bkg = bkginsignal;
                if (!doHist) {
                    cout << "bkg: " << bkg->Integral() << endl;
                    cout << "bkginsignal: " << bkginsignal->Integral() << endl;
                }
            }
        }
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
    }
    //    std::pair<TF3,ChiSquaredFunction*> myChi2 = ChiSquaredFunction::getChiSquaredFunction("Chi2" , bkg , data , signal);
    //    myChi2.first.GetMinimumXYZ(x[0] , x[1] , x[2]);

    //    GetMinimum(myChi2.first,x,xerr,correlation);
    if (!doHist) {
//        double scaledDelta0 = ((x[0] - 0.7063)/xerr[0])*0.149;
//        double scaledDelta1 = ((x[1] - 0.3004)/xerr[1])*0.0891;
        double scaledDelta0 = ((x[0] - 0.7063));
        double scaledDelta1 = ((x[1] - 0.3004));
        double err0 = (0.149025/0.0280)*xerr[0];
        double err1 = (0.0891012/0.0227)*xerr[1];
        cout << "my getMin-vals Delta: " << scaledDelta0 << "  " << scaledDelta1 << "  " << x[2] << endl;
        cout << "my getMin-vals: " << scaledDelta0+0.667767 << "  " << scaledDelta1+0.326762 << "  " << x[2] << endl;
        cout << "my getMin-err: " << err0 << "  " << err1 << "  " << xerr[2] << endl;
        cout << "F0_FNeg correlation: " << correlation / (double) (xerr[0] * xerr[1]) << endl;
        cout << "my getMin-vals: " << x[0] << "  " << x[1] << "  " << x[2] << endl;
        cout << "my getMin-err: " << xerr[0] << "  " << xerr[1] << "  " << xerr[2] << endl;
    }
    if (doHist) {
        cout << "F0->Fill(" << x[0] << ");\tFNeg->Fill(" << x[1] << ");" << endl;
    }
    //    delete myChi2.second;
    return 0;
}






