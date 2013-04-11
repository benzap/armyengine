#include <cassert>
#include <functional>
#include <algorithm>

#include "CollisionManager.h"

void CollisionManager::addCallback(const collisionTagTuple& tagTuple, functionCollisionTemplate func) {
	assert(!this->hasCallback(tagTuple) && "Already has the given relationship");
	this->callbackTable[tagTuple] = func;
}

bool CollisionManager::hasCallback(const collisionTagTuple& tagTuple) {
	if (this->callbackTable.find(tagTuple) == this->callbackTable.end()) {
		return false;
	}
	return true;
}

int CollisionManager::triggerCallback(const collisionTagTuple& tagTuple, const collisionParamTuple& paramTuple) {
	assert(this->hasCallback(tagTuple) && "Can't trigger callback, callback doesn't exist");
	return this->callbackTable[tagTuple](paramTuple);
}

void CollisionManager::removeCallback(const collisionTagTuple& tagTuple) {
	assert(this->hasCallback(tagTuple) && "Can't delete callback, callback doesn't exist");
	this->callbackTable.erase(tagTuple);
}

void CollisionManager::registerCollision(const registeredCollisionTuple& theTuple) {
	assert(!this->hasRegisteredCollision(theTuple) && "theTuple already exists");
	this->registeredCollisionList.push_back(theTuple);
}

void CollisionManager::unregisterCollision(const registeredCollisionTuple& theTuple) {
	assert(this->hasRegisteredCollision(theTuple) && "theTuple doesn't exist");
	this->registeredCollisionList.remove(theTuple);
}

bool CollisionManager::hasRegisteredCollision(const registeredCollisionTuple& theTuple) {
	auto iter = std::find(this->registeredCollisionList.begin(),
		this->registeredCollisionList.end(), 
		theTuple);
	if (iter == this->registeredCollisionList.end()) {
		return false;
	}
	return true;
}