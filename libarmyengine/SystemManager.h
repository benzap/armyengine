#ifndef AE__SYSTEM_MANAGER_H
#define AE__SYSTEM_MANAGER_H
//DESCRIPTION
/*
System manager contains the 'systems' which you will run/process during the gameloop
*/

//CLASSES
class SystemManager;

//INCLUDES
#include <vector>
#include <memory>

#include "AbstractSystem.h"
#include "Systems.h"

//TYPEDEF
typedef std::vector<std::shared_ptr<systemType>> systemListType;

//BEGIN
class SystemManager {
private:
	systemListType systemList;

	SystemManager();
public:
	//Singleton instance
	static SystemManager* getInstance() {
		static SystemManager _instance;
		return &_instance;
	}

	void addSystem(std::shared_ptr<systemType>);
	bool hasSystem(const std::string&);
	void removeSystem(const std::string&);

	int processSystemList();
};

#endif //AE__SYSTEM_MANAGER_H