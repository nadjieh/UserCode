/* 
 * File:   DataPointsChiSquared.h
 * Author: nadjieh
 *
 * Created on March 7, 2012, 12:11 PM
 */

#ifndef DATAPOINTSCHISQUARED_H
#define	DATAPOINTSCHISQUARED_H
#include "TH1.h"
#include "TGraph.h"
#include "TMath.h"
#include "TFile.h"
#include "TVectorD.h"
#include "TDirectory.h"
#include <vector>
#include <string>
#include <iostream>
using namespace std;
class DataPointsChiSquared {
public:
    DataPointsChiSquared(TH1D data, TH1D mc, std::string type = "Both", int v = 0)
                        :Data(data),MC(mc),verbosity(v){
        errors.clear();
        this->errorSetter(type);
        this->calc_chi_square();
    };
    virtual ~DataPointsChiSquared(){};
    double getChi2()const{
        return Chi2;
    };
private:
    TH1D Data;
    TH1D MC; //in my toy model, the MC could be SM or reweighetd as non-SM
    std::vector<double> errors;
    double Chi2;
    int verbosity;
    void errorSetter(std::string type){
        /* Data: only data errors are included
         * MC: only MC errors are included
         * Both: error is a comibination of both
         * NOTE: errors are all statistical
         */
        if(type == "Data" || type == "data" || type == "d" || type == "D"){
            for(int i = 0; i<Data.GetXaxis()->GetNbins(); i++)
                errors.push_back(Data.GetBinError(i+1));
        }else if(type == "MC" || type == "mc" || type == "m" || type == "M"){
            for(int i = 0; i<MC.GetXaxis()->GetNbins(); i++)
                errors.push_back(MC.GetBinError(i+1));            
        }else if(type == "Both" || type == "both" || type == "b" || type == "B"){
            for(int i = 0; i<MC.GetXaxis()->GetNbins(); i++){
                if(verbosity > 2)
                    std::cout<<"Data error: "<<Data.GetBinError(i+1)<<
                            "\tMC error: "<<MC.GetBinError(i+1)<<",\tTotal: "
                            <<sqrt(pow(MC.GetBinError(i+1),2)+pow(Data.GetBinError(i+1),2))
                            <<std::endl;
                errors.push_back(sqrt(pow(MC.GetBinError(i+1),2)+pow(Data.GetBinError(i+1),2)));
            }
        }
    }
    
    void calc_chi_square(){
        // The method taken from 
        //http://tesla.desy.de/~pcastro/example_progs/fit/minuit_c_style/fit_minuit.cxx
        //calculate chisquare
        double chisq = 0;
        for (int i=0;i<Data.GetXaxis()->GetNbins(); i++) {
            // chi square is the quadratic sum of the distance from the point 
            //to the function weighted by its error
            double delta  = (double)(Data.GetBinContent(i+1)-MC.GetBinContent(i+1))/(double)errors.at(i);
            chisq += delta*delta;
            if(verbosity > 2)
                std::cout<<"Data Value: "<<Data.GetBinContent(i+1)<<
                         "\tMC Value: "<<MC.GetBinContent(i+1)<<",\tError: "<<errors.at(i)
                         <<"\tChi2: "<<chisq<<std::endl;
        }
        Chi2 = chisq;
    };

};

class DataPointChiSquaredHandler{
public:
    DataPointChiSquaredHandler(std::string name, TH1D * data, std::vector<TH1D*> MCs,
                               TGraph* fvars, int nBins = 10, std::string type = "Both", int v = 0)
                               :Name(name),verbosity(v){
                                   cout<<"in DataPointChiSquaredHandler:\n\t"<<data<<"\t"<<MCs.at(0)
                                   <<"\t"<<fvars<<endl;
        this->rebinner(data,nBins);
        unsigned int n = MCs.size();
        cout<<"Size of MC: "<<n<<endl;
        TVectorD x_fvar(n);
        TVectorD y_chi2(n);
        
        
        for(unsigned int i = 0; i < n; i++){
            if(verbosity > 2)
                std::cout<<"RW histogram number "<<i<<std::endl;
            this->rebinner(MCs.at(i),nBins);
            DataPointsChiSquared chi2_calc(*data, *MCs.at(i),type,verbosity);
            if(verbosity > 2)
                std::cout<<"------------------- "<<i<<std::endl;
            std::cout<<"A: "<<y_chi2[i]<<std::endl;
            cout<<chi2_calc.getChi2()<<endl;
            y_chi2[i] = chi2_calc.getChi2(); 
            double tmpY;
            cout<<fvars->GetN()<<endl;
            fvars->GetPoint(i,x_fvar[i],tmpY);
            std::cout<<"B: "<<y_chi2[i]<<std::endl;
        }
        chiSquareds = new TGraph(x_fvar,y_chi2);
        chiSquareds->SetName("chiSquared_helicity");
    };
    DataPointChiSquaredHandler(std::string name, TH1D * data, std::vector<TH1D*> MCs,
                               double* fvars, int nBins = 10, std::string type = "Both", int v = 0)
                               :Name(name),verbosity(v){
                                   cout<<"in DataPointChiSquaredHandler:\n\t"<<data<<"\t"<<MCs.at(0)
                                   <<"\t"<<fvars[0]<<endl;
        this->rebinner(data,nBins);
        unsigned int n = MCs.size();
        cout<<"Size of MC: "<<n<<endl;
        TVectorD x_fvar(n);
        TVectorD y_chi2(n);
        
        
        for(unsigned int i = 0; i < n; i++){
            if(verbosity > 2)
                std::cout<<"RW histogram number "<<i<<std::endl;
            this->rebinner(MCs.at(i),nBins);
            DataPointsChiSquared chi2_calc(*data, *MCs.at(i),type,verbosity);
            if(verbosity > 2)
                std::cout<<"------------------- "<<i<<std::endl;
            std::cout<<"A: "<<y_chi2[i]<<std::endl;
            cout<<chi2_calc.getChi2()<<endl;
            y_chi2[i] = chi2_calc.getChi2(); 
            x_fvar[i] =fvars[i];
            std::cout<<"B: "<<y_chi2[i]<<std::endl;
        }
        chiSquareds = new TGraph(x_fvar,y_chi2);
        chiSquareds->SetName("chiSquared_helicity");
    };
    
    virtual ~DataPointChiSquaredHandler(){
        delete chiSquareds;
    };
    
    TGraph * getGraph()const{return chiSquareds;};
    
    void Write(TDirectory* d){
        d->mkdir(std::string(Name+"_ChiSquaredPlot").c_str())->cd();
        double * x = chiSquareds->GetX();
        double * y = chiSquareds->GetY();
        if(verbosity > 0){
            std::cout<<"The content of final chi2 graph: "<<std::endl;
            for(int i = 0; i < chiSquareds->GetN(); i++)
                std::cout<<"fVar: "<<x[i]<<",\tchi2: "<<y[i]<<std::endl;
        }
        chiSquareds->Write();
        d->cd();
    }
    
private:
    void rebinner(TH1D* histo, int nFinalBins){
        if((histo->GetXaxis()->GetNbins() % nFinalBins) == 0){
            if(verbosity > 0)
                std::cout<<"Before Rebinning: "<<histo->GetXaxis()->GetNbins()<<std::endl;
            histo->Rebin(((histo->GetXaxis()->GetNbins())/nFinalBins));
            if(verbosity > 0)
                std::cout<<"After Rebinning: "<<histo->GetXaxis()->GetNbins()<<std::endl;
        }else{
            std::cout<<nFinalBins<<" does not count "<<histo->GetXaxis()->GetNbins()<<std::endl;
            std::cout<<"I will take the biggest number less than "<<nFinalBins<<"that counts it .."<<std::endl;
            int n = 1;
            for(int i = 2; i<nFinalBins; i++){
                if((histo->GetXaxis()->GetNbins() % i) == 0)
                    n = i;
            }
            histo->Rebin(((histo->GetXaxis()->GetNbins())/n));
        }
    }
    TGraph * chiSquareds;
    std::string Name;
    int verbosity;
};

#endif	/* DATAPOINTSCHISQUARED_H */

