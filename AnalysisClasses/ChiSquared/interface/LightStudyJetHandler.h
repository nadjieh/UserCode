/* 
 * File:   LightStudyJetHandler.h
 * Author: ajafari
 *
 * Created on August 30, 2010, 4:03 PM
 */

#ifndef _LIGHTSTUDYJETHANDLER_H
#define	_LIGHTSTUDYJETHANDLER_H
#include "SpecificEffHandler.h"
bool AlwaysTrue(const ExtendedJet * j){return true;}
bool isQuark(const ExtendedJet * j){
    std::string name = j->getMatchName();
    return (name == "Q" || name == "QBar");
}
bool isRadiation(const ExtendedJet * j){
    std::string name = j->getMatchName();
    return (!(name == "Q" || name == "QBar" || name == "HadB" || name == "LepB"));
}
bool isBJet(const ExtendedJet * j){
    std::string name = j->getMatchName();
    return (name == "HadB" || name == "LepB");
}
class QuarkMatchedHandler : public SpecificEffHandler<ExtendedJet>{
public:
    QuarkMatchedHandler(std::string name):SpecificEffHandler<ExtendedJet>(name){
        SpecificEffHandler<ExtendedJet>::AllCondition = AlwaysTrue;
        SpecificEffHandler<ExtendedJet>::Condition = isQuark;
        SpecificEffHandler<ExtendedJet>::ResetConditionForAllProps();
    };
    virtual ~QuarkMatchedHandler(){};
};
class RadiationHandler : public SpecificEffHandler<ExtendedJet>{
public:
    RadiationHandler(std::string name):SpecificEffHandler<ExtendedJet>(name){
        SpecificEffHandler<ExtendedJet>::AllCondition = AlwaysTrue;
        SpecificEffHandler<ExtendedJet>::Condition = isRadiation;
        SpecificEffHandler<ExtendedJet>::ResetConditionForAllProps();
    };
    virtual ~RadiationHandler(){};
};
class BMatchedHandler : public SpecificEffHandler<ExtendedJet>{
public:
    BMatchedHandler(std::string name):SpecificEffHandler<ExtendedJet>(name){
        SpecificEffHandler<ExtendedJet>::AllCondition = AlwaysTrue;
        SpecificEffHandler<ExtendedJet>::Condition = isBJet;
        SpecificEffHandler<ExtendedJet>::ResetConditionForAllProps();
    };
    BMatchedHandler(const BMatchedHandler& h, std::string suffix):
    SpecificEffHandler<ExtendedJet>((SpecificEffHandler<ExtendedJet>)h,suffix){
    };
    virtual ~BMatchedHandler(){};
};

#endif	/* _LIGHTSTUDYJETHANDLER_H */

