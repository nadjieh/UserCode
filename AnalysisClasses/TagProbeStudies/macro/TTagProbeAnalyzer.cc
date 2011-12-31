/* 
 * File:   TTagProbeAnalyzer.cc
 * Author: ajafari
 *
 * Created on October 28, 2010, 4:29 PM
 */

#include "TTree.h"
#include "TBranch.h"
#include "TFile.h"
#include "TClonesArray.h"
#include "../../../AnalysisClasses/EventSelection/interface/PracticalEvent.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootHLTInfo.h"
#include "../../../Base/BaseAnalysis/interface/EfficiencyHandler.h"
#include "../../../AnalysisClasses/EventSelection/interface/ElectronSelector.h"
#include "../../../AnalysisClasses/TagProbeStudies/interface/TagProbeObjectPropertis.h"
#include "../../../AnalysisClasses/ChiSquared/interface/DR.h"
#include "../../../AnalysisClasses/TagProbeStudies/interface/TagProbEffHandler.h"

using namespace std;
using namespace TopTree;

/*
 *
 */
ElectronSelector s("n");
bool IDCondition(const TRootTagProbeObject * c){
    return(s.isVBTF70Id((TRootElectron*)c));
}
bool ISOCondition(const TRootTagProbeObject * c){
    return(((double)c->combinedIso(3,3,3)/(double)c->Et())<0.1);
}
bool AlwaysTrue(const TRootTagProbeObject * c){
    return(true);
}
//EfficiencyHandler<TRootTagProbeObject> IdEff("Identification");
//EfficiencyHandler<TRootTagProbeObject> IsoEff("Isolation");


int main(int argc, char** argv) {
    std::string inFileName = "";
    std::string outFileName = "";
    bool EcalBarrelSeparated = false;

   for (int f = 1; f < argc; f++) {
        std::string arg_fth(*(argv + f));
//        cout<<"-------- "<< arg_fth<<endl;
        if (arg_fth == "out") {
          f++;
          outFileName = std::string(*(argv + f));
        }else if (arg_fth == "input") {
          f++;
          inFileName = std::string(*(argv + f));
        }else if (arg_fth == "ECEEseparation") {
          f++;
          std::string lm = std::string(*(argv + f));
          EcalBarrelSeparated = (lm == "true");
          cout<<lm<<" "<<EcalBarrelSeparated<<endl;
        }
    }

    TagProbeEffHandler * IdEff = new TagProbeEffHandler("Identification",true);
    TagProbeEffHandler * IsoEff = new TagProbeEffHandler("Isolation",true);
    TagProbeEffHandler * IsoIdEff = new TagProbeEffHandler("IsolationAfterId",true);
    TagProbeEffHandler * IdEff_EC = new TagProbeEffHandler("Identification_endcap",true);
    TagProbeEffHandler * IsoEff_EC = new TagProbeEffHandler("Isolation_endcap",true);
    TagProbeEffHandler * IsoIdEff_EC = new TagProbeEffHandler("IsolationAfterId_endcap",true);
    TagProbeEffHandler * IdEff_EB = new TagProbeEffHandler("Identification_barrel",true);
    TagProbeEffHandler * IsoEff_EB = new TagProbeEffHandler("Isolation_barrel",true);
    TagProbeEffHandler * IsoIdEff_EB = new TagProbeEffHandler("IsolationAfterId_barrel",true);


    TFile * in = new TFile(inFileName.c_str(),"read");

    
    IdEff->AllCondition = AlwaysTrue;
    IdEff->Condition = IDCondition;
    IdEff->ResetConditionForAllProps();
    IsoEff->AllCondition = AlwaysTrue;
    IsoEff->Condition = ISOCondition;
    IsoEff->ResetConditionForAllProps();
    IsoIdEff->AllCondition = IDCondition;
    IsoIdEff->Condition = ISOCondition;
    IsoIdEff->ResetConditionForAllProps();

    IdEff_EC->AllCondition = AlwaysTrue;
    IdEff_EC->Condition = IDCondition;
    IdEff_EC->ResetConditionForAllProps();
    IsoEff_EC->AllCondition = AlwaysTrue;
    IsoEff_EC->Condition = ISOCondition;
    IsoEff_EC->ResetConditionForAllProps();
    IsoIdEff_EC->AllCondition = IDCondition;
    IsoIdEff_EC->Condition = ISOCondition;
    IsoIdEff_EC->ResetConditionForAllProps();

    IdEff_EB->AllCondition = AlwaysTrue;
    IdEff_EB->Condition = IDCondition;
    IdEff_EB->ResetConditionForAllProps();
    IsoEff_EB->AllCondition = AlwaysTrue;
    IsoEff_EB->Condition = ISOCondition;
    IsoEff_EB->ResetConditionForAllProps();
    IsoIdEff_EB->AllCondition = IDCondition;
    IsoIdEff_EB->Condition = ISOCondition;
    IsoIdEff_EB->ResetConditionForAllProps();

    TTree * eventTree = (TTree*)in->Get("eventTree");
    TTree * runTree = (TTree*)in->Get("runTree");


    PracticalEvent * pracEvt = new PracticalEvent(eventTree,runTree,/*isTt*/true,/*jetOk*/ true,/*genOk*/true,/*elecOk*/false,
           /*muOk*/true,/*metOk*/false,/*pvOk*/true,/*TPok*/true);
    TH2D h("minRJE_isoVal","minRJE_isoVal",80,0.,20., 40,0., 4.);

    while (pracEvt->Next()){
        if(pracEvt->TagProbeCollection()->GetEntriesFast() > 1){
            cout<<"more than 1 pairs in on event!"<<endl;
            return 6;
        }
        for(int i = 0; i < pracEvt->TagProbeCollection()->GetEntriesFast(); i++){
            TRootTagProbeObject * t = (TRootTagProbeObject*)pracEvt->TagProbeCollection()->At(i);
            if(t->PIndex.size() > 0){
                cout<<"Bad assignment! "<<endl;
                return 5;
            }
            if(!t->hasMatch){
                cout<<"non matched electron! "<<endl;
                return 6;
            }
//            cout<<"befor Fill"<<endl;

	    if(!EcalBarrelSeparated){
                IdEff->Fill(t,1);
                IsoEff->Fill(t,1);
//                cout<<"I am here"<<endl;
                IsoIdEff->Fill(t,1);
	    }

//            cout<<"befor ECalBarrel"<<endl;
            minRJetProbe s;
            h.Fill(t->combinedIso(3,3,3), s.ReadValue(t).at(0),1);
            if(EcalBarrelSeparated){
                if(t->isEB()){
//                    cout<<"here"<<endl;
                    IdEff_EB->Fill(t,1);
                    IsoEff_EB->Fill(t,1);
                    IsoIdEff_EB->Fill(t,1);
                }
                else if(t->isEE()){
//                    cout<<"there"<<endl;
                    IdEff_EC->Fill(t,1);
                    IsoEff_EC->Fill(t,1);
                    IsoIdEff_EC->Fill(t,1);
                }
            }

        }
    }

    TFile * F = new TFile(outFileName.c_str(),"recreate");
    F->cd();
    if(!EcalBarrelSeparated){
        IdEff->WriteAll(F);
        IsoEff->WriteAll(F);
        IsoIdEff->WriteAll(F);
    }else{
        IdEff_EC->WriteAll(F);
        IsoEff_EC->WriteAll(F);
        IsoIdEff_EC->WriteAll(F);
        IdEff_EB->WriteAll(F);
        IsoEff_EB->WriteAll(F);
        IsoIdEff_EB->WriteAll(F);

    }
    F->cd();
    h.Write();
    F->Write();
    F->Close();

    return 0;
}

