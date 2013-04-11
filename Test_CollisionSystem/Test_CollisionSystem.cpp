#include <iostream>
#include <memory>
#include <functional>

#include "Managers.h"
#include "Entities.h"
#include "Components.h"
#include "Systems.h"
#include "AE_Attributes.h"
#include "AE_Events.h"
#include "AE_Utilities.h"

#define MOUSEINPUTCALLBACK "CursorCallback"

int main() {
	auto entityManager = EntityManager::getInstance();

	//create entities
	auto entity = std::shared_ptr<entityType> (new MainEntity("Cursor", 0));
	entityManager->addEntity(entity);
	
	auto shapeComponent = std::shared_ptr<componentType> (new ShapeComponent("CursorHeight"));
	entity->addComponent(shapeComponent);
	shapeComponent->setAttribute_string(ATTRIBUTE_SHAPE_TYPE, SHAPETYPE_RECTANGLE);
	shapeComponent->setAttribute_float(ATTRIBUTE_WIDTH, 2.0f);
	shapeComponent->setAttribute_float(ATTRIBUTE_HEIGHT, 10.0f);
	shapeComponent->setAttribute_float(ATTRIBUTE_RADIUS, 5.0);
	shapeComponent->setAttribute_int(ATTRIBUTE_OUTLINE_COLOR_ALPHA, 0);
	shapeComponent->setAttribute_int(ATTRIBUTE_FILL_COLOR_RED, 255);
	shapeComponent->setAttribute_int(ATTRIBUTE_FILL_COLOR_BLUE, 0);
	shapeComponent->setAttribute_int(ATTRIBUTE_FILL_COLOR_GREEN, 0);
	shapeComponent->setAttribute_float(ATTRIBUTE_OFFSET_X, 4.0);
	shapeComponent->setAttribute_float(ATTRIBUTE_OFFSET_Y, 0.0);
	shapeComponent->setAttribute_float(ATTRIBUTE_ZBUFFER, 1.1f);
	shapeComponent->update();

	auto shapeComponent2 = std::shared_ptr<componentType> (new ShapeComponent("CursorWidth"));
	entity->addComponent(shapeComponent2);
	shapeComponent2->setAttribute_string(ATTRIBUTE_SHAPE_TYPE, SHAPETYPE_RECTANGLE);
	shapeComponent2->setAttribute_float(ATTRIBUTE_WIDTH, 10.0f);
	shapeComponent2->setAttribute_float(ATTRIBUTE_HEIGHT, 2.0f);
	shapeComponent2->setAttribute_float(ATTRIBUTE_RADIUS, 5.0);
	shapeComponent2->setAttribute_int(ATTRIBUTE_OUTLINE_COLOR_ALPHA, 0);
	shapeComponent2->setAttribute_int(ATTRIBUTE_FILL_COLOR_RED, 255);
	shapeComponent2->setAttribute_int(ATTRIBUTE_FILL_COLOR_BLUE, 0);
	shapeComponent2->setAttribute_int(ATTRIBUTE_FILL_COLOR_GREEN, 0);
	shapeComponent2->setAttribute_float(ATTRIBUTE_OFFSET_X, 0.0);
	shapeComponent2->setAttribute_float(ATTRIBUTE_OFFSET_Y, 4.0);
	shapeComponent2->setAttribute_float(ATTRIBUTE_ZBUFFER, 1.1f);
	shapeComponent2->update();

	auto collisionComponent = std::shared_ptr<componentType> (new CollisionComponent("Cursor Collision"));
	entity->addComponent(collisionComponent);
	collisionComponent->setAttribute_string(ATTRIBUTE_COLLISION_BOUND_TYPE, COLLISION_BOUND_RECTANGLE);
	collisionComponent->setAttribute_float(ATTRIBUTE_WIDTH, 5.0);
	collisionComponent->setAttribute_float(ATTRIBUTE_HEIGHT, 5.0);
	collisionComponent->setAttribute_string(ATTRIBUTE_COLLISION_TAG, "Cursor");

	auto positionComponent = std::shared_ptr<componentType> (new PositionComponent("CursorPosition"));
	entity->addComponent(positionComponent);
	positionComponent->setAttribute_float(ATTRIBUTE_POSITION_X, 400);
	positionComponent->setAttribute_float(ATTRIBUTE_POSITION_Y, 300);
	positionComponent->setAttribute_float(ATTRIBUTE_OFFSET_X, -5.0);
	positionComponent->setAttribute_float(ATTRIBUTE_OFFSET_Y, -5.0);

	auto inputComponent = std::shared_ptr<componentType> (new InputComponent("Cursor Input"));
	entity->addComponent(inputComponent);
	inputComponent->setAttribute_string(ATTRIBUTE_INPUT_TYPE, INPUT_MOUSE_MOVE);
	inputComponent->setAttribute_string(ATTRIBUTE_CALLBACK, MOUSEINPUTCALLBACK);

	auto callbackManager = CallbackManager::getInstance();
	callbackManager->addCallback(MOUSEINPUTCALLBACK, (functionEventTemplate) [] (int ID, int eventIndex) {
		auto entity = EntityManager::getInstance()->getEntityById(ID);

		sf::Event theEvent = *EventManager::getInstance()->getEvents()[eventIndex];

		float xPosition = static_cast<float> (theEvent.mouseMove.x);
		float yPosition = static_cast<float> (theEvent.mouseMove.y);

		//apply the position of the mouse to the position of the entity
		auto positionComponent = entity->getComponentByName("CursorPosition");
		positionComponent->setAttribute_float("Position_X", xPosition);
		positionComponent->setAttribute_float("Position_Y", yPosition);

		return 0;
	});

	auto entity2 = std::shared_ptr<entityType> (new MainEntity("Collidable Button", 1));
	entityManager->addEntity(entity2);
	auto shapeComponent3 = std::shared_ptr<componentType> (new ShapeComponent("Button Shape"));
	entity2->addComponent(shapeComponent3);
	shapeComponent3->setAttribute_string(ATTRIBUTE_SHAPE_TYPE, SHAPETYPE_RECTANGLE);
	shapeComponent3->setAttribute_float(ATTRIBUTE_WIDTH, 300.0f);
	shapeComponent3->setAttribute_float(ATTRIBUTE_HEIGHT, 200.0f);
	shapeComponent3->setAttribute_float(ATTRIBUTE_RADIUS, 5.0);
	shapeComponent3->setAttribute_int(ATTRIBUTE_OUTLINE_COLOR_RED, 0);
	shapeComponent3->setAttribute_int(ATTRIBUTE_OUTLINE_COLOR_BLUE, 255);
	shapeComponent3->setAttribute_int(ATTRIBUTE_OUTLINE_COLOR_GREEN, 0);
	shapeComponent3->setAttribute_int(ATTRIBUTE_OUTLINE_COLOR_ALPHA, 255);
	shapeComponent3->setAttribute_float(ATTRIBUTE_OUTLINE_THICKNESS, 5.0);
	shapeComponent3->setAttribute_int(ATTRIBUTE_FILL_COLOR_RED, 0);
	shapeComponent3->setAttribute_int(ATTRIBUTE_FILL_COLOR_BLUE, 0);
	shapeComponent3->setAttribute_int(ATTRIBUTE_FILL_COLOR_GREEN, 255);
	shapeComponent3->setAttribute_float(ATTRIBUTE_OFFSET_X, 0.0);
	shapeComponent3->setAttribute_float(ATTRIBUTE_OFFSET_Y, 0.0);
	shapeComponent3->setAttribute_float(ATTRIBUTE_ZBUFFER, 0.0);
	shapeComponent3->update();

	auto textComponent = std::shared_ptr<componentType> (new TextComponent("Text"));
	entity2->addComponent(textComponent);
	textComponent->setAttribute_string(ATTRIBUTE_TEXT_STRING, "Not collided with");
	textComponent->setAttribute_int(ATTRIBUTE_TEXT_SIZE, 30);
	textComponent->setAttribute_int(ATTRIBUTE_FILL_COLOR_ALPHA, 200);
	textComponent->setAttribute_int(ATTRIBUTE_FILL_COLOR_RED, 20);
	textComponent->setAttribute_int(ATTRIBUTE_FILL_COLOR_GREEN, 20);
	textComponent->setAttribute_int(ATTRIBUTE_FILL_COLOR_BLUE, 20);
	textComponent->update();

	auto positionComponent2 = std::shared_ptr<componentType> (new PositionComponent("BoxPosition"));
	entity2->addComponent(positionComponent2);
	positionComponent2->setAttribute_float(ATTRIBUTE_POSITION_X, 100.0);
	positionComponent2->setAttribute_float(ATTRIBUTE_POSITION_Y, 150.0);
	positionComponent2->setAttribute_float(ATTRIBUTE_OFFSET_X, 0);
	positionComponent2->setAttribute_float(ATTRIBUTE_OFFSET_Y, 0);

	auto collisionComponent2 = std::shared_ptr<componentType> (new CollisionComponent("CollisionButton"));
	entity2->addComponent(collisionComponent2);
	collisionComponent2->setAttribute_string(ATTRIBUTE_COLLISION_BOUND_TYPE, COLLISION_BOUND_RECTANGLE);
	collisionComponent2->setAttribute_float(ATTRIBUTE_WIDTH, 300.0);
	collisionComponent2->setAttribute_float(ATTRIBUTE_HEIGHT, 200.0);
	collisionComponent2->setAttribute_string(ATTRIBUTE_COLLISION_TAG, "Button");

	//adding callbacks for when collisions occur
	auto collisionManager = CollisionManager::getInstance();
	collisionManager->addCallback(collisionTagTuple("Button", "Cursor"),
		(functionCollisionTemplate) [] (collisionParamTuple paramTuple) {
			int entityID1, entityID2;
			std::string compName1, compName2;
			bool bRegistered;
			std::tie(entityID1, compName1, entityID2, compName2, bRegistered) = paramTuple;
	
			//grab the button entity
			auto buttonEntity = EntityManager::getInstance()->getEntityById(entityID1);
			//grab the shape component within that entity
			auto shapeComponent = buttonEntity->getComponentByName("Button Shape");
			auto textComponent = buttonEntity->getComponentByName("Text");

			if (bRegistered) {
				//change the shape component to have new outline
				shapeComponent->setAttribute_int(ATTRIBUTE_FILL_COLOR_RED, 255);
				shapeComponent->setAttribute_int(ATTRIBUTE_FILL_COLOR_GREEN, 0);
				shapeComponent->setAttribute_int(ATTRIBUTE_FILL_COLOR_BLUE, 0);
				textComponent->setAttribute_string(ATTRIBUTE_TEXT_STRING, "Collided!");
				std::cout << "Collision!" << std::endl;

			}
			else {
				shapeComponent->setAttribute_int(ATTRIBUTE_FILL_COLOR_RED, 0);
				shapeComponent->setAttribute_int(ATTRIBUTE_FILL_COLOR_GREEN, 255);
				shapeComponent->setAttribute_int(ATTRIBUTE_FILL_COLOR_BLUE, 0);
				textComponent->setAttribute_string(ATTRIBUTE_TEXT_STRING, "Not Collided");
			}
			shapeComponent->update();
			textComponent->update();
			return 0;


	});

	//Start working on the window instance and system
	auto window = sf::RenderWindow(sf::VideoMode(800,600), "Mouse Cursor Input Test");
	//remove the mouse cursor
	window.setMouseCursorVisible(false);

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
	systemManager->addSystem(std::shared_ptr<systemType> (new CollisionSystem()));
	systemManager->addSystem(std::shared_ptr<systemType> (std::static_pointer_cast<systemType> (eventSystem)));

	while(window.isOpen()) {
		window.clear();
		eventManager->pollEvents();
		systemManager->processSystemList();
		window.display();
	}
	return 0;
}