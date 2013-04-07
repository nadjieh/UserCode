./QCDHistogramCreator out v4_QCD4_plots.root input   Summer11/QCDSourceFromOrso/Mu_v4.root METResolFileName /home/nadjieh/work/AnalysisClasses/ToyAnalysis/macro/METresolutions.root PUWeightFileName v4qcdPU3.root isData yes iso 1 > 1_v4_QCD4.txt

./QCDHistogramCreator out May10_QCD4_plots.root input   Summer11/QCDSourceFromOrso/Mu_May10.root METResolFileName /home/nadjieh/work/AnalysisClasses/ToyAnalysis/macro/METresolutions.root PUWeightFileName May10qcdPU3.root isData yes iso 1 > 1_May10_QCD4.txt


./QCDHistogramCreator out v4_QCD4_plots.root input   Summer11/QCDSourceFromOrso/Mu_v4.root METResolFileName /home/nadjieh/work/AnalysisClasses/ToyAnalysis/macro/METresolutions.root PUWeightFileName v4qcdPU3.root isData yes iso 2 > 2_v4_QCD4.txt

./QCDHistogramCreator out May10_QCD4_plots.root input   Summer11/QCDSourceFromOrso/Mu_May10.root METResolFileName /home/nadjieh/work/AnalysisClasses/ToyAnalysis/macro/METresolutions.root PUWeightFileName May10qcdPU3.root isData yes iso 2 > 2_May10_QCD4.txt

./QCDHistogramCreator out v4_QCD4_plots.root input   Summer11/QCDSourceFromOrso/Mu_v4.root METResolFileName /home/nadjieh/work/AnalysisClasses/ToyAnalysis/macro/METresolutions.root PUWeightFileName v4qcdPU3.root isData yes iso 3 > 3_v4_QCD4.txt

./QCDHistogramCreator out May10_QCD4_plots.root input   Summer11/QCDSourceFromOrso/Mu_May10.root METResolFileName /home/nadjieh/work/AnalysisClasses/ToyAnalysis/macro/METresolutions.root PUWeightFileName May10qcdPU3.root isData yes iso 3 > 3_May10_QCD4.txt


./QCDHistogramCreator out v4_QCD4_plots.root input   Summer11/QCDSourceFromOrso/Mu_v4.root METResolFileName /home/nadjieh/work/AnalysisClasses/ToyAnalysis/macro/METresolutions.root PUWeightFileName v4qcdPU3.root isData yes iso 4 > 4_v4_QCD4.txt

./QCDHistogramCreator out May10_QCD4_plots.root input   Summer11/QCDSourceFromOrso/Mu_May10.root METResolFileName /home/nadjieh/work/AnalysisClasses/ToyAnalysis/macro/METresolutions.root PUWeightFileName May10qcdPU3.root isData yes iso 4 > 4_May10_QCD4.txt

./QCDHistogramCreator out v4_QCD4_plots.root input   Summer11/QCDSourceFromOrso/Mu_v4.root METResolFileName /home/nadjieh/work/AnalysisClasses/ToyAnalysis/macro/METresolutions.root PUWeightFileName v4qcdPU3.root isData yes > v4_QCD4.txt

./QCDHistogramCreator out May10_QCD4_plots.root input   Summer11/QCDSourceFromOrso/Mu_May10.root METResolFileName /home/nadjieh/work/AnalysisClasses/ToyAnalysis/macro/METresolutions.root PUWeightFileName May10qcdPU3.root isData yes > May10_QCD4.txt

rm -f *_QCD.root


hadd 1_QCD.root 1_v4_QCD4_plots.root 1_May10_QCD4_plots.root
hadd 2_QCD.root 2_v4_QCD4_plots.root 2_May10_QCD4_plots.root
hadd 3_QCD.root 3_v4_QCD4_plots.root 3_May10_QCD4_plots.root
hadd 4_QCD.root 4_v4_QCD4_plots.root 4_May10_QCD4_plots.root


