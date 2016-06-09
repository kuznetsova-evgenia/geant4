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
// neutron_hp -- source file
// J.P. Wellisch, Nov-1996
// A prototype of the low energy neutron transport model.
//
// 070523 Try to limit sum of secondary photon energy while keeping distribution shape 
//        in the of nDiscrete = 1 an nPartial = 1. Most case are satisfied. 
//        T. Koi
// 070606 Add Partial case by T. Koi 
// 070618 fix memory leaking by T. Koi
// 080801 fix memory leaking by T. Koi
// 080801 Correcting data disorder which happened when both InitPartial 
//        and InitAnglurar methods was called in a same instance by T. Koi
//
// there is a lot of unused (and undebugged) code in this file. Kept for the moment just in case. @@

#include "G4NeutronHPPhotonDist.hh"
#include "G4NeutronHPLegendreStore.hh"
#include "G4Electron.hh"
#include "G4Poisson.hh"

#include <numeric>

G4bool G4NeutronHPPhotonDist::InitMean(std::ifstream & aDataFile)
{
  G4bool result = true;
  if(aDataFile >> repFlag)
  {
    aDataFile >> targetMass;
    if(repFlag==1)
    {
    // multiplicities
      aDataFile >> nDiscrete;
      disType = new G4int[nDiscrete];
      energy = new G4double[nDiscrete];
      actualMult = new G4int[nDiscrete];
      theYield = new G4NeutronHPVector[nDiscrete];
      for (G4int i=0; i<nDiscrete; i++)
      {
	aDataFile >> disType[i]>>energy[i];
	energy[i]*=eV;
	theYield[i].Init(aDataFile, eV);
      }
    }
    else if(repFlag == 2)
    {
       aDataFile >> theInternalConversionFlag;
       aDataFile >> theBaseEnergy;
       theBaseEnergy*=eV;
       aDataFile >> theInternalConversionFlag;
       aDataFile >> nGammaEnergies;
       theLevelEnergies = new G4double[nGammaEnergies];
       theTransitionProbabilities = new G4double[nGammaEnergies];
       if(theInternalConversionFlag == 2) thePhotonTransitionFraction = new G4double[nGammaEnergies];
       for(G4int  ii=0; ii<nGammaEnergies; ii++)
       {
	 if(theInternalConversionFlag == 1)
	 {
           aDataFile >> theLevelEnergies[ii] >> theTransitionProbabilities[ii];
	   theLevelEnergies[ii]*=eV;
	 }
	 else if(theInternalConversionFlag == 2)
	 {
           aDataFile >> theLevelEnergies[ii] >> theTransitionProbabilities[ii] >> thePhotonTransitionFraction[ii];
	   theLevelEnergies[ii]*=eV;
	 }
	 else
	 {
           throw G4HadronicException(__FILE__, __LINE__, "G4NeutronHPPhotonDist: Unknown conversion flag");
	 }
      }
       // Note, that this is equivalent to using the 'Gamma' classes.
      // throw G4HadronicException(__FILE__, __LINE__, "G4NeutronHPPhotonDist: Transition probability array not sampled for the moment.");
    }
    else
    {
      G4cout << "Data representation in G4NeutronHPPhotonDist: "<<repFlag<<G4endl;
      throw G4HadronicException(__FILE__, __LINE__, "G4NeutronHPPhotonDist: This data representation is not implemented.");
    }
  }
  else
  {
    result = false;
  }
  return result;
}

void G4NeutronHPPhotonDist::InitAngular(std::ifstream & aDataFile)
{

  G4int i, ii;
  //angular distributions
  aDataFile >> isoFlag;
  if (isoFlag != 1)
  {
    aDataFile >> tabulationType >> nDiscrete2 >> nIso;
//080731
      if ( theGammas != NULL && nDiscrete2 != nDiscrete ) G4cout << "080731c G4NeutronHPPhotonDist nDiscrete2 != nDiscrete, It looks like something wrong in your NDL files. Please update the latest. If you still have this messages after the update, then please report to Geant4 Hyper News." << G4endl;

      // The order of cross section (InitPartials) and distribution (InitAngular here) data are different, we have to re-coordinate consistent data order.
      std::vector < G4double > vct_gammas_par; 
      std::vector < G4double > vct_shells_par; 
      std::vector < G4int > vct_primary_par; 
      std::vector < G4int > vct_distype_par; 
      std::vector < G4NeutronHPVector* > vct_pXS_par;
      if ( theGammas != NULL ) 
      {
         //copy the cross section data 
         for ( i = 0 ; i < nDiscrete ; i++ )
         {
            vct_gammas_par.push_back( theGammas[ i ] );
            vct_shells_par.push_back( theShells[ i ] );
            vct_primary_par.push_back( isPrimary[ i ] );
            vct_distype_par.push_back( disType[ i ] );
            G4NeutronHPVector* hpv = new G4NeutronHPVector;
            *hpv = thePartialXsec[ i ];
            vct_pXS_par.push_back( hpv );
         }
      }
     if ( theGammas == NULL ) theGammas = new G4double[nDiscrete2];
     if ( theShells == NULL ) theShells = new G4double[nDiscrete2];
//080731

    for (i=0; i< nIso; i++) // isotropic photons
    {
       aDataFile >> theGammas[i] >> theShells[i];
       theGammas[i]*=eV;
       theShells[i]*=eV;
    }
    nNeu = new G4int [nDiscrete2-nIso];
    if(tabulationType==1)theLegendre=new G4NeutronHPLegendreTable *[nDiscrete2-nIso];
    if(tabulationType==2)theAngular =new G4NeutronHPAngularP *[nDiscrete2-nIso];
    for(i=nIso; i< nDiscrete2; i++)
    {
      if(tabulationType==1) 
      {
        aDataFile >> theGammas[i] >> theShells[i] >> nNeu[i-nIso];
        theGammas[i]*=eV;
        theShells[i]*=eV;
        theLegendre[i-nIso]=new G4NeutronHPLegendreTable[nNeu[i-nIso]];
        theLegendreManager.Init(aDataFile); 
        for (ii=0; ii<nNeu[i-nIso]; ii++)
        {
          theLegendre[i-nIso][ii].Init(aDataFile);
        }
      }
      else if(tabulationType==2)
      {
        aDataFile >> theGammas[i] >> theShells[i] >> nNeu[i-nIso];
        theGammas[i]*=eV;
        theShells[i]*=eV;
        theAngular[i-nIso]=new G4NeutronHPAngularP[nNeu[i-nIso]];
        for (ii=0; ii<nNeu[i-nIso]; ii++)
        {
          theAngular[i-nIso][ii].Init(aDataFile);
        }
      }
      else
      {
        G4cout << "tabulation type: tabulationType"<<G4endl;
        throw G4HadronicException(__FILE__, __LINE__, "cannot deal with this tabulation type for angular distributions.");
      }
    }
//080731
     if ( vct_gammas_par.size() > 0 ) 
     {
        //Reordering cross section data to corrsponding distribution data 
        for ( i = 0 ; i < nDiscrete ; i++ ) 
        {
           for ( G4int j = 0 ; j < nDiscrete ; j++ )  
           {
              // Checking gamma and shell to identification 
              if ( theGammas[ i ] == vct_gammas_par [ j ] && theShells [ i ] == vct_shells_par[ j ] )
              {
                 isPrimary [ i ] = vct_primary_par [ j ];
                 disType [ i ] = vct_distype_par [ j ];
                 thePartialXsec[ i ] = ( *( vct_pXS_par[ j ] ) );
              }
           }
        }
        //Garbage collection 
        for ( std::vector < G4NeutronHPVector* >::iterator 
           it = vct_pXS_par.begin() ; it != vct_pXS_par.end() ; it++ )
        {
           delete *it;
        }
     }
//080731
  }
}


void G4NeutronHPPhotonDist::InitEnergies(std::ifstream & aDataFile)
{
  G4int i, energyDistributionsNeeded = 0;
  for (i=0; i<nDiscrete; i++)
  {
    if( disType[i]==1) energyDistributionsNeeded =1;
  }
  if(!energyDistributionsNeeded) return;
  aDataFile >>  nPartials;
  distribution = new G4int[nPartials];
  probs = new G4NeutronHPVector[nPartials];
  partials = new G4NeutronHPPartial * [nPartials];
  G4int nen;
  G4int dummy;
  for (i=0; i<nPartials; i++)
  {
    aDataFile >> dummy;
    probs[i].Init(aDataFile, eV);
    aDataFile >> nen;
    partials[i] = new G4NeutronHPPartial(nen);
    partials[i]->InitInterpolation(aDataFile);
    partials[i]->Init(aDataFile);
  }
}

void G4NeutronHPPhotonDist::InitPartials(std::ifstream & aDataFile)
{

  //G4cout << "G4NeutronHPPhotonDist::InitPartials " << G4endl;
  aDataFile >> nDiscrete >> targetMass;
  if(nDiscrete != 1)
  {
    theTotalXsec.Init(aDataFile, eV);
  }
  G4int i;
  theGammas = new G4double[nDiscrete];
  theShells = new G4double[nDiscrete];
  isPrimary = new G4int[nDiscrete];
  disType = new G4int[nDiscrete];
  thePartialXsec = new G4NeutronHPVector[nDiscrete];
  for(i=0; i<nDiscrete; i++)
  {
    aDataFile>>theGammas[i]>>theShells[i]>>isPrimary[i]>>disType[i];
    theGammas[i]*=eV;
    theShells[i]*=eV;
    thePartialXsec[i].Init(aDataFile, eV);
  }  

  //G4cout << "G4NeutronHPPhotonDist::InitPartials Test " << G4endl;
  //G4cout << "G4NeutronHPPhotonDist::InitPartials nDiscrete " << nDiscrete << G4endl;
  //G4NeutronHPVector* aHP = new G4NeutronHPVector;
  //aHP->Check(1);
}

G4ReactionProductVector * G4NeutronHPPhotonDist::GetPhotons(G4double anEnergy)
{

  //G4cout << "G4NeutronHPPhotonDist::GetPhotons repFlag " << repFlag << G4endl;
  // the partial cross-section case is not in this yet. @@@@  << 070601 TK add partial 
  G4int i, ii, iii;
  G4int nSecondaries = 0;
  G4ReactionProductVector * thePhotons = new G4ReactionProductVector;
  if(repFlag==1)
  {
    G4double current=0;
    for(i=0; i<nDiscrete; i++)
    {
      current = theYield[i].GetY(anEnergy);
      actualMult[i] = G4Poisson(current); // max cut-off still missing @@@
      if(nDiscrete==1&&current<1.0001) 
      {
        actualMult[i] = static_cast<G4int>(current);
        if(current<1) 
        {
          actualMult[i] = 0;
          if(G4UniformRand()<current) actualMult[i] = 1;
        }
      }
      nSecondaries += actualMult[i];
    }
    //G4cout << "nSecondaries " << nSecondaries  << " anEnergy " << anEnergy/eV << G4endl;
    for(i=0;i<nSecondaries;i++)
    {
      G4ReactionProduct * theOne = new G4ReactionProduct;
      theOne->SetDefinition(G4Gamma::Gamma());
      thePhotons->push_back(theOne);
    }
    G4int count=0;

/*
G4double totalCascadeEnergy = 0.;
G4double lastCascadeEnergy = 0.;
G4double eGamm = 0;
G4int maxEnergyIndex = 0;
*/
    //Gcout << "nDiscrete " << nDiscrete << " nPartials " << nPartials << G4endl;
//3456
      if ( nDiscrete == 1 && nPartials == 1 )  
      {
         if ( actualMult[ 0 ] > 0 ) 
         {
	    if ( disType[0] == 1 ) // continuum
            {

/*
      for(ii=0; ii< actualMult[0]; ii++)
      {   

          G4double  sum=0, run=0;
          for(iii=0; iii<nPartials; iii++) sum+=probs[iii].GetY(anEnergy);
          G4double random = G4UniformRand();
          G4int theP = 0;
          for(iii=0; iii<nPartials; iii++)
          {
            run+=probs[iii].GetY(anEnergy);
            theP = iii;
            if(random<run/sum) break;
          }
          if(theP==nPartials) theP=nPartials-1; // das sortiert J aus.
          sum=0; 
          G4NeutronHPVector * temp;
          temp = partials[theP]->GetY(anEnergy); //@@@ look at, seems fishy
          // Looking for TotalCascdeEnergy or LastMaxEnergy
          if (ii == 0)
          {
            maxEnergyIndex = temp->GetVectorLength()-1;
            totalCascadeEnergy = temp->GetX(maxEnergyIndex);
            lastCascadeEnergy = totalCascadeEnergy;
          }
          lastCascadeEnergy -= eGamm;
          if (ii != actualMult[i]-1) eGamm = temp->SampleWithMax(lastCascadeEnergy);
	  else eGamm = lastCascadeEnergy;
          thePhotons->operator[](count)->SetKineticEnergy(eGamm);
          delete temp;

     }
*/
               G4NeutronHPVector * temp;
               temp = partials[ 0 ]->GetY(anEnergy); //@@@ look at, seems fishy
               G4double maximumE = temp->GetX( temp->GetVectorLength()-1 ); // This is an assumption.

               //G4cout << "start " << actualMult[ 0 ] << " maximumE " << maximumE/eV << G4endl;

               std::vector< G4double > photons_e_best( actualMult[ 0 ] , 0.0 );
               G4double best = DBL_MAX;
               G4int maxTry = 1000; 
               for ( G4int j = 0 ; j < maxTry ; j++ )
               {
                  std::vector< G4double > photons_e( actualMult[ 0 ] , 0.0 );
                  for ( std::vector< G4double >::iterator 
                      it = photons_e.begin() ; it < photons_e.end() ; it++ ) 
                 {
                     *it = temp->Sample();   
                 }
                 if ( std::accumulate( photons_e.begin() , photons_e.end() , 0.0 ) > maximumE ) 
                 {
                    if ( std::accumulate( photons_e.begin() , photons_e.end() , 0.0 ) < best )
                       photons_e_best = photons_e;
                    continue;
                 }
                 else
                 {
                    for ( std::vector< G4double >::iterator 
                        it = photons_e.begin() ; it < photons_e.end() ; it++ ) 
                    {
                       thePhotons->operator[](count)->SetKineticEnergy( *it );
                    }  
                    //G4cout << "OK " << actualMult[0] << " j " << j << " total photons E  " 
                    //          << std::accumulate( photons_e.begin() , photons_e.end() , 0.0 )/eV << " ratio " << std::accumulate( photons_e.begin() , photons_e.end() , 0.0 ) / maximumE 
                    //          << G4endl;
                    
                    break;
                 }
                 G4cout << "NeutronHPPhotonDist could not find fitted energy set for multiplicity of " <<  actualMult[0] << "." << G4endl; 
                 G4cout << "NeutronHPPhotonDist will use the best set." << G4endl; 
                 for ( std::vector< G4double >::iterator 
                     it = photons_e_best.begin() ; it < photons_e_best.end() ; it++ ) 
                 {
                     thePhotons->operator[](count)->SetKineticEnergy( *it );
                 }
                 //G4cout << "Not Good " << actualMult[0] << " j " << j << " total photons E  " 
                 //       << best/eV << " ratio " << best / maximumE 
                 //       << G4endl;
               }
               // TKDB
               delete temp;
            }
	    else    // discrete
 	    {
               thePhotons->operator[](count)->SetKineticEnergy(energy[i]);
	    }
	    count++;
	    if(count    > nSecondaries)  throw G4HadronicException(__FILE__, __LINE__, "G4NeutronHPPhotonDist::GetPhotons inconsistancy");
        }
         
      }
      else
      {
    for(i=0; i<nDiscrete; i++)
    { 
      for(ii=0; ii< actualMult[i]; ii++)
      {   
	if(disType[i]==1) // continuum
	{
          G4double  sum=0, run=0;
          for(iii=0; iii<nPartials; iii++) sum+=probs[iii].GetY(anEnergy);
          G4double random = G4UniformRand();
          G4int theP = 0;
          for(iii=0; iii<nPartials; iii++)
          {
            run+=probs[iii].GetY(anEnergy);
            theP = iii;
            if(random<run/sum) break;
          }
          if(theP==nPartials) theP=nPartials-1; // das sortiert J aus.
          sum=0; 
          G4NeutronHPVector * temp;
          temp = partials[theP]->GetY(anEnergy); //@@@ look at, seems fishy
          G4double eGamm = temp->Sample();
          thePhotons->operator[](count)->SetKineticEnergy(eGamm);
          delete temp;
	}
	else // discrete
	{
          thePhotons->operator[](count)->SetKineticEnergy(energy[i]);
	}
	count++;
	if(count > nSecondaries)  throw G4HadronicException(__FILE__, __LINE__, "G4NeutronHPPhotonDist::GetPhotons inconsistancy");
      }
    }
      }
    // now do the angular distributions...
    if( isoFlag == 1)
    {
      for (i=0; i< nSecondaries; i++)
      {
	G4double costheta = 2.*G4UniformRand()-1;
	G4double theta = std::acos(costheta);
	G4double phi = twopi*G4UniformRand();
	G4double sinth = std::sin(theta);
	G4double en = thePhotons->operator[](i)->GetTotalEnergy();
	G4ThreeVector temp(en*sinth*std::cos(phi), en*sinth*std::sin(phi), en*std::cos(theta) );
	thePhotons->operator[](i)->SetMomentum( temp ) ;
  //      G4cout << "Isotropic distribution in PhotonDist"<<temp<<G4endl;
      }
    }
    else
    {
      for(i=0; i<nSecondaries; i++)
      { 
	G4double currentEnergy = thePhotons->operator[](i)->GetTotalEnergy();
	for(ii=0; ii<nDiscrete2; ii++) 
	{
          if (std::abs(currentEnergy-theGammas[ii])<0.1*keV) break;
	}
	if(ii==nDiscrete2) ii--; // fix for what seems an (file12 vs file 14) inconsistancy found in the ENDF 7N14 data. @@
	if(ii<nIso)
	{
          // isotropic distribution
          G4double theta = pi*G4UniformRand();
          G4double phi = twopi*G4UniformRand();
          G4double sinth = std::sin(theta);
          G4double en = thePhotons->operator[](i)->GetTotalEnergy();
          G4ThreeVector tempVector(en*sinth*std::cos(phi), en*sinth*std::sin(phi), en*std::cos(theta) );
          thePhotons->operator[](i)->SetMomentum( tempVector ) ;
	}
	else if(tabulationType==1)
	{
          // legendre polynomials
          G4int it(0);
          for (iii=0; iii<nNeu[ii-nIso]; iii++) // find the neutron energy
          {
            it = iii;
	    if(theLegendre[ii-nIso][iii].GetEnergy()>anEnergy)
              break;
          }
          G4NeutronHPLegendreStore aStore(2);
          aStore.SetCoeff(1, &(theLegendre[ii-nIso][it]));  
          aStore.SetCoeff(0, &(theLegendre[ii-nIso][it-1])); 
          G4double cosTh = aStore.SampleMax(anEnergy);
          G4double theta = std::acos(cosTh);
          G4double phi = twopi*G4UniformRand();
          G4double sinth = std::sin(theta);
          G4double en = thePhotons->operator[](i)->GetTotalEnergy();
          G4ThreeVector tempVector(en*sinth*std::cos(phi), en*sinth*std::sin(phi), en*std::cos(theta) );
          thePhotons->operator[](i)->SetMomentum( tempVector ) ;
	}
	else
	{
          // tabulation of probabilities.
          G4int it(0);
          for (iii=0; iii<nNeu[ii-nIso]; iii++) // find the neutron energy
          {
            it = iii;
	    if(theAngular[ii-nIso][iii].GetEnergy()>anEnergy)
              break;
          }
          G4double costh = theAngular[ii-nIso][it].GetCosTh(); // no interpolation yet @@
          G4double theta = std::acos(costh);
          G4double phi = twopi*G4UniformRand();
          G4double sinth = std::sin(theta);
          G4double en = thePhotons->operator[](i)->GetTotalEnergy();
          G4ThreeVector tmpVector(en*sinth*std::cos(phi), en*sinth*std::sin(phi), en*costh );
          thePhotons->operator[](i)->SetMomentum( tmpVector ) ;
	}
      }  
    } 
  }
  else if(repFlag == 2)
  {
    G4double * running = new G4double[nGammaEnergies];
    running[0]=theTransitionProbabilities[0];
    G4int i;
    for(i=1; i<nGammaEnergies; i++)
    {
      running[i]=running[i-1]+theTransitionProbabilities[i];
    }
    G4double random = G4UniformRand();
    G4int it=0;
    for(i=0; i<nGammaEnergies; i++)
    {
      it = i;
      if(random < running[i]/running[nGammaEnergies-1]) break;
    }
    delete [] running;
    G4double totalEnergy = theBaseEnergy - theLevelEnergies[it];
    G4ReactionProduct * theOne = new G4ReactionProduct;
    theOne->SetDefinition(G4Gamma::Gamma());
    random = G4UniformRand();
    if(theInternalConversionFlag==2 && random>thePhotonTransitionFraction[it])
    {
      theOne->SetDefinition(G4Electron::Electron());
    }
    theOne->SetTotalEnergy(totalEnergy);
    if( isoFlag == 1)
    {
      G4double costheta = 2.*G4UniformRand()-1;
      G4double theta = std::acos(costheta);
      G4double phi = twopi*G4UniformRand();
      G4double sinth = std::sin(theta);
      G4double en = theOne->GetTotalEnergy();
      G4ThreeVector temp(en*sinth*std::cos(phi), en*sinth*std::sin(phi), en*std::cos(theta) );
      theOne->SetMomentum( temp ) ;
    }
    else
    {
      G4double currentEnergy = theOne->GetTotalEnergy();
      for(ii=0; ii<nDiscrete2; ii++) 
      {
        if (std::abs(currentEnergy-theGammas[ii])<0.1*keV) break;
      }
      if(ii==nDiscrete2) ii--; // fix for what seems an (file12 vs file 14) inconsistancy found in the ENDF 7N14 data. @@
      if(ii<nIso)
      {
        // isotropic distribution
        G4double theta = pi*G4UniformRand();
        G4double phi = twopi*G4UniformRand();
        G4double sinth = std::sin(theta);
        G4double en = theOne->GetTotalEnergy();
        G4ThreeVector tempVector(en*sinth*std::cos(phi), en*sinth*std::sin(phi), en*std::cos(theta) );
        theOne->SetMomentum( tempVector ) ;
      }
      else if(tabulationType==1)
      {
        // legendre polynomials
        G4int it(0);
        for (iii=0; iii<nNeu[ii-nIso]; iii++) // find the neutron energy
        {
          it = iii;
	  if(theLegendre[ii-nIso][iii].GetEnergy()>anEnergy)
            break;
        }
        G4NeutronHPLegendreStore aStore(2);
        aStore.SetCoeff(1, &(theLegendre[ii-nIso][it]));  
        aStore.SetCoeff(0, &(theLegendre[ii-nIso][it-1])); 
        G4double cosTh = aStore.SampleMax(anEnergy);
        G4double theta = std::acos(cosTh);
        G4double phi = twopi*G4UniformRand();
        G4double sinth = std::sin(theta);
        G4double en = theOne->GetTotalEnergy();
        G4ThreeVector tempVector(en*sinth*std::cos(phi), en*sinth*std::sin(phi), en*std::cos(theta) );
        theOne->SetMomentum( tempVector ) ;
      }
      else
      {
        // tabulation of probabilities.
        G4int it(0);
        for (iii=0; iii<nNeu[ii-nIso]; iii++) // find the neutron energy
        {
          it = iii;
	  if(theAngular[ii-nIso][iii].GetEnergy()>anEnergy)
            break;
        }
        G4double costh = theAngular[ii-nIso][it].GetCosTh(); // no interpolation yet @@
        G4double theta = std::acos(costh);
        G4double phi = twopi*G4UniformRand();
        G4double sinth = std::sin(theta);
        G4double en = theOne->GetTotalEnergy();
        G4ThreeVector tmpVector(en*sinth*std::cos(phi), en*sinth*std::sin(phi), en*costh );
        theOne->SetMomentum( tmpVector ) ;
      }
    }
    thePhotons->push_back(theOne);
  }
  else if( repFlag==0 )
  {

// TK add 
      if ( thePartialXsec == 0 ) 
      {
         //G4cout << "repFlag is 0, but no PartialXsec data" << G4endl;
         //G4cout << "This is not support yet." << G4endl;
         return thePhotons;
      }

// Partial Case 

      G4ReactionProduct * theOne = new G4ReactionProduct;
      theOne->SetDefinition( G4Gamma::Gamma() );
      thePhotons->push_back( theOne );

// Energy 

      //G4cout << "Partial Case nDiscrete " << nDiscrete << G4endl;
      G4double sum = 0.0; 
      std::vector < G4double > dif( nDiscrete , 0.0 ); 
      for ( G4int i = 0 ; i < nDiscrete ; i++ ) 
      {
         G4double x = thePartialXsec[ i ].GetXsec( anEnergy );  // x in barn 
         if ( x > 0 ) 
         {
            sum += x;   
         } 
         dif [ i ] = sum; 
         //G4cout << "i " << i << ", x " << x << ", dif " << dif [ i ] << G4endl;
      }
      
      G4double rand = G4UniformRand();

      G4int iphoton = 0; 
      for ( G4int i = 0 ; i < nDiscrete ; i++ ) 
      {
         G4double y = rand*sum; 
         if ( dif [ i ] > y ) 
         {
            iphoton = i; 
            break;  
         } 
      }
      //G4cout << "iphoton " << iphoton << G4endl;
      //G4cout << "photon energy " << theGammas[ iphoton ] /eV  << G4endl;

// Angle 
      G4double cosTheta = 0.0; // mu

      if ( isoFlag == 1 )
      {

//       Isotropic Case

         cosTheta = 2.*G4UniformRand()-1;

      }
      else
      {

         if ( iphoton < nIso )
         {

//          still Isotropic 

            cosTheta = 2.*G4UniformRand()-1;

         }
         else
         {

            //G4cout << "Not Isotropic and isoFlag " << isoFlag  << G4endl;
            //G4cout << "tabulationType " << tabulationType << G4endl;
            //G4cout << "nDiscrete2  " << nDiscrete2 << G4endl;
            //G4cout << "nIso " << nIso << G4endl;
            //G4cout << "size of nNeu " << nDiscrete2-nIso << G4endl;
            //G4cout << "nNeu[iphoton-nIso] " << nNeu[iphoton-nIso] << G4endl;

            if ( tabulationType == 1 )
            {
//             legendre polynomials

               G4int iangle = 0; 
               for ( G4int j = 0 ; j < nNeu [ iphoton - nIso ] ; j++ )
               {
                  iangle = j;
                  if ( theLegendre[ iphoton - nIso ][ j ].GetEnergy() > anEnergy ) break;
               }
 
               G4NeutronHPLegendreStore aStore( 2 );
               aStore.SetCoeff( 1 , &( theLegendre[ iphoton - nIso ][ iangle ] ) );  
               aStore.SetCoeff( 0 , &( theLegendre[ iphoton - nIso ][ iangle - 1 ] ) ); 

               cosTheta = aStore.SampleMax( anEnergy );

            }
            else if ( tabulationType == 2 )
            {
        
//             tabulation of probabilities.

               G4int iangle = 0; 
               for ( G4int j = 0 ; j < nNeu [ iphoton - nIso ] ; j++ )
               {
                  iangle = j;
                  if ( theAngular[ iphoton - nIso ][ j ].GetEnergy() > anEnergy ) break;
               }

               cosTheta = theAngular[iphoton-nIso][ iangle ].GetCosTh(); // no interpolation yet @@

            }
         }
      }
      
// Set 
      G4double phi = twopi*G4UniformRand();
      G4double theta = std::acos( cosTheta );
      G4double sinTheta = std::sin( theta );

      G4double photonE = theGammas[ iphoton ];
      G4ThreeVector direction ( sinTheta*std::cos( phi ) , sinTheta * std::sin( phi ) , cosTheta );
      G4ThreeVector photonP = photonE * direction;
      thePhotons->operator[]( 0 )->SetMomentum( photonP ) ;
    
  }
  else
  {
    delete thePhotons;
    thePhotons = 0; // no gamma data available; some work needed @@@@@@@
  }    
  return thePhotons;
}

