/* 
 * File:   SpecificEffHandler.h
 * Author: ajafari
 *
 * Created on July 7, 2010, 9:46 AM
 */

#ifndef _SPECIFICEFFHANDLER_H
#define	_SPECIFICEFFHANDLER_H
#include "../../../Base/BaseAnalysis/interface/EfficiencyHandler.h"
#include "../../../Base/BaseAnalysis/interface/TH2Ext.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootJet.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootCaloJet.h"
#include "../../../AnalysisClasses/ChiSquared/interface/MyObjectProperties.h"
#include "../../../AnalysisClasses/ChiSquared/interface/ExtendedJet.h"

#include "TH2.h"
#include "TDirectory.h"
#include <string>
using namespace std;
using namespace TopTree;
struct PtWeightInfo{
    bool stupid;
    bool includeQCD;
    std::string mode;
    int code;
};
struct EtaOnTopOfPtWeightInfo{
    PtWeightInfo ptInfo;
    bool stupid;
    int code;
};
struct TwoDimWeightInfo{
    bool stupid;
    std::string smooth;
};

template <class T>
class SpecificEffHandler : public EfficiencyHandler<T>{
public:
    typedef EfficiencyHandler<T> BASE_;
//    bool (*FunctionBtag)(const T*) ;
    SpecificEffHandler(string name):BASE_(name){
        BASE_::setSelfEff();
//        BASE_::Condition = FunctionBtag;
        BASE_::AllCondition = 0;
        BASE_::AddProp(new TBtag());
        BASE_::AddProp(new Pt());
        BASE_::AddProp(new Eta());
        BASE_::AddProp(new JetBasedMLJ());
        twoD = false;
        bTag_Pt = 0 ;
        bTag_Eta = 0 ;
        Pt_Eta = 0 ;
    };
    SpecificEffHandler(const SpecificEffHandler<T>& effH, std::string suffix): BASE_((BASE_)effH,suffix){
    };
    virtual ~SpecificEffHandler(){};
    virtual std::string WhoAmI()const{
        return "SpecificEffHandler";
    }
    virtual void Fill(const T* theObject, double weight = 1) {
//        cout<<"Weight in Specific Handler: "<<weight<<endl;
        BASE_::Fill(theObject,weight);
        if(twoD){
            bTag_Pt->Fill(theObject->getJet().Pt(),theObject->getJet().btag_trackCountingHighEffBJetTags(),weight);
            bTag_Eta->Fill(fabs(theObject->getJet().Eta()),theObject->getJet().btag_trackCountingHighEffBJetTags(),weight);
            Pt_Eta->Fill(fabs(theObject->getJet().Eta()),theObject->getJet().Pt(),weight);
        }
    }
    
    virtual void WriteAll(TDirectory* dir){
        if(dir == NULL)
            cout<<"Bad Directory in SpecificHandler"<<endl;
        BASE_::WriteAll(dir);
        dir->mkdir(string(BASE_::getName()+"_2D").c_str())->cd();
        if(twoD == 1){
            if(BASE_::verbosity > 0){
                cout<<"Writing 2Ds in "<<string(BASE_::getName()+"_2D")<<"\n\tbecause twoD here is "<<twoD<<endl;
            }
            if(bTag_Pt != NULL)
                bTag_Pt->Write();
            if(bTag_Eta != NULL)
                bTag_Eta->Write();
            if(Pt_Eta != NULL)
                Pt_Eta->Write();
            if(BASE_::verbosity > 0){
                cout<<"End of WriteAll method"<<endl;
            }
        }

        dir->cd();
    }
    void set2Ds(){
        twoD = true;
        TBtag myBtag;
        Pt myPt;
        Eta myEta;

        bTag_Eta = new TH2D(*myEta.GetH2(&myBtag,string(BASE_::getName()+"_bTagEta"),"bTag vs eta"));
        bTag_Pt = new TH2D(*myPt.GetH2(&myBtag,string(BASE_::getName()+"_bTagPt"),"bTag vs Pt"));
        Pt_Eta = new TH2D(*myEta.GetH2(&myPt,string(BASE_::getName()+"_PtEta"),"Pt vs Eta"));
    }
    void ResetConditionForAllProps(){
        for(uint i = 0 ; i < EfficiencyHandler<T>::GetProperties() ; i++)
            EfficiencyHandler<T>::GetEffH1(i)->Condition = EfficiencyHandler<T>::Condition;
    }
    TH2D * bTag_Pt;
    TH2D * bTag_Eta;
    TH2D * Pt_Eta;
    bool twoD;
};
typedef SpecificEffHandler<ExtendedJet> JetSpecificEfficiencyHandler;











#endif	/* _SPECIFICEFFHANDLER_H */

