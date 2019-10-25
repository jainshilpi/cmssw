#ifndef EnergyUncertaintyElectronSpecific_H
#define EnergyUncertaintyElectronSpecific_H

/** \class EnergyUncertaintyElectronSpecific
 **
 **  \author Anne-Fleur Barfuss, Kansas State University
 **
 ***/

#include "DataFormats/EgammaCandidates/interface/GsfElectron.h"

namespace electronAlgos {

  double computeEnergyUncertainty(reco::GsfElectron::Classification c, double eta, double brem, double energy);

}

#endif
