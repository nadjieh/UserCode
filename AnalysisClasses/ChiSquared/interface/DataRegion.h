/* 
 * File:   DataRegion.h
 * Author: ajafari
 *
 * Created on July 8, 2010, 12:54 PM
 */

#ifndef _DATAREGION_H
#define	_DATAREGION_H
#include "BaseRegion.h"
#include "SpecificEffHandler.h"
#include "SpecificHistograms.h"
#include "TLorentzVector.h"
#include <string>
#include <iostream>
#include "/user/ajafari/CMSSW_3_8_5_patch3/src/TopBrussels/TopTreeProducer/interface/TRootCaloJet.h"
#include "/user/ajafari/CMSSW_3_8_5_patch3/src/TopBrussels/TopTreeProducer/interface/TRootJet.h"
#include "/user/ajafari/CMSSW_3_8_5_patch3/src/AnalysisClasses/ChiSquared/interface/ExtendedJet.h"
#include "TopEvent.h"
bool FunctionBtag_Data(const ExtendedJet * e){return(true);}

using namespace std;

class DataRegion : public BaseRegion {
public:

    DataRegion(std::string name, double LE, double HE,bool antiBtag = false,double AntiTagCut = 1000.) :
    BaseRegion(name, LE, HE),applyAntiBtagOnLightCands(antiBtag),antiTagCut(AntiTagCut) {
        JetSpecificEfficiencyHandler*  tmp = new JetSpecificEfficiencyHandler(string(name) + "_HadB");
        JetSpecificEfficiencyHandler*  tmp2= new JetSpecificEfficiencyHandler(string(name) + "_LightJet");
        JetSpecificEfficiencyHandler*  tmp3= new JetSpecificEfficiencyHandler(string(name) + "_LepB");
        tmp->Condition = FunctionBtag_Data;
        tmp->ResetConditionForAllProps();
        tmp->set2Ds();

        tmp2->Condition = FunctionBtag_Data;
        tmp2->ResetConditionForAllProps();
        tmp2->set2Ds();

        tmp3->Condition = FunctionBtag_Data;
        tmp3->ResetConditionForAllProps();
        tmp3->set2Ds();
        BaseRegion::AddHandler(tmp);
        BaseRegion::AddHandler(tmp2);
        BaseRegion::AddHandler(tmp3);

    };

    virtual ~DataRegion() {
    };

    virtual void Fill(TopEvent JE, double weight) {

        JetSpecificEfficiencyHandler * LightHandler = BaseRegion::getHandler(1);
        if(BaseRegion::verbosity > 1){
            cout<<"Fill Method in "<<BaseRegion::Name<<"\t"<<this->WhoAmI()<<endl;
            cout<<"\tWeight = "<<weight<<endl;
            cout<<"Started by "<<LightHandler->getName()<<endl;
        }
        ExtendedJet * jet = NULL;
        double mJetLepton = JE.getMll1();
        if (BaseRegion::isInRegion(mJetLepton)){
            jet = new ExtendedJet(JE.getQ1());
            jet->setMJetLepton(mJetLepton);
            if(!applyAntiBtagOnLightCands){
                if(BaseRegion::verbosity > 1){
                    cout<<"\tfilled with ALL LightCands (1)\n\t\tMll1 = "<<jet->getMJetLepton()<<endl;
                }
                LightHandler->Fill(jet, weight);
            }
            else if(jet->getJet().btag_trackCountingHighEffBJetTags() < antiTagCut){
                if(BaseRegion::verbosity > 1)
                    cout<<"\tfilled with AntiTagged LightCands (1)\n\t\tMll1 = "<<jet->getMJetLepton()<<endl;
                LightHandler->Fill(jet, weight);
            }
        }
//        if(BaseRegion::verbosity > 1)
//            cout<<"\tfilled with the first LightCand"<<endl;
        mJetLepton = JE.getMll2();
        if (BaseRegion::isInRegion(mJetLepton)){
            jet = new ExtendedJet(JE.getQ2());
            jet->setMJetLepton(mJetLepton);
            if(!applyAntiBtagOnLightCands){
                if(BaseRegion::verbosity > 1)
                    cout<<"\tfilled with ALL LightCands (2)\n\t\tMll2 = "<<jet->getMJetLepton()<<endl;
                LightHandler->Fill(jet, weight);
            }
            else if(jet->getJet().btag_trackCountingHighEffBJetTags() < antiTagCut){
                if(BaseRegion::verbosity > 1)
                    cout<<"\tfilled with AntiTagged LightCands (2)\n\t\tMll2 = "<<jet->getMJetLepton()<<endl;
                LightHandler->Fill(jet, weight);
            }
        }
//        if(BaseRegion::verbosity > 1)
//            cout<<"\tfilled with the second LightCand"<<endl;


        JetSpecificEfficiencyHandler * HadBHandler = BaseRegion::getHandler(0);       
        if(BaseRegion::verbosity > 1)
            cout<<"Continued by "<<HadBHandler->getName()<<endl;
        mJetLepton = JE.getMlHadB();
        if (BaseRegion::isInRegion(mJetLepton)){
            jet = new ExtendedJet(JE.getHadBCand());
            jet->setMJetLepton(mJetLepton);
            HadBHandler->Fill(jet, weight);
            if(BaseRegion::verbosity > 1)
                cout<<"\tfilled with the hadBCand\n\t\tMlHadB = "<<jet->getMJetLepton()<<endl;
        }

        mJetLepton = JE.getMlb();
        if(BaseRegion::isInRegion(mJetLepton)){
            jet = new ExtendedJet(JE.getLepBCand());
            jet->setMJetLepton(mJetLepton);
            if(BaseRegion::verbosity > 1)
                cout<<"\tthe rest is filled by LepBCand\n\t\tMlb = "<<jet->getMJetLepton()<<endl;
            BaseRegion::FillRest(jet, weight);
        }

    };


    virtual std::string WhoAmI()const {
        return "DataRegion";
    };
    bool applyAntiBtagOnLightCands;
    double antiTagCut;
};

#endif	/* _DATAREGION_H */

