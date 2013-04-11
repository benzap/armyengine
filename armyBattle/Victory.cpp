#include "ArmyBattle.h"
#include "Victory.h"
#include "AB_Utilities.h"

Victory::Victory(float xPosition, float yPosition) : 
	WorldObject(AB_VICTORY, xPosition, yPosition),
	restartButton(Button(xPosition + AB_VICTORY_TEXT_OFFSET_X,
	yPosition + AB_VICTORY_TEXT_OFFSET_Y)),
	victoryText(HUDElement(xPosition + AB_VICTORY_MSG1_X, yPosition + AB_VICTORY_MSG1_Y)),
	teamText(HUDElement(xPosition + AB_VICTORY_MSG2_X, yPosition + AB_VICTORY_MSG2_Y)) {
		auto armyengine = ArmyEngine::getInstance();
		auto componentFactory = armyengine->getComponentFactory();
		//setup the shape component to represent the border of the 
		// victory screen
		auto shapeComponent = componentFactory.createShapeComponent(AB_VICTORY_SHAPE);
		this->getEntity()->addComponent(shapeComponent);

		//shape attributes
		shapeComponent->setAttribute_int(ATTRIBUTE_ENABLE, 0);
		shapeComponent->setAttribute_string(ATTRIBUTE_SHAPE_TYPE, SHAPETYPE_RECTANGLE);
		shapeComponent->setAttribute_float(ATTRIBUTE_WIDTH, 400.0);
		shapeComponent->setAttribute_float(ATTRIBUTE_HEIGHT, 400.0);
		COLOR_FILL_BLACK(shapeComponent);
		COLOR_OUTLINE_GREEN(shapeComponent);
		shapeComponent->update();

		//button parameters
		restartButton.hide();
		restartButton.setButtonText("Restart");
		restartButton.setSize(200, 100);
		restartButton.setButtonCallback((functionEventTemplate) [] (int ID, int eventIndex) {
			auto entityManager = EntityManager::getInstance();
			auto entity = entityManager->getEntityById(ID);
			sf::Event theEvent = *EventManager::getInstance()->getEvents()[eventIndex];
			auto mouseButton = theEvent.mouseButton.button;
			if (mouseButton == sf::Mouse::Button::Left) {
				auto world = World::getInstance();
				world->menu.hide();
				world->victory.hide();
				world->generateWorld();
				EntityManager::getInstance()->sortEntityList();

#ifdef LOGGING
				std::cout << "Restart Button Pressed" << std::endl;
#endif //LOGGING
			}
			return 0;
		});

		//set the Z-buffer of the text to show
		auto textComponent = restartButton.buttonHUDElement.getEntity()->getComponentByName(AB_HUD_TEXT);
		textComponent->setAttribute_float(ATTRIBUTE_ZBUFFER, 16.0);

		//change the text size for the restart button
		restartButton.buttonHUDElement.setTextSize(50);

		//text parameters
		victoryText.setSuccessString(AB_VICTORY_MSG1);
		victoryText.hide();
		teamText.setSuccessString("");
		teamText.hide();

}

void Victory::display(EnumTeam teamID) {
	auto shapeComponent = this->getEntity()->getComponentByName(AB_VICTORY_SHAPE);
	shapeComponent->setAttribute_int(ATTRIBUTE_ENABLE, 1);
	shapeComponent->update();

	//change the teamText element to reflect who won
	if (teamID == EnumTeam::RED) {
		this->teamText.setWarningString("Team RED Wins!");
	}
	else {
		this->teamText.setInfoString("Team BLUE Wins!");
	}

	this->restartButton.display();
	this->victoryText.display();
	this->teamText.display();
}

void Victory::hide() {
	auto shapeComponent = this->getEntity()->getComponentByName(AB_VICTORY_SHAPE);
	shapeComponent->setAttribute_int(ATTRIBUTE_ENABLE, 0);
	shapeComponent->update();

	this->restartButton.hide();
	this->victoryText.hide();
	this->teamText.hide();
}