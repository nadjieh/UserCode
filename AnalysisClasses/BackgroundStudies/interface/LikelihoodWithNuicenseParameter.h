/* 
 * File:   LikelihoodWithNuicenseParameter.h
 * Author: nadjieh
 *
 * Created on June 9, 2012, 7:39 PM
 */

#ifndef LIKELIHOODWITHNUICENSEPARAMETER_H
#define	LIKELIHOODWITHNUICENSEPARAMETER_H

class LikelihoodWithNuicenseParameter {
public:
    LikelihoodWithNuicenseParameter(string name , TH1* Signal , TH1* Data , TH1* Bkg):
    signal(Signal),data(Data){
        
    };
    LikelihoodWithNuicenseParameter(const LikelihoodWithNuicenseParameter& orig);
    virtual ~LikelihoodWithNuicenseParameter();
private:
    TH1* signal;
    TH1* data;
    TH1* bkg;

};

#endif	/* LIKELIHOODWITHNUICENSEPARAMETER_H */

