/* 
 * File:   LumiOutPutToJSON.h
 * Author: nadjieh
 *
 * Created on March 17, 2012, 10:15 PM
 */

#ifndef LUMIOUTPUTTOJSON_H
#define	LUMIOUTPUTTOJSON_H
#include <stdlib.h>
#include <algorithm>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
using namespace std;
class LumiOutPutToJSON {
public:
    LumiOutPutToJSON(int v = 0):verbosity(v){};
    LumiOutPutToJSON(const LumiOutPutToJSON& orig){};
    virtual ~LumiOutPutToJSON(){};
    void getUnprescaledJSON(std::string name, string out){
        fstream file_out(out.c_str(),ios::out);
        fstream file_op(name.c_str(),ios::in);
        int line = 0;
        char myChar[2000];
        int endPosLumi = 2;
        int endPosRun = 2;
        
        while(!file_op.eof())
        {
            line++;
            file_op.getline(myChar,2000);
            stringstream mystr(myChar);
            if(mystr.str() == "")
                break;
//            if(line == 2){
            if(line == 3){
                endPosLumi = mystr.str().find("S |")+1;
                endPosRun = mystr.str().find("n |")+1;
                continue;
            }
//            cout<<endPosLumi<<"\t"<<endPosRun<<endl;
            cout<<mystr.str().substr(2,endPosRun-2)<<mystr.str().substr(endPosRun,endPosLumi-endPosRun)<<endl;
            file_out<<mystr.str().substr(2,endPosRun-2)<<mystr.str().substr(endPosRun,endPosLumi-endPosRun)<<endl;


            
        }
        file_op.close();
        file_out.close();
    }
private:
    int verbosity;
};

#endif	/* LUMIOUTPUTTOJSON_H */

