
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;
using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    for (int j = 1; j < 53; j++) {
        char str[2000];
        stringstream outname;
        outname << "run_" << j << ".sh";
        fstream file_out(outname.str().c_str(), ios::out);
        cout << outname.str() << endl;

        fstream file_op("PUUP/run.sh", ios::in);
        int line = 0;
        while (!file_op.eof()) {
            line++;
            if (line > 16)
                break;
            stringstream mystr;
            file_op.getline(str, 2000);
            //            cout << string(str) << endl;
            int pos1 = string(str).find("pileup");
            //            cout << pos1 << endl;
            string firstPart = string(str).substr(0, pos1);
            //            cout << firstPart << endl;
            string secondPart = string(str).substr(pos1 + 8, string(str).size() - pos1 - 8);
            //            cout << secondPart << endl;
            mystr << firstPart << " dopdf " << j << " " << secondPart;
            //            cout << mystr.str() << endl;
            if (string(str) != "") {
                //                cout<<"putting in file"<<endl;
                file_out << mystr.str() << endl;
            }
            //            cout<<"I have put --- line: "<<line<<endl;
        }
        //        cout << "file is finished" << endl;
        file_op.close();
        file_out.close();
        cout << endl;
    }
    return 0;
}
