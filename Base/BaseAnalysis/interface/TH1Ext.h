/* 
 * File:   TH1Ext.h
 * Author: hbakhshi
 *
 * Created on December 2, 2008, 1:10 PM
 */

#ifndef _TH1EXT_H
#define	_TH1EXT_H

#include <TH1.h>
#include "ObjectProperty.h"
#include <string>
#include <iostream>

using namespace std;

template<class T>
class ObjectProperty;

template<class T, class Base = TH1D>
class TH1Ext : public Base {
public:

    TH1Ext(const ObjectProperty<T>* theProp) : TH1D() {
        theProperty = theProp;
        Base::SetDefaultSumw2(kTRUE);
    };
    TH1Ext(const ObjectProperty<T>* theProp, int nbins, double * xbins ) : TH1D((theProp->PropertyName).c_str(),(theProp->PropertyTitle).c_str(),nbins,xbins) {
        theProperty = theProp;
        Base::SetDefaultSumw2(kTRUE);
    };
    TH1Ext(TH1D * input):TH1D(*input){Base::SetDefaultSumw2(kTRUE);};
    virtual int Fill(const T* theObject, double weight = 1) {
        if (theProperty == 0) {
            cout << "NULL !!!";
            throw std::exception();
        } else {
            std::vector<double> val = theProperty->ReadValue(theObject);
            for(unsigned int i = 0; i<val.size(); i++)
                Base::Fill(val.at(i), weight);
            return 1;
        }
    };

    string GetPropertyName() {
        return theProperty->PropertyName;
    };

    string GetPropertyObjectName() {
        return theProperty->ObjectName;
    };

    string GetPropertyTitle() {
        return theProperty->PropertyTitle;
    };

    int GetPropertyID() {
        return theProperty->PropertyID;
    };

    bool IsIt(int propID) {
        return GetPropertyID() == propID;
    };

    double MaxPropVal(){
        return theProperty->MaxValue;
    };

    double MinPropVal(){
        return theProperty->MinValue;
    };
    ObjectProperty<T>* getProperty()const{
        return theProperty;
    };
    void setPropertyName(std::string pname) {
        theProperty->PropertyName = pname;
    };

    void setPropertyObjectName(std::string oname) {
        theProperty->ObjectName = oname;
    };

    void setPropertyTitle(std::string ptitle) {
        theProperty->PropertyTitle = ptitle;
    };

    void setPropertyID(int id) {
        theProperty->PropertyID = id;
    };

//    bool IsIt(int propID) {
//        return GetPropertyID() == propID;
//    };
//
//    double MaxPropVal(){
//        return theProperty->MaxValue;
//    };
//
//    double MinPropVal(){
//        return theProperty->MinValue;
//    };
protected:
    const ObjectProperty<T>* theProperty;
//private:
//    std::vector<ObjectProperty<T>* > allProperties;
};

#endif	/* _TH1EXT_H */

