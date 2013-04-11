#include <memory>

#include "SFML\Graphics.hpp"

#include "TextComponent.h"
#include "TextManager.h"
#include "AE_Attributes.h"

TextComponent::TextComponent(std::string name) : 
	AbstractComponent(name, "Text") {

	std::string keyname = name + std::to_string(reinterpret_cast<int>(this));
	//unique keyname for our referenced text object

	//need to create our text object and place it within the text manager
	auto textManager = TextManager::getInstance();
	textManager->addText(keyname, std::shared_ptr<sf::Text> (new sf::Text()));


	//***********************************
	//********** ATTRIBUTES *************
	//***********************************
	
	//the keyname is stored as an attribute for later retrieval
	setAttribute_string(ATTRIBUTE_KEYNAME, keyname);

	//Determines whether the given shape should be shown
		//0 - disable
		//1 - enable
	setAttribute_int(ATTRIBUTE_ENABLE, 1);

	//Text string to show on the screen
	setAttribute_string(ATTRIBUTE_TEXT_STRING, DEFAULT_TEXT_STRING);

	//Text string font
	setAttribute_int(ATTRIBUTE_TEXT_SIZE, 30);
	setAttribute_int(ATTRIBUTE_TEXT_STYLE_UNDERLINE, 0);
	setAttribute_int(ATTRIBUTE_TEXT_STYLE_BOLD, 0);
	setAttribute_int(ATTRIBUTE_TEXT_STYLE_ITALIC, 0);
	setAttribute_string(ATTRIBUTE_TEXT_FONT, DEFAULT_FONT);

	//The text fill color
	setAttribute_int(ATTRIBUTE_FILL_COLOR_RED, 255);
	setAttribute_int(ATTRIBUTE_FILL_COLOR_GREEN, 255);
	setAttribute_int(ATTRIBUTE_FILL_COLOR_BLUE, 255);
	setAttribute_int(ATTRIBUTE_FILL_COLOR_ALPHA, 255);

	//Related Sprite attributes
	//This provides the offset of the collision bound from its origin within the X and Y direction
	this->setAttribute_float(ATTRIBUTE_OFFSET_X, 0.0);
	this->setAttribute_float(ATTRIBUTE_OFFSET_Y, 0.0);

	//This provides the origin, or center point where rotation and the point of positioning is determined
	this->setAttribute_float(ATTRIBUTE_ORIGIN_X, 0.0);
	this->setAttribute_float(ATTRIBUTE_ORIGIN_Y, 0.0);

	//Provides the depth of the sprite, lower means farther away, which means it
	    //will be covered by anything with a higher z-buffer {ex A(0.1) covers B(0.0)}
	this->setAttribute_float(ATTRIBUTE_ZBUFFER, 1.0);

	//The scale of the sprite being used
		//relative to the position component
	this->setAttribute_float(ATTRIBUTE_SCALE_X, 1.0);
	this->setAttribute_float(ATTRIBUTE_SCALE_Y, 1.0);

	//Determines the rotation of the sprite
		//relative to a given position component
		//given in radians
	this->setAttribute_float(ATTRIBUTE_ROTATION, 0.0);

	//After all of the attributes are added, we perform an update to push
	//  all of our defaults onto the text instance
	this->update();
}

int TextComponent::update() {
	auto textManager = TextManager::getInstance();
	auto theText = textManager->getText(getAttribute_string(ATTRIBUTE_KEYNAME));

	//set the string to display
	theText->setString(getAttribute_string(ATTRIBUTE_TEXT_STRING));

	//set the character size
	theText->setCharacterSize(getAttribute_int(ATTRIBUTE_TEXT_SIZE));

	//set the text style
	int textAttributes = (getAttribute_int(ATTRIBUTE_TEXT_STYLE_BOLD)) ?
		sf::Text::Bold : 0;
	textAttributes |= (getAttribute_int(ATTRIBUTE_TEXT_STYLE_ITALIC)) ?
		sf::Text::Italic : 0;
	textAttributes |= (getAttribute_int(ATTRIBUTE_TEXT_STYLE_UNDERLINE)) ?
		sf::Text::Underlined : 0;
	theText->setStyle(textAttributes);

	//check and set our font
	if (textManager->hasFont(getAttribute_string(ATTRIBUTE_TEXT_FONT))) {
		theText->setFont(*(textManager->getFont(getAttribute_string(ATTRIBUTE_TEXT_FONT))));
	}

	//set our text color
	theText->setColor(
		sf::Color(
			getAttribute_int(ATTRIBUTE_FILL_COLOR_RED),
			getAttribute_int(ATTRIBUTE_FILL_COLOR_GREEN),
			getAttribute_int(ATTRIBUTE_FILL_COLOR_BLUE),
			getAttribute_int(ATTRIBUTE_FILL_COLOR_ALPHA))
	);

	return 0;
}