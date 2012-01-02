
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
  JetHists(std::string name):Name(name){
    N90 = new TH1D((Name+"_N90").c_str(),(Name+"_N90").c_str(),30,0.,30.);
    N90->GetXaxis()->SetTitle("N90");
    emFraction = new TH1D((Name+"_emFraction").c_str(),(Name+"_emFraction").c_str(),100,-1.2,1.2);
    emFraction->GetXaxis()->SetTitle("emFraction");
    NCaloTowers = new TH1D((Name+"_NCaloTowers").c_str(),(Name+"_NCaloTowers").c_str(),50,0.,100.);
    NCaloTowers->GetXaxis()->SetTitle("NCaloTowers");
    fHPD = new TH1D((Name+"_fHPD").c_str(),(Name+"_fHPD").c_str(),100,-1.2,1.2);
    fHPD->GetXaxis()->SetTitle("fHPD");
    TCHE = new TH1D((Name+"_TCHE").c_str(),(Name+"_TCHE").c_str(),100,-400.,100.);//
    TCHE->GetXaxis()->SetTitle("TrackCountingHighEfficiency");
    TCHP = new TH1D((Name+"_TCHP").c_str(),(Name+"_TCHP").c_str(),100,-300.,100.);
    TCHP->GetXaxis()->SetTitle("TrackCountingHighPurity");
    SMNIP = new TH1D((Name+"_SMNIP").c_str(),(Name+"_SMNIP").c_str(),100,-10000.,20000.);
/*    SMNIP->GetXaxis()->SetTitle("softMuonByIP3dBJetTags");
    SM = new TH1D((Name+"_SM").c_str(),(Name+"_SM").c_str(),100,-1.,1.6);//
    SM->GetXaxis()->SetTitle("softMuonBJetTags");
    SMPt = new TH1D((Name+"_SMPt").c_str(),(Name+"_SMPt").c_str(),100,0.,450);//
    SMPt->GetXaxis()->SetTitle("softMuonByPtBJetTags");*/
    //SE = new TH1D((Name+"_SE").c_str(),(Name+"_SE").c_str(),1000,-150.,60.);
    //SE->GetXaxis()->SetTitle("softElectronBJetTags");
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

    kinHists = new KinematicHists<TRootJet>(Name);
  };
  virtual ~JetHists(){};
  virtual void Fill(std::vector<TRootCaloJet>  jet, int nGJ = 0, int nGBJ = 0, bool atBlevel = false){
	int n = 0;
	if(!atBlevel)
		n = jet.size();
	else
		n = 4;
//        cout<<"\tn: "<<n<<endl;
        for(int i = 0; i<n; i++){
	//cout<<"\ti: "<<i<<endl;
	N90->Fill(jet.at(i).n90());
        emFraction->Fill(jet.at(i).ecalEnergyFraction());
        NCaloTowers->Fill(jet.at(i).nConstituents());
        fHPD->Fill(jet.at(i).fHPD());
        
        TCHE->Fill(jet.at(i).btag_trackCountingHighEffBJetTags());
        TCHP->Fill(jet.at(i).btag_trackCountingHighPurBJetTags());
/*        SMNIP->Fill(jet.at(i).btag_softMuonByIP3dBJetTags());
        SM->Fill(jet.at(i).btag_softMuonBJetTags());
	SMPt->Fill(jet.at(i).btag_softMuonByPtBJetTags());*/
//        SE->Fill(jet.at(i).btag_softElectronBJetTags());
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
  virtual void WriteAll(TDirectory * dir){
        if(dir == 0)
          return;        
        TDirectory * my_dir = dir->mkdir((Name+"_Jet").c_str());
	my_dir->cd();
	N90->Write();
        emFraction->Write();
        NCaloTowers->Write();
        fHPD->Write();
        Et->Write();
        TCHE->Write();
        TCHP->Write();
        SMNIP->Write();
        SM->Write();
//        SE->Write();
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
  TH1D * SMNIP;
  TH1D * SM;
  TH1D * SMPt;
//  TH1D * SE;
  TH1D * SSVHE; 
  TH1D * SSVHP;
  TH1D * JP;
  TH1D * JBP;
  TH1D * CSVMVA;
  TH1D * CSV;
  TH1D * Et;
  TH1D * nGoodJets;
  TH1D * nGoodBJets; 
  KinematicHists<TRootJet> * kinHists;  

  std::string Name;
};
#endif

