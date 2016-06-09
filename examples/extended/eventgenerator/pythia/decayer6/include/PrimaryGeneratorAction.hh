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
//
// $Id: PrimaryGeneratorAction.hh,v 1.1 2008/11/03 11:48:35 gcosmo Exp $
// GEANT4 tag $Name: geant4-09-02 $
//
// 
// ----------------------------------------------------------------------------

#ifndef PrimaryGeneratorAction_h
#define PrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"

class G4ParticleGun;
class G4Event;
class DetectorConstruction;
class PrimaryGeneratorMessenger;

// ----------------------------------------------------------------------------

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:

    PrimaryGeneratorAction(DetectorConstruction*);    
   ~PrimaryGeneratorAction();

    void GeneratePrimaries(G4Event*);
    void SetRndmFlag(G4String val) { rndmFlag = val;}

  private:

    G4ParticleGun*           particleGun; // pointer a to G4  class
    DetectorConstruction*    Detector;    // pointer to the geometry

    PrimaryGeneratorMessenger* gunMessenger; // messenger of this class
    G4String                   rndmFlag;     // flag for a rndm impact point
};

// ----------------------------------------------------------------------------

#endif


