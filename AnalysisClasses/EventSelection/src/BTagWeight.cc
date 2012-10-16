#include "../interface/BTagWeight.h"

double BTagWeight::weight(vector<vector<JetInfo> >jets) {
    int njets = jets.size();
    std::vector<int> comb(jets.size());
    for (unsigned int i = 0; i < jets.size(); i++)
        comb[i] = 0;
    int idx = 0;
    int max = taggers + 1; //force sorted tagging //1 << taggers;
    double pMC = 0;
    double pData = 0;
    if (jets.size() == 0) return 0.;
    while (comb[jets.size() - 1] < max) {
        std::vector<int> tags;
        for (int j = 0; j < taggers; j++)
            tags.push_back(0);

        double mc = 1.;
        double data = 1.;
        for (int j = 0; j < njets; j++) // loop on jets
        {
            // std::cout << std::endl << "Jet" << j ;

            // if none tagged, take the 1-eff SF for the loosest:
            double tagMc = 1. - jets[j][0].eff;
            double tagData = 1. - jets[j][0].eff * jets[j][0].sf;
            if (comb[j] > 0) //if at least one tagged take the SF for the tightest tagger
            {
                int k = comb[j] - 1;
                tagMc = jets[j][k].eff;
                tagData = jets[j][k].eff * jets[j][k].sf;

                if (comb[j] < taggers) //if at least one tagged take the SF for the tightest tagger
                {
                    int k1 = comb[j];
                    tagMc *= 1 - jets[j][k1].eff / jets[j][k].eff;
                    tagData *= 1 - jets[j][k1].eff / jets[j][k].eff * jets[j][k1].sf / jets[j][k].sf;

                }
            }


            for (int k = 0; k < taggers; k++) // loop on taggers
            {
                bool tagged = (comb[j] > k); ///((comb[j] >> k) & 0x1) == 1;
                if (tagged) tags[k]++;
            }
            mc *= tagMc;
            data *= tagData;
        }

        if (filter(tags)) {
            //  std::cout << mc << " " << data << " " << data/mc << " " << pData/pMC << endl;
            pMC += mc;
            pData += data;
            //n    std::cout << std::endl<< "mc, data,ratioThis,ratioTot " <<  mc << " " << data << " " << data/mc << " " << pData/pMC << endl;
        }
        while (comb[idx] == max - 1 && idx + 1 < (int) jets.size()) idx++; // find first jets for which we did not already test all configs 
        // next combination
        comb[idx]++; // test a new config for that jet
        for (int i = 0; i < idx; i++) {
            comb[i] = 0;
        } // reset the tested configs for all previous jets
        idx = 0;
    }
    if (pMC == 0) return 0;
    return pData / pMC;
}

bool BTagWeight::filter(std::vector<int> t) {
    return t[0] >= 1; //&& t[1] >= 1;
    // return (t >= minTags && t <= maxTags);
}

void BTagWeight::GetEffSF_TCHEL(double pt, double eta, double discriminator_value, double& eff, double& sf, int Systematics) {
    TF1 BTagScaleFactor("fSFB", "0.603913*((1.+(0.286361*x))/(1.+(0.170474*x)))", 30, 1000);

    TF1 EffB("EffB", "3.90732786802e-06*x*x*x*x +  -0.000239934437355*x*x*x +  0.00664986827287*x*x +  -0.112578996016*x +  1.00775721404", -100, 100);
    TF1 EffC("EffC", "0.343760640168*exp(-0.00315525164823*x*x*x + 0.0805427315196*x*x + -0.867625139194*x + 1.44815935164 )", -100, 100);

    TF1 MisTag_Eta0_5("MistagEta0_5", "(((-0.0235318+(0.00268868*x))+(-6.47688e-06*(x*x)))+(7.92087e-09*(x*(x*x))))+(-4.06519e-12*(x*(x*(x*x))))", 20., 670.);
    TF1 MisTag_Eta5_1("MistagEta5_1", "(((-0.0257274+(0.00289337*x))+(-7.48879e-06*(x*x)))+(9.84928e-09*(x*(x*x))))+(-5.40844e-12*(x*(x*(x*x))))", 20., 670.);
    TF1 MisTag_Eta1_15("MistagEta1_15", "(((-0.0310046+(0.00307803*x))+(-7.94145e-06*(x*x)))+(1.06889e-08*(x*(x*x))))+(-6.08971e-12*(x*(x*(x*x))))", 20., 670.);
    TF1 MisTag_Eta15_24("MistagEta15_24", "(((-0.0274561+(0.00301096*x))+(-8.89588e-06*(x*x)))+(1.40142e-08*(x*(x*x))))+(-8.95723e-12*(x*(x*(x*x))))", 20., 670.);

    TF1 SFlight_Eta0_5("SFlightEta0_5", "(1.13615*((1+(-0.00119852*x))+(1.17888e-05*(x*x))))+(-9.8581e-08*(x*(x*(x/(1+(0.00689317*x))))))", 20., 670.);
    TF1 SFlight_Eta5_1("SFlightEta5_1", "(1.13277*((1+(-0.00084146*x))+(3.80313e-06*(x*x))))+(-8.75061e-09*(x*(x*(x/(1+(0.00118695*x))))))", 20., 670.);
    TF1 SFlight_Eta1_15("SFlightEta1_15", "(1.17163*((1+(-0.000828475*x))+(3.0769e-06*(x*x))))+(-4.692e-09*(x*(x*(x/(1+(0.000337759*x))))))", 20., 670.);
    TF1 SFlight_Eta15_24("SFlightEta15_24", "(1.14554*((1+(-0.000128043*x))+(4.10899e-07*(x*x))))+(-2.07565e-10*(x*(x*(x/(1+(-0.00118618*x))))))", 20., 670.);


    //double eff, sf;

    if (discriminator_value > 1.7)//it is b        
    {
        sf = BTagScaleFactor.Eval(pt);
        //systematics : 0=the exact bsf values ; 1 = 4%; -1 = -4% PAS-11-003
        double four_percent = (((Systematics > 0) ? 1.0 : -1.0) * 4.0 * sf / 100.0);
        sf += four_percent;
        //        if (Systematics != 0) {
        //            if (fabs(eta) < 1.2)
        //                sf += four_percent;
        //            else
        //                sf -= four_percent;
        //        }

        eff = EffB.Eval(discriminator_value);
    }/*else if (discriminator_value > 1.0) //???? is it C????
        {
            sf = BTagScaleFactor.Eval(pt);
            eff = EffC.Eval(disc);
        }*/
    else // it is a light quark
    {
        if (fabs(eta) < 0.5) {
            eff = MisTag_Eta0_5.Eval(pt);
            sf = SFlight_Eta0_5.Eval(pt);
        } else if (fabs(eta) < 1.0) {
            eff = MisTag_Eta5_1.Eval(pt);
            sf = SFlight_Eta5_1.Eval(pt);
        } else if (fabs(eta) < 1.5) {
            eff = MisTag_Eta1_15.Eval(pt);
            sf = SFlight_Eta1_15.Eval(pt);
        } else if (fabs(eta) < 2.4) {
            eff = MisTag_Eta15_24.Eval(pt);
            sf = SFlight_Eta15_24.Eval(pt);
        }
    }
}

void BTagWeight::GetEffSF_SSVHEM(double pt, double eta, double discriminator_value, double& eff, double& sf, int Systematics) {
    TF1 BTagScaleFactor("fSFB", "0.896462*((1.+(0.00957275*x))/(1.+(0.00837582*x)))", 30, 1000);

    TF1 EffB("EffB", "0.00559749726591*x*x*x*x +  -0.0250942917873*x*x*x +  -0.07343076238*x*x +  0.209954428241*x +  0.587277178178", -100, 100);
    TF1 EffC("EffC", "0.00143789244176*x*x*x*x +  -0.00186154098096*x*x*x +  -0.0230147611829*x*x +  -0.0497041720896*x +  0.324134245921", -100, 100);

    TF1 MisTag_Eta0_8("MistagEta0_8", "(((0.000547883+(0.00023023*x))+(-7.31792e-07*(x*x)))+(1.15659e-09*(x*(x*x))))+(-7.00641e-13*(x*(x*(x*x))))", 20., 670.);
    TF1 MisTag_Eta8_16("MistagEta8_16", "(((0.000615562+(0.000240254*x))+(-7.00237e-07*(x*x)))+(1.2566e-09*(x*(x*x))))+(-8.59011e-13*(x*(x*(x*x))))", 20., 670.);
    TF1 MisTag_Eta16_24("MistagEta16_24", "(((0.000372388+(0.000309735*x))+(-4.35952e-07*(x*x)))+(3.63763e-10*(x*(x*x))))+(-2.11993e-13*(x*(x*(x*x))))", 20., 670.);

    TF1 SFlight_Eta0_8("SFlightEta0_8", "((0.86318+(0.000801639*x))+(-1.64119e-06*(x*x)))+(2.59121e-10*(x*(x*x)))", 20., 670.);
    TF1 SFlight_Eta8_16("SFlightEta8_16", "((0.958973+(-0.000269555*x))+(1.381e-06*(x*x)))+(-1.87744e-09*(x*(x*x)))", 20., 670.);
    TF1 SFlight_Eta16_24("SFlightEta16_24", "((0.923033+(-0.000898227*x))+(4.74565e-06*(x*x)))+(-6.11053e-09*(x*(x*x)))", 20., 670.);


    sf = 1.0;
    eff = 1.0;
    //double eff, sf;

    if (discriminator_value > 1.74)//it is b        
    {
        sf = BTagScaleFactor.Eval(pt);
        //systematics : 0=the exact bsf values ; 1 = 4%B -4%E ; -1 = -4%B 4%
        double four_percent = (((Systematics > 0) ? 1.0 : -1.0) * 4.0 * sf / 100.0);
        if (Systematics != 0) {
            if (fabs(eta) < 1.2)
                sf += four_percent;
            else
                sf -= four_percent;
        }
        eff = EffB.Eval(discriminator_value);
    }/*else if (discriminator_value > 1.0) //???? is it C????
        {
            sf = BTagScaleFactor.Eval(pt);
            eff = EffC.Eval(disc);
        }*/
    else // it is a light quark
    {
        if (fabs(eta) < 0.8) {
            eff = MisTag_Eta0_8.Eval(pt);
            sf = SFlight_Eta0_8.Eval(pt);
        } else if (fabs(eta) < 1.6) {
            eff = MisTag_Eta8_16.Eval(pt);
            sf = SFlight_Eta8_16.Eval(pt);
        } else if (fabs(eta) < 2.4) {
            eff = MisTag_Eta16_24.Eval(pt);
            sf = SFlight_Eta16_24.Eval(pt);
        }
    }
}

double BTagScaleFactorErr(double pt) {
    /*https://twiki.cern.ch/twiki/pub/CMS/BtagPOG/SFb-mujet_payload.txt*/
    double err = 0;
    float ptmin[] = {30, 40, 50, 60, 70, 80, 100, 120, 160, 210, 260, 320, 400, 500};
    float ptmax[] = {40, 50, 60, 70, 80, 100, 120, 160, 210, 260, 320, 400, 500, 670};
    double SFb_error[] = {0.0543376, 0.0534339, 0.0266156, 0.0271337, 0.0276364, 0.0308838, 0.0381656,
        0.0336979, 0.0336773, 0.0347688, 0.0376865, 0.0556052, 0.0598105, 0.0861122};
    for (int i = 0; i < 14; i++) {
        if (pt < ptmax[i] && pt > ptmin[i]) {
            err = SFb_error[i];
            break;
        }
    }
    return err;
}

void BTagWeight::GetEffSF_TCHPT(double pt, double eta, int partonFlavour, double discriminator_value,
        double& eff, double& sf, int Systematics) {
    /*https://twiki.cern.ch/twiki/pub/CMS/BtagPOG/SFb-mujet_payload.txt*/
    TF1 BTagScaleFactor("fSFB", "0.895596*((1.+(9.43219e-05*x))/(1.+(-4.63927e-05*x)))", 30, 670);

    /*https://twiki.cern.ch/twiki/pub/CMS/BtagPOG/eff_b_c-ttbar_payload.txt*/
    TF1 EffB("EffB", "1.26119661124e-05*x*x*x*x +  -0.000683198597977*x*x*x +  0.0145106168149*x*x +  -0.159575511553*x +  0.887707865272", -100, 100);
    TF1 EffC("EffC", "0.451288118581*exp(-0.0213290505241*x*x*x + 0.356020789904*x*x + -2.20158883207*x + 1.84838018633 )", -100, 100);

    /*https://twiki.cern.ch/twiki/pub/CMS/BtagPOG/MistagFuncs.C*/
    TF1 MisTag_Eta0_24("MistagTCHPT", "(-0.00101+(4.70405e-05*x))+(8.3338e-09*(x*x))", 20., 670.);

    /*https://twiki.cern.ch/twiki/pub/CMS/BtagPOG/SFlightFuncs.C*/
    TF1 SFlight_Eta0_24("SFlightTCHP", "((1.20711+(0.000681067*x))+(-1.57062e-06*(x*x)))+(2.83138e-10*(x*(x*x)))", 20., 670.);
    TF1 SFlight_Eta0_24_UncDown("SFlightTCHP_UncDown", "((1.03418+(0.000428273*x))+(-5.43024e-07*(x*x)))+(-6.18061e-10*(x*(x*x)))", 20., 670.);
    TF1 SFlight_Eta0_24_UncUp("SFlightTCHP_UncUp", "((1.38002+(0.000933875*x))+(-2.59821e-06*(x*x)))+(1.18434e-09*(x*(x*x)))", 20., 670.);

    /*https://twiki.cern.ch/twiki/pub/CMS/BtagPOG/SFb-mujet_payload.txt*/
    /*+ btag recipe: https://twiki.cern.ch/twiki/bin/viewauth/CMS/BtagPOG#2011_Data_and_MC*/
    TF1 SFc_Eta0_24("fSFC", "0.895596*((1.+(9.43219e-05*x))/(1.+(-4.63927e-05*x)))", 30., 670.);



    sf = 1.0;
    eff = 1.0;
    //double eff, sf;

    if (fabs(partonFlavour) == 5)//it is b        
    {
        sf = BTagScaleFactor.Eval(pt);
        //systematics : 0=the exact bsf ; 1=upper limit -1=lower limit
        double SFerr = (((Systematics > 0) ? 1.0 : -1.0) * BTagScaleFactorErr(pt) * sf );
        sf += SFerr;
        eff = EffB.Eval(discriminator_value);
        if (discriminator_value < -0.5)
            eff = 1;
        if (discriminator_value > 20)
            eff = 0;
    } else if (fabs(partonFlavour) == 4)// it is a c quark
    {
        eff = EffC.Eval(discriminator_value);
        if (discriminator_value < 0.5)
            eff = 0.99;
        if (discriminator_value > 20)
            eff = 0;
        /*
         * systematics : 0=the exact bsf ; 1=upper limit -1=lower limit
         * twice the b_SF: 
         * https://twiki.cern.ch/twiki/bin/viewauth/CMS/BtagPOG
         */
        double SFerr = (((Systematics > 0) ? 1.0 : -1.0) * BTagScaleFactorErr(pt) * sf );
        sf = SFc_Eta0_24.Eval(pt);
        sf += 2 * SFerr;
    } else // it is a light quark
    {
        eff = MisTag_Eta0_24.Eval(pt);
        /*
         * systematics : 0=the exact bsf ; 1=upper limit -1=lower limit
         */
        sf = SFlight_Eta0_24.Eval(pt);

        if (Systematics < 0)
            sf += SFlight_Eta0_24_UncDown.Eval(pt);
        else if (Systematics > 0)
            sf += SFlight_Eta0_24_UncUp.Eval(pt);

    }
    //    if (fabs(eta) > 2.6)
    //        eff = 0;
}