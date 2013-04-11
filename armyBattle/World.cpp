#include <cassert>
#include <random>
#include <algorithm>
#include <ctime>
#include <iostream>

#include "World.h"
#include "MouseCursor.h"
#include "AB_Utilities.h"
#include "AB_Assets.h"

World::World() :
	currentTurn(0),
	playerTurn(EnumTeam::RED),
	scoreboard(Scoreboard(WORLD_HUD_SIZE_X, WORLD_HUD_SIZE_Y - AB_WORLD_OUTLINE_THICKNESS*2 - SCOREBOARD_FONT_SIZE)),
	mouseCursor(MouseCursor()),
	firingDangerZone(FiringDangerZone()),
	turnState(EnumTurnState::INIT),
	viewState(EnumViewState::WORLD),
	statusBar(StatusBar(HUD_SPACING*2-30, 5)),
	statusLog(StatusLog(555, 5)),
	menuButton(Button(760-BUTTON_DEFAULT_OUTLINE, 10 + BUTTON_DEFAULT_OUTLINE)),
	menu(Menu()),
	currentDroneID(0),
	victory(Victory(200.0, 100.0)),
	helpScreen(HelpScreen(200.0, 100.0))
{

	//the world has it's own entity which may be modified
	auto armyEngine = ArmyEngine::getInstance();
	auto entityFactory = armyEngine->getEntityFactory();

	//initialize and create the button callback
	menuButton.setButtonText("?");
	menuButton.buttonHUDElement.setTextSize(20);

	//change the Z-buffer to display correctly
	auto textComponent_HUD = menuButton.buttonHUDElement.getEntity()->getComponentByName(AB_HUD_TEXT);
	textComponent_HUD->setAttribute_float(ATTRIBUTE_ZBUFFER, 14.0);

	auto textPosition = menuButton.buttonHUDElement.getPosition();
	menuButton.buttonHUDElement.setPosition(textPosition[0]+5, textPosition[1]);
	menuButton.setSize(20., 20.);
	menuButton.setButtonCallback((functionEventTemplate) [] (int ID, int eventIndex) {
		auto entityManager = EntityManager::getInstance();
		auto entity = entityManager->getEntityById(ID);
		sf::Event theEvent = *EventManager::getInstance()->getEvents()[eventIndex];
		auto mouseButton = theEvent.mouseButton.button;
		if (mouseButton == sf::Mouse::Button::Left) {
			auto world = World::getInstance();
				world->helpScreen.display();
		}
		return 0;
	});
	
	//create our entity and assign to the engine
	auto entity = entityFactory.createMainEntity(AB_WORLD);
	armyEngine->addEntity(entity);

	//get the component factory
	auto componentFactory = armyEngine->getComponentFactory();

	//create the position component
	auto positionComponent = componentFactory.createPositionComponent(AB_WORLD_POSITION);
	entity->addComponent(positionComponent);

	//Position Attributes
	positionComponent->setAttribute_float(ATTRIBUTE_POSITION_X, WORLD_HUD_SIZE_X);
	positionComponent->setAttribute_float(ATTRIBUTE_POSITION_Y, WORLD_HUD_SIZE_Y);
	positionComponent->update();

	//create sprite component
	auto spriteComponent = componentFactory.createSpriteComponent(AB_WORLD_SPRITE);
	entity->addComponent(spriteComponent);

	//sprite attributes
	spriteComponent->setAttribute_string(ATTRIBUTE_SPRITE_NAME, AB_SPRITE_BACKGROUND);
	spriteComponent->setAttribute_int(ATTRIBUTE_ENABLE, 1);
	spriteComponent->setAttribute_int(ATTRIBUTE_ZBUFFER, 10.01);

	//Create the shape component
	auto shapeComponent = componentFactory.createShapeComponent(AB_WORLD_SHAPE_BASE);
	entity->addComponent(shapeComponent);

	//Shape Component Attributes
	shapeComponent->setAttribute_string(ATTRIBUTE_SHAPE_TYPE, SHAPETYPE_RECTANGLE);
	shapeComponent->setAttribute_float(ATTRIBUTE_WIDTH, WORLD_SIZE_X - WORLD_HUD_SIZE_X);
	shapeComponent->setAttribute_float(ATTRIBUTE_HEIGHT, WORLD_SIZE_Y - WORLD_HUD_SIZE_Y);

	//yellow outline
	COLOR_OUTLINE_GREEN(shapeComponent); //macro
	shapeComponent->setAttribute_int(ATTRIBUTE_OUTLINE_COLOR_ALPHA, 255);
	shapeComponent->setAttribute_float(ATTRIBUTE_OUTLINE_THICKNESS, AB_WORLD_OUTLINE_THICKNESS);

	//set the fill color
	COLOR_FILL_BLACK(shapeComponent); //macro
	shapeComponent->setAttribute_int(ATTRIBUTE_FILL_COLOR_RED, 10);
	shapeComponent->setAttribute_int(ATTRIBUTE_FILL_COLOR_GREEN, 10);
	shapeComponent->setAttribute_int(ATTRIBUTE_FILL_COLOR_BLUE, 10);
	shapeComponent->setAttribute_int(ATTRIBUTE_FILL_COLOR_ALPHA, 0);


	shapeComponent->setAttribute_float(ATTRIBUTE_OFFSET_X, -AB_WORLD_OUTLINE_THICKNESS);
	shapeComponent->setAttribute_float(ATTRIBUTE_OFFSET_Y, -AB_WORLD_OUTLINE_THICKNESS);
	shapeComponent->setAttribute_float(ATTRIBUTE_ZBUFFER, 10.0);
	shapeComponent->update();

	//component for out of bounds collision detection

	auto outOfBoundsEntity = entityFactory.createMainEntity(AB_WORLD_OUT_OF_BOUNDS);
	armyEngine->addEntity(outOfBoundsEntity);

	//get the component factory

	//Create the shape component
	auto outOfBoundsShapeComponent = componentFactory.createShapeComponent(AB_WORLD_OUT_OF_BOUNDS_SHAPE);
	entity->addComponent(outOfBoundsShapeComponent);

	//Shape Component Attributes
	outOfBoundsShapeComponent->setAttribute_string(ATTRIBUTE_SHAPE_TYPE, SHAPETYPE_RECTANGLE);
	outOfBoundsShapeComponent->setAttribute_float(ATTRIBUTE_WIDTH, WORLD_SIZE_X);
	outOfBoundsShapeComponent->setAttribute_float(ATTRIBUTE_HEIGHT, WORLD_HUD_SIZE_Y - AB_WORLD_OUTLINE_THICKNESS*2);
	outOfBoundsShapeComponent->setAttribute_float(ATTRIBUTE_OFFSET_X, -WORLD_HUD_SIZE_X);
	outOfBoundsShapeComponent->setAttribute_float(ATTRIBUTE_OFFSET_Y, -WORLD_HUD_SIZE_Y);


	COLOR_OUTLINE_BLACK(outOfBoundsShapeComponent); //macro

	//set the fill color
	COLOR_FILL_BLACK(outOfBoundsShapeComponent); //macro
	outOfBoundsShapeComponent->setAttribute_int(ATTRIBUTE_FILL_COLOR_ALPHA, 255);

	outOfBoundsShapeComponent->setAttribute_float(ATTRIBUTE_ZBUFFER, 10.0);
	outOfBoundsShapeComponent->update();

	//add collision component to represent the extents of its bounds for getting
	// hit or selected
	auto outOfBoundsCollisionComponent = componentFactory.createCollisionComponent(AB_WORLD_OUT_OF_BOUNDS_COLLISION);
	entity->addComponent(outOfBoundsCollisionComponent);

	//Collision Component Attributes
	outOfBoundsCollisionComponent->setAttribute_int(ATTRIBUTE_ENABLE, 1);
	outOfBoundsCollisionComponent->setAttribute_string(ATTRIBUTE_COLLISION_BOUND_TYPE, COLLISION_BOUND_RECTANGLE);
	outOfBoundsCollisionComponent->setAttribute_float(ATTRIBUTE_WIDTH, WORLD_SIZE_X);
	outOfBoundsCollisionComponent->setAttribute_float(ATTRIBUTE_HEIGHT, WORLD_HUD_SIZE_Y - AB_WORLD_OUTLINE_THICKNESS*2);
	outOfBoundsCollisionComponent->setAttribute_string(ATTRIBUTE_COLLISION_TAG, AB_WORLD_OUT_OF_BOUNDS);	
	outOfBoundsCollisionComponent->setAttribute_float(ATTRIBUTE_OFFSET_X, -WORLD_HUD_SIZE_X);
	outOfBoundsCollisionComponent->setAttribute_float(ATTRIBUTE_OFFSET_Y, -WORLD_HUD_SIZE_Y);
	outOfBoundsCollisionComponent->update();

	//adding input component to open and close our menu
	auto inputComponent = componentFactory.createInputComponent(AB_WORLD_INPUT_PRESSED);
	entity->addComponent(inputComponent);

	//input attributes
	inputComponent->setAttribute_string(ATTRIBUTE_INPUT_TYPE, INPUT_KEYBOARD_PRESSED);
	inputComponent->setAttribute_string(ATTRIBUTE_CALLBACK, AB_WORLD_INPUT_PRESSED);

	//input callback
	armyEngine->addInputCallback(AB_WORLD_INPUT_PRESSED,
		(functionEventTemplate) [] (int ID, int eventIndex) {
			auto world = World::getInstance();

			//get the current state
			auto viewState = world->viewState;
			auto turnState = world->turnState;
			auto entityManager = EntityManager::getInstance();
			auto entity = entityManager->getEntityById(ID);
			sf::Event theEvent = *EventManager::getInstance()->getEvents()[eventIndex];
			auto keypressed = theEvent.key;
			if (keypressed.code == sf::Keyboard::Escape) {
				if (viewState == EnumViewState::WORLD) {
					//change our state to the MENU
					world->viewState = EnumViewState::MENU;
					world->menu.display();
				}
				else {
					//else we assume it's on the menu,
					// and change it back to the world state
					world->viewState = EnumViewState::WORLD;
					world->menu.hide();
				}
			}
			return 0;
	});
}

void World::generateWorld() {
	//need to remove 
	this->currentTurn = 0;
	this->turnState = EnumTurnState::INIT;
	this->viewState = EnumViewState::WORLD;

	auto armyEngine = ArmyEngine::getInstance();
	armyEngine->setWindowSize(WORLD_SIZE_X, WORLD_SIZE_Y);

	//before we clear the unitlist, set all of the
	// drones to unactive to turn off any collision callbacks etc
	for (auto drone : this->getDroneUnits()) {
		drone->setUnactive();
	}

	this->unitList.clear();
	std::default_random_engine randEngine_generator(time(NULL));
	std::uniform_int_distribution<int> randIntEngine_x(
		DEFAULT_UNIT_WIDTH+5,
		WORLD_SIZE_X/2 - WORLD_HUD_SIZE_X - DEFAULT_UNIT_WIDTH - DRONE_OUTLINE_THICKNESS);
	std::uniform_int_distribution<int> randIntEngine_y(
		DEFAULT_UNIT_HEIGHT+5,
		WORLD_SIZE_Y - WORLD_HUD_SIZE_Y - DEFAULT_UNIT_HEIGHT - DRONE_OUTLINE_THICKNESS);

	//function to check if the generated position for the drone overlaps with any others
	auto isOverlapping = [&] (int x1, int y1) {
		for (auto drone : this->unitList) {
			auto dronePosition = drone->getPosition();
			int x2 = dronePosition[0];
			int y2 = dronePosition[1];
			int width = DEFAULT_UNIT_WIDTH + DRONE_OUTLINE_THICKNESS * 2 + AB_HOMEBASE_SIZE_OFFSET;
			int height = DEFAULT_UNIT_HEIGHT + DRONE_OUTLINE_THICKNESS * 2 + AB_HOMEBASE_SIZE_OFFSET;
			int t;
			if ((t = x1 - x2) > width || -t > width) { continue; }
			if ((t = y1 - y2) > height || -t > height) { continue; }
			return true;
		}
		return false;
	};

	int xPosition = 0;
	int yPosition = 0;
	//for team RED, on the left side and team BLUE on the right side
	for (int i = 0; i < NUM_UNITS_PER_TEAM; i++) {
		do {
			xPosition = randIntEngine_x(randEngine_generator) + WORLD_HUD_SIZE_X;
			yPosition = randIntEngine_y(randEngine_generator) + WORLD_HUD_SIZE_Y;
		} while (isOverlapping(xPosition, yPosition));

		auto droneRed = std::shared_ptr<DroneUnit> (new DroneUnit(EnumTeam::RED, xPosition, yPosition));
		this->unitList.push_back(std::dynamic_pointer_cast<Unit>(droneRed));		

		do {
			xPosition = randIntEngine_x(randEngine_generator) + WORLD_SIZE_X/2 + WORLD_HUD_SIZE_X;
			yPosition = randIntEngine_y(randEngine_generator) + WORLD_HUD_SIZE_Y;
		} while (isOverlapping(xPosition, yPosition));

		auto droneBlue = std::shared_ptr<DroneUnit> (new DroneUnit(EnumTeam::BLUE, xPosition, yPosition));
		this->unitList.push_back(std::dynamic_pointer_cast<Unit>(droneBlue));
	}

	//place the homebase units for both red and blue team
	do {
		xPosition = randIntEngine_x(randEngine_generator) + WORLD_HUD_SIZE_X;
		yPosition = randIntEngine_y(randEngine_generator) + WORLD_HUD_SIZE_Y;
	} while (isOverlapping(xPosition, yPosition)
		&& ((yPosition < WORLD_SIZE_Y - AB_WORLD_OUTLINE_THICKNESS - AB_HOMEBASE_SIZE_OFFSET)
		&& (yPosition > AB_WORLD_OUTLINE_THICKNESS + AB_HOMEBASE_SIZE_OFFSET))
		&& ((xPosition < WORLD_SIZE_X - AB_WORLD_OUTLINE_THICKNESS - AB_HOMEBASE_SIZE_OFFSET)
		&& (xPosition > AB_WORLD_OUTLINE_THICKNESS + AB_HOMEBASE_SIZE_OFFSET)));
	auto homebaseRed = std::shared_ptr<HomebaseUnit> (new HomebaseUnit(EnumTeam::RED, xPosition, yPosition));
	this->unitList.push_back(std::dynamic_pointer_cast<Unit> (homebaseRed));

	do {
		xPosition = (randIntEngine_x(randEngine_generator) + WORLD_SIZE_X/2 + WORLD_HUD_SIZE_X);
		yPosition = randIntEngine_y(randEngine_generator) + WORLD_HUD_SIZE_Y;
	} while (isOverlapping(xPosition, yPosition)
		&& (yPosition < WORLD_SIZE_Y - AB_WORLD_OUTLINE_THICKNESS - AB_HOMEBASE_SIZE_OFFSET)
		&& (yPosition > AB_WORLD_OUTLINE_THICKNESS + AB_HOMEBASE_SIZE_OFFSET)
		&& (xPosition < WORLD_SIZE_X - AB_WORLD_OUTLINE_THICKNESS - AB_HOMEBASE_SIZE_OFFSET)
		&& (xPosition > AB_WORLD_OUTLINE_THICKNESS + AB_HOMEBASE_SIZE_OFFSET));
	auto homebaseBlue = std::shared_ptr<HomebaseUnit> (new HomebaseUnit(EnumTeam::BLUE, xPosition, yPosition));
	this->unitList.push_back(std::dynamic_pointer_cast<Unit> (homebaseBlue));
	scoreboard.setRedCount(HOMEBASE_STARTING_HEALTH);
	scoreboard.setBlueCount(HOMEBASE_STARTING_HEALTH);
}

void World::endGame(EnumTeam teamID) {
	this->victory.display(teamID);
	this->viewState = EnumViewState::VICTORY;
	this->turnState = EnumTurnState::VICTORY;
	for (auto drone : this->getDroneUnits()) {
		drone->setUnactive();
	}
}

droneListType World::getDroneUnits(EnumTeam teamID) {
	auto droneList = droneListType();
	for (auto unit : this->unitList) {
		if (unit->getType() == AB_DRONE) {
			if (unit->getTeamID() == teamID || teamID == EnumTeam::BOTH) {
				auto droneUnit = std::dynamic_pointer_cast<DroneUnit> (unit);
				if (droneUnit != nullptr) {
					droneList.push_back(droneUnit);
				}
				else {
					std::cout << "ERROR: Unable to cast Unit to DroneUnit";
					std::cout << std::endl;
				}
			}
		}
	}
	return droneList;
}

unitListType& World::getUnitList() {
	return this->unitList;
}

std::shared_ptr<DroneUnit> World::getDroneByID(int ID) {
	auto droneList = getDroneUnits();
	auto iter = std::find_if(droneList.begin(), droneList.end(),
		[&ID] (std::shared_ptr<DroneUnit> elem) {
			if (elem->getDroneID() == ID) {
				return true;
			}
			return false;
	});
	if (iter != droneList.end()) {
		return *iter;
	}
	return nullptr;
}

std::shared_ptr<HomebaseUnit> World::getHomebaseByID(int ID) {
	//make a copy of our unit list
	auto unitList = unitListType(this->getUnitList());
	//remove all of the units that aren't homebase units
	std::remove_if(unitList.begin(), unitList.end(),
		[&ID] (std::shared_ptr<Unit> elem) {
			if (elem->getType() != AB_HOMEBASE) {
				return true;
			}
			return false;
	});

	//get the homebase unit with the correct ID
	auto iter = std::find_if(unitList.begin(), unitList.end(),
		[&ID] (std::shared_ptr<Unit> elem) {
			if (elem->getEntity()->getID() == ID) {
				return true;
			}
			return false;
	});
	if (iter != unitList.end()) {
		auto homebaseUnit = std::dynamic_pointer_cast<HomebaseUnit>(*iter);
		if (homebaseUnit != nullptr) {
			return homebaseUnit;
		}
		else {
			std::cout << "ERROR: could not cast Unit to HomeBaseUnit";
			std::cout << std::endl;
			return std::shared_ptr<HomebaseUnit> (nullptr);
		}
	}
	else {
		std::cout << "ERROR: homebaseunit by the given ID doesn't exist";
		std::cout << std::endl;
		return std::shared_ptr<HomebaseUnit>(nullptr);
	}
}

EnumTeam World::getPlayerTurn() {
	return this->playerTurn;
}

void World::changePlayerTurn() {
	this->playerTurn = (this->playerTurn == EnumTeam::RED) ?
		EnumTeam::BLUE : EnumTeam::RED;	
}
EnumTurnState World::getTurnState(){
	return this->turnState;
}

int World::getCurrentDroneID(){
	return this->currentDroneID;
}

void World::setCurrentDroneID(int id){
	this->currentDroneID = id;
}


