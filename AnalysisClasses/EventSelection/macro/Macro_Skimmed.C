//#include "../interface/Cut.h"
#include "../interface/ElectronSelector.h"

#include "../interface/Event.h"
#include "../interface/EventsHists.h"
#include "../interface/JetSelector.h"
#include "../interface/MuonVetoSelector.h"
//#include "../interface/NoSelection.h"
#include "../interface/PrimaryVertexSelector.h"
#include <iomanip>
#include "/user/ajafari/CMSSW_3_8_5_patch3/src/TopBrussels/TopTreeProducer/interface/TRootMuon.h"
#include "/user/ajafari/CMSSW_3_8_5_patch3/src/TopBrussels/TopTreeProducer/interface/TRootElectron.h"
#include "/user/ajafari/CMSSW_3_8_5_patch3/src/TopBrussels/TopTreeProducer/interface/TRootJet.h"
#include "/user/ajafari/CMSSW_3_8_5_patch3/src/TopBrussels/TopTreeProducer/interface/TRootCaloJet.h"
#include "/user/ajafari/CMSSW_3_8_5_patch3/src/TopBrussels/TopTreeProducer/interface/TRootMET.h"
#include "/user/ajafari/CMSSW_3_8_5_patch3/src/TopBrussels/TopTreeProducer/interface/TRootGenEvent.h"
#include "/user/ajafari/CMSSW_3_8_5_patch3/src/TopBrussels/TopTreeProducer/interface/TRootSignalEvent.h"
#include "/user/ajafari/CMSSW_3_8_5_patch3/src/TopBrussels/TopTreeProducer/interface/TRootEvent.h"
#include "/user/ajafari/CMSSW_3_8_5_patch3/src/TopBrussels/TopTreeProducer/interface/TRootRun.h"
#include "/user/ajafari/CMSSW_3_8_5_patch3/src/TopBrussels/TopTreeProducer/interface/TRootParticle.h"
#include "/user/ajafari/CMSSW_3_8_5_patch3/src/TopBrussels/TopTreeProducer/interface/TRootMCParticle.h"
#include "/user/ajafari/CMSSW_3_8_5_patch3/src/TopBrussels/TopTreeProducer/interface/TRootVertex.h"



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
EventHists beforSelection("beforSelection");
EventHists atLeastOnGPV("primaryVertex");
EventHists atleastOneGESelection("AtleastOneGoodElectron");
EventHists ExactlyOneGESelection("ExactlyOneGoodElectron");
EventHists ConversionRejection("ConversionRejection");
EventHists EcalDriven("EcalDriven");
EventHists SecondVetoSelection("SecondElectron");
EventHists AtLeastFourJetsSelection("AtLeastFourJets");
EventHists MetSelection("MetSelection");
EventHists MuonVeto("MuonVeto");
EventHists PassedBtagSelection("PassedBtag");

int n0;
int nPV;
bool doPV;
int nLeatsOneGE;
bool doElectron;
int nExactOneGE;
int nNoMu;
bool doMuon;
int nNoLE;
bool doSecondE;
int nConv;
bool doConv;
int nEcalDriven;
bool doEcalDriven;
int nJet;
bool dojet;
int nJetCaloTowers;
bool dojetCaloTowers;
int nJetEmf;
bool dojetEmf;
int nJetN90;
bool dojetN90;
int nJetfHPD;
bool dojetfHPD;
int nBtag;
bool doBtag;

double XSec;
double Luminosity;
double intialBeforePresel;

int verbosity;
TBranch* genEvt_br;
TClonesArray* genEvt;
TBranch* jets_br;
TClonesArray* ak5jets;
TBranch* muons_br;
TClonesArray* muons;
TBranch* electrons_br;
TClonesArray* electrons;
TBranch* mets_br;
TClonesArray* mets;
TBranch* pvs_br;
TClonesArray* PVs;

std::vector<std::string> inputFileNames;
std::string outFileName;
void beginJob(){
     n0 = 0;
     nPV = 0;
     doPV = false;
     nLeatsOneGE = 0;
     doElectron = false;
     nExactOneGE = 0;
     nNoMu = 0;
     doMuon = false;
     nNoLE = 0;
     doSecondE = false;
     nConv= 0;
     doConv = false;
     nEcalDriven = 0;
     doEcalDriven = false;
     nJet= 0;
     dojet = true;
     nBtag= 0;
     doBtag = true;
     verbosity = 0;
     //inputFileNames.clear();
}

void Macro(string fname){
	cout << fname.c_str() <<endl;
	TFile* f=TFile::Open(fname.c_str());

//	TTree* runTree = (TTree*) f->Get("runTree");
	TTree* eventTree = (TTree*) f->Get("eventTree");

//	TBranch* run_br = (TBranch *) runTree->GetBranch("runInfos");
//	TRootRun* runInfos = 0;
//	run_br->SetAddress(&runInfos);

	TBranch* event_br = (TBranch *) eventTree->GetBranch("Event");
	TRootEvent* event = 0;
	event_br->SetAddress(&event);
        
        jets_br = (TBranch *) eventTree->GetBranch("CaloJets_selectedPatJetsAK5Calo");
        ak5jets = new TClonesArray("TopTree::TRootCaloJet", 0);
        jets_br->SetAddress(&ak5jets);



        muons_br = (TBranch *) eventTree->GetBranch("Muons");
        muons = new TClonesArray("TopTree::TRootMuon", 0);
        muons_br->SetAddress(&muons);


        electrons_br = (TBranch *) eventTree->GetBranch("Electrons");
        electrons = new TClonesArray("TopTree::TRootElectron", 0);
        electrons_br->SetAddress(&electrons);

        mets_br = (TBranch *) eventTree->GetBranch("MET");
        mets = new TClonesArray("TopTree::TRootMET", 0);
        mets_br->SetAddress(&mets);

        pvs_br = (TBranch *) eventTree->GetBranch("PrimaryVertex");
        PVs = new TClonesArray("TopTree::TRootVertex", 0);
        pvs_br->SetAddress(&PVs);

//        runTree->GetEvent(0);




        //Declaration of histograms


	unsigned int nEvents = (int)eventTree->GetEntries();
        std::cout<<"beforeLoop"<<std::endl;
//	nEvents = 20;

	for(unsigned int ievt=0; ievt<nEvents; ievt++)
	{
            eventTree->GetEvent(ievt);
	    if(verbosity > 0)
	    	cout<<"befor event number "<<ievt<<"\t||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"<<endl;                        
            Event myEvent_tmp(*ak5jets, *electrons,* mets,* muons, * PVs);
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
	    if(verbosity > 0)
	    	cout<<"Vertex Makers ---------------------------------------------------------------------"<<endl;
            myEvent_tmp.VertexMaker();
    	    if(verbosity > 0)
	    	cout<<"Muon Maker ---------------------------------------------------------------------"<<endl;
            myEvent_tmp.MuonMaker(/*pt*/20.,/*eta*/2.4,/*chi2*/10,/*D0*/0.02,/*nvh*/11,/*isoCut_*/0.05);
            if(verbosity > 0)
	    	cout<<"START TO SELECT : "<<endl;
            beforSelection.Fill(myEvent_tmp);
            n0++;
            if(doPV){
                if(myEvent_tmp.Gpvs.size() > 0){
                    nPV++;
                    atLeastOnGPV.Fill(myEvent_tmp);
		    if(verbosity > 0)
			cout<<"\tPVCut Passed"<<endl;
                } else
                    continue;
            }
            
            if(doElectron){
                if(myEvent_tmp.Gelectrons.size() != 0){
                    nLeatsOneGE++;
                    atleastOneGESelection.Fill(myEvent_tmp);
		    if(verbosity > 0)
			cout<<"\tLeatsOneGE Passed"<<endl;
                } else
                    continue;
                if(myEvent_tmp.Gelectrons.size() == 1){
                    nExactOneGE++;
                    ExactlyOneGESelection.Fill(myEvent_tmp);
		    if(verbosity > 0)
			cout<<"\tExactOneGE Passed"<<endl;
                } else
                    continue;
            }
            if(doConv){
                if(!myEvent_tmp.Gelectrons.at(0).isFromConversion()){
                    nConv++;
                    ConversionRejection.Fill(myEvent_tmp);
		    if(verbosity > 0)
			cout<<"\tConversion Passed"<<endl;
                } else
                    continue;
            }
            if(doEcalDriven){
                if(myEvent_tmp.Gelectrons.at(0).isEcalDrivenSeed()){
                    nEcalDriven++;
                    EcalDriven.Fill(myEvent_tmp);
		    if(verbosity > 0)
			cout<<"\tEcalDriven Passed"<<endl;
                } else
                    continue;
            }
            if(doSecondE){
                if(myEvent_tmp.Secondelectrons.size() == 0){
                    nNoLE++;
                    SecondVetoSelection.Fill(myEvent_tmp);
		    if(verbosity > 0)
			cout<<"\tNoLE Passed"<<endl;
                } else
                    continue;
            }
            if(doMuon){
                if(myEvent_tmp.Dmuons.size() == 0){
                    nNoMu++;
                    MuonVeto.Fill(myEvent_tmp);
		    if(verbosity > 0)
			cout<<"\tMu veto Passed"<<endl;
                } else
                    continue;
            }
            if(dojet){
                if(myEvent_tmp.Gjets.size() >= 4){
                    nJet++;
                    AtLeastFourJetsSelection.Fill(myEvent_tmp);
		    if(verbosity > 0)
			cout<<"\t>=4 Jet Passed"<<endl;
                } else
                    continue;
            }
            if(doBtag){
                if(myEvent_tmp.Bjets.size() != 0){
                    nBtag++;
                    PassedBtagSelection.Fill(myEvent_tmp);
		    if(verbosity > 0)
			cout<<"\t>= 1bTag Passed"<<endl;
                } else
                    continue;
            }
        }
}

void endJob(){
//    double intialBeforePresel = (double)n0/(double)intialBeforePresel;
    double weight = (double)(XSec*Luminosity)/(double)intialBeforePresel;
    cout<<"Cut flow in "<<Luminosity<<" pb-1 , Weight is "<<weight<<endl;
    cout<<"\tInitial:\t"<<XSec*Luminosity<<"|\t"<<1.<<endl;
    cout<<"\tPreSele:\t"<<n0*weight<<"|\t"<<intialBeforePresel<<endl;
    cout<<"\tPVertex:\t"<<nPV*weight<<"|\t"<<(double)nPV/(double)n0<<endl;
    if(doPV)
        cout<<"\t>= 1 GE:\t"<<nLeatsOneGE*weight<<"|\t"<<(double)nLeatsOneGE/(double)nPV<<endl;
    else
        cout<<"\t>= 1 GE:\t"<<nLeatsOneGE*weight<<"|\t"<<(double)nLeatsOneGE/(double)n0<<endl;
    cout<<"\t== 1 GE:\t"<<nExactOneGE*weight<<"|\t"<<(double)nExactOneGE/(double)nLeatsOneGE<<endl;
    cout<<"\t!ConvGE:\t"<<nConv*weight<<"|\t"<<(double)nConv/(double)nExactOneGE<<endl;
    if(doConv)
        cout<<"\tECalDrE:\t"<<nEcalDriven*weight<<"|\t"<<(double)nEcalDriven/(double)nConv<<endl;
    else
        cout<<"\tECalDrE:\t"<<nEcalDriven*weight<<"|\t"<<(double)nEcalDriven/(double)nExactOneGE<<endl;
    
    if(doEcalDriven)
        cout<<"\t!2'ndLE:\t"<<nNoLE*weight<<"|\t"<<(double)nNoLE/(double)nEcalDriven<<endl;
    else if(doConv)
        cout<<"\t!2'ndLE:\t"<<nNoLE*weight<<"|\t"<<(double)nNoLE/(double)nConv<<endl;
    else
	cout<<"\t!2'ndLE:\t"<<nNoLE*weight<<"|\t"<<(double)nNoLE/(double)nExactOneGE<<endl;
    cout<<"\t !LMuon:\t"<<nNoMu*weight<<"|\t"<<(double)nNoMu/(double)nNoLE<<endl;
    cout<<"\t>=4GJet:\t"<<nJet*weight<<"|\t"<<(double)nJet/(double)nNoMu<<endl;
    cout<<"\t>=1BJet:\t"<<nBtag*weight<<"|\t"<<(double)nBtag/(double)nJet<<endl;

    cout<<"\t"<<XSec*Luminosity<<"\t"<<n0*weight<<"\t"<<nPV*weight<<"\t"<<nLeatsOneGE*weight<<"\t"<<nExactOneGE*weight
            <<"\t"<<nConv*weight<<"\t"<<nEcalDriven*weight<<"\t"<<nNoLE*weight<<"\t"<<nNoMu*weight<<"\t"<<nJet*weight<<"\t"<<nBtag*weight<<endl;
    cout<<"\n"<<XSec*Luminosity<<"\n"<<n0*weight<<"\n"<<nPV*weight<<"\n"<<nLeatsOneGE*weight<<"\n"<<nExactOneGE*weight
            <<"\n"<<nConv*weight<<"\n"<<nEcalDriven*weight<<"\n"<<nNoLE*weight<<"\n"<<nNoMu*weight<<"\n"<<nJet*weight<<"\n"<<nBtag*weight<<endl;

    cout<<"\n"<<intialBeforePresel<<"\n"<<n0<<"\n"<<nPV<<"\n"<<nLeatsOneGE<<"\n"<<nExactOneGE
            <<"\n"<<nConv<<"\n"<<nEcalDriven<<"\n"<<nNoLE<<"\n"<<nNoMu<<"\n"<<nJet<<"\n"<<nBtag<<endl;


    TFile * outfile = new TFile(outFileName.c_str(),"recreate");
    outfile->cd();
    beforSelection.WriteAll(outfile);
    if(doPV)
        atLeastOnGPV.WriteAll(outfile);
    if(doElectron){
        atleastOneGESelection.WriteAll(outfile);
        ExactlyOneGESelection.WriteAll(outfile);
    }
    if(doSecondE)
        SecondVetoSelection.WriteAll(outfile);
    if(doConv)
        ConversionRejection.WriteAll(outfile);
    if(doEcalDriven)
        EcalDriven.WriteAll(outfile);
    if(doMuon)
        MuonVeto.WriteAll(outfile);
    if(dojet)
        AtLeastFourJetsSelection.WriteAll(outfile);
    if(doBtag)
        PassedBtagSelection.WriteAll(outfile);
//    MetSelection.WriteAll(outfile);

    outfile->cd();
    outfile->Close();
}

int main(int argc, char** argv){
//    sleep(60);
    for (int f = 1; f < argc; f++) {
        std::string arg_fth(*(argv + f));
        if (arg_fth == "out") {
          f++;
          std::string out(*(argv + f));
          outFileName = string("/home/ajafari/CodeBackup/Aug2010/CMSSW_3_6_1_patch3/SelectionHists/"+out);
        }else if (arg_fth == "input") {
          f++;
          std::string in(*(argv + f));
	  in ="/home/ajafari/rootfiles/TopTrees/7TeV/July10/Skimmed/FullSelection/FS_ECalDriven_"+in;
//	  in ="/tmp/ajafari/Skimmed/"+in;
          inputFileNames.push_back(in);
        }else if(arg_fth == "XSec"){
          f++;
          std::string Xsec(*(argv + f));
          XSec = atof(Xsec.c_str());
        }else if(arg_fth == "Lumi"){
          f++;
          std::string Lumi(*(argv + f));
          Luminosity = atof(Lumi.c_str());
        }else if(arg_fth == "Initial"){
          f++;
          std::string intialBeforePresel_(*(argv + f));
          intialBeforePresel = atof(intialBeforePresel_.c_str());
        }
    }

	beginJob();
        std::cout<<"Output:\n\t"<<outFileName<<endl;
        for(uint p = 0; p < inputFileNames.size(); p++){
            std::cout<<"Input put:\n\t"<<inputFileNames.at(p)<<endl;
            Macro(inputFileNames.at(p));
        }
        endJob();
	return 0;
}
