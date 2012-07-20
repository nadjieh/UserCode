/* 
 * File:   HistogramCreator.C
 * Author: nadjieh
 *
 * Created on March 12, 2012, 2:51 PM
 */
//same as SelectAndSave with less complexities. Aimed to run on selected samples.

#include "TDirectory.h"
#include "../../interface/ElectronSelector.h"

#include "../../interface/Event.h"

#include "../../interface/ElectronHists.h"
#include "../../interface/MuonHists.h"
#include "../../interface/PVHists.h"
#include "../../interface/JetHists.h"
#include "../../interface/JetSelector.h"
#include "../../interface/MuonVetoSelector.h"
#include "../../interface/MetHists.h"
#include "../../interface/PrimaryVertexSelector.h"
#include "../../interface/BTagWeight.h"

#include "../../../PhysicsObjects/interface/SemiLepTopQuark.h"

#include "../../../../TopBrussels/TopTreeProducer/interface/TRootMuon.h"
#include "../../../../TopBrussels/TopTreeProducer/interface/TRootElectron.h"
#include "../../../../TopBrussels/TopTreeProducer/interface/TRootJet.h"
#include "../../../../TopBrussels/TopTreeProducer/interface/TRootCaloJet.h"
#include "../../../../TopBrussels/TopTreeProducer/interface/TRootPFJet.h"
#include "../../../../TopBrussels/TopTreeProducer/interface/TRootMET.h"
#include "../../../../TopBrussels/TopTreeProducer/interface/TRootGenEvent.h"
#include "../../../../TopBrussels/TopTreeProducer/interface/TRootNPGenEvent.h"
#include "../../../../TopBrussels/TopTreeProducer/interface/TRootEvent.h"
#include "../../../../TopBrussels/TopTreeProducer/interface/TRootRun.h"
#include "../../../../TopBrussels/TopTreeProducer/interface/TRootParticle.h"
#include "../../../../TopBrussels/TopTreeProducer/interface/TRootMCParticle.h"
#include "../../../../TopBrussels/TopTreeProducer/interface/TRootVertex.h"
#include "../../../../TopBrussels/TopTreeProducer/interface/TRootHLTInfo.h"
#include "../../../../AnalysisClasses/EventSelection/interface/PracticalEvent.h"
#include "../../../../AnalysisClasses/ToyAnalysis/interface/GenSingleTopMaker.h"
#include "../../../../TopBrussels/TopTreeAnalysis/MCInformation/interface/Lumi3DReWeighting.h"




#include <sstream>
#include <string>

#include <TApplication.h>
#include <TFile.h>
#include <TH1.h>
#include <TH2.h>
#include <TCanvas.h>
#include <TBranch.h>
#include <TTree.h>
#include <TSystem.h>
#include <vector>
using namespace std;
using namespace TopTree;
/*
 * 
 */
class SingleTopHistograms{
public:
    SingleTopHistograms(string name):Name(name){
        Wmass = new TH1D(string(name+"_Wmass").c_str(),string(name+": final-W-mass").c_str(),50, 0.,200.);
        Wmass->GetXaxis()->SetTitle("M_{W}");
        WmassII = new TH1D(string(name+"_WmassMET").c_str(),string(name+": final-W-mass (MET)").c_str(),50, 0.,200.);
        WmassII->GetXaxis()->SetTitle("M_{W}");
        topMass = new TH1D(string(name+"_topMass").c_str(),string(name+": final-top-mass").c_str(),50, 50.,500.);
        topMass->GetXaxis()->SetTitle("M_{top}");
        topMassII = new TH1D(string(name+"_topMassMET").c_str(),string(name+": final-top-mass (MET)").c_str(),50, 50.,500.);
        topMassII->GetXaxis()->SetTitle("M_{top}");
        cosTheta = new TH1D(string(name+"cosTheta").c_str(),string(name+": cos(#theta)").c_str(),50, -1.,1.);
        cosTheta->GetXaxis()->SetTitle("cos(#theta*)");
        cosThetaII = new TH1D(string(name+"cosTheta_MET").c_str(),string(name+": cos(#theta) (MET)").c_str(),50, -1.,1.);
        cosThetaII->GetXaxis()->SetTitle("cos(#theta*)");
        cosTheta2D = new TH2D(string(name+"cosTheta2D").c_str(),string(name+": cos(#theta); cos(#theta)_{gen}; cos(#theta)_{rec}").c_str(),50, -1.,1.,50, -1.,1.);
        cosTheta2DII = new TH2D(string(name+"cosTheta2D_MET").c_str(),string(name+": cos(#theta) (MET); cos(#theta)_{gen}; cos(#theta)_{rec}").c_str(),50, -1.,1.,50, -1.,1.);
        semiEcosTheta = new TH1D(string(name+"semiEcosTheta").c_str(),string(name+": cos(#theta)").c_str(),50, -1.,1.);
        semiEcosTheta->GetXaxis()->SetTitle("cos(#theta*)");
        semiTaucosTheta = new TH1D(string(name+"semiTaucosTheta").c_str(),string(name+": cos(#theta)").c_str(),50, -1.,1.);
        semiTaucosTheta->GetXaxis()->SetTitle("cos(#theta*)");
        diTaucosTheta = new TH1D(string(name+"diTaucosTheta").c_str(),string(name+": cos(#theta)").c_str(),50, -1.,1.);
        diTaucosTheta->GetXaxis()->SetTitle("cos(#theta*)");
        diEcosTheta = new TH1D(string(name+"diEcosTheta").c_str(),string(name+": cos(#theta)").c_str(),50, -1.,1.);
        diEcosTheta->GetXaxis()->SetTitle("cos(#theta*)");
        diMucosTheta = new TH1D(string(name+"diMucosTheta").c_str(),string(name+": cos(#theta)").c_str(),50, -1.,1.);
        diMucosTheta->GetXaxis()->SetTitle("cos(#theta*)");
        MuEcosTheta = new TH1D(string(name+"MuEcosTheta").c_str(),string(name+": cos(#theta)").c_str(),50, -1.,1.);
        MuEcosTheta->GetXaxis()->SetTitle("cos(#theta*)");
        TauEcosTheta = new TH1D(string(name+"TauEcosTheta").c_str(),string(name+": cos(#theta)").c_str(),50, -1.,1.);
        TauEcosTheta->GetXaxis()->SetTitle("cos(#theta*)");
        MuTaucosTheta = new TH1D(string(name+"MuTaucosTheta").c_str(),string(name+": cos(#theta)").c_str(),50, -1.,1.);
        MuTaucosTheta->GetXaxis()->SetTitle("cos(#theta*)");
        fullHadcosTheta = new TH1D(string(name+"fullHadcosTheta").c_str(),string(name+": cos(#theta)").c_str(),50, -1.,1.);
        fullHadcosTheta->GetXaxis()->SetTitle("cos(#theta*)");
       
    };
    ~SingleTopHistograms(){};
    void Fill(SemiLepTopQuark myLeptonicTop, double  lumiWeight3D = 1, GenSingleTopMaker* genTop = 0){
        Wmass->Fill(myLeptonicTop.W().M(),lumiWeight3D);
        topMass->Fill(myLeptonicTop.top().M(),lumiWeight3D);
        WmassII->Fill(myLeptonicTop.W(2).M(),lumiWeight3D);
        topMassII->Fill(myLeptonicTop.top(2).M(),lumiWeight3D);
        cout<<genTop->isSemiMuSingleTop<<endl;
        if(genTop == 0){
            cout<<"I am data like!!!"<<endl;
            cosTheta->Fill(myLeptonicTop.cosThetaStar(),lumiWeight3D);
            cosThetaII->Fill(myLeptonicTop.cosThetaStar(2),lumiWeight3D);
        }else if(!genTop->isSemiMuSingleTop){//cout<<"//Other top decays"<<endl;
            cosTheta->Fill(myLeptonicTop.cosThetaStar(),lumiWeight3D);
            cosThetaII->Fill(myLeptonicTop.cosThetaStar(2),lumiWeight3D);
        }else if(genTop->genSingleTop.MuCharge() != myLeptonicTop.MuCharge()){//cout<<"// fake muons"<<endl;
            cosTheta->Fill(myLeptonicTop.cosThetaStar(),lumiWeight3D);
            cosThetaII->Fill(myLeptonicTop.cosThetaStar(2),lumiWeight3D);
        }else{
            //cout<<"// OK"<<endl;
            cosTheta2D->Fill(genTop->genSingleTop.cosThetaStar(0),myLeptonicTop.cosThetaStar(), lumiWeight3D);
            cosTheta2DII->Fill(genTop->genSingleTop.cosThetaStar(0),myLeptonicTop.cosThetaStar(2), lumiWeight3D);
        }
        if(genTop != 0){
            if(genTop->isDiETt)
                diEcosTheta->Fill(myLeptonicTop.cosThetaStar(),lumiWeight3D);
            else if(genTop->isDiMuTt)
                diMucosTheta->Fill(myLeptonicTop.cosThetaStar(),lumiWeight3D);
            else if(genTop->isDiTauTt)
                diTaucosTheta->Fill(myLeptonicTop.cosThetaStar(),lumiWeight3D);
            else if(genTop->isSemiTauTt)
                semiTaucosTheta->Fill(myLeptonicTop.cosThetaStar(),lumiWeight3D);
            else if(genTop->isSemiElecTt)
                semiEcosTheta->Fill(myLeptonicTop.cosThetaStar(),lumiWeight3D);
            else if(genTop->isMuETt)
                MuEcosTheta->Fill(myLeptonicTop.cosThetaStar(),lumiWeight3D);
            else if(genTop->isMuTauTt)
                MuTaucosTheta->Fill(myLeptonicTop.cosThetaStar(),lumiWeight3D);
            else if(genTop->isETauTt)
                TauEcosTheta->Fill(myLeptonicTop.cosThetaStar(),lumiWeight3D);
            else if(genTop->isFullHadTt)
                fullHadcosTheta->Fill(myLeptonicTop.cosThetaStar(),lumiWeight3D);
        }
    }
    void Write(TDirectory * dir){
        TDirectory * inDir = dir->mkdir(Name.c_str());
        inDir->cd();
        cosTheta->Write();
        Wmass->Write();
        topMass->Write();
        cosThetaII->Write();
        WmassII->Write();
        topMassII->Write();
        cosTheta2D->Write();
        cosTheta2DII->Write();
        (inDir->mkdir("ttDecayModes"))->cd();
        semiEcosTheta->Write();
        semiTaucosTheta->Write();
        diTaucosTheta->Write();
        diEcosTheta->Write();
        diMucosTheta->Write();
        MuEcosTheta->Write();
        TauEcosTheta->Write();
        MuTaucosTheta->Write();
        fullHadcosTheta->Write();
        inDir->cd();
        dir->cd();
    }
    string Name;
    TH1D * Wmass;
    TH1D * WmassII;
    TH1D * topMass;
    TH1D * topMassII;
    TH1D * cosTheta;
    TH1D * cosThetaII;
    TH2D * cosTheta2D;
    TH2D * cosTheta2DII;
    TH1D * semiEcosTheta;
    TH1D * semiTaucosTheta;
    TH1D * diTaucosTheta;
    TH1D * diEcosTheta;
    TH1D * diMucosTheta;
    TH1D * MuEcosTheta;
    TH1D * TauEcosTheta;
    TH1D * MuTaucosTheta;
    TH1D * fullHadcosTheta;

};
int main(int argc, char** argv) {

    PVHists atLeastOnGPV("final_PV");
    JetHists Jets("final_Jet",2);
    JetHists BJets("final_BJet",2);
    JetHists nonBJets("final_nonBJet",2);
    JetHists Light("final_Light",2);
    MuonHists GoldenFinalPUMuons("final_Muon");
    MetHists MetHist("finalMet");
    
    SingleTopHistograms Default("Default");
    SingleTopHistograms EtaCut("EtaFwD");
    SingleTopHistograms HtCut("HtCut");
    SingleTopHistograms AntiEtaCut("antiEtaFwD");
    SingleTopHistograms AntiHtCut("antiHtCut");
    
    SingleTopHistograms DefaultTrue("DefaultTrue");
    SingleTopHistograms EtaCutTrue("EtaFwDTrue");
    SingleTopHistograms HtCutTrue("HtCutTrue");
    SingleTopHistograms AntiEtaCutTrue("antiEtaFwDTrue");
    SingleTopHistograms AntiHtCutTrue("antiHtCutTrue");

    TH1D * HT = new TH1D("HT","H_{T};H_{T}(GeV)",500, 0.,500.);
    TH1D * finalMT = new TH1D("finalMT","final-W-neutrino transverse mass",100, 0.,200.);
    finalMT->GetXaxis()->SetTitle("M_{T}(W,#nu)");
    TH1D * delNu = new TH1D("delNu","delNu",100, 0.,100.);
    delNu->GetXaxis()->SetTitle("#Delta#nu");
    TH1D * delNuII = new TH1D("delNuMET","delNuMET",100, 0.,100.);
    delNuII->GetXaxis()->SetTitle("#Delta#nu");
    std::vector<std::string> inputFileNames;
    std::string plotFileName;
    int verbosity = 0;
    TH1D * METResolutions = 0;
    std::string HLTname = "HLT_IsoMu17_v*";
    bool pu3D =true;
    string PUWeightFileName="";
    double XSec = 1; double Luminosity = 1; double PreSelEff = 1; double doJES = 1;
    bool isData = false;
    int smearingSkim = 1;
    for (int f = 1; f < argc; f++) {
        std::string arg_fth(*(argv + f));

        if (arg_fth == "out") {
          f++;
          std::string out(*(argv + f));
	  plotFileName = out;
        }else if (arg_fth == "input") {
          f++;
          std::string in(*(argv + f));
          inputFileNames.push_back(string("~/work/samples/"+in));
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
            if(in == "yes" || in == "YES" || in == "Yes" || in == "y" || in == "Y")
		isData = true;
	    else
		isData = false;
        }else if (arg_fth == "METResolFileName") {
            f++;
            std::string in(*(argv + f));
            TFile * METResolFileName = TFile::Open(in.c_str());
            METResolutions = (TH1D*) METResolFileName->Get("METresolutions");
        }else if (arg_fth == "HLTname") {
            f++;
            std::string in(*(argv + f));
            HLTname = in;
            std::cout<<HLTname<<endl;
        }else if (arg_fth == "PUWeightFileName") {
            f++;
            std::string in(*(argv + f));
            PUWeightFileName = in;
            std::cout<<HLTname<<endl;
        }else if (arg_fth == "smearingSkim") {
            f++;
            std::string in(*(argv + f));
            smearingSkim = atof(in.c_str());
        }
    }
    
    TFile* f = 0;
    TApplication theApp("App", &argc, argv);
    double nInit = 0;
    double nFinalPU = 0;
    double nFinalHLT = 0;
    double nFinalbTag = 0;
    double nFinal = 0;
    double nHLTrunB = 0;
    double nMt = 0;
    double nGoodSolution = 0;
    Lumi3DReWeighting Lumi3DWeights;
    if(pu3D){
//        Lumi3DWeights.weight3D_set("../../../../TopBrussels/TopTreeAnalysis/macros/PileUpReweighting//MC_Fall11.root",
//    "../../../../TopBrussels/TopTreeAnalysis/macros/PileUpReweighting/RunAB.root", "pileup", "pileup");
        Lumi3DWeights.weight3D_set("../../../../TopBrussels/TopTreeAnalysis/macros/PileUpReweighting//MC_Fall11.root",
    "../../../../TopBrussels/TopTreeAnalysis/macros/PileUpReweighting/runA_finebin_Pileup_unPrescaledIsoMu17_true.root", "pileup", "pileup");
        Lumi3DWeights.setWFileName(PUWeightFileName);
        Lumi3DWeights.weight3D_init(1.0);
//    Lumi3DWeights.weight3D_init(PUWeightFileName);
    }
    TFile * HLTweights = TFile::Open("../HLT_IsoMu17_W.root");
    TH1D * HLTWeights = (TH1D*)HLTweights->Get("weight");
    GenSingleTopMaker* genSingleTop = 0;
    for(unsigned int fNumber = 0; fNumber<inputFileNames.size(); fNumber++){
        cout<<"file number "<<fNumber+1<<": "<<inputFileNames.at(fNumber)<<endl;
        f = TFile::Open(inputFileNames.at(fNumber).c_str());
        
        TTree* runTree = (TTree*) f->Get("runTree");
        TTree* eventTree = (TTree*) f->Get("eventTree");


        
        PracticalEvent * pracEvt = new PracticalEvent(eventTree,runTree);
        pracEvt->eventTree->SetBranchStatus("*", 1);

        std::cout<<"beforeLoop"<<std::endl;

        int ievt = 0;
        
        while (pracEvt->Next()) {
//
//            if(ievt > 2)
//                break;
            /* for single top genAnalysis
             * not to be used for real one
             */
            if(!isData && pracEvt->NPGenEvtCollection() != 0){
//                cout<<"I am here"<<endl;
                    genSingleTop = new GenSingleTopMaker((TRootNPGenEvent*)pracEvt->NPGenEvtCollection()->At(0), verbosity);
            }
            double lumiWeight3D = 1;
            if(pu3D){


                if(!isData){
        //            cout<<"here I am ... "<<pracEvt->Event()<<endl;
                    lumiWeight3D = Lumi3DWeights.weight3D(pracEvt->Event());
                } else lumiWeight3D = 1;
            }
//            cout<<lumiWeight3D<<endl;
            nInit+=lumiWeight3D;
//            nInit++;
            ievt++;
            if(verbosity > 0)
                cout<<"*******************************************************************"<<endl;

            std::vector<TRootPFJet>  myJets_;
            myJets_.clear();
//            cout<<"I am going to Jet Correction "<<isData<<endl;
            myJets_ = pracEvt->ScaledPFJetCollection(1,isData);

            Event myEvent_tmp( myJets_, *pracEvt->ElectronCollection()
            ,pracEvt->TypeICorrMET(),*pracEvt->MuonCollection(),*pracEvt->VertexCollection());
            if(verbosity > 0)
                cout<<"PV size: "<<myEvent_tmp.pvs.size()<<"\n"
                    <<"Muon size: "<<myEvent_tmp.muons.size()<<"\n"
                    <<"Electron size: "<<myEvent_tmp.electrons.size()<<"\n"
                    <<"Jet size: "<<myEvent_tmp.PFJets.size()<<"\n"<<endl;
            myEvent_tmp.verbose(verbosity);
            if(verbosity > 0)
                cout<<"ScrapFilterMaker-------------------------------------------------------------------"<<endl;
            double scrapFilterer = (double)(pracEvt->Event()->nHighPurityTracks())/(double)(pracEvt->Event()->nTracks());
            if(verbosity > 0)
                cout<<"HBHEnoiseFilterMaker-------------------------------------------------------------------"<<endl;//?????
            if(verbosity > 0)
                cout<<"Vertex Makers ---------------------------------------------------------------------"<<endl;
            myEvent_tmp.VertexMaker();
            if(verbosity > 0)
                cout<<"Electron Maker ---------------------------------------------------------------------"<<endl;
            myEvent_tmp.ElectronMaker();
            /*pt = 30., eta = 2.5,  Exc_Low = 1.4442 , Exc_High = 1.5660, Id = "VBTF70", IdSecond = "VBTF95" (not applied),
             * D0 = 0.02, IsoCut = 0.125, drToPV = 10000.,  secondEIso = 0.2, secPt=15 GeV 
             */
            
                  
            if(verbosity > 0)
                cout<<"Jet Makers ---------------------------------------------------------------------"<<endl;
            myEvent_tmp.PFJetMaker(/*bTagAlgo*/"TCHP",/*pt*/30.,/*eta*/4.5);
            if(verbosity > 0)
                cout<<"Muon Maker ---------------------------------------------------------------------"<<endl;
            myEvent_tmp.MuonMaker();
            /*
             * pt = 20.,  eta = 2.1, chi2 = 10,  D0 = 0.02,  nvh = 10, isoCut_ = 0.15,  doGL = false,  
             * nPixWithMeasuredHits = 1,  nSegM = 1
             */
            if(verbosity > 0)
                cout<<"START TO SELECT : "<<endl;
            if(scrapFilterer > 0.2){
                if(verbosity>0)
                    cout<<"\tPassed!! scrapFilterer is "<<scrapFilterer<<endl;
            }else
                continue;

//            TopTree::TRootHLTInfo hltInfo = pracEvt->RunInfo()->getHLTinfo(pracEvt->Event()->runId());
//            int trigID = hltInfo.hltPath(HLTname);
//
//            if(pracEvt->Event()->trigHLT(trigID)){
////		nHLTrunB++;
//		nHLTrunB+=lumiWeight3D;
//                if(verbosity > 0){
//                    cout<<hltInfo.hltNames(trigID)<<"\t"<<hltInfo.hltWasRun(trigID)<<
//                    "\t"<<hltInfo.hltAccept(trigID)<<endl;
//                    cout<<"\tHLT is passed"<<endl;
//                }
//            }else 
//                continue;
            
            if(myEvent_tmp.Gpvs.size() > 0){
                if(verbosity > 0)
                    cout<<"\tPVCut Passed"<<endl;
            } else
                continue;

            if(myEvent_tmp.Dmuons.size() == 1){
                if(verbosity > 0)
                    cout<<"\tMu selection Passed"<<endl;
            } else
                continue;

            if(myEvent_tmp.looseMuons.size()==0){
                if(verbosity > 0)
                    cout<<"\tlooseMuVeto is passed"<<endl;
            }else 
                continue;

            if(myEvent_tmp.Gelectrons.size()==0 && myEvent_tmp.Secondelectrons.size()==0){
                if(verbosity > 0)
                    cout<<"\tlooseEVeto is passed"<<endl;
            }else 
                continue;

            if(myEvent_tmp.GPFJets.size() == 2){		
                if(verbosity > 0){
                        cout<<"\t==2 Jet Passed"<<endl;
                }
            } else
                continue;
            double mt = 0;
            double metT = sqrt((myEvent_tmp.mets.at(0).Px()*myEvent_tmp.mets.at(0).Px())+
                            (myEvent_tmp.mets.at(0).Py()*myEvent_tmp.mets.at(0).Py()));

            double muT =  sqrt((myEvent_tmp.Dmuons.at(0).Px()*myEvent_tmp.Dmuons.at(0).Px())+
                            (myEvent_tmp.Dmuons.at(0).Py()*myEvent_tmp.Dmuons.at(0).Py()));
            mt = sqrt(pow(muT+metT,2) - pow(myEvent_tmp.mets.at(0).Px()+myEvent_tmp.Dmuons.at(0).Px(),2)
                                                - pow(myEvent_tmp.mets.at(0).Py()+myEvent_tmp.Dmuons.at(0).Py(),2));
            if(mt>40){
//                nMt++;
                nMt+=lumiWeight3D;
                if(verbosity>0)
                    cout<<"\tM_T cut is passed"<<endl;
            }else
                continue;

            if(myEvent_tmp.BPFJets.size() == 1){
                if(verbosity > 0)
                    cout<<"\t== 1bTag Passed"<<endl;
            } else
                continue;
            /*btag sf*/
            nFinalPU+=lumiWeight3D;
//            cout<<"pu: "<<lumiWeight3D<<"\t";
	    double bw = 1;
	    if(!isData){
                double sf, eff;
                BTagWeight myBtagWeight;
                vector< vector<BTagWeight::JetInfo> > jInfosToReWeight(myEvent_tmp.GPFJets.size());
                for (int iJet = 0; iJet < myEvent_tmp.GPFJets.size(); iJet++) {
                    BTagWeight::GetEffSF_TCHPT(myEvent_tmp.GPFJets[iJet].Pt(), 
                                            myEvent_tmp.GPFJets[iJet].Eta(), 
                                            myEvent_tmp.GPFJets[iJet].btag_trackCountingHighPurBJetTags(),
                                            myEvent_tmp.GPFJets[iJet].partonFlavour(),
                                            eff, sf , 0);
                    BTagWeight::JetInfo jinfo(eff, sf);
                    jInfosToReWeight[iJet].push_back(jinfo);
                }
                bw *= myBtagWeight.weight(jInfosToReWeight);
	    }
//            cout<<"bw: "<<bw<<"\t";
            lumiWeight3D *= bw;

            nFinalbTag+=bw;
            /*HLT sf*/
	    double hltW = 1;
//	    if(!isData){
//                int bin = HLTWeights->GetXaxis()->FindBin(myEvent_tmp.Dmuons.at(0).Eta());
//                hltW=HLTWeights->GetBinContent(bin);
//	    }
            lumiWeight3D*=hltW;
//            cout<<"hlt: "<<hltW<<endl;
            nFinalHLT+=hltW;
            
            nFinal+=lumiWeight3D;
            
            int mySecondJetIndex = 0;
            if(mySecondJetIndex == myEvent_tmp.firstBtagIndex)
                mySecondJetIndex = 1;
            std::vector<TRootPFJet> nonBs ; nonBs.push_back(myEvent_tmp.GPFJets.at(mySecondJetIndex));
            std::vector<TRootPFJet> sortedJetsbyEta; sortedJetsbyEta.push_back(myEvent_tmp.SortedJetsByEta().at(0));
            //Reweighting process
            SemiLepTopQuark myLeptonicTop(myEvent_tmp.BPFJets.at(0),myEvent_tmp.mets.at(0),myEvent_tmp.Dmuons.at(0),
                    myEvent_tmp.GPFJets.at(mySecondJetIndex), sortedJetsbyEta.at(0),METResolutions);
            myLeptonicTop.setMuCharge((int)myEvent_tmp.Dmuons.at(0).charge());
            double eta = fabs(sortedJetsbyEta.at(0).Eta());
            double ht = myEvent_tmp.GPFJets.at(0).Pt()+ myEvent_tmp.GPFJets.at(1).Pt();
            
            
            ht+=myEvent_tmp.Dmuons.at(0).Pt();
            ht+=myEvent_tmp.mets.at(0).Pt();
            HT->Fill(ht,lumiWeight3D);
            if(myLeptonicTop.hasNeutrinoSolution()){
                nGoodSolution++;
                DefaultTrue.Fill(myLeptonicTop,lumiWeight3D,genSingleTop);
                if(ht >= 180)
                    HtCutTrue.Fill(myLeptonicTop,lumiWeight3D,genSingleTop);
                else
                    AntiHtCutTrue.Fill(myLeptonicTop,lumiWeight3D,genSingleTop);
                if(eta > 1.5)
                    EtaCutTrue.Fill(myLeptonicTop,lumiWeight3D,genSingleTop);
                else
                    AntiEtaCutTrue.Fill(myLeptonicTop,lumiWeight3D,genSingleTop);                    
            }
            Default.Fill(myLeptonicTop,lumiWeight3D,genSingleTop);
            if(ht >= 180)
                HtCut.Fill(myLeptonicTop,lumiWeight3D,genSingleTop);
            else
                AntiHtCut.Fill(myLeptonicTop,lumiWeight3D,genSingleTop);
            if(eta > 1.5)
                EtaCut.Fill(myLeptonicTop,lumiWeight3D,genSingleTop);
            else
                AntiEtaCut.Fill(myLeptonicTop,lumiWeight3D,genSingleTop); 
            
            if(genSingleTop != NULL)
                delete genSingleTop;

//            atLeastOnGPV.Fill(myEvent_tmp.Gpvs,myEvent_tmp.Gpvs.size(),lumiWeight3D);
//            GoldenFinalPUMuons.Fill(myEvent_tmp.Dmuons,myEvent_tmp.Dmuons.size(),lumiWeight3D);
//            Jets.FillPFJets(myEvent_tmp.GPFJets,myEvent_tmp.GPFJets.size(),myEvent_tmp.BPFJets.size(),false,lumiWeight3D);
//            BJets.FillPFJets(myEvent_tmp.BPFJets,myEvent_tmp.BPFJets.size(),myEvent_tmp.BPFJets.size(),false,lumiWeight3D);
//
//            MetHist.Fill(&myEvent_tmp.mets.at(0),lumiWeight3D);
//            finalMT->Fill(mt,lumiWeight3D);


            

        }

        cout<<"before closing file input "<<f->GetName()<<endl;
        f->Close();
        delete f;

    }
    cout<<"before endjob"<<endl;
    TFile * fout = new TFile(plotFileName.c_str(),"recreate");
    fout->cd();
//    atLeastOnGPV.WriteAll(fout);
//    GoldenFinalPUMuons.WriteAll(fout);
//    Jets.WriteAll(fout);
//    BJets.WriteAll(fout);
//    MetHist.WriteAll(fout);  
//    finalMT->Write();
//    Default.Write(fout);
    Default.Write(fout);
    EtaCut.Write(fout);
    AntiEtaCut.Write(fout);
    HtCut.Write(fout);
    AntiHtCut.Write(fout);
    DefaultTrue.Write(fout);
    EtaCutTrue.Write(fout);
    AntiEtaCutTrue.Write(fout);
    HtCutTrue.Write(fout);
    AntiHtCutTrue.Write(fout);
    HT->Write();
    fout->Write();
    fout->Close();
    
    cout<<nInit<<"\n"<<nHLTrunB<<"\n"<<nMt<<"\n"<<nFinal<<endl;
    cout<<"only pu weight:\t"<<nFinalPU<<"\n"<<"only btag sf:\t"<<nFinalbTag<<endl;
    cout<<"only HLT weight:\t"<<nFinalHLT<<"\n"<<"all sf's:\t"<<nFinal<<endl;
    return 0;
}

