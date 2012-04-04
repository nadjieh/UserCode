/* 
 * File:   PracticalEvent.h
 * Author: ajafari
 *
 * Created on July 8, 2010, 3:00 PM
 */

#ifndef _PRACTICALEVENT_H
#define	_PRACTICALEVENT_H
#include "TTree.h"
#include "TBranch.h"
#include "TClonesArray.h"
#include <vector>
#include <string>
#include <iomanip>
#include <iostream>
#include "../../../TopBrussels/TopTreeProducer/interface/TRootMuon.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootElectron.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootCaloJet.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootPFJet.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootMET.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootPFMET.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootGenEvent.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootNPGenEvent.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootEvent.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootRun.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootParticle.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootMCParticle.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootVertex.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootTagProbeObject.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootHLTInfo.h"
//#include "EventsHists.h
#include "../../../TopBrussels/TopTreeAnalysis/Reconstruction/interface/JetCorrectorParameters.h"
#include "../../../TopBrussels/TopTreeAnalysis/Reconstruction/interface/JetCorrectionUncertainty.h"
#include "../../../TopBrussels/TopTreeAnalysis/Tools/interface/JetTools.h"


using namespace std;
using namespace TopTree;
class PracticalEvent{
public:
    PracticalEvent(TTree * evt, TTree * run, bool isTtBar = false, bool jetOk = true, bool genOk = true, bool elecOk = true,
            bool muOk = true, bool metOk = true, bool pvOk = true, bool TPok = false):
            jetOk_(jetOk),genOk_(genOk),elecOk_(elecOk),muOk_(muOk),metOk_(metOk),pvOk_(pvOk),tpOk_(TPok){
            eventTree = (TTree*)evt;
            run_ = 0;
            if(run != NULL){
                runTree = (TTree*)run;
                cout<<"runTree: "<<runTree->GetName()<<endl;
                run_br = (TBranch *) runTree->GetBranch("runInfos");
                cout<<"run_br: "<<run_br->GetName()<<endl;
                run_br->SetAddress(&run_);
                runTree->GetEvent(0);
            }
            else{
                runTree = 0;
                run_br = 0;
            }
            TtBar = isTtBar;
            //---------------------------- Event
//            cout<<"eventTree: "<<eventTree->GetName()<<endl;
            event_br = (TBranch *) eventTree->GetBranch("Event");
//            cout<<"event_br: "<<event_br->GetName()<<endl;
            event = 0;
            event_br->SetAddress(&event);

           //---------------------------- Jets
            
//            if(jetOk_){
                jets = new TClonesArray("TopTree::TRootPFJet", 0);
                jets_br = (TBranch *) eventTree->GetBranch("PFJets_selectedPatJetsPF2PAT");
                if(jets_br != NULL)
                    jets_br->SetAddress(&jets);
                else
                    cout<<"No Branch PFJets_selectedPatJetsPF2PAT" <<endl;
//            }

            //---------------------------- genEvents
//            if(genOk_){
                if(TtBar){
                    genEvent_br = (TBranch *) eventTree->GetBranch("GenEvent");
                    genEvents = new TClonesArray("TopTree::TRootGenEvent", 0);
                    if(genEvent_br != NULL)
                        genEvent_br->SetAddress(&genEvents);
                    else
                        cout<<"No Branch GenEvent" <<endl;
                }
                else {
                    NPgenEvent_br = (TBranch *) eventTree->GetBranch("NPGenEvent");
                    NPgenEvents = new TClonesArray("TopTree::TRootNPGenEvent", 0);
                    if(NPgenEvent_br != NULL)
                        NPgenEvent_br->SetAddress(&NPgenEvents);
                    else
                        cout<<"No Branch NPGenEvent" <<endl;
                }
//            }
            //---------------------------- Electrons
//            cout<<elecOk_<<endl;
//            if(elecOk_){
                electron_br = (TBranch *) eventTree->GetBranch("Electrons_selectedPatElectronsPF2PAT");
                electrons = new TClonesArray("TopTree::TRootElectron", 0);
                if(electron_br != NULL)
                    electron_br->SetAddress(&electrons);
                else
                    cout<<"No Branch Electrons_selectedPatElectronsPF2PAT" <<endl;
//            }
            //---------------------------- Muons
//            cout<<muOk_<<endl;
//            if(muOk_){
                muon_br = (TBranch *) eventTree->GetBranch("Muons_selectedPatMuonsPF2PAT");
                muons = new TClonesArray("TopTree::TRootMuon", 0);
                if(muon_br != NULL)
                    muon_br->SetAddress(&muons);
                else
                    cout<<"No Branch Muons_selectedPatMuonsPF2PAT" <<endl;
//            }
            //---------------------------- MET
//            cout<<metOk_<<endl;
//            if(metOk_){
                met_br = (TBranch *) eventTree->GetBranch("PFMET");
                mets = new TClonesArray("TopTree::TRootPFMET", 0);
                if(met_br != NULL)
                    met_br->SetAddress(&mets);
                else
                    cout<<"No Branch PFMET" <<endl;
//            }
            //---------------------------- PrimaryVertex
//            if(pvOk_){
                pvs_br = (TBranch *) eventTree->GetBranch("PrimaryVertex");
                PVs = new TClonesArray("TopTree::TRootVertex", 0);
                if(pvs_br != NULL)
                    pvs_br->SetAddress(&PVs);
                else
                    cout<<"No Branch PrimaryVertex" <<endl;
//            }
            //---------------------------- TagAndProbeObjects
//            if(tpOk_){
                TP_br = (TBranch *) eventTree->GetBranch("TagProbeObject");
                tps = new TClonesArray("TopTree::TRootTagProbeObject", 0);
                if(TP_br != NULL)
                    TP_br->SetAddress(&tps);
                else
                    cout<<"No Branch TagProbeObject" <<endl;
//            }
            if(runTree != 0)
                runTree->GetEntries();
            eventNumber = 0;
    };
    ~PracticalEvent(){};
    
    bool Next(){
        if(eventNumber == eventTree->GetEntries())
            return false;
        else{
            eventTree->GetEvent(eventNumber);
            eventNumber++;
            if(runTree != NULL)
                runTree->GetEvent(0);
        }
        return true;
    };
    bool Next(int initial,int final){
        if(eventNumber == final || eventNumber < initial)
            return false;
        else{
            eventTree->GetEvent(eventNumber);
            eventNumber++;
            if(runTree != NULL)
                runTree->GetEvent(0);
        }
        return true;
    };
    void setInitialEventNumber(int n){
        eventNumber = n;
    }
    TClonesArray * JetCollection()const{
        return jets;
    };
    TClonesArray * METCollection()const{
        return mets;
    };
    TClonesArray * ElectronCollection()const{
        return electrons;
    };
    TClonesArray * MuonCollection()const{
        return muons;
    };
    TClonesArray * GenEvtCollection()const{
        return genEvents;
    };
    TClonesArray * NPGenEvtCollection()const{
        return NPgenEvents;
    };
    TClonesArray * VertexCollection()const{
        return PVs;
    };
    TClonesArray * TagProbeCollection()const{
        return tps;
    };
    std::vector<TRootPFJet> unCorrectedPFJetVector(){
        std::vector<TRootPFJet> init_jets_corrected;
        init_jets_corrected.clear();
//	cout<<jets->GetEntriesFast()<<endl;
        for(int i=0; i<jets->GetEntriesFast(); i++)
        	init_jets_corrected.push_back(*( (TRootPFJet*) jets->At(i)) );
        return init_jets_corrected;
    }
    std::vector<TRootPFJet> ScaledPFJetCollection(double fScaling, bool isData){
        //cout<<"In prac: "<<isData<<endl;
        std::vector<TRootJet*> init_jets_corrected;
        init_jets_corrected.clear();
//	cout<<jets->GetEntriesFast()<<endl;
        for(int i=0; i<jets->GetEntriesFast(); i++)
        	init_jets_corrected.push_back( (TRootJet*) jets->At(i)->Clone() );
//        if(init_jets_corrected.size() != 0)
//		cout<<"Before Correction:\n\t"<<init_jets_corrected.at(0)->Pt()<<endl;
	//////////////////////////////////
        //cout<<"//Step 1: Initialize JEC factors"<<endl;
        //////////////////////////////////
        vector<JetCorrectorParameters> vCorrParam;
        vCorrParam.clear();

        JetCorrectorParameters *L3JetCorPar  = new JetCorrectorParameters("/home/nadjieh/work/TopBrussels/TopTreeAnalysis/macros/JECFiles/START42_V17_AK5PFchs_L3Absolute.txt");
        JetCorrectorParameters *L2JetCorPar  = new JetCorrectorParameters("/home/nadjieh/work/TopBrussels/TopTreeAnalysis/macros/JECFiles/START42_V17_AK5PFchs_L2Relative.txt");
        JetCorrectorParameters *L1JetCorPar  = new JetCorrectorParameters("/home/nadjieh/work/TopBrussels/TopTreeAnalysis/macros/JECFiles/START42_V17_AK5PFchs_L1FastJet.txt");
        JetCorrectorParameters *ResJetCorPar = new JetCorrectorParameters("/home/nadjieh/work/TopBrussels/TopTreeAnalysis/macros/JECFiles/START42_V17_AK5PFchs_L2L3Residual.txt");
        vCorrParam.push_back(*L1JetCorPar);
        vCorrParam.push_back(*L2JetCorPar);
        vCorrParam.push_back(*L3JetCorPar);
        vCorrParam.push_back(*ResJetCorPar);
        delete L1JetCorPar;
        delete L2JetCorPar;
        delete L3JetCorPar;
        delete ResJetCorPar;

        JetCorrectionUncertainty *jecUnc = new JetCorrectionUncertainty("/home/nadjieh/work/TopBrussels/TopTreeAnalysis/macros/JECFiles/START42_V17_AK5PFchs_Uncertainty.txt");
        // true means redo also the L1
        JetTools *jetTools = new JetTools(vCorrParam, jecUnc, true);
        //cout<<"ACTION: "<<endl;   
      
      
        // Apply Jet Corrections on-the-fly
        if( isData ) {
            jetTools->correctJets(init_jets_corrected,event->kt6PFJetsPF2PAT_rho(),true);
        } else {
            jetTools->correctJets(init_jets_corrected,event->kt6PFJetsPF2PAT_rho(),false);
        }
        
        TRootMET * myMet = (TRootMET*)this->mets->At(0)->Clone();
        jetTools->correctMETTypeOne(init_jets_corrected,myMet, isData);
        CorrectedMETI = *((TRootPFMET*)myMet);
        
        
        std::vector<TRootPFJet> res; res.clear();
        for(unsigned int i = 0; i < init_jets_corrected.size(); i++){
            TRootPFJet myJet = *((TRootPFJet*)init_jets_corrected.at(i));
//            cout<<"\tNoScaling "<<myJet.Pt()<<endl;
            myJet.SetPxPyPzE(fScaling*myJet.Px(),fScaling*myJet.Py(),fScaling*myJet.Pz(), fScaling*myJet.E());
//            cout<<"\tScaling "<<myJet.Pt()<<endl;
            res.push_back(myJet);
        }
	for(unsigned int d = 0; d < res.size(); d++)
    	    if(init_jets_corrected[d]) delete init_jets_corrected[d];
	init_jets_corrected.clear();
	delete jecUnc;
        delete jetTools;
        delete myMet;
        return res;
    };

    TRootEvent * Event()const{return event;};
    TRootRun * RunInfo()const{return run_;};
    
    bool isTtBar()const{return TtBar;};
    void setTtBar(){TtBar = true;};
    bool isHLT(){
        if(this->RunInfo() == NULL){
            cout<<"NO runInfor!!!!!!!!!!"<<endl;
            return false;
        }
        TopTree::TRootHLTInfo hltInfo = this->RunInfo()->getHLTinfo(this->Event()->runId()); // get the triggerconfiguration for this run

              // get the trigger bits
        int HLT = hltInfo.hltPath("HLT_Ele15_LW_L1R");



        if( this->Event()->trigHLT(HLT) ) // skip event if it doesn't pass our selected electron trigger

            return true;
        return(false);
    }
    
    TTree * eventTree;
    TTree * runTree;
    TRootPFMET TypeICorrMET()const{return CorrectedMETI;}
private:

    bool TtBar;

    TBranch* event_br;
    TBranch* run_br;
    
    TRootEvent * event;
    TRootRun * run_;
    
    TBranch* jets_br;
    TClonesArray* jets;
    TBranch* genEvent_br;
    TClonesArray* genEvents;
    TBranch* NPgenEvent_br;
    TClonesArray* NPgenEvents;
    TBranch* electron_br;
    TClonesArray* electrons;
    TBranch* muon_br;
    TClonesArray* muons;
    TBranch* met_br;
    TClonesArray* mets;
    TBranch* pvs_br;
    TClonesArray* PVs;
    TBranch* TP_br;
    TClonesArray* tps;

    bool jetOk_;
    bool genOk_;
    bool elecOk_;
    bool muOk_;
    bool metOk_;
    bool pvOk_;
    bool tpOk_;

    int eventNumber;
    
    TRootPFMET  CorrectedMETI;

};

#endif	/* _PRACTICALEVENT_H */

