#ifndef STATESYSTEM_H
#define STATESYSTEM_H
//DESCRIPTION
/*
State system is used to control the state of each entity based on the
given state callback of the state component.

The state system has a unique method, which is called at the beginning of each system
The function which can be plugged in, is called a "state machine" and is the heart of the game
which is to be played, as it is used to change the global state, and as a result, affect the state 
of the many entities with state components that make up the game.
*/
//CLASSES
class StateSystem;

//INCLUDES
#include <map>
#include <functional>

#include "CallbackManager.h"
#include "StateManager.h"
#include "AbstractSystem.h"
#include "Components.h"
#include "Entities.h"

//TYPEDEFS
typedef std::function<int(void)> functionStateMachineTemplate;
typedef bool stateType;
typedef std::map<std::string, stateType> stateListType;

//! Used to to process the state components and perform callbacks.
class StateSystem : public AbstractSystem {
private:
	functionStateMachineTemplate stateMachineFunction;
	CallbackManager* callbackManager;
	StateManager* stateManager;

public:
	StateSystem();
	void setStateMachineFunction(functionStateMachineTemplate);
	int triggerStateMachine();

	int process();
};

#endif //STATESYSTEM_H
