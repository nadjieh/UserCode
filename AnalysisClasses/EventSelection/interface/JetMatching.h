
/* 
 * File:   JetMatching.h
 * Author: ajafari
 *
 * Created on May 5, 2010, 4:47 PM
 */
#ifndef _JETMATCHING_H
#define	_JETMATCHING_H
#include <vector>
#include <TLorentzVector.h>
#include <TClonesArray.h>
#include <iostream>
#include "../../../TopBrussels/TopTreeProducer/interface/TRootGenEvent.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootElectron.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootNPGenEvent.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootCaloJet.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootMCParticle.h"
#include "../../../AnalysisClasses/ChiSquared/interface/DR.h"


using namespace std;
using namespace TopTree;

struct mySortByPt{
    bool operator() (std::pair<TLorentzVector, int> comb1, std::pair<TLorentzVector, int> comb2) { return (comb1.first.Pt() > comb2.first.Pt());}
} SortByPt;
bool MaryamMethod_TtBarSemiElec_Correlation(const std::vector<TRootCaloJet>& mjetsV,TRootGenEvent * gevent,std::vector<std::pair<TRootCaloJet, int> >& recJets,const TClonesArray* genEvents){
    
    
    recJets.clear();
    for(unsigned int j = 0; j < 4/*mjetsV.size()*/; j++) {
		recJets.push_back(make_pair(mjetsV.at(j), -1));
	}

    std::vector<std::pair<TLorentzVector, int> >  PrtonsWithRefs;

    for(int i=0;i<genEvents->GetEntriesFast();i++){
            gevent = (TRootGenEvent*) genEvents->At(i);
            PrtonsWithRefs.push_back(make_pair(gevent->hadronicDecayB(),0));
            PrtonsWithRefs.push_back(make_pair(gevent->leptonicDecayB(),1));
            PrtonsWithRefs.push_back(make_pair(gevent->hadronicDecayQuark(),2));
            PrtonsWithRefs.push_back(make_pair(gevent->hadronicDecayQuarkBar(),3));
            }
            std::sort(PrtonsWithRefs.begin(), PrtonsWithRefs.end(), SortByPt);


    for (unsigned int i = 0; i < PrtonsWithRefs.size(); i++) {
            double minDR = -1.;
//            TRootCaloJet * matchJet = 0;
            for (int k = 0; k < 4/*recJets.size()*/; k++) {
                DR<TLorentzVector> dmr(PrtonsWithRefs[i].first,(recJets[k].first));
                    double tmpDR = dmr.getValue();
                    if((tmpDR < minDR || minDR == -1) && recJets[k].second == -1) {
                            minDR = tmpDR;
                            if(fabs(minDR) <= 0.3) {
//                                    matchJet=&(recJets[k].first);
                                    for(unsigned int m = 0; m < 4/*recJets.size()*/; m++)
                                            if(recJets[m].second == PrtonsWithRefs[i].second) recJets[m].second = -1;
                                    recJets[k].second = PrtonsWithRefs[i].second;
                            }
                    }
            }
    }
//            cout<<"jet one: "<<recJets[0].second<<"\njet two :"<<recJets[1].second<<"\njet three: "<<recJets[2].second;
//            cout<<"\njet four: "<<recJets[3].second<<endl;
     return(recJets[0].second != -1 && recJets[1].second != -1 && recJets[2].second != -1 && recJets[3].second != -1);

}
bool MaryamMethod_Others_Correlation(std::vector<TRootCaloJet> mjetsV,TRootNPGenEvent * gevent,std::vector<std::pair<TRootCaloJet, int> >& recJets){
    TRootCaloJet J;
    recJets.clear();
    for(unsigned int j = 0; j < 4/*mjetsV.size()*/; j++) {
		J = mjetsV.at(j);
		recJets.push_back(make_pair(J, -1));
	}
    std::vector<TRootMCParticle> Quarks = gevent->bquarks();
    std::vector<std::pair<TLorentzVector, int> >  PrtonsWithRefs;
    PrtonsWithRefs.clear();
    for(uint q = 0; q<Quarks.size(); q++){
        PrtonsWithRefs.push_back(make_pair(((TLorentzVector)Quarks.at(q)),0));
    }
    Quarks.clear();
    Quarks = gevent->quarks();
    for(uint q = 0; q<Quarks.size(); q++){
        PrtonsWithRefs.push_back(make_pair(((TLorentzVector)Quarks.at(q)),2));
    }
    std::sort(PrtonsWithRefs.begin(), PrtonsWithRefs.end(), SortByPt);


//    uint nQuarks = ;
//    if(nQuarks > 4)
//        nQuarks = 4;
    for (unsigned int i = 0; i < PrtonsWithRefs.size(); i++) {
            double minDR = -1.;
//            TRootCaloJet * matchJet = 0;
            for (int k = 0; k < 4/*recJets.size()*/; k++) {
                DR<TLorentzVector> dmr(PrtonsWithRefs[i].first,(recJets[k].first));
                    double tmpDR = dmr.getValue();
                    if((tmpDR < minDR || minDR == -1) && recJets[k].second == -1) {
                            minDR = tmpDR;
                            if(fabs(minDR) <= 0.3) {
//                                    matchJet=&(recJets[k].first);
                                    for(unsigned int m = 0; m < 4/*recJets.size()*/; m++)
                                            if(recJets[m].second == PrtonsWithRefs[i].second) recJets[m].second = -1;
                                    recJets[k].second = PrtonsWithRefs[i].second;
                            }
                    }
            }
    }
//    for(unsigned int j = 0; j < 4/*mjetsV.size()*/; j++){
////        cout<<j+1<<"'th Jet: "<<recJets.at(j).second<<endl;
//    }
     return(recJets[0].second != -1 && recJets[1].second != -1 && recJets[2].second != -1 && recJets[3].second != -1);

}
void ElectronMatcher(TLorentzVector GenElec, std::vector<TRootElectron> goldenElecs, int& matchedEleIndex){
//        cout<<"I am in Electron Matcher in the index at first is "<<matchedEleIndex<<endl;
        
        double minErr = 1000000.;
        for(unsigned int i = 0; i<goldenElecs.size(); i++){
            TLorentzVector myE(goldenElecs.at(i));
            DR<TLorentzVector> dr(myE,GenElec);
            if(dr.getValue() >= 0.3)
                continue;
          
//            cout<<"In the cone of 0.3\t"<<dr.getValue()<<endl;
            double PtDif = (double)(GenElec.Pt() - myE.Pt())/(double)GenElec.Pt();
//                cout<<"\tPtErr: "<<PtDif<<"\n";
            if (fabs(PtDif)>3.0)
                continue;
            if (PtDif<minErr){
                minErr = PtDif;
                matchedEleIndex = i;
//                cout<<"I have found vit!!\t"<<i<<"\t"<<matchedEleIndex<<endl;
            }
        }
        
//        cout<<"Final MatchingIndex: "<<matchedEleIndex<<endl;
    }

bool isTwoElectronMatched(TLorentzVector gen,TLorentzVector reco){
    DR<TLorentzVector> dr(gen,reco);
    if(dr.getValue() >= 0.3)
        return false;
    double PtDif = (double)(gen.Pt() - reco.Pt())/(double)gen.Pt();
//                cout<<"\tPtErr: "<<PtDif<<"\n";
    if (fabs(PtDif)>3.0)
        return false;
    return true;

}

void ZElectronMatcher(std::vector<TLorentzVector> GenElec, std::vector<TRootElectron> goldenElecs,
int& matchedEleIndex1, int& matchedEleIndex2 ){
    if(GenElec.size() != 2){
        matchedEleIndex1 = -1;
        matchedEleIndex2 = -1;
        return;
    }
//    std::vector<std::pair<int,double> > gen1;
//    std::vector<std::pair<int,double> > gen2;
//
//    gen1.clear();
//    gen2.clear();
//
//    Info.clear();
    double minErr1 = 10000;
    double minErr2 = 10000;

    matchedEleIndex1 = -1;
    matchedEleIndex2 = -1;

    int index1 = -1;
    int index2 = -1;

    for(unsigned int i = 0; i<goldenElecs.size(); i++){
        TLorentzVector myE(goldenElecs.at(i));

        TLorentzVector myGen1(GenElec.at(0));
        DR<TLorentzVector> dr1(myE,myGen1);

        TLorentzVector myGen2(GenElec.at(1));
        DR<TLorentzVector> dr2(myE,myGen2);

        if(dr1.getValue() <= 0.3){
            double PtDif = (double)(myE.Pt() - myGen1.Pt())/(double)myGen1.Pt();
            if(PtDif <= 3.0){
                if(PtDif < minErr1){
                    minErr1 = PtDif;
                    index1 = i;
                }
            }
        }
        if(dr2.getValue() <= 0.3){
            double PtDif = (double)(myE.Pt() - myGen2.Pt())/(double)myGen2.Pt();
            if(PtDif <= 3.0){
                if(PtDif < minErr2){
                    minErr2 = PtDif;
                    index2 = i;
                }
            }
        }
    }
    if(index2 != index1){
        matchedEleIndex1 = index1;
        matchedEleIndex2 = index2;
        return;
    }

}

#endif	/* _JETMATCHING_H */

