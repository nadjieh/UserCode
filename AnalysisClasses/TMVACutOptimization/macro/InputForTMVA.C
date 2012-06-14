#include <string>
#include <vector>
#include <iostream>

#include "TFile.h"
#include "TTree.h"
using namespace std;



TFile * out;
TTree * sigTree;
TTree * bkgTree;
float TopBottomInvMass;
float MET;
float MT;
float DPhiTopSecondBottom;
float DOmegaTopSecondBottom;

std::vector<std::pair<string,bool> > inputNameType;
void SetSignalBkgTree(){
  if (out == NULL){
    std::cout<<"File is not valid"<<endl;
    return;
  }
  out = new TFile("InputForMVA.root","recreate");
  sigTree = new TTree("Signal","s-channel signal info");
  sigTree->Branch("MET",&MET,"MET/F");
  sigTree->Branch("MT",&MT,"MT/F");
  sigTree->Branch("TopBottomInvMass",&TopBottomInvMass,"TopBottomInvMass/F");
  //add other mass variables
  sigTree->Branch("DPhiTopSecondBottom",&DPhiTopSecondBottom,"DPhiTopSecondBottom/F");
  sigTree->Branch("DOmegaTopSecondBottom",&DOmegaTopSecondBottom,"DOmegaTopSecondBottom/F");
  //add whatever angle you want
  /*Other high level variables*/
    
  bkgTree = new TTree("Background","backgrounds to s-channel info");
  bkgTree->Branch("MET",&MET,"MET/F");
  bkgTree->Branch("MT",&MT,"MT/F");
  bkgTree->Branch("TopBottomInvMass",&TopBottomInvMass,"TopBottomInvMass/F");
  //add other mass variables
  bkgTree->Branch("DPhiTopSecondBottom",&DPhiTopSecondBottom,"DPhiTopSecondBottom/F");
  bkgTree->Branch("DOmegaTopSecondBottom",&DOmegaTopSecondBottom,"DOmegaTopSecondBottom/F");
  //add whatever angle you want
  /*Other high level variables*/
    
  /*NOTE:
   * You may add different background trees, one for ttbar, one for W+jets, etc. It will be like:
   * TTbkgTree = new TTree("TTBackground","tt backgrounds to s-channel info");
   * WbkgTree = new TTree("WBackground","WJets backgrounds to s-channel info");
   * and you have to add same branches for to each tree
   */
    
    
}
void setInputNameType(){
  /*input file info is set here
   * true: signal, false: background
   * in case you have different bkgs, make a pair of name and string which indicates the type of background:
   * std::vector<std::pair<string,string> > inputNameType;
   * inputNameType.push_back(make_pair("a/b/c/d/X.root","tt"));
   * inputNameType.push_back(make_pair("a/b/c/d/Y.root","WJet"));
   */
  inputNameType.push_back(make_pair("a/b/c/d/X.root",true));
  inputNameType.push_back(make_pair("a/b/c/d/Y.root",false));
}
void Analysis_EventSelection( std::string inputName, bool isSignal){
  /* step1: we open an input toptree file with the name of inputName
   * step2: we apply event selection
   * step3: for selected event, we calculate the variables introduced at the beginning, like  TopBottomInvMass
   * , etc.
   * step4: if the file is from signal sample, we fill the signal tree and if not, the bkgTree is filled.
   */ 
  //step 4
  if(isSignal)
    sigTree->Fill();
  else
    bkgTree->Fill();
        
}

void Analysis(){
  /* The Analysis_EventSelection is applied on all input files to fill the trees */
  for(unsigned int i = 0; i<inputNameType.size();i++){
    Analysis_EventSelection( inputNameType.at(i).first,inputNameType.at(i).second);
  }
    
}

void EndJob(){
  /*here we store trees in a file
   * this file will be given to tmva at the end.
   */
  out->cd();
  sigTree->Write();
  bkgTree->Write();
  out->Write();
  out->Close();
}


int main(){
  /*now we call our methods in order*/
  setInputNameType();
  SetSignalBkgTree();
  Analysis();
  EndJob();
  return 1;
}
