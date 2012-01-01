/* 
 * File:   EfficiencyH1.h
 * Author: ajafari
 *
 * Created on January 30, 2009, 3:40 PM
 */

#ifndef _EFFICIENCY_H
#define	_EFFICIENCY_H

#include "ObjectProperty.h"
#include "TH1Ext.h"
#include <string>
#include <TCanvas.h>
#include <TGraph.h>
#include <TGraphAsymmErrors.h>
#include "TDirectory.h"
#include <iostream>
using namespace std;

template<class T>
class EfficiencyH1 : public TH1Ext<T> {
public:

    EfficiencyH1(ObjectProperty<T>* theProp, std::string name) : TH1Ext<T>(theProp),
    Name(name) {
        hAll = theProp->GetH1(name + "_ALL");
        hAll->SetDefaultSumw2(kTRUE);
        NameInteg = name;
        std::string title = name;
        if (name != "")
            name += ("_PASSED_" + theProp->ObjectName + "_" + theProp->PropertyName);
        else
            name = theProp->ObjectName + "_" + theProp->PropertyName;

        TH1Ext<T>::SetNameTitle(name.c_str(), title.c_str());
        TH1Ext<T>::SetBins(theProp->NumberOfBins, theProp->MinValue, theProp->MaxValue);
        TH1Ext<T>::SetXTitle(theProp->PropertyTitle.c_str());

        AllCondition = 0;
//        cout << AllCondition << endl;
        selfEff = false;
        verbosity = 0;
    };
    EfficiencyH1(TH1D * pass, TH1D * all, std::string name):TH1Ext<T>(pass),Name(name),NameInteg(name){
        hAll = new TH1D(*all);
        hAll->SetDefaultSumw2(kTRUE);
        this->theProperty = 0;
};
    virtual ~EfficiencyH1() {
    };

    bool (*Condition)(const T*);
    bool (*AllCondition)(const T*);

    void setSelfEff() {
        selfEff = true;
    };
    bool isSetSelfEff()const{
        return selfEff;
    };
    void setVerbosity(int i) {
        verbosity = i;
    };

    virtual int Fill(const T* theObject, double weight = 1) {
        if(verbosity > 4)
            cout<<"In EfficiencyH1::Fill Method of "<<Name<<endl;
        if (this->theProperty == 0) {
            cout << "NULL !!!";
            throw std::exception();
        } else {
            bool allPassed = true;
            if (AllCondition != 0)
                allPassed = AllCondition(theObject);

            if(verbosity > 4 && !allPassed)
                cout<<"\t\tAllCondition is not met !"<<endl;

            if (allPassed) {
                std::vector<double> val = this->theProperty->ReadValue(theObject);
                for(unsigned int i = 0; i < val.size(); i++)
                    hAll->Fill(val.at(i), weight);
                if (Condition(theObject)){
                    if(verbosity > 4)
                        cout<<"\t\tAll and PassCondition is met ..."<<endl;
                for(unsigned int i = 0; i < val.size(); i++)
                    TH1D::Fill(val.at(i), weight);
                }
                return 1;
            }
        }
        return -10;
    };

    virtual void WriteAll(TDirectory* dir, bool mkdir = true) {
        if (dir == 0)
            return;
        TDirectory* dir2 = 0;
        if(verbosity > 3){
            cout<<"\tmkdir is "<<mkdir<<endl;
        }
        if (mkdir) {
            dir2 = dir->mkdir(this->theProperty->PropertyName.c_str());
            dir2->cd();
        } else {
            dir->cd();
        }

        hAll->Write();
        TH1Ext<T>::Write();
        if(verbosity > 1){
            cout<<"In EfficiencyH1::WriteAll Method of "<<Name<<endl;
            if(mkdir)
                cout<<"\tIn "<<dir2->GetName()<<" Directory"<<endl;
            cout<<"\t"<<hAll->GetName()<<" is written"<<endl;
            cout<<"\t"<<this->Name<<" is written"<<endl;
        }


        eff_bay = new TGraphAsymmErrors(this, hAll);
        if(verbosity > 1)
            cout<<"\tI want to create Bayesian\n\t\tProperty:"<<this->theProperty<<endl;
        if(this->theProperty != NULL){
            eff_bay->GetXaxis()->SetTitle(this->theProperty->PropertyTitle.c_str());
        }
        else{
            eff_bay->GetXaxis()->SetTitle(this->GetXaxis()->GetTitle());
        }
        string asym_name("EffBayesianAsymmErr");
        if(this->theProperty != NULL){
            asym_name = Name + "_" + asym_name + "_" + this->theProperty->PropertyName;
        }
        else{
            asym_name = Name + "_" + asym_name + "_" + string(this->GetXaxis()->GetTitle());
        }
        eff_bay->SetName(asym_name.c_str());
        eff_bay->Write();
        if(verbosity > 1)
            cout<<"\tBayesian is written"<<endl;
        TCanvas c;
        c.cd();
        eff_bay->Draw("AP");
        c.Write("Drown_Bay");

        EffPoissonErr();
        EffPoisson->Write();
        if(verbosity > 1)
            cout<<"\tPoissonian is written"<<endl;
        if(dir2 != NULL)
            (dir2->mkdir("Integrated"))->cd();
        else
            (dir->mkdir("Integrated"))->cd();
        if(this->theProperty != NULL){
            IntegratedAll = new TH1D((NameInteg + "_IntegratedAll_0I").c_str(),
            (NameInteg + "_IntegratedAll_0I").c_str(), this->theProperty->NumberOfBins,
            this->theProperty->MinValue, this->theProperty->MaxValue);
            IntegratedAll->SetDefaultSumw2(kTRUE);

            IntegratedPass = new TH1D((NameInteg + "_IntegratedPass_0I").c_str(),
            (NameInteg + "_IntegratedPass_0I").c_str(), this->theProperty->NumberOfBins,
            this->theProperty->MinValue, this->theProperty->MaxValue);
            IntegratedPass->SetDefaultSumw2(kTRUE);
        }else{
            IntegratedAll = new TH1D((NameInteg + "_IntegratedAll_0I").c_str(),
            (NameInteg + "_IntegratedAll_0I").c_str(), this->GetNbinsX(),
            this->GetXaxis()->GetXmin(), this->GetXaxis()->GetXmax());
            IntegratedAll->SetDefaultSumw2(kTRUE);
            
            IntegratedPass = new TH1D((NameInteg + "_IntegratedPass_0I").c_str(),
            (NameInteg + "_IntegratedPass_0I").c_str(), this->GetNbinsX(),
            this->GetXaxis()->GetXmin(), this->GetXaxis()->GetXmax());
            IntegratedPass->SetDefaultSumw2(kTRUE);
        }
        if(this->theProperty != NULL){
            for (int i = 0; i<this->theProperty->NumberOfBins; i++) {
                double passed = this->Integral(1, i + 1);
//                double passErr = 0;
//                for(int d = 1; d<i+2;d++){
//                    passErr += (this->GetBinError(d)*this->GetBinError(d));
//                }
//                passErr = sqrt(passErr);
                double all;
                if (selfEff) {
                    all = hAll->Integral(1, this->theProperty->NumberOfBins);
                } else
                    all = hAll->Integral(1, i + 1);
//                double allErr = 0;
//                if(selfEff){
//                    for(int d = 0; d<this->theProperty->NumberOfBins;d++){
//                        allErr += (hAll->GetBinError(d+1)*hAll->GetBinError(d+1));
//                    }
//                }else{
//                    for(int d = 1; d<i+2;d++){
//                        allErr += (hAll->GetBinError(d)*hAll->GetBinError(d));
//                    }
//                }
//                allErr = sqrt(allErr);
                IntegratedAll->SetBinContent(i + 1, all);
//                IntegratedAll->SetBinError(i + 1, allErr);//if(i == 400) cout<<"Err in poisson All: "<<allErr<<endl;
                IntegratedPass->SetBinContent(i + 1, passed);
//                IntegratedPass->SetBinError(i + 1, passErr);//if(i == 400) cout<<"Err in poisson Pass: "<<passErr<<endl;
            }
        }
        else{
            for (int i = 0; i<this->GetNbinsX(); i++) {
                double passed = this->Integral(1, i + 1);
//                double passErr = 0;
//                for(int d = 1; d<i+2;d++){
//                    passErr += (this->GetBinError(d)*this->GetBinError(d));
//                }
//                passErr = sqrt(passErr);
                double all;
                if (selfEff) {
                    all = hAll->Integral(1, this->GetNbinsX());
                    if(verbosity > 50)
                        cout<<"\tSelfEff\n\tall = "<<all<<endl;
                } else{
                    all = hAll->Integral(1, i + 1);
                    if(verbosity > 50)
                        cout<<"\tNotSelfEff\n\tall = "<<all<<endl;
                }
//                double allErr = 0;
//                if(selfEff){
//                    for(int d = 0; d<this->theProperty->NumberOfBins;d++){
//                        allErr += (hAll->GetBinError(d+1)*hAll->GetBinError(d+1));
//                    }
//                }else{
//                    for(int d = 1; d<i+2;d++){
//                        allErr += (hAll->GetBinError(d)*hAll->GetBinError(d));
//                    }
//                }
//                allErr = sqrt(allErr);
                IntegratedAll->SetBinContent(i + 1, all);
//                IntegratedAll->SetBinError(i + 1, allErr);//if(i == 400) cout<<"Err in poisson All: "<<allErr<<endl;
                IntegratedPass->SetBinContent(i + 1, passed);
//                IntegratedPass->SetBinError(i + 1, passErr);//if(i == 400) cout<<"Err in poisson All: "<<passErr<<endl;
            }
        }
        if(verbosity > 1)
            cout<<"\tIntegrateds are filled"<<endl;
        IntegratedEff_bay = new TGraphAsymmErrors(IntegratedPass, IntegratedAll);
        std::string IEname(NameInteg + "_Integrated_");
        if(this->theProperty != NULL){
            IEname += this->theProperty->PropertyName + "_0I";
        }
        else{
            IEname += string(this->GetXaxis()->GetTitle()) + "_0I";
        }
        IntegratedEff_bay->SetName(IEname.c_str());
        IntegratedEff_bay->Write();

        if(verbosity > 1)
            cout<<"\tIntegrateds are written"<<endl;


        IntegratedAll->Write();
        IntegratedPass->Write();

        IntegratedPass_0I = new TH1D(*IntegratedPass);
        IntegratedPass_0I->SetDefaultSumw2(kTRUE);
        IntegratedPass_0I->Divide(IntegratedAll);
        PoissonianErrorCalculator(IntegratedPass,IntegratedAll,IntegratedPass_0I);
        IntegratedPass_0I->SetName((IEname + "_Poisson").c_str());
        IntegratedPass_0I->Write();
        if(this->theProperty != NULL){
            IntegratedAll = new TH1D((NameInteg + "_IntegratedAll_Iinf").c_str(),
            (NameInteg + "_IntegratedAll_Iinf").c_str(), this->theProperty->NumberOfBins,
            this->theProperty->MinValue, this->theProperty->MaxValue);
            IntegratedAll->SetDefaultSumw2(kTRUE);
            IntegratedPass = new TH1D((NameInteg + "_IntegratedPass_Iinf").c_str(),
            (NameInteg + "_IntegratedPass_Iinf").c_str(), this->theProperty->NumberOfBins,
            this->theProperty->MinValue, this->theProperty->MaxValue);
            IntegratedPass->SetDefaultSumw2(kTRUE);
        }else{
            IntegratedAll = new TH1D((NameInteg + "_IntegratedAll_Iinf").c_str(),
            (NameInteg + "_IntegratedAll_Iinf").c_str(),  this->GetNbinsX(),
            this->GetXaxis()->GetXmin(), this->GetXaxis()->GetXmax());
            IntegratedAll->SetDefaultSumw2(kTRUE);
            
            IntegratedPass = new TH1D((NameInteg + "_IntegratedPass_Iinf").c_str(),
            (NameInteg + "_IntegratedPass_Iinf").c_str(),  this->GetNbinsX(),
            this->GetXaxis()->GetXmin(), this->GetXaxis()->GetXmax());
            IntegratedPass->SetDefaultSumw2(kTRUE);
        }
        if(this->theProperty != NULL){
            for (int i = 0; i<this->theProperty->NumberOfBins; i++) {
                double passed = this->Integral(i + 1, this->theProperty->NumberOfBins);
                double passErr = 0;
                for(int d = i+1; d<=this->theProperty->NumberOfBins;d++){
                    passErr += (this->GetBinError(d)*this->GetBinError(d));
                }
                passErr = sqrt(passErr);
                double all;
                //	    std::cout<<selfEff<< "Iinf again"<<std::endl;
                if (selfEff)
                    all = hAll->Integral(1, this->theProperty->NumberOfBins);
                else
                    all = hAll->Integral(i + 1, this->theProperty->NumberOfBins);
                //	    std::cout<<"Integrated all Iinf: "<<all<<std::endl;
                //	    std::cout<<"Integrated passed Iinf: "<<passed<<std::endl;
                double allErr = 0;
                if(selfEff){
                    for(int d = 0; d<this->theProperty->NumberOfBins;d++){
                        allErr += (hAll->GetBinError(d+1)*hAll->GetBinError(d+1));
                    }
                }else{
                    for(int d = i+1; d<=this->theProperty->NumberOfBins;d++){
                        allErr += (hAll->GetBinError(d)*hAll->GetBinError(d));
                    }
                }
                allErr = sqrt(allErr);
                IntegratedAll->SetBinContent(i + 1, all);
                IntegratedAll->SetBinError(i + 1, allErr);
                IntegratedPass->SetBinContent(i + 1, passed);
                IntegratedPass->SetBinError(i + 1, passErr);
            }
        }
        else{
            for (int i = 0; i<this->GetNbinsX(); i++) {
                double passed = this->Integral(i + 1, this->GetNbinsX());
                double passErr = 0;
                for(int d = i+1; d<=this->GetNbinsX();d++){
                    passErr += (this->GetBinError(d)*this->GetBinError(d));
                }
                passErr = sqrt(passErr);
                double all;
                //	    std::cout<<selfEff<< "Iinf again"<<std::endl;
                if (selfEff)
                    all = hAll->Integral(1, this->GetNbinsX());
                else
                    all = hAll->Integral(i + 1, this->GetNbinsX());
                //	    std::cout<<"Integrated all Iinf: "<<all<<std::endl;
                //	    std::cout<<"Integrated passed Iinf: "<<passed<<std::endl;
                double allErr = 0;
                if(selfEff){
                    for(int d = 0; d<this->GetNbinsX();d++){
                        allErr += (hAll->GetBinError(d+1)*hAll->GetBinError(d+1));
                    }
                }else{
                    for(int d = i+1; d<=this->GetNbinsX();d++){
                        allErr += (hAll->GetBinError(d)*hAll->GetBinError(d));
                    }
                }
                allErr = sqrt(allErr);
                IntegratedAll->SetBinContent(i + 1, all);
                IntegratedPass->SetBinContent(i + 1, passed);
                IntegratedPass->SetBinError(i + 1, passErr);
                IntegratedAll->SetBinError(i + 1, allErr);
            }
        }
        IntegratedEff_bay = new TGraphAsymmErrors(IntegratedPass, IntegratedAll);
        std::string IEname_inf(NameInteg + "_Integrated_");
        if(this->theProperty != NULL){
            IEname_inf += this->theProperty->PropertyName + "_Iinf";
        }
        else{
            IEname_inf += string(this->GetXaxis()->GetTitle()) + "_Iinf";
        }
        IntegratedEff_bay->SetName(IEname_inf.c_str());
        IntegratedEff_bay->Write();

        IntegratedAll->Write();
        IntegratedPass->Write();

        IntegratedPass_Iinf = new TH1D(*IntegratedPass);
        IntegratedPass_Iinf->SetDefaultSumw2(kTRUE);
        IntegratedPass_Iinf->Divide(IntegratedAll);
        PoissonianErrorCalculator(IntegratedPass,IntegratedAll,IntegratedPass_Iinf);
        IntegratedPass_Iinf->SetName((IEname_inf + "_Poisson").c_str());
        IntegratedPass_Iinf->Write();
        dir->cd();
    };
    void PoissonianErrorCalculator(TH1 * pass, TH1 * all, TH1 * eff){
	if(pass->GetNbinsX() != all->GetNbinsX())
            return;
	for(int i = 0; i<pass->GetNbinsX(); i++){
		double p = pass->GetBinContent(i+1);
		double a = all->GetBinContent(i+1);
                if(a != 0){
                    double err = 0;
                    double Eff = (double) p/(double)a;/*eff->GetBinContent(i+1);*///if((i+1)==401)cout<<pass->GetName()<<"\tEff in Poisson: "<<Eff<< endl;
                    double EffBar = 1 - Eff;
//                    Eff = (double) p/(double)a;
//                    err = sqrt(p * (double)(a - p) / (double)a) / (double)a;
                    double allErr = (double)all->GetBinError(i+1);//if((i+1)==401)cout<<"all->GetBinError(i+1) : "<<all->GetBinError(i+1)<<", a: "<<a<<endl;
                    double passErr = (double)pass->GetBinError(i+1);//if((i+1)==401)cout<<"pass->GetBinError(i+1) : "<<pass->GetBinError(i+1)<<", p: "<<p<<endl;
//                    err = sqrt((EffBar*EffBar*passErr*passErr)+(Eff*Eff*allErr*allErr))/(double)a;
                    err = sqrt((EffBar*EffBar*passErr*passErr)+(Eff*Eff*(allErr*allErr-passErr*passErr)))/(double)a;
//                    eff->SetBinContent(i+1, Eff);
                    eff->SetBinError(i+1, err);
                }
	}
    };
    void EffPoissonErr() {
        TH1D * tmp = new TH1D();
        string poison_name("EffPoissonErr");
        if(this->theProperty != NULL){
            poison_name = Name + "_" + poison_name + "_" + this->theProperty->PropertyName;
        }
        else{
            poison_name = Name + "_" + poison_name + "_" + string(this->GetXaxis()->GetTitle());
        }

        tmp->SetNameTitle(poison_name.c_str(), "");
        if(this->theProperty != NULL){
            tmp->SetBins(this->theProperty->NumberOfBins, this->theProperty->MinValue, this->theProperty->MaxValue);
            tmp->SetXTitle(this->theProperty->PropertyTitle.c_str());
        }else{
            tmp->SetBins(this->GetNbinsX(), this->GetXaxis()->GetXmin(), this->GetXaxis()->GetXmax());
            tmp->SetXTitle(this->GetXaxis()->GetTitle());
        }
        tmp->SetDefaultSumw2(kTRUE);
        if(this->theProperty != NULL){
            for (int i = 0; i<this->theProperty->NumberOfBins; i++) {
                double passed = this->GetBinContent(i + 1);
                double all = hAll->GetBinContent(i + 1);

                if (all != 0) {
                    double eff = 0;
                    double Err = 0;

                    eff = passed / all;
//                    Err = sqrt(passed * (double)(all - passed) /(double) all) /(double) all;
                    double allErr = hAll->GetBinError(i + 1);//if(i == 400) cout<<"Err in poisson All: "<<allErr<<endl;
                    allErr = (double)allErr/(double)all;
                    double passErr = this->GetBinError(i + 1);//if(i == 400) cout<<"Err in poisson Pass: "<<passErr<<endl;
                    passErr = (double)passErr/(double)passed;
                    Err = eff * sqrt((passErr*passErr) + (allErr*allErr));
                    tmp->SetBinContent(i + 1, eff);
                    tmp->SetBinError(i + 1, Err);
                }
            }
        }else{
                for (int i = 0; i<this->GetNbinsX(); i++) {
                double passed = this->GetBinContent(i + 1);
                double all = hAll->GetBinContent(i + 1);
//                cout<<"=====================//\n\tall in bin "<<i<<" = "<<all<<endl;
//                cout<<"=====================//\n\tpass in bin "<<i<<" = "<<passed<<endl;

                if (all != 0) {
                    double eff = 0;
                    double Err = 0;

                    eff = passed / all;
//                    Err = sqrt(passed * (double)(all - passed) /(double) all) /(double) all;
                    double allErr = hAll->GetBinError(i + 1);//if(i == 400) cout<<"this->theProperty != NULL: Err in poisson All: "<<allErr<<endl;
                    allErr = (double)allErr/(double)all;
                    double passErr = this->GetBinError(i + 1);//if(i == 400) cout<<"this->theProperty != NULL: Err in poisson Pass: "<<passErr<<endl;
                    passErr = (double)passErr/(double)passed;
                    Err = eff * sqrt((passErr*passErr) + (allErr*allErr));
                    tmp->SetBinContent(i + 1, eff);
                    tmp->SetBinError(i + 1, Err);
//                    cout<<"=====================//\n\tErr in bin "<<i<<" = "<<Err<<endl;
                }
            }
        }
        
        EffPoisson = tmp;
    };

    const TH1D* GetHAll() const {
        if (hAll == NULL)
            std::cout << "=================== All NULL" << std::endl;
        return hAll;
    };
    TH1D* GetHAll() {
        if (hAll == NULL)
            std::cout << "=================== All NULL" << std::endl;
        return hAll;
    };

    TH1D* GetPoissonianEff() {
        return EffPoisson;
    };

    TGraphAsymmErrors * GetBayesianEff() {
        return eff_bay;
    };

    virtual void add(EfficiencyH1<T> * h2) {
        if (h2 == NULL)
            std::cout << "=================== hist NULL" << std::endl;
        std::cout << "hAll: " << hAll->GetBinContent(401) << "  " << ((TH1D*) h2->GetHAll())->GetBinContent(401) << endl;
        hAll->Add((TH1D*) h2->GetHAll());
        std::cout << "hAll: " << hAll->GetBinContent(401) << "  " << ((TH1D*) h2->GetHAll())->GetBinContent(401) << endl;
        std::cout << "hPass: " << ((TH1D*)this)->GetBinContent(401) << "  " << ((TH1D*) h2)->GetBinContent(401) << endl;
        TH1D::Add((TH1D*) h2);
        std::cout << "hPass: " << ((TH1D*)this)->GetBinContent(401) << "  " << ((TH1D*) h2)->GetBinContent(401) << endl;
    };

    virtual double GetBinContentAll(int i){
//        cout<<"In EffH1-All at i = "<<i<<": "<<hAll->GetBinContent(i)<<endl;
        return hAll->GetBinContent(i) ;
    }
    virtual double GetBinContentPass(int i){
//        cout<<"In EffH1-Pass: "<<((TH1D*)this)->GetBinContent(i)<<endl;
        return ((TH1D*)this)->GetBinContent(i) ;
    }
    virtual void multiply(EfficiencyH1<T> * h2) {
        hAll->Multiply(h2->GetHAll());
        TH1D::Multiply((TH1D*) h2);
    };

    virtual void multiply(double m) {
        hAll->Scale(m);
        this->Scale(m);
    };

    virtual void divide(EfficiencyH1<T> * h2) {
        hAll->Divide(h2->GetHAll());
        TH1D::Divide((TH1D*) h2);
    };

    virtual void subtract(EfficiencyH1<T> * h2) {
        TH1D * hAll2 = (TH1D*) (h2->GetHAll());
        //        std::cout<<hAll->GetBinContent(5)<<"  "<<hAll2->GetBinContent(5)<<std::endl;
        //        std::cout<<this->GetBinContent(5)<<"  "<<((TH1D*)h2)->GetBinContent(5)<<std::endl;
        //        TH1D * resAll = new TH1D((*hAll) - (*hAll2));
        (*hAll) - (*hAll2);
        (*this) - (*h2);
        //        std::cout<<hAll->GetBinContent(5)<<"  "<<hAll2->GetBinContent(5)<<std::endl;
        //        std::cout<<this->GetBinContent(5)<<"  "<<((TH1D*)h2)->GetBinContent(5)<<std::endl;
        //        std::cout<<resAll->GetBinContent(5)<<"  "<<hAll2->GetBinContent(5)<<std::endl;
        //        hAll = resAll;
        //        this = resPass;
        //        hAll->Divide(h2->GetHAll());
        //        TH1D::Divide((TH1D*)h2);
    };

    void setAll(TH1D * h) {
        hAll = h;
    };

    void setName(std::string name) {
        Name = name;
    };

    std::string getNameInteg()const {
        return NameInteg;
    };

    void setNameInteg(std::string nameInteg) {
        NameInteg = nameInteg;
    };
protected:
    TH1D* hAll;
    TH1D* EffPoisson;
    TH1D* IntegratedPass_0I;
    TH1D* IntegratedPass_Iinf;
    TH1D* IntegratedAll;
    TH1D* IntegratedPass;
    //
    TGraphAsymmErrors *IntegratedEff_bay;
    TGraphAsymmErrors *eff_bay;
    std::string Name;
    std::string NameInteg;
    bool selfEff; // if you claculate the efficiency of variable I and want to hava it as a function of variable J, selfEff is false. if I is same as J, 
    // selfEff should be changed to true. selfEff is used only in integrated part of the efficiency calculation.
    int verbosity;
};

#endif	/* _EfficiencyH1HANDLER_H */

