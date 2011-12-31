/* 
 * File:   TopEvent.h
 * Author: ajafari
 *
 * Created on August 20, 2010, 12:06 PM
 */

#ifndef _TOPEVENT_H
#define	_TOPEVENT_H

#include "/user/ajafari/CMSSW_3_8_5_patch3/src/TopBrussels/TopTreeProducer/interface/TRootElectron.h"
#include "/user/ajafari/CMSSW_3_8_5_patch3/src/AnalysisClasses/ChiSquared/interface/ExtendedJet.h"
#include "/user/ajafari/CMSSW_3_8_5_patch3/src/AnalysisClasses/LightJets/interface/NeededStructs.h"
#include "TLorentzVector.h"
#include <vector>
#include <string>
using namespace std;
using namespace TopTree;

class TopEvent{
public:
    TopEvent(std::vector<ExtendedJet> jets, TRootElectron elec, MassAndResolution constraint):Electron(elec){
        Jets.clear();
        for(uint i = 0; i<jets.size(); i++)
            Jets.push_back(jets.at(i));
        constraints.topMass = constraint.topMass;
        constraints.topRes = constraint.topRes;
        constraints.wMass = constraint.wMass;
        constraints.wRes = constraint.wRes;
    };
    TopEvent(){
        Jets.clear();
        Electron = TLorentzVector(-1,-1,-1,-1);
        constraints.topMass = 0;
        constraints.wMass = 0;
        constraints.topRes = 0;
        constraints.wRes = 0;
        WIndecies.first = -1;
        WIndecies.second = -1;
        HadBIndex = -1;
        LepBIndex = -1;
    };
    ~TopEvent(){};
    
    std::vector<ExtendedJet> Jets;
    TRootElectron Electron;
    MassAndResolution constraints;
    std::pair<int,int> WIndecies;
    int HadBIndex;
    int LepBIndex;
    double M3; //depend on the leptonic bjet
    double TopPtSum;
    ExtendedJet getLepBCand()const{
        return Jets.at(LepBIndex);
    }
    ExtendedJet getHadBCand()const{
        return Jets.at(HadBIndex);
    }
    ExtendedJet getQ1()const{
//        cout<<"Q1: "<<WIndecies.first<<endl;
        return Jets.at(WIndecies.first);
    }
    ExtendedJet getQ2()const{
//        cout<<"Q2: "<<WIndecies.second<<endl;
        return Jets.at(WIndecies.second);
    }

    double getWChiSquared()const{
        TLorentzVector W = this->getHadronicW();
        double res = (W.M() - constraints.wMass) * (W.M() - constraints.wMass);
        res = (double)res/(constraints.wRes * constraints.wRes);
        return res;
    }
    double getTopChiSquared()const{
        TLorentzVector Top = this->getHadronicTop();
        double Wpart = this->getWChiSquared();
        double TopPart = (Top.M() - constraints.topMass) * (Top.M() - constraints.topMass);
        TopPart = (double)TopPart/(constraints.topRes * constraints.topRes);
        return (Wpart + TopPart);
    }
    double getMlb()const{
        TLorentzVector LB = (TLorentzVector)(this->getLepBCand().getJet()) + (TLorentzVector)(Electron);
        return LB.M();
    }
    double getMlHadB()const{
        TLorentzVector HB = (TLorentzVector)(this->getHadBCand().getJet()) + (TLorentzVector)(Electron);
        return HB.M();
    }
    double getMll1()const{
        TLorentzVector ll1 = (TLorentzVector)(this->getQ1().getJet()) + (TLorentzVector)(Electron);
        return ll1.M();
    }
    double getMll2()const{
        TLorentzVector ll2 = (TLorentzVector)(this->getQ2().getJet()) + (TLorentzVector)(Electron);
        return ll2.M();
    }

    bool isQ1Matched()const{
        return ((this->getQ1().getMatchName() == "Q") || (this->getQ1().getMatchName() == "QBar"));
    }
    bool isQ2Matched()const{
        return ((this->getQ2().getMatchName() == "Q") || (this->getQ2().getMatchName() == "QBar"));
    }
    bool isWMatched()const{
        bool res = this->isQ1Matched() && this->isQ2Matched() && 
        (this->getQ1().getMatchName() != this->getQ2().getMatchName());
        return res;
    }
    bool isHadBCandMatched()const{
        return (this->getHadBCand().getMatchName() == "HadB");
    }
    bool isLepBCandMatched()const{
        return (this->getLepBCand().getMatchName() == "LepB");
    }
    bool isHadronicTopMatched()const{
        return (this->isWMatched() && this->isHadBCandMatched());
    }
    
    bool LeptonicJetIsB()const{
        std::string match = this->getLepBCand().getMatchName();
        return (match == "HadB" || match == "LepB");
    }

    TLorentzVector getHadronicTop()const{
       return (this->getHadronicW() +(TLorentzVector)(this->getHadBCand().getJet()));
    }

    TLorentzVector getHadronicW()const{
       return ((TLorentzVector)(this->getQ1().getJet()) + (TLorentzVector)(this->getQ2().getJet()));
    }
};


#endif	/* _TOPEVENT_H */

