/* 
 * File:   PairMaker2.h
 * Author: ajafari
 *
 * Created on October 24, 2010, 3:54 PM
 */

#ifndef PAIRMAKER2_H
#define	PAIRMAKER2_H
#include <vector>
#include "/afs/cern.ch/user/a/ajafari/scratch0/CMSSW_3_8_5_patch3/src/TopBrussels/TopTreeProducer/interface/TRootElectron.h"
#include "/afs/cern.ch/user/a/ajafari/scratch0/CMSSW_3_8_5_patch3/src/TopBrussels/TopTreeProducer/interface/TRootTagProbeObject.h"
using namespace TopTree;
class PairMaker{
public:
    PairMaker(double lowmass,double highmass, bool checkCharge):lowmass_(lowmass),highmass_(highmass),checkCharge_(checkCharge){
        Pairs.clear();
        verbosity = 0;
    };
    virtual ~PairMaker(){};
    void MakePairs(const std::vector<TopTree::TRootElectron>& elecs, int match1 = -1, int jet = -1,int match2 = -1){
        if(verbosity > 0)
            cout<<"In Maker:"<<endl;
        for(unsigned int i = 0; i<elecs.size(); i++){
                    TRootTagProbeObject TPO(elecs.at(i));
                    if(verbosity > 0)
                        cout<<i<<"\t"<<TPO.Pt()<<"\t"<<TPO.Eta()<<endl;
                    for(unsigned int j = 0; j<elecs.size(); j++){
                        if(j == i)
                            continue;
//                        double x = elecs.at(j).X() + TPO.X();
//                        double y = elecs.at(j).Y() + TPO.Y();
//                        double z = elecs.at(j).Z() + TPO.Z();
//                        double t = elecs.at(j).T() + TPO.T();
//                        TLorentzVector V(x,y,z,t);
                        TLorentzVector V(elecs.at(j).X() + TPO.X(),elecs.at(j).Y() + TPO.Y(),elecs.at(j).Z() + TPO.Z(),elecs.at(j).T() + TPO.T());
                        if(verbosity > 0){
                            cout<<"\tmass check: "<<lowmass_<<" < "<<V.M()<<" < "<<highmass_<<endl;
                        }
                        if(this->PairInMassRange(V.M())){
                            TPO.PIndex.push_back(j);
                            TPO.Mass.push_back(V.M());
                            if(verbosity > 0){
                                cout<<"\t\tprobe accepted "<<endl;
                            }
                        }
                        if(verbosity > 0){
                            cout<<"InfoSize: "<<TPO.PIndex.size()<<endl;
                            cout<<"\tIndex: "<<TPO.PIndex.at((TPO.PIndex.size()-1))<<endl;
                            cout<<"\tIndex: "<<TPO.Mass.at((TPO.PIndex.size()-1))<<endl;
                        }
                    }
                    TPO.hasMatch = ((match1 == (int)i) || (match2 == (int)i));
                    if(verbosity > 0)
                        cout<<"matchId: "<<TPO.hasMatch<<endl;
                    TPO.nJet = jet;
//                    cout<<"nJet: "<<TPO.nJet<<endl;
                    if(verbosity > 0)
                        cout<<"\tnumber of Probes: "<<TPO.PIndex.size()<<endl;
                    Pairs.push_back(TPO);
        }
    };

    bool ConsistentPairs(bool isTtBar = false){
        if(isTtBar){
            if(Pairs.size() == 1) {
                return(Pairs.at(0).hasMatch);
            }
            else
                return false;
        }
        int nTot = 0;
        for(unsigned int i = 0; i<Pairs.size(); i++){
            nTot+=Pairs.at(i).Mass.size();
        }
        if(verbosity > 0){
            cout<<"In Consitency method:\n\tnumber of all probes: "<<nTot<<endl;
            cout<<"\tnumber of pairs: "<<Pairs.size()<<endl;
            cout<<"\tDo I accept it: "<<(nTot == (int)Pairs.size() && Pairs.size() < 3 && Pairs.size() > 0)<<endl;
        }
        return (nTot == (int)Pairs.size() && Pairs.size() < 3 && Pairs.size() > 0);
    }
    bool PairInMassRange(double m){
        return(m > lowmass_ && m < highmass_);
    }

    void JetPairCleaning(std::vector<TRootCaloJet> jets){
        cleanJets.clear();
	if(verbosity > 0)
		cout<<"Jet size before cleaning: "<<jets.size()<<endl;
        for(uint s = 0; s < jets.size(); s++){
//            TRootCaloJet myJet = jets.at(s);
            bool ifElecClosedBy = false;
	    if(verbosity > 0)
	        cout<<"In JetCleaning, number of GoldenElectrons is: "<<Pairs.size()<<endl;
            for(uint q = 0; q<Pairs.size(); q++){
                DR<TLorentzVector> dr(jets.at(s),Pairs.at(q));
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
                 cleanJets.push_back(jets.at(s));

            }else if(verbosity > 0)
			cout<<"Jet-Electron overlap"<<endl;
        }
	if(verbosity > 0)
		cout<<"Jet size after cleaning: "<<cleanJets.size()<<endl;
        
    }

    void setJetInfo(){
        double minR = 11000.;
//        std::vector<TRootTagProbeObject> tmp;
//        tmp.clear();
        if(verbosity > 0)
            cout<<"In setJetInfo:"<<endl;
        for(uint q = 0; q<Pairs.size(); q++){
            for(uint s = 0; s<cleanJets.size(); s++){
                DR<TLorentzVector> dr(cleanJets.at(s),Pairs.at(q));
                if(dr.getValue() < minR)
                    minR = dr.getValue();
                if(verbosity > 0)
                    cout<<"\t\tminR: "<<minR<<endl;
            }
//            TRootTagProbeObject t(Pairs.at(q));
//            t.minRJet = minR;
//            t.nJet = cleanJets.size();
//            tmp.push_back(t);
            Pairs.at(q).minRJet = minR;
            Pairs.at(q).nJet = cleanJets.size();
        }
        if(verbosity > 0)
            cout<<"\tPairs.size: "<<Pairs.size()<<"\n";
//        Pairs.clear();
//        if(verbosity > 0)
//            cout<<"Pairs.size: "<<Pairs.size()<<"\t";
//        Pairs = tmp;
        if(verbosity > 0){
            for(uint f = 0; f <Pairs.size(); f++){
                cout<<"\t\tnJet: "<<Pairs.at(f).nJet<<endl;
                cout<<"\t\tminR: "<<Pairs.at(f).minRJet<<endl;
            }
        }
    }
    std::vector<TRootTagProbeObject> Pairs;
    int verbosity;
private:
    double lowmass_;
    double highmass_;
    bool checkCharge_;
    std::vector<TRootCaloJet> cleanJets;
    
};



#endif	/* PAIRMAKER2_H */

