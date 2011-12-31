/* 
 * File:   EtaOnPtWeightJetEffHandler.h
 * Author: ajafari
 *
 * Created on July 7, 2010, 4:33 PM
 */

#ifndef _ETAONPTWEIGHTJETEFFHANDLER_H
#define	_ETAONPTWEIGHTJETEFFHANDLER_H

#include "SpecificEffHandler.h"
#include "/user/ajafari/CMSSW_3_8_5_patch3/src/AnalysisClasses/LightJets/interface/ReweithingFunctions.h"
#include <string>
using namespace std;
using namespace TopTree;

class EtaOnPtWeightEffHandler : public SpecificEffHandler<ExtendedJet>{
public:
    EtaOnPtWeightEffHandler(std::string name,int etaCode, int ptCode, bool EtaStupid = false,
            bool PtStupid = false, bool includeQCD = false,std::string mode = "All_LoverR_Normal")
            :SpecificEffHandler<ExtendedJet>(name){
        EtaOnTopOfPtWeightInfo_.code = etaCode;
        EtaOnTopOfPtWeightInfo_.ptInfo.code = ptCode;
        EtaOnTopOfPtWeightInfo_.stupid = EtaStupid;
        EtaOnTopOfPtWeightInfo_.ptInfo.stupid = PtStupid;
        EtaOnTopOfPtWeightInfo_.ptInfo.includeQCD = includeQCD;
        EtaOnTopOfPtWeightInfo_.ptInfo.mode = mode;
    };
    EtaOnPtWeightEffHandler(const EtaOnPtWeightEffHandler& effH, std::string suffix):SpecificEffHandler<ExtendedJet>((SpecificEffHandler<ExtendedJet>)effH,suffix){
    };
    virtual ~EtaOnPtWeightEffHandler(){};
    
    //EtaOnTopOfPt
   virtual void Fill(const ExtendedJet* theObject, double weight){
        double w = weight;
        if(EtaOnTopOfPtWeightInfo_.stupid){
            if(EtaOnTopOfPtWeightInfo_.ptInfo.stupid)
                w = stupidEtaWeighter(theObject->getJet().Eta(),stupidWeighter(theObject->getJet().Pt(),weight));
            else
                w = stupidEtaWeighter(theObject->getJet().Eta(),weightAfterPtReweighting(theObject->getJet().Pt(),weight,
                        EtaOnTopOfPtWeightInfo_.ptInfo.mode,EtaOnTopOfPtWeightInfo_.ptInfo.includeQCD,
                        EtaOnTopOfPtWeightInfo_.ptInfo.code));
        }
        else{

            if(EtaOnTopOfPtWeightInfo_.ptInfo.stupid)
                w = weightAfterEtaReweighting(theObject->getJet().Eta(),stupidWeighter(theObject->getJet().Pt(),weight),
                        EtaOnTopOfPtWeightInfo_.ptInfo.mode,EtaOnTopOfPtWeightInfo_.ptInfo.includeQCD,EtaOnTopOfPtWeightInfo_.code);
            else
                w = weightAfterEtaReweighting(theObject->getJet().Eta(),weightAfterPtReweighting(theObject->getJet().Pt(),
                        weight,EtaOnTopOfPtWeightInfo_.ptInfo.mode,EtaOnTopOfPtWeightInfo_.ptInfo.includeQCD,
                        EtaOnTopOfPtWeightInfo_.ptInfo.code),EtaOnTopOfPtWeightInfo_.ptInfo.mode,
                        EtaOnTopOfPtWeightInfo_.ptInfo.includeQCD,EtaOnTopOfPtWeightInfo_.code);

        }
        SpecificEffHandler<ExtendedJet>::Fill(theObject,w);
    };
    virtual std::string WhoAmI()const{
        return "EtaOnPtWeightEffHandler";
    };
private:
    EtaOnTopOfPtWeightInfo EtaOnTopOfPtWeightInfo_;
};

#endif	/* _ETAONPTWEIGHTJETEFFHANDLER_H */

