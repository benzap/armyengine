#include <memory>
#include <map>
#include <string>
#include <cassert>

#include "SFML\Graphics.hpp"
#include "TextureManager.h"

void TextureManager::addTexture(const std::string& name, std::shared_ptr<textureType> texture) {
	assert(!this->hasTexture(name) && "Texture by that name already exists");
	this->textureMap[name] = texture;
}

void TextureManager::deleteTexture(const std::string& name) {
	assert(this->hasTexture(name) && "Texture by that name doesn't exist");
	int numkeys = this->textureMap.erase(name);
	assert(numkeys == 1 && "Shouldn't be more than one key");
}

bool TextureManager::hasTexture(const std::string& name) {
	if (this->textureMap.find(name) == this->textureMap.end()) {
		return false;
	}
	return true;
}

std::shared_ptr<textureType> TextureManager::getTexture(const std::string& name) {
	assert(this->hasTexture(name) && "Texture does not exist");
	return this->textureMap[name];
}