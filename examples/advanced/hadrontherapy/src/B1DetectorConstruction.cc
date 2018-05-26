//***** Geant4.9.4: Generated by Geant4 Geometry Editor at  Sun Mar 18 05:39:45 EDT 2018 *****

//------HeaderFile-
 #include "B1DetectorConstruction.hh"

#include "G4UnitsTable.hh"

#include "G4VUserDetectorConstruction.hh"

#include "globals.hh"
#include "G4Material.hh"
#include "G4MaterialTable.hh"
#include "G4NistManager.hh"
#include "G4Element.hh"
#include "G4ElementTable.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Cons.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4PVPlacement.hh"
#include "G4PVReplica.hh"
#include "G4SDManager.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4SubtractionSolid.hh"
#include <assert.h>

using namespace CLHEP;

bool roEnabled = true;

B1DetectorConstruction::B1DetectorConstruction()
{
	if(roEnabled) {
		static G4String ROGeometryName = "DetectorROGeometry";
		RO = new HadrontherapyDetectorROGeometry(ROGeometryName);
		G4cout << "Going to register Parallel world...";
		RegisterParallelWorld(RO);
		G4cout << "... done" << G4endl;
	}
}

B1DetectorConstruction::~B1DetectorConstruction() {}

G4VPhysicalVolume* B1DetectorConstruction::Construct()
{
	G4cout << "Constructing B1DetectorConstruction...\n";
	G4VPhysicalVolume *world = ConstructVolumes();
	assert(htdc == nullptr);
	htdc.reset(new HadrontherapyDetectorConstruction(Envelope));
	if(roEnabled) {
		htdc->InitializeDetectorROGeometry(RO, htdc->GetDetectorToWorldPosition());
	}
	return world;
}

G4VPhysicalVolume* B1DetectorConstruction::ConstructVolumes( )
{
// Get nist material manager
  G4NistManager* nist = G4NistManager::Instance();
// Elements

// Materials from Combination


// Materials from Scratch
// Vacuum
G4double density= 0.0000000000000001*g/cm3;//from PhysicalConstants.h
G4double pressure= 3.e-5*bar;
G4double temperature = 300*kelvin;
G4double z;
G4double a;
 G4Material* Vacuum = new G4Material("Vacuum", z=1., a=1.01*g/mole, density,
kStateGas,temperature,pressure);
  /*G4double density= 2.376e-15*g/cm3; 
  G4double temperature= 300*kelvin;
  G4double pressure= 2.0e-5*bar;
  G4double nel=1;
  G4Material* Vacuum = new G4Material("Vacuum", density, nel,
                                       kStateGas,temperature,pressure);
  //Vacuum-> AddMaterial(Air, massfraction= 1.);*/


// Visualization attributes


G4VisAttributes * blue= new G4VisAttributes( G4Colour(0/255. ,51/255. ,255/255. ));
blue -> SetVisibility(true);
G4VisAttributes * green= new G4VisAttributes( G4Colour(0/255. ,204/255. ,51/255. ));
green -> SetVisibility(true);
G4VisAttributes * red= new G4VisAttributes( G4Colour(255/255. ,51/255. ,51/255. ));
red -> SetVisibility(true);
G4VisAttributes * white= new G4VisAttributes( G4Colour(255/255. ,255/255. ,255/255. ));
white -> SetVisibility(true);white->SetVisibility(false);

G4VisAttributes * yellow= new G4VisAttributes( G4Colour(255/255. ,255/255. ,51/255. ));
yellow -> SetVisibility(true);
G4VisAttributes * orange= new G4VisAttributes( G4Colour(255/255. ,204/255. ,51/255. ));
orange -> SetVisibility(true);

G4Material* World_mat = nist->FindOrBuildMaterial("G4_AIR");
G4Material* water = nist->FindOrBuildMaterial("G4_WATER");
G4Material* tungsten = nist->FindOrBuildMaterial("G4_W");
G4Material* mylar = nist->FindOrBuildMaterial("G4_MYLAR");
G4Material* kapton = nist->FindOrBuildMaterial("G4_KAPTON");
G4Material* aluminium = nist->FindOrBuildMaterial("G4_Al");

// Logical  Volumes

G4Box *solidBox3x3x4m= new G4Box("solidBox3x3x4m", 1500.0*mm, 1500.0*mm, 5000.0*mm );
G4LogicalVolume * Box3x3x4m = new G4LogicalVolume(solidBox3x3x4m, 	 //its solid
			 World_mat, 		 //its material
			"Box3x3x4m" ,		 //its name
			 0,0,0);

Box3x3x4m->SetVisAttributes(white);

G4Tubs *solidKapton_w= new G4Tubs("solidKapton_w", 0.0*mm, 72.0*mm, 1.25E-5*m, 0.0*deg, 360.0*deg );
G4LogicalVolume * Kapton_w = new G4LogicalVolume(solidKapton_w, 	 //its solid
			 kapton, 		 //its material
			"Kapton_w" ,		 //its name
			 0,0,0);

Kapton_w->SetVisAttributes(blue);

G4Box *solidBox3x3x4m1= new G4Box("solidBox3x3x4m1", 1500.0*mm, 1500.0*mm, 5000.0*mm );
G4LogicalVolume * Box3x3x4m1 = new G4LogicalVolume(solidBox3x3x4m1, 	 //its solid
			 World_mat, 		 //its material
			"Box3x3x4m1" ,		 //its name
			 0,0,0);

Box3x3x4m1->SetVisAttributes(white);

G4Tubs *solidTungsten_wire= new G4Tubs("solidTungsten_wire", 0.0*mm, 1.25E-5*m, 30.0*mm, 0.0*deg, 360.0*deg );
G4LogicalVolume * Tungsten_wire = new G4LogicalVolume(solidTungsten_wire, 	 //its solid
			 tungsten, 		 //its material
			"Tungsten_wire" ,		 //its name
			 0,0,0);

Tungsten_wire->SetVisAttributes(green);

G4Tubs *solidTungsten_wire1= new G4Tubs("solidTungsten_wire1", 0.0*mm, 1.25E-5*m, 30.0*mm, 0.0*deg, 360.0*deg );
G4LogicalVolume * Tungsten_wire1 = new G4LogicalVolume(solidTungsten_wire1, 	 //its solid
			 tungsten, 		 //its material
			"Tungsten_wire1" ,		 //its name
			 0,0,0);

Tungsten_wire1->SetVisAttributes(green);

G4Tubs *solidAlfoil= new G4Tubs("solidAlfoil", 0.0*mm, 60.0*mm, 3.03E-6*m, 0.0*deg, 360.0*deg );
G4LogicalVolume * Alfoil = new G4LogicalVolume(solidAlfoil, 	 //its solid
			 aluminium, 		 //its material
			"Alfoil" ,		 //its name
			 0,0,0);

Alfoil->SetVisAttributes(blue);

G4Tubs *solidMylarfoil= new G4Tubs("solidMylarfoil", 0.0*mm, 60.0*mm, 3.0E-6*m, 0.0*deg, 360.0*deg );
G4LogicalVolume * Mylarfoil = new G4LogicalVolume(solidMylarfoil, 	 //its solid
			 mylar, 		 //its material
			"Mylarfoil" ,		 //its name
			 0,0,0);

Mylarfoil->SetVisAttributes(red);
//---------------------------------------------------------------------------------------------------------------------------------
G4Tubs *solidSealing_cartridge= new G4Tubs("solidSealing_cartridge", 62.0*mm, 65.8*mm, 10.45*mm, 0.0*deg, 360.0*deg );
G4LogicalVolume * Sealing_cartridge = new G4LogicalVolume(solidSealing_cartridge, 	 //its solid
			 Vacuum, 		 //its material
			"Sealing_cartridge" ,		 //its name
			 0,0,0);

Sealing_cartridge->SetVisAttributes(yellow);

G4Tubs *solidSealing_cartridge_vac= new G4Tubs("solidSealing_cartridge_vac", 0*mm, 62*mm, 10.45*mm, 0.0*deg, 360.0*deg );
G4LogicalVolume * Sealing_cartridge_vac = new G4LogicalVolume(solidSealing_cartridge_vac, 	 //its solid
			 Vacuum, 		 //its material
			"Sealing_cartridge_vac" ,		 //its name
			 0,0,0);

//---------------------------------------------------------------------------------------------------------------------------------
G4Tubs *solidVacuum_tube= new G4Tubs("solidVacuum_tube", 21.0*mm, 25.0*mm, 180.0*mm, 0.0*rad, 360.0*rad );
G4LogicalVolume * Vacuum_tube = new G4LogicalVolume(solidVacuum_tube, 	 //its solid
			 Vacuum, 		 //its material
			"Vacuum_tube" ,		 //its name
			 0,0,0);

Vacuum_tube->SetVisAttributes(green);

G4Tubs *solidVacuum_tube_vac= new G4Tubs("solidVacuum_tube_vac", 0*mm, 21.0*mm, 180.0*mm, 0.0*rad, 360.0*rad );
G4LogicalVolume * Vacuum_tube_vac = new G4LogicalVolume(solidVacuum_tube_vac, 	 //its solid
			 Vacuum, 		 //its material
			"Vacuum_tube_vac" ,		 //its name
			 0,0,0);
//-----------------------------------------------------------------------------------------------------------------------------
G4Tubs *solidVacuum_tube2= new G4Tubs("solidVacuum_tube2", 22.5*mm, 24.5*mm, 8.0*mm, 0.0*deg, 360.0*deg );
G4LogicalVolume * Vacuum_tube2 = new G4LogicalVolume(solidVacuum_tube2, 	 //its solid
			 Vacuum, 		 //its material
			"Vacuum_tube2" ,		 //its name
			 0,0,0);

Vacuum_tube2->SetVisAttributes(yellow);

G4Tubs *solidVacuum_tube2_vac= new G4Tubs("solidVacuum_tube2_vac", 0*mm, 22.5*mm, 8.0*mm, 0.0*deg, 360.0*deg );
G4LogicalVolume * Vacuum_tube2_vac = new G4LogicalVolume(solidVacuum_tube2_vac, 	 //its solid
			 Vacuum, 		 //its material
			"Vacuum_tube2_vac" ,		 //its name
			 0,0,0);

//-----------------------------------------------------------------------------------------------------------------------------
G4Cons *solidQPSSM_junction= new G4Cons("solidQPSSM_junction", 24.75*mm, 28.75*mm, 30.5*mm, 34.5*mm, 12.5*mm, 0.0*deg, 360.0*deg );
G4LogicalVolume * QPSSM_junction = new G4LogicalVolume(solidQPSSM_junction, 	 //its solid
			 Vacuum, 		 //its material
			"QPSSM_junction" ,		 //its name
			 0,0,0);

QPSSM_junction->SetVisAttributes(red);

G4Cons *solidQPSSM_junction_vac= new G4Cons("solidQPSSM_junction_vac", 0*mm, 24.75*mm, 0*mm, 30.5*mm, 12.5*mm, 0.0*deg, 360.0*deg );
G4LogicalVolume * QPSSM_junction_vac = new G4LogicalVolume(solidQPSSM_junction_vac, 	 //its solid
			 Vacuum, 		 //its material
			"QPSSM_junction_vac" ,		 //its name
			 0,0,0);

//------------------------------------------------------------------------------------------------------------------------------
G4Trd *solidVacuumSM1_inner= new G4Trd("solidVacuumSM1_inner", 35.0*mm, 35.0*mm, 33.0*mm, 42.0*mm, 167.0*mm );
G4Trd *solidVacuumSM2_outer= new G4Trd("solidVacuumSM2_outer", 39.0*mm, 39.0*mm, 37.0*mm, 46.0*mm, 167.0*mm );
G4Trd *solidVacuumSM3_inner= new G4Trd("solidVacuumSM3_inner", 35.0*mm, 62.5*mm, 42.0*mm, 63.0*mm, 185.0*mm );
G4Trd *solidVacuumSM4_outer= new G4Trd("solidVacuumSM4_outer", 39.0*mm, 66.5*mm, 46.0*mm, 67.0*mm, 185.0*mm );

G4SubtractionSolid* SM_vac1 = new G4SubtractionSolid("SM_vacuum1",solidVacuumSM2_outer,solidVacuumSM1_inner);
G4LogicalVolume *SM_vacuum1  = new G4LogicalVolume(SM_vac1, 	 //its solid
			 Vacuum, 		 //its material
			"VacuumSM4_outer" ,		 //its name
			 0,0,0);

G4SubtractionSolid* SM_vac2 = new G4SubtractionSolid("SM_vacuum2",solidVacuumSM4_outer,solidVacuumSM3_inner);
G4LogicalVolume *SM_vacuum2  = new G4LogicalVolume(SM_vac2, 	 //its solid
			 Vacuum, 		 //its material
			"VacuumSM4_outer" ,		 //its name
			 0,0,0);

G4Box *solidPBSvacuumch= new G4Box("solidPBSvacuumch", 295.0*mm, 295.0*mm, 523.0*mm );
G4LogicalVolume * PBSvacuumch = new G4LogicalVolume(solidPBSvacuumch, 	 //its solid
			 Vacuum, 		 //its material
			"PBSvacuumch" ,		 //its name
			 0,0,0);

PBSvacuumch->SetVisAttributes(red);

G4Trd *solidVacuumSM1_inner_vac= new G4Trd("solidVacuumSM1_inner_vac", 35.0*mm, 35.0*mm, 33.0*mm, 42.0*mm, 167.0*mm );
G4LogicalVolume * VacuumSM1_inner_vac = new G4LogicalVolume(solidVacuumSM1_inner_vac, 	 //its solid
			 Vacuum, 		 //its material
			"VacuumSM1_inner_vac" ,		 //its name
			 0,0,0);

G4Trd *solidVacuumSM2_inner_vac= new G4Trd("solidVacuumSM3_inner_vac", 35.0*mm, 62.5*mm, 42.0*mm, 63.0*mm, 185.0*mm );
G4LogicalVolume * VacuumSM3_inner_vac = new G4LogicalVolume(solidVacuumSM2_inner_vac, 	 //its solid
			 Vacuum, 		 //its material
			"VacuumSM3_inner_vac" ,		 //its name
			 0,0,0);


//-----------------------------------------------------------------------------------------------------------------------

G4Box *solidKapton_kevlar_W= new G4Box("solidKapton_kevlar_W", 196.0*mm, 156.0*mm, 5.0E-5*m );
G4LogicalVolume * Kapton_kevlar_W = new G4LogicalVolume(solidKapton_kevlar_W, 	 //its solid
			 kapton, 		 //its material
			"Kapton_kevlar_W" ,		 //its name
			 0,0,0);

Kapton_kevlar_W->SetVisAttributes(blue);

G4Box *solidIC23_Entrance_window= new G4Box("solidIC23_Entrance_window", 160.0*mm, 160.0*mm, 0.095*mm );
G4LogicalVolume * IC23_Entrance_window = new G4LogicalVolume(solidIC23_Entrance_window, 	 //its solid
			 mylar, 		 //its material
			"IC23_Entrance_window" ,		 //its name
			 0,0,0);
IC23_Entrance_window->SetVisAttributes(red);

G4Box *solidIC23_Mylar12um1= new G4Box("solidIC23_Mylar12um1", 160.0*mm, 160.0*mm, 0.006*mm );
G4LogicalVolume * IC23_Mylar12um1 = new G4LogicalVolume(solidIC23_Mylar12um1, 	 //its solid
			 mylar, 		 //its material
			"IC23_Mylar12um1" ,		 //its name
			 0,0,0);
IC23_Mylar12um1->SetVisAttributes(green);

G4Box *solidIC23_Mylar12um2= new G4Box("solidIC23_Mylar12um2", 160.0*mm, 160.0*mm, 0.006*mm );
G4LogicalVolume * IC23_Mylar12um2 = new G4LogicalVolume(solidIC23_Mylar12um2, 	 //its solid
			 mylar, 		 //its material
			"IC23_Mylar12um2" ,		 //its name
			 0,0,0);

IC23_Mylar12um2->SetVisAttributes(blue);

G4Box *solidIC23_Mylar12um3= new G4Box("solidIC23_Mylar12um3", 160.0*mm, 160.0*mm, 0.006*mm );
G4LogicalVolume * IC23_Mylar12um3 = new G4LogicalVolume(solidIC23_Mylar12um3, 	 //its solid
			 mylar, 		 //its material
			"IC23_Mylar12um3" ,		 //its name
			 0,0,0);
IC23_Mylar12um3->SetVisAttributes(green);


G4Box *solidIC23_Mylar2_5um= new G4Box("solidIC23_Mylar2_5um", 160.0*mm, 160.0*mm, 0.00125*mm );
G4LogicalVolume * IC23_Mylar2_5um = new G4LogicalVolume(solidIC23_Mylar2_5um, 	 //its solid
			 mylar, 		 //its material
			"IC23_Mylar2_5um" ,		 //its name
			 0,0,0);
IC23_Mylar2_5um->SetVisAttributes(yellow);

// Physical Volumes ----  Single Positioned Placement,   Repeated Placement,   Slicing  --------------------------- 


// Single Positioned Placement 

G4RotationMatrix rotMatrixWorld;   // unit rotation matrix
G4double angleWorld = 0.0*deg;   // rotational angle
rotMatrixWorld.rotateX(angleWorld);  // rot matrix

G4VPhysicalVolume *  World= new G4PVPlacement( new G4RotationMatrix(rotMatrixWorld) ,        // Frame rotation 
		 G4ThreeVector(0.0*mm, 0.0*mm, 0.0*mm),
		 "World",   // 1st constructor its name 
		 Box3x3x4m,         //its logical volume 
		 NULL,	//its mother volume 
		 false,	//no boolean operation 
		 0);	//copy number 

G4RotationMatrix rotMatrixEnvelope;   // unit rotation matrix
G4double angleEnvelope = 0.0*deg;   // rotational angle
rotMatrixEnvelope.rotateX(angleEnvelope);  // rot matrix

Envelope= new G4PVPlacement( new G4RotationMatrix(rotMatrixEnvelope) ,        // Frame rotation 
		 G4ThreeVector(0.0*mm, 0.0*mm, 0.0*mm),
		 "Envelope",   // 1st constructor its name 
		 Box3x3x4m1,         //its logical volume 
		 World,	//its mother volume 
		 false,	//no boolean operation 
		 0);	//copy number 

G4RotationMatrix rotMatrixIC1_Alfoil;   // unit rotation matrix
G4double angleIC1_Alfoil = 0.0*deg;   // rotational angle
rotMatrixIC1_Alfoil.rotateX(angleIC1_Alfoil);  // rot matrix

G4VPhysicalVolume *  IC1_Alfoil= new G4PVPlacement( new G4RotationMatrix(rotMatrixIC1_Alfoil) ,        // Frame rotation 
		 G4ThreeVector(0.0*mm, 0.0*mm, -1970.15*mm),
		 "IC1_Alfoil",   // 1st constructor its name 
		 Alfoil,         //its logical volume 
		 Envelope,	//its mother volume 
		 false,	//no boolean operation 
		 0);	//copy number 

G4RotationMatrix rotMatrixIC1_Mylar;   // unit rotation matrix
G4double angleIC1_Mylar = 0.0*deg;   // rotational angle
rotMatrixIC1_Mylar.rotateX(angleIC1_Mylar);  // rot matrix

G4VPhysicalVolume *  IC1_Mylar= new G4PVPlacement( new G4RotationMatrix(rotMatrixIC1_Mylar) ,        // Frame rotation 
		 G4ThreeVector(0.0*mm, 0.0*mm, 0.0*mm),
		 "IC1_Mylar",   // 1st constructor its name 
		 Mylarfoil,         //its logical volume 
		 IC1_Alfoil,	//its mother volume 
		 false,	//no boolean operation 
		 0);	//copy number 
//-------------------------------------------------------------------------------------------------------------------------------
G4RotationMatrix rotMatrixQPS_sealing_cartridge;   // unit rotation matrix
G4double angleQPS_sealing_cartridge = 0.0*deg;   // rotational angle
rotMatrixQPS_sealing_cartridge.rotateX(angleQPS_sealing_cartridge);  // rot matrix

G4VPhysicalVolume *  QPS_sealing_cartridge= new G4PVPlacement( new G4RotationMatrix(rotMatrixQPS_sealing_cartridge) ,        // Frame rotation 
		 G4ThreeVector(0.0*mm, 0.0*mm, -1949.95*mm),
		 "QPS_sealing_cartridge",   // 1st constructor its name 
		 Sealing_cartridge,         //its logical volume 
		 Envelope,	//its mother volume 
		 false,	//no boolean operation 
		 0);	//copy number 


G4RotationMatrix rotMatrixQPS_sealing_cartridge_vac_ph;   // unit rotation matrix
G4double angleQPS_sealing_cartridge_vac_ph = 0.0*deg;   // rotational angle
rotMatrixQPS_sealing_cartridge_vac_ph.rotateX(angleQPS_sealing_cartridge_vac_ph);  // rot matrix
G4VPhysicalVolume *  QPS_sealing_cartridge_vac_ph= new G4PVPlacement( new G4RotationMatrix(rotMatrixQPS_sealing_cartridge_vac_ph) ,        // Frame rotation 
		 G4ThreeVector(0.0*mm, 0.0*mm, 0*mm),
		 "QPS_sealing_cartridge_vac_ph",   // 1st constructor its name 
		 Sealing_cartridge_vac,         //its logical volume 
		 QPS_sealing_cartridge,	//its mother volume 
		 false,	//no boolean operation 
		 0);	//copy number 

//--------------------------------------------------------------------------------------------------------------------------------
G4RotationMatrix rotMatrixQPS_vacuum_tube;   // unit rotation matrix
G4double angleQPS_vacuum_tube = 0.0*deg;   // rotational angle
rotMatrixQPS_vacuum_tube.rotateX(angleQPS_vacuum_tube);  // rot matrix

G4VPhysicalVolume *  QPS_vacuum_tube= new G4PVPlacement( new G4RotationMatrix(rotMatrixQPS_vacuum_tube) ,        // Frame rotation 
		 G4ThreeVector(0.0*mm, 0.0*mm, -1759.5*mm),
		 "QPS_vacuum_tube",   // 1st constructor its name 
		 Vacuum_tube,         //its logical volume 
		 Envelope,	//its mother volume 
		 false,	//no boolean operation 
		 0);	//copy number 

G4RotationMatrix rotMatrixQPS_vacuum_tube_vac_ph;   // unit rotation matrix
G4double angleQPS_vacuum_tube_vac_ph = 0.0*deg;   // rotational angle
rotMatrixQPS_vacuum_tube_vac_ph.rotateX(angleQPS_vacuum_tube_vac_ph);  // rot matrix

G4VPhysicalVolume *  QPS_vacuum_tube_vac_ph= new G4PVPlacement( new G4RotationMatrix(rotMatrixQPS_vacuum_tube_vac_ph) ,        // Frame rotation 
		 G4ThreeVector(0.0*mm, 0.0*mm, 0*mm),
		 "QPS_vacuum_tube_vac_ph",   // 1st constructor its name 
		 Vacuum_tube_vac,         //its logical volume 
		 QPS_vacuum_tube,	//its mother volume 
		 false,	//no boolean operation 
		 0);	//copy number 
//-------------------------------------------------------------------------------------------------------------------------
G4RotationMatrix rotMatrixQPS_vacuum_tube2;   // unit rotation matrix
G4double angleQPS_vacuum_tube2 = 0.0*deg;   // rotational angle
rotMatrixQPS_vacuum_tube2.rotateX(angleQPS_vacuum_tube2);  // rot matrix

G4VPhysicalVolume *  QPS_vacuum_tube2= new G4PVPlacement( new G4RotationMatrix(rotMatrixQPS_vacuum_tube2) ,        // Frame rotation 
		 G4ThreeVector(0.0*mm, 0.0*mm, -1571.5*mm),
		 "QPS_vacuum_tube2",   // 1st constructor its name 
		 Vacuum_tube2,         //its logical volume 
		 Envelope,	//its mother volume 
		 false,	//no boolean operation 
		 0);	//copy number 

G4RotationMatrix rotMatrixQPS_vacuum_tube2_vac_ph;   // unit rotation matrix
G4double angleQPS_vacuum_tube2_vac_ph = 0.0*deg;   // rotational angle
rotMatrixQPS_vacuum_tube2_vac_ph.rotateX(angleQPS_vacuum_tube2_vac_ph);  // rot matrix

G4VPhysicalVolume *  QPS_vacuum_tube2_vac_ph= new G4PVPlacement( new G4RotationMatrix(rotMatrixQPS_vacuum_tube2_vac_ph) ,        // Frame rotation 
		 G4ThreeVector(0.0*mm, 0.0*mm, 0*mm),
		 "QPS_vacuum_tube2_vac_ph",   // 1st constructor its name 
		 Vacuum_tube2_vac,         //its logical volume 
		 QPS_vacuum_tube2,	//its mother volume 
		 false,	//no boolean operation 
		 0);	//copy number 

//-------------------------------------------------------------------------------------------------
G4RotationMatrix rotMatrixQPS_SM_vacuumjunction;   // unit rotation matrix
G4double angleQPS_SM_vacuumjunction = 0.0*deg;   // rotational angle
rotMatrixQPS_SM_vacuumjunction.rotateX(angleQPS_SM_vacuumjunction);  // rot matrix

G4VPhysicalVolume *  QPS_SM_vacuumjunction= new G4PVPlacement( new G4RotationMatrix(rotMatrixQPS_SM_vacuumjunction) ,        // Frame rotation 
		 G4ThreeVector(0.0*mm, 0.0*mm, -1551.0*mm),
		 "QPS_SM_vacuumjunction",   // 1st constructor its name 
		 QPSSM_junction,         //its logical volume 
		 Envelope,	//its mother volume 
		 false,	//no boolean operation 
		 0);	//copy number 

G4RotationMatrix rotMatrixQPS_SM_vacuumjunction_vac_ph;   // unit rotation matrix
G4double angleQPS_SM_vacuumjunction_vac_ph = 0.0*deg;   // rotational angle
rotMatrixQPS_SM_vacuumjunction_vac_ph.rotateX(angleQPS_SM_vacuumjunction_vac_ph);  // rot matrix

G4VPhysicalVolume *  QPS_SM_vacuumjunction_vac_ph= new G4PVPlacement( new G4RotationMatrix(rotMatrixQPS_SM_vacuumjunction_vac_ph) ,        // Frame rotation 
		 G4ThreeVector(0.0*mm, 0.0*mm, 0*mm),
		 "QPS_SM_vacuumjunction_vac_ph",   // 1st constructor its name 
		 QPSSM_junction_vac,         //its logical volume 
		 QPS_SM_vacuumjunction,	//its mother volume 
		 false,	//no boolean operation 
		 0);	//copy number 
//------------------------------------------------------------------------------------------------------------------

G4RotationMatrix rotMatrixSMph_vacuum1;   // unit rotation matrix
G4double angleSMph_vacuum1 = 0.0*deg;   // rotational angle
rotMatrixSMph_vacuum1.rotateX(angleSMph_vacuum1);  // rot matrix

G4VPhysicalVolume *  SMph_vacuum1= new G4PVPlacement( new G4RotationMatrix(rotMatrixSMph_vacuum1) ,        // Frame rotation 
		 G4ThreeVector(0.0*mm, 0.0*mm, -1371.0*mm),
		 "SMph_vacuum1",   // 1st constructor its name 
		 SM_vacuum1,         //its logical volume 
		 Envelope,	//its mother volume 
		 false,	//no boolean operation 
		 0);	//copy number

G4RotationMatrix rotMatrixSMph_vacuum1_vac_ph;   // unit rotation matrix
G4double angleSMph_vacuum1_vac_ph = 0.0*deg;   // rotational angle
rotMatrixSMph_vacuum1_vac_ph.rotateX(angleSMph_vacuum1_vac_ph);  // rot matrix

G4VPhysicalVolume *  SMph_vacuum1_vac_ph= new G4PVPlacement( new G4RotationMatrix(rotMatrixSMph_vacuum1_vac_ph) ,        // Frame rotation 
		 G4ThreeVector(0.0*mm, 0.0*mm, 0*mm),
		 "SMph_vacuum1_vac_ph",   // 1st constructor its name 
		 VacuumSM1_inner_vac,         //its logical volume 
		 SMph_vacuum1,	//its mother volume 
		 false,	//no boolean operation 
		 0);	//copy number 
//----------------------------------------------------------------------------------------------------------------

G4RotationMatrix rotMatrixSMph_vacuum2;   // unit rotation matrix
G4double angleSMph_vacuum2 = 0.0*deg;   // rotational angle
rotMatrixSMph_vacuum2.rotateX(angleSMph_vacuum2);  // rot matrix

G4VPhysicalVolume *  SMph_vacuum2= new G4PVPlacement( new G4RotationMatrix(rotMatrixSMph_vacuum2) ,        // Frame rotation 
		 G4ThreeVector(0.0*mm, 0.0*mm, -1019.5*mm),
		 "SMph_vacuum2",   // 1st constructor its name 
		 SM_vacuum2,         //its logical volume 
		 Envelope,	//its mother volume 
		 false,	//no boolean operation 
		 0);	//copy number

G4RotationMatrix rotMatrixSMph_vacuum2_vac_ph;   // unit rotation matrix
G4double angleSMph_vacuum2_vac_ph = 0.0*deg;   // rotational angle
rotMatrixSMph_vacuum2_vac_ph.rotateX(angleSMph_vacuum2_vac_ph);  // rot matrix

G4VPhysicalVolume *  SMph_vacuum2_vac_ph= new G4PVPlacement( new G4RotationMatrix(rotMatrixSMph_vacuum2_vac_ph) ,        // Frame rotation 
		 G4ThreeVector(0.0*mm, 0.0*mm, 0*mm),
		 "SMph_vacuum2_vac_ph",   // 1st constructor its name 
		 VacuumSM3_inner_vac,         //its logical volume 
		 SMph_vacuum2,	//its mother volume 
		 false,	//no boolean operation 
		 0);	//copy number  
//-------------------------------------------------------------------------------------------------------------------


G4RotationMatrix rotMatrixPBS_vacuum_ch_phys;   // unit rotation matrix
G4double anglePBS_vacuum_ch_phys = 0.0*deg;   // rotational angle
rotMatrixPBS_vacuum_ch_phys.rotateX(anglePBS_vacuum_ch_phys);  // rot matrix

G4VPhysicalVolume *  PBS_vacuum_ch_phys= new G4PVPlacement( new G4RotationMatrix(rotMatrixPBS_vacuum_ch_phys) ,        // Frame rotation 
		 G4ThreeVector(0.0*mm, 0.0*mm, -311.5*mm), //339.5
		 "PBS_vacuum_ch_phys",   // 1st constructor its name 
		 PBSvacuumch,         //its logical volume 
		 Envelope,	//its mother volume 
		 false,	//no boolean operation 
		 0);	//copy number 

G4RotationMatrix rotMatrixKapKewWindow_ph;   // unit rotation matrix
G4double angleKapKewWindow_ph = 0.0*deg;   // rotational angle
rotMatrixKapKewWindow_ph.rotateX(angleKapKewWindow_ph);  // rot matrix

G4VPhysicalVolume *  KapKewWindow_ph= new G4PVPlacement( new G4RotationMatrix(rotMatrixKapKewWindow_ph) ,        // Frame rotation 
		 G4ThreeVector(0.0*mm, 0.0*mm, 211.55*mm),
		 "KapKewWindow_ph",   // 1st constructor its name 
		 Kapton_kevlar_W,         //its logical volume 
		 Envelope,	//its mother volume 
		 false,	//no boolean operation 
		 0);	//copy number 

 if(0) {
G4Box *solidPhantom= new G4Box("solidPhantom", 500*mm, 500.0*mm, 500.0*mm );
G4LogicalVolume * Phantom = new G4LogicalVolume(solidPhantom, 	 //its solid
			 water, 		 //its material
			"Phantom" ,		 //its name
			 0,0,0);

Phantom->SetVisAttributes(green);

G4RotationMatrix rotMatrixPhantom_ph;   // unit rotation matrix
G4double anglePhantom_ph = 0.0*deg;   // rotational angle
rotMatrixPhantom_ph.rotateX(anglePhantom_ph);  // rot matrix

G4VPhysicalVolume *  Phantom_ph= new G4PVPlacement( new G4RotationMatrix(rotMatrixPhantom_ph) ,        // Frame rotation 
		 G4ThreeVector(0.0*mm, 0.0*mm, 1200*mm),
		 "Phantom_ph",   // 1st constructor its name 
		 Phantom,         //its logical volume 
		 Envelope,	//its mother volume 
		 false,	//no boolean operation 
		 0);	//copy number 
 }



// Repeated Placement Translation 
 

G4RotationMatrix rotMatrixIC1_405_electrodes;   // unit rotation matrix
G4double angleIC1_405_electrodes = 90.0*deg;   // rotational angle
rotMatrixIC1_405_electrodes.rotateY(angleIC1_405_electrodes);  // rot matrix

G4int copyIC1_405_electrodes;
copyIC1_405_electrodes=0;
for (G4int indexIC1_405_electrodes=1; indexIC1_405_electrodes<=12; indexIC1_405_electrodes++){
  G4double transIC1_405_electrodes =-19.25*mm+3.5*mm*(indexIC1_405_electrodes-1);
  G4VPhysicalVolume * IC1_405_electrodes = new G4PVPlacement(new G4RotationMatrix(rotMatrixIC1_405_electrodes),      //rotation 90 deg X 
		 G4ThreeVector(0.0*mm, transIC1_405_electrodes, -1975.02*mm),
		 "IC1_405_electrodes",   //its name 
		 Tungsten_wire,         //its logical volume
		 Envelope,            //its mother volume
		 false,             //no boolean operation
		 copyIC1_405_electrodes++);      //copy number 
}

G4RotationMatrix rotMatrixIC1_403_electrodes;   // unit rotation matrix
G4double angleIC1_403_electrodes = 90.0*deg;   // rotational angle
rotMatrixIC1_403_electrodes.rotateX(angleIC1_403_electrodes);  // rot matrix

G4int copyIC1_403_electrodes;
copyIC1_403_electrodes=0;
for (G4int indexIC1_403_electrodes=1; indexIC1_403_electrodes<=12; indexIC1_403_electrodes++){
  G4double transIC1_403_electrodes =-19.25*mm+3.5*mm*(indexIC1_403_electrodes-1);
  G4VPhysicalVolume * IC1_403_electrodes = new G4PVPlacement(new G4RotationMatrix(rotMatrixIC1_403_electrodes),      //no rotation 
		 G4ThreeVector(transIC1_403_electrodes, 0*mm, -1965.27*mm),
		 "IC1_403_electrodes",   //its name 
		 Tungsten_wire1,         //its logical volume
		 Envelope,            //its mother volume
		 false,             //no boolean operation
		 copyIC1_403_electrodes++);      //copy number 
}




G4int copyIC1kaptonEntW;
copyIC1kaptonEntW=0;
for (G4int indexIC1kaptonEntW=1; indexIC1kaptonEntW<=2;indexIC1kaptonEntW++){
  G4double transIC1kaptonEntW = -1979.9*mm+19.5*mm*(indexIC1kaptonEntW-1);
  G4VPhysicalVolume * IC1kaptonEntW = new G4PVPlacement(0,           //no rotation 
		 G4ThreeVector(0.0*mm, 0.0*mm, transIC1kaptonEntW),
		 "IC1kaptonEntW",        //its name 
		 Kapton_w,              //its logical volume
		 Envelope,                 //its mother volume
		 false,                 //no boolean operation
		 copyIC1kaptonEntW++);          //copy number
}

G4int copyIC23_Mylar12um1_ph;
copyIC23_Mylar12um1_ph=0;
for (G4int indexIC23_Mylar12um1_ph=1; indexIC23_Mylar12um1_ph<=2;indexIC23_Mylar12um1_ph++){
  G4double transIC23_Mylar12um1_ph = 282.6*mm+5.3*mm*(indexIC23_Mylar12um1_ph-1);
  G4VPhysicalVolume * IC23_Mylar12um1_ph = new G4PVPlacement(0,           //no rotation 
		 G4ThreeVector(0.0*mm, 0.0*mm, transIC23_Mylar12um1_ph),
		 "IC23_Mylar12um1_ph",        //its name 
		 IC23_Mylar12um1,              //its logical volume
		 Envelope,                 //its mother volume
		 false,                 //no boolean operation
		 copyIC23_Mylar12um1_ph++);          //copy number
}

G4int copyIC23_Mylar12um2_ph;
copyIC23_Mylar12um2_ph=0;
for (G4int indexIC23_Mylar12um2_ph=1; indexIC23_Mylar12um2_ph<=7;indexIC23_Mylar12um2_ph++){
  G4double transIC23_Mylar12um2_ph = 298.4*mm+5.3*mm*(indexIC23_Mylar12um2_ph-1);
  G4VPhysicalVolume * IC23_Mylar12um2_ph = new G4PVPlacement(0,           //no rotation 
		 G4ThreeVector(0.0*mm, 0.0*mm, transIC23_Mylar12um2_ph),
		 "IC23_Mylar12um2_ph",        //its name 
		 IC23_Mylar12um2,              //its logical volume
		 Envelope,                 //its mother volume
		 false,                 //no boolean operation
		 copyIC23_Mylar12um2_ph++);          //copy number
}

G4int copyIC23_Mylar12um3_ph;
copyIC23_Mylar12um3_ph=0;
for (G4int indexIC23_Mylar12um3_ph=1; indexIC23_Mylar12um3_ph<=2;indexIC23_Mylar12um3_ph++){
  G4double transIC23_Mylar12um3_ph = 340.9*mm+5.3*mm*(indexIC23_Mylar12um3_ph-1);
  G4VPhysicalVolume * IC23_Mylar12um3_ph = new G4PVPlacement(0,           //no rotation 
		 G4ThreeVector(0.0*mm, 0.0*mm, transIC23_Mylar12um3_ph),
		 "IC23_Mylar12um3_ph",        //its name 
		 IC23_Mylar12um3,              //its logical volume
		 Envelope,                 //its mother volume
		 false,                 //no boolean operation
		 copyIC23_Mylar12um3_ph++);          //copy number
}

G4int copyIC23_Mylar2_5um_ph;
copyIC23_Mylar2_5um_ph=0;
for (G4int indexIC23_Mylar2_5um_ph=1; indexIC23_Mylar2_5um_ph<=2;indexIC23_Mylar2_5um_ph++){
  G4double transIC23_Mylar2_5um_ph = 293.2*mm+42.4*mm*(indexIC23_Mylar2_5um_ph-1);
  G4VPhysicalVolume * IC23_Mylar2_5um_ph = new G4PVPlacement(0,           //no rotation 
		 G4ThreeVector(0.0*mm, 0.0*mm, transIC23_Mylar2_5um_ph),
		 "IC23_Mylar2_5um_ph",        //its name 
		 IC23_Mylar2_5um,              //its logical volume
		 Envelope,                 //its mother volume
		 false,                 //no boolean operation
		 copyIC23_Mylar2_5um_ph++);          //copy number
}

G4int copyIC23Entrance_W_ph;
copyIC23Entrance_W_ph=0;
for (G4int indexIC23Entrance_W_ph=1; indexIC23Entrance_W_ph<=2;indexIC23Entrance_W_ph++){
  G4double transIC23Entrance_W_ph = 273.6*mm+78.6*mm*(indexIC23Entrance_W_ph-1);
  G4VPhysicalVolume * IC23Entrance_W_ph = new G4PVPlacement(0,           //no rotation 
		 G4ThreeVector(0.0*mm, 0.0*mm, transIC23Entrance_W_ph),
		 "IC23Entrance_W_ph",        //its name 
		 IC23_Entrance_window,              //its logical volume
		 Envelope,                 //its mother volume
		 false,                 //no boolean operation
		 copyIC23Entrance_W_ph++);          //copy number
}
// Repeated Placement AxialSymmetoric


// Slicing Translation 


// Slicing AxialSymmetric 


// return the physical World


 return World;
}
