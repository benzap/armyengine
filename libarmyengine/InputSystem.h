#ifndef AE__INPUTSYSTEM_H
#define AE__INPUTSYSTEM_H
//DESCRIPTION
/*
Procedure
- Input System grabs the current events from the EventManager
- Input system finds entities with InputComponents
- Input system determines if the Events should be sent to the given InputComponents Callback
- Upon determining if a given InputComponent needs an Event, 
  + triggers that given InputComponent's Callback with the entity ID and event index
*/

//CLASSES
class InputSystem;

//INCLUDES
#include <memory>
#include "SFML\Window.hpp"
#include "AbstractSystem.h"
#include "EventManager.h"
#include "CallbackManager.h"

//DEFINITIONS

//TYPEDEFS

//BEGIN
class InputSystem : public AbstractSystem {
private:
	CallbackManager* callbackManager;
	EventManager* eventManager;

	//compares the event to the given input attributes
	//TODO: type clarifiers for component attributes
	bool isEvent(eventType theEvent, std::string inputType);
public:
	InputSystem();

	int process();
};



#endif //AE__INPUTSYSTEM_H