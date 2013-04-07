
{
	int n = 14;   
    double f00 = 0.713279;
    double fl0 = 0.293116;
    double F0Down[n] = { 0.713687,  0.71828 ,  0.705494,  0.711246,  0.71668 ,  0.713997,  0.721927 ,  0.715236, 0.727189 , 0.71628 ,  0.713362,  0.710543, f00 ,  0.718134};
    double FLDown[n] = { 0.292233,  0.295116 ,  0.30041,  0.295068,  0.28893 ,  0.292321,  0.273131 ,  0.296725, 0.289097 , 0.296116 ,  0.292738,  0.292989, fl0 ,  0.288012 };
    double F0UP[n] =   { 0.723795,  0.710279 ,  0.756202,  0.714611,  0.714998,  0.712626,  0.721927 ,  0.727304, 0.716897 , 0.71628 ,  0.72163 ,  0.710543, f00 ,  0.722006};
	double FLUP[n] =   { 0.282776,  0.281116 ,  0.248782,  0.291828,  0.290839,  0.293839,  0.273131 ,  0.284073, 0.298316 , 0.296116 ,  0.284106,  0.292989, fl0 ,  0.28357};

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
    for (int i = 0; i < n; i++) {
        double avgF0_ = (fabs(F0UP[i]-f00)+fabs(F0Down[i]-f00))/2.;
        double avgFL_ = (fabs(FLUP[i]-fl0)+fabs(FLDown[i]-fl0))/2.;
        cout<<strVc[i]<<"&\t"<<avgFL_<<"&\t"<<avgF0_<<"\\"<<"\\"<<endl;
        cout<<"\\hline"<<endl;
        sumFLUP += (avgFL_ * avgFL_);
        sumF0UP += (avgF0_ * avgF0_);
		double frU = 1 - F0UP[i] -   FLUP[i] ;
		double frD = 1 - F0Down[i] - FLDown[i] ;
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


