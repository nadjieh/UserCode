/* 
 * File:   MCRegion.h
 * Author: ajafari
 *
 * Created on July 7, 2010, 5:04 PM
 */

#ifndef _MCREGION_H
#define	_MCREGION_H
#include "BaseRegion.h"
#include <iostream>
#include "SpecificEffHandler.h"
#include "SpecificHistograms.h"
#include "/user/ajafari/CMSSW_3_8_5_patch3/src/AnalysisClasses/ChiSquared/interface/ExtendedJet.h"
using namespace std;
using namespace TopTree;
bool FunctionBtag_MC(const ExtendedJet * e){return(true);}
class MCRegion : public BaseRegion {
public:

    MCRegion(std::string name, double LE, double HE,bool extOK, bool setTwoD = true) : BaseRegion(name, LE, HE),ExtOk(extOK) {
        JetSpecificEfficiencyHandler*  tmp = new JetSpecificEfficiencyHandler(string(name) + "_B");
        JetSpecificEfficiencyHandler*  tmp2= new JetSpecificEfficiencyHandler(string(name) + "_NB");
        JetSpecificEfficiencyHandler*  tmp3= new JetSpecificEfficiencyHandler(string(name) + "_NBB");
        tmp->Condition = FunctionBtag_MC;
        tmp->ResetConditionForAllProps();
        if(setTwoD)
            tmp->set2Ds();

        tmp2->Condition = FunctionBtag_MC;
        tmp2->ResetConditionForAllProps();
        if(setTwoD)
            tmp2->set2Ds();
        
        tmp3->Condition = FunctionBtag_MC;
        tmp3->ResetConditionForAllProps();
        if(setTwoD)
            tmp3->set2Ds();
        
        BaseRegion::AddHandler(tmp);
        BaseRegion::AddHandler(tmp2);
        BaseRegion::AddHandler(tmp3);
    };

    virtual ~MCRegion() {
    };

    virtual void Fill(TopEvent input, double weight = 1.) {
        if(BaseRegion::verbosity > 0){
            cout<<"Fill Method in "<<BaseRegion::Name<<"\t"<<this->WhoAmI()<<endl;
            cout<<"\tWeight = "<<weight<<endl;
        }
        if(BaseRegion::isInRegion(input.getMlb())){
            ExtendedJet * jet = &(input.getLepBCand());
            jet->setMJetLepton(input.getMlb());
            if(ExtOk){
                std::string matchname = jet->getMatchName();
                JetSpecificEfficiencyHandler * BHandler = BaseRegion::getHandler(0);
                JetSpecificEfficiencyHandler * NBHandler = BaseRegion::getHandler(1);
                if(BaseRegion::verbosity > 0)
                    cout<<"Extended jets will be used and we work only with LepBCands ..."<<endl;
                
                if(BHandler == NULL)
                    cout<<"BHandler is NULL"<<endl;
                if (matchname == "HadB" || matchname == "LepB"){
                    BHandler->Fill(jet, weight);
                    if(BaseRegion::verbosity > 0)
                        cout<<"\t"<<BHandler->getName()<<"\n\tis filled because of being "<<matchname<<endl;
                }
                else{
                    NBHandler->Fill(jet, weight);
                    if(BaseRegion::verbosity > 0)
                        cout<<"\t"<<NBHandler->getName()<<"\n\tis filled because of being "<<matchname<<endl;
                }
            } else{
                if(BaseRegion::verbosity > 0)
                    cout<<"TRootCaloJets will be used and we work only with LepBCands ..."<<endl;
                int jetFlv = (int) fabs(jet->getJet().partonFlavour());
                JetSpecificEfficiencyHandler * BHandler = BaseRegion::getHandler(0);
                JetSpecificEfficiencyHandler * NBHandler = BaseRegion::getHandler(1);
                if (jetFlv == 5){
                    BHandler->Fill(jet, weight);
                    if(BaseRegion::verbosity > 0)
                        cout<<"\t"<<BHandler->getName()<<"\n\tis filled because of having the flavor of "<<jetFlv<<endl;
                }
                else{
                    NBHandler->Fill(jet, weight);
                    if(BaseRegion::verbosity > 0)
                        cout<<"\t"<<BHandler->getName()<<"\n\tis filled because of having the flavor of "<<jetFlv<<endl;
                }
            }

            BaseRegion::FillRest(jet, weight);
        }
    };


    virtual std::string WhoAmI()const {
        return "MCRegion";
    };
    bool isWithExtendedJets()const{return ExtOk;};
private:
    bool ExtOk;
};

#endif	/* _MCREGION_H */

