#include "CommonTools/CandAlgos/interface/ModifyObjectValueBase.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "RecoEgamma/EgammaTools/interface/json_wrapper.h"
//#include "RecoEgamma/EgammaTools/interface/SF_Reader.h"
#include <bits/stdc++.h>

// UTILITIES
std::string stripZeros(std::string bin_str);
std::vector<std::string> chooseCategory( double pt, std::vector<double> pt_bndrs, double eta, std::vector<double> eta_bndrs); 

class EGammaSFModifier : public ModifyObjectValueBase {

public:
  EGammaSFModifier(const edm::ParameterSet& conf, edm::ConsumesCollector& cond);
  ~EGammaSFModifier() override{}
  
  void modifyObject(pat::Electron& ele) const final;
  void modifyObject(pat::Photon& pho) const final;

private:
  std::string elejson_file;
  std::string phojson_file;
  std::string year;
  std::string ele_sf_name;
  std::string pho_sf_name;
  std::vector<double> ele_pt_bndrs;
  std::vector<double> pho_pt_bndrs;
  std::vector<double> ele_eta_bndrs;
  std::vector<double> pho_eta_bndrs;

  SF_Reader elesf;
  SF_Reader phosf;
  SF_Reader geteleSF() const;
  SF_Reader getphoSF() const;
};

SF_Reader EGammaSFModifier::geteleSF() const{
  return elesf;
};

SF_Reader EGammaSFModifier::getphoSF() const{
  return phosf;
};

DEFINE_EDM_PLUGIN(ModifyObjectValueFactory,
		  EGammaSFModifier,
		  "EGammaSFModifier");

EGammaSFModifier::EGammaSFModifier(const edm::ParameterSet& conf, edm::ConsumesCollector& cond):
  ModifyObjectValueBase(conf),
  elejson_file            (conf.getParameter<std::string> ("elefilename") ), 
  phojson_file            (conf.getParameter<std::string> ("phofilename") ), 
  year                 (conf.getParameter<std::string> ("year") ), 
  ele_sf_name          (conf.getParameter<std::string> ("ele_sf_name") ),
  pho_sf_name          (conf.getParameter<std::string> ("pho_sf_name") ),
  ele_pt_bndrs         (conf.getParameter<std::vector<double>> ("ele_pt_bndrs") ),
  pho_pt_bndrs         (conf.getParameter<std::vector<double>> ("pho_pt_bndrs") ), 
  ele_eta_bndrs        (conf.getParameter<std::vector<double>> ("ele_eta_bndrs") ),
  pho_eta_bndrs        (conf.getParameter<std::vector<double>> ("pho_eta_bndrs") ) {

  // ASSERTIONS
  if(not static_cast<bool>(std::ifstream(elejson_file))) { 
    throw cms::Exception("ConfigError") << "Error constructing EGammaSFModifier, ele sf file " << elejson_file << " doesn't exist" << std::endl;
  } 

  if(not static_cast<bool>(std::ifstream(phojson_file))) { 
    throw cms::Exception("ConfigError") << "Error constructing EGammaSFModifier, pho sf file " << phojson_file << " doesn't exist" << std::endl;
  } 

  if (year!="2016" and year!="2017" and year!="2018") {
    throw cms::Exception("ConfigError") <<"Error constructing EGammaSFModifier, year "<< year << " not valid" << std::endl;
  } 

  std::cout<<"SJ!!! Inside EGammaSFModifier ; year is "<<year<<std::endl;
  std::cout<<"SJ!!! Inside EGammaSFModifier ; EleFile name : SF name : "<<elejson_file<<" "<<ele_sf_name<<std::endl;
  elesf.read_json( elejson_file );
  
  std::cout<<"SJ!!! Inside EGammaSFModifier ; PhoFile name : SF name : "<<phojson_file<<" "<<pho_sf_name<<std::endl;
  phosf.read_json( phojson_file );



}

void EGammaSFModifier::modifyObject(pat::Electron& ele) const {

  std::vector<std::string> ele_pt_eta_str {chooseCategory(ele.pt(), ele_pt_bndrs, ele.eta(), ele_eta_bndrs)};

  double eleUserFloatValue = -99;
  double eleUserFloatError = -99;


  // IF UNDER/OVERFLOW TAKE THE CLOSEST BIN
  eleUserFloatValue = geteleSF().value(year, ele_sf_name, ele_pt_eta_str[0], ele_pt_eta_str[1]);
  eleUserFloatError = geteleSF().error(year, ele_sf_name, ele_pt_eta_str[0], ele_pt_eta_str[1]);

  ele.addUserFloat(ele_sf_name + "_value", eleUserFloatValue);
  ele.addUserFloat(ele_sf_name + "_error", eleUserFloatError);

  std::cout<<"SJ!!!ele pt : eta bin : SF +/err "<<ele_pt_eta_str[0]<<" "<<ele_pt_eta_str[1]<<" "<<eleUserFloatValue<<" "<<eleUserFloatError<<std::endl;
}

void EGammaSFModifier::modifyObject(pat::Photon& pho) const {

  std::vector<std::string> pho_pt_eta_str {chooseCategory(pho.pt(), pho_pt_bndrs, pho.eta(), pho_eta_bndrs)};

  double phoUserFloatValue = -99;
  double phoUserFloatError = -99;

  
  // IF UNDER/OVERFLOW TAKE THE CLOSEST BIN
  phoUserFloatValue = getphoSF().value(year, pho_sf_name, pho_pt_eta_str[0], pho_pt_eta_str[1]);
  phoUserFloatError = getphoSF().error(year, pho_sf_name, pho_pt_eta_str[0], pho_pt_eta_str[1]);

  pho.addUserFloat(pho_sf_name + "_value", phoUserFloatValue);
  pho.addUserFloat(pho_sf_name + "_error", phoUserFloatError);

  std::cout<<"SJ!!!pho pt : eta bin : SF +/err "<<pho_pt_eta_str[0]<<" "<<pho_pt_eta_str[1]<<" "<<phoUserFloatValue<<" "<<phoUserFloatError<<std::endl;
}

string stripZeros (string bin_str) {
  while (bin_str[bin_str.length() - 1] == '0' and bin_str[bin_str.length() - 2] != '.') {
    bin_str.erase(bin_str.length() - 1); 
  }
  return bin_str;
}

std::vector<std::string> chooseCategory( double pt, std::vector<double> pt_bndrs, double eta, std::vector<double> eta_bndrs) {

  std::string pt_str = "nope";
  std::string pt_lower_edge = "nope";
  std::string pt_upper_edge = "nope";

  for( int n = 0 ; n < ( int ) pt_bndrs.size() ; n++ ) {

    ///special cases shoulld be treated earlier
    // TREATING UNDERRFLOW 
    if ( ( double )  pt < pt_bndrs[0] ) { 
      pt_lower_edge = std::to_string( pt_bndrs[0] );
      pt_upper_edge = std::to_string( pt_bndrs[1] );
      pt_str = "pt:[" + stripZeros(pt_lower_edge) + "," + stripZeros(pt_upper_edge) + "]";
      break;
   }

    // TREATING OVERRFLOW 
    else if ( ( double ) pt > pt_bndrs[pt_bndrs.size() - 1] ) { 
      pt_lower_edge = std::to_string( pt_bndrs[pt_bndrs.size() - 2] );
      pt_upper_edge = std::to_string( pt_bndrs[pt_bndrs.size() - 1] );
      pt_str = "pt:[" + stripZeros(pt_lower_edge) + "," + stripZeros(pt_upper_edge) + "]";
      break;
   }

    // REGULAR CASE
    else if ( ( double ) pt > pt_bndrs[pt_bndrs.size() - n - 1] ) {
      pt_lower_edge = std::to_string( pt_bndrs[pt_bndrs.size() - n - 1] );
      pt_upper_edge = std::to_string( pt_bndrs[pt_bndrs.size() - n] );
      pt_str = "pt:[" + stripZeros(pt_lower_edge) + "," + stripZeros(pt_upper_edge) + "]";
      break;
    }


  }

  // PT BIN ASSERTION
  if (pt_str == "nope" or pt_lower_edge == "nope" or pt_upper_edge == "nope") { 
    throw cms::Exception("ConfigError") << "Error constructing EGammaSFModifier, can't construct pt bin" << std::endl;
  }

  std::string eta_str = "nope";
  std::string eta_lower_edge = "nope";
  std::string eta_upper_edge = "nope";

  for( int n = 0 ; n < ( int ) eta_bndrs.size() ; n++ ) {

    ///special cases shoulld be treated earlier
    // TREATING UNDERFLOW 
    if (  ( double ) eta < eta_bndrs[0] ) { 
      eta_lower_edge = std::to_string( eta_bndrs[0] );
      eta_upper_edge = std::to_string( eta_bndrs[1] );
      eta_str = "eta:[" + stripZeros(eta_lower_edge) + "," + stripZeros(eta_upper_edge) + "]";
      break;
    }

    // TREATING OVERFLOW 
    else if ( ( double ) eta > eta_bndrs[eta_bndrs.size() - 1] ) { 
      eta_lower_edge = std::to_string( eta_bndrs[eta_bndrs.size() - 2] );
      eta_upper_edge = std::to_string( eta_bndrs[eta_bndrs.size() - 1] );
      eta_str = "eta:[" + stripZeros(eta_lower_edge) + "," + stripZeros(eta_upper_edge) + "]";
      
      break;
    }

    // REGULAR CASE
    else if ( ( double ) eta > eta_bndrs[eta_bndrs.size() - n - 1] ) {
      eta_lower_edge = std::to_string( eta_bndrs[eta_bndrs.size() - n - 1] );
      eta_upper_edge = std::to_string( eta_bndrs[eta_bndrs.size() - n] );
      eta_str = "eta:[" + stripZeros(eta_lower_edge) + "," + stripZeros(eta_upper_edge) + "]";

      break;
    }

  }

  // ETA BIN ASSERTION
  if (eta_str == "nope" or eta_lower_edge == "nope" or eta_upper_edge == "nope") { 
    throw cms::Exception("ConfigError") << "Error constructing EGammaSFModifier, can't construct eta bin" << std::endl;
  }

  std::vector<std::string> cat {pt_str, eta_str};

  return cat;
}

