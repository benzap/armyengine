//RESPONSIBILITY: Ben was responsible for designing, implementing, and testing this class.

#ifndef AB__WORLDOBJECT_H
#define AB__WORLDOBJECT_H
//DESCRIPTION
/*
This is the WorldObject class. It is a base class for every object on the screen. It allows for collision detection between objects, as well as placing objects on the
screen via x and y positions.
*/
//CLASSES
class WorldObject;

//INCLUDES
#include <memory>
#include <vector>

#include "ArmyEngine.h"

//ENUMERATION



//DEFINITIONS
#define WORLD_POSITION_COMPONENT "ArmyBattle_PositonComponent_WorldObject"

//BEGIN
class WorldObject {
private:
	std::shared_ptr<entityType> entity;
	bool bCollision;
public:
	WorldObject(const std::string& name, 
		float xPosition, float yPosition);

	~WorldObject();

	void setPosition(float xPosition, float yPosition);
	bool hasCollided();
	void setCollided();
	void clearCollision();
	std::vector<float> getPosition();

	std::shared_ptr<entityType> getEntity();
};

#endif //AB__WORLDOBJECT_H