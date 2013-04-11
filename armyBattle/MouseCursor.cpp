#include "MouseCursor.h"

MouseCursor::MouseCursor() {
	auto armyEngine = ArmyEngine::getInstance();
	auto entityFactory = armyEngine->getEntityFactory();

	//create the mouse cursor and add to the engine
	this->cursorEntity = entityFactory.createMainEntity(AB_MOUSE);
	armyEngine->addEntity(this->cursorEntity);
	auto entity = this->cursorEntity;

	//get the component factory
	auto componentFactory = armyEngine->getComponentFactory();

	//set and add the position component
	auto positionComponent = componentFactory.createPositionComponent(AB_MOUSE_POSITION);
	entity->addComponent(positionComponent);

	//Position Attribtues
	//not required, controlled by input component

	//set and add the shape component for the idle width cursor shape
	auto shapeComponent_width = componentFactory.createShapeComponent(AB_MOUSE_SHAPE_WIDTH_IDLE);
	entity->addComponent(shapeComponent_width);

	//Width idle shape component attributes
	shapeComponent_width->setAttribute_string(ATTRIBUTE_SHAPE_TYPE, SHAPETYPE_RECTANGLE);
	shapeComponent_width->setAttribute_float(ATTRIBUTE_WIDTH, 10.0f);
	shapeComponent_width->setAttribute_float(ATTRIBUTE_HEIGHT, 2.0f);
	shapeComponent_width->setAttribute_int(ATTRIBUTE_OUTLINE_COLOR_ALPHA, 0);
	shapeComponent_width->setAttribute_int(ATTRIBUTE_FILL_COLOR_RED, 255);
	shapeComponent_width->setAttribute_int(ATTRIBUTE_FILL_COLOR_BLUE, 0);
	shapeComponent_width->setAttribute_int(ATTRIBUTE_FILL_COLOR_GREEN, 0);
	shapeComponent_width->setAttribute_float(ATTRIBUTE_OFFSET_X, 0.0);
	shapeComponent_width->setAttribute_float(ATTRIBUTE_OFFSET_Y, 4.0);
	shapeComponent_width->setAttribute_float(ATTRIBUTE_ZBUFFER, 100.0f);
	shapeComponent_width->update();

	//set and add the shape component for the idle height cursor shape
	auto shapeComponent_height = componentFactory.createShapeComponent(AB_MOUSE_SHAPE_HEIGHT_IDLE);
	entity->addComponent(shapeComponent_height);

	//Height idle shape component attributes
	shapeComponent_height->setAttribute_string(ATTRIBUTE_SHAPE_TYPE, SHAPETYPE_RECTANGLE);
	shapeComponent_height->setAttribute_float(ATTRIBUTE_WIDTH, 2.0f);
	shapeComponent_height->setAttribute_float(ATTRIBUTE_HEIGHT, 10.0f);
	shapeComponent_height->setAttribute_int(ATTRIBUTE_OUTLINE_COLOR_ALPHA, 0);
	shapeComponent_height->setAttribute_int(ATTRIBUTE_FILL_COLOR_RED, 255);
	shapeComponent_height->setAttribute_int(ATTRIBUTE_FILL_COLOR_BLUE, 0);
	shapeComponent_height->setAttribute_int(ATTRIBUTE_FILL_COLOR_GREEN, 0);
	shapeComponent_height->setAttribute_float(ATTRIBUTE_OFFSET_X, 4.0);
	shapeComponent_height->setAttribute_float(ATTRIBUTE_OFFSET_Y, 0.0);
	shapeComponent_height->setAttribute_float(ATTRIBUTE_ZBUFFER, 10.0f);
	shapeComponent_height->update();

	//set the collision component to represent the mouse cursor when it is in the idle state
	auto collisionComponent_idle = componentFactory.createCollisionComponent(AB_MOUSE_COLLISION_IDLE);
	entity->addComponent(collisionComponent_idle);

	//collision component attributes
	collisionComponent_idle->setAttribute_string(ATTRIBUTE_COLLISION_BOUND_TYPE, COLLISION_BOUND_RECTANGLE);
	collisionComponent_idle->setAttribute_float(ATTRIBUTE_WIDTH, 5.0);
	collisionComponent_idle->setAttribute_float(ATTRIBUTE_HEIGHT, 5.0);
	collisionComponent_idle->setAttribute_string(ATTRIBUTE_COLLISION_TAG, AB_MOUSE);

	//add and set the input component for the idle state
	auto inputComponent_idle = componentFactory.createInputComponent(AB_MOUSE_INPUT_IDLE);
	entity->addComponent(inputComponent_idle);

	//input component attributes
	inputComponent_idle->setAttribute_string(ATTRIBUTE_INPUT_TYPE, INPUT_MOUSE_MOVE);
	inputComponent_idle->setAttribute_string(ATTRIBUTE_CALLBACK, AB_MOUSE_MOVE_CALLBACK);

	//add the appropriate callback for moving the mouse
	armyEngine->addInputCallback(AB_MOUSE_MOVE_CALLBACK, (functionEventTemplate) [] (int ID, int eventIndex) {
		auto entityManager = EntityManager::getInstance();
		auto entity = entityManager->getEntityById(ID);

		sf::Event theEvent = *EventManager::getInstance()->getEvents()[eventIndex];

		float xPosition = static_cast<float> (theEvent.mouseMove.x);
		float yPosition = static_cast<float> (theEvent.mouseMove.y);

		//apply the position of the mouse to the position of the entity
		auto positionComponent = entity->getComponentByName(AB_MOUSE_POSITION);
		positionComponent->setAttribute_float(ATTRIBUTE_POSITION_X, xPosition);
		positionComponent->setAttribute_float(ATTRIBUTE_POSITION_Y, yPosition);

		return 0;
	});

}

void MouseCursor::setIdle() {
	//enable the input component
	auto entity = this->cursorEntity;
	auto inputComponent_idle = entity->getComponentByName(AB_MOUSE_INPUT_IDLE);
	inputComponent_idle->setAttribute_int(ATTRIBUTE_ENABLE, 1);

	//enable the shape components
	auto shapeComponent_width = entity->getComponentByName(AB_MOUSE_SHAPE_WIDTH_IDLE);
	shapeComponent_width->setAttribute_int(ATTRIBUTE_ENABLE, 1);
	auto shapeComponent_height = entity->getComponentByName(AB_MOUSE_SHAPE_HEIGHT_IDLE);
	shapeComponent_height->setAttribute_int(ATTRIBUTE_ENABLE, 1);
}

void MouseCursor::disable() {
	//disable the input component
	auto entity = this->cursorEntity;
	auto inputComponent_idle = entity->getComponentByName(AB_MOUSE_INPUT_IDLE);
	inputComponent_idle->setAttribute_int(ATTRIBUTE_ENABLE, 0);

	//disable the shape components
	auto shapeComponent_width = entity->getComponentByName(AB_MOUSE_SHAPE_WIDTH_IDLE);
	shapeComponent_width->setAttribute_int(ATTRIBUTE_ENABLE, 0);
	auto shapeComponent_height = entity->getComponentByName(AB_MOUSE_SHAPE_HEIGHT_IDLE);
	shapeComponent_height->setAttribute_int(ATTRIBUTE_ENABLE, 0);
}