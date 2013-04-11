#include <memory>
#include <vector>
#include <cassert>

#include "SystemManager.h"
#include "Systems.h"

SystemManager::SystemManager() {
}

void SystemManager::addSystem(std::shared_ptr<systemType> system) {
	assert(!this->hasSystem(system->getName()) && "System of that type already exists");
	this->systemList.push_back(system);
}

bool SystemManager::hasSystem(const std::string& name) {
	for (auto system : this->systemList) {
		if (system->getName() == name) {
			return true;
		}
	}
	return false;
}

void SystemManager::removeSystem(const std::string& name) {
	assert(this->hasSystem(name) && "System by that name doesn't exist");
	systemListType::iterator pos;
	for (pos ; pos != this->systemList.end(); pos++) {
		if (pos->get()->getName() == name) {
			this->systemList.erase(pos);
			return;
		}
	}
	assert(0 && "Somehow, the element didn't exist");
}

int SystemManager::processSystemList() {
	for (auto system : this->systemList) {
		system->process();
	}
	return EXIT_SUCCESS;
}