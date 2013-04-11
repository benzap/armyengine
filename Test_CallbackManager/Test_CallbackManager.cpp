#include <iostream>
#include <memory>
#include "Managers.h"
#include "Entities.h"
#include "Components.h"
#include "AE_Attributes.h"

#define ENTITYID 0

class DisableSprites_Callback {
public:
	int operator() (int ID) {
		auto entityManager = EntityManager::getInstance();
		auto entity = entityManager->getEntityById(ID);

		//go through the entity and disable all sprites
		for (auto spriteComponent : entity->getComponentsByFamily("Sprite")) {
			spriteComponent->setAttribute_int(ATTRIBUTE_ENABLE, 0);
		}

		return 0;
	}
};

int main() {
	auto callbackManager = CallbackManager::getInstance();
	//add the callback to our manager
	callbackManager->addCallback("disableSprites", (functionTemplate) DisableSprites_Callback());
	callbackManager->addCallback("enableDroneSprite", (functionTemplate) [] (int ID) {
		auto entityManager = EntityManager::getInstance();
		auto entity = entityManager->getEntityById(ID);

		auto sComponent = entity->getComponentByName("DroneSprite");
		sComponent->setAttribute_int(ATTRIBUTE_ENABLE, 1);
		return 0;
	});

	//create a new entity with sprites
	auto entity = std::shared_ptr<MainEntity> (new MainEntity("Drone", ENTITYID));
	entity->addComponent(std::shared_ptr<AbstractComponent> (new SpriteComponent("DroneSprite")));
	entity->addComponent(std::shared_ptr<AbstractComponent> (new SpriteComponent("DroneRedTag")));

	//add the entity to the entity manager
	auto entityManager = EntityManager::getInstance();
	entityManager->addEntity(entity);

	for (auto spriteComponent : entity->getComponentsByFamily("Sprite")) {
		std::cout << "SpriteComponent['bEnabled'] --> " << spriteComponent->getAttribute_int(ATTRIBUTE_ENABLE) << std::endl;
	}

	//trigger the callback, effects entity with ID->ENTITYID
	callbackManager->triggerCallback("disableSprites", ENTITYID);

	//call second callback
	callbackManager->triggerCallback("enableDroneSprite", ENTITYID);


	//check to see if it worked (by default, sprite components bEnabled -> 1)
	for (auto spriteComponent : entity->getComponentsByFamily("Sprite")) {
		std::cout << "SpriteComponent['bEnabled'] --> " << spriteComponent->getAttribute_int(ATTRIBUTE_ENABLE) << std::endl;
	}

	return 0;
}