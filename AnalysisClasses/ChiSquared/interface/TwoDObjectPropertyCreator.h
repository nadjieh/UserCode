/* 
 * File:   TwoDObjectPropertyCreator.h
 * Author: ajafari
 *
 * Created on September 28, 2010, 3:40 PM
 */

#ifndef _TWODOBJECTPROPERTYCREATOR_H
#define	_TWODOBJECTPROPERTYCREATOR_H
#include "PurChiSquaredHandler.h"
#include "EffChiSquaredHandler.h"
#include "BaseAnalysisHandler.h"
#include "TH1.h"
template <class T>
class TwoDObjectPropertyCreator{
public:
    TwoDObjectPropertyCreator<T>(std::string name,std::vector<ObjectProperty<T> *> properties):Name(name){
        hists.clear();
        props.clear();
        mixtureIndex.clear();
        for(unsigned int i = 0; i < properties.size(); i++){
            props.push_back(properties.at(i));
            std::string nameY = properties.at(i)->PropertyName;
            double Ymin = properties.at(i)->MinValue;
            double Ymax = properties.at(i)->MaxValue;
            int Ybin = properties.at(i)->NumberOfBins;
            TH2D * h = 0;
            for(unsigned int j = i + 1; j < properties.size(); j++){
                std::string name = std::string(nameY+"_"+properties.at(j)->PropertyName);
                double Xmin = properties.at(j)->MinValue;
                double Xmax = properties.at(j)->MaxValue;
                int Xbin = properties.at(j)->NumberOfBins;
                h = new TH2D(name.c_str(),name.c_str(),Xbin,Xmin,Xmax,Ybin,Ymin,Ymax);
                h->GetXaxis()->SetTitle(std::string(properties.at(j)->PropertyName).c_str());
                h->GetYaxis()->SetTitle(nameY.c_str());
                hists.push_back(h);
                mixtureIndex.push_back(make_pair(i,j));
            }
        }

    };
    virtual ~TwoDObjectPropertyCreator<T>(){};
    void Fill(const T * obj, double weight = 1.){
        for(unsigned int i = 0; i < hists.size(); i++){
            double x = (props.at(mixtureIndex.at(i).second)->ReadValue(obj)).at(0);
            double y = (props.at(mixtureIndex.at(i).first)->ReadValue(obj)).at(0);
            hists.at(i)->Fill(x,y,weight);
        }
    }
    void Write(TDirectory * dir){
        (dir->mkdir(string(Name+"_2Ds").c_str()))->cd();
        for(unsigned int i = 0; i < hists.size(); i++){
            hists.at(i)->Write();
        }
        dir->cd();
    }
private:
    std::string Name;
    std::vector<ObjectProperty<T> * > props;
    std::vector<TH2*> hists;
    std::vector<std::pair<unsigned  int , unsigned int> > mixtureIndex;
};

#endif	/* _TWODOBJECTPROPERTYCREATOR_H */

