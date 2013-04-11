#include "Unit.h"

Unit::Unit(const std::string& name, EnumTeam teamID) :
	WorldObject(name, 0, 0),
	teamID(teamID),
	type(name) {
}

Unit::~Unit() {
	//WorldObject::~WorldObject();
}

void Unit::setType(const std::string& type) {
	this->type = type;
}

const std::string& Unit::getType() {
	return this->type;
}

EnumTeam Unit::getTeamID() {
	return this->teamID;
}