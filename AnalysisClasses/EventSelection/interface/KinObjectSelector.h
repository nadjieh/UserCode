#ifndef _KINOBJECTSELECTOR_H
#define _KINOBJECTSELECTOR_H
#include <iomanip>
#include "/user/ajafari/CMSSW_3_8_5_patch3/src/TopBrussels/TopTreeProducer/interface/TRootMuon.h"
#include "/user/ajafari/CMSSW_3_8_5_patch3/src/TopBrussels/TopTreeProducer/interface/TRootElectron.h"
#include "/user/ajafari/CMSSW_3_8_5_patch3/src/TopBrussels/TopTreeProducer/interface/TRootJet.h"
#include "/user/ajafari/CMSSW_3_8_5_patch3/src/TopBrussels/TopTreeProducer/interface/TRootMET.h"
#include "/user/ajafari/CMSSW_3_8_5_patch3/src/TopBrussels/TopTreeProducer/interface/TRootGenEvent.h"
#include "/user/ajafari/CMSSW_3_8_5_patch3/src/TopBrussels/TopTreeProducer/interface/TRootSignalEvent.h"
#include "/user/ajafari/CMSSW_3_8_5_patch3/src/TopBrussels/TopTreeProducer/interface/TRootEvent.h"
#include "/user/ajafari/CMSSW_3_8_5_patch3/src/TopBrussels/TopTreeProducer/interface/TRootRun.h"
#include "/user/ajafari/CMSSW_3_8_5_patch3/src/TopBrussels/TopTreeProducer/interface/TRootParticle.h"
#include "/user/ajafari/CMSSW_3_8_5_patch3/src/TopBrussels/TopTreeProducer/interface/TRootMCParticle.h"
#include <sstream>

#include <TFile.h>
#include <TH1.h>
#include <TH2.h>
#include <TCanvas.h>
#include <TBranch.h>
#include <TTree.h>
#include <TClonesArray.h>
#include <vector>

template<class theObject>
class KinObjectSelector{
public:
    KinObjectSelector(double ptCut, double etaCut = 12., bool EtaExclusion = false, double LEdgeEcclusion = 0.,double HEdgeEcclusion = 0.){
        ptcut = ptCut;
        etacut = etaCut; // FOR MET, NO CUT ON ETA IS GIVEN IN THE CONSTRUCTOR BY THE USER AND NO CUT IS APPLIED ON MET->ETA()
        etaexclusion = EtaExclusion; // EXCLUSION IS ONLY NEEDED FOR THE ELECTRON
        lowEdgeEcclusion = LEdgeEcclusion;
        highEdgeEcclusion = HEdgeEcclusion;
    };
    ~KinObjectSelector(){};
    bool KinematicsOK(theObject * myObj){
        double eta = fabs(myObj->Eta());
        double pt = myObj->Pt();
        bool etaOk = eta < etacut;
        if(etaexclusion)
            etaOk = (etaOk && !( eta > lowEdgeEcclusion && eta < highEdgeEcclusion ));
        return(etaOk && (pt > ptcut));
    };
    std::vector<theObject> SelectFromCollection(TClonesArray * theObjects){
        std::vector<theObject> res;
        res.clear();
        theObject  myObj;
        for(int i=0;i<theObjects->GetEntriesFast();i++){
            myObj = *((theObject*) theObjects->At(i));
            if(KinematicsOK(&myObj))
                res.push_back(myObj);
	}
	return(res);
    };
private:
    double ptcut;
    double etacut;
    bool etaexclusion;
    double lowEdgeEcclusion;
    double highEdgeEcclusion;
};
#endif /*_KINOBJECTSELECTOR_H*/
