/* 
 * File:   JetSelector.h
 * Author: ajafari
 *
 * Created on July 21, 2010, 7:08 PM
 */

#ifndef _JetSelector_H
#define	_JetSelector_H
#include <string>
#include <iostream>
#include "/user/ajafari/CMSSW_3_8_5_patch3/src/TopBrussels/TopTreeProducer/interface/TRootCaloJet.h"

using namespace TopTree;
using namespace std;
class JetSelector{
public:
    JetSelector(std::string name, std::string bTagAlgo = "TCHE", double pt = 25., double eta = 2.4,
            int nCaloTower = 5,double EmfUp = 1000.,double EmfLow = -1.,double fhpd_ = 1000., int N90_ = -1, double bTagCut_ = 4.):Name(name)
        ,btagAlgo(bTagAlgo)
        ,ptCut(pt)
        ,etaCut(eta)
        ,nCT(nCaloTower)
        ,emfUp(EmfUp)
        ,emfLow(EmfLow)
        ,fhpd(fhpd_)
        ,N90(N90_)
        ,bTagCut(bTagCut_){verbosity =0;/*JES = 1.;*/};
    virtual ~JetSelector(){};
    void verbose(int i){verbosity = i;}
    bool isGoodJet(TRootCaloJet jet){
//        double JetPt = (jet.Pt())*JES;
	if(verbosity > 0){
	    cout<<"eta: "<<fabs(jet.Eta())<<" (cut: "<<etaCut<<"), "<<bool(fabs(jet.Eta()) < etaCut)<<endl;
	    cout<<"pt: "<<jet.Pt()<<" (cut: "<<ptCut<<"), "<<bool(jet.Pt() > ptCut)<<endl;
	    cout<<"nCT: "<<jet.nConstituents()<<" (cut: "<<nCT<<"), "<<bool(jet.nConstituents()>nCT)<<endl;
	    cout<<"Emf: "<<jet.ecalEnergyFraction()<<"\n\t(cut Up: "<<emfUp<<"), "
                    <<bool(jet.ecalEnergyFraction()<emfUp)<<"\n\t(cut Low: "<<emfLow<<"), "
                    <<bool(jet.ecalEnergyFraction()>emfLow)<<endl;
	    cout<<"fHpd: "<<jet.fHPD()<<" (cut: "<<fhpd<<"), "<<bool(jet.fHPD()<fhpd)<<endl;
	    cout<<"N90: "<<jet.n90Hits()<<" (cut: "<<N90<<"), "<<bool(jet.n90Hits()>N90)<<endl;
	    if(fabs(jet.Eta()) < etaCut &&  jet.Pt() > ptCut &&  jet.nConstituents() > nCT &&
                    jet.ecalEnergyFraction() < emfUp && jet.ecalEnergyFraction() > emfLow &&
                    jet.fHPD() < fhpd && jet.n90Hits() > N90)
	    cout<<"Golden Jet is Accepted :-)"<<endl;
	}
        return (fabs(jet.Eta()) < etaCut &&  jet.Pt() > ptCut &&  jet.nConstituents() > nCT &&
                jet.ecalEnergyFraction() < emfUp && jet.ecalEnergyFraction() > emfLow
                && jet.fHPD() < fhpd && jet.n90Hits() > N90);
    }
    void setJets(std::vector<TRootCaloJet> jets){
        GoldenJets.clear();
        GoldenBJets.clear();
        GoldenBIndecies.clear();
        for(uint i = 0 ; i<jets.size(); i++){
	    if(verbosity > 0)
		cout<<"----- Jet number "<<i<<endl;
            if(isGoodJet(jets.at(i))){
                GoldenJets.push_back(jets.at(i));
                if(isB(jets.at(i))){
                    if(verbosity > 0)
			cout<<"The Golden BJet is found\n\tGolden Jet Number is "<<(GoldenJets.size() - 1)<<endl;
		    GoldenBJets.push_back(jets.at(i));
                    GoldenBIndecies.push_back((GoldenJets.size() - 1));
		}
            }
        }
    }
    int numberOfGoodJets(){
        return GoldenJets.size();
    }
    virtual bool EventPassedMe(){
        return (numberOfGoodJets() >= 4);
    }
    bool EventPassBtagging(){
        return (GoldenBJets.size() > 0);
    }
    std::vector<TRootCaloJet> bJets()const{return GoldenBJets;}
    std::vector<TRootCaloJet> goldenJets()const{return GoldenJets;}
    bool isB(TRootCaloJet jet)const{
        if(btagAlgo == "TCHE"){
	    if(verbosity > 0){
		cout<<"-- bTag Value: "<<jet.btag_trackCountingHighEffBJetTags()<<endl;
		if(jet.btag_trackCountingHighEffBJetTags() > bTagCut)
		    cout<<"bTagCut "<<bTagCut <<" passed ... "<<endl;
	    }
	    return (jet.btag_trackCountingHighEffBJetTags() > bTagCut);
	}
        if(btagAlgo == "TCHP")
            return (jet.btag_trackCountingHighPurBJetTags() > bTagCut);
//        if(btagAlgo == "SMNIP")
//            return (jet.btag_softMuonNoIPBJetTags() > bTagCut);
        if(btagAlgo == "SM")
            return (jet.btag_softMuonBJetTags() > bTagCut);
        if(btagAlgo == "SE")
            return (jet.btag_softElectronBJetTags() > bTagCut);
//        if(btagAlgo == "SSV")
//            return (jet.btag_simpleSecondaryVertexBJetTags() > bTagCut);
        if(btagAlgo == "JP")
            return (jet.btag_jetProbabilityBJetTags() > bTagCut);
        if(btagAlgo == "JBP")
            return (jet.btag_jetBProbabilityBJetTags() > bTagCut);
//        if(btagAlgo == "IPMVA")
//            return (jet.btag_impactParameterMVABJetTags() > bTagCut);
        if(btagAlgo == "CSVMVA")
            return (jet.btag_combinedSecondaryVertexMVABJetTags() > bTagCut);
        if(btagAlgo == "CSV")
            return (jet.btag_combinedSecondaryVertexBJetTags() > bTagCut);
        std::cout<<"BAD ALGORITHM, RETURNS FALSE ..."<<std::endl;
        return false;
    }
//    void setJES(double jes){
//        JES = jes;
//    }
    int FirstBtagIndexInGJets()const{
        int res = -1;
        if(GoldenBIndecies.size() == 0)
            return res;
        if(GoldenBIndecies.at(0) < 4)
            return GoldenBIndecies.at(0);
        return -1;
    };
private:
    std::string Name;
    std::string btagAlgo;
    double ptCut;
    double etaCut;
    int nCT;
    double emfUp;
    double emfLow;
    double fhpd;
    int N90;
    double bTagCut;
    std::vector<TRootCaloJet> GoldenBJets;
    std::vector<TRootCaloJet> GoldenJets;
    std::vector<int> GoldenBIndecies;
    int verbosity;
//    double JES;


};

#endif	/* _JetSelector_H */

