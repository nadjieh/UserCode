/* 
 * File:   EfficiencyHandler.h
 * Author: ajafari
 *
 * Created on January 30, 2009, 4:56 PM
 */

#ifndef _EFFICIENCYHANDLER_H
#define	_EFFICIENCYHANDLER_H

#include <vector>
#include <string>
#include <sstream>
#include "EfficiencyH1.h"
#include "EfficiencyExt.h"
#include "ObjectProperty.h"
#include "Histograms.h"

using namespace std;

template<class T>
class EfficiencyHandler {
public:

    EfficiencyHandler(string name) : Name(name),
    ExtMode(false),selfEff(false) {
        verbosity = -1;
    };

    EfficiencyHandler(const EfficiencyHandler<T>& effH, std::string suffix) : Name(effH.getName()),
    ExtMode(effH.isExtMode()),ExtInside(effH.getExtInside()),ExtfitFunc(effH.getExtfitFunc()),ExtXMin(effH.getExtXMin())
    ,ExtXMax(effH.getExtXMax()),selfEff(effH.isSelfEfficiency()) {
        allProps.clear();
        std::stringstream s;
        std::stringstream sAll;
        std::stringstream sInteg;
        for(uint i = 0; i<effH.GetProperties(); i++){
            EfficiencyH1<T> * tmp = new EfficiencyH1<T>(*effH.GetEffH1(i));
            TH1D * hall  = new TH1D(*tmp->GetHAll());
            sInteg<<tmp->getNameInteg()<<suffix;
            s<<tmp->GetName()<<suffix;
            tmp->SetNameTitle(s.str().c_str(),s.str().c_str());
            tmp->setName(s.str());
            tmp->setNameInteg(sInteg.str());
            sAll<<hall->GetName()<<suffix;
            hall->SetNameTitle(sAll.str().c_str(),sAll.str().c_str());
            tmp->setAll(hall);
            allProps.push_back(tmp);
            verbosity = -1;
        }

    };

    //If the instance is created by this constructor, all of the inner eff's use EfficiencyExt

    EfficiencyHandler(string name, ObjectProperty<T>* inside, TF1* _fitFunc, double xmin, double xmax) : Name(name),
    ExtMode(true),
    ExtInside(inside),
    ExtfitFunc(_fitFunc),
    ExtXMin(xmin),
    ExtXMax(xmax),selfEff(false) {
        
        verbosity = -1;
    };
    EfficiencyHandler(std::string name,std::vector<TH1D*> passes, std::vector<TH1D*>alls):Name(name){
      allProps.clear();
      for(unsigned int i = 0; i<passes.size(); i++){
          EfficiencyH1<T> * eff = new EfficiencyH1<T>(passes.at(i),alls.at(i),string(passes.at(i)->GetName()));
          allProps.push_back(eff);
      }
    };
    virtual ~EfficiencyHandler() {

    };

    bool (*Condition)(const T*);
    bool (*AllCondition)(const T*);
    void setVerbosity(int i){verbosity = i;cout<<"In effHandler "<<Name<<" verbosity is set to "<<verbosity<<endl;}
    void setSelfEff(){
        selfEff = true; 
    };
    void setSelfEff(bool b){
        selfEff = b;
    };
        
    EfficiencyH1<T>* AddProp(ObjectProperty<T>* prop) {
        EfficiencyH1<T>* eff;
        if (!ExtMode) {
            eff = new EfficiencyH1<T > (prop, Name);
        }else {
            eff = new EfficiencyExt<T> (prop, ExtInside, ExtfitFunc, ExtXMin, ExtXMax, Name);
        }

        if(selfEff)
            eff->setSelfEff();
        eff->setVerbosity(verbosity);
        eff->Condition = Condition;
        eff->AllCondition = AllCondition;
        allProps.push_back(eff);

        return eff;
    };
    virtual void Fill(const T* theObject, double weight = 1) {
        if(verbosity > 0)
            cout<<"In EfficiencyHandler::Fill of\n\t"<<Name<<endl;
        for (uint i = 0; i < allProps.size(); i++) {
            EfficiencyH1<T>* eff_i = allProps[i];
            eff_i->Fill(theObject, weight);
        }
    };

    virtual void WriteAll(TDirectory* dir, bool mkdir = true) {
        if (dir == 0)
            return;
//        cout<<verbosity<<endl;
        if(verbosity > 0){
            cout<<verbosity<<" In EfficiencyHandler::WriteAll of\n\t"<<Name<<endl;
        }
        TDirectory* my_dir = dir->mkdir(Name.c_str());
        my_dir->cd();
        if(verbosity > 0){
            cout<<"\tNumber of properties is "<<allProps.size()<<endl;
        }

        for (uint i = 0; i < allProps.size(); i++) {
            EfficiencyH1<T>* eff_i = allProps[i];
            eff_i->setVerbosity(verbosity);
            if(verbosity > 3){
                cout<<"\t\t\tSelfEff: "<<selfEff<<endl;
            }
            if(selfEff){
                eff_i->setSelfEff();
                if(verbosity > 3){
                    cout<<"\t\t\tSelfEff In H1: "<<eff_i->isSetSelfEff()<<endl;
                }
            }
            if(eff_i == NULL)
                cout<<"%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% NULL"<<endl;
            eff_i->WriteAll(my_dir,mkdir);
        }
        dir->cd();
    };
    virtual void add(EfficiencyHandler<T> eh2){
        for(uint i = 0; i < allProps.size(); i++){
//            EfficiencyH1<T>* eff_i = allProps[i];
//            std::cout<<i<<"======"<<std::endl;
            EfficiencyH1<T>* eff2_i = eh2.GetEffH1(i);
//            std::cout<<((TH1D*)(allProps[i]->GetHAll()))->GetName()<<endl;
            allProps[i]->add(eff2_i);
        }
    };
    virtual void multiply(EfficiencyHandler<T> eh2){
        for(uint i = 0; i < allProps.size(); i++){
//            EfficiencyH1<T>* eff_i = allProps[i];
            EfficiencyH1<T>* eff2_i = eh2.GetEffH1(i);
            allProps[i]->multiply(eff2_i);
        }
    };
    virtual void multiply(double m){
        for(uint i = 0; i < allProps.size(); i++){
            allProps[i]->multiply(m);
        }
    };
    virtual void divide(EfficiencyHandler<T> eh2){
        for(uint i = 0; i < allProps.size(); i++){
            EfficiencyH1<T>* eff2_i = eh2.GetEffH1(i);
            allProps[i]->divide(eff2_i);
        }
    };
    virtual double GetBinContentAll(int s,int i){
        if(s > allProps.size()){
            cout<<"Bad Handler request"<<endl;
            return -1000;
        }
//        cout<<"In EfficiencyHandler "<<Name<<endl;
            return allProps[s]->GetBinContentAll(i);
    };
    virtual double GetBinContentPass(int s,int i){
        if(s > allProps.size()){
            cout<<"Bad Handler request"<<endl;
            return -1000;
        }
            return allProps[s]->GetBinContentPass(i);
    };
    virtual void subtract(EfficiencyHandler<T> eh2){
        for(uint i = 0; i < allProps.size(); i++){
            EfficiencyH1<T>* eff2_i = eh2.GetEffH1(i);
            allProps[i]->subtract(eff2_i);
        }
    };
    void setName(std::string name){
        Name = name;
    };
    std::string getName()const{
        return Name;
    };
    bool isExtMode()const{
        return ExtMode;
    };
    void setExtMode(bool ext){
        ExtMode = ext;
    };
    ObjectProperty<T>* getExtInside()const{
        return ExtInside;
    };
    void setExtInside(ObjectProperty<T>* prop){
        ExtInside = new ObjectProperty<T>(*prop);
    };
    TF1 * getExtfitFunc()const{
        return ExtfitFunc;
    };
    void setExtfitFunc(TF1 * f){
        ExtfitFunc = new TF1(*f);
    };
    double getExtXMin()const{
        return ExtXMin;
    };
    void setExtXMin(double t){
        ExtXMin = t;
    };
    double getExtXMax()const{
        return ExtXMax;
    };
    void setExtXMax(double t){
        ExtXMax = t;
    };
    bool isSelfEfficiency()const{
        return selfEff;
    };
    uint GetProperties()const{return allProps.size();};
    EfficiencyH1<T>* GetEffH1(int i)const{return allProps.at(i);};
    virtual uint GetEntries()const{
        return(allProps[0]->GetHAll()->GetEntries());
    };
    virtual uint GetNbins()const{
        return(allProps[0]->GetHAll()->GetXaxis()->GetNbins());
    };

    virtual void SetEntries(double n){
        for(uint i = 0; i<allProps.size(); i++){
            allProps[i]->GetHAll()->SetEntries(n);
            allProps[i]->SetEntries(n);
        }
    };
    void setBinContent(unsigned int i, double x){
        allProps[0]->GetHAll()->SetBinContent((int)i,x);
    }
    void SetBinErrorAll(unsigned int i, double x){
        allProps[0]->GetHAll()->SetBinError((int)i,x);
    }
    void SetBinErrorPass(unsigned int i, double x){
        ((TH1D*)(allProps[0]))->SetBinError((int)i,x);
    }
    double GetBinErrorAll(unsigned int i){
        return allProps[0]->GetHAll()->GetBinError((int)i);
    }
    double GetBinErrorPass(unsigned int i){
//        return allProps[0]->GetHAll()->GetBinError((int)i);
        return (((TH1D*)(allProps[0]))->GetBinError((int)i));
    }
//    double getBinContent(unsigned int i){
//
//        return allProps[0]->GetHAll()->GetBinContent((int)i);
////        return allProps[0]->GetBinContent((int)i);
//    }
    std::string WhoAmI()const{return "EfficiencyHandler";}
protected:
    vector<EfficiencyH1<T>*> allProps;
//    vector<TH2Ext<T>* > TwoDs;
    string Name;

    bool ExtMode;
    //variables needed for ext mode
    ObjectProperty<T>* ExtInside;
    TF1* ExtfitFunc;
    double ExtXMin, ExtXMax;
    bool selfEff; // same as EfficiencyH1
    int verbosity;

};
#endif	/* _EFFICIENCYHANDLER_H */

