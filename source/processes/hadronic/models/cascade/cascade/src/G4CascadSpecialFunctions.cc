//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
#include "G4CascadSpecialFunctions.hh"

std::pair<G4int, G4double> 
G4CascadSpecialFunctions::getPositionInEnergyScale2(G4double e) 
{
  G4int verboseLevel = 2;

  if (verboseLevel > 3) {
    G4cout << " >>> G4CascadSpecialFunctions::getPositionInEnergyScale2" << G4endl;
  }

  const G4double EMT2[31] = {
    0.0, 0.05, 0.1, 0.15, 0.2, 0.25, 0.3, 0.35, 0.4, 0.45,
    0.5, 1.0,  1.5, 2.0,  2.5, 3.0,  3.5, 4.0,  4.5, 5.0,
    5.5, 6.0,  6.5, 7.0,  7.5, 8.0,  8.5, 9.0,  9.5, 10.0, 15.0
  };

  G4int ik = 30;
  G4double sk = 1.0;

  for (G4int i = 1; i < 31; i++) {

    if (e <= EMT2[i]) {
      ik = i;
      sk = (e - EMT2[ik - 1]) / (EMT2[ik] - EMT2[ik - 1]);
      break;
    }
  }

  return std::pair<G4int, G4double>(ik, sk);
}


std::pair<G4int, G4double> 
G4CascadSpecialFunctions::getPositionInEnergyScale1(G4double e) 
{
  G4int verboseLevel = 2;

  if (verboseLevel > 3) {
    G4cout << " >>> G4CascadSpecialFunctions::getPositionInEnergyScale1" << G4endl;
  }

  const G4double EMT1[20] = {
    0.5, 1.0, 1.5, 2.0, 2.5, 3.0, 3.5, 4.0, 4.5, 5.0,
    5.5, 6.0, 6.5, 7.0, 7.5, 8.0, 8.5, 9.0, 9.5, 10.0
  };

  G4int ik=0;
  G4double sk=0.;
  
  if (e < EMT1[0]) {
    ik = 1;
    sk = 0.0;

  } else if (e <= EMT1[19]) {     

    for (G4int i = 1; i < 20; i++) {

      if (e <= EMT1[i]) {
        ik = i;
        sk = (e - EMT1[ik - 1]) / (EMT1[ik] - EMT1[ik - 1]);

        break;
      };
    };

  } else {

    ik = 19;
    sk = 1.0;
  };

  if (verboseLevel > 2) {
    G4cout << " e " << e << " ik " << ik << " sk " << sk << G4endl;
  }

  return std::pair<G4int, G4double>(ik, sk);
}


G4double 
G4CascadSpecialFunctions::absorptionCrosSection(G4double e, G4int type) 
{
  G4int verboseLevel = 2;

  if (verboseLevel > 3) {
    G4cout << " >>> G4CascadSpecialFunctions::absorptionCrosSection  type:" << type <<G4endl;
  }

  const G4double corr_fac = 0.2;
  G4double csec = 0.0;
  
  if (e < 0.3) {
    csec = 0.1106 / std::sqrt(e) - 0.8 + 0.08 / ((e - 0.123) * (e - 0.123) + 0.0056);

  } else if (e < 1.0) {
    csec = 3.6735 * (1.0 - e) * (1.0 - e);     
  };

  if (csec < 0.0) csec = 0.0;

  if (verboseLevel > 2) {
    G4cout << " ekin " << e << " abs. csec " << corr_fac * csec << G4endl;   
  }

  return corr_fac * csec;
}


std::pair<G4int, G4double> 
G4CascadSpecialFunctions::getPositionInEnergyScaleEMS(G4double e) 
{
  G4int verboseLevel = 2;

  if (verboseLevel > 3) {
    G4cout << " >>> G4CascadSpecialFunctions::getPositionInEnergyScaleEMS" << G4endl;
  }

  const G4double EMS[46] = {
    0.05, 0.06, 0.07, 0.08, 0.09, 0.10, 0.11, 0.12, 0.13, 0.14,
    0.15, 0.16, 0.17, 0.18, 0.19, 0.20, 0.21, 0.22, 0.23, 0.24,
    0.25, 0.26, 0.27, 0.28, 0.29, 0.30, 0.31, 0.32, 0.33, 0.34,
    0.35, 0.36, 0.37, 0.38, 0.39, 0.40, 0.41, 0.42, 0.43, 0.44,
    0.45, 0.46, 0.47, 0.48, 0.49, 0.50
  };

  G4int ik=0;
  G4double sk=0.;
  
  if (e < EMS[0]) {
    ik = 1;
    sk = 0.0;

  } else if (e <= EMS[45]) {     

    for (G4int i = 1; i < 46; i++) {

      if (e <= EMS[i]) {
        ik = i;
        sk = (e - EMS[ik - 1]) / (EMS[ik] - EMS[ik - 1]);

        break;
      };
    };

  } else {

    ik = 45;
    sk = 1.0;
  };

  return std::pair<G4int, G4double>(ik, sk);
}


G4double 
G4CascadSpecialFunctions::crossSection(G4double e, G4int is) 
{
  G4int verboseLevel = 2;

  if (verboseLevel > 3) {
    G4cout << " >>> G4CascadSpecialFunctions::crossSection" << G4endl;
  }

  const G4double dsig[46][2] = {
    {13.7,  15.0}, {15.8,  17.6}, {19.0,  15.0}, {46.0,  15.8}, {52.0,  21.0},
    {55.0,  21.9}, {77.0,  31.0}, {101.0, 38.4}, {124.0, 42.7}, {148.0, 55.4},
    {165.0, 55.3}, {172.0, 67.9}, {205.0, 66.2}, {189.0, 67.2}, {190.0, 67.8},
    {178.0, 63.8}, {148.0, 64.0}, {141.0, 52.1}, {135.0, 58.0}, {127.0, 48.3},
    {107.0, 40.0}, {111.0, 37.8}, {81.3,  37.5}, {78.0,  31.7}, {75.0,  30.0},
    {64.3,  30.0}, {60.3,  27.7}, {58.9,  26.0}, {55.0,  27.0}, {48.0,  26.0},
    {45.2,  26.7}, {40.8,  26.0}, {39.3,  27.0}, {40.7,  27.1}, {31.2,  26.5},
    {34.6,  26.9}, {31.4,  27.6}, {27.1,  28.4}, {26.2,  27.5}, {24.4,  27.2},
    {25.7,  28.8}, {23.8,  29.3}, {21.5,  27.0}, {22.2,  29.5}, {21.5,  31.2}, 
    {19.0, 30.7}
  };

  const G4double asig[4][6][31] = {
    {{1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 24.3, 24.1, 24.0, 26.3, 
      28.6, 24.8, 19.9, 19.2, 17.4, 15.3, 13.5, 12.3, 11.9, 10.4,
      11.8, 11.4, 11.0, 10.8, 10.9, 11.7, 11.4, 10.2, 11.0, 11.0, 9.0}, 

     {0.  , 0.  , 0.  , 0.  , 0.  , 0.  , 0.  , 1.45, 2.90, 4.10,
      5.30, 22.0, 21.2, 19.9, 14.9, 12.6, 12.3, 11.3, 10.8, 9.50,
      8.27, 7.20, 6.70, 6.25, 6.04, 5.89, 5.70, 5.60, 5.05, 4.17, 4.00},

     {0.  , 0.  , 0.  , 0.  , 0.  , 0.  , 0.  , 0.  , 0.  , 0.  ,
      0.  , 2.27, 4.28, 7.81, 8.03, 8.11, 7.90, 7.82, 7.61, 7.47,
      7.07, 7.66, 7.05, 6.71, 6.38, 6.36, 6.37, 6.57, 6.01, 5.48, 6.80},

     {0.  , 0.  , 0.  , 0.  , 0.  , 0.  , 0.  , 0.  , 0.  , 0.  ,
      0.  , 0.  , 1.20, 2.85, 3.70, 4.81, 5.33, 7.74, 6.91, 6.94,
      7.57, 7.21, 7.11, 7.10, 6.93, 6.79, 6.71, 6.55, 6.55, 6.15, 8.50},

     {0.  , 0.  , 0.  , 0.  , 0.  , 0.  , 0.  , 0.  , 0.  , 0.  ,
      0.  , 0.  , 0.  , .005, 0.54, 0.74, 0.86, 0.91, 1.10, 1.16,
      1.36, 1.40, 1.43, 1.47, 1.47, 1.43, 1.38, 1.38, 1.63, 1.36, 2.80},

     // Used as pp, nn total cross section
     {0.  , 0.  , 0.  , 0.  , 0.  , 0.  , 0.  , 0.  , 0.  , 0.  ,
      34.0, 46.2, 46.9, 45.2, 47.1, 42.3, 41.8, 41.2, 41.6, 41.6,
      41.0, 43.0, 42.4, 40.0, 39.9, 39.8, 42.0, 40.0, 39.8, 39.6, 38.7}},

    {{1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 33.0, 31.3, 29.5, 27.8,
      14.6, 16.0, 17.5, 18.3, 19.4, 18.7, 15.6, 14.8, 13.6, 12.5,
      12.2, 11.9, 11.4, 11.2, 10.1, 9.62, 8.41, 7.14, 7.09, 5.04, 10.2},

     {0.  , 0.  , 0.  , 0.  , 0.  , 0.  , 0.  , 2.00, 4.00, 6.50, 
      19.5, 20.8, 19.8, 18.6, 17.7, 14.4, 13.5, 10.4, 10.1, 12.0,
      8.87, 8.51, 8.49, 9.20, 8.29, 7.43, 8.20, 4.69, 4.57, 4.06, 4.10},

     {0.  , 0.  , 0.  , 0.  , 0.  , 0.  , 0.  , 0.  , 0.  , 0.  ,
      0.68, 2.76, 3.85, 8.35, 12.7, 12.3, 10.8, 12.0, 10.9, 10.2,
      10.6, 12.2, 11.8, 11.0, 10.4, 10.5, 11.0, 10.6, 11.8, 12.5, 13.2},

     {0.  , 0.  , 0.  , 0.  , 0.  , 0.  , 0.  , 0.  , 0.  , 0.  ,
      0.22, 0.52, 0.64, 1.19, 1.52, 1.75, 1.51, 2.04, 1.85, 1.70,
      1.92, 1.66, 1.74, 1.50, 1.39, 1.35, 1.41, 1.48, 1.43, 1.35, 3.20},

     {0.  , 0.  , 0.  , 0.  , 0.  , 0.  , 0.  , 0.  , 0.  , 0.  ,
      0.  , 0.  , 0.14, 0.24, 0.30, 0.46, 0.85, 1.40, 1.54, 1.52,
      1.47, 1.48, 1.49, 1.42, 1.39, 1.37, 1.22, 1.19, 0.93, 0.  , 2.10}, 

     // Used as np total cross section
     {0.  , 0.  , 0.  , 0.  , 0.  , 0.  , 0.  , 0.  , 0.  , 0.  ,
      35.0, 40.0, 42.4, 42.3, 41.0, 40.9, 40.4, 39.8, 35.0, 33.6,
      41.2, 41.0, 41.1, 41.2, 41.2, 39.6, 36.0, 36.0, 36.2, 36.2 ,40.2}},
 
    {{1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 60.0, 38.0, 30.6, 24.0,
      18.5, 12.8, 13.6, 9.15, 8.20, 7.80, 7.10, 6.40, 5.81, 5.85,
      5.50, 5.33, 5.40, 5.50, 4.90, 5.02, 5.00, 4.98, 4.96, 4.96, 4.50},

     {0.  , 0.  , 0.  , 0.  , 0.  , 0.  , 0.  , 0.38, 0.75, 1.28, 
      2.26, 11.8, 11.1, 7.56, 6.04, 5.68, 4.15, 3.21, 2.12, 1.66,
      1.54, 1.53, 1.47, 1.33, 1.39, 1.35, 1.29, 1.23, 1.13, 1.06, 0.70},

     {0.  , 0.  , 0.  , 0.  , 0.  , 0.  , 0.  , 0.  , 0.  , 0.  ,
      0.05, 2.19, 6.02, 7.36, 6.97, 5.83, 6.53, 5.09, 4.24, 3.24,
      3.31, 3.11, 2.91, 2.78, 2.72, 2.68, 2.48, 2.27, 2.02, 1.77, 4.40},

     {0.  , 0.  , 0.  , 0.  , 0.  , 0.  , 0.  , 0.  , 0.  , 0.  ,
      0.06, 0.35, 0.55, 0.77, 0.89, 0.80, 0.86, 0.97, 0.90, 0.86,
      0.84, 0.84, 0.83, 0.81, 0.79, 0.82, 0.76, 0.88, 0.89, 0.89, 3.00},

     {0.  , 0.  , 0.  , 0.  , 0.  , 0.  , 0.  , 0.  , 0.  , 0.  ,
      0.  , 0.02, 0.07, 0.33, 0.92, 1.39, 2.11, 1.81, 2.39, 2.60,
      2.19, 1.70, 1.60, 0.68, 1.43, 1.46, 1.46, 1.37, 1.16, 1.09, 2.60},

     // Used as pi+ p, pi- n total cross section
     {0.  , 0.  , 0.  , 0.  , 0.  , 0.  , 0.  , 0.  , 0.  , 0.  ,
      18.9, 27.2, 34.9, 29.1, 30.8, 29.6, 28.2, 27.5, 26.9, 26.3,
      25.9, 25.6, 25.2, 26.1, 25.5, 25.4, 25.3, 25.1, 24.9, 24.8, 24.1}},

     // pi- p -> 2 body   (pi+ n -> two body)
    {{5.90, 9.40, 24.5, 62.6, 65.3, 41.3, 29.3, 24.3, 22.7, 22.9,
      23.2, 28.4, 11.7, 10.1, 8.30, 7.16, 6.49, 6.36, 6.60, 5.84, 
       5.3,  5.2,  5.2,  5.1, 4.74, 4.7,  4.6,  4.5,  4.4,  4.3, 4.3},
     // pi- p -> 3 body
     {0.  , 0.  , 0.  , 0.  , 0.10, 0.40, 2.70, 3.50, 5.30, 6.60,
      9.10, 17.6, 12.2, 9.78, 7.51, 6.91, 6.86, 6.46, 6.19, 5.13,
      3.90, 2.82, 3.10, 3.12, 2.52, 2.22, 2.02, 2.01, 1.98, 2.14, 1.20},
     
     {0.  , 0.  , 0.  , 0.  , 0.  , 0.  , 0.  , 0.  , 0.  , 0.  ,
      0.76, 2.63, 3.72, 6.53, 7.47, 7.94, 7.12, 6.85, 6.09, 5.35,
      4.12, 3.85, 3.68, 4.09, 3.58, 3.29, 3.08, 2.93, 2.80, 2.65, 3.30},

     {0.  , 0.  , 0.  , 0.  , 0.  , 0.  , 0.  , 0.  , 0.  , 0.  ,
      0.59, 0.74, 1.47, 4.10, 4.78, 4.90, 5.07, 5.50, 5.48, 5.03,
      4.65, 4.39, 4.06, 3.53, 3.08, 3.05, 2.91, 3.42, 3.93, 3.93, 4.10},
     // pi- p -> 6 body
     {0.  , 0.  , 0.  , 0.  , 0.  , 0.  , 0.  , 0.  , 0.  , 0.  , 
      0.01, .007, 0.03, .099, .251, .376, .419, .582, .755, .777,
      1.13, 1.08, 1.13, 1.08, .962, .866, .738, .674, .645, .613, 1.30},

     // Used as pi- p and pi+ n total cross section
     {0.  , 0.  , 0.  , 0.  , 0.  , 0.  , 0.  , 0.  , 0.  , 0.  ,
      31.3, 46.0, 30.0, 35.7, 33.4, 31.6, 30.4, 29.6, 28.9, 28.5, 
      28.1, 27.5, 31.0, 27.7, 27.8, 27.1, 26.2, 26.0, 26.0, 25.9, 25.7}}
  };

  const G4double EMT2_10 = 0.5;
  G4double csec = 0.0;
  G4int l = is;

  if (l == 4) {
    l = 1;

  } else if (l == 10) {
    l = 3;

  } else if (l == 5 || l == 6) {
    l = 4;
  } else if (l == 7 || l == 14) {
    l = 5;
  };

  if (e < EMT2_10) { 

    if (l == 1) { // pp or nn

      if (e >= 0.4) {
        csec = 34.5;

      } else if (e >= 0.04) {
        csec = 0.23938 / (e * e) + 1.802 / e + 27.147;

      } else if (e >= 0.001) {
        csec = -0.0050574 / (e * e) + 9.0692 / e + 6.9466;

      } else {
        csec = 4.0 / e;
      }  	

    } else if (l == 2) { // np

      if (e >= 0.4) {
        csec = 0.88737 / e + 53.37 * e + 3.5475;

      } else if (e >= 0.04) {
        csec = 0.093074 / (e * e) - 0.011148 / e + 22.429;

      } else if (e >= 0.001) {
        csec = -0.0011748 / (e * e) + 3.0885 / e + 5.3107;

      } else {
        csec = 1.92 / e;
      };   	

    } else { // pi + n, p 

      if (e <= 0.05) {

        if (l == 3) {
	  csec = 3.7 + 204.35 * e;

	} else if (l == 4) {
	  csec = 6.5 + 170.71 * e;

        } else if (l == 5) {
	  csec = 5.1 + 187.53 * e;
	}; 

      } else {
        std::pair<G4int, G4double> iksk = getPositionInEnergyScaleEMS(e);
        G4int ik = iksk.first;
        G4double sk = iksk.second;

	if (l < 5) {
	  int j = l - 3;
	  csec = dsig[ik - 1][j] + sk * (dsig[ik][j] - dsig[ik - 1][j]);

	} else {
	  csec = 0.5 * (dsig[ik - 1][0] + dsig[ik - 1][1] + 
			sk * (dsig[ik][0] - dsig[ik - 1][0] + dsig[ik][1] - dsig[ik - 1][1]));
	}; 
      }; 
    };  

  } else {
    std::pair<G4int, G4double> iksk = getPositionInEnergyScale2(e);
    G4int ik = iksk.first;
    G4double sk = iksk.second;

    if (l < 5) {
      csec = asig[l - 1][5][ik - 1] + sk * (asig[l - 1][5][ik] - asig[l - 1][5][ik - 1]);

    } else {
      csec = 0.5 * (asig[2][5][ik - 1] + asig[3][5][ik - 1] +
		    sk * (asig[2][5][ik] - asig[2][5][ik - 1] +
			  asig[3][5][ik] - asig[3][5][ik - 1]));
    }; 
  }; 

  return csec;  
}

