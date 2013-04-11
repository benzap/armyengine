#include <memory>
#include <list>
#include <string>
#include <cassert>
#include <algorithm>

#include "AbstractComponent.h"
#include "AbstractEntity.h"

AbstractEntity::AbstractEntity(const std::string& name, const std::string& family,const int ID)
: name(name), family(family), ID(ID) {}

//AbstractEntity::~AbstractEntity() {}

int AbstractEntity::getID() {
	return this->ID;
}

const std::string& AbstractEntity::getName() {
	return this->name;
}

const std::string& AbstractEntity::getFamily() {
	return this->family;
}

bool AbstractEntity::hasComponentName(const std::string& name) {
	auto iter = std::find_if(this->componentVector.begin(), this->componentVector.end(),
		[&name] (std::shared_ptr<componentType> elem) {
			if (elem->getName() == name) {
				return true;
			}
			return false;
	});
	if (iter != componentVector.end()) {
		return true;
	}
	return false;
}

bool AbstractEntity::hasComponentFamily(const std::string& family) {
	auto iter = std::find_if(this->componentVector.begin(), this->componentVector.end(),
		[&family] (std::shared_ptr<componentType> elem) {
			if (elem->getFamily() == family) {
				return true;
			}
			return false;
	});
	if (iter != this->componentVector.end()) {
		return true;
	}
	return false;
}

void AbstractEntity::addComponent(std::shared_ptr<componentType> component) {
	assert(!this->hasComponentName(component->getName()) && "Already has component by that name");
	this->componentVector.push_back(component);
	return;
}

const componentVectorType& AbstractEntity::getAllComponents() {
	return this->componentVector;
}

std::list<std::shared_ptr<componentType>> AbstractEntity::getComponentsByFamily(const std::string& family) {
	std::list<std::shared_ptr<componentType>> componentList;
	for(auto component : this->componentVector) {
		if (family == component->getFamily()) {
			componentList.push_back(component);
		}
	}
	return componentList;
}

std::shared_ptr<componentType> AbstractEntity::getComponentByName(const std::string& name) {
	assert(this->hasComponentName(name) && "No component by that name");
	auto iter = std::find_if(this->componentVector.begin(), this->componentVector.end(),
		[&name] (std::shared_ptr<componentType> elem) {
			if (elem->getName() == name) {
				return true;
			}
			return false;
	});
	if (iter != this->componentVector.end()) {
		return *iter;
	}
	return std::shared_ptr<componentType> (nullptr);
}