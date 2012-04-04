/* 
 * File:   PrescaledTest.C
 * Author: nadjieh
 *
 * Created on March 11, 2012, 5:09 PM
 */

#include "../interface/PrescaledHLTFinder.h"
#include "../interface/LumiOutPutToJSON.h"
#include <iostream>

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    LumiOutPutToJSON ltj(0);
//    ltj.getUnprescaledJSON("unPrescaled/aug_unPresLumi.txt","unPrescaled/aug_unPresLumi.json");
//    ltj.getUnprescaledJSON("unPrescaled/may_unPresLumi.txt","unPrescaled/may_unPresLumi.json");
    ltj.getUnprescaledJSON("unPrescaled/prv4_unPresLumi.txt","unPrescaled/prv4_unPresLumi.json");
//    ltj.getUnprescaledJSON("unPrescaled/prv6_unPresLumi.txt","unPrescaled/prv6_unPresLumi.json");

//    PrescaledHLTFinder myPSfinder(0);
//    myPSfinder.readHLTScaleInfo("all2011.txt","HLT_IsoMu17_eta2p1_CentralJet30_BTagIP_v*");
//    cout<<myPSfinder.getPrescaleInfo().size()<<endl;
//    for(int i = 0; i<myPSfinder.getPrescaleInfo().size(); i++){
//        for(int j = 0; j<myPSfinder.getPrescaleInfo().at(i).second.size(); j++){
//        cout<<j+1<<"- RunId: "<<myPSfinder.getPrescaleInfo().at(i).first<<
//              ",   LumiId: "<<myPSfinder.getPrescaleInfo().at(i).second.at(j).first<<
//              ",   prescale factor: "<<myPSfinder.getPrescaleInfo().at(i).second.at(j).second<<endl;
//        }
//    }
//    myPSfinder.writePrescaleJSON();
    return 0;
}

