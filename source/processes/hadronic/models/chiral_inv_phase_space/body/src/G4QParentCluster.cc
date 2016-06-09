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
// $Id: G4QParentCluster.cc,v 1.25 2006/11/27 10:44:55 mkossov Exp $
// GEANT4 tag $Name: geant4-09-02 $
//
//      ---------------- G4QParentCluster ----------------
//             by Mikhail Kossov, Sept 1999.
//      class fora Parent nuclear cluster in the CHIPS Model
// ----------------------------------------------------------

//#define debug
//#define pdebug

#include "G4QParentClusterVector.hh"

G4QParentCluster::G4QParentCluster(G4int PDGCode): thePDGCode(PDGCode), theProbability(0.){}

G4QParentCluster::G4QParentCluster(G4int PDGCode, G4double prob): 
  thePDGCode(PDGCode), theProbability(prob){}

G4QParentCluster::G4QParentCluster(const G4QParentCluster& rhs)
{
  thePDGCode          = rhs.thePDGCode;
  theProbability      = rhs.theProbability;
  nQPart2             = rhs.nQPart2;
  transQC             = rhs.transQC;
  lowLimit            = rhs.lowLimit;
  highLimit           = rhs.highLimit;
  theEnvBoundedMass   = rhs.theEnvBoundedMass;
  theEnvBindingEnergy = rhs.theEnvBindingEnergy;
  theNucBoundedMass   = rhs.theNucBoundedMass;
  theNucBindingEnergy = rhs.theNucBindingEnergy;
}

G4QParentCluster::G4QParentCluster(G4QParentCluster* rhs)
{
  thePDGCode          = rhs->thePDGCode;
  theProbability      = rhs->theProbability;
  nQPart2             = rhs->nQPart2;
  transQC             = rhs->transQC;
  lowLimit            = rhs->lowLimit;
  highLimit           = rhs->highLimit;
  theEnvBoundedMass   = rhs->theEnvBoundedMass;
  theEnvBindingEnergy = rhs->theEnvBindingEnergy;
  theNucBoundedMass   = rhs->theNucBoundedMass;
  theNucBindingEnergy = rhs->theNucBindingEnergy;
}

const G4QParentCluster& G4QParentCluster::operator=(const G4QParentCluster& rhs)
{
  if(this != &rhs)                          // Beware of self assignment
  {
    thePDGCode          = rhs.thePDGCode;
    theProbability      = rhs.theProbability;
    nQPart2             = rhs.nQPart2;
    transQC             = rhs.transQC;
    lowLimit            = rhs.lowLimit;
    highLimit           = rhs.highLimit;
    theEnvBoundedMass   = rhs.theEnvBoundedMass;
    theEnvBindingEnergy = rhs.theEnvBindingEnergy;
    theNucBoundedMass   = rhs.theNucBoundedMass;
    theNucBindingEnergy = rhs.theNucBindingEnergy;
  }
  return *this;
}

G4QParentCluster::~G4QParentCluster() {}

// Standard output for G4QParentCluster
std::ostream& operator<<(std::ostream& lhs, G4QParentCluster& rhs)
{//      ===============================================
  lhs << "[ParClPDG=" << rhs.GetPDGCode() << ", probab=" << rhs.GetProbability() << "]";
  return lhs;
}

// Standard output for const G4QParentCluster
std::ostream& operator<<(std::ostream& lhs, const G4QParentCluster& rhs)
{//      ===============================================
  lhs << "[ParClPDG=" << rhs.GetPDGCode() << ", probab=" << rhs.GetProbability() << "]";
  return lhs;
}





