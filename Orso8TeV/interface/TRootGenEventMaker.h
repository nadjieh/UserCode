/* 
 * File:   TRootGenEventMaker.h
 * Author: nadjieh
 *
 * Created on November 6, 2012, 7:16 PM
 */

#ifndef TROOTGENEVENTMAKER_H
#define	TROOTGENEVENTMAKER_H
#include "../../TopBrussels/TopTreeProducer/interface/TRootNPGenEvent.h"
#include "../../TopBrussels/TopTreeProducer/interface/TRootGenTop.h"
#include "../../TopBrussels/TopTreeProducer/interface/TRootMCParticle.h"
#include "GenInfoMuonTree.h"
#include "../../AnalysisClasses/PhysicsObjects/interface/SemiLepTopQuark.h"
#include <iostream>
#include <string>
using namespace TopTree;
using namespace std;

class TRootGenEventMaker {
public:

    TRootGenEventMaker(GenInfoMuonTree * input, string sample ,int v = 0): verbosity(v){
        ntop = input->SampleRecognizer(sample);
        input->WdecayInTW = -1;
        std::vector<TRootGenTop> tops;
        if(verbosity > 0){
            cout<<"Begin GenInfo processing: -------------------------------------"<<endl;
            cout<<"Number of tops: "<<ntop<<endl;
            if(ntop == 1)
                cout<<"Single top process"<<endl;
            if(ntop == 2)
                cout<<"Top pair process"<<endl;
        }
        if (ntop > 0){
            tops.push_back(input->GetGenTop(1));
            if(verbosity > 0){
                cout<<"First Top properties: \n\tPdgId: "<<tops[0].type()<<",\tcharge: "<<tops[0].charge()
                    <<"\n\tDecay channel:";
                if(tops[0].isHadronic()){
                    cout<<" Hadrtonic";
                    cout<<"\n\t\tQ Id: "<<tops[0].quark().type()<<",\tcharge: "<<tops[0].quark().charge();
                    cout<<"\n\t\tQBar Id: "<<tops[0].quarkBar().type()<<",\tcharge: "<<tops[0].quarkBar().charge();
                    cout<<"\n\t\tQ pt: "<<tops[0].quark().Pt()<<" "<<tops[0].quark().Px()<<" "
                            <<tops[0].quark().Py()<<" "<<tops[0].quark().Pz()<<" "<<tops[0].quark().E()<<" ";
                    cout<<"\n\t\tQBar pt: "<<tops[0].quarkBar().Pt()<<" "<<tops[0].quarkBar().Px()<<" "
                            <<tops[0].quarkBar().Py()<<" "<<tops[0].quarkBar().Pz()<<" "<<tops[0].quarkBar().E()<<" ";
                }
                if(tops[0].isLeptonicEl()){
                    cout<<" Electronic";
                    cout<<"\n\t\tElectron Id: "<<tops[0].lepton().type()<<",\tcharge: "<<tops[0].lepton().charge();
                    cout<<"\n\t\tNeutrino Id: "<<tops[0].neutrino().type()<<",\tcharge: "<<tops[0].neutrino().charge();
                }
                if(tops[0].isLeptonicMu()){
                    cout<<" Muonic";
                    cout<<"\n\t\tMuon Id: "<<tops[0].lepton().type()<<",\tcharge: "<<tops[0].lepton().charge();
                    cout<<"\n\t\tNeutrino Id: "<<tops[0].neutrino().type()<<",\tcharge: "<<tops[0].neutrino().charge();
                }
                if(tops[0].isLeptonicTau()){
                    cout<<" Tau";
                    cout<<"\n\t\tTau Id: "<<tops[0].lepton().type()<<",\tcharge: "<<tops[0].lepton().charge();
                    cout<<"\n\t\tNeutrino Id: "<<tops[0].neutrino().type()<<",\tcharge: "<<tops[0].neutrino().charge();
                }
                cout<<"\n\tbQuark Id: "<<tops[0].bquark().type()<<",\tcharge: "<<tops[0].bquark().charge();                
                cout<<"\n\t\tbQuark pt: "<<tops[0].bquark().Pt()<<" "<<tops[0].bquark().Px()<<" "
                            <<tops[0].bquark().Py()<<" "<<tops[0].bquark().Pz()<<" "<<tops[0].bquark().E()<<" ";
            }
        }
        if (ntop > 1){
            tops.push_back(input->GetGenTop(2));
            if(verbosity > 0){
                cout<<"Second Top properties: \n\tPdgId: "<<tops[1].type()<<",\tcharge: "<<tops[1].charge()
                    <<"\n\tDecay channel:";
                if(tops[1].isHadronic()){
                    cout<<" Hadrtonic";
                    cout<<"\n\t\tQ Id: "<<tops[1].quark().type()<<",\tcharge: "<<tops[1].quark().charge();
                    cout<<"\n\t\tQBar Id: "<<tops[1].quarkBar().type()<<",\tcharge: "<<tops[1].quarkBar().charge();
                }
                if(tops[1].isLeptonicEl()){
                    cout<<" Electronic";
                    cout<<"\n\t\tElectron Id: "<<tops[1].lepton().type()<<",\tcharge: "<<tops[1].lepton().charge();
                    cout<<"\n\t\tNeutrino Id: "<<tops[1].neutrino().type()<<",\tcharge: "<<tops[1].neutrino().charge();
                }
                if(tops[1].isLeptonicMu()){
                    cout<<" Muonic";
                    cout<<"\n\t\tMuon Id: "<<tops[1].lepton().type()<<",\tcharge: "<<tops[1].lepton().charge();
                    cout<<"\n\t\tNeutrino Id: "<<tops[1].neutrino().type()<<",\tcharge: "<<tops[1].neutrino().charge();
                }
                if(tops[1].isLeptonicTau()){
                    cout<<" Tau";
                    cout<<"\n\t\tTau Id: "<<tops[1].lepton().type()<<",\tcharge: "<<tops[1].lepton().charge();
                    cout<<"\n\t\tNeutrino Id: "<<tops[1].neutrino().type()<<",\tcharge: "<<tops[1].neutrino().charge();
                }
                cout<<"\n\tbQuark Id: "<<tops[1].bquark().type()<<",\tcharge: "<<tops[1].bquark().charge()<<endl;                
            }
        }
        std::vector<TRootMCParticle> leptons = input->GetAllLeptons();
        if(verbosity > 0){
            cout<<"Number of leptons: "<<leptons.size()<<endl;
            for(int i = 0; i<leptons.size(); i++){
                cout<<"\tId: "<<leptons[i].type()<<
                "\n\tMother: "<<leptons[i].motherType()<<endl;
            }
        }
        if (ntop > 0){
            input->DealWithTW(tops, leptons);
            if(verbosity > 0){
                cout<<"Other W decay mode based on lepton information: "<<input->WdecayInTW<<endl;
            }
        }
        std::vector<TRootMCParticle> quarks = input->GetAllQuarks(tops);
        if(verbosity > 0){
            cout<<"Number of quarks: "<<quarks.size()<<endl;
            for(int i = 0; i<quarks.size(); i++){
                cout<<"\tId: "<<quarks[i].type()<<
                "\n\tMother: "<<quarks[i].motherType()<<endl;
            }
        }
        std::vector<TRootMCParticle> tmp;
        TRootNPGenEvent * genEvt = new TRootNPGenEvent(false, tops, leptons, quarks, tmp,
                tmp, tmp, tmp, tmp);
        output = *genEvt;
        delete genEvt;

    }

    virtual ~TRootGenEventMaker(){};
    TRootNPGenEvent output;
private:
    int ntop;
    int verbosity;
};

#endif	/* TROOTGENEVENTMAKER_H */

