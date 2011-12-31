/* 
 * File:   SelectAndSave.c
 * Author: ajafari
 *
 * Created on August 6, 2010, 8:18 PM
 */

#include <stdio.h>
#include <stdlib.h>

//#include "../interface/Cut.h"
//#include "../interface/Cut.h"
#include "../interface/ElectronSelector.h"

#include "../interface/Event.h"
//#include "../interface/EventsHists.h"
#include "../interface/ElectronHists.h"
#include "../interface/MuonHists.h"
#include "../interface/PVHists.h"
#include "../interface/JetHists.h"
#include "../interface/JetSelector.h"
#include "../interface/MuonVetoSelector.h"
//#include "../interface/NoSelection.h"
#include "../interface/PrimaryVertexSelector.h"
#include "../interface/EventSelector.h"
#include <iomanip>
#include "/user/ajafari/CMSSW_3_8_5_patch3/src/TopBrussels/TopTreeProducer/interface/TRootMuon.h"
#include "/user/ajafari/CMSSW_3_8_5_patch3/src/TopBrussels/TopTreeProducer/interface/TRootElectron.h"
#include "/user/ajafari/CMSSW_3_8_5_patch3/src/TopBrussels/TopTreeProducer/interface/TRootJet.h"
#include "/user/ajafari/CMSSW_3_8_5_patch3/src/TopBrussels/TopTreeProducer/interface/TRootCaloJet.h"
#include "/user/ajafari/CMSSW_3_8_5_patch3/src/TopBrussels/TopTreeProducer/interface/TRootMET.h"
#include "/user/ajafari/CMSSW_3_8_5_patch3/src/TopBrussels/TopTreeProducer/interface/TRootGenEvent.h"
#include "/user/ajafari/CMSSW_3_8_5_patch3/src/TopBrussels/TopTreeProducer/interface/TRootNPGenEvent.h"
#include "/user/ajafari/CMSSW_3_8_5_patch3/src/TopBrussels/TopTreeProducer/interface/TRootSignalEvent.h"
#include "/user/ajafari/CMSSW_3_8_5_patch3/src/TopBrussels/TopTreeProducer/interface/TRootEvent.h"
#include "/user/ajafari/CMSSW_3_8_5_patch3/src/TopBrussels/TopTreeProducer/interface/TRootRun.h"
#include "/user/ajafari/CMSSW_3_8_5_patch3/src/TopBrussels/TopTreeProducer/interface/TRootParticle.h"
#include "/user/ajafari/CMSSW_3_8_5_patch3/src/TopBrussels/TopTreeProducer/interface/TRootMCParticle.h"
#include "/user/ajafari/CMSSW_3_8_5_patch3/src/TopBrussels/TopTreeProducer/interface/TRootVertex.h"
#include "/user/ajafari/CMSSW_3_8_5_patch3/src/TopBrussels/TopTreeProducer/interface/TRootHLTInfo.h"
#include "/user/ajafari/CMSSW_3_8_5_patch3/src/AnalysisClasses/EventSelection/interface/PracticalEvent.h"
#include "/user/ajafari/CMSSW_3_8_5_patch3/src/AnalysisClasses/EventSelection/interface/EventPropertiesHist.h"



#include <sstream>
#include <string>

#include <TFile.h>
#include <TH1.h>
#include <TH2.h>
#include <TCanvas.h>
#include <TBranch.h>
#include <TTree.h>
#include <vector>

using namespace std;
using namespace TopTree;
//EventHists sas_beforSelection("beforSelection");
//EventHists sas_HLT("HLTSelection");

PVHists sas_atLeastOnGPV("before_PV_selection");
ElectronHists sas_ExactlyOneGESelection("before_GE_selection");
MuonHists sas_MuVetoSelection("before_MuVeto_selection");
ElectronHists sas_zVetoHits("before_zVeto_Selection",3,true);
ElectronHists sas_MissingHits("before_MissingHits_Selection");
ElectronHists sas_PartnerTrack("before_PartnerTrack_selection");
JetHists sas_Jets("before_Jet_selection");


JetHists sas_BJets("before_BJet_selection");
ElectronHists sas_AllFinalElectrons("before_BJet_AllFinalElec");
ElectronHists sas_GoldenFinalElectrons("before_BJet_GoldenFinalElec");
EventPropertiesHist sas_evtProps_Final("before_BJet_eventProperties");
EventPropertiesHist sas_evtProps("before_GE_eventProperties");
PVHists sas_PV_Final("before_BJet_PrimaryVertex");


/*EventHists sas_Zveto("Zveto");
EventHists sas_ConversionRejection("ConversionRejection");
EventHists sas_AtLeastFourJetsSelection("AtLeastFourJets");
EventHists sas_MetSelection("sas_MetSelection");
EventHists sas_MuonVeto("sas_MuonVeto");
EventHists sas_PassedBtagSelection("PassedBtag");
*/


int sas_n0;
int sas_nHlt;
bool sas_doHLT;
int sas_nPV;
bool sas_doPV;
int sas_nLeatsOneGE;
bool sas_doElectron;
int sas_nExactOneGE;
int sas_nNoMu;
bool sas_doMuon;
int sas_nNoLE;
bool sas_doSecondE;
int sas_nConv_a;
int sas_nConv_b;
int  sas_nConv;
bool sas_doConv;
bool sas_doEcalDriven;
int sas_nEcalDriven;
int sas_nJet;
int sas_nJet3;
bool sas_dojet;
int sas_nBtag;
bool sas_doBtag;
bool sas_doZveto;
int sas_nZveto;
bool sas_doMET;
int sas_nMET;
double XSec;
double Luminosity;
double PreSelEff;

bool isData;

bool isTtBar;
bool isSignal;

int sas_verbosity;
int n_beforescrap;
bool fillTree;
TFile * sas_out;
TTree * eventTree_f;
TH1D * M3;
TH1D * HT;
TH1D * nTrackRatio;
TH1D * met;
std::vector<std::string> sas_inputFileNames;
std::string sas_outFileName;
std::string sas_plotFileName;
std::string sas_outFileName_FullSelection;

void beginJob(){
     sas_n0 = 0;
     sas_nHlt = 0;
     sas_doHLT = false;
     sas_nPV = 0;
     sas_doPV = true;//
     sas_nLeatsOneGE = 0;
     sas_doElectron = true;//
     sas_nExactOneGE = 0;
     sas_nNoMu = 0;
     sas_doMuon = true;//
     sas_doZveto = true;//
     sas_nZveto = 0;
     sas_nNoLE = 0;
     sas_doSecondE = false;
     sas_nConv_a= 0;
     sas_nConv_b= 0;
     sas_doConv = true;//
     sas_nEcalDriven = 0;
     sas_doEcalDriven =false;
     sas_nJet= 0;
     sas_nJet3 = 0;
     sas_dojet = true;//
     sas_nBtag= 0;
     sas_doBtag = false;//
     sas_verbosity = 0;
     fillTree = false;//
     n_beforescrap = 0;
     sas_nMET = 0;
     sas_doMET = true;//
     //isData = false;
     //inputFileNames.clear();
}



void endJob(){
    TFile * plots = new TFile(sas_plotFileName.c_str(),"recreate");
    TH1D * CutFlowHist = new TH1D("CutFlow","",10,0,10);
    CutFlowHist->GetXaxis()->SetBinLabel(1,"Initial");
    CutFlowHist->GetXaxis()->SetBinLabel(2,"primaryVertex");
    CutFlowHist->GetXaxis()->SetBinLabel(3,"goodElectron");
    CutFlowHist->GetXaxis()->SetBinLabel(4,"muonVeto");
    CutFlowHist->GetXaxis()->SetBinLabel(5,"Zveto");
    CutFlowHist->GetXaxis()->SetBinLabel(6,"conversion");
    CutFlowHist->GetXaxis()->SetBinLabel(7,">= 3 jets");
    CutFlowHist->GetXaxis()->SetBinLabel(8,">= 4 jets");
    CutFlowHist->GetXaxis()->SetBinLabel(9,"MET>30 ");

    CutFlowHist->SetBinContent(1,sas_n0);
    CutFlowHist->SetBinContent(2,sas_nPV);
    CutFlowHist->SetBinContent(3,sas_nExactOneGE);
    CutFlowHist->SetBinContent(4,sas_nNoMu);
    CutFlowHist->SetBinContent(5,sas_nZveto);
    CutFlowHist->SetBinContent(6,sas_nConv_b);
    CutFlowHist->SetBinContent(7,sas_nJet3);
    CutFlowHist->SetBinContent(8,sas_nJet);
    CutFlowHist->SetBinContent(9,sas_nMET);



    plots->cd();
    if(sas_doPV){
        CutFlowHist->Write();
        sas_atLeastOnGPV.WriteAll(plots);
    }
    sas_evtProps.WriteAll(plots);
    if(sas_doElectron)
        sas_ExactlyOneGESelection.WriteAll(plots);
    if(sas_doMuon)
        sas_MuVetoSelection.WriteAll(plots);
    if(sas_doZveto)
        sas_zVetoHits.WriteAll(plots);
    if(sas_doConv){
        sas_MissingHits.WriteAll(plots);
        sas_PartnerTrack.WriteAll(plots);
    }
    if(sas_dojet)
        sas_Jets.WriteAll(plots);
    if(sas_doBtag){
        sas_BJets.WriteAll(plots);
        sas_AllFinalElectrons.WriteAll(plots);
        sas_GoldenFinalElectrons.WriteAll(plots);
        sas_evtProps_Final.WriteAll(plots);
	sas_PV_Final.WriteAll(plots);
        plots->cd();
        M3->Write();
        HT->Write();
	nTrackRatio->Write();
    }
    if(sas_doMET)
	met->Write();

/*    sas_beforSelection.WriteAll(plots);
    sas_atLeastOnGPV.WriteAll(plots);
    sas_ExactlyOneGESelection.WriteAll(plots);
    sas_MuonVeto.WriteAll(plots);
    sas_Zveto.WriteAll(plots);
    sas_ConversionRejection.WriteAll(plots);
*/
    plots->Write();
    plots->Close();
    double intialBeforePresel = (double)sas_n0/(double)PreSelEff;
    double weight = (double)(XSec*Luminosity)/(double)intialBeforePresel;
    cout<<"Cut flow in "<<Luminosity<<" pb-1 , Weight is "<<weight<<endl;
    cout<<"\tInitial:\t"<<XSec*Luminosity<<"|\t"<<1.<<endl;
    cout<<"\tPreSele:\t"<<sas_n0*weight<<"|\t"<<PreSelEff<<endl;
    cout<<"\tPVertex:\t"<<sas_nPV*weight<<"|\t"<<(double)sas_nPV/(double)sas_n0<<endl;
    if(sas_doPV)
        cout<<"\t>= 1 GE:\t"<<sas_nLeatsOneGE*weight<<"|\t"<<(double)sas_nLeatsOneGE/(double)sas_nPV<<endl;
    else
        cout<<"\t>= 1 GE:\t"<<sas_nLeatsOneGE*weight<<"|\t"<<(double)sas_nLeatsOneGE/(double)sas_n0<<endl;
    cout<<"\t== 1 GE:\t"<<sas_nExactOneGE*weight<<"|\t"<<(double)sas_nExactOneGE/(double)sas_nLeatsOneGE<<endl;
    cout<<"\t!ConvGE:\t"<<sas_nConv*weight<<"|\t"<<(double)sas_nConv/(double)sas_nExactOneGE<<endl;
    if(sas_doConv)
        cout<<"\t!2'ndLE:\t"<<sas_nNoLE*weight<<"|\t"<<(double)sas_nNoLE/(double)sas_nConv<<endl;
    else
	cout<<"\t!2'ndLE:\t"<<sas_nNoLE*weight<<"|\t"<<(double)sas_nNoLE/(double)sas_nExactOneGE<<endl;
    cout<<"\t !LMuon:\t"<<sas_nNoMu*weight<<"|\t"<<(double)sas_nNoMu/(double)sas_nNoLE<<endl;
    cout<<"\t>=4GJet:\t"<<sas_nJet*weight<<"|\t"<<(double)sas_nJet/(double)sas_nNoMu<<endl;
    cout<<"\t>=1BJet:\t"<<sas_nBtag*weight<<"|\t"<<(double)sas_nBtag/(double)sas_nJet<<endl;

    cout<<"\t"<<XSec*Luminosity<<"\t"<<sas_n0*weight<<"\t"<<sas_nPV*weight<<"\t"<<sas_nLeatsOneGE*weight<<"\t"<<sas_nExactOneGE*weight
            <<"\t"<<sas_nConv*weight<<"\t"<<sas_nEcalDriven*weight<<"\t"<<sas_nNoLE*weight<<"\t"<<sas_nNoMu*weight<<"\t"<<sas_nJet*weight<<"\t"<<sas_nBtag*weight<<endl;
    cout<<"\n"<<XSec*Luminosity<<"\n"<<sas_n0*weight<<"\n"<<sas_nPV*weight<<"\n"<<sas_nLeatsOneGE*weight<<"\n"<<sas_nExactOneGE*weight
            <<"\n"<<sas_nConv*weight<<"\n"<<sas_nNoLE*weight<<"\n"<<sas_nNoMu*weight<<"\n"<<sas_nJet*weight<<"\n"<<sas_nBtag*weight<<endl;

    cout<<"\n"<<intialBeforePresel<<"\n"<<n_beforescrap<<"\n"<<sas_n0<<"\n"<<sas_nPV<<"\n"<<sas_nLeatsOneGE<<"\n"<<sas_nExactOneGE<<"\n"<<sas_nNoMu<<"\n"<<sas_nZveto
            <<"\n"<<sas_nConv_a<<"\n"<<sas_nConv_b<<"\n"<<sas_nJet3<<"\n"<<sas_nJet<<"\n"<<sas_nBtag<<endl;
    cout<<sas_nMET<<endl;

}

int main(int argc, char** argv){
//    sleep(60);
    isTtBar = true;
    isSignal = true;
    double doJES = 1.;
    for (int f = 1; f < argc; f++) {
        std::string arg_fth(*(argv + f));

        if (arg_fth == "out") {
          f++;
          std::string out(*(argv + f));
          sas_outFileName_FullSelection = out;
	  sas_plotFileName = "Histograms_"+out;
	  sas_plotFileName = out;
        }else if (arg_fth == "input") {
          f++;
          std::string in(*(argv + f));
          sas_inputFileNames.push_back(string("~/"+in));
//          sas_inputFileNames.push_back(string("~/"+in));
        }else if(arg_fth == "XSec"){
          f++;
          std::string Xsec(*(argv + f));
          XSec = atof(Xsec.c_str());
        }else if(arg_fth == "Lumi"){
          f++;
          std::string Lumi(*(argv + f));
          Luminosity = atof(Lumi.c_str());
        }else if(arg_fth == "preSelEff"){
          f++;
          std::string preSelEff(*(argv + f));
          PreSelEff = atof(preSelEff.c_str());
        }else if (arg_fth == "JES") {
            f++;
            std::string in(*(argv + f));
           doJES = atof(in.c_str());
        }else if (arg_fth == "isData") {
            f++;
            std::string in(*(argv + f));
//	    cout<<in<<endl;
            if(in == "yes" || in == "YES" || in == "Yes" || in == "y" || in == "Y")
		isData = true;
	    else
		isData = false;
//	    cout<<"1- "<<isData<<endl;
        }
    }
    M3 = new TH1D("M3","",100,0.,500);
    M3->GetXaxis()->SetTitle("M3");
    HT = new TH1D("HT","",100,0.,1000);
    HT->GetXaxis()->SetTitle("H_{T}");
    nTrackRatio = new TH1D("nTrackRatio","",100,0.,1.);
    nTrackRatio->GetXaxis()->SetTitle("High Purity track content of event");
    met = new TH1D("MET","",1000,0.,500.);
    met->GetXaxis()->SetTitle("missing transverse energy");

//    cout<<"2- "<<isData<<endl;
    cout<<doJES<<endl;
    cout << sas_inputFileNames.at(0).c_str() << endl;
    //     cout << "----------------------" << endl;

    TFile* f = 0;

    beginJob();
    //cout<<sas_inputFileNames.size()<<endl;

    for(unsigned int fNumber = 0; fNumber<sas_inputFileNames.size(); fNumber++){
    //cout<< "Before openning "<<fNumber<<"'th file: "<<endl;
    
    f = TFile::Open(sas_inputFileNames.at(fNumber).c_str());

    TTree* runTree = (TTree*) f->Get("runTree");
    TTree* eventTree = (TTree*) f->Get("eventTree");
    //cout<<"Tree is got"<<endl;
    PracticalEvent * pracEvt = new PracticalEvent(eventTree,runTree,true);
    pracEvt->eventTree->SetBranchStatus("*", 1);
    //    eventTree->SetBranchStatus("GenEvent", 1);

    if(fillTree ){
	stringstream s("");
	s<<(fNumber+1)<<"_"<<sas_outFileName_FullSelection;
        sas_out = new TFile(s.str().c_str(), "recreate");
        sas_out->cd();
        eventTree_f = pracEvt->eventTree->CloneTree(0);
    }

    std::cout<<"beforeLoop"<<std::endl;
    //	nEvents = 10000;
   int ievt = 0;
   bool onepassed = false;
    while (pracEvt->Next()) {
	ievt++;
//	if(ievt > 1000)
//	     break;
        
//cout<<ievt<<"        //////////////////////////////////"<<endl;
	//Step 0: Correct the jets
	//////////////////////////////////
	if(sas_verbosity > 0){
            cout<<"JES: "<<doJES<<endl;
        }
        std::vector<TRootCaloJet>  myJets_;
        myJets_.clear();
        //cout<<"I am going to Jet Correction "<<isData<<endl;
        myJets_ = pracEvt->ScaledJetCollection(doJES,isData);
	//cout<<"Correction is done\n\t"<<myJets_.at(0).Pt()<<endl;
        n_beforescrap++;
       //if(tevt == NULL ){
//	   cout<<"Hell"<<endl;
//	   return 0;
//	}
        if(isData){
        	bool isBeamBG = true;
        	float nTrk = ( (float) (pracEvt->Event()->nTracks()) );
        	float nPureTrk  = ( (float)  (pracEvt->Event()->nHighPurityTracks()) );
       //cout<<"SCRAPPING: "<<nTrk<<endl;
       		if(nTrk > 10)
       		{
         		if( ( (float) nPureTrk ) / ( (float)nTrk ) > 0.25 )
           		isBeamBG = false;
       		}
       		nTrackRatio->Fill(( (float) nPureTrk ) / ( (float)nTrk ));
       		if(isBeamBG) {
         		continue;
        	}
	}
        Event myEvent_tmp( myJets_, *pracEvt->ElectronCollection(),*pracEvt->METCollection(),*pracEvt->MuonCollection(),*pracEvt->VertexCollection());
        myEvent_tmp.verbose(sas_verbosity);
        if(sas_verbosity > 0)
            cout<<"Vertex Makers ---------------------------------------------------------------------"<<endl;
//        if(sas_doPV)
            myEvent_tmp.VertexMaker();
        if(sas_verbosity > 0)
            cout<<"Electron Maker ---------------------------------------------------------------------"<<endl;
        myEvent_tmp.ElectronMaker(/*pt*/30.,/*ets*/2.5,/*ExLow*/1.4442,/*Exc_High*/1.5660,
                /*Id */"VBTF70",/*IdSecond*/"VBTF95",/*Iso*/"",/*D0*/0.02,/*IsoCut*/0.1,
		/*drToPV*/1.,/*secondEIso*/1.);
        if(sas_verbosity > 0)
            cout<<"Jet Cleaning  ---------------------------------------------------------------------"<<endl;
        myEvent_tmp.JetCleaning();
        if(sas_verbosity > 0)
            cout<<"Jet Makers ---------------------------------------------------------------------"<<endl;
        myEvent_tmp.JetMaker(/*bTagAlgo*/"TCHE",/*pt*/30.,/*eta*/2.4,/*nCaloTower*/0,/*EmfUp*/1000.,/*EmfLow*/0.01,/*fhpd_*/0.98,
                /*N90_*/1.,/*bTagCut_*/4.);
        if(sas_verbosity > 0)
            cout<<"Muon Maker ---------------------------------------------------------------------"<<endl;
        myEvent_tmp.MuonMaker(/*pt*/10.,/*eta*/2.5,/*chi2*/100000.,/*D0*/1000.,/*nvh*/-1,/*isoCut_*/0.2,/*doGL*/true);
        if(sas_verbosity > 0)
            cout<<"START TO SELECT : "<<endl;
//                sas_beforSelection.Fill(myEvent_tmp);
        sas_n0++;
        if(sas_doPV){
            sas_atLeastOnGPV.Fill(myEvent_tmp.pvs,myEvent_tmp.Gpvs.size());
            if(myEvent_tmp.Gpvs.size() > 0){
                sas_nPV++;
                if(sas_verbosity > 0)
                    cout<<"\tPVCut Passed"<<endl;
            } else
                continue;
        }
	sas_evtProps.Fill(pracEvt->Event());
        if(sas_doElectron){
	    TLorentzVector ge(-1,-1,-1,-1);
            sas_ExactlyOneGESelection.Fill(myEvent_tmp.electrons,ge,myEvent_tmp.Gpvs.at(0).z(),myEvent_tmp.Gelectrons.size());
            if(myEvent_tmp.Gelectrons.size() != 0){
                sas_nLeatsOneGE++;
//                        sas_atleastOneGESelection.Fill(myEvent_tmp);
                if(sas_verbosity > 0)
                    cout<<"\tLeatsOneGE Passed"<<endl;
            } else
                continue;
            if(myEvent_tmp.Gelectrons.size() == 1){
                sas_nExactOneGE++;
                if(sas_verbosity > 0)
                    cout<<"\tExactOneGE Passed"<<endl;
            } else
                continue;
        }
        if(sas_doMuon){
	    sas_MuVetoSelection.Fill(myEvent_tmp.muons,myEvent_tmp.Dmuons.size());
            if(myEvent_tmp.Dmuons.size() == 0){
                sas_nNoMu++;
                if(sas_verbosity > 0)
                    cout<<"\tMu veto Passed"<<endl;
            } else
                continue;
        }
	if(sas_doZveto){
	    int nPair = 0;
	    bool vetoPass = myEvent_tmp.isZVetoPassed(nPair,76.,106.);
	    sas_zVetoHits.Fill(myEvent_tmp.Secondelectrons,(TLorentzVector)(myEvent_tmp.Gelectrons.at(0)),myEvent_tmp.Gpvs.at(0).z(),nPair);
	    if(vetoPass){
		sas_nZveto++;
		if(sas_verbosity > 0)
		    cout<<"\tZVeto is passed"<<endl;
	    }else 
		continue;
	}
        if(sas_doConv){
	   sas_MissingHits.Fill(myEvent_tmp.Gelectrons,(TLorentzVector)(myEvent_tmp.Gelectrons.at(0)),myEvent_tmp.Gpvs.at(0).z());
            //if(!myEvent_tmp.Gelectrons.at(0).isFromConversion()){
	    if(myEvent_tmp.Gelectrons.at(0).missingHits() == 0){
                sas_nConv_a++;
                if(sas_verbosity > 0)
                    cout<<"\tConversion_a Passed"<<endl;
            } else
                continue;
           sas_PartnerTrack.Fill(myEvent_tmp.Gelectrons,(TLorentzVector)(myEvent_tmp.Gelectrons.at(0)),myEvent_tmp.Gpvs.at(0).z());
	    if(!myEvent_tmp.GoldenElectronHasPartnerTrack()){
		sas_nConv_b++;
                if(sas_verbosity > 0)
                    cout<<"\tConversion_b Passed"<<endl;
	    }else
		continue;
        }
        if(sas_doEcalDriven){
            if(myEvent_tmp.Gelectrons.at(0).isEcalDrivenSeed()){
                sas_nEcalDriven++;
    //                    EcalDriven.Fill(myEvent_tmp);
                if(sas_verbosity > 0)
                    cout<<"\tEcalDriven Passed"<<endl;
            } else
                continue;
        }
        if(sas_doSecondE){
            if(myEvent_tmp.Secondelectrons.size() == 0){
                sas_nNoLE++;
    //                    sas_SecondVetoSelection.Fill(myEvent_tmp);
                if(sas_verbosity > 0)
                    cout<<"\tNoLE Passed"<<endl;
            } else
                continue;
        }
	if(fillTree)
            eventTree_f->Fill();
        if(sas_dojet){
	    sas_Jets.Fill(myEvent_tmp.jets,myEvent_tmp.Gjets.size(),myEvent_tmp.Bjets.size());
	    if(myEvent_tmp.Gjets.size() >= 3)		
		sas_nJet3++;
            if(myEvent_tmp.Gjets.size() >= 4){
                sas_nJet++;
    //                    sas_AtLeastFourJetsSelection.Fill(myEvent_tmp);
                if(sas_verbosity > 0){
                    cout<<"\t>=4 Jet Passed"<<endl;
		    cout<<"3: "<<sas_nJet3<<", 4: "<<sas_nJet<<endl;
		}
            } else
                continue;
        }
	if(sas_doMET){
	    //cout<<"b MET"<<endl;
	    met->Fill(myEvent_tmp.mets.at(0).Pt());
	    //cout<<"a MET"<<endl;
	    if(myEvent_tmp.mets.at(0).Pt()>30)
		sas_nMET++;
	    else
		continue;
	}
        if(sas_doBtag){
	    TLorentzVector ge(-1,-1,-1,-1);
	    sas_BJets.Fill(myEvent_tmp.Gjets,myEvent_tmp.Gjets.size(),myEvent_tmp.Bjets.size(),true);
	//    cout<<"1"<<endl;
	    sas_AllFinalElectrons.Fill(myEvent_tmp.electrons,ge,myEvent_tmp.Gpvs.at(0).z(),myEvent_tmp.Gelectrons.size());
        //    cout<<"2"<<endl;
	    sas_GoldenFinalElectrons.Fill(myEvent_tmp.Gelectrons,ge,myEvent_tmp.Gpvs.at(0).z(),myEvent_tmp.Gelectrons.size());
        //    cout<<"3"<<endl;
            sas_evtProps_Final.Fill(pracEvt->Event());
            sas_PV_Final.Fill(myEvent_tmp.pvs,myEvent_tmp.Gpvs.size());

	    double ht = 0;
	    for(unsigned int wq = 0; wq < myEvent_tmp.Gjets.size(); wq++){
		ht += myEvent_tmp.Gjets.at(wq).Pt();
	    }
	    HT->Fill(ht);
	    double max = -100;
	    double m3 = -100;
            for(unsigned int wq = 0; wq < 4; wq++){
		TLorentzVector sum(0,0,0,0);
		if(sas_verbosity > 0){
		    cout<<"maximum Pt: "<<max<<endl;
                    cout<<"M3: "<<m3<<endl;
		    cout<<"Jet to put aside: "<<wq<<endl;
		}
		for(unsigned int wp = 0; wp < 4; wp++){
		    if(wp == wq)
			continue;
                    if(sas_verbosity > 0){
                        cout<<"\tJet to consider: "<<wp<<endl;
                    }

		    sum += myEvent_tmp.Gjets.at(wp);
		}
                if(sas_verbosity > 0){
                    cout<<"current Pt: "<<sum.Pt()<<endl;
                }

		if(sum.Pt() > max){
		    max = sum.Pt();
		    m3 = sum.M();
		}
	    }
//	    cout<<" M3  "<<m3<<endl;
	    M3->Fill(m3);
            if(myEvent_tmp.Bjets.size() != 0){
                sas_nBtag++;
    //                    sas_PassedBtagSelection.Fill(myEvent_tmp);
                if(sas_verbosity > 0)
                    cout<<"\t>= 1bTag Passed"<<endl;
            } else
                continue;
        }
        //cout<<"Event selected"<<endl;
 /*       TBranch* b = eventTree_f->GetBranch("PrimaryVertex");
        TClonesArray * PVs = new TClonesArray("TopTree::TRootVertex", 0);
        b->SetAddress(&PVs);

        TBranch*eb = (TBranch *) eventTree_f->GetBranch("Electrons");
        TClonesArray* tmpEle = new TClonesArray("TopTree::TRootElectron", 0);
        eb->SetAddress(&tmpEle);

        eventTree_f->GetEvent(ievt);
        cout<<"PV: "<<PVs->GetEntriesFast()<<endl;
        cout<<"Elec: "<<tmpEle->GetEntriesFast()<<endl;*/        
	//cout<<"nEvents in final tree: "<<eventTree_f->GetEntries()<<endl;
        onepassed = true;
        
    }

        cout<<"before closing file input "<<f->GetName()<<endl;
        f->Close();
        delete f;

	if(fillTree){
            sas_out->cd();
            sas_out->Write();
            sas_out->Close();
        }
    }
        endJob();
	return 0;
}
