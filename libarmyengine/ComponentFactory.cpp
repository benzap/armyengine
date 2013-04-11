#include "ComponentFactory.h"

ComponentFactory::ComponentFactory() {

}

std::shared_ptr<componentType> ComponentFactory::createCollisionComponent(std::string name) {
	return std::shared_ptr<componentType>(new CollisionComponent(name));
}

std::shared_ptr<componentType> ComponentFactory::createHealthComponent(std::string name) {
	return std::shared_ptr<componentType>(new HealthComponent(name));
}

std::shared_ptr<componentType> ComponentFactory::createInputComponent(std::string name) {
	return std::shared_ptr<componentType>(new InputComponent(name));
}

std::shared_ptr<componentType> ComponentFactory::createPositionComponent(std::string name) {
	return std::shared_ptr<componentType>(new PositionComponent(name));
}

std::shared_ptr<componentType> ComponentFactory::createShapeComponent(std::string name) {
	return std::shared_ptr<componentType>(new ShapeComponent(name));
}

std::shared_ptr<componentType> ComponentFactory::createSpriteComponent(std::string name) {
	return std::shared_ptr<componentType>(new SpriteComponent(name));
}

std::shared_ptr<componentType> ComponentFactory::createStateComponent(std::string name) {
	return std::shared_ptr<componentType>(new StateComponent(name));
}

std::shared_ptr<componentType> ComponentFactory::createTextComponent(std::string name) {
	return std::shared_ptr<componentType>(new TextComponent(name));
}
