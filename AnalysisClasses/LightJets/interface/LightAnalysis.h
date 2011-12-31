/* 
 * File:   LightAnalysis.h
 * Author: ajafari
 *
 * Created on September 2, 2010, 11:29 AM
 */

#ifndef _LIGHTANALYSIS_H
#define	_LIGHTANALYSIS_H
#include "../../../AnalysisClasses/ChiSquared/interface/LightStudyJetHandler.h"
#include "../../../AnalysisClasses/ChiSquared/interface/EffChiSquaredHandler.h"
#include "../../../AnalysisClasses/ChiSquared/interface/TopEvent.h"

class LightAnalysis{
public:
    LightAnalysis(std::string name, std::string type, double lowEdge = -1., double highEdge = 10000.,double antiTag=1000.):
    Name(name),Type(type),LowEdge(lowEdge),HighEdge(highEdge),AntiTagCut(antiTag){
        handlers.clear();
        QuarkMatchedHandler * meff_h = new QuarkMatchedHandler("QuarkMatched");
        meff_h->set2Ds();
        handlers.push_back(meff_h);
        BMatchedHandler * eff_h = new BMatchedHandler("BMatched");
        eff_h->set2Ds();
        handlers.push_back(eff_h);
        RadiationHandler * t = new RadiationHandler("Radiation");
        t->set2Ds();
        handlers.push_back(t);
        verbosity = 0;
    }
    virtual ~LightAnalysis(){};
    virtual void Fill(const TopEvent je, double weight = 1.){
        ExtendedJet myCand1;
        ExtendedJet myCand2;
        if(Type == "LepB"){
            myCand1 = je.getLepBCand();
            myCand1.setMJetLepton(je.getMlb());
        } else if(Type == "HadB"){
            myCand1 = je.getHadBCand();
            myCand1.setMJetLepton(je.getMlHadB());
        } else if(Type == "Light"){
            myCand1 = je.getQ1();
            myCand1.setMJetLepton(je.getMll1());
            myCand2 = je.getQ2();
            myCand2.setMJetLepton(je.getMll2());
        }
//        cout<<handlers.size()<<endl;
        if(verbosity > 3)
            cout<<"In Analysis "<<Name<<"\t"<<Type<<endl;
        for(uint i = 0; i<handlers.size(); i++){
            if(verbosity > 3)
                cout<<"\tIn Handler "<<handlers.at(i)->getName()<<endl;
            if(Type != "Light"){
                if(verbosity > 3){
                    cout<<"In Lep Analysis:"<<endl;
                    cout<<"\t\t"<<LowEdge<<" < "<<myCand1.getMJetLepton()<<" < "<<HighEdge<<" : "
                    <<(bool)(fabs(myCand1.getMJetLepton()) > LowEdge && fabs(myCand1.getMJetLepton()) < HighEdge)
                    <<endl;
                }
                if(myCand1.getMJetLepton() > LowEdge && myCand1.getMJetLepton() < HighEdge)
                    handlers.at(i)->Fill(&myCand1,weight);
                if(verbosity > 3)
                    cout<<"\t\tHandler "<<Name<<"_"<<Type<<"\n\t\t"<<handlers.at(i)->getName()<<" is filled"<<endl;
            }
            else{
                if(verbosity > 3){
                    cout<<"In Light Analysis:"<<endl;
                    cout<<"\t\t"<<LowEdge<<" < "<<myCand1.getMJetLepton()<<" < "<<HighEdge<<" : "
                    <<(bool)(fabs(myCand1.getMJetLepton()) > LowEdge && fabs(myCand1.getMJetLepton()) < HighEdge)
                    <<endl;
                }
                if(myCand1.getMJetLepton() > LowEdge && myCand1.getMJetLepton() < HighEdge){
                    if(verbosity > 3)
                        cout<<myCand1.getJet().btag_trackCountingHighEffBJetTags()<<" <(?) "<<AntiTagCut<<endl;
                    if(myCand1.getJet().btag_trackCountingHighEffBJetTags() < AntiTagCut){
                        handlers.at(i)->Fill(&myCand1,weight);
                        if(verbosity > 3)
                            cout<<"myCand1 is filled"<<endl;
                    }
                }

                if(verbosity > 3)
                    cout<<"\t\tHandler "<<Name<<"_"<<Type<<"\n\t\t"<<handlers.at(i)->getName()<<" is filled"<<endl;
                
                if(verbosity > 3)
                    cout<<"\t\t"<<LowEdge<<" < "<<myCand2.getMJetLepton()<<" < "<<HighEdge<<" : "
                    <<(bool)(fabs(myCand2.getMJetLepton()) > LowEdge && fabs(myCand2.getMJetLepton()) < HighEdge)
                    <<endl;
                if(myCand2.getMJetLepton() > LowEdge && myCand2.getMJetLepton() < HighEdge){
                    if(verbosity > 3)
                        cout<<myCand2.getJet().btag_trackCountingHighEffBJetTags()<<" <(?) "<<AntiTagCut<<endl;
                    if(myCand2.getJet().btag_trackCountingHighEffBJetTags() < AntiTagCut){
                        handlers.at(i)->Fill(&myCand2,weight);
                        if(verbosity > 3)
                            cout<<"myCand2 is filled"<<endl;
                    }
                }
                if(verbosity > 3)
                    cout<<"\t\tHandler "<<Name<<"_"<<Type<<"\n\t\t"<<handlers.at(i)->getName()<<" is filled"<<endl;
            }
        }
    }
    void WriteAll(TDirectory * dir){
        dir->cd();
        TDirectory * my_Dir = (TDirectory *)dir->mkdir(string(Name+"_"+Type).c_str());
        my_Dir->cd();
        
        for(uint i = 0; i<handlers.size(); i++){
            handlers.at(i)->WriteAll(my_Dir);
        }
        dir->cd();
    }
    void setVerbosity(int i){
        verbosity = i;
    }
    void AddHandler(SpecificEffHandler<ExtendedJet> * input){
        handlers.push_back(input);
    }
    std::string WhoAmI(){
        return "LightAnalysis";
    }
    std::string getName(){
        return Name;
    }
    void setName(std::string name){
        Name = name;
    }
    double getIntegral(int handlerNumber){
         TH1D * Hist = handlers.at(handlerNumber)->GetEffH1(0)->GetHAll();
         return Hist->Integral();
    }
    std::string Name;
    std::string Type;
    double LowEdge;
    double HighEdge;
    double AntiTagCut;
    int verbosity;
    std::vector<SpecificEffHandler<ExtendedJet>* > handlers;
};

#endif	/* _LIGHTANALYSIS_H */

