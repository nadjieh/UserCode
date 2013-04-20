/* 
 * File:   LeptonTriggerComponent.h
 * Author: nadjieh
 *
 * Created on April 17, 2013, 8:06 PM
 */

#ifndef LEPTONTRIGGERCOMPONENT_H
#define	LEPTONTRIGGERCOMPONENT_H
#include "TString.h"
#include "TH1.h"
#include "TFile.h"
using namespace std;

class LeptonTriggerComponent {
public:

    LeptonTriggerComponent(TString trigName = "", TString var = "", TString dataRun = "") :
    name(trigName), variable(var), dataset(dataRun) {
        verbosity = 0;
        TString fileName = this->GetFileName("data");
        TFile * f = TFile::Open(fileName);
        dataEff = (TH1*)f->Get(var+"_data_eff");
        fileName = this->GetFileName("mc");
        f = TFile::Open(fileName);
        mcEff = (TH1*)f->Get(var+"_mc_eff");
    }

    virtual ~LeptonTriggerComponent() {
    }
    //setters

    void SetVerbosity(int n) {
        verbosity = n;
    }

    void SetTriggerName(TString n) {
        name = n;
    }

    void SetDataSet(TString n) {
        dataset = n;
    }

    //getters

    /*
     * We consider only the triggers available in both data and MC. This can change in future
     */
    TString GetInfoDirectory() {
        return dataset + "/HLT_" + name;
    }

    TString GetFileName(TString Data) {
        return (this->GetInfoDirectory() + "/" + variable + "_" + Data + ".root");
    }

    double GetDataEfficiency(double varValue) {
        int bin = dataEff->GetXaxis()->FindBin(varValue);
        return dataEff->GetBinContent(bin);
    }
    double GetMCEfficiency(double varValue) {
        int bin = mcEff->GetXaxis()->FindBin(varValue);
        return mcEff->GetBinContent(bin);
    }
    double GetLeptonTriggerSF(double varValue){
        return (this->GetDataEfficiency(varValue)/this->GetMCEfficiency(varValue));
    }

private:
    TString name;
    TString variable;
    TString dataset;
    TH1* dataEff;
    TH1* mcEff;
    int verbosity;
};

#endif	/* LEPTONTRIGGERCOMPONENT_H */

