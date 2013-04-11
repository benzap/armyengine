//RESPONSIBILITY: Ben was responsible for designing, implementing, and testing this class.

#ifndef FIRINGDANGERZONE_H
#define FIRINGDANGERZONE_H
//DECRIPTION
/*
The FiringDangerZone class creates is used to set up an object on the screen which shows the area that the drone is attacking in.
*/
//CLASSES
class FiringDangerZone;

//INCLUDES
#include <cmath>

#include "ArmyEngine.h"

#include "WorldObject.h"

//DEFINITION

//The minimum spread for the angle in degrees
#define FIRING_MIN_SPREAD 15 
//The maximum spread for the firing angle in degrees
#define FIRING_MAX_SPREAD 60

//determines the increment for changing the spread
// when using the input to change the spread
#define FIRINGZONE_ANGLE_INCREMENT 5

//The area to represent the partial circle
#define FIRING_CIRCLE_AREA (3000 * PI)

//determines how many points make up
// the partial circle shape
#define FIRING_NUM_POLYGON_POINTS 10

//determines how many points make up 
// the collision bounds for the firing
// zone
#define FIRING_NUM_COLLISION_POINTS 10

//the unique name for this particular entity
#define AB_FIRINGZONE "FiringDangerZone"

#define AB_FIRINGZONE_SHAPE "FiringDangerZone_Shape"
#define AB_FIRINGZONE_COLLISION "FiringDangerZone_Collision"
#define AB_FIRINGZONE_INPUT_MOUSEMOVE "FiringDangerZone_InputMouseMove"
#define AB_FIRING_INPUT_MOUSEPRESSED "FiringDanagerZone_InputMousePressed"
#define AB_FIRING_INPUT_KEYPRESSED "FiringDangerZone_InputKeyPressed"

//BEGIN
class FiringDangerZone : public WorldObject {
private:
	float firingSpread;
	float firingAngle;
	bool bFired;

public:
	FiringDangerZone();

	//after changing the current firing angle or firing spread
	// updates the designated polygon shape, and collision bounds to represent the new
	// firing angle and firing spread.
	void update();

	//displays the super duper firing danger zone
	void display();

	//hides the firing danger zone
	void hide();

	//enables the collision component and performs
	// the firing operation
	void fire();

	//gets the current firing angle
	float getFiringAngle();

	//sets the current firing angle
	void setFiringAngle(float);

	//gets the current firing spread
	float getFiringSpread();

	//sets the current firing spread
	void setFiringSpread(float);

	bool hasFired();
	void setFired();
	void clearFired();

};

#endif //FIRINGDANGERZONE_H