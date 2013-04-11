//RESPONSIBILITY: Kyle was responsible for designing, implementing, and testing this class.
//Ben helped with some issues that Kyle had.
#ifndef AB__BUTTON_H
#define AB__BUTTON_H

//DESCRIPTION
/*
This class sets up buttons. Buttons can be clicked on, and set up to perform different tasks based on the use of the button.
*/
//CLASSES
class Button;

//INCLUDES
#include "HUDElement.h"
#include <string>
#include <iostream>
#include "WorldObject.h"
using namespace std;

//DEFINITION
#define AB_BUTTON "Button"
#define AB_BUTTON_SHAPE "ButtonShape"
#define AB_BUTTON_HUD "Button_HUD"
#define AB_BUTTON_COLLISION "Button_Collision"
#define AB_BUTTON_PRESSED "Button_Pressed"

#define BUTTON_DEFAULT_WIDTH 60.0f
#define BUTTON_DEFAULT_HEIGHT 30.0f
#define BUTTON_DEFAULT_OUTLINE 3.0f

#define HUD_SPACING 76

#define BUTTON_COLOR_R 0
#define BUTTON_COLOR_G 255
#define BUTTON_COLOR_B 0
#define BUTTON_FONT_SIZE 16


class Button : public WorldObject {
private:
	string buttonText;

public:
	HUDElement buttonHUDElement;

	Button(float xPosition, float yPosition);

	void setButtonText(string);
	void setButtonCallback(functionEventTemplate);

	void hide();
	void display();

	void setSize(float, float);

};

#endif //AB__BUTTON_H