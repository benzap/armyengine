#include "World.h"
#include "StatusBar.h"


StatusBar::StatusBar(float xPosition, float yPosition) :
	playerNextMove(HUDElement(xPosition, yPosition, STATUSBAR_FONT_SIZE)),
	mostRecentAction(HUDElement(xPosition, yPosition + STATUSBAR_FONT_SIZE, STATUSBAR_FONT_SIZE)) {
		this->setplayerNextMove(STATUSBAR_DEFAULT_MESSAGE);
		this->setmostRecentAction(STATUSBAR_DEFAULT_MESSAGE);

}

void StatusBar::setplayerNextMove(string value, EnumColor color) {
	if (color == EnumColor::SUCCESS) {
		playerNextMove.setSuccessString(value);
	}
	else if (color == EnumColor::INFO) {
		playerNextMove.setInfoString(value);
	}
	else if (color == EnumColor::WARNING) {
		playerNextMove.setWarningString(value);
	}
}

void StatusBar::setmostRecentAction(string value, EnumColor color) {
	if (color == EnumColor::SUCCESS) {
		mostRecentAction.setSuccessString(value);
	}
	else if (color == EnumColor::INFO) {
		mostRecentAction.setInfoString(value);
	}
	else if (color == EnumColor::WARNING) {
		mostRecentAction.setWarningString(value);
	}
}