#ifndef AE__EVENTSYSTEM_H
#define AE__EVENTSYSTEM_H
//DESCRIPTION
/*
Event system is used to add event callbacks to handle certain events that
are performed which might have a global impact on the application
*/

//CLASSES
class EventSystem;

//INCLUDES
#include <memory>
#include <tuple>
#include <vector>

#include "AbstractSystem.h"
#include "SFML\Window.hpp"
#include "EventManager.h"
#include "CallbackManager.h"

//DEFINITIONS
#define REGISTERED_EVENT_CLOSED "REGISTER_EVENT_CLOSED"
#define REGISTERED_EVENT_RESIZED "REGISTER_EVENT_RESIZED"
#define REGISTERED_EVENT_LOSTFOCUS "REGISTER_EVENT_LOSTFOCUS"
#define REGISTERED_EVENT_GAINEDFOCUS "REGISTER_EVENT_GAINEDFOCUS"
#define REGISTERED_EVENT_TEXTENTERED "REGISTER_EVENT_TEXTENTERED"
#define REGISTERED_EVENT_MOUSE_ENTER "REGISTER_EVENT_MOUSE_ENTER"
#define REGISTERED_EVENT_MOUSE_EXIT "REGISTER_EVENT_MOUSE_EXIT"

//#define REGISTERED_EVENT_KEY_PRESSED "REGISTER_EVENT_KEY_PRESSED"

//TYPEDEFS

//BEGIN
class EventSystem : public AbstractSystem {
private:
	CallbackManager* callbackManager;
	EventManager* eventManager;
	
public:
	EventSystem();

	void registerClosed_Callback(functionEventTemplate);
	void registerResized_Callback(functionEventTemplate);
	void registerLostFocus_Callback(functionEventTemplate);
	void registerGainedFocus_Callback(functionEventTemplate);
	void registerTextEntered_Callback(functionEventTemplate);
	void registerMouseEntered_Callback(functionEventTemplate);
	void registerMouseLeft_Callback(functionEventTemplate);

	int process();
};


#endif //AE__EVENTSYSTEM_H