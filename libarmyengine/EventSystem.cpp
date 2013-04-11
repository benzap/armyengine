#include <iostream>
#include <memory>
#include <cassert>
#include <algorithm>

#include "EventSystem.h"
#include "Components.h"
#include "AE_Events.h"
#include "AE_Attributes.h"

EventSystem::EventSystem() :
	AbstractSystem("Event"),
	callbackManager(CallbackManager::getInstance()),
	eventManager(EventManager::getInstance()) {
	auto defaultCallback = (functionEventTemplate) [] (int i, int eventID) {return 0;};

	this->registerClosed_Callback(defaultCallback);
	this->registerResized_Callback(defaultCallback);
	this->registerLostFocus_Callback(defaultCallback);
	this->registerGainedFocus_Callback(defaultCallback);
	this->registerTextEntered_Callback(defaultCallback);
	this->registerMouseEntered_Callback(defaultCallback);
	this->registerMouseLeft_Callback(defaultCallback);
}

void EventSystem::registerClosed_Callback(functionEventTemplate func) {
	if (callbackManager->hasCallback(REGISTERED_EVENT_CLOSED)) {
		callbackManager->removeCallback(REGISTERED_EVENT_CLOSED);
	}
	callbackManager->addCallback(REGISTERED_EVENT_CLOSED, func);
}

void EventSystem::registerResized_Callback(functionEventTemplate func) {
	if (callbackManager->hasCallback(REGISTERED_EVENT_RESIZED)) {
		callbackManager->removeCallback(REGISTERED_EVENT_RESIZED);
	}
	callbackManager->addCallback(REGISTERED_EVENT_RESIZED, func);
}

void EventSystem::registerLostFocus_Callback(functionEventTemplate func) {
	if (callbackManager->hasCallback(REGISTERED_EVENT_LOSTFOCUS)) {	
		callbackManager->removeCallback(REGISTERED_EVENT_LOSTFOCUS);
	}
	callbackManager->addCallback(REGISTERED_EVENT_LOSTFOCUS, func);
}

void EventSystem::registerGainedFocus_Callback(functionEventTemplate func) {
	if (callbackManager->hasCallback(REGISTERED_EVENT_GAINEDFOCUS)) {
		callbackManager->removeCallback(REGISTERED_EVENT_GAINEDFOCUS);
	}
	callbackManager->addCallback(REGISTERED_EVENT_GAINEDFOCUS, func);
}

void EventSystem::registerTextEntered_Callback(functionEventTemplate func) {
	if (callbackManager->hasCallback(REGISTERED_EVENT_TEXTENTERED)) {
		callbackManager->removeCallback(REGISTERED_EVENT_TEXTENTERED);
	}
	callbackManager->addCallback(REGISTERED_EVENT_TEXTENTERED, func);
}

void EventSystem::registerMouseEntered_Callback(functionEventTemplate func) {
	if (callbackManager->hasCallback(REGISTERED_EVENT_MOUSE_ENTER)) {
		callbackManager->removeCallback(REGISTERED_EVENT_MOUSE_ENTER);
	}
	callbackManager->addCallback(REGISTERED_EVENT_MOUSE_ENTER, func);
}

void EventSystem::registerMouseLeft_Callback(functionEventTemplate func) {
	if (callbackManager->hasCallback(REGISTERED_EVENT_MOUSE_EXIT)) {
		callbackManager->removeCallback(REGISTERED_EVENT_MOUSE_EXIT);
	}
	callbackManager->addCallback(REGISTERED_EVENT_MOUSE_EXIT, func);
}

int EventSystem::process() {
	auto eventList = eventManager->getEvents();
	for (auto theEvent : eventList) {
		//get eventIndex
		auto iter = std::find(eventList.begin(), eventList.end(), theEvent);
		assert(!(iter == eventList.end()) && "Event doesn't exist");
		int eventIndex = iter - eventList.begin();


		if (theEvent->type == sf::Event::Closed) {
			callbackManager->triggerCallback(REGISTERED_EVENT_CLOSED, 0, eventIndex);
		}
		else if (theEvent->type == sf::Event::Resized) {
			callbackManager->triggerCallback(REGISTERED_EVENT_RESIZED, 0, eventIndex);
		}
		else if (theEvent->type == sf::Event::LostFocus) {
			callbackManager->triggerCallback(REGISTERED_EVENT_LOSTFOCUS, 0, eventIndex);
		}
		else if (theEvent->type == sf::Event::GainedFocus) {
			callbackManager->triggerCallback(REGISTERED_EVENT_GAINEDFOCUS, 0, eventIndex);
		}
		else if (theEvent->type == sf::Event::TextEntered) {
			callbackManager->triggerCallback(REGISTERED_EVENT_TEXTENTERED, 0, eventIndex);
		}
		else if (theEvent->type == sf::Event::MouseEntered) {
			callbackManager->triggerCallback(REGISTERED_EVENT_MOUSE_ENTER, 0, eventIndex);
		}
		else if (theEvent->type == sf::Event::MouseLeft) {
			callbackManager->triggerCallback(REGISTERED_EVENT_MOUSE_EXIT, 0, eventIndex);
		}
		else {
			//do nothing
		}
	}
	return 0;
}