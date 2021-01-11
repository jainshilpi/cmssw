//*****************************************************************************
// File:      EgammaHcalIsolation.cc
// ----------------------------------------------------------------------------
// OrigAuth:  Matthias Mozer
// Institute: IIHE-VUB
//=============================================================================
//*****************************************************************************
//C++ includes
#include <vector>
#include <functional>

//ROOT includes
#include <Math/VectorUtil.h>

//CMSSW includes
#include "RecoEgamma/EgammaIsolationAlgos/interface/EgammaHcalIsolation.h"
#include "DataFormats/HcalDetId/interface/HcalDetId.h"
#include "Geometry/CommonDetUnit/interface/TrackingGeometry.h"
#include "Geometry/Records/interface/TrackerDigiGeometryRecord.h"
#include "RecoCaloTools/Selectors/interface/CaloConeSelector.h"
#include "DataFormats/RecoCandidate/interface/RecoCandidate.h"

using namespace std;

double scaleToE(const double& eta) { return 1.0; }
double scaleToEt(const double& eta) { return sin(2 * atan(exp(-eta))); }

EgammaHcalIsolation::EgammaHcalIsolation(double extRadius,
                                         double intRadius,
					 ///SJ
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
                                         const HBHERecHitCollection& mhbhe)
    : extRadius_(extRadius),
      intRadius_(intRadius),
///SJ
/* eLowB_(eLowB),
      eLowE_(eLowE),
      etLowB_(etLowB),
      etLowE_(etLowE),
*/
///SJ
      eLowBD1_(eLowBD1),
      eLowBD2_(eLowBD2),
      eLowB_(eLowB),
      eLowED1_(eLowED1),
      eLowE_(eLowE),

      theCaloGeom_(theCaloGeom),
      mhbhe_(mhbhe) {
  //set up the geometry and selector
  //const CaloGeometry* caloGeom = theCaloGeom_.product();
  caloGeom = theCaloGeom_.product(); ///SJ

  NMaxClusters_ = 4; ///SJ

  doubleConeSel_ = new CaloDualConeSelector<HBHERecHit>(intRadius_, extRadius_, caloGeom, DetId::Hcal);
}

EgammaHcalIsolation::~EgammaHcalIsolation() { delete doubleConeSel_; }


//////SJ made changes to include depths
/*
double EgammaHcalIsolation::getHcalSum(const GlobalPoint& pclu,
                                       const HcalDepth& depth,
                                       double (*scale)(const double&)) const {
  double sum = 0.;
  if (!mhbhe_.empty()) {
    //Compute the HCAL energy behind ECAL
    doubleConeSel_->selectCallback(pclu, mhbhe_, [this, &sum, &depth, &scale](const HBHERecHit& i) {
      double eta = theCaloGeom_.product()->getPosition(i.detid()).eta();
      HcalDetId hcalDetId(i.detid());
      /////SJ ---> update the rechit thresholds
      if (hcalDetId.subdet() == HcalBarrel &&         //Is it in the barrel?
      i.energy() > eLowB_ &&                      //Does it pass the min energy?
          i.energy() * scaleToEt(eta) > etLowB_ ) &&    //Does it pass the min et?
	  (depth == AllDepths || depth == Depth1)) {  //Are we asking for the first depth?
	  sum += i.energy() * scale(eta);
      }
      if (hcalDetId.subdet() == HcalEndcap &&       //Is it in the endcap?
          i.energy() > eLowE_ &&                    //Does it pass the min energy?
          i.energy() * scaleToEt(eta) > etLowE_) {  //Does it pass the min et?
        switch (depth) {                            //Which depth?
          case AllDepths:
            sum += i.energy() * scale(eta);
            break;
          case Depth1:
            sum += (isDepth2(i.detid())) ? 0 : i.energy() * scale(eta);
            break;
          case Depth2:
            sum += (isDepth2(i.detid())) ? i.energy() * scale(eta) : 0;
            break;
        }
      }
    });
  }

  return sum;
}
*/


/////SJ - copy of above with depth info
double EgammaHcalIsolation::getHcalSum(const GlobalPoint& pclu,
                                       const HcalDepth& depth,
                                       double (*scale)(const double&)) const {
  double sum = 0.;
  if (!mhbhe_.empty()) {
    //Compute the HCAL energy behind ECAL
    doubleConeSel_->selectCallback(pclu, mhbhe_, [this, &sum, &depth, &scale](const HBHERecHit& i) {
	double eta = theCaloGeom_.product()->getPosition(i.detid()).eta();
	HcalDetId hcalDetId(i.detid());
	/////SJ ---> update the rechit thresholds
	if (hcalDetId.subdet() == HcalBarrel &&         //Is it in the barrel?
	    passEBEThresh(i.energy(), i.detid())){ ////SJ
	    //i.energy() > eLowB_ &&                      //Does it pass the min energy?
	    //i.energy() * scaleToEt(eta) > etLowB_ ){//&&    //Does it pass the min et?
	  //&& (depth == AllDepths || depth == Depth1) ) {  //Are we asking for the first depth?
	  //sum += i.energy() * scale(eta);
	  switch (depth) {                            //Which depth?
	  case AllDepths:
	    sum += i.energy() * scale(eta);
	    break;
	  case Depth1:
	    sum += (HcalDetId(i.detid()).depth()==1) ? i.energy() * scale(eta) : 0;
	    break;
	  case Depth2:
	    sum += (HcalDetId(i.detid()).depth()==2) ? i.energy() * scale(eta) : 0;
	    break;
	  case Depth3:
	    sum += (HcalDetId(i.detid()).depth()==3) ? i.energy() * scale(eta) : 0;
	    break;
	  case Depth4:
	    sum += (HcalDetId(i.detid()).depth()==4) ? i.energy() * scale(eta) : 0;
	    break;
	    
	  case Depth5:
	    sum += (HcalDetId(i.detid()).depth()==5) ? 0 : 0;
	    break;
	    
	  case Depth6:
	    sum += (HcalDetId(i.detid()).depth()==6) ? 0 : 0;
	    break;
	    
	  case Depth7:
	    sum += (HcalDetId(i.detid()).depth()==7) ? 0 : 0;
	    break;
	    
	  
	  }//switch (depth)
        //sum += i.energy() * scale(eta);
	
	}
	
	if (hcalDetId.subdet() == HcalEndcap &&       //Is it in the endcap?
	    passEEEThresh(i.energy(), i.detid())){ ///SJ
	    //i.energy() > eLowE_ &&                    //Does it pass the min energy?
	    //i.energy() * scaleToEt(eta) > etLowE_) {  //Does it pass the min et?
	  switch (depth) {                            //Which depth?
	  case AllDepths:
	    sum += i.energy() * scale(eta);
	    break;
	  case Depth1:
	    sum += (HcalDetId(i.detid()).depth()==1) ? i.energy() * scale(eta) : 0;
	    break;
	  case Depth2:
	    sum += (HcalDetId(i.detid()).depth()==2) ? i.energy() * scale(eta) : 0;
	    break;
	  case Depth3:
	    sum += (HcalDetId(i.detid()).depth()==3) ? i.energy() * scale(eta) : 0;
	    break;
	  case Depth4:
	    sum += (HcalDetId(i.detid()).depth()==4) ? i.energy() * scale(eta) : 0;
	    break;
	  case Depth5:
	    sum += (HcalDetId(i.detid()).depth()==5) ? i.energy() * scale(eta) : 0;
            break;
	  case Depth6:
	    sum += (HcalDetId(i.detid()).depth()==6) ? i.energy() * scale(eta) : 0;
            break;
	  case Depth7:
	    sum += (HcalDetId(i.detid()).depth()==7) ? i.energy() * scale(eta) : 0;
            break;
	    
	  }//switch (depth)
	
	}
      });
  }

  return sum;
}


bool EgammaHcalIsolation::isDepth2(const DetId& detId) const {
  if ((HcalDetId(detId).depth() == 2 && HcalDetId(detId).ietaAbs() >= 18 && HcalDetId(detId).ietaAbs() < 27) ||
      (HcalDetId(detId).depth() == 3 && HcalDetId(detId).ietaAbs() == 27)) {
    return true;
    
  } else {
    return false;
  }
}




///////////////////////////SJ//////////////////
double EgammaHcalIsolation::getHcalSum(const std::vector<HcalDetId>& rechits,
				       const HcalDepth& depth
				       ) const {
  double sum = 0.;
  if (!mhbhe_.empty()) {
    //Compute the HCAL energy behind ECAL
    for (auto const& rh : mhbhe_) {
      if (std::find(rechits.begin(), rechits.end(), rh.id()) != rechits.end()) {
	//esum += rh.ietaAbs() < 18 || rh.ietaAbs() > 29 ? rh.hadEnergy() : rh.hadEnergyHeInnerLayer(); ---> check its in hte original https://cmssdt.cern.ch/lxr/source/RecoEgamma/EgammaIsolationAlgos/src/EgammaHadTower.cc#0094  - why?
	
	//double eta = theCaloGeom_.product()->getPosition(i.detid()).eta();
	double eta = theCaloGeom_.product()->getPosition(rh.id()).eta();
	//HcalDetId hcalDetId(i.detid());
	HcalDetId hcalDetId(rh.id());
	if (hcalDetId.subdet() == HcalBarrel &&         //Is it in the barrel?
	    passEBEThresh(rh.energy(), rh.detid()) &&  ///SJ
	    //rh.energy() > eLowB_ &&                      //Does it pass the min energy?
	    //rh.energy() * scaleToEt(eta) > etLowB_ &&    //Does it pass the min et?
	    (depth == AllDepths || depth == Depth1)) {  //Are we asking for the first depth?
	  sum += rh.energy() ;
	}
	if (hcalDetId.subdet() == HcalEndcap &&       //Is it in the endcap?
	    passEEEThresh(rh.energy(), rh.detid()) ) {
	    //rh.energy() > eLowE_ &&                    //Does it pass the min energy?
	    //rh.energy() * scaleToEt(eta) > etLowE_) {  //Does it pass the min et?
	  
	  switch (depth) {                            //Which depth?
          case AllDepths:
	    sum += rh.energy();
            break;
          case Depth1:
            //sum += (isDepth2(i.detid())) ? 0 : i.energy() * scale(eta);
	    sum += (isDepth2(rh.id())) ? 0 : rh.energy() ;
            break;
          case Depth2:
            //sum += (isDepth2(i.detid())) ? i.energy() * scale(eta) : 0;
	    sum += (isDepth2(rh.id())) ? rh.energy(): 0;
            break;
	case Depth3:
	  sum += (HcalDetId(rh.detid()).depth()==3) ? rh.energy(): 0;
	  break;
	case Depth4:
	  sum += (HcalDetId(rh.detid()).depth()==4) ? rh.energy()  : 0;
	  break;
	case Depth5:
	  sum += (HcalDetId(rh.detid()).depth()==5) ? rh.energy() : 0;
            break;
	case Depth6:
	  sum += (HcalDetId(rh.detid()).depth()==6) ? rh.energy() : 0;
            break;
	case Depth7:
	  sum += (HcalDetId(rh.detid()).depth()==7) ? rh.energy() : 0;
            break;

	  }
	  
	}//
      
      }//if (std::find(rechits.begin(), rechits.end(), rh.id()) != rechits.end())

    }//for (auto const& rh : mhbhe_)
  }//if (!mhbhe_.empty()) 
  return sum;
}
  

//////////////////////////////////SJ/////////////////////////////////
HcalDetId EgammaHcalIsolation::rechitOf(const reco::CaloCluster& cluster) const {


  ////========================================MAKE SURE that this definition is similar to towerOf inthe sense that that probably asks for seed???

  ///get the global point of seed
  //const CaloSubdetectorGeometry* sdg = caloGeom->getSubdetectorGeometry(DetId::Hcal, subdet); ////Check what to pass as subdet

  std::cout<<"SJ!! inside rechitOf 0 "<<std::endl;

  double bestdR = 999;
  HcalDetId bestdetid;
  
  DetId seeddetid = cluster.seed();
  if (seeddetid.det() != DetId::Ecal) {
    // Basic clusters of hybrid super-cluster do not have the seed set; take the first DetId instead
    // Should be checked . The single Tower Mode should be favoured until fixed
    seeddetid = cluster.hitsAndFractions()[0].first;
    if (seeddetid.det() != DetId::Ecal) {
      HcalDetId detid;
      return detid;
    }
  }

  for (int subdet = 0; subdet <= 7; subdet++) {

    const CaloSubdetectorGeometry* sdg = caloGeom->getSubdetectorGeometry(DetId::Hcal, subdet); ////Check what to pass as subdet
    
    std::cout<<"SJ!! inside rechitOf 1 "<<std::endl;
    
    ///debug - SJ
    if (sdg == nullptr) continue;
    
    
    
    std::cout<<"SJ!! inside rechitOf 2 "<<std::endl;
    //DetId detid = sdg->getClosestCell(cluster.get<reco::SuperClusterRef>().get());
    
    //DetId detid = sdg->getClosestCell(GlobalPoint(cluster.seed().position().x(), cluster.seed().position().y(), cluster.seed().position().z()) );
    
    HcalDetId detid = sdg->getClosestCell(GlobalPoint(cluster.position().x(), cluster.position().y(), cluster.position().z()) );  ///get the seed position later once it works
    
    GlobalPoint pos = caloGeom->getGeometry(detid)->getPosition();
    const GlobalPoint& p(pos);
    
    double eta_sc = cluster.eta();
    double phi_sc = cluster.phi();
    double eta_rh = p.eta();
    double phi_rh = p.phi();
    
    float dR = reco::deltaR2(eta_sc, phi_sc, eta_rh, phi_rh);
    
    std::cout<<"SJ!!! subdet - dR "<<subdet<<" "<<dR<<std::endl;
    if(dR < bestdR){
      dR = bestdR;
      bestdetid = detid;
    }
    
  }///

  
  std::cout<<"SJ!! inside rechitOf 3 "<<std::endl;
  
  return bestdetid;
}

//////////////////////////////////SJ/////////////////////////////////
std::vector<HcalDetId> EgammaHcalIsolation::rechitsOf(const reco::SuperCluster& sc) const {
  std::vector<HcalDetId> rechits;
  std::vector<reco::CaloClusterPtr> orderedClusters;

  // in this mode, check only the tower behind the seed
  /*if (mode_ == SingleTower) { ///Prefer to keep the name same to avoid many changes ----> Now move this since mode is not defined here
    rechits.push_back(rechitOf(*sc.seed()));
  }
  */
  
  // in this mode check the towers behind each basic cluster
  //if (mode_ == TowersBehindCluster) {
  // Loop on the basic clusters
  reco::CaloCluster_iterator it = sc.clustersBegin();
  reco::CaloCluster_iterator itend = sc.clustersEnd();
  
  for (; it != itend; ++it) {
    orderedClusters.push_back(*it);
  }
  std::sort(orderedClusters.begin(), orderedClusters.end(), CaloClusterGreaterThan);
  unsigned nclusters = orderedClusters.size();
  for (unsigned iclus = 0; iclus < nclusters && iclus < NMaxClusters_; ++iclus) {
    // Get the tower
    HcalDetId id = rechitOf(*(orderedClusters[iclus]));
#ifdef EDM_ML_DEBUG
    std::cout << "CaloTowerId " << id << std::endl;
#endif
    std::vector<HcalDetId>::const_iterator itcheck = find(rechits.begin(), rechits.end(), id);
    if (itcheck == rechits.end()) {
      rechits.push_back(id);
    }
  }
  //}

  //  if(towers.size() > 4) {
  //    std::cout << " NTOWERS " << towers.size() << " ";
  //    for(unsigned i=0; i<towers.size() ; ++i) {
  //      std::cout << towers[i] << " ";
  //    }
  //    std::cout <<  std::endl;
  //    for ( unsigned iclus=0 ; iclus < orderedClusters.size(); ++iclus) {
  //      // Get the tower
  //      CaloTowerDetId id = towerOf(*(orderedClusters[iclus]));
  //      std::cout << " Pos " << orderedClusters[iclus]->position() << " " << orderedClusters[iclus]->energy() << " " << id ;
  //    }
  //    std::cout << std::endl;
  //  }
  return rechits;
}

////SJ
bool EgammaHcalIsolation::passEBEThresh(double energy, const DetId& detId) const{

  int depth = HcalDetId(detId).depth();
  HcalDepth dep = static_cast<HcalDepth>(depth); 

  HcalDetId hcalDetId(detId);
  if (hcalDetId.subdet() != HcalBarrel) return false;
  
  
  switch (dep) {
    
  case AllDepths:
    return false; ///this case will never arise since its per rechit check
  case Depth1:
    return (energy > eLowBD1_ ? true : false);
  case Depth2:
    return (energy > eLowBD2_ ? true : false);
  case Depth3:
    return (energy > eLowB_ ? true : false);
  case Depth4:
    return (energy > eLowB_ ? true : false);
  case Depth5:
    return false;
  case Depth6:
    return false;
  case Depth7:
    return false;
    
  }//switch (depth)
  
  return false;
}


////SJ
bool EgammaHcalIsolation::passEEEThresh(double energy, const DetId& detId) const{

  int depth = HcalDetId(detId).depth();
  HcalDepth dep = static_cast<HcalDepth>(depth); 

  HcalDetId hcalDetId(detId);
  if (hcalDetId.subdet() == HcalBarrel) return false;
  
  
  switch (dep) {

  case AllDepths:
    return false; ///this case will never arise since its per rechit check
  case Depth1:
    return (energy > eLowED1_ ? true : false);
  case Depth2:
    return (energy > eLowE_ ? true : false);
  case Depth3:
    return (energy > eLowE_ ? true : false);
  case Depth4:
    return (energy > eLowE_ ? true : false);
  case Depth5:
    return (energy > eLowE_ ? true : false);
  case Depth6:
    return (energy > eLowE_ ? true : false);
  case Depth7:
    return (energy > eLowE_ ? true : false);
    
  }//switch (depth)
  
  return false;
}

///SJ
bool CaloClusterGreaterThan(const reco::CaloClusterPtr& c1, const reco::CaloClusterPtr& c2) { return (*c1 > *c2); }
