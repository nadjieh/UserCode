/* 
 * File:   BaseAnalysisHandler.h
 * Author: ajafari
 *
 * Created on August 19, 2010, 2:26 PM
 */

#ifndef _BASEANALYSISHANDLER_H
#define	_BASEANALYSISHANDLER_H



#include "/user/ajafari/CMSSW_3_8_5_patch3/src/AnalysisClasses/EventSelection/interface/GoodObjects.h"
#include "/user/ajafari/CMSSW_3_8_5_patch3/src/AnalysisClasses/ChiSquared/interface/TopEvent.h"
#include "/user/ajafari/CMSSW_3_8_5_patch3/src/AnalysisClasses/ChiSquared/interface/Combinator.h"
#include "/user/ajafari/CMSSW_3_8_5_patch3/src/AnalysisClasses/LightJets/interface/NeededStructs.h"


template <class T>
class BaseAnalysisHandler{
public:
    struct TopPtSort{
        bool operator() (TopEvent comb1, TopEvent comb2) { return (comb1.getHadronicTop().Pt() > comb2.getHadronicTop().Pt());}
    } myTopPtSort;

    BaseAnalysisHandler(std::string anaName, bool dobtag,bool dataLike, bool extJetOk_,double Lumi_,
    MassAndResolution massAndres,ElectronCuts elecCuts,JetCuts jetCuts_,std::string which = "minChi2",bool Ott = false
    ,bool rrE = false, bool matchElectron = false) :
    Name(anaName),
    doBtag(dobtag),
    doBtagDataLike(dataLike),
    extJetOk(extJetOk_),
    Lumi(Lumi_),
    electronCuts(elecCuts),
    jetCuts(jetCuts_),
    whichMethodToSelectHadTop(which),
    OtherTts(Ott),
    RejectRadEvt(rrE),
    matchEle(matchElectron)
    {
        constraints.topMass = massAndres.topMass;
        constraints.wMass = massAndres.wMass;
        constraints.topRes = massAndres.topRes;
        constraints.wRes = massAndres.wRes;
        Only4MatchedJets = false;
        PileUp = 10000.;
        verbosity = 0;
	n4jets = 0;
	nScrap = 0;
    };
    virtual ~BaseAnalysisHandler(){};
    T * AddAnalysis(T * analysis){
        if(analysis->WhoAmI() == "EfficiencyHandler")
            analysis->setName(string(Name + "_" + analysis->getName()));
//        else
//            analysis->Name = Name + "_" + analysis->Name;
        Analyses.push_back(analysis);
        f.push_back(-10000);
        return analysis;
    }
    virtual void Fill(TopEvent jetElec, double weight = 1., int nAna = -1) = 0;
    
    virtual void End(int q = 0) = 0;
    void setOnly4MatchedJets(){Only4MatchedJets = true;};
    void setVerbosity(int i){
        verbosity = i;
//        cout<<"In AnalysisHandler "<<Name<<" verbosity is set to "<<verbosity<<endl;
    }

    void Analyze(PracticalEvent* e,double weight, double JES = 1., int nAna = -1, bool isData = false, bool doCorr=true){
        GoodObjects * GO = new GoodObjects(e,  electronCuts,jetCuts,extJetOk,verbosity,OtherTts,0,e->GenEvtCollection(),matchEle,JES,isData,doCorr);
        if(verbosity > 1)
            cout<<"In the BaseAnalysis::Analyze method of "<<Name<<"\n\tOnly4MatchedJets is "
                    <<Only4MatchedJets<<" and GO->has4MatchedJets is "<<GO->has4MatchedJets()<<endl;
        if(Only4MatchedJets && !GO->has4MatchedJets())
            return;

        TRootElectron  elec = GO->Electron();
        std::vector<ExtendedJet> jets = GO->ExtJets();
//        cout<<"Before JetChecking of analysis "<<nAna<<endl;
        if(jets.size() < 4){
            delete GO;
            return;
        }
	n4jets++;
	if(isData && e->isBeamBkg()){
            delete GO;
            return;
	}
        nScrap++;
//        cout<<"After JetChecking of analysis "<<nAna<<endl;
        if(RejectRadEvt){
            if(verbosity > 0){
                cout<<"\t"<<GO->nJetsAfterCleaning<<" (JetCollectionSize) ? "<<jets.size()<<" (GoodJetSize)";
                if((int)jets.size() < GO->nJetsAfterCleaning)
                    cout<<"\tRejected"<<endl;
                else
                    cout<<"\tAccepted"<<endl;
            }
            if((int)jets.size() < GO->nJetsAfterCleaning ){
                delete GO;
                return;
            }
        }
//
        int btagIndex = -1;
        if(doBtag){
            if(verbosity > 1)
                cout<<"Going to ask for one b ..."<<endl;
            btagIndex = GO->getFirstBtagIndex();
            if( btagIndex == -1){
                if(verbosity > 1)
                    cout<<"No bjets found. event is rejected"<<endl;
                delete GO;
                return;
            }
            if(verbosity > 1)
                cout<<"bjet found. event is accepted.\n\tThe btag index is "<<btagIndex<<endl;
        }
//        TopEvent Chi2 = ChiSquaredManager(jets,elec,btagIndex);
        minChi2 = ChiSquaredManager(jets,elec,btagIndex);
        if(PileUp != 10000.){
            Event EVT(*e->VertexCollection());
            EVT.VertexMaker();
            TRootVertex pv = EVT.Gpvs.at(0);
            double dr = sqrt((minChi2.getQ1().getJet().X() - pv.X())*(minChi2.getQ1().getJet().X() - pv.X()) +
                             (minChi2.getQ1().getJet().Y() - pv.Y())*(minChi2.getQ1().getJet().Y() - pv.Y()) +
                             (minChi2.getQ1().getJet().Z() - pv.Z())*(minChi2.getQ1().getJet().Z() - pv.Z()));
            if(dr > PileUp){
                delete GO;
                return;
            }
            dr = sqrt((minChi2.getQ1().getJet().X() - pv.X())*(minChi2.getQ1().getJet().X() - pv.X()) +
                             (minChi2.getQ1().getJet().Y() - pv.Y())*(minChi2.getQ1().getJet().Y() - pv.Y()) +
                             (minChi2.getQ1().getJet().Z() - pv.Z())*(minChi2.getQ1().getJet().Z() - pv.Z()));
            if(dr > PileUp){
                delete GO;
                return;
            }
        }
//        cout<<"Before Filling of analysis "<<nAna<<endl;
        if(whichMethodToSelectHadTop == "minChi2"){
            this->Fill(minChi2,weight,nAna);
        }
        else if(whichMethodToSelectHadTop == "maxTopPt"){
            this->Fill(HighestPtCombination,weight,nAna);
        }
        else if(whichMethodToSelectHadTop == "minChi2inMaxTopPt"){
            this->Fill(minChi2InHighestPtCombination,weight,nAna);
        }
        else if(whichMethodToSelectHadTop == "maxPtinminChi2s"){
            this->Fill(maxPtInFourLeastminChi2,weight,nAna);
        }
        delete GO;
    }
    int n4jets;
    int nScrap;
    std::vector<double> f;
    std::string getName()const{return Name;}
    bool isDoBtag()const{return doBtag;}
    bool isDoBtagDataLike()const{return doBtagDataLike;}
    void RejectEventsWithRadiation(){RejectRadEvt = true;}
    void setMatchEle(bool e){matchEle = e;}
    TopEvent getTopEvent()const{return minChi2;}
    void setPileUp(double PUcut){
        PileUp = PUcut;
    }
    void resetMinChi2Top(){
        minChi2.Electron.SetPxPyPzE(-1,-1,-1,-1);
        minChi2.HadBIndex = -1;
        minChi2.Jets.clear();
        minChi2.LepBIndex = -1;
        minChi2.M3 = -1;
        minChi2.TopPtSum = -1;
        minChi2.WIndecies.first = -1;
        minChi2.WIndecies.second = -1;
    }
protected:
    std::string Name;
    bool doBtag;
    bool doBtagDataLike;
    bool extJetOk;
    double Lumi;
    bool Only4MatchedJets;
    MassAndResolution constraints;
    ElectronCuts electronCuts;
    JetCuts jetCuts;
    std::vector<T*> Analyses;
    int verbosity;
    TopEvent myTop;
    TopEvent HighestPtCombination;
    TopEvent minChi2InHighestPtCombination;
    TopEvent maxPtInFourLeastminChi2;
    TopEvent minChi2;
    std::string whichMethodToSelectHadTop;
    bool OtherTts;
    bool RejectRadEvt;
    bool matchEle;
    double PileUp;
    TopEvent ChiSquaredManager(std::vector<ExtendedJet> jets, TRootElectron electron, int bTagIndex) {
        if(verbosity > 1)
            cout<<"In BaseAnalysis::ChiSquaredManager"<<endl;
        Combinator allCombinations(jets,electron,constraints,"FirstFourLeadingJets",/*dobTag*/doBtag,
        /*btagInd*/bTagIndex,/*dataBtag*/doBtagDataLike);
        allCombinations.setVerbosity(verbosity);
        if (bTagIndex != -1){
            if(verbosity > 1)
                cout<<"btagIndex is changed to "<<bTagIndex<<" in Combinator."<<endl;
            allCombinations.setBtaggingDone(bTagIndex);
        }
        std::vector<TopEvent> AllPossibleCombinations = allCombinations.getAllCombinations();
        if(verbosity > 5){
            for(uint j = 0; j < AllPossibleCombinations.size(); j++)
                cout<<"\t\tChi2 "<<AllPossibleCombinations.at(j).getTopChiSquared()<<"\t\tTopPt"<<
                AllPossibleCombinations.at(j).getHadronicTop().Pt()<<endl;
        }
        TopEvent c = AllPossibleCombinations.at(0);
        c.TopPtSum = allCombinations.getTopPtSum();
        myTop = allCombinations.getTopEvent();
        if(verbosity > 1){
            cout<<"\tTo make lightJet one\n\tJetIndex is "<<c.getQ1().getIndex()<<" "<<c.getQ1().getMatchName()<<endl;
            cout<<"\tTo make lightJet two\n\tJetIndex is "<<c.getQ2().getIndex()<<" "<<c.getQ2().getMatchName()<<endl;
            cout<<"\tTo make hadBjet\n\tJetIndex is "<<c.getHadBCand().getIndex()<<" "<<c.getHadBCand().getMatchName()<<endl;
            cout<<"\t\tChi2: "<<c.getTopChiSquared()<<endl;
            cout<<"\t\tMll1: "<<c.getMll1()<<endl;
            cout<<"\t\tMll2: "<<c.getMll2()<<endl;
            cout<<"\t\tMlHadB: "<<c.getMlHadB()<<endl;
            cout<<"\t\tMlb: "<<c.getMlb()<<endl;
            cout<<"\t\tTopSumPt: "<<c.TopPtSum<<endl;
            cout<<"\tUsing highest topPt: "<<endl;
        }
        if(whichMethodToSelectHadTop == "minChi2inMaxTopPt"){
            std::sort(AllPossibleCombinations.begin(),AllPossibleCombinations.end(),myTopPtSort);
            double min = 100000.;
            for(uint k = 0; k < 3; k++){
                if(verbosity > 2){
                    cout<<"\t\tHighest topPt, Pt is "<<AllPossibleCombinations.at(k).getHadronicTop().Pt()<<endl;
                    cout<<"\t\t\tHighest topPt, chi2 is "<<AllPossibleCombinations.at(k).getTopChiSquared()<<endl;
                }
                if(AllPossibleCombinations.at(k).getTopChiSquared()<min){
                    minChi2InHighestPtCombination = AllPossibleCombinations.at(k);
                    minChi2InHighestPtCombination.TopPtSum = allCombinations.getTopPtSum();
                    min = minChi2InHighestPtCombination.getTopChiSquared();
                }
            }
            if(verbosity > 1){
                cout<<"\t\tminChi2InHighest topPt, chi2 is "<<minChi2InHighestPtCombination.getTopChiSquared()<<endl;
                cout<<"\t\tminChi2InHighest topPt is "<<minChi2InHighestPtCombination.getHadronicTop().Pt()<<endl;
            }
        }
        if(whichMethodToSelectHadTop == "maxTopPt"){
            std::sort(AllPossibleCombinations.begin(),AllPossibleCombinations.end(),myTopPtSort);
            HighestPtCombination = AllPossibleCombinations.at(0);
            HighestPtCombination.TopPtSum = allCombinations.getTopPtSum();
            if(verbosity > 1){
                cout<<"\t\tInHighest topPt, chi2 is "<<HighestPtCombination.getTopChiSquared()<<endl;
                cout<<"\t\tHighest topPt is "<<HighestPtCombination.getHadronicTop().Pt()<<endl;
            }
        }
        if(whichMethodToSelectHadTop == "maxPtinminChi2s"){
            double maxToppt = 0;
            for(uint i = 0; i<4; i++){
                if(AllPossibleCombinations.at(i).getHadronicTop().Pt() > maxToppt){
                    maxToppt = AllPossibleCombinations.at(i).getHadronicTop().Pt();
                    maxPtInFourLeastminChi2 = AllPossibleCombinations.at(i);
                    maxPtInFourLeastminChi2.TopPtSum = allCombinations.getTopPtSum();
                }
            }
            if(verbosity > 1){
                cout<<"\t\tInHighest topPt, chi2 is "<<maxPtInFourLeastminChi2.getTopChiSquared()<<endl;
                cout<<"\t\tHighest topPt is "<<maxPtInFourLeastminChi2.getHadronicTop().Pt()<<endl;
            }
        }
        return c;
    };
};

#endif	/* _BASEANALYSISHANDLER_H */

