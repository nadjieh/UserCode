#if !defined(__CINT__) && !defined(__MAKECINT__)
#include <stdlib.h>
#include <Math/GenVector/LorentzVector.h>
#include "Riostream.h"
#include "TROOT.h"
#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TMath.h"

#include "FWCore/FWLite/interface/AutoLibraryLoader.h"
#include "DataFormats/FWLite/interface/Handle.h"
#include "DataFormats/FWLite/interface/Event.h"

#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/PatCandidates/interface/Particle.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/MuonReco/interface/MuonIsolation.h"



#endif

double InnerProduct(const reco::Particle p1 , const reco::Particle p2){
    return((p1.p4()).Dot(p2.p4()));
}


void CreateHLParticle(reco::Particle &HLP, const reco::Particle p1 , const reco::Particle p2){//no charge
    HLP.setP4(p1.p4()+p2.p4());
}
double Mass(const reco::Particle HLP){
    double M2 = fabs(InnerProduct(HLP,HLP));
    return sqrt(M2);
}


double Distance(double phi1, double phi2, double eta1, double eta2 ){
    
    double DeltaPhi = fabs(phi1 - phi2);
    if (DeltaPhi>M_PI) DeltaPhi = 2*M_PI - DeltaPhi;
    double DeltaEta = fabs(eta1 - eta2);
    return (sqrt(DeltaPhi*DeltaPhi + DeltaEta*DeltaEta));
}

void cuts_description(std::vector<string> &cutDescription) // Nadjieh
{
  cutDescription.push_back("HLTR_MuIso_MuNonIso_MuElecRelaxed");
  cutDescription.push_back("LooseMu_pt>10_Eta<2.1");
  cutDescription.push_back("TightMu_pt>20_Eta<2.1");
  cutDescription.push_back("No Other Loose Muon (mu.size()<2)");
  cutDescription.push_back("NonElec_pt>20_Eta<2.1  (el.size() == 0)");
  cutDescription.push_back("Central b-tag_pt>30_Eta<2.5_btag>0 (bjet.size()>0)");
  cutDescription.push_back("Forward jet_pt>50_Eta>2.5 (fjet.size()>0)");
  cutDescription.push_back("No Other Central b-tag (bjet.size()<0)");
  cutDescription.push_back("No anti-b-tagged central jet _pt>30_eta<2.5_btag<0");
  cutDescription.push_back("MET above threshold _MET>40");
  cutDescription.push_back("MTW is in Signal region : (50,100)");
}

void Efficiency(int accepted[] , int total , std::vector<string> cutDescription,TH1D* hist ) // Nadjieh
{
    cout<<"Efficiency method has been called"<<endl;
    for (int i=0; i<11; i++)
    {
       //cout<<total<<endl;
       cout<<"accepted["<<i<<"] is:"<<accepted[i]<<endl;
       double efficiency = (((double)accepted[i])/((double)total));
       hist->SetBinContent(i, efficiency);
       cout<< "Description of Cut No. "<<i<<" : " <<cutDescription.at(i)<<" : "<<efficiency<<endl; 
    }
}

void loop_on_sample(TString input, bool file_in_same_path)
{
  TFile f1(input,"OLD");
  fwlite::Event ev(&f1);

  TString output = "histo_";
  if (file_in_same_path) {
    output +=input;
  } else { 
    int step = input.Length() -1 ;
    TString RealFileName; 
    while(input(step , 1) != "/")  { step --; }
    RealFileName += input(step+1 , 1).Data();   
    output +=RealFileName;
  }
  cout << "Writing output in file " << output << endl;

  TFile* outfile = new TFile(output,"RECREATE","file with histograms");
  outfile->mkdir("MuonHists","MuonHists");
  outfile->cd("MuonHists");
  outfile->mkdir("MuonIsolation","MuonIsolation");

//-------------Data  Members-------------- 
// Suitable to calculate efficiency
  int n_Evt = 0;
  int n_accepted[11];
  
//Use for Histograms  
  double low = 0.;
  double high = 500.;
  int nbins = 20;

// Initialization of accepted numbers
  for(int i=0; i<11; i++)   n_accepted[i] = 0;
  std::vector<string> cutsDescription;
  cuts_description(cutsDescription);


  
// Histogram declaration 
  
  TH1F *hHT = new TH1F("ht","ht",nbins,low,high);
  TH1D *hMTWtrueNu = new TH1D("MTWtrueNu","MTWtrueNu",nbins,low,high);
  TH1D *hMTW = new TH1D("MTW","MTW",nbins,low,high);
  TH1D* hEff = new TH1D("Cuts Efficiency","Cuts Efficiency",11, -1., 11.);
  
  //Jet Hists
  TH1D* JetMultiplicity =  new TH1D("JetMultiplicity","Jet Multiplicity",10, 0., 20.);
  TH1D *fJetEta = new TH1D("fJetEta","#eta",10, -5.,5.);
  TH1D *fJetPt = new TH1D("fJetPt","P_{t}, forward jets",50 ,0., 100.);
  TH1D *JetEtanonBtag = new TH1D("EtaNonBtag","#eta",10, -5.,5.);
  TH1D *JetPtnonBtag = new TH1D("PtNonBtag","P_{t}, non-b-tagged jets",50 ,0.,100);
  TH1D *PtMostEnergicFjet = new TH1D("PtMostEnergicFjet","P_{t}, MostEnergicFjet",50 ,0.,100);
  TH1D *EtMostEnergicFjet = new TH1D("EtMostEnergicFjet","E_{t}, MostEnergicFjet",50 ,0.,100);
  TH1D *EtDifferenceQuarkJet = new TH1D("EtDifferenceQuarkJet","E_{t}",200 ,-100.,100.);
  TH1D *temEta = new TH1D("temEta","#eta",10, -5.,5.);
  //bTags
  TH1F* btagDiscriminator1 = new TH1F("btagDiscriminator1","b-tag Discriminator1",10,-2.,3.);
  /* TH1F* btagDiscriminator2 = new TH1F("btagDiscriminator2","b-tag Discriminator2",100,-12.,5.);
   TH1F* btagDiscriminator3 = new TH1F("btagDiscriminator3","b-tag Discriminator3",100,-12.,5.);
   TH1F* btagDiscriminator4 = new TH1F("btagDiscriminator4","b-tag Discriminator4",100,-12.,5.); 
   TH1F* btagDiscriminator5 = new TH1F("btagDiscriminator5","b-tag Discriminator5",100,-12.,5.);
 */
  TH2F* bTagvsDistance = new TH2F ("bTagvsDistance","bTagvsDistance",40,0.,2. , 100, 0., 10.);
  //Muon Hists
  TH1D* MuPt = new TH1D("Muon Pt","P_{t}, Muon",50 ,0., 100.);
  TH1D* MuEta = new TH1D("MuonEta","#eta_{#mu}",10, -5.,5.);
  
     //Iso03 
  TH1F* MuIso03emEt = new TH1F("MuIso03emEt","#mu Iso03emEt",50 ,0., 100.);
  TH1F* MuIso03hadEt = new TH1F("MuIso03hadEt","#mu Iso03hadEt",50 ,0., 100.);
  TH1F* MuIso03hoEt = new TH1F("MuIso03hoEt","#mu Iso03hoEt",50 ,0., 100.);
  TH1F* MuIso03sumPt = new TH1F("MuIso03sumPt","#mu Iso03sumPt",50 ,0., 100.);
  
  TH1I* MuIso03nJets = new TH1I("MuIso03nJets","#mu Iso03nJets",20 ,0, 20);
  TH1I* MuIso03nTracks = new TH1I("MuIso03nTracks","#mu Iso03nTracks",20 ,0, 20);
   
     //Iso05
  TH1F* MuIso05emEt = new TH1F("MuIso05emEt","#mu Iso05emEt",50 ,0., 100.);
  TH1F* MuIso05hadEt = new TH1F("MuIso05hadEt","#mu Iso05hadEt",50 ,0., 100.);
  TH1F* MuIso05hoEt = new TH1F("MuIso05hoEt","#mu Iso05hoEt",50 ,0., 100.);
  TH1F* MuIso05sumPt = new TH1F("MuIso05sumPt","#mu Iso05sumPt",50 ,0., 100.);
  
  TH1I* MuIso05nJets = new TH1I("MuIso05nJets","#mu Iso05nJets",20 ,0, 20);
  TH1I* MuIso05nTracks = new TH1I("MuIso05nTracks","#mu Iso05nTracks",20 ,0, 20);

//MET Hists
  TH1D* MET = new TH1D("MET","MET",100 ,0., 200.);
  
  
  // W Hists
  // RECO
  TH1D *DifPtL = new TH1D("DifPtL","P_{t}, |recoW-genW| Less NuPz",400 ,0., 500.);
  TH1D *DifPtM = new TH1D("DifPtM","P_{t}, |recoW-genW| More NuPz",400 ,0., 500.);
  
  TH1D *DifPzL = new TH1D("DifPzL","P_{z}, |recoW-genW| Less NuPz",400,0., 500.);
  TH1D *DifPzM = new TH1D("DifPzM","P_{z}, |recoW-genW| More NuPz",400 ,0., 500.);
  TH2D *DifLvsM = new TH2D("DifLvsM","P_{z} |recoW-genW|",200,0.,300.,200,0.,300.);
  
  // Top Hists
  TH1D *topMass = new TH1D("Top Mass","Top Mass",75, 0., 400.);
  //TH1D *topMass2 = new TH1D("Top Mass2","Top Mass2",300, 0., 400.);
  TH1D *DotTopFjet = new TH1D("DotTopFjet","Scalar product of the p4 recoTop and the most forwardjet",20 ,-5.,5.);
  TH2D *EtaFJvsTopdotFJ = new TH2D("EtaFJvsTopdotFJ","EtaFJvsTopdotFJ",10, -5.,5.,50, -5.,5.);
  
// Loop on the sample
    cout<<"Loop on the sample begins!!"<<endl;
    for( ev.toBegin(); ! ev.atEnd(); ++ev) {
        n_Evt++;
        pat::Particle TOP;
    cout<<"Event number "<<n_Evt<<endl;
    // Is it SingleTop event?   
        fwlite::Handle<bool > handle_SingleTopEvent;
        handle_SingleTopEvent.getByLabel(ev,"SingleTop", "SingleTopEvent");
        bool SingleTopEvent = handle_SingleTopEvent.ref();
        if (SingleTopEvent) {cout << "event selected" << endl;} else {cout << "event rejected" << endl;}

    // To use in the Efficiency method for each Cut 
        fwlite::Handle<std::vector<bool> > handle_Cuts;   
        handle_Cuts.getByLabel (ev,"SingleTop","cuts");
        std::vector<bool> Cuts = handle_Cuts.ref();
        for (unsigned int i = 0; i < Cuts.size(); i++)
            if (Cuts.at(i)) n_accepted[i]++;
        cout<<"Cut vector has been studied!!"<<endl;

    // Retrive the Event's Weight
        fwlite::Handle<double > handle_weight;
        handle_weight.getByLabel(ev,"SingleTop", "weight");
        double weight = handle_weight.ref();
        cout << "weight: " << weight << endl;

    // Retrive HT of the event
        fwlite::Handle<double > handle_HT;
        handle_HT.getByLabel(ev,"SingleTop", "HT");
        double HT = handle_HT.ref();
        hHT->Fill(HT,weight);
        cout<<"HT is retrieved:" <<HT<<endl;
        
    // Retrive MTWtrueNu of the event    
        fwlite::Handle<double > handle_MTWtrueNu;
        handle_MTWtrueNu.getByLabel(ev,"SingleTop", "MTWtrueNu");
        double MTWtrueNu = handle_MTWtrueNu.ref();
        hMTWtrueNu->Fill(MTWtrueNu,weight); 
        
    // Retrive MTW of the event    
        fwlite::Handle<double > handle_MTW;
        handle_MTW.getByLabel(ev,"SingleTop", "MTW");        
        double MTW = handle_MTW.ref();
        hMTW->Fill(MTW,weight);

    // Retrive the recoGenParticles esp. W and the most energic bQuark    
        fwlite::Handle<std::vector<reco::GenParticle> > handle_genParticles;
        handle_genParticles.getByLabel(ev,"genParticles");
        std::vector<reco::GenParticle> genParticles = handle_genParticles.ref();

        double GenPz = 0.;
        double GenPt = 0.;
        double bQuarkEta = 0.;
        double bQuarkPhi = 0.;
        double bQuarkEnergy = -1.;
        double Etb;

        for(size_t i = 0; i < genParticles.size(); ++ i) 
        {
            if (abs(genParticles.at(i).pdgId()) == 24 && genParticles.at(i).status() == 3) 
            {
                GenPz = genParticles.at(i).pz();
                GenPt = genParticles.at(i).pt();
                cout<<"Pz of GenW: "<<genParticles.at(i).pz()<<endl;
                cout<<"The status is: "<<genParticles.at(i).status()<<endl;
            }  
            else if(abs(genParticles.at(i).pdgId()) == 5 && genParticles.at(i).energy()>bQuarkEnergy/*genParticles.at(i).status() == 3*/)   
                 {
                     bQuarkPhi = genParticles.at(i).phi();
                     bQuarkEta = genParticles.at(i).eta();                                                    
                     bQuarkEnergy = genParticles.at(i).energy();    
                     Etb = genParticles.at(i).et();  
                 }
       }
       cout<<"reco::GenParticles have been retrieved!!"<<endl;

 // Retrive patJets  
        fwlite::Handle<std::vector<pat::Jet> > handle_Jet;
        handle_Jet.getByLabel(ev,"selectedLayer1Jets");
        
        std::string theLabel1 = "combinedSVJetTags";
       /* std::string theLabel2 = "trackCountingHighPurBJetTags";
        std::string theLabel3 = "trackCountingHighEffBJetTags";
        std::string theLabel4 = "combinedSVMVABJetTags";
        std::string theLabel5 = "combinedSecondaryVertexMVABJetTags";*/    
        double NoBtag = 0.;
        double maxeta=0.;
        double maxPt=0.;
        double maxEt=0.;
        double fjetEta=99.;
        double EtaofMax = 0.;
        double pt_of_maxeta=-1.;
        int j=0;
        float MaxTag = -1000000.;
        
        float distance = 10000.;
        float bTag = -1000.;
        double EtB ;
        const pat::Jet * TopBJet; //jet of the most b-tag value
        const pat::Jet * MostForwardJet;
        
        
        JetMultiplicity->Fill(double(handle_Jet->size()),weight);
        
        for( std::vector<pat::Jet>::const_iterator it = handle_Jet->begin(); it != handle_Jet->end(); ++it)
        {
            float btag1 = (*it).bDiscriminator(theLabel1);
        /*  float btag2 = (*it).bDiscriminator(theLabel2);
            float btag3 = (*it).bDiscriminator(theLabel3);
            float btag4 = (*it).bDiscriminator(theLabel4);
            float btag5 = (*it).bDiscriminator(theLabel5);
          */       
            double jetPt = (*it).pt();
            double jetEt = (*it).et();
            double jetPhi = (*it).phi();
            double jetEta = (*it).eta();        
            double jetPx = (*it).px(); 
            double jetPy = (*it).py(); 
            double jetPz = (*it).pz(); 
            double jetE = (*it).energy(); 
            
            
            btagDiscriminator1->Fill(btag1,weight);
            /*btagDiscriminator2->Fill(btag2,weight);
            /*btagDiscriminator3->Fill(btag3,weight);
            btagDiscriminator4->Fill(btag4,weight); 
            btagDiscriminator5->Fill(btag5,weight);
            */               

            //for non-btag jets
            if (btag1<0)
            {
                cout<<"btag1<0"<<endl;
                JetEtanonBtag->Fill(jetEta,weight);        
                JetPtnonBtag->Fill(jetPt,weight);
            } 
            else 
            {  // Find the closest b-jet to the GenBQuark and observe it's bDiscriminator
                
                if(Distance(jetPhi,bQuarkPhi,jetEta, bQuarkEta) < distance) 
                {
                    distance = Distance(jetPhi, bQuarkPhi,jetEta,  bQuarkEta );  
                    bTag = btag1;           
                    EtB = jetEt;
                }
                if ( btag1 >= 0.9 && btag1>MaxTag) //btag1>MaxTag = -1000000. 
                {
                    
                    
                    MaxTag = btag1;
                    NoBtag++;
                    TopBJet = &(*it);
                    
                    
                    cout<<"TopBJet eta: "<<(*TopBJet).eta()<<endl;
                    cout<<"TopBJet Pz: "<<(*TopBJet).pz()<<endl;
                }
                
            }

            //eta and Pt of highest abs(eta) jet
            if (fabs(jetEta) > maxeta) 
            {
                maxeta = fabs(jetEta);
                MostForwardJet = &(*it);
               /* fjetEta = jetEta;
                pt_of_maxeta = 	jetPt;*/
            }
            
            //pt of highest pt and et of highest et
            if (fabs(jetEta) > 2.5)
            {
                j++;
                if (jetPt > maxPt) 
                {
                    maxPt = jetPt;
                    EtaofMax = jetEta;
                }
                if (jetEt > maxEt) maxEt = jetEt;

            }

        }    
        fJetEta->Fill(MostForwardJet->eta(),weight);        
        fJetPt->Fill(MostForwardJet->pt(),weight);
        bTagvsDistance->Fill(bTag,distance,weight);
        EtDifferenceQuarkJet->Fill(((EtB-Etb)/Etb),weight);
        if (j!= 0)
        {
           PtMostEnergicFjet->Fill(maxPt,weight);
           EtMostEnergicFjet->Fill(maxEt,weight);
           temEta->Fill(EtaofMax,weight);

        }
        cout<<"All pat::Jets have been retrived"<<endl;
            
     // Retrive reconstructed W and fill the histograms   
        fwlite::Handle<std::vector<pat::Particle> > handle_recoW;
        handle_recoW.getByLabel(ev,"SingleTop", "recoW");
        std::vector<pat::Particle> recoW = handle_recoW.ref();
        pat::Particle W;
        if(recoW.size() != 0)
        {
            cout<<"W finder!"<<endl;
            W = recoW.at(0);
            cout<<"W is found!!!"<<endl;
            if (NoBtag!=0.)
            {
                cout<<"at least on b-jet :)"<<endl;
                CreateHLParticle(TOP, *TopBJet,W);
                cout<<"TOP.mass(): "<<TOP.mass() <<"   Mass(TOP):  "<<Mass(TOP);
                topMass->Fill( fabs(TOP.mass()),weight);
                cout<<"Hist of top mass has been filled!!!!!!!!!!"<<endl;
            }
     //Which W solution is better?
            DifPzL->Fill(fabs(recoW.at(0).pz() - GenPz),weight);
            DifPtL->Fill(fabs(recoW.at(0).pt() - GenPt),weight);

            DifPzM->Fill(fabs(recoW.at(1).pz() - GenPz),weight);
            DifPtM->Fill(fabs(recoW.at(1).pt() - GenPt),weight);
            DifLvsM->Fill(fabs(recoW.at(0).pz() - GenPz),fabs(recoW.at(1).pz() - GenPz), weight);

        }
        cout<<"All pat::recoW's have been retrived"<<endl;
     
       // Retrive patMuons 
        fwlite::Handle<std::vector<pat::Muon> > handle_Muon;
        handle_Muon.getByLabel(ev,"selectedLayer1Muons");
        std::vector<pat::Muon> Muons = handle_Muon.ref();

        for( std::vector<pat::Muon>::const_iterator it = handle_Muon->begin(); it != handle_Muon->end(); it++)
        {
            double muEta = (*it).eta();
            double muPt = (*it).pt();
            double muPx = (*it).px(); 
            double muPy = (*it).py(); 
            double muPz = (*it).pz(); 
            double muE = (*it).energy();
              //Iso declaration, initialization
            const reco::MuonIsolation& muIsoInfo03 = (*it).getIsolationR03();
            const reco::MuonIsolation& muIsoInfo05 = (*it).getIsolationR05();

            // Fill

            MuEta->Fill(muEta,weight);
            MuPt->Fill(muPt,weight);

            // Iso03
            
            cout<<"Muon Iso 03:"<<endl;
            MuIso03emEt->Fill(muIsoInfo03.emEt);
            cout<<"muIsoInfo03.emEt : "<<muIsoInfo03.emEt<<endl;
            MuIso03hadEt->Fill(muIsoInfo03.hadEt);
            cout<<"muIsoInfo03.hadEt : "<<muIsoInfo03.hadEt<<endl;
            MuIso03hoEt->Fill(muIsoInfo03.hoEt);
            cout<<"muIsoInfo03.hoEt : "<<muIsoInfo03.hoEt<<endl;
            MuIso03sumPt->Fill(muIsoInfo03.sumPt);
            cout<<"muIsoInfo03.sumPt : "<<muIsoInfo03.sumPt<<endl;

            MuIso03nJets->Fill(muIsoInfo03.nJets);
            cout<<"muIsoInfo03.nJets : "<<muIsoInfo03.nJets<<endl;
            MuIso03nTracks->Fill(muIsoInfo03.nTracks); 
            cout<<"muIsoInfo03.nTracks : "<<muIsoInfo03.nTracks<<endl;

             // Iso05

             cout<<"Muon Iso 05:"<<endl;
            MuIso05emEt->Fill(muIsoInfo05.emEt);
            cout<<"muIsoInfo05.emEt : "<<muIsoInfo05.emEt<<endl;
            MuIso05hadEt->Fill(muIsoInfo05.hadEt);
            cout<<"muIsoInfo05.hadEt : "<<muIsoInfo05.hadEt<<endl;
            MuIso05hoEt->Fill(muIsoInfo05.hoEt);
            cout<<"muIsoInfo05.hoEt : "<<muIsoInfo05.hoEt<<endl;
            MuIso05sumPt->Fill(muIsoInfo05.sumPt);
            cout<<"muIsoInfo05.sumPt : "<<muIsoInfo05.sumPt<<endl;

            MuIso05nJets->Fill(muIsoInfo05.nJets);
            cout<<"muIsoInfo05.nJets : "<<muIsoInfo05.nJets<<endl;
            MuIso05nTracks->Fill(muIsoInfo05.nTracks); 
            cout<<"muIsoInfo05.nTracks : "<<muIsoInfo05.nTracks<<endl;

         } 
        cout<<"All pat::Muons have been retrived"<<endl;
        
       // Retrive patMET 
         fwlite::Handle<std::vector<pat::MET> > handle_MET;
         handle_MET.getByLabel(ev,"selectedLayer1METs");
         for( std::vector<pat::MET>::const_iterator it = handle_MET->begin(); it != handle_MET->end(); it++)
         {
            double met = (*it).pt();
            double metPx = (*it).px(); 
            double metPy = (*it).py(); 
            MET ->Fill(met,weight); 

         }
         cout<<"MET has been retrived"<<endl;
      // Top Calculations
         cout<<"top energy = "<<TOP.energy()<<endl;
         cout<<"Most fjet energy = "<<(*MostForwardJet).energy()<<endl;
         cout<<"InnerProduct(TOP, *MostForwardJet): "<< InnerProduct(TOP, *MostForwardJet)/(TOP.energy()*(*MostForwardJet).energy())<<endl;
         double DotP = InnerProduct(TOP, *MostForwardJet)/(TOP.energy()*(*MostForwardJet).energy());
         DotTopFjet->Fill(DotP,weight);
         
         EtaFJvsTopdotFJ->Fill((*MostForwardJet).eta(),DotP,weight);
        
         
      }
 
      Efficiency(n_accepted,n_Evt,cutsDescription,hEff); 

      outfile->Write();

}


int main()
{
  AutoLibraryLoader::enable();
  

 // loop_on_sample("/home/ajafari/ROOTfiles/SkimmedFiles/Signal/MCatNLO/SingleTopSkimSignalMCatNLO.root",false); // first sample (e.g. signal)
  loop_on_sample("/home/ajafari/ROOTfiles/SkimmedFiles/Chowder/SingleTopSkimChowder.root",false); // first sample (e.g. one of the backgrounds)
  //loop_on_sample("/home/ajafari/ROOTfiles/SkimmedFiles/QCD/Gumbo/SingleTopSkimQCDgumbo.root",false); // second sample (e.g. one of the backgrounds)
  //loop_on_sample("/home/ajafari/ROOTfiles/SkimmedFiles/QCD/Stew/SingleTopSkimQCDstew.root",false);
  loop_on_sample("/home/ajafari/ROOTfiles/SkimmedFiles/Signal/MADGRAPH/SingleTopSkimFastMADGRAPH.root",false);
  loop_on_sample("/home/ajafari/ROOTfiles/SkimmedFiles/QCD/ppMuPt20-15/SingleTopSkimQCDpp.root",false);
  
//
//loop_on_sample("../test/tmp3SingleTopSkim.root",false);
  return 0;
}

