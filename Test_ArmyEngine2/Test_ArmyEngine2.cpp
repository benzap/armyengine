//Used to test the collision between two circles

#include <iostream>
#include <cassert>

#include "ArmyEngine.h"

std::shared_ptr<entityType> createCursor() {
	auto armyEngine = ArmyEngine::getInstance();
	auto entity = armyEngine->getEntityFactory().createMainEntity("Cursor");

	auto componentFactory = armyEngine->getComponentFactory();

	//The vertical red bar shape
	auto shapeComponent = componentFactory.createShapeComponent("CursorHeight");
	entity->addComponent(shapeComponent);
	//shapeComponent->setAttribute_string(ATTRIBUTE_SHAPE_TYPE, SHAPETYPE_CIRCLE);
	//shapeComponent->setAttribute_float(ATTRIBUTE_RADIUS, 5.0f);
	shapeComponent->setAttribute_string(ATTRIBUTE_SHAPE_TYPE, SHAPETYPE_POLYGON);
	auto trianglePoints = shapeComponent->getAttribute_floatArray(ATTRIBUTE_POLYGON_POINTS);
	trianglePoints->push_back(0); trianglePoints->push_back(0);
	//trianglePoints->push_back(0); trianglePoints->push_back(100);
	trianglePoints->push_back(100); trianglePoints->push_back(100);
	trianglePoints->push_back(100); trianglePoints->push_back(0);

	shapeComponent->setAttribute_int(ATTRIBUTE_OUTLINE_COLOR_ALPHA, 0);
	shapeComponent->setAttribute_int(ATTRIBUTE_FILL_COLOR_RED, 100);
	shapeComponent->setAttribute_int(ATTRIBUTE_FILL_COLOR_BLUE, 100);
	shapeComponent->setAttribute_int(ATTRIBUTE_FILL_COLOR_GREEN, 0);
	shapeComponent->setAttribute_float(ATTRIBUTE_OFFSET_X, 0.0);
	shapeComponent->setAttribute_float(ATTRIBUTE_OFFSET_Y, 0.0);
	shapeComponent->setAttribute_float(ATTRIBUTE_ZBUFFER, 1.1f);
	shapeComponent->update();

	//The horizontal bar shape
	/*
	auto shapeComponent2 = componentFactory.createShapeComponent("CursorWidth");
	entity->addComponent(shapeComponent2);
	shapeComponent2->setAttribute_string(ATTRIBUTE_SHAPE_TYPE, SHAPETYPE_RECTANGLE);
	shapeComponent2->setAttribute_float(ATTRIBUTE_WIDTH, 10.0f);
	shapeComponent2->setAttribute_float(ATTRIBUTE_HEIGHT, 2.0f);
	shapeComponent2->setAttribute_int(ATTRIBUTE_OUTLINE_COLOR_ALPHA, 0);
	shapeComponent2->setAttribute_int(ATTRIBUTE_FILL_COLOR_RED, 100);
	shapeComponent2->setAttribute_int(ATTRIBUTE_FILL_COLOR_BLUE, 100);
	shapeComponent2->setAttribute_int(ATTRIBUTE_FILL_COLOR_GREEN, 0);
	shapeComponent2->setAttribute_float(ATTRIBUTE_OFFSET_X, 0.0);
	shapeComponent2->setAttribute_float(ATTRIBUTE_OFFSET_Y, 4.0);
	shapeComponent2->setAttribute_float(ATTRIBUTE_ZBUFFER, 1.1f);
	shapeComponent2->update();
	*/

	//The position component for positioning the shapes representing the cursor and collision bounds
	auto positionComponent = componentFactory.createPositionComponent("CursorPosition");
	entity->addComponent(positionComponent);
	positionComponent->setAttribute_float(ATTRIBUTE_POSITION_X, 400);
	positionComponent->setAttribute_float(ATTRIBUTE_POSITION_Y, 300);
	positionComponent->setAttribute_float(ATTRIBUTE_OFFSET_X, 0.0);
	positionComponent->setAttribute_float(ATTRIBUTE_OFFSET_Y, 0.0);

	//The Collision component, is used to identify the collision bounds of the cursor
	auto collisionComponent = componentFactory.createCollisionComponent("CursorCollision");
	entity->addComponent(collisionComponent);
	collisionComponent->setAttribute_string(ATTRIBUTE_COLLISION_BOUND_TYPE, COLLISION_BOUND_POLYGON);
	collisionComponent->setAttribute_float(ATTRIBUTE_RADIUS, 5.0);
	collisionComponent->setAttribute_string(ATTRIBUTE_COLLISION_TAG, "Cursor");
	trianglePoints = collisionComponent->getAttribute_floatArray(ATTRIBUTE_POLYGON_POINTS);
	trianglePoints->push_back(0); trianglePoints->push_back(0);
	//trianglePoints->push_back(0); trianglePoints->push_back(100);
	trianglePoints->push_back(100); trianglePoints->push_back(100);
	trianglePoints->push_back(100); trianglePoints->push_back(0);

	//The input component, since this entity resembles actions involving input,
	// it is required
	auto inputComponent = componentFactory.createInputComponent("CursorInput");
	entity->addComponent(inputComponent);
	inputComponent->setAttribute_string(ATTRIBUTE_INPUT_TYPE, INPUT_MOUSE_MOVE);
	inputComponent->setAttribute_string(ATTRIBUTE_CALLBACK, "CursorCallback");

	//The input callback for moving the mouse. This is called everytime the mouse moves
	// and affects this entity
	armyEngine->addInputCallback("CursorCallback", (functionEventTemplate) [] (int ID, int eventIndex) {
		auto entity = EntityManager::getInstance()->getEntityById(ID);

		sf::Event theEvent = *EventManager::getInstance()->getEvents()[eventIndex];

		float xPosition = static_cast<float> (theEvent.mouseMove.x);
		float yPosition = static_cast<float> (theEvent.mouseMove.y);

		//apply the position of the mouse to the position of the entity
		auto positionComponent = entity->getComponentByName("CursorPosition");
		positionComponent->setAttribute_float(ATTRIBUTE_POSITION_X, xPosition);
		positionComponent->setAttribute_float(ATTRIBUTE_POSITION_Y, yPosition);

		return 0;
	});

	return entity;
}

std::shared_ptr<entityType> createButton(std::string name, int xPosition, int yPosition) {
	auto armyEngine = ArmyEngine::getInstance();
	auto entity = armyEngine->getEntityFactory().createMainEntity("Button");

	auto componentFactory = armyEngine->getComponentFactory();

	auto shapeComponent = componentFactory.createShapeComponent("ButtonShape");
	entity->addComponent(shapeComponent);
	shapeComponent->setAttribute_string(ATTRIBUTE_SHAPE_TYPE, SHAPETYPE_CIRCLE);
	shapeComponent->setAttribute_float(ATTRIBUTE_RADIUS, 25.0);
	shapeComponent->setAttribute_int(ATTRIBUTE_OUTLINE_COLOR_RED, 0);
	shapeComponent->setAttribute_int(ATTRIBUTE_OUTLINE_COLOR_BLUE, 255);
	shapeComponent->setAttribute_int(ATTRIBUTE_OUTLINE_COLOR_GREEN, 0);
	shapeComponent->setAttribute_int(ATTRIBUTE_OUTLINE_COLOR_ALPHA, 255);
	shapeComponent->setAttribute_float(ATTRIBUTE_OUTLINE_THICKNESS, 3.0);
	shapeComponent->setAttribute_int(ATTRIBUTE_FILL_COLOR_RED, 0);
	shapeComponent->setAttribute_int(ATTRIBUTE_FILL_COLOR_BLUE, 0);
	shapeComponent->setAttribute_int(ATTRIBUTE_FILL_COLOR_GREEN, 255);
	shapeComponent->setAttribute_float(ATTRIBUTE_OFFSET_X, 0.0);
	shapeComponent->setAttribute_float(ATTRIBUTE_OFFSET_Y, 0.0);
	shapeComponent->setAttribute_float(ATTRIBUTE_ZBUFFER, 0.0);
	shapeComponent->update();

	auto textComponent = componentFactory.createTextComponent("ButtonText");
	entity->addComponent(textComponent);
	textComponent->setAttribute_string(ATTRIBUTE_TEXT_STRING, name);
	textComponent->setAttribute_int(ATTRIBUTE_TEXT_SIZE, 20);
	textComponent->setAttribute_int(ATTRIBUTE_FILL_COLOR_ALPHA, 200);
	textComponent->setAttribute_int(ATTRIBUTE_FILL_COLOR_RED, 20);
	textComponent->setAttribute_int(ATTRIBUTE_FILL_COLOR_GREEN, 20);
	textComponent->setAttribute_int(ATTRIBUTE_FILL_COLOR_BLUE, 20);
	textComponent->setAttribute_float(ATTRIBUTE_OFFSET_X, 10);
	textComponent->setAttribute_float(ATTRIBUTE_OFFSET_Y, 10);
	textComponent->update();

	auto positionComponent = componentFactory.createPositionComponent("ButtonPosition");
	entity->addComponent(positionComponent);
	positionComponent->setAttribute_float(ATTRIBUTE_POSITION_X, xPosition);
	positionComponent->setAttribute_float(ATTRIBUTE_POSITION_Y, yPosition);
	positionComponent->setAttribute_float(ATTRIBUTE_OFFSET_X, 0);
	positionComponent->setAttribute_float(ATTRIBUTE_OFFSET_Y, 0);

	auto collisionComponent = componentFactory.createCollisionComponent("ButtonCollision");
	entity->addComponent(collisionComponent);
	collisionComponent->setAttribute_string(ATTRIBUTE_COLLISION_BOUND_TYPE, COLLISION_BOUND_CIRCLE);
	collisionComponent->setAttribute_float(ATTRIBUTE_RADIUS, 25.0);
	collisionComponent->setAttribute_string(ATTRIBUTE_COLLISION_TAG, "Button");

	armyEngine->addCollisionCallback(collisionTagTuple("Button", "Cursor"),
		(functionCollisionTemplate) [] (collisionParamTuple paramTuple) {
			int entityID1, entityID2;
			std::string compName1, compName2;
			bool bRegistered;
			std::tie(entityID1, compName1, entityID2, compName2, bRegistered) = paramTuple;

			//grab the button entity
			auto buttonEntity = EntityManager::getInstance()->getEntityById(entityID1);

			auto shapeComponent = buttonEntity->getComponentByName("ButtonShape");
			auto textComponent = buttonEntity->getComponentByName("ButtonText");

			if (bRegistered) {
				//change the shape component to have new outline
				shapeComponent->setAttribute_int(ATTRIBUTE_FILL_COLOR_RED, 255);
				shapeComponent->setAttribute_int(ATTRIBUTE_FILL_COLOR_GREEN, 0);
				shapeComponent->setAttribute_int(ATTRIBUTE_FILL_COLOR_BLUE, 0);
				textComponent->setAttribute_string(ATTRIBUTE_TEXT_STRING, "C");
				std::cout << "Collision!" << std::endl;

			}
			else {
				shapeComponent->setAttribute_int(ATTRIBUTE_FILL_COLOR_RED, 0);
				shapeComponent->setAttribute_int(ATTRIBUTE_FILL_COLOR_GREEN, 255);
				shapeComponent->setAttribute_int(ATTRIBUTE_FILL_COLOR_BLUE, 0);
				textComponent->setAttribute_string(ATTRIBUTE_TEXT_STRING, "D");
			}
			shapeComponent->update();
			textComponent->update();
			return 0;
	});
	return entity;
}

int main() {
	auto armyEngine = ArmyEngine::getInstance();
	armyEngine->addEntity(createCursor());
	armyEngine->addEntity(createButton("Resume", 100, 100));
	/*armyEngine->addEntity(createButton("Restart", 100, 60));
	armyEngine->addEntity(createButton("Quit", 100, 110));
	armyEngine->addEntity(createButton("Other3", 100, 160));
	armyEngine->addEntity(createButton("Other1", 250, 10));
	armyEngine->addEntity(createButton("Other2", 250, 60));
	armyEngine->addEntity(createButton("Other3", 250, 110));
	armyEngine->addEntity(createButton("Other3", 250, 160));
	armyEngine->addEntity(createButton("Other1", 400, 10));
	armyEngine->addEntity(createButton("Other2", 400, 60));
	armyEngine->addEntity(createButton("Other3", 400, 110));
	armyEngine->addEntity(createButton("Other3", 400, 160));
	armyEngine->addEntity(createButton("Other1", 550, 10));
	armyEngine->addEntity(createButton("Other2", 550, 60));
	armyEngine->addEntity(createButton("Other3", 550, 110));
	armyEngine->addEntity(createButton("Other3", 550, 160));
	armyEngine->addEntity(createButton("Other1", 700, 10));
	armyEngine->addEntity(createButton("Other2", 700, 60));
	armyEngine->addEntity(createButton("Other3", 700, 110));
	armyEngine->addEntity(createButton("Other3", 700, 160));*/


	//create the close program event
	armyEngine->addEventCallback(EnumEventType::EVENT_CLOSED, [] (int eventIndex) {
		auto armyEngine = ArmyEngine::getInstance();
		auto window = armyEngine->getWindow();
		window->close();
		return 0;
	});


	armyEngine->runMainLoop();

	return 0;
}