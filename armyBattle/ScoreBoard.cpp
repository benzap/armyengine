#include "World.h"
#include "ScoreBoard.h"


Scoreboard::Scoreboard(float xPosition, float yPosition) :
	redTeamHUD(HUDElement(xPosition, yPosition, SCOREBOARD_FONT_SIZE)),
	redTeamNumDrones(HOMEBASE_STARTING_HEALTH),
	blueTeamHUD(HUDElement(xPosition + HUD_SPACING, yPosition, SCOREBOARD_FONT_SIZE)),
	blueTeamNumDrones(HOMEBASE_STARTING_HEALTH) {
		//set our HUD's to show the number of drones
		this->setRedCount(redTeamNumDrones);
		this->setBlueCount(blueTeamNumDrones);
}

void Scoreboard::setRedCount(int value) {
	redTeamHUD.setString(std::to_string(value) + " : ", 
		SCOREBOARD_COLOR_R,
		SCOREBOARD_COLOR_G,
		SCOREBOARD_COLOR_B);
}

void Scoreboard::setBlueCount(int value) {
	blueTeamHUD.setString(std::to_string(value), 
		SCOREBOARD_COLOR_R,
		SCOREBOARD_COLOR_G,
		SCOREBOARD_COLOR_B);
}