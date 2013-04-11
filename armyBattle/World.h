//RESPONSIBILITY: Both group members were responsible for designing, implementing, and testing this class, and worked on it at various points.

#ifndef AB__WORLD_H
#define AB__WORLD_H
//DESCRIPTION
/*
This is the world class. It instantiates all of the objects that are displayed on the screen, and contains information about all the drones as well as the game's state.
*/
//CLASSES
class World;

//INCLUDES
#include <list>

#include "ArmyEngine.h"
#include "DroneUnit.h"
#include "HomeBaseUnit.h"
#include "ScoreBoard.h"
#include "StatusBar.h"
#include "StatusLog.h"
#include "Unit.h"
#include "MouseCursor.h"
#include "FiringDangerZone.h"
#include "Button.h"
#include "Menu.h"
#include "Victory.h"
#include "HelpScreen.h"

//TYPEDEFS
typedef std::vector<std::shared_ptr<Unit>> unitListType;
typedef std::list<std::shared_ptr<DroneUnit>> droneListType;

//ENUMERATIONS
enum class EnumTurnState {
	RESUME, //Returning from MENU view
	INIT, //initializing when performing team switches
	ASSIGN, //assignment of next drone for the next 4 given routines
	MOVING, //moving state
	ATTACKING, //attacking state
	SENSING, //sensing state
	BROADCASTING, //broadcasting state
	VICTORY //victory state when a HomebaseUnit has been destroyed
};

//Determines the state of handling the view
enum class EnumViewState {
	WORLD,
	MENU,
	VICTORY
};

//DEFINITIONS
//component names for the world entity
#define AB_WORLD "World"
#define AB_WORLD_SPRITE "World_Sprite"
#define AB_WORLD_SHAPE_BASE "World_Shape_Base"
#define AB_WORLD_INPUT_PRESSED "World_Input_Pressed"
#define AB_WORLD_POSITION "World_Position"
#define AB_WORLD_OUTLINE_THICKNESS 3
#define AB_WORLD_OUT_OF_BOUNDS "World_Out_Of_Bounds"
#define AB_WORLD_OUT_OF_BOUNDS_POSITION "World_Out_Of_Bounds_Position"
#define AB_WORLD_OUT_OF_BOUNDS_SHAPE "World_Out_Of_Bounds_Shape"
#define AB_WORLD_OUT_OF_BOUNDS_COLLISION "World_Out_Of_Bounds_Collision"

#define NUM_UNITS_PER_TEAM 10

//HUD_SIZE is a subset of the WORLD_SIZE,
// and is used to determine how much space should be
// allocated to the HUD itself
#define WORLD_HUD_SIZE_X AB_WORLD_OUTLINE_THICKNESS*2
#define WORLD_HUD_SIZE_Y 50

#define WORLD_SIZE_X 800
#define WORLD_SIZE_Y 600

//BEGIN
class World {
private:
	unitListType unitList;
	int currentTurn;
	EnumTeam playerTurn;
	int currentDroneID;
	World();
public:
	Scoreboard scoreboard;
	StatusBar statusBar;
	StatusLog statusLog;
	MouseCursor mouseCursor;
	Button menuButton;
	FiringDangerZone firingDangerZone;
	Menu menu;
	Victory victory;
	HelpScreen helpScreen;

	EnumTurnState turnState;
	EnumViewState viewState;
	droneListType teamDroneList;

	static World* getInstance() {
		static World _instance;
		return &_instance;
	}

	void endGame(EnumTeam);

	void generateWorld();
	droneListType getDroneUnits(EnumTeam = EnumTeam::BOTH);
	unitListType& getUnitList();
	std::shared_ptr<DroneUnit> getDroneByID(int);
	std::shared_ptr<HomebaseUnit> getHomebaseByID(int);
	EnumTeam getPlayerTurn();
	void changePlayerTurn();
	EnumTurnState getTurnState();
	int getCurrentDroneID();
	void setCurrentDroneID(int);

};


#endif //AB__WORLD_H