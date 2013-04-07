/* 
 * File:   WeightHelper.h
 * Author: nadjieh
 *
 * Created on January 2, 2013, 10:42 AM
 */

#ifndef WEIGHTHELPER_H
#define	WEIGHTHELPER_H
#include "MuonTree.h"
#include "GenInfoMuonTree.h"

void GetWeights(GenInfoMuonTree* myMuonTree, double& allW, double& puOnly, double& btagPu) {//To be corrected with new weighting recipe
    double defW = myMuonTree->weight * (myMuonTree->leptonEff * 890 + myMuonTree->leptonEffB * 4428);
    puOnly = defW * myMuonTree->PUWeight;
    allW = myMuonTree->GetTotalWeightNoPU();
    allW *= myMuonTree->PUWeight;
    btagPu = allW;
}

void GetWeightsNoPu(GenInfoMuonTree* myMuonTree, double& allW, double& puOnly, double& btagPu) {//To be corrected with new weighting recipe
    puOnly = myMuonTree->weight * (myMuonTree->leptonEff * 890 + myMuonTree->leptonEffB * 4428);
    allW = myMuonTree->GetTotalWeightNoPU();
    btagPu = allW;
}

void GetWeights(MuonTree* myMuonTree, double& allW, double& puOnly, double& btagPu) {//To be corrected with new weighting recipe
    double defW = myMuonTree->weight * (myMuonTree->leptonEff * 890 + myMuonTree->leptonEffB * 4428);
    puOnly = defW * myMuonTree->PUWeight;
    allW = myMuonTree->GetTotalWeightNoPU();
    allW *= myMuonTree->PUWeight;
    btagPu = allW;
}

void GetWeightsNoPu(MuonTree* myMuonTree, double& allW, double& puOnly, double& btagPu) {//To be corrected with new weighting recipe
    puOnly = myMuonTree->weight * (myMuonTree->leptonEff * 890 + myMuonTree->leptonEffB * 4428);
    allW = myMuonTree->GetTotalWeightNoPU();
    btagPu = allW;
}

void GetWeightsSysBTag(GenInfoMuonTree* myMuonTree, double& allW, double& puOnly, double& btagPu, int btagW = 0) {//To be corrected with new weighting recipe
    GetWeights(myMuonTree, allW, puOnly, btagPu);
    if (myMuonTree->bWeight != 0) {
        allW = (allW / myMuonTree->bWeight);
        puOnly = (puOnly / myMuonTree->bWeight);
        btagPu = (btagPu / myMuonTree->bWeight);
    }
    if (btagW == 1) {
        allW *= myMuonTree->bWeightBTagUp;
        puOnly *= myMuonTree->bWeightBTagUp;
        btagPu *= myMuonTree->bWeightBTagUp;
        return;
    } else if (btagW == -1) {
        allW *= myMuonTree->bWeightBTagDown;
        puOnly *= myMuonTree->bWeightBTagDown;
        btagPu *= myMuonTree->bWeightBTagDown;
        return;
    }
    GetWeights(myMuonTree, allW, puOnly, btagPu);
}

void GetWeightsSysBTag(MuonTree* myMuonTree, double& allW, double& puOnly, double& btagPu, int btagW = 0) {//To be corrected with new weighting recipe
    GetWeights(myMuonTree, allW, puOnly, btagPu);
    if (myMuonTree->bWeight != 0) {
        allW = (allW / myMuonTree->bWeight);
        puOnly = (puOnly / myMuonTree->bWeight);
        btagPu = (btagPu / myMuonTree->bWeight);
    }
    if (btagW == 1) {
        allW *= myMuonTree->bWeightBTagUp;
        puOnly *= myMuonTree->bWeightBTagUp;
        btagPu *= myMuonTree->bWeightBTagUp;
        return;
    } else if (btagW == -1) {
        allW *= myMuonTree->bWeightBTagDown;
        puOnly *= myMuonTree->bWeightBTagDown;
        btagPu *= myMuonTree->bWeightBTagDown;
        return;
    }
    GetWeights(myMuonTree, allW, puOnly, btagPu);
}

void GetWeightsSysMisTag(GenInfoMuonTree* myMuonTree, double& allW, double& puOnly, double& btagPu, int mistagW = 0) {//To be corrected with new weighting recipe
    GetWeights(myMuonTree, allW, puOnly, btagPu);
    if (myMuonTree->bWeight != 0) {
        allW = (allW / myMuonTree->bWeight);
        puOnly = (puOnly / myMuonTree->bWeight);
        btagPu = (btagPu / myMuonTree->bWeight);
    }
    if (mistagW == 1) {
        allW *= myMuonTree->bWeightMisTagUp;
        puOnly *= myMuonTree->bWeightMisTagUp;
        btagPu *= myMuonTree->bWeightMisTagUp;
        return;
    } else if (mistagW == -1) {
        allW *= myMuonTree->bWeightMisTagDown;
        puOnly *= myMuonTree->bWeightMisTagDown;
        btagPu *= myMuonTree->bWeightMisTagDown;
        return;
    }
    GetWeights(myMuonTree, allW, puOnly, btagPu);
}

void GetWeightsSysMisTag(MuonTree* myMuonTree, double& allW, double& puOnly, double& btagPu, int mistagW = 0) {//To be corrected with new weighting recipe
    GetWeights(myMuonTree, allW, puOnly, btagPu);
    if (myMuonTree->bWeight != 0) {
        allW = (allW / myMuonTree->bWeight);
        puOnly = (puOnly / myMuonTree->bWeight);
        btagPu = (btagPu / myMuonTree->bWeight);
    }
    if (mistagW == 1) {
        allW *= myMuonTree->bWeightMisTagUp;
        puOnly *= myMuonTree->bWeightMisTagUp;
        btagPu *= myMuonTree->bWeightMisTagUp;
        return;
    } else if (mistagW == -1) {
        allW *= myMuonTree->bWeightMisTagDown;
        puOnly *= myMuonTree->bWeightMisTagDown;
        btagPu *= myMuonTree->bWeightMisTagDown;
        return;
    }
    GetWeights(myMuonTree, allW, puOnly, btagPu);
}

void GetWeightsSysPU(GenInfoMuonTree* myMuonTree, double& allW, double& puOnly, double& btagPu, int puW = 0) {//To be corrected with new weighting recipe
    GetWeights(myMuonTree, allW, puOnly, btagPu);
    if (myMuonTree->PUWeight != 0) {
        allW = (allW / myMuonTree->PUWeight);
        puOnly = (puOnly / myMuonTree->PUWeight);
        btagPu = (btagPu / myMuonTree->PUWeight);
    }
    if (puW == 1) {
        allW *= myMuonTree->PUWeightPUUp;
        puOnly *= myMuonTree->PUWeightPUUp;
        btagPu *= myMuonTree->PUWeightPUUp;
        return;
    } else if (puW == -1) {
        allW *= myMuonTree->PUWeightPUDown;
        puOnly *= myMuonTree->PUWeightPUDown;
        btagPu *= myMuonTree->PUWeightPUDown;
        return;
    }
    GetWeights(myMuonTree, allW, puOnly, btagPu);
}

void GetWeightsSysPU(MuonTree* myMuonTree, double& allW, double& puOnly, double& btagPu, int puW = 0) {//To be corrected with new weighting recipe
    GetWeights(myMuonTree, allW, puOnly, btagPu);
    if (myMuonTree->PUWeight != 0) {
        allW = (allW / myMuonTree->PUWeight);
        puOnly = (puOnly / myMuonTree->PUWeight);
        btagPu = (btagPu / myMuonTree->PUWeight);
    }
    if (puW == 1) {
        allW *= myMuonTree->PUWeightPUUp;
        puOnly *= myMuonTree->PUWeightPUUp;
        btagPu *= myMuonTree->PUWeightPUUp;
        return;
    } else if (puW == -1) {
        allW *= myMuonTree->PUWeightPUDown;
        puOnly *= myMuonTree->PUWeightPUDown;
        btagPu *= myMuonTree->PUWeightPUDown;
        return;
    }
    GetWeights(myMuonTree, allW, puOnly, btagPu);
}
void GetWeightsSysLumi(MuonTree* myMuonTree, double& allW, double& puOnly, double& btagPu, int lumi = 0) {//To be corrected with new weighting recipe
    double unc = 0.044;
    double uncLumiA = 890*(1+(unc*lumi));
    double uncLumiB = 4428*(1+(unc*lumi));
    double defW = myMuonTree->weight * (myMuonTree->leptonEff * uncLumiA + myMuonTree->leptonEffB * uncLumiB);
    puOnly = defW * myMuonTree->PUWeight;
    allW = defW*myMuonTree->bWeight*myMuonTree->PUWeight;;
    btagPu = allW;
}
void GetWeightsSysLumi(GenInfoMuonTree* myMuonTree, double& allW, double& puOnly, double& btagPu, int lumi = 0) {//To be corrected with new weighting recipe
    double unc = 0.044;
    double uncLumiA = 890*(1+(unc*lumi));
    double uncLumiB = 4428*(1+(unc*lumi));
    double defW = myMuonTree->weight * (myMuonTree->leptonEff * uncLumiA + myMuonTree->leptonEffB * uncLumiB);
    puOnly = defW * myMuonTree->PUWeight;
    allW = defW*myMuonTree->bWeight*myMuonTree->PUWeight;;
    btagPu = allW;
}
double GetPDFWeight(GenInfoMuonTree* myMuonTree, int iPar = 0) {
    double weight = 1;
    switch (iPar) {
        case 1: weight = myMuonTree->PDFWeight1;
            break;
        case 2: weight = myMuonTree->PDFWeight2;
            //            cout << "PDFWeight: " << weight << endl;
            break;
        case 3: weight = myMuonTree->PDFWeight3;
            break;
        case 4: weight = myMuonTree->PDFWeight4;
            break;
        case 5: weight = myMuonTree->PDFWeight5;
            break;
        case 6: weight = myMuonTree->PDFWeight6;
            break;
        case 7: weight = myMuonTree->PDFWeight7;
            break;
        case 8: weight = myMuonTree->PDFWeight8;
            break;
        case 9: weight = myMuonTree->PDFWeight9;
            break;
        case 10: weight = myMuonTree->PDFWeight10;
            break;
        case 11: weight = myMuonTree->PDFWeight11;
            break;
        case 12: weight = myMuonTree->PDFWeight12;
            break;
        case 13: weight = myMuonTree->PDFWeight13;
            break;
        case 14: weight = myMuonTree->PDFWeight14;
            break;
        case 15: weight = myMuonTree->PDFWeight15;
            break;
        case 16: weight = myMuonTree->PDFWeight16;
            break;
        case 17: weight = myMuonTree->PDFWeight17;
            break;
        case 18: weight = myMuonTree->PDFWeight18;
            break;
        case 19: weight = myMuonTree->PDFWeight19;
            break;
        case 20: weight = myMuonTree->PDFWeight20;
            break;
        case 21: weight = myMuonTree->PDFWeight21;
            break;
        case 22: weight = myMuonTree->PDFWeight22;
            break;
        case 23: weight = myMuonTree->PDFWeight23;
            break;
        case 24: weight = myMuonTree->PDFWeight24;
            break;
        case 25: weight = myMuonTree->PDFWeight25;
            break;
        case 26: weight = myMuonTree->PDFWeight26;
            break;
        case 27: weight = myMuonTree->PDFWeight27;
            break;
        case 28: weight = myMuonTree->PDFWeight28;
            break;
        case 29: weight = myMuonTree->PDFWeight29;
            break;
        case 30: weight = myMuonTree->PDFWeight30;
            break;
        case 31: weight = myMuonTree->PDFWeight31;
            break;
        case 32: weight = myMuonTree->PDFWeight32;
            break;
        case 33: weight = myMuonTree->PDFWeight33;
            break;
        case 34: weight = myMuonTree->PDFWeight34;
            break;
        case 35: weight = myMuonTree->PDFWeight35;
            break;
        case 36: weight = myMuonTree->PDFWeight36;
            break;
        case 37: weight = myMuonTree->PDFWeight37;
            break;
        case 38: weight = myMuonTree->PDFWeight38;
            break;
        case 39: weight = myMuonTree->PDFWeight39;
            break;
        case 40: weight = myMuonTree->PDFWeight40;
            break;
        case 41: weight = myMuonTree->PDFWeight41;
            break;
        case 42: weight = myMuonTree->PDFWeight42;
            break;
        case 43: weight = myMuonTree->PDFWeight43;
            break;
        case 44: weight = myMuonTree->PDFWeight44;
            break;
        case 45: weight = myMuonTree->PDFWeight45;
            break;
        case 46: weight = myMuonTree->PDFWeight46;
            break;
        case 47: weight = myMuonTree->PDFWeight47;
            break;
        case 48: weight = myMuonTree->PDFWeight48;
            break;
        case 49: weight = myMuonTree->PDFWeight49;
            break;
        case 50: weight = myMuonTree->PDFWeight50;
            break;
        case 51: weight = myMuonTree->PDFWeight51;
            break;
        case 52: weight = myMuonTree->PDFWeight52;
            break;
    }
    return weight;
}
#endif	/* WEIGHTHELPER_H */

