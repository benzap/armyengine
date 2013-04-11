#include "PositionComponent.h"
#include "AE_Attributes.h"

PositionComponent::PositionComponent(std::string name)
	: AbstractComponent(name, "Position") {

	//Determines the position of the entity as a whole
		//Currently used by the sprite system to determine the position
	this->setAttribute_float(ATTRIBUTE_POSITION_X, 0.0);
	this->setAttribute_float(ATTRIBUTE_POSITION_Y, 0.0);

	//Determines the offset of the position. This is particularly useful
	    //for providing a view offset
	this->setAttribute_float(ATTRIBUTE_OFFSET_X, 0.0);
	this->setAttribute_float(ATTRIBUTE_OFFSET_Y, 0.0);

	//Determines the overall objects rotation
		//Given in radians
	this->setAttribute_float(ATTRIBUTE_ROTATION, 0.0);
}

int PositionComponent::update() {
	return 0;
}