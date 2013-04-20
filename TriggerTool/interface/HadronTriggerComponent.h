/* 
 * File:   HadronTriggerComponent.h
 * Author: nadjieh
 *
 * Created on April 17, 2013, 8:06 PM
 */

#ifndef HADRONTRIGGERCOMPONENT_H
#define	HADRONTRIGGERCOMPONENT_H
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <cmath>
using namespace std;

struct JetInfo {
    double jetPt;
    double btagLow;
    double btagHigh;
    string type;
    string category;
};

struct TurnOnCurveFitPars {//y = a*exp( b*exp(c*x) )
    double a;
    double b;
    double c;
};

class HadronTriggerComponent {
public:

    HadronTriggerComponent(string trigName = "", string dataRun = "") :
    name(trigName), dataset(dataRun) {
        verbosity = 0;
        string fileName = this->GetFileName("???");
        myfile.open(fileName.c_str(), ios::in);
    }

    virtual ~HadronTriggerComponent() {
    }
    //setters

    void SetVerbosity(int n) {
        verbosity = n;
    }

    void SetTriggerName(string n) {
        name = n;
    }

    void SetDataSet(string n) {
        dataset = n;
    }

    //getters

    /*
     * We consider only the triggers available in both data and MC. This can change in future
     */
    string GetRegion(int nJet, int nTag) {
        stringstream s;
        s << nJet << "J" << nTag <<"T";
        return s.str();
    }

    string GetMCJetFlavor(int pdgId) {
        if (pdgId == 5) {
            return "MCb";
        }
        if (pdgId == 4) {
            return "MCc";
        }
        if (pdgId < 4) {
            return "MClight";
        }
        return "";
    }

    string GetInfoDirectory() {
        return dataset + name;
    }

    string GetFileName(string name) {
        return (this->GetInfoDirectory() + string("/") + name); // to be completed
    }

    pair<double, double> GetBTagInterval(double btagValue) {
        if (btagValue > -100. && btagValue < -5.)
            return make_pair(-100., -5.);
        if (btagValue > -5. && btagValue < 0.)
            return make_pair(-5., 0);
        if (btagValue > 0. && btagValue < 1.)
            return make_pair(0., 1.);
        if (btagValue > 1. && btagValue < 2.)
            return make_pair(1., 2.);
        if (btagValue > 2. && btagValue < 3.41)
            return make_pair(2., 3.41);
        if (btagValue > 3.41 && btagValue < 5.)
            return make_pair(3.41, 5.);
        if (btagValue > 5. && btagValue < 10.)
            return make_pair(5., 10.);
        if (btagValue > 10. && btagValue < 1000.)
            return make_pair(10., 1000.);
        return make_pair(-1000, -1000);
    }

    TurnOnCurveFitPars GetFitParameters(JetInfo myJetInfo) {
        //Supposed to extract a, b and c from myfile based on the JetInfo
        TurnOnCurveFitPars ret;
        //to be changed
        ret.a = 1;
        ret.b = 1;
        ret.c = 0;

        return ret;
    }

    double GetPerJetEfficiency(JetInfo myJetInfo) {
        TurnOnCurveFitPars pars = GetFitParameters(myJetInfo);
        return pars.a * exp(pars.b * exp(pars.c * myJetInfo.jetPt));
    }


private:
    string name;
    string dataset;
    ofstream myfile;
    int verbosity;
};


#endif	/* HADRONTRIGGERCOMPONENT_H */

