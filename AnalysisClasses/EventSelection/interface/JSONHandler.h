/* 
 * File:   JSONHandler.h
 * Author: nadjieh
 *
 * Created on March 11, 2012, 11:34 AM
 */

#ifndef JSONHANDLER_H
#define	JSONHANDLER_H
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include "../../../TopBrussels/TopTreeProducer/interface/TRootEvent.h"

using namespace std;
using namespace TopTree;
class JSONHandler {
public:
    JSONHandler(int v = 0):verbosity(v){};
    JSONHandler(const JSONHandler& orig){};
    virtual ~JSONHandler(){};
    
    void readJSON(string JSONname){
        if(verbosity > 0)
            cout<<"JSON file is "<<JSONname<<endl;
        string inputJSON;
        ifstream myfile (JSONname.c_str());
        if (myfile.is_open())
        {
            getline (myfile,inputJSON); // Only the first line is needed
            myfile.close();
        }

        vector<string> splittedInputJSON;
        size_t begin = 2, end = 2;

        while(end < inputJSON.size())
        {
            end = inputJSON.find("]], \"",begin);
            string splitted = inputJSON.substr(begin, end - begin + 1);
            begin = end + 5;

            size_t tempEnd = splitted.find("\": [[", 0);
            string runNr = splitted.substr(0, tempEnd);
            stringstream ss(runNr);
            int runNumber = 0;
            ss >> runNumber;

            string remain = splitted.substr(tempEnd + 4, splitted.size() - ( tempEnd + 3 ) );
            size_t tempEnd2 = remain.find("]", 0);
            size_t tempBegin2 = 0;

            while(tempEnd2 < remain.size())
            {
                string lumiInfo = remain.substr(tempBegin2 + 1, tempEnd2 - tempBegin2 - 1);
                tempBegin2 = tempEnd2 + 3;
                tempEnd2 = remain.find("]", tempBegin2);

                // parse lumiInfo string
                size_t tempBegin3 = lumiInfo.find(", ",0);
                string minLS = lumiInfo.substr(0,tempBegin3);
                string maxLS = lumiInfo.substr(tempBegin3 + 2, lumiInfo.size());
                int minLumiSection = 0;
                int maxLumiSection = 0;
                stringstream ssMin(minLS);		
                stringstream ssMax(maxLS);
                ssMin >> minLumiSection;
                ssMax >> maxLumiSection;

                vector<int> tempInfo;
                tempInfo.push_back(runNumber);
                tempInfo.push_back(minLumiSection);
                tempInfo.push_back(maxLumiSection);
                runLumiInfo.push_back(tempInfo);
            }
        }
        if(verbosity > 0)
            cout<<"Info size is "<<runLumiInfo.size()<<endl;
    }
    
    bool isSelectedByJSON(TRootEvent * event){

        bool goodEvent = false;
        if(verbosity > 0)
            cout<<"EventRunID: "<<event->runId() <<",\tEventLumiBlockID: "<<event->lumiBlockId()<<endl;
        for(unsigned int k=0; k<runLumiInfo.size(); k++)
        {
                if(event->runId() == runLumiInfo[k][0] && event->lumiBlockId() >= runLumiInfo[k][1] && event->lumiBlockId() <= runLumiInfo[k][2]){
                    if(verbosity > 0)
                        cout<<runLumiInfo[k][0]<<"\t"<<runLumiInfo[k][1]<<"\t"<<runLumiInfo[k][2]<<endl;
                    goodEvent = true;
                    break;
                }
        }

        return goodEvent;
    }
private:
    vector< vector<int> > runLumiInfo;
    int verbosity;

};

#endif	/* JSONHANDLER_H */

