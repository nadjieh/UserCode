/* 
 * File:   MultiplicableEffHandler.h
 * Author: ajafari
 *
 * Created on October 13, 2009, 3:25 PM
 */

#ifndef _MULTIPLICABLEEFFHANDLER_H
#define	_MULTIPLICABLEEFFHANDLER_H


#include <vector>
#include <string>
#include "EfficiencyH1.h"
#include "EfficiencyExt.h"
#include "ObjectProperty.h"
#include "TGraphAsymmErrors.h"

using namespace std;

template<class T>
class MultiplicableEffHandler {
public:

    MultiplicableEffHandler(string name) : Name(name),
    ExtMode(false) {
            selfPure = false;
            selfEff = false;
    };

    //If the instance is created by this constructor, all of the inner eff's use EfficiencyExt

    MultiplicableEffHandler(string name, ObjectProperty<T>* inside, TF1* _fitFunc, double xmin, double xmax) : Name(name),
    ExtMode(true),
    ExtInside(inside),
    ExtfitFunc(_fitFunc),
    ExtXMin(xmin),
    ExtXMax(xmax) {
            selfPure = false;
            selfEff = false;
    };

    ~MultiplicableEffHandler() {

    };

    bool (*EffCondition)(const T*); //for efficiency
    bool (*AllEffCondition)(const T*); //for efficiency
    bool (*PureCondition)(const T*); //for purity
    bool (*AllPureCondition)(const T*); //for purity
    void setEffSelf(){selfEff = true;};
    void setPureSelf(){selfPure = true;};
    void AddProp(ObjectProperty<T>* prop) {
        
        EfficiencyH1<T>* eff;
        EfficiencyH1<T>* pure;
        std::string effName = "Eff_"+Name;
        std::string pureName = "Pure_"+Name;
        if (!ExtMode) {
            eff = new EfficiencyH1<T > (prop, effName);
            pure = new EfficiencyH1<T > (prop, pureName);
        }else {
            eff = new EfficiencyExt<T> (prop, ExtInside, ExtfitFunc, ExtXMin, ExtXMax, effName);
            pure = new EfficiencyExt<T> (prop, ExtInside, ExtfitFunc, ExtXMin, ExtXMax, pureName);
        }

        eff->Condition = EffCondition;
        eff->AllCondition = AllEffCondition;
        if(selfEff)
            eff->setSelfEff();
        pure->Condition = PureCondition;
        pure->AllCondition = AllPureCondition;
        if(selfPure)
            pure->setSelfEff();
        std::pair<EfficiencyH1<T>*,EfficiencyH1<T>* > EffPurePair;
        EffPurePair.first = eff;
        EffPurePair.second = pure;
        allProps.push_back(EffPurePair);
    };
    void setInteg(string which){whichInteg = which;};
    void Fill(const T* theObject, double weight = 1) {
        for (unsigned int i = 0; i < allProps.size(); i++) {
            EfficiencyH1<T>* eff_i = allProps[i].first;
            EfficiencyH1<T>* pure_i = allProps[i].second;

            eff_i->Fill(theObject, weight);
            pure_i->Fill(theObject, weight);
        }
    };

    void WriteAll(TDirectory* dir) {
        if (dir == 0)
            return;
//        std::cout<<"========= "<<Name<<std::endl;
        TDirectory* my_dir = dir->mkdir(Name.c_str());
        my_dir->cd();
        TDirectory * purity = my_dir->mkdir("Purity");
        TDirectory * efficiency = my_dir->mkdir("Efficiency");
        for (unsigned int i = 0; i < allProps.size(); i++) {
            EfficiencyH1<T>* eff_i = allProps[i].first;
            EfficiencyH1<T>* pure_i = allProps[i].second;
            purity->cd();
            pure_i->WriteAll(purity);
            efficiency->cd();
            eff_i->WriteAll(efficiency);
            TH1D * eff_hist = eff_i->GetPoissonianEff();
            const TH1D * pure_hist = pure_i->GetPoissonianEff();
            eff_hist->SetNameTitle("multiply","multiply");
            eff_hist->Multiply(pure_hist);
            TH1D eff_hist_I = eff_i->GetIntegratedPass(whichInteg);
            TH1D pure_hist_I = pure_i->GetIntegratedPass(whichInteg);
            pure_hist_I.SetNameTitle("multiply_Integ","multiply_Integ");
            pure_hist_I.Multiply(&eff_hist_I);
//            my_dir->cd();
            eff_hist->Write();
            pure_hist_I.Write();
        }

        dir->cd();
    };
    unsigned int GetProperties(){return allProps.size();};
    EfficiencyH1<T>* GetEffH1(int i){return allProps.at(i);};
private:
    vector<std::pair<EfficiencyH1<T>*,EfficiencyH1<T>* > > allProps;
    string Name;
    string whichInteg;
    bool ExtMode;
    bool selfPure;
    bool selfEff;
    //variables needed for ext mode
    ObjectProperty<T>* ExtInside;
    TF1* ExtfitFunc;
    double ExtXMin, ExtXMax;
};


#endif	/* _MULTIPLICABLEEFFHANDLER_H */

