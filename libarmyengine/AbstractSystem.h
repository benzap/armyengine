#ifndef AE__ABSTRACTSYSTEM_H
#define AE__ABSTRACTSYSTEM_H
//DESCRIPTION
/*
The abstract interface to relate the classes
*/

//CLASS
class AbstractSystem;

//INCLUDES
#include <memory>
#include <list>
#include <string>

#include "Entities.h"
#include "EntityManager.h"

//TYPEDEFS
typedef AbstractSystem systemType;

//BEGIN
class AbstractSystem {
private:
	std::string name;

protected:
	EntityManager* entityManager;

public:
	AbstractSystem(std::string);
	~AbstractSystem();

	std::string getName();

	//process set of entities
    virtual int process() = 0;
};

#endif //AE__ABSTRACTSYSTEM_H