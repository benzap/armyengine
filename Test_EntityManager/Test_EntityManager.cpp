#include <iostream>
#include <memory>

#include "Managers.h"
#include "Entities.h"
#include "Components.h"


int main() {
	//preallocate the instance
	auto entityManager = EntityManager::getInstance();

	//lets create an entity to place in entity manager
	auto entity = std::shared_ptr<AbstractEntity> (new MainEntity("Drone", 0));
	entity->addComponent(std::shared_ptr<AbstractComponent> (new HealthComponent("Drone Health")));
	entity->addComponent(std::shared_ptr<AbstractComponent> (new HealthComponent("Drone Armor")));
	entityManager->addEntity(entity);

	entity = std::shared_ptr<AbstractEntity> (new MainEntity("Drone", 1));
	entity->addComponent(std::shared_ptr<AbstractComponent> (new HealthComponent("Drone Health")));
	entity->addComponent(std::shared_ptr<AbstractComponent> (new HealthComponent("Drone Armor")));
	entityManager->addEntity(entity);

	entity = std::shared_ptr<AbstractEntity> (new MainEntity("Base", 2));
	entity->addComponent(std::shared_ptr<AbstractComponent> (new HealthComponent("Drone Health")));
	entity->addComponent(std::shared_ptr<AbstractComponent> (new HealthComponent("Drone Armor")));
	entityManager->addEntity(entity);

	//getting entity by ID
	auto entity_0 = entityManager->getEntityById(0);
	std::cout << "Entity ID 0: " << entity_0->getName() << std::endl;

	//getting entity by Name
	auto entityList = entityManager->getEntitiesByName("Drone");
	std::cout << "list: entities by name 'Drone'" << std::endl;
	for (auto entity : entityList) {
		std::cout << "Name: " << entity->getName();
		std::cout << "( " << entity->getID() << " )" << std::endl;
	}

	//getting entity by Family
	entityList = entityManager->getEntitiesByFamily("Main");
	std::cout << "list: entities by family 'Main'" << std::endl;
	for (auto entity : entityList) {
		std::cout << "Name: " << entity->getName();
		std::cout << "( " << entity->getID() << " )" << std::endl;
	}

	//get all entities in an STL vector
	auto entityVec = entityManager->getAllEntities();
	std::cout << "list: all entities" << std::endl;
	for (auto entity : entityList) {
		std::cout << "Name: " << entity->getName();
		std::cout << "( " << entity->getID() << " )" << std::endl;
	}

	return 0;
}