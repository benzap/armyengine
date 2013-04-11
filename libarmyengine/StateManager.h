#ifndef STATEMANAGER_H
#define STATEMANAGER_H
//DESCRIPTION
/*
The state manager holds information on the state of the system
It is a global representation of the state of the system.
*/
//CLASSES
class StateManager;

//INCLUDES
#include <map>
#include <string>

#include "CallbackManager.h"

//TYPEDEFS
typedef bool stateType;
typedef std::map<std::string, stateType> stateListType;

//BEGIN
class StateManager {
private:
	stateListType stateList;
	StateManager() {}
public:
	static StateManager* getInstance() {
		static StateManager _instance;
		return &_instance;
	}

	void addStateCallback(const std::string&, functionTemplate);

	void setEnable(const std::string&);
	void setDisable(const std::string&);
	stateType getState(const std::string&);

	bool hasState(const std::string&);
};


#endif //STATEMANGER_H