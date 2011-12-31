/* 
 * File:   ZTagAndProbeEventSelection.cc
 * Author: ajafari
 *
 * Created on October 27, 2010, 11:53 AM
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
#include "../../../AnalysisClasses/TagProbeStudies/interface/ExtTagProbEffHandler.h"

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

int main(int argc, char** argv) {
    std::vector<std::string> inFileName;
    std::vector<double> inWeights;
    inFileName.clear();
    inWeights.clear();
    std::string outFileName = "";
    double lowMass = 10000.;
    double highMass = -10000.;
    bool matchAna = false;
    bool EcalBarrelSeparated = false;
    bool fillSubVal = false;
    double xMinSubVal = -1;
    double xMaxSubVal = -1;


    for (int f = 1; f < argc; f++) {
        std::string arg_fth(*(argv + f));
//        cout<<"-------- "<< arg_fth<<endl;
        if (arg_fth == "out") {
          f++;
          outFileName = std::string(*(argv + f));
        }else if (arg_fth == "input") {
          f++;
//          inFileName.push_back( std::string("/home/ajafari/rootfiles/TopTrees/7TeV/July10/TagAndProbe/106._76._"+string(*(argv + f))));
//          inFileName.push_back( std::string("/home/ajafari/rootfiles/TopTrees/7TeV/December10/TagAndProbe/106._76._"+string(*(argv + f))));
          inFileName.push_back( std::string("/home/ajafari/"+string(*(argv + f))));
        }else if (arg_fth == "weight") {
          f++;
          inWeights.push_back(atof((std::string(*(argv + f))).c_str()));
        }else if (arg_fth == "lowmass") {
          f++;
          std::string lm = std::string(*(argv + f));
          lowMass = atof(lm.c_str());
        }else if (arg_fth == "highmass") {
          f++;
          std::string lm = std::string(*(argv + f));
          highMass = atof(lm.c_str());
        }else if (arg_fth == "genanalysis") {
          f++;
          std::string lm = std::string(*(argv + f));
          matchAna = (lm == "true");
        }else if (arg_fth == "ECEEseparation") {
          f++;
          std::string lm = std::string(*(argv + f));
          EcalBarrelSeparated = (lm == "true");
        }else if (arg_fth == "doSubVal") {
          f++;
          std::string lm = std::string(*(argv + f));
          fillSubVal = (lm == "true");
        }else if (arg_fth == "minXsubVal") {
          f++;
          std::string lm = std::string(*(argv + f));
          xMinSubVal = atof(lm.c_str());
        }else if (arg_fth == "maxXsubVal") {
          f++;
          std::string lm = std::string(*(argv + f));
          xMaxSubVal = atof(lm.c_str());
        }
    }

    int hamed = 0;
    TagProbeEffHandler * IdEff = new TagProbeEffHandler("Identification",true,true);
    TagProbeEffHandler * IsoEff = new TagProbeEffHandler("Isolation",true,true);
    TagProbeEffHandler * IsoIdEff = new TagProbeEffHandler("IsolationAfterId",true,true);
    TagProbeEffHandler * IdEff_EC = new TagProbeEffHandler("Identification_endcap",true,true);
    TagProbeEffHandler * IsoEff_EC = new TagProbeEffHandler("Isolation_endcap",true,true);
    TagProbeEffHandler * IsoIdEff_EC = new TagProbeEffHandler("IsolationAfterId_endcap",true,true);
    TagProbeEffHandler * IdEff_EB = new TagProbeEffHandler("Identification_barrel",true,true);
    TagProbeEffHandler * IsoEff_EB = new TagProbeEffHandler("Isolation_barrel",true,true);
    TagProbeEffHandler * IsoIdEff_EB = new TagProbeEffHandler("IsolationAfterId_barrel",true,true);
    
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

    ExtTagProbeEffHandler * ExtIdEff = new ExtTagProbeEffHandler("ExtIdentification",fillSubVal,xMinSubVal,xMaxSubVal,true,true);
    ExtTagProbeEffHandler * ExtIsoEff = new ExtTagProbeEffHandler("ExtIsolation",fillSubVal,xMinSubVal,xMaxSubVal,true,true);
    
    ExtIdEff->AllCondition = AlwaysTrue;
    ExtIdEff->Condition = IDCondition;
    ExtIdEff->ResetConditionForAllProps();
    ExtIsoEff->AllCondition = AlwaysTrue;
    ExtIsoEff->Condition = ISOCondition;
    ExtIsoEff->ResetConditionForAllProps();

    TH2D h("minRJE_isoVal","minRJE_isoVal",80,0.,20., 40,0., 4.);
    TH1D drTP("drTP","drTP",100,0.,4.);
    
    for(unsigned int nf = 0; nf<inFileName.size(); nf++ ){
        double weight = 1;
        if(inFileName.size() != 0)
            weight = inWeights.at(nf);

        cout<<weight<<"\t"<<inFileName.at(nf)<<endl;

        TFile * in = new TFile(inFileName.at(nf).c_str(),"read");
        TTree * eventTree = (TTree*)in->Get("eventTree");
        TTree * runTree = (TTree*)in->Get("runTree");

        PracticalEvent * pracEvt = new PracticalEvent(eventTree,runTree,/*isTt*/false,/*jetOk*/ true,/*genOk*/true,/*elecOk*/false,
               /*muOk*/true,/*metOk*/false,/*pvOk*/true,/*TPok*/true);

        while (pracEvt->Next()){
            //cout<<"======== Evt: "<<hamed<<endl;
//            hamed++;
//            if(hamed > 1000)
//                break;
            if(pracEvt->TagProbeCollection()->GetEntriesFast() > 2){
                cout<<"more than 2 pairs in on event!"<<endl;
                return 6;
            }
            bool done = false;
            if(!matchAna){
                for(int i = 0; i < pracEvt->TagProbeCollection()->GetEntriesFast(); i++){
                    if(((TRootTagProbeObject*)pracEvt->TagProbeCollection()->At(i))->PIndex.size() > 1){
                        cout<<"Bad assignment! "<<endl;
                        return 5;
                    }
                    if(((TRootTagProbeObject*)pracEvt->TagProbeCollection()->At(i))->PIndex.size() < 1){
                        cout<<"No probe for this tag!!!"<<endl;
                        return 7;
                    }
                    bool tagID = IDCondition(((TRootTagProbeObject*)pracEvt->TagProbeCollection()->At(i)));
                    bool tagISO = ISOCondition(((TRootTagProbeObject*)pracEvt->TagProbeCollection()->At(i)));
                    bool tagPV_distance = (fabs(((TRootVertex*)pracEvt->VertexCollection()->At(0))->z() - ((TRootTagProbeObject*)pracEvt->TagProbeCollection()->At(i))->vz()) < 1);
                    bool tagD0 = (((TRootTagProbeObject*)pracEvt->TagProbeCollection()->At(i))->d0() < 0.02) ;
                    if(!(tagID && tagISO))
//                    if(!(tagID && tagISO && tagPV_distance && tagD0))
                        continue;
                    done =true;
                    int index = ((TRootTagProbeObject*)pracEvt->TagProbeCollection()->At(i))->PIndex.at(0);
                    TRootTagProbeObject t = (*(TRootTagProbeObject*)pracEvt->TagProbeCollection()->At(index));
                    if(!EcalBarrelSeparated){
                        IdEff->Fill(&t,weight);
                        IsoEff->Fill(&t,weight);
                        IsoIdEff->Fill(&t,weight);
                        ExtIdEff->Fill(&t,weight);
                        ExtIsoEff->Fill(&t,weight);
                    }
                    DR<TLorentzVector> dr(t, *((TRootTagProbeObject*)pracEvt->TagProbeCollection()->At(i)));
                    drTP.Fill(dr.getValue());

                    minRJetProbe s;
                    h.Fill(t.combinedIso(3,3,3), s.ReadValue(&t).at(0),1);
                    if(EcalBarrelSeparated){
                        if(t.isEB()){
                            IdEff_EB->Fill(&t,weight);
                            IsoEff_EB->Fill(&t,weight);
                            IsoIdEff_EB->Fill(&t,weight);
                        }
                        else if(t.isEE()){
                            IdEff_EC->Fill(&t,weight);
                            IsoEff_EC->Fill(&t,weight);
                            IsoIdEff_EC->Fill(&t,weight);
                        }
                    }
                }
            }
            if(done)
                hamed++;
            else if(matchAna){
                for(int i = 0; i < pracEvt->TagProbeCollection()->GetEntriesFast(); i++){
                    if(((TRootTagProbeObject*)pracEvt->TagProbeCollection()->At(i))->PIndex.size() > 1){
                        cout<<"Bad assignment! "<<endl;
                        return 5;
                    }
                    if(((TRootTagProbeObject*)pracEvt->TagProbeCollection()->At(i))->PIndex.size() < 1){
                        cout<<"No probe for this tag!!!"<<endl;
                        return 7;
                    }
                    if(!((TRootTagProbeObject*)pracEvt->TagProbeCollection()->At(i))->hasMatch)
                        continue;
                    int index = ((TRootTagProbeObject*)pracEvt->TagProbeCollection()->At(i))->PIndex.at(0);
                    TRootTagProbeObject t = (*(TRootTagProbeObject*)pracEvt->TagProbeCollection()->At(index));
                    if(!t.hasMatch)
                        continue;
                    IdEff->Fill(&t,1);
                    IsoEff->Fill(&t,1);
                    DR<TLorentzVector> dr(t, *((TRootTagProbeObject*)pracEvt->TagProbeCollection()->At(i)));
                    drTP.Fill(dr.getValue());

                    minRJetProbe s;
                    h.Fill(t.combinedIso(3,3,3), s.ReadValue(&t).at(0),1);
                }

            }
        }
        in->Close();
        delete in;
    }

    TFile * F = new TFile(outFileName.c_str(),"recreate");
    F->cd();
    h.Write();
    drTP.Write();
    if(!EcalBarrelSeparated){
        IdEff->WriteAll(F);
        IsoEff->WriteAll(F);
        IsoIdEff->WriteAll(F);
        ExtIdEff->WriteAll(F);
        ExtIsoEff->WriteAll(F);
    }else{
        IdEff_EC->WriteAll(F);
        IsoEff_EC->WriteAll(F);
        IsoIdEff_EC->WriteAll(F);
        IdEff_EB->WriteAll(F);
        IsoEff_EB->WriteAll(F);
        IsoIdEff_EB->WriteAll(F);

    }
    F->Write();
    F->Close();
    cout<<hamed<<endl;
    return 0;
}

