/* 
 * File:   GetData.C
 * Author: ajafari
 *
 * Created on November 23, 2010, 7:39 PM
 */

#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;
using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
char str[2000];
fstream file_out("DO.sh",ios::out);
for(unsigned int i = 0; i<500; i++){
    stringstream s;
    s<<"/home/ajafari/Pseudo_100/"<<i+1<<"/doAna_"<<i+1<<".sh";
    fstream file_op(s.str().c_str(),ios::in);
    int line = 0;
    while(!file_op.eof())
    {
        line++;
    //    cout<<"===========================  "<<line<<endl;
        stringstream mystr;

          file_op.getline(str,2000);
          mystr<<str<<endl;
          if(string(str) != ""){
            file_out<<mystr.str()<<endl;
          }

    }
    file_op.close();
}
file_out.close();
cout <<endl;
    return 0;
}

