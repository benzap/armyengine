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
	auto entity = std::shared_ptr<entityType> (new MainEntity("Rectangle", 0));
	auto positionComponent = std::shared_ptr<componentType> (new PositionComponent("Position"));
	entity->addComponent(positionComponent);
	auto shapeComponent = std::shared_ptr<componentType> (new ShapeComponent("RectangleShape"));
	entity->addComponent(shapeComponent);

	//change the position
	positionComponent->setAttribute_float(ATTRIBUTE_POSITION_X, 100);
	positionComponent->setAttribute_float(ATTRIBUTE_POSITION_Y, 150);

	//tinker with the shape component
	shapeComponent->setAttribute_float(ATTRIBUTE_WIDTH, 100);
	shapeComponent->setAttribute_float(ATTRIBUTE_HEIGHT, 200);
	shapeComponent->setAttribute_string(ATTRIBUTE_SHAPE_TYPE, SHAPETYPE_RECTANGLE);

	shapeComponent->setAttribute_int(ATTRIBUTE_OUTLINE_COLOR_BLUE, 0);
	shapeComponent->setAttribute_int(ATTRIBUTE_OUTLINE_COLOR_GREEN, 0);
	shapeComponent->setAttribute_float(ATTRIBUTE_OUTLINE_THICKNESS, 5.0);
	shapeComponent->update();

	auto entityManager = EntityManager::getInstance();
	entityManager->addEntity(entity);

	entity = std::shared_ptr<entityType> (new MainEntity("Rectangle", 0));
	positionComponent = std::shared_ptr<componentType> (new PositionComponent("Position"));
	entity->addComponent(positionComponent);
	shapeComponent = std::shared_ptr<componentType> (new ShapeComponent("CircleShape"));
	entity->addComponent(shapeComponent);

	//change the position
	positionComponent->setAttribute_float(ATTRIBUTE_POSITION_X, 150);
	positionComponent->setAttribute_float(ATTRIBUTE_POSITION_Y, 150);

	//tinker with the shape component
	shapeComponent->setAttribute_float(ATTRIBUTE_RADIUS, 50);
	shapeComponent->setAttribute_string(ATTRIBUTE_SHAPE_TYPE, SHAPETYPE_CIRCLE);

	shapeComponent->setAttribute_int(ATTRIBUTE_FILL_COLOR_BLUE, 0);
	shapeComponent->setAttribute_int(ATTRIBUTE_FILL_COLOR_GREEN, 255);
	shapeComponent->setAttribute_int(ATTRIBUTE_FILL_COLOR_RED, 0);
	shapeComponent->setAttribute_int(ATTRIBUTE_FILL_COLOR_ALPHA, 128);

	shapeComponent->setAttribute_int(ATTRIBUTE_OUTLINE_COLOR_BLUE, 0);
	shapeComponent->setAttribute_int(ATTRIBUTE_OUTLINE_COLOR_GREEN, 255);
	shapeComponent->setAttribute_int(ATTRIBUTE_OUTLINE_COLOR_RED, 0);
	shapeComponent->setAttribute_int(ATTRIBUTE_OUTLINE_COLOR_ALPHA, 128);

	shapeComponent->setAttribute_float(ATTRIBUTE_OUTLINE_THICKNESS, 5.0);
	shapeComponent->update();

	entityManager->addEntity(entity);
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