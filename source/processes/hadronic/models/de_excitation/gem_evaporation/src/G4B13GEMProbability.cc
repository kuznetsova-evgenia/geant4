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
// $Id: G4B13GEMProbability.cc,v 1.4 2006/06/29 20:20:39 gunter Exp $
// GEANT4 tag $Name: geant4-09-02 $
//
// Hadronic Process: Nuclear De-excitations
// by V. Lara (Nov 1999)
//


#include "G4B13GEMProbability.hh"

G4B13GEMProbability::G4B13GEMProbability() :
  G4GEMProbability(13,5,3.0/2.0) // A,Z,Spin
{

    ExcitEnergies.push_back(3534.7*keV);
    ExcitSpins.push_back(7.0/2.0);
    ExcitLifetimes.push_back(0.2e-15*s);

    ExcitEnergies.push_back(3712*keV);
    ExcitSpins.push_back(7.0/2.0);
    ExcitLifetimes.push_back(0.26e-15*s);

    ExcitEnergies.push_back(4131*keV);
    ExcitSpins.push_back(7.0/2.0);
    ExcitLifetimes.push_back(0.04e-15*s);

    SetExcitationEnergiesPtr(&ExcitEnergies);
    SetExcitationSpinsPtr(&ExcitSpins);
    SetExcitationLifetimesPtr(&ExcitLifetimes);
}


G4B13GEMProbability::G4B13GEMProbability(const G4B13GEMProbability &) : G4GEMProbability()
{
  throw G4HadronicException(__FILE__, __LINE__, "G4B13GEMProbability::copy_constructor meant to not be accessable");}




const G4B13GEMProbability & G4B13GEMProbability::
operator=(const G4B13GEMProbability &)
{
  throw G4HadronicException(__FILE__, __LINE__, "G4B13GEMProbability::operator= meant to not be accessable");
  return *this;
}


G4bool G4B13GEMProbability::operator==(const G4B13GEMProbability &) const
{
  return false;
}

G4bool G4B13GEMProbability::operator!=(const G4B13GEMProbability &) const
{
  return true;
}



