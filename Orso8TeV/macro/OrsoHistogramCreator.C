/* 
 * File:   OrsoHistogramCreator.C
 * Author: nadjieh
 *
 * Created on October 12, 2012, 12:34 PM
 */

#include "TDirectory.h"

#include "../../AnalysisClasses/EventSelection/interface/ElectronSelector.h"

#include "../../AnalysisClasses/EventSelection/interface/Event.h"

#include "../../AnalysisClasses/EventSelection/interface/ElectronHists.h"
#include "../../AnalysisClasses/EventSelection/interface/MuonHists.h"
#include "../../AnalysisClasses/EventSelection/interface/PVHists.h"
#include "../../AnalysisClasses/EventSelection/interface/JetHists.h"
#include "../../AnalysisClasses/EventSelection/interface/JetSelector.h"
#include "../../AnalysisClasses/EventSelection/interface/MuonVetoSelector.h"
#include "../../AnalysisClasses/EventSelection/interface/MetHists.h"
#include "../../AnalysisClasses/EventSelection/interface/PrimaryVertexSelector.h"
#include "../../TopBrussels/TopTreeProducer/interface/TRootMuon.h"
#include "../../TopBrussels/TopTreeProducer/interface/TRootElectron.h"
#include "../../TopBrussels/TopTreeProducer/interface/TRootJet.h"
#include "../../TopBrussels/TopTreeProducer/interface/TRootCaloJet.h"
#include "../../TopBrussels/TopTreeProducer/interface/TRootPFJet.h"
#include "../../TopBrussels/TopTreeProducer/interface/TRootMET.h"
#include "../../TopBrussels/TopTreeProducer/interface/TRootGenEvent.h"
#include "../../TopBrussels/TopTreeProducer/interface/TRootNPGenEvent.h"
#include "../../TopBrussels/TopTreeProducer/interface/TRootEvent.h"
#include "../../TopBrussels/TopTreeProducer/interface/TRootRun.h"
#include "../../TopBrussels/TopTreeProducer/interface/TRootParticle.h"
#include "../../TopBrussels/TopTreeProducer/interface/TRootMCParticle.h"
#include "../../TopBrussels/TopTreeProducer/interface/TRootVertex.h"
#include "../../TopBrussels/TopTreeProducer/interface/TRootHLTInfo.h"
#include "../../AnalysisClasses/EventSelection/interface/PracticalEvent.h"
#include "../../AnalysisClasses/ToyAnalysis/interface/GenSingleTopMaker.h"
#include "../../AnalysisClasses/PhysicsObjects/interface/SemiLepTopQuark.h"
#include "../../AnalysisClasses/ChiSquared/interface/DR.h"
#include "../interface/MuonTree.h"
#include "../interface/SingleTopHistograms.h"

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


int main(int argc, char** argv) {

    PVHists atLeastOnGPV("DefW_PV");
    JetHists Jets("DefW_Jet", 2);
    JetHists BJets("DefW_BJet", 2);
    JetHists nonBJets("DefW_nonBJet", 2);
    JetHists FwDJet("DefW_FwD", 2);
    MuonHists GoldenFinalPUMuons("DefW_Muon");
    MetHists MetHist("DefW_Met");


    PVHists atLeastOnGPV_allW("allW_PV");
    JetHists Jets_allW("allW_Jet", 2);
    JetHists BJets_allW("allW_BJet", 2);
    JetHists nonBJets_allW("allW_nonBJet", 2);
    JetHists FwDJet_allW("allW_FwD", 2);
    MuonHists GoldenFinalPUMuons_allW("allW_Muon");
    MetHists MetHist_allW("allW_Met");

    SingleTopHistograms Default_Def("Default_Def");
    SingleTopHistograms EtaCut_Def("EtaFwD_Def");
    SingleTopHistograms HtCut_Def("HtCut_Def");
    SingleTopHistograms AntiEtaCut_Def("antiEtaFwD_Def");
    SingleTopHistograms AntiHtCut_Def("antiHtCut_Def");

    SingleTopHistograms DefaultTrue_Def("DefaultTrue_Def");
    SingleTopHistograms EtaCutTrue_Def("EtaFwDTrue_Def");
    SingleTopHistograms HtCutTrue_Def("HtCutTrue_Def");
    SingleTopHistograms AntiEtaCutTrue_Def("antiEtaFwDTrue_Def");
    SingleTopHistograms AntiHtCutTrue_Def("antiHtCutTrue_Def");


    SingleTopHistograms Default_allW("Default_allW");

    SingleTopHistograms EtaCut_allW("EtaFwD_allW");


    SingleTopHistograms DefaultTrue_allW("DefaultTrue_allW");


    SingleTopHistograms EtaCutTrue_allW("EtaFwDTrue_allW");
     
    
    TH1D * HT = new TH1D("HT", "H_{T};H_{T}(GeV)", 500, 0., 500.);

    TH1D * def_finalMT = new TH1D("def_finalMT", "final-W-neutrino transverse mass", 100, 0., 200.);
    def_finalMT->GetXaxis()->SetTitle("M_{T}(W,#nu)");
    TH1D * allW_finalMT = new TH1D("allW_finalMT", "final-W-neutrino transverse mass", 100, 0., 200.);
    allW_finalMT->GetXaxis()->SetTitle("M_{T}(W,#nu)");
    std::vector<std::string> inputFileNames;
    std::string plotFileName;
    int verbosity = 0;
    TH1D * METResolutions = 0;
    bool pu3D = false; //true;
    double doJES = 1;
    bool isData = false;
    int smearingSkim = 1;
	TString sample = "";
    for (int f = 1; f < argc; f++) {
        std::string arg_fth(*(argv + f));

		if (arg_fth == "input") {
            f++;
            std::string in(*(argv + f));
            inputFileNames.push_back(string("~/work/samples/Orso8TeV/sep/" + in +".root"));
			sample = in;
			plotFileName = in+"_plots.root";
        } else if (arg_fth == "JES") {
            f++;
            std::string in(*(argv + f));
            doJES = atof(in.c_str());
        } else if (arg_fth == "isData") {
            f++;
            std::string in(*(argv + f));
            if (in == "yes" || in == "YES" || in == "Yes" || in == "y" || in == "Y")
                isData = true;
            else
                isData = false;
        } else if (arg_fth == "METResolFileName") {
            f++;
            std::string in(*(argv + f));
            TFile * METResolFileName = TFile::Open(in.c_str());
            METResolutions = (TH1D*) METResolFileName->Get("METresolutions");
        } else if (arg_fth == "smearingSkim") {
            f++;
            std::string in(*(argv + f));
            smearingSkim = atof(in.c_str());
        }
    }
    cout<<"START"<<endl;

    TFile* f = 0;
    TApplication theApp("App", &argc, argv);
    double nInit = 0;
    double nFinal = 0;
    double nHLTrunB = 0;
    double nMt = 0;
    double nGoodSolution = 0;

    MuonTree * myMuonTree = 0;
    TTree * eventTree = 0;


    GenSingleTopMaker* genSingleTop = 0;
    TH1D * dr_jet_lep = new TH1D("drJetLep", "drJetLep", 1000, -0.5, 9.5);
    TH2D * nVtx_cosTheta = new TH2D("nVtxcosTheta", "nVtxcosTheta", 100, 0, 100, 100, -1.,1.);
    TH2D * MT_cosTheta = new TH2D("MTcosTheta", "MTcosTheta", 200, 0, 200, 100, -1.,1.);
    TH2D * MT_cosTheta_true = new TH2D("MTcosTheta_true", "MTcosTheta_true", 200, 0, 200, 100, -1.,1.);
    TH2D * PtJet_cosTheta = new TH2D("PtJetcosTheta", "PtJetcosTheta", 300, 0, 300, 100, -1.,1.);
    TH2D * met_mtW = new TH2D("metMtW", "metMtW", 300, 0, 300, 300, 0.,300.);
    TH2D * ptmu_mtW = new TH2D("ptmuMtW", "ptmuMtW", 300, 0, 300, 300, 0.,300.);
    TH2D * Wpt_cosTheta = new TH2D("WptcosTheta", "WptcosTheta", 300, 0, 300, 100, -1.,1.);
    TH2D * toppt_cosTheta = new TH2D("topptcosTheta", "topptcosTheta", 300, 0, 300, 100, -1.,1.);
    TH2D * mupt_cosTheta = new TH2D("muptcosTheta", "muptcosTheta", 300, 0, 300, 100, -1.,1.);
    for (unsigned int fNumber = 0; fNumber < inputFileNames.size(); fNumber++) {
        cout << "file number " << fNumber + 1 << ": " << inputFileNames.at(fNumber) << endl;
        TFile* f = TFile::Open(inputFileNames.at(fNumber).c_str());
        myMuonTree = new MuonTree(eventTree, f,sample + "_2J_1T_noSyst");
        double lumiWeight3D = 1;
        for (int eventNumber = 0; eventNumber < myMuonTree->fChain->GetEntriesFast(); eventNumber++) {
            myMuonTree->GetEntry(eventNumber);
			if(!myMuonTree->passExtraSelection())
				continue;
            TLorentzVector muon = myMuonTree->GetLepton();
            TLorentzVector bjet = myMuonTree->GetBJet();
            TLorentzVector fjet = myMuonTree->GetFJet();
            TLorentzVector met = myMuonTree->GetMET();
            double mt = myMuonTree->GetMTW();
            TLorentzVector fwdJet = myMuonTree->GetMostFwDJet();
            nFinal += lumiWeight3D;
            SemiLepTopQuark myLeptonicTop(bjet, met, muon, fjet, fwdJet, METResolutions);
            myLeptonicTop.setMuCharge((int) myMuonTree->charge);
            TLorentzVector myB;
            TLorentzVector myF;
            double eta = fabs(fwdJet.Eta());
            double ht = myMuonTree->GetHT();
            HT->Fill(ht, myMuonTree->GetTotalWeightNoPU());
			double defW = myMuonTree->weight*(myMuonTree->leptonEff*699+myMuonTree->leptonEffB*4342);
			double allW = myMuonTree->GetTotalWeightNoPU();
			DR<TLorentzVector> * dr= new DR<TLorentzVector>(muon,bjet);
			dr_jet_lep->Fill(dr->getValue(),allW);
			delete dr;
			dr= new DR<TLorentzVector>(muon,fjet);
			dr_jet_lep->Fill(dr->getValue(),allW);
			delete dr;
			if(isData){
				defW = 1;
				allW = 1;
			}
			/*
			 * Filling CosTheta Histograms
			 */
            if (myLeptonicTop.hasNeutrinoSolution()) {
				MT_cosTheta_true->Fill(myMuonTree->GetMTW(),myLeptonicTop.cosThetaStar(),defW);
                nGoodSolution++;
                DefaultTrue_Def.Fill(myLeptonicTop, defW, genSingleTop);
                DefaultTrue_allW.Fill(myLeptonicTop, allW, genSingleTop);
                if (ht >= 180){
                    HtCutTrue_Def.Fill(myLeptonicTop, defW, genSingleTop);
                }
                else
                    AntiHtCutTrue_Def.Fill(myLeptonicTop, defW, genSingleTop);
                if (eta > 1.5){
                    EtaCutTrue_Def.Fill(myLeptonicTop, defW, genSingleTop);
                    EtaCutTrue_allW.Fill(myLeptonicTop, allW, genSingleTop);
                }
                else
                    AntiEtaCutTrue_Def.Fill(myLeptonicTop, defW, genSingleTop);
            }else{
				nVtx_cosTheta->Fill(myMuonTree->nVertices,myLeptonicTop.cosThetaStar(),defW);
				MT_cosTheta->Fill(myMuonTree->GetMTW(),myLeptonicTop.cosThetaStar(),defW);
				PtJet_cosTheta->Fill(myMuonTree->secondJetPt,myLeptonicTop.cosThetaStar(),defW);
				Wpt_cosTheta->Fill(myLeptonicTop.W().Pt(),myLeptonicTop.cosThetaStar(),defW);
				toppt_cosTheta->Fill(myLeptonicTop.top().Pt(),myLeptonicTop.cosThetaStar(),defW);
				mupt_cosTheta->Fill(myMuonTree->GetLepton().Pt(),myLeptonicTop.cosThetaStar(),defW);
				met_mtW->Fill(myMuonTree->GetMTW(),myMuonTree->GetMET().Pt(),defW);
				ptmu_mtW->Fill(myMuonTree->GetMTW(),myMuonTree->GetLepton().Pt(),defW);
			}
           	Default_Def.Fill(myLeptonicTop, defW, genSingleTop);
           	Default_allW.Fill(myLeptonicTop, allW, genSingleTop);
            if (ht >= 180)
                HtCut_Def.Fill(myLeptonicTop, defW, genSingleTop);
            else
                AntiHtCut_Def.Fill(myLeptonicTop, defW, genSingleTop);
            if (eta > 1.5){
                EtaCut_Def.Fill(myLeptonicTop, defW, genSingleTop);
                EtaCut_allW.Fill(myLeptonicTop, allW, genSingleTop);
            }
            else
                AntiEtaCut_Def.Fill(myLeptonicTop, defW, genSingleTop);

            if (genSingleTop != NULL)
                delete genSingleTop;

			/*
			 * Filling Event Histograms
			 */
            TRootPFJet BJET(bjet);
            TRootPFJet nonBJET(fjet);
            TRootPFJet FWDJET(fwdJet);
            TRootMuon MUON(muon);
            TRootPFMET MET(met);
            TRootVertex VTX;
            Event myEvent_tmp;
            myEvent_tmp.Gpvs.push_back(VTX);
            atLeastOnGPV.Fill(myEvent_tmp.Gpvs, myMuonTree->nVertices, defW);
            myEvent_tmp.Dmuons.push_back(MUON);
            GoldenFinalPUMuons.Fill(myEvent_tmp.Dmuons, myEvent_tmp.Dmuons.size(), defW);
            myEvent_tmp.GPFJets.push_back(BJET);
            myEvent_tmp.GPFJets.push_back(nonBJET);
            Jets.FillPFJets(myEvent_tmp.GPFJets, myEvent_tmp.GPFJets.size(), myEvent_tmp.BPFJets.size(), false, defW);
            myEvent_tmp.BPFJets.push_back(BJET);            
            BJets.FillPFJets(myEvent_tmp.BPFJets, myEvent_tmp.BPFJets.size(), myEvent_tmp.BPFJets.size(), false,defW);
            std::vector<TRootPFJet> nonBs; nonBs.push_back(nonBJET);
            nonBJets.FillPFJets(nonBs, nonBs.size(), myEvent_tmp.BPFJets.size(), false, defW);
            std::vector<TRootPFJet> sortedJetsbyEta; sortedJetsbyEta.push_back(FWDJET);
            FwDJet.FillPFJets(sortedJetsbyEta, sortedJetsbyEta.size(), myEvent_tmp.BPFJets.size(), false, defW);
            myEvent_tmp.mets.push_back(MET);
            MetHist.Fill(&myEvent_tmp.mets.at(0), defW);
            def_finalMT->Fill(mt, defW);


            atLeastOnGPV_allW.Fill(myEvent_tmp.Gpvs, myEvent_tmp.Gpvs.size(), allW);
            GoldenFinalPUMuons_allW.Fill(myEvent_tmp.Dmuons, myEvent_tmp.Dmuons.size(), allW);
            Jets_allW.FillPFJets(myEvent_tmp.GPFJets, myEvent_tmp.GPFJets.size(), myEvent_tmp.BPFJets.size(), false, allW);
            BJets_allW.FillPFJets(myEvent_tmp.BPFJets, myEvent_tmp.BPFJets.size(), myEvent_tmp.BPFJets.size(), false, allW);
            nonBJets_allW.FillPFJets(nonBs, nonBs.size(), myEvent_tmp.BPFJets.size(), false, allW);
            FwDJet_allW.FillPFJets(sortedJetsbyEta, sortedJetsbyEta.size(), myEvent_tmp.BPFJets.size(), false, allW);
            MetHist_allW.Fill(&myEvent_tmp.mets.at(0), allW);
            allW_finalMT->Fill(mt, allW);
        }

        cout << "before closing file input " << f->GetName() << endl;
        f->Close();
        delete f;

    }
    cout << "before endjob" << endl;
    TFile * fout = new TFile(plotFileName.c_str(), "recreate");
    fout->cd();
    
    atLeastOnGPV.WriteAll(fout);
    GoldenFinalPUMuons.WriteAll(fout);
    Jets.WriteAll(fout);
    BJets.WriteAll(fout);
    nonBJets.WriteAll(fout);
    FwDJet.WriteAll(fout);
    MetHist.WriteAll(fout);
    def_finalMT->Write();

    atLeastOnGPV_allW.WriteAll(fout);
    GoldenFinalPUMuons_allW.WriteAll(fout);
    Jets_allW.WriteAll(fout);
    BJets_allW.WriteAll(fout);
    nonBJets_allW.WriteAll(fout);
    FwDJet_allW.WriteAll(fout);
    MetHist_allW.WriteAll(fout);
    allW_finalMT->Write();
    
    Default_Def.Write(fout);
    Default_allW.Write(fout);
    EtaCut_Def.Write(fout);
    EtaCut_allW.Write(fout);
    
    AntiEtaCut_Def.Write(fout);
    HtCut_Def.Write(fout);
    AntiHtCut_Def.Write(fout);
    DefaultTrue_allW.Write(fout);
    DefaultTrue_Def.Write(fout);
    EtaCutTrue_allW.Write(fout);
    EtaCutTrue_Def.Write(fout);
    AntiEtaCutTrue_Def.Write(fout);
    HtCutTrue_Def.Write(fout);
    AntiHtCutTrue_Def.Write(fout);
    HT->Write();
    dr_jet_lep->Write();
    nVtx_cosTheta->Write();
    PtJet_cosTheta->Write();
    MT_cosTheta->Write();
    MT_cosTheta_true->Write();
    Wpt_cosTheta->Write();
    toppt_cosTheta->Write();
	met_mtW->Write();
    ptmu_mtW->Write();
    mupt_cosTheta->Write();
//    ntag->Write();
    fout->Write();
    fout->Close();

    cout << nInit << "\n" << nHLTrunB << "\n" << nMt << "\n" << nFinal << "\n" << nGoodSolution << endl;
    return 0;
}

