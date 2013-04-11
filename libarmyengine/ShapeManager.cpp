#include <cassert>

#include "ShapeManager.h"

void ShapeManager::addCircleShape(const std::string& name, std::shared_ptr<sf::CircleShape> cshape) {
	assert(!this->hasCircleShape(name) && "CircleShape by that name already exists");
	this->circleShapeMap[name] = cshape;
}

void ShapeManager::removeCircleShape(const std::string& name) {
	assert(this->hasCircleShape(name) && "CircleShape by that name doesn't exist");
	this->circleShapeMap.erase(name);
}

bool ShapeManager::hasCircleShape(const std::string& name) {
	if (this->circleShapeMap.find(name) == this->circleShapeMap.end()) {
		return false;
	}
	return true;
}

std::shared_ptr<sf::CircleShape> ShapeManager::getCircleShape(const std::string& name) {
	assert(this->hasCircleShape(name) && "CircleShape by that name does not exist");
	return this->circleShapeMap[name];
}

void ShapeManager::addRectangleShape(const std::string& name, std::shared_ptr<sf::RectangleShape> rshape) {
	assert(!this->hasRectangleShape(name) && "RectangleShape by that name already exists");
	this->rectangleShapeMap[name] = rshape;
}

void ShapeManager::removeRectangleShape(const std::string& name) {
	assert(this->hasRectangleShape(name) && "RectangleShape by that name doesn't exist");
	this->rectangleShapeMap.erase(name);
}

bool ShapeManager::hasRectangleShape(const std::string& name) {
	if (this->rectangleShapeMap.find(name) == this->rectangleShapeMap.end()) {
		return false;
	}
	return true;
}

std::shared_ptr<sf::RectangleShape> ShapeManager::getRectangleShape(const std::string& name) {
	assert(this->hasRectangleShape(name) && "RectangleShape by that name does not exist");
	return this->rectangleShapeMap[name];
}

void ShapeManager::addConvexShape(const std::string& name, std::shared_ptr<sf::ConvexShape> shape) {
	assert(!this->hasConvexShape(name) && "ConvexShape by that name already exists");
	this->convexShapeMap[name] = shape;
}

void ShapeManager::removeConvexShape(const std::string& name) {
	assert(this->hasConvexShape(name) && "ConvexShape doesn't exist");
	this->convexShapeMap.erase(name);
}

bool ShapeManager::hasConvexShape(const std::string& name) {
	if (this->convexShapeMap.find(name) == this->convexShapeMap.end()) {
		return false;
	}
	return true;
}

std::shared_ptr<sf::ConvexShape> ShapeManager::getConvexShape(const std::string& name) {
	assert(this->hasConvexShape(name) && "ConvexShape by that name does not exist");
	return this->convexShapeMap[name];
}