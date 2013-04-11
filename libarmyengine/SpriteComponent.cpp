#include "SpriteComponent.h"
#include "AE_Attributes.h"

SpriteComponent::SpriteComponent(std::string name) : 
	AbstractComponent(name, "Sprite") {
	//determines if the given sprite should be shown
		//1 - show sprite
		//0 - don't show sprite
	this->setAttribute_int(ATTRIBUTE_ENABLE, 1);

	//provides a name of a sprite which is stored within the sprite manager
	    //None is a default sprite, which will be a white square with an X in it
	this->setAttribute_string(ATTRIBUTE_SPRITE_NAME, "None");

	//This provides the offset of the sprite from its origin within the X and Y direction
	    //Useful for a multisprite entity, you provide an offset to change its placement
	this->setAttribute_float(ATTRIBUTE_OFFSET_X, 0.0);
	this->setAttribute_float(ATTRIBUTE_OFFSET_Y, 0.0);

	//This provides the origin, or center point where rotation and the point of positioning is determined
	this->setAttribute_float(ATTRIBUTE_ORIGIN_X, 0.0);
	this->setAttribute_float(ATTRIBUTE_ORIGIN_Y, 0.0);

	//Provides the depth of the sprite, lower means farther away, which means it
	    //will be covered by anything with a higher z-buffer {ex A(0.1) covers B(0.0)}
	this->setAttribute_float(ATTRIBUTE_ZBUFFER, 1.0);

	//The scale of the sprite being used
		//relative to the position component
	this->setAttribute_float(ATTRIBUTE_SCALE_X, 1.0);
	this->setAttribute_float(ATTRIBUTE_SCALE_Y, 1.0);

	//Determines the rotation of the sprite
		//relative to a given position component
		//given in radians
	this->setAttribute_float(ATTRIBUTE_ROTATION, 0.0);
}

int SpriteComponent::update() {
	return 0;
}