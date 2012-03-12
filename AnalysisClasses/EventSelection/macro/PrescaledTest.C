/* 
 * File:   PrescaledTest.C
 * Author: nadjieh
 *
 * Created on March 11, 2012, 5:09 PM
 */

#include "../interface/PrescaledHLTFinder.h"
#include <iostream>

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {

    PrescaledHLTFinder myPSfinder(0);
    myPSfinder.readHLTScaleInfo("pr.txt","HLT_IsoMu17_v*");
    cout<<myPSfinder.getPrescaleInfo().size()<<endl;
//    for(int i = 0; i<myPSfinder.getPrescaleInfo().size(); i++){
//        for(int j = 0; j<myPSfinder.getPrescaleInfo().at(i).second.size(); j++){
//        cout<<j+1<<"- RunId: "<<myPSfinder.getPrescaleInfo().at(i).first<<
//              ",   LumiId: "<<myPSfinder.getPrescaleInfo().at(i).second.at(j).first<<
//              ",   prescale factor: "<<myPSfinder.getPrescaleInfo().at(i).second.at(j).second<<endl;
//        }
//    }
    myPSfinder.writePrescaleJSON();
    return 0;
}

