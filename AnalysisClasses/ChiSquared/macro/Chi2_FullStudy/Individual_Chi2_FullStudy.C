#include "/user/ajafari/CMSSW_3_8_5_patch3/src/AnalysisClasses/ChiSquared/interface/Combinator.h"
#include "/user/ajafari/CMSSW_3_8_5_patch3/src/AnalysisClasses/ChiSquared/interface/TopEvent.h"
#include "/user/ajafari/CMSSW_3_8_5_patch3/src/AnalysisClasses/ChiSquared/interface/ChiSquaredAnalysisHandler.h"
#include "/user/ajafari/CMSSW_3_8_5_patch3/src/AnalysisClasses/EventSelection/interface/PracticalEvent.h"
#include "/user/ajafari/CMSSW_3_8_5_patch3/src/AnalysisClasses/EventSelection/interface/Event.h"
#include "/user/ajafari/CMSSW_3_8_5_patch3/src/AnalysisClasses/EventSelection/interface/GoodObjects.h"




#include<iostream>
#include "TFile.h"
#include "TTree.h"

using namespace std;
int main(int argc, char** argv){
    std::string anaName;
    std::string inputName;
    double Luminosity = 0;
    double intialBeforePresel = 0;
    double XSec = 0;
    bool isTtBar = false;
    bool isData = false;
    double beta = 1;
    double finalCoeff = 1;
    for (int f = 1; f < argc; f++) {
        std::string arg_fth(*(argv + f));
        if (arg_fth == "out") {
          f++;
          std::string out(*(argv + f));
          anaName = string(out);
        }else if (arg_fth == "input") {
          f++;
          std::string in(*(argv + f));
          if(in == "Signal.root" || in == "OtherTtBar.root"){
              isTtBar = true;
	      finalCoeff = 0.108*9*0.676*1.5*0.982*0.950;
	  }else if(in == "twChannel.root"){
	      isTtBar = false;
	      finalCoeff = 0.108*9 * 0.982 * 0.950;
	  }else{
              isTtBar = false;
              finalCoeff =  0.982 * 0.950;
          }
          in ="/user/ajafari/FinalSkims/"+in;
          inputName = in;
        }else if(arg_fth == "XSec"){
          f++;
          std::string Xsec(*(argv + f));
          XSec = atof(Xsec.c_str());
        }else if(arg_fth == "Lumi"){
          f++;
          std::string Lumi(*(argv + f));
          Luminosity = atof(Lumi.c_str());
        }else if(arg_fth == "Initial"){
          f++;
          std::string intialBeforePresel_(*(argv + f));
          intialBeforePresel = atof(intialBeforePresel_.c_str());
        }else if(arg_fth == "Beta"){
          f++;
          std::string intialBeforePresel_(*(argv + f));
          beta = atof(intialBeforePresel_.c_str());
        }else if (arg_fth == "isData") {
            f++;
            std::string in(*(argv + f));
//          cout<<in<<endl;
            if(in == "yes" || in == "YES" || in == "Yes" || in == "y" || in == "Y")
                isData = true;
            else
                isData = false;
//          cout<<"1- "<<isData<<endl;
        }

    }
    TFile * F = new TFile(inputName.c_str(),"read");
    TTree* runTree = (TTree*) F->Get("runTree");
    TTree* eventTree = (TTree*) F->Get("eventTree");

    double weight = (double)(finalCoeff*beta*XSec*Luminosity)/(double)intialBeforePresel;
    if(isData)
	weight = 1.;
    cout<<inputName<<"\n\tWeight: "<<weight<<endl;
    ElectronCuts myElecCuts;
    myElecCuts.Pt = 30;
    myElecCuts.eta = 2.5; myElecCuts.ExLow = 1.4442; myElecCuts.ExHigh = 1.5660;
    myElecCuts.Id = "VBTF70"; myElecCuts.IdSecond = "VBTF95";
    myElecCuts.IsoType = "";
    myElecCuts.D0 = 0.02; 
    myElecCuts.IsoCut = 0.1;
    myElecCuts.drToPV = 1.;
    myElecCuts.SecondEIso = 1.;

    JetCuts myJetCuts;
    myJetCuts.bTagAlgo = "TCHE"; myJetCuts.Pt = 30.; myJetCuts.eta = 2.4;
    myJetCuts.nCaloTower = 0;
    myJetCuts.EmfUp = 1000; myJetCuts.EmfLow = 0.01;
    myJetCuts.fhpd = 0.98; myJetCuts.N90 = 1;
    myJetCuts.bTagCut = 4.;

    MassAndResolution myMassResolution;
    myMassResolution.topMass = 183.3;
    myMassResolution.topRes = 15.16;
    myMassResolution.wMass = 89.95;
    myMassResolution.wRes = 10.99;

    PracticalEvent pracEvt(eventTree,runTree,isTtBar);

    ChiSquaredAnalysisHandler myAnalysis(anaName,/*dobtag*/false,/*dataLike*/false,/*ExtJets*/ true, Luminosity,myMassResolution,
            myElecCuts,myJetCuts,"minChi2");
//    myAnalysis.setChi2Cut(100.);
//    myAnalysis.setTopPtCut(200.);

    myAnalysis.setVerbosity(0);
//    myAnalysis.setVerbosity(6);

    int i = 0;

    while (pracEvt.Next()){
//	if(i<1340)
//		continue;
 //       cout<<"----------------------------------------------------------------------event number : "<<i+1<<endl;
//        if(i<1220)
//            continue;
        myAnalysis.Analyze(&pracEvt,weight,/*JES*/ 1., /*nAna*/ -1, isData);
	i++;
        //if(i > 10000)
        //    break;
    }

    myAnalysis.End();
    cout<<"n4Jets: "<<myAnalysis.n4jets<<endl;
    cout<<"nScrap: "<<myAnalysis.nScrap<<endl;
    cout<<i<<endl;
    return 0;
};


