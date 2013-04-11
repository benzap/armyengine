#ifndef AE__HEALTHCOMPONENT_H
#define AE__HEALTHCOMPONENT_H
//DESCRIPTION
/*
Used to describe the health component of an entity
which could be used for determining state
*/
//CLASSES
class HealthComponent;

//INCLUDES
#include <string>

#include "AbstractComponent.h"

//BEGIN
class HealthComponent : public AbstractComponent {
private:

public:
	HealthComponent(std::string);
	int update();
};

#endif //AE__HEALTHCOMPONENT_H