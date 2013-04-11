#include "ArmyBattle.h"
#include "HelpScreen.h"
#include "AB_Utilities.h"

HelpScreen::HelpScreen(float xPosition, float yPosition) : 
	WorldObject(AB_HELP_SCREEN, xPosition, yPosition),
	helpText(HUDElement(xPosition + AB_HELP_SCREEN_MSG_X, yPosition + AB_HELP_SCREEN_MSG_Y)),
	exitButton(Button(xPosition + AB_HELP_SCREEN_TEXT_OFFSET_X,
	yPosition + AB_HELP_SCREEN_TEXT_OFFSET_Y)) {

		int spacing = 0;
	for (int i = 0; i < AB_HELP_SCREEN_NUM_INSTRUCTIONS; i++) {
		this->helpTextList.push_back(
			std::shared_ptr<HUDElement> (new HUDElement(xPosition, yPosition + spacing + AB_HELP_SCREEN_NUM_INSTRUCTIONS_OFFSET, AB_HELP_SCREEN_HUD_TEXT_SIZE)));
		spacing += AB_HELP_SCREEN_HUD_TEXT_SIZE + 1;
	}
		helpTextList[0]->setSuccessString("To play the game, do the following:");
		helpTextList[1]->setSuccessString("-Move the currently selected drone by moving the");
		helpTextList[2]->setSuccessString("mouse and LEFT clicking where you want to place it");
		helpTextList[3]->setSuccessString("-Use the mouse to change the direction of your");
		helpTextList[4]->setSuccessString("attack");
		helpTextList[5]->setSuccessString("-Change the firing spread by using the UP and DOWN"); 
		helpTextList[6]->setSuccessString("keys");
		helpTextList[7]->setSuccessString("-Click the LEFT mouse to fire or ENTER to skip");
		helpTextList[8]->setSuccessString("-Press ENTER to Scan");
		helpTextList[9]->setSuccessString("-Press ENTER to Broadcast");
		helpTextList[10]->setSuccessString("-Repeat all this for each drone");
		helpTextList[11]->setSuccessString("-The game ends when a player's Home Base loses");
		helpTextList[12]->setSuccessString("all of its health and is destroyed");
		for (auto hud : this->helpTextList) {
		hud->hide();
	}

		auto armyengine = ArmyEngine::getInstance();
		auto componentFactory = armyengine->getComponentFactory();

		auto shapeComponent = componentFactory.createShapeComponent(AB_HELP_SCREEN_SHAPE);
		this->getEntity()->addComponent(shapeComponent);

		//shape attributes
		shapeComponent->setAttribute_int(ATTRIBUTE_ENABLE, 0);
		shapeComponent->setAttribute_string(ATTRIBUTE_SHAPE_TYPE, SHAPETYPE_RECTANGLE);
		shapeComponent->setAttribute_float(ATTRIBUTE_WIDTH, 400.0);
		shapeComponent->setAttribute_float(ATTRIBUTE_HEIGHT, 400.0);
		shapeComponent->setAttribute_int(ATTRIBUTE_FILL_COLOR_RED, 255); 
		shapeComponent->setAttribute_int(ATTRIBUTE_FILL_COLOR_GREEN, 255); 
		shapeComponent->setAttribute_int(ATTRIBUTE_FILL_COLOR_BLUE, 255);
		COLOR_OUTLINE_GREEN(shapeComponent);
		shapeComponent->update();
		
		exitButton.hide();
		exitButton.setButtonText("X");
		auto textPosition = exitButton.buttonHUDElement.getPosition();
		exitButton.buttonHUDElement.setPosition(textPosition[0]+5, textPosition[1]);
		exitButton.buttonHUDElement.setTextSize(20);
		exitButton.setSize(20., 20.);
		
		exitButton.setButtonCallback((functionEventTemplate) [] (int ID, int eventIndex) {
			auto entityManager = EntityManager::getInstance();
			auto entity = entityManager->getEntityById(ID);
			sf::Event theEvent = *EventManager::getInstance()->getEvents()[eventIndex];
			auto mouseButton = theEvent.mouseButton.button;
			if (mouseButton == sf::Mouse::Button::Left) {
				auto world = World::getInstance();
				world->menu.hide();
				world->helpScreen.hide();
			}
			return 0;
		});

		//set the Z-buffer of the text to show
		auto textComponent = exitButton.buttonHUDElement.getEntity()->getComponentByName(AB_HUD_TEXT);
		textComponent->setAttribute_float(ATTRIBUTE_ZBUFFER, 16.0);

		//text parameters
		helpText.setSuccessString(AB_HELP_SCREEN_MSG);
		helpText.hide();

}

void HelpScreen::display() {
	auto shapeComponent = this->getEntity()->getComponentByName(AB_HELP_SCREEN_SHAPE);
	shapeComponent->setAttribute_int(ATTRIBUTE_ENABLE, 1);
	shapeComponent->update();
	this->exitButton.display();
	this->helpText.display();
	auto world = World::getInstance();
	world->viewState = EnumViewState::MENU;
	for (auto hud : this->helpTextList) {
		hud->display();
	}
}

void HelpScreen::hide() {
	auto shapeComponent = this->getEntity()->getComponentByName(AB_HELP_SCREEN_SHAPE);
	shapeComponent->setAttribute_int(ATTRIBUTE_ENABLE, 0);
	shapeComponent->update();
	this->exitButton.hide();
	this->helpText.hide();
	auto world = World::getInstance();
	world->viewState = EnumViewState::WORLD;
	for (auto hud : this->helpTextList) {
		hud->hide();
	}
}