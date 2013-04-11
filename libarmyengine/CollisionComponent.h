#ifndef AE__COLLISIONCOMPONENT_H
#define AE__COLLISIONCOMPONENT_H
//DESCRIPTION
/*
Collision component is a figmentary bound which reacts to overlapping
other collision bounds.
*/
//CLASSES
class CollisionComponent;

//INCLUDES
#include <string>

#include "AbstractComponent.h"

//BEGIN
class CollisionComponent : public AbstractComponent {
private:

public:
	CollisionComponent(std::string);
	int update();
};

#endif //AE__COLLISIONCOMPONENT_H