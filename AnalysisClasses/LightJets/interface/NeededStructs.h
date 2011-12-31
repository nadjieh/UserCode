/* 
 * File:   NeededStructs.h
 * Author: ajafari
 *
 * Created on October 18, 2010, 1:34 PM
 */

#ifndef NEEDEDSTRUCTS_H
#define	NEEDEDSTRUCTS_H

struct ElectronCuts{
    double Pt;
    double eta;
    double ExLow;
    double ExHigh;
    std::string Id;
    std::string IdSecond;
    std::string IsoType;
    double D0;
    double IsoCut;
};
struct JetCuts{
    std::string bTagAlgo;
    double Pt;
    double eta;
    int nCaloTower;
    double EmfUp;
    double EmfLow;
    double fhpd;
    int N90;
    double bTagCut;
};
struct MassAndResolution{
    double topMass;
    double topRes;
    double wMass;
    double wRes;
};


#endif	/* NEEDEDSTRUCTS_H */

