#include <memory>
#include <list>
#include <vector>
#include <cassert>
#include <algorithm>
#include <iostream>

#include "EntityManager.h"
#include "Entities.h"
#include "AE_Attributes.h"

void EntityManager::addEntity(std::shared_ptr<entityType> entity) {
	this->entityList.push_back(entity);
}

void EntityManager::removeEntity(std::shared_ptr<entityType> entity) {
	assert(this->hasEntityById(entity->getID()) && "No entity exists with the given ID");
	auto iter = std::find(this->entityList.begin(), this->entityList.end(), entity);
	if (iter != this->entityList.end()) {
		this->entityList.erase(iter);
	}
}

bool EntityManager::hasEntityById(const int ID) {
	for (auto entity : this->entityList) {
		if (ID == entity->getID()) {
			return true;
		}
	}
	return false;
}

std::shared_ptr<entityType> EntityManager::getEntityById(const int ID) {
	assert(this->hasEntityById(ID) && "No entity with the given ID");
	for (auto entity : this->entityList) {
		if (ID == entity->getID()) {
			return entity;
		}
	}
	return std::shared_ptr<entityType> (nullptr);
}

entityVectorType EntityManager::getAllEntities() {
	return this->entityList;
}

entityListType EntityManager::getEntitiesByName(const std::string& entityName) {
	std::list<std::shared_ptr<entityType>> entityList;
	for ( auto entity : this->entityList) {
		if (entityName == entity->getName()) {
			entityList.push_back(entity);
		}
	}
	return entityList;
}

entityListType EntityManager::getEntitiesByFamily(const std::string& entityFamily) {
	std::list<std::shared_ptr<entityType>> entityList;
	for ( auto entity : this->entityList) {
		if (entityFamily == entity->getFamily()) {
			entityList.push_back(entity);
		}
	}
	return entityList;
}

void EntityManager::sortEntityList() {
	//call the handle on each of our entities
	for (auto entity : this->entityList) {
		entity->handle();
	}
	
	std::sort(entityList.begin(), entityList.end(),
		[] (std::shared_ptr<entityType> first, std::shared_ptr<entityType> second) {
			auto componentVector = first->getAllComponents();
			//grab first component with a z-buffer,
			// assuming components were sorted by entity.handle() function
			// for this particular situation
			auto compIter = std::find_if(componentVector.begin(), componentVector.end(),
				[] (std::shared_ptr<componentType> elem) {
					if (elem->hasAttribute(ATTRIBUTE_ZBUFFER)) {
						return true;
					}
					return false;
			});
			//if our first entity doesn't have a component
			// with a Z-buffer, we return false
			if (compIter == componentVector.end()) {
				return false;
			}
			//grab our Z-Buffer value from the component stored within
			// the iterator
			auto componentFirst = *compIter;
			float firstZ = componentFirst->getAttribute_float(ATTRIBUTE_ZBUFFER);

			componentVector = second->getAllComponents();
			compIter = std::find_if(componentVector.begin(), componentVector.end(),
				[] (std::shared_ptr<componentType> elem) {
					if (elem->hasAttribute(ATTRIBUTE_ZBUFFER)) {
						return true;
					}
					return false;
			});

			//if our second entity doesn't have a component
			// with a Z-buffer, we return true
			if (compIter == componentVector.end()) {
				return true;
			}
			//grab our Z-Buffer value from the component stored within
			// the iterator
			auto componentSecond = *compIter;
			float secondZ = componentSecond->getAttribute_float(ATTRIBUTE_ZBUFFER);

			return (firstZ < secondZ);
	});
}