#include "StatusLog.h"

StatusLog::StatusLog(float xPosition, float yPosition) {
	//populate our HUDElement list
	
	int spacing = 0;
	for (int i = 0; i < AB_STATUSLOG_NUM_HUDS; i++) {
		this->hudList.push_back(
			std::shared_ptr<HUDElement> (new HUDElement(xPosition, yPosition + spacing, AB_STATUSLOG_HUD_TEXT_SIZE)));
		spacing += AB_STATUSLOG_HUD_TEXT_SIZE + 1;
	}

	//set each of our hud elements to be empty strings
	for (auto hud : this->hudList) {
		hud->setSuccessString("");
		hud->display();
	}
}

void StatusLog::propagate() {
	//propagate the strings down into the lower HUD elements
	for (int i = hudList.size()-1; i > 0; i--) {
		//get the colors from the previous one
		auto comp = hudList[i-1]->getEntity()->getComponentByName(AB_HUD_TEXT);
		std::string  theString = hudList[i-1]->getString();
		int rColor = comp->getAttribute_int(ATTRIBUTE_FILL_COLOR_RED);
		int gColor = comp->getAttribute_int(ATTRIBUTE_FILL_COLOR_GREEN);
		int bColor = comp->getAttribute_int(ATTRIBUTE_FILL_COLOR_BLUE);

		//apply to the current one
		hudList[i]->setString(theString, rColor, gColor, bColor);
	}

	//clear our very first hud element in the list
	hudList[0]->setString("", 0, 0, 0);
}

void StatusLog::setWarningString(const std::string& theString) {
	this->propagate();
	hudList[0]->setWarningString(theString);
}

void StatusLog::setSuccessString(const std::string& theString) {
	this->propagate();
	hudList[0]->setSuccessString(theString);
}

void StatusLog::setInfoString(const std::string& theString) {
	this->propagate();
	hudList[0]->setInfoString(theString);
}

void StatusLog::setString(const std::string& theString, int rColor, int gColor, int bColor) {
	this->propagate();
	hudList[0]->setString(theString, rColor, gColor, bColor);
}

void StatusLog::clear() {
	for (auto hud : hudList) {
		hud->setSuccessString("");
	}
}