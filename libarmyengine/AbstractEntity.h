#ifndef AE__ABSTRACTENTITY_H
#define AE__ABSTRACTENTITY_H
//DESCRIPTION
/*
The abstract for entities. Entities describe any game objects which make up the game.
This ranges from visual entities to audio entities
*/

//CLASSES
class AbstractEntity;

//INCLUDES
#include <map>
#include <vector>
#include <memory>

#include "AbstractComponent.h"

//TYPEDEFS
typedef AbstractEntity entityType;
typedef std::vector<std::shared_ptr<componentType>> componentVectorType;

//BEGIN
class AbstractEntity {
private:
	componentVectorType componentVector;
	int ID;
	std::string name;
	std::string family;
public:
	AbstractEntity(const std::string&, const std::string& ,const int);
	//~AbstractEntity();

	const std::string& getName();
	const std::string& getFamily();
	int getID();

	//returns true if a component exists with the given name
	bool hasComponentName(const std::string&);

	//returns true if a component exists with the given family
	bool hasComponentFamily(const std::string&);

	//Add a component to given entity
	void addComponent(std::shared_ptr<componentType>);

	const componentVectorType& getAllComponents();

	//Returns a list of components which belongs to the given family
	std::list<std::shared_ptr<componentType>> getComponentsByFamily(const std::string&);

	//Returns a component by its given name
	std::shared_ptr<componentType> getComponentByName(const std::string&);

	//virtual function to perform pre-initialization
	// before being processed. Currently it is being used to sort the
	// shape, text, and sprite components to provide Z-buffer ordering.
	virtual int handle() = 0;
};

#endif //AE__ABSTRACTENTITY_H