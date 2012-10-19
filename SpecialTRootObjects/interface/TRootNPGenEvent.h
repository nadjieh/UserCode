#ifndef TRootNPGenEvent_h
#define TRootNPGenEvent_h
#include <iostream>
#include <iomanip>
#include <vector>

#include "TObject.h"
#include "Rtypes.h"

#include "../interface/TRootMCParticle.h"
#include "../interface/TRootGenTop.h"
using namespace std;
namespace TopTree {

    class TRootNPGenEvent : public TObject {
    public:

        TRootNPGenEvent() {
            isNewPhysics_ = false;
        };

        TRootNPGenEvent(const Bool_t isNewPhysics, const std::vector<TopTree::TRootGenTop> tops, const std::vector<TopTree::TRootMCParticle> leptons, const std::vector<TopTree::TRootMCParticle> quarks,
                const std::vector<TopTree::TRootMCParticle> bquarks, const std::vector<TopTree::TRootMCParticle> invisibleParticles, const std::vector<TopTree::TRootMCParticle> neutrinos,
                const std::vector<TopTree::TRootMCParticle> gluinos, const std::vector<TopTree::TRootMCParticle> stops) {
            isNewPhysics_ = isNewPhysics;
            tops_ = tops;
            leptons_ = leptons;
            quarks_ = quarks;
            bquarks_ = bquarks;
            invisibleParticles_ = invisibleParticles;
            neutrinos_ = neutrinos;
            gluinos_ = gluinos;
            stops_ = stops;
        };

        TRootNPGenEvent(const TRootNPGenEvent& gevt) {
            isNewPhysics_ = gevt.isNewPhysics_;
            tops_ = gevt.tops_;
            leptons_ = gevt.leptons_;
            quarks_ = gevt.quarks_;
            bquarks_ = gevt.bquarks_;
            invisibleParticles_ = gevt.invisibleParticles_;
            neutrinos_ = gevt.neutrinos_;
            gluinos_ = gevt.gluinos_;
            stops_ = gevt.stops_;
        };

        virtual ~TRootNPGenEvent() {
            ;
        };

        virtual TString typeName() const {
            return "TRootNPGenEvent";
        }

        Bool_t isNewPhysics() const {
            return isNewPhysics_;
        };

        Bool_t isThereTop() const {
            return tops_.size() > 0 ? true : false;
        };

        Int_t numberOfTops() const {
            return tops_.size();
        };

        Int_t numberOfLeptons() const {
            return leptons_.size();
        };

        Int_t numberOfQuarks() const {
            return quarks_.size();
        };

        Int_t numberOfBQuarks() const {
            return bquarks_.size();
        };

        Int_t numberOfInvisibleParticles() const {
            return invisibleParticles_.size();
        };

        Int_t numberOfNeutrinos() const {
            return neutrinos_.size();
        };

        Int_t numberOfGluinos() const {
            return gluinos_.size();
        };

        Int_t numberOfStops() const {
            return stops_.size();
        };

        std::vector<TRootGenTop> tops() const {
            return tops_;
        };

        std::vector<TRootMCParticle> leptons() const {
            return leptons_;
        };

        std::vector<TRootMCParticle> quarks() const {
            return quarks_;
        };

        std::vector<TRootMCParticle> bquarks() const {
            return bquarks_;
        };

        std::vector<TRootMCParticle> invisibleParticles() const {
            return invisibleParticles_;
        };

        std::vector<TRootMCParticle> neutrinos() const {
            return neutrinos_;
        };

        std::vector<TRootMCParticle> gluinos() const {
            return gluinos_;
        };

        std::vector<TRootMCParticle> stops() const {
            return stops_;
        };

        friend std::ostream& operator<<(std::ostream& stream, const TRootNPGenEvent& gevent) {
            stream << "Event ";
            if (gevent.isNewPhysics()) stream << " is NewPhysics ";
            stream << ". ";
            stream << gevent.numberOfTops() << " tops - " << gevent.numberOfLeptons() << " leptons - " << gevent.numberOfQuarks() << " quarks - ( " << gevent.numberOfBQuarks() << "b ) ";
            stream << gevent.numberOfInvisibleParticles() << " invisible particles ( " << gevent.numberOfNeutrinos() << " neutrinos )";
            return stream;
        }

        void topChargeBassigner() {
            std::vector<TRootMCParticle> topBs = this->correctBassigner();
            for (unsigned int nT = 0; nT < this->tops().size(); nT++) {
                if (this->tops().at(nT).W().charge() < 0)
                    tops_.at(nT).setCharge(-1);

                else
                    tops_.at(nT).setCharge(1);
                //                    cout << "b in top mother type: " << this->tops()[nT].bquark().motherType() << endl;
                //                    cout << "\n\t" << this->tops()[nT].bquark().Px() <<
                //                            "\n\t" << this->tops()[nT].bquark().Py() <<
                //                            "\n\t" << this->tops()[nT].bquark().Pz() <<
                //                            "\n\t" << this->tops()[nT].bquark().E() << endl;
                //                    cout << "top charge: " << tops_.at(nT).charge() << endl;
                //                cout << (this->tops()[nT].bquark().motherType() * this->tops()[nT].charge()) << "\tI am safe then!" << endl;
                for (unsigned int nb = 0; nb < topBs.size(); nb++) {
                    if ((topBs[nb].motherType() * this->tops()[nT].charge()) > 0)
                        tops_[nT].setBquark(topBs[nb]);
                }
            }
        }

        std::vector<TRootMCParticle> correctBassigner() {
            std::vector<TRootMCParticle> topBs;
            for (unsigned int nb = 0; nb < bquarks_.size(); nb++) {
                if (fabs(bquarks_[nb].motherType()) == 6) {
                    //                    cout << "4 vector in method:\n\t" << bquarks_[nb].Px() <<
                    //                            "\n\t" << bquarks_[nb].Py() <<
                    //                            "\n\t" << bquarks_[nb].Pz() <<
                    //                            "\n\t" << bquarks_[nb].E() << endl;
                    topBs.push_back(bquarks_[nb]);
                }
            }
            //            cout << "b size: " << topBs.size() << "\tmother id: " << topBs.at(0).motherType() << endl;
            return topBs;
        }

        std::vector<int > getNonTopWList() {
            /*
             * 1: E
             * 2: Mu
             * 3: Tau
             * 4: Q
             */
            std::vector<int > res;
            res.clear();
            if (tops_.size() > 2) {
                cout << "Very BAD event!!" << endl;
                return res;
            }
            int nMuons = 0;
            int nEs = 0;
            int nTaus = 0;
            int nLightQuarks = 0 ;
            for (unsigned int i = 0; i < quarks_.size(); i++) {
                if (fabs(quarks_[i].motherType()) == 24 && fabs(quarks_[i].status()) == 3 &&
                        fabs(quarks_[i].type()) < 5)
                    nLightQuarks++;
            }
            for (unsigned int i = 0; i < leptons_.size(); i++) {
                if (fabs(leptons_[i].motherType()) == 24 && fabs(leptons_[i].status()) == 3) {
                    if (fabs(leptons_[i].type()) == 11)
                        nEs++;
                    else if (fabs(leptons_[i].type()) == 13)
                        nMuons++;
                    else if (fabs(leptons_[i].type()) == 15)
                        nTaus++;
                }
            }
//            cout << "\tElectrons: " << nEs <<
//                    "\n\tMuons: " << nMuons <<
//                    "\n\tTaus: " << nTaus <<
//                    "\n\tquarks: " << nLightQuarks << endl;
            if ((2*(nTaus + nEs + nMuons) + nLightQuarks) % 2 == tops_.size()){
                cout<<"Pay attention here for tW!!"<<endl;
                return res;
            }
            if (tops_.size() == 1) {
                if (nEs > 1)
                    res.push_back(1);
                else if (nMuons > 1)
                    res.push_back(2);
                else if (nTaus > 1)
                    res.push_back(3);
                else if (nLightQuarks > 2)
                    res.push_back(4);
                else if (nEs == 1 && !tops_[0].isLeptonicEl())
                    res.push_back(1);
                else if (nMuons == 1 && !tops_[0].isLeptonicMu())
                    res.push_back(2);
                else if (nTaus == 1 && !tops_[0].isLeptonicTau())
                    res.push_back(3);
                else if (nLightQuarks == 2 && !tops_[0].isHadronic())
                    res.push_back(4);
            }
            return res;
        }
    private:

        Bool_t isNewPhysics_;
        std::vector<TRootGenTop> tops_;
        std::vector<TRootMCParticle> leptons_;
        std::vector<TRootMCParticle> quarks_;
        std::vector<TRootMCParticle> bquarks_;
        std::vector<TRootMCParticle> invisibleParticles_;
        std::vector<TRootMCParticle> neutrinos_;
        std::vector<TRootMCParticle> gluinos_;
        std::vector<TRootMCParticle> stops_;

        ClassDef(TRootNPGenEvent, 2);
    };
}

#endif
