/* 
 * File:   TPObjectProducer.C
 * Author: ajafari
 *
 * Created on October 22, 2010, 4:30 PM
 */

#include "../../../../AnalysisClasses/EventSelection/interface/GoodObjects.h"
#include "../../../../AnalysisClasses/EventSelection/interface/PracticalEvent.h"
#include "../../../../AnalysisClasses/TagProbeStudies/interface/PairMaker.h"
#include "../../../../AnalysisClasses/LightJets/interface/NeededStructs.h"
#include "../../../../TopBrussels/TopTreeProducer/interface/TRootMCParticle.h"


using namespace std;
using namespace TopTree;
/*
 * 
 */
int main(int argc, char** argv) {
    std::string anaName;
    std::vector<std::string> input;
    input.clear();
    bool isTtBar = false;
    double lowmass;
    double highmass;
    bool checkCharge = false;
    bool isData = false;
    bool doPV_ = false;
    for (int f = 1; f < argc; f++) {
        std::string arg_fth(*(argv + f));
//        cout<<"-------- "<< arg_fth<<endl;
        if (arg_fth == "out") {
          f++;
          anaName = std::string(*(argv + f));
        }else if (arg_fth == "input") {
          f++;
          std::string in(*(argv + f));
          if(in == "TtBar.root" || in == "SignalD6T.root")
              isTtBar = true;
//          in ="/home/ajafari/rootfiles/TopTrees/7TeV/December10/TagAndProbe/Data/"+in;
          in ="/home/ajafari/rootfiles/TopTrees/7TeV/December10/DT6Tune/"+in;
//          in ="/home/ajafari/"+in;
          input.push_back( in);
          cout<<input.at(input.size()-1)<<endl;
        }else if (arg_fth == "lowmass") {
          f++;
          std::string in(*(argv + f));
          lowmass = atof(in.c_str());
          anaName = string(in +"_"+anaName );
        }else if (arg_fth == "highmass") {
          f++;
          std::string in(*(argv + f));
          highmass = atof(in.c_str());
          anaName = string(in +"_"+anaName );
        }else if (arg_fth == "oppositCharge") {
          f++;
          std::string in(*(argv + f));
          if(in == "true")
              checkCharge = true;
        }else if (arg_fth == "isData") {
          f++;
          std::string in(*(argv + f));
          if(in == "true")
              isData = true;
        }else if (arg_fth == "doPV") {
          f++;
          std::string in(*(argv + f));
          if(in == "true")
              doPV_ = true;
        }
    }
    anaName = string("/home/ajafari/"+anaName);
    cout<<anaName<<endl;
    TFile * _out = new TFile(anaName.c_str(), "recreate");
    _out->cd();
    TRootEvent* rootEvent = 0;
    TRootRun* rootRun = 0;
    TTree * _eventTree_f = new TTree("eventTree", "Event Infos");
    _eventTree_f->Branch("Event", "TopTree::TRootEvent", &rootEvent);

    TTree * _runTree_f = new TTree("runTree", "Run Infos");
    _runTree_f->Branch("runInfos", "TopTree::TRootRun", &rootRun);

    TClonesArray * jets = new TClonesArray("TopTree::TRootCaloJet", 1000);
    _eventTree_f->Branch("CaloJets_selectedPatJetsAK5Calo", "TClonesArray", &jets);
    jets->SetOwner(kTRUE);

    TClonesArray * pvs = new TClonesArray("TopTree::TRootVertex", 1000);
    _eventTree_f->Branch("PrimaryVertex", "TClonesArray", &pvs);
    pvs->SetOwner(kTRUE);

    TClonesArray * gen = new TClonesArray("TopTree::TRootGenEvent", 1000);
    TClonesArray * NPGenEvts = new TClonesArray("TopTree::TRootNPGenEvent", 1000);

    if(!isData){
        if(isTtBar){
            _eventTree_f->Branch("GenEvent", "TClonesArray", &gen);
            gen->SetOwner(kTRUE);
        }else{
            _eventTree_f->Branch("NPGenEvent", "TClonesArray", &NPGenEvts);
            NPGenEvts->SetOwner(kTRUE);
        }
    }

    TClonesArray * TPos = new TClonesArray("TopTree::TRootTagProbeObject", 1000);
    _eventTree_f->Branch("TagProbeObject", "TClonesArray", &TPos);
    TPos->SetOwner(kTRUE);

    //test
    int nTP = 0;
    int nElec = 0;
    int nMu = 0;
    int nLooseMu = 0;
    int nJetsGolden = 0;
    int nJetsFinal = 0;
    int nGenEvt = 0;
    int nPV = 0;
    //

    for(unsigned int o =0 ; o < input.size(); o++){
        std::cout<<input.at(o)<<std::endl;
        TFile * F = new TFile(input.at(o).c_str(),"read");
        if(F == NULL){
            std::cout<<"Bad file pointer"<<std::endl;
            return 0;
        }
        TTree* runTree = (TTree*) F->Get("runTree");
        TTree* eventTree = (TTree*) F->Get("eventTree");
        PracticalEvent * pracEvt = NULL;
        if(isTtBar)
            pracEvt = new PracticalEvent(eventTree,runTree,true);
        else
            pracEvt = new PracticalEvent(eventTree,runTree);



        int i = 0;

        bool GoAhead = true;
        while (pracEvt->Next()){
                  i++;
//                  if(i>50)
//                break;
//            std::cout<<"________________________________________________ event number : "<<i+1<<std::endl;

            std::vector<TLorentzVector> elecsZ;
            if(!isData){
                elecsZ.clear();
                if(isTtBar){
                       GoAhead =((TRootGenEvent*)pracEvt->GenEvtCollection()->At(0))->isSemiLeptonic(TRootGenEvent::LeptonType(1));
                } else{
        //            cout<<"I look for a genMatch"<<endl;
//                    std::vector<TRootMCParticle> leptons = ((TRootNPGenEvent*)pracEvt->NPGenEvtCollection()->At(0))->leptons();
//
//                    for(unsigned int s = 0; s<leptons.size(); s++){
//                        if(fabs(leptons.at(s).type()) == 11 && leptons.at(s).status() == 3 && leptons.at(s).motherType() == 23){
//                            elecsZ.push_back((TLorentzVector)leptons.at(s));
//                        }
//                    }
                }
            }

            rootEvent = new TRootEvent(*pracEvt->Event());
    //        cout<<"Event in Final: "<<rootEvent->eventId()<<endl;

            Event myEvent_tmp(*pracEvt->JetCollection(),pracEvt->VertexCollection(), *pracEvt->ElectronCollection());
//            myEvent_tmp.verbosity = 4;
            myEvent_tmp.ElectronMaker(30., 2.5, 1.442 ,1.56,"NoId","NoId", "", 0.02, 1000);
            myEvent_tmp.JetMaker("TCHE", 30.,2.4,-1,10000.,0.01,0.98,1);
            myEvent_tmp.VertexMaker(24.);

            if(doPV_ && myEvent_tmp.Gpvs.size() == 0){
                if(isTtBar)
                    (*gen).Delete();
                else
                    (*NPGenEvts).Delete();
//                (*muons).Delete();
                (*pvs).Delete();
                (*jets).Delete();
                (*TPos).Delete();
                delete rootEvent;
                continue;                
            }
            //Muon

             //PVs
            for(int k = 0; k<pracEvt->VertexCollection()->GetEntriesFast(); k++){
                TRootVertex * genEvt = (TRootVertex*)(pracEvt->VertexCollection()->At(k));
                if(genEvt != NULL){
                    new( (*pvs)[k] ) TRootVertex(*genEvt);
                    nPV++;
                }
            }
            if(!isData){
             //genEvt
                if(isTtBar){
                    for(int k = 0; k<pracEvt->GenEvtCollection()->GetEntriesFast(); k++){
                        TRootGenEvent * genEvt = (TRootGenEvent*)pracEvt->GenEvtCollection()->At(k);
                        if(genEvt != NULL)
                            new( (*gen)[k] ) TRootGenEvent(*genEvt);
                        nGenEvt++;
                    }
                }else{
                    for(int k = 0; k<pracEvt->NPGenEvtCollection()->GetEntriesFast(); k++){
                        TRootNPGenEvent * genEvt = (TRootNPGenEvent*)pracEvt->NPGenEvtCollection()->At(k);
                        if(genEvt != NULL){
                            new( (*NPGenEvts)[k] ) TRootNPGenEvent(*genEvt);
                            nGenEvt++;
                        }
                    }
                }
            }
    //

            nJetsGolden +=myEvent_tmp.Gjets.size();
            //Jets
            for(unsigned int k = 0; k<myEvent_tmp.Gjets.size(); k++){
                TRootCaloJet  genEvt = myEvent_tmp.Gjets.at(k);
                new( (*jets)[k] ) TRootCaloJet(genEvt);
                nJetsFinal++;
            }
            if(!GoAhead){
                if(isTtBar)
                    (*gen).Delete();
                else
                    (*NPGenEvts).Delete();
//                (*muons).Delete();
                (*pvs).Delete();
                (*jets).Delete();
                (*TPos).Delete();
                delete rootEvent;
                continue;
            }
            int match1 = -1;
            int match2 = -1;
            if(isTtBar){
                TLorentzVector genMatch = ((TRootGenEvent*)pracEvt->GenEvtCollection()->At(0))->lepton();
                ElectronMatcher(genMatch,myEvent_tmp.Gelectrons, match1);
            } else{
                ZElectronMatcher(elecsZ,myEvent_tmp.Gelectrons,match1,match2);
            }
    //        cout<<myEvent_tmp.Gelectrons.size()<<endl;

            PairMaker * pm = new PairMaker(lowmass,highmass,checkCharge);
    //        pm->verbosity = 1;
            pm->MakePairs(myEvent_tmp.Gelectrons,match1,-1,match2);
            nElec+=myEvent_tmp.Gelectrons.size();

            if(pm->ConsistentPairs(isTtBar)){
                pm->JetPairCleaning(myEvent_tmp.Gjets);

                pm->setJetInfo();

                //TP && Electron
                for(unsigned int k = 0; k<pm->Pairs.size(); k++){
                    nTP++;
                    new( (*TPos)[k] ) TRootTagProbeObject((pm->Pairs).at(k));
                }
                _eventTree_f->Fill();


            }
    //        cout<<"Electron size: "<<myEvent_tmp.Gelectrons.size()<<endl;
    //        cout<<"TP size: "<<TPos->GetEntriesFast()<<endl;



    //        cout<<"''''''''''''''''''''''''''''''''''''TP size: "<<endl;
            if(i%100000 == 0)
                _eventTree_f->AutoSave();

            delete rootEvent;
            if(isTtBar)
                (*gen).Delete();
            else
                (*NPGenEvts).Delete();
//            (*muons).Delete();
    //        (*electrons).Delete();
            (*pvs).Delete();
            (*TPos).Delete();
            (*jets).Delete();
            delete pm;
        }

        rootRun = new TRootRun(*pracEvt->RunInfo());
        _out->cd();
        _runTree_f->Fill();
        delete F;
    }
    cout<<"before closing file out "<<_out->GetName()<<endl;
    _out->cd();
    _out->Write();

    cout<<nElec<<endl;
    cout<<nTP<<endl<<endl;
    cout<<nMu<<endl;
    cout<<nLooseMu<<endl<<endl;
    cout<<nGenEvt<<endl<<endl;
    cout<<nJetsFinal<<endl;
    cout<<nJetsGolden<<endl<<endl;
    cout<<nPV<<endl;

    return (EXIT_SUCCESS);
}

