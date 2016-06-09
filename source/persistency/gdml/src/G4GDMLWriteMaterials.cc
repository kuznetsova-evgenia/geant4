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
// $Id: G4GDMLWriteMaterials.cc,v 1.20 2008/07/16 15:46:34 gcosmo Exp $
// GEANT4 tag $Name: geant4-09-02 $
//
// class G4GDMLWriteMaterials Implementation
//
// Original author: Zoltan Torzsok, November 2007
//
// --------------------------------------------------------------------

#include "G4GDMLWriteMaterials.hh"

void G4GDMLWriteMaterials::
AtomWrite(xercesc::DOMElement* element,const G4double& a)
{
   xercesc::DOMElement* atomElement = NewElement("atom");
   atomElement->setAttributeNode(NewAttribute("unit","g/mole"));
   atomElement->setAttributeNode(NewAttribute("value",a*mole/g));
   element->appendChild(atomElement);
}

void G4GDMLWriteMaterials::
DWrite(xercesc::DOMElement* element,const G4double& d)
{
   xercesc::DOMElement* DElement = NewElement("D");
   DElement->setAttributeNode(NewAttribute("unit","g/cm3"));
   DElement->setAttributeNode(NewAttribute("value",d*cm3/g));
   element->appendChild(DElement);
}

void G4GDMLWriteMaterials::
PWrite(xercesc::DOMElement* element,const G4double& P)
{
   xercesc::DOMElement* PElement = NewElement("P");
   PElement->setAttributeNode(NewAttribute("unit","pascal"));
   PElement->setAttributeNode(NewAttribute("value",P/pascal));
   element->appendChild(PElement);
}

void G4GDMLWriteMaterials::
TWrite(xercesc::DOMElement* element,const G4double& T)
{
   xercesc::DOMElement* TElement = NewElement("T");
   TElement->setAttributeNode(NewAttribute("unit","K"));
   TElement->setAttributeNode(NewAttribute("value",T/kelvin));
   element->appendChild(TElement);
}

void G4GDMLWriteMaterials::
IsotopeWrite(const G4Isotope* const isotopePtr)
{
   const G4String name = GenerateName(isotopePtr->GetName(),isotopePtr);

   xercesc::DOMElement* isotopeElement = NewElement("isotope");
   isotopeElement->setAttributeNode(NewAttribute("name",name));
   isotopeElement->setAttributeNode(NewAttribute("N",isotopePtr->GetN()));
   isotopeElement->setAttributeNode(NewAttribute("Z",isotopePtr->GetZ()));
   materialsElement->appendChild(isotopeElement);
   AtomWrite(isotopeElement,isotopePtr->GetA());
}

void G4GDMLWriteMaterials::ElementWrite(const G4Element* const elementPtr)
{
   const G4String name = GenerateName(elementPtr->GetName(),elementPtr);

   xercesc::DOMElement* elementElement = NewElement("element");
   elementElement->setAttributeNode(NewAttribute("name",name));

   const size_t NumberOfIsotopes = elementPtr->GetNumberOfIsotopes();

   if (NumberOfIsotopes>0)
   {
      const G4double* RelativeAbundanceVector =
            elementPtr->GetRelativeAbundanceVector();             
      for (size_t i=0;i<NumberOfIsotopes;i++)
      {
         G4String fractionref = GenerateName(elementPtr->GetIsotope(i)->GetName(),
                                             elementPtr->GetIsotope(i));
         xercesc::DOMElement* fractionElement = NewElement("fraction");
         fractionElement->setAttributeNode(NewAttribute("n",
                                           RelativeAbundanceVector[i]));
         fractionElement->setAttributeNode(NewAttribute("ref",fractionref));
         elementElement->appendChild(fractionElement);
         AddIsotope(elementPtr->GetIsotope(i));
      }
   }
   else
   {
      elementElement->setAttributeNode(NewAttribute("Z",elementPtr->GetZ()));
      AtomWrite(elementElement,elementPtr->GetA());
   }

   materialsElement->appendChild(elementElement);
     // Append the element AFTER all the possible components are appended!
}

void G4GDMLWriteMaterials::MaterialWrite(const G4Material* const materialPtr)
{
   G4String state_str("undefined");
   const G4State state = materialPtr->GetState();
   if (state==kStateSolid) { state_str = "solid"; } else
   if (state==kStateLiquid) { state_str = "liquid"; } else
   if (state==kStateGas) { state_str = "gas"; }

   const G4String name = GenerateName(materialPtr->GetName(), materialPtr);

   xercesc::DOMElement* materialElement = NewElement("material");
   materialElement->setAttributeNode(NewAttribute("name",name));
   materialElement->setAttributeNode(NewAttribute("state",state_str));

   if (materialPtr->GetTemperature() != STP_Temperature)
     { TWrite(materialElement,materialPtr->GetTemperature()); }
   if (materialPtr->GetPressure() != STP_Pressure)
     { PWrite(materialElement,materialPtr->GetPressure()); }
   DWrite(materialElement,materialPtr->GetDensity());
  
   const size_t NumberOfElements = materialPtr->GetNumberOfElements();

   if (NumberOfElements>1)
   {
      const G4double* MassFractionVector = materialPtr->GetFractionVector();

      for (size_t i=0;i<NumberOfElements;i++)
      {
         const G4String fractionref =
                        GenerateName(materialPtr->GetElement(i)->GetName(),
                                     materialPtr->GetElement(i));
         xercesc::DOMElement* fractionElement = NewElement("fraction");
         fractionElement->setAttributeNode(NewAttribute("n",
                                           MassFractionVector[i]));
         fractionElement->setAttributeNode(NewAttribute("ref",fractionref));
         materialElement->appendChild(fractionElement);
         AddElement(materialPtr->GetElement(i));
      }
   }
   else
   {
      materialElement->setAttributeNode(NewAttribute("Z",materialPtr->GetZ()));
      AtomWrite(materialElement,materialPtr->GetA());
   }

   materialsElement->appendChild(materialElement);
     // Append the material AFTER all the possible components are appended!
}

void G4GDMLWriteMaterials::MaterialsWrite(xercesc::DOMElement* element)
{
   G4cout << "G4GDML: Writing materials..." << G4endl;

   materialsElement = NewElement("materials");
   element->appendChild(materialsElement);

   isotopeList.clear();
   elementList.clear();
   materialList.clear();
}

void G4GDMLWriteMaterials::AddIsotope(const G4Isotope* const isotopePtr)
{
   for (size_t i=0; i<isotopeList.size(); i++)   // Check if isotope is
   {                                             // already in the list!
     if (isotopeList[i] == isotopePtr)  { return; }
   }
   isotopeList.push_back(isotopePtr);
   IsotopeWrite(isotopePtr);
}

void G4GDMLWriteMaterials::AddElement(const G4Element* const elementPtr)
{
   for (size_t i=0;i<elementList.size();i++)     // Check if element is
   {                                             // already in the list!
      if (elementList[i] == elementPtr) { return; }
   }
   elementList.push_back(elementPtr);
   ElementWrite(elementPtr);
}

void G4GDMLWriteMaterials::AddMaterial(const G4Material* const materialPtr)
{
   for (size_t i=0;i<materialList.size();i++)    // Check if material is
   {                                             // already in the list!
      if (materialList[i] == materialPtr)  { return; }
   }
   materialList.push_back(materialPtr);
   MaterialWrite(materialPtr);
}
