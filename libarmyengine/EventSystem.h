/** 
    @file
    @author Benjamin Zaporzan <benzaporzan@gmail.com>

    @section LICENSE
    
    Copyright (C) 2013  Benjamin Zaporzan
    
    This program is free software: you can redistribute it and/or
    modify it under the terms of the GNU General Public License as
    published by the Free Software Foundation, either version 3 of the
    License, or (at your option) any later version.
    
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    General Public License for more details.
    
    You should have received a copy of the GNU General Public License
    along with this program.  If not, see
    [[http://www.gnu.org/licenses/]].

    @section DESCRIPTION

    Contains the event system, which is a system for processing global
    events that may be consistent over the entire execution.

    This is useful for assigning callbacks for things like pressing
    the close button, or resizing the window.
    
*/

#ifndef AE__EVENTSYSTEM_H
#define AE__EVENTSYSTEM_H

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
//! Describes the occurence of closing the application
#define REGISTERED_EVENT_CLOSED "REGISTER_EVENT_CLOSED"

//! Describes the occurence of resizing the application window
#define REGISTERED_EVENT_RESIZED "REGISTER_EVENT_RESIZED"

//! Describes the occurence of losing focus to the application
#define REGISTERED_EVENT_LOSTFOCUS "REGISTER_EVENT_LOSTFOCUS"

//! Describes the occurence of gaining focus to the application
#define REGISTERED_EVENT_GAINEDFOCUS "REGISTER_EVENT_GAINEDFOCUS"

//! Describes the occurence of text being entered
#define REGISTERED_EVENT_TEXTENTERED "REGISTER_EVENT_TEXTENTERED"

//! Describes the occurence of the mouse entering the application window
#define REGISTERED_EVENT_MOUSE_ENTER "REGISTER_EVENT_MOUSE_ENTER"

//! Describes the occurence of the mouse leaving the application window
#define REGISTERED_EVENT_MOUSE_EXIT "REGISTER_EVENT_MOUSE_EXIT"

//#define REGISTERED_EVENT_KEY_PRESSED "REGISTER_EVENT_KEY_PRESSED"

//! Used to handle global events that affect the entire application.

/*!

  Event system is used to add event callbacks to handle certain events
  that are performed which might have a global impact on the
  application.

 */
class EventSystem : public AbstractSystem {
 private:
  //! Reference to the singleton callback manager
  CallbackManager* callbackManager;
  //! Reference to the singleton event manager
  EventManager* eventManager;
  
 public:
  EventSystem();
  
  //! Assign callback for closing the window
  void registerClosed_Callback(functionEventTemplate);

  //! Assign callback for resizing the window
  void registerResized_Callback(functionEventTemplate);

  //! Assign callback for losing focus to the window
  void registerLostFocus_Callback(functionEventTemplate);

  //! Assign callback for gaining focus to the window
  void registerGainedFocus_Callback(functionEventTemplate);

  //! Assign callback for entering text into the window
  void registerTextEntered_Callback(functionEventTemplate);

  //! Assign callback for the mouse entering the window
  void registerMouseEntered_Callback(functionEventTemplate);

  //! Assign callback for the mouse leaving the window
  void registerMouseLeft_Callback(functionEventTemplate);
  
  //! Used to process the events and perform the appropriate callbacks
  int process();
};


#endif //AE__EVENTSYSTEM_H
