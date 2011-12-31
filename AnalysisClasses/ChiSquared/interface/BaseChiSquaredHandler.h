/* 
 * File:   BaseChiAquaredHandler.h
 * Author: ajafari
 *
 * Created on August 19, 2010, 3:35 PM
 */

#ifndef _BASECHIAQUAREDHANDLER_H
#define	_BASECHIAQUAREDHANDLER_H
#include "/user/ajafari/CMSSW_3_8_5_patch3/src/Base/BaseAnalysis/interface/EfficiencyHandler.h"
#include "/user/ajafari/CMSSW_3_8_5_patch3/src/AnalysisClasses/ChiSquared/interface/MyObjectProperties.h"
#include "TH2.h"
#include "TDirectory.h"
using namespace std;

class BaseChiSquaredHandler : public EfficiencyHandler<TopEvent>{
public:
    typedef EfficiencyHandler<TopEvent> ChiBASE_;
//    bool (*FunctionBtag)(const T*) ;
    BaseChiSquaredHandler(string name):ChiBASE_(name){
        ChiBASE_::AllCondition = 0;
//        ChiBASE_::AddProp(new TChiSquared());
//        ChiBASE_::AddProp(new TChiSquaredM());
//        ChiBASE_::AddProp(new TChiSquaredR());
        ChiBASE_::AddProp(new ExtChi2());
        ChiBASE_::AddProp(new TTopPt());
        ChiBASE_::AddProp(new TMlb());
        ChiBASE_::AddProp(new TMll());
        
    };
    virtual ~BaseChiSquaredHandler(){};
    virtual std::string WhoAmI()const{
        return "BaseChiSquaredHandler";
    }
    virtual void Fill(const TopEvent* theObject, double weight = 1) {
        ChiBASE_::Fill(theObject,weight);
    }

    virtual void WriteAll(TDirectory* dir){
        if(dir == NULL)
            cout<<"Bad Directory in SpecificHandler"<<endl;
        ChiBASE_::WriteAll(dir);

        dir->cd();
    }
    void ResetConditionForAllProps(){
        for(uint i = 0 ; i < EfficiencyHandler<TopEvent>::GetProperties() ; i++){
            EfficiencyHandler<TopEvent>::GetEffH1(i)->Condition = EfficiencyHandler<TopEvent>::Condition;
            EfficiencyHandler<TopEvent>::GetEffH1(i)->AllCondition = EfficiencyHandler<TopEvent>::AllCondition;
        }
    }
};
#endif	/* _BASECHIAQUAREDHANDLER_H */

