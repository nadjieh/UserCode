/* 
 * File:   Event.h
 * Author: ajafari
 *
 * Created on December 25, 2009, 7:05 PM
 */


#ifndef _EVENT_H
#define	_EVENT_H
#include "TClonesArray.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootEvent.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootRun.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootJet.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootCaloJet.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootMuon.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootMET.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootElectron.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootTagProbeObject.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootVertex.h"

//#include "../../../AnalysisClasses/ChiSquared/interface/DR.h"
#include "../../../AnalysisClasses/EventSelection/interface/JetMatching.h"


#include "ElectronSelector.h"
#include "MuonVetoSelector.h"
#include "PrimaryVertexSelector.h"
#include "JetSelector.h"
//#include "EventsHists.h"


using namespace TopTree;
class Event{
public:
    Event(TRootEvent Evt, TRootRun Run, TClonesArray jets_,TClonesArray electrons_,TClonesArray mets_,TClonesArray muons_, TClonesArray primaryVertices):evt(Evt), run(Run){
        this->clear();
        for(int i = 0; i<jets_.GetEntriesFast(); i++)
            jets.push_back(*(TRootCaloJet*)jets_.At(i));
        for(int i = 0; i<electrons_.GetEntriesFast(); i++)
            electrons.push_back(*(TRootElectron*)electrons_.At(i));
        for(int i = 0; i<mets_.GetEntriesFast(); i++)
            mets.push_back(*(TRootMET*)mets_.At(i));   
        for(int i = 0; i<muons_.GetEntriesFast(); i++)
            muons.push_back(*(TRootMuon*)muons_.At(i));
        for(int i = 0; i<primaryVertices.GetEntriesFast(); i++)
            pvs.push_back(*(TRootVertex*)primaryVertices.At(i));
        GenElec.SetPxPyPzE(0,0,0,0);
        doMatchElec = false;
        firstBtagIndex = -1;
        verbosity = 0;
//        JES = 1;
        
    };
    Event(TRootEvent Evt, TRootRun Run, TClonesArray jets_,std::vector<TRootElectron> electrons_,TClonesArray mets_,TClonesArray muons_, TClonesArray primaryVertices):evt(Evt), run(Run){
        this->clear();
        for(int i = 0; i<jets_.GetEntriesFast(); i++)
            jets.push_back(*(TRootCaloJet*)jets_.At(i));
        for( unsigned int i = 0; i<electrons_.size(); i++)
            electrons.push_back(electrons_.at(i));
        for(int i = 0; i<mets_.GetEntriesFast(); i++)
            mets.push_back(*(TRootMET*)mets_.At(i));
        for(int i = 0; i<muons_.GetEntriesFast(); i++)
            muons.push_back(*(TRootMuon*)muons_.At(i));
        for(int i = 0; i<primaryVertices.GetEntriesFast(); i++)
            pvs.push_back(*(TRootVertex*)primaryVertices.At(i));

        GenElec.SetPxPyPzE(0,0,0,0);
        doMatchElec = false;
        firstBtagIndex = -1;
        verbosity = 0;        
//        JES = 1;
    };
    Event(TClonesArray jets_,TClonesArray electrons_,TClonesArray mets_,TClonesArray muons_,
    TClonesArray primaryVertices){
        this->clear();
        for(int i = 0; i<jets_.GetEntriesFast(); i++)
            jets.push_back(*(TRootCaloJet*)jets_.At(i));
        for(int i = 0; i<electrons_.GetEntriesFast(); i++)
            electrons.push_back(*(TRootElectron*)electrons_.At(i));
        for(int i = 0; i<mets_.GetEntriesFast(); i++)
            mets.push_back(*(TRootMET*)mets_.At(i));
        //cout<<"Muon size in constructor: " <<muons_.GetEntriesFast();
        for(int i = 0; i<muons_.GetEntriesFast(); i++)
            muons.push_back(*(TRootMuon*)muons_.At(i));
        for(int i = 0; i<primaryVertices.GetEntriesFast(); i++)
            pvs.push_back(*(TRootVertex*)primaryVertices.At(i));

        GenElec.SetPxPyPzE(0,0,0,0);
        doMatchElec = false;
        firstBtagIndex = -1;
        verbosity = 0;
//        JES = 1;

    };
    Event(TClonesArray primaryVertices){
        this->clear();
        for(int i = 0; i<primaryVertices.GetEntriesFast(); i++)
            pvs.push_back(*(TRootVertex*)primaryVertices.At(i));

        GenElec.SetPxPyPzE(0,0,0,0);
        doMatchElec = false;
        firstBtagIndex = -1;
        verbosity = 0;
//        JES = 1;

    };
    Event(std::vector<TRootCaloJet> jets_,TClonesArray electrons_,TClonesArray mets_,TClonesArray muons_,
    TClonesArray primaryVertices){
        this->clear();
        for(unsigned int i = 0; i<jets_.size(); i++)
            jets.push_back(jets_.at(i));
        for(int i = 0; i<electrons_.GetEntriesFast(); i++)
            electrons.push_back(*(TRootElectron*)electrons_.At(i));
        for(int i = 0; i<mets_.GetEntriesFast(); i++)
            mets.push_back(*(TRootMET*)mets_.At(i));
//	cout<<"Muon size in constructor: " <<muons_.GetEntriesFast();
        for(int i = 0; i<muons_.GetEntriesFast(); i++)
            muons.push_back(*(TRootMuon*)muons_.At(i));
        for(int i = 0; i<primaryVertices.GetEntriesFast(); i++)
            pvs.push_back(*(TRootVertex*)primaryVertices.At(i));

        GenElec.SetPxPyPzE(0,0,0,0);
        doMatchElec = false;
        firstBtagIndex = -1;
        verbosity = 0;
//        JES = 1;

    };
    Event(TClonesArray jets_,std::vector<TRootElectron> electrons_,
    TClonesArray mets_,TClonesArray muons_, TClonesArray primaryVertices){
        this->clear();
        for(int i = 0; i<jets_.GetEntriesFast(); i++)
            jets.push_back(*(TRootCaloJet*)jets_.At(i));
        for( unsigned int i = 0; i<electrons_.size(); i++)
            electrons.push_back(electrons_.at(i));
        for(int i = 0; i<mets_.GetEntriesFast(); i++)
            mets.push_back(*(TRootMET*)mets_.At(i));
        for(int i = 0; i<muons_.GetEntriesFast(); i++)
            muons.push_back(*(TRootMuon*)muons_.At(i));
        for(int i = 0; i<primaryVertices.GetEntriesFast(); i++)
            pvs.push_back(*(TRootVertex*)primaryVertices.At(i));

        GenElec.SetPxPyPzE(0,0,0,0);
        doMatchElec = false;
        firstBtagIndex = -1;
        verbosity = 0;
//        JES = 1;
    };
    Event(TClonesArray jets_,TClonesArray electrons_){
        this->clear();
        for(int i = 0; i<jets_.GetEntriesFast(); i++)
            jets.push_back(*(TRootCaloJet*)jets_.At(i));
//        if(jets.size() != 0){
//            cout<<"In the Event: "<<jets.at(0).Pt()<<endl;
//        }
        for( int i = 0; i<electrons_.GetEntriesFast(); i++)
            electrons.push_back(*(TRootElectron*)electrons_.At(i));
        GenElec.SetPxPyPzE(0,0,0,0);
        doMatchElec = false;
        firstBtagIndex = -1;
        verbosity = 0;
//        JES = 1;
    };
    Event(std::vector<TRootCaloJet> jets_,TClonesArray electrons_){
        this->clear();
        jets = jets_;
//        if(jets_.size() != 0){
//            cout<<"In the Event: "<<jets_.at(0).Pt()<<endl;
//        }
        for( int i = 0; i<electrons_.GetEntriesFast(); i++)
            electrons.push_back(*(TRootElectron*)electrons_.At(i));
        GenElec.SetPxPyPzE(0,0,0,0);
        doMatchElec = false;
        firstBtagIndex = -1;
        verbosity = 0;
//        JES = 1;
    };
    Event(TClonesArray jets_,TClonesArray TPelectrons_,TClonesArray electrons_){
        this->clear();
        for(int i = 0; i<jets_.GetEntriesFast(); i++)
            jets.push_back(*(TRootCaloJet*)jets_.At(i));
        for( int i = 0; i<TPelectrons_.GetEntriesFast(); i++)
            TPobjs.push_back(*(TRootTagProbeObject*)TPelectrons_.At(i));
        for( int i = 0; i<electrons_.GetEntriesFast(); i++)
            electrons.push_back(*(TRootElectron*)electrons_.At(i));
        GenElec.SetPxPyPzE(0,0,0,0);
        doMatchElec = false;
        firstBtagIndex = -1;
        verbosity = 0;
//        JES = 1;
    };
    Event(TClonesArray jets_,TClonesArray * pv,TClonesArray electrons_){
        this->clear();
        for(int i = 0; i<jets_.GetEntriesFast(); i++)
            jets.push_back(*(TRootCaloJet*)jets_.At(i));
        for( int i = 0; i<pv->GetEntriesFast(); i++)
            pvs.push_back(*(TRootVertex*)pv->At(i));
        for( int i = 0; i<electrons_.GetEntriesFast(); i++)
            electrons.push_back(*(TRootElectron*)electrons_.At(i));
        GenElec.SetPxPyPzE(0,0,0,0);
        doMatchElec = false;
        firstBtagIndex = -1;
        verbosity = 0;
//        JES = 1;
    };
    
        

    ~Event(){};
    void verbose(int i){verbosity = i;}
    void ElectronMaker(double pt = 20., double eta = 2.4, double Exc_Low = 1.442 ,double Exc_High = 1.56,
        std::string Id = "rTight",std::string IdSecond = "rLoose", std::string Iso = "", double D0 = 0.02, double IsoCut = 0.1, 
	double drToPV = 10000., double secondEIso = 1000.){
	double PVz = 0;
	if(Gpvs.size() != 0)
	    PVz = Gpvs.at(0).z();
        ElectronSelector electronSelector("ElectronSelector",pt,eta,Exc_Low,Exc_High,Id,IdSecond,Iso,D0,IsoCut,20.,drToPV ,secondEIso);
	electronSelector.verbose(verbosity);
        electronSelector.setElectrons(electrons,PVz);
        if( verbosity > 1){
                if(doMatchElec)
                    cout<<"I want to match the electron!\tMatching in ElectronSelector is "<<doMatchElec<<
                    " and index is "<<matchElecIndex<<endl;
                cout<<"GenElec properties in ElectronSelector:\n\t"<<GenElec.Px()<<"\n\t"<<GenElec.Py()<<"\n\t"<<GenElec.Pz()<<endl;
        }
        if(doMatchElec){
//            electronSelector.ElectronMatcher(GenElec);
            ElectronMatcher(GenElec,electronSelector.GoldenElecs(),matchElecIndex);
        }
//        matchElecIndex = electronSelector.matchedEleIndex;
        Gelectrons.clear();
        Gelectrons = electronSelector.GoldenElecs();
	if(verbosity > 0)
	    cout<<"In event, number of GoldenElectrons is: "<<Gelectrons.size()<<"\nIn event, number of SecondElectrons is: "<<Secondelectrons.size()<<endl;
        Secondelectrons.clear();
        Secondelectrons = electronSelector.secondElectrons();

    };
     void JetCleaning(){
         std::vector<TRootCaloJet> CleanJets;
         CleanJets.clear();
	if(verbosity > 0)
		cout<<"Jet size before cleaning: "<<jets.size()<<endl;
        for(uint s = 0; s < jets.size(); s++){
            TRootCaloJet myJet = jets.at(s);
            bool ifElecClosedBy = false;
	    if(verbosity > 4)
	        cout<<"In JetCleaning, number of GoldenElectrons is: "<<Gelectrons.size()<<endl;
            for(uint q = 0; q<Gelectrons.size(); q++){
                DR<TLorentzVector> dr(myJet,Gelectrons.at(q));
                double r = dr.getValue();
//		if(verbosity > 0)
//	            cout<<"DeltaR: "<<r<<endl;
                if(r<0.3){
//                    cout<<myJet.Pt()<<"\t"<<Gelectrons.at(q).Pt()<<endl;
                    if(!ifElecClosedBy)
                        ifElecClosedBy = true;
                }
            }
            if(!ifElecClosedBy){
                 CleanJets.push_back(myJet);
                 
            }else if(verbosity > 4)
			cout<<"Jet-Electron overlap"<<endl;
        }
         jets.clear();
         jets = CleanJets;
	if(verbosity > 0)
		cout<<"Jet size after cleaning: "<<jets.size()<<endl;
    }
    void JetMaker(std::string bTagAlgo = "TCHE", double pt = 25., double eta = 2.4,int nCaloTower = 5,
        double EmfUp = 1000.,double EmfLow = -1., double fhpd_ = 1000., int N90_ = -1, double bTagCut_ = 4.){
        JetSelector jetSelector("JetSelector",bTagAlgo,pt,eta,nCaloTower,EmfUp,EmfLow,fhpd_,N90_,bTagCut_);
//        jetSelector.setJES(JES);
        jetSelector.verbose(verbosity);
        jetSelector.setJets(jets);

        Gjets.clear();
        Gjets = jetSelector.goldenJets();
        firstBtagIndex = jetSelector.FirstBtagIndexInGJets();
        if(verbosity > 0)
            cout<<"\tThe index of the first b-jet: "<<firstBtagIndex<<endl;
        Bjets.clear();
        Bjets = jetSelector.bJets();

    }

    void VertexMaker(double zCut = 24){
        PrimaryVertexSelector PVSelector("PrimaryVertexSelector",zCut);
        PVSelector.verbose(verbosity);
        PVSelector.setPVs(pvs);

        Gpvs.clear();
        Gpvs = PVSelector.GoldenVertices();
    }


    void MuonMaker(double pt = 20., double eta = 2.4,double chi2 = 10, double D0 = 0.02, int nvh = 11,
        double isoCut_ = 0.05, bool doGL = false){
        if(verbosity > 2)
		cout<<"In MuMaker Method: "<<endl;
	MuonVetoSelector MuSelector("MuonVetoSelector",pt,eta,chi2,D0,nvh,isoCut_,doGL);
        MuSelector.verbose(verbosity);
        MuSelector.setMuons(muons);

        Dmuons.clear();
        Dmuons = MuSelector.desiredMuons();
    }
    void TagAndProbeMaker(){
        
    }
//    void setJES(double jes){
//        JES = jes;
//    }
    void clear(){
        jets.clear();
        Gjets.clear();
        Bjets.clear();

        electrons.clear();
        Gelectrons.clear();
        Secondelectrons.clear();

        muons.clear();
        Dmuons.clear();

        pvs.clear();
        Gpvs.clear();

        mets.clear();

        TPobjs.clear();
    };
    bool GoldenElectronHasPartnerTrack(){
    	TRootElectron e = Gelectrons.at(0);
	if(verbosity > 2){
	    cout<<"In conversion Method\n\tDist: "<<fabs(e.Dist())<<", <? 0.02\n\tDcot: "<<fabs(e.DCot())<<", <? 0.02\n\tmissingHits: "<<e.missingHits()<<", ==? 0"<<endl;
            if((fabs(e.Dist())<0.02 && fabs(e.DCot())<0.02)){
		cout<<"Golden electron has partner track :-("<<endl;
	    }
	}
        return ((fabs(e.Dist())<0.02 && fabs(e.DCot())<0.02));    
    }
    bool isZVetoPassed(int& nPair , double lowmass = 100, double highmass = 10){
      if(Secondelectrons.size() == 0){
	if(verbosity > 2){
	    cout<<"In Zveto method:\n\tNo second electron :-)"<<endl;
	}
	return true;
      }
      bool inRange =false;
      nPair = 0;
      for(uint i = 0; i<Secondelectrons.size(); i++){
      	TLorentzVector tmp(Secondelectrons.at(i).Px() + Gelectrons.at(0).Px(),Secondelectrons.at(i).Py() + Gelectrons.at(0).Py(),
			 Secondelectrons.at(i).Pz() + Gelectrons.at(0).Pz(),Secondelectrons.at(i).E() + Gelectrons.at(0).E());
	if(lowmass<tmp.M() && tmp.M()<highmass){
	    inRange = true;
	    nPair++;
	}
      }
//	cout<<"In Zveto method:\n\t"<<lowmass<<" <? "<<tmp.M()<<" <? "<<highmass<<endl;
      if(verbosity > 2){
	if(!inRange){
	    cout<<"\tEvent passed Zveto! :-)"<<endl;
	}
      }
      return( !inRange );
    }
    TRootEvent evt;
    TRootRun run;
    std::vector<TRootCaloJet> jets;
    std::vector<TRootCaloJet> Gjets;
    std::vector<TRootCaloJet> Bjets;

    std::vector<TRootElectron> electrons;
    std::vector<TRootElectron> Gelectrons;
    std::vector<TRootElectron> Secondelectrons;

    std::vector<TRootMuon> muons;
    std::vector<TRootMuon> Dmuons;
    
    std::vector<TRootVertex> pvs;
    std::vector<TRootVertex> Gpvs;
    std::vector<TRootMET> mets;

    std::vector<TRootTagProbeObject> TPobjs;
    
    TLorentzVector GenElec;
    bool doMatchElec;
    int matchElecIndex;
    int firstBtagIndex;
    int verbosity;
//    double JES;
};


#endif	/* _EVENT_H */
