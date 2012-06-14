/* 
 * File:   HistogramCreator.C
 * Author: nadjieh
 *
 * Created on March 12, 2012, 2:51 PM
 */
//same as SelectAndSave with less complexities. Aimed to run on selected samples.


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
#include "../../../../Base/BaseAnalysis/interface/EfficiencyHandler.h"
#include "../../../ToyAnalysis/interface/MyObjectProperties.h"




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
bool TrueCondition(const TRootPFJet * e){/*cout<<"I am here in all"<<endl;*/ return(true);}

int main(int argc, char** argv) {

    EfficiencyHandler<TRootPFJet> nonB("nonBEff");
    nonB.setVerbosity(0);
    nonB.AllCondition = 0;
    nonB.Condition = TrueCondition;
    nonB.setSelfEff();
    nonB.AddProp(new JetEta());

    EfficiencyHandler<TRootPFJet> B("BEff");
    B.setVerbosity(0);
    B.AllCondition = 0;
    B.Condition = TrueCondition;
    B.setSelfEff();
    B.AddProp(new JetEta());
    
    EfficiencyHandler<TRootPFJet> FwD("FwDEff");
    FwD.setVerbosity(0);
    FwD.AllCondition = 0;
    FwD.Condition = TrueCondition;
    FwD.setSelfEff();
    FwD.AddProp(new JetEta());
    
    PVHists atLeastOnGPV("final_PV");
    JetHists Jets("final_Jet",2);
    JetHists BJets("final_BJet",2);
    JetHists nonBJets("final_nonBJet",2);
    JetHists Light("final_Light",2);
    MuonHists GoldenFinalMuons("final_Muon");
    MetHists MetHist("finalMet");
    TH1D * finalMT = new TH1D("finalMT","final-W-neutrino transverse mass",100, 0.,200.);
    finalMT->GetXaxis()->SetTitle("M_{T}(W,#nu)");
    TH1D * Wmass = new TH1D("Wmass","final-W-mass",50, 0.,200.);
    Wmass->GetXaxis()->SetTitle("M_{W}");
    TH1D * WmassII = new TH1D("WmassMET","final-W-mass",50, 0.,200.);
    WmassII->GetXaxis()->SetTitle("M_{W}");
    TH1D * topMass = new TH1D("topMass","final-top-mass",50, 50.,500.);
    topMass->GetXaxis()->SetTitle("M_{top}");
    TH1D * topMassII = new TH1D("topMassMET","final-top-mass",50, 50.,500.);
    topMassII->GetXaxis()->SetTitle("M_{top}");
    TH1D * delNu = new TH1D("delNu","delNu",100, 0.,100.);
    delNu->GetXaxis()->SetTitle("#Delta#nu");
    TH1D * delNuII = new TH1D("delNuMET","delNuMET",100, 0.,100.);
    delNuII->GetXaxis()->SetTitle("#Delta#nu");
    TH1D * cosTheta = new TH1D("cosTheta","cos(#theta)",50, -1.,1.);
    cosTheta->GetXaxis()->SetTitle("cos(#theta*)");
    TH1D * cosThetaII = new TH1D("cosTheta_MET","cos(#theta)",50, -1.,1.);
    cosThetaII->GetXaxis()->SetTitle("cos(#theta*)");
    TH2D * cosTheta_EtaFwd = new TH2D("cosTheta_EtaFwd","cos(#theta*_{l}) vs. #eta_{Jet}^{Fwd}",500, 0.,5.,50, -1.,1. );
    cosTheta_EtaFwd->GetXaxis()->SetTitle("#eta_{Jet}^{Fwd}");
    cosTheta_EtaFwd->GetYaxis()->SetTitle("cos(#theta*_{l})");
    TH2D * cosTheta_EtaLight = new TH2D("cosTheta_EtaLight","cos(#theta*_{l}) vs. #eta_{Jet}^{Light}",500, 0.,5.,50, -1.,1. );
    cosTheta_EtaLight->GetXaxis()->SetTitle("#eta_{Jet}^{Light}");
    cosTheta_EtaLight->GetYaxis()->SetTitle("cos(#theta*_{l})");
    TH2D * cosTheta_Ht = new TH2D("cosTheta_Ht","cos(#theta*_{l}) vs. H_{T}(GeV)",500, 0.,500.,50, -1.,1. );
    cosTheta_Ht->GetXaxis()->SetTitle("H_{T}(GeV)");
    cosTheta_Ht->GetYaxis()->SetTitle("cos(#theta*_{l})");
    TH2D * EtaFwd_Ht = new TH2D("EtaFwd_Ht","|#eta_{FwdJet}| vs. H_{T}(GeV);H_{T}(GeV);|#eta_{FwdJet}|",500, 0.,500.,500, 0.,5. );
//    EtaFwd_Ht->GetXaxis()->SetTitle("H_{T}(GeV)");
//    EtaFwd_Ht->GetYaxis()->SetTitle("cos(#theta*_{l})");
    std::vector<std::string> inputFileNames;
    std::string plotFileName;
    int verbosity = 0;
    TH1D * METResolutions = 0;
    std::string HLTname = "HLT_IsoMu17_v*";
    bool pu3D =false;//true;
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
    double nFinal = 0;
    double nHLTrunB = 0;
    double nMt = 0;
    Lumi3DReWeighting Lumi3DWeights;
    if(pu3D){
//        Lumi3DWeights.weight3D_set("../../../../TopBrussels/TopTreeAnalysis/macros/PileUpReweighting//MC_Fall11.root",
//    "../../../../TopBrussels/TopTreeAnalysis/macros/PileUpReweighting/RunAB.root", "pileup", "pileup");
        Lumi3DWeights.weight3D_set("../../../../TopBrussels/TopTreeAnalysis/macros/PileUpReweighting//MC_Fall11.root",
    "../../../../TopBrussels/TopTreeAnalysis/macros/PileUpReweighting/pileup_2011Data_finebin_true.root", "pileup", "pileup");
        Lumi3DWeights.setWFileName(PUWeightFileName);
        Lumi3DWeights.weight3D_init(1.0);
//    Lumi3DWeights.weight3D_init(PUWeightFileName);
    }
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
//            if(ievt > 10)
//                break;
            /* for single top genAnalysis
             * not to be used for real one
             */
//            GenSingleTopMaker myGenSingleTop((TRootNPGenEvent*)pracEvt->NPGenEvtCollection()->At(0));
//            if(!myGenSingleTop.isSemiMuSingleTop)
//                continue;
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

            TopTree::TRootHLTInfo hltInfo = pracEvt->RunInfo()->getHLTinfo(pracEvt->Event()->runId());
            int trigID = hltInfo.hltPath(HLTname);

            if(pracEvt->Event()->trigHLT(trigID)){
//		nHLTrunB++;
		nHLTrunB+=lumiWeight3D;
                if(verbosity > 0){
                    cout<<hltInfo.hltNames(trigID)<<"\t"<<hltInfo.hltWasRun(trigID)<<
                    "\t"<<hltInfo.hltAccept(trigID)<<endl;
                    cout<<"\tHLT is passed"<<endl;
                }
            }else 
                continue;
            
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
//            nFinal++;
            nFinal+=lumiWeight3D;
            
            int mySecondJetIndex = 0;
            if(mySecondJetIndex == myEvent_tmp.firstBtagIndex)
                mySecondJetIndex = 1;
            
            double ht = myEvent_tmp.GPFJets.at(0).Pt()+ myEvent_tmp.GPFJets.at(1).Pt();
            ht+=myEvent_tmp.Dmuons.at(0).Pt();
            ht+=myEvent_tmp.mets.at(0).Pt();
            //Reweighting process
//            SemiLepTopQuark myLeptonicTop(myEvent_tmp.BPFJets.at(0),myEvent_tmp.mets.at(0),myEvent_tmp.Dmuons.at(0),
//                    myEvent_tmp.GPFJets.at(mySecondJetIndex),METResolutions);
            
            
            std::vector<TRootPFJet> nonBs ; nonBs.push_back(myEvent_tmp.GPFJets.at(mySecondJetIndex));
            std::vector<TRootPFJet> sortedJetsbyEta; sortedJetsbyEta.push_back(myEvent_tmp.SortedJetsByEta().at(0));
            atLeastOnGPV.Fill(myEvent_tmp.Gpvs,myEvent_tmp.Gpvs.size(),lumiWeight3D);
            GoldenFinalMuons.Fill(myEvent_tmp.Dmuons,myEvent_tmp.Dmuons.size(),lumiWeight3D);
            Jets.FillPFJets(myEvent_tmp.GPFJets,myEvent_tmp.GPFJets.size(),myEvent_tmp.BPFJets.size(),false,lumiWeight3D);
            BJets.FillPFJets(myEvent_tmp.BPFJets,myEvent_tmp.BPFJets.size(),myEvent_tmp.BPFJets.size(),false,lumiWeight3D);
            nonBJets.FillPFJets(nonBs,nonBs.size(),myEvent_tmp.BPFJets.size(),false,lumiWeight3D);
            Light.FillPFJets(sortedJetsbyEta,sortedJetsbyEta.size(),myEvent_tmp.BPFJets.size(),false,lumiWeight3D);
            MetHist.Fill(&myEvent_tmp.mets.at(0),lumiWeight3D);
            finalMT->Fill(mt,lumiWeight3D);
            nonB.Fill(&nonBs.at(0),lumiWeight3D);
            B.Fill(&myEvent_tmp.BPFJets.at(0),lumiWeight3D);
            FwD.Fill(&sortedJetsbyEta.at(0),lumiWeight3D);
//            cosTheta->Fill(myLeptonicTop.cosThetaStar(),lumiWeight3D);
//            cosThetaII->Fill(myLeptonicTop.cosThetaStar(2),lumiWeight3D);
//            cosTheta_EtaFwd->Fill(fabs(sortedJetsbyEta.at(0).Eta()),myLeptonicTop.cosThetaStar(),lumiWeight3D);
//            cosTheta_EtaLight->Fill(fabs(nonBs.at(0).Eta()),myLeptonicTop.cosThetaStar(),lumiWeight3D);
//            cosTheta_Ht->Fill(ht,myLeptonicTop.cosThetaStar(),lumiWeight3D);
            EtaFwd_Ht->Fill(ht,fabs(sortedJetsbyEta.at(0).Eta()),lumiWeight3D);
//            Wmass->Fill(myLeptonicTop.W().M(),lumiWeight3D);
//            topMass->Fill(myLeptonicTop.top().M(),lumiWeight3D);
//            WmassII->Fill(myLeptonicTop.W(2).M(),lumiWeight3D);
//            topMassII->Fill(myLeptonicTop.top(2).M(),lumiWeight3D);
//            delNu->Fill((fabs(myGenSingleTop.genSingleTop.getMET(0).Pt()-myLeptonicTop.getMET().Pt())/(double)
//            myGenSingleTop.genSingleTop.getMET(0).Pt()),lumiWeight3D);
//            delNuII->Fill((fabs(myGenSingleTop.genSingleTop.getMET(0).Pt()-myLeptonicTop.getMET(2).Pt())/(double)
//            myGenSingleTop.genSingleTop.getMET(0).Pt()),lumiWeight3D);
            

        }

        cout<<"before closing file input "<<f->GetName()<<endl;
        f->Close();
        delete f;

    }
    cout<<"before endjob"<<endl;
    TFile * fout = new TFile(plotFileName.c_str(),"recreate");
    fout->cd();
    atLeastOnGPV.WriteAll(fout);
    GoldenFinalMuons.WriteAll(fout);
    Jets.WriteAll(fout);
    BJets.WriteAll(fout);
    Light.WriteAll(fout);
    nonBJets.WriteAll(fout);
    MetHist.WriteAll(fout);  
    finalMT->Write();
    cosTheta->Write();
    Wmass->Write();
    topMass->Write();
    cosThetaII->Write();
    WmassII->Write();
    topMassII->Write();
    delNu->Write();
    delNuII->Write();
    cosTheta_EtaFwd->Write();
    cosTheta_EtaLight->Write();
    cosTheta_Ht->Write();
    EtaFwd_Ht->Write();
    nonB.WriteAll(fout);
    B.WriteAll(fout);
    FwD.WriteAll(fout);
    
    fout->Write();
    fout->Close();
    
    cout<<nInit<<"\n"<<nHLTrunB<<"\n"<<nMt<<"\n"<<nFinal<<endl;
    return 0;
}

