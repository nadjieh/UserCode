rm -f readme_*
./doFullChi2EffPur out Signal_Discrimination Lumi 100. input Signal.root XSec 23.3 Initial  220551 > readme_signal
./doFullChi2EffPur out WJets_Discrimination Lumi 100. input WJets.root XSec 31314  Initial  1.00787e+07 > readme_W
