//
// ********************************************************************
// * DISCLAIMER                                                       *
// *                                                                  *
// * The following disclaimer summarizes all the specific disclaimers *
// * of contributors to this software. The specific disclaimers,which *
// * govern, are listed with their locations in:                      *
// *   http://cern.ch/geant4/license                                  *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.                                                             *
// *                                                                  *
// * This  code  implementation is the  intellectual property  of the *
// * GEANT4 collaboration.                                            *
// * By copying,  distributing  or modifying the Program (or any work *
// * based  on  the Program)  you indicate  your  acceptance of  this *
// * statement, and all its terms.                                    *
// ********************************************************************
//
//
// $Id: G4QuasmonVector.hh,v 1.10 2002/12/12 19:14:32 gunter Exp $
// GEANT4 tag $Name: geant4-05-01 $
//
//      ---------------- G4QuasmonVector ----------------
//             by Mikhail Kossov, Sept 1999.
// Type definition for a Vector of Quasmons - output of CHIPS model
// ----------------------------------------------------------------

#ifndef G4QuasmonVector_h
#define G4QuasmonVector_h 1

#include "G4Quasmon.hh"
#include "g4std/vector"

typedef G4std::vector<G4Quasmon *> G4QuasmonVector;
struct DeleteQuasmon{ void operator()(G4Quasmon *aN){delete aN;} };

#endif