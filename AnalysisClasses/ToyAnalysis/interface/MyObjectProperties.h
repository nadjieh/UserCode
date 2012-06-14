/* 
 * File:   MyObjectProperties.h
 * Author: nadjieh
 *
 * Created on May 11, 2012, 10:46 AM
 */

#ifndef MYOBJECTPROPERTIES_H
#define	MYOBJECTPROPERTIES_H

#include "../../../Base/BaseAnalysis/interface/ObjectProperty.h"
#include "../../PhysicsObjects/interface/SemiLepTopQuark.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootPFJet.h"
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;
using namespace TopTree;
class JetEta : public ObjectProperty<TRootPFJet> {
public:

    JetEta() : ObjectProperty<TRootPFJet>("JetEta", "JetEta", 0., 5., 500, "TRootPFJet", 1) {
    };

    virtual ~JetEta() {
    };

    virtual std::vector<double> ReadValue(const TRootPFJet * c)const {
       std::vector<double> values;
       values.clear();
       values.push_back(fabs(c->Eta()));
        return(values);
    };
};

class FwDJetEta : public ObjectProperty<SemiLepTopQuark> {
public:

    FwDJetEta() : ObjectProperty<SemiLepTopQuark>("FwDJetEta", "FwDJetEta", 0., 5., 500, "SemiLepTopQuark", 1) {
    };

    virtual ~FwDJetEta() {
    };

    virtual std::vector<double> ReadValue(const SemiLepTopQuark * c)const {
       std::vector<double> values;
       values.clear();
       values.push_back(fabs(c->getFwDJet().Eta()));
        return(values);
    };
};

class CosThetaStarW : public ObjectProperty<SemiLepTopQuark> {
public:

    CosThetaStarW() : ObjectProperty<SemiLepTopQuark>("CosThetaStarW", "CosThetaStarW", -1, 1, 500, "SemiLepTopQuark", 1) {
    };

    virtual ~CosThetaStarW() {
    };

    virtual std::vector<double> ReadValue(const SemiLepTopQuark * c)const {
       std::vector<double> values;
       values.clear();
       values.push_back(c->cosThetaStar());
        return(values);
    };
};

class CosThetaStarMET : public ObjectProperty<SemiLepTopQuark> {
public:

    CosThetaStarMET() : ObjectProperty<SemiLepTopQuark>("CosThetaStarMET", "CosThetaStarMET", -1., 1., 500, "SemiLepTopQuark", 1) {
    };

    virtual ~CosThetaStarMET() {
    };

    virtual std::vector<double> ReadValue(const SemiLepTopQuark * c)const {
       std::vector<double> values;
       values.clear();
       values.push_back(c->cosThetaStar(2));
        return(values);
    };
};
class HT : public ObjectProperty<SemiLepTopQuark> {
public:

    HT() : ObjectProperty<SemiLepTopQuark>("HT", "HT", 0., 1000., 500, "SemiLepTopQuark", 1) {
    };

    virtual ~HT() {
    };

    virtual std::vector<double> ReadValue(const SemiLepTopQuark * c)const {
        double res = c->getMET(-1).Pt();//MET
        res+=c->getbJet().Pt();
        res+=c->getunTagged().Pt();
        res+=c->getMuon().Pt();
       std::vector<double> values;
       values.clear();
       values.push_back(res);
        return(values);
    };
};

#endif	/* MYOBJECTPROPERTIES_H */

