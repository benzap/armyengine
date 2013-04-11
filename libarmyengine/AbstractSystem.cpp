//INCLUDES
#include <memory>
#include <list>
#include <string>

#include "AbstractSystem.h"

AbstractSystem::AbstractSystem(std::string name) : 
	name(name), 
	entityManager(EntityManager::getInstance()) {}

AbstractSystem::~AbstractSystem() {}

std::string AbstractSystem::getName() {
	return this->name;
}