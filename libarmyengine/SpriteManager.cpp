#include <memory>
#include <map>
#include <string>
#include <cassert>

#include "SFML\Graphics.hpp"
#include "SpriteManager.h"

void SpriteManager::addSprite(const std::string& name, std::shared_ptr<spriteType> theSprite) {
	assert(!this->hasSprite(name) && "Sprite by that name already exists"); 
	this->spriteList[name] = theSprite;
}

void SpriteManager::removeSprite(const std::string& name) {
	assert(this->hasSprite(name) && "Sprite doesn't exist");
	//remove element by key
	this->spriteList.erase(name);
}

bool SpriteManager::hasSprite(const std::string& name) {
	if(this->spriteList.find(name) == this->spriteList.end()) {
		return false;
	}
	return true;
}

std::shared_ptr<spriteType> SpriteManager::getSprite(const std::string& name) {
	assert(this->hasSprite(name) && "Sprite doesn't exist by that name");
	return this->spriteList[name];
}