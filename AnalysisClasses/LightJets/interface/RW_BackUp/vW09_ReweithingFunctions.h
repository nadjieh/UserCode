/* 
 * File:   ReweithingFunctions.h
 * Author: ajafari
 *
 * Created on April 28, 2010, 1:10 PM
 */

using namespace std;
#ifndef _REWEITHINGFUNCTIONS_H
#define	_REWEITHINGFUNCTIONS_H

#include <cmath>
#include <vector>
#include <iostream>
#include <TMath.h>
double PolyNomialFunctions(double weight, double x, std::vector<double> coefficients){
    uint polyNomDegree = coefficients.size() - 1;
    double res = 0.;
    for(uint i = 0; i <= polyNomDegree; i++){
        double xpower = 1;
        for(uint j = 0; j<i; j++){
            xpower *= x;
        }
        res += (coefficients[i] * xpower);
    }
    return (weight*res);
}
double power(int n, double x){
    double res = 1;
    for(int i = 0; i < n; i++){
	res *= x;
    }
    return res;
}

double PolyNomialFunctions2D(double weight, double x, double y, std::vector<double> par){
    double res = par[0] + par[1] * power(1,x) + par[2] * power(1,y) + par[3] * power(2,x) + par[4] * power(2,y) + par[5] * x * y;
    res += par[6] * power(3,x) + par[7] * power(2,x) * y + par[8] * power(2,y) * x + par[9] * power(3,y) + par[10] * power(4,x);
    res += par[11] * power(3,x) * y + par[12] * power(2,x) * power(2,y) + par[13] * power(3,y) * x + par[14] * power(4,y) + par[15] * power(5,x);
    res += par[16] * power(4,x) * y + par[17] * power(3,x) * power(2,y) + par[18] * power(3,y) * power(2,x) + par[19] * power(4,y) * x + par[20] * power(5,y);
    return (weight*res);
}


double expFunction(double weight, double x, double constant, double powerCoeff){
    return(weight*exp(constant + (x*powerCoeff)));
}
//for ONlySignal this weighting was not needed
double weightAfterPtReweighting(double Pt, double W0,std::string mode , bool includeQCD, int code = 0){// Only act on the light jets on right hand side
if(mode == "All_LoverR_Normal"){
        if(!includeQCD)
        {   if(code == 1)
                return(expFunction(W0,Pt,1.277,-0.01337));
            else if(code == 2)
                return(expFunction(W0,Pt,1.261,-0.01322));
            else if(code == 4)
                return(35.32*W0*TMath::Landau(Pt, -25.52,19.22 ));
            else if(code == 5)
                return(31.98*W0*TMath::Landau(Pt, -22.36,19.91 ));
            else if(code == 6)
                return(36.18*W0*TMath::Landau(Pt, -26.65,19.12 ));
            else if(code == 7)
                return(533.4*W0*TMath::Gaus(Pt,-853.2,267.9));
            else if(code == 8)
                return(7061*W0*TMath::Gaus(Pt,-1254,320.7));
            else if(code == 9)
                return(expFunction(W0,Pt,1.201,-0.01279));
            else if(code == 10)
                return(expFunction(W0,Pt,1.192,-0.0127));
            else if(code == 11)
                return(30.23*W0*TMath::Landau(Pt, -28.31,21.54 ));
            else if(code == 12)
                return(19.17*W0*TMath::Landau(Pt, -7.642,24.62 ));
            else if(code == 13)
                return(expFunction(W0,Pt,1.606,-0.01799));
            else if(code == 14)
                return(expFunction(W0,Pt,1.602,-0.01795));
            else if(code == 15)
                return(17.95*W0*TMath::Landau(Pt, 20.41,17.44 ));
            else if(code == 16)
                return(16.22*W0*TMath::Landau(Pt, 24.68,17.81 ));
            else if(code == 17)
                return(expFunction(W0,Pt,1.346,-0.01374));
            else if(code == 18)
                return(55.26*W0*TMath::Landau(Pt, -34.53,16.22 ));
            else if(code == 19){
//                cout<<"old W: "<<W0<<endl;
//                cout<<"new W: "<<expFunction(W0,Pt,1.314,-0.01399)<<endl;
                return(expFunction(W0,Pt,1.314,-0.01399));
            }
            else if(code == 20)
                return(11.01*W0*TMath::Landau(Pt, 38.65,23.1 ));
            else if(code == 21)
                return(11*W0*TMath::Landau(Pt, 38.73,23.09 ));
            else if(code == 22)
                return(49.27*W0*TMath::Landau(Pt, -33.53,17.24 ));
            else if(code == 23)
                return(53.2*W0*TMath::Landau(Pt, -35.65,53.2 ));
            else if(code == 24)
                return(expFunction(W0,Pt,1.329,-0.01351));
            else if(code == 25)
                return(expFunction(W0,Pt,1.071,-0.01222));
            else if(code == 26)
                return(27.64*W0*TMath::Landau(Pt, -37.1,23.38 ));
            else if(code == 27)
                return(expFunction(W0,Pt,1.324,-0.01438));
            else if(code == 28)
                return(17.73*W0*TMath::Landau(Pt, 5.666,22.21 ));
            else if(code == 29)
                return(17.73*W0*TMath::Landau(Pt, 5.676,22.21 ));
            else
                return (W0);
        }
        else
            return (W0);
    }
    else
        return W0;
}

double weightWith2D(std::string smooth, double eta, double pt, double W0){
  return(W0);
}
double weightAfterEtaReweighting(double Eta, double W0,std::string mode , bool includeQCD, int code = 0){// Only act on the light jets on right hand side
    if(mode == "NB_LoverR"){
        return (expFunction(W0,Eta,2.27,-0.01976)); //~/scratch0/CMSSW_3_1_4/src/AnalysisClasses/LightJets/macro/MC/Luminosity100pb-1/NB_PtWeighting.pdf #12
    }
    else if(mode == "NB_LoverR_Normal"){
        return (expFunction(W0,Eta,1.791,-0.01976)); //~/scratch0/CMSSW_3_1_4/src/AnalysisClasses/LightJets/macro/MC/Luminosity100pb-1/NB_PtWeighting.pdf #12
    }
    else if(mode == "All_LoverR"){
        if(!includeQCD)
            return (expFunction(W0,Eta,2.206,-0.01339)); //~/scratch0/CMSSW_3_1_4/src/AnalysisClasses/LightJets/macro/MC/Luminosity100pb-1/NBB_EtaWeighting.pdf #10
                                                         //~/scratch0/CMSSW_3_1_4/src/AnalysisClasses/LightJets/macro/DataLike/Luminosity100pb-1/LepBCand_PtWeight.pdf #10
        else
            return (W0);
    }
    else if(mode == "All_LoverR_Normal"){
        if(!includeQCD){
            std::vector<double> coeff_;
            if(code == 2){
                coeff_.clear();
                coeff_.push_back(3.984);
                coeff_.push_back(-2.687);
                coeff_.push_back(-1.765);
                coeff_.push_back(8.586);
                coeff_.push_back(-8.453);
                coeff_.push_back(3.233);
                coeff_.push_back(-0.4303);
                return(PolyNomialFunctions(W0,fabs(Eta),coeff_));
            }
            else if(code == 3){
                coeff_.clear();
                coeff_.push_back(3.066);
                coeff_.push_back(0.7081);
                coeff_.push_back(-1.723);
                coeff_.push_back(0.04209);
                return(PolyNomialFunctions(W0,fabs(Eta),coeff_));
            }
            else if(code == 4){
                coeff_.clear();
                coeff_.push_back(3.776);
                coeff_.push_back(-1.54);
                coeff_.push_back(0.07662);
                return(PolyNomialFunctions(W0,fabs(Eta),coeff_));
            }
            else if(code == 5){
                coeff_.clear();
                coeff_.push_back(3.634);
                coeff_.push_back(-1.311);
                return(PolyNomialFunctions(W0,fabs(Eta),coeff_));
            }
            else if(code == 6){
                return(W0*3.203*exp(-0.5*((fabs(Eta)-0.06988)/1.253)*((fabs(Eta)-0.06988)/1.253)));
            }
            else if(code == 7){
                coeff_.clear();
                coeff_.push_back(9.222);
                coeff_.push_back(-34.74);
                coeff_.push_back(96.63);
                coeff_.push_back(-131.4);
                coeff_.push_back(91.31);
                coeff_.push_back(-31.5);
                coeff_.push_back(4.271);
                return(PolyNomialFunctions(W0,fabs(Eta),coeff_));
            }
            else if(code == 8){
                coeff_.clear();
                coeff_.push_back(6.717);
                coeff_.push_back(-8.284);
                coeff_.push_back(9.782);
                coeff_.push_back(-5.046);
                coeff_.push_back(0.4179);
                coeff_.push_back(0.1792);
                return(PolyNomialFunctions(W0,fabs(Eta),coeff_));
            }
            else if(code == 9){
                coeff_.clear();
                coeff_.push_back(6.862);
                coeff_.push_back(-9.441);
                coeff_.push_back(12.52);
                coeff_.push_back(-7.719);
                coeff_.push_back(1.564);
                return(PolyNomialFunctions(W0,fabs(Eta),coeff_));
            }
            else if(code == 10){
                coeff_.clear();
                coeff_.push_back(4.8);
                coeff_.push_back(1.13);
                coeff_.push_back(-2.873);
                coeff_.push_back(0.7152);
                return(PolyNomialFunctions(W0,fabs(Eta),coeff_));
            }
            else if(code == 11){
                coeff_.clear();
                coeff_.push_back(6.002);
                coeff_.push_back(-2.678);
                coeff_.push_back(0.2161);
                return(PolyNomialFunctions(W0,fabs(Eta),coeff_));
            }
            else if(code == 12){
                coeff_.clear();
                coeff_.push_back(5.595);
                coeff_.push_back(-2.031);
                return(PolyNomialFunctions(W0,fabs(Eta),coeff_));
            }
            else if(code == 13){
                return(W0*5.161*exp(-0.5*((fabs(Eta)-0.0577)/1.302)*((fabs(Eta)-0.0577)/1.302)));
            }
            else if(code == 14){
                return(W0*4.572*exp(-0.5*((fabs(Eta)-0.261)/1.158)*((fabs(Eta)-0.261)/1.158)));
            }
        }
        else
            return (W0);
    }
    else if(mode == "CS_LoverR"){
            return (expFunction(W0,Eta,2.658,-0.0218)); //~/scratch0/CMSSW_3_1_4/src/AnalysisClasses/LightJets/macro/DataLike/Luminosity100pb-1/LightBCand_PtWeight.pdf #11
    }
    else if(mode == "CS_LoverR_Normal"){
            return (expFunction(W0,Eta,1.602,-0.0218)); //~/scratch0/CMSSW_3_1_4/src/AnalysisClasses/LightJets/macro/DataLike/Luminosity100pb-1/LightBCand_PtWeight.pdf #11
    }
    return W0;
}
double stupidWeighter(double Pt, double W0){
    if(Pt>26. && Pt <= 28.)
            return(W0 * 3.37191);
    if(Pt>28. && Pt <= 30.)
            return(W0 * 3.17217);
    if(Pt>30. && Pt <= 32.)
            return(W0 * 3.56245);
    if(Pt>32. && Pt <= 34.)
            return(W0 * 1.79211);
    if(Pt>34. && Pt <= 36.)
            return(W0 * 5.97949);
    if(Pt>36. && Pt <= 38.)
            return(W0 * 4.37271);
    if(Pt>38. && Pt <= 40.)
            return(W0 * 1.97724);
    if(Pt>40. && Pt <= 42.)
            return(W0 * 2.20677);
    if(Pt>42. && Pt <= 44.)
            return(W0 * 2.88647);
    if(Pt>44. && Pt <= 46.)
            return(W0 * 3.82226);
    if(Pt>46. && Pt <= 48.)
            return(W0 * 1.64669);
    if(Pt>48. && Pt <= 50.)
            return(W0 * 2.16624);
    if(Pt>50. && Pt <= 52.)
            return(W0 * 2.10225);
    if(Pt>52. && Pt <= 54.)
            return(W0 * 2.29062);
    if(Pt>54. && Pt <= 56.)
            return(W0 * 2.49368);
    if(Pt>56. && Pt <= 58.)
            return(W0 * 1.61835);
    if(Pt>58. && Pt <= 60.)
            return(W0 * 1.5758);
    if(Pt>60. && Pt <= 62.)
            return(W0 * 1.36425);
    if(Pt>62. && Pt <= 64.)
            return(W0 * 1.45247);
    if(Pt>64. && Pt <= 66.)
            return(W0 * 1.67052);
    if(Pt>66. && Pt <= 68.)
            return(W0 * 1.41909);
    if(Pt>68. && Pt <= 70.)
            return(W0 * 1.34598);
    if(Pt>70. && Pt <= 72.)
            return(W0 * 1.13364);
    if(Pt>72. && Pt <= 74.)
            return(W0 * 1.25978);
    if(Pt>74. && Pt <= 76.)
            return(W0 * 1.36849);
    if(Pt>76. && Pt <= 78.)
            return(W0 * 1.26803);
    if(Pt>78. && Pt <= 80.)
            return(W0 * 1.25958);
    if(Pt>80. && Pt <= 82.)
            return(W0 * 1.27831);
    if(Pt>82. && Pt <= 84.)
            return(W0 * 1.18637);
    if(Pt>84. && Pt <= 86.)
            return(W0 * 1.47366);
    if(Pt>86. && Pt <= 88.)
            return(W0 * 1.14275);
    if(Pt>88. && Pt <= 90.)
            return(W0 * 1.2233);
    if(Pt>90. && Pt <= 92.)
            return(W0 * 1.13442);
    if(Pt>92. && Pt <= 94.)
            return(W0 * 1.12923);
    if(Pt>94. && Pt <= 96.)
            return(W0 * 1.09484);
    if(Pt>96. && Pt <= 98.)
            return(W0 * 1.03217);
    if(Pt>98. && Pt <= 100.)
            return(W0 * 0.903118);
    if(Pt>100. && Pt <= 102.)
            return(W0 * 0.881307);
    if(Pt>102. && Pt <= 104.)
            return(W0 * 0.874402);
    if(Pt>104. && Pt <= 106.)
            return(W0 * 1.03995);
    if(Pt>106. && Pt <= 108.)
            return(W0 * 1.25523);
    if(Pt>108. && Pt <= 110.)
            return(W0 * 1.07054);
    if(Pt>110. && Pt <= 112.)
            return(W0 * 0.675101);
    if(Pt>112. && Pt <= 114.)
            return(W0 * 1.23954);
    if(Pt>114. && Pt <= 116.)
            return(W0 * 1.02866);
    if(Pt>116. && Pt <= 118.)
            return(W0 * 0.545374);
    if(Pt>118. && Pt <= 120.)
            return(W0 * 0.759216);
    if(Pt>120. && Pt <= 122.)
            return(W0 * 0.678844);
    if(Pt>122. && Pt <= 124.)
            return(W0 * 0.621471);
    if(Pt>124. && Pt <= 126.)
            return(W0 * 0.509826);
    if(Pt>126. && Pt <= 128.)
            return(W0 * 0.942781);
    if(Pt>128. && Pt <= 130.)
            return(W0 * 0.55088);
    if(Pt>130. && Pt <= 132.)
            return(W0 * 0.568614);
    if(Pt>132. && Pt <= 134.)
            return(W0 * 0.616548);
    if(Pt>134. && Pt <= 136.)
            return(W0 * 0.686621);
    if(Pt>136. && Pt <= 138.)
            return(W0 * 0.655079);
    if(Pt>138. && Pt <= 140.)
            return(W0 * 0.503708);
    if(Pt>140. && Pt <= 142.)
            return(W0 * 0.774329);
    if(Pt>142. && Pt <= 144.)
            return(W0 * 0.578995);
    if(Pt>144. && Pt <= 146.)
            return(W0 * 0.476994);
    if(Pt>146. && Pt <= 148.)
            return(W0 * 0.644449);
    if(Pt>148. && Pt <= 150.)
            return(W0 * 0.874138);
    if(Pt>150. && Pt <= 152.)
            return(W0 * 0.609766);
    if(Pt>152. && Pt <= 154.)
            return(W0 * 0.413367);
    if(Pt>154. && Pt <= 156.)
            return(W0 * 0.436523);
    if(Pt>156. && Pt <= 158.)
            return(W0 * 0.360203);
    if(Pt>158. && Pt <= 160.)
            return(W0 * 0.293428);
    if(Pt>160. && Pt <= 162.)
            return(W0 * 0.45681);
    if(Pt>162. && Pt <= 164.)
            return(W0 * 0.555306);
    if(Pt>164. && Pt <= 166.)
            return(W0 * 0.626862);
    if(Pt>166. && Pt <= 168.)
            return(W0 * 0.315336);
    if(Pt>168. && Pt <= 170.)
            return(W0 * 0.365657);
    if(Pt>170. && Pt <= 172.)
            return(W0 * 0.503017);
    if(Pt>172. && Pt <= 174.)
            return(W0 * 0.418733);
    if(Pt>174. && Pt <= 176.)
            return(W0 * 0.222952);
    if(Pt>176. && Pt <= 178.)
            return(W0 * 0.381239);
    if(Pt>178. && Pt <= 180.)
            return(W0 * 0.318989);
    if(Pt>180. && Pt <= 182.)
            return(W0 * 0.453851);
    if(Pt>182. && Pt <= 184.)
            return(W0 * 0.452568);
    if(Pt>184. && Pt <= 186.)
            return(W0 * 0.487303);
    if(Pt>186. && Pt <= 188.)
            return(W0 * 0.316907);
    if(Pt>188. && Pt <= 190.)
            return(W0 * 0.325034);
    if(Pt>190. && Pt <= 192.)
            return(W0 * 0.394949);
    if(Pt>192. && Pt <= 194.)
            return(W0 * 0.496529);
    if(Pt>194. && Pt <= 196.)
            return(W0 * 0.298501);
    if(Pt>196. && Pt <= 198.)
            return(W0 * 0.38837);
    if(Pt>198. && Pt <= 200.)
            return(W0 * 0.283977);
    if(Pt>200. && Pt <= 202.)
            return(W0 * 0.406558);
    if(Pt>202. && Pt <= 204.)
            return(W0 * 0.222294);
    if(Pt>204. && Pt <= 206.)
            return(W0 * 0.433985);
    if(Pt>206. && Pt <= 208.)
            return(W0 * 0.171248);
    if(Pt>208. && Pt <= 210.)
            return(W0 * 0.394347);
    if(Pt>210. && Pt <= 212.)
            return(W0 * 0.299356);
    if(Pt>212. && Pt <= 214.)
            return(W0 * 0.170482);
    if(Pt>214. && Pt <= 216.)
            return(W0 * 0.537575);
    if(Pt>216. && Pt <= 218.)
            return(W0 * 0.256941);
    if(Pt>218. && Pt <= 220.)
            return(W0 * 0.344262);
    if(Pt>220. && Pt <= 222.)
            return(W0 * 0.153168);
    if(Pt>222. && Pt <= 224.)
            return(W0 * 0.182312);
    if(Pt>224. && Pt <= 226.)
            return(W0 * 0.224353);
    if(Pt>226. && Pt <= 228.)
            return(W0 * 0.239286);
    if(Pt>228. && Pt <= 230.)
            return(W0 * 0.1861);
    if(Pt>230. && Pt <= 232.)
            return(W0 * 0.284845);
    if(Pt>232. && Pt <= 234.)
            return(W0 * 0.416206);
    if(Pt>234. && Pt <= 236.)
            return(W0 * 0.265207);
    if(Pt>236. && Pt <= 238.)
            return(W0 * 0.192219);
    if(Pt>238. && Pt <= 240.)
            return(W0 * 0.274594);
    if(Pt>240. && Pt <= 242.)
            return(W0 * 0.1146);
    if(Pt>242. && Pt <= 244.)
            return(W0 * 0.275746);
    if(Pt>244. && Pt <= 246.)
            return(W0 * 0.180017);
    if(Pt>246. && Pt <= 248.)
            return(W0 * 0.36452);
    if(Pt>248. && Pt <= 250.)
            return(W0 * 0.161099);
    if(Pt>250. && Pt <= 252.)
            return(W0 * 0.0534401);
    if(Pt>252. && Pt <= 254.)
            return(W0 * 0.217346);
    if(Pt>254. && Pt <= 256.)
            return(W0 * 0.13801);
    if(Pt>256. && Pt <= 258.)
            return(W0 * 0.372189);
    if(Pt>258. && Pt <= 260.)
            return(W0 * 0.250249);
    if(Pt>260. && Pt <= 262.)
            return(W0 * 0.213865);
    if(Pt>262. && Pt <= 264.)
            return(W0 * 0.123222);
    if(Pt>264. && Pt <= 266.)
            return(W0 * 0.106198);
    if(Pt>266. && Pt <= 268.)
            return(W0 * 0.205477);
    if(Pt>268. && Pt <= 270.)
            return(W0 * 0.195545);
    if(Pt>270. && Pt <= 272.)
            return(W0 * 0.279192);
    if(Pt>272. && Pt <= 274.)
            return(W0 * 0.062867);
    if(Pt>274. && Pt <= 276.)
            return(W0 * 0.11102);
    if(Pt>276. && Pt <= 278.)
            return(W0 * 1.04221);
    if(Pt>278. && Pt <= 280.)
            return(W0 * 0.170187);
    if(Pt>280. && Pt <= 282.)
            return(W0 * 0.332263);
    if(Pt>282. && Pt <= 284.)
            return(W0 * 0.106027);
    if(Pt>284. && Pt <= 286.)
            return(W0 * 0.369676);
    if(Pt>286. && Pt <= 288.)
            return(W0 * 0.600835);
    if(Pt>288. && Pt <= 290.)
            return(W0 * 0.632859);
    if(Pt>290. && Pt <= 292.)
            return(W0 * 0.65123);
    if(Pt>292. && Pt <= 294.)
            return(W0 * 0.57182);
    if(Pt>294. && Pt <= 296.)
            return(W0 * 0.211179);
    if(Pt>296. && Pt <= 298.)
            return(W0 * 0.76698);
    if(Pt>298. && Pt <= 300.)
            return(W0 * 0.209726);
    if(Pt>300. && Pt <= 302.)
            return(W0 * 0.215173);
    if(Pt>302. && Pt <= 304.)
            return(W0 * 0.304719);
    if(Pt>304. && Pt <= 306.)
            return(W0 * 0.332964);
    if(Pt>306. && Pt <= 308.)
            return(W0 * 0.238939);
    if(Pt>308. && Pt <= 310.)
            return(W0 * 0.310838);
    if(Pt>310. && Pt <= 312.)
            return(W0 * 0.253595);
    if(Pt>312. && Pt <= 314.)
            return(W0 * 0.0918853);
    if(Pt>314. && Pt <= 316.)
            return(W0 * 1.07387);
    if(Pt>316. && Pt <= 318.)
            return(W0 * 0.486212);
    if(Pt>318. && Pt <= 320.)
            return(W0 * 0);
    if(Pt>320. && Pt <= 322.)
            return(W0 * 0.0762036);
    if(Pt>322. && Pt <= 324.)
            return(W0 * 0.291207);
    if(Pt>324. && Pt <= 326.)
            return(W0 * 0.141637);
    if(Pt>326. && Pt <= 328.)
            return(W0 * 0.192053);
    if(Pt>328. && Pt <= 330.)
            return(W0 * 0);
    if(Pt>330. && Pt <= 332.)
            return(W0 * 0.356635);
    if(Pt>332. && Pt <= 334.)
            return(W0 * 0.0165978);
    if(Pt>334. && Pt <= 336.)
            return(W0 * 0.059263);
    if(Pt>336. && Pt <= 338.)
            return(W0 * 0.118295);
    if(Pt>338. && Pt <= 340.)
            return(W0 * 0.210476);
    if(Pt>340. && Pt <= 342.)
            return(W0 * 0.673741);
    if(Pt>342. && Pt <= 344.)
            return(W0 * 0);
    if(Pt>344. && Pt <= 346.)
            return(W0 * 0.287082);
    if(Pt>346. && Pt <= 348.)
            return(W0 * 0.0928017);
    if(Pt>348. && Pt <= 350.)
            return(W0 * 0.098576);
    if(Pt>350. && Pt <= 352.)
            return(W0 * 0.260469);
    if(Pt>352. && Pt <= 354.)
            return(W0 * 0.104188);
    if(Pt>354. && Pt <= 356.)
            return(W0 * 0.0290279);
    if(Pt>356. && Pt <= 358.)
            return(W0 * 0.0471317);
    if(Pt>358. && Pt <= 360.)
            return(W0 * 0.606403);
    if(Pt>360. && Pt <= 362.)
            return(W0 * 0);
    if(Pt>362. && Pt <= 364.)
            return(W0 * 0);
    if(Pt>364. && Pt <= 366.)
            return(W0 * 0.000739569);
    if(Pt>366. && Pt <= 368.)
            return(W0 * 0.0929438);
    if(Pt>368. && Pt <= 370.)
            return(W0 * 0.0477716);
    if(Pt>370. && Pt <= 372.)
            return(W0 * 0);
    if(Pt>372. && Pt <= 374.)
            return(W0 * 0);
    if(Pt>374. && Pt <= 376.)
            return(W0 * 0.287082);
    if(Pt>376. && Pt <= 378.)
            return(W0 * 0);
    if(Pt>378. && Pt <= 380.)
            return(W0 * 30.3322);
    if(Pt>380. && Pt <= 382.)
            return(W0 * 0.861246);
    if(Pt>382. && Pt <= 384.)
            return(W0 * 0);
    if(Pt>384. && Pt <= 386.)
            return(W0 * 0.142865);
    if(Pt>386. && Pt <= 388.)
            return(W0 * 0.0904856);
    if(Pt>388. && Pt <= 390.)
            return(W0 * 0);
    if(Pt>390. && Pt <= 392.)
            return(W0 * 0);
    if(Pt>392. && Pt <= 394.)
            return(W0 * 0);
    if(Pt>394. && Pt <= 396.)
            return(W0 * 0.0402423);
    if(Pt>396. && Pt <= 398.)
            return(W0 * 0);
    if(Pt>398. && Pt <= 400.)
            return(W0 * 0.430623);
    else
        return W0;

}
double stupidEtaWeighter(double Eta, double W0){
        if((fabs(Eta)>=0) && (fabs(Eta)<0.1))
                return(W0*1.77443);
        if((fabs(Eta)>=0.1) && (fabs(Eta)<0.2))
                return(W0*1.79258);
        if((fabs(Eta)>=0.2) && (fabs(Eta)<0.3))
                return(W0*2.22315);
        if((fabs(Eta)>=0.3) && (fabs(Eta)<0.4))
                return(W0*1.77608);
        if((fabs(Eta)>=0.4) && (fabs(Eta)<0.5))
                return(W0*1.37785);
        if((fabs(Eta)>=0.5) && (fabs(Eta)<0.6))
                return(W0*1.29945);
        if((fabs(Eta)>=0.6) && (fabs(Eta)<0.7))
                return(W0*1.45487);
        if((fabs(Eta)>=0.7) && (fabs(Eta)<0.8))
                return(W0*1.11566);
        if((fabs(Eta)>=0.8) && (fabs(Eta)<0.9))
                return(W0*1.54609);
        if((fabs(Eta)>=0.9) && (fabs(Eta)<1))
                return(W0*1.5884);
        if((fabs(Eta)>=1) && (fabs(Eta)<1.1))
                return(W0*1.38452);
        if((fabs(Eta)>=1.1) && (fabs(Eta)<1.2))
                return(W0*1.0461);
        if((fabs(Eta)>=1.2) && (fabs(Eta)<1.3))
                return(W0*1.21175);
        if((fabs(Eta)>=1.3) && (fabs(Eta)<1.4))
                return(W0*0.872573);
        if((fabs(Eta)>=1.4) && (fabs(Eta)<1.5))
                return(W0*0.833577);
        if((fabs(Eta)>=1.5) && (fabs(Eta)<1.6))
                return(W0*0.896141);
        if((fabs(Eta)>=1.6) && (fabs(Eta)<1.7))
                return(W0*0.825954);
        if((fabs(Eta)>=1.7) && (fabs(Eta)<1.8))
                return(W0*0.72068);
        if((fabs(Eta)>=1.8) && (fabs(Eta)<1.9))
                return(W0*0.573243);
        if((fabs(Eta)>=1.9) && (fabs(Eta)<2))
                return(W0*0.450822);
        if((fabs(Eta)>=2) && (fabs(Eta)<2.1))
                return(W0*0.390888);
        if((fabs(Eta)>=2.1) && (fabs(Eta)<2.2))
                return(W0*0.40855);
        if((fabs(Eta)>=2.2) && (fabs(Eta)<2.3))
                return(W0*0.38984);
        if((fabs(Eta)>=2.3) && (fabs(Eta)<2.4))
                return(W0*0.360557);
        if((fabs(Eta)>=2.4) && (fabs(Eta)<2.5))
                return(W0*0);
        if((fabs(Eta)>=2.5) && (fabs(Eta)<2.6))
                return(W0*0);
        if((fabs(Eta)>=2.6) && (fabs(Eta)<2.7))
                return(W0*0);
        if((fabs(Eta)>=2.7) && (fabs(Eta)<2.8))
                return(W0*0);
        if((fabs(Eta)>=2.8) && (fabs(Eta)<2.9))
                return(W0*0);
        if((fabs(Eta)>=2.9) && (fabs(Eta)<3))
                return(W0*0);
        else
            return W0;

}


double stupid2D(double W0, double pt, double eta){//LepLight
if(fabs(eta) >= 0 && fabs(eta) < 0.1 ){
	if( pt >= 20 && pt < 40 )
		return(W0 * 0.318092);
	if( pt >= 40 && pt < 60 )
		return(W0 * 0.358756);
	if( pt >= 60 && pt < 80 )
		return(W0 * 0.545966);
	if( pt >= 80 && pt < 100 )
		return(W0 * 0.723075);
	if( pt >= 100 && pt < 120 )
		return(W0 * 1.51712);
	if( pt >= 120 && pt < 140 )
		return(W0 * 1.55657);
	if( pt >= 140 && pt < 160 )
		return(W0 * 2.06543);
	if( pt >= 160 && pt < 180 )
		return(W0 * 6.224);
	if( pt >= 180 && pt < 200 )
		return(W0 * 3.11831);
	if( pt >= 200 && pt < 220 )
		return(W0 * 3.06378);
	if( pt >= 220 && pt < 240 )
		return(W0 * 5.54819);
	if( pt >= 240 && pt < 260 )
		return(W0 * 11.5285);
	if( pt >= 260 && pt < 280 )
		return(W0 * 1.22059);
	if( pt >= 280 && pt < 300 )
		return(W0 * 17.2788);
	if( pt >= 300 && pt < 320 )
		return(W0 * 18.7419);
	if( pt >= 320 && pt < 340 )
		return(W0 * 17.5216);
	if( pt >= 340 && pt < 360 )
		return(W0 * 6.01946);
	if( pt >= 360 && pt < 380 )
		return(W0 * 0);
	if( pt >= 380 && pt < 400 )
		return(W0 * 354.27);
}else if(fabs(eta) >= 0.1 && fabs(eta) < 0.2 ){
	if( pt >= 20 && pt < 40 )
		return(W0 * 0.316686);
	if( pt >= 40 && pt < 60 )
		return(W0 * 0.477804);
	if( pt >= 60 && pt < 80 )
		return(W0 * 0.53932);
	if( pt >= 80 && pt < 100 )
		return(W0 * 0.975066);
	if( pt >= 100 && pt < 120 )
		return(W0 * 1.27061);
	if( pt >= 120 && pt < 140 )
		return(W0 * 2.55576);
	if( pt >= 140 && pt < 160 )
		return(W0 * 2.28775);
	if( pt >= 160 && pt < 180 )
		return(W0 * 1.49223);
	if( pt >= 180 && pt < 200 )
		return(W0 * 3.50702);
	if( pt >= 200 && pt < 220 )
		return(W0 * 1.82499);
	if( pt >= 220 && pt < 240 )
		return(W0 * 11.8231);
	if( pt >= 240 && pt < 260 )
		return(W0 * 8.02158);
	if( pt >= 260 && pt < 280 )
		return(W0 * 4.93897);
	if( pt >= 280 && pt < 300 )
		return(W0 * 21.3716);
	if( pt >= 300 && pt < 320 )
		return(W0 * 21.1728);
	if( pt >= 320 && pt < 340 )
		return(W0 * 8.38287);
	if( pt >= 340 && pt < 360 )
		return(W0 * 18.854);
	if( pt >= 360 && pt < 380 )
		return(W0 * 7.28697);
	if( pt >= 380 && pt < 400 )
		return(W0 * 0);
}else if(fabs(eta) >= 0.2 && fabs(eta) < 0.3 ){
	if( pt >= 20 && pt < 40 )
		return(W0 * 0.606035);
	if( pt >= 40 && pt < 60 )
		return(W0 * 0.341966);
	if( pt >= 60 && pt < 80 )
		return(W0 * 0.403401);
	if( pt >= 80 && pt < 100 )
		return(W0 * 0.654097);
	if( pt >= 100 && pt < 120 )
		return(W0 * 0.843821);
	if( pt >= 120 && pt < 140 )
		return(W0 * 1.81462);
	if( pt >= 140 && pt < 160 )
		return(W0 * 1.12325);
	if( pt >= 160 && pt < 180 )
		return(W0 * 1.79277);
	if( pt >= 180 && pt < 200 )
		return(W0 * 6.38474);
	if( pt >= 200 && pt < 220 )
		return(W0 * 6.22119);
	if( pt >= 220 && pt < 240 )
		return(W0 * 1.58292);
	if( pt >= 240 && pt < 260 )
		return(W0 * 18.4713);
	if( pt >= 260 && pt < 280 )
		return(W0 * 1.08549);
	if( pt >= 280 && pt < 300 )
		return(W0 * 11.8636);
	if( pt >= 300 && pt < 320 )
		return(W0 * 0.531478);
	if( pt >= 320 && pt < 340 )
		return(W0 * 5.69449);
	if( pt >= 340 && pt < 360 )
		return(W0 * 0);
	if( pt >= 360 && pt < 380 )
		return(W0 * 0.233873);
	if( pt >= 380 && pt < 400 )
		return(W0 * 0);
}else if(fabs(eta) >= 0.3 && fabs(eta) < 0.4 ){
	if( pt >= 20 && pt < 40 )
		return(W0 * 0.389074);
	if( pt >= 40 && pt < 60 )
		return(W0 * 0.37889);
	if( pt >= 60 && pt < 80 )
		return(W0 * 0.580337);
	if( pt >= 80 && pt < 100 )
		return(W0 * 0.883995);
	if( pt >= 100 && pt < 120 )
		return(W0 * 1.06698);
	if( pt >= 120 && pt < 140 )
		return(W0 * 1.79298);
	if( pt >= 140 && pt < 160 )
		return(W0 * 1.93049);
	if( pt >= 160 && pt < 180 )
		return(W0 * 2.29079);
	if( pt >= 180 && pt < 200 )
		return(W0 * 2.14879);
	if( pt >= 200 && pt < 220 )
		return(W0 * 2.3754);
	if( pt >= 220 && pt < 240 )
		return(W0 * 15.4242);
	if( pt >= 240 && pt < 260 )
		return(W0 * 1.75027);
	if( pt >= 260 && pt < 280 )
		return(W0 * 7.15813);
	if( pt >= 280 && pt < 300 )
		return(W0 * 8.62701);
	if( pt >= 300 && pt < 320 )
		return(W0 * 3.0885);
	if( pt >= 320 && pt < 340 )
		return(W0 * 3.59396);
	if( pt >= 340 && pt < 360 )
		return(W0 * 5.14751);
	if( pt >= 360 && pt < 380 )
		return(W0 * 0);
	if( pt >= 380 && pt < 400 )
		return(W0 * 0);
}else if(fabs(eta) >= 0.4 && fabs(eta) < 0.5 ){
	if( pt >= 20 && pt < 40 )
		return(W0 * 0.401327);
	if( pt >= 40 && pt < 60 )
		return(W0 * 0.522364);
	if( pt >= 60 && pt < 80 )
		return(W0 * 0.61443);
	if( pt >= 80 && pt < 100 )
		return(W0 * 0.939439);
	if( pt >= 100 && pt < 120 )
		return(W0 * 1.15924);
	if( pt >= 120 && pt < 140 )
		return(W0 * 2.60981);
	if( pt >= 140 && pt < 160 )
		return(W0 * 2.88121);
	if( pt >= 160 && pt < 180 )
		return(W0 * 1.66574);
	if( pt >= 180 && pt < 200 )
		return(W0 * 1.33527);
	if( pt >= 200 && pt < 220 )
		return(W0 * 4.32971);
	if( pt >= 220 && pt < 240 )
		return(W0 * 6.37536);
	if( pt >= 240 && pt < 260 )
		return(W0 * 25.4476);
	if( pt >= 260 && pt < 280 )
		return(W0 * 5.10086);
	if( pt >= 280 && pt < 300 )
		return(W0 * 6.83043);
	if( pt >= 300 && pt < 320 )
		return(W0 * 0.92512);
	if( pt >= 320 && pt < 340 )
		return(W0 * 129.824);
	if( pt >= 340 && pt < 360 )
		return(W0 * 6.05636);
	if( pt >= 360 && pt < 380 )
		return(W0 * 0);
	if( pt >= 380 && pt < 400 )
		return(W0 * 6.04721);
}else if(fabs(eta) >= 0.5 && fabs(eta) < 0.6 ){
	if( pt >= 20 && pt < 40 )
		return(W0 * 0.528617);
	if( pt >= 40 && pt < 60 )
		return(W0 * 0.430308);
	if( pt >= 60 && pt < 80 )
		return(W0 * 0.567643);
	if( pt >= 80 && pt < 100 )
		return(W0 * 0.780122);
	if( pt >= 100 && pt < 120 )
		return(W0 * 1.27111);
	if( pt >= 120 && pt < 140 )
		return(W0 * 1.67944);
	if( pt >= 140 && pt < 160 )
		return(W0 * 2.63034);
	if( pt >= 160 && pt < 180 )
		return(W0 * 2.02331);
	if( pt >= 180 && pt < 200 )
		return(W0 * 5.2675);
	if( pt >= 200 && pt < 220 )
		return(W0 * 2.78489);
	if( pt >= 220 && pt < 240 )
		return(W0 * 5.10555);
	if( pt >= 240 && pt < 260 )
		return(W0 * 11.0557);
	if( pt >= 260 && pt < 280 )
		return(W0 * 31.1576);
	if( pt >= 280 && pt < 300 )
		return(W0 * 64.293);
	if( pt >= 300 && pt < 320 )
		return(W0 * 0);
	if( pt >= 320 && pt < 340 )
		return(W0 * 0);
	if( pt >= 340 && pt < 360 )
		return(W0 * 0.587393);
	if( pt >= 360 && pt < 380 )
		return(W0 * 15.5059);
	if( pt >= 380 && pt < 400 )
		return(W0 * 0);
}else if(fabs(eta) >= 0.6 && fabs(eta) < 0.7 ){
	if( pt >= 20 && pt < 40 )
		return(W0 * 0.591158);
	if( pt >= 40 && pt < 60 )
		return(W0 * 0.488303);
	if( pt >= 60 && pt < 80 )
		return(W0 * 0.627739);
	if( pt >= 80 && pt < 100 )
		return(W0 * 1.13913);
	if( pt >= 100 && pt < 120 )
		return(W0 * 1.69442);
	if( pt >= 120 && pt < 140 )
		return(W0 * 1.95508);
	if( pt >= 140 && pt < 160 )
		return(W0 * 3.12115);
	if( pt >= 160 && pt < 180 )
		return(W0 * 2.32859);
	if( pt >= 180 && pt < 200 )
		return(W0 * 3.75179);
	if( pt >= 200 && pt < 220 )
		return(W0 * 1.74421);
	if( pt >= 220 && pt < 240 )
		return(W0 * 8.49375);
	if( pt >= 240 && pt < 260 )
		return(W0 * 6.93424);
	if( pt >= 260 && pt < 280 )
		return(W0 * 28.0808);
	if( pt >= 280 && pt < 300 )
		return(W0 * 0.379767);
	if( pt >= 300 && pt < 320 )
		return(W0 * 5.92082);
	if( pt >= 320 && pt < 340 )
		return(W0 * 55.4819);
	if( pt >= 340 && pt < 360 )
		return(W0 * 73.1885);
	if( pt >= 360 && pt < 380 )
		return(W0 * 10.7857);
	if( pt >= 380 && pt < 400 )
		return(W0 * 0);
}else if(fabs(eta) >= 0.7 && fabs(eta) < 0.8 ){
	if( pt >= 20 && pt < 40 )
		return(W0 * 0.489059);
	if( pt >= 40 && pt < 60 )
		return(W0 * 0.467886);
	if( pt >= 60 && pt < 80 )
		return(W0 * 0.644896);
	if( pt >= 80 && pt < 100 )
		return(W0 * 0.985631);
	if( pt >= 100 && pt < 120 )
		return(W0 * 1.64032);
	if( pt >= 120 && pt < 140 )
		return(W0 * 1.42949);
	if( pt >= 140 && pt < 160 )
		return(W0 * 2.00806);
	if( pt >= 160 && pt < 180 )
		return(W0 * 6.49942);
	if( pt >= 180 && pt < 200 )
		return(W0 * 2.54786);
	if( pt >= 200 && pt < 220 )
		return(W0 * 7.20752);
	if( pt >= 220 && pt < 240 )
		return(W0 * 3.51967);
	if( pt >= 240 && pt < 260 )
		return(W0 * 25.3746);
	if( pt >= 260 && pt < 280 )
		return(W0 * 3.7237);
	if( pt >= 280 && pt < 300 )
		return(W0 * 22.8038);
	if( pt >= 300 && pt < 320 )
		return(W0 * 2.36021);
	if( pt >= 320 && pt < 340 )
		return(W0 * 7.85298);
	if( pt >= 340 && pt < 360 )
		return(W0 * 0);
	if( pt >= 360 && pt < 380 )
		return(W0 * 8.12645);
	if( pt >= 380 && pt < 400 )
		return(W0 * 1.31724);
}else if(fabs(eta) >= 0.8 && fabs(eta) < 0.9 ){
	if( pt >= 20 && pt < 40 )
		return(W0 * 0.609967);
	if( pt >= 40 && pt < 60 )
		return(W0 * 0.511116);
	if( pt >= 60 && pt < 80 )
		return(W0 * 0.639507);
	if( pt >= 80 && pt < 100 )
		return(W0 * 1.00567);
	if( pt >= 100 && pt < 120 )
		return(W0 * 1.3454);
	if( pt >= 120 && pt < 140 )
		return(W0 * 1.22132);
	if( pt >= 140 && pt < 160 )
		return(W0 * 3.12539);
	if( pt >= 160 && pt < 180 )
		return(W0 * 6.49245);
	if( pt >= 180 && pt < 200 )
		return(W0 * 6.87092);
	if( pt >= 200 && pt < 220 )
		return(W0 * 10.6367);
	if( pt >= 220 && pt < 240 )
		return(W0 * 2.742);
	if( pt >= 240 && pt < 260 )
		return(W0 * 11.8687);
	if( pt >= 260 && pt < 280 )
		return(W0 * 28.9825);
	if( pt >= 280 && pt < 300 )
		return(W0 * 18.8368);
	if( pt >= 300 && pt < 320 )
		return(W0 * 5.14446);
	if( pt >= 320 && pt < 340 )
		return(W0 * 42.0001);
	if( pt >= 340 && pt < 360 )
		return(W0 * 0);
	if( pt >= 360 && pt < 380 )
		return(W0 * 0);
	if( pt >= 380 && pt < 400 )
		return(W0 * 0);
}else if(fabs(eta) >= 0.9 && fabs(eta) < 1 ){
	if( pt >= 20 && pt < 40 )
		return(W0 * 0.526814);
	if( pt >= 40 && pt < 60 )
		return(W0 * 0.588494);
	if( pt >= 60 && pt < 80 )
		return(W0 * 0.803734);
	if( pt >= 80 && pt < 100 )
		return(W0 * 1.33437);
	if( pt >= 100 && pt < 120 )
		return(W0 * 1.41648);
	if( pt >= 120 && pt < 140 )
		return(W0 * 2.43155);
	if( pt >= 140 && pt < 160 )
		return(W0 * 1.85195);
	if( pt >= 160 && pt < 180 )
		return(W0 * 2.88728);
	if( pt >= 180 && pt < 200 )
		return(W0 * 3.16022);
	if( pt >= 200 && pt < 220 )
		return(W0 * 1.68493);
	if( pt >= 220 && pt < 240 )
		return(W0 * 14.6421);
	if( pt >= 240 && pt < 260 )
		return(W0 * 41.8946);
	if( pt >= 260 && pt < 280 )
		return(W0 * 55.8369);
	if( pt >= 280 && pt < 300 )
		return(W0 * 36.4096);
	if( pt >= 300 && pt < 320 )
		return(W0 * 0);
	if( pt >= 320 && pt < 340 )
		return(W0 * 0);
	if( pt >= 340 && pt < 360 )
		return(W0 * 8.51832);
	if( pt >= 360 && pt < 380 )
		return(W0 * 0);
	if( pt >= 380 && pt < 400 )
		return(W0 * 0);
}else if(fabs(eta) >= 1 && fabs(eta) < 1.1 ){
	if( pt >= 20 && pt < 40 )
		return(W0 * 0.503754);
	if( pt >= 40 && pt < 60 )
		return(W0 * 0.536137);
	if( pt >= 60 && pt < 80 )
		return(W0 * 0.832128);
	if( pt >= 80 && pt < 100 )
		return(W0 * 1.09161);
	if( pt >= 100 && pt < 120 )
		return(W0 * 1.88759);
	if( pt >= 120 && pt < 140 )
		return(W0 * 2.25694);
	if( pt >= 140 && pt < 160 )
		return(W0 * 2.85084);
	if( pt >= 160 && pt < 180 )
		return(W0 * 2.97571);
	if( pt >= 180 && pt < 200 )
		return(W0 * 3.01576);
	if( pt >= 200 && pt < 220 )
		return(W0 * 8.45397);
	if( pt >= 220 && pt < 240 )
		return(W0 * 4.53738);
	if( pt >= 240 && pt < 260 )
		return(W0 * 6.12016);
	if( pt >= 260 && pt < 280 )
		return(W0 * 4.35247);
	if( pt >= 280 && pt < 300 )
		return(W0 * 0);
	if( pt >= 300 && pt < 320 )
		return(W0 * 11.3469);
	if( pt >= 320 && pt < 340 )
		return(W0 * 16.1252);
	if( pt >= 340 && pt < 360 )
		return(W0 * 10.0787);
	if( pt >= 360 && pt < 380 )
		return(W0 * 0);
	if( pt >= 380 && pt < 400 )
		return(W0 * 59.4106);
}else if(fabs(eta) >= 1.1 && fabs(eta) < 1.2 ){
	if( pt >= 20 && pt < 40 )
		return(W0 * 0.388756);
	if( pt >= 40 && pt < 60 )
		return(W0 * 0.583198);
	if( pt >= 60 && pt < 80 )
		return(W0 * 0.740322);
	if( pt >= 80 && pt < 100 )
		return(W0 * 1.42307);
	if( pt >= 100 && pt < 120 )
		return(W0 * 1.62373);
	if( pt >= 120 && pt < 140 )
		return(W0 * 1.66021);
	if( pt >= 140 && pt < 160 )
		return(W0 * 2.96565);
	if( pt >= 160 && pt < 180 )
		return(W0 * 5.93886);
	if( pt >= 180 && pt < 200 )
		return(W0 * 10.2898);
	if( pt >= 200 && pt < 220 )
		return(W0 * 15.9164);
	if( pt >= 220 && pt < 240 )
		return(W0 * 1.81494);
	if( pt >= 240 && pt < 260 )
		return(W0 * 2.64334);
	if( pt >= 260 && pt < 280 )
		return(W0 * 18.7265);
	if( pt >= 280 && pt < 300 )
		return(W0 * 6.05636);
	if( pt >= 300 && pt < 320 )
		return(W0 * 4.69766);
	if( pt >= 320 && pt < 340 )
		return(W0 * 0);
	if( pt >= 340 && pt < 360 )
		return(W0 * 0);
	if( pt >= 360 && pt < 380 )
		return(W0 * 0);
	if( pt >= 380 && pt < 400 )
		return(W0 * 0);
}else if(fabs(eta) >= 1.2 && fabs(eta) < 1.3 ){
	if( pt >= 20 && pt < 40 )
		return(W0 * 0.722557);
	if( pt >= 40 && pt < 60 )
		return(W0 * 0.548222);
	if( pt >= 60 && pt < 80 )
		return(W0 * 0.776278);
	if( pt >= 80 && pt < 100 )
		return(W0 * 1.02827);
	if( pt >= 100 && pt < 120 )
		return(W0 * 1.42865);
	if( pt >= 120 && pt < 140 )
		return(W0 * 2.46459);
	if( pt >= 140 && pt < 160 )
		return(W0 * 3.79682);
	if( pt >= 160 && pt < 180 )
		return(W0 * 1.42415);
	if( pt >= 180 && pt < 200 )
		return(W0 * 4.32861);
	if( pt >= 200 && pt < 220 )
		return(W0 * 7.93596);
	if( pt >= 220 && pt < 240 )
		return(W0 * 14.4188);
	if( pt >= 240 && pt < 260 )
		return(W0 * 34.0348);
	if( pt >= 260 && pt < 280 )
		return(W0 * 11.8878);
	if( pt >= 280 && pt < 300 )
		return(W0 * 44.8555);
	if( pt >= 300 && pt < 320 )
		return(W0 * 0);
	if( pt >= 320 && pt < 340 )
		return(W0 * 0.361744);
	if( pt >= 340 && pt < 360 )
		return(W0 * 10.0787);
	if( pt >= 360 && pt < 380 )
		return(W0 * 5.08641);
	if( pt >= 380 && pt < 400 )
		return(W0 * 0);
}else if(fabs(eta) >= 1.3 && fabs(eta) < 1.4 ){
	if( pt >= 20 && pt < 40 )
		return(W0 * 0.562367);
	if( pt >= 40 && pt < 60 )
		return(W0 * 0.637764);
	if( pt >= 60 && pt < 80 )
		return(W0 * 0.657311);
	if( pt >= 80 && pt < 100 )
		return(W0 * 1.70512);
	if( pt >= 100 && pt < 120 )
		return(W0 * 1.84392);
	if( pt >= 120 && pt < 140 )
		return(W0 * 2.95572);
	if( pt >= 140 && pt < 160 )
		return(W0 * 3.92082);
	if( pt >= 160 && pt < 180 )
		return(W0 * 4.06276);
	if( pt >= 180 && pt < 200 )
		return(W0 * 14.9568);
	if( pt >= 200 && pt < 220 )
		return(W0 * 16.3531);
	if( pt >= 220 && pt < 240 )
		return(W0 * 14.4097);
	if( pt >= 240 && pt < 260 )
		return(W0 * 7.25505);
	if( pt >= 260 && pt < 280 )
		return(W0 * 0);
	if( pt >= 280 && pt < 300 )
		return(W0 * 10.377);
	if( pt >= 300 && pt < 320 )
		return(W0 * 0);
	if( pt >= 320 && pt < 340 )
		return(W0 * 63.4513);
	if( pt >= 340 && pt < 360 )
		return(W0 * 0);
	if( pt >= 360 && pt < 380 )
		return(W0 * 0);
	if( pt >= 380 && pt < 400 )
		return(W0 * 6.04721);
}else if(fabs(eta) >= 1.4 && fabs(eta) < 1.5 ){
	if( pt >= 20 && pt < 40 )
		return(W0 * 0.719602);
	if( pt >= 40 && pt < 60 )
		return(W0 * 0.503164);
	if( pt >= 60 && pt < 80 )
		return(W0 * 0.81968);
	if( pt >= 80 && pt < 100 )
		return(W0 * 1.38045);
	if( pt >= 100 && pt < 120 )
		return(W0 * 1.8401);
	if( pt >= 120 && pt < 140 )
		return(W0 * 4.84643);
	if( pt >= 140 && pt < 160 )
		return(W0 * 2.22622);
	if( pt >= 160 && pt < 180 )
		return(W0 * 7.32117);
	if( pt >= 180 && pt < 200 )
		return(W0 * 9.76088);
	if( pt >= 200 && pt < 220 )
		return(W0 * 14.8261);
	if( pt >= 220 && pt < 240 )
		return(W0 * 3.76849);
	if( pt >= 240 && pt < 260 )
		return(W0 * 37.9881);
	if( pt >= 260 && pt < 280 )
		return(W0 * 44.6829);
	if( pt >= 280 && pt < 300 )
		return(W0 * 16.8911);
	if( pt >= 300 && pt < 320 )
		return(W0 * 4.22235);
	if( pt >= 320 && pt < 340 )
		return(W0 * 0);
	if( pt >= 340 && pt < 360 )
		return(W0 * 0);
	if( pt >= 360 && pt < 380 )
		return(W0 * 0);
	if( pt >= 380 && pt < 400 )
		return(W0 * 0);
}else if(fabs(eta) >= 1.5 && fabs(eta) < 1.6 ){
	if( pt >= 20 && pt < 40 )
		return(W0 * 1.06685);
	if( pt >= 40 && pt < 60 )
		return(W0 * 0.724317);
	if( pt >= 60 && pt < 80 )
		return(W0 * 1.2868);
	if( pt >= 80 && pt < 100 )
		return(W0 * 1.4886);
	if( pt >= 100 && pt < 120 )
		return(W0 * 1.37564);
	if( pt >= 120 && pt < 140 )
		return(W0 * 3.93566);
	if( pt >= 140 && pt < 160 )
		return(W0 * 2.81103);
	if( pt >= 160 && pt < 180 )
		return(W0 * 13.3937);
	if( pt >= 180 && pt < 200 )
		return(W0 * 3.06887);
	if( pt >= 200 && pt < 220 )
		return(W0 * 13.2023);
	if( pt >= 220 && pt < 240 )
		return(W0 * 14.6772);
	if( pt >= 240 && pt < 260 )
		return(W0 * 129.972);
	if( pt >= 260 && pt < 280 )
		return(W0 * 8.69823);
	if( pt >= 280 && pt < 300 )
		return(W0 * 0);
	if( pt >= 300 && pt < 320 )
		return(W0 * 0);
	if( pt >= 320 && pt < 340 )
		return(W0 * 10.1422);
	if( pt >= 340 && pt < 360 )
		return(W0 * 0);
	if( pt >= 360 && pt < 380 )
		return(W0 * 0);
	if( pt >= 380 && pt < 400 )
		return(W0 * 0);
}else if(fabs(eta) >= 1.6 && fabs(eta) < 1.7 ){
	if( pt >= 20 && pt < 40 )
		return(W0 * 0.760886);
	if( pt >= 40 && pt < 60 )
		return(W0 * 1.01203);
	if( pt >= 60 && pt < 80 )
		return(W0 * 0.887763);
	if( pt >= 80 && pt < 100 )
		return(W0 * 1.72977);
	if( pt >= 100 && pt < 120 )
		return(W0 * 2.51944);
	if( pt >= 120 && pt < 140 )
		return(W0 * 3.07827);
	if( pt >= 140 && pt < 160 )
		return(W0 * 1.8428);
	if( pt >= 160 && pt < 180 )
		return(W0 * 3.28993);
	if( pt >= 180 && pt < 200 )
		return(W0 * 11.0494);
	if( pt >= 200 && pt < 220 )
		return(W0 * 27.0544);
	if( pt >= 220 && pt < 240 )
		return(W0 * 20.16);
	if( pt >= 240 && pt < 260 )
		return(W0 * 6.09254);
	if( pt >= 260 && pt < 280 )
		return(W0 * 637.472);
	if( pt >= 280 && pt < 300 )
		return(W0 * 0.231204);
	if( pt >= 300 && pt < 320 )
		return(W0 * 0);
	if( pt >= 320 && pt < 340 )
		return(W0 * 0);
	if( pt >= 340 && pt < 360 )
		return(W0 * 0);
	if( pt >= 360 && pt < 380 )
		return(W0 * 0);
	if( pt >= 380 && pt < 400 )
		return(W0 * 0);
}else if(fabs(eta) >= 1.7 && fabs(eta) < 1.8 ){
	if( pt >= 20 && pt < 40 )
		return(W0 * 0.642922);
	if( pt >= 40 && pt < 60 )
		return(W0 * 1.05548);
	if( pt >= 60 && pt < 80 )
		return(W0 * 0.960916);
	if( pt >= 80 && pt < 100 )
		return(W0 * 1.55431);
	if( pt >= 100 && pt < 120 )
		return(W0 * 4.79326);
	if( pt >= 120 && pt < 140 )
		return(W0 * 4.18058);
	if( pt >= 140 && pt < 160 )
		return(W0 * 2.08835);
	if( pt >= 160 && pt < 180 )
		return(W0 * 3.54306);
	if( pt >= 180 && pt < 200 )
		return(W0 * 20.4784);
	if( pt >= 200 && pt < 220 )
		return(W0 * 17.7166);
	if( pt >= 220 && pt < 240 )
		return(W0 * 5.87563);
	if( pt >= 240 && pt < 260 )
		return(W0 * 10.8128);
	if( pt >= 260 && pt < 280 )
		return(W0 * 0);
	if( pt >= 280 && pt < 300 )
		return(W0 * 0);
	if( pt >= 300 && pt < 320 )
		return(W0 * 0);
	if( pt >= 320 && pt < 340 )
		return(W0 * 0);
	if( pt >= 340 && pt < 360 )
		return(W0 * 0);
	if( pt >= 360 && pt < 380 )
		return(W0 * 0);
	if( pt >= 380 && pt < 400 )
		return(W0 * 0);
}else if(fabs(eta) >= 1.8 && fabs(eta) < 1.9 ){
	if( pt >= 20 && pt < 40 )
		return(W0 * 0.682097);
	if( pt >= 40 && pt < 60 )
		return(W0 * 0.757677);
	if( pt >= 60 && pt < 80 )
		return(W0 * 1.26857);
	if( pt >= 80 && pt < 100 )
		return(W0 * 2.63329);
	if( pt >= 100 && pt < 120 )
		return(W0 * 3.18628);
	if( pt >= 120 && pt < 140 )
		return(W0 * 3.95505);
	if( pt >= 140 && pt < 160 )
		return(W0 * 2.19399);
	if( pt >= 160 && pt < 180 )
		return(W0 * 40.5505);
	if( pt >= 180 && pt < 200 )
		return(W0 * 166.119);
	if( pt >= 200 && pt < 220 )
		return(W0 * 84.9501);
	if( pt >= 220 && pt < 240 )
		return(W0 * 9.26904);
	if( pt >= 240 && pt < 260 )
		return(W0 * 3.13182);
	if( pt >= 260 && pt < 280 )
		return(W0 * 0);
	if( pt >= 280 && pt < 300 )
		return(W0 * 0);
	if( pt >= 300 && pt < 320 )
		return(W0 * 0);
	if( pt >= 320 && pt < 340 )
		return(W0 * 0);
	if( pt >= 340 && pt < 360 )
		return(W0 * 0);
	if( pt >= 360 && pt < 380 )
		return(W0 * 0);
	if( pt >= 380 && pt < 400 )
		return(W0 * 0);
}else if(fabs(eta) >= 1.9 && fabs(eta) < 2 ){
	if( pt >= 20 && pt < 40 )
		return(W0 * 0.726992);
	if( pt >= 40 && pt < 60 )
		return(W0 * 0.938888);
	if( pt >= 60 && pt < 80 )
		return(W0 * 2.49734);
	if( pt >= 80 && pt < 100 )
		return(W0 * 2.70626);
	if( pt >= 100 && pt < 120 )
		return(W0 * 2.10184);
	if( pt >= 120 && pt < 140 )
		return(W0 * 10.4076);
	if( pt >= 140 && pt < 160 )
		return(W0 * 2.32306);
	if( pt >= 160 && pt < 180 )
		return(W0 * 26.9988);
	if( pt >= 180 && pt < 200 )
		return(W0 * 1.47769);
	if( pt >= 200 && pt < 220 )
		return(W0 * 43.4691);
	if( pt >= 220 && pt < 240 )
		return(W0 * 325.989);
	if( pt >= 240 && pt < 260 )
		return(W0 * 0);
	if( pt >= 260 && pt < 280 )
		return(W0 * 0);
	if( pt >= 280 && pt < 300 )
		return(W0 * 0);
	if( pt >= 300 && pt < 320 )
		return(W0 * 0);
	if( pt >= 320 && pt < 340 )
		return(W0 * 0);
	if( pt >= 340 && pt < 360 )
		return(W0 * 0);
	if( pt >= 360 && pt < 380 )
		return(W0 * 0);
	if( pt >= 380 && pt < 400 )
		return(W0 * 0);
}else if(fabs(eta) >= 2 && fabs(eta) < 2.1 ){
	if( pt >= 20 && pt < 40 )
		return(W0 * 0.8785);
	if( pt >= 40 && pt < 60 )
		return(W0 * 1.03276);
	if( pt >= 60 && pt < 80 )
		return(W0 * 1.98497);
	if( pt >= 80 && pt < 100 )
		return(W0 * 3.64707);
	if( pt >= 100 && pt < 120 )
		return(W0 * 6.40634);
	if( pt >= 120 && pt < 140 )
		return(W0 * 11.0251);
	if( pt >= 140 && pt < 160 )
		return(W0 * 9.54702);
	if( pt >= 160 && pt < 180 )
		return(W0 * 42.9576);
	if( pt >= 180 && pt < 200 )
		return(W0 * 33.8873);
	if( pt >= 200 && pt < 220 )
		return(W0 * 77.172);
	if( pt >= 220 && pt < 240 )
		return(W0 * 0);
	if( pt >= 240 && pt < 260 )
		return(W0 * 101.53);
	if( pt >= 260 && pt < 280 )
		return(W0 * 0);
	if( pt >= 280 && pt < 300 )
		return(W0 * 0);
	if( pt >= 300 && pt < 320 )
		return(W0 * 0);
	if( pt >= 320 && pt < 340 )
		return(W0 * 0);
	if( pt >= 340 && pt < 360 )
		return(W0 * 0);
	if( pt >= 360 && pt < 380 )
		return(W0 * 0);
	if( pt >= 380 && pt < 400 )
		return(W0 * 0);
}else if(fabs(eta) >= 2.1 && fabs(eta) < 2.2 ){
	if( pt >= 20 && pt < 40 )
		return(W0 * 0.871076);
	if( pt >= 40 && pt < 60 )
		return(W0 * 1.3897);
	if( pt >= 60 && pt < 80 )
		return(W0 * 1.76013);
	if( pt >= 80 && pt < 100 )
		return(W0 * 3.5811);
	if( pt >= 100 && pt < 120 )
		return(W0 * 3.91971);
	if( pt >= 120 && pt < 140 )
		return(W0 * 3.92759);
	if( pt >= 140 && pt < 160 )
		return(W0 * 26.3115);
	if( pt >= 160 && pt < 180 )
		return(W0 * 67.2417);
	if( pt >= 180 && pt < 200 )
		return(W0 * 43.059);
	if( pt >= 200 && pt < 220 )
		return(W0 * 0);
	if( pt >= 220 && pt < 240 )
		return(W0 * 0);
	if( pt >= 240 && pt < 260 )
		return(W0 * 0);
	if( pt >= 260 && pt < 280 )
		return(W0 * 0);
	if( pt >= 280 && pt < 300 )
		return(W0 * 0);
	if( pt >= 300 && pt < 320 )
		return(W0 * 0);
	if( pt >= 320 && pt < 340 )
		return(W0 * 0);
	if( pt >= 340 && pt < 360 )
		return(W0 * 0);
	if( pt >= 360 && pt < 380 )
		return(W0 * 0);
	if( pt >= 380 && pt < 400 )
		return(W0 * 0);
}else if(fabs(eta) >= 2.2 && fabs(eta) < 2.3 ){
	if( pt >= 20 && pt < 40 )
		return(W0 * 0.732174);
	if( pt >= 40 && pt < 60 )
		return(W0 * 1.48502);
	if( pt >= 60 && pt < 80 )
		return(W0 * 2.80749);
	if( pt >= 80 && pt < 100 )
		return(W0 * 3.72006);
	if( pt >= 100 && pt < 120 )
		return(W0 * 3.38743);
	if( pt >= 120 && pt < 140 )
		return(W0 * 6.75427);
	if( pt >= 140 && pt < 160 )
		return(W0 * 2.22629);
	if( pt >= 160 && pt < 180 )
		return(W0 * 0);
	if( pt >= 180 && pt < 200 )
		return(W0 * 0);
	if( pt >= 200 && pt < 220 )
		return(W0 * 20.0839);
	if( pt >= 220 && pt < 240 )
		return(W0 * 0);
	if( pt >= 240 && pt < 260 )
		return(W0 * 0);
	if( pt >= 260 && pt < 280 )
		return(W0 * 0);
	if( pt >= 280 && pt < 300 )
		return(W0 * 0);
	if( pt >= 300 && pt < 320 )
		return(W0 * 0);
	if( pt >= 320 && pt < 340 )
		return(W0 * 0);
	if( pt >= 340 && pt < 360 )
		return(W0 * 0);
	if( pt >= 360 && pt < 380 )
		return(W0 * 0);
	if( pt >= 380 && pt < 400 )
		return(W0 * 0);
}else if(fabs(eta) >= 2.3 && fabs(eta) < 2.4 ){
	if( pt >= 20 && pt < 40 )
		return(W0 * 1.37133);
	if( pt >= 40 && pt < 60 )
		return(W0 * 1.33613);
	if( pt >= 60 && pt < 80 )
		return(W0 * 1.96615);
	if( pt >= 80 && pt < 100 )
		return(W0 * 3.7926);
	if( pt >= 100 && pt < 120 )
		return(W0 * 14.9473);
	if( pt >= 120 && pt < 140 )
		return(W0 * 3.44838);
	if( pt >= 140 && pt < 160 )
		return(W0 * 8.73556);
	if( pt >= 160 && pt < 180 )
		return(W0 * 0);
	if( pt >= 180 && pt < 200 )
		return(W0 * 27.473);
	if( pt >= 200 && pt < 220 )
		return(W0 * 0);
	if( pt >= 220 && pt < 240 )
		return(W0 * 0);
	if( pt >= 240 && pt < 260 )
		return(W0 * 0);
	if( pt >= 260 && pt < 280 )
		return(W0 * 0);
	if( pt >= 280 && pt < 300 )
		return(W0 * 0);
	if( pt >= 300 && pt < 320 )
		return(W0 * 0);
	if( pt >= 320 && pt < 340 )
		return(W0 * 0);
	if( pt >= 340 && pt < 360 )
		return(W0 * 0);
	if( pt >= 360 && pt < 380 )
		return(W0 * 0);
	if( pt >= 380 && pt < 400 )
		return(W0 * 0);
}
return W0;
}
#endif	/* _REWEITHINGFUNCTIONS_H */
