//RESPONSIBILITY: Ben was responsible for designing, implementing, and testing this class.

#ifndef AB__ARMYBATTLE_H
#define AB__ARMYBATTLE_H
//DESCRIPTION
/*
This is the main "ArmyBattle" class that runs the game loop, and sets up the world.
*/
//CLASSES
class ArmyBattle;

//INCLUDES
#include <memory>

#include "ArmyEngine.h"

#include "ArmyBattleStateMachine.h"
#include "World.h"

class ArmyBattle {
private:
	World& world;
	ArmyBattleStateMachine stateMachine;
public:
	ArmyBattle();

	//The main game loop which is used to run the game
	void runMainGameLoop();
};

#endif //AB__ARMYBATTLE_H