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
// $Id: G4Li8GEMChannel.hh,v 1.3 2006/06/29 20:16:43 gunter Exp $
// GEANT4 tag $Name: geant4-09-02 $
//
// Hadronic Process: Nuclear De-excitations
// by V. Lara (Sept. 2001)
//


#ifndef G4Li8GEMChannel_h
#define G4Li8GEMChannel_h 1

#include "G4GEMChannel.hh"
#include "G4Li8GEMCoulombBarrier.hh"
#include "G4Li8GEMProbability.hh"

class G4Li8GEMChannel : public G4GEMChannel
{
public:
  // only available constructor
  G4Li8GEMChannel() : G4GEMChannel(8,3,"Li8",
				   &theEvaporationProbability,
				   &theCoulombBarrier)
  {
    theEvaporationProbability.SetCoulomBarrier(&theCoulombBarrier);
  }
  
  // destructor
  ~G4Li8GEMChannel() {};
  
private:
  const G4Li8GEMChannel & operator=(const G4Li8GEMChannel & right);  
    
  G4Li8GEMChannel(const G4Li8GEMChannel & right);
  
public:
  G4bool operator==(const G4Li8GEMChannel & right) const;
  G4bool operator!=(const G4Li8GEMChannel & right) const;
    
private:
  
  G4Li8GEMCoulombBarrier theCoulombBarrier;
	
  G4Li8GEMProbability theEvaporationProbability;
  
};
#endif
