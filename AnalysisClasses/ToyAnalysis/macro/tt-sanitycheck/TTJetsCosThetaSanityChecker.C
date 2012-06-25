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
    for (int f = 1; f < argc; f++) {
        std::string arg_fth(*(argv + f));

        if (arg_fth == "out") {
          f++;
          std::string out(*(argv + f));
          outFile = string(out+".root");
        }else if (arg_fth == "input") {
          f++;
          std::string in(*(argv + f));
          inFiles.push_back(string("~/"+in));
        }
    }


    TApplication theApp("App", &argc, argv);
    TH1D * cosTheta = new TH1D("cosTheta","cos(#theta)",1000, -1,1 );
    TH1D * cosThetaRW = new TH1D("cosThetaRW","cos(#theta)_{rw}",1000, -1,1 );
    TH1D * cosThetaGen = new TH1D("cosThetaGen","cos(#theta)_{gen}",1000, -1,1 );
    TH1D * topMass = new TH1D("topMass","m_{top}",150, 0,300);
    TH1D * Wmass = new TH1D("Wmass","m_{W}",75, 0,150 );
    TH1D * cosThetaGen_I = new TH1D("cosThetaGen_I","cos(#theta)_{gen}",1000, -1,1 );
    TH1D * topMass_I = new TH1D("topMass_I","m_{top}",150, 0,300);
    TH1D * Wmass_I = new TH1D("Wmass_I","m_{W}",75, 0,150 );
    CosThetaWeighter myWeighter(8.51588e-01,1.19857e-01);
    TFile * f = 0;
    for(unsigned int fNumber = 0; fNumber<inFiles.size(); fNumber++){
        cout<<"RunNumber|\tEventNumber|\tLumiBlock|\tptLepton|\trelIso|\tptjet1|\tptjet2|\tMET|\tMT|\tbtagjet1|\tbtagjet2"<<endl;
        f = TFile::Open(inFiles.at(fNumber).c_str());
//        cout<<"nFiles: "<<toy_inputFileNames.size()<<endl;

        TTree* runTree = (TTree*) f->Get("runTree");
        TTree* eventTree = (TTree*) f->Get("eventTree");
        
//        cout<<runTree->GetName()<<"????"<<endl;

        PracticalEvent * pracEvt = new PracticalEvent(eventTree,runTree,true);
        pracEvt->eventTree->SetBranchStatus("*", 1);



        int ievt = 0;
        

        while (pracEvt->Next()) {
            ievt++;
//            if(ievt > 10)
//                break;
            GenSingleTopMaker myGenStMaker((TRootGenEvent*)pracEvt->GenEvtCollection()->At(0));
            if(myGenStMaker.isSemiMuSingleTop){
                double W = 1;//myWeighter.getWeight(myGenStMaker.genSingleTop.cosThetaStar())*lumiWeight3D;
                if(myGenStMaker.genSingleTop.cosThetaStar() > 1){
                    cout<<"============ what a hell"<<endl;
                    break;
                }
                cosThetaGen->Fill(myGenStMaker.genSingleTop.cosThetaStar(),W);
                topMass->Fill(myGenStMaker.genSingleTop.top().M(),W);
                Wmass->Fill(myGenStMaker.genSingleTop.W().M(),W);
                /*cosThetaGen_I->Fill(myGenStMaker.cosThetaStar,W);
                topMass_I->Fill(myGenStMaker.topMass,W);
                Wmass_I->Fill(myGenStMaker.wMass,W);*/
//                myGenStMaker.genSingleTop.printContent();
            }
        }
        f->Close();
        delete f;
    }
    cout<<"before endjob"<<endl;
    TFile * myFile = new TFile("cosTheta.root", "recreate");
    myFile->cd();
    cosTheta->Write();
    cosThetaRW->Write();
    cosThetaGen->Write();
    Wmass->Write();
    topMass->Write();
    cosThetaGen_I->Write();
    Wmass_I->Write();
    topMass_I->Write();
    myFile->Write();
    myFile->Close();
    return 0;
}

