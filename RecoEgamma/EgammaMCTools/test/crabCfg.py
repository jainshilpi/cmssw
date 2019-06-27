from CRABClient.UserUtilities import config

config = config()

#submitVersion = "10X_V0"
#submitVersion = "10X_VB"
#submitVersion = "150_V0_2017"
submitVersion = "150_V1_2017"
#submitVersion = "MC18_V2_noPU"
mainOutputDir = '/store/group/phys_egamma/PFClusterCalibration/%s' % submitVersion

config.General.workArea                 = './'
config.General.transferOutputs          = True
config.General.transferLogs             = True

config.JobType.pluginName               = 'Analysis'
config.JobType.psetName                 = 'pfClusterForCalibration.py'
#config.JobType.psetName                 = 'pfClusterForCalibration_ECALThB.py'
config.JobType.allowUndistributedCMSSW  = True

config.Data.inputDBS                    = 'global'
#config.Data.splitting                   = 'FileBased'
config.Data.splitting                   = 'LumiBased'
config.Data.unitsPerJob                 = 9
config.JobType.numCores                = 4
config.Data.useParent                   = True
config.Data.publication                 = True
config.Data.outLFNDirBase = '%s/%s/' % (mainOutputDir,'mc')
config.Data.allowNonValidInputDataset = True 

config.Site.storageSite                 = 'T2_CH_CERN'

if __name__ == '__main__':

    datasets = {

        #'DoublePhotonNoMaterial_FlatPt-0p0To10_noPU' : '/DoublePhotonNoMaterial_FlatPt-0p01To10/RunIISummer18DR-NoPUExtZeroMat_NoMaterial_101X_upgrade2018_realistic_v7-v1/AODSIM', 
        #'DoublePhotonNoMaterial_FlatPt-0p0To10_0to70PU' : '/DoublePhotonNoMaterial_FlatPt-0p01To10/RunIISummer18DR-FlatPU0to70ExtZeroMat_NoMaterial_101X_upgrade2018_realistic_v7-v1/AODSIM',
        #'DoublePhotonNoMaterial_FlatPt-10To300_noPU' : '/DoublePhotonNoMaterial_FlatPt-10To300/RunIISummer18DR-NoPUExtZeroMat_NoMaterial_101X_upgrade2018_realistic_v7-v1/AODSIM', 
        #'DoublePhotonNoMaterial_FlatPt-10To300_0to70PU' : '/DoublePhotonNoMaterial_FlatPt-10To300/RunIISummer18DR-FlatPU0to70ExtZeroMat_NoMaterial_101X_upgrade2018_realistic_v7-v1/AODSIM'


        #'DoublePhotonNoMaterial_FlatPt-0p0To10_noPU' : '/DoublePhotonNoMaterial_FlatPt-0p01To10/RunIIWinter19PFCalibDR-2017ConditionsNoPUExtZeroMaterial_NoMaterial_105X_mc2017_realistic_v5-v1/AODSIM',
        #'DoublePhotonNoMaterial_FlatPt-0p0To10_0to70PU' : '/DoublePhotonNoMaterial_FlatPt-0p01To10/RunIIWinter19PFCalibDR-2017ConditionsFlatPU0to70ExtZeroMaterial_NoMaterial_105X_mc2017_realistic_v5-v1/AODSIM',
        'DoublePhotonNoMaterial_FlatPt-10To300_noPU' : '/DoublePhotonNoMaterial_FlatPt-10To300/RunIIWinter19PFCalibDR-2017ConditionsNoPUExtZeroMaterial_NoMaterial_105X_mc2017_realistic_v5-v1/AODSIM', 
        #'DoublePhotonNoMaterial_FlatPt-10To300_0to70PU' : '/DoublePhotonNoMaterial_FlatPt-10To300/RunIIWinter19PFCalibDR-2017ConditionsFlatPU0to70ExtZeroMaterial_NoMaterial_105X_mc2017_realistic_v5-v1/AODSIM'

        }

    from CRABAPI.RawCommand import crabCommand
    from CRABClient.ClientExceptions import ClientException
    from httplib import HTTPException

    def submit(config):
        try:
            crabCommand('submit', config = config)
        except HTTPException as hte:
            print "Failed submitting task: %s" % (hte.headers)
        except ClientException as cle:
            print "Failed submitting task: %s" % (cle)

    for name, dataset in datasets.iteritems():
        config.General.requestName = name
        config.Data.inputDataset = dataset
        submit(config)
