#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4UIterminal.hh"
#include "G4UItcsh.hh"
#include "VSONDetectorConstruction.hh"
#include "QGSP_BERT.hh"
#include "VSONPrimaryGeneratorAction.hh"
#include "VSONRunAction.hh"
#include "VSONEventAction.hh"
#include "iostream"
#include "fstream"

#include "CLHEP/Random/Random.h"
#include <time.h>


#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif

int main(int argc,char** argv)
{ 

  G4String filename = "/dev/null";
  G4int Nevent = 0;
  if(argc>=2)Nevent = atoi(argv[1]);
  if(argc>=3)filename = argv[2];
  std::ofstream output(filename);


  time_t timer;
  time(&timer);
  int seed = long(timer);
  CLHEP::HepRandom::setTheSeed(seed);


  // Run manager
  //
  G4RunManager* runManager = new G4RunManager;

  // User Initialization classes (mandatory)
  //
  G4VUserDetectorConstruction* detector = new VSONDetectorConstruction();
  runManager->SetUserInitialization(detector);
  //
  G4VUserPhysicsList* physics = new QGSP_BERT;
  runManager->SetUserInitialization(physics);

  runManager->Initialize();

  // User Action classes
  //
  G4VUserPrimaryGeneratorAction* gen_action = new VSONPrimaryGeneratorAction;
  runManager->SetUserAction(gen_action);
  //
  G4UserRunAction* run_action = new VSONRunAction;
  runManager->SetUserAction(run_action);
  //
  G4UserEventAction* event_action = new VSONEventAction(output);
  runManager->SetUserAction(event_action);
  //
  
  //get the pointer to the User Interface manager   
  G4UImanager* UI = G4UImanager::GetUIpointer();  

  if (argc!=1)   // batch mode  
    {
      //G4String command = "/control/execute ";
      //G4String fileName = argv[1];
      //UI->ApplyCommand(command+fileName);
      runManager->BeamOn(Nevent);
    }
    
  else           // interactive mode : define visualization and UI terminal
    { 
#ifdef G4VIS_USE
      G4VisManager* visManager = new G4VisExecutive;
      visManager->Initialize();
#endif    
     
      G4UIsession * session = 0;
#ifdef G4UI_USE_TCSH
      session = new G4UIterminal(new G4UItcsh);      
#else
      session = new G4UIterminal();
#endif
#ifdef G4VIS_USE
      UI->ApplyCommand("/control/execute vis.mac");
#endif
      session->SessionStart();
      delete session;
     
#ifdef G4VIS_USE
      delete visManager;
#endif     
    }
    
  delete runManager;

  return 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
