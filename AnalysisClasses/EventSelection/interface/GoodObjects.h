/* 
 * File:   GoodObjects.h
 * Author: ajafari
 *
 * Created on July 8, 2010, 4:23 PM
 */

#ifndef _GOODOBJECTS_H
#define	_GOODOBJECTS_H



#include <iostream>
#include <vector>
#include "../../../TopBrussels/TopTreeProducer/interface/TRootCaloJet.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootPFJet.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootElectron.h"
#include "../../../AnalysisClasses/EventSelection/interface/PracticalEvent.h"
#include "../../../AnalysisClasses/EventSelection/interface/JetMatching.h"
#include "../../../AnalysisClasses/ChiSquared/interface/ExtendedJet.h"
#include "../../../AnalysisClasses/LightJets/interface/NeededStructs.h"
#include "Event.h"


using namespace TopTree;
class GoodObjects{
public:
    GoodObjects(PracticalEvent * pracEvt, ElectronCuts elecCut,JetCuts jetCuts, bool ExtJet_ = true,int ver = -1,
    bool includeAllTts = false,int nCleanJet = 0,TClonesArray* ges = 0, bool doEMatch = false,double JES = 1., bool isData = false
            , int jetType = 1):
    ExtJet(ExtJet_),
    verbosity(ver),
    OtherTts(includeAllTts),
    nJetsAfterCleaning(nCleanJet)
    {
        if(jetType == 1){
            Event myEvent_tmp(pracEvt->ScaledJetCollection(JES,isData), *pracEvt->ElectronCollection());

            myEvent_tmp.verbose(verbosity);
            myEvent_tmp.doMatchElec = doEMatch;
            if(ges != NULL && doEMatch){
                TRootGenEvent * ge = (TRootGenEvent*)ges->At(0);
                myEvent_tmp.GenElec.SetPxPyPzE(ge->lepton().Px(),ge->lepton().Py(),ge->lepton().Pz(),ge->lepton().E());
            }
            if( verbosity > 1){
                    if(doEMatch )
                        cout<<"I want to match the electron!\tMatching in Event is "<<myEvent_tmp.doMatchElec<<endl;
                    cout<<"GenElec properties in Event:\n\t"<<myEvent_tmp.GenElec.Px()<<"\n\t"<<myEvent_tmp.GenElec.Py()<<"\n\t"<<
                    myEvent_tmp.GenElec.Pz()<<endl;
            }
            if(verbosity > 1)
                cout<<"Electron Maker ---------------------------------------------------------------------"<<endl;
            myEvent_tmp.ElectronMaker(elecCut.Pt,elecCut.eta,elecCut.ExLow,elecCut.ExHigh,elecCut.Id,elecCut.IdSecond,
            elecCut.IsoType,elecCut.D0,elecCut.IsoCut);
            if(verbosity > 1)
                cout<<"Jet Cleaning  ---------------------------------------------------------------------"<<endl;
            myEvent_tmp.JetCleaning();
            nJetsAfterCleaning = myEvent_tmp.CaloJets.size();
            if(verbosity > 1)
                cout<<"Jet Makers ---------------------------------------------------------------------"<<endl;
            myEvent_tmp.JetMaker(jetCuts.bTagAlgo,jetCuts.Pt,jetCuts.eta,jetCuts.nCaloTower,jetCuts.EmfUp,jetCuts.EmfLow,
            jetCuts.fhpd,jetCuts.N90,jetCuts.bTagCut);
            if(verbosity > 1)
                cout<<"\t"<<myEvent_tmp.Gelectrons.size()<<" golden electron is found"<<endl;
            if(doEMatch){
                if(myEvent_tmp.matchElecIndex != -1){
                    if(verbosity > 1){
                        cout<<"I have found a matched electron and its index in the Event is "<<myEvent_tmp.matchElecIndex<<endl;
                    }
                    electron = myEvent_tmp.Gelectrons.at(myEvent_tmp.matchElecIndex);
                }
                else{
                    if(verbosity > 1){
                        cout<<"I am supposed to find a matched electron but its index in the Event is "<<myEvent_tmp.matchElecIndex<<endl;
                    }
                    return;
                }
            }else if(myEvent_tmp.Gelectrons.size() != 0)
                electron = myEvent_tmp.Gelectrons.at(0);
            else
                return;
            JetMatched4 = false;
            Jets_.clear();
            Jets_ = myEvent_tmp.GCaloJets;
            IndexOfFirstBtag = myEvent_tmp.firstBtagIndex;
            if(verbosity > 1){
                cout<<"\t"<<Jets_.size()<<" golden jets are found. The bTagIndex is "<<IndexOfFirstBtag<<endl;
            }
            if(Jets_.size() < 4){
                if(verbosity > 1)
                    cout<<"number of golden jets is less than 4. Go to next event ..."<<endl;
                return;
            }

            if(ExtJet){
                std::vector<std::pair<TRootCaloJet, int> > recJets;
                recJets.clear();
                if(pracEvt->isTtBar()){
                    if(((TRootGenEvent*)(pracEvt->GenEvtCollection()->At(0)))->isSemiLeptonic()){
                        JetMatched4 = MaryamMethod_TtBarSemiElec_Correlation(Jets_,
                            ((TRootGenEvent*)pracEvt->GenEvtCollection()->At(0)),
                            recJets,pracEvt->GenEvtCollection());
                    }
                    else if(OtherTts){
                        for(unsigned int i = 0; i<4; i++){
                            recJets.push_back(make_pair(Jets_.at(i),-1));
                        }
                    }
                }
                else{
                    bool tmp = MaryamMethod_Others_Correlation(Jets_,(TRootNPGenEvent*)(pracEvt->NPGenEvtCollection()->At(0)),recJets);
                    if(verbosity > 1)
                        cout<<"boolshit boolean ! "<<tmp<<endl;
                }
                    myExtJets.clear();

                    for(uint j = 0; j<recJets.size(); j++){
                        ExtendedJet myExtJet(recJets.at(j),j);
                        myExtJets.push_back(myExtJet);

                    }
            }
            else{
                myExtJets.clear();
                std::vector<int> matches;
                matches.clear();
                if(pracEvt->isTtBar()){
                    for(uint i = 0 ; i<4; i++){
                        if(!Jets_.at(i).isTopJet())
                            continue;
                        int flv = (int)fabs(Jets_.at(i).partonFlavour());
                        if(verbosity > 1)
                            cout<<"I am a topJet.\n\tMy flavor is "<<flv<<endl;
                        if(flv < 5 && flv != 0)
                            flv = 2;//light
                        else if(flv == 5)
                            flv = 0;//B
                        else
                            flv = -1;
                        matches.push_back(flv);
                        ExtendedJet myExt(make_pair(Jets_.at(i),flv),i);
                        myExtJets.push_back(myExt);
                    }
                    if(matches.size() >= 4)
                        JetMatched4 = (matches[0] != -1 && matches[1] != -1 && matches[2] != -1 && matches[3] != -1);
                }else{
                    for(uint i = 0 ; i<4; i++){
    //                        for(uint i = 0 ; i<Jets_.size(); i++){
                        int flv = (int)fabs(Jets_.at(i).partonFlavour());
                        if(flv < 5 && flv != 0)
                            flv = 2;//light
                        else if(flv == 5)
                            flv = 0;//B
                        else
                            flv = -1;
                        ExtendedJet myExt(make_pair(Jets_.at(i),flv),i);
                        myExtJets.push_back(myExt);
                    }
                }
            }
        }else if (jetType == 2){
            Event myEvent_tmp(pracEvt->ScaledPFJetCollection(JES,isData), *pracEvt->ElectronCollection());
        
            myEvent_tmp.verbose(verbosity);
            myEvent_tmp.doMatchElec = doEMatch;
            if(ges != NULL && doEMatch){
                TRootGenEvent * ge = (TRootGenEvent*)ges->At(0);
                myEvent_tmp.GenElec.SetPxPyPzE(ge->lepton().Px(),ge->lepton().Py(),ge->lepton().Pz(),ge->lepton().E());
            }
            if( verbosity > 1){
                    if(doEMatch )
                        cout<<"I want to match the electron!\tMatching in Event is "<<myEvent_tmp.doMatchElec<<endl;
                    cout<<"GenElec properties in Event:\n\t"<<myEvent_tmp.GenElec.Px()<<"\n\t"<<myEvent_tmp.GenElec.Py()<<"\n\t"<<
                    myEvent_tmp.GenElec.Pz()<<endl;
            }
            if(verbosity > 1)
                cout<<"Electron Maker ---------------------------------------------------------------------"<<endl;
            myEvent_tmp.ElectronMaker(elecCut.Pt,elecCut.eta,elecCut.ExLow,elecCut.ExHigh,elecCut.Id,elecCut.IdSecond,
            elecCut.IsoType,elecCut.D0,elecCut.IsoCut);
            if(verbosity > 1)
                cout<<"No Jet Cleaning  is needed for PFToPAT------------------------------------------"<<endl;

            nJetsAfterCleaning = myEvent_tmp.PFJets.size();
            if(verbosity > 1)
                cout<<"Jet Makers ---------------------------------------------------------------------"<<endl;
            myEvent_tmp.PFJetMaker(jetCuts.bTagAlgo,jetCuts.Pt,jetCuts.eta,jetCuts.nCaloTower,jetCuts.EmfUp,jetCuts.EmfLow,
            jetCuts.fhpd,jetCuts.N90,jetCuts.bTagCut);
            if(verbosity > 1)
                cout<<"\t"<<myEvent_tmp.Gelectrons.size()<<" golden electron is found"<<endl;
            if(doEMatch){
                if(myEvent_tmp.matchElecIndex != -1){
                    if(verbosity > 1){
                        cout<<"I have found a matched electron and its index in the Event is "<<myEvent_tmp.matchElecIndex<<endl;
                    }
                    electron = myEvent_tmp.Gelectrons.at(myEvent_tmp.matchElecIndex);
                }
                else{
                    if(verbosity > 1){
                        cout<<"I am supposed to find a matched electron but its index in the Event is "<<myEvent_tmp.matchElecIndex<<endl;
                    }
                    return;
                }
            }else if(myEvent_tmp.Gelectrons.size() != 0)
                electron = myEvent_tmp.Gelectrons.at(0);
            else
                return;
            JetMatched4 = false;
            PFJets_.clear();
            PFJets_ = myEvent_tmp.GPFJets;
            IndexOfFirstBtag = myEvent_tmp.firstBtagIndex;
            if(verbosity > 1){
                cout<<"\t"<<Jets_.size()<<" golden jets are found. The bTagIndex is "<<IndexOfFirstBtag<<endl;
            }
            if(PFJets_.size() < 4){
                if(verbosity > 1)
                    cout<<"number of golden jets is less than 4. Go to next event ..."<<endl;
                return;
            }
        }
    };
    TRootElectron Electron()const{
        return electron;
    };
    std::vector<TRootCaloJet> CaloJets()const{
        return Jets_;
    };
    std::vector<TRootCaloJet> Jets()const{
        return this->CaloJets();
    };
    std::vector<TRootPFJet> PFJets()const{
        return PFJets_;
    };
    std::vector<ExtendedJet> ExtJets()const{
        return myExtJets;
    };
    bool has4MatchedJets()const{
        return JetMatched4;
    };
    TRootCaloJet getFirstCaloBTag()const{
        return Jets_.at(IndexOfFirstBtag);
    };
    TRootCaloJet getFirstBTag()const{
        return this->getFirstCaloBTag();
    };
    TRootCaloJet getFirstPFBTag()const{
        return PFJets_.at(IndexOfFirstBtag);
    };
    ExtendedJet getFirstExtBTag()const{
        return (myExtJets.at(IndexOfFirstBtag));
    };
    int getFirstBtagIndex()const{
        return IndexOfFirstBtag;
    };
private:
    bool ExtJet;
    std::vector<TRootCaloJet> Jets_;
    std::vector<TRootPFJet> PFJets_;
    TRootElectron electron;
    bool JetMatched4;
    std::vector<ExtendedJet> myExtJets;
    int IndexOfFirstBtag;
    int verbosity;
    bool OtherTts;
public:
    int nJetsAfterCleaning;
};


#endif	/* _GOODOBJECTS_H */

