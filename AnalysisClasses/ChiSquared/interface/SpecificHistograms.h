/* 
 * File:   SpecificHistograms.h
 * Author: ajafari
 *
 * Created on July 27, 2010, 6:43 PM
 */

#ifndef _SPECIFICHISTOGRAMS_H
#define	_SPECIFICHISTOGRAMS_H
#include "/user/ajafari/CMSSW_3_8_5_patch3/src/Base/BaseAnalysis/interface/Histograms.h"
#include "/user/ajafari/CMSSW_3_8_5_patch3/src/TopBrussels/TopTreeProducer/interface/TRootCaloJet.h"
#include "/user/ajafari/CMSSW_3_8_5_patch3/src/TopBrussels/TopTreeProducer/interface/TRootJet.h"
#include "/user/ajafari/CMSSW_3_8_5_patch3/src/AnalysisClasses/ChiSquared/interface/MyObjectProperties.h"
#include "TH2.h"
#include "TDirectory.h"
#include <string>
using namespace TopTree;
class SpecificHistograms: public Histograms<ExtendedJet>{
public:
    SpecificHistograms(std::string name):Histograms<ExtendedJet>(name){
        Histograms<ExtendedJet>::AddHisto2(new Eta(), new TBtag());
        Histograms<ExtendedJet>::AddHisto2(new Eta(), new Pt());
        Histograms<ExtendedJet>::AddHisto2(new Pt(), new TBtag());
    };
    virtual ~SpecificHistograms(){};
};

#endif	/* _SPECIFICHISTOGRAMS_H */

