#include "StateManager.h"

void StateManager::addStateCallback(const std::string& name, functionTemplate func) {
	auto callbackManager = CallbackManager::getInstance();
	callbackManager->addCallback(name, (functionTemplate) func);
}

void StateManager::setEnable(const std::string& name) {
	this->stateList[name] = true;
}

void StateManager::setDisable(const std::string& name) {
	this->stateList[name] = false;
}

stateType StateManager::getState(const std::string& name) {
	if (!this->hasState(name)) {
		return false;
	}
	else {
		return this->stateList[name];
	}
}

bool StateManager::hasState(const std::string& name) {
	if (this->stateList.find(name) == this->stateList.end()) {
		return false;
	}
	return true;
}