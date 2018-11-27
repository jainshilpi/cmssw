import FWCore.ParameterSet.Config as cms

#-------------------------------------------------
#AlCaReco filtering for HCAL HEMuon:
#-------------------------------------------------
import HLTrigger.HLTfilters.hltHighLevel_cfi
ALCARECOHcalCalHEMuonFilterHLT = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone(
    HLTPaths           = cms.vstring('DoubleMuon'),
    eventSetupPathsKey = cms.string('HcalCalHEMuonFilter'),
    throw = False #dont throw except on unknown path name
)

from Calibration.HcalAlCaRecoProducers.alcaHEMuonFilter_cfi import *

seqALCARECOHcalCalHEMuonFilter = cms.Sequence(ALCARECOHcalCalHEMuonFilterHLT *
                                              alcaHEMuonFilter)
