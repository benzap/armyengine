#ifndef AE__STATECOMPONENT_H
#define AE__STATECOMPONENT_H
//DESCRIPTION
/*
The State component is used to resemble a given state within the given entity
An entity will contain several states, but it should only be in one state at a given time
(this is situational)

When the entity changes into the given state, the component should be notified that
it has been changed to that given state.
*/
//CLASSES
class StateComponent;

//INCLUDES
#include <string>

#include "AbstractComponent.h"

//TYPEDEFS

//DEFINITIONS
#define COMPONENT_FAMILY_STATE "State"

//BEGIN
class StateComponent : public AbstractComponent {
public:
	StateComponent(std::string);
	int update();
};

#endif //AE__STATECOMPONENT_H