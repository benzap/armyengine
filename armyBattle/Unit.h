//RESPONSIBILITY: Kyle was responsible for designing, implementing, and testing this class.

#ifndef AB__UNIT_H
#define AB__UNIT_H
//DESCRIPTION
/*
This is the base class for DroneUnit and HomeBaseUnit that contains attributes common to both classes.
*/
//CLASSES
class Unit;

//INCLUDES
#include <memory>
#include <string>

#include "ArmyEngine.h"

#include "WorldObject.h"
//TYPEDEFS

//ENUMERATIONS

//enumeration for determining the team
// that the unit is on
enum EnumTeam {
	RED,
	BLUE,
	BOTH
};

//DEFINITIONS
#define DEFAULT_UNIT_WIDTH 10.0f
#define DEFAULT_UNIT_HEIGHT 10.0f

//BEGIN
class Unit : public WorldObject {
private:
	std::string type;
	EnumTeam teamID;
public:
	Unit(const std::string& name, EnumTeam teamID);
	virtual ~Unit();
	void setType(const std::string& type);
	const std::string& getType();

	EnumTeam getTeamID();

};

#endif //AB__UNIT_H