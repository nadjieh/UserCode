/* 
 * File:   ElectronSelector.h
 * Author: ajafari
 *
 * Created on November 28, 2009, 4:15 PM
 */

#ifndef _ELECTRONSELECTOR_H
#define	_ELECTRONSELECTOR_H


#include <iomanip>
#include "../../../TopBrussels/TopTreeProducer/interface/TRootMuon.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootElectron.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootJet.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootMET.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootGenEvent.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootEvent.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootRun.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootParticle.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootMCParticle.h"
#include <sstream>
//#include "VBTF70.h" 
#include <TFile.h>
#include <TH1.h>
#include <TH2.h>
#include <TCanvas.h>
#include <TBranch.h>
#include <TTree.h>
#include <TClonesArray.h>
#include <vector>
#include <iostream>
using namespace TopTree;
using namespace std;


class ElectronSelector{
public:
    ElectronSelector(std::string name,double pt = 30., double eta = 2.5, double Exc_Low = 1.4442
        ,double Exc_High = 1.5660, std::string Id = "rTight",std::string secondID = "rLoose" ,
	std::string Iso = "", double D0 = 0.02, double IsoCut = 0.125,double secPt = 15., 
        double distToPV = 10000.,double secIsoCut =0.2 ):Name(name)
        ,ptCut(pt)
        ,etaCut(eta)
        ,exclusion_Low(Exc_Low)
        ,exclusion_High(Exc_High)
        ,id(Id)
        ,idSec(secondID)
        ,iso(Iso)
        ,d0Cut(D0)
        ,isoCut(IsoCut)
        ,secondptCut(secPt)
        ,distToPv(distToPV)
        ,secondIsoCut(secIsoCut){verbosity = 0;};

    virtual ~ElectronSelector(){};
    void verbose(int i){verbosity = i;}

    bool isGoodElectron(TRootElectron e, std::string gap= "SC", double PVposition = 0.){
        //double distanceToPV = fabs(e.vz() - PVposition);
	//bool closeToPV = (distanceToPV < distToPv);
	//if(verbosity > 2 )
  	//     cout<<"PV position Z: "<<PVposition<<", distanceToPV = "<<distanceToPV<<" ? "<<distToPv<<" isOk = "<<closeToPV<<endl;
        double eta = fabs(e.Eta());
	if (verbosity > 2)
		cout<<"eta: "<<eta<<endl;
	bool EtaGoodRange = (eta < etaCut);
        if(gap == "SC")
            eta = fabs(e.caloPosition().Eta());
	if (verbosity > 2)
		cout<<"etaSC: "<<eta<<endl;
        EtaGoodRange = (EtaGoodRange && !(exclusion_Low < eta && eta < exclusion_High) );
	if (verbosity > 2)
		cout<<"eta in range: "<<EtaGoodRange<<endl;
	bool PtGoodRange = e.Pt() > ptCut;
	if (verbosity > 2)
		cout<<"Pt: "<<e.Pt()<<"\tPtGoodRange: "<<PtGoodRange<<endl;
	bool Id = this->isId(e);
	if (verbosity > 2)
		cout<<"ID: "<<Id<<endl;
	double relIso = (e.chargedHadronIso()+e.neutralHadronIso()+e.photonIso())/e.Pt();
	bool isIso = (relIso<isoCut);
	if (verbosity > 2)
		cout<<"IsoVal: "<<relIso<<"\tisIso: "<<isIso<<endl;
        bool d0Constraint = (fabs(e.d0()) < d0Cut);//wrt BS
	if (verbosity > 2){
		cout<<"D0: "<<fabs(e.d0())<<"\td0Constraint: "<<d0Constraint<<endl;
//		cout<<"ip: "<<fabs(e.dB())<<"\td0Constraint: "<<d0Constraint<<endl;
        }
	if (verbosity > 2)
		if(EtaGoodRange && PtGoodRange && Id && isIso && d0Constraint/* && closeToPV*/)
			cout<<"Golden Electron is Accepted :-)"<<endl;
	return(EtaGoodRange && PtGoodRange && Id && isIso && d0Constraint/* && closeToPV*/);
    }
    bool isSecondElectron(TRootElectron e, std::string gap= "SC"){
        double eta = fabs(e.Eta());
	if (verbosity > 2)
		cout<<"eta: "<<eta<<endl;
	bool EtaGoodRange = (eta < etaCut);
       // if(gap == "SC")
       //     eta = fabs(e.caloPosition().Eta());
       //if (verbosity > 2)
//		cout<<"etaSC: "<<eta<<endl;
//        EtaGoodRange = (EtaGoodRange && !(exclusion_Low < eta && eta < exclusion_High) );
	if (verbosity > 2)
		cout<<"eta in range: "<<EtaGoodRange<<endl;
	bool PtGoodRange = e.Pt() > secondptCut;
	if (verbosity > 2)
		cout<<"Pt: "<<e.Pt()<<"\tPtGoodRange: "<<PtGoodRange<<endl;
	//bool Id = this->isSecondId(e);
	//if (verbosity > 2)
	//	cout<<"ID: "<<Id<<endl;
	double relIso = (e.chargedHadronIso()+e.neutralHadronIso()+e.photonIso())/e.Pt();
	bool isIso = (relIso<secondIsoCut);
	if(verbosity > 2 )
	  cout<<"IsoVal = "<<relIso<<" isIso: "<<isIso<<endl;
	if (verbosity > 2)
		if(EtaGoodRange && PtGoodRange /*&& Id*/ && isIso)
			cout<<"Second Electron is Accepted :-)"<<endl;
	return(EtaGoodRange && PtGoodRange /*&& Id*/ && isIso);
    }
    bool isVBTF70Id(TopTree::TRootElectron * e){
	if(e->isEB()){//ECal Barrel
            if(verbosity > 2){
                cout<<"\tElectron eta is "<<e->Eta()<<" and is EB: "<<endl;
                cout<<"\t\tHoE: "<<fabs(e->hadronicOverEm())<<" ? "<<0.025<<endl;
                cout<<"\t\tSiEta: "<<fabs(e->sigmaIEtaIEta())<<" ? "<<0.01<<endl;
                cout<<"\t\tDelEta: "<<fabs(e->deltaEtaIn())<<" ? "<<0.004<<endl;
                cout<<"\t\tDelPhi: "<<fabs(e->deltaPhiIn())<<" ? "<<0.03<<endl;
                cout<<"\t\tIsId: "<<(fabs(e->hadronicOverEm()) < 0.025 && fabs(e->sigmaIEtaIEta()) < 0.01
                        && fabs(e->deltaEtaIn()) < 0.004 && fabs(e->deltaPhiIn()) < 0.03)<<endl;
            }
            return(fabs(e->hadronicOverEm()) < 0.025 && fabs(e->sigmaIEtaIEta()) < 0.01
                    && fabs(e->deltaEtaIn()) < 0.004 && fabs(e->deltaPhiIn()) < 0.03);
	}
	if(e->isEE()){//ECal EndCap
            if(verbosity > 2){
                cout<<"\tElectron eta is "<<e->Eta()<<" and is EE: "<<endl;
                cout<<"\t\tHoE: "<<fabs(e->hadronicOverEm())<<" ? "<<0.025<<endl;
                cout<<"\t\tSiEta: "<<fabs(e->sigmaIEtaIEta())<<" ? "<<0.03<<endl;
                cout<<"\t\tDelEta: "<<fabs(e->deltaEtaIn())<<" ? "<<0.005<<endl;
                cout<<"\t\tDelPhi: "<<fabs(e->deltaPhiIn())<<" ? "<<0.02<<endl;
                cout<<"\t\tIsId: "<<(fabs(e->hadronicOverEm()) < 0.025 && fabs(e->sigmaIEtaIEta()) < 0.03
                    && fabs(e->deltaEtaIn()) < 0.005 && fabs(e->deltaPhiIn()) < 0.02)<<endl;
            }
            return(fabs(e->hadronicOverEm()) < 0.025 && fabs(e->sigmaIEtaIEta()) < 0.03
                    && fabs(e->deltaEtaIn()) < 0.005 && fabs(e->deltaPhiIn()) < 0.02);
	}
	cout<<"Eta position is weird! return false ////////////"<<endl;
	return false;
    }
    bool isVBTF95Id(TopTree::TRootElectron * e){
	if(e->isEB()){//ECal Barrel
            if(verbosity > 2){
                cout<<"\tElectron eta is "<<e->Eta()<<" and is EB: "<<endl;
                cout<<"\t\tHoE: "<<fabs(e->hadronicOverEm())<<" ? "<<0.15<<endl;
                cout<<"\t\tSiEta: "<<fabs(e->sigmaIEtaIEta())<<" ? "<<0.01<<endl;
                cout<<"\t\tDelEta: "<<fabs(e->deltaEtaIn())<<" ? "<<0.007<<endl;
                cout<<"\t\tDelPhi: "<<fabs(e->deltaPhiIn())<<" ? "<<0.8<<endl;
                cout<<"\t\tIsId: "<<(fabs(e->hadronicOverEm()) < 0.15 && fabs(e->sigmaIEtaIEta()) < 0.01
                    && fabs(e->deltaEtaIn()) < 0.007 && fabs(e->deltaPhiIn()) < 0.8)<<endl;
            }
            return(fabs(e->hadronicOverEm()) < 0.15 && fabs(e->sigmaIEtaIEta()) < 0.01
                    && fabs(e->deltaEtaIn()) < 0.007 && fabs(e->deltaPhiIn()) < 0.8);
	}
	if(e->isEE()){//ECal EndCap
            if(verbosity > 2){
                cout<<"\tElectron eta is "<<e->Eta()<<" and is EE: "<<endl;
                cout<<"\t\tHoE: "<<fabs(e->hadronicOverEm())<<" ? "<<0.07<<endl;
                cout<<"\t\tSiEta: "<<fabs(e->sigmaIEtaIEta())<<" ? "<<0.03<<endl;
                cout<<"\t\tDelEta: "<<fabs(e->deltaEtaIn())<<" ? "<<0.01<<endl;
                cout<<"\t\tDelPhi: "<<fabs(e->deltaPhiIn())<<" ? "<<0.7<<endl;
                cout<<"\t\tIsId: "<<(fabs(e->hadronicOverEm()) < 0.07 && fabs(e->sigmaIEtaIEta()) < 0.03
                    && fabs(e->deltaEtaIn()) < 0.01 && fabs(e->deltaPhiIn()) < 0.7)<<endl;
            }
            return(fabs(e->hadronicOverEm()) < 0.07 && fabs(e->sigmaIEtaIEta()) < 0.03
                    && fabs(e->deltaEtaIn()) < 0.01 && fabs(e->deltaPhiIn()) < 0.7);
	}
	cout<<"Eta position is weird! return false ////////////"<<endl;
	return false;
    }
    bool isId(TRootElectron e){
        if(id == "rTight")
            return e.isRobustTight();
        else if(id == "rLoose")
            return e.isRobustLoose();
        else if(id == "Loose")
            return e.isLoose();
        else if(id == "Tight")
            return e.isTight();
        else if(id == "VBTF70"){
            if(verbosity > 2)
                cout<<"\tId is "<<id<<endl;
            return isVBTF70Id(&e);
        }
        else if(id == "VBTF95"){
            if(verbosity > 2)
                cout<<"\tId is "<<id<<endl;
            return isVBTF95Id(&e);
        }
        else if(id == "NoId")
            return true;
        std::cout<<"Bad ID, returns false"<<std::endl;
        return false;
    }
    bool isSecondId(TRootElectron e){
        if(idSec == "rTight")
            return e.isRobustTight();
        else if(idSec == "rLoose")
            return e.isRobustLoose();
        else if(idSec == "Loose")
            return e.isLoose();
        else if(idSec == "Tight")
            return e.isTight();
        else if(idSec == "VBTF70"){
            if(verbosity > 2)
                cout<<"\tId is "<<idSec<<endl;
            return isVBTF70Id(&e);
        }
        else if(idSec == "VBTF95"){
            if(verbosity > 2)
                cout<<"\tId is "<<idSec<<endl;
            return isVBTF95Id(&e);
        } else if(id == "NoId")
            return false;
        std::cout<<"Bad ID, returns false"<<std::endl;
        return false;
    }
    void setElectrons(std::vector<TRootElectron> input, double PVposition = 0.){
        goldenElecs.clear();
        secondElecs.clear();
        for(uint i =0; i<input.size(); i++){
	    if(verbosity > 2)
		cout<<"====== Electron number "<<i<<endl;
            if(isGoodElectron(input.at(i),"SC",PVposition)){
                goldenElecs.push_back(input.at(i));
            }
            else if(isSecondElectron(input.at(i)))
                secondElecs.push_back(input.at(i));
        }
	if(verbosity > 2){
	    cout<<"number of Goldens: "<<goldenElecs.size()<<endl;
	    cout<<"number of Seconds: "<<secondElecs.size()<<endl;
	    cout<<"=================="<<endl;
	}
    }
    int numberOfGE()const{

        return goldenElecs.size();
    }
    virtual bool EventPassedMe(){
        return (this->numberOfGE() > 0);
    }
    TRootElectron GoldenElec()const{
        return goldenElecs.at(0);
    }
    bool MuChannelPassElecVeto(){return ((this->secondElectrons().size() == 0) && (this->GoldenElecs().size()==0));}
    bool ElecChannelPassElecVeto(){return ( this->secondElectrons().size()==0);}
    std::vector<TRootElectron> GoldenElecs()const{
	if(verbosity > 2)
	    cout<<"in the GoldenElecs method size is: "<<goldenElecs.size()<<endl;
	return goldenElecs;
    }
    bool GoldenNotFromConversion()const{return ((fabs(goldenElecs.at(0).DCot()) > 0.02 || fabs(goldenElecs.at(0).Dist()) > 0.02)  &&(goldenElecs.at(0).missingHits() == 0) );}
    bool EventPassConversion()const{return this->GoldenNotFromConversion();}// backward compatibility
    std::vector<TRootElectron> secondElectrons()const{return secondElecs;};
private:
    std::string Name;
    double ptCut;
    double etaCut;
    double exclusion_Low;
    double exclusion_High;
    std::string id;
    std::string idSec;
    std::string iso;
    double d0Cut;
    double isoCut;
    double secondptCut;
    std::vector<TRootElectron> secondElecs;
    std::vector<TRootElectron> goldenElecs;
    int verbosity;
    double distToPv;
    double secondIsoCut;
};
#endif	/* _ELECTRONSELECTOR_H */


