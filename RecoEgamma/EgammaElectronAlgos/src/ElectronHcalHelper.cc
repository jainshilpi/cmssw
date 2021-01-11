
#include "RecoEgamma/EgammaElectronAlgos/interface/ElectronHcalHelper.h"
#include "RecoEgamma/EgammaIsolationAlgos/interface/EgammaHcalIsolation.h"
#include "RecoEgamma/EgammaIsolationAlgos/interface/EgammaTowerIsolation.h"
#include "RecoEgamma/EgammaIsolationAlgos/interface/EgammaHadTower.h"
#include "Geometry/Records/interface/CaloGeometryRecord.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"

using namespace reco;

ElectronHcalHelper::ElectronHcalHelper(const Configuration& cfg)
    : cfg_(cfg), caloGeomCacheId_(0), hcalIso_(nullptr), towerIso1_(nullptr), towerIso2_(nullptr), hadTower_(nullptr) {}

void ElectronHcalHelper::checkSetup(const edm::EventSetup& es) {
  if (cfg_.hOverEConeSize == 0) {
    return;
  }

  if (cfg_.useTowers) {
    delete hadTower_;
    hadTower_ = new EgammaHadTower(es);
  } else {
    unsigned long long newCaloGeomCacheId_ = es.get<CaloGeometryRecord>().cacheIdentifier();
    if (caloGeomCacheId_ != newCaloGeomCacheId_) {
      caloGeomCacheId_ = newCaloGeomCacheId_;
      es.get<CaloGeometryRecord>().get(caloGeom_);
    }
  }
}

void ElectronHcalHelper::readEvent(const edm::Event& evt) {
  if (cfg_.hOverEConeSize == 0) {
    return;
  }

  if (cfg_.useTowers) {
    delete towerIso1_;
    towerIso1_ = nullptr;
    delete towerIso2_;
    towerIso2_ = nullptr;

    edm::Handle<CaloTowerCollection> towersH_;
    if (!evt.getByToken(cfg_.hcalTowers, towersH_)) {
      edm::LogError("ElectronHcalHelper::readEvent") << "failed to get the hcal towers";
    }
    hadTower_->setTowerCollection(towersH_.product());
    towerIso1_ = new EgammaTowerIsolation(cfg_.hOverEConeSize, 0., cfg_.hOverEPtMin, 1, towersH_.product());
    towerIso2_ = new EgammaTowerIsolation(cfg_.hOverEConeSize, 0., cfg_.hOverEPtMin, 2, towersH_.product());
  } else {
    delete hcalIso_;
    hcalIso_ = nullptr;

    edm::Handle<HBHERecHitCollection> hbhe_;
    if (!evt.getByToken(cfg_.hcalRecHits, hbhe_)) {
      edm::LogError("ElectronHcalHelper::readEvent") << "failed to get the rechits";
    }

    ///SJ
    //hcalIso_ = new EgammaHcalIsolation(
    //  cfg_.hOverEConeSize, 0., cfg_.hOverEHBMinE, cfg_.hOverEHFMinE, 0., 0., caloGeom_, *hbhe_);

    hcalIso_ = new EgammaHcalIsolation(
				       cfg_.hOverEConeSize, 0., cfg_.HBThreshold1, cfg_.HBThreshold2, cfg_.HBThreshold, cfg_.HEThreshold1, cfg_.HEThreshold, caloGeom_, *hbhe_);

  }

  std::cout<<"SJ!!! All the confnig params: hOverEConeSize : hOverEPtMin : hOverEHBMinE : hOverEHFMinE : "<<cfg_.hOverEConeSize<<" "<<cfg_.hOverEPtMin<<" "<<cfg_.hOverEHBMinE<<" "<<cfg_.hOverEHFMinE<<std::endl;
}

///SJ
/*
std::vector<CaloTowerDetId> ElectronHcalHelper::hcalTowersBehindClusters(const reco::SuperCluster& sc) const {
  return hadTower_->towersOf(sc);
}
*/

///SJ
std::vector<CaloTowerDetId> ElectronHcalHelper::hcalTowersBehindClusters(const reco::SuperCluster& sc) const { 
  
  return hadTower_->towersOf(sc);
}


///SJ
std::vector<HcalDetId> ElectronHcalHelper::hcalRecHitsBehindClusters(const reco::SuperCluster& sc) const {
  
  return hcalIso_->rechitsOf(sc);
}

/////////////SJ
double ElectronHcalHelper::hcalESumDepth1BehindClusters(const std::vector<CaloTowerDetId>& towers) const {
  
  return hadTower_->getDepth1HcalESum(towers);  ////seems this is E sum not Et sum

}

double ElectronHcalHelper::hcalESumDepth2BehindClusters(const std::vector<CaloTowerDetId>& towers) const {
  
  return hadTower_->getDepth2HcalESum(towers);  ////seems this is E sum not Et sum

}

///SJ
double ElectronHcalHelper::hcalESumRecHitDepth1BehindClusters(const std::vector<HcalDetId>& towers) const {

  return hcalIso_->getHcalESumDepth1(towers); /// so get the E sum again 

}

///SJ
double ElectronHcalHelper::hcalESumRecHitDepth2BehindClusters(const std::vector<HcalDetId>& towers) const {

  return hcalIso_->getHcalESumDepth2(towers); 

}

/*
double ElectronHcalHelper::hcalESumDepth1BehindClusters(const std::vector<CaloTowerDetId>& towers) const {
  return hadTower_->getDepth1HcalESum(towers);
}

double ElectronHcalHelper::hcalESumDepth2BehindClusters(const std::vector<CaloTowerDetId>& towers) const {
  return hadTower_->getDepth2HcalESum(towers);
}
*/

////SJ
////is it Et sum or E sum???
double ElectronHcalHelper::hcalESum(const SuperCluster& sc, const std::vector<CaloTowerDetId>* excludeTowers) const {
  if (cfg_.hOverEConeSize == 0) {
    return 0;
  }
  if (cfg_.useTowers) {
    return (hcalESumDepth1(sc, excludeTowers) + hcalESumDepth2(sc, excludeTowers));
  } else {
    return hcalIso_->getHcalESum(&sc);
  }
}

/*
///SJ
double ElectronHcalHelper::hcalESum(const SuperCluster& sc, const std::vector<CaloTowerDetId>* excludeTowers) const {
  if (cfg_.hOverEConeSize == 0) {
    return 0;
  }
  if (cfg_.useTowers) {
    return (hcalESumDepth1(sc, excludeTowers) + hcalESumDepth2(sc, excludeTowers));
  } else {
    return hcalIso_->getHcalESum(&sc);
  }
}
*/
////this is in a max cone
double ElectronHcalHelper::hcalESumDepth1(const SuperCluster& sc,
                                          const std::vector<CaloTowerDetId>* excludeTowers) const {
  if (cfg_.hOverEConeSize == 0) {
    return 0;
  }
  if (cfg_.useTowers) {
    return towerIso1_->getTowerESum(&sc, excludeTowers);
  } else {
    return hcalIso_->getHcalESumDepth1(&sc);
  }
}

double ElectronHcalHelper::hcalESumDepth2(const SuperCluster& sc,
                                          const std::vector<CaloTowerDetId>* excludeTowers) const {
  if (cfg_.hOverEConeSize == 0) {
    return 0;
  }
  if (cfg_.useTowers) {
    return towerIso2_->getTowerESum(&sc, excludeTowers);
  } else {
    return hcalIso_->getHcalESumDepth2(&sc);
  }
}


////SJ - ones related to depth for run 3
///working on HCAL rechits for now. Once Aram replies, I will update the depth info for tower based

//////22sept ---> just do it for rechit based
double ElectronHcalHelper::hcalEDepth(const SuperCluster& sc,
				      //const std::vector<CaloTowerDetId>* excludeTowers,
				      const int depth) const {
  if (cfg_.hOverEConeSize == 0) {
    return 0;
  }
  return hcalIso_->getHcalEDepth(&sc, depth);

}


bool ElectronHcalHelper::hasActiveHcal(const reco::SuperCluster& sc) const {
  if (cfg_.checkHcalStatus && cfg_.hOverEConeSize != 0 && cfg_.useTowers) {
    return hadTower_->hasActiveHcal(sc);
  } else {
    return true;
  }
}

ElectronHcalHelper::~ElectronHcalHelper() {
  if (cfg_.hOverEConeSize == 0) {
    return;
  }
  if (cfg_.useTowers) {
    delete towerIso1_;
    delete towerIso2_;
    delete hadTower_;
  } else {
    delete hcalIso_;
  }
}
