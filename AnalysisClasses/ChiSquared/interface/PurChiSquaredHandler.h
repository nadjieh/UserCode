/* 
 * File:   PurChiSquaredHandler.h
 * Author: ajafari
 *
 * Created on August 19, 2010, 1:45 PM
 */

#ifndef _PURCHISQUAREDHANDLER_H
#define	_PURCHISQUAREDHANDLER_H
#include "BaseChiSquaredHandler.h"

bool IsMatchedPur(const TopEvent * c) {
  return(c->LeptonicJetIsB());
}
class PurChiSquaredHandler: public BaseChiSquaredHandler{
public:
    PurChiSquaredHandler(std::string name):BaseChiSquaredHandler(name){
        BaseChiSquaredHandler::AllCondition = 0;
        BaseChiSquaredHandler::Condition = IsMatchedPur;
        BaseChiSquaredHandler::ResetConditionForAllProps();
    };
    virtual ~PurChiSquaredHandler(){};
};


#endif	/* _PURCHISQUAREDHANDLER_H */

