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
// $Id: G4BREPSolidSphere.cc,v 1.11 2006/06/29 18:41:32 gunter Exp $
// GEANT4 tag $Name: geant4-09-02 $
//
// ----------------------------------------------------------------------
// GEANT 4 class source file
//
// G4BREPSolidSphere.cc
//
// ----------------------------------------------------------------------

#include "G4BREPSolidSphere.hh"
#include "G4SphericalSurface.hh"

G4BREPSolidSphere::G4BREPSolidSphere(const G4String& name,
				     const G4Vector3D& origin,
				     const G4Vector3D& xhat, 
				     const G4Vector3D& zhat,
				     G4double radius)
  : G4BREPSolid(name)
{
  SurfaceVec    = new G4Surface*[1];
  G4double ph1  = 0;
  G4double ph2  = 2*pi;
  G4double th1  = 0;
  G4double th2  = pi;
  SurfaceVec[0] = new G4SphericalSurface(origin, xhat, zhat, radius, ph1, ph2, th1, th2);
  nb_of_surfaces = 1;
  
  constructorParams.origin = origin;
	constructorParams.xhat   = xhat;
	constructorParams.zhat   = zhat;
	constructorParams.radius = radius;
  
  active=1;
  Initialize();
}

G4BREPSolidSphere::G4BREPSolidSphere( __void__& a )
  : G4BREPSolid(a)
{
}

G4BREPSolidSphere::~G4BREPSolidSphere()
{
}

EInside G4BREPSolidSphere::Inside(register const G4ThreeVector& Pt) const
{
  G4double Dist = SurfaceVec[0]->HowNear(Pt);
  if(Dist > 0+kCarTolerance) return kInside;
  if(Dist < 0-kCarTolerance) return kOutside;
  return kSurface;
}


G4ThreeVector G4BREPSolidSphere::SurfaceNormal(const G4ThreeVector& Pt) const
{
  G4Vector3D n =  SurfaceVec[0]->Normal(Pt);
  G4ThreeVector norm(n.x(), n.y(), n.z());
  return norm;
}


G4double G4BREPSolidSphere::DistanceToIn(const G4ThreeVector& Pt) const
{
  return  std::fabs(SurfaceVec[0]->HowNear(Pt));
}


G4double G4BREPSolidSphere::DistanceToIn(register const G4ThreeVector& Pt, 
					 register const G4ThreeVector& V) const
{
  // SphReset();  
  G4Vector3D Pttmp(Pt);
  G4Vector3D Vtmp(V);   
  G4Ray      r(Pttmp, Vtmp);
  G4int      Result = SurfaceVec[0]->Intersect( r );

  if(Result>0)
  {
    ShortestDistance = SurfaceVec[0]->GetDistance();
    return std::sqrt(ShortestDistance);
  }
  return kInfinity; 
}


G4double G4BREPSolidSphere::DistanceToOut(register const G4ThreeVector& Pt, 
					  register const G4ThreeVector& V, 
					  const G4bool calcNorm, 
					  G4bool *validNorm, 
					  G4ThreeVector *n) const
{
  if(validNorm) *validNorm = false;
  // SphReset();  
  G4Vector3D Pttmp(Pt);
  G4Vector3D Vtmp(V);   
  G4Ray      r(Pttmp, Vtmp);

  if(SurfaceVec[0]->Intersect( r ))
  {
    if(calcNorm)
    {
      *validNorm = true;
      *n = SurfaceNormal(Pt);
    }

    ShortestDistance = SurfaceVec[0]->GetDistance();
    return std::sqrt(ShortestDistance);
  }
  return kInfinity; 
}


G4double G4BREPSolidSphere::DistanceToOut(const G4ThreeVector& Pt) const
{
  return  std::fabs(SurfaceVec[0]->HowNear(Pt));
}

// Streams solid contents to output stream.
std::ostream& G4BREPSolidSphere::StreamInfo(std::ostream& os) const
{
  G4BREPSolid::StreamInfo( os )
  << "\n origin: " << constructorParams.origin
  << "\n xhat:   " << constructorParams.xhat
  << "\n zhat:   " << constructorParams.zhat
  << "\n radius: " << constructorParams.radius
  << "\n-----------------------------------------------------------\n";

  return os;
}

