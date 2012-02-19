/* 
 * File:   PrimaryVertexSelector.h
 * Author: ajafari
 *
 * Created on July 21, 2010, 5:52 PM
 */

#ifndef _PrimaryVertexSelector_H
#define	_PrimaryVertexSelector_H

#include "../../../TopBrussels/TopTreeProducer/interface/TRootVertex.h"
#include <string>
#include <TMath.h>

using namespace TopTree;
class PrimaryVertexSelector{
public:
    PrimaryVertexSelector(std::string name, double zCut = 24.):Name(name),zCut_(zCut){verbosity = 0;};
    virtual ~PrimaryVertexSelector(){};
    bool isPVGood(TRootVertex pv){
        double rho = sqrt((pv.x()*pv.x())+(pv.y()*pv.y()));
	if(verbosity > 0){
	    cout<<"Rho: "<<rho<<endl;
	    cout<<"ndof: "<<fabs(pv.ndof())<<endl;
	    cout<<"z: "<<fabs(pv.z())<<endl;
	    cout<<"notFake: "<<!pv.isFake()<<endl;
	    if(fabs(pv.ndof()) >= 4. && fabs(pv.z()) < zCut_ && !pv.isFake() && rho < 2.)
		cout<<"Good PrimaryVertex :-)"<<endl;
	}
        return(fabs(pv.ndof()) >= 4. && fabs(pv.z()) < zCut_ && !pv.isFake() && rho < 2.);
    }
    void verbose(int i){verbosity = i;}
    void setPVs(std::vector<TRootVertex> pvs){
        goldenVertices.clear();
//        for(uint i=0; i<pvs.size(); i++){
//	for(uint i=0; i<1; i++){
        if(verbosity > 0)
            cout<<"+++++ Primary Vertex number 0"<<endl;
        if(isPVGood(pvs.at(0))){
            goldenVertices.push_back(pvs.at(0));
            }
//        }
    }
    int numberOfGPV(){
        return goldenVertices.size();
    }
    virtual bool EventPassedMe(){
        return(this->numberOfGPV() > 0);
    }
    std::vector<TRootVertex> GoldenVertices()const{return goldenVertices;}
private:
    std::string Name;
    std::vector<TRootVertex> goldenVertices;
    int verbosity;
    double zCut_;
};

#endif	/* _PrimaryVertexSelector_H */

