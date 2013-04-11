#ifndef AE__INPUTCOMPONENT_H
#define AE__INPUTCOMPONENT_H
//DESCRIPTION
/*
Input component is a special StateComponent that will 
trigger a callback when a provided input is used

Provided inputs include "Keyboard" and "Mouse"
Depending on which one is chosen, the resulting attributes searched will also vary
*/
//CLASSES
class InputComponent;

//INCLUDES
#include "AbstractComponent.h"
#include "AE_Events.h"
//TYPEDEFS

//DEFINITIONS
#define COMPONENT_FAMILY_INPUT "Input"

//BEGIN
class InputComponent : public AbstractComponent {
private:

public:
	InputComponent(std::string);

	int update();
};

#endif //AE__INPUTCOMPONENT_H