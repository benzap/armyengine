#include <iostream>
#include <cmath>
#include <algorithm>

#include "AE_Attributes.h"
#include "MouseCursor.h"
#include "DroneUnit.h"
#include "AB_Utilities.h"
#include "AB_Assets.h"
#include "World.h"

DroneUnit::DroneUnit(EnumTeam teamID, float xPosition, float yPosition) :
	Unit(AB_DRONE, teamID),
	state(EnumDroneState::IDLE_WAITING),
	hasFired(false),
	isSelected(false),
	shootingAngle(0.f),
	shootingSpread(0.f),
	movementPoints(DEFAULT_MOVEMENT_POINTS),
	numSensedUnitsWithin40(0) {
		//set the droneID to the entity ID,
		// this allows for a great convenience when
		// trying to find unique drones
		this->droneID = this->getEntity()->getID();
		this->setPosition(xPosition, yPosition);

		auto armyEngine = ArmyEngine::getInstance();

		//grabbing the component factory
		auto componentFactory = armyEngine->getComponentFactory();

		//adding our spriteComponent
		auto spriteComponent = componentFactory.createSpriteComponent(AB_DRONE_SPRITE);
		this->getEntity()->addComponent(spriteComponent);

		//the sprite attributes
		if (this->getTeamID() == EnumTeam::RED) {
			spriteComponent->setAttribute_string(ATTRIBUTE_SPRITE_NAME, AB_SPRITE_RED_DRONE_IDLE);
		}
		else {
			spriteComponent->setAttribute_string(ATTRIBUTE_SPRITE_NAME, AB_SPRITE_BLUE_DRONE_IDLE);
		}
		//the sprite is 100 pixels by 100 pixels, this sets the size of our sprite to be
		// 15 pixels by 15 pixels
		spriteComponent->setAttribute_float(ATTRIBUTE_SCALE_X, 0.15);
		spriteComponent->setAttribute_float(ATTRIBUTE_SCALE_Y, 0.15);
		spriteComponent->setAttribute_float(ATTRIBUTE_ORIGIN_X, 50);
		spriteComponent->setAttribute_float(ATTRIBUTE_ORIGIN_Y, 50);
		spriteComponent->setAttribute_int(ATTRIBUTE_ENABLE, 1);
		spriteComponent->setAttribute_float(ATTRIBUTE_ZBUFFER, 0.01);
		spriteComponent->update();

		//add shape component to represent the drone
		auto shapeComponent = componentFactory.createShapeComponent(AB_DRONE_SHAPE_BASE);
		this->getEntity()->addComponent(shapeComponent);

		//Shape Component Attributes
		shapeComponent->setAttribute_int(ATTRIBUTE_ENABLE, 0);
		shapeComponent->setAttribute_string(ATTRIBUTE_SHAPE_TYPE, SHAPETYPE_RECTANGLE);
		shapeComponent->setAttribute_float(ATTRIBUTE_WIDTH, DEFAULT_UNIT_WIDTH);
		shapeComponent->setAttribute_float(ATTRIBUTE_HEIGHT, DEFAULT_UNIT_HEIGHT);

		//yellow outline
		COLOR_OUTLINE_GREEN(shapeComponent); //macro
		shapeComponent->setAttribute_int(ATTRIBUTE_OUTLINE_COLOR_ALPHA, 255);
		shapeComponent->setAttribute_float(ATTRIBUTE_OUTLINE_THICKNESS, DRONE_OUTLINE_THICKNESS);

		//set the drone color based on the teamID
		if (this->getTeamID() == EnumTeam::RED) {
			COLOR_FILL_RED(shapeComponent); //macro
		}
		else if (this->getTeamID() == EnumTeam::BLUE) {
			COLOR_FILL_BLUE(shapeComponent); //macro
		}

		shapeComponent->setAttribute_float(ATTRIBUTE_OFFSET_X, 0.0);
		shapeComponent->setAttribute_float(ATTRIBUTE_OFFSET_Y, 0.0);
		shapeComponent->setAttribute_float(ATTRIBUTE_ZBUFFER, 0.0);
		shapeComponent->update();

		//add collision component to represent the extents of its bounds for getting
		// hit or selected
		auto collisionComponent = componentFactory.createCollisionComponent(AB_DRONE_COLLISION);
		this->getEntity()->addComponent(collisionComponent);

		//Collision Component Attributes
		collisionComponent->setAttribute_int(ATTRIBUTE_ENABLE, 1);
		collisionComponent->setAttribute_string(ATTRIBUTE_COLLISION_BOUND_TYPE, COLLISION_BOUND_CIRCLE);
		collisionComponent->setAttribute_float(ATTRIBUTE_WIDTH, DEFAULT_UNIT_WIDTH+5);
		collisionComponent->setAttribute_float(ATTRIBUTE_HEIGHT, DEFAULT_UNIT_HEIGHT+5);
		collisionComponent->setAttribute_float(ATTRIBUTE_RADIUS, 7.5);
		collisionComponent->setAttribute_float(ATTRIBUTE_OFFSET_X, -7.5);
		collisionComponent->setAttribute_float(ATTRIBUTE_OFFSET_Y, -7.5);
		collisionComponent->setAttribute_string(ATTRIBUTE_COLLISION_TAG, AB_DRONE);	
		collisionComponent->update();

		//adding a second shapecomponent to represent the drone's movement radius
		// this should be enabled when the drone is going to be moved
		auto shapeComponent_move_radius = componentFactory.createShapeComponent(AB_DRONE_SHAPE_MOVEMENTRADIUS);
		this->getEntity()->addComponent(shapeComponent_move_radius);
		shapeComponent_move_radius->setAttribute_int(ATTRIBUTE_ENABLE, 0);
		//set the offset, so that it centers on the drone
		shapeComponent_move_radius->setAttribute_float(ATTRIBUTE_OFFSET_X,
			-this->getMovementPoints()+DRONE_OUTLINE_THICKNESS*2);
		shapeComponent_move_radius->setAttribute_float(ATTRIBUTE_OFFSET_Y,
			-this->getMovementPoints()+DRONE_OUTLINE_THICKNESS*2);

		shapeComponent_move_radius->setAttribute_string(ATTRIBUTE_SHAPE_TYPE, SHAPETYPE_CIRCLE);
		shapeComponent_move_radius->setAttribute_float(ATTRIBUTE_RADIUS, this->getMovementPoints());
		shapeComponent_move_radius->setAttribute_float(ATTRIBUTE_ZBUFFER, -0.1);
		COLOR_OUTLINE_BLUE(shapeComponent_move_radius);
		shapeComponent_move_radius->setAttribute_int(ATTRIBUTE_OUTLINE_COLOR_ALPHA, 50);
		shapeComponent_move_radius->setAttribute_float(ATTRIBUTE_OUTLINE_THICKNESS, 
			AB_DRONE_SHAPE_MOVEMENTRADIUS_OUTLINETHICKNESS);
		COLOR_FILL_BLUE(shapeComponent_move_radius);
		shapeComponent_move_radius->setAttribute_int(ATTRIBUTE_FILL_COLOR_ALPHA, 100);
		shapeComponent_move_radius->update();

		//shapeComponent to show the sensing radius of the current drone
		auto shapeComponent_sense_radius = componentFactory.createShapeComponent(AB_DRONE_SHAPE_SENSERADIUS);
		this->getEntity()->addComponent(shapeComponent_sense_radius);
		shapeComponent_sense_radius->setAttribute_int(ATTRIBUTE_ENABLE, 0);
		//set the offset, so that it centers on the drone
		shapeComponent_sense_radius->setAttribute_float(ATTRIBUTE_OFFSET_X,
			-(AB_DRONE_SENSE_RADIUS_40 - AB_DRONE_SENSE_RADIUS)+DRONE_OUTLINE_THICKNESS*2);
		shapeComponent_sense_radius->setAttribute_float(ATTRIBUTE_OFFSET_Y,
			-(AB_DRONE_SENSE_RADIUS_40 - AB_DRONE_SENSE_RADIUS)+DRONE_OUTLINE_THICKNESS*2);

		shapeComponent_sense_radius->setAttribute_string(ATTRIBUTE_SHAPE_TYPE, SHAPETYPE_CIRCLE);
		shapeComponent_sense_radius->setAttribute_float(ATTRIBUTE_RADIUS, AB_DRONE_SENSE_RADIUS);
		shapeComponent_sense_radius->setAttribute_float(ATTRIBUTE_ZBUFFER, -0.1);
		COLOR_OUTLINE_BLUE(shapeComponent_sense_radius);
		shapeComponent_sense_radius->setAttribute_int(ATTRIBUTE_OUTLINE_COLOR_ALPHA, 50);
		shapeComponent_sense_radius->setAttribute_float(ATTRIBUTE_OUTLINE_THICKNESS, 
			AB_DRONE_SENSE_RADIUS_40 - AB_DRONE_SENSE_RADIUS);
		COLOR_FILL_BLUE(shapeComponent_sense_radius);
		shapeComponent_sense_radius->setAttribute_int(ATTRIBUTE_FILL_COLOR_ALPHA, 100);
		shapeComponent_sense_radius->update();

		//shapeComponent to show the broadcasting radius of the current drone
		auto shapeComponent_broadcast_radius = componentFactory.createShapeComponent(AB_DRONE_SHAPE_BROADCASTRADIUS);
		this->getEntity()->addComponent(shapeComponent_broadcast_radius);
		shapeComponent_broadcast_radius->setAttribute_int(ATTRIBUTE_ENABLE, 0);
		//set the offset, so that it centers on the drone
		shapeComponent_broadcast_radius->setAttribute_float(ATTRIBUTE_OFFSET_X,
			-(AB_DRONE_BROADCAST_RADIUS)+DRONE_OUTLINE_THICKNESS*2);
		shapeComponent_broadcast_radius->setAttribute_float(ATTRIBUTE_OFFSET_Y,
			-(AB_DRONE_BROADCAST_RADIUS)+DRONE_OUTLINE_THICKNESS*2);

		shapeComponent_broadcast_radius->setAttribute_string(ATTRIBUTE_SHAPE_TYPE, SHAPETYPE_CIRCLE);
		shapeComponent_broadcast_radius->setAttribute_float(ATTRIBUTE_RADIUS, AB_DRONE_BROADCAST_RADIUS);
		shapeComponent_broadcast_radius->setAttribute_float(ATTRIBUTE_ZBUFFER, -0.1);
		shapeComponent_broadcast_radius->setAttribute_float(ATTRIBUTE_OUTLINE_THICKNESS, 0);
		COLOR_FILL_BLUE(shapeComponent_broadcast_radius);
		shapeComponent_broadcast_radius->setAttribute_int(ATTRIBUTE_FILL_COLOR_ALPHA, 100);
		shapeComponent_broadcast_radius->update();

		//*****************************
		//**** COLLISION CALLBACKS ****
		//*****************************

		//Collision callback trigger for any collisions between the Drone and the Mouse Cursor
		armyEngine->addCollisionCallback(collisionTagTuple(AB_DRONE, AB_MOUSE), 
			(functionCollisionTemplate) [] (collisionParamTuple paramTuple) {
				int entityID1, entityID2;
				std::string compName1, compName2;
				bool bRegistered;
				std::tie(entityID1, compName1, entityID2, compName2, bRegistered) = paramTuple;

				auto world = World::getInstance();

				//don't do anything if it's currently in the MENU
				if (world->viewState != EnumViewState::WORLD) return 0;

				auto droneUnit = world->getDroneByID(entityID1);
				auto state = droneUnit->getDroneState();

				auto shapeComponent_sense_radius = droneUnit->getEntity()->getComponentByName(AB_DRONE_SHAPE_SENSERADIUS);
				auto msg = std::string();

				if (bRegistered) {
					switch(state) {
					case EnumDroneState::IDLE_WAITING:
					case EnumDroneState::SENSING:
					case EnumDroneState::BROADCASTING:
					case EnumDroneState::IDLE_FINISHED:
						droneUnit->setSensingArea();

						break;
					case EnumDroneState::ATTACKING:
					case EnumDroneState::MOVING:
						break;
					} //switch(state) {
				} //END if (bRegistered) {
				else {
					switch(state) {
					case EnumDroneState::IDLE_WAITING:
					case EnumDroneState::SENSING:
					case EnumDroneState::BROADCASTING:
					case EnumDroneState::IDLE_FINISHED:
						if(state != EnumDroneState::SENSING){
							msg = "";
							shapeComponent_sense_radius->setAttribute_int(ATTRIBUTE_ENABLE, 0);
							world->statusBar.setmostRecentAction(msg, EnumColor::WARNING);
							break;
						}
					case EnumDroneState::ATTACKING:
					case EnumDroneState::MOVING:
						break;
					} //switch(state) {
				} //END else { (!bRegistered)
				return 0;
		});

		//Collision callback trigger for any collisions between the Drone and the Firing Zone
		armyEngine->addCollisionCallback(collisionTagTuple(AB_DRONE, AB_FIRINGZONE), 
			(functionCollisionTemplate) [] (collisionParamTuple paramTuple) {
				int entityID1, entityID2;
				std::string compName1, compName2;
				bool bRegistered;
				std::tie(entityID1, compName1, entityID2, compName2, bRegistered) = paramTuple;

				auto world = World::getInstance();

				//don't do anything if it's currently in the MENU
				if (world->viewState != EnumViewState::WORLD) return 0;

				auto droneUnit = world->getDroneByID(entityID1);
				auto state = droneUnit->getDroneState();

				if (bRegistered) {
					if (state == EnumDroneState::IDLE_WAITING) {
						droneUnit->setDroneState(EnumDroneState::DEAD);
						//if the firing zone collides with the drone, he's dead.
						droneUnit->setUnactive();
						droneUnit->lastWordsMessage(world->getCurrentDroneID());
					}
					else if (state == EnumDroneState::MOVING) {

					}
					else if (state == EnumDroneState::ATTACKING) {

					}
					else if (state == EnumDroneState::SENSING) {

					}
					else if (state == EnumDroneState::BROADCASTING) {

					}
					else if (state == EnumDroneState::IDLE_FINISHED) {
						droneUnit->setDroneState(EnumDroneState::DEAD);
						//if the firing zone collides with the drone, it's dead.
						droneUnit->setUnactive();
					}
				} //END if (bRegistered) {
				else { //repeat the registered calls, no real reason for this
					if (state == EnumDroneState::IDLE_WAITING) {

					}
					else if (state == EnumDroneState::MOVING) {

					}
					else if (state == EnumDroneState::ATTACKING) {

					}
					else if (state == EnumDroneState::SENSING) {

					}
					else if (state == EnumDroneState::BROADCASTING) {

					}
					else if (state == EnumDroneState::IDLE_FINISHED) {

					}
				} //END else { (!bRegistered)
				return 0;
		});


		//Collision callback trigger for any collisions between the Drone and the other drones
		armyEngine->addCollisionCallback(collisionTagTuple(AB_DRONE, AB_DRONE), 
			(functionCollisionTemplate) [] (collisionParamTuple paramTuple) {
				int entityID1, entityID2;
				std::string compName1, compName2;
				bool bRegistered;
				std::tie(entityID1, compName1, entityID2, compName2, bRegistered) = paramTuple;

				auto world = World::getInstance();

				//don't do anything if it's currently in the MENU
				if (world->viewState != EnumViewState::WORLD) return 0;

				auto droneUnit = world->getDroneByID(entityID1);
				auto state = droneUnit->getDroneState();

				if (bRegistered) {
					if (state == EnumDroneState::IDLE_WAITING) {

					}
					else if (state == EnumDroneState::MOVING) {
						droneUnit->setCollided();
					}
					else if (state == EnumDroneState::ATTACKING) {

					}
					else if (state == EnumDroneState::SENSING) {

					}
					else if (state == EnumDroneState::BROADCASTING) {

					}
					else if (state == EnumDroneState::IDLE_FINISHED) {

					}
				} //END if (bRegistered) {
				else {
					if (state == EnumDroneState::IDLE_WAITING) {

					}
					else if (state == EnumDroneState::MOVING) {
						droneUnit->clearCollision();
					}
					else if (state == EnumDroneState::ATTACKING) {

					}
					else if (state == EnumDroneState::SENSING) {

					}
					else if (state == EnumDroneState::BROADCASTING) {

					}
					else if (state == EnumDroneState::IDLE_FINISHED) {

					}
				} //END else { (!bRegistered)
				return 0;
		});

		//Collision callback trigger for any collisions between the Drone and the HomeBase unit
		armyEngine->addCollisionCallback(collisionTagTuple(AB_DRONE, AB_HOMEBASE), 
			(functionCollisionTemplate) [] (collisionParamTuple paramTuple) {
				int entityID1, entityID2;
				std::string compName1, compName2;
				bool bRegistered;
				std::tie(entityID1, compName1, entityID2, compName2, bRegistered) = paramTuple;

				auto world = World::getInstance();

				//don't do anything if it's currently in the MENU
				if (world->viewState != EnumViewState::WORLD) return 0;

				auto droneUnit = world->getDroneByID(entityID1);
				auto state = droneUnit->getDroneState();

				//HACK - this should be fixed
				//if (droneUnit == nullptr) return 0;

				if (bRegistered) {
					if (state == EnumDroneState::IDLE_WAITING) {

					}
					else if (state == EnumDroneState::MOVING) {
						droneUnit->setCollided();
					}
					else if (state == EnumDroneState::ATTACKING) {

					}
					else if (state == EnumDroneState::SENSING) {

					}
					else if (state == EnumDroneState::BROADCASTING) {

					}
					else if (state == EnumDroneState::IDLE_FINISHED) {

					}
				} //END if (bRegistered) {
				else {
					if (state == EnumDroneState::IDLE_WAITING) {

					}
					else if (state == EnumDroneState::MOVING) {
						droneUnit->clearCollision();
					}
					else if (state == EnumDroneState::ATTACKING) {

					}
					else if (state == EnumDroneState::SENSING) {

					}
					else if (state == EnumDroneState::BROADCASTING) {

					}
					else if (state == EnumDroneState::IDLE_FINISHED) {

					}
				} //END else { (!bRegistered)
				return 0;
		});

		//Collision callback trigger for any collisions between the Drone and the out of bounds area (top part of screen)
		armyEngine->addCollisionCallback(collisionTagTuple(AB_DRONE, AB_WORLD_OUT_OF_BOUNDS), 
			(functionCollisionTemplate) [] (collisionParamTuple paramTuple) {
				int entityID1, entityID2;
				std::string compName1, compName2;
				bool bRegistered;
				std::tie(entityID1, compName1, entityID2, compName2, bRegistered) = paramTuple;

				auto world = World::getInstance();

				//don't do anything if it's currently in the MENU
				if (world->viewState != EnumViewState::WORLD) return 0;

				auto droneUnit = world->getDroneByID(entityID1);
				auto state = droneUnit->getDroneState();

				if (bRegistered) {
					if (state == EnumDroneState::IDLE_WAITING) {

					}
					else if (state == EnumDroneState::MOVING) {
						droneUnit->setCollided();
					}
					else if (state == EnumDroneState::ATTACKING) {

					}
					else if (state == EnumDroneState::SENSING) {

					}
					else if (state == EnumDroneState::BROADCASTING) {

					}
					else if (state == EnumDroneState::IDLE_FINISHED) {

					}
				} //END if (bRegistered) {
				else {
					if (state == EnumDroneState::IDLE_WAITING) {

					}
					else if (state == EnumDroneState::MOVING) {
						droneUnit->clearCollision();
					}
					else if (state == EnumDroneState::ATTACKING) {

					}
					else if (state == EnumDroneState::SENSING) {

					}
					else if (state == EnumDroneState::BROADCASTING) {

					}
					else if (state == EnumDroneState::IDLE_FINISHED) {

					}
				} //END else { (!bRegistered)
				return 0;
		});

		//***********************
		//*** INPUT CALLBACKS ***
		//***********************

		//callback for mouse moves
		// the operation of this call is based on the current state of the drone
		// for moving, this callback will perform an offset on the shape component 
		// based on the current position of the mouse
		auto inputComponent_mouseMove = componentFactory.createInputComponent(AB_DRONE_INPUT_MOUSE_MOVE);
		this->getEntity()->addComponent(inputComponent_mouseMove);
		inputComponent_mouseMove->setAttribute_int(ATTRIBUTE_ENABLE, 0);
		inputComponent_mouseMove->setAttribute_string(ATTRIBUTE_INPUT_TYPE, INPUT_MOUSE_MOVE);
		inputComponent_mouseMove->setAttribute_string(ATTRIBUTE_CALLBACK, AB_DRONE_INPUT_MOUSE_MOVE);
		armyEngine->addInputCallback(AB_DRONE_INPUT_MOUSE_MOVE, (functionEventTemplate) [] (int ID, int eventIndex) {
			auto entityManager = EntityManager::getInstance();
			auto entity = entityManager->getEntityById(ID);

			auto world = World::getInstance();

			//don't do anything if it's currently in the MENU
			if (world->viewState != EnumViewState::WORLD) return 0;

			auto droneUnit = world->getDroneByID(ID);
			auto state = droneUnit->getDroneState();

			sf::Event theEvent = *EventManager::getInstance()->getEvents()[eventIndex];
			float xMousePosition = static_cast<float> (theEvent.mouseMove.x);
			float yMousePosition = static_cast<float> (theEvent.mouseMove.y);

			if (state == EnumDroneState::IDLE_WAITING) {

			}
			else if (state == EnumDroneState::MOVING) {
				//apply the position of the mouse to the position of the entity
				auto spriteComponent = entity->getComponentByName(AB_DRONE_SPRITE);
				auto shapeComponent = entity->getComponentByName(AB_DRONE_SHAPE_BASE);
				auto collisionComponent = entity->getComponentByName(AB_DRONE_COLLISION);
				auto positionComponent = entity->getComponentByName(WORLD_POSITION_COMPONENT);
				//get the shape's current position
				float xDronePosition = positionComponent->getAttribute_float(ATTRIBUTE_POSITION_X);
				float yDronePosition = positionComponent->getAttribute_float(ATTRIBUTE_POSITION_Y);

				//get the difference in distances for each component
				float resultX = xMousePosition - xDronePosition;
				float resultY = yMousePosition - yDronePosition;

				//if the mouse is within the extents of how far the drone can move
				// perform the drone movement by adjusting the offset
				// otherwise, the drone is not moved. this movement is not permanent, and is just
				// a visual aid
				float pyth_result = resultX * resultX + resultY * resultY;
				float movementPoints = droneUnit->getMovementPoints() * droneUnit->getMovementPoints();
				float movementPoints_bound = (droneUnit->getMovementPoints() + AB_DRONE_SHAPE_MOVEMENTRADIUS_OUTLINETHICKNESS*2) *
					(droneUnit->getMovementPoints() + AB_DRONE_SHAPE_MOVEMENTRADIUS_OUTLINETHICKNESS*2);
				if (pyth_result <= movementPoints) {
					shapeComponent->setAttribute_float(ATTRIBUTE_OFFSET_X, resultX);
					shapeComponent->setAttribute_float(ATTRIBUTE_OFFSET_Y, resultY);
					spriteComponent->setAttribute_float(ATTRIBUTE_OFFSET_X, resultX);
					spriteComponent->setAttribute_float(ATTRIBUTE_OFFSET_Y, resultY);
					collisionComponent->setAttribute_float(ATTRIBUTE_OFFSET_X, resultX);
					collisionComponent->setAttribute_float(ATTRIBUTE_OFFSET_Y, resultY);
					world->mouseCursor.disable();

				}
				//take the outline thickness into account as a bound for the offset
				else if (pyth_result <= movementPoints_bound) {
					//get the angle
					float angle;
					if (resultX < 0 && resultY >= 0) {
						angle = PI - atanf(resultY / -resultX);
					}
					else if (resultX >= 0 && resultY >= 0) {
						angle = atanf(resultY / resultX);
					}
					else if (resultX >= 0 && resultY < 0) {
						angle = -1 * atanf(-resultY / resultX);
					}
					else if (resultX < 0 && resultY < 0) {
						angle = PI + atanf(resultY / resultX);
					}
					//form our position based on the movement points
					//and our current angle to the cursor
					auto newResultX = droneUnit->getMovementPoints() * cosf(angle);
					auto newResultY = droneUnit->getMovementPoints() * sinf(angle);

					//place the result on our shape and collision components
					shapeComponent->setAttribute_float(ATTRIBUTE_OFFSET_X, newResultX);
					shapeComponent->setAttribute_float(ATTRIBUTE_OFFSET_Y, newResultY);
					spriteComponent->setAttribute_float(ATTRIBUTE_OFFSET_X, newResultX);
					spriteComponent->setAttribute_float(ATTRIBUTE_OFFSET_Y, newResultY);
					collisionComponent->setAttribute_float(ATTRIBUTE_OFFSET_X, newResultX);
					collisionComponent->setAttribute_float(ATTRIBUTE_OFFSET_Y, newResultY);
					world->mouseCursor.disable();
				}
				else {
					shapeComponent->setAttribute_float(ATTRIBUTE_OFFSET_X, 0);
					shapeComponent->setAttribute_float(ATTRIBUTE_OFFSET_Y, 0);
					spriteComponent->setAttribute_float(ATTRIBUTE_OFFSET_X, 0);
					spriteComponent->setAttribute_float(ATTRIBUTE_OFFSET_Y, 0);
					collisionComponent->setAttribute_float(ATTRIBUTE_OFFSET_X, 0);
					collisionComponent->setAttribute_float(ATTRIBUTE_OFFSET_Y, 0);
					world->mouseCursor.setIdle();
				}

			}
			else if (state == EnumDroneState::ATTACKING) {

			}
			else if (state == EnumDroneState::SENSING) {

			}
			else if (state == EnumDroneState::BROADCASTING) {

			}
			else if (state == EnumDroneState::IDLE_FINISHED) {

			}

			return 0;
		});

		//callback for mouse clicks.
		// the operation of this callback is based on the current state of the drone
		// for moving, this callback will perform the move for the drone that is currently moving
		auto inputComponent_mousePressed = componentFactory.createInputComponent(AB_DRONE_INPUT_MOUSE_PRESSED);
		this->getEntity()->addComponent(inputComponent_mousePressed);
		inputComponent_mousePressed->setAttribute_int(ATTRIBUTE_ENABLE, 0);
		inputComponent_mousePressed->setAttribute_string(ATTRIBUTE_INPUT_TYPE, INPUT_MOUSE_PRESSED);
		inputComponent_mousePressed->setAttribute_string(ATTRIBUTE_CALLBACK, AB_DRONE_INPUT_MOUSE_PRESSED);

		armyEngine->addInputCallback(AB_DRONE_INPUT_MOUSE_PRESSED, (functionEventTemplate) [] (int ID, int eventIndex) {
			auto entityManager = EntityManager::getInstance();
			auto entity = entityManager->getEntityById(ID);

			auto world = World::getInstance();

			//don't do anything if it's currently in the MENU
			if (world->viewState != EnumViewState::WORLD) return 0;

			auto droneUnit = world->getDroneByID(ID);
			auto state = droneUnit->getDroneState();

			sf::Event theEvent = *EventManager::getInstance()->getEvents()[eventIndex];
			auto mouseButton = theEvent.mouseButton.button;

			if (state == EnumDroneState::IDLE_WAITING) {

			}
			else if (state == EnumDroneState::MOVING) {
				if (!droneUnit->hasCollided() && mouseButton == sf::Mouse::Button::Left) {

					auto shapeComponent = entity->getComponentByName(AB_DRONE_SHAPE_BASE);
					auto spriteComponent = entity->getComponentByName(AB_DRONE_SPRITE);
					auto collisionComponent = entity->getComponentByName(AB_DRONE_COLLISION);
					auto positionComponent = entity->getComponentByName(WORLD_POSITION_COMPONENT);
					//if the drone unit hasn't collided with anything,
					// we can perform the final move of our drone
					float movementPoints = droneUnit->getMovementPoints();
					//first, the new position can be determined by the shape's offset
					float xOffset = shapeComponent->getAttribute_float(ATTRIBUTE_OFFSET_X);
					float yOffset = shapeComponent->getAttribute_float(ATTRIBUTE_OFFSET_Y);
					float xPosition = positionComponent->getAttribute_float(ATTRIBUTE_POSITION_X);
					float yPosition = positionComponent->getAttribute_float(ATTRIBUTE_POSITION_Y);

					//change the position
					positionComponent->setAttribute_float(ATTRIBUTE_POSITION_X, xPosition + xOffset);
					positionComponent->setAttribute_float(ATTRIBUTE_POSITION_Y, yPosition + yOffset);

					//reset our offest for both the collision and the shape components
					shapeComponent->setAttribute_float(ATTRIBUTE_OFFSET_X, 0.0);
					shapeComponent->setAttribute_float(ATTRIBUTE_OFFSET_Y, 0.0);
					spriteComponent->setAttribute_float(ATTRIBUTE_OFFSET_X, 0.0);
					spriteComponent->setAttribute_float(ATTRIBUTE_OFFSET_Y, 0.0);
					collisionComponent->setAttribute_float(ATTRIBUTE_OFFSET_X, 0.0);
					collisionComponent->setAttribute_float(ATTRIBUTE_OFFSET_Y, 0.0);

					shapeComponent->update();

					//reduce our movement points
					movementPoints -= sqrtf(xOffset*xOffset + yOffset*yOffset);

					if (movementPoints < DEFAULT_MOVEMENT_THRESHOLD) {
						//we've met the movement threshold, so we continue on to the next state
						// for this drone
						droneUnit->setDroneState(EnumDroneState::ATTACKING);
						droneUnit->setMovementPoints(DEFAULT_MOVEMENT_POINTS);
					}
					else {
						//else, we perform setMoving again
						droneUnit->setMovementPoints(movementPoints);
						droneUnit->setMoving();
					}
				}
				else {
					std::cout << "Has Collided" << std::endl;
				}
			}
			else if (state == EnumDroneState::ATTACKING) {

			}
			else if (state == EnumDroneState::SENSING) {

			}
			else if (state == EnumDroneState::BROADCASTING) {

			}
			else if (state == EnumDroneState::IDLE_FINISHED) {

			}
			//apply the position of the mouse to the position of the entity
			auto shapeComponent = entity->getComponentByName(AB_DRONE_SHAPE_BASE);

			return 0;
		});

		auto inputComponent_keyPressed = componentFactory.createInputComponent(AB_DRONE_INPUT_KEYBOARD_PRESSED);
		this->getEntity()->addComponent(inputComponent_keyPressed);

		//input attributes
		inputComponent_keyPressed->setAttribute_string(ATTRIBUTE_INPUT_TYPE, INPUT_KEYBOARD_PRESSED);
		inputComponent_keyPressed->setAttribute_string(ATTRIBUTE_CALLBACK, AB_DRONE_INPUT_KEYBOARD_PRESSED);

		armyEngine->addInputCallback(AB_DRONE_INPUT_KEYBOARD_PRESSED, (functionEventTemplate) [] (int ID, int eventIndex) {
			auto entityManager = EntityManager::getInstance();
			auto entity = entityManager->getEntityById(ID);

			auto world = World::getInstance();

			//don't do anything if it's currently in the MENU
			if (world->viewState != EnumViewState::WORLD) return 0;

			auto droneUnit = world->getDroneByID(ID);
			auto state = droneUnit->getDroneState();

			sf::Event theEvent = *EventManager::getInstance()->getEvents()[eventIndex];

			auto keypressed = theEvent.key;

			if (state == EnumDroneState::IDLE_WAITING) {

			}
			else if (state == EnumDroneState::MOVING) {

			}
			else if (state == EnumDroneState::ATTACKING) {
				if (keypressed.code == sf::Keyboard::Return){
					droneUnit->setDroneState(EnumDroneState::SENSING);
					world->firingDangerZone.hide();
				}
			}
			else if (state == EnumDroneState::SENSING) {
				if (keypressed.code == sf::Keyboard::Return) {
					droneUnit->setDroneState(EnumDroneState::BROADCASTING);
					droneUnit->setDoneSensing();
				}
			}
			else if (state == EnumDroneState::BROADCASTING) {
				if (keypressed.code == sf::Keyboard::Return) {
					droneUnit->setDroneState(EnumDroneState::IDLE_FINISHED);
					droneUnit->setDoneBroadcasting();
				}
			}
			else if (state == EnumDroneState::IDLE_FINISHED) {

			}

			return 0;
		});


}

void DroneUnit::movePosition(EnumMove theMove, float distance) {
	//grab the current position
	auto thePosition = this->getPosition();

	//based on the enumeration, assign distance
	if (theMove == EnumMove::UP) {
		thePosition[1] += distance;
	}
	else if (theMove == EnumMove::DOWN) {
		thePosition[1] -= distance;
	}
	else if (theMove == EnumMove::LEFT) {
		thePosition[0] += distance;
	}
	else if (theMove == EnumMove::RIGHT) {
		thePosition[0] -= distance;
	}
	//set the new position
	this->setPosition(thePosition[0], thePosition[1]);
}

void DroneUnit::senseSurroundingUnits() {
	//Clear the sensedUnits from previous call
	this->sensedUnits.clear();
	this->numSensedUnitsWithin40 = 0;
	//Grab the parent class
	auto world = World::getInstance();
	//Get the drone units from the parent class
	droneListType droneUnits;
	droneListType allDroneUnits;
	allDroneUnits = world->getDroneUnits(EnumTeam::BOTH);
	if (this->getTeamID() == EnumTeam::RED) {
		droneUnits = world->getDroneUnits(EnumTeam::BLUE);
	}
	else if (this->getTeamID() == EnumTeam::BLUE) {
		droneUnits = world->getDroneUnits(EnumTeam::RED);
	}

	//get the unit position
	auto thisPosition = this->getPosition();

	//  if unit within 20 tiles
	for (auto drone : droneUnits) {
		if(drone->getDroneState() != EnumDroneState::DEAD){
			//first check to see if it is checking against itself
			if (this->getDroneID() == drone->getDroneID()) {
				continue;
			}

			auto dronePosition = drone->getPosition();
			//dronePosition wrt our unit
			dronePosition[0] -= thisPosition[0];
			dronePosition[1] -= thisPosition[1];

			auto distanceSqd = dronePosition[0] * dronePosition[0] +
				dronePosition[1] * dronePosition[1];


			if (distanceSqd < AB_DRONE_SENSE_RADIUS * AB_DRONE_SENSE_RADIUS) 
				this->sensedUnits.push_back(std::static_pointer_cast<Unit>(drone));
		}
	}
	//  if unit within 40 tiles
	for (auto drone : allDroneUnits) {
		if(drone->getDroneState() != EnumDroneState::DEAD){
			//first check to see if it is checking against itself
			if (this->getDroneID() == drone->getDroneID()) {
				continue;
			}

			auto dronePosition = drone->getPosition();
			//dronePosition wrt our unit
			dronePosition[0] -= thisPosition[0];
			dronePosition[1] -= thisPosition[1];

			auto distanceSqd = dronePosition[0] * dronePosition[0] +
				dronePosition[1] * dronePosition[1];

			if ((distanceSqd > AB_DRONE_SENSE_RADIUS * AB_DRONE_SENSE_RADIUS) && (distanceSqd < AB_DRONE_SENSE_RADIUS_40 * AB_DRONE_SENSE_RADIUS_40))
				this->numSensedUnitsWithin40 += 1;
		}
	}
}

void DroneUnit::broadcastCommunication() {
	//Grab the parent class
	auto world = World::getInstance();
	//Get the drone units from the parent class
	auto droneUnits = world->getDroneUnits(this->getTeamID());

	//get the unit position
	auto thisPosition = this->getPosition();
	auto sensedUnits = this->getSensedUnits();
	//for unit in unitList
	for (auto drone : droneUnits) {
		//first check to see if it is checking against itself
		if (this->getDroneID() == drone->getDroneID()) {
			continue;
		}

		auto dronePosition = drone->getPosition();
		//dronePosition wrt our unit
		dronePosition[0] -= thisPosition[0];
		dronePosition[1] -= thisPosition[1];

		auto distanceSqd = dronePosition[0] * dronePosition[0] +
			dronePosition[1] * dronePosition[1];

		//  if unit within 100 tiles
		if (distanceSqd < AB_DRONE_BROADCAST_RADIUS * AB_DRONE_BROADCAST_RADIUS) {
			//grab the unit close by and get his list of sensed units
			auto bSensedUnits = drone->getSensedUnits();

			//iterate over this current drone's sensed units
			for(auto theSensedUnit : sensedUnits) {

				//get the ID for the current unit
				auto ID = theSensedUnit->getEntity()->getID();

				//check to see if the unit has already been sensed by the current drone
				auto iter = std::find_if(bSensedUnits.begin(), bSensedUnits.end(),
					[=] (std::shared_ptr<Unit> elem) {
						if (elem->getEntity()->getID() == ID) {
							return true;
						}
						return false;
				});

				//if it doesn't exist within the sensed drone,
				// then we append it to that list
				if(iter == bSensedUnits.end()) {
					bSensedUnits.push_back(theSensedUnit);
				}
			} //END for(auto theSensedUnit : sensedUnits) {
			drone->setSensedUnits(bSensedUnits);

		}
	}
}

void DroneUnit::setUnactive() {
	//get the sprite component
	auto spriteComponent = this->getEntity()->getComponentByName(AB_DRONE_SPRITE);

	//based on what team it is, we assign it a certain sprite to display
	if (this->getTeamID() == EnumTeam::RED) {
		spriteComponent->setAttribute_string(ATTRIBUTE_SPRITE_NAME, AB_SPRITE_RED_DRONE_DEAD);
	}
	else {
		spriteComponent->setAttribute_string(ATTRIBUTE_SPRITE_NAME, AB_SPRITE_BLUE_DRONE_DEAD);
	}

	auto shapeComponent = this->getEntity()->getComponentByName(AB_DRONE_SHAPE_BASE);
	shapeComponent->setAttribute_int(ATTRIBUTE_OUTLINE_COLOR_ALPHA, 30);
	shapeComponent->setAttribute_int(ATTRIBUTE_FILL_COLOR_ALPHA, 30);
	shapeComponent->update();
	//disable all of the inputs and collision components
	auto collisionComponent = this->getEntity()->getComponentByName(AB_DRONE_COLLISION);
	collisionComponent->setAttribute_int(ATTRIBUTE_ENABLE, 0);

	auto shapeComponent_moveradius = this->getEntity()->getComponentByName(AB_DRONE_SHAPE_MOVEMENTRADIUS);
	shapeComponent_moveradius->setAttribute(ATTRIBUTE_ENABLE, 0);
	shapeComponent_moveradius->update();

	auto shapeComponent_senseradius = this->getEntity()->getComponentByName(AB_DRONE_SHAPE_SENSERADIUS);
	shapeComponent_senseradius->setAttribute_int(ATTRIBUTE_ENABLE, 0);
}

void DroneUnit::setFiring() {
	auto world = World::getInstance();
	world->mouseCursor.setIdle();

	//get the shapecomponent and set the outline color
	auto shapeComponent = this->getEntity()->getComponentByName(AB_DRONE_SHAPE_BASE);
	COLOR_OUTLINE_YELLOW(shapeComponent);

	//set the drone color based on the teamID
	if (this->getTeamID() == EnumTeam::RED) {
		COLOR_FILL_RED(shapeComponent); //macro
	}
	else if (this->getTeamID() == EnumTeam::BLUE) {
		COLOR_FILL_BLUE(shapeComponent); //macro
	}
	shapeComponent->setAttribute_int(ATTRIBUTE_FILL_COLOR_ALPHA, 100);
	shapeComponent->update();


	//get the mouse move input component and enable it
	auto inputComponent_MouseMove = this->getEntity()->getComponentByName(AB_DRONE_INPUT_MOUSE_MOVE);
	inputComponent_MouseMove->setAttribute_int(ATTRIBUTE_ENABLE, 0);

	//get the mouse button pressed component and enable it
	auto inputComponent_MousePressed = this->getEntity()->getComponentByName(AB_DRONE_INPUT_MOUSE_PRESSED);
	inputComponent_MousePressed->setAttribute_int(ATTRIBUTE_ENABLE, 0);

	//get the moving shape component and enable it
	auto shapeComponent_move_radius = this->getEntity()->getComponentByName(AB_DRONE_SHAPE_MOVEMENTRADIUS);
	shapeComponent_move_radius->setAttribute_int(ATTRIBUTE_ENABLE, 0);
	shapeComponent_move_radius->update();
}

void DroneUnit::setMoving() {
	//get the shapecomponent and set the outline color
	auto shapeComponent = this->getEntity()->getComponentByName(AB_DRONE_SHAPE_BASE);
	COLOR_OUTLINE_YELLOW(shapeComponent);

	//set the drone color based on the teamID
	if (this->getTeamID() == EnumTeam::RED) {
		COLOR_FILL_RED(shapeComponent); //macro
	}
	else if (this->getTeamID() == EnumTeam::BLUE) {
		COLOR_FILL_BLUE(shapeComponent); //macro
	}
	shapeComponent->setAttribute_int(ATTRIBUTE_FILL_COLOR_ALPHA, 155);
	shapeComponent->update();

	//get the mouse move input component and enable it
	auto inputComponent_MouseMove = this->getEntity()->getComponentByName(AB_DRONE_INPUT_MOUSE_MOVE);
	inputComponent_MouseMove->setAttribute_int(ATTRIBUTE_ENABLE, 1);

	//get the mouse button pressed component and enable it
	auto inputComponent_MousePressed = this->getEntity()->getComponentByName(AB_DRONE_INPUT_MOUSE_PRESSED);
	inputComponent_MousePressed->setAttribute_int(ATTRIBUTE_ENABLE, 1);

	//get the moving shape component and enable it
	auto shapeComponent_move_radius = this->getEntity()->getComponentByName(AB_DRONE_SHAPE_MOVEMENTRADIUS);
	shapeComponent_move_radius->setAttribute_int(ATTRIBUTE_ENABLE, 1);

	shapeComponent_move_radius->setAttribute_float(ATTRIBUTE_OFFSET_X,
		-this->getMovementPoints()+DRONE_OUTLINE_THICKNESS*2);
	shapeComponent_move_radius->setAttribute_float(ATTRIBUTE_OFFSET_Y,
		-this->getMovementPoints()+DRONE_OUTLINE_THICKNESS*2);

	shapeComponent_move_radius->setAttribute_float(ATTRIBUTE_RADIUS, this->getMovementPoints());
	shapeComponent_move_radius->update();

}

void DroneUnit::setIdle() {
	//get the sprite component
	auto spriteComponent = this->getEntity()->getComponentByName(AB_DRONE_SPRITE);

	//based on what team it is, we assign it a certain sprite to display
	if (this->getTeamID() == EnumTeam::RED) {
		spriteComponent->setAttribute_string(ATTRIBUTE_SPRITE_NAME, AB_SPRITE_RED_DRONE_IDLE);
	}
	else {
		spriteComponent->setAttribute_string(ATTRIBUTE_SPRITE_NAME, AB_SPRITE_BLUE_DRONE_IDLE);
	}

	//get the shapecomponent and set the outline color
	auto shapeComponent = this->getEntity()->getComponentByName(AB_DRONE_SHAPE_BASE);
	COLOR_OUTLINE_GREEN(shapeComponent);

	//set the drone color based on the teamID
	if (this->getTeamID() == EnumTeam::RED) {
		COLOR_FILL_RED(shapeComponent); //macro
	}
	else if (this->getTeamID() == EnumTeam::BLUE) {
		COLOR_FILL_BLUE(shapeComponent); //macro
	}
	shapeComponent->setAttribute_int(ATTRIBUTE_FILL_COLOR_ALPHA, 255);
	shapeComponent->update();

	//get the mouse move input component and disable it
	auto inputComponent_MouseMove = this->getEntity()->getComponentByName(AB_DRONE_INPUT_MOUSE_MOVE);
	inputComponent_MouseMove->setAttribute_int(ATTRIBUTE_ENABLE, 0);

	//get the mouse button pressed component and disable it
	auto inputComponent_MousePressed = this->getEntity()->getComponentByName(AB_DRONE_INPUT_MOUSE_PRESSED);
	inputComponent_MousePressed->setAttribute_int(ATTRIBUTE_ENABLE, 0);

	//get the moving shape component and ensure it's disabled
	auto shapeComponent_move_radius = this->getEntity()->getComponentByName(AB_DRONE_SHAPE_MOVEMENTRADIUS);
	shapeComponent_move_radius->setAttribute_int(ATTRIBUTE_ENABLE, 0);
}

void DroneUnit::setFinished() {
	//get the sprite component
	auto spriteComponent = this->getEntity()->getComponentByName(AB_DRONE_SPRITE);

	//based on what team it is, we assign it a certain sprite to display
	if (this->getTeamID() == EnumTeam::RED) {
		spriteComponent->setAttribute_string(ATTRIBUTE_SPRITE_NAME, AB_SPRITE_RED_DRONE_FINISHED);
	}
	else {
		spriteComponent->setAttribute_string(ATTRIBUTE_SPRITE_NAME, AB_SPRITE_BLUE_DRONE_FINISHED);
	}

	//get the shapecomponent and set the outline color
	auto shapeComponent = this->getEntity()->getComponentByName(AB_DRONE_SHAPE_BASE);

	//set the drone color based on the teamID
	if (this->getTeamID() == EnumTeam::RED) {
		COLOR_FILL_RED(shapeComponent); //macro
	}
	else if (this->getTeamID() == EnumTeam::BLUE) {
		COLOR_FILL_BLUE(shapeComponent); //macro
	}
	shapeComponent->setAttribute_int(ATTRIBUTE_FILL_COLOR_ALPHA, 255);

	//give it a white outline to represent that it is spent
	shapeComponent->setAttribute_int(ATTRIBUTE_OUTLINE_COLOR_RED, 255);
	shapeComponent->setAttribute_int(ATTRIBUTE_OUTLINE_COLOR_GREEN, 255);
	shapeComponent->setAttribute_int(ATTRIBUTE_OUTLINE_COLOR_BLUE, 255);

	shapeComponent->update();

	//get the mouse move input component and disable it
	auto inputComponent_MouseMove = this->getEntity()->getComponentByName(AB_DRONE_INPUT_MOUSE_MOVE);
	inputComponent_MouseMove->setAttribute_int(ATTRIBUTE_ENABLE, 0);

	//get the mouse button pressed component and disable it
	auto inputComponent_MousePressed = this->getEntity()->getComponentByName(AB_DRONE_INPUT_MOUSE_PRESSED);
	inputComponent_MousePressed->setAttribute_int(ATTRIBUTE_ENABLE, 0);

	//get the moving shape component and ensure it's disabled
	auto shapeComponent_move_radius = this->getEntity()->getComponentByName(AB_DRONE_SHAPE_MOVEMENTRADIUS);
	shapeComponent_move_radius->setAttribute_int(ATTRIBUTE_ENABLE, 0);
}

//used to set drone to the sensing state
void DroneUnit::setSensing() {
	//get the sprite component
	auto spriteComponent = this->getEntity()->getComponentByName(AB_DRONE_SPRITE);

	//based on what team it is, we assign it a certain sprite to display
	if (this->getTeamID() == EnumTeam::RED) {
		spriteComponent->setAttribute_string(ATTRIBUTE_SPRITE_NAME, AB_SPRITE_RED_DRONE_FINISHED);
	}
	else {
		spriteComponent->setAttribute_string(ATTRIBUTE_SPRITE_NAME, AB_SPRITE_BLUE_DRONE_FINISHED);
	}

	auto shapeComponent = this->getEntity()->getComponentByName(AB_DRONE_SHAPE_BASE);
	//set the drone color based on the teamID
	if (this->getTeamID() == EnumTeam::RED) {
		COLOR_FILL_RED(shapeComponent); //macro
	}
	else if (this->getTeamID() == EnumTeam::BLUE) {
		COLOR_FILL_BLUE(shapeComponent); //macro
	}
	shapeComponent->setAttribute_int(ATTRIBUTE_FILL_COLOR_ALPHA, 255);

	//give it a white outline to represent that it is spent
	shapeComponent->setAttribute_int(ATTRIBUTE_OUTLINE_COLOR_RED, 255);
	shapeComponent->setAttribute_int(ATTRIBUTE_OUTLINE_COLOR_GREEN, 255);
	shapeComponent->setAttribute_int(ATTRIBUTE_OUTLINE_COLOR_BLUE, 255);
	shapeComponent->update();

	//get the mouse move input component and disable it
	auto inputComponent_MouseMove = this->getEntity()->getComponentByName(AB_DRONE_INPUT_MOUSE_MOVE);
	inputComponent_MouseMove->setAttribute_int(ATTRIBUTE_ENABLE, 0);

	//get the mouse button pressed component and disable it
	auto inputComponent_MousePressed = this->getEntity()->getComponentByName(AB_DRONE_INPUT_MOUSE_PRESSED);
	inputComponent_MousePressed->setAttribute_int(ATTRIBUTE_ENABLE, 0);

	//get the moving shape component and ensure it's disabled
	auto shapeComponent_move_radius = this->getEntity()->getComponentByName(AB_DRONE_SHAPE_MOVEMENTRADIUS);
	shapeComponent_move_radius->setAttribute_int(ATTRIBUTE_ENABLE, 0);

}

void DroneUnit::setSensingArea(){
	if(state != EnumDroneState::BROADCASTING){
		auto shapeComponent = this->getEntity()->getComponentByName(AB_DRONE_SHAPE_BASE);
		auto shapeComponent_sense_radius = this->getEntity()->getComponentByName(AB_DRONE_SHAPE_SENSERADIUS);
		auto world = World::getInstance();
		shapeComponent_sense_radius->setAttribute_int(ATTRIBUTE_ENABLE, 1);
		shapeComponent->update();

		auto msg = std::string();
		//show the status of the current drone
		msg += "[";
		msg += std::to_string(this->getDroneID());
		if(this->getTeamID() == world->getPlayerTurn())
			msg += "] Sensed Enemies: ";
		else
			msg += "] Sensed Friendlies: ";
		msg += std::to_string(this->getSensedUnits().size());
		msg += " Over 40: ";
		msg += std::to_string(this->getNumSensedUnitsWithin40());
		world->statusBar.setmostRecentAction(msg, EnumColor::WARNING);
	}

}

//used to set the drone to the broadcasting state
void DroneUnit::setBroadcasting() {

	auto shapeComponent = this->getEntity()->getComponentByName(AB_DRONE_SHAPE_BASE);
	auto shapeComponent_broadcast_radius = this->getEntity()->getComponentByName(AB_DRONE_SHAPE_BROADCASTRADIUS);
	shapeComponent_broadcast_radius->setAttribute_int(ATTRIBUTE_ENABLE, 1);
	shapeComponent->update();
}

void DroneUnit::setDoneBroadcasting() {

	auto shapeComponent = this->getEntity()->getComponentByName(AB_DRONE_SHAPE_BASE);
	auto shapeComponent_broadcast_radius = this->getEntity()->getComponentByName(AB_DRONE_SHAPE_BROADCASTRADIUS);
	shapeComponent_broadcast_radius->setAttribute_int(ATTRIBUTE_ENABLE, 0);
	shapeComponent->update();
}

void DroneUnit::setDoneSensing() {

	auto shapeComponent = this->getEntity()->getComponentByName(AB_DRONE_SHAPE_BASE);
	auto shapeComponent_sense_radius = this->getEntity()->getComponentByName(AB_DRONE_SHAPE_SENSERADIUS);
	shapeComponent_sense_radius->setAttribute_int(ATTRIBUTE_ENABLE, 0);
	shapeComponent->update();
}

void DroneUnit::lastWordsMessage(int attackingDroneID){

	this->sensedUnits.clear();
	this->numSensedUnitsWithin40 = 0;
	auto world = World::getInstance();

	droneListType droneUnits;
	if (this->getTeamID() == EnumTeam::RED) {
		droneUnits = world->getDroneUnits(EnumTeam::BLUE);
	}
	else if (this->getTeamID() == EnumTeam::BLUE) {
		droneUnits = world->getDroneUnits(EnumTeam::RED);
	}
	for (auto drone : droneUnits) {

		//first check to see if it is checking against itself
		if (this->getDroneID() == drone->getDroneID()) {
			continue;
		}
		if(drone->getDroneID() == attackingDroneID)
			this->sensedUnits.push_back(std::static_pointer_cast<Unit>(drone));
	}
	this->broadcastCommunication();
	auto msg = std::string();
	msg += "Drone ";
	msg += std::to_string(this->getDroneID());
	msg += " was killed by drone ";
	msg += std::to_string(attackingDroneID);
	world->statusLog.setWarningString(msg);

}
//get - set methods

bool DroneUnit::getHasFired() {
	return this->hasFired;
}

void DroneUnit::setHasFired(bool value) {
	this->hasFired = value;
}

bool DroneUnit::getIsSelected() {
	return this->isSelected;
}

void DroneUnit::setIsSelected(bool value) {
	this->isSelected = value;
}

float DroneUnit::getShootingAngle() {
	return this->shootingAngle;
}

void DroneUnit::setShootingAngle(float value) {
	this->shootingAngle = value;
}

float DroneUnit::getShootingSpread() {
	return this->shootingSpread;
}

void DroneUnit::setShootingSpread(float value) {
	this->shootingSpread = value;
}

int DroneUnit::getDroneID() {
	return this->droneID;
}

int DroneUnit::getMovementPoints() {
	return this->movementPoints;
}

void DroneUnit::setMovementPoints(int value) {
	this->movementPoints = value;
}

sensedUnitListType DroneUnit::getSensedUnits() {
	return this->sensedUnits;
}

void DroneUnit::setSensedUnits(sensedUnitListType sensed) {
	this->sensedUnits = sensed;
}

int DroneUnit::getNumSensedUnitsWithin40() {
	return this->numSensedUnitsWithin40;
}

EnumDroneState DroneUnit::getDroneState() {
	return this->state;
}

void DroneUnit::setDroneState(EnumDroneState state) {
	this->state = state;
}