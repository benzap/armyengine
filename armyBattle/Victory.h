//RESPONSIBILITY: Ben was responsible for designing, implementing, and testing this class.

#ifndef AB__VICTORY_H
#define AB__VICTORY_H
//DECSCRIPTION
/*
Used for displaying a victory message after the game has ended. It includes a button to restart the game.
*/
//CLASSES
class Victory;

//INCLUDE
#include "WorldObject.h"
#include "Button.h"
#include "HUDElement.h"

//DEFINITION
#define AB_VICTORY "Victory"
#define AB_VICTORY_SHAPE "Victory_Shape"

#define AB_VICTORY_TEXT_OFFSET_X 100
#define AB_VICTORY_TEXT_OFFSET_Y 250

#define AB_VICTORY_MSG1 "Victory!"

#define AB_VICTORY_MSG1_X 100
#define AB_VICTORY_MSG1_Y 50

#define AB_VICTORY_MSG2_X 100
#define AB_VICTORY_MSG2_Y 150

//BEGIN
class Victory : public WorldObject {
private:
	HUDElement victoryText;
	HUDElement teamText;
	Button restartButton;
public:
	Victory(float xPosition, float yPosition);
	void display(EnumTeam teamID);
	void hide();
};



#endif //AB__VICTORY_H