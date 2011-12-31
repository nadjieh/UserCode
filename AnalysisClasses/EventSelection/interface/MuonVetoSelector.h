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
#include "/user/ajafari/CMSSW_3_8_5_patch3/src/TopBrussels/TopTreeProducer/interface/TRootMuon.h"
using namespace TopTree;
using namespace std;
class MuonVetoSelector{
public:
    MuonVetoSelector(std::string name, double pt = 20., double eta = 2.4,double chi2 = 10,
		     double D0 = 0.02, int nvh = 11, double isoCut_ = 0.05, bool doGlobal = false):Name(name)
            ,ptCut(pt)
            ,EtaCut(eta)
            ,chi2Cut(chi2)
            ,d0Cut(D0)
            ,nvhCut(nvh)
            ,isoCut(isoCut_)
            ,doGL(doGlobal){verbosity = 0;};
    virtual ~MuonVetoSelector(){};
    void verbose(int i){verbosity = i;}
    bool isDesiredMuon(TRootMuon muon){
            double relIso=(muon.isoR03_sumPt()+muon.isoR03_emEt()+muon.isoR03_hadEt())/muon.Pt();
	    bool GL = true;
	    if(doGL)
	      GL = muon.isGlobalMuon();
	    if(verbosity > 2){
		cout<<"eta: "<<fabs(muon.Eta())<<" <? " <<EtaCut<<endl;
		cout<<"pt: "<<muon.Pt()<<" > ? "<<ptCut<<endl;
		cout<<"Chi2: "<<muon.chi2()<<" < ? "<<chi2Cut<<endl;
		cout<<"D0: "<<muon.d0()<<" < ? "<<d0Cut<<endl;
		cout<<"nvh: "<<muon.nofValidHits()<< " >= ? "<<nvhCut<<endl;
		cout<<"isoVal: "<<relIso<<" < ? "<<relIso<<endl;
		cout<<"doGL: "<<doGL<<"\tisGlobal: "<<GL<<endl;
		if(muon.Pt() > ptCut && fabs(muon.Eta()) < EtaCut && muon.chi2()< chi2Cut && fabs(muon.d0())< d0Cut && muon.nofValidHits()>= nvhCut && relIso< isoCut && GL)
		    cout<<"Desired Muon is found :-("<<endl;
	    }
            return(muon.Pt() > ptCut && fabs(muon.Eta()) < EtaCut && muon.chi2()< chi2Cut && fabs(muon.d0())< d0Cut && muon.nofValidHits()>= nvhCut && relIso< isoCut && GL);
    }
    void setMuons(std::vector<TRootMuon> muons){
        DesiredMuons.clear();
	//cout<<"Muon.size : "<<muons.size()<<endl; 
        for(uint i = 0; i<muons.size(); i++){
	    if(verbosity > 0)
		cout<<"***** Muon number "<<i<<endl;
            if(isDesiredMuon(muons.at(i)))
                DesiredMuons.push_back(muons.at(i));
        }
    }
    int numberOfDesiredMuon(){
        return DesiredMuons.size();
    }
    virtual bool EventPassedMe(){
        return(this->numberOfDesiredMuon() < 1);
    }
    std::vector<TRootMuon> desiredMuons()const{return DesiredMuons; }
private:
    std::string Name;
    double ptCut;
    double EtaCut;
    double chi2Cut;
    double d0Cut;
    int nvhCut;
    double isoCut;
    std::vector<TRootMuon> DesiredMuons;
    bool doGL;
    int verbosity;
};
#endif	/* _MuonVetoSelector_H */

