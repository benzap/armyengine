#include <cassert>

#include "TextManager.h"

void TextManager::addText(const std::string& name, std::shared_ptr<sf::Text> text) {
	assert(!(this->hasText(name)) && "Text by that name already exists");
	this->textMap[name] = text;
}

void TextManager::removeText(const std::string& name) {
	assert(this->hasText(name) && "Text by that name doesn't exist");
	this->textMap.erase(name);
}

bool TextManager::hasText(const std::string& name) {
	if (this->textMap.find(name) == this->textMap.end()) {
		return false;
	}
	return true;
}

std::shared_ptr<sf::Text> TextManager::getText(const std::string& name) {
	assert(this->hasText(name) && "Text by that name doesn't exist");
	return this->textMap[name];
}

void TextManager::addFont(const std::string& name, std::shared_ptr<sf::Font> font) {
	assert(!(this->hasFont(name)) && "Font by that name already exists");
	this->fontMap[name] = font;
}

void TextManager::removeFont(const std::string& name) {
	assert(this->hasFont(name) && "Font by that name doesn't exist");
	this->fontMap.erase(name);
}

bool TextManager::hasFont(const std::string& name) {
	if (this->fontMap.find(name) == this->fontMap.end()) {
		return false;
	}
	return true;
}

std::shared_ptr<sf::Font> TextManager::getFont(const std::string& name) {
	assert(this->hasFont(name) && "Font by that name doesn't exist");
	return this->fontMap[name];
}