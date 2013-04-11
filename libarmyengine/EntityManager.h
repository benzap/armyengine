#ifndef AE__ENTITYMANAGER_H
#define AE__ENTITYMANAGER_H
//DESCRIPTION
/*
Manages the entities that are within the game
Can be used to retrive entities, and list them by family, name, id
*/

//CLASSES
class EntityManager;

//INCLUDES
#include <vector>
#include <list>
#include <memory>
#include <mutex>

#include "AbstractEntity.h"

//TYPEDEFS
typedef std::vector<std::shared_ptr<entityType>> entityVectorType;
typedef std::list<std::shared_ptr<entityType>> entityListType;

//BEGIN
class EntityManager {
private:
	entityVectorType entityList;

	EntityManager() {}

public:
	static EntityManager* getInstance() {
		static EntityManager _instance;
		return &_instance;
	}

	void addEntity(std::shared_ptr<entityType>);
	void removeEntity(std::shared_ptr<entityType>);

	bool hasEntityById(const int);
	std::shared_ptr<entityType> getEntityById(const int);

	entityVectorType getAllEntities();
	entityListType getEntitiesByName(const std::string&);
	entityListType getEntitiesByFamily(const std::string&);

	//operation sorts the entityList based on Z-Buffer index
	// attribute. Other sorting criteria will be considered later.
	void sortEntityList();
};



#endif //AE__ENTITYMANAGER_H