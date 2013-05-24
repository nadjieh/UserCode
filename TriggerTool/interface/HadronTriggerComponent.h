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
#include <vector>
using namespace std;

struct JetInfo {
    double jetPt;
    double btag;
    string type;
    string category;
};

struct TurnOnCurveErrors {//da, db, dc, NO covariances
    double da;
    double db;
    double dc;
};

struct TurnOnCurveFitPars {//y = a*exp( b*exp(c*x) )
    double a;
    double b;
    double c;
};

class BtagRange {
public:

    BtagRange(double lowB, double highB/*, TurnOnCurveFitPars fit, TurnOnCurveErrors efit*/) : btagLow(lowB),
    btagHigh(highB) {
        //        fitPar.a = fit.a;
        //        fitPar.b = fit.b;
        //        fitPar.c = fit.c;
        //        fitParErr.da = efit.da;
        //        fitParErr.db = efit.db;
        //        fitParErr.dc = efit.dc;
    }

    BtagRange(double lowB, double highB, double a, double b, double c, double da, double db, double dc) :
    btagLow(lowB), btagHigh(highB) {
        fitPar.a = a;
        fitPar.b = b;
        fitPar.c = c;
        fitParErr.da = da;
        fitParErr.db = db;
        fitParErr.dc = dc;
    }

    virtual ~BtagRange() {
    }

    bool isInRange(double btag) {
        return ((btag >= btagLow) && (btag < btagHigh));
    }

    void SetFitParameters(double a, double b, double c) {
        fitPar.a = a;
        fitPar.b = b;
        fitPar.c = c;
    };

    void SetFitParameterErrors(double a, double b, double c) {
        fitParErr.da = a;
        fitParErr.db = b;
        fitParErr.dc = c;
    };

    TurnOnCurveFitPars GetFitParameters()const {
        return fitPar;
    };

    TurnOnCurveErrors GetFitParameterErrors()const {
        return fitParErr;
    };
private:
    double btagLow;
    double btagHigh;
    TurnOnCurveFitPars fitPar;
    TurnOnCurveErrors fitParErr;
};

class Category {
public:

    Category(string myCat) : cat(myCat) {
        myBtagRanges.clear();
    }

    virtual ~Category() {
    }

    void AddBtagRange(BtagRange input) {
        myBtagRanges.push_back(input);
    }

    void SetCatName(string name) {
        cat = name;
    }

    string CategoryName()const {
        return cat;
    }

    std::vector<BtagRange> GetBtagRanges()const {
        return myBtagRanges;
    }
private:
    string cat;
    std::vector<BtagRange> myBtagRanges;
};

class TurnOnInfo {
public:

    TurnOnInfo(string TYPE) : type(TYPE) {
        allInfo.clear();
    }

    ~TurnOnInfo() {
    }

    void SetInfo(std::vector<Category> input) {
        for (unsigned int i = 0; i < input.size(); i++) {
            allInfo.push_back(input[i]);
        }
    }

    void AddCategory(Category input) {
        allInfo.push_back(input);
    }

    std::vector<BtagRange> GetCategory(string catName) {
        /*
         * 0: all
         * 1: 2J0B
         * 2: 2J1B
         * 3: 3J1B
         * 4: 3J2B
         */
        if (catName == "all")
            return allInfo[0].GetBtagRanges();
        if (catName == "2J0B")
            return allInfo[1].GetBtagRanges();
        if (catName == "2J1B")
            return allInfo[2].GetBtagRanges();
        if (catName == "3J1B")
            return allInfo[3].GetBtagRanges();
        if (catName == "3J2B")
            return allInfo[4].GetBtagRanges();
        cout << "Bad Category!! Expect Errors!" << endl;
        std::vector<BtagRange> ret;
        return ret;
    }

    TurnOnCurveFitPars GetFitParameters(JetInfo myJet) {
        std::vector<BtagRange> myBlock = GetCategory(myJet.category);
        for (unsigned int i = 0; i < myBlock.size(); i++) {
            if (myBlock[i].isInRange(myJet.btag)) {
                return myBlock[i].GetFitParameters();
            }
        }
        cout << "Bad batg!! Expect Errors!" << endl;
        TurnOnCurveFitPars ret;
        return ret;
    }

    TurnOnCurveErrors GetFitParameterErrors(JetInfo myJet) {
        std::vector<BtagRange> myBlock = GetCategory(myJet.category);
        for (unsigned int i = 0; i < myBlock.size(); i++) {
            if (myBlock[i].isInRange(myJet.btag)) {
                return myBlock[i].GetFitParameterErrors();
            }
        }
        cout << "Bad batg!! Expect Errors!" << endl;
        TurnOnCurveErrors ret;
        return ret;
    }

    void SetType(string TYPE) {
        type = TYPE;
    }

    void ResetCategories() {
        allInfo.clear();
    }
private:
    string type;
    std::vector<Category> allInfo;
};

class HadronTriggerComponent {
public:

    HadronTriggerComponent(string trigName = "", string dataRun = "", string type = "data") :
    name(trigName), dataset(dataRun), myTurnOnInfo(type) {
        // Just read the data ascii file and store the information in a class
        verbosity = 0;
        string fileName = this->GetFileName(string(type + ".ascii"));
        ifstream myfile;
        myfile.open(fileName.c_str(), ios::in);
        string tmptype, tmpcat;
        double tmpblow, tmpbhigh, tmpa, tmpb, tmpc, tmperra, tmperrb, tmperrc;
        Category * myCat = 0;
        myTurnOnInfo.ResetCategories();
        int iLine = 0;
        cout << "Going through the lines of file "<< fileName<< endl;
        
        while (!myfile.eof()) {
            myfile >> tmptype >> tmpcat >> tmpblow >> tmpbhigh >> tmpa >> tmpb >> tmpc >> tmperra >> tmperrb >> tmperrc;
            if (myCat == 0) {
                myCat = new Category(tmpcat);
            } else if (string(myCat->CategoryName()) != tmpcat) {
                cout<<"Line: "<<iLine<<"\tnew Category"<<endl;
                myTurnOnInfo.AddCategory(*myCat);
                myCat = new Category(tmpcat);
            }
            BtagRange myBrange(tmpblow, tmpbhigh, tmpa, tmpb, tmpc, tmperra, tmperrb, tmperrc);
            myCat->AddBtagRange(myBrange);
            iLine++;
        }
        myfile.close();
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
        s << nJet << "J" << nTag << "T";
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
        return "../files/" + dataset + "/" + name;
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
        return myTurnOnInfo.GetFitParameters(myJetInfo);
    }

    TurnOnCurveFitPars GetParametersErrors(JetInfo myJetInfo) {
        //Supposed to extract a, b and c from myfile based on the JetInfo
        return myTurnOnInfo.GetFitParameters(myJetInfo);
    }

    double GetPerJetEfficiency(JetInfo myJetInfo) {
        TurnOnCurveFitPars pars = GetFitParameters(myJetInfo);
        return pars.a * exp(pars.b * exp(pars.c * myJetInfo.jetPt));
    }
    /*
     * Will be completed later
     * ln u = ln a + b * exp (c*pt) 
     * du/u = da/a + db * exp(c*pt) + b * pt * exp (c*pt)
     * (du/u)^2 = (da/a)^2 + (db * exp(c*pt))^2 + (b * pt* dc * exp (c*pt))^2
     *            + 2*(da/a)*(db * exp(c*pt)) + 2*da/a*(b * pt* dc * exp (c*pt)) + 2*(db * exp(c*pt))*(b * pt* dc * exp (c*pt))


    Independent JetTag and flavor categories
    double GetPerJetUncertainty(JetInfo myJetInfo) {
        TurnOnCurveErrors errors = GetParametersErrors(myJetInfo);
        TurnOnCurveFitPars pars = GetFitParameters(myJetInfo);
        double self1 = pow((errors.da / pars.a), 2);
        double self2 = pow((errors.db * exp(pars.c * myJetInfo.jetPt)), 2);
        double self3 = pow((pars.b * myJetInfo.jetPt * errors.dc * exp(pars.c * myJetInfo.jetPt)), 2);
        double
    }
     */

private:
    string name;
    string dataset;
    int verbosity;
    TurnOnInfo myTurnOnInfo;
};


#endif	/* HADRONTRIGGERCOMPONENT_H */

