//RESPONSIBILITY: Kyle was responsible for designing, implementing, and testing this class.

#ifndef AB__HOMEBASEUNIT_H
#define AB__HOMEBASEUNIT_H
//DESCRIPTION
/*
This is the HomebaseUnit class. The Homebase is the object that you use the drones to try to destroy.
*/
//CLASSES
class HomebaseUnit;

//INCLUDES
#include "Unit.h"

//DEFINITION
#define AB_HOMEBASE "Homebase"
#define AB_HOMEBASE_SHAPE_BASE "Homebase_Shape_Base"
#define AB_HOMEBASE_COLLISION "Homebase_Collision"

#define AB_HOMEBASE_TEXT "Homebase_Text"
#define AB_HOMEBASE_TEXT_SIZE 22

#define AB_HOMEBASE_OUTLINE_THICKNESS 1
#define AB_HOMEBASE_SIZE_OFFSET 15

#define HOMEBASE_STARTING_HEALTH 10

class HomebaseUnit : public Unit {
private:
	int healthPoints;
	int homebaseID;
	bool isDead;
public:
	HomebaseUnit(EnumTeam, float xPosition, float yPosition);

	void registerHit();
	int getHealthPoints();
	int getHomebaseID();
	bool getIsDead();
	void setIsDead();
};

#endif //AB__HOMEBASEUNIT_H