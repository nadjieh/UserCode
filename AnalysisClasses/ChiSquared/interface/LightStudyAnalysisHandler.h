/* 
 * File:   LightStudyAnalysisHandler.h
 * Author: ajafari
 *
 * Created on August 30, 2010, 4:01 PM
 */

#ifndef _LIGHTSTUDYANALYSISHANDLER_H
#define	_LIGHTSTUDYANALYSISHANDLER_H

#include "/user/ajafari/CMSSW_3_8_5_patch3/src/AnalysisClasses/LightJets/interface/LightAnalysis.h"
#include "BaseAnalysisHandler.h"
#include "TH1.h"
class LightStudyAnalysisHandler: public BaseAnalysisHandler<LightAnalysis>{
public:
    typedef BaseAnalysisHandler<LightAnalysis> BASE_;
    LightStudyAnalysisHandler(std::string name, bool dobtag,bool datalike, bool extJetOk_,double Lumi_,
            MassAndResolution massAndres,ElectronCuts elecCuts,JetCuts jetCuts_,std::string which = "minChi2",
            double chi2cut = 100000., double topPtcut = 0.,bool Ott = false):BASE_(name,dobtag,datalike,extJetOk_,Lumi_,
            massAndres,elecCuts,jetCuts_,which,Ott),chi2Cut(chi2cut),TopPtCut(topPtcut)
    {
        BASE_::Analyses.clear();
    };
    virtual ~LightStudyAnalysisHandler(){};
    virtual void Fill(const TopEvent je, double weight = 1., int nAna = -1){
        if(BASE_::verbosity > 0){
            cout<<"Info from TopEvent:\n\tChi2: "<<je.getTopChiSquared();
            cout<<"\n\tHadronicTop matchedChi2: "<<je.isHadronicTopMatched();
            cout<<"\n\tExtLepCand matchedChi2: "<<je.LeptonicJetIsB();
            cout<<"\n\tMlb: "<<je.getMlb()<<endl;
        }
        if(je.getTopChiSquared() >= chi2Cut || je.getHadronicTop().Pt() <= TopPtCut){
            if(BASE_::verbosity > 0){
                cout<<"\tTopPtCut or chi2Cut is not passed\n\t\t"<<
                        je.getHadronicTop().Pt()<<" > (?) "<<TopPtCut<<"\n\t\t"<<
                        je.getTopChiSquared()<<" < (?) "<<chi2Cut<<endl;

            }
            return;
        }
        if(nAna == -1){
            for(uint i = 0; i<BASE_::Analyses.size(); i++){
                BASE_::Analyses.at(i)->Fill(je,weight);
            }
        }else{
            if(nAna > BASE_::Analyses.size()){
                cout<<"analysis does not exist"<<endl;
                return;
            }
            BASE_::Analyses.at(nAna)->Fill(je,weight);
        }
    }
    void WriteAll(TDirectory * dir){
        dir->cd();
        TDirectory * my_Dir = (TDirectory *)dir->mkdir(BASE_::Name.c_str());
        my_Dir->cd();
        for(uint i = 0; i<BASE_::Analyses.size(); i++){
            BASE_::Analyses.at(i)->WriteAll(my_Dir);
        }
        dir->cd();
    }

    virtual void End(int q = 0 ){
        TFile * f = new TFile(string(BASE_::Name+"_"+BASE_::whichMethodToSelectHadTop+".root").c_str(),"recreate");
        this->WriteAll(f);
        f->Close();
    }
    void setChi2Cut(double cut){chi2Cut = cut;};
    void setTopPtCut(double cut){TopPtCut = cut;};
    void setVerbosity(int i){
        BASE_::setVerbosity(i);
//        cout<<"In Handler "<<BASE_::Name<<" verbosity is set to "<<verbosity<<endl;
        for(uint j = 0; j<Analyses.size(); j++){
            Analyses.at(j)->setVerbosity(verbosity);
        }
    }
//private:
    double chi2Cut;
    double TopPtCut;

};





#endif	/* _LIGHTSTUDYANALYSISHANDLER_H */

