/*                                                                                                                                                                                                                                                                                         
* File:   Matcher.h                                                                                                                           \
                                                                                                                               
* Author: ajafari                                                                                                                             \
                                                                                                                                               
*                                                                                                                                             \
                                                                                                                                               
* Created on December 23, 2009, 1:57 PM                                                                                                       \
                                                                                                                                               
*/

#ifndef _COMBINATOR_H
#define _COMBINATOR_H

#include "TopEvent.h"


#include <iostream>

using namespace std;
using namespace TopTree;
typedef std::vector<ExtendedJet> jetIndex;
class Combinator{
public:
        struct ChiSquaredSort{
          bool operator() (TopEvent comb1, TopEvent comb2) { return (comb1.getTopChiSquared() < comb2.getTopChiSquared());}
        } myChiSquaredSort;
	Combinator(std::vector<ExtendedJet> jets, TRootElectron elec, MassAndResolution constraints,
        std::string Alg = "FirstFourLeadingJets",bool dobTag = false, int btagInd = -1,bool dataBtag = false,
        int verbose = 0,double M3 = 0):
        bTaggingDone(dobTag),
        bTagIndex(btagInd),
        dataLikeBtagging(dataBtag),
        verbosity(verbose),
        MhighestPt(M3){
            myTop.Jets = jets;
            myTop.Electron = elec;
            myTop.constraints.topMass = constraints.topMass;
            myTop.constraints.wMass = constraints.wMass;
            myTop.constraints.topRes = constraints.topRes;
            myTop.constraints.wRes = constraints.wRes;
            algorithm = Alg;
            TopPtSum = 0.;
	};
	Combinator(std::vector<ExtendedJet> jets, TRootElectron elec, double wmass, double wRes, double topMass,
        double topRes, std::string Alg = "FirstFourLeadingJets",bool dobTag = false, int btagInd = -1,
        bool dataBtag = false,int verbose = 0, double M3= 0):
        bTaggingDone(dobTag),
        bTagIndex(btagInd),
        dataLikeBtagging(dataBtag),
        verbosity(verbose),
        MhighestPt(M3){
            myTop.Jets = jets;
            myTop.Electron = elec;
            myTop.constraints.topMass = topMass;
            myTop.constraints.wMass = wmass;
            myTop.constraints.topRes = topRes;
            myTop.constraints.wRes = wRes;
            algorithm = Alg;
            TopPtSum = 0.;
	};
	~Combinator(){};
        void setVerbosity(int i){verbosity = i;}
	std::vector<TopEvent> getAllCombinations(){
		std::vector<TopEvent> combinations;
		combinations.clear();
                if(verbosity > 0){
                    cout<<"To make all possible combinations the algorithm\n\t"<<algorithm<<endl;
                    cout<<"\tDo I want to do with bTagging: "<<bTaggingDone<<endl;
                    cout<<"\tThe index of the HadB jet: "<<bTagIndex<<endl;
                }
                if(algorithm == "FirstFourLeadingJets"){
                    TopPtSum = 0.;
                    for(uint i = 0; i < myTop.Jets.size(); i++){
                        if(verbosity > 2){
                            cout<<i<<"'th combination: "<<endl;
                        }
                        if(bTaggingDone && (int)i == bTagIndex)
                            continue;
                        if(verbosity > 2){
                            cout<<"\tEither No-batgging or i != bTagIndex ..."<<endl;
                        }
                        jetIndex threeJets = ExcludeOneJet(i,myTop.Jets);
                        if(verbosity > 2){
                            cout<<"\tIndecies to combine: "<<threeJets.at(0).getIndex()<<" "<<threeJets.at(1).getIndex()<<" "<<threeJets.at(2).getIndex()<<endl;
                            cout<<"\tLepB index: "<<i<<endl;
                            cout<<"\tLepB MatchName: "<<myTop.Jets.at(i).getMatchName()<<endl;
                            cout<<"\tGo to Combine ... "<<endl;
                        }
                        makeCombinationsOfThreeJets(threeJets,combinations,i);
                    };
                }
                sort(combinations.begin(),combinations.end(),myChiSquaredSort);
                
                if(verbosity > 2 && myTop.HadBIndex != -1)
                    cout<<"Matched Top Properties:\n\tChi2: "<<myTop.getTopChiSquared()<<endl;
		return combinations;
	};
        void setBtaggingDone(int index){bTaggingDone = true; bTagIndex = index;};
        TopEvent getTopEvent()const{return myTop;};
        double getTopPtSum()const{return TopPtSum;};
private:
        TopEvent myTop;
        std::string algorithm;
        bool bTaggingDone;
        int bTagIndex;
        bool dataLikeBtagging;// in this case, bJet will not sit in W. To avoid b-contamination/bias in Mll
        int verbosity;
        double MhighestPt;
        double TopPtSum;
	jetIndex ExcludeOneJet(uint exclude, jetIndex input){
		jetIndex res;
		res.clear();
                for(uint i = 0; i<input.size(); i++){
                        if ( i == exclude)
                                continue;
                        res.push_back(input.at(i));
                }
		return(res);
	};
        TLorentzVector Jet3(jetIndex jetIndecies){
            TLorentzVector tmp(0,0,0,0);
            for(uint i = 0; i < 3; i++){
                tmp = tmp + (TLorentzVector)jetIndecies.at(i).getJet();
            }
            return tmp;
        }
        
	void makeCombinationsOfThreeJets(jetIndex jetIndecies,std::vector<TopEvent> & combinations , int lepBindex){
            double mean = 0;
            double standardDeviation = 0;
            double M3 = this->Jet3(jetIndecies).M();
            TopPtSum += this->Jet3(jetIndecies).Pt();
            for(uint i = 0; i<3; i++){
                        if(verbosity > 3){
                            cout<<"\t\tThe dataLikeBtagging variable is "<< dataLikeBtagging;
                            if(dataLikeBtagging)
                                cout<<", so I won't put the btagged jet in W!!"<<endl;
                            else
                                cout<<", so I don't care about the btagged jet"<<endl;
                        }
                        if(!(bTaggingDone && dataLikeBtagging && (jetIndecies.at(i).getIndex() != bTagIndex))){
                            int j = (i+1) % 3;
                            int k = (i+2) % 3;
                            TopEvent tmpTop(myTop);
                            tmpTop.LepBIndex = lepBindex;
                            tmpTop.M3 = M3;
                            if(verbosity > 3){
                                cout<<"\t\tW:. "<<j<<" "<<k<<"\t"<<tmpTop.constraints.wMass<<" "<<tmpTop.constraints.wRes<<endl;
                            }

                            tmpTop.WIndecies.first = jetIndecies.at(j).getIndex();
                            tmpTop.WIndecies.second = jetIndecies.at(k).getIndex();
                            if(verbosity > 3){
                                cout<<"\t\tJet1:\n\t\tInfoOut of W: "<<jetIndecies.at(j).getMatchName()<<" "<<jetIndecies.at(j).getIndex()<<" "<<jetIndecies.at(j).hasGenMatchedR()<<endl;
                                cout<<"\t\tInfo inaside W: "<<tmpTop.getQ1().getMatchName()<<" "<<tmpTop.WIndecies.first<<" "<<tmpTop.isQ1Matched()<<endl;
                                cout<<"\t\tJet2:\n\t\tInfoOut of W: "<<jetIndecies.at(k).getMatchName()<<" "<<jetIndecies.at(k).getIndex()<<" "<<jetIndecies.at(k).hasGenMatchedR()<<endl;
                                cout<<"\t\tInfo inaside W: "<<tmpTop.getQ2().getMatchName()<<" "<<tmpTop.WIndecies.second<<" "<<tmpTop.isQ2Matched()<<endl;
                                cout<<"\t\tTop:. "<<j<<" "<<k<<" "<<i<<"\t"<<tmpTop.constraints.topMass<<" "<<tmpTop.constraints.topRes<<endl;
                            }
                            tmpTop.HadBIndex = jetIndecies.at(i).getIndex();
                            if(verbosity > 3){
                                cout<<"\t\tJet3:\n\t\tInfoOut of Top: "<<jetIndecies.at(i).getMatchName()<<" "<<jetIndecies.at(i).getIndex()<<" "<<jetIndecies.at(i).hasGenMatchedR()<<endl;
                                cout<<"\t\tInfo inaside Top: "<<tmpTop.getHadBCand().getMatchName()<<" "<<tmpTop.HadBIndex<<" "<<tmpTop.isHadBCandMatched()<<endl;
                                cout<<"\t\tIn Combination: "<<endl;
                                cout<<"\t\t\tChi2 is "<<tmpTop.getTopChiSquared()<<endl;
                                cout<<"\t\t\tCombination is HadronicTop Matched: "<<tmpTop.isHadronicTopMatched()<<endl;
    //                            cout<<"\t\t\tCombination is LepCand Matched: "<<comb.isLepCandMatched()<<endl;
                                cout<<"\t\t\tCombination is ExtLepCand Matched: "<<tmpTop.LeptonicJetIsB()<<endl;
                                cout<<"\t\t\tCombination Pt is: "<<tmpTop.getHadronicTop().Pt()<<endl;
                            }
                            if(tmpTop.isHadronicTopMatched())
                                myTop = tmpTop;
                            combinations.push_back(tmpTop);
                            mean += tmpTop.getTopChiSquared();
                    }
                mean = (double)mean/3.;
                for(uint i = combinations.size(); i > combinations.size()-3; i--){
                    standardDeviation += ((combinations.at(i-1).getTopChiSquared() - mean)*(combinations.at(i-1).getTopChiSquared() - mean));
                }
                if(verbosity > 3){
                    cout<<"Mean is: "<<mean<<", and SD is: "<<sqrt(standardDeviation)<<endl;
                    cout<<"TopSumPt: "<<TopPtSum<<endl;
                }
            }
                
	};
};
#endif/* _COMBINATOR_H */
