/*                                                                                                                                              
 * File:   Matcher.h                                                                                                                            
 * Author: ajafari                                                                                                                              
 *                                                                                                                                              
 * Created on December 23, 2009, 1:57 PM                                                                                                        
 */

#ifndef _TopEvent_H
#define _TopEvent_H
#include "/afs/cern.ch/user/a/ajafari/scratch0/CMSSW_3_8_5_patch3/src/Base/BaseAnalysis/interface/ObjectProperty.h"
#include "/afs/cern.ch/user/a/ajafari/scratch0/CMSSW_3_8_5_patch3/src/TopBrussels/TopTreeProducer/interface/TRootElectron.h"
#include "/afs/cern.ch/user/a/ajafari/scratch0/CMSSW_3_8_5_patch3/src/TopBrussels/TopTreeProducer/interface/TRootTagProbeObject.h"
#include "/afs/cern.ch/user/a/ajafari/scratch0/CMSSW_3_8_5_patch3/src/TopBrussels/TopTreeProducer/interface/TRootCaloJet.h"
#include "/afs/cern.ch/user/a/ajafari/scratch0/CMSSW_3_8_5_patch3/src/TopBrussels/TopTreeProducer/interface/TRootJet.h"
#include "/afs/cern.ch/user/a/ajafari/scratch0/CMSSW_3_8_5_patch3/src/AnalysisClasses/ChiSquared/interface/ExtendedJet.h"
#include "/afs/cern.ch/user/a/ajafari/scratch0/CMSSW_3_8_5_patch3/src/AnalysisClasses/ChiSquared/interface/TopEvent.h"
#include "/afs/cern.ch/user/a/ajafari/scratch0/CMSSW_3_8_5_patch3/src/AnalysisClasses/LightJets/interface/EventShapeVariables.h"
#include "/afs/cern.ch/user/a/ajafari/scratch0/CMSSW_3_8_5_patch3/src/AnalysisClasses/ChiSquared/interface/DR.h"

#include <iostream>
#include <sstream>
using namespace std;
using namespace TopTree;
#include <vector>
//class ProbePt : public ObjectProperty<TRootTagProbeObject> {
//public:
//
//    ProbePt() : ObjectProperty<TRootTagProbeObject>("ProbePt", "ProbePt", 20., 180., 8, "TPO", 1) {
//    };
//
//    virtual ~ProbePt() {
//    };
//
//    virtual std::vector<double> ReadValue(const TRootTagProbeObject * c)const {
//       std::vector<double> values;
//       values.clear();
//       values.push_back(c->Pt());
//        return(values);
//    };
//};

class ProbePt : public ObjectProperty<TRootTagProbeObject> {
public:

    ProbePt() : ObjectProperty<TRootTagProbeObject>("ProbePt", "ProbePt", 30., 80., 5, "TPO", 1) {
    };

    virtual ~ProbePt() {
    };

    virtual std::vector<double> ReadValue(const TRootTagProbeObject * c)const {
       std::vector<double> values;
       values.clear();
       values.push_back(c->Pt());
        return(values);
    };
};
class ProbeEta : public ObjectProperty<TRootTagProbeObject> {
public:

    ProbeEta() : ObjectProperty<TRootTagProbeObject>("ProbeEta", "ProbeEta", 0., 2.5, 5, "TPO", 1) {
    };

    virtual ~ProbeEta() {
    };

    virtual std::vector<double> ReadValue(const TRootTagProbeObject * c)const {
       std::vector<double> values;
       values.clear();
       values.push_back(c->Eta());
        return(values);
    };
};
//class ProbeEta : public ObjectProperty<TRootTagProbeObject> {
//public:
//
//    ProbeEta() : ObjectProperty<TRootTagProbeObject>("ProbeEta", "ProbeEta", 0., 3., 15, "TPO", 1) {
//    };
//
//    virtual ~ProbeEta() {
//    };
//
//    virtual std::vector<double> ReadValue(const TRootTagProbeObject * c)const {
//       std::vector<double> values;
//       values.clear();
//       values.push_back(c->Eta());
//        return(values);
//    };
//};
class ProbePhi : public ObjectProperty<TRootTagProbeObject> {
public:

    ProbePhi() : ObjectProperty<TRootTagProbeObject>("ProbePhi", "ProbePhi", 0., 3., 5, "TPO", 1) {
    };

    virtual ~ProbePhi() {
    };

    virtual std::vector<double> ReadValue(const TRootTagProbeObject * c)const {
       std::vector<double> values;
       values.clear();
       values.push_back(c->Phi());
        return(values);
    };
};
//class ProbePhi : public ObjectProperty<TRootTagProbeObject> {
//public:
//
//    ProbePhi() : ObjectProperty<TRootTagProbeObject>("ProbePhi", "ProbePhi", 0., 4., 40, "TPO", 1) {
//    };
//
//    virtual ~ProbePhi() {
//    };
//
//    virtual std::vector<double> ReadValue(const TRootTagProbeObject * c)const {
//       std::vector<double> values;
//       values.clear();
//       values.push_back(c->Phi());
//        return(values);
//    };
//};
class minRJetProbe : public ObjectProperty<TRootTagProbeObject> {
public:

    minRJetProbe() : ObjectProperty<TRootTagProbeObject>("minRJetProbe", "minRJetProbe", 0., 5., 5, "TPO", 1) {
    };

    virtual ~minRJetProbe() {
    };

    virtual std::vector<double> ReadValue(const TRootTagProbeObject * c)const {
       std::vector<double> values;
       values.clear();
       values.push_back(c->minRJet);
        return(values);
    };
};
//class minRJetProbe : public ObjectProperty<TRootTagProbeObject> {
//public:
//
//    minRJetProbe() : ObjectProperty<TRootTagProbeObject>("minRJetProbe", "minRJetProbe", 0., 4., 40, "TPO", 1) {
//    };
//
//    virtual ~minRJetProbe() {
//    };
//
//    virtual std::vector<double> ReadValue(const TRootTagProbeObject * c)const {
//       std::vector<double> values;
//       values.clear();
//       values.push_back(c->minRJet);
//        return(values);
//    };
//};
class nJet : public ObjectProperty<TRootTagProbeObject> {
public:

    nJet() : ObjectProperty<TRootTagProbeObject>("nJet", "nJet", 0., 5., 5, "TPO", 1) {
    };

    virtual ~nJet() {
    };

    virtual std::vector<double> ReadValue(const TRootTagProbeObject * c)const {
       std::vector<double> values;
       values.clear();
       values.push_back((double)c->nJet);
        return(values);
    };
};
//class nJet : public ObjectProperty<TRootTagProbeObject> {
//public:
//
//    nJet() : ObjectProperty<TRootTagProbeObject>("nJet", "nJet", 0., 10., 10, "TPO", 1) {
//    };
//
//    virtual ~nJet() {
//    };
//
//    virtual std::vector<double> ReadValue(const TRootTagProbeObject * c)const {
//       std::vector<double> values;
//       values.clear();
//       values.push_back((double)c->nJet);
//        return(values);
//    };
//};
class Zmass : public ObjectProperty<TRootTagProbeObject> {
public:

    Zmass() : ObjectProperty<TRootTagProbeObject>("TagProbInvMass", "TagProbInvMass", 50., 130., 80, "TPO", 1) {
    };

    virtual ~Zmass() {
    };

    virtual std::vector<double> ReadValue(const TRootTagProbeObject * c)const {
       std::vector<double> values;
       values.clear();
       values.push_back((double)c->Mass.at(0));
        return(values);
    };
};
class ProbeTrackIso : public ObjectProperty<TRootTagProbeObject> {
public:

    ProbeTrackIso() : ObjectProperty<TRootTagProbeObject>("ProbeTrackIso", "ProbeTrackIso", 0., 10., 100, "TPO", 1) {
    };

    virtual ~ProbeTrackIso() {
    };

    virtual std::vector<double> ReadValue(const TRootTagProbeObject * c)const {
       std::vector<double> values;
       values.clear();
       values.push_back(c->trackerIso(3));
        return(values);
    };
};
class ProbeEcalIso : public ObjectProperty<TRootTagProbeObject> {
public:

    ProbeEcalIso() : ObjectProperty<TRootTagProbeObject>("ProbeEcalIso", "ProbeEcalIso", 0., 10., 100, "TPO", 1) {
    };

    virtual ~ProbeEcalIso() {
    };

    virtual std::vector<double> ReadValue(const TRootTagProbeObject * c)const {
       std::vector<double> values;
       values.clear();
       values.push_back(c->ecalIso(3));
        return(values);
    };
};
class ProbeHcalIso : public ObjectProperty<TRootTagProbeObject> {
public:

    ProbeHcalIso() : ObjectProperty<TRootTagProbeObject>("ProbeHcalIso", "ProbeHcalIso", 0., 10., 100, "TPO", 1) {
    };

    virtual ~ProbeHcalIso() {
    };

    virtual std::vector<double> ReadValue(const TRootTagProbeObject * c)const {
       std::vector<double> values;
       values.clear();
       values.push_back(c->hcalIso(3));
        return(values);
    };
};
class ProbeHoE : public ObjectProperty<TRootTagProbeObject> {
public:

    ProbeHoE() : ObjectProperty<TRootTagProbeObject>("ProbeHoE", "ProbeHoE", 0., 1., 1000, "TPO", 1) {
    };

    virtual ~ProbeHoE() {
    };

    virtual std::vector<double> ReadValue(const TRootTagProbeObject * c)const {
       std::vector<double> values;
       values.clear();
       values.push_back(fabs(c->hadronicOverEm()));
        return(values);
    };
};
class ProbeSigmaIEtaIEta : public ObjectProperty<TRootTagProbeObject> {
public:

    ProbeSigmaIEtaIEta() : ObjectProperty<TRootTagProbeObject>("ProbeSigmaIEtaIEta", "ProbeSigmaIEtaIEta", 0., 1., 100, "TPO", 1) {
    };

    virtual ~ProbeSigmaIEtaIEta() {
    };

    virtual std::vector<double> ReadValue(const TRootTagProbeObject * c)const {
       std::vector<double> values;
       values.clear();
       values.push_back(fabs(c->sigmaIEtaIEta()));
        return(values);
    };
};
class ProbedelEtaIn : public ObjectProperty<TRootTagProbeObject> {
public:

    ProbedelEtaIn() : ObjectProperty<TRootTagProbeObject>("ProbedelEtaIn", "ProbedelEtaIn", 0., 1., 1000, "TPO", 1) {
    };

    virtual ~ProbedelEtaIn() {
    };

    virtual std::vector<double> ReadValue(const TRootTagProbeObject * c)const {
       std::vector<double> values;
       values.clear();
       values.push_back(fabs(c->deltaEtaIn()));
        return(values);
    };
};
class ProbedelPhiIn : public ObjectProperty<TRootTagProbeObject> {
public:

    ProbedelPhiIn() : ObjectProperty<TRootTagProbeObject>("ProbedelPhiIn", "ProbedelPhiIn", 0., 1., 100, "TPO", 1) {
    };

    virtual ~ProbedelPhiIn() {
    };

    virtual std::vector<double> ReadValue(const TRootTagProbeObject * c)const {
       std::vector<double> values;
       values.clear();
       values.push_back(fabs(c->deltaPhiIn()));
        return(values);
    };
};
#endif /*_TopEvent_H*/
