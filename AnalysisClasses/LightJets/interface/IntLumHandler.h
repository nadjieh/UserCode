/* 
 * File:   IntLumHandler.h
 * Author: hbakhshi
 *
 * Created on March 10, 2010, 5:15 PM
 */

#ifndef _INTLUMHANDLER_H
#define	_INTLUMHANDLER_H

#include <exception>
#include <string>
#include <vector>
#include <sstream>

#include "TDirectory.h"
#include "TMath.h"
#include "NeededStructs.h"
#include "AnalysisHandler.h"
#include "MCAnalysis.h"

using namespace std;
typedef AnalysisHandler BASE;

class InvalidNumbers : public std::exception {
public:
    string WHAT;

    InvalidNumbers(string wht) : WHAT(wht) {
    };

    virtual ~InvalidNumbers() throw () {
    };

    virtual const char* what() const throw () {
        return WHAT.c_str();
    }
};

class IntLumHandler : public AnalysisHandler {
public:
    typedef MCAnalysis Filler;
    typedef TopEvent Object;

    IntLumHandler(std::string name_, double xsec, double Total, double initial, std::vector<double> args, bool dobtag, bool datalike,
            bool extJetOk_, double Lumi_, MassAndResolution massAndres, ElectronCuts elecCuts, JetCuts jetCuts_,
            std::string which = "minChi2", bool Ott = false, int MIN_TO_SPLIT = 20) :
    BASE(name_, dobtag, datalike, extJetOk_, Lumi_, massAndres, elecCuts, jetCuts_, which, Ott)
    , XSec(xsec), Working_IntLum(Lumi_), TotalNEvents(Total), NInitialBeforePreSel(initial), Name(name_), CurrentEvent(0) {
        int NIt = NIterations();
        if (NIt == 0)
            throw InvalidNumbers("These events are not suitable for this intLuminocity");

        if (NIt > MIN_TO_SPLIT)
            for (int i = 0; i < NIt; i++) {
                std::stringstream name;
                name << Name << "_" << Working_IntLum << "_" << i;
                Filler * f_i = new Filler(name.str(), args);
                BASE::AddAnalysis(f_i);
                if(BASE::verbosity == -10)
                    cout<<"MCAnalysis "<<f_i->Name<<" is added"<<endl;
            } else {
            std::stringstream name;
            name << Name << "_" << Working_IntLum << "_" << 0;
            Filler * f_i = new Filler(name.str(), args);
            //      Filler f_i(name.str(), args);
            BASE::AddAnalysis(f_i);
            if(BASE::verbosity == -10)
                cout<<"MCAnalysis "<<f_i->Name<<" is added"<<endl;
        }
    };

    virtual ~IntLumHandler() {
    };

    double NEventsNeeded() {
        //    return XSec*Working_IntLum;
        if(BASE::verbosity == -10)
            cout<<"\tnumber of events in this Lumi: "<<TotalNEvents * (XSec * Working_IntLum / NInitialBeforePreSel)<<endl;
        return TotalNEvents * (XSec * Working_IntLum / NInitialBeforePreSel);
    };

    int NIterations() {
//        if(BASE::verbosity == -10)
            cout<<"\tnumber of iterations: "<<int(floor(TotalNEvents / NEventsNeeded()))<<endl;
        return int(floor(TotalNEvents / NEventsNeeded()));
    };

    Filler* CurrentFiller() {
        int current_id = int(floor(CurrentEvent / NEventsNeeded()));     
        if (current_id < int(BASE::Analyses.size()))
            return ((Filler*) (BASE::Analyses.at(current_id)));
        else
            return NULL;
    }

    virtual void Fill(const Object obj, double Weight = 1.) {
//        cout<<"I am in Fill Method"<<endl;
//        if (obj != NULL) {
            Filler* filler = CurrentFiller();
            if (filler != NULL) {
                filler->Fill(obj, 1);
            }
//        }
        CurrentEvent++;
    };

    void End(TDirectory * dir) {
        BASE::End();
        if(BASE::verbosity == -10)
            cout<<"BASE is Done!"<<endl;
        std::stringstream name;
        name << Name << "_" << Working_IntLum;
        TDirectory* newDir = dir->mkdir(name.str().c_str());
        newDir->cd();

        vector<double> val_mean;
        vector<double> val_min;
        vector<double> val_max;
        vector<double> err_mean;
        int nValidErr[(int)(this->NVariables())];
        int nValidEff[(int)(this->NVariables())];
	for(int m = 0; m < this->NVariables(); m++){
	    nValidErr[m] = 0;
	    nValidEff[m] = 0;
	}
        int varid;
        for (varid = 0; varid <this->NVariables(); varid++) {
            val_max.push_back(-10000.);
            val_min.push_back(10000.);
            val_mean.push_back(0.0);
            err_mean.push_back(0.0);
        }
        for (uint i = 0; i < BASE::Analyses.size(); i++) {
            Filler* elem = (MCAnalysis*)(BASE::Analyses[i]);
            if(BASE::verbosity == -10)
                cout<<"\t@@@@\tIn the MCANalysis \n\t\t"<<elem->Name<<"\n\t-----------------------------------"<<endl;
            //My specific:
            elem->TruthValueCalculator();
            elem->MethodValueCalculator();
            // 
            for (varid = 0; varid < this->NVariables(); varid++) {
                double myVal = elem->Value(varid);
                if(myVal > 0 && myVal != 1 ){
                    val_mean[varid] += myVal;
                    if (myVal > val_max[varid])
                        val_max[varid] = myVal;
                    if (myVal < val_min[varid])
                        val_min[varid] = myVal;
                    nValidEff[varid]++;
                }
                if(elem->Error(varid) > 0){
                    err_mean[varid] += elem->Error(varid);
                    nValidErr[varid]++;
                }
            }
        }


        newDir->cd();

        for (varid = 0; varid < this->NVariables(); varid++) {
//            val_mean[varid] /= BASE::Analyses.size();
//            err_mean[varid] /= BASE::Analyses.size();
            val_mean[varid] /= nValidEff[varid];
            err_mean[varid] /= nValidErr[varid];
            double distance = val_max[varid] - val_min[varid];
            cout<<"varid: "<<varid<<endl;
            cout<<"val_mean["<<varid<<"] = "<<val_mean[varid]<<endl;
            cout<<"err_mean["<<varid<<"] = "<<err_mean[varid]<<endl;
            cout<<"Min: "<<val_min[varid]<<", Max: "<<val_max[varid]<<", Distance: "<<distance<<endl;
            cout<<"nValid: " << nValidEff[varid]<<"\t"<<nValidErr[varid]<<endl;
            


            VAL_Init.push_back(val_mean[varid]);
            ERR_Init.push_back(err_mean[varid]);

            if (BASE::Analyses.size() > 1) {

                string hName = "hTemplate_" + this->GetVariableName(varid);
                string hTitle = "Template Results (" + this->GetVariableName(varid) + ")";

                TH1* h = new TH1D(hName.c_str(), hTitle.c_str(), 1000, val_min[varid] - (distance / 10.), val_max[varid] + (distance / 10.));
                for (uint s = 0; s < BASE::Analyses.size(); s++){
                    if(BASE::verbosity == -10)
                        cout<<"********* In the End method, Filling the Gaussian hidtogram"<<endl;
                    double myVal = ((MCAnalysis*)(BASE::Analyses[s]))->Value(varid);
                    if(myVal > 0 && myVal != 1)
                        h->Fill(myVal);
                }


                string fName = "fGaussian" + this->GetVariableName(varid);
                TF1* f = new TF1(fName.c_str(), "[0]*Gaus(x,[1],[2])", h->GetXaxis()->GetXmin(), h->GetXaxis()->GetXmax());

                f->SetParName(0, "Coeff");
                f->SetParameter("Coeff", BASE::Analyses.size() * TMath::Gaus(0., 0., err_mean[varid], kTRUE));
                f->SetParName(1, "Value");
                f->SetParameter("Value", val_mean[varid]);
                f->SetParName(2, "Error");
                f->SetParameter("Error", err_mean[varid]);


                h->Fit(f, "Q");
                h->Fit(f, "Q");
                h->Fit(f, "Q");

                VAL_.push_back(f->GetParameter("Value"));
                ERR_.push_back(f->GetParameter("Error"));

                h->Write();
                f->Write();
            } else {
                VAL_.push_back(val_mean[varid]);
                ERR_.push_back(err_mean[varid]);
            }
        }

        dir->cd();
    };

    double XSec;
    double Working_IntLum;
    double TotalNEvents;
    double NInitialBeforePreSel;
    string Name;
    int CurrentEvent;

//    std::vector<Filler> Fillers;

    int NVariables() {
        return (*(BASE::Analyses.begin()))->NVariables();
    }

    string GetVariableName(int i) {
        return (*(BASE::Analyses.begin()))->GetVariableName(i);
    }

    vector<double> VAL_Init;

    double ValueInit(int varid = 0) {
        return VAL_Init[varid];
    };
    vector<double> ERR_Init;

    double ERRInit(int varid = 0) {
        return ERR_Init[varid];
    };

    vector<double> VAL_;

    double Value(int varid = 0) {
        return VAL_[varid];
    };
    vector<double> ERR_;

    double ERR(int varid = 0) {
        return ERR_[varid];
    };
};

class IntLumis : public std::vector<IntLumHandler> {
public:
    //typedef IntLumHandler<Filler, Object> elements;
    typedef MCAnalysis Filler;
    typedef TopEvent Object;
    typedef IntLumHandler elements;
    typedef std::vector < elements > base;

    IntLumis(std::string name_, double xsec, int Total, int initial,bool dobtag, bool datalike,
            bool extJetOk_, MassAndResolution massAndres, ElectronCuts elecCuts, JetCuts jetCuts_,std::string which_ = "minChi2",
            bool Ott = false, int MIN_TO_SPLIT_ = 20) : Name(name_), XSec(xsec),TotalNEvents(Total), InitialBeforePreSel(initial),
            dobTag(dobtag),dobTagDataLike(datalike),extJets(extJetOk_),myMass(massAndres),myElec(elecCuts),myJet(jetCuts_),which(which_),
            OtherTtBar(Ott),MIN_TO_SPLIT(MIN_TO_SPLIT_) { };

public:
    void AddLumi(double Lumi, vector<double>* args = NULL) {
        elements elem(Name, XSec,TotalNEvents,InitialBeforePreSel,*args,dobTag,dobTagDataLike,extJets,Lumi,myMass,myElec,myJet,which,
                OtherTtBar,MIN_TO_SPLIT);

//        elements elem(XSec, Lumi, TotalNEvents, Name, args, MIN_TO_SPLIT);
        base::push_back(elem);
    }

    void Fill(const Object* obj) {
        for (uint i = 0; i < base::size(); i++) {
            elements* elem = &(base::at(i));

            elem->Fill(*obj);
        }
    }

    virtual void Write(TDirectory* dir) {
        if (base::size() == 0)
            return;

        TDirectory* newDir = dir->mkdir(Name.c_str());
        newDir->cd();

        vector<TH1*> hCompareInits;
        vector<TH1*> hCompareFits;

        int NVars = base::at(0).NVariables();
        for (int varid = 0; varid < NVars; varid++) {
            string name = base::at(0).GetVariableName(varid);

            string hName = name + "_hCompareInit";
            string hTitle = name + " vs. Int. Lumi (Mean values)";
            hCompareInits.push_back(new TH1D(hName.c_str(), hTitle.c_str(), base::size(), 0, base::size()));

            hName += name + "_hCompareFit";
            hTitle = name + " vs. Int. Lumi (Fit values)";
            hCompareFits.push_back(new TH1D(hName.c_str(), hTitle.c_str(), base::size(), 0, base::size()));
        }

        for (uint i = 0; i < base::size();) {
            elements* elem = &(base::at(i));

            elem->End(newDir);

            newDir->cd();

            std::stringstream bin_name;
            bin_name << elem->Working_IntLum;

            i++;
            for (int varid = 0; varid < base::at(0).NVariables(); varid++) {
                hCompareFits[varid]->GetXaxis()->SetBinLabel(i, bin_name.str().c_str());
                hCompareFits[varid]->SetBinContent(i, elem->Value(varid));
                hCompareFits[varid]->SetBinError(i, elem->ERR(varid));

                hCompareInits[varid]->GetXaxis()->SetBinLabel(i, bin_name.str().c_str());
                hCompareInits[varid]->SetBinContent(i, elem->ValueInit(varid));
                hCompareInits[varid]->SetBinError(i, elem->ERRInit(varid));
            }
        }

        for (int varid = 0; varid < base::at(0).NVariables(); varid++) {
            hCompareFits[varid]->Write();
            hCompareInits[varid]->Write();
        }
        dir->cd();
    }

    string Name;
    double XSec;
    double TotalNEvents;
    double InitialBeforePreSel;
    bool dobTag;
    bool dobTagDataLike;
    bool extJets;
    MassAndResolution myMass;
    ElectronCuts myElec;
    JetCuts myJet;
    string which;
    bool OtherTtBar;
    int MIN_TO_SPLIT;

    ~IntLumis() {
    };
};

#endif	/* _INTLUMHANDLER_H */

