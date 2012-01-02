/* 
 * File:   TRootTagProbeObject.h
 * Author: ajafari
 *
 * Created on October 20, 2010, 2:42 PM
 */

#ifndef TROOTTAGPROBEOBJECT_H
#define	TROOTTAGPROBEOBJECT_H
#include "TRootElectron.h"
#include <vector>
using namespace std;

namespace TopTree{
    class TRootTagProbeObject : public TRootElectron{
    public:
        TRootTagProbeObject(bool match = false, int jet = -1,double minR = 10000.):TRootElectron(),hasMatch(match),nJet(jet),minRJet(minR){PIndex.clear(); Mass.clear();};
        TRootTagProbeObject(const TRootElectron& e,bool match = false, int jet = -1,double minR = 10000.):TRootElectron(e),hasMatch(match),nJet(jet),minRJet(minR){PIndex.clear(); Mass.clear();};
        TRootTagProbeObject(Double_t px, Double_t py, Double_t pz, Double_t e,bool match = false, int jet = -1,double minR = 10000.):
        TRootElectron(px,py,pz,e),hasMatch(match),nJet(jet),minRJet(minR){PIndex.clear(); Mass.clear();};
        TRootTagProbeObject(Double_t px, Double_t py, Double_t pz, Double_t e, Double_t vtx_x, Double_t vtx_y,
        Double_t vtx_z,bool match = false, int jet = -1,double minR = 10000.):TRootElectron(px,py,pz,e,vtx_x,vtx_y,vtx_z),hasMatch(match)
        ,nJet(jet),minRJet(minR){PIndex.clear(); Mass.clear();};
        TRootTagProbeObject(Double_t px, Double_t py, Double_t pz, Double_t e, Double_t vtx_x, Double_t vtx_y, Double_t vtx_z,
        Int_t type, Int_t charge,bool match = false, int jet = -1,double minR = 10000.):TRootElectron(px,py,pz,e,vtx_x,vtx_y,vtx_z,type,charge),
        hasMatch(match),nJet(jet),minRJet(minR){PIndex.clear(); Mass.clear();};
        TRootTagProbeObject(const TLorentzVector &momentum,bool match = false, int jet = -1,double minR = 10000.):TRootElectron(momentum),
        hasMatch(match),nJet(jet),minRJet(minR){PIndex.clear(); Mass.clear();};
        TRootTagProbeObject(const TLorentzVector &momentum, const TVector3 &vertex, Int_t type, Float_t charge,
        bool match = false, int jet = -1,double minR = 10000.):TRootElectron(momentum,vertex,type,charge),hasMatch(match),nJet(jet),minRJet(minR){PIndex.clear(); Mass.clear();};
        virtual ~TRootTagProbeObject(){};
        std::vector<unsigned int > PIndex;
        std::vector<double > Mass;
        bool hasMatch;
        int nJet;
        double minRJet;
        ClassDef (TRootTagProbeObject,1)
    };
}


#endif	/* TROOTTAGPROBEOBJECT_H */


