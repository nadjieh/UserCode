/* 
 * File:   MuonVetoSelector.h
 * Author: ajafari
 *
 * Created on July 21, 2010, 6:38 PM
 */

#ifndef _MuonVetoSelector_H
#define	_MuonVetoSelector_H


#include <string>
#include <iostream>
#include "../../../TopBrussels/TopTreeProducer/interface/TRootMuon.h"
using namespace TopTree;
using namespace std;
class MuonVetoSelector{
public:
    MuonVetoSelector(std::string name, double pt = 20., double eta = 2.1,double chi2 = 10,
		     double D0 = 0.2, int nTrkLM = 5, int nvMuhit = 0, int nValidPixelHits = 1,
                     int nSegM = 1, double pvZ = 10000, double isocut= 0.12):Name(name)
            ,ptCut(pt)
            ,EtaCut(eta)
            ,chi2Cut(chi2)
            ,d0Cut(D0)
            ,nTrkLwMCut(nTrkLM)
            ,nMuValHit(nvMuhit)
            ,nValidPixelHits(nValidPixelHits)
	    ,nSegMatched(nSegM)
            ,Zpv(pvZ)
            ,isoCut(isocut){verbosity = 0;};
    virtual ~MuonVetoSelector(){};
    void verbose(int i){verbosity = i;}
    bool isDesiredMuon(TRootMuon muon){
            double relIso=relativePFIsolation(muon);
	    if(verbosity > 2){
		cout<<"isGlobal: "<<muon.isGlobalMuon()<<endl;
		cout<<"pt: "<<muon.Pt()<<" > ? "<<ptCut<<endl;
		cout<<"eta: "<<fabs(muon.Eta())<<" <? " <<EtaCut<<endl;
		cout<<"Chi2: "<<muon.chi2()<<" < ? "<<chi2Cut<<endl;
		cout<<"nTrkLayerWithMesurement: "<<muon.nofTrackerLayersWithMeasurement()<<
                        " > ? "<<nTrkLwMCut<<endl;
		cout<<"nMuvh: "<<muon.nofValidMuHits()<< " > ? "<<nMuValHit<<endl;
		cout<<"D0: "<<fabs(muon.d0())<<" < ? "<<d0Cut<<endl;
		cout<<"dist to pv: "<<fabs(muon.vz()-Zpv)<<" < ? 0.5"<<endl;
		cout<<"nValidPixelHit: "<<muon.nofValidPixelHits()<< " > ? "<< nValidPixelHits<<endl;
		cout<<"nSegMatched: "<<muon.nofMatchedStations()<<" > ? "<<nSegMatched<<endl;
		cout<<"isoVal: "<<relIso<<" < ? "<<isoCut<<endl;
                cout<<"isGlobalPromptTight: "<<muon.idGlobalMuonPromptTight()<<endl;
		if(muon.Pt() > ptCut && fabs(muon.Eta()) < EtaCut  && muon.chi2() < chi2Cut &&
                   muon.nofTrackerLayersWithMeasurement()> nTrkLwMCut && muon.nofValidMuHits() > nMuValHit && 
                   fabs(muon.d0()) < d0Cut && fabs(muon.vz()-Zpv) < 0.5 && muon.nofValidPixelHits() > nValidPixelHits &&
                   muon.nofMatchedStations() > nSegMatched && relIso < isoCut  )
		    cout<<"Desired Muon is found :-)"<<endl;
	    }
            return(muon.Pt() > ptCut && fabs(muon.Eta()) < EtaCut  && muon.chi2() < chi2Cut &&
                   muon.nofTrackerLayersWithMeasurement()> nTrkLwMCut && muon.nofValidMuHits() > nMuValHit && 
                   fabs(muon.d0()) < d0Cut && fabs(muon.vz()-Zpv) < 0.5 && muon.nofValidPixelHits() > nValidPixelHits &&
                   muon.nofMatchedStations() > nSegMatched && relIso < isoCut  );
    }
    bool isLooseMuon(TRootMuon muon ){
            double relIso=this->relativePFIsolation(muon);
	    if(verbosity > 2){
		cout<<"isGlobal: "<<muon.isGlobalMuon()<<endl;
		cout<<"isTracker: "<<muon.isTrackerMuon()<<endl;
		cout<<"eta: "<<fabs(muon.Eta())<<" <? 2.5" <<endl;
		cout<<"pt: "<<muon.Pt()<<" > ? 10"<<endl;
		cout<<"isoVal: "<<relIso<<" < ? 0.2"<<endl;
		if((muon.isGlobalMuon() || muon.isTrackerMuon()) && (fabs(muon.Eta())<2.5) && (muon.Pt()>10) && relIso<0.2)
		    cout<<"Loose muon is found :-("<<endl;
	    }
	    return ((muon.isGlobalMuon() || muon.isTrackerMuon()) && (fabs(muon.Eta())<2.5) && (muon.Pt()>10) && relIso<0.2);
    }
    void setMuons(std::vector<TRootMuon> muons){
        DesiredMuons.clear();
        LooseMuons.clear();
        if(verbosity > 0)
            cout<<"Muon.size : "<<muons.size()<<endl; 
        for(uint i = 0; i<muons.size(); i++){
	    if(verbosity > 0)
		cout<<"***** Muon number "<<i<<endl;
            if(isDesiredMuon(muons.at(i)))
                DesiredMuons.push_back(muons.at(i));
	    else if (isLooseMuon(muons.at(i)))
		LooseMuons.push_back(muons.at(i));
        }
    }
    int numberOfDesiredMuon(){
        return DesiredMuons.size();
    }
    bool MuChannelPassMuVeto(){return (this->looseMuons().size() == 0);}
    bool ElecChannelPassMuVeto(){return ((this->looseMuons().size() == 0) && (this->desiredMuons().size()==0));}
    virtual bool EventPassedMe(){
        return(this->numberOfDesiredMuon() < 1);
    }
    std::vector<TRootMuon> desiredMuons()const{return DesiredMuons; }
    std::vector<TRootMuon> looseMuons()const{return LooseMuons; }
    double relativePFIsolation(TRootMuon muon){
        return ((muon.chargedHadronIso() + max( 0.0, muon.neutralHadronIso() + muon.photonIso() - 0.5*muon.puChargedHadronIso() ) ) / muon.Pt());
    }
private:
    std::string Name;
    double ptCut;
    double EtaCut;
    double chi2Cut;
    double d0Cut;
    int nTrkLwMCut;
    int nMuValHit;
    int nValidPixelHits;
    int nSegMatched;
    double Zpv;
    double isoCut;
    std::vector<TRootMuon> DesiredMuons;
    std::vector<TRootMuon> LooseMuons;
    int nPixelWithMeasuredHits;
    int verbosity;
};
#endif	/* _MuonVetoSelector_H */

