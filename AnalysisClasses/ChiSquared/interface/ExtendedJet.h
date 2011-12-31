/* 
 * File:   ExtendedJet.h
 * Author: ajafari
 *
 * Created on December 28, 2009, 6:42 PM
 */

#ifndef _EXTENDEDJET_H
#define	_EXTENDEDJET_H
#include <iostream>
#include "../../../TopBrussels/TopTreeProducer/interface/TRootCaloJet.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootJet.h"
using namespace std;
using namespace TopTree;
typedef std::pair<int,double> jetIndexValueThis;
typedef std::pair<jetIndexValueThis,jetIndexValueThis> BothAlgValuesThis; //R_Pt
typedef std::vector<std::pair<TLorentzVector,BothAlgValuesThis> > Qinfo; //R_Pt
class ExtendedJet{
public:
    struct doSth{
        bool operator() (std::pair<double,std::string> comb1, std::pair<double,std::string> comb2) { return (comb1.first < comb2.first);}
    } mydoSth;
    ExtendedJet(std::pair<TRootCaloJet,int> jetQpair, int myindex = -1){
//        std::cout<<"in ExtJet Constructor"<<std::endl;
        myJet = jetQpair.first;
        if(jetQpair.second == -1)
            matchName = "none";
        else if(jetQpair.second == 0)
            matchName = "HadB";
        else if(jetQpair.second == 1)
            matchName = "LepB";
        else if(jetQpair.second == 2)
            matchName = "Q";
        else if(jetQpair.second == 3)
            matchName = "QBar";
        index = myindex;
        myDesiredVal = -10000;

    }
    ExtendedJet(){
        myJet.SetPxPyPzE(-1.,-1.,-1.,-1.);
        matchName = "none";
        index = -1;
        myDesiredVal = -10000;
    };
    ~ExtendedJet(){};
    bool hasGenMatchedR()const{
        return(matchName != "none");
    };
    std::string getMatchName()const{
        return(matchName);
    };
    

//    }
    TLorentzVector getP4()const{
        TLorentzVector tmp(myJet.Px(),myJet.Py(),myJet.Pz(),myJet.E());
        return tmp;
    };

    int getIndex()const{return index;}
    bool isLeading()const{
        return (index < 4);
    };
    TRootCaloJet getJet()const{
        return myJet;
    };
    void setMJetLepton(double m){
        myDesiredVal = m;
    };
    double getMJetLepton()const{
        return myDesiredVal;
    };
private:
    TRootCaloJet myJet;
    std::string matchName;
    std::vector<std::pair<double,std::string> > delRs;
    std::vector<std::pair<double,std::string> > delPts;
    int index;
    double myDesiredVal;
 
};
#endif	/* _EXTENDEDJET_H */

