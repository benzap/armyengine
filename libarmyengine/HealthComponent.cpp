#include "HealthComponent.h"

HealthComponent::HealthComponent(std::string name) 
	: AbstractComponent(name, "Health") {
	this->setAttribute_int("BaseHealth", 100);
}

int HealthComponent::update() {
	return 0;
}