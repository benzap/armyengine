#ifndef AE__TEXTCOMPONENT_H
#define AE__TEXTCOMPONENT_H
//DESCRIPTION
/*
Text component shows text...
*/
//CLASSES
class TextComponent;

//INCLUDES
#include <string>

#include "AbstractComponent.h"

//BEGIN
class TextComponent : public AbstractComponent {
private:

public:
	TextComponent(std::string);
	int update();
};

#endif //AE__TEXTCOMPONENT_H