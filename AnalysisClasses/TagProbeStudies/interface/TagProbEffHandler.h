/* 
 * File:   TagProbEffHandler.h
 * Author: ajafari
 *
 * Created on October 28, 2010, 5:50 PM
 */

#ifndef TAGPROBEFFHANDLER_H
#define	TAGPROBEFFHANDLER_H
using namespace std;
using namespace TopTree;
#include "/afs/cern.ch/user/a/ajafari/scratch0/CMSSW_3_8_5_patch3/src/AnalysisClasses/TagProbeStudies/interface/TagProbeObjectPropertis.h"
#include "TH2.h"

class TagProbeEffHandler : public EfficiencyHandler<TRootTagProbeObject> {
public:
    typedef EfficiencyHandler<TRootTagProbeObject> BASE_;

    TagProbeEffHandler(std::string name, bool twoD = true, bool isZ = false) :
    BASE_(name),
    twoD_(twoD) {
        v.clear();
        BASE_::AllCondition = 0;
        BASE_::AddProp(new ProbeEta());
        v.push_back(new ProbeEta());
        BASE_::AddProp(new ProbePt());
        v.push_back(new ProbePt());
        BASE_::AddProp(new ProbePhi());
        v.push_back(new ProbePhi());
        BASE_::AddProp(new nJet());
        v.push_back(new nJet());
        BASE_::AddProp(new minRJetProbe());
        v.push_back(new minRJetProbe());

        BASE_::AddProp(new ProbeTrackIso());
        v.push_back(new ProbeTrackIso());
        BASE_::AddProp(new ProbeHcalIso());
        v.push_back(new ProbeHcalIso());
        BASE_::AddProp(new ProbeEcalIso());
        v.push_back(new ProbeEcalIso());

        BASE_::AddProp(new ProbeHoE());
        v.push_back(new ProbeHoE());
        BASE_::AddProp(new ProbeSigmaIEtaIEta());
        v.push_back(new ProbeSigmaIEtaIEta());
        BASE_::AddProp(new ProbedelEtaIn());
        v.push_back(new ProbedelEtaIn());
        BASE_::AddProp(new ProbedelPhiIn());
        v.push_back(new ProbedelPhiIn());



        if (isZ) {
            BASE_::AddProp(new Zmass());
            v.push_back(new Zmass());
        }
        twoDHists.clear();
        for (uint i = 0; i < v.size(); i++) {
            for (uint j = i + 1; j < v.size(); j++) {
                twoDHists.push_back(new TH2D(*(TH2D*) (v.at(i)->GetH2(v.at(j), "", ""))));
            }
        }
    }
    bool twoD_;
    std::vector<TH2D*> twoDHists;

    virtual void Fill(TRootTagProbeObject* t, double weight = 1) {
        BASE_::Fill(t, weight);
        //        cout<<twoDHists.size()<<endl;
        int n = 0;
        for (uint i = 0; i < v.size(); i++) {
            for (uint j = i + 1; j < v.size(); j++) {
                twoDHists.at(n)->Fill(v.at(i)->ReadValue(t).at(0), v.at(j)->ReadValue(t).at(0), weight);
                n++;
                //                cout<<n<<endl;
            }
        }
    }

    virtual void WriteAll(TDirectory * dir) {
        BASE_::WriteAll(dir);
        if (twoDHists.size() != 0) {
            dir->mkdir(string(BASE_::getName() + "_2D").c_str())->cd();
            for (uint j = 0; j < twoDHists.size(); j++) {
                twoDHists.at(j)->Write();
            }
        }

    }

    void ResetConditionForAllProps() {
        for (uint i = 0; i < BASE_::GetProperties(); i++) {
            BASE_::GetEffH1(i)->Condition = BASE_::Condition;
            BASE_::GetEffH1(i)->AllCondition = BASE_::AllCondition;
        }
    }
private:
    std::vector<ObjectProperty<TRootTagProbeObject> * > v;
};


#endif	/* TAGPROBEFFHANDLER_H */

