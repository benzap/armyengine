#include <memory>
#include <cassert>
#include <iostream>

#include "ArmyEngine.h"

ArmyEngine::ArmyEngine() :
	window(sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE)),
	componentFactory(ComponentFactory()),
	entityFactory(EntityFactory()) {
	//removing the cursor
	this->window.setMouseCursorVisible(false);


	//First, assign the window to all of the required entities that have dependance on it.
	// event manager needs the window to get the events
	auto eventManager = EventManager::getInstance();
	eventManager->setWindow(&(this->window));
	
	// assign stateSystem
	this->stateSystem = std::shared_ptr<StateSystem>(new StateSystem());

	//assign and create our eventSystem
	this->eventSystem = std::shared_ptr<EventSystem>(new EventSystem());

	// spriteSystem needs the window to draw
	auto spriteSystem = std::shared_ptr<systemType> (new SpriteSystem(window));

	//Assign the systems to our system manager
	auto systemManager = SystemManager::getInstance();
	systemManager->addSystem(std::static_pointer_cast<systemType> (this->eventSystem));
	systemManager->addSystem(spriteSystem);
	systemManager->addSystem(std::shared_ptr<systemType>(new InputSystem()));
	systemManager->addSystem(std::shared_ptr<systemType> (new CollisionSystem()));
	systemManager->addSystem(std::static_pointer_cast<systemType> (this->stateSystem));

	//default event handling

	//by default, closing will end the program
	this->addEventCallback(EnumEventType::EVENT_CLOSED,
		[&] (int ID) {
			window.close();
			return 0;
	});

}

ComponentFactory& ArmyEngine::getComponentFactory() {
	return this->componentFactory;
}

EntityFactory& ArmyEngine::getEntityFactory() {
	return this->entityFactory;
}

void ArmyEngine::setStateMachineFunction(functionStateMachineTemplate func) {
	this->stateSystem->setStateMachineFunction(func);
}

void ArmyEngine::addEntity(std::shared_ptr<entityType> entity) {
	auto entityManager = EntityManager::getInstance();
	entityManager->addEntity(entity);
}

void ArmyEngine::addCollisionCallback(collisionTagTuple tagTuple, functionCollisionTemplate func) {
	auto collisionManager = CollisionManager::getInstance();
	if (!collisionManager->hasCallback(tagTuple)) {
		collisionManager->addCallback(tagTuple, func);
	}
	else {
		std::cout << "Warning: Collision callback for given tuple already exists" << std::endl;
	}
}

void ArmyEngine::addStateCallback(std::string name, functionTemplate func) {
	auto callbackManager = CallbackManager::getInstance();
	callbackManager->addCallback(name, (functionTemplate) func);
}

void ArmyEngine::addEventCallback(EnumEventType eventType, functionRegisterTemplate func) {
	//need to wrap the function into a form that can be used by the callback manager
	//auto funcWrapper = RegisterFunctionWrapper(func);
	auto funcWrapper = (functionEventTemplate) [func] (int ID, int eventIndex) {
		return func(eventIndex);
	};

	if (eventType == EnumEventType::EVENT_CLOSED) {
		this->eventSystem->registerClosed_Callback(funcWrapper);
	}
	else if (eventType == EnumEventType::EVENT_GAINEDFOCUS) {
		this->eventSystem->registerGainedFocus_Callback(funcWrapper);
	}
	else if (eventType == EnumEventType::EVENT_LOSTFOCUS) {
		this->eventSystem->registerLostFocus_Callback(funcWrapper);
	}
	else if (eventType == EnumEventType::EVENT_MOUSE_ENTER) {
		this->eventSystem->registerMouseEntered_Callback(funcWrapper);
	}
	else if (eventType == EnumEventType::EVENT_MOUSE_EXIT) {
		this->eventSystem->registerMouseLeft_Callback(funcWrapper);
	}
	else if (eventType == EnumEventType::EVENT_RESIZED) {
		this->eventSystem->registerResized_Callback(funcWrapper);
	}
	else if (eventType == EnumEventType::EVENT_TEXTENTERED) {
		this->eventSystem->registerTextEntered_Callback(funcWrapper);
	}
	else {
		assert(0 && "eventType not registered");
	}
}

void ArmyEngine::addInputCallback(std::string name, functionEventTemplate func) {
	auto callbackManager = CallbackManager::getInstance();
	if (!callbackManager->hasCallback(name)) {
		callbackManager->addCallback(name, (functionEventTemplate) func);
	}
	else {
		std::cout << "Warning: Attempting to add callback '" << name << "' which already exists, ignoring.";
		std::cout << std::endl;
	}
}

sf::RenderWindow* ArmyEngine::getWindow() {
	return &(this->window);
}

void ArmyEngine::setWindowSize(int width, int height) {
	this->window.setSize(sf::Vector2u(width, height));
}

void ArmyEngine::runMainLoop() {
	auto entityManager = EntityManager::getInstance();
	entityManager->sortEntityList();
	while(this->window.isOpen()) {
		this->window.clear();
		EventManager::getInstance()->pollEvents();
		SystemManager::getInstance()->processSystemList();
		window.display();
	}
}

void ArmyEngine::setStateEnable(const std::string& attr_key) {
	auto stateManager = StateManager::getInstance();
	stateManager->setEnable(attr_key);
}

void ArmyEngine::setStateDisable(const std::string& attr_key) {
	auto stateManager = StateManager::getInstance();
	stateManager->setDisable(attr_key);
}

stateType ArmyEngine::getState(const std::string& attr_key) {
	auto stateManager = StateManager::getInstance();
	return stateManager->getState(attr_key);
}

void ArmyEngine::loadSpriteFromFile(std::string name, std::string filename) {
	auto textureManager = TextureManager::getInstance();
	auto spriteManager = SpriteManager::getInstance();

	//TODO: check to see if the file exists before we try and load it
	//load the texture into a shared_ptr object
	auto theTexture = std::shared_ptr<sf::Texture> (new sf::Texture());
	if (!theTexture->loadFromFile(filename)) {
		std::cout << "Error loading texture from file: " << filename << std::endl;
	}
	//store the texture within the texture manager
	textureManager->addTexture(name, theTexture);

	//create our sprite object from our texture
	auto theSprite = std::shared_ptr<spriteType> (new sf::Sprite(*textureManager->getTexture(name)));

	//add the sprite to the manager
	spriteManager->addSprite(name, theSprite);
}