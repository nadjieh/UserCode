/* 
 * File:   DR.h
 * Author: ajafari
 *
 * Created on December 15, 2009, 1:49 PM
 */

#ifndef _DR_H
#define	_DR_H

#include <TLorentzVector.h>
#include <TMath.h>
#include <iostream>
template <class T>
class DR{
public:
    DR(T v1,T v2):V1(v1),V2(v2){};
    double getValue(){
        double delEta = V1.Eta() - V2.Eta();
        double delPhi = fabs(V1.Phi() - V2.Phi());
        if(delPhi > M_PI)
            delPhi = 2 * M_PI - delPhi;
//        std::cout<<"dphi = "<<delPhi<<" and deta = "<<delEta<<std::endl;
        return sqrt(delPhi * delPhi + delEta * delEta);
    };
    ~DR(){};
private:
    T V1;
    T V2;
};
#endif	/* _DR_H */

