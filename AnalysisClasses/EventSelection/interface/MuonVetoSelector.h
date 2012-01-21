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
		     double D0 = 0.02, int nvh = 11, double isoCut_ = 0.15, int nPixWithMeasuredHits = 1, int nSegM = 1):Name(name)
            ,ptCut(pt)
            ,EtaCut(eta)
            ,chi2Cut(chi2)
            ,d0Cut(D0)
            ,nvhCut(nvh)
            ,isoCut(isoCut_)
            ,nPixelWithMeasuredHits(nPixWithMeasuredHits)
	    ,nSegMatched(nSegM){verbosity = 0;};
    virtual ~MuonVetoSelector(){};
    void verbose(int i){verbosity = i;}
    bool isDesiredMuon(TRootMuon muon){
            double relIso=(muon.chargedHadronIso()+muon.neutralHadronIso()+muon.photonIso())/muon.Pt();
	    bool GlTrk = (muon.isTrackerMuon() && muon.isGlobalMuon());
	    bool isGlobalPromptTight = ((muon.nofValidMuHits()>0) && (muon.chi2()<chi2Cut));
	    if(verbosity > 2){
		cout<<"isGlobal: "<<muon.isGlobalMuon()<<endl;
		cout<<"isTracker: "<<muon.isTrackerMuon()<<endl;
		cout<<"eta: "<<fabs(muon.Eta())<<" <? " <<EtaCut<<endl;
		cout<<"pt: "<<muon.Pt()<<" > ? "<<ptCut<<endl;
		cout<<"Chi2: "<<muon.chi2()<<" < ? "<<chi2Cut<<endl;
		cout<<"D0: "<<muon.d0()<<" < ? "<<d0Cut<<endl;
		cout<<"nvh: "<<muon.nofValidHits()<< " >= ? "<<nvhCut<<endl;
		cout<<"nMuvh: "<<muon.nofValidMuHits()<< " >= ? 0"<<endl;
		cout<<"isoVal: "<<relIso<<" < ? "<<isoCut<<endl;
		cout<<"nPixelLayersWithMeasuredHits: "<<muon.nofPixelLayersWithMeasurement()<<" < ? "<<nPixelWithMeasuredHits<<endl;
		cout<<"nSegMatched: "<<muon.nofMatches()<<" < ? "<<nSegMatched<<endl;
		if(muon.Pt() > ptCut && fabs(muon.Eta()) < EtaCut  && fabs(muon.d0())< d0Cut && muon.nofValidHits()>= nvhCut && relIso< isoCut && isGlobalPromptTight && GlTrk && (muon.nofPixelLayersWithMeasurement() >= nPixelWithMeasuredHits) && (muon.nofMatches()>nSegMatched))
		    cout<<"Desired Muon is found :-)"<<endl;
	    }
            return(muon.Pt() > ptCut && fabs(muon.Eta()) < EtaCut && fabs(muon.d0())< d0Cut && muon.nofValidHits()>= nvhCut && relIso< isoCut && isGlobalPromptTight && GlTrk &&  (muon.nofPixelLayersWithMeasurement() >= nPixelWithMeasuredHits) && (muon.nofMatches()>nSegMatched));
    }
    bool isLooseMuon(TRootMuon muon ){
            double relIso=(muon.chargedHadronIso()+muon.neutralHadronIso()+muon.photonIso())/muon.Pt();
	    if(verbosity > 2){
		cout<<"isGlobal: "<<muon.isGlobalMuon()<<endl;
		cout<<"eta: "<<fabs(muon.Eta())<<" <? 2.5" <<endl;
		cout<<"pt: "<<muon.Pt()<<" > ? 10"<<endl;
		cout<<"isoVal: "<<relIso<<" < ? 0.2"<<endl;
		if(muon.isGlobalMuon() && (fabs(muon.Eta())<2.5) && (muon.Pt()>10) && relIso<0.2)
		    cout<<"Loose electron is found :-("<<endl;
	    }
	    return (muon.isGlobalMuon() && (fabs(muon.Eta())<2.5) && (muon.Pt()>10) && relIso<0.2);
    }
    void setMuons(std::vector<TRootMuon> muons){
        DesiredMuons.clear();
	//cout<<"Muon.size : "<<muons.size()<<endl; 
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
    virtual bool EventPassedMe(){
        return(this->numberOfDesiredMuon() < 1);
    }
    std::vector<TRootMuon> desiredMuons()const{return DesiredMuons; }
    std::vector<TRootMuon> looseMuons()const{return LooseMuons; }
private:
    std::string Name;
    double ptCut;
    double EtaCut;
    double chi2Cut;
    double d0Cut;
    int nvhCut;
    double isoCut;
    std::vector<TRootMuon> DesiredMuons;
    std::vector<TRootMuon> LooseMuons;
    int nPixelWithMeasuredHits;
    int nSegMatched;
    int verbosity;
};
#endif	/* _MuonVetoSelector_H */

