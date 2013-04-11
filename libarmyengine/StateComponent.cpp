#include "StateComponent.h"
#include "AE_Attributes.h"

StateComponent::StateComponent(std::string name) :
	AbstractComponent(name, COMPONENT_FAMILY_STATE) {

	//Determines whether the given state is active, and should
		//trigger the given callback
	this->setAttribute_int(ATTRIBUTE_ENABLE, 1);

	//Key of the callback function to trigger
	this->setAttribute_string(ATTRIBUTE_CALLBACK, "None");

	//determines if the given state callback will be repeated
	this->setAttribute_int("bRepeat", 1);
}

int StateComponent::update() {
	return 0;
}