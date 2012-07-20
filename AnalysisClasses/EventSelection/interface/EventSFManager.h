/* 
 * File:   EventSFManager.h
 * Author: nadjieh
 *
 * Created on June 25, 2012, 3:52 PM
 */

#ifndef EVENTSFMANAGER_H
#define	EVENTSFMANAGER_H
#include "Weighter.h"
#include "BTagWeight.h"
#include "TH1.h"
#include "TH2.h"
#include <vector>
#include <iostream>
#include <string>
#include "../../../TopBrussels/TopTreeProducer/interface/TRootPFJet.h"
using namespace std;
using namespace TopTree;
class EventSFManager{
public:
    EventSFManager(){lepton = 0; hlt = 0; btag = 0; }
    ~EventSFManager(){}
    void init_LeptonSF(TH1D * h = 0, double sf = 1){
        lepton = new LeptonWeighter(h,sf);
    }
    void init_LeptonSF(TH2D * h = 0, double sf = 1){
        lepton = new LeptonWeighter(h,sf);
    }
    
    void init_HLTSF(TH1D * h = 0, double sf = 1){
        hlt = new HLTWeighter(h,sf);
    }
    void init_HLTSF(TH2D * h = 0, double sf = 1){
        hlt = new HLTWeighter(h,sf);
    }
    void init_BTagSF(int syst = 0, int nTaggers = 1){
        btag = new BTagWeight(syst, nTaggers);
    }
    
    double GetWeight(std::vector<TRootPFJet> jets, double hlt1 = -1000., 
                     double lep1 = -1000., bool dobtag = false, double hlt2 = -1000., double lep2 = -1000.){
        double weight = 1;
        weight*=hlt->getWeight(hlt1,hlt2);
        weight*=lepton->getWeight(lep1,lep2);
        if(!dobtag)
            return weight;
        //Only for one tagger! TCHPT
        double sf, eff;
        vector< vector<BTagWeight::JetInfo> > jInfosToReWeight(jets.size());
        for (int iJet = 0; iJet < (int)jets.size(); iJet++) {
            BTagWeight::GetEffSF_TCHPT(jets[iJet].Pt(), 
                                        jets[iJet].Eta(), 
                                        jets[iJet].btag_trackCountingHighPurBJetTags(),
                                        jets[iJet].partonFlavour(),
                                        eff, sf , 0);
            BTagWeight::JetInfo jinfo(eff, sf);
            jInfosToReWeight[iJet].push_back(jinfo);
        }
        return weight*=btag->weight(jInfosToReWeight);
}
private:
    LeptonWeighter * lepton;
    HLTWeighter * hlt;
    BTagWeight * btag;

    
};

#endif	/* EVENTSFMANAGER_H */

