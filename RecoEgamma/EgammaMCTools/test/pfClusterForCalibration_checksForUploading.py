# EGM skimmer
# Author: Rafael Lopes de Sa

import FWCore.ParameterSet.Config as cms

# Run with the 2017 detector
from Configuration.StandardSequences.Eras import eras
#process = cms.Process('SKIM',eras.Run2_2017)
process = cms.Process('SKIM',eras.Run2_2018)

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
#process.GlobalTag = GlobalTag(process.GlobalTag, '101X_upgrade2018_realistic_v7', '')
#process.GlobalTag = GlobalTag(process.GlobalTag, '105X_mc2017_realistic_v5', '')
process.GlobalTag = GlobalTag(process.GlobalTag, '105X_upgrade2018_realistic_v4', '')



###replace here
process.GlobalTag.toGet.extend( cms.VPSet(
#process.GlobalTag.toGet.replace( cms.VPSet(
        cms.PSet(
            record = cms.string('GBRDWrapperRcd'),
            tag = cms.string('ecalPFClusterCor2018ULV2_EB_ZS_mean_25ns'),
            label = cms.untracked.string('ecalPFClusterCor2017V2_EB_ZS_mean_25ns'),
            connect = cms.string('sqlite_file:ecalPFClusterCor2018ULV2_EB_ZS_mean_25ns.db')
            ),
        cms.PSet(
            record = cms.string('GBRDWrapperRcd'),
            tag = cms.string('ecalPFClusterCor2018ULV2_EB_Full_ptbin1_mean_25ns'),
            label = cms.untracked.string('ecalPFClusterCor2017V2_EB_Full_ptbin1_mean_25ns'),
            connect = cms.string('sqlite_file:ecalPFClusterCor2018ULV2_EB_Full_ptbin1_mean_25ns.db')
            ),
        cms.PSet(
            record = cms.string('GBRDWrapperRcd'),
            tag = cms.string('ecalPFClusterCor2018ULV2_EB_Full_ptbin2_mean_25ns'),
            label = cms.untracked.string('ecalPFClusterCor2017V2_EB_Full_ptbin2_mean_25ns'),
            connect = cms.string('sqlite_file:ecalPFClusterCor2018ULV2_EB_Full_ptbin2_mean_25ns.db')
            ),

        cms.PSet(
            record = cms.string('GBRDWrapperRcd'),
            tag = cms.string('ecalPFClusterCor2018ULV2_EB_Full_ptbin3_mean_25ns'),
            label = cms.untracked.string('ecalPFClusterCor2017V2_EB_Full_ptbin3_mean_25ns'),
            connect = cms.string('sqlite_file:ecalPFClusterCor2018ULV2_EB_Full_ptbin3_mean_25ns.db')
            ),

        cms.PSet(
            record = cms.string('GBRDWrapperRcd'),
            tag = cms.string('ecalPFClusterCor2018ULV2_EB_ZS_sigma_25ns'),
            label = cms.untracked.string('ecalPFClusterCor2017V2_EB_ZS_sigma_25ns'),
            connect = cms.string('sqlite_file:ecalPFClusterCor2018ULV2_EB_ZS_sigma_25ns.db')
            ),
        cms.PSet(
            record = cms.string('GBRDWrapperRcd'),
            tag = cms.string('ecalPFClusterCor2018ULV2_EB_Full_ptbin1_sigma_25ns'),
            label = cms.untracked.string('ecalPFClusterCor2017V2_EB_Full_ptbin1_sigma_25ns'),
            connect = cms.string('sqlite_file:ecalPFClusterCor2018ULV2_EB_Full_ptbin1_sigma_25ns.db')
            ),
        cms.PSet(
            record = cms.string('GBRDWrapperRcd'),
            tag = cms.string('ecalPFClusterCor2018ULV2_EB_Full_ptbin2_sigma_25ns'),
            label = cms.untracked.string('ecalPFClusterCor2017V2_EB_Full_ptbin2_sigma_25ns'),
            connect = cms.string('sqlite_file:ecalPFClusterCor2018ULV2_EB_Full_ptbin2_sigma_25ns.db')
            ),
        cms.PSet(
            record = cms.string('GBRDWrapperRcd'),
            tag = cms.string('ecalPFClusterCor2018ULV2_EB_Full_ptbin3_sigma_25ns'),
            label = cms.untracked.string('ecalPFClusterCor2017V2_EB_Full_ptbin3_sigma_25ns'),
            connect = cms.string('sqlite_file:ecalPFClusterCor2018ULV2_EB_Full_ptbin3_sigma_25ns.db')
            ),
        cms.PSet(
            record = cms.string('GBRDWrapperRcd'),
            tag = cms.string('ecalPFClusterCor2018ULV2_EE_ZS_mean_25ns'),
            label = cms.untracked.string('ecalPFClusterCor2017V2_EE_ZS_mean_25ns'),
            connect = cms.string('sqlite_file:ecalPFClusterCor2018ULV2_EE_ZS_mean_25ns.db')
            ),
        cms.PSet(
            record = cms.string('GBRDWrapperRcd'),
            tag = cms.string('ecalPFClusterCor2018ULV2_EE_Full_ptbin1_mean_25ns'),
            label = cms.untracked.string('ecalPFClusterCor2017V2_EE_Full_ptbin1_mean_25ns'),
            connect = cms.string('sqlite_file:ecalPFClusterCor2018ULV2_EE_Full_ptbin1_mean_25ns.db')
            ),
        cms.PSet(
            record = cms.string('GBRDWrapperRcd'),
            tag = cms.string('ecalPFClusterCor2018ULV2_EE_Full_ptbin2_mean_25ns'),
            label = cms.untracked.string('ecalPFClusterCor2017V2_EE_Full_ptbin2_mean_25ns'),
            connect = cms.string('sqlite_file:ecalPFClusterCor2018ULV2_EE_Full_ptbin2_mean_25ns.db')
            ),


        cms.PSet(
            record = cms.string('GBRDWrapperRcd'),
            tag = cms.string('ecalPFClusterCor2018ULV2_EE_Full_ptbin3_mean_25ns'),
            label = cms.untracked.string('ecalPFClusterCor2017V2_EE_Full_ptbin3_mean_25ns'),
            connect = cms.string('sqlite_file:ecalPFClusterCor2018ULV2_EE_Full_ptbin3_mean_25ns.db')
            ),


        cms.PSet(
            record = cms.string('GBRDWrapperRcd'),
            tag = cms.string('ecalPFClusterCor2018ULV2_EE_ZS_sigma_25ns'),
            label = cms.untracked.string('ecalPFClusterCor2017V2_EE_ZS_sigma_25ns'),
            connect = cms.string('sqlite_file:ecalPFClusterCor2018ULV2_EE_ZS_sigma_25ns.db')
            ),
        cms.PSet(
            record = cms.string('GBRDWrapperRcd'),
            tag = cms.string('ecalPFClusterCor2018ULV2_EE_Full_ptbin1_sigma_25ns'),
            label = cms.untracked.string('ecalPFClusterCor2017V2_EE_Full_ptbin1_sigma_25ns'),
            connect = cms.string('sqlite_file:ecalPFClusterCor2018ULV2_EE_Full_ptbin1_sigma_25ns.db')
            ),
        cms.PSet(
            record = cms.string('GBRDWrapperRcd'),
            tag = cms.string('ecalPFClusterCor2018ULV2_EE_Full_ptbin2_sigma_25ns'),
            label = cms.untracked.string('ecalPFClusterCor2017V2_EE_Full_ptbin2_sigma_25ns'),
            connect = cms.string('sqlite_file:ecalPFClusterCor2018ULV2_EE_Full_ptbin2_sigma_25ns.db')
            ),
        cms.PSet(
            record = cms.string('GBRDWrapperRcd'),
            tag = cms.string('ecalPFClusterCor2018ULV2_EE_Full_ptbin3_sigma_25ns'),
            label = cms.untracked.string('ecalPFClusterCor2017V2_EE_Full_ptbin3_sigma_25ns'),
            connect = cms.string('sqlite_file:ecalPFClusterCor2018ULV2_EE_Full_ptbin3_sigma_25ns.db')
            ),
        ))


process.MessageLogger.cerr.threshold = 'ERROR'
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

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

#process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(10000))
process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(100))

process.source = cms.Source("PoolSource",                 
                            fileNames = cms.untracked.vstring(
        #'/store/mc/RunIIWinter19PFCalibDR/DoublePhotonNoMaterial_FlatPt-10To300/AODSIM/2018ConditionsFlatPU0to70ExtZeroMaterial_NoMaterial_105X_upgrade2018_realistic_v4-v1/230000/BD8D622F-C9A7-4B4F-A9C1-77C7831B11B5.root'
        '/store/mc/RunIIWinter19PFCalibDR/DoublePhotonNoMaterial_FlatPt-10To300/AODSIM/2018ConditionsFlatPU0to70ExtZeroMaterial_NoMaterial_105X_upgrade2018_realistic_v4-v1/230000/B4DF3A8B-4170-6442-9A04-B60A024EA849.root'
        ),
                            secondaryFileNames = cms.untracked.vstring(

        #'/store/mc/RunIIWinter19PFCalibDR/DoublePhotonNoMaterial_FlatPt-10To300/GEN-SIM-RAW/2018ConditionsFlatPU0to70ExtZeroMaterial_NoMaterial_105X_upgrade2018_realistic_v4-v1/2310000/3913B738-12EE-0B4D-A9EC-847F55E07B92.root',
        #'/store/mc/RunIIWinter19PFCalibDR/DoublePhotonNoMaterial_FlatPt-10To300/GEN-SIM-RAW/2018ConditionsFlatPU0to70ExtZeroMaterial_NoMaterial_105X_upgrade2018_realistic_v4-v1/2310000/4E20A4B6-AB1A-8D43-8F45-1403BDDE9EAC.root',
        #'/store/mc/RunIIWinter19PFCalibDR/DoublePhotonNoMaterial_FlatPt-10To300/GEN-SIM-RAW/2018ConditionsFlatPU0to70ExtZeroMaterial_NoMaterial_105X_upgrade2018_realistic_v4-v1/2310000/B8619FBB-B5D3-C34F-9648-0B7E3072403D.root'


        '/store/mc/RunIIWinter19PFCalibDR/DoublePhotonNoMaterial_FlatPt-10To300/GEN-SIM-RAW/2018ConditionsFlatPU0to70ExtZeroMaterial_NoMaterial_105X_upgrade2018_realistic_v4-v1/2310000/0EE292DE-FC8F-5145-8552-0C1A64ADA497.root',
        '/store/mc/RunIIWinter19PFCalibDR/DoublePhotonNoMaterial_FlatPt-10To300/GEN-SIM-RAW/2018ConditionsFlatPU0to70ExtZeroMaterial_NoMaterial_105X_upgrade2018_realistic_v4-v1/2310000/471659E1-B870-1B49-8E58-BE418D741198.root',
        '/store/mc/RunIIWinter19PFCalibDR/DoublePhotonNoMaterial_FlatPt-10To300/GEN-SIM-RAW/2018ConditionsFlatPU0to70ExtZeroMaterial_NoMaterial_105X_upgrade2018_realistic_v4-v1/2310000/D83A47B1-3B1B-954A-AEC3-DFCBB8FB6AE1.root',
        '/store/mc/RunIIWinter19PFCalibDR/DoublePhotonNoMaterial_FlatPt-10To300/GEN-SIM-RAW/2018ConditionsFlatPU0to70ExtZeroMaterial_NoMaterial_105X_upgrade2018_realistic_v4-v1/2310000/F8DDE8B5-F650-B746-9F9F-E195A1AFC994.root'
)
                            )
process.PFCLUSTERoutput = cms.OutputModule("PoolOutputModule",
                                           dataset = cms.untracked.PSet(dataTier = cms.untracked.string('RECO'),
                                                                        filterName = cms.untracked.string('')
                                                                        ),
                                           eventAutoFlushCompressedSize = cms.untracked.int32(5242880),
                                           fileName = cms.untracked.string('/eos/cms/store/group/phys_egamma/PFClusterCalibration/skimEGMobjects_fromRAW_newCorr.root'),
                                           outputCommands = savedCollections,
                                           splitLevel = cms.untracked.int32(0)
                                           )


#Setup FWK for multithreaded                                                                                                                                                                                
process.options.numberOfThreads=cms.untracked.uint32(4)
process.options.numberOfStreams=cms.untracked.uint32(0)

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

# Ends job and writes our output
process.endjob_step = cms.EndPath(process.endOfProcess)
process.output_step = cms.EndPath(process.PFCLUSTERoutput)

# Schedule definition, rebuilding rechits
process.schedule = cms.Schedule(process.trackingtruth_step,process.pfclusters_step,process.selection_step,process.endjob_step,process.output_step)


print process.dumpPython()
