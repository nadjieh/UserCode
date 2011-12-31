/* 
 * File:   TwoDWeightJetEffHandler.h
 * Author: ajafari
 *
 * Created on July 7, 2010, 4:45 PM
 */

#ifndef _TWODWEIGHTJETEFFHANDLER_H
#define	_TWODWEIGHTJETEFFHANDLER_H
#include "SpecificEffHandler.h"
#include "LightStudyJetHandler.h"
#include "/user/ajafari/CMSSW_3_8_5_patch3/src/AnalysisClasses/LightJets/interface/ReweithingFunctions.h"
#include <string>
using namespace std;
using namespace TopTree;

class TwoDWeightEffHandler : public SpecificEffHandler<ExtendedJet>{
public:
    TwoDWeightEffHandler(std::string name, std::string smooth, bool stupid = false):SpecificEffHandler<ExtendedJet>(name){
        TwoDimWeightInfo_.smooth = smooth;
        TwoDimWeightInfo_.stupid = stupid;
    };
    TwoDWeightEffHandler(const TwoDWeightEffHandler& effH, std::string suffix):SpecificEffHandler<ExtendedJet>((SpecificEffHandler<ExtendedJet>)effH,suffix){
    };
    //2D Weight



    //2D weight
   virtual void Fill(const ExtendedJet* theObject, double weight){
        double w = 1.;
        if(TwoDimWeightInfo_.stupid)
            w = stupid2D(weight,theObject->getJet().Pt(),theObject->getJet().Eta());
        else
            w = weightWith2D(TwoDimWeightInfo_.smooth,theObject->getJet().Eta(),theObject->getJet().Pt(), weight);
        SpecificEffHandler<ExtendedJet>::Fill(theObject,w);
    };
    virtual std::string WhoAmI()const{
        return "TwoDWeightEffHandler";
    }
private:
    TwoDimWeightInfo TwoDimWeightInfo_;
};

class TwoDWeightLightEffHandler : public BMatchedHandler{
public:
    TwoDWeightLightEffHandler(std::string name, std::string smooth, bool stupid = false):BMatchedHandler(name){
        TwoDimWeightInfo_.smooth = smooth;
        TwoDimWeightInfo_.stupid = stupid;
    };
    TwoDWeightLightEffHandler(const TwoDWeightLightEffHandler& effH, std::string suffix):BMatchedHandler((BMatchedHandler)effH,suffix){
    };
    //2D Weight



    //2D weight
   virtual void Fill(const ExtendedJet* theObject, double weight){
        double w = 1.;
        if(TwoDimWeightInfo_.stupid)
            w = stupid2D(weight,theObject->getJet().Pt(),theObject->getJet().Eta());
        else
            w = weightWith2D(TwoDimWeightInfo_.smooth,theObject->getJet().Eta(),theObject->getJet().Pt(), weight);
        BMatchedHandler::Fill(theObject,w);
    };
    virtual std::string WhoAmI()const{
        return "TwoDWeightLightEffHandler";
    }
private:
    TwoDimWeightInfo TwoDimWeightInfo_;
};

#endif	/* _TWODWEIGHTJETEFFHANDLER_H */

