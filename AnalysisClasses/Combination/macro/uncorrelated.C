
{
	int n = 14;   
    double f00 = 0.713279;
    double fl0 = 0.293116;


   TF1 *CLF = new TF1("CLF","pol1",164.8,179.2);
   CLF->SetParameter(0,0.03546242);
   CLF->SetParError(0,0.01240139);
   CLF->SetParLimits(0,0,0);
   CLF->SetParameter(1,0.001496536);
   CLF->SetParError(1,7.200211e-05);
   CLF->SetParLimits(1,0,0);
    double mlu = CLF->Eval(174.5);
    double mld = CLF->Eval(170.5);

   TF1 *CZF = new TF1("CZF","pol1",164.8,179.2);
   CZF->SetParameter(0,0.9709326);
   CZF->SetParError(0,0.01240139);
   CZF->SetParLimits(0,0,0);
   CZF->SetParameter(1,-0.001496536);
   CZF->SetParError(1,7.200211e-05);
   CZF->SetParLimits(1,0,0);
    double mzu = CZF->Eval(174.5);
    double mzd = CZF->Eval(170.5);

    double F0Down[n] = { 0.720105,  0.71636,  0.723243,  0.711246,  0.714559  ,  0.716997,  0.721927 ,  0.715236, mzd ,  0.71628 ,  0.713362,  0.716371, 0.70254 ,  0.722882};
    double FLDown[n] = { 0.286097,  0.2818 ,  0.274679,  0.295068,  0.28893   ,  0.292321,  0.288131 ,  0.296725, mld , 0.296116 ,  0.293738,  0.29646, 0.305549697 , 0.3034751037};
    double F0UP[n] =   { 0.706452,  0.7101 ,  0.703315,  0.714611,  0.711999  ,  0.713626,  0.721927 ,  0.727304, mzu, 0.71628 ,  0.71763 ,  0.7101866, 0.7240 ,  0.7036750474};
	double FLUP[n] =   { 0.300134,  0.2818 ,  0.311554,  0.291828,  0.29150025,  0.293839,  0.288131 ,  0.284073, mlu, 0.296116 ,  0.287106,  0.289770, 0.28068,  0.2827568963};

/*    double F0Down[n] = { 0.720105,  0.71636,  0.723243,  0.711246,  0.714559  ,  0.716997,  0.721927 ,  0.715236, 0.728189 ,  0.71628 ,  0.713362,  0.716371, 0.70254 ,  0.722882};
    double FLDown[n] = { 0.286097,  0.2818 ,  0.269325,  0.295068,  0.28893   ,  0.292321,  0.288131 ,  0.296725, 0.285097 , 0.296116 ,  0.293738,  0.29646, 0.305549697 , 0.3034751037};
    double F0UP[n] =   { 0.706452,  0.7101 ,  0.703315,  0.714611,  0.711999  ,  0.713626,  0.721927 ,  0.727304, 0.717897, 0.71628 ,  0.71763 ,  0.7101866, 0.7240 ,  0.7036750474};
	double FLUP[n] =   { 0.300134,  0.2818 ,  0.316906,  0.291828,  0.29150025,  0.293839,  0.288131 ,  0.284073, 0.302316, 0.296116 ,  0.287106,  0.289770, 0.28068,  0.2827568963*/

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

//additional effects
//gen values assignement
//f0              : 0.714326	+/-	0.111332
//f_              : 0.291271	+/-	0.0664435
	double dgl = 0.291271 - fl0;
	double dg0 = 0.714326 - f00;
	cout<<"gen values assignement: &"<<dgl<<"&\t"<<dg0<<"\\"<<"\\ "<<endl;
	cout<<"gen values assignement: "<<sqrt((sumFLUP * sumFLUP)+pow(dgl,2))<<"\t"<<sqrt((sumF0UP * sumF0UP)+pow(dg0,2))<<endl;
//MC stats
	double f0new = 0.002;
	double flnew = 0.002;
    cout<<"MC stats              : "<<sqrt((sumFLUP * sumFLUP)+pow(flnew,2))<<"\t"<<sqrt((sumF0UP * sumF0UP)+pow(f0new,2))<<endl;
}


