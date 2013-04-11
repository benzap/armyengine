#ifndef AE__ENTITYFACTORY_H
#define AE__ENTITYFACTORY_H
//DESCRIPTION
/*

*/

//CLASSES
class EntityFactory;

//INCLUDES
#include <memory>

#include "Entities.h"

class EntityFactory {
private:
	static int idNum;
public:
	EntityFactory();
	std::shared_ptr<entityType> createMainEntity(std::string);
};

#endif //AE__ENTITYFACTORY_H