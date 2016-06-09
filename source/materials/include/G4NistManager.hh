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
// $Id: G4NistManager.hh,v 1.23 2008/08/07 10:15:16 vnivanch Exp $
// GEANT4 tag $Name: geant4-09-02 $
//
//
// -------------------------------------------------------------------
//
// GEANT4 Class header file
//
// File name:     G4NistManager
//
// Author:        Vladimir Ivanchenko
//
// Creation date: 23.12.2004
//
// Modifications:
// 27.02.06 V.Ivanchneko add GetAtomicMassAmu and ConstructNewGasMaterial
// 11.05.06 V.Ivanchneko add warning flag to FindMaterial method
// 17.10.06 V.Ivanchneko add methods: GetAtomicMass, GetNistElementNames,
//                       GetNistMaterialNames
// 02.05.07 V.Ivanchneko add GetNistFirstIsotopeN and GetNumberOfNistIsotopes 
// 28.07.07 V.Ivanchneko make simple methods inline
// 28.10.07 V.Ivanchneko add state, T, P to maetrial build
//
// Class Description:
//
// A utility static class
//

// -------------------------------------------------------------------
//
// Class Description:
//
// Element data from the NIST DB on Atomic Weights and Isotope Compositions
// http://physics.nist.gov/PhysRefData/Compositions/index.html
//
// -------------------------------------------------------------------
//

#ifndef G4NistManager_h
#define G4NistManager_h 1

#include <vector>
#include "globals.hh"
#include "G4Material.hh"
#include "G4NistElementBuilder.hh"
#include "G4NistMaterialBuilder.hh"

class G4NistMessenger;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

class G4NistManager
{

public:

  static G4NistManager* Instance();
  ~G4NistManager();

  // Get G4Element by index
  //
  inline G4Element* GetElement(size_t index);
  
  // Find or build G4Element by atomic number
  //
  inline G4Element* FindOrBuildElement(G4int Z, G4bool isotopes=true);
  
  // Find or build G4Element by symbol
  //
  inline G4Element* FindOrBuildElement(const G4String& symb, 
				       G4bool isotopes=true);

  // Get number of elements
  //
  inline size_t GetNumberOfElements() const;

  // Get atomic number by element symbol
  //
  inline G4int GetZ(const G4String& symb) const;

  // Get the mass of the element in amu for the natuaral isotope composition
  // with electron shell 
  //
  inline G4double GetAtomicMassAmu(G4int Z) const;

  // Get mass of the isotope in Geant4 units without electron shell
  //
  inline G4double GetIsotopeMass(G4int Z, G4int N) const;

  // Get mass of the isotope in Geant4 units with electron shell
  //
  inline G4double GetAtomicMass(G4int Z, G4int N) const;

  // Get total ionisation energy of an atom
  //
  inline G4double GetTotalElectronBindingEnergy(G4int Z) const;

  // Get N for the first natural isotope
  //
  inline G4int GetNistFirstIsotopeN(G4int Z) const;

  // Get number of natural isotopes
  //
  inline G4int GetNumberOfNistIsotopes(G4int Z) const;

  // Get natural isotope abandance
  //
  inline G4double GetIsotopeAbundance(G4int Z, G4int N) const;

  // Print element by Z
  //
  inline void PrintElement(G4int Z);  

  // Print element from internal DB by symbol, if "all" - print all elements
  //
  void PrintElement(const G4String&);    

  // Print G4Element by name, if "all" - print all G4Elements
  //
  void PrintG4Element(const G4String&);  

  // Access to the vector of Geant4 predefined element names 
  //
  inline const std::vector<G4String>& GetNistElementNames() const;

  // Get G4Material by index 
  //
  inline G4Material* GetMaterial(size_t index);
  
  // Find or build a G4Material by name, from the Geant4 dataBase
  //
  inline G4Material* FindOrBuildMaterial(const G4String& name, 
					 G4bool isotopes=true,
					 G4bool warning=false);
  
  // Construct a G4Material from scratch by atome count
  // 
  inline G4Material* ConstructNewMaterial(
			          const G4String& name,
				  const std::vector<G4String>& elm,
				  const std::vector<G4int>& nbAtoms,
				  G4double dens, 
				  G4bool isotopes=true,
				  G4State   state    = kStateSolid,     
				  G4double  temp     = STP_Temperature,  
				  G4double  pressure = STP_Pressure); 
				      
  // Construct a G4Material from scratch by fraction mass
  // 
  inline G4Material* ConstructNewMaterial(
				  const G4String& name,
				  const std::vector<G4String>& elm,
				  const std::vector<G4double>& weight,
				  G4double dens, 
				  G4bool isotopes=true,
				  G4State   state    = kStateSolid,     
				  G4double  temp     = STP_Temperature,  
				  G4double  pressure = STP_Pressure); 

  // Construct a gas G4Material from scratch by atome count
  // 
  inline G4Material* ConstructNewGasMaterial(const G4String& name,
					     const G4String& nameNist,
					     G4double temp, 
					     G4double pres, 
					     G4bool isotopes=true);

  // Get number of G4Materials
  //
  inline size_t GetNumberOfMaterials();
  
  inline G4int GetVerbose();

  void SetVerbose(G4int);

  // Print G4Material by name
  //
  void PrintG4Material(const G4String&);

  // Print predefined Geant4 materials:
  // "simple" - only pure materials in basic state (Z = 1, ..., 98)
  // "compound" - NIST compounds
  // "hep" - HEP materials and compounds
  // "all" - all
  //
  inline void ListMaterials(const G4String&);

  // Access to the list of names of Geant4 predefined materials
  //
  inline const std::vector<G4String>& GetNistMaterialNames() const;

  // Fast computation of Z^1/3
  //
  inline G4double GetZ13(G4double Z);
  inline G4double GetZ13(G4int Z);

  // Fast computation of A^0.27 for natuaral abandances
  //
  inline G4double GetA27(G4int Z);

  // Fast computation of log(A)
  //
  inline G4double GetLOGA(G4double A);
  inline G4double GetLOGZ(G4int Z);

  // Fast computation of log(A) for natuaral abandances
  //
  inline G4double GetLOGA(G4int Z);

private:

  G4NistManager();
  static G4NistManager* instance;

  G4double POWERZ13[256];
  G4double LOGA[256];
  G4double POWERA27[101];
  G4double LOGAZ[101];
  
  std::vector<G4Element*>   elements;
  std::vector<G4Material*>  materials;
  
  size_t   nElements;
  size_t   nMaterials;
  
  G4int    verbose;

  G4NistElementBuilder*    elmBuilder;
  G4NistMaterialBuilder*   matBuilder;
  G4NistMessenger*         messenger;

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline size_t G4NistManager::GetNumberOfMaterials() 
{
  return nMaterials;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline G4Element* G4NistManager::GetElement(size_t index)
{
  G4Element* elm = 0; 
  const G4ElementTable* theElementTable = G4Element::GetElementTable();
  if(index < theElementTable->size()) elm = (*theElementTable)[index];
  return elm;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline 
G4Element* G4NistManager::FindOrBuildElement(G4int Z, G4bool isotopes)
{
  return elmBuilder->FindOrBuildElement(Z, isotopes);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline
G4Element* G4NistManager::FindOrBuildElement(const G4String& symb,
                                                   G4bool isotopes)
{
  return elmBuilder->FindOrBuildElement(symb, isotopes);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline size_t G4NistManager::GetNumberOfElements() const
{ 
  return nElements;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline G4int G4NistManager::GetZ(const G4String& symb) const
{
  return elmBuilder->GetZ(symb);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline G4double G4NistManager::GetAtomicMassAmu(G4int Z) const
{
  return elmBuilder->GetA(Z);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline 
G4double G4NistManager::GetIsotopeMass(G4int Z, G4int N) const
{
  return elmBuilder->GetIsotopeMass(Z, N);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline 
G4double G4NistManager::GetAtomicMass(G4int Z, G4int N) const
{
  return elmBuilder->GetAtomicMass(Z, N);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline 
G4double G4NistManager::GetTotalElectronBindingEnergy(G4int Z) const
{
  return elmBuilder->GetTotalElectronBindingEnergy(Z);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline 
G4double G4NistManager::GetIsotopeAbundance(G4int Z, G4int N) const
{
  return elmBuilder->GetIsotopeAbundance(Z, N);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline 
G4int G4NistManager::GetNistFirstIsotopeN(G4int Z) const
{
  return elmBuilder->GetNistFirstIsotopeN(Z);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline 
G4int G4NistManager::GetNumberOfNistIsotopes(G4int Z) const
{
  return elmBuilder->GetNumberOfNistIsotopes(Z);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline 
const std::vector<G4String>& G4NistManager::GetNistElementNames() const
{
  return elmBuilder->GetElementNames();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline void G4NistManager::PrintElement(G4int Z)
{
  elmBuilder->PrintElement(Z);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline G4Material* G4NistManager::GetMaterial(size_t index)
{
  const G4MaterialTable* theMaterialTable = G4Material::GetMaterialTable();
  G4Material* mat = 0;
  if(index < theMaterialTable->size()) mat = (*theMaterialTable)[index];
  return mat;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline G4int G4NistManager::GetVerbose()
{
  return verbose;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline
G4Material* G4NistManager::FindOrBuildMaterial(const G4String& name,
					       G4bool isotopes,
					       G4bool warning)
{
  return matBuilder->FindOrBuildMaterial(name, isotopes, warning);  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline G4Material* G4NistManager::ConstructNewMaterial(
                                      const G4String& name,
                                      const std::vector<G4String>& elm,
                                      const std::vector<G4int>& nbAtoms,
				      G4double dens, 
				      G4bool isotopes,
				      G4State   state,     
				      G4double  T,  
				      G4double  P) 

{
  return 
    matBuilder->ConstructNewMaterial(name,elm,nbAtoms,dens,isotopes,state,T,P);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline G4Material* G4NistManager::ConstructNewMaterial(
                                      const G4String& name,
                                      const std::vector<G4String>& elm,
                                      const std::vector<G4double>& w,
				      G4double dens, 
				      G4bool isotopes,
				      G4State   state,     
				      G4double  T,  
				      G4double  P) 
{
  return matBuilder->ConstructNewMaterial(name,elm,w,dens,isotopes,state,T,P);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline G4Material* G4NistManager::ConstructNewGasMaterial(
				      const G4String& name,
                                      const G4String& nameNist,
				      G4double temp, G4double pres, 
				      G4bool isotopes)
{
  return matBuilder->ConstructNewGasMaterial(name,nameNist,
					     temp,pres,isotopes);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline void G4NistManager::ListMaterials(const G4String& list)
{
  matBuilder->ListMaterials(list);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline
const std::vector<G4String>& G4NistManager::GetNistMaterialNames() const
{
  return matBuilder->GetMaterialNames();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline G4double G4NistManager::GetZ13(G4double Z)
{
  G4int iz = G4int(Z);
  G4double x = (Z - G4double(iz))/(3.0*Z);
  if(iz > 255) iz = 255;
  else if(iz < 0) iz = 0;
  return POWERZ13[iz]*(1.0 + x);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline G4double G4NistManager::GetZ13(G4int Z)
{
  return POWERZ13[Z];
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline G4double G4NistManager::GetA27(G4int Z)
{
  G4double res = 0.0;
  if(Z < 101) res = POWERA27[Z]; 
  return res;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline G4double G4NistManager::GetLOGZ(G4int Z)
{
  G4double res = 0.0;
  if(Z < 256) res = LOGA[Z];
  return res;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline G4double G4NistManager::GetLOGA(G4double A)
{
  G4int ia = G4int(A);
  G4double x = (A - G4double(ia))/A;
  if(ia > 255) ia = 255;
  else if(ia < 0) ia = 0;
  return LOGA[ia] + x*(1.0 - 0.5*x);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline G4double G4NistManager::GetLOGA(G4int Z)
{
  G4double res = 0.0;
  if(Z < 101) res = LOGAZ[Z]; 
  return res;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

