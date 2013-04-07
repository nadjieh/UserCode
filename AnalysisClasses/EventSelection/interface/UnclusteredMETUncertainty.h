/* 
 * File:   UnclusteredMETUncertainty.h
 * Author: nadjieh
 *
 * Created on August 6, 2012, 6:03 PM
 */

#ifndef UNCLUSTEREDMETUNCERTAINTY_H
#define	UNCLUSTEREDMETUNCERTAINTY_H
#include "PracticalEvent.h"
#include <vector>
#include "TLorentzVector.h"
#include "../../../TopBrussels/TopTreeProducer/interface/TRootPFMET.h"
using namespace TopTree;
class UnclusteredEnergyUnc {
public:

    UnclusteredEnergyUnc(PracticalEvent * pracEvt, double uncValue = 1) : UncValue(uncValue) {
        jets.SetPxPyPzE(0, 0, 0, 0);
        leptons.SetPxPyPzE(0, 0, 0, 0);
        met.SetPxPyPzE(0, 0, 0, 0);
        std::vector<TRootPFJet> unCorrJets = pracEvt->unCorrectedPFJetCollection(false);
        for (unsigned int i = 0; i < unCorrJets.size(); i++) {
            jets += unCorrJets[i];
        }
        for (int i = 0; i < pracEvt->MuonCollection()->GetEntriesFast(); i++) {
            leptons += (*((TLorentzVector*) pracEvt->MuonCollection()->At(i)));
        }
        for (int i = 0; i < pracEvt->ElectronCollection()->GetEntriesFast(); i++) {
            leptons += (*((TLorentzVector*) pracEvt->ElectronCollection()->At(i)));
        }
        met = *((TRootPFMET*)pracEvt->METCollection()->At(0));
    }

    ~UnclusteredEnergyUnc() {
    }

    TLorentzVector getChangedUncEnergyMET(int systematics) {
        TLorentzVector diff = met - jets - leptons;
        if (systematics == 1)
            diff += (diff * UncValue);
        else if (systematics == -1)
            diff -= (diff * UncValue);
        return (diff + jets + leptons);
    }
private:
    TLorentzVector jets;
    TLorentzVector leptons;
    TLorentzVector met;
    double UncValue;
};


#endif	/* UNCLUSTEREDMETUNCERTAINTY_H */

