#ifndef AE__EVENTMANAGER_H
#define AE__EVENTMANAGER_H
//DESCRIPTION
/*

*/
//CLASSES
class EventManager;

//INCLUDES
#include <memory>
#include <list>
#include <vector>

#include "SFML\Graphics.hpp"

//TYPEDEFS
typedef sf::Event eventType;
typedef std::vector<std::shared_ptr<eventType>> eventListType;

//BEGIN
class EventManager {
private:
	eventListType eventList;
	sf::RenderWindow* window;
	EventManager() {
		this->window = nullptr;
	}
public:
	static EventManager* getInstance() {
		static EventManager _instance;
		return &_instance;
	}

	void setWindow(sf::RenderWindow*);

	void pollEvents();
	eventListType& getEvents();

	

};

#endif //AE__EVENTMANAGER_H