//RESPONSIBILITY: Kyle was responsible for designing, implementing, and testing this class.

#ifndef AB__HELPSCREEN_H
#define AB__HELPSCREEN_H
//DECSCRIPTION
/*
Used for displaying a help screen to tell the users what to do. 
*/

//CLASSES
class HelpScreen;

//INCLUDE
#include "WorldObject.h"
#include "HUDElement.h"
#include "Button.h"

//DEFINITION
#define AB_HELP_SCREEN "Help_Screen"
#define AB_HELP_SCREEN_SHAPE "Help_Screen_Shape"

#define AB_HELP_SCREEN_TEXT_OFFSET_X 360
#define AB_HELP_SCREEN_TEXT_OFFSET_Y 10 + BUTTON_DEFAULT_OUTLINE
#define AB_HELP_SCREEN_NUM_INSTRUCTIONS_OFFSET 50

#define AB_HELP_SCREEN_MSG "Instructions"

#define AB_HELP_SCREEN_MSG_X 100
#define AB_HELP_SCREEN_MSG_Y 10
#define AB_HELP_SCREEN_NUM_INSTRUCTIONS 13
#define AB_HELP_SCREEN_HUD_TEXT_SIZE 16

//BEGIN
class HelpScreen : public WorldObject {
private:
	std::vector<std::shared_ptr<HUDElement>> helpTextList;
	HUDElement helpText;
	Button exitButton;
public:
	HelpScreen(float xPosition, float yPosition);
	void display();
	void hide();
};



#endif //AB__HELPSCREEN_H