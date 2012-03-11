/* 
 * File:   TemplateFitArrayCreator.h
 * Author: nadjieh
 *
 * Created on March 10, 2012, 12:41 PM
 */

#ifndef TEMPLATEFITARRAYCREATOR_H
#define	TEMPLATEFITARRAYCREATOR_H
#include "TH1.h"
#include "TF1.h"
#include <string>
class TemplateFitArrayCreator {
public:
    TemplateFitArrayCreator(std::string name , const char* myF):Name(name) {
        TF1 * f = new TF1(std::string(Name+"_F").c_str(),myF,-1,1);
        h = new TH1D(std::string(Name+"_h").c_str(),std::string(Name+"_h").c_str(),50,-1,1);
        h->Sumw2();
        h->FillRandom(std::string(Name+"_F").c_str(),10000);
        h->Scale(1./h->Integral());
        delete f;

    };
    virtual ~TemplateFitArrayCreator(){delete h;};
    TH1D * GetHistogram(){return h;};
private:
    std::string Name;
    TH1D * h;
};

#endif	/* TEMPLATEFITARRAYCREATOR_H */

