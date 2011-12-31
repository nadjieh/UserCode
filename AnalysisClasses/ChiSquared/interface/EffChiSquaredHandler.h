/* 
 * File:   MatchedEffChiSquaredHandler.h
 * Author: ajafari
 *
 * Created on August 19, 2010, 1:34 PM
 */

#ifndef _MatchedEffChiSquaredHandler_H
#define	_MatchedEffChiSquaredHandler_H
#include "BaseChiSquaredHandler.h"
bool CutEffectCond(const TopEvent * e){return(true);}
bool IsMatchedEff(const TopEvent * c) {
  return(c->LeptonicJetIsB());
}



class MatchedEffChiSquaredHandler: public BaseChiSquaredHandler{
public:
    MatchedEffChiSquaredHandler(std::string name):BaseChiSquaredHandler(name){
        BaseChiSquaredHandler::setSelfEff();
        BaseChiSquaredHandler::AllCondition = IsMatchedEff;
        BaseChiSquaredHandler::Condition = CutEffectCond;
        BaseChiSquaredHandler::ResetConditionForAllProps();
        this->ResetSelfEffForAllProps();
    };
    virtual ~MatchedEffChiSquaredHandler(){};
private:
    void ResetSelfEffForAllProps(){
        for(uint i = 0 ; i < EfficiencyHandler<TopEvent>::GetProperties() ; i++){
            EfficiencyHandler<TopEvent>::GetEffH1(i)->setSelfEff();
        }
    }
};


class EffChiSquaredHandler: public BaseChiSquaredHandler{
public:
    EffChiSquaredHandler(std::string name):BaseChiSquaredHandler(name){
        BaseChiSquaredHandler::setSelfEff();
        BaseChiSquaredHandler::AllCondition = CutEffectCond;
        BaseChiSquaredHandler::Condition = CutEffectCond;
        BaseChiSquaredHandler::ResetConditionForAllProps();
        this->ResetSelfEffForAllProps();
    };
    virtual ~EffChiSquaredHandler(){};
private:
    void ResetSelfEffForAllProps(){
        for(uint i = 0 ; i < EfficiencyHandler<TopEvent>::GetProperties() ; i++){
            EfficiencyHandler<TopEvent>::GetEffH1(i)->setSelfEff();
        }
    }
};


#endif	/* _MatchedEffChiSquaredHandler_H */

