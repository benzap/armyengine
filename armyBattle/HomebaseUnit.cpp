#include "World.h"
#include "HomeBaseUnit.h"
#include "AB_Utilities.h"

HomebaseUnit::HomebaseUnit(EnumTeam teamID, float xPosition, float yPosition) :
	Unit(AB_HOMEBASE, teamID),
	healthPoints(HOMEBASE_STARTING_HEALTH) {
		this->setPosition(xPosition, yPosition);

		this->homebaseID = this->getEntity()->getID();

		//grabbing the component factory
		auto componentFactory = ArmyEngine::getInstance()->getComponentFactory();

		//add shape component to represent the drone
		auto shapeComponent = componentFactory.createShapeComponent(AB_HOMEBASE_SHAPE_BASE);
		this->getEntity()->addComponent(shapeComponent);

		//Shape Component Attributes
		shapeComponent->setAttribute_string(ATTRIBUTE_SHAPE_TYPE, SHAPETYPE_RECTANGLE);
		shapeComponent->setAttribute_float(ATTRIBUTE_WIDTH, DEFAULT_UNIT_WIDTH + AB_HOMEBASE_SIZE_OFFSET);
		shapeComponent->setAttribute_float(ATTRIBUTE_HEIGHT, DEFAULT_UNIT_HEIGHT + AB_HOMEBASE_SIZE_OFFSET);

		//yellow outline
		COLOR_OUTLINE_ORANGE(shapeComponent); //macro
		shapeComponent->setAttribute_int(ATTRIBUTE_OUTLINE_COLOR_ALPHA, 255);
		shapeComponent->setAttribute_float(ATTRIBUTE_OUTLINE_THICKNESS, AB_HOMEBASE_OUTLINE_THICKNESS);

		//set the drone color based on the teamID
		if (this->getTeamID() == EnumTeam::RED) {
			COLOR_FILL_RED(shapeComponent); //macro
		}
		else if (this->getTeamID() == EnumTeam::BLUE) {
			COLOR_FILL_BLUE(shapeComponent); //macro
		}

		shapeComponent->setAttribute_float(ATTRIBUTE_OFFSET_X, 0.0);
		shapeComponent->setAttribute_float(ATTRIBUTE_OFFSET_Y, 0.0);
		shapeComponent->setAttribute_float(ATTRIBUTE_ZBUFFER, 0.01);
		shapeComponent->update();

		//add text component to represent the health of homebase
		auto textComponent = componentFactory.createTextComponent(AB_HOMEBASE_TEXT);
		this->getEntity()->addComponent(textComponent);

		textComponent->setAttribute_string(ATTRIBUTE_TEXT_STRING, std::to_string(this->healthPoints));
		textComponent->setAttribute_int(ATTRIBUTE_TEXT_SIZE, AB_HOMEBASE_TEXT_SIZE);

		//text color of the homebaseunit health points indicator
		textComponent->setAttribute_int(ATTRIBUTE_FILL_COLOR_RED, 0);
		textComponent->setAttribute_int(ATTRIBUTE_FILL_COLOR_GREEN, 0);
		textComponent->setAttribute_int(ATTRIBUTE_FILL_COLOR_BLUE, 0);
		textComponent->setAttribute_int(ATTRIBUTE_FILL_COLOR_ALPHA, 255);

		//text style
		textComponent->setAttribute_int(ATTRIBUTE_TEXT_STYLE_BOLD, 1);

		textComponent->setAttribute_float(ATTRIBUTE_OFFSET_X, 0);
		textComponent->setAttribute_float(ATTRIBUTE_OFFSET_Y, -2);
		textComponent->setAttribute_float(ATTRIBUTE_ZBUFFER, 0.1);
		textComponent->update();

		//add collision component to represent the extents of its bounds for getting
		// hit or selected
		auto collisionComponent = componentFactory.createCollisionComponent(AB_HOMEBASE_COLLISION);
		this->getEntity()->addComponent(collisionComponent);

		//Collision Component Attributes
		collisionComponent->setAttribute_string(ATTRIBUTE_COLLISION_BOUND_TYPE, COLLISION_BOUND_RECTANGLE);
		collisionComponent->setAttribute_float(ATTRIBUTE_WIDTH, DEFAULT_UNIT_WIDTH + AB_HOMEBASE_SIZE_OFFSET);
		collisionComponent->setAttribute_float(ATTRIBUTE_HEIGHT, DEFAULT_UNIT_HEIGHT + AB_HOMEBASE_SIZE_OFFSET);
		collisionComponent->setAttribute_string(ATTRIBUTE_COLLISION_TAG, AB_HOMEBASE);	
		collisionComponent->update();
}

void HomebaseUnit::registerHit() {
	this->healthPoints -= 1;
	auto textComponent = this->getEntity()->getComponentByName(AB_HOMEBASE_TEXT);
	textComponent->setAttribute_string(ATTRIBUTE_TEXT_STRING, std::to_string(this->healthPoints));
	textComponent->update();

	//update our scoreboard
	auto world = World::getInstance();
	if (world->getPlayerTurn() == EnumTeam::RED) {
		world->scoreboard.setRedCount(this->healthPoints);
	}
	else {
		world->scoreboard.setBlueCount(this->healthPoints);
	}

	//check to see if the homebase has been destroyed and end the game if necessary
	if (this->getHealthPoints() <= 0) {
		if (this->getTeamID() == EnumTeam::RED) {
			world->endGame(EnumTeam::BLUE);
		}
		else {
			world->endGame(EnumTeam::RED);
		}
	}
}

int HomebaseUnit::getHealthPoints() {
	return this->healthPoints;
}

int HomebaseUnit::getHomebaseID() {
	return this->homebaseID;
}