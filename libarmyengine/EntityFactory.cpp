#include "EntityFactory.h"

int EntityFactory::idNum = 0;

EntityFactory::EntityFactory() {
}

std::shared_ptr<entityType> EntityFactory::createMainEntity(std::string name) {
	auto entity = std::shared_ptr<entityType>(new MainEntity(name, EntityFactory::idNum));
	EntityFactory::idNum += 1;
	return entity;
}