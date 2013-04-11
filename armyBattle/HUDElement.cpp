#include "HUDElement.h"
#include "AB_Utilities.h"

HUDElement::HUDElement(float xPosition, float yPosition, int fontSize) :
	WorldObject(AB_HUD, xPosition, yPosition),
	prefix("") {
		auto componentFactory = ArmyEngine::getInstance()->getComponentFactory();

		//add text component to represent the text
		auto textComponent = componentFactory.createTextComponent(AB_HUD_TEXT);
		this->getEntity()->addComponent(textComponent);

		//Text Attributes
		textComponent->setAttribute_string(ATTRIBUTE_TEXT_STRING, prefix);
		textComponent->setAttribute_int(ATTRIBUTE_TEXT_SIZE, fontSize);

		COLOR_FILL_ORANGE(textComponent); //macro

		textComponent->setAttribute_int(ATTRIBUTE_FILL_COLOR_ALPHA, 255);
		textComponent->setAttribute_float(ATTRIBUTE_OFFSET_X, 0);
		textComponent->setAttribute_float(ATTRIBUTE_OFFSET_Y, -5);
		textComponent->setAttribute_float(ATTRIBUTE_ZBUFFER, 11.0);
		textComponent->update();
}

void HUDElement::setWarningString(const std::string& theString) {
	auto textComponent = this->getEntity()->getComponentByName(AB_HUD_TEXT);
	textComponent->setAttribute_string(ATTRIBUTE_TEXT_STRING, this->prefix + theString);

	//change the color of the string to resemble a warning
	COLOR_FILL_RED(textComponent);
	textComponent->update();
}

void HUDElement::setSuccessString(const std::string& theString) {
	auto textComponent = this->getEntity()->getComponentByName(AB_HUD_TEXT);
	textComponent->setAttribute_string(ATTRIBUTE_TEXT_STRING, this->prefix + theString);

	//change the color of the string to resemble a success
	COLOR_FILL_GREEN(textComponent);
	textComponent->update();
}

void HUDElement::setInfoString(const std::string& theString) {
	auto textComponent = this->getEntity()->getComponentByName(AB_HUD_TEXT);
	textComponent->setAttribute_string(ATTRIBUTE_TEXT_STRING, this->prefix + theString);

	//change the color of the string to resemble a info string
	COLOR_FILL_BLUE(textComponent);
	textComponent->update();
}

void HUDElement::setString(const std::string& theString, int rColor, int gColor, int bColor) {
	auto textComponent = this->getEntity()->getComponentByName(AB_HUD_TEXT);
	textComponent->setAttribute_string(ATTRIBUTE_TEXT_STRING, this->prefix + theString);

	textComponent->setAttribute_int(ATTRIBUTE_FILL_COLOR_RED, rColor);
	textComponent->setAttribute_int(ATTRIBUTE_FILL_COLOR_GREEN, gColor);
	textComponent->setAttribute_int(ATTRIBUTE_FILL_COLOR_BLUE, bColor);
	textComponent->update();
}

std::string HUDElement::getString() {
	auto textComponent = this->getEntity()->getComponentByName(AB_HUD_TEXT);
	return textComponent->getAttribute_string(ATTRIBUTE_TEXT_STRING);
}

void HUDElement::setPrefix(const std::string& theString) {
	this->prefix = theString;
	auto textComponent = this->getEntity()->getComponentByName(AB_HUD_TEXT);
	textComponent->setAttribute_string(ATTRIBUTE_TEXT_STRING, this->prefix + theString);
	textComponent->update();
}

void HUDElement::setTextSize(int fontSize) {
	auto textComponent = this->getEntity()->getComponentByName(AB_HUD_TEXT);
	textComponent->setAttribute_int(ATTRIBUTE_TEXT_SIZE, fontSize);
	textComponent->update();
}

void HUDElement::enableBold() {
	auto textComponent = this->getEntity()->getComponentByName(AB_HUD_TEXT);
	textComponent->setAttribute_int(ATTRIBUTE_TEXT_STYLE_BOLD, 1);
	textComponent->update();
}

void HUDElement::disableBold() {
	auto textComponent = this->getEntity()->getComponentByName(AB_HUD_TEXT);
	textComponent->setAttribute_int(ATTRIBUTE_TEXT_STYLE_BOLD, 0);
	textComponent->update();
}

void HUDElement::enableItalic() {
	auto textComponent = this->getEntity()->getComponentByName(AB_HUD_TEXT);
	textComponent->setAttribute_int(ATTRIBUTE_TEXT_STYLE_ITALIC, 1);
	textComponent->update();
}

void HUDElement::disableItalic() {
	auto textComponent = this->getEntity()->getComponentByName(AB_HUD_TEXT);
	textComponent->setAttribute_int(ATTRIBUTE_TEXT_STYLE_ITALIC, 0);
	textComponent->update();
}

void HUDElement::enableUnderline() {
	auto textComponent = this->getEntity()->getComponentByName(AB_HUD_TEXT);
	textComponent->setAttribute_int(ATTRIBUTE_TEXT_STYLE_UNDERLINE, 1);
	textComponent->update();
}

void HUDElement::disableUnderline() {
	auto textComponent = this->getEntity()->getComponentByName(AB_HUD_TEXT);
	textComponent->setAttribute_int(ATTRIBUTE_TEXT_STYLE_UNDERLINE, 0);
	textComponent->update();
}

void HUDElement::hide() {
	auto textComponent = this->getEntity()->getComponentByName(AB_HUD_TEXT);
	textComponent->setAttribute_int(ATTRIBUTE_ENABLE, 0);
	textComponent->update();
}

void HUDElement::display() {
	auto textComponent = this->getEntity()->getComponentByName(AB_HUD_TEXT);
	textComponent->setAttribute_int(ATTRIBUTE_ENABLE, 1);
	textComponent->update();
}