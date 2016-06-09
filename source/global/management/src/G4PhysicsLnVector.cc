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
// $Id: G4PhysicsLnVector.cc,v 1.17 2008/09/22 14:49:57 gcosmo Exp $
// GEANT4 tag $Name: geant4-09-02 $
//
// 
// --------------------------------------------------------------
//      GEANT 4 class implementation file
//
//  G4PhysicsLnVector.cc
//
//  27 Apr 1999 - M.G.Pia: Created from G4PhysicsLogVector
//
// --------------------------------------------------------------

#include "G4PhysicsLnVector.hh"

G4PhysicsLnVector::G4PhysicsLnVector()
  : G4PhysicsVector(), dBin(0.), baseBin(0.)
{
  type = T_G4PhysicsLnVector;
}

G4PhysicsLnVector::G4PhysicsLnVector(size_t theNbin)
  : G4PhysicsVector(), dBin(0.), baseBin(0.)
{
  type = T_G4PhysicsLnVector;

  // Add extra one bin (hidden to user) to handle correctly when 
  // Energy=theEmax in getValue. 
  dataVector.reserve(theNbin+1);
  binVector.reserve(theNbin+1); 

  numberOfBin = theNbin;

  for (size_t i=0; i<=numberOfBin; i++)
  {
     binVector.push_back(0.0);
     dataVector.push_back(0.0);
  }
}  

G4PhysicsLnVector::G4PhysicsLnVector(G4double theEmin, 
                                     G4double theEmax, size_t theNbin)
  : G4PhysicsVector(),
    dBin(std::log(theEmax/theEmin)/theNbin),
    baseBin(std::log(theEmin)/dBin)
{
  type = T_G4PhysicsLnVector;

  // Add extra one bin (hidden to user) to handle correctly when 
  // Energy=theEmax in getValue. 
  dataVector.reserve(theNbin+1);
  binVector.reserve(theNbin+1); 

  numberOfBin = theNbin;

  for (size_t i=0; i<numberOfBin+1; i++)
  {
    binVector.push_back(std::exp(std::log(theEmin)+i*dBin));
    dataVector.push_back(0.0);
  }

  edgeMin = binVector[0];
  edgeMax = binVector[numberOfBin-1];
}

G4PhysicsLnVector::~G4PhysicsLnVector(){}

G4bool G4PhysicsLnVector::Retrieve(std::ifstream& fIn, G4bool ascii)
{
  G4bool success = G4PhysicsVector::Retrieve(fIn, ascii);
  if (success)
  {
    G4double theEmin = binVector[0];
    dBin = std::log(binVector[1]/theEmin);
    baseBin = std::log(theEmin)/dBin;
  }
  return success;
}

G4PhysicsLnVector::G4PhysicsLnVector(const G4PhysicsLnVector& right)
  : G4PhysicsVector(right)
{
  dBin = right.dBin;
  baseBin = right.baseBin;
}

G4PhysicsLnVector& 
G4PhysicsLnVector::operator=(const G4PhysicsLnVector& right)
{
  // Check assignment to self
  //
  if(this == &right) { return *this; }

  DeleteData();
  CopyData(right);

  dBin    = right.dBin;
  baseBin = right.baseBin;
  return *this;
}
