from CRABClient.UserUtilities import config, getUsernameFromSiteDB
import sys
config = config()


#submitVersion = "V0/8To17Oct"
#submitVersion = "V0/8To17Oct/with25umGold"
#submitVersion = "V0/8To17Oct/with1p1mmPCB"
#submitVersion = "V0/8To17Oct/noPCBinEE"
submitVersion = "V0/tmpChecks/BeamPosChecks/"
#mainOutputDir = '/store/group/upgrade/HGCAL/simulation/2018/Oct/%s' % submitVersion
mainOutputDir = '/store/group/upgrade/HGCAL/simulation/2018/Oct/%s' % submitVersion

config.General.transferLogs = False
#config.General.transferLogs = True

config.JobType.pluginName  = 'PRIVATEMC'
config.Data.inputDBS = 'global'
#config.Data.publication = True
config.Data.publication = False
config.Data.splitting     = 'EventBased'
#config.Data.unitsPerJob   = 2000
#config.Data.totalUnits    = 1000000

config.Data.unitsPerJob   = 500
config.Data.totalUnits    = 2000

#config.Data.totalUnits    = 100000

config.JobType.allowUndistributedCMSSW = True

config.Site.storageSite = 'T2_CH_CERN'
#config.Site.whitelist       = ['T3_TW_NCU']
#config.Site.storageSite = 'T3_TW_NCU'

if __name__ == '__main__':

    from CRABAPI.RawCommand import crabCommand
    from CRABClient.ClientExceptions import ClientException
    from httplib import HTTPException

    # We want to put all the CRAB project directories from the tasks we submit here into one common directory.
    # That's why we need to set this parameter (here or above in the configuration file, it does not matter, we will not overwrite it).
    config.General.workArea = 'crab_projects_%s' % submitVersion

    def submit(config):
        try:
            crabCommand('submit', config = config)
        except HTTPException as hte:
            print "Failed submitting task: %s" % (hte.headers)
        except ClientException as cle:
            print "Failed submitting task: %s" % (cle)


    ##### submit MC

    config.Data.outLFNDirBase = '%s/%s/' % (mainOutputDir,'mc')
    config.JobType.psetName  = 'tmp_cfg.py'
    #config.General.requestName  = 'Ele50GeV_beamy123p7'
    #config.General.requestName  = 'Ele50GeV_beamyM123p7'
    #config.General.requestName  = 'Ele50GeV_beamXM10p7127beamYM6p185'
    config.General.requestName  = 'Ele100GeV_beamAllOver'
    submit(config)

