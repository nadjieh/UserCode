/* 
 * File:   MCAnalysis.h
 * Author: ajafari
 *
 * Created on July 9, 2010, 2:28 PM
 */

#ifndef _MCANALYSIS_H
#define	_MCANALYSIS_H

#include "BaseAnalysis.h"
#include "../../../AnalysisClasses/ChiSquared/interface/MCRegion.h"
#include <iostream>
using namespace std;
using namespace TopTree;
class MCAnalysis : public BaseAnalysis{
public:
    MCAnalysis(std::string anaName,double LEL, double HEL,double LER, double HER,double chi2cut = 100000.,
    double topPtcut = 0., bool extJetOk_ = true):
    BaseAnalysis(anaName,LEL,HEL,LER,HER,chi2cut,topPtcut){
        BaseAnalysis::R = new MCRegion(string(BaseAnalysis::Name + "_RightRegion_"),BaseAnalysis::Edges[2],BaseAnalysis::Edges[3],extJetOk_);
        BaseAnalysis::L = new MCRegion(string(BaseAnalysis::Name + "_LeftRegion_"),BaseAnalysis::Edges[0],BaseAnalysis::Edges[1],extJetOk_);
    };
    MCAnalysis(std::string anaName,std::vector<double> args,double chi2cut = 100000.,
    double topPtcut = 0., bool extJetOk_ = true):
    BaseAnalysis(anaName,args.at(0),args.at(1),args.at(2),args.at(3),chi2cut,topPtcut){
        BaseAnalysis::R = new MCRegion(string(BaseAnalysis::Name + "_RightRegion_"),BaseAnalysis::Edges[2],BaseAnalysis::Edges[3],extJetOk_,false);
        BaseAnalysis::L = new MCRegion(string(BaseAnalysis::Name + "_LeftRegion_"),BaseAnalysis::Edges[0],BaseAnalysis::Edges[1],extJetOk_,false);
    };
    virtual ~MCAnalysis(){};

    virtual void End(std::string fName, double f = -10000){
        if(f == -10000){
            f = (MCAnalysis::LeftRegion())->F(MCAnalysis::RightRegion());
            cout<<"\n\n\n\tFmc is "<<f<<" in MCAnalysis "<<BaseAnalysis::Name<<endl;
        }
        else
            cout<<"\n\n\n\tF control sample is "<<f<<" in MCAnalysis "<<BaseAnalysis::Name<<endl;
        BaseAnalysis::End(fName,f);
        
    }
    std::string WhoAmI()const{return "MCAnalysis";};
    void TruthValueCalculator(){
        for(int i = 0; i<6; i++){
            errors[i] = -100.;
            effs[i] = -100.;
            if(i<3)
                bins[i] = -100.;
        }
        JetSpecificEfficiencyHandler * tmp = this->LeftRegion()->getHandler(0);
        if(verbosity == -10)
            cout<<"\tName of bTruth:\n\t"<<tmp->getName()<<endl;
        if (tmp == NULL){
            cout<<"SEGMENTATION VIOLATION!!!!"<<endl;
            return;
        }
        TH1D * btag = (TH1D*)tmp->GetEffH1(0);
        if (btag == NULL){
            cout<<"BTAG: SEGMENTATION VIOLATION!!!!"<<endl;
            return;
        }
        double all = btag->Integral();
        if(all == 0)
            return;
        for(int nbins = 0; nbins < btag->GetNbinsX(); nbins++){
            double pass = btag->Integral(nbins + 1,btag->GetNbinsX());
            if(pass > all)
                continue;
            double eff = ((double)pass/(double)all);
            double err = sqrt(pass * (double)(all - pass) / (double)all) / (double)all;

            if(fabs(eff - 0.25) < 0.01){
                effs[0] = eff;
                errors[0] = err;
                bins[0] = nbins;
            } else if(fabs(eff - 0.50) < 0.01){
                effs[2] = eff;
                errors[2] = err;
                bins[1] = nbins;
            } else if(fabs(eff - 0.75) < 0.01){
                effs[4] = eff;
                errors[4] = err;
                bins[2] = nbins;
            }
        }
    }
    void MethodValueCalculator(){
        JetSpecificEfficiencyHandler * tmp = new JetSpecificEfficiencyHandler(*this->LeftRegion()->getHandler(3));
        if(verbosity == -10)
            cout<<"\tName of bTruth:\n\t"<<tmp->getName()<<endl;
        if (tmp == NULL){
            cout<<"SEGMENTATION VIOLATION!!!!"<<endl;
            return;
        }
        TH1D * btag = (TH1D*)tmp->GetEffH1(0);
        if (btag == NULL){
            cout<<"BTAG: SEGMENTATION VIOLATION!!!!"<<endl;
            return;
        }
        double all = btag->Integral();
        if(all == 0)
            return;
        
        double pass = btag->Integral(bins[0] + 1,btag->GetNbinsX());
        if(pass <= all){
            effs[1] = ((double)pass/(double)all);
            errors[1] = sqrt(pass * (double)(all - pass) / (double)all) / (double)all;
        }

        pass = btag->Integral(bins[1] + 1,btag->GetNbinsX());
        if(pass <= all){
            effs[3] = ((double)pass/(double)all);
            errors[3] = sqrt(pass * (double)(all - pass) / (double)all) / (double)all;
        }

        pass = btag->Integral(bins[2] + 1,btag->GetNbinsX());
        if(pass <= all){
            effs[5] = ((double)pass/(double)all);
            errors[5] = sqrt(pass * (double)(all - pass) / (double)all) / (double)all;
        }      
    }
    double Value(int id){
        if(verbosity == -10)
            cout<<"\t\tFor id = "<<id<<", eff is "<<effs[id]<<endl;
        return effs[id];
    }
    double Error(int id){
        if(verbosity == -10)
            cout<<"\t\tFor id = "<<id<<", error is "<<errors[id]<<endl;
        return errors[id];
    }
    std::string GetVariableName(int id){
        if(id == 0 )
            return "Eff_Truth_25";
        if(id == 1 )
            return "Eff_Method_25";
        if(id == 2 )
            return "Eff_Truth_50";
        if(id == 3 )
            return "Eff_Method_50";
        if(id == 4 )
            return "Eff_Truth_75";
        if(id == 5 )
            return "Eff_Method_75";
        return "-1";
    }
    double NVariables(){
        return 6;
    }
    double errors[6];
    double effs[6];
    double bins[3];
private:
    MCRegion * RightRegion(){ return (MCRegion*)BaseAnalysis::R ; }
    MCRegion * LeftRegion(){ return (MCRegion*)BaseAnalysis::L ; }


};

#endif	/* _MCANALYSIS_H */

