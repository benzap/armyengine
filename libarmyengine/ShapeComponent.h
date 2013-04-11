#ifndef AE__SHAPECOMPONENT_H
#define AE__SHAPECOMPONENT_H
//DESCRIPTION
/*
Shape Component is a lot like sprite component, but has several predefined shapes
which don't require a sprite in order to express them visually on the screen
*/
//CLASSES
class ShapeComponent;

//INCLUDE
#include <string>

#include "AbstractComponent.h"

//BEGIN
class ShapeComponent : public AbstractComponent {
private:

public:
	ShapeComponent(std::string);

	int update();
};


#endif //AE__SHAPECOMPONENT_H