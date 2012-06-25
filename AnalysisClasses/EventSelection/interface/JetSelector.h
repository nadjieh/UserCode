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
#include "../../../TopBrussels/TopTreeProducer/interface/TRootCaloJet.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootPFJet.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootJet.h"

using namespace TopTree;
using namespace std;
class JetSelector{
public:
    JetSelector(std::string name, std::string bTagAlgo = "TCHE", double pt = 25., double eta = 2.4,
            int nCaloTower = 5,double EmfUp = 1000.,double EmfLow = -1.,double fhpd_ = 1000., int N90_ = -1, double bTagCut_ = 3.41):Name(name)
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

    bool isGoodPFJet(TRootPFJet jet){
                bool cond1 = bool(fabs(jet.Eta()) < etaCut &&  jet.Pt() > ptCut &&  jet.nConstituents() > nCT );
                bool cond2 = bool(jet.chargedEmEnergyFraction() < 0.99 && jet.neutralHadronEnergyFraction() < 0.99 &&
                             jet.neutralEmEnergyFraction() < 0.99 && jet.chargedHadronEnergyFraction() > 0 &&
                             jet.chargedMultiplicity() > 0);
                if(verbosity > 0){
                    cout<<"eta: "<<fabs(jet.Eta())<<" (cut: "<<etaCut<<"), "<<bool(fabs(jet.Eta()) < etaCut)<<endl;
                    cout<<"pt: "<<jet.Pt()<<" (cut: "<<ptCut<<"), "<<bool(jet.Pt() > ptCut)<<endl;
                    cout<<"nCT: "<<jet.nConstituents()<<" (cut: "<<nCT<<"), "<<bool(jet.nConstituents()>nCT)<<endl;
                    if(fabs(jet.Eta())<2.4){
                        cout<<"PFJet ID is applied:"<<endl;
                        cout<<"CEF: "<<jet.chargedEmEnergyFraction()<<" (cut: 0.99), "<<bool(jet.chargedEmEnergyFraction()<0.99)<<endl;
                        cout<<"NHF: "<<jet.neutralHadronEnergyFraction()<<" (cut: 0.99), "<<bool(jet.neutralHadronEnergyFraction()<0.99)<<endl;
                        cout<<"NEF: "<<jet.neutralEmEnergyFraction()<<" (cut: 0.99), "<<bool(jet.neutralEmEnergyFraction()<0.99)<<endl;
                        cout<<"CHF: "<<jet.chargedHadronEnergyFraction()<<" (cut: 0), "<<bool(jet.chargedHadronEnergyFraction()>0)<<endl;
                        cout<<"NCH: "<<jet.chargedMultiplicity()<<" (cut: 0), "<<bool(jet.chargedMultiplicity()>0)<<endl;
                    }
                }
                if(cond1 && fabs(jet.Eta())>=2.4 && verbosity > 0)
                    cout<<"Golden Jet is Accepted :-)\n"<<endl;
                if(cond1 && fabs(jet.Eta())>=2.4)
                        return cond1;
                else if(cond1 && fabs(jet.Eta())<2.4){
                        if(cond2 && verbosity > 0)
                            cout<<"Golden Jet is Accepted :-)\n"<<endl;
                        return cond2;
                }
                return cond1;
        }

    


    bool isGoodCaloJet(TRootCaloJet jet){
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

    bool isGoodJet(TRootCaloJet jet){
	return	this->isGoodCaloJet(jet);
    }
  void setCaloJets(std::vector<TRootCaloJet> jets){
        GoldenCaloJets.clear();
        GoldenCaloBJets.clear();
        GoldenBIndecies.clear();
        for(uint i = 0 ; i<jets.size(); i++){
            if(verbosity > 0)
                cout<<"----- Jet number "<<i<<endl;
            if(isGoodCaloJet(jets.at(i))){
                GoldenCaloJets.push_back(jets.at(i));
                if(isCaloB(jets.at(i))){
                    if(verbosity > 0)
                        cout<<"The Golden BJet is found\n\tGolden Jet Number is "<<(GoldenCaloJets.size() - 1)<<endl;
                    GoldenCaloBJets.push_back(jets.at(i));
                    GoldenBIndecies.push_back((GoldenCaloJets.size() - 1));
                }
            }
        }
    }

    void setJets(std::vector<TRootCaloJet> jets){
       this->setCaloJets(jets);
    }
  void setPFJets(std::vector<TRootPFJet> jets){
        GoldenPFJets.clear();
        GoldenPFBJets.clear();
        GoldenBIndecies.clear();
        for(uint i = 0 ; i<jets.size(); i++){
            if(verbosity > 0)
                cout<<"----- Jet number "<<i<<endl;
            bool s = isGoodPFJet(jets.at(i));
            if(s){
                GoldenPFJets.push_back(jets.at(i));
                if(isPFB(jets.at(i))){
                    if(verbosity > 0)
                        cout<<"The Golden BJet is found\n\tGolden Jet Number is "<<(GoldenPFJets.size() - 1)<<endl;
                    GoldenPFBJets.push_back(jets.at(i));
                    GoldenBIndecies.push_back((GoldenPFJets.size() - 1));
                }
            }
        }
    }

    int numberOfGoodCaloJets(){
        return GoldenCaloJets.size();
    }
    int numberOfGoodJets(){
        return this->numberOfGoodCaloJets();
    }
    int numberOfGoodPFJets(){
        return GoldenPFJets.size();
    }

    virtual bool EventPassedMeCalo(){
        return (numberOfGoodCaloJets() >= 4);
    }
    virtual bool EventPassedMe(){
        return this->EventPassedMeCalo();
    }

    bool EventPassBtaggingCalo(){
        return (GoldenCaloBJets.size() > 0);
    }
    bool EventPassBtaggingPF(){
        return (GoldenPFBJets.size() > 0);
    }
    bool EventPassBtagging(){
        return this->EventPassBtaggingCalo();
    }
    std::vector<TRootCaloJet> bJetsCalo()const{return GoldenCaloBJets;}
    std::vector<TRootCaloJet> goldenJetsCalo()const{return GoldenCaloJets;}
    std::vector<TRootCaloJet> bJets()const{return this->bJetsCalo();}
    std::vector<TRootCaloJet> goldenJets()const{return this->goldenJetsCalo();}
    std::vector<TRootPFJet> bJetsPF()const{return GoldenPFBJets;}
    std::vector<TRootPFJet> goldenJetsPF()const{return GoldenPFJets;}
    bool isCaloB(TRootCaloJet jet)const{
        if(btagAlgo == "TCHE"){
	    if(verbosity > 0){
		cout<<"-- bTag Value: "<<jet.btag_trackCountingHighEffBJetTags()<<endl;
		if(jet.btag_trackCountingHighEffBJetTags() > bTagCut)
		    cout<<"bTagCut "<<bTagCut <<" passed ... "<<endl;
	    }
	    return (jet.btag_trackCountingHighEffBJetTags() > bTagCut);
	}
        if(btagAlgo == "TCHP")
            if(verbosity > 0){
		cout<<"-- bTag Value: "<<jet.btag_trackCountingHighPurBJetTags()<<endl;
		if(jet.btag_trackCountingHighPurBJetTags() > bTagCut)
		    cout<<"bTagCut "<<bTagCut <<" passed ... "<<endl;
	    }
            return (jet.btag_trackCountingHighPurBJetTags() > bTagCut);
        if(btagAlgo == "JP"){
            if(verbosity > 0){
		cout<<"-- bTag Value: "<<jet.btag_jetProbabilityBJetTags()<<endl;
		if(jet.btag_jetProbabilityBJetTags() > bTagCut)
		    cout<<"bTagCut "<<bTagCut <<" passed ... "<<endl;
            }
            return (jet.btag_jetProbabilityBJetTags() > bTagCut);
        }
        if(btagAlgo == "JBP")
            return (jet.btag_jetBProbabilityBJetTags() > bTagCut);
        if(btagAlgo == "CSVMVA")
            return (jet.btag_combinedSecondaryVertexMVABJetTags() > bTagCut);
        if(btagAlgo == "CSV"){
            if(verbosity > 0){
		cout<<"-- bTag Value: "<<jet.btag_combinedSecondaryVertexBJetTags()<<endl;
		if(jet.btag_combinedSecondaryVertexBJetTags() > bTagCut)
		    cout<<"bTagCut "<<bTagCut <<" passed ... "<<endl;
            }
            return (jet.btag_combinedSecondaryVertexBJetTags() > bTagCut);
        }
       if(btagAlgo == "SSVE")
            return (jet.btag_simpleSecondaryVertexHighEffBJetTags() > bTagCut);
        if(btagAlgo == "SSVP")
            return (jet.btag_simpleSecondaryVertexHighPurBJetTags() > bTagCut);
        std::cout<<"BAD ALGORITHM, RETURNS FALSE ..."<<std::endl;
        return false;
    }
    bool isB(TRootCaloJet jet)const{return this->isCaloB(jet);}
    bool isPFB(TRootPFJet jet)const{
        if(btagAlgo == "TCHE"){
	    if(verbosity > 0){
		cout<<"-- bTag Value: "<<jet.btag_trackCountingHighEffBJetTags()<<endl;
		if(jet.btag_trackCountingHighEffBJetTags() > bTagCut)
		    cout<<"bTagCut "<<bTagCut <<" passed ... "<<endl;
	    }
	    return (jet.btag_trackCountingHighEffBJetTags() > bTagCut);
	}
        if(btagAlgo == "TCHP")
            if(verbosity > 0){
		cout<<"-- bTag Value: "<<jet.btag_trackCountingHighPurBJetTags()<<endl;
		if(jet.btag_trackCountingHighPurBJetTags() > bTagCut)
		    cout<<"bTagCut "<<bTagCut <<" passed ... "<<endl;
	    }
            return (jet.btag_trackCountingHighPurBJetTags() > bTagCut);
        if(btagAlgo == "JP")
            return (jet.btag_jetProbabilityBJetTags() > bTagCut);
        if(btagAlgo == "JBP")
            return (jet.btag_jetBProbabilityBJetTags() > bTagCut);
        if(btagAlgo == "CSVMVA")
            return (jet.btag_combinedSecondaryVertexMVABJetTags() > bTagCut);
        if(btagAlgo == "CSV")
            return (jet.btag_combinedSecondaryVertexBJetTags() > bTagCut);
       if(btagAlgo == "SSVE")
            return (jet.btag_simpleSecondaryVertexHighEffBJetTags() > bTagCut);
        if(btagAlgo == "SSVP")
            return (jet.btag_simpleSecondaryVertexHighPurBJetTags() > bTagCut);
        std::cout<<"BAD ALGORITHM, RETURNS FALSE ..."<<std::endl;
        return false;
    }
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
    std::vector<TRootPFJet> GoldenPFBJets;
    std::vector<TRootPFJet> GoldenPFJets;
    std::vector<TRootCaloJet> GoldenCaloBJets;
    std::vector<TRootCaloJet> GoldenCaloJets;
    std::vector<int> GoldenBIndecies;
    int verbosity;
//    double JES;


};

#endif	/* _JetSelector_H */

