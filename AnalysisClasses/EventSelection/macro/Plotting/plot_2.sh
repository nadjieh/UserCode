./TestCreateWeighedHists out Summer11_tbar_plots.root input   Summer11/FullySelected_Tbar_TopTree_Skimmed.root METResolFileName /home/nadjieh/work/AnalysisClasses/ToyAnalysis/macro/METresolutions.root PUWeightFileName tbarPU3.root  isData no puOption pileup_MC_Flat10PlusTail.root > Summer11_tbar.txt

#./TestCreateWeighedHists out Summer11_tt_plots.root input   Summer11/FullySelected_TT_TopTree_Skimmed.root METResolFileName /home/nadjieh/work/AnalysisClasses/ToyAnalysis/macro/METresolutions.root PUWeightFileName ttPU3.root  isData no> Summer11_tt.txt

#./TestCreateWeighedHists out Summer11_ttNu_plots.root input   FullySelected/1_FullSelection_TypeIMET_Tt.root METResolFileName /home/nadjieh/work/AnalysisClasses/ToyAnalysis/macro/METresolutions.root PUWeightFileName ttPU3.root  isData no puOption MC_Fall11.root> Summer11_ttNu.txt

#./TestCreateWeighedHists out Summer11_paper_plots.root input   FullySelected/DataSources/1_FullSelection_TypeIMET_paper.root METResolFileName /home/nadjieh/work/AnalysisClasses/ToyAnalysis/macro/METresolutions.root PUWeightFileName qcdPU3.root isData yes puOption pileup_MC_Flat10PlusTail.root > Summer11_paper.txt

./TestCreateWeighedHists out Summer11_dy_plots.root input   Summer11/FullySelected_DY_TopTree_Skimmed.root METResolFileName /home/nadjieh/work/AnalysisClasses/ToyAnalysis/macro/METresolutions.root PUWeightFileName dyPU3.root  isData no puOption pileup_MC_Flat10PlusTail.root> Summer11_dy.txt

./TestCreateWeighedHists out Summer11_paper_plots.root input   FullySelected/DataSources/1_FullSelection_TypeIMET_paper.root METResolFileName /home/nadjieh/work/AnalysisClasses/ToyAnalysis/macro/METresolutions.root PUWeightFileName tmp.root isData yes  > Summer11_paper.txt

#./TestCreateWeighedHists out Summer11_runB_plots.root input   Data/vJSON/runB_TopTree_Skimmed.root METResolFileName /home/nadjieh/work/AnalysisClasses/ToyAnalysis/macro/METresolutions.root PUWeightFileName tmp.root isData yes puOption pileup_MC_Flat10PlusTail.root > Summer11_runB.txt



