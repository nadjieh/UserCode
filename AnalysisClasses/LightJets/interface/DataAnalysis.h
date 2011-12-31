/* 
 * File:   DataAnalysis.h
 * Author: ajafari
 *
 * Created on July 9, 2010, 5:53 PM
 */

#ifndef _DATAANALYSIS_H
#define	_DATAANALYSIS_H

#include "BaseAnalysis.h"
#include "../../../AnalysisClasses/ChiSquared/interface/DataRegion.h"

#include <iostream>
using namespace std;
using namespace TopTree;
class DataAnalysis : public BaseAnalysis{
public:
    DataAnalysis(std::string anaName, double LEL, double HEL,
    double LER, double HER,double chi2cut = 100000.,double topPtcut = 0.,bool doAntiTag = false,
    double AntiTagCut = 1000.):BaseAnalysis(anaName,LEL,HEL,LER,HER,chi2cut,topPtcut){
        BaseAnalysis::R = new DataRegion(string(BaseAnalysis::Name + "_RightRegion_"),BaseAnalysis::Edges[2],
        BaseAnalysis::Edges[3],doAntiTag,AntiTagCut);
        BaseAnalysis::L = new DataRegion(string(BaseAnalysis::Name + "_LeftRegion_"),BaseAnalysis::Edges[0],
        BaseAnalysis::Edges[1],doAntiTag,AntiTagCut);
    };
    virtual ~DataAnalysis(){};
    virtual void End(std::string fName, double f =-10000){
        if (f == -10000){
            f = (DataAnalysis::LeftRegion())->F(DataAnalysis::RightRegion());
            cout<<"\n\n\n\tF control sample is "<<f<<" in DataAnalysis "<<BaseAnalysis::Name<<endl;
        }
        else
            cout<<"\n\n\n\tFmc is "<<f<<" in DataAnalysis "<<BaseAnalysis::Name<<endl;
        BaseAnalysis::End(fName,f);
        
    }
   std::string WhoAmI()const{return "DataAnalysis";};
private:
    DataRegion * RightRegion(){ return (DataRegion*)BaseAnalysis::R ; }
    DataRegion * LeftRegion(){ return (DataRegion*)BaseAnalysis::L ; }

};





#endif	/* _DATAANALYSIS_H */

