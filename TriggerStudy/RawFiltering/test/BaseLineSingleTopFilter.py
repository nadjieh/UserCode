import FWCore.ParameterSet.Config as cms
process = cms.Process("forTrigger")
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
process.GlobalTag.globaltag = 'GR_R_44_V7::All'
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(10) )
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring("file:~/SyncSingleTop/V1/50A31B1A-8AAB-E011-835B-0026189438F5.root",
	"file:~/SyncSingleTop/V1/FE4EF257-A3AB-E011-9698-00304867915A.root"
    )
)
## output
process.output = cms.OutputModule("PoolOutputModule",
  fileName       = cms.untracked.string('BaseLineSelected_st.root'),
  outputCommands = cms.untracked.vstring(
    'drop *_*_*_*',
    'keep *_*_*_RECO',
  ),
  SelectEvents   = cms.untracked.PSet( SelectEvents = cms.vstring( 'p' ) ),
  splitLevel     = cms.untracked.int32(0),
  dataset = cms.untracked.PSet(
    dataTier   = cms.untracked.string(''),
    filterName = cms.untracked.string('')
  )
)
process.myFilter = cms.EDFilter("BaseLineSingleTopFilter",
  jetPtCut = cms.double(30.),
  muPtCut = cms.double(30.),
  jetEtaCut = cms.double(4.5), 
  muEtaCut = cms.double(2.1),
  nSelectedJets = cms.int32(2),
  nSelectedMu = cms.int32(1),
  applyMTcut = cms.bool(False),
  MTCut = cms.double(40),
  muons = cms.InputTag("muons"),
  jets = cms.InputTag("ak5PFJets"),
  met = cms.InputTag("pfMet"),
)
## path definitions
process.p      = cms.Path(
    process.myFilter
)
process.endjob = cms.Path(
    process.myFilter * process.endOfProcess
)
process.fanout = cms.EndPath(
    process.output
)

## schedule definition
process.schedule = cms.Schedule(
    process.p,
    process.endjob,
    process.fanout
)

