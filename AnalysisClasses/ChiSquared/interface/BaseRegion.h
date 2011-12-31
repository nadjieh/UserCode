/* 
 * File:   BaseRegion.h
 * Author: ajafari
 *
 * Created on July 7, 2010, 3:55 PM
 */

#ifndef _BASEREGION_H
#define	_BASEREGION_H
#include "SpecificEffHandler.h"
#include "SpecificHistograms.h"
#include <vector>
#include <iostream>
#include <string>
using namespace std;
using namespace TopTree;

#include <exception>

class RegionConflictException : public std::exception {
public:
    string MESSAGE;

    RegionConflictException(string message)throw() : std::exception(),
    MESSAGE(message) {};

    virtual ~RegionConflictException() throw(){};
    virtual const char* what() const throw () {
        return string( "REGION CONFLICT : " + MESSAGE).c_str();
    };
};

class BaseRegion {
public:

    BaseRegion(std::string name, double LE, double HE) : Name(name), LowEdge(LE), HighEdge(HE) {
        Handlers.clear();
        verbosity = 0;
    };

    virtual ~BaseRegion() {
    };
    void setVerbosity(int i){verbosity = i;cout<<"In region "<<Name<<" verbosity is set to "<<verbosity<<endl;}
    void AddHandler(JetSpecificEfficiencyHandler * Handler) {
        Handlers.push_back(Handler);
        if(verbosity > 0){
            cout<<"Handler "<<Handler->getName()<<" is added ... "<<endl;
            cout<<"Handlers size is "<<Handlers.size()<<endl;
        }
    };

    void WriteAll(TDirectory * dir) {
        if (dir == 0)
            return;
        //        std::cout<<"========= "<<Name<<std::endl;
        if(verbosity > 0)
            cout<<"Writing in "<<dir->GetName()<<" ..."<<endl;
        TDirectory* my_dir = dir->mkdir(Name.c_str());
        my_dir->cd();
        if(verbosity > 0)
            cout<<"Writing in inner directory of "<<my_dir->GetName()<<" ..."<<endl;
        for (uint i = 0; i < Handlers.size(); i++) {
            if(verbosity > 0)
                cout<<i<<"'th Handler: "<<Handlers.at(i)->getName()<<endl;
            Handlers.at(i)->WriteAll(my_dir);
            if(verbosity > 0)
                cout<<"Information of "<< Handlers.at(i)->getName()<<" has been written in \n\t"<<
                        dir->GetName()<<"\n\t"<<my_dir->GetName()<<" ...\n"<<endl;
        }

        dir->cd();
    };
    
    bool isInRegion(double Mlb) {
        if(verbosity > 0){
            cout<<"In check range method of region of "<<this->Name<<"\t"<<this->WhoAmI()<<endl;
            cout<<"\t"<<LowEdge<<" < "<<Mlb<<" < "<<HighEdge<<" : "
                    <<(bool)(fabs(Mlb) > LowEdge && fabs(Mlb) < HighEdge)<<endl;
        }
        return (fabs(Mlb) > LowEdge && fabs(Mlb) < HighEdge);
    }

    std::string getName()const {
        return Name;
    };

    void setName(std::string name_) {
        Name = name_;
    };

    uint numberOfHandlers()const {
        return Handlers.size();
    };
    void setVrbosityOfHandlers(int v){
        for(uint i = 0; i<Handlers.size();i++){
            Handlers.at(i)->setVerbosity(v);
        }
    }

    JetSpecificEfficiencyHandler * getHandler(uint i)const {
        if(verbosity > 0)
            cout<<"The "<<i<<"'th handler in this region is "<<Handlers.at(i)->getName()<<endl;
        return Handlers.at(i);
    };
//    SpecificHistograms * getHisto2D(uint i)const {
//        return Histos2D.at(i);
//    };

    virtual std::string WhoAmI()const = 0;
    virtual void Fill(TopEvent JE, double weight) =0;
    double F(BaseRegion * right) {
        if(verbosity > 0)
            cout<<"F Calculation ..."<<endl;
        JetSpecificEfficiencyHandler * rightLight = right->getHandler(1);
        if(verbosity > 0)
            cout<<"Current RightHandler is "<<rightLight->getName()<<endl;
        JetSpecificEfficiencyHandler * leftLight = BaseRegion::getHandler(1);
        if(verbosity > 0)
            cout<<"Current LeftHandler is "<<leftLight->getName()<<endl;
        TH1D * rightHist = rightLight->GetEffH1(0)->GetHAll();
        TH1D * leftHist = leftLight->GetEffH1(0)->GetHAll();
        if(verbosity > 0)
            cout<<"To Calculate F, I got \n\t"<<rightHist->GetName()<<" from right and"
                    <<"\n\t"<<leftHist->GetName()<<" from left ..."<<endl;
        double right_ = rightHist->Integral();
        double left_ = leftHist->Integral();
        if(verbosity > 0)
            cout<<"\tLeft Integral is "<<left_<<" and Right Integral is "<<right_
                    <<"\n\tF = "<<(double) left_ / (double) right_<<endl;

        return ((double) left_ / (double) right_);
    };
    virtual void Subtract(BaseRegion * right, double f = -10000) {
        //if(verbosity > 0)
            cout<<"In subtraction method ..."<<endl;
        if (this->HighEdge > right->LowEdge)
            throw new RegionConflictException("RIGHT LE IS LESS THAN LEFT HE");
        //if(verbosity > 0)
            cout<<"F = "<<f<<" and if it is -10000, I will calculate it here ..."<<endl;
        if(f == -10000)
            f = F(right);
        //if(verbosity > 0)
            cout<<"Now F is :"<<f<<endl;
        JetSpecificEfficiencyHandler * tmpHandler = NULL;
        for (uint i = 1; i < right->numberOfHandlers(); i++) {
            tmpHandler = right->getHandler(i);
            //if(verbosity > 0)
                cout<<i<<"'th right handler is "<<tmpHandler->getName()<<" ..."<<endl;
            JetSpecificEfficiencyHandler * RightNBB = new JetSpecificEfficiencyHandler(*tmpHandler, "_RC");
            RightNBB->setVerbosity(verbosity);
            cout<<tmpHandler->twoD<<"\t my First!"<<endl;
            if(tmpHandler->twoD)
                RightNBB->set2Ds();
            else
                RightNBB->twoD = false;
            JetSpecificEfficiencyHandler * LeftNBB = new JetSpecificEfficiencyHandler(*BaseRegion::getHandler(2),
                    std::string(RightNBB->getName() + "_SubtractedCopy"));
            LeftNBB->setVerbosity(verbosity);
            cout<<BaseRegion::getHandler(2)->twoD<<"\t my Second"<<endl;
            if(BaseRegion::getHandler(2)->twoD)
                LeftNBB->set2Ds();
            else
                LeftNBB->twoD = false;
            RightNBB->setName(string(RightNBB->getName() + "_RC")); //RighCopy
            //if(verbosity > 0){
                cout<<"The copy of "<<i<<"'th right handler is \n\t"<<RightNBB->getName()<<" ..."<<endl;
                cout<<"\tIntegral of it: "<<RightNBB->GetEffH1(0)->GetHAll()->Integral();
                cout<<"\n\tEntries of it: "<<RightNBB->GetEffH1(0)->GetHAll()->GetEntries()<<endl;
//            }
            LeftNBB->setName(string(LeftNBB->getName()+"_" +tmpHandler->getName()+ "_SubtractedCopy"));
            //if(verbosity > 0){
                cout<<"The copy of the left handler is \n\t"<<LeftNBB->getName()<<" ..."<<endl;
                cout<<"\tIntegral of it: "<<LeftNBB->GetEffH1(0)->GetHAll()->Integral();
                cout<<"\n\tEntries of it: "<<LeftNBB->GetEffH1(0)->GetHAll()->GetEntries()<<endl;
//            }

            RightNBB->multiply((-1. * f));
            //if(verbosity > 0){
                cout<<i<<"'th right handler is multiplied by "<< -1. * f<<" ..."<<endl;
                cout<<"\tIntegral of it: "<<RightNBB->GetEffH1(0)->GetHAll()->Integral();
                cout<<"\n\tEntries of it: "<<RightNBB->GetEffH1(0)->GetHAll()->GetEntries()<<endl;
//            }
            LeftNBB->add(*RightNBB);
            //if(verbosity > 0){
                cout<<"The copy of the left handler is added to "<<-1.*f<<" times of the right one ..."<<endl;
                cout<<"\tIntegral of it: "<<LeftNBB->GetEffH1(0)->GetHAll()->Integral();
                cout<<"\n\tEntries of it: "<<LeftNBB->GetEffH1(0)->GetHAll()->GetEntries()<<endl;
//            }

            LeftNBB->SetEntries(((BaseRegion::getHandler(2))->GetEntries() - f * tmpHandler->GetEntries()));
            //if(verbosity > 0)
                cout<<"The entries of left is just set: "<<LeftNBB->GetEffH1(0)->GetHAll()->GetEntries()<<endl;
            BaseRegion::AddHandler(LeftNBB);
            //if(verbosity > 0)
                cout<<LeftNBB->getName()<< " is added to the left region ..."<<endl;
        }
    };

protected:

    virtual void FillRest(const ExtendedJet * jet, double weight) {
        if(verbosity > 0)
            cout<<"The FillRest Method starts with \n\t"<<Handlers.at(2)->getName()<<endl;
        for (uint i = 2; i < Handlers.size(); i++) {
            Handlers.at(i)->Fill(jet, weight);
            if(verbosity > 1)
                cout<<"\t"<<Handlers.at(i)->getName()<<" is just filled\n\tWeight :"<<weight<<endl;
        }
    };



    std::string Name;
    double LowEdge;
    double HighEdge;
    std::vector<JetSpecificEfficiencyHandler*> Handlers;
    int verbosity;
};

#endif	/* _BASEREGION_H */

