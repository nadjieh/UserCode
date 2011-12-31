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
#include "../../../TopBrussels/TopTreeProducer/interface/TRootSignalEvent.h"
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
    
    LooseId = new TH1D((Name+"_LooseId").c_str(), (Name+"_LooseId").c_str(), 2,0.,2.);
    LooseId->GetXaxis()->SetTitle("LooseId");
    robustLooseId = new TH1D((Name+"_robustLooseId").c_str(),( Name+"_robustLooseId").c_str(), 2,0.,2.);
    robustLooseId->GetXaxis()->SetTitle("robustLooseId");
    TightId = new TH1D((Name+"_TightId").c_str(),( Name+"_TightId").c_str(), 2,0.,2.);
    TightId->GetXaxis()->SetTitle("TightId");
    robustTightId = new TH1D((Name+"_robustTightId").c_str(),( Name+"_robustTightId").c_str(), 2,0.,2.);
    robustTightId->GetXaxis()->SetTitle("robustTightId");
    isConversion = new TH1D((Name+"_missingHits").c_str(),( Name+"_missingHits").c_str(), 10,0.,10.);
    isConversion->GetXaxis()->SetTitle("N_{missing hits}");
    isECalDriven = new TH1D((Name+"_isECalDriven").c_str(),( Name+"_isECalDriven").c_str(), 2,0.,2.);
    isECalDriven->GetXaxis()->SetTitle("isECalDriven");

//    trackerIso = new TH1D((Name+"_trkIso").c_str(),(Name+"_trkIso").c_str(),500,0.,10.);
//    trackerIso->GetXaxis()->SetTitle("trackerIso");
    relTrkIso = new TH1D((Name+"_relTrkIso").c_str(),(Name+"_relTrkIso").c_str(),50,0.,5.);
    relTrkIso->GetXaxis()->SetTitle("relTrkIso");
//    ecalIso = new TH1D((Name+"_ecalIso").c_str(),(Name+"_ecalIso").c_str(),500,0.,10.);
//    ecalIso->GetXaxis()->SetTitle("ecalIso");
//    hcalIso = new TH1D((Name+"_hcalIso").c_str(),(Name+"_hcalIso").c_str(),500,0.,10.);
//    hcalIso->GetXaxis()->SetTitle("hcalIso");
//    caloIso = new TH1D((Name+"_caloIso").c_str(),(Name+"_caloIso").c_str(),500,0.,10.);
//    caloIso->GetXaxis()->SetTitle("caloIso");
    relCaloIso = new TH1D((Name+"_relCaloIso").c_str(),(Name+"_relCaloIso").c_str(),50,0.,5.);
    relCaloIso->GetXaxis()->SetTitle("relCaloIso");
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

    delVePV = new TH1D((Name+"_delVePV").c_str(),(Name+"_delVePV").c_str(),10,0.,5.);   
    delVePV->GetXaxis()->SetTitle("#DeltaZ(ele,PV)");
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
    for(unsigned int i = 0; i<electron.size(); i++){
      //std::cout<<"in Fill Electron Method: 1"<<std::endl;
	kinHists->Fill(&(electron.at(i)));
      //std::cout<<"in Fill Electron Method: 2"<<std::endl;
        robustLooseId->Fill(electron.at(i).isRobustLoose());
        isECalDriven->Fill(electron.at(i).isEcalDrivenSeed());
        isConversion->Fill(electron.at(i).missingHits());
      //std::cout<<"in Fill Electron Method: 3"<<std::endl;
        TightId->Fill(electron.at(i).isTight());
      //std::cout<<"in Fill Electron Method: 4"<<std::endl;
        robustTightId->Fill(electron.at(i).isRobustTight());
      //std::cout<<"in Fill Electron Method: 5"<<std::endl;
//        trackerIso->Fill(electron.at(i).trackerIso(isoCone));
      //std::cout<<"in Fill Electron Method: 6"<<std::endl;
//        ecalIso->Fill(electron.at(i).ecalIso(isoCone));
      //std::cout<<"in Fill Electron Method: 7"<<std::endl;
//        hcalIso->Fill(electron.at(i).hcalIso(isoCone));
      //std::cout<<"in Fill Electron Method: 8"<<std::endl;
//        caloIso->Fill((electron.at(i).hcalIso(isoCone)+electron.at(i).ecalIso(isoCone)));
      //std::cout<<"in Fill Electron Method: 9"<<std::endl;
        relTrkIso->Fill(((double)electron.at(i).trackerIso(isoCone)/(double)electron.at(i).Pt()));
      //std::cout<<"in Fill Electron Method: 10"<<std::endl;
        relCaloIso->Fill(((double)(electron.at(i).ecalIso(isoCone)+electron.at(i).hcalIso(isoCone))/(double)electron.at(i).Pt()));
      //std::cout<<"in Fill Electron Method: 11"<<std::endl;
        relativeIso->Fill(((double)(electron.at(i).ecalIso(isoCone)+electron.at(i).hcalIso(isoCone)+electron.at(i).trackerIso(isoCone))/(double)electron.at(i).Pt()));
      //std::cout<<"in Fill Electron Method: 12"<<std::endl;
        D0->Fill(electron.at(i).d0());//WRT BeamSpot
      //std::cout<<"in Fill Electron Method: 13"<<std::endl;
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
        LooseId->Fill(electron.at(i).isLoose());
        delVePV->Fill(fabs(electron.at(i).vz() - zPV));
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
	robustLooseId->Write();
        TightId->Write();
        robustTightId->Write();
        isECalDriven->Write();
        isConversion->Write();
//        trackerIso->Write();
//        ecalIso->Write();
//        hcalIso->Write();
//        caloIso->Write();
        relTrkIso->Write();
        relCaloIso->Write();
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

	delVePV->Write();
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
  TH1D * LooseId;
  TH1D * robustLooseId;
  TH1D * TightId;
  TH1D * robustTightId;
//  TH1D * trackerIso;
//  TH1D * ecalIso;
//  TH1D * hcalIso;
//  TH1D * caloIso;
  TH1D * relTrkIso;
  TH1D * relCaloIso;
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

  TH1D * delVePV;
  TH1D * DCot;
  TH1D * Dist;

  TH1D * isECalDriven;
  TH1D * isConversion;

  TH2D * DcotDist;

  KinematicHists<TRootElectron> * kinHists;  
  std::string Name;
  bool  forSecond;
  TH1D * zMass;
  TH1D * nGoodElectrons;

};
#endif

