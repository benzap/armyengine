#ifndef AE__ARMYENGINE_H
#define AE__ARMYENGINE_H
//DESCRIPTION
/*
Main class which should be used as an interface to access the functionality
of the armyengine pieces

The only other classes considered for modification are the Managers
*/
//CLASSES
class ArmyEngine;

//INCLUDES
#include <memory>
#include <functional>

#include "SFML\Window.hpp"
#include "SFML\Graphics.hpp"

#include "Managers.h"
#include "Systems.h"
#include "Entities.h"
#include "Components.h"
#include "AE_Attributes.h"
#include "AE_Events.h"
#include "AE_Utilities.h"

#include "ComponentFactory.h"
#include "EntityFactory.h"

//TYPEDEF
typedef std::function<int(int)> functionRegisterTemplate;

//ENUMERATION
enum EnumEventType {
	EVENT_CLOSED,
	EVENT_RESIZED,
	EVENT_LOSTFOCUS,
	EVENT_GAINEDFOCUS,
	EVENT_TEXTENTERED,
	EVENT_MOUSE_ENTER,
	EVENT_MOUSE_EXIT
};

//DEFINITION
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define WINDOW_TITLE "ArmyEngine Game"

//BEGIN
class ArmyEngine {
private:
	sf::RenderWindow window;

	ComponentFactory componentFactory;
	EntityFactory entityFactory;

	//derived eventSystem class required to add our
	// registered callbacks
	std::shared_ptr<EventSystem> eventSystem;

	//derived stateSystem class required to add our
	// state engine
	std::shared_ptr<StateSystem> stateSystem;

	ArmyEngine();

public:
	static ArmyEngine* getInstance() {
		static ArmyEngine _instance;
		return &_instance;
	}

	//get - set
	ComponentFactory& getComponentFactory();
	EntityFactory& getEntityFactory();

	//set the 
	void setStateMachineFunction(functionStateMachineTemplate func);
	void addEntity(std::shared_ptr<entityType>);
	void addCollisionCallback(collisionTagTuple, functionCollisionTemplate);
	void addStateCallback(std::string, functionTemplate);
	void addEventCallback(EnumEventType, functionRegisterTemplate);
	void addInputCallback(std::string, functionEventTemplate);
	sf::RenderWindow* getWindow();
	void setWindowSize(int width, int height);

	void setStateEnable(const std::string&);
	void setStateDisable(const std::string&);
	stateType getState(const std::string&);

	void loadSpriteFromFile(std::string name, std::string filename);

	void runMainLoop();
};

#endif //AE__ARMYENGINE_H