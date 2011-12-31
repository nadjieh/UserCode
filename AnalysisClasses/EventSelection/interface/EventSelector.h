/* 
 * File:   EventSelector.h
 * Author: ajafari
 *
 * Created on December 25; 2009, 3:42 PM
 */

#ifndef _EVENTSELECTOR_H
#define	_EVENTSELECTOR_H
#include "TClonesArray.h"
#include "Event.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootEvent.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootRun.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootElectron.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootJet.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootCaloJet.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootMET.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootMuon.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootHLTInfo.h"
#include <iostream>
using namespace std;
using namespace TopTree;
class EventSelection{
public:
    EventSelection(Event& evt, bool hlt_ = true, bool atLeastOneGE_ = true, bool exactOneGE_ = true, bool noSecondE_ = true, bool noMuon_ = true, bool jets_ = true, bool btag_ = false, bool met_ = false):
    hlt(hlt_),atLeastOneGE(atLeastOneGE_), exactOneGE(exactOneGE_),noSecondE(noSecondE_), noMuon(noMuon_),jets(jets_),btag(btag_), met(met_){
        setInputCollections(evt);
        elecEta = 2.4;
        elecExclusion.first = 1.442;
        elecExclusion.second = 1.56;
        elecPt = 20.;
        jetEta = 2.4;
        jetEt = 25.;
        //bTagger = ;
        bTagCut = 4.;
        verbosity = 0;
    };
    ~EventSelection(){};
    void setInputCollections(Event evt)
    {    
         Run = evt.run;
         Evt = evt.evt;
         Elecs = evt.electrons;
         Muons = evt.muons;
         Jets = evt.jets; 
         Mets = evt.mets;
        verbosity = 0;
    };
    bool isSelected(int& n1,int& n2,int& n3,int& n4,int& n5,int& n6, bool exactly4Jets = false){
        bool res = true;
//        cout<<"in event selector. res is: "<<res<<endl;
	res = hlt && res ?  isHLT() : res;
        if(res)
//            cout<<"passed HLT"<<endl;
//        else
//            cout<<"failed HLT"<<endl;
//        if(res)
            n1++;

	res = atLeastOneGE && res ? hasAtLeastOneElec() : res;
//        bool tmp = atLeastOneGE && res ? hasAtLeastOneElec() : res;
        if(res){
            n2++;
        }
	res = exactOneGE && res ? hasExactlyOneElec : res;
//        bool first2 = (exactOneGE && res);

//        if(first2)
//            res = hasExactlyOneElec;


//        int evtId = Evt.eventId();
//        if(evtId == 108243 || evtId == 115571 ||evtId == 497345 ||evtId == 543540 ||evtId == 474425 ||evtId == 365247 || evtId == 199361 || evtId == 409736
//               || evtId == 409736 || evtId ==  333560 || evtId ==  457016 || evtId ==  456337 || evtId ==  60853 || evtId ==  117042 || evtId ==  218627 || evtId ==  309878
//                 ||  evtId ==  352666 || evtId ==  209264 || evtId ==  271794){
//            cout<<Evt.eventId()<<"\trun: "<<Evt.runId()<< ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"<<hasExactlyOneElec<<endl;
//            cout<<"res: "<<res<<"  tmp: "<<tmp<<"  has exactly one electron: "<<hasExactlyOneElec<<endl;
//            cout<<"first2: "<<first2<<" exactOneGE:"<<exactOneGE<<endl;
//        }
        if(res)
            n3++;
        res = noSecondE && res ? hasNoSecondElec() : res;
        if(res)
            n4++;
	res = noMuon && res ? hasNoMuon() :res;
        if(res)
            n5++;
	res = jets && res ? hasAtLeastFourJets() : res;
        if(exactly4Jets){
            if((nrGoodJets == 4) && res)
                n6++;
        }
        else
            if(res)
                n6++;
	res = btag && res ? hasOneBtag() : res;
	res = met && res ? hasHighMet() : res;
//        cout<<"befor return res is: "<<res<<endl;
        return(res);
    };
    void doCounting(){
        counting = true;
    }
    
private:
    bool hlt ; 
    bool atLeastOneGE ; 
    bool exactOneGE ; 
    bool noSecondE ; 
    bool noMuon ; 
    bool jets ; 
    bool btag ;
    bool met ;
    
    TRootRun Run;
    TRootEvent Evt;
    std::vector<TRootElectron>  Elecs;
    std::vector<TRootMuon>  Muons;
    std::vector<TRootCaloJet>  Jets;
    std::vector<TRootMET>  Mets;
    double elecEta;
    double elecPt;
    double jetEta;
    double jetEt;
    //std::string bTagger;
    double bTagCut;
    bool hasExactlyOneElec;
    bool counting;
    int nrGoodJets;
    std::pair<double,double> elecExclusion;
    int verbosity ;
    
    bool isHLT(){

        TopTree::TRootHLTInfo hltInfo = Run.getHLTinfo(Evt.runId()); // get the triggerconfiguration for this run

              // get the trigger bits
        int HLT = hltInfo.hltPath("HLT_Ele15_LW_L1R");

        if(verbosity>0) cout << "HLT_Electron_bit: " <<  HLT << endl;

        if( Evt.trigHLT(HLT) ) // skip event if it doesn't pass our selected electron trigger

            return true;
        return(false);
    };
    bool goodElectron(TRootElectron  elec){
        double eta = fabs(elec.Eta());
        bool goodEta = ((eta < elecEta) && !(eta > elecExclusion.first && eta < elecExclusion.second));
        bool kinematics =((elec.Pt()>elecPt) && goodEta);
	 bool isId = elec.isRobustTight();
        bool isIso = ((double)elec.combinedIso(3,3,3)/(double)elec.Pt())<0.1;
	bool d0Constraint = (elec.d0() < 200);
	return(kinematics && isId && isIso && d0Constraint);
    };
    int nGoodElectrons(){
	int nGoodElec = 0;
	TRootElectron  electron;
	for(uint i=0;i<Elecs.size();i++){
		electron = Elecs.at(i);
                if(goodElectron(electron)){
			nGoodElec++;
                }
	}
	return(nGoodElec);
    };
    bool hasAtLeastOneElec(){
        int nGE = nGoodElectrons();
//        int evtId= Evt.eventId();
//        if(evtId == 108243 || evtId == 115571 ||evtId == 497345 ||evtId == 543540 ||evtId == 474425 ||evtId == 365247 || evtId == 199361 || evtId == 409736
//               || evtId == 409736 || evtId ==  333560 || evtId ==  457016 || evtId ==  456337 || evtId ==  60853 || evtId ==  117042 || evtId ==  218627 || evtId ==  309878
//                 ||  evtId ==  352666 || evtId ==  209264 || evtId ==  271794)
//            cout<<"selected Electrons: "<<nGE<<endl;
        hasExactlyOneElec = false;
        hasExactlyOneElec = (nGE == 1);
//        if(evtId == 108243 || evtId == 115571 ||evtId == 497345 ||evtId == 543540 ||evtId == 474425 ||evtId == 365247 || evtId == 199361 || evtId == 409736
//       || evtId == 409736 || evtId ==  333560 || evtId ==  457016 || evtId ==  456337 || evtId ==  60853 || evtId ==  117042 || evtId ==  218627 || evtId ==  309878
//         ||  evtId ==  352666 || evtId ==  209264 || evtId ==  271794)
//            if (hasExactlyOneElec)
//                cout<<"hasExactlyOneElec "<<nGE<<endl;
        return(nGE > 0 );
    };
    bool hasNoSecondElec(){
    	int n = 0;
        TRootElectron elec;
	for(uint i = 0; i<Elecs.size(); i++){
            elec = Elecs.at(i);
            double eta = fabs(elec.Eta());
            bool goodEta = ((eta < elecEta) && !(eta > elecExclusion.first && eta < elecExclusion.second));
            if (elec.isRobustLoose() && elec.Pt() > elecPt && goodEta)
                n++;
	}
	return(!((n-1) > 0));
    };
    
    bool hasNoMuon(){
        TRootMuon muon;
	int nrGoodMuons=0;

	for(uint i=0;i<Muons.size();i++){

		muon = Muons.at(i);
		double relIso=(muon.isoR03_sumPt()+muon.isoR03_emEt()+muon.isoR03_hadEt())/muon.Pt();

	if (muon.Pt() > 20 && fabs(muon.Eta()) < 2.1 && muon.chi2()<10 && muon.d0()<200 && muon.nofValidHits()>=11 && relIso<0.05) 
		nrGoodMuons++;
	}


	return(nrGoodMuons < 1) ;
    };
    bool hasAtLeastFourJets(){
        TRootCaloJet jet;
	nrGoodJets=0;

	for(uint i=0;i<Jets.size(); i++){

		jet =  (Jets.at(i));
		if (jet.Et()>jetEt && fabs(jet.Eta())<jetEta && jet.nConstituents() > 5) 
			nrGoodJets++;

	}
//        cout<<"in selector: "<<nrGoodJets<<endl;
        return(nrGoodJets >= 4);
//        return(nrGoodJets == 4);
    };
    bool hasOneBtag(){
        int nBJets = 0;
        for(uint i=0;i<Jets.size(); i++){
                TRootCaloJet jet =  Jets.at(i);
		if (jet.Et()>jetEt && fabs(jet.Eta())<jetEta && jet.nConstituents() > 5 && jet.btag_trackCountingHighEffBJetTags() > bTagCut) 
			nBJets++;

	}
        return(nBJets >= 1);
    };
    
    bool hasHighMet(){
        if(Mets.size() == 0)
		return(false);

	TRootMET met =Mets.at(0);
	return(met.Pt()>20) ;
    };
};

#endif	/* _EVENTSELECTOR_H */


