#include "InputComponent.h"
#include "AE_Events.h"
#include "AE_Attributes.h"

InputComponent::InputComponent(std::string name) :
	AbstractComponent(name, COMPONENT_FAMILY_INPUT) {

	//input component is processed only when it's enabled
	this->setAttribute_int(ATTRIBUTE_ENABLE, 1);

	//callback function key for the callback to be called from
	// CallbackManager
	this->setAttribute_string(ATTRIBUTE_CALLBACK, "None");

	//determine the input type ["Move", "Scroll", "ButtonPressed", "ButtonReleased"]
	//by default it will get button presses
	this->setAttribute_string(ATTRIBUTE_INPUT_TYPE, INPUT_KEYBOARD_PRESSED);

	//For events, we need to provide a means in which to retrieve the given event
	//so we provide an index to resemble the position within the EventManager eventList

	//Don't define it for safety reasons
	//this->setAttribute_int("EventIndex", 0);
}

int InputComponent::update() {
	return 0;
}