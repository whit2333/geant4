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
// Hadrontherapy advanced example for Geant4
// See more at: https://twiki.cern.ch/twiki/bin/view/Geant4/AdvancedExamplesHadrontherapy

#include "HadrontherapyPrimaryGeneratorAction.hh"
#include "HadrontherapyPrimaryGeneratorMessenger.hh"
#include "HadrontherapyAnalysisManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4GeneralParticleSource.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "Randomize.hh"

/////////////////////////////////////////////////////////////////////////////
HadrontherapyPrimaryGeneratorAction::HadrontherapyPrimaryGeneratorAction()
{
  
   SetDefaultPrimaryParticle();  
  
  // Definition of the General particle Source
  particleGun = new G4GeneralParticleSource();
}  

/////////////////////////////////////////////////////////////////////////////
HadrontherapyPrimaryGeneratorAction::~HadrontherapyPrimaryGeneratorAction()
{
  delete particleGun;
  
}

/////////////////////////////////////////////////////////////////////////////
void HadrontherapyPrimaryGeneratorAction::SetDefaultPrimaryParticle()
{ 
 
}
  /////////////////////////////////////////////////////////////////////////////
  void HadrontherapyPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
  {
#ifdef G4ANALYSIS_USE_ROOT
    // Increment the event counter
    HadrontherapyAnalysisManager::GetInstance()->startNewEvent();
#endif
    particleGun -> GeneratePrimaryVertex( anEvent ); 
    } 

