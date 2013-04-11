#include "World.h"
#include "Button.h"
#include "AB_Utilities.h"

#include <iostream>
#include <string>


Button::Button(float xPosition, float yPosition) :
	WorldObject(AB_BUTTON, xPosition, yPosition),
	buttonHUDElement(HUDElement(xPosition, yPosition, BUTTON_FONT_SIZE)),
	buttonText("Test message") {
		this->setButtonText(buttonText);

		//change the Z-Buffer of our button to display over the
		//  the button
		auto textComponent_HUD = this->buttonHUDElement.getEntity()->getComponentByName(AB_HUD_TEXT);
		textComponent_HUD->setAttribute_float(ATTRIBUTE_ZBUFFER, 4.0);
		textComponent_HUD->update();

		auto armyEngine = ArmyEngine::getInstance();

		auto entity = this->getEntity();

		auto componentFactory = armyEngine->getComponentFactory();
		auto shapeComponent = componentFactory.createShapeComponent(AB_BUTTON_SHAPE);
		entity->addComponent(shapeComponent);

		//shape attributes
		shapeComponent->setAttribute_int(ATTRIBUTE_ENABLE, 1);
		shapeComponent->setAttribute_string(ATTRIBUTE_SHAPE_TYPE, SHAPETYPE_RECTANGLE);
		shapeComponent->setAttribute_float(ATTRIBUTE_WIDTH, BUTTON_DEFAULT_WIDTH);
		shapeComponent->setAttribute_float(ATTRIBUTE_HEIGHT, BUTTON_DEFAULT_HEIGHT);
		shapeComponent->setAttribute_int(ATTRIBUTE_OUTLINE_COLOR_RED, 0);
		shapeComponent->setAttribute_int(ATTRIBUTE_OUTLINE_COLOR_BLUE, 255);
		shapeComponent->setAttribute_int(ATTRIBUTE_OUTLINE_COLOR_GREEN, 0);
		shapeComponent->setAttribute_int(ATTRIBUTE_OUTLINE_COLOR_ALPHA, 255);
		shapeComponent->setAttribute_float(ATTRIBUTE_OUTLINE_THICKNESS, BUTTON_DEFAULT_OUTLINE);
		shapeComponent->setAttribute_int(ATTRIBUTE_FILL_COLOR_RED, 0);
		shapeComponent->setAttribute_int(ATTRIBUTE_FILL_COLOR_BLUE, 128);
		shapeComponent->setAttribute_int(ATTRIBUTE_FILL_COLOR_GREEN, 128);
		shapeComponent->setAttribute_int(ATTRIBUTE_FILL_COLOR_ALPHA, 255);
		shapeComponent->setAttribute_float(ATTRIBUTE_OFFSET_X, 0.0);
		shapeComponent->setAttribute_float(ATTRIBUTE_OFFSET_Y, 0.0);
		shapeComponent->setAttribute_float(ATTRIBUTE_ZBUFFER, 12.0);
		shapeComponent->update();

		//collision component for mouse over focusing
		auto collisionComponent = componentFactory.createCollisionComponent(AB_BUTTON_COLLISION);
		entity->addComponent(collisionComponent);

		collisionComponent->setAttribute_int(ATTRIBUTE_ENABLE, 1);
		collisionComponent->setAttribute_string(ATTRIBUTE_COLLISION_BOUND_TYPE, COLLISION_BOUND_RECTANGLE);
		collisionComponent->setAttribute_float(ATTRIBUTE_WIDTH, BUTTON_DEFAULT_WIDTH);
		collisionComponent->setAttribute_float(ATTRIBUTE_HEIGHT, BUTTON_DEFAULT_HEIGHT);
		collisionComponent->setAttribute_string(ATTRIBUTE_COLLISION_TAG, AB_BUTTON);

		armyEngine->addCollisionCallback(collisionTagTuple(AB_BUTTON, AB_MOUSE),
			(functionCollisionTemplate) [] (collisionParamTuple paramTuple) {
				int entityID1, entityID2;
				std::string compName1, compName2;
				bool bRegistered;
				std::tie(entityID1, compName1, entityID2, compName2, bRegistered) = paramTuple;

				//grab the button entity
				auto buttonEntity = EntityManager::getInstance()->getEntityById(entityID1);

				auto shapeComponent = buttonEntity->getComponentByName(AB_BUTTON_SHAPE);
				auto inputComponent = buttonEntity->getComponentByName(AB_BUTTON_PRESSED);


				if (bRegistered) {
					//change the shape component to have new outline
					shapeComponent->setAttribute_int(ATTRIBUTE_FILL_COLOR_RED, 128);
					shapeComponent->setAttribute_int(ATTRIBUTE_FILL_COLOR_GREEN, 0);
					shapeComponent->setAttribute_int(ATTRIBUTE_FILL_COLOR_BLUE, 0);
					//enable input component
					inputComponent->setAttribute_int(ATTRIBUTE_ENABLE, 1);

				}
				else {
					shapeComponent->setAttribute_int(ATTRIBUTE_FILL_COLOR_RED, 0);
					shapeComponent->setAttribute_int(ATTRIBUTE_FILL_COLOR_GREEN, 128);
					shapeComponent->setAttribute_int(ATTRIBUTE_FILL_COLOR_BLUE, 128);
					//disable input component
					inputComponent->setAttribute_int(ATTRIBUTE_ENABLE, 0);

				}
				shapeComponent->update();

				return 0;
		});

		auto inputComponent_mousePressed = componentFactory.createInputComponent(AB_BUTTON_PRESSED);
		entity->addComponent(inputComponent_mousePressed);
		inputComponent_mousePressed->setAttribute_int(ATTRIBUTE_ENABLE, 0);
		inputComponent_mousePressed->setAttribute_string(ATTRIBUTE_INPUT_TYPE, INPUT_MOUSE_PRESSED);
		inputComponent_mousePressed->setAttribute_string(ATTRIBUTE_CALLBACK, AB_BUTTON_PRESSED);

		armyEngine->addInputCallback(AB_BUTTON_PRESSED, (functionEventTemplate) [] (int ID, int eventIndex) {
			auto entityManager = EntityManager::getInstance();
			auto entity = entityManager->getEntityById(ID);
			sf::Event theEvent = *EventManager::getInstance()->getEvents()[eventIndex];
			auto mouseButton = theEvent.mouseButton.button;
			if (mouseButton == sf::Mouse::Button::Left) {
				std::cout << "ERROR: callback hasn't been set" << std::endl;
				exit(0);
			}
			return 0;
		});

}

void Button::setButtonText(string text){
	buttonHUDElement.setString(text, 
		BUTTON_COLOR_R,
		BUTTON_COLOR_G,
		BUTTON_COLOR_B);
}

void Button::setButtonCallback(functionEventTemplate func) {
	//the supplied callback is supposed to be unique, so we need a way to
	// make it unique.
	// going to use the button's pointer address
	std::string keyname = std::string(AB_BUTTON_PRESSED) + std::to_string(reinterpret_cast<int>(this));

	//assign the name of our callback to the input component
	auto inputcomponent = this->getEntity()->getComponentByName(AB_BUTTON_PRESSED);
	inputcomponent->setAttribute_string(ATTRIBUTE_CALLBACK, keyname);

	//insert the input callback into our engine to register it.
	auto armyengine = ArmyEngine::getInstance();
	armyengine->addInputCallback(keyname, func);
}

void Button::hide() {
	this->buttonHUDElement.hide();
	//disable our shape component
	auto shapeComponent = this->getEntity()->getComponentByName(AB_BUTTON_SHAPE);
	shapeComponent->setAttribute_int(ATTRIBUTE_ENABLE, 0);
	shapeComponent->update();

	//disable our collision component
	auto collisionComponent = this->getEntity()->getComponentByName(AB_BUTTON_COLLISION);
	collisionComponent->setAttribute_int(ATTRIBUTE_ENABLE, 0);
	collisionComponent->update();

	//disable the input component, this is for ensuring it is disabled
	// when a callback is performed
	auto inputComponent = this->getEntity()->getComponentByName(AB_BUTTON_PRESSED);
	inputComponent->setAttribute_int(ATTRIBUTE_ENABLE, 0);
	inputComponent->update();
}

void Button::display() {
	this->buttonHUDElement.display();

	//disable our shape component
	auto shapeComponent = this->getEntity()->getComponentByName(AB_BUTTON_SHAPE);
	shapeComponent->setAttribute_int(ATTRIBUTE_ENABLE, 1);
	shapeComponent->update();

	//disable our collision component
	auto collisionComponent = this->getEntity()->getComponentByName(AB_BUTTON_COLLISION);
	collisionComponent->setAttribute_int(ATTRIBUTE_ENABLE, 1);
	collisionComponent->update();
}

void Button::setSize(float width, float height) {
	auto shapeComponent = this->getEntity()->getComponentByName(AB_BUTTON_SHAPE);
	shapeComponent->setAttribute_float(ATTRIBUTE_WIDTH, width);
	shapeComponent->setAttribute_float(ATTRIBUTE_HEIGHT, height);
	shapeComponent->update();

	auto collisionComponent = this->getEntity()->getComponentByName(AB_BUTTON_COLLISION);
	collisionComponent->setAttribute_float(ATTRIBUTE_WIDTH, width);
	collisionComponent->setAttribute_float(ATTRIBUTE_HEIGHT, height);
	collisionComponent->update();
}