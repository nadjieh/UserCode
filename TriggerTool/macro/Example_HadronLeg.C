/* 
 * File:   Example.c
 * Author: Davide Piccolo
 *
 * Created on May 24, 2013, 4:44 PM
 */

#include "../interface/HadronTriggerComponent.h"

int main() {
    cout << "start program" << endl;
    HadronTriggerComponent myhadrontrigger("CerntralJet30_BTagIP", "Nov2011AOD");
    string mytype = "data";
    string mycategory = "all";

    // One jet
    float mypt = 132.;
    float mybtag = 2.6;
    JetInfo myJet;
    myJet.jetPt = mypt;
    myJet.btag = mybtag;
    myJet.type = mytype;
    myJet.category = mycategory;

    TurnOnCurveFitPars myfitParameters = myhadrontrigger.GetFitParameters(myJet);

    cout << "a = " << myfitParameters.a << "   b = " << myfitParameters.b << "  c = " << myfitParameters.c << endl;
    cout << "  efficiency = " << myhadrontrigger.GetPerJetEfficiency(myJet) << endl;

    // All jets in event
    std::vector<JetInfo> jetsInEvent;
    jetsInEvent.push_back(myJet);
    JetInfo myJet2;
    myJet2.jetPt = 50;
    myJet2.btag = 5.1;
    myJet.type = mytype;
    myJet.category = mycategory;
    jetsInEvent.push_back(myJet2);
    double totalEff = 1;
    for (unsigned int i = 0; i < jetsInEvent.size(); i++) {
        totalEff *= myhadrontrigger.GetPerJetEfficiency(jetsInEvent[i]);
    }
    //This is the total event weight on jet part. It should be multiplied by the SF from lepton leg
}
