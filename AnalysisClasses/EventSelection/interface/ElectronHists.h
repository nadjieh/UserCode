/*                                                                                                                                              
 * File:   ElectronHists.h                                                                                                                     
 * Author: ajafari                                                                                                                              
 *                                                                                                                                              
 * Created on November 29, 2009, 8:55 PM                                                                                                        
 */

#ifndef _ELECTRONHISTS_H
#define _ELECTRONHISTS_H

#include <iomanip>
#include "../../../TopBrussels/TopTreeProducer/interface/TRootMuon.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootElectron.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootJet.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootMET.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootGenEvent.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootEvent.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootRun.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootParticle.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootMCParticle.h"
#include "ElectronSelector.h"
#include <sstream>

#include <TFile.h>
#include <TH1.h>
#include <TH2.h>
#include <TCanvas.h>
#include <TBranch.h>
#include <TString.h>
#include <TDirectory.h>
#include <TTree.h>
#include <TClonesArray.h>
#include <vector>
#include <string>

#include "KinematicHists.h"

using namespace TopTree;

class ElectronHists{
 public:
  ElectronHists(std::string name, int cone = 3, bool second = false ): isoCone(cone),forSecond(second){
          Name = name;
    
    VBTF70 = new TH1D((Name+"_VBTF70").c_str(),( Name+"_VBTF70").c_str(), 2,0.,2.);
    VBTF70->GetXaxis()->SetTitle("VBTF70");
    mvaTrig = new TH1D((Name+"_mvaTrig").c_str(),( Name+"_mvaTrig").c_str(), 50,0.,2.);
    mvaTrig->GetXaxis()->SetTitle("mvaTrig");
    isConversion = new TH1D((Name+"_missingHits").c_str(),( Name+"_missingHits").c_str(), 10,0.,10.);
    isConversion->GetXaxis()->SetTitle("N_{missing hits}");

    relativeIso = new TH1D((Name+"_relativeIso").c_str(),(Name+"_relativeIso").c_str(),50,0.,5.);
    relativeIso->GetXaxis()->SetTitle("relativeIso");

    D0 = new TH1D((Name+"_D0").c_str(),(Name+"_D0").c_str(),100,0.,2.);
    D0->GetXaxis()->SetTitle("D0");

    sigIeta_B = new TH1D((Name+"_sigIeta_B").c_str(),(Name+"_#sigma_{i#eta i#eta}(barrel)").c_str(),20,-0.1,0.1);
    sigIeta_B->GetXaxis()->SetTitle("#sigma_{i#eta i#eta} (barrel)");
    delEtaIn_B = new TH1D((Name+"_delEtaIn_B").c_str(),(Name+"_#Delta#eta_{in}(barrel)").c_str(),100,0.,0.1);
    delEtaIn_B->GetXaxis()->SetTitle("#Delta#eta_{in} (barrel)");
    delPhiIn_B = new TH1D((Name+"_delPhiIn_B").c_str(),(Name+"_#Delta#phi_{in}(barrel)").c_str(),100,0.,1.);
    delPhiIn_B->GetXaxis()->SetTitle("#Delta#phi_{in} (barrel)");
    HoverE_B = new TH1D((Name+"_HoverE_B").c_str(),(Name+"_HoverE(barrel)").c_str(),100,0.,1.);
    HoverE_B->GetXaxis()->SetTitle("H/E (barrel)");

    sigIeta_E = new TH1D((Name+"_sigIeta_E").c_str(),(Name+"_#sigma_{i#eta i#eta}(endcap)").c_str(),20,-0.1,0.1);
    sigIeta_E->GetXaxis()->SetTitle("#sigma_{i#eta i#eta} (endcap)");
    delEtaIn_E  = new TH1D((Name+"_delEtaIn_E").c_str(),(Name+"_#Delta#eta_{in}(endcap)").c_str(),100,0.,0.1);
    delEtaIn_E->GetXaxis()->SetTitle("#Delta#eta_{in} (endcap)");
    delPhiIn_E = new TH1D((Name+"_delPhiIn_E").c_str(),(Name+"_#Delta#phi_{in}(endcap)").c_str(),100,0.,1.);
    delPhiIn_E->GetXaxis()->SetTitle("#Delta#phi_{in} (endcap)");
    HoverE_E = new TH1D((Name+"_HoverE_E").c_str(),(Name+"_HoverE(endcap)").c_str(),100,0.,1.);
    HoverE_E->GetXaxis()->SetTitle("H/E (endcap)");
    DCot = new TH1D((Name+"_DCot").c_str(),"DCot (regarding partener track)",100,0.,2.);
    DCot->GetXaxis()->SetTitle("DCot");
    Dist = new TH1D((Name+"_Dist").c_str(),"Dist (regarding partener track)",100,0.,2.);
    Dist->GetXaxis()->SetTitle("Dist");

    DcotDist = new TH2D((Name+"_DCotDist").c_str(),"Dist vs DCot (regarding partener track)",100,0.,2.,100,0.,2.);
    DcotDist->GetXaxis()->SetTitle("DCot");
    DcotDist->GetYaxis()->SetTitle("Dist");

    nGoodElectrons = new TH1D((Name+"_nSelectedElecs").c_str(),"number of selected electrons",10,0.,10.);
    nGoodElectrons->GetXaxis()->SetTitle("N_{selected electrons}");

    if(forSecond){
	zMass = new TH1D((Name+"_InvMass").c_str(),"Invariant mass of electron pair",100,20.,120.);
	zMass->GetXaxis()->SetTitle("InvMass(GE,LE)");
    }
    kinHists = new KinematicHists<TRootElectron>(Name);

  };
  virtual ~ElectronHists(){};
  virtual void Fill(std::vector<TRootElectron> electron, TLorentzVector GE, double zPV = 0, int nGE = 0){
    ElectronSelector eSelector;  
    for(unsigned int i = 0; i<electron.size(); i++){
	kinHists->Fill(&(electron.at(i)));
        VBTF70->Fill(eSelector.isVBTF70Id(&(electron.at(i))));
        isConversion->Fill(electron.at(i).missingHits());
        relativeIso->Fill(eSelector.relativePFIsolation(electron.at(i)));
        D0->Fill(electron.at(i).d0());
        if(electron.at(i).isEB()){
            sigIeta_B->Fill(electron.at(i).sigmaIEtaIEta()); //first it should be stored in TRootElectron
            delEtaIn_B->Fill(electron.at(i).deltaEtaIn());
        //std::cout<<"in Fill Electron Method: 14"<<std::endl;
            delPhiIn_B->Fill(electron.at(i).deltaPhiIn());
        //std::cout<<"in Fill Electron Method: 15"<<std::endl;
            HoverE_B->Fill(electron.at(i).hadronicOverEm());
        }

      if(electron.at(i).isEE()){
        sigIeta_E->Fill(electron.at(i).sigmaIEtaIEta()); //first it should be stored in TRootElectron
        delEtaIn_E->Fill(electron.at(i).deltaEtaIn());
      //std::cout<<"in Fill Electron Method: 14"<<std::endl;
        delPhiIn_E->Fill(electron.at(i).deltaPhiIn());
      //std::cout<<"in Fill Electron Method: 15"<<std::endl;
        HoverE_E->Fill(electron.at(i).hadronicOverEm());
      }

      //std::cout<<"in Fill Electron Method: 16"<<std::endl;
        DCot->Fill(fabs(electron.at(i).DCot()));
        Dist->Fill(fabs(electron.at(i).Dist()));
	DcotDist->Fill(fabs(electron.at(i).DCot()),fabs(electron.at(i).Dist()));
        if(forSecond){
	    double zmass = (electron.at(i)+GE).M();
            zMass->Fill(zmass);
        }
    }
    nGoodElectrons->Fill(nGE);
  };
  virtual void WriteAll(TDirectory * dir){
        if (dir == 0)
            return;
        TDirectory* my_dir = dir->mkdir((Name+"_Electron").c_str());
        my_dir->cd();
        VBTF70->Write();
        mvaTrig->Write();
        isConversion->Write();
        relativeIso->Write();
        D0->Write();
        sigIeta_B->Write();
        delEtaIn_B->Write();
        delPhiIn_B->Write();
        HoverE_B->Write();
        sigIeta_E->Write();
        delEtaIn_E->Write();
        delPhiIn_E->Write();
        HoverE_E->Write();
	DCot->Write();
	Dist->Write();
	DcotDist->Write();
        kinHists->Write(); 
	if(forSecond){
	    zMass->Write();
        }
	nGoodElectrons->Write();
        dir->cd();
  };
 private:
  int isoCone;
  TH1D * VBTF70;
  TH1D * mvaTrig;
  TH1D * relativeIso;
  TH1D * D0;
  TH1D * sigIeta_B;
  TH1D * delEtaIn_B;
  TH1D * delPhiIn_B;
  TH1D * HoverE_B;

  TH1D * sigIeta_E;
  TH1D * delEtaIn_E;
  TH1D * delPhiIn_E;
  TH1D * HoverE_E;
 
  TH1D * DCot;
  TH1D * Dist;

  TH1D * isConversion;

  TH2D * DcotDist;

  KinematicHists<TRootElectron> * kinHists;  
  std::string Name;
  bool  forSecond;
  TH1D * zMass;
  TH1D * nGoodElectrons;

};
#endif

