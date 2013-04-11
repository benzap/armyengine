#include <cassert>

#include "StateSystem.h"
#include "Managers.h"
#include "Entities.h"
#include "Components.h"
#include "AE_Attributes.h"

StateSystem::StateSystem() : 
	AbstractSystem(COMPONENT_FAMILY_STATE),
	callbackManager(CallbackManager::getInstance()),
	stateManager(StateManager::getInstance()) {
	//set the function to an assertion
	this->stateMachineFunction = [] { return 0; };
}

void StateSystem::setStateMachineFunction(functionStateMachineTemplate func) {
	this->stateMachineFunction = func;
}

int StateSystem::triggerStateMachine() {
	return this->stateMachineFunction();
}

int StateSystem::process() {
	//run the state machine function
	if (this->stateMachineFunction()) {
		assert(0 && "State machine returned a non-zero value");
	}

	//grab the state components from the entities
	for (auto entity : this->entityManager->getAllEntities()) {
		//get only the state components
		for (auto stateComponent : entity->getComponentsByFamily(COMPONENT_FAMILY_STATE)) {
			//weed out the components that aren't enabled
			if (!stateComponent->getAttribute_int(ATTRIBUTE_ENABLE)) {
				continue;
			}

			//perform the state component callback
			auto callbackString = stateComponent->getAttribute_string(ATTRIBUTE_CALLBACK);
			callbackManager->triggerCallback(callbackString, entity->getID());

			//check to see if it's on repeat, otherwise disable the state component
			// from executing again
			if (!stateComponent->getAttribute_int("bRepeat")) {
				stateComponent->setAttribute_int(ATTRIBUTE_ENABLE, 0);
			}

		} //END for (auto stateComponent : ...
	} //END for (auto entity : ...
	return 0;
}