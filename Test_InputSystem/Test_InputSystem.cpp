#include <iostream>
#include <memory>
#include "SFML\Window.hpp"
#include "Systems.h"
#include "Managers.h"
#include "Entities.h"
#include "Components.h"
#include "AE_Events.h"
#include "AE_Attributes.h"

std::shared_ptr<AbstractEntity> createCursorEntity(std::string name) {
	static int ID = 0;
	auto entity = std::shared_ptr<AbstractEntity> (new MainEntity(name, ID++));
	//assign components
	//sprite
	auto spriteComponent = std::shared_ptr<AbstractComponent> (new SpriteComponent("CursorSprite"));
	spriteComponent->setAttribute_float("Offset_X", -100.);
	spriteComponent->setAttribute_float("Offset_Y", -100.);
	entity->addComponent(spriteComponent);

	//position
	auto positionComponent = std::shared_ptr<AbstractComponent> (new PositionComponent("CursorPosition"));
	entity->addComponent(positionComponent);

	//input, mouse move
	auto inputComponent = std::shared_ptr<AbstractComponent> (new InputComponent("CursorInput"));
	//assign input to entity
	entity->addComponent(inputComponent);
	//define attributes of the input
	inputComponent->setAttribute_string(ATTRIBUTE_INPUT_TYPE, INPUT_MOUSE_MOVE);
	inputComponent->setAttribute_string(ATTRIBUTE_CALLBACK, "CursorMoveCallBack");
	
	//Create our callback function and store it in the manager
	auto callbackManager = CallbackManager::getInstance();
	if (!callbackManager->hasCallback("CursorMoveCallback")) {
		callbackManager->addCallback("CursorMoveCallBack", (functionEventTemplate) [] (int ID, int eventIndex) {
			auto entity = EntityManager::getInstance()->getEntityById(ID);
		
			//grab the given event from the current eventList using the event index
			sf::Event theEvent = *EventManager::getInstance()->getEvents()[eventIndex];
		
			//we know that the event is a INPUT_MOUSE_MOVE event, 
			  //so we treat it as that type of an sfml::Event object with
			  //its given set of attributes
			//http://www.sfml-dev.org/documentation/2.0/Event_8hpp_source.php  
			//http://www.sfml-dev.org/documentation/2.0/structsf_1_1Event_1_1MouseMoveEvent.php
			//Grab the mouse x and y positions 
			float xPosition = static_cast<float> (theEvent.mouseMove.x);
			float yPosition = static_cast<float> (theEvent.mouseMove.y);
			std::cout << "(" << xPosition << ", " << yPosition << ")" << std::endl;
			//apply the position of the mouse to the position of the entity
			auto positionComponent = entity->getComponentByName("CursorPosition");
			positionComponent->setAttribute_float("Position_X", xPosition);
			positionComponent->setAttribute_float("Position_Y", yPosition);

			return 0;
		});
	} //(!callbackManager->hasCallback("CursorMoveCallback")) {
	return entity;
}

int main() {
	auto window = sf::RenderWindow(sf::VideoMode(800,600), "Mouse Cursor Input Test");
	//event manager requires a target window to operate correctly
	auto eventManager = EventManager::getInstance();

	//we set the target window to our render window
	eventManager->setWindow(&window);

	auto eventSystem = std::shared_ptr<EventSystem> (new EventSystem());
	eventSystem->registerClosed_Callback([&] (int ID, int eventIndex) {
		window.close();
		return 0;
	});

	//populate the system manager
	auto systemManager = SystemManager::getInstance();
	systemManager->addSystem(std::shared_ptr<systemType> (new SpriteSystem(window)));
	systemManager->addSystem(std::shared_ptr<systemType> (new InputSystem()));
	systemManager->addSystem(std::shared_ptr<systemType> (std::static_pointer_cast<systemType> (eventSystem)));

	//populate our entity manager
	auto entityManager = EntityManager::getInstance();
	entityManager->addEntity(createCursorEntity("MouseCursor"));

	while(window.isOpen()) {
		window.clear();
		eventManager->pollEvents();
		systemManager->processSystemList();
		window.display();
	}
	return 0;
}