
{
	int n = 14;   
    double f00 = 0.713279;
    double fl0 = 0.293116;
    double F0Down[n] = { 0.705833,  0.71628  ,  0.715345,  0.711246,  0.71668 ,  0.716997,  0.721927 ,  0.715236, 0.728189 ,  0.71628 ,  0.713362,  0.710543, 0.70628  ,  0.713134};
    double FLDown[n] = { 0.300225,  0.295116 ,  0.291915,  0.295068,  0.28893 ,  0.292321,  0.288131 ,  0.296725, 0.285097 , 0.296116 ,  0.293738,  0.292989, 0.297116 ,  0.296012};
    double F0UP[n] =   { 0.717311,  0.711279 ,  0.711086,  0.714611,  0.714998,  0.713626,  0.721927 ,  0.727304, 0.717897 , 0.71628  ,  0.71763 ,  0.710543, 0.72228  ,  0.719006};
	double FLUP[n] =   { 0.288874,  0.281116 ,  0.276432,  0.291828,  0.290839,  0.293839,  0.288131 ,  0.284073, 0.302316 , 0.296116 ,  0.287106,  0.292989, 0.285116 ,  0.290157};

    std::vector<string> strVc;
    strVc.push_back("JES");
    strVc.push_back("JER");
    strVc.push_back("unclustered energy");
    strVc.push_back("pileup");
    strVc.push_back("b-flavored scale factor");
    strVc.push_back("non-b-flavored scale factor");
    strVc.push_back("single-top generator");
    strVc.push_back("$\\rm Q^{2}$ scale");
    strVc.push_back("$\\rm m_{top}$");
    strVc.push_back("PDF");
    strVc.push_back("$\\rm t\\bar{t}$ normalization");
    strVc.push_back("QCD shape");
    strVc.push_back("W+jets shape");
    strVc.push_back("integrated luminosity");
    double sumFLUP = 0;
    double sumF0UP = 0;
	double frSyst = 0;
	double fr0 = 1- f00 - fl0;
    std::cout.setf(std::ios::fixed);
    std::cout.precision(3);
	double s = 0;
    //3 sigma for mass
	F0Down[8] = (F0Down[8] - f00)/3 + f00;
    //F0Down[8] = (F0Down[8]+(2*f00))/3;
    FLDown[8] = (FLDown[8]+(2*fl0))/3;
    F0UP[8]   = (F0UP[8]+(2*f00))/3;
    FLUP[8]   = (FLUP[8]+(2*fl0))/3;
    for (int i = 0; i < n; i++) {
        double avgF0_ = (fabs(F0UP[i]-f00)+fabs(F0Down[i]-f00))/2.;
        double avgFL_ = (fabs(FLUP[i]-fl0)+fabs(FLDown[i]-fl0))/2.;
        //if(i == 8){
		//	avgF0_ = avgF0_/3;
		//	avgFL_ = avgFL_/3;
		//}
        cout<<strVc[i]<<"&\t"<<avgFL_<<"&\t"<<avgF0_<<"\\"<<"\\"<<endl;
        cout<<"\\hline"<<endl;
        sumFLUP += (avgFL_ * avgFL_);
        sumF0UP += (avgF0_ * avgF0_);
		frU = 1 - F0UP[i] -   FLUP[i] ;
		frD = 1 - F0Down[i] - FLDown[i] ;
		double avgFR_ = (fabs(frU-fr0)+fabs(frD-fr0))/2.;
		frSyst+=pow(avgFR_,2);
    }
    sumFLUP = sqrt(sumFLUP);
    sumF0UP = sqrt(sumF0UP);
    cout<<"\\hline"<<endl;
    cout << "total systematic uncertainty &"<<sumFLUP<<"&"<<sumF0UP<<"	\\"<<"\\"<<endl;
	cout<<"Fr      = "<<fr0<<endl;
	cout<<"Fr syst = "<<sqrt(frSyst)<<endl;
}


