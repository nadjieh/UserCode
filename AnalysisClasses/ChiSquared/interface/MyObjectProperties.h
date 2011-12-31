/*                                                                                                                                              
 * File:   Matcher.h                                                                                                                            
 * Author: ajafari                                                                                                                              
 *                                                                                                                                              
 * Created on December 23, 2009, 1:57 PM                                                                                                        
 */

#ifndef _TopEvent_H
#define _TopEvent_H
#include "../../../Base/BaseAnalysis/interface/ObjectProperty.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootElectron.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootCaloJet.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootJet.h"
#include "../../../AnalysisClasses/ChiSquared/interface/ExtendedJet.h"
#include "../../../AnalysisClasses/ChiSquared/interface/TopEvent.h"
#include "../../../AnalysisClasses/LightJets/interface/EventShapeVariables.h"
#include "DR.h"

#include <iostream>
#include <sstream>
using namespace std;
using namespace TopTree;
#include <vector>
class TChiSquared : public ObjectProperty<TopEvent> {
public:

    TChiSquared() : ObjectProperty<TopEvent>("TChiSquared_fine", "TChiSquared_fine", 0., 100., 1000, "TopEvent", 1) {
    };

    virtual ~TChiSquared() {
    };

    virtual std::vector<double> ReadValue(const TopEvent * c)const {
       std::vector<double> values;
       values.clear();
       values.push_back(c->getTopChiSquared());
        return(values);
    };
};

class TChiSquaredM : public ObjectProperty<TopEvent> {
public:

    TChiSquaredM() : ObjectProperty<TopEvent>("TChiSquared_middle", "TChiSquared_middle", 0., 100., 100, "TopEvent", 2) {
    };

    virtual ~TChiSquaredM() {
    };

    virtual std::vector<double> ReadValue(const TopEvent * c)const {
       std::vector<double> values;
       values.clear();
       values.push_back(c->getTopChiSquared());
        return(values);
    };
};

class TChiSquaredR : public ObjectProperty<TopEvent> {
public:

    TChiSquaredR() : ObjectProperty<TopEvent>("TChiSquared_rough", "TChiSquared_rough", 0., 100., 10, "TopEvent", 3) {
    };

    virtual ~TChiSquaredR() {
    };

    virtual std::vector<double> ReadValue(const TopEvent * c)const {
       std::vector<double> values;
       values.clear();
       values.push_back(c->getTopChiSquared());
        return(values);
    };
};
class ExtChi2 : public ObjectProperty<TopEvent> {
public:

    ExtChi2() : ObjectProperty<TopEvent>("ExtChi2", "ExtChi2", 0., 100000., 10000, "TopEvent", 3) {
    };

    virtual ~ExtChi2() {
    };

    virtual std::vector<double> ReadValue(const TopEvent * c)const {
       std::vector<double> values;
       values.clear();
       values.push_back(c->getTopChiSquared());
        return(values);
    };
};
class TTopPt : public ObjectProperty<TopEvent> {
public:

    TTopPt() : ObjectProperty<TopEvent>("TopPt", "TopPt", 0., 1000., 200, "TopEvent", 4) {
    };

    virtual ~TTopPt() {
    };

    virtual std::vector<double> ReadValue(const TopEvent * c)const {
       std::vector<double> values;
       values.clear();
       values.push_back(c->getHadronicTop().Pt());
        return(values);
    };
};

class TMlb : public ObjectProperty<TopEvent> {
public:

    TMlb() : ObjectProperty<TopEvent>("Mlb", "Mlb", 0., 1000., 50, "TopEvent", 4) {
    };

    virtual ~TMlb() {
    };

    virtual std::vector<double> ReadValue(const TopEvent * c)const {
       std::vector<double> values;
       values.clear();
       values.push_back(c->getMlb());
        return(values);
    };


};


class TMll : public ObjectProperty<TopEvent> {
public:

    TMll() : ObjectProperty<TopEvent>("Mll", "Mll", 0., 1000., 50, "TopEvent", 4) {
    };

    virtual ~TMll() {
    };

    virtual std::vector<double> ReadValue(const TopEvent * c)const {
       std::vector<double> values;
       values.clear();
       values.push_back(c->getMll1());
       values.push_back(c->getMll2());
        return(values);
    };


};

class TopEta : public ObjectProperty<TopEvent> {
public:

    TopEta() : ObjectProperty<TopEvent>("TopEta", "TopEta",0.,3., 30, "TopEvent", 4) {
    };

    virtual ~TopEta() {
    };

    virtual std::vector<double> ReadValue(const TopEvent * c)const {
       std::vector<double> values;
       values.clear();
       values.push_back(fabs(c->getHadronicTop().Eta()));
        return(values);
    };


};

class TopPt : public ObjectProperty<TopEvent> {
public:

    TopPt() : ObjectProperty<TopEvent>("TopQuarkPt", "TopQuarkPt",0.,400., 200, "TopEvent", 4) {
    };

    virtual ~TopPt() {
    };

    virtual std::vector<double> ReadValue(const TopEvent * c)const {
       std::vector<double> values;
       values.clear();
       values.push_back(c->getHadronicTop().Pt());
        return(values);
    };


};

class DrTopW : public ObjectProperty<TopEvent> {
public:

    DrTopW() : ObjectProperty<TopEvent>("DrTopW", "DrTopW",0.,4., 80, "TopEvent", 4) {
    };

    virtual ~DrTopW() {
    };

    virtual std::vector<double> ReadValue(const TopEvent * c)const {
       std::vector<double> values;
       values.clear();
       DR<TLorentzVector> dr(c->getHadronicTop(),c->getHadronicW());
       values.push_back(dr.getValue());
        return(values);
    };
};
class DPhiTopW : public ObjectProperty<TopEvent> {
public:

    DPhiTopW() : ObjectProperty<TopEvent>("DPhiTopW", "DPhiTopW",0.,4.,40 , "TopEvent", 4) {
    };

    virtual ~DPhiTopW() {
    };

    virtual std::vector<double> ReadValue(const TopEvent * c)const {
       std::vector<double> values;
       values.clear();
       double dphi = fabs(c->getHadronicTop().Phi() - c->getHadronicW().Phi());
       if(dphi > M_PI)
           dphi = fabs((2*M_PI) - dphi);
       values.push_back(dphi);
        return(values);
    };
};
class DThetaTopW : public ObjectProperty<TopEvent> {
public:

    DThetaTopW() : ObjectProperty<TopEvent>("DThetaTopW", "DThetaTopW",0.,4.,80, "TopEvent", 4) {
    };

    virtual ~DThetaTopW() {
    };

    virtual std::vector<double> ReadValue(const TopEvent * c)const {
       std::vector<double> values;
       values.clear();
       double dTheta = fabs(c->getHadronicTop().Theta() - c->getHadronicW().Theta());
       values.push_back(dTheta);
        return(values);
    };
};
class DrTopLepB : public ObjectProperty<TopEvent> {
public:

    DrTopLepB() : ObjectProperty<TopEvent>("DrTopLepB", "DrTopLepB",0.,4., 80, "TopEvent", 4) {
    };

    virtual ~DrTopLepB() {
    };

    virtual std::vector<double> ReadValue(const TopEvent * c)const {
       std::vector<double> values;
       values.clear();
       DR<TLorentzVector> dr(c->getHadronicTop(),c->getLepBCand().getP4());
       values.push_back(dr.getValue());
        return(values);
    };
};
class DPhiTopLepB : public ObjectProperty<TopEvent> {
public:

    DPhiTopLepB() : ObjectProperty<TopEvent>("DPhiTopLepB", "DPhiTopLepB",0.,4.,40 , "TopEvent", 4) {
    };

    virtual ~DPhiTopLepB() {
    };

    virtual std::vector<double> ReadValue(const TopEvent * c)const {
       std::vector<double> values;
       values.clear();
       double dphi = fabs(c->getHadronicTop().Phi() - c->getLepBCand().getP4().Phi());
       if(dphi > M_PI)
           dphi = fabs((2*M_PI) - dphi);
       values.push_back(dphi);
        return(values);
    };
};
class DThetaTopLepB : public ObjectProperty<TopEvent> {
public:

    DThetaTopLepB() : ObjectProperty<TopEvent>("DThetaTopLepB", "DThetaTopLepB",0.,4.,80, "TopEvent", 4) {
    };

    virtual ~DThetaTopLepB() {
    };

    virtual std::vector<double> ReadValue(const TopEvent * c)const {
       std::vector<double> values;
       values.clear();
       double dTheta = fabs(c->getHadronicTop().Theta() - c->getLepBCand().getP4().Theta());
       values.push_back(dTheta);
        return(values);
    };
};
class DrTopHadB : public ObjectProperty<TopEvent> {
public:

    DrTopHadB() : ObjectProperty<TopEvent>("DrTopHadB", "DrTopHadB",0.,4., 80, "TopEvent", 4) {
    };

    virtual ~DrTopHadB() {
    };

    virtual std::vector<double> ReadValue(const TopEvent * c)const {
       std::vector<double> values;
       values.clear();
       DR<TLorentzVector> dr(c->getHadronicTop(),c->getHadBCand().getP4());
       values.push_back(dr.getValue());
        return(values);
    };
};
class DPhiTopHadB : public ObjectProperty<TopEvent> {
public:

    DPhiTopHadB() : ObjectProperty<TopEvent>("DPhiTopHadB", "DPhiTopHadB",0.,4.,40 , "TopEvent", 4) {
    };

    virtual ~DPhiTopHadB() {
    };

    virtual std::vector<double> ReadValue(const TopEvent * c)const {
       std::vector<double> values;
       values.clear();
       double dphi = fabs(c->getHadronicTop().Phi() - c->getHadBCand().getP4().Phi());
       if(dphi > M_PI)
           dphi = fabs((2*M_PI) - dphi);
       values.push_back(dphi);
        return(values);
    };
};
class DThetaTopHadB : public ObjectProperty<TopEvent> {
public:

    DThetaTopHadB() : ObjectProperty<TopEvent>("DThetaTopHadB", "DThetaTopHadB",0.,4.,80, "TopEvent", 4) {
    };

    virtual ~DThetaTopHadB() {
    };

    virtual std::vector<double> ReadValue(const TopEvent * c)const {
       std::vector<double> values;
       values.clear();
       double dTheta = fabs(c->getHadronicTop().Theta() - c->getHadBCand().getP4().Theta());
       values.push_back(dTheta);
        return(values);
    };
};
class DrHadWHadB : public ObjectProperty<TopEvent> {
public:

    DrHadWHadB() : ObjectProperty<TopEvent>("DrHadWHadB", "DrHadWHadB",0.,4., 80, "TopEvent", 4) {
    };

    virtual ~DrHadWHadB() {
    };

    virtual std::vector<double> ReadValue(const TopEvent * c)const {
       std::vector<double> values;
       values.clear();
       DR<TLorentzVector> dr(c->getHadronicW(),c->getHadBCand().getP4());
       values.push_back(dr.getValue());
        return(values);
    };
};
class DPhiHadWHadB : public ObjectProperty<TopEvent> {
public:

    DPhiHadWHadB() : ObjectProperty<TopEvent>("DPhiHadWHadB", "DPhiHadWHadB",0.,4.,40 , "TopEvent", 4) {
    };

    virtual ~DPhiHadWHadB() {
    };

    virtual std::vector<double> ReadValue(const TopEvent * c)const {
       std::vector<double> values;
       values.clear();
       double dphi = fabs(c->getHadronicW().Phi() - c->getHadBCand().getP4().Phi());
       if(dphi > M_PI)
           dphi = fabs((2*M_PI) - dphi);
       values.push_back(dphi);
        return(values);
    };
};
class DThetaHadWHadB : public ObjectProperty<TopEvent> {
public:

    DThetaHadWHadB() : ObjectProperty<TopEvent>("DThetaHadWHadB", "DThetaHadWHadB",0.,4.,80, "TopEvent", 4) {
    };

    virtual ~DThetaHadWHadB() {
    };

    virtual std::vector<double> ReadValue(const TopEvent * c)const {
       std::vector<double> values;
       values.clear();
       double dTheta = fabs(c->getHadronicW().Theta() - c->getHadBCand().getP4().Theta());
       values.push_back(dTheta);
        return(values);
    };
};
class DrHadWLepB : public ObjectProperty<TopEvent> {
public:

    DrHadWLepB() : ObjectProperty<TopEvent>("DrHadWLepB", "DrHadWLepB",0.,4., 80, "TopEvent", 4) {
    };

    virtual ~DrHadWLepB() {
    };

    virtual std::vector<double> ReadValue(const TopEvent * c)const {
       std::vector<double> values;
       values.clear();
       DR<TLorentzVector> dr(c->getHadronicW(),c->getLepBCand().getP4());
       values.push_back(dr.getValue());
        return(values);
    };
};
class DPhiHadWLepB : public ObjectProperty<TopEvent> {
public:

    DPhiHadWLepB() : ObjectProperty<TopEvent>("DPhiHadWLepB", "DPhiHadWLepB",0.,4.,40 , "TopEvent", 4) {
    };

    virtual ~DPhiHadWLepB() {
    };

    virtual std::vector<double> ReadValue(const TopEvent * c)const {
       std::vector<double> values;
       values.clear();
       double dphi = fabs(c->getHadronicW().Phi() - c->getLepBCand().getP4().Phi());
       if(dphi > M_PI)
           dphi = fabs((2*M_PI) - dphi);
       values.push_back(dphi);
        return(values);
    };
};
class DThetaHadWLepB : public ObjectProperty<TopEvent> {
public:

    DThetaHadWLepB() : ObjectProperty<TopEvent>("DThetaHadWLepB", "DThetaHadWLepB",0.,4.,80, "TopEvent", 4) {
    };

    virtual ~DThetaHadWLepB() {
    };

    virtual std::vector<double> ReadValue(const TopEvent * c)const {
       std::vector<double> values;
       values.clear();
       double dTheta = fabs(c->getHadronicW().Theta() - c->getLepBCand().getP4().Theta());
       values.push_back(dTheta);
        return(values);
    };
};
class DrHadBLepton : public ObjectProperty<TopEvent> {
public:

    DrHadBLepton() : ObjectProperty<TopEvent>("DrHadBLepton", "DrHadBLepton",0.,4., 80, "TopEvent", 4) {
    };

    virtual ~DrHadBLepton() {
    };

    virtual std::vector<double> ReadValue(const TopEvent * c)const {
       std::vector<double> values;
       values.clear();
       DR<TLorentzVector> dr(c->getHadBCand().getP4(),c->Electron);
       values.push_back(dr.getValue());
        return(values);
    };
};
class DPhiHadBLepton : public ObjectProperty<TopEvent> {
public:

    DPhiHadBLepton() : ObjectProperty<TopEvent>("DPhiHadBLepton", "DPhiHadBLepton",0.,4.,40 , "TopEvent", 4) {
    };

    virtual ~DPhiHadBLepton() {
    };

    virtual std::vector<double> ReadValue(const TopEvent * c)const {
       std::vector<double> values;
       values.clear();
       double dphi = fabs(c->getHadBCand().getP4().Phi() - c->Electron.Phi());
       if(dphi > M_PI)
           dphi = fabs((2*M_PI) - dphi);
       values.push_back(dphi);
        return(values);
    };
};
class DThetaHadBLepton : public ObjectProperty<TopEvent> {
public:

    DThetaHadBLepton() : ObjectProperty<TopEvent>("DThetaHadBLepton", "DThetaHadBLepton",0.,4.,80, "TopEvent", 4) {
    };

    virtual ~DThetaHadBLepton() {
    };

    virtual std::vector<double> ReadValue(const TopEvent * c)const {
       std::vector<double> values;
       values.clear();
       double dTheta = fabs(c->getHadBCand().getP4().Theta() - c->Electron.Theta());
       values.push_back(dTheta);
        return(values);
    };
};
class RelTopPt : public ObjectProperty<TopEvent> {
public:

    RelTopPt() : ObjectProperty<TopEvent>("RelTopPt", "RelTopPt",0.,1.,80, "TopEvent", 4) {
    };

    virtual ~RelTopPt() {
    };

    virtual std::vector<double> ReadValue(const TopEvent * c)const {
       std::vector<double> values;
       values.clear();
       
       values.push_back(((double)c->getHadronicTop().Pt()/(double)c->TopPtSum));
        return(values);
    };
};

class TBtag : public ObjectProperty<ExtendedJet> {
public:
    TBtag() : ObjectProperty<ExtendedJet>("Btag", "Btag", -200.,60.,520, "ExtendedJet", 5) {
        
    };

    virtual ~TBtag() {
    };

    virtual std::vector<double> ReadValue(const ExtendedJet * c)const {
       std::vector<double> values;
       values.clear();
       values.push_back(c->getJet().btag_trackCountingHighEffBJetTags());
        return(values);
    };


};
class Pt : public ObjectProperty<ExtendedJet> {
public:

    Pt() : ObjectProperty<ExtendedJet>("Pt", "Pt",0.,400., 200, "ExtendedJet", 6) {
    };

    virtual ~Pt() {
    };

    virtual std::vector<double> ReadValue(const ExtendedJet * c)const {
       std::vector<double> values;
       values.clear();
       values.push_back(c->getJet().Pt());
        return(values);
    };


};
class Eta : public ObjectProperty<ExtendedJet> {
public:

    Eta() : ObjectProperty<ExtendedJet>("Eta", "Eta",0.,3., 30, "ExtendedJet", 7) {
    };

    virtual ~Eta() {
    };

    virtual std::vector<double> ReadValue(const ExtendedJet * c)const {
       std::vector<double> values;
       values.clear();
       values.push_back(fabs(c->getJet().Eta()));
        return(values);
    };
};
class JetBasedMLJ : public ObjectProperty<ExtendedJet> {
public:

    JetBasedMLJ() : ObjectProperty<ExtendedJet>("JetBasedMLJ", "JetBasedMLJ",0.,1000., 50, "ExtendedJet", 7)
    { };

    virtual ~JetBasedMLJ() {
    };

    virtual std::vector<double> ReadValue(const ExtendedJet * c)const {
       std::vector<double> values;
       values.clear();
       values.push_back(c->getMJetLepton());
//       cout<<"IN MyObejcProperty, JetBasedMLJ\n\t===> "<<values.at(0)<<endl;
        return(values);
    };
};

//EventShapes
class TopEventShape : public ObjectProperty<TopEvent> {
public:

    TopEventShape(std::string which, double R = 2.) :
    ObjectProperty<TopEvent>(which, which,0.,1.1,110, "TopEvent", 10),Which(which), r(R) {
    };

    virtual ~TopEventShape() {
    };

    virtual std::vector<double> ReadValue(const TopEvent * c)const {
        EventShapeVariables myShapeVar(*c);
        std::vector<double> values;
        values.clear();
        if(Which == "isotropy"){
            values.push_back(myShapeVar.isotropy(100));
        }
        else if(Which == "circularity"){
            values.push_back(myShapeVar.circularity(100));
        }
        else if(Which == "sphericity"){
            values.push_back(myShapeVar.sphericity(r));
        }
        else if(Which == "aplanarity"){
            values.push_back(myShapeVar.aplanarity(r));
        }
        else if(Which == "C"){
            values.push_back(myShapeVar.C(r));
        }
        else if(Which == "D"){
            values.push_back(myShapeVar.D(r));
        }
        else
            values.push_back(-1.);

        return(values);
    };
private:
    std::string Which;
    double r;
};
class HT : public ObjectProperty<TopEvent> {
public:

    HT(std::vector<int> indecies, std::string name) :
    ObjectProperty<TopEvent>(string("Ht_"+name),string("Ht_"+name), 0., 1000., 100, "TopEvent", 4) {
        index.clear();
        index = indecies;
    };

    virtual ~HT() {
    };

    virtual std::vector<double> ReadValue(const TopEvent * c)const {
       std::vector<double> values;
       values.clear();
       double val = 0;
       for(unsigned int i = 0; i < index.size(); i++){
           val += c->Jets.at(index.at(i)).getJet().Pt();
       }
       values.push_back(val);
        return(values);
    };
private:
    std::vector<int> index;


};


#endif /*_TopEvent_H*/
/*        BASE_::AddProp(new TopEta());
        BASE_::AddProp(new TopPt());

        BASE_::AddProp(new DrTopW());
        BASE_::AddProp(new DrTopLepB());
        BASE_::AddProp(new DrTopHadB());
        BASE_::AddProp(new DrHadWLepB());
        BASE_::AddProp(new DrHadWHadB());
        BASE_::AddProp(new DrHadBLepton());

        BASE_::AddProp(new DPhiHadBLepton());
        BASE_::AddProp(new DPhiHadWHadB());
        BASE_::AddProp(new DPhiHadWLepB());
        BASE_::AddProp(new DPhiTopHadB());
        BASE_::AddProp(new DPhiTopLepB());
        BASE_::AddProp(new DPhiTopW());

        BASE_::AddProp(new DThetaHadBLepton());
        BASE_::AddProp(new DThetaHadWHadB());
        BASE_::AddProp(new DThetaHadWLepB());
        BASE_::AddProp(new DThetaTopHadB());
        BASE_::AddProp(new DThetaTopLepB());
        BASE_::AddProp(new DThetaTopW());


        BASE_::AddProp(new TopEventShape("isotropy"));
        BASE_::AddProp(new TopEventShape("circularity"));
        BASE_::AddProp(new TopEventShape("sphericity"));
        BASE_::AddProp(new TopEventShape("aplanarity"));
        BASE_::AddProp(new TopEventShape("C"));
        BASE_::AddProp(new TopEventShape("D"));

        std::vector<int> index;
        index.push_back(0);
        index.push_back(1);
        index.push_back(2);
        BASE_::AddProp(new HT(index,"123"));
        index.clear();
        index.push_back(1);
        index.push_back(2);
        index.push_back(3);
        BASE_::AddProp(new HT(index,"234"));
        index.clear();
        index.push_back(0);
        index.push_back(1);
        index.push_back(3);
        BASE_::AddProp(new HT(index,"124"));
        index.clear();
        index.push_back(0);
        index.push_back(2);
        index.push_back(3);
        BASE_::AddProp(new HT(index,"134"));
        index.clear();
        index.push_back(0);
        index.push_back(1);
        BASE_::AddProp(new HT(index,"12"));
        index.clear();
        index.push_back(0);
        index.push_back(2);
        BASE_::AddProp(new HT(index,"13"));
        index.clear();
        index.push_back(0);
        index.push_back(3);
        BASE_::AddProp(new HT(index,"14"));
        index.clear();
        index.push_back(1);
        index.push_back(2);
        BASE_::AddProp(new HT(index,"23"));
        index.clear();
        index.push_back(1);
        index.push_back(3);
        BASE_::AddProp(new HT(index,"24"));
        index.clear();
        index.push_back(2);
        index.push_back(3);
        BASE_::AddProp(new HT(index,"34"));
        index.clear();
        index.push_back(0);
        index.push_back(1);
        index.push_back(2);
        index.push_back(3);
        BASE_::AddProp(new HT(index,"all"));*/
