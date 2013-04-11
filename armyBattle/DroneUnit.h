//RESPONSIBILITY: Both group members were responsible for designing, implementing, and testing this class.
//Ben did the shooting and moving, and Kyle did the sensing, broadcasting, and "last words" message.
#ifndef AB__DRONEUNIT_H
#define AB__DRONEUNIT_H
//DESCRIPTION
/*
This is the DroneUnit class. DroneUnits are the main thing with which the player interacts on the screen. They move, shoot, sense, and broadcast.
*/
//CLASSES
class DroneUnit;

//INCLUDES
#include <memory>
#include <vector>
#include <cmath>

#include "ArmyEngine.h"
#include "Unit.h"

//TYPEDEFS
typedef std::vector<std::shared_ptr<Unit>> sensedUnitListType;

//ENUMERATIONS
//Determines how to handle the current state of affairs
//for a drone
enum class EnumDroneState {
	IDLE_WAITING = 0,
	MOVING = 1,
	ATTACKING = 2,
	SENSING = 3,
	BROADCASTING = 4,
	IDLE_FINISHED = 5,
	DEAD = 66,
};

//used to determine direction
enum EnumMove {
	UP,
	DOWN,
	LEFT,
	RIGHT
};

//DEFINITIONS

//the drone type string
#define AB_DRONE "Drone"

//the drone sprite name
#define AB_DRONE_SPRITE "Drone_Sprite_base"

//the drone shape name
#define AB_DRONE_SHAPE_BASE "Drone_Shape_Base"

//the drone movement radius shape
#define AB_DRONE_SHAPE_MOVEMENTRADIUS "Drone_Shape_Movement_Radius"
#define AB_DRONE_SHAPE_MOVEMENTRADIUS_OUTLINETHICKNESS 10.0f

//the drone sense radius shape
#define AB_DRONE_SHAPE_SENSERADIUS "Drone_Shape_Sense_Radius"
#define AB_DRONE_SENSE_RADIUS 50.0f
#define AB_DRONE_SENSE_RADIUS_40 100.0f

//the drone broadcast radius shape
#define AB_DRONE_SHAPE_BROADCASTRADIUS "Drone_Shape_Brodcast_Radius"
#define AB_DRONE_BROADCAST_RADIUS 250.0f

//the drone collision component name
#define AB_DRONE_COLLISION "Drone_Collision"
#define AB_DRONE_COLLISION_RADIUS "Drone_Collision_Radius"

//component name for drone input mouse click callback
#define AB_DRONE_INPUT_MOUSE_PRESSED "Drone_Input_MousePressed"

//component name for drone input mouse move callback
#define AB_DRONE_INPUT_MOUSE_MOVE "Drone_Input_MouseMove"

#define AB_DRONE_INPUT_KEYBOARD_PRESSED "Drone_Input_KeyPressed"

#define DEFAULT_MOVEMENT_POINTS 50
#define DEFAULT_MOVEMENT_THRESHOLD 10

//Shape Attributes
#define DRONE_OUTLINE_THICKNESS 0.0f

//BEGIN
class DroneUnit : public Unit {
private:
	bool hasFired;
	bool isSelected;
	float shootingAngle;
	float shootingSpread;
	int droneID; //same as the Unit::entity->getID();
	int movementPoints;
	sensedUnitListType sensedUnits;
	EnumDroneState state;
	int numSensedUnitsWithin40; //...
public:
	DroneUnit(EnumTeam teamID, float xPosition, float yPosition);

	void movePosition(EnumMove theMove, float distance);
	void senseSurroundingUnits();
	void broadcastCommunication();

	//sets the current drone so that it is
	// inactive, this removes any player input to it
	// and is performed on drones not owned by the player.
	void setUnactive();

	//used to set the current drone as the currently firing
	// one, and sets the necessary inputs to perform
	void setFiring();

	//used to set the current drone as the currently moving
	// one, and sets the necessary inputs to perform such an action
	void setMoving();

	//used to set the current drone as idle, and removes any moving or firing
	// inputs that may be currently enabled.
	void setIdle();

	//used to set the drone to a finished state
	void setFinished();

	//used to set drone to the sensing state
	void setSensing();
	void setSensingArea();
	void setDoneSensing();

	//used to set the drone to the broadcasting state
	void setBroadcasting();
	void setDoneBroadcasting();

	//get - set methods
	bool getHasFired();
	void setHasFired(bool = true);

	bool getIsSelected();
	void setIsSelected(bool = true);

	float getShootingAngle();
	void setShootingAngle(float);

	float getShootingSpread();
	void setShootingSpread(float);

	int getDroneID();

	int getMovementPoints();
	void setMovementPoints(int);

	sensedUnitListType getSensedUnits();
	int getNumSensedUnitsWithin40();
	void setSensedUnits(sensedUnitListType sensed);

	EnumDroneState getDroneState();
	void setDroneState(EnumDroneState);

	void lastWordsMessage(int);

};


#endif //AB__DRONEUNIT_H