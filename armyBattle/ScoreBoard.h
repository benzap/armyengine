//RESPONSIBILITY: Kyle was responsible for designing, implementing, and testing this class.

#ifndef AB__SCOREBOARD_H
#define AB__SCOREBOARD_H
//DESCRIPTION
/*
The Scoreboard uses HUDElements to display the health of the two team's HomebaseUnit.
*/
//CLASSES
class Scoreboard;

//INCLUDES
#include "HUDElement.h"

//DEFINITION
#define HUD_SPACING 76

#define SCOREBOARD_COLOR_R 255
#define SCOREBOARD_COLOR_G 255
#define SCOREBOARD_COLOR_B 255
#define SCOREBOARD_FONT_SIZE 32


class Scoreboard {
private:
	HUDElement redTeamHUD;
	int redTeamNumDrones;

	HUDElement blueTeamHUD;
	int blueTeamNumDrones;
public:
	Scoreboard(float xPosition, float yPosition);

	void setRedCount(int);
	void setBlueCount(int);
};

#endif //AB__SCOREBOARD_H