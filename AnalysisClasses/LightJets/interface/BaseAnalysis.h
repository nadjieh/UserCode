/* 
 * File:   MyAnalysis.h
 * Author: ajafari
 *
 * Created on July 6, 2010, 4:29 PM
 */

#ifndef _MYANALYSIS_H
#define	_MYANALYSIS_H
#include <vector>

#include <iostream>
#include <iomanip>
#include "../../../TopBrussels/TopTreeProducer/interface/TRootMuon.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootElectron.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootCaloJet.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootJet.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootMET.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootGenEvent.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootNPGenEvent.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootEvent.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootRun.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootMCParticle.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootParticle.h"



#include "../../../AnalysisClasses/ChiSquared/interface/TopEvent.h"
#include "../../../AnalysisClasses/ChiSquared/interface/Combinator.h"
#include "../../../AnalysisClasses/ChiSquared/interface/ExtendedJet.h"



#include <sstream>
#include <iostream>
#include <string>
#include <TFile.h>
#include <TSystem.h>
#include <TProfile.h>
#include <TH1.h>
#include <TH2.h>
#include <bits/stl_vector.h>
#include <TCanvas.h>
#include <TDirectory.h>
#include <TBranch.h>
#include <TTree.h>
#include <vector>
#include <TLorentzVector.h>
#include <stdexcept>

#include "../../../AnalysisClasses/ChiSquared/interface/DR.h"
#include "../../../AnalysisClasses/EventSelection/interface/PracticalEvent.h"
#include "../../../AnalysisClasses/EventSelection/interface/GoodObjects.h"
#include "../../../AnalysisClasses/ChiSquared/interface/BaseRegion.h"





using namespace std;
using namespace TopTree;



class BaseAnalysis {
public:

    BaseAnalysis(std::string anaName, double LEL, double HEL,double LER, double HER,
    double chi2cut, double topPtcut) :
    Name(anaName),
    chi2Cut(chi2cut),
    TopPtCut(topPtcut){
        if(!((LEL < HEL) && (HEL <= LER) && (LER < HER)))
            throw new RegionConflictException("BAD BOUNDERIES");
        Edges.clear();
        Edges.push_back(LEL);
        Edges.push_back(HEL);
        Edges.push_back(LER);
        Edges.push_back(HER);
        bTag_Mlb = new TProfile(string(anaName+"_bTag_Mlb_forBoundries").c_str(),"#Delta_{b} vs M_{l,b candidate}",100,0.,1000.,-200.,60.);
        bTag_Mlb->GetXaxis()->SetTitle("M_{l,b candidate}");
        bTag_Mlb->GetYaxis()->SetTitle("#Delta_{b}");
        verbosity = 0;
        path = "./";
    };
    virtual ~BaseAnalysis(){};
    void AddWeighedHandlersToRightRegion(SpecificEffHandler<ExtendedJet> * handler){
        R->AddHandler(handler);
    }
    void setVerbosity(int v){
        verbosity = v;
        cout<<"In Analysis "<<Name<<" verbosity is set to "<<verbosity<<endl;
        L->setVerbosity(v);
        R->setVerbosity(v);
        L->setVrbosityOfHandlers(v);
        R->setVrbosityOfHandlers(v);
    }
    void setRegionsVerbosity(){
        L->setVerbosity(verbosity);
        R->setVerbosity(verbosity);
        L->setVrbosityOfHandlers(verbosity);
        R->setVrbosityOfHandlers(verbosity);
    };
    void WriteAll(TDirectory * dir) {
        if (dir == 0)
            return;
        if(verbosity > 0)
                std::cout<<"========= In BaseAnalysis::WriteAll method of \t\n"<<Name<<std::endl;
        TDirectory* my_dir = dir->mkdir(Name.c_str());
        my_dir->cd();
        L->WriteAll(my_dir);
        R->WriteAll(my_dir);
        my_dir->cd();
        bTag_Mlb->Write();
        dir->cd();
    };
    virtual void Fill(TopEvent input, double weight = 1.) {//MC
        if(input.getTopChiSquared() >= chi2Cut || input.getHadronicTop().Pt() <= TopPtCut){
            if(verbosity > 0){
                cout<<"\tTopPtCut or chi2Cut is not passed\n\t\t"<<
                        input.getHadronicTop().Pt()<<" > (?) "<<TopPtCut<<"\n\t\t"<<
                        input.getTopChiSquared()<<" < (?) "<<chi2Cut<<endl;

            }
            return;
        }
        std::string whoamiL = L->WhoAmI();
        std::string whoamiR = R->WhoAmI();
        if (whoamiL != whoamiR)
            throw new RegionConflictException("REGIONS ARE NOT MATCHED");
        if(verbosity > 0)
                std::cout<<"In Fill of "<<whoamiL<<" "<<L->getName()<<std::endl;

        L->Fill(input, weight);

        if(verbosity > 0)
                std::cout<<"In Fill of "<<whoamiR<<" "<<R->getName()<<std::endl;
        R->Fill(input, weight);
        
    };
    double getF()const{
        return(L->F(R));
    };
    //private:
    std::vector<double> Edges;
    void SetPath(string p){
        path = p;
    }
    virtual void End(std::string outName, double f){
        L->Subtract(R,f);
//        cout<<"========= F: "<<f<<endl;
        TFile * out = new TFile(outName.c_str(), "recreate");
        out->cd();
        this->WriteAll(out);
        out->Close();
    };
    std::string WhoAmI()const {return "BaseAnalysis";};
    std::string getName()const{return Name;};
    void setName(std::string name){Name = name;};
    std::string Name;
    TProfile * bTag_Mlb; //to see the boundries
protected:
    BaseRegion* L;
    BaseRegion* R;
    int verbosity;
    double chi2Cut;
    double TopPtCut;
    string path;
public:
    virtual double Value(int id){
        return -1;
    }
    virtual double Error(int id){
        return -1;
    }
    virtual std::string GetVariableName(int id){
        return "-1";
    }
    virtual double NVariables(){
        return -1;
    }

};

#endif	/* _MYANALYSIS_H */

