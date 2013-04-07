/* 
 * File:   KinematicHists.h
 * Author: ajafari
 *
 * Created on November 28, 2009, 5:48 PM
 */

#ifndef _KINEMATICHISTS_H
#define	_KINEMATICHISTS_H

#include <iomanip>
#include "../../../TopBrussels/TopTreeProducer/interface/TRootMuon.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootElectron.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootJet.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootMET.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootPFMET.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootGenEvent.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootEvent.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootRun.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootParticle.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootMCParticle.h"
#include <sstream>

#include <TFile.h>
#include <TH1.h>
#include <TH2.h>
#include <TCanvas.h>
#include <TBranch.h>
#include <TTree.h>
#include <TClonesArray.h>
#include <vector>
template<class theObject>
class KinematicHists{
public:
    KinematicHists(std::string name, bool sumw2 = false):Name(name), setSumW2(sumw2){
        pt = new TH1D((Name+"_Pt").c_str(), (Name+"_Pt").c_str(), 50,0.,200.);
        eta = new TH1D((Name+"_Eta").c_str(),(Name+"_Eta").c_str(), 100,-5.,5.);
        absEta = new TH1D((Name+"_absEta").c_str(),(Name+"_absEta").c_str(), 10,0,5.);
        pt->GetXaxis()->SetTitle("P_{T}");
        eta->GetXaxis()->SetTitle("#eta");
        absEta->GetXaxis()->SetTitle("|#eta|");
        if(setSumW2){
            pt->Sumw2();
            eta->Sumw2();
            absEta->Sumw2();
        }
    };
    virtual ~KinematicHists(){};
    virtual void Fill(theObject * obj,double weight = 1){
        pt->Fill(obj->Pt(),weight);
        eta->Fill(obj->Eta(),weight);
        absEta->Fill(obj->Eta(),weight);
    };
    virtual void Write(){
      pt->Write();
      eta->Write();
      absEta->Write();
    };
private:
    std::string Name;
    TH1D * pt;
    TH1D * eta;
    TH1D * absEta;
    bool setSumW2;
};


#endif	/* _KINEMATICHISTS_H */

