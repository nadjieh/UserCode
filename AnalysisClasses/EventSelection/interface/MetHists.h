/*                                                                                                                                              
 * File:   MetHists.h                                                                                                                     
 * Author: ajafari                                                                                                                              
 *                                                                                                                                              
 * Created on November 29, 2009, 8:55 PM                                                                                                        
 */

#ifndef _METHISTS_H
#define _METHISTS_H

#include <iomanip>
#include "/user/ajafari/CMSSW_3_8_5_patch3/src/TopBrussels/TopTreeProducer/interface/TRootMuon.h"
#include "/user/ajafari/CMSSW_3_8_5_patch3/src/TopBrussels/TopTreeProducer/interface/TRootElectron.h"
#include "/user/ajafari/CMSSW_3_8_5_patch3/src/TopBrussels/TopTreeProducer/interface/TRootJet.h"
#include "/user/ajafari/CMSSW_3_8_5_patch3/src/TopBrussels/TopTreeProducer/interface/TRootMET.h"
#include "/user/ajafari/CMSSW_3_8_5_patch3/src/TopBrussels/TopTreeProducer/interface/TRootGenEvent.h"
#include "/user/ajafari/CMSSW_3_8_5_patch3/src/TopBrussels/TopTreeProducer/interface/TRootSignalEvent.h"
#include "/user/ajafari/CMSSW_3_8_5_patch3/src/TopBrussels/TopTreeProducer/interface/TRootEvent.h"
#include "/user/ajafari/CMSSW_3_8_5_patch3/src/TopBrussels/TopTreeProducer/interface/TRootRun.h"
#include "/user/ajafari/CMSSW_3_8_5_patch3/src/TopBrussels/TopTreeProducer/interface/TRootParticle.h"
#include "/user/ajafari/CMSSW_3_8_5_patch3/src/TopBrussels/TopTreeProducer/interface/TRootMCParticle.h"
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

class MetHists{
 public:
  MetHists(std::string name):Name(name){ 
    kinHists = new KinematicHists<TRootMET>(Name);
  };
  virtual ~MetHists(){};
  virtual void Fill(TRootMET * MET){
	kinHists->Fill(MET);
  };
  virtual void WriteAll(TDirectory * dir){
        if(dir == 0)
          return;
        TDirectory * my_dir = dir->mkdir((Name+"_MET").c_str());
	my_dir->cd();
       
        kinHists->Write(); 
        dir->cd();
  };
 private:
  KinematicHists<TRootMET> * kinHists;  
  std::string Name;

};
#endif

