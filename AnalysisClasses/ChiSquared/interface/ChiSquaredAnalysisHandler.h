/* 
 * File:   ChiSquaredAnalysisHandler.h
 * Author: ajafari
 *
 * Created on August 19, 2010, 2:01 PM
 */

#ifndef _CHISQUAREDBASEANALYSIS_H
#define	_CHISQUAREDBASEANALYSIS_H
#include "PurChiSquaredHandler.h"
#include "EffChiSquaredHandler.h"
#include "BaseAnalysisHandler.h"
#include "TH1.h"
#include "TwoDObjectPropertyCreator.h"
class ChiSquaredAnalysisHandler: public BaseAnalysisHandler<BaseChiSquaredHandler>{
public:
    typedef BaseAnalysisHandler<BaseChiSquaredHandler> BASE_;
    ChiSquaredAnalysisHandler(std::string name, bool dobtag,bool datalike, bool extJetOk_,double Lumi_,
            MassAndResolution massAndres,ElectronCuts elecCuts,JetCuts jetCuts_,std::string which = "minChi2",
            double chi2cut = 100000., double topPtcut = 0.):BASE_(name,dobtag,datalike,extJetOk_,Lumi_,massAndres,
            elecCuts,jetCuts_,which),chi2Cut(chi2cut),TopPtCut(topPtcut)
    {
        BASE_::Analyses.clear();
        PurChiSquaredHandler * purity_h = new PurChiSquaredHandler("Purity");
        BASE_::AddAnalysis(purity_h);
        MatchedEffChiSquaredHandler * meff_h = new MatchedEffChiSquaredHandler("MatchedEfficiency");
        BASE_::AddAnalysis(meff_h);
/*        std::vector<ObjectProperty<TopEvent> * > propsToStudy;
        propsToStudy.clear();
        EffChiSquaredHandler * eff_h = new EffChiSquaredHandler("Efficiency");
        eff_h->AddProp(new TopEventShape("isotropy",2.));
        propsToStudy.push_back(new TopEventShape("isotropy",2.));
        eff_h->AddProp(new TopEventShape("circularity",2.));
        propsToStudy.push_back(new TopEventShape("circularity",2.));
        eff_h->AddProp(new TopEventShape("sphericity",2.));
        propsToStudy.push_back(new TopEventShape("sphericity",2.));
        eff_h->AddProp(new TopEventShape("aplanarity",2.));
        propsToStudy.push_back(new TopEventShape("aplanarity",2.));
        eff_h->AddProp(new TopEventShape("C",2.));
        propsToStudy.push_back(new TopEventShape("C",2.));
        eff_h->AddProp(new TopEventShape("D",2.));
        propsToStudy.push_back(new TopEventShape("D",2.));

        std::vector<int> index;
        index.clear();
        index.push_back(0);
        index.push_back(1);
        index.push_back(2);
        index.push_back(3);
        eff_h->AddProp(new HT(index,"allJets"));
        propsToStudy.push_back(new HT(index,"allJets"));

        index.clear();
        index.push_back(1);
        index.push_back(2);
        index.push_back(3);
        eff_h->AddProp(new HT(index,"Last3Jets"));
        propsToStudy.push_back(new HT(index,"Last3Jets"));

        index.clear();
        index.push_back(0);
        index.push_back(1);
        index.push_back(2);
        eff_h->AddProp(new HT(index,"First3Jets"));
        propsToStudy.push_back(new HT(index,"First3Jets"));

        index.clear();
        index.push_back(0);
        index.push_back(3);
        index.push_back(2);
        eff_h->AddProp(new HT(index,"No2ndJet"));
        propsToStudy.push_back(new HT(index,"No2ndJet"));

        index.clear();
        index.push_back(0);
        index.push_back(1);
        index.push_back(3);
        eff_h->AddProp(new HT(index,"No3rdJet"));
        propsToStudy.push_back(new HT(index,"No3rdJet"));

        index.clear();
        index.push_back(0);
        index.push_back(1);
        eff_h->AddProp(new HT(index,"Jets01"));
        propsToStudy.push_back(new HT(index,"Jets01"));

        index.clear();
        index.push_back(0);
        index.push_back(2);
        eff_h->AddProp(new HT(index,"Jets02"));
        propsToStudy.push_back(new HT(index,"Jets02"));

        index.clear();
        index.push_back(0);
        index.push_back(3);
        eff_h->AddProp(new HT(index,"Jets03"));
        propsToStudy.push_back(new HT(index,"Jets03"));

        index.clear();
        index.push_back(1);
        index.push_back(2);
        eff_h->AddProp(new HT(index,"Jets12"));
        propsToStudy.push_back(new HT(index,"Jets12"));

        index.clear();
        index.push_back(1);
        index.push_back(3);
        eff_h->AddProp(new HT(index,"Jets13"));
        propsToStudy.push_back(new HT(index,"Jets13"));

        index.clear();
        index.push_back(2);
        index.push_back(3);
        eff_h->AddProp(new HT(index,"Jets23"));
        propsToStudy.push_back(new HT(index,"Jets23"));

        
        eff_h->AddProp(new TopPt());
        propsToStudy.push_back(new TopPt());
        eff_h->AddProp(new TopEta());
        propsToStudy.push_back(new TopEta());

        eff_h->AddProp(new DrHadBLepton());
        propsToStudy.push_back(new DrHadBLepton());
        eff_h->AddProp(new DrHadWHadB());
        propsToStudy.push_back(new DrHadWHadB());
        eff_h->AddProp(new DrHadWLepB());
        propsToStudy.push_back(new DrHadWLepB());
        eff_h->AddProp(new DrTopHadB());
        propsToStudy.push_back(new DrTopHadB());
        eff_h->AddProp(new DrTopLepB());
        propsToStudy.push_back(new DrTopLepB());
        eff_h->AddProp(new DrTopW());
        propsToStudy.push_back(new DrTopW());

        eff_h->AddProp(new DThetaHadBLepton());
        propsToStudy.push_back(new DThetaHadBLepton());
        eff_h->AddProp(new DThetaHadWHadB());
        propsToStudy.push_back(new DThetaHadWHadB());
        eff_h->AddProp(new DThetaHadWLepB());
        propsToStudy.push_back(new DThetaHadWLepB());
        eff_h->AddProp(new DThetaTopHadB());
        propsToStudy.push_back(new DThetaTopHadB());
        eff_h->AddProp(new DThetaTopLepB());
        propsToStudy.push_back(new DThetaTopLepB());
        eff_h->AddProp(new DThetaTopW());
        propsToStudy.push_back(new DThetaTopW());

        eff_h->AddProp(new DPhiHadBLepton());
        propsToStudy.push_back(new DPhiHadBLepton());
        eff_h->AiddProp(new DPhiHadWHadB());
        propsToStudy.push_back(new DPhiHadWHadB());
        eff_h->AddProp(new DPhiHadWLepB());
        propsToStudy.push_back(new DPhiHadWLepB());
        eff_h->AddProp(new DPhiTopHadB());
        propsToStudy.push_back(new DPhiTopHadB());
        eff_h->AddProp(new DPhiTopLepB());
        propsToStudy.push_back(new DPhiTopLepB());
        eff_h->AddProp(new DPhiTopW());
        propsToStudy.push_back(new DPhiTopW());

        

        eff_h->ResetConditionForAllProps();
        
        BASE_::AddAnalysis(eff_h);
        
        my2Ds = new TwoDObjectPropertyCreator<TopEvent>("DiscrimW",propsToStudy);*/
        my2Ds = 0;
        matchedChi2 = new TH1D("matched_Chi2","matched_Chi2",1000,0.,100.);
        matchedChi2->GetXaxis()->SetTitle("#chi^{2} of matched top");
        matchedTopPt = new TH1D("matched_TopPt","matched_TopPt",1000,0.,1000.);
        matchedTopPt->GetXaxis()->SetTitle("P_{T} of matched top");
    };
    virtual ~ChiSquaredAnalysisHandler(){};
    virtual void Fill(const TopEvent je, double weight = 1.,int nAna = -1){
        if(BASE_::verbosity > 0){
            cout<<"Info from TopEvent:\n\tChi2: "<<je.getTopChiSquared();
            cout<<"\n\tHadronicTop matchedChi2: "<<je.isHadronicTopMatched();
            cout<<"\n\tExtLepCand matchedChi2: "<<je.LeptonicJetIsB();
//            cout<<"\n\tLepCand matchedChi2: "<<c->isLepCandmatchedChi2();
            cout<<"\n\tMlb: "<<je.getMlb()<<endl;
            cout<<"\n\tTopSumPt: "<<je.TopPtSum<<endl;
            cout<<"\n\trelTopPt: "<<(double)je.getHadronicTop().Pt()/(double)je.TopPtSum<<endl;
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
                BASE_::Analyses.at(i)->Fill(&je,weight);
            }
        }else{
            if(nAna == -1){
                cout<<"analysis does not exist"<<endl;
                return;
            }
            BASE_::Analyses.at(nAna)->Fill(&je,weight);
        }
        if(myTop.HadBIndex != -1){
            matchedChi2->Fill(myTop.getTopChiSquared());
            matchedTopPt->Fill(myTop.getHadronicTop().Pt());
        }
	//cout<<"my2Ds = "<<my2Ds<<endl;
	if(my2Ds != NULL)
	        my2Ds->Fill(&je,weight);
    }
    void WriteAll(TDirectory * dir){
        dir->cd();
        TDirectory * my_Dir = (TDirectory *)dir->mkdir(BASE_::Name.c_str());
        my_Dir->cd();
        for(uint i = 0; i<BASE_::Analyses.size(); i++){
            BASE_::Analyses.at(i)->WriteAll(my_Dir);
        }
        if(myTop.HadBIndex != -1){
            matchedChi2->Write();
            matchedTopPt->Write();
        }
	if(my2Ds != NULL)
        	my2Ds->Write(my_Dir);
        dir->cd();
    }
    
    virtual void End(int q = 0 ){
        TFile * f = new TFile(string(BASE_::Name+"_"+BASE_::whichMethodToSelectHadTop+".root").c_str(),"recreate");
        this->WriteAll(f);
        f->Close();
    }
    void setChi2Cut(double cut){chi2Cut = cut;};
    void setTopPtCut(double cut){TopPtCut = cut;};

private:
    TH1D * matchedChi2;
    TH1D * matchedTopPt;
    double chi2Cut;
    double TopPtCut;
    TwoDObjectPropertyCreator<TopEvent> * my2Ds;

};


#endif	/* _CHISQUAREDBASEANALYSIS_H */

