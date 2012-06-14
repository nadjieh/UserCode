/* 
 * File:   PrescaledHLTFinder.h
 * Author: nadjieh
 *
 * Created on March 11, 2012, 4:27 PM
 */

#ifndef PRESCALEDHLTFINDER_H
#define	PRESCALEDHLTFINDER_H
#include <stdlib.h>
#include <algorithm>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
using namespace std;
struct mySortRunID{
    bool operator() (pair<int, vector<pair<int,int> >  > comb1, pair<int, vector<pair<int,int> > > comb2) { return (comb1.first < comb2.first);}
} SortByRunID;
struct mySortLumiID{
    bool operator() (pair<int,int>  comb1, pair<int,int>  comb2) { return (comb1.first < comb2.first);}
} SortByLumiID;
class PrescaledHLTFinder {
public:
    PrescaledHLTFinder(int v = 0):verbosity(v){};
    virtual ~PrescaledHLTFinder(){};
    
    void readHLTScaleInfo(std::string infoFileName, std::string desiredPath){
        fstream file_op(infoFileName.c_str(),ios::in);
        int line = 0;
        char myChar[2000];
        std::string BaseRun("");
        while(!file_op.eof())
        {
            line++;
            if(verbosity > 0){
                cout<<"line number "<<line<<":";
                cout<<"---------------------------------------------------------------"<<endl;
            }
            file_op.getline(myChar,2000);
            stringstream mystr(myChar);
            if(mystr.str().size() == 0)
                break;
            if(verbosity > 0)
                cout<<mystr.str()<<endl;
            string run  = mystr.str().substr(0,mystr.str().find(","));
            if(BaseRun == string("")){
                BaseRun = run;
            }
            if(verbosity > 0)
                cout<<"run number in line "<<line<<" is "<<run<<" and baseRun is "<<BaseRun<<endl;
            string tmp  = mystr.str().substr(mystr.str().find(",")+1,mystr.str().size());
            string lumi = tmp.substr(0,tmp.find(","));
            if(verbosity > 0)
                cout<<"lumi number in line "<<line<<" is "<<lumi<<endl;
            string HLT = tmp.substr(tmp.find(",")+1,tmp.size());
            HLT = HLT.substr(1,HLT.size()-2);
            if(verbosity > 2){
                cout<<"HLTinfo in line "<<line<<" is "<<HLT<<endl;
                cout<<"The first place of ; in line "<<line<<" is "<<HLT.find(";")<<endl;
            }
            while (HLT.find(";") > 0 && HLT.find(";") < HLT.size()){
                string pathName_prescale = HLT.substr(0,HLT.find(";"));
                string pathName = pathName_prescale.substr(0,pathName_prescale.find(","));
                string prescale = pathName_prescale.substr(pathName_prescale.find(",")+1,
                                  pathName_prescale.size());
                if(verbosity > 0)
                    cout<<"info block: "<<pathName_prescale<<",  pathName: "<<pathName
                        <<",  prescale: "<<prescale<<endl;
                //for version checks
                std::string subHltName = desiredPath.substr(0,desiredPath.find("*"));  
                std::string subIpath = pathName.substr(0,desiredPath.find("*"));     
                    
                if(verbosity > 2)
                    cout<<"info block in case of *, pathName: "<<subHltName<<endl;

//                if(atoi(prescale.c_str()) != 1 && string(subHltName) == string(subIpath)){
                if(atoi(prescale.c_str()) > 1 && string(subHltName) == string(subIpath)){
                    if(verbosity > 0)
                        cout<<"HLT is prescaled ....  "<<subHltName<<endl;
                    
                    runId_lumiId_preScale[atoi(run.c_str())][atoi(lumi.c_str())] = atoi(prescale.c_str());
                }
                HLT = HLT.substr(HLT.find(";")+1,HLT.size());
            }
        }
        
        file_op.close();

    }

    std::map<int, std::map<int,int> > getPrescaleInfo()const
    {return runId_lumiId_preScale;}
    
    void writePrescaleJSON(string outName = ""){
        stringstream mystream;
        mystream<<"{";
        for(std::map<int, std::map<int,int> >::const_iterator run_lumi_itr = runId_lumiId_preScale.begin()
                ; run_lumi_itr != runId_lumiId_preScale.end() ; run_lumi_itr++){
            mystream<<"\""<< run_lumi_itr->first <<"\": [["<<
                    run_lumi_itr->second.begin()->first<<", "<<
                    run_lumi_itr->second.rbegin()->first;
            
            std::map<int, std::map<int,int> >::const_iterator itr_tmp(runId_lumiId_preScale.end());
            itr_tmp--;
            if(run_lumi_itr == itr_tmp )
                    mystream<<"]]";
            else
                    mystream<<"]], ";
        }
        mystream<<"}";
        cout<<mystream.str()<<endl;
    }
//    void checkMissingLS(int runID){
//        for(int i = 0; i<runId_lumiId_preScale.size(); i++){
//            if(runId_lumiId_preScale.at(i).first == runID){
//                int delta = - runId_lumiId_preScale.at(i).second.at(0).first
//                            + runId_lumiId_preScale.at(i).second.at(runId_lumiId_preScale.at(i).second.size()-1).first;
//                if (delta != runId_lumiId_preScale.at(i).second.size())
//                    cout<<"Some lumis are missing in run "<<runID<<endl;
//            }
//        }
//    }
    
private:
    std::map<int, std::map<int,int> > runId_lumiId_preScale;
    int verbosity;
};

#endif	/* PRESCALEDHLTFINDER_H */

