#include <iostream>

#include "WorldObject.h"
#include "ArmyEngine.h"

WorldObject::WorldObject(const std::string& name, float xPosition, float yPosition) :
	bCollision(false) {
		//grabbing the armyEngine singleton instance
		auto armyEngine = ArmyEngine::getInstance();

		//grabbing the factory to create our entity
		auto entityFactory = armyEngine->getEntityFactory();

		//grabbing our factory to create components
		auto componentFactory = armyEngine->getComponentFactory();

		//creating an entity with the given name
		this->entity = entityFactory.createMainEntity(name);

		//placing the entity within the system
		armyEngine->addEntity(this->entity);

		//create a position component and add it to the entity
		auto positionComponent = componentFactory.createPositionComponent(WORLD_POSITION_COMPONENT);
		this->entity->addComponent(positionComponent);

		//Position Component Attributes
		positionComponent->setAttribute_float(ATTRIBUTE_POSITION_X, xPosition);
		positionComponent->setAttribute_float(ATTRIBUTE_POSITION_Y, yPosition);
		positionComponent->update();

}

WorldObject::~WorldObject() {
#ifdef LOGGING
	std::cout << "Removing WorldObject " << this->getEntity()->getID() << std::endl;
#endif

	//remove the entity that the world object is linked to
	auto entityManager = EntityManager::getInstance();
	entityManager->removeEntity(this->getEntity());
}

void WorldObject::setPosition(float xPosition, float yPosition) {
	auto positionComponent = this->entity->getComponentByName(WORLD_POSITION_COMPONENT);
	positionComponent->setAttribute_float(ATTRIBUTE_POSITION_X, xPosition);
	positionComponent->setAttribute_float(ATTRIBUTE_POSITION_Y, yPosition);
	positionComponent->update();
}

bool WorldObject::hasCollided() {
	return this->bCollision;
}

void WorldObject::setCollided() {
	this->bCollision = true;
}

void WorldObject::clearCollision() {
	this->bCollision = false;
}

std::vector<float> WorldObject::getPosition() {
	//get the position component from the entity
	auto positionComponent = this->entity->getComponentByName(WORLD_POSITION_COMPONENT);

	//create and assign values to the vector
	auto theVector = std::vector<float>();
	theVector.push_back(positionComponent->getAttribute_float(ATTRIBUTE_POSITION_X));
	theVector.push_back(positionComponent->getAttribute_float(ATTRIBUTE_POSITION_Y));
	return theVector;
}

std::shared_ptr<entityType> WorldObject::getEntity() {
	return this->entity;
}