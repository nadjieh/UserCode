/* 
 * File:   IObjectProperty.h
 * Author: hbakhshi
 *
 * Created on December 2, 2008, 11:23 AM
 */

#ifndef _IOBJECTPROPERTY_H
#define	_IOBJECTPROPERTY_H

#include <string>
#include <TH1.h>
#include <TH2.h>
#include "TH1Ext.h"
#include "TH2Ext.h"
#include "PropertyOperatorResult.h"
#include "UnaryOperators.h"

using namespace std;

template<class T>
class ObjectProperty {
public:

    ObjectProperty(string PN, string PT, double min, double max, int NBins, string ON, int ID) : ObjectName(ON),
    PropertyID(ID),
    PropertyName(PN),
    PropertyTitle(PT),
    MinValue(min),
    MaxValue(max),
    NumberOfBins(NBins) {
    };

    ObjectProperty(string PN, string PT,/* double * x,*/ int NBins, string ON, int ID) : ObjectName(ON),
    PropertyID(ID),
    PropertyName(PN),
    PropertyTitle(PT),
   // BinsLowEdge(x),
    NumberOfBins(NBins) {
        MinValue = 10000.;
        MaxValue = -1.;
    };

    virtual ~ObjectProperty() {
    };
    void SetBinsLowEdge(std::vector<double> x){
        for(unsigned int s = 0; s<x.size(); s++)
            this->BinsLowEdge.push_back(x.at(s));
    }
    string ObjectName;
    int PropertyID;
    string PropertyName;
    string PropertyTitle;
    double MinValue;
    double MaxValue;
    std:: vector<double> BinsLowEdge;
    int NumberOfBins;
//    virtual double ReadValue(const T*) const = 0;
    virtual std::vector<double> ReadValue(const T*) const = 0;
    

    virtual TH1Ext<T>* GetH1(string name, string title = "");

    TH2Ext<T>* GetH2(ObjectProperty<T>* otherProperty, string name , string title = "");

    template<class OtherProperty>
    TH2Ext<T>* GetH2(string name , string title = "");

    //Operators
    ObjectProperty<T>* operator + (const ObjectProperty<T>* ObjToAdd){
        return (new PropertyOperatorResult<T>(this , ObjToAdd , PropertyOperatorResult<T>::Plus));
    };

    ObjectProperty<T>* operator - (const ObjectProperty<T>* ObjToAdd){
        return (new PropertyOperatorResult<T>(this , ObjToAdd , PropertyOperatorResult<T>::Minus));
    };

    ObjectProperty<T>* operator * (const ObjectProperty<T>* ObjToAdd){
        return (new PropertyOperatorResult<T>(this , ObjToAdd , PropertyOperatorResult<T>::Multiply));
    };

    ObjectProperty<T>* operator / (const ObjectProperty<T>* ObjToAdd){
        return (new PropertyOperatorResult<T>(this , ObjToAdd , PropertyOperatorResult<T>::Divide));
    };

    ObjectProperty<T>* operator + (double ObjToAdd){
        return (new PropertyOperatorResult<T>(this , ObjToAdd , PropertyOperatorResult<T>::Plus));
    };

    ObjectProperty<T>* operator - (double ObjToAdd){
        return (new PropertyOperatorResult<T>(this , ObjToAdd , PropertyOperatorResult<T>::Minus));
    };

    ObjectProperty<T>* operator * (double ObjToAdd){
        return (new PropertyOperatorResult<T>(this , ObjToAdd , PropertyOperatorResult<T>::Multiply));
    };

    ObjectProperty<T>* operator / (double ObjToAdd){
        return (new PropertyOperatorResult<T>(this , ObjToAdd , PropertyOperatorResult<T>::Divide));
    };
};

template<class T>
TH1Ext<T>* ObjectProperty<T>::GetH1(string name , string title) {
    if(title == "")
        title = name;
    if (name != ""){
        name += ("_" + this->ObjectName + "_" + this->PropertyName);
//        title += (" (" + this->ObjectName + "," + this->PropertyName + ")" );
    }
    else{
        name = this->ObjectName + "_" + this->PropertyName;
//        title = (" (" + this->ObjectName + "," + this->PropertyName + ")" );
    }

    TH1Ext<T>* ret = new TH1Ext<T > (this);

    ret->SetNameTitle(name.c_str(), title.c_str());
    if(MinValue <= MaxValue)
        ret->SetBins(this->NumberOfBins, this->MinValue, this->MaxValue);
    else{
        double x[this->BinsLowEdge.size()];
        for(unsigned int i = 0; i<this->BinsLowEdge.size(); i++){
            x[i] = this->BinsLowEdge.at(i);
        }
        ret->SetBins(this->NumberOfBins, x);
    }
    ret->SetXTitle(this->PropertyTitle.c_str());

    return ret;
}

template<class T>
TH2Ext<T>* ObjectProperty<T>::GetH2(ObjectProperty<T>* otherProperty,string name ,string title){
    if(title == "")
        title = name;

    if (name != "")
        name += ("_" +otherProperty->PropertyName + "vs"+ ObjectName + "_" + PropertyName );
    else
        name = otherProperty->PropertyName + "vs" +  ObjectName + "_" + PropertyName;

    TH2Ext<T>* ret = new TH2Ext<T > (this, otherProperty);
    ret->SetNameTitle(name.c_str(), title.c_str());
    ret->SetBins(NumberOfBins, MinValue, MaxValue, otherProperty->NumberOfBins, otherProperty->MinValue, otherProperty->MaxValue);

    ret->SetXTitle(PropertyTitle.c_str());
    ret->SetYTitle(otherProperty->PropertyTitle.c_str());

    return ret;
}

template<class T>
template<class OtherProperty>
TH2Ext<T>* ObjectProperty<T>::GetH2(string name , string title) {
    ObjectProperty<T> otherProperty = new OtherProperty();
    return GetH2(otherProperty , name , title);
}

#endif	/* _IOBJECTPROPERTY_H */

