#ifndef AE__POSITIONCOMPONENT_H
#define AE__POSITIONCOMPOENNT_H
//DESCRIPTION
/*
Used to describe the position of the
Entity. Used as a base for the sprite system to determine the
Positioning of the sprite
*/
//CLASS
class PositionComponent;

//INCLUDE
#include <string>

#include "AbstractComponent.h"

//BEGIN
class PositionComponent : public AbstractComponent {
private:

public:
	PositionComponent(std::string);

	int update();
};

#endif //AE__POSITIONCOMPONENT_H