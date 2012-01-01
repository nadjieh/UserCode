/* 
 * File:   EffHandleAdder.h
 * Author: ajafari
 *
 * Created on November 5, 2009, 1:35 PM
 */

#ifndef _EFFHANDLEADDER_H
#define	_EFFHANDLEADDER_H
#include "TH1.h"
#include "TFile.h"
#include "TString.h"
#include "TDirectory.h"
#include "TList.h"
typedef std::pair<TString, std::vector<TString> > nameSubNamesAssociation;
class EffHandleAdder{
public:
    EffHandleAdder(TFile f1, TFile f2){
        input1 = f1; input2 = f2;
        mainDirNames = getMainDirNames();
        mainDirProps = getMainDirProps();
    };
    ~EffHandleAdder(){};
    
    std::vector<TString> getMainDirNames(){
        TList * mainList = input1.GetListOfKeys();
        std::vector<TString> mainDirNameVec;
        mainDirs.clear();
        for(uint i = 0; i<mainList->GetSize(); i++){
            mainDirNameVec.push_back(mainList->At(i)->GetName());
        }
        return(mainDirNameVec);
    }; //EffHandler
    std::vector<nameSubNamesAssociation> getMainDirProps(){
        std::vector<nameSubNamesAssociation> res;
        res.clear();
        std::vector<TString> propNames;
        for(uint i = 0; i< mainDirNames.size(); i++){
            TDirectory * EffHandler = (TDirectory*)input1.Get(mainDirNames.at(i));
            EffHandler->cd();
            TList * listOfProps = EffHandler->GetListOfKeys();
            propNames.clear();
            for(uint j = 0; j<listOfProps->GetSize(); j++ ){
                propNames.push_back(listOfProps->At(j)->GetName());
            }
            res.push_back(make_pair(mainDirNames.at(i), propNames));                
        }
        return(res);
    };
    void mainJob(){
        for(uint i = 0; i< mainDirProps.size(); i++){
            TDirectory * maindir1 = (TDirectory*)input1.Get(mainDirProps.at(i).first);
            TDirectory * maindir2 = (TDirectory*)input2.Get(mainDirProps.at(i).first);
            for(uint j = 0; j<mainDirProps.at(i).second.size(); j++){
                maindir1->cd();
                TDirectory * prop1 = (TDirectory*)maindir1.Get(mainDirProps.at(i).second.at(j));
                maindir2->cd();
                TDirectory * prop2 = (TDirectory*)maindir2.Get(mainDirProps.at(i).second.at(j));
            }
        }
    };
private:
    TFile input1;
    TFile input2;
    TFile output;
    std::vector<TString> mainDirNames;
    std::vector<nameSubNamesAssociation> mainDirProps;
        
    };
};

#endif	/* _EFFHANDLEADDER_H */

