#include <iostream>
#include <string>
#include "TMath.h"
#include "TH1.h"
using namespace std;
#define NSM  305295
#define N0100  375847
#define Nunphys  277183
#define SigmaSM  9.42
#define mtop  172.5
#define MW  80.39

struct Coefficients{
	double m;
	double n;
	double k;
};

double q(double mt, double mw, double mb){
	return (1./(2*mt))*sqrt((pow(mt, 4)+pow(mw, 4)+pow(mb, 4))-(2*pow((mt*mw),2)+2*pow((mt*mb),2)+2*pow((mb*mw),2)));
}

double Gamma(double * x, double * par){
	/*
	 * x[0]: VL
	 * x[1]: VR
	 * x[2]: gL
	 * x[3]: gR

	 * par[0]: mt
	 * par[1]: mW
	 * par[2]: mb
	 */
	double xb = (double)par[2]/(double)par[0];
	double xW = (double)par[1]/(double)par[0];
	double xW2 = pow(xW,2);
	double xb2 = pow(xb,2);
	double xW4 = pow(xW2,2);
	double xb4 = pow(xb2,2);
	//double q = q(par[0],par[1],par[2]);
	double t1 = (pow(x[0],2)+pow(x[1],2))*(1 + xW2 - 2*xb2 - 2*xW4 + xW2*xb2 + xb4);
	double t2 = (12 * xW2 * xb * x[0] * x[1] );
    double t3 =  2 * (pow(x[2],2)+pow(x[3],2)) * (1 - (xW2/2.) - 2 * xb2 - (xW4/2.) - (xW2 * xb2/2.) + xb4);
	double t4 = (12 * xW2 * xb * x[2] * x[3] ) ;
	double t5 = 6 * xW * (x[0]*x[3]+x[1]*x[2]) * (1- xW2 - xb2);
	double t6 = 6 * xW * (x[0]*x[2]+x[1]*x[3]) * (1+ xW2 - xb2);
	return(pow(xW2,-1)*(t1 - t2 + t3 -t4 -t5 + t6));
}
double GammaZero(double * x, double * par){
	/*
	 * x[0]: VL
	 * x[1]: VR
	 * x[2]: gL
	 * x[3]: gR

	 * par[0]: mt
	 * par[1]: mW
	 * par[2]: mb
	 */
	double xb = (double)par[2]/(double)par[0];
	double xW = (double)par[1]/(double)par[0];
	double xW2 = pow(xW,2);
	double xb2 = pow(xb,2);
//	double xW4 = pow(xW2,2);
	double xb4 = pow(xb2,2);
	//double q = q(par[0],par[1],par[2]);
	double t1 = pow(xW2,-1) * (pow(x[0],2) + pow(x[1],2))*(1 - xW2 - 2*xb2 - xW2*xb2 + xb4);
	double t2 = 4 * xb * x[0]*x[1];
    double t3 =  (pow(x[2],2)+pow(x[3],2)) * (1 - xW2 + xb2);
	double t4 = 4 * xb * x[2]*x[3];
	double t5 = (2 * pow(xW,-1) * (x[0]*x[3] + x[1]*x[2]) * (1 - xW2 - xb2) ) ;
	double t6 = 2 * pow(xW,-1) * xb * (x[1]*x[3] + x[0]*x[2]) * (1 + xW2 - xb2);
	return (t1 - t2 + t3 - t4 -t5 + t6);
}

double commonTerm(double * x, double * par){
	/*
	 * x[0]: VL
	 * x[1]: VR
	 * x[2]: gL
	 * x[3]: gR

	 * par[0]: mt
	 * par[1]: mW
	 * par[2]: mb
	 */
	double xb = (double)par[2]/(double)par[0];
	double xW = (double)par[1]/(double)par[0];
	double xW2 = pow(xW,2);
	double xb2 = pow(xb,2);
	double xW4 = pow(xW2,2);
	double xb4 = pow(xb2,2);
	double Q = q(par[0],par[1],par[2]);
	double coeff1 = 0.5*pow(Q,-1)*par[0]*pow(xW2,-1);
	double coeff2 = 1 - 2*xW2 - 2*xb2 + xW4 -2*xW2*xb2 + xb4 ;
	double t1 = -1 * xW2 * (pow(x[0],2) - pow(x[1],2));
	double t2 = (pow(x[2],2) - pow(x[3],2)) * (1- xb2);
	double t3 = 2*xW*(x[0]*x[3]-x[1]*x[2]);
	double t4 = 2*xW*xb*(x[0]*x[1]-x[3]*x[2]);
	return (coeff1 * coeff2 * (t1 + t2 + t3 + t4));
}

double GammaT(double * x, double * par){
	/*
	 * x[0]: VL
	 * x[1]: VR
	 * x[2]: gL
	 * x[3]: gR

	 * par[0]: mt
	 * par[1]: mW
	 * par[2]: mb
	 */
	double xb = (double)par[2]/(double)par[0];
	double xW = (double)par[1]/(double)par[0];
	double xW2 = pow(xW,2);
	double xb2 = pow(xb,2);
//	double xW4 = pow(xW2,2);
	double xb4 = pow(xb2,2);
	//double q = q(par[0],par[1],par[2]);
	double t1 = (pow(x[0],2) + pow(x[1],2)) * (1 - xW2 + xb2);
	double t2 = 4 * xb * x[0]*x[1];
	double t3 = pow(xW2,-1) * (pow(x[2],2) + pow(x[3],2))*(1 - xW2 - 2*xb2 - xW2*xb2 + xb4);
	double t4 = 4 * xb * x[2]*x[3];
	double t5 = 2 * pow(xW,-1) * (x[0]*x[3] + x[1]*x[2]) * (1 - xW2 - xb2)  ;
	double t6 = 2 * pow(xW,-1) * xb * (x[1]*x[3] + x[0]*x[2]) * (1 + xW2 - xb2);
	return (t1 - t2 + t3 - t4 -t5 + t6);
}

double GammaL(double * x, double * par){
	/*
	 * x[0]: VL
	 * x[1]: VR
	 * x[2]: gL
	 * x[3]: gR

	 * par[0]: mt
	 * par[1]: mW
	 * par[2]: mb
	 */
	
	double T = GammaT(x,par);
	double C = commonTerm(x,par);
	return T-C;
}
double GammaR(double * x, double * par){
	/*
	 * x[0]: VL
	 * x[1]: VR
	 * x[2]: gL
	 * x[3]: gR

	 * par[0]: mt
	 * par[1]: mW
	 * par[2]: mb
	 */
	
	double T = GammaT(x,par);
	double C = commonTerm(x,par);
	return T+C;
}
double FZero(double * x, double * par){
	double G0 = GammaZero(x,par);
	double G = Gamma(x,par);
	return G0/G;
}
double FNeg(double * x, double * par){
	double G = Gamma(x,par);
	double GL = GammaL(x,par);
	return GL/G;
}
double FR(double * x, double * par){
	double G = Gamma(x,par);
	double GR = GammaR(x,par);
	return GR/G;
}


Coefficients GetFs(double VL, double VR, double gL, double gR, double mt = 175., double mW = 80.39, double mb = 4.8){
	double par[3] = {mt, mW, mb};
	double x[4] = {VL,VR,gL,gR};
        Coefficients ceof;
        ceof.m = FNeg(x,par);
        ceof.n = FZero(x,par);
        ceof.k = FR(x,par);
	/*cout<<"F0 = "<<FZero(x,par)<<endl;
	cout<<"FL = "<<FL(x,par)<<endl;
	cout<<"FR = "<<FR(x,par)<<endl;*/
        return ceof;
}

double MojtabaWidth(double VL, double VR, double gL, double gR, double mt = 175., double mW = 80.39/*, double mb = 4.8*/){
	double r = mt/mW;
	const double Gf = 1.166364*pow(10,-5);
	double massTerm = mt*pow(mW,2);
	const double OtherCoeffs = pow((8*sqrt(2)*TMath::Pi()),-1);
	double r2 = pow(r,2);
	double r4 = pow(r,4);
	double coeff1 = Gf * pow((r2-1),2) * pow(r4,-1) * massTerm * OtherCoeffs;
	double t1 = (r2+2)*(pow(VL,2)+pow(VR,2));
	double t2 = (2*r2 + 1)*(pow(gL,2)+pow(gR,2));
	double t3 = 6*r*(VL*gR+VR*gL);
	return (coeff1*(t1 + t2 + t3));
}

Coefficients VLVRCoeffs(double VL, double VR, double cf = 1, double mt = 175., double mW = 80.39/*, double mb = 4.8*/){
	const double VlVRConst = 1.49 * cf;
	Coefficients ret;
	ret.m = pow(VL,4)*pow(MojtabaWidth(VL,VR,0,0,mt,mW),-1)*VlVRConst;
	ret.n = pow(VL,2)*pow(VR,2)*pow(MojtabaWidth(VL,VR,0,0,mt,mW),-1)*VlVRConst;
	ret.k = pow(VR,4)*pow(MojtabaWidth(VL,VR,0,0,mt,mW),-1)*VlVRConst;
	return ret;
}
Coefficients Weights(double VL, double VR, double SF = 1, double mt = mtop, double mW = MW) {
    Coefficients coeffs = VLVRCoeffs(VL, VR, SF, mt, mW);
    Coefficients ret;
    ret.m = coeffs.m * SigmaSM / NSM;
    ret.n = coeffs.n * SigmaSM / Nunphys;
    ret.k = coeffs.k * SigmaSM / N0100;
    return ret;
}