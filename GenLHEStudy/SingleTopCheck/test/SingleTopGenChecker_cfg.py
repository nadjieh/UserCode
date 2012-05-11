import FWCore.ParameterSet.Config as cms

process = cms.Process('LHEGEN')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
process.GlobalTag.globaltag   = 'START50_V15A::All'
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(100)
)
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
        "/store/relval/CMSSW_5_1_2/RelValTTbar/GEN-SIM-RECO/START50_V15A-v1/0237/4A92E0B9-BD60-E111-AE2C-003048678AE4.root"
     )
)
process.SingleTopGenChecker = cms.EDAnalyzer("SingleTopGenChecker",
  mcTruthCollection = cms.InputTag("genParticles"),
  outputFile = cms.string("singletopGenCheckr.root")
)
## path definitions
process.p      = cms.Path(
    process.SingleTopGenChecker
)

## schedule definition
process.schedule = cms.Schedule(
    process.p
)


