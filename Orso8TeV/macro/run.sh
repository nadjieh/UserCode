#Data
#./QCDOrsoHistogramCreator input Data METResolFileName /home/nadjieh/work/AnalysisClasses/ToyAnalysis/macro/METresolutions.root isData yes
#./DefWOrsoHistogramCreator input Data METResolFileName /home/nadjieh/work/AnalysisClasses/ToyAnalysis/macro/METresolutions.root isData yes
./DataOrsoHistogramCreator input Data METResolFileName /home/nadjieh/work/AnalysisClasses/ToyAnalysis/macro/METresolutions.root isData yes

#MC
./OrsoHistogramCreator input WW METResolFileName /home/nadjieh/work/AnalysisClasses/ToyAnalysis/macro/METresolutions.root isData no > WW.txt
./OrsoHistogramCreator input SbarChannel METResolFileName /home/nadjieh/work/AnalysisClasses/ToyAnalysis/macro/METresolutions.root isData no > SbarChannel.txt
./OrsoHistogramCreator input SChannel METResolFileName /home/nadjieh/work/AnalysisClasses/ToyAnalysis/macro/METresolutions.root isData no > SChannel.txt
./OrsoHistogramCreator input TbarChannel METResolFileName /home/nadjieh/work/AnalysisClasses/ToyAnalysis/macro/METresolutions.root isData no > TbarChannel.txt
./OrsoHistogramCreator input TbarWChannel METResolFileName /home/nadjieh/work/AnalysisClasses/ToyAnalysis/macro/METresolutions.root isData no > TbarWChannel.txt
./OrsoHistogramCreator input TChannel METResolFileName /home/nadjieh/work/AnalysisClasses/ToyAnalysis/macro/METresolutions.root isData no > TChannel.txt
./OrsoHistogramCreator input TTBar METResolFileName /home/nadjieh/work/AnalysisClasses/ToyAnalysis/macro/METresolutions.root isData no > TTBar.txt
./OrsoHistogramCreator input TWChannel METResolFileName /home/nadjieh/work/AnalysisClasses/ToyAnalysis/macro/METresolutions.root isData no > TWChannel.txt
./OrsoHistogramCreator input WJets METResolFileName /home/nadjieh/work/AnalysisClasses/ToyAnalysis/macro/METresolutions.root isData no > WJets.txt
./OrsoHistogramCreator input WZ METResolFileName /home/nadjieh/work/AnalysisClasses/ToyAnalysis/macro/METresolutions.root isData no > WZ.txt
./OrsoHistogramCreator input ZJets METResolFileName /home/nadjieh/work/AnalysisClasses/ToyAnalysis/macro/METresolutions.root isData no > ZJets.txt
./OrsoHistogramCreator input ZZ METResolFileName /home/nadjieh/work/AnalysisClasses/ToyAnalysis/macro/METresolutions.root isData no > ZZ.txt
#./OrsoHistogramCreator input TBENuChannel_Comphep METResolFileName /home/nadjieh/work/AnalysisClasses/ToyAnalysis/macro/METresolutions.root isData no > TBENuChannel_Comphep.txt
#./OrsoHistogramCreator input TBMuNuChannel_Comphep METResolFileName /home/nadjieh/work/AnalysisClasses/ToyAnalysis/macro/METresolutions.root isData no > TBMuNuChannel_Comphep.txt
#./OrsoHistogramCreator input TBTauNuChannel_Comphep METResolFileName /home/nadjieh/work/AnalysisClasses/ToyAnalysis/macro/METresolutions.root isData no > TBTauNuChannel_Comphep.txt
#./OrsoHistogramCreator input TbarChannel_MassDown METResolFileName /home/nadjieh/work/AnalysisClasses/ToyAnalysis/macro/METresolutions.root isData no
#./OrsoHistogramCreator input TChannel_MassDown METResolFileName /home/nadjieh/work/AnalysisClasses/ToyAnalysis/macro/METresolutions.root isData no
#./OrsoHistogramCreator input TTBar_MassDown METResolFileName /home/nadjieh/work/AnalysisClasses/ToyAnalysis/macro/METresolutions.root isData no
#./OrsoHistogramCreator input TbarChannel_MassUp METResolFileName /home/nadjieh/work/AnalysisClasses/ToyAnalysis/macro/METresolutions.root isData no
#./OrsoHistogramCreator input TChannel_MassUp METResolFileName /home/nadjieh/work/AnalysisClasses/ToyAnalysis/macro/METresolutions.root isData no
#./OrsoHistogramCreator input TTBar_MassUp METResolFileName /home/nadjieh/work/AnalysisClasses/ToyAnalysis/macro/METresolutions.root isData no

