
/*                                                                                                                                              
 * File:   JetHists.h                                                                                                                     
 * Author: ajafari                                                                                                                              
 *                                                                                                                                              
 * Created on November 29, 2009, 8:55 PM                                                                                                        
 */

#ifndef _JETHISTS_H
#define _JETHISTS_H

#include <iomanip>
#include "../../../TopBrussels/TopTreeProducer/interface/TRootMuon.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootElectron.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootJet.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootCaloJet.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootPFJet.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootMET.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootGenEvent.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootEvent.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootRun.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootParticle.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootMCParticle.h"
#include <sstream>

#include <TFile.h>
#include <TH1.h>
#include <TH2.h>
#include <TString.h>
#include <TDirectory.h>
#include <TCanvas.h>
#include <TBranch.h>
#include <TTree.h>
#include <TClonesArray.h>
#include <vector>

#include "KinematicHists.h"

using namespace TopTree;
class JetHists{
 public:
  JetHists(std::string name, int type = 1, bool sumw2 = false):Name(name), jetType(type), setsumw2(sumw2){
      if(this->jetType == 1){
        N90 = new TH1D((Name+"_N90").c_str(),(Name+"_N90").c_str(),30,0.,30.);
        N90->GetXaxis()->SetTitle("N90");
        emFraction = new TH1D((Name+"_emFraction").c_str(),(Name+"_emFraction").c_str(),100,-1.2,1.2);
        emFraction->GetXaxis()->SetTitle("emFraction");
        NCaloTowers = new TH1D((Name+"_NCaloTowers").c_str(),(Name+"_NCaloTowers").c_str(),50,0.,100.);
        NCaloTowers->GetXaxis()->SetTitle("NCaloTowers");
        fHPD = new TH1D((Name+"_fHPD").c_str(),(Name+"_fHPD").c_str(),100,-1.2,1.2);
        fHPD->GetXaxis()->SetTitle("fHPD");
      } else if(this->jetType == 2) {
        NCaloTowers = new TH1D((Name+"_NCaloTowers").c_str(),(Name+"_NCaloTowers").c_str(),50,0.,100.);
        NCaloTowers->GetXaxis()->SetTitle("NCaloTowers");
        NEF = new TH1D((Name+"_NEF").c_str(),(Name+"_NEF").c_str(),50,0.,1.);
        NEF->GetXaxis()->SetTitle("NEF");
        NHF = new TH1D((Name+"_NHF").c_str(),(Name+"_NHF").c_str(),50,0.,1.);
        NHF->GetXaxis()->SetTitle("NHF");
        CEF = new TH1D((Name+"_CEF").c_str(),(Name+"_CEF").c_str(),50,0.,1.);
        CEF->GetXaxis()->SetTitle("CEF");
        CHF = new TH1D((Name+"_CHF").c_str(),(Name+"_CHF").c_str(),50,0.,1.);
        CHF->GetXaxis()->SetTitle("CHF");
        NCH = new TH1D((Name+"_NCH").c_str(),(Name+"_NCH").c_str(),50,0.,100.);
        NCH->GetXaxis()->SetTitle("NCH");
          
      }
    TCHE = new TH1D((Name+"_TCHE").c_str(),(Name+"_TCHE").c_str(),100,-400.,100.);//
    TCHE->GetXaxis()->SetTitle("TrackCountingHighEfficiency");
    TCHP = new TH1D((Name+"_TCHP").c_str(),(Name+"_TCHP").c_str(),100,-300.,100.);
    TCHP->GetXaxis()->SetTitle("TrackCountingHighPurity");
    SSVHE = new TH1D((Name+"_SSVHE").c_str(),(Name+"_SSVHE").c_str(),100,-106.,6.);
    SSVHE->GetXaxis()->SetTitle("simpleSecondaryVertexHighEffBJetTags");
    SSVHP = new TH1D((Name+"_SSVHP").c_str(),(Name+"_SSVHP").c_str(),100,-106.,6.);
    SSVHP->GetXaxis()->SetTitle("simpleSecondaryVertexHighPurBJetTags");
    JP = new TH1D((Name+"_JP").c_str(),(Name+"_JP").c_str(),100,0.,7.);//
    JP->GetXaxis()->SetTitle("jetProbabilityBJetTags");
    JBP = new TH1D((Name+"_JBP").c_str(),(Name+"_JBP").c_str(),100,0.,11.);//
    JBP->GetXaxis()->SetTitle("jetBProbabilityBJetTags");
    CSVMVA = new TH1D((Name+"_CSVMVA").c_str(),(Name+"_CSVMVA").c_str(),100,-10.,2.);//
    CSVMVA->GetXaxis()->SetTitle("combinedSecondaryVertexMVABJetTags");
    CSV = new TH1D((Name+"_CSV").c_str(),(Name+"_CSV").c_str(),100,-10.,2.);//
    CSV->GetXaxis()->SetTitle("combinedSecondaryVertexBJetTags");
    Et = new TH1D((Name+"_Et").c_str(),(Name+"_Et").c_str(),50,0.,200.);
    Et->GetXaxis()->SetTitle("Et");    
    nGoodJets =  new TH1D((Name+"_nGoodJets").c_str(),(Name+"_nGoodJets").c_str(),10,0.,10.);
    nGoodJets->GetXaxis()->SetTitle("N_{good jets}");
    nGoodBJets =  new TH1D((Name+"_nGoodBJets").c_str(),(Name+"_nGoodBJets").c_str(),10,0.,10.);
    nGoodBJets->GetXaxis()->SetTitle("N_{good b-jets}");

    kinHists = new KinematicHists<TRootJet>(Name,setsumw2);
    //default is CaloJet=1; PFJet =2;
  };
  virtual ~JetHists(){};
  void setJetType(int type){this->jetType = type;}
  
  virtual void FillCaloJets(std::vector<TRootCaloJet>  jet, int nGJ = 0, int nGBJ = 0, bool atBlevel = false){
	int n = 0;
	if(!atBlevel)
		n = jet.size();
	else
		n = 4;
//        cout<<"\tn: "<<n<<endl;
        for(int i = 0; i<n; i++){
	//cout<<"\ti: "<<i<<endl;
            if(N90 != NULL){
                N90->Fill(jet.at(i).n90());
                emFraction->Fill(jet.at(i).ecalEnergyFraction());
                fHPD->Fill(jet.at(i).fHPD());
            }else if (N90 == NULL){
                cout<<"PF-Calo confusion! ID plots will not be filled ..."<<endl;
            }

            NCaloTowers->Fill(jet.at(i).nConstituents());
            TCHE->Fill(jet.at(i).btag_trackCountingHighEffBJetTags());
            TCHP->Fill(jet.at(i).btag_trackCountingHighPurBJetTags());
            SSVHE->Fill(jet.at(i).btag_simpleSecondaryVertexHighEffBJetTags());
            SSVHP->Fill(jet.at(i).btag_simpleSecondaryVertexHighPurBJetTags());
            JP->Fill(jet.at(i).btag_jetProbabilityBJetTags());
            JBP->Fill(jet.at(i).btag_jetBProbabilityBJetTags());
            CSVMVA->Fill(jet.at(i).btag_combinedSecondaryVertexMVABJetTags());
            CSV->Fill(jet.at(i).btag_combinedSecondaryVertexBJetTags());
        
            Et->Fill(jet.at(i).Et());

//        std::cout<<"in Jet Fill method"<<std::endl;
            kinHists->Fill(&(jet.at(i)));
	}
	nGoodJets->Fill(nGJ);
	nGoodBJets->Fill(nGBJ);
  };
  virtual void Fill(std::vector<TRootCaloJet>  jet, int nGJ = 0, int nGBJ = 0, bool atBlevel = false){this->FillCaloJets(jet,nGJ,nGBJ,atBlevel);}
  
  virtual void FillPFJets(std::vector<TRootPFJet>  jet, int nGJ = 0, int nGBJ = 0, bool atBlevel = false,double weight=1){
	int n = 0;
        //Specific to top-pair analysis: 
	if(!atBlevel)
		n = jet.size();
	else
		n = 4;
        //-------------------------
        for(int i = 0; i<n; i++){
	//cout<<"\ti: "<<i<<endl;

            if(NCH != NULL){
                NCH->Fill(jet.at(i).chargedMultiplicity(),weight);
                NEF->Fill(jet.at(i).neutralEmEnergyFraction(),weight);
                NHF->Fill(jet.at(i).neutralHadronEnergyFraction(),weight);
                CEF->Fill(jet.at(i).chargedEmEnergyFraction(),weight);
                CHF->Fill(jet.at(i).chargedHadronEnergyFraction(),weight);
            }
            else if (NCH == NULL){
                cout<<"PF-Calo confusion! ID plots will not be filled ..."<<endl;
            }
            
            NCaloTowers->Fill(jet.at(i).nConstituents(),weight);


            TCHE->Fill(jet.at(i).btag_trackCountingHighEffBJetTags(),weight);
            TCHP->Fill(jet.at(i).btag_trackCountingHighPurBJetTags(),weight);
            SSVHE->Fill(jet.at(i).btag_simpleSecondaryVertexHighEffBJetTags(),weight);
            SSVHP->Fill(jet.at(i).btag_simpleSecondaryVertexHighPurBJetTags(),weight);
            JP->Fill(jet.at(i).btag_jetProbabilityBJetTags(),weight);
            JBP->Fill(jet.at(i).btag_jetBProbabilityBJetTags(),weight);
            CSVMVA->Fill(jet.at(i).btag_combinedSecondaryVertexMVABJetTags(),weight);
            CSV->Fill(jet.at(i).btag_combinedSecondaryVertexBJetTags(),weight);

            Et->Fill(jet.at(i).Et(),weight);

    //        std::cout<<"in Jet Fill method"<<std::endl;
            kinHists->Fill(&(jet.at(i)),weight);
	}
	nGoodJets->Fill(nGJ,weight);
	nGoodBJets->Fill(nGBJ,weight);
  };
  virtual void WriteAll(TDirectory * dir){
        if(dir == 0)
          return;        
        TDirectory * my_dir = dir->mkdir((Name+"_Jet").c_str());
	my_dir->cd();
        if(this->jetType==1){
            N90->Write();
            emFraction->Write();
            fHPD->Write();
        }else if(this->jetType == 2){
            CEF->Write();
            NEF->Write();
            CHF->Write();
            NHF->Write();
            NCH->Write();
        }
        NCaloTowers->Write();
        Et->Write();
        TCHE->Write();
        TCHP->Write();
        SSVHE->Write();
        SSVHP->Write();
        JP->Write();
        JBP->Write();
        CSVMVA->Write();
        CSV->Write();
        kinHists->Write(); 
	nGoodJets->Write();
	nGoodBJets->Write();
        dir->cd();
  };
 private:
  TH1D * N90;
  TH1D * emFraction;
  TH1D * NCaloTowers;
  TH1D * fHPD;
  TH1D * TCHE;
  TH1D * TCHP;
  TH1D * SSVHE; 
  TH1D * SSVHP;
  TH1D * JP;
  TH1D * JBP;
  TH1D * CSVMVA;
  TH1D * CSV;
  TH1D * Et;
  TH1D * nGoodJets;
  TH1D * nGoodBJets; 
  TH1D * CEF; //chargedEmEnergyFraction()
  TH1D * NHF;//neutralHadronEnergyFraction()
  TH1D * NEF;//neutralEmEnergyFraction()
  TH1D * CHF;//chargedHadronEnergyFraction()
  TH1D * NCH;//chargedMultiplicity()
  KinematicHists<TRootJet> * kinHists;  

  std::string Name;
  int jetType;
  bool setsumw2 ;
};
#endif

