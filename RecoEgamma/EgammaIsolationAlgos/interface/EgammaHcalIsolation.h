#ifndef EgammaIsolationAlgos_EgammaHcalIsolation_h
#define EgammaIsolationAlgos_EgammaHcalIsolation_h
//*****************************************************************************
// File:      EgammaHcalIsolation.h
// ----------------------------------------------------------------------------
// OrigAuth:  Matthias Mozer
// Institute: IIHE-VUB
//=============================================================================
//*****************************************************************************

//C++ includes
#include <vector>
#include <functional>

//CMSSW includes
#include "FWCore/Framework/interface/ESHandle.h"
#include "DataFormats/RecoCandidate/interface/RecoCandidate.h"
#include "Geometry/CaloGeometry/interface/CaloGeometry.h"
#include "RecoCaloTools/Selectors/interface/CaloDualConeSelector.h"
#include "DataFormats/GeometryVector/interface/GlobalPoint.h"
#include "DataFormats/GeometryVector/interface/GlobalVector.h"
#include "DataFormats/EgammaReco/interface/SuperCluster.h"
#include "DataFormats/EgammaReco/interface/SuperClusterFwd.h"
#include "DataFormats/HcalRecHit/interface/HcalRecHitCollections.h"

////SJ
#include "Geometry/Records/interface/CaloGeometryRecord.h"

//Sum helper functions
double scaleToE(const double &eta);
double scaleToEt(const double &eta);

class EgammaHcalIsolation {
public:
  //enum HcalDepth { AllDepths = 0, Depth1 = 1, Depth2 = 2 };
  enum HcalDepth { AllDepths = 0, Depth1 = 1, Depth2 = 2, Depth3 = 3, Depth4 = 4, Depth5 = 5, Depth6 = 6, Depth7 = 7 }; ////SJ
  //enum HcalDepth { AllDepths = 0, Depth1 = 1, Depth2 = 2, Depth3 = 3}; ////SJ
  //constructors
  EgammaHcalIsolation(double extRadius,
                      double intRadius,
                      /*double eLowB,
                      double eLowE,
                      double etLowB,
                      double etLowE,
		      */
                      double eLowBD1,
                      double eLowBD2,
                      double eLowB,
                      double eLowED1,
                      double eLowE,
                      edm::ESHandle<CaloGeometry> theCaloGeom,
                      const HBHERecHitCollection &mhbhe);

  //destructor
  ~EgammaHcalIsolation();

  //AllDepths
  double getHcalESum(const reco::Candidate *c) const { return getHcalESum(c->get<reco::SuperClusterRef>().get()); }
  double getHcalEtSum(const reco::Candidate *c) const { return getHcalEtSum(c->get<reco::SuperClusterRef>().get()); }
  double getHcalESum(const reco::SuperCluster *sc) const { return getHcalESum(sc->position()); }
  double getHcalEtSum(const reco::SuperCluster *sc) const { return getHcalEtSum(sc->position()); }
  double getHcalESum(const math::XYZPoint &p) const { return getHcalESum(GlobalPoint(p.x(), p.y(), p.z())); }
  double getHcalEtSum(const math::XYZPoint &p) const { return getHcalEtSum(GlobalPoint(p.x(), p.y(), p.z())); }
  double getHcalESum(const GlobalPoint &pclu) const { return getHcalSum(pclu, AllDepths, &scaleToE); }
  double getHcalEtSum(const GlobalPoint &pclu) const { return getHcalSum(pclu, AllDepths, &scaleToEt); }

  //Depth1
  double getHcalESumDepth1(const reco::Candidate *c) const {
    return getHcalESumDepth1(c->get<reco::SuperClusterRef>().get());
  }
  double getHcalEtSumDepth1(const reco::Candidate *c) const {
    return getHcalEtSumDepth1(c->get<reco::SuperClusterRef>().get());
  }
  double getHcalESumDepth1(const reco::SuperCluster *sc) const { return getHcalESumDepth1(sc->position()); }
  double getHcalEtSumDepth1(const reco::SuperCluster *sc) const { return getHcalEtSumDepth1(sc->position()); }
  double getHcalESumDepth1(const math::XYZPoint &p) const {
    return getHcalESumDepth1(GlobalPoint(p.x(), p.y(), p.z()));
  }
  double getHcalEtSumDepth1(const math::XYZPoint &p) const {
    return getHcalEtSumDepth1(GlobalPoint(p.x(), p.y(), p.z()));
  }
  double getHcalESumDepth1(const GlobalPoint &pclu) const { return getHcalSum(pclu, Depth1, &scaleToE); }
  double getHcalEtSumDepth1(const GlobalPoint &pclu) const { return getHcalSum(pclu, Depth1, &scaleToEt); }

  //Depth2
  double getHcalESumDepth2(const reco::Candidate *c) const {
    return getHcalESumDepth2(c->get<reco::SuperClusterRef>().get());
  }
  double getHcalEtSumDepth2(const reco::Candidate *c) const {
    return getHcalEtSumDepth2(c->get<reco::SuperClusterRef>().get());
  }
  double getHcalESumDepth2(const reco::SuperCluster *sc) const { return getHcalESumDepth2(sc->position()); }
  double getHcalEtSumDepth2(const reco::SuperCluster *sc) const { return getHcalEtSumDepth2(sc->position()); }
  double getHcalESumDepth2(const math::XYZPoint &p) const {
    return getHcalESumDepth2(GlobalPoint(p.x(), p.y(), p.z()));
  }
  double getHcalEtSumDepth2(const math::XYZPoint &p) const {
    return getHcalEtSumDepth2(GlobalPoint(p.x(), p.y(), p.z()));
  }
  double getHcalESumDepth2(const GlobalPoint &pclu) const { return getHcalSum(pclu, Depth2, &scaleToE); }
  double getHcalEtSumDepth2(const GlobalPoint &pclu) const { return getHcalSum(pclu, Depth2, &scaleToEt); }

  /////////////////SJ
  HcalDetId rechitOf(const reco::CaloCluster& cluster) const;  ////Check this again
  std::vector<HcalDetId> rechitsOf(const reco::SuperCluster& sc) const; ////Check this again
  /////////////////SJ


  ///////SJ ---> this is for behind the BC
  double getHcalESumDepth1(const std::vector<HcalDetId>& rechits) const { return getHcalSum(rechits, Depth1); }
  double getHcalESumDepth2(const std::vector<HcalDetId>& rechits) const { return getHcalSum(rechits, Depth2); }


  /////SJ for all the depths
  //////////////////////////////Depth
  double getHcalEDepth(const reco::Candidate *c, const int depth) const {
    //HcalDepth dep = static_cast<HcalDepth>(depth);
    return getHcalEDepth(c->get<reco::SuperClusterRef>().get(), depth);
  }
  double getHcalEtDepth(const reco::Candidate *c, const int depth) const {
    //HcalDepth dep = static_cast<HcalDepth>(depth);   
    return getHcalEtDepth(c->get<reco::SuperClusterRef>().get(), depth);
  }
  double getHcalEDepth(const reco::SuperCluster *sc, const int depth) const { 
    HcalDepth dep = static_cast<HcalDepth>(depth);   
    std::cout<<"SJ!!! int depths : HcalDepth dep "<<depth<<" "<<dep<<std::endl;
    
    return getHcalEDepth(sc->position(), dep); 
}
  double getHcalEtDepth(const reco::SuperCluster *sc, const int depth) const { 
    HcalDepth dep = static_cast<HcalDepth>(depth); 
    return getHcalEtDepth(sc->position(), dep); 
  }
  double getHcalEDepth(const math::XYZPoint &p, const HcalDepth dep) const {
    return getHcalEDepth(GlobalPoint(p.x(), p.y(), p.z()), dep);
  }
  double getHcalEtDepth(const math::XYZPoint &p, const HcalDepth dep) const {
    return getHcalEtDepth(GlobalPoint(p.x(), p.y(), p.z()), dep);
  }
  double getHcalEDepth(const GlobalPoint &pclu, const HcalDepth dep) const { return getHcalSum(pclu, dep, &scaleToE); }
  double getHcalEtDepth(const GlobalPoint &pclu, const HcalDepth dep) const { return getHcalSum(pclu, dep, &scaleToEt); }
  ///////////////////////////////////////

private:
  bool isDepth2(const DetId &) const;
  double getHcalSum(const GlobalPoint &, const HcalDepth &, double (*)(const double &)) const;

  double getHcalSum(const std::vector<HcalDetId>& rechits,  const HcalDepth& depth) const; ///SJ
  ////SJ
  bool passEBEThresh(double energy, const DetId& detId) const;
  bool passEEEThresh(double energy, const DetId& detId) const;

  double extRadius_;
  double intRadius_;

  ///SJ
  /*
  double eLowB_;
  double eLowE_;
  double etLowE_;
  double etLowB_;
  */
  ////SJs
  double eLowBD1_;
  double eLowBD2_;
  double eLowB_;
  double eLowED1_;
  double eLowE_;

  edm::ESHandle<CaloGeometry> theCaloGeom_;
  const HBHERecHitCollection &mhbhe_;

  const CaloGeometry* caloGeom; ///SJ
  unsigned int NMaxClusters_; ///SJ

  CaloDualConeSelector<HBHERecHit> *doubleConeSel_;
};

///SJ
bool CaloClusterGreaterThan(const reco::CaloClusterPtr& c1, const reco::CaloClusterPtr& c2); ///Think if we want to use the one in EgammaHcalTower

#endif
