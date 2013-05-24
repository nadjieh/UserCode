/* 
 * File:   Example.c
 * Author: Nadjieh
 *
 * Created on May 24, 2013, 4:44 PM
 */

#include "../interface/LeptonTriggerComponent.h"
#include <iostream>
using namespace std;
int main()
{
  cout << "start program" << endl;
  LeptonTriggerComponent myleptonpart("IsoMu17", "pt", "Nov2011AOD");
  cout<<"data efficiency:"<<myleptonpart.GetDataEfficiency(30.);
  cout<<"\tMC efficiency:"<<myleptonpart.GetMCEfficiency(30.);
  cout<<"\tScale Factor:"<<myleptonpart.GetLeptonTriggerSF(30.)<<endl;

}
