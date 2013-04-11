#ifndef AE__TEXTUREMANAGER_H
#define AE__TEXTUREMANAGER_H
//DESCRIPTION
/*
Texture manager is a class which manages the sprites that are to be used within the game
*/

//CLASSES
class TextureManager;

//INCLUDES
#include <memory>
#include <map>
#include <string>

#include "SFML\Graphics.hpp"

//TYPEDEFS
typedef sf::Texture textureType;
typedef std::map<std::string, std::shared_ptr<textureType>> textureMapType;

//BEGIN
class TextureManager {
private:
	textureMapType textureMap;

	TextureManager() {}
public:
	static TextureManager* getInstance() {
		static TextureManager _instance;
		return &_instance;
	}

	void addTexture(const std::string&, std::shared_ptr<textureType>);
	void deleteTexture(const std::string&);
	bool hasTexture(const std::string&);
	std::shared_ptr<textureType> getTexture(const std::string&);
};

#endif //AE__TEXTUREMANAGER_H