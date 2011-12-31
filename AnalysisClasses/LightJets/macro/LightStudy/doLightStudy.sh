rm -f README*
rm -f v3_ReweithingFunctions.h
rm -f *.root
cp ../ReweithingFunctions.h .
cp /afs/cern.ch/user/a/ajafari/scratch0/CMSSW_3_6_1_patch3/src/AnalysisClasses/LightJets/interface/RW_BackUp/Base_ReweithingFunctions.h /afs/cern.ch/user/a/ajafari/scratch0/CMSSW_3_6_1_patch3/src/AnalysisClasses/LightJets/interface/ReweithingFunctions.h 
make                                                         
./StudyLightJets_v3 out StudyLightJets Lumi 100. input Signal.root XSec 23.3 Initial  220551 nextinput OtherTtBar.root XSec 134.16 Lumi 100. Initial  1.26418e+06 nextinput SingleTopS.root XSec 1.49 Lumi 100. Initial  392115 nextinput SingleTopT.root XSec 20.93 Lumi 100. Initial  528231 nextinput SingleTopTW.root XSec 10.6 Lumi 100. Initial  459936 nextinput Vqq.root XSec 65 Lumi 100. Initial  937274 nextinput WJets.root XSec 31314 Lumi 100. Initial  1.00787e+07 nextinput ZJets.root XSec 3048 Lumi 100. Initial   1.08368e+06 lastinput  > README

./../Divide input StudyLightJets_AntiTag3 out v3
cp ../ReweithingFunctions.h .
./../printInfo input v3_EtaPt.root >>  ReweithingFunctions.h

cp ReweithingFunctions.h ~/scratch0/CMSSW_3_6_1_patch3/src/AnalysisClasses/LightJets/interface/RW_BackUp/v3_ReweithingFunctions.h

cp  ~/scratch0/CMSSW_3_6_1_patch3/src/AnalysisClasses/LightJets/interface/RW_BackUp/v3_ReweithingFunctions.h ~/scratch0/CMSSW_3_6_1_patch3/src/AnalysisClasses/LightJets/interface/ReweithingFunctions.h

make rw

./StudyLightJets_v3_RW out StudyLightJets Lumi 100. input Signal.root XSec 23.3 Initial  220551 nextinput OtherTtBar.root XSec 134.16 Lumi 100. Initial  1.26418e+06 nextinput SingleTopS.root XSec 1.49 Lumi 100. Initial  392115 nextinput SingleTopT.root XSec 20.93 Lumi 100. Initial  528231 nextinput SingleTopTW.root XSec 10.6 Lumi 100. Initial  459936 nextinput Vqq.root XSec 65 Lumi 100. Initial  937274 nextinput WJets.root XSec 31314 Lumi 100. Initial  1.00787e+07 nextinput ZJets.root XSec 3048 Lumi 100. Initial   1.08368e+06 lastinput  > README_RW
