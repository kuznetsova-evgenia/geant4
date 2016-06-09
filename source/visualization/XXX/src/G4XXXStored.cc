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
// $Id: G4XXXStored.cc,v 1.2 2006/06/29 21:27:46 gunter Exp $
// GEANT4 tag $Name: geant4-09-02 $
//
// 
// John Allison  7th March 2006
// A template for a graphics driver with a store/database.
//?? Lines beginning like this require specialisation for your driver.

#include "G4XXXStored.hh"
#include "G4XXXStoredSceneHandler.hh"
#include "G4XXXStoredViewer.hh"

G4XXXStored::G4XXXStored():
  G4VGraphicsSystem("G4XXXStored",
		    "XXXStored",
		    "Graphics driver with a store/database",
		    G4VGraphicsSystem::threeD  //?? Your functionality
		    )
{}

G4XXXStored::~G4XXXStored() {}

G4VSceneHandler* G4XXXStored::CreateSceneHandler(const G4String& name) {
  G4VSceneHandler* pScene = new G4XXXStoredSceneHandler(*this, name);
  return pScene;
}

G4VViewer* G4XXXStored::CreateViewer(G4VSceneHandler& scene,
			       const G4String& name) {
  G4VViewer* pView =
    new G4XXXStoredViewer((G4XXXStoredSceneHandler&) scene, name);
  if (pView) {
    if (pView->GetViewId() < 0) {
      G4cout <<
	"G4XXXStored::CreateViewer: ERROR flagged by negative"
        " view id in G4XXXStoredViewer creation."
        "\n Destroying view and returning null pointer."
	     << G4endl;
      delete pView;
      pView = 0;
    }
  }
  else {
    G4cout <<
      "G4XXXStored::CreateViewer: ERROR: null pointer on new G4XXXStoredViewer."
	   << G4endl;
  }
  return pView;
}
