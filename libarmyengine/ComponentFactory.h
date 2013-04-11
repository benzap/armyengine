#ifndef AE__COMPONENTFACTORY_H
#define AE__COMPONENTFACTORY_H
//DESCRIPTION
/*

*/
//CLASSES
class ComponentFactory;

//INCLUDES
#include <memory>

#include "Components.h"

class ComponentFactory {
private:

public:
	ComponentFactory();

	std::shared_ptr<componentType> createCollisionComponent(std::string);
	std::shared_ptr<componentType> createHealthComponent(std::string);
	std::shared_ptr<componentType> createInputComponent(std::string);
	std::shared_ptr<componentType> createPositionComponent(std::string);
	std::shared_ptr<componentType> createShapeComponent(std::string);
	std::shared_ptr<componentType> createSpriteComponent(std::string);
	std::shared_ptr<componentType> createStateComponent(std::string);
	std::shared_ptr<componentType> createTextComponent(std::string);
};


#endif //AE__COMPONENTFACTORY_H