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

using namespace std;
using namespace TopTree;
/*
 *
 */
int main(int argc, char** argv) {
    std::string anaName;
    std::string input;
    bool isTtBar = false;
    for (int f = 1; f < argc; f++) {
        std::string arg_fth(*(argv + f));
//        cout<<"-------- "<< arg_fth<<endl;
        if (arg_fth == "out") {
          f++;
          anaName = std::string(*(argv + f));
        }else if (arg_fth == "input") {
          f++;
          std::string in(*(argv + f));
//          if(in == "test.root")
//              isTtBar = true;
//          in ="/home/ajafari/"+in;
          input = in;
//          cout<<inputNameWeight.first<<endl;
        }
    }
    
    std::cout<<input<<std::endl;
    TFile * F = new TFile(input.c_str(),"read");
    if(F == NULL){
        std::cout<<"Bad file pointer"<<std::endl;
        return 0;
    }
    TTree* runTree = (TTree*) F->Get("runTree");
    TTree* eventTree = (TTree*) F->Get("eventTree");
    int i = 0;

    bool GoAhead = true;

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
    if(isTtBar){
        TBranch * GEVT_br = (TBranch *) eventTree->GetBranch("GenEvent");
        TClonesArray *  genEvts = new TClonesArray("TopTree::TRootGenEvent", 0);
        GEVT_br->SetAddress(&genEvts);
    }
    TBranch * TPs_br = (TBranch *) eventTree->GetBranch("TagProbeObject");
    TClonesArray *  TPs = new TClonesArray("TopTree::TRootTagProbeObject", 0);
    TPs_br->SetAddress(&TPs);
    
    int j = eventTree->GetEntriesFast();
    for (int k = 0; k<j; k++){
        eventTree->GetEvent(k);
//        if(i>10000)
//            break;
        std::cout<<"________________________________________________ event number : "<<i+1<<std::endl;
//        if(isTtBar)
////            GoAhead =((TRootGenEvent*)pracEvt->GenEvtCollection()->At(0))->isSemiLeptonic(TRootGenEvent::kElec);
//            GoAhead =((TRootGenEvent*)genEvts->At(0))->isSemiLeptonic(TRootGenEvent::LeptonType(1));
//        if (!GoAhead)
//            continue;
        if(TPs->GetEntriesFast()>2){
            cout<<"Bad selection"<<endl;
            return 1;
        }
        for(unsigned int l = 0; l<TPs->GetEntriesFast(); l++){
            TRootTagProbeObject * tp = (TRootTagProbeObject*)TPs->At(l);
            cout<<tp->Pt()<<"\t"<<tp->Eta()<<endl;
            if(tp->PIndex.size() > 1){
                cout<<tp->PIndex.size()<<endl;
                return 1;
            }
            for(unsigned int y = 0; y<tp->PIndex.size(); y++){
                if(!(tp->Mass.at(y) > 76 && tp->Mass.at(y) < 106)){
                    cout<<tp->PIndex.at(y)<<"\t"<<tp->Mass.at(y)<<endl;
                    return 1;
                }
            }
        }
        i++;

    }

    delete F;
    cout<<i<<endl;
    cout<<j<<endl;
//    cout<<nElec<<endl;
//    cout<<nTP<<endl<<endl;
//    cout<<nMu<<endl;
//    cout<<nLooseMu<<endl<<endl;
//    cout<<nGenEvt<<endl<<endl;
//    cout<<nJetsFinal<<endl;
//    cout<<nJetsGolden<<endl<<endl;
//    cout<<nPV<<endl;

    return (EXIT_SUCCESS);
}

