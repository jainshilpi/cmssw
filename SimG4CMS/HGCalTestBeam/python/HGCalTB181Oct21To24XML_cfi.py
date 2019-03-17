import FWCore.ParameterSet.Config as cms

XMLIdealGeometryESSource = cms.ESSource("XMLIdealGeometryESSource",
    geomXMLFiles = cms.vstring('Geometry/CMSCommonData/data/materials.xml',
        'Geometry/CMSCommonData/data/rotations.xml',
        'Geometry/HGCalCommonData/data/TB181/Oct18/cms.xml',
        'Geometry/HGCalCommonData/data/TB181/Oct18/21To24Oct/hgcal.xml',
        'Geometry/HGCalCommonData/data/TB181/Oct18/21To24Oct/hgcalEE.xml',
        'Geometry/HGCalCommonData/data/TB181/Oct18/21To24Oct/hgcalHE.xml',
        'Geometry/HGCalCommonData/data/hgcalwafer/v7/hgcalwafer.xml',
        'Geometry/HGCalCommonData/data/TB181/Oct18/21To24Oct/hgcalBeam.xml',
        'Geometry/HGCalCommonData/data/TB181/Oct18/21To24Oct/hgcalsense.xml',
        'Geometry/HGCalCommonData/data/TB181/hgcProdCuts.xml',
        'Geometry/HGCalCommonData/data/TB181/Oct18/21To24Oct/hgcalCons.xml'),
    rootNodeName = cms.string('cms:OCMS')
)


