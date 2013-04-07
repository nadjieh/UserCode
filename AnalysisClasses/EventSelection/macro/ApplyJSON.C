/* 
 * File:   ApplyJSON.C
 * Author: nadjieh
 *
 * Created on March 11, 2012, 12:02 PM
 */
#include "../interface/JSONHandler.h"
#include "../interface/PracticalEvent.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootEvent.h"
#include <string>
#include "TFile.h"
#include "TApplication.h"
#include "TTree.h"
using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    string outFileName;
    string JSONFileName;
    vector<string> inputs;
    for (int f = 1; f < argc; f++) {
        std::string arg_fth(*(argv + f));

        if (arg_fth == "out") {
            f++;
            std::string out(*(argv + f));
            outFileName = string(out+".root");
        }else if(arg_fth == "input"){
            f++;
            std::string in(*(argv + f));
            inputs.push_back(string("~/work/samples/"+in));
        }else if(arg_fth == "json"){
            f++;
            std::string in(*(argv + f));
            JSONFileName = in;
        }
    }

    TFile* f = 0;
    TFile* outFile = 0;
    TApplication theApp("App", &argc, argv);
    JSONHandler myJSON(0);
    myJSON.readJSON(JSONFileName);
//    myJSON.printJSON();
    
//    myJSON.setPrescaledRunLumis();
    TTree * eventTree_f = 0;
    TTree * runTree_f = 0;
    for(unsigned int fNumber = 0; fNumber<inputs.size(); fNumber++){
        cout<<inputs.at(fNumber)<<endl;
        f = TFile::Open(inputs.at(fNumber).c_str());
        
        TTree* runTree = (TTree*) f->Get("runTree");
        TTree* eventTree = (TTree*) f->Get("eventTree");

        PracticalEvent * pracEvt = new PracticalEvent(eventTree,runTree);
        pracEvt->eventTree->SetBranchStatus("*", 1);

        //initiate the output file
        stringstream s("");
        s/*<<(fNumber+1)<<"_"*/<<outFileName;
        outFile = new TFile(s.str().c_str(), "recreate");
        outFile->cd();
        eventTree_f = pracEvt->eventTree->CloneTree(0);
        runTree_f = pracEvt->runTree->CloneTree(0);

        int ievt = 0;
        while (pracEvt->Next()) {
            ievt++;

//            if(ievt > 1000)
//		break;
//            cout<<"------------------------------ eventNumber "<<ievt<<endl;

            if(!myJSON.isSelectedByJSON(pracEvt->Event())){
                cout<<"event is rejected:\n\tRunId: "<<pracEvt->Event()->runId()<<
                      "\tLumiId: "<<pracEvt->Event()->lumiBlockId()<<endl;
                continue;
            }
            eventTree_f->Fill();
        }
        runTree_f->Fill();
        cout<<"before closing file input "<<f->GetName()<<endl;
        f->Close();
        delete f;

        outFile->cd();
        outFile->Write();
        outFile->Close();
    }

    return 0;
}

