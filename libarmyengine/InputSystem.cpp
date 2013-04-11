#include <iostream>
#include <memory>
#include <cassert>
#include <string>
#include <algorithm>

#include "SFML\Window.hpp"

#include "Components.h"
#include "InputSystem.h"
#include "CallbackManager.h"
#include "EventManager.h"
#include "AE_Events.h"
#include "AE_Attributes.h"

InputSystem::InputSystem() :
	AbstractSystem(COMPONENT_FAMILY_INPUT),
	callbackManager(CallbackManager::getInstance()),
	eventManager(EventManager::getInstance()) {

}

int InputSystem::process() {

	//we need to sift through the entities
	for(auto entity : this->entityManager->getAllEntities()) {
		//determine if the entity has what we desire
		if(!entity->hasComponentFamily("Input")) {
			continue;
		}

		//grab all of the events
		auto eventList = this->eventManager->getEvents();

		//grab all of the input components
		for (auto inputComponent : entity->getComponentsByFamily("Input")) {
			//check to see if the input is enabled
			int bEnabled = inputComponent->getAttribute_int(ATTRIBUTE_ENABLE);
			if (bEnabled == 0) {
				continue;
			}

			//get the input type
			std::string inputType = inputComponent->getAttribute_string("InputType");

			for (auto event : eventList) {
				bool bIsEvent = false;
				if (inputType == INPUT_MOUSE_MOVE) {
					bIsEvent = this->isEvent(*event, inputType);
				}
				else if (inputType == INPUT_MOUSE_PRESSED) {
					bIsEvent = this->isEvent(*event, inputType);
				}
				else if (inputType == INPUT_MOUSE_RELEASED) {
					bIsEvent = this->isEvent(*event, inputType);
				}
				else if (inputType == INPUT_MOUSE_SCROLL) {
					bIsEvent = this->isEvent(*event, inputType);
				}
				else if (inputType == INPUT_KEYBOARD_PRESSED) {
					bIsEvent = this->isEvent(*event, inputType);
				}
				else if (inputType == INPUT_KEYBOARD_RELEASED) {
					bIsEvent = this->isEvent(*event, inputType);
				}
				else {
					continue;
				}

				if (bIsEvent) {
					//upon finding a matching event to the input, grab the callback, 
					  //and trigger it with the given component
					//get ID
					int entityID = entity->getID();

					//get eventIndex
					auto iter = std::find(eventList.begin(), eventList.end(), event);
					assert(!(iter == eventList.end()) && "Event doesn't exist");
					int eventIndex = iter - eventList.begin();

					//get the callback from the inputComponent
					std::string callbackString = inputComponent->getAttribute_string(ATTRIBUTE_CALLBACK);
					
					//trigger the callback
					assert(callbackManager->hasCallback(callbackString) && "inputComponent callback doesn't exist");
					callbackManager->triggerCallback(callbackString, entityID, eventIndex);
				} //if (bIsEvent) { ...
			}//END for (auto event : ...
		} //END for (auto inputComponent : ...
	} //END for(auto entity : ...
	return 0;
}

bool InputSystem::isEvent(eventType theEvent, std::string inputType) {
	if (inputType == INPUT_MOUSE_MOVE) {
		if (theEvent.type == sf::Event::MouseMoved) {
			return true;
		}
	}
	else if (inputType == INPUT_MOUSE_PRESSED) {
		if (theEvent.type == sf::Event::MouseButtonPressed) {
			return true;
		}
	}
	else if (inputType == INPUT_MOUSE_RELEASED) {
		if (theEvent.type == sf::Event::MouseButtonReleased) {
			return true;
		}
	}
	else if (inputType == INPUT_MOUSE_SCROLL) {
		if (theEvent.type == sf::Event::MouseWheelMoved) {
			return true;
		}
	}
	else if (inputType == INPUT_KEYBOARD_PRESSED) {
		if (theEvent.type == sf::Event::KeyPressed) {
			return true;
		}
	}
	else if (inputType == INPUT_KEYBOARD_RELEASED) {
		if (theEvent.type == sf::Event::KeyReleased) {
			return true;
		}
	}
	return false;
}