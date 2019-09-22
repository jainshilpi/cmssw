# EGM skimmer
# Author: Rafael Lopes de Sa

import FWCore.ParameterSet.Config as cms

# Run with the 2017 detector
from Configuration.StandardSequences.Eras import eras
process = cms.Process('SKIM',eras.Run2_2017)

# Import the standard packages for reconstruction and digitization
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
process.load('SimGeneral.MixingModule.mixNoPU_cfi')
process.load('Configuration.StandardSequences.Digi_cff')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_cff')
process.load('Configuration.StandardSequences.RawToDigi_cff')
process.load('Configuration.StandardSequences.L1Reco_cff')
process.load('Configuration.StandardSequences.Reconstruction_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
process.load('RecoEgamma.EgammaMCTools.pfClusterMatchedToPhotonsSelector_cfi')

# Global Tag configuration ... just using the same as in the RelVal
from Configuration.AlCa.GlobalTag import GlobalTag
#process.GlobalTag = GlobalTag(process.GlobalTag, '90X_upgrade2017_realistic_ExtendedZeroMaterial_EGM_PFCalib', '')

#process.GlobalTag = GlobalTag(process.GlobalTag, '100X_upgrade2018_realistic_Fromv10ExtZeroMaterial_v1', '')
#process.GlobalTag = GlobalTag(process.GlobalTag, '100X_upgrade2018_realistic_Fromv10ExtZeroMaterial_v1_QUEUE_2018_04_03_20_47_44', '')
process.GlobalTag = GlobalTag(process.GlobalTag, '100X_upgrade2018_realistic_Fromv10ExtZeroMaterial_v1_QUEUE_2018_04_04_09_06_15', '')

#process.MessageLogger.cerr.threshold = 'ERROR'
#process.MessageLogger.cerr.FwkReport.reportEvery = 1000

process.options = cms.untracked.PSet( allowUnscheduled = cms.untracked.bool(True) )

# This is where users have some control.
# Define which collections to save and which dataformat we are using
savedCollections = cms.untracked.vstring('drop *',
# The commented ones are large collections that can be kept for debug
#                                         'keep EcalRecHitsSorted_*_*_*',
#                                         'keep recoPFClusters_*_*_*',
#                                         'keep recoCaloClusters_*_*_*',
#                                         'keep recoSuperClusters_*_*_*', 
#                                         'keep recoGsfElectron*_*_*_*',
#                                         'keep recoPhoton*_*_*_*',
#                                         'keep *_mix_MergedTrackTruth_*',
                                         'keep *_reducedEcalRecHits*_*_*',
                                         'keep double_fixedGridRho*_*_*',
                                         'keep recoGenParticles_*_*_*',
                                         'keep GenEventInfoProduct_*_*_*',
                                         'keep PileupSummaryInfos_*_*_*',
                                         'keep *_ecalDigis_*_*',
                                         'keep *_offlinePrimaryVertices_*_*',
                                         'keep *_particleFlowCluster*_*_*')

#process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(-1))
#process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(100))
process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(20))

process.source = cms.Source("PoolSource",                 
                            fileNames = cms.untracked.vstring(
        '/store/mc/RunIISpring18DR/DoublePhotonNoMaterial_FlatPt-0p01To10/AODSIM/noPUExtZeroMaterial_NoMaterial_100X_upgrade2018_realistic_Fromv10ExtZeroMaterial_v1-v1/70000/2AD780A9-8A23-E811-9415-0025905B85FC.root'
        ),
                            secondaryFileNames = cms.untracked.vstring(

        '/store/mc/RunIISpring18DR/DoublePhotonNoMaterial_FlatPt-0p01To10/GEN-SIM-RAW/noPUExtZeroMaterial_NoMaterial_100X_upgrade2018_realistic_Fromv10ExtZeroMaterial_v1-v1/70000/22BB046D-7123-E811-85FA-0025905B85DC.root',
        '/store/mc/RunIISpring18DR/DoublePhotonNoMaterial_FlatPt-0p01To10/GEN-SIM-RAW/noPUExtZeroMaterial_NoMaterial_100X_upgrade2018_realistic_Fromv10ExtZeroMaterial_v1-v1/70000/28CDF63C-7423-E811-8A94-0CC47A4D7668.root'
)
                            )


process.PFCLUSTERoutput = cms.OutputModule("PoolOutputModule",
                                           dataset = cms.untracked.PSet(dataTier = cms.untracked.string('RECO'),
                                                                        filterName = cms.untracked.string('')
                                                                        ),
                                           eventAutoFlushCompressedSize = cms.untracked.int32(5242880),
                                           fileName = cms.untracked.string('skimEGMobjects_fromRAW.root'),
                                           outputCommands = savedCollections,
                                           splitLevel = cms.untracked.int32(0)
                                           )

# Run the digitizer to make the trackingparticles
process.mix.digitizers = cms.PSet(process.theDigitizersValid)
process.trackingtruth_step = cms.Path(process.pdigi_valid)

# Remake the PFClusters
process.pfclusters_step = cms.Path(process.bunchSpacingProducer *
                                   process.ecalDigis * 
                                   process.ecalPreshowerDigis * 
                                   process.ecalPreshowerRecHit *
                                   process.ecalMultiFitUncalibRecHit *
                                   process.ecalDetIdToBeRecovered *
                                   process.ecalRecHit *
                                   process.particleFlowRecHitPS * 
                                   process.particleFlowRecHitECAL * 
                                   process.particleFlowClusterECALUncorrected * 
                                   process.particleFlowClusterPS *
                                   process.particleFlowClusterECAL)

# Select the PFClusters we want to calibrate
process.particleFlowClusterECALMatchedToPhotons = process.pfClusterMatchedToPhotonsSelector.clone()
process.selection_step = cms.Path(process.particleFlowClusterECALMatchedToPhotons)


#now customise with the new ECAL thresholds
# B ~ 1.0 sigma noise equivalent thresholds
_pfZeroSuppressionThresholds_EB_2018_B = [0.140]*170
_pfZeroSuppressionThresholds_EEminus_2018_B = [0.11, 0.11, 0.12, 0.13, 0.14, 0.15, 0.16, 0.17, 0.17, 0.18, 0.18, 0.19, 0.19, 0.20, 0.22, 0.23, 0.25, 0.27, 0.29, 0.31, 0.34, 0.36, 0.39, 0.42, 0.45, 0.50, 0.57, 0.68, 0.84, 1.07, 1.40, 1.88, 2.55, 3.47, 4.73, 6.42, 8.65, 11.6, 15.4]
_pfZeroSuppressionThresholds_EEplus_2018_B = _pfZeroSuppressionThresholds_EEminus_2018_B

_particle_flow_zero_suppression_ECAL_2018_B = cms.PSet(
    thresholds = cms.vdouble(_pfZeroSuppressionThresholds_EB_2018_B + _pfZeroSuppressionThresholds_EEminus_2018_B + _pfZeroSuppressionThresholds_EEplus_2018_B
        )
    )
#not really necessary but just in case
process.particle_flow_zero_suppression_ECAL = _particle_flow_zero_suppression_ECAL_2018_B

for pset in process.particleFlowRecHitECAL.producers:
    if hasattr(pset,'name') and (pset.name.value() == 'PFEBRecHitCreator' or pset.name.value() == 'PFEERecHitCreator'):
        for qtest in pset.qualityTests:
            if hasattr(qtest,'name') and qtest.name.value() == 'PFRecHitQTestECALMultiThreshold':
                print 'overriding thresholds to ECAL scenario B for ',pset.name.value()
                qtest.thresholds = _particle_flow_zero_suppression_ECAL_2018_B.thresholds

# Ends job and writes our output
process.endjob_step = cms.EndPath(process.endOfProcess)
process.output_step = cms.EndPath(process.PFCLUSTERoutput)

# Schedule definition, rebuilding rechits
process.schedule = cms.Schedule(process.trackingtruth_step,process.pfclusters_step,process.selection_step,process.endjob_step,process.output_step)


