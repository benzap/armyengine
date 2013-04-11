#include <string>

#include "ArmyBattle.h"
#include "AB_Assets.h"

ArmyBattle::ArmyBattle() :
	world(*World::getInstance()),
	stateMachine() {
		auto armyEngine = ArmyEngine::getInstance();

		//setting up all of the images assets and loading the sprites
		armyEngine->loadSpriteFromFile(AB_SPRITE_RED_DRONE_IDLE, 
			std::string(DEFAULT_IMAGE_FOLDER) + AB_SPRITE_RED_DRONE_IDLE);

		armyEngine->loadSpriteFromFile(AB_SPRITE_RED_DRONE_FINISHED, 
			std::string(DEFAULT_IMAGE_FOLDER) + AB_SPRITE_RED_DRONE_FINISHED);

		armyEngine->loadSpriteFromFile(AB_SPRITE_RED_DRONE_DEAD, 
			std::string(DEFAULT_IMAGE_FOLDER) + AB_SPRITE_RED_DRONE_DEAD);

		armyEngine->loadSpriteFromFile(AB_SPRITE_BLUE_DRONE_IDLE, 
			std::string(DEFAULT_IMAGE_FOLDER) + AB_SPRITE_BLUE_DRONE_IDLE);

		armyEngine->loadSpriteFromFile(AB_SPRITE_BLUE_DRONE_FINISHED, 
			std::string(DEFAULT_IMAGE_FOLDER) + AB_SPRITE_BLUE_DRONE_FINISHED);

		armyEngine->loadSpriteFromFile(AB_SPRITE_BLUE_DRONE_DEAD, 
			std::string(DEFAULT_IMAGE_FOLDER) + AB_SPRITE_BLUE_DRONE_DEAD);

		armyEngine->loadSpriteFromFile(AB_SPRITE_BACKGROUND, 
			std::string(DEFAULT_IMAGE_FOLDER) + AB_SPRITE_BACKGROUND);

		//assign our state machine to the army engine
		armyEngine->setStateMachineFunction(this->stateMachine);

		//generate our drones
		world.generateWorld();
}

void ArmyBattle::runMainGameLoop() {
	auto armyEngine = ArmyEngine::getInstance();
	armyEngine->runMainLoop();
}