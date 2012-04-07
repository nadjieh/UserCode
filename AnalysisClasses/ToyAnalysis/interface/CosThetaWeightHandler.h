/* 
 * File:   CosThetaWeightHandler.h
 * Author: nadjieh
 *
 * Created on March 6, 2012, 12:53 PM
 */

#ifndef COSTHETAWEIGHTHANDLER_H
#define	COSTHETAWEIGHTHANDLER_H
#include "CosThetaWeighter.h"
#include "TH1.h"
#include "TFile.h"
#include "TGraph.h"
#include <vector>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;
class CosThetaWeightHandler{
public:
    CosThetaWeightHandler(double f0SM, double fminusSM, bool f0Fixed, bool fminusFixed, int n = 100)
    :nStep(n){
        name = "";
        verbosity = 0;
        weights.clear();
        if(f0Fixed && !fminusFixed){
            this->setWeightHistograms(f0SM,fminusSM,true);
        }else if(!f0Fixed && fminusFixed){
            this->setWeightHistograms(fminusSM,f0SM,false);            
        }
        /* for both not fixed, I have to think more*/   
    }
    CosThetaWeightHandler(std::pair<std::vector<TH1D*>,TGraph* > Weights){
        name = "";
        weights.clear();
        fvarValuesG = (TGraph*)Weights.second;
        for(unsigned int i = 0; i<Weights.first.size(); i++){
            if(Weights.first.at(i) == NULL){
                cout<<"No weights!!!!!  "<<Weights.first.size()<<endl;
                break;
            }
            if(string(((TH1D*)Weights.first.at(i))->GetName()) == "fvarValues"){
                fvarValues = ((TH1D*)Weights.first.at(i));
            }else{
                weights.push_back((TH1D*)Weights.first.at(i));
            }
        }
    }
    ~CosThetaWeightHandler(){
        TFile * f = new TFile(string("weightsInfo_"+name).c_str(),"recreate");
        f->cd();
        fvarValues->Write();
        fvarValuesG->Write();
        for(unsigned int i = 0; i < weights.size(); i++){
            weights.at(i)->Write();
        }
        f->Write();
        f->Close();
        for(unsigned int i = 0; i < weights.size(); i++){
            delete weights.at(i);
        }   
        delete fvarValues;
        delete fvarValuesG;
        weights.clear();
    }
    double getCosThetaWeight(double cosTheta, int step){
        return (weights.at(step)->GetBinContent(weights.at(step)->FindBin(cosTheta)));
    }
    void setVerbosity(int v){verbosity = v;}
    
    /*
     * access weight Info out of the final root file
     */
    TH1D * getVariatingFractionHist()const{return fvarValues;}
    TGraph * getVariatingFractionGraph()const{return fvarValuesG;}
    void setName(string Name){name =  string(Name);}
    
private:
    
    /*
     * find boundaries of the variating helicity fraction with the constraint of a fixed fraction and 
     * the sum of all fractions equals to one.
     */
    std::pair<double, double> findBoundaries(double f1SM/*is fixed*/, double f2SM/*varies*/){
        if(verbosity > 0)
            std::cout<<"In boundaries: "<<"\nFixed is "<<f1SM<<"\tvariable is "
                 <<f2SM<<"f3 is "<<1-f1SM-f2SM<<std::endl;
        double f3SM = 1-f1SM-f2SM;
        double upperBound = f2SM + f3SM;
        double lowerBound = f2SM - f3SM;
        if(verbosity > 0)
            std::cout<<"upper bound: "<<upperBound<<"\tlower bound: "<<lowerBound<<std::endl;
        if(lowerBound < 0)
            lowerBound = 0;
        return std::make_pair(lowerBound,upperBound);
    }
    
    /*
     * claculate the size of the steps based on number of steps and the fvar variation interval
     */
    double stepSize(std::pair<double,double> boundaries){
        return ((double)(boundaries.second - boundaries.first)/(double)nStep);
    }
    /*
     * main method: produces cosTheta weights for each fvar value
     */
    void setWeightHistograms(double f1/*is fixed*/, double f2/*varies*/, bool Default){
        double StepSize;
        std::pair<double,double> boundaries ;
        if(Default)
            boundaries = this->findBoundaries(f1,f2);
        else
            boundaries = this->findBoundaries(f2,f1);
        StepSize = this->stepSize(boundaries);
        double fvar = boundaries.first;
        if(verbosity > 0)
            std::cout<<boundaries.first<<"\t"<<boundaries.second<<"\t"<<nStep<<std::endl;
        /*this histogram and the double* are to store the fvar values for future uses*/
        fvarValues = new TH1D("fvarValues","fvarValues",nStep,boundaries.first,boundaries.second);
        double x[nStep];
        double y[nStep];
        
        for(int i = 0; i<= nStep ; i++){
            std::stringstream s;
            s<<"_"<<i;
            if(verbosity > 1)
                std::cout<<fvar<<"\tweight: "<<(double)(i+1)<<"\tstep size: "<<StepSize<<std::endl;
            fvarValues->Fill(fvar,(double)(i+1));
            x[i] = fvar;
            y[i] = (double)(i+1);
//            fvarValues->Fill(fvar);
            if(Default){
                CosThetaWeighter tmpWeighter(f1, f2, f1, fvar,std::string("weight"+s.str()));
                weights.push_back(new TH1D(*tmpWeighter.getWeightHistogram()));
            }
            else{
                CosThetaWeighter tmpWeighter(f1, f2, fvar, f2,std::string("weight"+s.str()));
                weights.push_back(new TH1D(*tmpWeighter.getWeightHistogram()));
            }
            fvar += StepSize;
        }
        fvarValuesG = new TGraph(nStep+1,x,y);
        fvarValuesG->SetName("fvarValuesG");
    }
    string name;
    int nStep;// default: 100
    std::vector<TH1D*> weights;
    TH1D * fvarValues;
    TGraph * fvarValuesG;
    int verbosity;
    
    
};

#endif	/* COSTHETAWEIGHTHANDLER_H */

