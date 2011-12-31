#include <iomanip>
#include "/afs/cern.ch/user/a/ajafari/scratch0/CMSSW_3_6_1_patch3/src/TopBrussels/TopTreeProducer/interface/TRootMuon.h"
#include "/afs/cern.ch/user/a/ajafari/scratch0/CMSSW_3_6_1_patch3/src/TopBrussels/TopTreeProducer/interface/TRootElectron.h"
#include "/afs/cern.ch/user/a/ajafari/scratch0/CMSSW_3_6_1_patch3/src/TopBrussels/TopTreeProducer/interface/TRootCaloJet.h"
#include "/afs/cern.ch/user/a/ajafari/scratch0/CMSSW_3_6_1_patch3/src/TopBrussels/TopTreeProducer/interface/TRootCaloJet.h"
#include "/afs/cern.ch/user/a/ajafari/scratch0/CMSSW_3_6_1_patch3/src/TopBrussels/TopTreeProducer/interface/TRootMET.h"
#include "/afs/cern.ch/user/a/ajafari/scratch0/CMSSW_3_6_1_patch3/src/TopBrussels/TopTreeProducer/interface/TRootGenEvent.h"
#include "/afs/cern.ch/user/a/ajafari/scratch0/CMSSW_3_6_1_patch3/src/TopBrussels/TopTreeProducer/interface/TRootSignalEvent.h"
#include "/afs/cern.ch/user/a/ajafari/scratch0/CMSSW_3_6_1_patch3/src/TopBrussels/TopTreeProducer/interface/TRootEvent.h"
#include "/afs/cern.ch/user/a/ajafari/scratch0/CMSSW_3_6_1_patch3/src/TopBrussels/TopTreeProducer/interface/TRootRun.h"
#include "/afs/cern.ch/user/a/ajafari/scratch0/CMSSW_3_6_1_patch3/src/TopBrussels/TopTreeProducer/interface/TRootParticle.h"
#include "/afs/cern.ch/user/a/ajafari/scratch0/CMSSW_3_6_1_patch3/src/TopBrussels/TopTreeProducer/interface/TRootMCParticle.h"
#include "/afs/cern.ch/user/a/ajafari/scratch0/CMSSW_3_6_1_patch3/src/AnalysisClasses/ChiSquared/interface/TopEvent.h"
#include "/afs/cern.ch/user/a/ajafari/scratch0/CMSSW_3_6_1_patch3/src/AnalysisClasses/EventSelection/interface/Event.h"
#include "/afs/cern.ch/user/a/ajafari/scratch0/CMSSW_3_6_1_patch3/src/AnalysisClasses/ChiSquared/interface/DR.h"
#include "/afs/cern.ch/user/a/ajafari/scratch0/CMSSW_3_6_1_patch3/src/AnalysisClasses/EventSelection/interface/JetMatching.h"

#include <sstream>
#include <string>
#include <TFile.h>
#include <TSystem.h>
#include <TH1.h>
#include <TH2.h>
#include <TCanvas.h>
#include <TBranch.h>
#include <TTree.h>
#include <vector>
#include <TLorentzVector.h>

//#include "../interface/DR.h"
//#include "../interface/HadronicW.h"
//#include "../interface/TopQuark.h"
//#include "../interface/Matcher.h"
//#include "../interface/ExtendedJet.h"
//#include "../../EventSelection/interface/Event.h"

#define My
using namespace std;
using namespace TopTree;
std::vector<TRootCaloJet> recoJets;
TBranch* mjets_br;
TClonesArray* mjets;
TBranch* genEvent_br;
TClonesArray* genEvents;
TBranch* electron_br;
TClonesArray* electrons;
TH1D * WMassDr;
TH1D * TopMassDr;
TH1D * WMassDPt;
TH1D * TopMassDPt;
TH1D *	genWMass;
TH1D *	genTopMass;
TFile* fIn;
TTree* eventTree;
TBranch* event_br;
int totalSemiElecEvents;
int verbosity;
TopEvent * topEvt;
int n;
bool doBtag;

#ifdef My
bool doDR;
TH1D * WMassDrAllMatched;
TH1D * TopMassDrAllMatched;
TH1D * WMassDPtAllMatched;
TH1D * TopMassDPtAllMatched;
double JES;
std::string strJES;
std::string inName;

#endif



#ifdef My

void analyze(Event myEvt, TRootGenEvent * gevent){
    //=========================
    std::vector<std::pair<TRootCaloJet, int> > jetQpairs;
    jetQpairs.clear();
    bool has4MatchedJet = MaryamMethod_TtBarSemiElec_Correlation(myEvt.Gjets,gevent,jetQpairs,genEvents);
    std::vector<ExtendedJet> myExtJets;
    myExtJets.clear();
    ExtendedJet * myExtJet;
    for(uint j = 0; j<jetQpairs.size(); j++){
        myExtJet = new ExtendedJet(jetQpairs.at(j),j);
        myExtJets.push_back(*myExtJet);
    }
    if(has4MatchedJet){
        TLorentzVector Q(-1,-1,-1,-1);
        TLorentzVector QBar(-1,-1,-1,-1);
        TLorentzVector HadB(-1,-1,-1,-1);
        TLorentzVector LepB(-1,-1,-1,-1);
        TLorentzVector tmp(-1,-1,-1,-1);
        for(uint i = 0; i < myExtJets.size(); i++){
            if(myExtJets.at(i).getMatchName() == "HadB")
                HadB = myExtJets.at(i).getP4();
            else if(myExtJets.at(i).getMatchName() == "LepB")
                LepB = myExtJets.at(i).getP4();
            else if(myExtJets.at(i).getMatchName() == "Q")
                Q = myExtJets.at(i).getP4();
            else if(myExtJets.at(i).getMatchName() == "QBar")
                QBar = myExtJets.at(i).getP4();
        }
        if((Q != tmp) && (QBar != tmp) && (HadB != tmp) && (LepB != tmp)){

            WMassDr->Fill((Q+QBar).M());
            TopMassDr->Fill((Q+QBar+HadB).M());
            
        }
        
    }

}
#endif


#ifdef My
void endJob(){
	std::cout<<"Number of SemiLeptonic events: "<<totalSemiElecEvents<<std::endl;
	TFile * out = new TFile(string(strJES+"masses_.root").c_str(),"RECREATE");
	out->cd();
        if(doDR){
            WMassDr->Write();
            TopMassDr->Write();
            WMassDrAllMatched->Write();
            TopMassDrAllMatched->Write();
        }
        else{
            WMassDPt->Write();
            TopMassDPt->Write();
            WMassDPtAllMatched->Write();
            TopMassDPtAllMatched->Write();
        }
	out->Close();
        cout<<n<<" events passed the selection"<<endl;
}
#endif

int main(int argc, char** argv){
        doDR = true;
        doBtag = false;
        verbosity = 0;
        n = 0;
        JES = 1.;
        for (int f = 1; f < argc; f++) {
            std::string arg_fth(*(argv + f));
//        cout<<"-------- "<< arg_fth<<endl;
            if (arg_fth == "JES") {
              f++;
              std::string out(*(argv + f));
              JES = atof(out.c_str());
              strJES = out;
            }else if (arg_fth == "input") {
              f++;
              inName = std::string(*(argv + f));
            }
        }
	fIn =  TFile::Open("/home/ajafari/rootfiles/TopTrees/7TeV/July10/Skimmed/FullSelection/FS_ECalDriven_Signal.root");
//	fIn =  TFile::Open(string("/home/ajafari/rootfiles/TopTrees/7TeV/July10/SystematicSamples/FullSelection/JES"+inName).c_str());
	std::cout<<"file opened: "<<fIn->GetName()<<std::endl;
        
	TTree* eventTree = (TTree*) fIn->Get("eventTree");
	event_br = (TBranch *) eventTree->GetBranch("Event");
	TRootEvent* event = 0;
	event_br->SetAddress(&event);
	mjets_br = (TBranch *) eventTree->GetBranch("CaloJets_selectedPatJetsAK5Calo");
	mjets = new TClonesArray("TopTree::TRootCaloJet", 0);
	mjets_br->SetAddress(&mjets);
	genEvent_br = (TBranch *) eventTree->GetBranch("GenEvent");
	genEvents = new TClonesArray("TopTree::TRootGenEvent", 0);
	genEvent_br->SetAddress(&genEvents);
	electron_br = (TBranch *) eventTree->GetBranch("Electrons");
	electrons = new TClonesArray("TopTree::TRootElectron", 0);
	electron_br->SetAddress(&electrons);
	
        WMassDr = new TH1D("WMassDr","WMassDr", 200,20.,220.);
	TopMassDr = new TH1D("TopMassDr","TopMassDr", 450,50.,500.);
	WMassDPt = new TH1D("WMassDPt","WMassDPt", 200,20.,220.);
	TopMassDPt = new TH1D("TopMassDPt","TopMassDPt", 450,50.,500.);
	WMassDrAllMatched = new TH1D("WMassDrAllMatched","WMassDrAllMatched", 200,20.,220.);
	TopMassDrAllMatched = new TH1D("TopMassDrAllMatched","TopMassDrAllMatched", 450,50.,500.);
	WMassDPtAllMatched = new TH1D("WMassDPtAllMatched","WMassDPtAllMatched", 200,20.,220.);
	TopMassDPtAllMatched = new TH1D("TopMassDPtAllMatched","TopMassDPtAllMatched", 450,50.,500.);
        
	totalSemiElecEvents = 0;
	unsigned int nEvents = (int)eventTree->GetEntries();
//        nEvents = 10;
	
	std::cout<<"total number of events: "<<nEvents<<std::endl;
	for(unsigned int ievt=0; ievt<nEvents; ievt++){
            cout<<"Event "<<ievt+1<<"  ..."<<endl;
            eventTree->GetEvent(ievt);
            cout<<electrons->GetEntriesFast()<<endl;
            std::vector<TRootCaloJet> myJets;
            myJets.clear();
            for(int o = 0; o<mjets->GetEntriesFast(); o++){
                TRootCaloJet jet_ = *(TRootCaloJet*)mjets->At(o);
//                cout<<"1- "<<jet_.Pt()<<endl;
                jet_.SetPxPyPzE(JES*jet_.Px(),JES*jet_.Py(),JES*jet_.Pz(),JES*jet_.E());
//                cout<<"2- "<<jet_.Pt()<<endl;
                myJets.push_back(jet_);
            }
            Event myEvent_tmp(myJets,*electrons);
            myEvent_tmp.verbose(verbosity);
            if(verbosity > 0)
                cout<<"Electron Maker ---------------------------------------------------------------------"<<endl;
            myEvent_tmp.ElectronMaker(/*pt*/30.,/*ets*/2.4,/*ExLow*/1.442,/*Exc_High*/1.56,
                    /*Id */"VBTF70",/*IdSecond*/"VBTF95",/*Iso*/"",/*D0*/0.02,/*IsoCut*/0.1);
            if(verbosity > 0)
                cout<<"Jet Cleaning  ---------------------------------------------------------------------"<<endl;
            myEvent_tmp.JetCleaning();
            if(verbosity > 0)
                cout<<"Jet Makers ---------------------------------------------------------------------"<<endl;
            myEvent_tmp.JetMaker(/*bTagAlgo*/"TCHE",/*pt*/30.,/*eta*/2.4,/*nCaloTower*/5,/*EmfUp*/0.9,
                    /*EmfLow*/0.05,/*fhpd_*/1000.,/*N90_*/-1,/*bTagCut_*/4.);
                // first find the semiElec Event
            if(eventTree == NULL){
                    std::cout<<"EventTree is NULL"<<std::endl;
                    continue;
            }
            TRootGenEvent * gevent = (TRootGenEvent*) genEvents->At(0);

            if(myEvent_tmp.Gjets.size() < 4)
                continue;

            if(doBtag)
                if(myEvent_tmp.Bjets.size() == 0)
                    continue;
            n++;
            // then analyze the semiLep event
            if(verbosity > 0)
                cout<<"Event "<<ievt+1<<" has 4 jets from top. Let's analyze it ..."<<endl;
            analyze(myEvent_tmp,gevent);
	}
	endJob();
	return 1;
}
