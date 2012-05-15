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

#endif	/* MYOBJECTPROPERTIES_H */

