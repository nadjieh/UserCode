/* 
 * File:   PtWeightJetEffHandler.h
 * Author: ajafari
 *
 * Created on July 7, 2010, 4:20 PM
 */

#ifndef _PTWEIGHTJETEFFHANDLER_H
#define	_PTWEIGHTJETEFFHANDLER_H
#include "SpecificEffHandler.h"
#include "/user/ajafari/CMSSW_3_8_5_patch3/src/AnalysisClasses/LightJets/interface/ReweithingFunctions.h"
#include <string>
#include <iostream>
using namespace std;
using namespace TopTree;

class PtWeightEffHandler : public SpecificEffHandler<ExtendedJet>{
public:
    PtWeightEffHandler(std::string name, int code, bool stupid = false,bool includeQCD = false,std::string mode = "All_LoverR_Normal"):SpecificEffHandler<ExtendedJet>(name){
        PtWeightInfo_.code = code;
        PtWeightInfo_.stupid = stupid;
        PtWeightInfo_.includeQCD = includeQCD;
        PtWeightInfo_.mode = mode;
    };
    PtWeightEffHandler(const PtWeightEffHandler& effH, std::string suffix):SpecificEffHandler<ExtendedJet>((SpecificEffHandler<ExtendedJet>)effH,suffix){
    };
    //Pt Weight
    virtual void Fill(const ExtendedJet* theObject, double weight){
        double w = weight;
        if(PtWeightInfo_.stupid)
            w = stupidWeighter(theObject->getJet().Pt(),weight);
        else
            w= weightAfterPtReweighting(theObject->getJet().Pt(),weight,PtWeightInfo_.mode,
                    PtWeightInfo_.includeQCD,PtWeightInfo_.code);
        if(SpecificEffHandler<ExtendedJet>::verbosity > 0){
            std::cout<<"\t\tPt: "<<theObject->getJet().Pt()<<std::endl;
            cout<<"Function's Code: "<<PtWeightInfo_.code<<endl;
            std::cout<<"\t\tWeight w.r.t Pt: "<<w<<std::endl;
        }
        SpecificEffHandler<ExtendedJet>::Fill(theObject,w);
    };
    virtual std::string WhoAmI()const{
        return "PtWeightEffHandler";
    };
private:
    PtWeightInfo PtWeightInfo_;
};

#endif	/* _PTWEIGHTJETEFFHANDLER_H */

