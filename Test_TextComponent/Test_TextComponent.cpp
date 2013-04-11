#include <iostream>
#include <list>
#include <memory>

#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"
#include "Components.h"
#include "Managers.h"
#include "Entities.h"
#include "Systems.h"
#include "AE_Attributes.h"
#include "AE_Events.h"

int main() {
	auto entity = std::shared_ptr<entityType> (new MainEntity("Text", 0));
	auto positionComponent = std::shared_ptr<componentType> (new PositionComponent("Position"));
	entity->addComponent(positionComponent);
	auto textComponent = std::shared_ptr<componentType> (new TextComponent("Text"));
	entity->addComponent(textComponent);

	//change the position
	positionComponent->setAttribute_float(ATTRIBUTE_POSITION_X, 100);
	positionComponent->setAttribute_float(ATTRIBUTE_POSITION_Y, 150);

	auto textManager = TextManager::getInstance();
	auto entityManager = EntityManager::getInstance();
	entityManager->addEntity(entity);
	textComponent->setAttribute_int(ATTRIBUTE_FILL_COLOR_BLUE, 0);
	textComponent->setAttribute_int(ATTRIBUTE_FILL_COLOR_GREEN, 255);
	textComponent->setAttribute_int(ATTRIBUTE_FILL_COLOR_RED, 0);
	textComponent->setAttribute_int(ATTRIBUTE_FILL_COLOR_ALPHA, 255);
	textComponent->setAttribute_int(ATTRIBUTE_TEXT_STYLE_BOLD, 1);
	textComponent->setAttribute_int(ATTRIBUTE_TEXT_STYLE_ITALIC, 1);
	textComponent->setAttribute_int(ATTRIBUTE_TEXT_SIZE, 50);

	textComponent->setAttribute_string(ATTRIBUTE_TEXT_STRING, "Hello world!");
	textComponent->update();

	sf::RenderWindow window(sf::VideoMode(800, 600), "Shape Window Test");

	auto systemManager = SystemManager::getInstance();
	auto eventSystem = std::shared_ptr<EventSystem> (new EventSystem());
	eventSystem->registerClosed_Callback([&] (int ID, int eventIndex) {
		window.close();
		return 0;
	});

	systemManager->addSystem(std::shared_ptr<systemType> (new SpriteSystem(window)));
	systemManager->addSystem(std::shared_ptr<systemType> (std::static_pointer_cast<systemType> (eventSystem)));
	

	//event manager requires a target window to operate correctly
	auto eventManager = EventManager::getInstance();

	//we set the target window to our render window
	eventManager->setWindow(&window);

	while(window.isOpen()) {
		window.clear();
		eventManager->pollEvents();
		systemManager->processSystemList();
		window.display();
	}
	return 0;
}

