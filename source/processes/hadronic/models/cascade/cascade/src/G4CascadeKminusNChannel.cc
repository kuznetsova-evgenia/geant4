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

#include "G4CascadeKminusNChannel.hh"

namespace {

  // Total cross section as a function of kinetic energy
  G4double kmntot[31];
  
  // Multiplicities as a function of kinetic energy
  G4double kmnMultiplicities[6][31];


  const G4int kmnindex[6][2] = 
    {{0, 5}, {5, 20}, {20, 48}, {48, 90}, {90, 110}, {110, 121}};

  // Outgoing particle types of a given multiplicity

  const G4int kmn2bfs[5][2] =
    {{2, 13}, {5, 21}, {5, 25}, {7, 27}, {15, 31} };

  const G4int kmn3bfs[15][3] =
    {{1,5,13},   {2,7,13},   {2,5,17},   {5,7,21},   {5,5,23},
     {5,7,25},   {7,7,27},   {3,5,27},   {13,15,21}, {13,15,25},
     {15,17,27}, {11,13,27}, {5,15,29},  {7,15,31},  {5,11,31} };

  const G4int kmn4bfs[28][4] =
    {{1,5,7,13},   {1,5,5,17},   {2,7,7,13},   {2,3,5,13},
     {2,5,7,17},   {5,7,7,21},   {3,5,5,21},   {5,5,7,23},
     {7,7,7,27},   {3,5,7,27},   {7,13,15,21}, {5,15,17,21},
     {5,11,13,21}, {5,13,15,23}, {5,7,7,25},   {3,5,5,25},
     {7,13,15,25}, {5,15,17,25}, {5,11,13,25}, {7,15,17,27},
     {7,11,13,27}, {5,11,17,27}, {3,13,15,27}, {5,7,15,29},   
     {5,5,11,29},  {7,7,15,31},  {3,5,15,31},  {5,7,11,31} }; 

  const G4int kmn5bfs[42][5] =
    {{1,5,7,7,13},   {1,3,5,5,13},   {1,5,5,7,17},   {2,7,7,7,13},
     {2,3,5,7,13},   {2,5,7,7,17},   {2,3,5,5,17},   {5,7,7,7,21},
     {3,5,5,7,21},   {7,7,13,15,21}, {3,5,13,15,21}, {5,7,15,17,21},
     {5,7,11,13,21}, {5,5,11,17,21}, {5,5,7,7,23},   {3,5,5,5,23},
     {5,7,13,15,23}, {5,5,11,13,23}, {5,5,15,17,23}, {5,7,7,7,25},
     {3,5,5,7,25},   {7,7,13,15,25}, {3,5,13,15,25}, {5,7,15,17,25},
     {5,7,11,13,25}, {5,5,11,17,25}, {7,7,7,7,27},   {3,5,7,7,27},
     {3,3,5,5,27},   {7,7,15,17,27}, {3,5,15,17,27}, {7,7,11,13,27},
     {3,5,11,13,27}, {5,7,11,17,27}, {3,7,13,15,27}, {5,7,7,15,29},
     {3,5,5,15,29},  {5,5,7,11,29},  {7,7,7,15,31},  {3,5,7,15,31},
     {5,7,7,11,31},  {3,5,5,11,31} };

  const G4int kmn6bfs[20][6] =
    {{1,5,7,7,7,13}, {1,3,5,5,7,13}, {1,5,5,7,7,17}, {1,3,5,5,5,17},
     {2,7,7,7,7,13}, {2,3,5,7,7,13}, {2,3,3,5,5,13}, {2,5,7,7,7,17},
     {2,3,5,5,7,17}, {5,7,7,7,7,21}, {3,5,5,7,7,21}, {3,3,5,5,5,21},
     {5,5,7,7,7,23}, {3,5,5,5,7,23}, {5,7,7,7,7,25}, {3,5,5,7,7,25},
     {3,3,5,5,5,25}, {7,7,7,7,7,27}, {3,5,7,7,7,27}, {3,3,5,5,7,27} };

  const G4int kmn7bfs[11][7] =
    {{1,5,7,7,7,7,13}, {1,3,5,5,7,7,13}, {1,3,3,5,5,5,13},
     {1,5,5,7,7,7,17}, {1,3,5,5,5,7,17}, {2,7,7,7,7,7,13},
     {2,3,5,7,7,7,13}, {2,3,3,5,5,7,13}, {2,5,7,7,7,7,17},
     {2,3,5,5,7,7,17}, {2,3,3,5,5,5,17} };

  // Cross sections for K- n -> 2-7 body final states
  // 
  // first index:    0-4: channels for mult = 2
  //                5-19: channels for mult = 3 
  //               20-47: channels for mult = 4
  //               48-89: channels for mult = 5
  //              90-109: channels for mult = 6
  //             110-120: channels for mult = 7
  //
  // second index: kinetic energy
  // 
  const G4float kmnCrossSections[121][31] = {
    //
    // multiplicity 2 (5 channels)
    //  
    // K- n
    { 0.00, 0.29, 0.65, 1.12, 1.95, 3.75, 5.76, 7.77, 9.78, 11.79,
      13.80, 9.73, 5.38, 4.10, 3.55, 3.41, 3.22, 3.11, 3.10, 3.00,
      3.00, 3.00, 3.00, 2.90, 2.90, 2.90, 2.80, 2.80, 2.80, 2.76, 2.50},

    // L pi-
    { 3.00, 4.79, 5.88, 6.71, 7.43, 7.24, 6.84, 6.45, 6.05, 5.66,
      5.26, 2.52, 1.16, 0.55, 0.32, 0.21, 0.14, 0.09, 0.06, 0.04,
      0.03, 0.02, 0.01, 0.01, 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0},

    // S0 pi-
    { 1.19, 1.92, 2.40, 2.70, 2.96, 2.82, 2.59, 2.36, 2.13, 1.90,
      1.66, 0.62, 0.41, 0.25, 0.15, 0.10, 0.07, 0.05, 0.04, 0.03,
      0.02, 0.01, 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0},

    // S- pi0
    { 0.96, 1.56, 1.92, 2.28, 2.53, 2.43, 2.27, 2.10, 1.94, 1.77,
      1.60, 0.64, 0.32, 0.20, 0.14, 0.10, 0.08, 0.07, 0.05, 0.04,
      0.03, 0.02, 0.01, 0.01, 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0},

    // X- K0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  
      0.0,  0.01, 0.02, 0.04, 0.05, 0.04, 0.02, 0.01, 0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0},

    //
    //  multiplicity 3 (15 channels)
    //
    // p K- pi-
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.12, 0.26, 0.41, 0.55, 0.70,
      0.85, 1.52, 1.56, 1.19, 0.92, 0.78, 0.67, 0.58, 0.49, 0.42,
      0.36, 0.31, 0.27, 0.23, 0.20, 0.17, 0.14, 0.12, 0.11, 0.10, 0.02},

    // n K- pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.09, 0.19, 0.30, 0.40, 0.51,
      0.61, 0.98, 1.98, 2.84, 1.91, 1.52, 1.25, 1.03, 0.84, 0.69,
      0.57, 0.47, 0.39, 0.34, 0.30, 0.27, 0.25, 0.23, 0.20, 0.19, 0.14},

    // n K0bar pi-
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.15, 0.33, 0.51, 0.69, 0.88,
      1.06, 2.83, 3.06, 2.38, 1.67, 1.29, 1.01, 0.79, 0.61, 0.48,
      0.38, 0.30, 0.24, 0.19, 0.15, 0.11, 0.09, 0.07, 0.05, 0.04, 0.01},

    // L pi- pi0
    { 1.00, 1.49, 1.76, 1.92, 2.00, 2.19, 2.42, 2.65, 2.88, 3.11,
      3.34, 3.33, 2.00, 1.17, 0.74, 0.52, 0.37, 0.28, 0.22, 0.18,
      0.14, 0.11, 0.09, 0.07, 0.06, 0.05, 0.03, 0.02, 0.02, 0.02, 0.0},

    // S+ 2pi-
    { 0.0,  0.0,  0.03, 0.13, 0.23, 0.36, 0.50, 0.64, 0.78, 0.92,
      1.06, 0.88, 0.51, 0.35, 0.26, 0.21, 0.17, 0.14, 0.12, 0.10,
      0.08, 0.07, 0.05, 0.04, 0.04, 0.03, 0.03, 0.02, 0.02, 0.02, 0.0},

    // S0 pi- pi0
    { 0.0,  0.0,  0.0,  0.0,  0.03, 0.08, 0.13, 0.18, 0.24, 0.29,
      0.35, 0.90, 0.74, 0.54, 0.35, 0.24, 0.17, 0.12, 0.08, 0.06,
      0.05, 0.04, 0.04, 0.03, 0.03, 0.02, 0.02, 0.01, 0.01, 0.01, 0.0},

    // S- 2pi0
    { 0.0,  0.0,  0.0,  0.02, 0.15, 0.20, 0.24, 0.28, 0.31, 0.35,
      0.39, 0.47, 0.35, 0.26, 0.20, 0.16, 0.14, 0.12, 0.10, 0.09,
      0.07, 0.06, 0.06, 0.05, 0.04, 0.03, 0.04, 0.04, 0.03, 0.03, 0.02},

    // S- pi+ pi-
    { 0.0,  0.0,  0.0,  0.04, 0.19, 0.27, 0.34, 0.41, 0.48, 0.55,
      0.63, 0.78, 0.58, 0.43, 0.33, 0.26, 0.19, 0.16, 0.13, 0.11,
      0.09, 0.08, 0.07, 0.06, 0.05, 0.04, 0.04, 0.04, 0.03, 0.03, 0.02},

    // L K- K0 
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.04, 0.07, 0.06, 0.05, 0.04, 0.03, 0.03, 0.02,
      0.02, 0.01, 0.01, 0.01, 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0},

    // S0 K- K0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.01, 0.02, 0.03, 0.02, 0.02, 0.01, 0.01, 0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0},

    // S- K0 K0bar
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.01, 0.01, 0.02, 0.02, 0.03, 0.03, 0.04, 0.05,
      0.04, 0.04, 0.03, 0.03, 0.02, 0.02, 0.01, 0.01, 0.0,  0.0,  0.0},

    // S- K+ K-
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.01, 0.01, 0.02, 0.03, 0.04, 0.04, 0.04, 0.03,
      0.03, 0.02, 0.02, 0.02, 0.01, 0.01, 0.0,  0.0,  0.0,  0.0,  0.0},

    // X0 K0 pi-
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.01, 0.03, 0.05, 0.04, 0.03, 0.02, 0.01, 0.01,
      0.01, 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0},

    // X- K0 pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.01, 0.03, 0.05, 0.04, 0.03, 0.02, 0.01, 0.01,
      0.01, 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0},

    // X- K+ pi-
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.01, 0.03, 0.05, 0.04, 0.03, 0.02, 0.01, 0.01,
      0.01, 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0},
 
    //
    //  multiplicity 4 (28 channels)
    //
    // p K- pi- pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.01, 0.01, 0.01,
      0.01, 0.11, 0.29, 0.47, 0.63, 0.62, 0.60, 0.57, 0.54, 0.51,
      0.48, 0.45, 0.43, 0.42, 0.41, 0.39, 0.37, 0.35, 0.33, 0.32, 0.27},

    // p K0bar 2pi-
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.01,
      0.01, 0.07, 0.18, 0.30, 0.40, 0.40, 0.39, 0.37, 0.32, 0.28,
      0.24, 0.21, 0.19, 0.17, 0.15, 0.13, 0.12, 0.11, 0.10, 0.10, 0.08},

    // n K- 2pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.01,
      0.01, 0.21, 0.48, 0.75, 1.01, 1.07, 1.12, 1.11, 1.08, 1.20,
      1.35, 1.50, 1.64, 1.74, 1.68, 1.62, 1.57, 1.50, 1.42, 1.33, 0.60},

    // n K- pi+ pi-
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.01, 0.01, 0.01,
      0.01, 0.36, 0.81, 1.26, 1.70, 1.66, 1.56, 1.48, 1.39, 1.50,
      1.69, 1.87, 2.02, 2.12, 2.00, 1.88, 1.75, 1.63, 1.51, 1.41, 0.60},

    // n K0bar pi- pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.01,
      0.01, 0.13, 0.54, 1.00, 1.26, 1.28, 1.13, 0.98, 0.86, 0.78, 
      0.71, 0.65, 0.60, 0.55, 0.50, 0.46, 0.43, 0.40, 0.37, 0.35, 0.23},

    // L pi- 2pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.02, 0.04, 0.08, 0.10, 0.12,
      0.13, 0.37, 0.37, 0.27, 0.20, 0.18, 0.16, 0.14, 0.14, 0.13,
      0.11, 0.10, 0.09, 0.08, 0.08, 0.08, 0.07, 0.07, 0.07, 0.07, 0.06},

    // L pi+ 2pi-
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.03, 0.06, 0.10, 0.13, 0.16,
      0.20, 0.62, 0.61, 0.45, 0.34, 0.27, 0.22, 0.19, 0.18, 0.16,
      0.14, 0.12, 0.11, 0.10, 0.09, 0.09, 0.08, 0.08, 0.07, 0.07, 0.06},

    // S+ pi- pi- pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.01, 0.01, 0.01, 0.02,
      0.02, 0.12, 0.19, 0.26, 0.31, 0.29, 0.26, 0.22, 0.18, 0.07,
      0.04, 0.03, 0.02, 0.01, 0.01, 0.0,  0.0,  0.0,  0.0,  0.0,  0.0},

    // S- 3pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.01, 0.03, 0.05, 0.06, 0.08,
      0.10, 0.21, 0.21, 0.17, 0.38, 0.40, 0.40, 0.36, 0.33, 0.16,
      0.12, 0.10, 0.08, 0.07, 0.06, 0.05, 0.04, 0.05, 0.04, 0.04, 0.03},

    // S- pi+ pi- pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.02, 0.05, 0.08, 0.11, 0.14,
      0.17, 0.35, 0.35, 0.40, 0.64, 0.61, 0.55, 0.48, 0.42, 0.20,
      0.15, 0.12, 0.10, 0.08, 0.07, 0.06, 0.05, 0.05, 0.04, 0.04, 0.03},

    // L K- K0 pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.02, 0.02, 0.02, 0.03, 0.03, 0.03,
      0.02, 0.02, 0.01, 0.01, 0.01, 0.0,  0.0,  0.0,  0.0,  0.0,  0.0},

    // L K0 K0bar pi-
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.02, 0.02, 0.02, 0.03, 0.03, 0.03,
      0.02, 0.02, 0.01, 0.01, 0.01, 0.0,  0.0,  0.0,  0.0,  0.0,  0.0},

    // L K+ K- pi-
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.01, 0.01, 0.01, 0.02, 0.02, 0.02,
      0.01, 0.01, 0.01, 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0},

    // S+ K0 K- pi-
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.01, 0.01, 0.01, 0.01, 0.01, 0.01,
      0.01, 0.01, 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0},

    // S0 pi- 2pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.04, 0.06, 0.08, 0.11, 0.10, 0.08, 0.06, 0.07, 0.06,
      0.05, 0.04, 0.04, 0.04, 0.03, 0.03, 0.04, 0.04, 0.03, 0.03, 0.03},

    // S0 pi+ 2pi-
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.06, 0.09, 0.14, 0.18, 0.15, 0.11, 0.08, 0.09, 0.08,
      0.06, 0.05, 0.05, 0.05, 0.04, 0.04, 0.04, 0.04, 0.03, 0.03, 0.03},

    // S0 K- K0 pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.01, 0.01, 0.02, 0.02,
      0.02, 0.01, 0.01, 0.01, 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0},

    // S0 K0 K0bar pi-
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.01, 0.01, 0.02, 0.02,
      0.02, 0.01, 0.01, 0.01, 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0},

    // S0 K+ K- pi-
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.01, 0.01, 0.02, 0.02,
      0.02, 0.01, 0.01, 0.01, 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0},

    // S- K0 K0bar pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.01, 0.01, 0.02, 0.02, 0.02, 0.02,
      0.02, 0.02, 0.02, 0.02, 0.01, 0.01, 0.0,  0.0,  0.0,  0.0,  0.0},

    // S- K+ K- pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.01, 0.02, 0.02, 0.03, 0.03, 0.03,
      0.02, 0.02, 0.02, 0.02, 0.01, 0.01, 0.0,  0.0,  0.0,  0.0,  0.0},

    // S- K0bar K+ pi-
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.01, 0.01, 0.02, 0.02, 0.03,
      0.03, 0.02, 0.02, 0.02, 0.01, 0.01, 0.0,  0.0,  0.0,  0.0,  0.0},

    // S- K0 K- pi+
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.01, 0.01, 0.02, 0.02, 0.03,
      0.03, 0.02, 0.02, 0.02, 0.01, 0.01, 0.0,  0.0,  0.0,  0.0,  0.0},

    // X0 K0 pi- pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.01, 0.01, 0.02, 0.02, 0.03, 0.03, 0.03, 0.03,
      0.03, 0.03, 0.02, 0.02, 0.02, 0.02, 0.01, 0.01, 0.01, 0.01, 0.0},

    // X0 K+ 2pi-
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.01, 0.01, 0.02, 0.02, 0.03, 0.03, 0.03, 0.03,
      0.03, 0.03, 0.02, 0.02, 0.02, 0.02, 0.01, 0.01, 0.01, 0.01, 0.0},

    // X- K0 2pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.01, 0.01, 0.01, 0.01, 0.01, 0.02, 0.02, 0.02,
      0.02, 0.02, 0.02, 0.02, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.0},

    // X- K0 pi+ pi-
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.01, 0.02, 0.02, 0.02, 0.02, 0.03, 0.03, 0.03,
      0.02, 0.02, 0.02, 0.02, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.0},

    // X- K+ pi- pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.01, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02,
      0.01, 0.01, 0.01, 0.01, 0.01, 0.0,  0.0,  0.0,  0.0,  0.0,  0.0},

    //
    //  multiplicity 5 (42 channels)
    // 
    // p K- pi- 2pi0   
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.02, 0.05, 0.07, 0.09, 0.14, 0.19, 0.25, 0.30, 0.31,
      0.28, 0.26, 0.25, 0.24, 0.24, 0.23, 0.23, 0.23, 0.23, 0.23, 0.20},

    // p K- pi+ 2pi-
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.04, 0.08, 0.11, 0.15, 0.21, 0.27, 0.33, 0.39, 0.39,
      0.35, 0.33, 0.31, 0.29, 0.28, 0.27, 0.26, 0.25, 0.24, 0.24, 0.20},

    // p K0bar 2pi- pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.03, 0.06, 0.09, 0.13, 0.17, 0.21, 0.25, 0.33, 0.37,
      0.35, 0.33, 0.31, 0.29, 0.28, 0.27, 0.26, 0.25, 0.24, 0.24, 0.20},

    // n K- 3pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.02, 0.06, 0.09, 0.12, 0.19, 0.28, 0.37, 0.34, 0.36,
      0.37, 0.38, 0.39, 0.39, 0.41, 0.42, 0.45, 0.46, 0.46, 0.46, 0.48},

    // n K- pi+ pi- pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.04, 0.09, 0.15, 0.20, 0.29, 0.39, 0.48, 0.43, 0.45,
      0.46, 0.48, 0.48, 0.48, 0.49, 0.49, 0.50, 0.50, 0.49, 0.49, 0.48},

    // n K0bar pi- 2pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.03, 0.06, 0.09, 0.12, 0.19, 0.28, 0.36, 0.34, 0.36,
      0.37, 0.38, 0.40, 0.41, 0.43, 0.45, 0.47, 0.48, 0.49, 0.49, 0.51},

    // n K0bar pi+ 2pi-
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.04, 0.09, 0.15, 0.20, 0.29, 0.39, 0.48, 0.43, 0.45,
      0.46, 0.48, 0.49, 0.50, 0.51, 0.52, 0.52, 0.52, 0.52, 0.52, 0.51},

    // L pi- 3pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.04, 0.16, 0.30, 0.44, 0.44, 0.44, 0.41, 0.44, 0.44,
      0.42, 0.39, 0.38, 0.37, 0.36, 0.35, 0.35, 0.35, 0.35, 0.35, 0.33},

    // L pi+ 2pi- pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.06, 0.27, 0.50, 0.73, 0.68, 0.61, 0.55, 0.57, 0.55,
      0.52, 0.49, 0.47, 0.45, 0.43, 0.41, 0.39, 0.38, 0.37, 0.37, 0.33},

    // L K- K0 2pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.01, 0.01, 0.01, 0.02, 0.02,
      0.03, 0.03, 0.03, 0.03, 0.03, 0.03, 0.03, 0.03, 0.02, 0.02, 0.01},

    // L K- K0 pi+ pi-
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.01, 0.01, 0.02, 0.02, 0.03, 0.03,
      0.04, 0.04, 0.04, 0.04, 0.04, 0.03, 0.03, 0.03, 0.02, 0.02, 0.01},

    // L K0 K0bar pi- pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.01, 0.01, 0.01,
      0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.01, 0.01, 0.01, 0.01, 0.0},

    // L K+ K- pi- pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.01, 0.02, 0.03, 0.04, 0.04, 0.04,
      0.04, 0.04, 0.03, 0.04, 0.04, 0.03, 0.03, 0.03, 0.02, 0.02, 0.01},

    // L K+ K0bar 2pi-
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.01, 0.01, 0.01, 0.02, 0.02,
      0.03, 0.03, 0.04, 0.03, 0.03, 0.03, 0.03, 0.03, 0.02, 0.02, 0.01},

    // S+ 2pi- 2pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.01, 0.02, 0.03, 0.03, 0.04, 0.04, 0.05, 0.06,
      0.06, 0.06, 0.05, 0.05, 0.04, 0.04, 0.04, 0.02, 0.03, 0.03, 0.01},

    // S+ pi+ 3pi-
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.02, 0.03, 0.05, 0.05, 0.06, 0.06, 0.07, 0.07,
      0.07, 0.07, 0.06, 0.06, 0.05, 0.05, 0.04, 0.04, 0.03, 0.03, 0.01},

    // S+ K0 K- pi- pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.01, 0.01, 0.01, 0.01, 0.01,
      0.01, 0.01, 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0},

    // S+ K+ K- 2pi-
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0},

    // S+ K0 K0bar 2pi-
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0},

    // S0 pi- 3pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.01, 0.06, 0.10, 0.18, 0.22, 0.22, 0.20, 0.23, 0.22,
      0.20, 0.20, 0.19, 0.20, 0.18, 0.18, 0.18, 0.17, 0.18, 0.18, 0.17},

    // S0 pi+ 2pi- pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.02, 0.09, 0.17, 0.29, 0.34, 0.30, 0.27, 0.29, 0.27,
      0.25, 0.25, 0.24, 0.24, 0.22, 0.21, 0.20, 0.19, 0.19, 0.19, 0.17},

    // S0 K0 K- 2pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.01, 0.01,
      0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.01, 0.01, 0.01, 0.01, 0.0},

    // S0 K0 K- pi+ pi-
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.01, 0.01,
      0.01, 0.01, 0.02, 0.02, 0.02, 0.02, 0.01, 0.01, 0.01, 0.01, 0.0},

    // S0 K0 K0bar pi- pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.01, 0.01,
      0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.0},

    // S0 K+ K- pi- pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.01, 0.01, 0.02, 0.02, 0.02,
      0.02, 0.02, 0.01, 0.02, 0.02, 0.01, 0.01, 0.01, 0.01, 0.01, 0.0},

    // S0 K+ K0bar 2pi-
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.01, 0.01,
      0.01, 0.01, 0.02, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.0},

    // S- 4pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.01, 0.01, 0.01, 0.02, 0.03, 0.03, 0.04, 0.04,
      0.05, 0.04, 0.05, 0.05, 0.06, 0.06, 0.05, 0.06, 0.06, 0.06, 0.05},

    // S- pi+ pi- 2pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.01, 0.01, 0.02, 0.02, 0.03, 0.04, 0.04, 0.05, 0.06,
      0.06, 0.06, 0.06, 0.07, 0.07, 0.07, 0.06, 0.06, 0.06, 0.06, 0.05},

    // S- 2pi+ 2pi-
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.01, 0.02, 0.03, 0.04, 0.05, 0.06, 0.06, 0.07, 0.07,
      0.08, 0.08, 0.08, 0.08, 0.08, 0.08, 0.07, 0.07, 0.06, 0.06, 0.05},

    // S- K0 K0bar 2pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.01, 0.01, 0.01,
      0.02, 0.02, 0.02, 0.02, 0.02, 0.03, 0.04, 0.04, 0.05, 0.05, 0.05},

    // S- K0 K0bar pi+ pi-
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.01, 0.01, 0.01,
      0.02, 0.02, 0.02, 0.03, 0.03, 0.04, 0.04, 0.04, 0.05, 0.05, 0.05},

    // S- K+ K- 2pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.01, 0.01,
      0.01, 0.02, 0.02, 0.02, 0.02, 0.02, 0.03, 0.03, 0.02, 0.02, 0.02},

    // S- K+ K- pi+ pi-
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.01, 0.01,
      0.01, 0.02, 0.02, 0.02, 0.02, 0.02, 0.03, 0.03, 0.02, 0.02, 0.02},

    // S- K0bar K+ pi- pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.01,
      0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.0,  0.0,  0.0,  0.0},

    // S- K0 K- pi+ pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.01, 0.01, 0.01,
      0.01, 0.01, 0.02, 0.02, 0.02, 0.02, 0.02, 0.01, 0.01, 0.01, 0.0},

    // X0 K0 pi- 2pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.01, 0.01, 0.01, 0.02,
      0.03, 0.03, 0.03, 0.03, 0.03, 0.03, 0.03, 0.03, 0.02, 0.02, 0.01},

    // X0 K0 pi+ 2pi-
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.01, 0.02, 0.02, 0.02, 0.03,
      0.04, 0.04, 0.04, 0.04, 0.04, 0.04, 0.03, 0.03, 0.02, 0.02, 0.01},

    // X0 K+ 2pi- pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.01, 0.02, 0.02, 0.02, 0.03,
      0.03, 0.03, 0.03, 0.03, 0.03, 0.03, 0.02, 0.02, 0.02, 0.02, 0.01},

    // X- K0 3pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.01, 0.01, 0.01, 0.02, 0.03,
      0.04, 0.04, 0.04, 0.04, 0.04, 0.04, 0.04, 0.06, 0.06, 0.06, 0.05},

    // X- K0 pi+ pi- pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.01, 0.02, 0.02, 0.03, 0.04,
      0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.06, 0.06, 0.06, 0.05},

    // X- K+ pi- 2pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.01, 0.01,
      0.02, 0.02, 0.02, 0.02, 0.02, 0.03, 0.03, 0.04, 0.03, 0.03, 0.03},

    // X- K+ pi+ 2pi-
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.01, 0.01, 0.02,
      0.03, 0.03, 0.03, 0.03, 0.03, 0.03, 0.03, 0.04, 0.04, 0.04, 0.03},

    //
    //  multiplicity 6 (20 channels)
    // 
    // p K- pi- 3pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.01, 0.01, 0.02, 0.03, 0.04, 0.06, 0.07, 0.08,
      0.09, 0.09, 0.10, 0.11, 0.13, 0.15, 0.16, 0.17, 0.19, 0.19, 0.21},

    // p K- pi+ 2pi- pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.01, 0.02, 0.03, 0.05, 0.06, 0.08, 0.09, 0.10,
      0.11, 0.12, 0.13, 0.14, 0.16, 0.17, 0.18, 0.19, 0.20, 0.20, 0.21},

    // p K0bar 2pi- 2pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.06, 0.14, 0.20, 0.25, 0.30,
      0.34, 0.35, 0.36, 0.39, 0.40, 0.44, 0.48, 0.51, 0.55, 0.56, 0.63},

    // p K0bar pi+ 3pi-
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.01, 0.09, 0.19, 0.26, 0.32, 0.37,
      0.43, 0.44, 0.45, 0.47, 0.48, 0.51, 0.53, 0.55, 0.58, 0.58, 0.63},

    // n K- 4pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.03, 0.08, 0.11, 0.15, 0.18,
      0.20, 0.21, 0.22, 0.24, 0.25, 0.28, 0.32, 0.35, 0.39, 0.40, 0.47},

    // n K- pi+ pi- 2pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.01, 0.01, 0.04, 0.10, 0.15, 0.19, 0.22,
      0.26, 0.26, 0.27, 0.30, 0.30, 0.33, 0.36, 0.38, 0.41, 0.42, 0.47},

    // n K- 2pi+ 2pi-
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.01, 0.01, 0.06, 0.14, 0.20, 0.24, 0.28,
      0.32, 0.33, 0.34, 0.36, 0.36, 0.38, 0.40, 0.41, 0.44, 0.44, 0.47},

    // n K0bar pi- 3pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.01, 0.04, 0.05, 0.06, 0.07, 0.08,
      0.09, 0.09, 0.11, 0.12, 0.14, 0.16, 0.19, 0.21, 0.23, 0.23, 0.20},

    // n K0bar pi+ 2pi- pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.01, 0.06, 0.07, 0.08, 0.09, 0.10,
      0.11, 0.12, 0.14, 0.16, 0.17, 0.19, 0.21, 0.23, 0.25, 0.25, 0.20},

    // L pi- 4pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.01, 0.04, 0.06, 0.12, 0.18, 0.29, 0.36, 0.46, 0.56,
      0.61, 0.61, 0.61, 0.63, 0.64, 0.65, 0.60, 0.50, 0.40, 0.39, 0.37},

    // L pi+ 2pi- 2pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.01, 0.06, 0.10, 0.19, 0.28, 0.40, 0.48, 0.59, 0.70,
      0.77, 0.77, 0.75, 0.76, 0.76, 0.76, 0.67, 0.54, 0.42, 0.41, 0.37},

    // L 2pi+ 3pi-
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.02, 0.09, 0.17, 0.32, 0.44, 0.56, 0.64, 0.76, 0.88,
      0.96, 0.96, 0.93, 0.93, 0.91, 0.88, 0.74, 0.59, 0.45, 0.44, 0.37},

    // S+ 2pi- 3pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.01, 0.01, 0.01, 0.03, 0.04, 0.06, 0.08, 0.09,
      0.09, 0.08, 0.08, 0.07, 0.08, 0.07, 0.07, 0.06, 0.07, 0.07, 0.05},

    // S+ pi+ 3pi- pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.01, 0.02, 0.02, 0.04, 0.06, 0.08, 0.10, 0.11,
      0.11, 0.10, 0.10, 0.09, 0.09, 0.08, 0.08, 0.07, 0.07, 0.07, 0.05},

    // S0 pi- 4pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.01, 0.02, 0.05, 0.09, 0.14, 0.18, 0.23, 0.28,
      0.31, 0.31, 0.31, 0.32, 0.32, 0.33, 0.30, 0.25, 0.20, 0.20, 0.19},

    // S0 pi+ 2pi- 2pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.02, 0.04, 0.09, 0.14, 0.20, 0.24, 0.30, 0.35,
      0.38, 0.38, 0.38, 0.39, 0.39, 0.39, 0.33, 0.28, 0.22, 0.21, 0.19},

    // S0 2pi+ 3pi-
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.01, 0.03, 0.06, 0.14, 0.22, 0.28, 0.32, 0.38, 0.44,
      0.48, 0.48, 0.47, 0.47, 0.46, 0.45, 0.37, 0.30, 0.23, 0.22, 0.19},

    // S- 5pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.01, 0.01, 0.03, 0.05, 0.07, 0.08, 0.08,
      0.09, 0.09, 0.10, 0.10, 0.10, 0.10, 0.11, 0.11, 0.11, 0.11, 0.11},

    // S- pi+ pi- 3pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.01, 0.01, 0.02, 0.04, 0.06, 0.09, 0.10, 0.10,
      0.11, 0.11, 0.12, 0.12, 0.12, 0.12, 0.12, 0.12, 0.11, 0.11, 0.11},

    // S- 2pi+ 2pi- pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.01, 0.02, 0.04, 0.06, 0.09, 0.12, 0.13, 0.13,
      0.14, 0.14, 0.15, 0.15, 0.14, 0.14, 0.13, 0.13, 0.12, 0.12, 0.11},

    //
    //  multiplicity 7 (11 channels)
    // 
    // p K- pi- 4pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.01, 0.02, 0.02, 0.03, 0.06, 
      0.07, 0.08, 0.09, 0.10, 0.11, 0.12, 0.14, 0.14, 0.16, 0.16, 0.18},

    // p K- pi+ 2pi- 2pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.01, 0.01, 0.02, 0.03, 0.04, 0.07,
      0.09, 0.10, 0.11, 0.12, 0.13, 0.14, 0.15, 0.16, 0.17, 0.17, 0.18},

    // p K- 2pi+ 3pi-
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.01, 0.02, 0.03, 0.04, 0.06, 0.09,
      0.11, 0.13, 0.14, 0.15, 0.16, 0.16, 0.17, 0.17, 0.18, 0.18, 0.18},

    // p K0bar 2pi- 3pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.01, 0.01, 0.02, 0.03, 0.03, 0.03,
      0.04, 0.04, 0.05, 0.05, 0.06, 0.06, 0.07, 0.07, 0.08, 0.08, 0.10},

    // p K0bar pi+ 3pi- pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.01, 0.02, 0.03, 0.04, 0.04, 0.04,
      0.05, 0.05, 0.06, 0.06, 0.07, 0.07, 0.08, 0.08, 0.09, 0.09, 0.10},

    // n K- 5pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.01, 0.01, 0.02, 0.03, 0.03, 0.04,
      0.05, 0.06, 0.06, 0.07, 0.08, 0.10, 0.11, 0.12, 0.12, 0.12, 0.16},

    // n K- pi+ pi- 3pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.01, 0.02, 0.03, 0.04, 0.04, 0.06,
      0.06, 0.07, 0.08, 0.09, 0.10, 0.11, 0.12, 0.13, 0.13, 0.13, 0.16},

    // n K- 2pi+ 2pi- pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.02, 0.03, 0.04, 0.05, 0.06, 0.07,
      0.08, 0.09, 0.10, 0.11, 0.12, 0.13, 0.13, 0.14, 0.14, 0.14, 0.16},

    // n K0bar pi- 4pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.01, 0.01, 0.02, 0.02, 0.02,
      0.03, 0.04, 0.04, 0.05, 0.06, 0.07, 0.08, 0.09, 0.10, 0.10, 0.13},

    // n K0bar pi+ 2pi- 2pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.01, 0.01, 0.01, 0.02, 0.02, 0.03,
      0.04, 0.05, 0.06, 0.07, 0.07, 0.09, 0.09, 0.10, 0.10, 0.10, 0.13},

    // n K0bar 2pi+ 3pi-
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.01, 0.02, 0.02, 0.03, 0.03, 0.04,
      0.05, 0.06, 0.07, 0.08, 0.09, 0.10, 0.10, 0.11, 0.11, 0.11, 0.13} };
}

G4CascadeKminusNChannelData::data_t
G4CascadeKminusNChannelData::data = { kmntot,
				      kmnMultiplicities,
				      kmnindex,
				      kmn2bfs,
				      kmn3bfs,
				      kmn4bfs,
				      kmn5bfs,
				      kmn6bfs,
				      kmn7bfs,
				      kmnCrossSections };
namespace {
  struct initializer
  {
    initializer() { G4CascadeKminusNChannelData::data.initialize(); }
  };
  
  initializer init;
}

