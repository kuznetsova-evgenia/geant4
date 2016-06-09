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
// $Id: DicomRun.hh,v 1.1 2008/11/27 21:55:27 arce Exp $
// GEANT4 tag $Name: geant4-09-02 $
// 
//---------------------------------------------------------------------
// (Purpose) 
//    Example implementation for multi-functional-detector and 
//   primitive scorer.
//    This DicomRun class has collections which accumulate
//   a event information into a run information.
//
//---------------------------------------------------------------------

#ifndef DicomRun_h
#define DicomRun_h 1

#include "G4Run.hh"
#include "G4Event.hh"

#include "G4THitsMap.hh"
#include <vector>
//
class DicomRun : public G4Run {

public:
  // constructor and destructor.
  //  vector of multifunctionaldetector name has to given to constructor.
  DicomRun(const std::vector<G4String> mfdName);
  virtual ~DicomRun();

public:
  // virtual method from G4Run. 
  // The method is overriden in this class for scoring.
  virtual void RecordEvent(const G4Event*);

  // Access methods for scoring information.
  // - Number of HitsMap for this RUN. 
  //   This is equal to number of collections.
  G4int GetNumberOfHitsMap() const {return theRunMap.size();}
  // - Get HitsMap of this RUN.
  //   by sequential number, by multifucntional name and collection name,
  //   and by collection name with full path.
  G4THitsMap<G4double>* GetHitsMap(G4int i){return theRunMap[i];}
  G4THitsMap<G4double>* GetHitsMap(const G4String& detName, 
				  const G4String& colName);
  G4THitsMap<G4double>* GetHitsMap(const G4String& fullName);

private:
  std::vector<G4String> theCollName;
  std::vector<G4int> theCollID;
  std::vector<G4THitsMap<G4double>*> theRunMap;
};

//

#endif
