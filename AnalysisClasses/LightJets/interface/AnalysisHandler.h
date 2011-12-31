/* 
 * File:   AnalysisHandler.h
 * Author: ajafari
 *
 * Created on August 5, 2010, 1:38 PM
 */

#ifndef _ANALYSISHANDLER_H
#define	_ANALYSISHANDLER_H

#include "BaseAnalysis.h"
#include "../../../EventSelection/interface/JetMatching.h"
#include "../../../ChiSquared/interface/BaseAnalysisHandler.h"
#include "../../../ChiSquared/interface/TopEvent.h"
#include <stdio.h>
#include <stdlib.h>
class AnalysisHandler : public BaseAnalysisHandler<BaseAnalysis>{
public:
    typedef BaseAnalysisHandler<BaseAnalysis> BASE_;
    AnalysisHandler(std::string anaName, bool dobtag,bool datalike, bool extJetOk_,double Lumi_, MassAndResolution massAndres,
            ElectronCuts elecCuts,JetCuts jetCuts_,std::string which = "minChi2",bool Ott = false,bool rre = false, bool matchElec = false):
            BASE_(anaName,dobtag,datalike,extJetOk_,Lumi_,massAndres,elecCuts,jetCuts_,which,Ott,rre,matchElec){ActivateSystem = false;};
    virtual ~AnalysisHandler(){};
    virtual void Fill(TopEvent jetElec, double weight = 1.,int nAna = -1){
//        cout<<"nAna "<<nAna<<endl;
        if(nAna == -1){
            for(uint i = 0; i<Analyses.size(); i++){
                Analyses.at(i)->bTag_Mlb->Fill(jetElec.getMlb(),jetElec.getLepBCand().getJet().btag_trackCountingHighEffBJetTags(),weight);
    //            if(jetElec.getMlb() < Analyses.at(i)->Edges.at(0) || jetElec.getMlb() > Analyses.at(i)->Edges.at(3)){
    //                continue;
    //            }
                Analyses.at(i)->Fill(jetElec,weight);
            }
        }else{
            if(nAna > Analyses.size()){
                cout<<"analysis does not exist"<<endl;
                return;
            }
//            cout<<"Filling "<<Analyses.at(nAna)->getName()<<endl;
            Analyses.at(nAna)->bTag_Mlb->Fill(jetElec.getMlb(),jetElec.getLepBCand().getJet().btag_trackCountingHighEffBJetTags(),weight);
                    Analyses.at(nAna)->Fill(jetElec,weight);
        }
    }
    void setAnalysisNonTrivialF(int nAnalysis, double f_){
        std::vector<double> tmpF;
        tmpF.clear();
        for(unsigned int i = 0; i<f.size(); i++){
            if((int)i != (nAnalysis - 1))
                tmpF.push_back(f.at(i));
            else
                tmpF.push_back(f_);
        }
        f.clear();
        f = tmpF;
    }
    virtual void End(){
        cout<<Analyses.size()<<endl;
        for(uint i = 0; i<Analyses.size(); i++){
            Analyses.at(i)->End(string(BASE_::Name +"_"+ Analyses.at(i)->Name+"_"+BASE_::whichMethodToSelectHadTop+".root"),f[i]);
            if(ActivateSystem){
                stringstream command; command<<"mv "<<BASE_::Name <<"_"+ Analyses.at(i)->Name<<"_"<<BASE_::whichMethodToSelectHadTop<<
                        ".root /home/ajafari/Pseudo_100/"<<i+1<<"/";
                system(command.str().c_str());
            }
                
            if(verbosity > 0)
                cout<<"f in "<<Analyses.at(i)->Name<<" is\n\t"<<f[i]<<endl;
        }
    }
    void setVerbosity(int i){
        BASE_::setVerbosity(i);
//        cout<<"In Handler "<<Name<<" verbosity is set to "<<verbosity<<endl;
        for(uint j = 0; j<Analyses.size(); j++){
            Analyses.at(j)->setVerbosity(verbosity);
        }
    }

    bool ActivateSystem;

};
#endif	/* _ANALYSISHANDLER_H */

