//RESPONSIBILITY: Kyle was responsible for designing, implementing, and testing this class.

#ifndef AB__STATUSBAR_H
#define AB__STATUSBAR_H

//DESCRIPTION
/*
The StatusBar uses HUDElements to display messages about the game to the player.
*/
//CLASSES
class StatusBar;

//INCLUDES
#include "HUDElement.h"
#include <string>
using namespace std;

//DEFINITION
#define HUD_SPACING 76

#define STATUSBAR_COLOR_R 0
#define STATUSBAR_COLOR_G 255
#define STATUSBAR_COLOR_B 0
#define STATUSBAR_FONT_SIZE 16

#define STATUSBAR_DEFAULT_MESSAGE "test"

//ENUMS
enum class EnumColor{
	WARNING,
	INFO,
	SUCCESS
};


class StatusBar {
private:
	HUDElement playerNextMove;
	HUDElement mostRecentAction;

public:
	StatusBar(float xPosition, float yPosition);

	void setplayerNextMove(string, EnumColor = EnumColor::SUCCESS);
	void setmostRecentAction(string, EnumColor = EnumColor::SUCCESS);
};

#endif //AB__STATUSBAR_H