#ifndef AE__SPRITEMANAGER_H
#define AE__SPRITEMANAGER_H
//DESCRIPTION
/*
Sprite manager is a class which manages the sprites that are to be used within the game
*/
//CLASSES
class SpriteManager;

//INCLUDES
#include <memory>
#include <map>
#include <string>

#include "SFML\Graphics.hpp"

//DEFINITIONS
//the default sprite to use when no sprite has been provided
#define DEFAULT_SPRITE "default"
//path to sprite
#define DEFAULT_SPRITE_PATH "../images/default.png"

//TYPEDEFS
typedef sf::Sprite spriteType;
typedef std::map<std::string, std::shared_ptr<spriteType>> spriteListType;

//BEGIN
class SpriteManager {
private:
	std::map<std::string, std::shared_ptr<spriteType>> spriteList;
	
	//texture for default sprite TODO: make this better
	sf::Texture defaultTexture;

	//Singleton
	SpriteManager() {
		//loading the default sprite
		this->defaultTexture.loadFromFile(DEFAULT_SPRITE_PATH);
		auto defaultSprite = std::shared_ptr<spriteType> (new sf::Sprite(this->defaultTexture));
		this->addSprite(DEFAULT_SPRITE, defaultSprite);
	};

	~SpriteManager() {
		
	}

public:
	static SpriteManager* getInstance() {
		static SpriteManager _instance;
		return &_instance;
	}

	void addSprite(const std::string&, std::shared_ptr<spriteType>);
	void removeSprite(const std::string&);
	bool hasSprite(const std::string&);
	std::shared_ptr<spriteType> getSprite(const std::string&);
};

#endif //AE__SPRITEMANAGER_H