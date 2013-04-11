#include <cassert>
#include <list>
#include <memory>

#include "SFML\Graphics.hpp"
#include "SFML\System.hpp"

#include "EventManager.h"

void EventManager::setWindow(sf::RenderWindow* window) {
	this->window = window;
}

void EventManager::pollEvents() {
	assert(this->window != nullptr && "sf::RenderWindow instance must be assigned to EventManager");

	//first, we clear out whatever events were in the list before
	this->eventList.clear();

	eventType event;
	while(this->window->pollEvent(event)) {
		auto allocEvent = std::shared_ptr<eventType> (new eventType);
		*allocEvent = event;
		this->eventList.push_back(allocEvent);
	}
}

eventListType& EventManager::getEvents() {
	assert(this->window != nullptr && "sf::RenderWindow instance must be assigned to EventManager");
	return this->eventList;
}