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
// $Id: G4VPrimitiveScorer.cc,v 1.2 2006/06/29 18:06:03 gunter Exp $
// GEANT4 tag $Name: geant4-09-02 $
//
// G4VPrimitiveScorer
#include "G4VPrimitiveScorer.hh"
#include "G4MultiFunctionalDetector.hh"
#include "G4SDManager.hh"
#include "G4Step.hh"
#include "G4TouchableHistory.hh"


G4VPrimitiveScorer::G4VPrimitiveScorer(G4String name, G4int depth)
 :primitiveName(name),detector(0),filter(0),verboseLevel(0),indexDepth(depth)
{;} 

G4VPrimitiveScorer::~G4VPrimitiveScorer()
{;}

G4int G4VPrimitiveScorer::GetCollectionID(G4int)
{
  if(detector)
   return G4SDManager::GetSDMpointer()
    ->GetCollectionID(detector->GetName()+"/"+primitiveName); 
  else
   return -1;
}

void G4VPrimitiveScorer::Initialize(G4HCofThisEvent*)
{;}

void G4VPrimitiveScorer::EndOfEvent(G4HCofThisEvent*)
{;}

void G4VPrimitiveScorer::clear()
{;}

void G4VPrimitiveScorer::DrawAll()
{;}

void G4VPrimitiveScorer::PrintAll()
{;}

G4int G4VPrimitiveScorer::GetIndex(G4Step* aStep)
{
  G4StepPoint* preStep = aStep->GetPreStepPoint();
  G4TouchableHistory* th = (G4TouchableHistory*)(preStep->GetTouchable());
  return th->GetReplicaNumber(indexDepth);
}

