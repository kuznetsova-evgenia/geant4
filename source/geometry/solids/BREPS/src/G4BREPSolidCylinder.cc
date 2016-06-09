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
// $Id: G4BREPSolidCylinder.cc,v 1.11 2006/06/29 18:41:18 gunter Exp $
// GEANT4 tag $Name: geant4-09-02 $
//
// ----------------------------------------------------------------------
// GEANT 4 class source file
//
// G4BREPSolidCylinder.cc
//
// ----------------------------------------------------------------------

#include "G4BREPSolidCylinder.hh"
#include "G4CircularCurve.hh"
#include "G4FPlane.hh"
#include "G4FCylindricalSurface.hh"

G4BREPSolidCylinder::G4BREPSolidCylinder(const G4String& name,
					 const G4ThreeVector& origin,
					 const G4ThreeVector& axis,
					 const G4ThreeVector& direction,
					 G4double radius,
					 G4double length)
  : G4BREPSolid(name)
{
  SurfaceVec = new G4Surface*[3];
  G4CurveVector cv;
  G4CircularCurve* tmp;



  // Creation of the cylindrical surface
  SurfaceVec[0] = new G4FCylindricalSurface(origin, axis, radius , length);
  //SurfaceVec[0]->SetBoundaries(&cv);
  //cv.clear();


  // Creation of the first circular surface, which origin is origin
  G4Point3D  ArcStart1 = G4Point3D( origin + ( radius*direction ) );
  G4Vector3D axis1     = G4Vector3D( axis.cross( direction ) );

  tmp = new G4CircularCurve;
  tmp->Init( G4Axis2Placement3D(direction, axis1, origin), radius );
  tmp->SetBounds(ArcStart1, ArcStart1);
  cv.push_back(tmp);

  SurfaceVec[1] = new G4FPlane(direction, axis1, origin);
  SurfaceVec[1]->SetBoundaries(&cv);
  cv.clear();
  

  // Creation of the second circular surface
  G4Point3D  origin2   = G4Point3D( origin  + ( length*axis ) );  
  G4Point3D  ArcStart2 = origin2 + G4Point3D( radius*direction );
  G4Vector3D axis2     = axis1;

  tmp = new G4CircularCurve;
  tmp->Init( G4Axis2Placement3D(direction, axis2, origin2), radius);
  tmp->SetBounds(ArcStart2, ArcStart2);
  cv.push_back(tmp);

  SurfaceVec[2] = new G4FPlane(direction, axis2, origin2);
  SurfaceVec[2]->SetBoundaries(&cv);
  cv.clear();


  nb_of_surfaces = 3;
  active=1;
  
  // Save constructor parameters
  constructorParams.origin       = origin;
  constructorParams.axis         = axis;
  constructorParams.direction    = direction;
  constructorParams.length       = length;
  constructorParams.radius       = radius;
  
  Initialize();
}

G4BREPSolidCylinder::G4BREPSolidCylinder( __void__& a )
  : G4BREPSolid(a)
{
}

G4BREPSolidCylinder::~G4BREPSolidCylinder()
{
}

// Streams solid contents to output stream.
std::ostream& G4BREPSolidCylinder::StreamInfo(std::ostream& os) const
{
  G4BREPSolid::StreamInfo( os )
  << "\n origin:       " << constructorParams.origin
  << "\n axis:         " << constructorParams.axis
  << "\n direction:    " << constructorParams.direction
  << "\n length:       " << constructorParams.length
  << "\n radius:       " << constructorParams.radius
  << "\n-----------------------------------------------------------\n";

  return os;
}

