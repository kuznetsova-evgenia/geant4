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
// $Id: DetectorConstruction.hh,v 1.4 2007/01/18 09:07:20 hbu Exp $
// GEANT4 tag $Name: geant4-09-02 $
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4Material;
class G4UniformMagField;
class G4UserLimits;
class DetectorMessenger;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class DetectorConstruction : public G4VUserDetectorConstruction
{
  public:

    DetectorConstruction();
   ~DetectorConstruction();

  public:

     G4VPhysicalVolume* Construct();

     void SetSize        (G4double);
     void SetMaterial    (G4String);
     void SetMagField    (G4double);
     void SetMaxStepSize (G4double);
     void SetMaxStepLength (G4double);

     void UpdateGeometry();

  public:

     const
     G4VPhysicalVolume* GetWorld()      {return pBox;};

     G4double           GetSize()       {return BoxSize;};
     G4Material*        GetMaterial()   {return aMaterial;};

     void               PrintParameters();

  private:

     G4VPhysicalVolume*    pBox;

     G4double              BoxSize;
     G4Material*           aMaterial;
     G4UniformMagField*    magField;
     G4UserLimits*         userLimits;

     DetectorMessenger* detectorMessenger;

  private:

     void               DefineMaterials();
     G4VPhysicalVolume* ConstructVolumes();
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


#endif

