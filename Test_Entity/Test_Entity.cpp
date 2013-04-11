#include <iostream>
#include <memory>

#include "Entities.h"
#include "Components.h"

int main() {

	auto entity = std::unique_ptr<AbstractEntity> (new MainEntity("SomeEntity", 0));
	entity->addComponent(std::shared_ptr<AbstractComponent>(new HealthComponent("DroneHealth")));
	entity->addComponent(std::shared_ptr<AbstractComponent>(new HealthComponent("ArmorHealth")));
	auto health = entity->getComponentByName("DroneHealth");
	health->setAttribute_int("BaseHealth", 90);
	std::cout << "Drone Health: " << health->getAttribute_int("BaseHealth") << std::endl;

	auto componentList = entity->getComponentsByFamily("Health");
	for (auto component : componentList) {
		std::cout << "Name: " << component->getName();
		std::cout << " BaseHealth: " << component->getAttribute_int("BaseHealth") << std::endl;
	}



	return 0;
}