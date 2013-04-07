/*                                                                                                                                              
 * File:   PVHists.h                                                                                                                     
 * Author: ajafari                                                                                                                              
 *                                                                                                                                              
 * Created on November 29, 2009, 8:55 PM                                                                                                        
 */

#ifndef _PVHISTS_H
#define _PVHISTS_H

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
#include "../../../TopBrussels/TopTreeProducer/interface/TRootVertex.h"
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

class PVHists{
 public:
  PVHists(std::string name, bool sumw2 = false):Name(name),setSumW2(sumw2){ 
    rho = new TH1D((Name+"_Rho").c_str(), (Name+"_Rho").c_str(), 100,0.,10.);
    rho->GetXaxis()->SetTitle("#rho");
    z = new TH1D((Name+"_z").c_str(),( Name+"_z").c_str(), 50,0.,50.);
    z->GetXaxis()->SetTitle("Z");
    ndof = new TH1D((Name+"_ndof").c_str(),( Name+"_ndof").c_str(), 150,0.,300.);
    ndof->GetXaxis()->SetTitle("ndof");
    isFake = new TH1D((Name+"_isFake").c_str(),( Name+"_isFake").c_str(), 2,0.,2.);
    isFake->GetXaxis()->SetTitle("isFake");
    nGPV = new TH1D((Name+"_nGPV").c_str(),( Name+"_nGPV").c_str(), 200,0.,200.);
    nGPV->GetXaxis()->SetTitle("nGPV");
    if(setSumW2){
        rho->Sumw2();
        z->Sumw2();
        ndof->Sumw2();
        isFake->Sumw2();
        nGPV->Sumw2();
    }
  };
  virtual ~PVHists(){};
  virtual void Fill(std::vector<TRootVertex> pvs, int nGpv = 10.,double weight=1){
	for(unsigned int i = 0; i<pvs.size(); i++){
		TRootVertex pv = pvs.at(i);
		double Rho = sqrt((pv.x() * pv.x()) + (pv.y() * pv.y()));
	        rho->Fill(Rho,weight);
      //std::cout<<"in Fill Electron Method: 3"<<std::endl;
	        z->Fill(fabs(pv.z()),weight);
      //std::cout<<"in Fill Electron Method: 4"<<std::endl;
        	ndof->Fill(pv.ndof(),weight);
      //std::cout<<"in Fill Electron Method: 5"<<std::endl;
	        isFake->Fill(pv.isFake(),weight);
	}
	nGPV->Fill(nGpv,weight);
     
  };
  virtual void WriteAll(TDirectory * dir){
        if (dir == 0)
            return;
        TDirectory* my_dir = dir->mkdir((Name+"_PrimaryVertex").c_str());
        my_dir->cd();
	rho->Write();
        z->Write();
        ndof->Write();
        isFake->Write();
	nGPV->Write();
        dir->cd();
  };
 private:
  TH1D * rho;
  TH1D * z;
  TH1D * ndof;
  TH1D * isFake;
  TH1D * nGPV;
  std::string Name;
  bool setSumW2;

};
#endif

