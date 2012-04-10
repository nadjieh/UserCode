import FWCore.ParameterSet.Config as cms
topSingleMuonLooseDQM_HLT_PU = cms.EDAnalyzer("TopSingleLeptonTriggerObjectDQM",
  ## ------------------------------------------------------
  ## SETUP
  ##
  ## configuration of the MonitoringEnsemble(s)
  ## [mandatory] : optional PSets may be omitted
  ##
  setup = cms.PSet(
    ## sub-directory to write the monitor histograms to
    ## [mandatory] : should not be changed w/o explicit
    ## communication to TopCom!
    directory = cms.string("Physics/Top/TopSingleMuonLooseDQM_HLT/"),
    ## [mandatory]
    sources = cms.PSet(
      muons = cms.InputTag("muons"),
      elecs = cms.InputTag("gsfElectrons"),
      jets  = cms.InputTag("ak5CaloJets"),
      mets  = cms.VInputTag("met", "tcMet", "pfMet"),
      pvs   = cms.InputTag("offlinePrimaryVertices")
    ),
    triggerInputs = cms.PSet(
      triggerResults = cms.InputTag("TriggerResults","","HLT"),
      triggerEvent   = cms.InputTag("hltTriggerSummaryAOD","","HLT"),
      paths          = cms.string("HLT_IsoMu17_v5"),
      processName = cms.string('HLT')
    ),

    ## [optional] : when omitted the verbosity level is set to STANDARD
    monitoring = cms.PSet(
      verbosity = cms.string("VERBOSE")
    ),

  ),
  ## ------------------------------------------------------
  ## PRESELECTION
  ##
  ## setup of the event preselection, which will not
  ## be monitored
  ## [mandatory] : but may be empty
  ##
  preselection = cms.PSet(
    ## [optional] : when omitted no preselection is applied
    vertex = cms.PSet(
      src    = cms.InputTag("offlinePrimaryVertices"),
      select = cms.string('abs(x)<1. & abs(y)<1. & abs(z)<20. & tracksSize>3 & !isFake')
    )
  ),
  ## ------------------------------------------------------
  ## SELECTION
  ##
  ## monitor histrograms are filled after each selection
  ## step, the selection is applied in the order defined
  ## by this vector
  ## [mandatory] : may be empty or contain an arbitrary
  ## number of PSets
  selection = cms.VPSet(
    cms.PSet(
      label  = cms.string("muons:step0"),
      src    = cms.InputTag("muons"),
      select = cms.string("pt>10 & abs(eta)<2.1 & isGlobalMuon & innerTrack.numberOfValidHits>10 & globalTrack.normalizedChi2>-1 & globalTrack.normalizedChi2<10"),
      min    = cms.int32(1),
    ),
    cms.PSet(
      label  = cms.string("pvs:step1"),
      src    = cms.InputTag("offlinePrimaryVertices"),
      select = cms.string("abs(x)<1. & abs(y)<1. & abs(z)<20. & tracksSize>3 & !isFake"),
      max    = cms.int32(10),
    ),
    cms.PSet(
      label  = cms.string("pvs:step2"),
      src    = cms.InputTag("offlinePrimaryVertices"),
      select = cms.string("abs(x)<1. & abs(y)<1. & abs(z)<20. & tracksSize>3 & !isFake"),
      max    = cms.int32(8),
    ),
    cms.PSet(
      label  = cms.string("pvs:step3"),
      src    = cms.InputTag("offlinePrimaryVertices"),
      select = cms.string("abs(x)<1. & abs(y)<1. & abs(z)<20. & tracksSize>3 & !isFake"),
      max    = cms.int32(6),
    ),
    cms.PSet(
      label  = cms.string("pvs:step4"),
      src    = cms.InputTag("offlinePrimaryVertices"),
      select = cms.string("abs(x)<1. & abs(y)<1. & abs(z)<20. & tracksSize>3 & !isFake"),
      max    = cms.int32(4),
    ),
    cms.PSet(
      label  = cms.string("pvs:step5"),
      src    = cms.InputTag("offlinePrimaryVertices"),
      select = cms.string("abs(x)<1. & abs(y)<1. & abs(z)<20. & tracksSize>3 & !isFake"),
      max    = cms.int32(2),
    ),
  )
)

topSingleMuonMediumDQM_HLT_PU = cms.EDAnalyzer("TopSingleLeptonTriggerObjectDQM",
  ## ------------------------------------------------------
  ## SETUP
  ##
  ## configuration of the MonitoringEnsemble(s)
  ## [mandatory] : optional PSets may be omitted
  ##
  setup = cms.PSet(
    ## sub-directory to write the monitor histograms to
    ## [mandatory] : should not be changed w/o explicit
    ## communication to TopCom!
    directory = cms.string("Physics/Top/TopSingleMuonMediumDQM_HLT/"),
    ## [mandatory]
    sources = cms.PSet(
      muons = cms.InputTag("muons"),
      elecs = cms.InputTag("gsfElectrons"),
      jets  = cms.InputTag("ak5CaloJets"),
      mets  = cms.VInputTag("met", "tcMet", "pfMet"),
      pvs   = cms.InputTag("offlinePrimaryVertices")

    ),
    triggerInputs = cms.PSet(
      triggerResults = cms.InputTag("TriggerResults","","HLT"),
      triggerEvent   = cms.InputTag("hltTriggerSummaryAOD","","HLT"),
      paths          = cms.string("HLT_IsoMu17_v5"),
      processName = cms.string('HLT')

    ),

    ## [optional] : when omitted the verbosity level is set to STANDARD
    monitoring = cms.PSet(
      verbosity = cms.string("VERBOSE")
    ),
   
  ),
  ## ------------------------------------------------------
  ## PRESELECTION
  ##
  ## setup of the event preselection, which will not
  ## be monitored
  ## [mandatory] : but may be empty
  ##
  preselection = cms.PSet(
    ## [optional] : when omitted no preselection is applied
    #trigger = cms.PSet(
    #  src    = cms.InputTag("TriggerResults","","HLT"),
    #  select = cms.vstring(['HLT_Mu15_v2'])
    #),
    ## [optional] : when omitted no preselection is applied
    vertex = cms.PSet(
      src    = cms.InputTag("offlinePrimaryVertices"),
      select = cms.string('abs(x)<1. & abs(y)<1. & abs(z)<20. & tracksSize>3 & !isFake')
    )
  ),
  ## ------------------------------------------------------
  ## SELECTION
  ##
  ## monitor histrograms are filled after each selection
  ## step, the selection is applied in the order defined
  ## by this vector
  ## [mandatory] : may be empty or contain an arbitrary
  ## number of PSets
  selection = cms.VPSet(
    cms.PSet(
      label  = cms.string("muons:step0"),
      src    = cms.InputTag("muons"),
      select = cms.string("pt>20 & abs(eta)<2.1 & isGlobalMuon & innerTrack.numberOfValidHits>10 & globalTrack.normalizedChi2>-1 & globalTrack.normalizedChi2<10 & (isolationR03.sumPt+isolationR03.emEt+isolationR03.hadEt)/pt<0.1"),       
      min    = cms.int32(1),
      max    = cms.int32(1),
    ),
    cms.PSet(
      label  = cms.string("pvs:step1"),
      src    = cms.InputTag("offlinePrimaryVertices"),
      select = cms.string("abs(x)<1. & abs(y)<1. & abs(z)<20. & tracksSize>3 & !isFake"),
      max    = cms.int32(10),
    ),
    cms.PSet(
      label  = cms.string("pvs:step2"),
      src    = cms.InputTag("offlinePrimaryVertices"),
      select = cms.string("abs(x)<1. & abs(y)<1. & abs(z)<20. & tracksSize>3 & !isFake"),
      max    = cms.int32(8),
    ),
    cms.PSet(
      label  = cms.string("pvs:step3"),
      src    = cms.InputTag("offlinePrimaryVertices"),
      select = cms.string("abs(x)<1. & abs(y)<1. & abs(z)<20. & tracksSize>3 & !isFake"),
      max    = cms.int32(6),
    ),
    cms.PSet(
      label  = cms.string("pvs:step4"),
      src    = cms.InputTag("offlinePrimaryVertices"),
      select = cms.string("abs(x)<1. & abs(y)<1. & abs(z)<20. & tracksSize>3 & !isFake"),
      max    = cms.int32(4),
    ),
    cms.PSet(
      label  = cms.string("pvs:step5"),
      src    = cms.InputTag("offlinePrimaryVertices"),
      select = cms.string("abs(x)<1. & abs(y)<1. & abs(z)<20. & tracksSize>3 & !isFake"),
      max    = cms.int32(2),
    ),
  )
)

topSingleElectronLooseDQM_HLT_PU = cms.EDAnalyzer("TopSingleLeptonTriggerObjectDQM",
  ## ------------------------------------------------------
  ## SETUP
  ##
  ## configuration of the MonitoringEnsemble(s)
  ## [mandatory] : optional PSets may be omitted
  ##
  setup = cms.PSet(
    ## sub-directory to write the monitor histograms to
    ## [mandatory] : should not be changed w/o explicit
    ## communication to TopCom!
    directory = cms.string("Physics/Top/TopSingleElectronLooseDQM_HLT/"),
    ## [mandatory]
    sources = cms.PSet(
      muons = cms.InputTag("muons"),
      elecs = cms.InputTag("gsfElectrons"),
      jets  = cms.InputTag("ak5CaloJets"),
      mets  = cms.VInputTag("met", "tcMet", "pfMet"),
      pvs   = cms.InputTag("offlinePrimaryVertices")

    ),
       triggerInputs = cms.PSet(
      triggerResults = cms.InputTag("TriggerResults","","HLT"),
      triggerEvent   = cms.InputTag("hltTriggerSummaryAOD","","HLT"),
      paths          = cms.string("HLT_IsoMu17_v5"),
      processName = cms.string('HLT')

    ),

    ## [optional] : when omitted the verbosity level is set to STANDARD
    monitoring = cms.PSet(
      verbosity = cms.string("VERBOSE")
    ),
    
  ),
  ## ------------------------------------------------------
  ## PRESELECTION
  ##
  ## setup of the event preselection, which will not
  ## be monitored
  ## [mandatory] : but may be empty
  ##
  preselection = cms.PSet(
    ## [optional] : when omitted no preselection is applied
    #trigger = cms.PSet(
    #  src    = cms.InputTag("TriggerResults","","HLT"),
    #  select = cms.vstring(['HLT_Ele15_SW_CaloEleId_L1R'])
    #),
    ## [optional] : when omitted no preselection is applied
    vertex = cms.PSet(
      src    = cms.InputTag("offlinePrimaryVertices"),
      select = cms.string('abs(x)<1. & abs(y)<1. & abs(z)<20. & tracksSize>3 & !isFake')
    )
  ),
  ## ------------------------------------------------------
  ## SELECTION
  ##
  ## monitor histrograms are filled after each selection
  ## step, the selection is applied in the order defined
  ## by this vector
  ## [mandatory] : may be empty or contain an arbitrary
  ## number of PSets
  selection = cms.VPSet(
    cms.PSet(
      label  = cms.string("elecs:step0"),
      src    = cms.InputTag("gsfElectrons"),
      electronId = cms.PSet( src = cms.InputTag("simpleEleId70cIso"), pattern = cms.int32(1) ),
      select = cms.string("pt>15 & abs(eta)<2.5"),
      min    = cms.int32(1),
    ),
    cms.PSet(
      label  = cms.string("pvs:step1"),
      src    = cms.InputTag("offlinePrimaryVertices"),
      select = cms.string("abs(x)<1. & abs(y)<1. & abs(z)<20. & tracksSize>3 & !isFake"),
      max    = cms.int32(10),
    ),
    cms.PSet(
      label  = cms.string("pvs:step2"),
      src    = cms.InputTag("offlinePrimaryVertices"),
      select = cms.string("abs(x)<1. & abs(y)<1. & abs(z)<20. & tracksSize>3 & !isFake"),
      max    = cms.int32(8),
    ),
    cms.PSet(
      label  = cms.string("pvs:step3"),
      src    = cms.InputTag("offlinePrimaryVertices"),
      select = cms.string("abs(x)<1. & abs(y)<1. & abs(z)<20. & tracksSize>3 & !isFake"),
      max    = cms.int32(6),
    ),
    cms.PSet(
      label  = cms.string("pvs:step4"),
      src    = cms.InputTag("offlinePrimaryVertices"),
      select = cms.string("abs(x)<1. & abs(y)<1. & abs(z)<20. & tracksSize>3 & !isFake"),
      max    = cms.int32(4),
    ),
    cms.PSet(
      label  = cms.string("pvs:step5"),
      src    = cms.InputTag("offlinePrimaryVertices"),
      select = cms.string("abs(x)<1. & abs(y)<1. & abs(z)<20. & tracksSize>3 & !isFake"),
      max    = cms.int32(2),
    ),
  )
)

topSingleElectronMediumDQM_HLT_PU = cms.EDAnalyzer("TopSingleLeptonTriggerObjectDQM",
  ## ------------------------------------------------------
  ## SETUP
  ##
  ## configuration of the MonitoringEnsemble(s)
  ## [mandatory] : optional PSets may be omitted
  ##
  setup = cms.PSet(
    ## sub-directory to write the monitor histograms to
    ## [mandatory] : should not be changed w/o explicit
    ## communication to TopCom!
    directory = cms.string("Physics/Top/TopSingleElectronMediumDQM_HLT/"),
    ## [mandatory]
    sources = cms.PSet(
      muons = cms.InputTag("muons"),
      elecs = cms.InputTag("gsfElectrons"),
      jets  = cms.InputTag("ak5CaloJets"),
      mets  = cms.VInputTag("met", "tcMet", "pfMet"),
      pvs   = cms.InputTag("offlinePrimaryVertices")

    ),
        triggerInputs = cms.PSet(
      triggerResults = cms.InputTag("TriggerResults","","HLT"),
      triggerEvent   = cms.InputTag("hltTriggerSummaryAOD","","HLT"),
      paths          = cms.string("HLT_IsoMu17_v5"),
      processName = cms.string('HLT')

    ),

    ## [optional] : when omitted the verbosity level is set to STANDARD
    monitoring = cms.PSet(
      verbosity = cms.string("VERBOSE")
    ),
    
  ),
  ## ------------------------------------------------------
  ## PRESELECTION
  ##
  ## setup of the event preselection, which will not
  ## be monitored
  ## [mandatory] : but may be empty
  ##
  preselection = cms.PSet(
    ## [optional] : when omitted no preselection is applied
    vertex = cms.PSet(
      src    = cms.InputTag("offlinePrimaryVertices"),
      select = cms.string('abs(x)<1. & abs(y)<1. & abs(z)<20. & tracksSize>3 & !isFake')
    )
  ),
  ## ------------------------------------------------------
  ## SELECTION
  ##
  ## monitor histrograms are filled after each selection
  ## step, the selection is applied in the order defined
  ## by this vector
  ## [mandatory] : may be empty or contain an arbitrary
  ## number of PSets
  selection = cms.VPSet(
    cms.PSet(
      label = cms.string("elecs:step0"),
      src   = cms.InputTag("gsfElectrons"),
      electronId = cms.PSet( src = cms.InputTag("simpleEleId70cIso"), pattern = cms.int32(1) ),
      select = cms.string("pt>25 & abs(eta)<2.5 & (dr03TkSumPt+dr03EcalRecHitSumEt+dr03HcalTowerSumEt)/pt<0.1"),
      min = cms.int32(1),
      max = cms.int32(1),
    ),
    cms.PSet(
      label  = cms.string("pvs:step1"),
      src    = cms.InputTag("offlinePrimaryVertices"),
      select = cms.string("abs(x)<1. & abs(y)<1. & abs(z)<20. & tracksSize>3 & !isFake"),
      max    = cms.int32(10),
    ),
    cms.PSet(
      label  = cms.string("pvs:step2"),
      src    = cms.InputTag("offlinePrimaryVertices"),
      select = cms.string("abs(x)<1. & abs(y)<1. & abs(z)<20. & tracksSize>3 & !isFake"),
      max    = cms.int32(8),
    ),
    cms.PSet(
      label  = cms.string("pvs:step3"),
      src    = cms.InputTag("offlinePrimaryVertices"),
      select = cms.string("abs(x)<1. & abs(y)<1. & abs(z)<20. & tracksSize>3 & !isFake"),
      max    = cms.int32(6),
    ),
    cms.PSet(
      label  = cms.string("pvs:step4"),
      src    = cms.InputTag("offlinePrimaryVertices"),
      select = cms.string("abs(x)<1. & abs(y)<1. & abs(z)<20. & tracksSize>3 & !isFake"),
      max    = cms.int32(4),
    ),
    cms.PSet(
      label  = cms.string("pvs:step5"),
      src    = cms.InputTag("offlinePrimaryVertices"),
      select = cms.string("abs(x)<1. & abs(y)<1. & abs(z)<20. & tracksSize>3 & !isFake"),
      max    = cms.int32(2),
    ),
  )
)
