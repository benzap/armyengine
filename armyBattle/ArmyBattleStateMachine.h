//RESPONSIBILITY: Both group members were responsible for designing, implementing, and testing this class, and worked on it at various points.

#ifndef AB__ARMYBATTLESTATEMACHINE_H
#define AB__ARMYBATTLESTATEMACHINE_H
//DESCRIPTION
/*
This is the game's state machine, which controls the player's turns (changing from one turn to another, changing the drones states from moving to sensing, 
sensing to broadcasting, etc. 
*/
//CLASSES
class ArmyBattleStateMachine;

//INCLUDES
#include <list>

#include "ArmyEngine.h"
#include "World.h"
#include "DroneUnit.h"

//BEGIN
class ArmyBattleStateMachine {
private:
	World& world;
public:
	ArmyBattleStateMachine();

	int operator() ();
};

#endif //AB__ARMYBATTLESTATEMACHINE_H