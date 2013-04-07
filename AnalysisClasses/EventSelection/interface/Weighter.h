/* 
 * File:   HLTweight.h
 * Author: nadjieh
 *
 * Created on June 25, 2012, 3:32 PM
 */

#ifndef WEIGHT_H
#define	WEIGHT_H
#include "TH1.h"
#include "TH2.h"
#include <iostream>
class Weighter{
public:
    Weighter(TH1D * h = 0, double sf = 1):wightHist1D(*h), SF(sf){}
    Weighter(TH2D * h = 0, double sf = 1):wightHist2D(*h), SF(sf){}
    virtual ~Weighter(){}
    virtual double getWeight(double input1 = -1000. , double input2 = -1000){
        if(input1 != -1000. && input2 == -1000.){
            int bin =  wightHist1D.GetXaxis()->FindBin(input1);
            return wightHist1D.GetBinContent(bin);
        }else if(input1 != -1000. && input2 != -1000.){
            int binX =  wightHist2D.GetXaxis()->FindBin(input1);
            int binY =  wightHist2D.GetYaxis()->FindBin(input2);
            return wightHist2D.GetBinContent(binX,binY);            
        }else if(input1 == -1000. && input2 != -1000.){
            std::cout<<"change the order of inputs! It returns 1!!"<<std::endl;
            return 1.;
        }          
        return SF;
    }
protected:
    TH1D wightHist1D;
    TH2D wightHist2D;
    double SF;
};
class HLTWeighter: public Weighter{
public:
    HLTWeighter(TH1D * h = 0, double sf = 1):Weighter(h,sf){}
    HLTWeighter(TH2D * h = 0, double sf = 1):Weighter(h,sf){}
    virtual ~HLTWeighter(){}
};
class LeptonWeighter: public Weighter{
public:
    LeptonWeighter(TH1D * h = 0, double sf = 1):Weighter(h,sf){}
    LeptonWeighter(TH2D * h = 0, double sf = 1):Weighter(h,sf){}
    virtual ~LeptonWeighter(){}
};


#endif	/* WEIGHT_H */

