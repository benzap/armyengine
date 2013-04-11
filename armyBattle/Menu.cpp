#include <iostream>

#include "ArmyBattle.h"
#include "Menu.h"

Menu::Menu() :
	WorldObject(AB_MENU, 0.0f, 0.0f) {
		//add Resume button
		// add the corresponding callback when clicked
		auto resumeButton = std::shared_ptr<Button>(new Button(AB_MENU_BUTTON_OFFSET_X, AB_MENU_BUTTON_OFFSET_Y));
		resumeButton->setSize(AB_MENU_BUTTON_WIDTH, AB_MENU_BUTTON_HEIGHT);
		resumeButton->setButtonText("Resume");
		//perform a few changes to our text element to have it sit better within the button
		auto pos = resumeButton->buttonHUDElement.getPosition();
		resumeButton->buttonHUDElement.setPosition(
			pos[0] + AB_MENU_BUTTON_TEXT_OFFSET_X,
			pos[1] + AB_MENU_BUTTON_TEXT_OFFSET_Y);
		resumeButton->buttonHUDElement.setTextSize(AB_MENU_BUTTON_TEXT_SIZE);
		resumeButton->hide();

		//resume button callback
		resumeButton->setButtonCallback((functionEventTemplate) [] (int ID, int eventIndex) {
			auto entityManager = EntityManager::getInstance();
			auto entity = entityManager->getEntityById(ID);
			sf::Event theEvent = *EventManager::getInstance()->getEvents()[eventIndex];
			auto mouseButton = theEvent.mouseButton.button;
			if (mouseButton == sf::Mouse::Button::Left) {
				auto world = World::getInstance();
				world->viewState = EnumViewState::WORLD;
				world->menu.hide();
			}
			return 0;
		});

		//change the Z-buffer
		auto textComponent = resumeButton->buttonHUDElement.getEntity()->getComponentByName(AB_HUD_TEXT);
		textComponent->setAttribute_float(ATTRIBUTE_ZBUFFER, 16.0);

		buttonList.push_back(resumeButton);

		auto restartButton = std::shared_ptr<Button>(new Button(AB_MENU_BUTTON_OFFSET_X, AB_MENU_BUTTON_OFFSET_Y + AB_MENU_BUTTON_SPACING));
		restartButton->setSize(AB_MENU_BUTTON_WIDTH, AB_MENU_BUTTON_HEIGHT);
		restartButton->setButtonText("Restart");
		pos = restartButton->buttonHUDElement.getPosition();
		restartButton->buttonHUDElement.setPosition(
			pos[0] + AB_MENU_BUTTON_TEXT_OFFSET_X,
			pos[1] + AB_MENU_BUTTON_TEXT_OFFSET_Y);
		restartButton->buttonHUDElement.setTextSize(AB_MENU_BUTTON_TEXT_SIZE);
		restartButton->hide();

		//restart button callback

		restartButton->setButtonCallback((functionEventTemplate) [] (int ID, int eventIndex) {
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

		//change the Z-buffer
		textComponent = restartButton->buttonHUDElement.getEntity()->getComponentByName(AB_HUD_TEXT);
		textComponent->setAttribute_float(ATTRIBUTE_ZBUFFER, 16.0);

		buttonList.push_back(restartButton);	

		//Quit Button
		auto quitButton = std::shared_ptr<Button>(new Button(AB_MENU_BUTTON_OFFSET_X, AB_MENU_BUTTON_OFFSET_Y + AB_MENU_BUTTON_SPACING*2));
		quitButton->setSize(AB_MENU_BUTTON_WIDTH, AB_MENU_BUTTON_HEIGHT);
		quitButton->setButtonText("Quit");
		pos = quitButton->buttonHUDElement.getPosition();
		quitButton->buttonHUDElement.setPosition(
			pos[0] + AB_MENU_BUTTON_TEXT_OFFSET_X,
			pos[1] + AB_MENU_BUTTON_TEXT_OFFSET_Y);
		quitButton->buttonHUDElement.setTextSize(AB_MENU_BUTTON_TEXT_SIZE);
		quitButton->hide();

		quitButton->setButtonCallback((functionEventTemplate) [] (int ID, int eventIndex) {
			auto entityManager = EntityManager::getInstance();
			auto entity = entityManager->getEntityById(ID);
			sf::Event theEvent = *EventManager::getInstance()->getEvents()[eventIndex];
			auto mouseButton = theEvent.mouseButton.button;
			if (mouseButton == sf::Mouse::Button::Left) {
				exit(0);
			}
			return 0;
		});

		textComponent = quitButton->buttonHUDElement.getEntity()->getComponentByName(AB_HUD_TEXT);
		textComponent->setAttribute_float(ATTRIBUTE_ZBUFFER, 16.0);

		buttonList.push_back(quitButton);

		auto armyEngine = ArmyEngine::getInstance();
		auto componentFactory = armyEngine->getComponentFactory();
		auto shapeComponent = componentFactory.createShapeComponent(AB_MENU_SHAPE);
		this->getEntity()->addComponent(shapeComponent);

		//shape attributes
		shapeComponent->setAttribute_int(ATTRIBUTE_ENABLE, 0);
		shapeComponent->setAttribute_string(ATTRIBUTE_SHAPE_TYPE, SHAPETYPE_RECTANGLE);
		shapeComponent->setAttribute_float(ATTRIBUTE_WIDTH, 800.0f);
		shapeComponent->setAttribute_float(ATTRIBUTE_HEIGHT, 600.0f);
		shapeComponent->setAttribute_int(ATTRIBUTE_OUTLINE_COLOR_RED, 0);
		shapeComponent->setAttribute_int(ATTRIBUTE_OUTLINE_COLOR_BLUE, 0);
		shapeComponent->setAttribute_int(ATTRIBUTE_OUTLINE_COLOR_GREEN, 0);
		shapeComponent->setAttribute_int(ATTRIBUTE_OUTLINE_COLOR_ALPHA, 128);
		shapeComponent->setAttribute_float(ATTRIBUTE_OUTLINE_THICKNESS, 3.0);
		shapeComponent->setAttribute_int(ATTRIBUTE_FILL_COLOR_RED, 0);
		shapeComponent->setAttribute_int(ATTRIBUTE_FILL_COLOR_BLUE, 0);
		shapeComponent->setAttribute_int(ATTRIBUTE_FILL_COLOR_GREEN, 0);
		shapeComponent->setAttribute_int(ATTRIBUTE_FILL_COLOR_ALPHA, 170);
		shapeComponent->setAttribute_float(ATTRIBUTE_OFFSET_X, 0.0);
		shapeComponent->setAttribute_float(ATTRIBUTE_OFFSET_Y, 0.0);
		shapeComponent->setAttribute_float(ATTRIBUTE_ZBUFFER, 11.0);
		shapeComponent->update();
}

void Menu::display() {

	//enable the menu shape component as well
	auto shapeComponent = this->getEntity()->getComponentByName(AB_MENU_SHAPE);
	shapeComponent->setAttribute_int(ATTRIBUTE_ENABLE, 1);

	for (auto button : this->buttonList) {
		button->display();
	}
}

void Menu::hide() {

	//disable the menu shape component
	auto shapeComponent = this->getEntity()->getComponentByName(AB_MENU_SHAPE);
	shapeComponent->setAttribute_int(ATTRIBUTE_ENABLE, 0);

	for (auto button : this->buttonList) {
		//enable our text HUDElement component
		button->hide();
	}
}