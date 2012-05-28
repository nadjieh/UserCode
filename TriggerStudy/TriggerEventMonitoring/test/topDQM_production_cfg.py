import FWCore.ParameterSet.Config as cms

process = cms.Process('TOPDQM')

## imports of standard configurations
process.load('DQMOffline.Configuration.DQMOffline_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

## --------------------------------------------------------------------
## Frontier Conditions: (adjust accordingly!!!)
##
## For CMSSW_3_8_X MC use             ---> 'START38_V12::All'
## For Data (38X re-processing) use   ---> 'GR_R_38X_V13::All'
## For Data (38X prompt reco) use     ---> 'GR10_P_V10::All'
##
## For more details have a look at: WGuideFrontierConditions
## --------------------------------------------------------------------
##process.GlobalTag.globaltag = 'START38_V12::All'
process.GlobalTag.globaltag = 'GR_R_52_V7::All' 
#process.GlobalTag.globaltag   = 'START52_V4A::All'

## input file(s) for testing
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
     #'/store/relval/CMSSW_4_2_3/RelValTTbar/GEN-SIM-RECO/START42_V12-v2/0062/728877FF-717B-E011-9989-00261894395B.root'
     #'/store/data/Run2011A/SingleMu/AOD/PromptReco-v4/000/165/999/A2B8A207-838B-E011-B1F5-000423D94908.root'
#    '/store/relval/CMSSW_4_2_3/RelValTTbar/GEN-SIM-RECO/MC_42_V12-v2/0062/60815BF5-387B-E011-805B-0018F3D0970C.root'
#	'/store/relval/CMSSW_5_2_0/RelValTTbar/GEN-SIM-RECO/START52_V4A-v1/0248/14F70731-1A69-E111-B218-0018F3D096EA.root'
     "/store/data/Run2012B/SingleMu/AOD/PromptReco-v1/000/194/702/EE71F090-EFA5-E111-84E0-BCAEC518FF52.root"
     )
)

## number of events
process.maxEvents = cms.untracked.PSet(
#  input = cms.untracked.int32(500)
  input = cms.untracked.int32(-1)
)

## apply VBTF electronID (needed for the current implementation
## of topSingleElectronDQMLoose and topSingleElectronDQMMedium)
process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.StandardSequences.MagneticField_cff")
process.load("DQM.Physics.topElectronID_cff")

#process.topSingleMuonLooseTriggerDQM.setup.triggerExtras.src  = cms.InputTag("TriggerResults","","REDIGI42X")
#process.topSingleMuonLooseTriggerDQM.preselection.trigger.src = cms.InputTag("TriggerResults","","REDIGI42X")
#process.topSingleMuonLooseTriggerDQM.preselection.trigger.select  = cms.vstring(['HLT_Mu15_v2'])
#process.topSingleMuonMediumTriggerDQM.preselection.trigger.select = cms.vstring(['HLT_Mu15_v2'])

## output
process.output = cms.OutputModule("PoolOutputModule",
  fileName       = cms.untracked.string('topDQM_production.root'),
  outputCommands = cms.untracked.vstring(
    'drop *_*_*_*',
    'keep *_*_*_TOPDQM',
    'drop *_TriggerResults_*_TOPDQM',
    'drop *_simpleEleId70cIso_*_TOPDQM',
  ),
  splitLevel     = cms.untracked.int32(0),
  dataset = cms.untracked.PSet(
    dataTier   = cms.untracked.string(''),
    filterName = cms.untracked.string('')
  )
)

## load jet corrections
process.load("JetMETCorrections.Configuration.JetCorrectionServicesAllAlgos_cff")
process.prefer("ak5CaloL2L3")

## check the event content
process.content = cms.EDAnalyzer("EventContentAnalyzer")

## configure message logger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
process.MessageLogger.categories.append('TopSingleLeptonTriggerDQM'   )
process.MessageLogger.cerr.TopSingleLeptonTriggerDQM    = cms.untracked.PSet(limit = cms.untracked.int32(1))
process.MessageLogger.categories.append('TopDiLeptonOfflineDQM')
process.MessageLogger.cerr.TopDiLeptonOfflineDQM = cms.untracked.PSet(limit = cms.untracked.int32(1))

process.MEtoEDMConverter.deleteAfterCopy = cms.untracked.bool(False)  ## line added to avoid crash when changing run number
## To examin more paths at the same time, clone the module
##process.NEWHLTtopSingleMuonMediumTriggerDQM = process.topSingleMuonMediumTriggerDQM.clone()
##process.NEWHLTtopSingleMuonMediumTriggerDQM.preselection.trigger.select = cms.vstring(['NEWPATH'])#Only one
##process.NEWHLTtopSingleMuonMediumTriggerDQM.setup.directory = cms.string("Physics/Top/NEWHLTTopSingleMuonLooseTriggerDQM/")
## add it to the p path below

process.SingleTopTriggerDQM.preselection.trigger.select = cms.vstring(['HLT_IsoMu17_eta2p1_CentralPFNoPUJet30_BTagIPIter_v1'])
## path definitions
process.p      = cms.Path(
   #process.content *
    process.simpleEleId70cIso          *
    #process.topSingleMuonMediumTriggerDQM     +
    process.SingleTopTriggerDQM
)
process.endjob = cms.Path(
    process.endOfProcess
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
