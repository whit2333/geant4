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
// Author: Mathieu Karamitros, kara@cenbg.in2p3.fr

// The code is developed in the framework of the ESA AO7146
//
// We would be very happy hearing from you, send us your feedback! :)
//
// In order for Geant4-DNA to be maintained and still open-source,
// article citations are crucial. 
// If you use Geant4-DNA chemistry and you publish papers about your software, 
// in addition to the general paper on Geant4-DNA:
//
// Int. J. Model. Simul. Sci. Comput. 1 (2010) 157–178
//
// we would be very happy if you could please also cite the following
// reference papers on chemistry:
//
// J. Comput. Phys. 274 (2014) 841-882
// Prog. Nucl. Sci. Tec. 2 (2011) 503-508 

#ifndef MOLECULEGUNMESSENGER_HH_
#define MOLECULEGUNMESSENGER_HH_

#include "G4UImessenger.hh"
#include "G4ThreeVector.hh"
#include "G4memory.hh"
#include "G4MoleculeGun.hh"
#include <vector>

class G4UIcmdWithAString;
class G4UIcmdWith3VectorAndUnit;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithAnInteger;
class G4UIdirectory;
class G4MoleculeGunMessenger;
class G4MoleculeShoot;

//------------------------------------------------------------------------------

class G4MoleculeShootMessenger : public G4UImessenger
{
public:
  G4MoleculeShootMessenger(const G4String& name,
                           G4MoleculeGunMessenger*,
                           G4shared_ptr<G4MoleculeShoot>);
  virtual ~G4MoleculeShootMessenger();
  virtual void SetNewValue(G4UIcommand * command, G4String newValue);
  virtual G4String GetCurrentValue(G4UIcommand * command);

  inline G4shared_ptr<G4MoleculeShoot>& GetShoot() {
    return fpShoot;
  }

protected:
  G4UIcmdWithAString* fpGunSpecies;
  G4UIcmdWith3VectorAndUnit* fpGunPosition;
  G4UIcmdWith3VectorAndUnit* fpGunRdnmPosition ;
  G4UIcmdWithADoubleAndUnit* fpGunTime;
  G4UIcmdWithAnInteger* fpGunN;
  G4UIcmdWithAString* fpGunType;
  G4shared_ptr<G4MoleculeShoot> fpShoot;
};

//------------------------------------------------------------------------------

class G4MoleculeGunMessenger : public G4UImessenger
{

public:
  G4MoleculeGunMessenger(G4MoleculeGun*);
  virtual ~G4MoleculeGunMessenger();

  virtual void SetNewValue(G4UIcommand * command, G4String newValue);
  virtual G4String GetCurrentValue(G4UIcommand * command);

  const std::vector<G4MoleculeShootMessenger*>&
    GetShootMessengers() const
  {
    return fMultipleGun;
  }

protected:
  G4MoleculeGun* fpMoleculeGun;
  G4UIcmdWithAString* fpGunNewGunType;

  template<typename T>
  G4MoleculeShootMessenger* CreateNewType(const G4String& name)
  {
    G4shared_ptr<G4MoleculeShoot> moleculeShoot(new TG4MoleculeShoot<T>());
    G4MoleculeShootMessenger* shoot =
        new G4MoleculeShootMessenger(name,
                                     this,
                                     moleculeShoot);
    fMultipleGun.push_back(shoot);
    fpMoleculeGun->AddMoleculeShoot(shoot->GetShoot());
    return shoot;
  }

  std::vector<G4MoleculeShootMessenger*> fMultipleGun;
};

#endif /* MOLECULEGUNMESSENGER_HH_ */
