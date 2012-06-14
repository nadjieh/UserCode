/*
 * For the moment I use the event selection chain in explicitly
 * It comes from AnalysisClasses/EventSelection/macro/t-SingleTopSelection/SelectAndSave.C
 */
/* 
 * File:   SelectAndSave.c
 * Author: ajafari
 *
 * Created on January 29, 2012, 8:18 PM
 */



#include "../../../../TopBrussels/TopTreeProducer/interface/TRootGenEvent.h"

#include "../../../EventSelection/interface/PracticalEvent.h"
#include "../../../PhysicsObjects/interface/SemiLepTopQuark.h"
#include "../../interface/GenSingleTopMaker.h"
#include "../../interface/CosThetaWeighter.h"
#include "../../interface/CosThetaWeightHandler.h"
#include "../../interface/DataPointsChiSquared.h"





#include <sstream>
#include <string>

#include <TApplication.h>
#include <TFile.h>
#include <TH1.h>
#include <TH2.h>
#include <TCanvas.h>
#include <TBranch.h>
#include <TTree.h>
#include <TSystem.h>
#include <vector>

using namespace std;
using namespace TopTree;

int main(int argc, char** argv){
    std::vector<string> inFiles;
    string outFile;
    int nSteps;
    double f0;
    double fminus;
    bool f0Fixed = false;
    bool fminusFixed = true;
    for (int f = 1; f < argc; f++) {
        std::string arg_fth(*(argv + f));

        if (arg_fth == "out") {
          f++;
          std::string out(*(argv + f));
          outFile = string(out);
        }else if (arg_fth == "input") {
          f++;
          std::string in(*(argv + f));
          inFiles.push_back(string("~/"+in));
        }else if (arg_fth == "nSteps") {
          f++;
          std::string in(*(argv + f));
          nSteps = (int)atof(in.c_str());
        }else if (arg_fth == "f0") {
          f++;
          std::string in(*(argv + f));
          f0 = atof(in.c_str());
        }else if (arg_fth == "fminus") {
          f++;
          std::string in(*(argv + f));
          fminus = atof(in.c_str());
        }else if (arg_fth == "isFixed") {
          f++;
          std::string in(*(argv + f));
          if(in == string("f0")){
              f0Fixed = true;
              fminusFixed = false;
          }else if(in == string("fminus")){
              f0Fixed = false;
              fminusFixed = true;
          }
        }
    }


    TApplication theApp("App", &argc, argv);


    TH1D * cosThetaGen = new TH1D("cosThetaGen","cos(#theta)_{gen}",1000, -1,1 );
    TH1D * topMass = new TH1D("topMass","m_{top}",150, 0,300);
    TH1D * Wmass = new TH1D("Wmass","m_{W}",75, 0,150 );
    CosThetaWeightHandler myHandler(f0,fminus,f0Fixed,fminusFixed,nSteps);
    std::vector<TH1D*> cosThetaRW;
    for(int i = 0; i<=nSteps; i++){
        stringstream d;
        d<<"cosThetaRW_"<<i;
        cosThetaRW.push_back(new TH1D(d.str().c_str(),d.str().c_str(),1000, -1,1));
    }
//    CosThetaWeighter myWeighter(6.64263e-01,3.03734e-01,0.1);
    TFile * f = 0;
    for(unsigned int fNumber = 0; fNumber<inFiles.size(); fNumber++){
        cout<<"RunNumber|\tEventNumber|\tLumiBlock|\tptLepton|\trelIso|\tptjet1|\tptjet2|\tMET|\tMT|\tbtagjet1|\tbtagjet2"<<endl;
        f = TFile::Open(inFiles.at(fNumber).c_str());
//        cout<<"nFiles: "<<toy_inputFileNames.size()<<endl;

        TTree* runTree = (TTree*) f->Get("runTree");
        TTree* eventTree = (TTree*) f->Get("eventTree");

        PracticalEvent * pracEvt = new PracticalEvent(eventTree,runTree);
        pracEvt->eventTree->SetBranchStatus("*", 1);

        int ievt = 0;

        while (pracEvt->Next()) {
            ievt++;
//            if(ievt > 10)
//                break;
            GenSingleTopMaker myGenStMaker((TRootNPGenEvent*)pracEvt->NPGenEvtCollection()->At(0));
            if(myGenStMaker.isSemiMuSingleTop){
                cosThetaGen->Fill(myGenStMaker.genSingleTop.cosThetaStar(),1);
                for(int step = 0; step <= nSteps; step++){
                    double W = myHandler.getCosThetaWeight(myGenStMaker.genSingleTop.cosThetaStar(),step);
                    cosThetaRW.at(step)->Fill(myGenStMaker.genSingleTop.cosThetaStar(),W);
                }
                topMass->Fill(myGenStMaker.genSingleTop.top().M(),1);
                Wmass->Fill(myGenStMaker.genSingleTop.W().M(),1);
//                myGenStMaker.genSingleTop.printContent();
            }
        }
        f->Close();
        delete f;
    }
    TFile * myFile = new TFile(string("cosTheta_"+outFile).c_str(), "recreate");
    myFile->cd();
    myFile->mkdir("CosThetaRW")->cd();
    for(int step = 0; step <= nSteps; step++){
        cosThetaRW.at(step)->Write();
    }
    myFile->cd();
    cosThetaGen->Write();
    Wmass->Write();
    topMass->Write();
    DataPointChiSquaredHandler myChiSquaredHandler("GenChi2",cosThetaGen,cosThetaRW,
                               myHandler.getVariatingFractionGraph());
    myChiSquaredHandler.Write(myFile);
    myFile->Write();
    myFile->Close();
    return 0;
}
