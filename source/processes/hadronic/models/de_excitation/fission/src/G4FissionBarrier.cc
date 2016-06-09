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
// $Id: G4FissionBarrier.cc,v 1.5 2006/06/29 20:13:35 gunter Exp $
// GEANT4 tag $Name: geant4-09-02 $
//
// Hadronic Process: Nuclear De-excitations
// by V. Lara (Oct 1998)


#include "G4FissionBarrier.hh"

G4FissionBarrier::G4FissionBarrier(const G4FissionBarrier & ) : G4VFissionBarrier()
{
    throw G4HadronicException(__FILE__, __LINE__, "G4FissionBarrier::copy_constructor meant to not be accessable.");
}


const G4FissionBarrier & G4FissionBarrier::operator=(const G4FissionBarrier & )
{
    throw G4HadronicException(__FILE__, __LINE__, "G4FissionBarrier::operator= meant to not be accessable.");
    return *this;
}

G4bool G4FissionBarrier::operator==(const G4FissionBarrier & ) const 
{
    return false;
}

G4bool G4FissionBarrier::operator!=(const G4FissionBarrier & ) const 
{
    return true;
}



G4double G4FissionBarrier::FissionBarrier(const G4int A, const G4int Z, const G4double U)
    // Compute fission barrier according with Barashenkov's prescription for A >= 65
{
    if (A >= 65) return BarashenkovFissionBarrier(A,Z)/(1.0 + std::sqrt(U/(2.0*static_cast<G4double>(A))));
    else return 100.0*GeV;
}


G4double G4FissionBarrier::BarashenkovFissionBarrier(const G4int A, const G4int Z)
    // Calculates Fission Barrier heights 
{
    // Liquid drop model parameters for
    // surface energy of a spherical nucleus
    const G4double aSurf = 17.9439*MeV;
    // and coulomb energy
    const G4double aCoul = 0.7053*MeV;
    const G4int N = A - Z;
    const G4double k = 1.7826;

    // fissibility parameter
    G4double x = (aCoul/(2.0*aSurf))*(static_cast<G4double>(Z)*static_cast<G4double>(Z))/static_cast<G4double>(A);
    x /= (1.0 - k*(static_cast<G4double>(N-Z)/static_cast<G4double>(A))*
	  (static_cast<G4double>(N-Z)/static_cast<G4double>(A)));
  
    // Liquid drop model part of Fission Barrier
    G4double BF0 = aSurf*std::pow(static_cast<G4double>(A),2./3.);
    if (x <= 2./3.) BF0 *= 0.38*(3./4.-x);
    else BF0 *= 0.83*(1. - x)*(1. - x)*(1. - x);


    // 
    G4double D = 1.248*MeV;
    D *= (static_cast<G4double>(N)-2.0*(N/2)) + (static_cast<G4double>(Z)-2.0*(Z/2));

    return BF0 + D - SellPlusPairingCorrection(Z,N);
}

