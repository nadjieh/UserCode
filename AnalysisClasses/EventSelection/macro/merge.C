#include "TTree.h"
#include "TDirectory.h"
#include "TClass.h"
#include "TFile.h"
#include "TList.h"
#include "TROOT.h"
#include "TKey.h"
#include "TSystem.h"
#include "TH1.h"
#include <string>
#include <iostream>
using namespace std;
int sn;
void CopyDir(TDirectory *source) {
   //copy all objects and subdirs of directory source as a subdir of the current directory   
//   source->ls();
   cout<<source->ClassName()<<endl;

   TDirectory *savdir = gDirectory;
   
   TDirectory *adir = 0;
   TFile * a = TFile::Open("a.root");   
   bool isFile = (source->ClassName() == a->ClassName());
   delete a;
   if(isFile){
//	cout<<"I am TFile"<<endl;
	savdir->cd();
   }
   else{
       adir = savdir->mkdir(source->GetName());
       adir->cd();
   }
   //loop on all entries of this directory
   TKey *key;
   TIter nextkey(source->GetListOfKeys());
   int time =0;
   while ((key = (TKey*)nextkey())) {
      const char *classname = key->GetClassName();
      TClass *cl = gROOT->GetClass(classname);
      if (!cl) continue;
      if (cl->InheritsFrom(TDirectory::Class())) {
//	 continue;
//	 cout<<sn<<"   "<<key->GetName()<<endl;
	 if(sn > 0 && (string(key->GetName()) == "before_Jet_selection_Jet"  ||   string(key->GetName()) == "before_BJet_selection_Jet")){
	     cout<<"I have found before_Jet_selection_Jet"<<endl;
	     continue;
	 }
         source->cd(key->GetName());
         TDirectory *subdir = gDirectory;
	 if(isFile)
             savdir->cd();
         else
             adir->cd();
         CopyDir(subdir);
         if(isFile)
             savdir->cd();
         else
             adir->cd();
      } else if (cl->InheritsFrom(TTree::Class())) {
         TTree *T = (TTree*)source->Get(key->GetName());
         if(isFile)
             savdir->cd();
         else
             adir->cd();

         TTree *newT = T->CloneTree(-1,"fast");
         newT->Write();
      } else {
//	if(time > 0)
//	   continue;
         source->cd();
//	 if(string(key->GetName())== "CutFlow")
//		continue;
	 /*TH1D * h = (TH1D*)source->Get(key->GetName());
	 if(string(key->GetName())== "CutFlow" /*&& h->GetBinContent(2) == 0){
	      cout<<"\t"<<h->GetName()<<endl;
	      for(int op = 0; op<h->GetNbinsX(); op++)
		    cout<<h->GetBinContent(op)<<endl;
              //continue;

         }*/
         TObject *obj = key->ReadObj();
         if(isFile)
             savdir->cd();
         else
             adir->cd();
         obj->Write();
         delete obj;
//	time++;
     }
  }
  if(isFile)
    savdir->SaveSelf(kTRUE);
  else
    adir->SaveSelf(kTRUE);
  savdir->cd();
}
void CopyFile(const char *fname) {
   //Copy all objects and subdirs of file fname as a subdir of the current directory
   TDirectory *target = gDirectory;
   TFile *f = TFile::Open(fname);
   if (!f || f->IsZombie()) {
      printf("Cannot copy file: %s\n",fname);
      target->cd();
      return;
   }
   target->cd();
   CopyDir(f);
   delete f;
   target->cd();
} 
void doJob(std::string fname,std::string f1Name, std::string f2Name){
//   TFile * f1 = TFile::Open(f1Name.c_str());
//   TFile * f2 = TFile::Open(f2Name.c_str());
   TFile * target = new TFile(fname.c_str(),"recreate");
   target->cd();
   sn =0;
   CopyFile(f1Name.c_str());
   target->cd();
   sn++;
   CopyFile(f2Name.c_str());
   target->cd();
   target->Write();
   target->Close();
}




