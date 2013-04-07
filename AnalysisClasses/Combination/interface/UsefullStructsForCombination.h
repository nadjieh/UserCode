/* 
 * File:   UsefullStructsForCombination.h
 * Author: nadjieh
 *
 * Created on January 9, 2013, 11:16 AM
 */

#ifndef USEFULLSTRUCTSFORCOMBINATION_H
#define	USEFULLSTRUCTSFORCOMBINATION_H
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
using namespace std;

struct InputForCombination1D {
    string name;
    TH1* nonRWs;
    TH1* data;
    TH1* signalID;
};

struct InputForCombination2D {
    string name;
    TH1* nonRWs;
    TH1* data;
    std::vector<TH2*> signalIID;
};

struct InputForCombination3D {
    string name;
    TH1* nonRWs;
    TH1* data;
    std::vector<TH2*> signalIID;
    std::vector<TH3*> signalIIID;
};

struct WTempForCombination1D {
    InputForCombination1D rest;
    TH1* Wtemplate;
};

struct WTempForCombination2D {
    InputForCombination2D rest;
    TH1* Wtemplate;
};

struct WTempForCombination3D {
    InputForCombination3D rest;
    TH1* Wtemplate;
};

#endif	/* USEFULLSTRUCTSFORCOMBINATION_H */

