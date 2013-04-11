#ifndef AE__SPRITECOMPONENT_H
#define AE__SPRITECOMPONENT_H
//DESCRIPTION
/*
Sprite component is included in an entity to have it display itself
given a set of attributes that describe the sprite to use, and the position
*/
//CLASS
class SpriteComponent;

//INCLUDE
#include <string>

#include "AbstractComponent.h"

//BEGIN
class SpriteComponent : public AbstractComponent {

public:
	SpriteComponent(std::string);

	//Within the sprite component, the update command is used to set
	//the correct width and height of the rectangular sprite
	int update();
};

#endif //AE__SPRITECOMPONENT_H