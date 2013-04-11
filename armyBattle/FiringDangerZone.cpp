#include <iostream>
#include "FiringDangerZone.h"
#include "AB_Utilities.h"
#include "World.h"
#include "AE_Attributes.h"
#include "AE_Events.h"

FiringDangerZone::FiringDangerZone() :
	WorldObject(AB_FIRINGZONE, 0.0, 0.0),
	firingAngle(0.0),
	firingSpread(FIRING_MIN_SPREAD),
	bFired(false) {

		auto armyEngine = ArmyEngine::getInstance();

		auto componentFactory = ArmyEngine::getInstance()->getComponentFactory();

		//The shape component making up the firing zone
		auto shapeComponent = componentFactory.createShapeComponent(AB_FIRINGZONE_SHAPE);
		this->getEntity()->addComponent(shapeComponent);

		//shape attributes
		shapeComponent->setAttribute_string(ATTRIBUTE_SHAPE_TYPE, SHAPETYPE_POLYGON);
		shapeComponent->setAttribute_float(ATTRIBUTE_OUTLINE_THICKNESS, 2.0);
		COLOR_OUTLINE_BLUE(shapeComponent);
		COLOR_FILL_BLUE(shapeComponent);
		shapeComponent->setAttribute_int(ATTRIBUTE_FILL_COLOR_ALPHA, 155);
		shapeComponent->setAttribute_float(ATTRIBUTE_ZBUFFER, 1.0);
		shapeComponent->setAttribute_int(ATTRIBUTE_ENABLE, 0);

		//we don't define the polygons, as this is decided by the
		// update() method at the end of this constructor
		shapeComponent->update();

		//The collision component making up the firing zone
		auto collisionComponent = componentFactory.createCollisionComponent(AB_FIRINGZONE_COLLISION);
		this->getEntity()->addComponent(collisionComponent);

		//collision attributes
		collisionComponent->setAttribute_string(ATTRIBUTE_COLLISION_BOUND_TYPE, COLLISION_BOUND_POLYGON);
		collisionComponent->setAttribute_int(ATTRIBUTE_ENABLE, 0);
		collisionComponent->setAttribute_string(ATTRIBUTE_COLLISION_TAG, AB_FIRINGZONE);
		collisionComponent->setAttribute_string(ATTRIBUTE_CALLBACK, AB_FIRINGZONE_COLLISION);

		armyEngine->addCollisionCallback(collisionTagTuple(AB_FIRINGZONE, AB_DRONE), 
			(functionCollisionTemplate) [] (collisionParamTuple paramTuple) {
				int entityID1, entityID2;
				std::string compName1, compName2;
				bool bRegistered;
				std::tie(entityID1, compName1, entityID2, compName2, bRegistered) = paramTuple;

				auto world = World::getInstance();
				auto droneUnit = world->getDroneByID(entityID2);
				auto state = droneUnit->getDroneState();

				if (bRegistered) {
					if (state == EnumDroneState::IDLE_WAITING ||
						state == EnumDroneState::IDLE_FINISHED) {
							droneUnit->setDroneState(EnumDroneState::DEAD);
							//if the firing zone collides with the drone, he's dead.
							droneUnit->setUnactive();
					}
				}
				return 0;
		});

		armyEngine->addCollisionCallback(collisionTagTuple(AB_FIRINGZONE, AB_HOMEBASE), 
			(functionCollisionTemplate) [] (collisionParamTuple paramTuple) {
				int entityID1, entityID2;
				std::string compName1, compName2;
				bool bRegistered;
				std::tie(entityID1, compName1, entityID2, compName2, bRegistered) = paramTuple;

				auto world = World::getInstance();
				auto homeUnit = world->getHomebaseByID(entityID2);

				if (bRegistered) {
					homeUnit->registerHit();
				}
				return 0;
		});

		//The input component for mouse movements
		// this component determines the angle upon which the firing
		// dangerzone will be presented
		auto inputComponent_mouseMove = componentFactory.createInputComponent(AB_FIRINGZONE_INPUT_MOUSEMOVE);
		this->getEntity()->addComponent(inputComponent_mouseMove);

		//input attributes
		inputComponent_mouseMove->setAttribute_string(ATTRIBUTE_INPUT_TYPE, INPUT_MOUSE_MOVE);
		inputComponent_mouseMove->setAttribute_int(ATTRIBUTE_ENABLE, 0);
		inputComponent_mouseMove->setAttribute_string(ATTRIBUTE_CALLBACK, AB_FIRINGZONE_INPUT_MOUSEMOVE);

		//callback, the input checks the current mouse position, determines the angle, and assigns this angle
		// 
		armyEngine->addInputCallback(AB_FIRINGZONE_INPUT_MOUSEMOVE, (functionEventTemplate) [] (int ID, int eventIndex) {
			auto world = World::getInstance();

			//don't do anything if it's currently in the MENU
			if (world->viewState != EnumViewState::WORLD) return 0;

			auto entityManager = EntityManager::getInstance();
			auto entity = entityManager->getEntityById(ID);

			sf::Event theEvent = *EventManager::getInstance()->getEvents()[eventIndex];

			//the corrected position are the coordinates with respect to
			// the origin being at the location of the firingDangerZone
			auto firingPosition = world->firingDangerZone.getPosition();

			float xPosition = static_cast<float> (theEvent.mouseMove.x) - firingPosition[0];
			float yPosition = static_cast<float> (theEvent.mouseMove.y) - firingPosition[1];
			float angle;
			//grab the FiringDangerZone instance provided in the World instance,
			// and change the angle to describe it's current position
			if (xPosition < 0 && yPosition >= 0) {
				angle = PI - atanf(yPosition / -xPosition);
			}
			else if (xPosition >= 0 && yPosition >= 0) {
				angle = atanf(yPosition / xPosition);
			}
			else if (xPosition >= 0 && yPosition < 0) {
				angle = -1 * atanf(-yPosition / xPosition);
			}
			else if (xPosition < 0 && yPosition < 0) {
				angle = PI + atanf(yPosition / xPosition);
			}

			//apply the angle to our firing danger zone object
			world->firingDangerZone.setFiringAngle(angle);

			//update our firing danger zone shape and collision bounds
			world->firingDangerZone.update();

			return 0;
		});

		//input for pushing left click for firing
		auto inputComponent_mousepressed = componentFactory.createInputComponent(AB_FIRING_INPUT_MOUSEPRESSED);
		this->getEntity()->addComponent(inputComponent_mousepressed);

		//input attributes
		inputComponent_mousepressed->setAttribute_int(ATTRIBUTE_ENABLE, 0);
		inputComponent_mousepressed->setAttribute_string(ATTRIBUTE_INPUT_TYPE, INPUT_MOUSE_PRESSED);
		inputComponent_mousepressed->setAttribute_string(ATTRIBUTE_CALLBACK, AB_FIRING_INPUT_MOUSEPRESSED);

		//the input callback for pressing the button
		armyEngine->addInputCallback(AB_FIRING_INPUT_MOUSEPRESSED, (functionEventTemplate) [] (int ID, int eventIndex) {
			auto world = World::getInstance();

			//don't do anything if it's currently in the MENU
			if (world->viewState != EnumViewState::WORLD) return 0;

			auto entityManager = EntityManager::getInstance();
			auto entity = entityManager->getEntityById(ID);

			sf::Event theEvent = *EventManager::getInstance()->getEvents()[eventIndex];
			auto mouseButton = theEvent.mouseButton.button;

			if (mouseButton == sf::Mouse::Button::Left) {
				auto world = World::getInstance();
				world->firingDangerZone.fire();
			}
			return 0;
		});

		//input for pressing the keyboard keys to change the spread
		auto inputComponent_keypressed = componentFactory.createInputComponent(AB_FIRING_INPUT_KEYPRESSED);
		this->getEntity()->addComponent(inputComponent_keypressed);

		inputComponent_keypressed->setAttribute_int(ATTRIBUTE_ENABLE, 0);
		inputComponent_keypressed->setAttribute_string(ATTRIBUTE_INPUT_TYPE, INPUT_KEYBOARD_PRESSED);
		inputComponent_keypressed->setAttribute_string(ATTRIBUTE_CALLBACK, AB_FIRING_INPUT_KEYPRESSED);

		//input callback for keyboard pressed
		armyEngine->addInputCallback(AB_FIRING_INPUT_KEYPRESSED, (functionEventTemplate) [] (int ID, int eventIndex) {
			auto world = World::getInstance();

			//don't do anything if it's currently in the MENU
			if (world->viewState != EnumViewState::WORLD) return 0;

			auto entityManager = EntityManager::getInstance();
			auto entity = entityManager->getEntityById(ID);

			sf::Event theEvent = *EventManager::getInstance()->getEvents()[eventIndex];
			auto keyboardButton = theEvent.key;
			auto angleSpread = world->firingDangerZone.getFiringSpread() / PI * 180;
			if (keyboardButton.code == sf::Keyboard::Down ||
				keyboardButton.code == sf::Keyboard::S) {
					angleSpread += FIRINGZONE_ANGLE_INCREMENT;
					if (angleSpread > FIRING_MAX_SPREAD) {
						angleSpread = FIRING_MAX_SPREAD;
					}
			}
			else if (keyboardButton.code == sf::Keyboard::Up ||
				keyboardButton.code == sf::Keyboard::W) {
					angleSpread -= FIRINGZONE_ANGLE_INCREMENT;
					if (angleSpread < FIRING_MIN_SPREAD) {
						angleSpread = FIRING_MIN_SPREAD;
					}
			}

			world->firingDangerZone.setFiringSpread(angleSpread / 180 * PI);
			world->firingDangerZone.update();
			return 0;
		});

}

void FiringDangerZone::update() {
	auto entity = this->getEntity();
	//grab all of the components that are going to be modified
	auto positionComponent = entity->getComponentByName(WORLD_POSITION_COMPONENT);
	auto shapeComponent = entity->getComponentByName(AB_FIRINGZONE_SHAPE);
	auto collisionComponent = entity->getComponentByName(AB_FIRINGZONE_COLLISION);

	//first, determine the radius of our firing zone from our spread
	// and our desired max area
	float radius = sqrt(FIRING_CIRCLE_AREA / (this->getFiringSpread() * 2));

	//grab our vectors containing our polygon points
	auto shapeVector = componentFloatArrayType();

	//first, push the origin
	shapeVector.push_back(0.0); shapeVector.push_back(0.0);

	//get the angle step based on the spread
	float angleStep_shape = this->getFiringSpread()*2 / (FIRING_NUM_POLYGON_POINTS - 1);

	//form our partial circle based on this information
	float currentSpread = this->getFiringSpread();
	for (int i = 2; i < (FIRING_NUM_POLYGON_POINTS*2); i += 2) {
		shapeVector.push_back(radius * cosf(currentSpread));
		shapeVector.push_back(radius * sinf(currentSpread));
		currentSpread -= angleStep_shape;
	}

	auto currentAngle = this->getFiringAngle();
	//rotate the points about the origin and translate based on the position component
	for (int i = 0; i < shapeVector.size(); i+=2) {
		auto xPoint = shapeVector[i];
		auto yPoint = shapeVector[i+1];

		shapeVector[i] = xPoint * cosf(currentAngle) - yPoint * sinf(currentAngle);
		shapeVector[i+1] = xPoint * sinf(currentAngle) + yPoint * cosf(currentAngle);
	}

	//supply our collision and shape vectors with the updated values
	shapeComponent->setAttribute_floatArray(ATTRIBUTE_POLYGON_POINTS, shapeVector);
	collisionComponent->setAttribute_floatArray(ATTRIBUTE_POLYGON_POINTS, shapeVector);

	//update our components
	collisionComponent->update();
	shapeComponent->update();
}

void FiringDangerZone::display() {
	auto entity = this->getEntity();

	//grab all of the components that are going to be modified
	auto shapeComponent = entity->getComponentByName(AB_FIRINGZONE_SHAPE);
	auto inputComponent_mouseMove = entity->getComponentByName(AB_FIRINGZONE_INPUT_MOUSEMOVE);
	auto inputComponent_mousePressed = entity->getComponentByName(AB_FIRING_INPUT_MOUSEPRESSED);
	auto inputComponent_buttonPressed = entity->getComponentByName(AB_FIRING_INPUT_KEYPRESSED);
	//auto collisionComponent = entity->getComponentByName(AB_FIRINGZONE_COLLISION);

	//enable shape
	shapeComponent->setAttribute_int(ATTRIBUTE_ENABLE, 1);

	//enable our inputs
	inputComponent_mouseMove->setAttribute_int(ATTRIBUTE_ENABLE, 1);
	inputComponent_mousePressed->setAttribute_int(ATTRIBUTE_ENABLE, 1);
	inputComponent_buttonPressed->setAttribute_int(ATTRIBUTE_ENABLE, 1);
}

void FiringDangerZone::hide() {
	auto entity = this->getEntity();

	//hide the the firing danger zone, and ensure the collision bounds are also disabled
	auto shapeComponent = entity->getComponentByName(AB_FIRINGZONE_SHAPE);
	auto inputComponent_mouseMove = entity->getComponentByName(AB_FIRINGZONE_INPUT_MOUSEMOVE);
	auto inputComponent_mousePressed = entity->getComponentByName(AB_FIRING_INPUT_MOUSEPRESSED);
	auto inputComponent_buttonPressed = entity->getComponentByName(AB_FIRING_INPUT_KEYPRESSED);
	auto collisionComponent = entity->getComponentByName(AB_FIRINGZONE_COLLISION);

	//disable the shape
	shapeComponent->setAttribute_int(ATTRIBUTE_ENABLE, 0);

	//disable the inputs
	inputComponent_mouseMove->setAttribute_int(ATTRIBUTE_ENABLE, 0);
	inputComponent_mousePressed->setAttribute_int(ATTRIBUTE_ENABLE, 0);
	inputComponent_buttonPressed->setAttribute_int(ATTRIBUTE_ENABLE, 0);

	//disable the collision 
	collisionComponent->setAttribute_int(ATTRIBUTE_ENABLE, 0);
}

void FiringDangerZone::fire() {
	this->setFired();
	auto entity = this->getEntity();

	auto shapeComponent = entity->getComponentByName(AB_FIRINGZONE_SHAPE);
	auto collisionComponent = entity->getComponentByName(AB_FIRINGZONE_COLLISION);
	auto inputComponent_mousePressed = entity->getComponentByName(AB_FIRING_INPUT_MOUSEPRESSED);
	auto inputComponent_mouseMove = entity->getComponentByName(AB_FIRINGZONE_INPUT_MOUSEMOVE);
	auto inputComponent_keypressed = entity->getComponentByName(AB_FIRING_INPUT_KEYPRESSED);

	//enable the collision component
	shapeComponent->setAttribute_int(ATTRIBUTE_ENABLE, 0);
	shapeComponent->update();
	collisionComponent->setAttribute_int(ATTRIBUTE_ENABLE, 1);
	collisionComponent->update();

	//disable all of our inputs
	inputComponent_mousePressed->setAttribute_int(ATTRIBUTE_ENABLE, 0);
	inputComponent_mouseMove->setAttribute_int(ATTRIBUTE_ENABLE, 0);
	inputComponent_keypressed->setAttribute_int(ATTRIBUTE_ENABLE, 0);

}

float FiringDangerZone::getFiringAngle() {
	return (this->firingAngle / 180. * PI);
}

void FiringDangerZone::setFiringAngle(float angle) {
	this->firingAngle = angle / PI * 180;
}

float FiringDangerZone::getFiringSpread() {
	return (this->firingSpread / 180. * PI);
}

void FiringDangerZone::setFiringSpread(float angle) {
	this->firingSpread = angle / PI * 180;
}

bool FiringDangerZone::hasFired() {
	return this->bFired;
}

void FiringDangerZone::setFired() {
	this->bFired = true;
}

void FiringDangerZone::clearFired() {
	this->bFired = false;
}