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

    Contains the input system, used to process entities with input
    components.
    
*/

#ifndef AE__INPUTSYSTEM_H
#define AE__INPUTSYSTEM_H
//DESCRIPTION
/*

*/

//CLASSES
class InputSystem;

//INCLUDES
#include <memory>
#include "SFML\Window.hpp"
#include "AbstractSystem.h"
#include "EventManager.h"
#include "CallbackManager.h"

//DEFINITIONS

//TYPEDEFS

//! Used to process input components in entities

/*!

  Procedure

  - Input System grabs the current events from the EventManager

  - Input system finds entities with InputComponents

  - Input system determines if the Events should be sent to the given
    InputComponents Callback

  - Upon determining if a given InputComponent needs an Event,

   + triggers that given InputComponent's Callback with the entity ID
   and event index

 */
class InputSystem : public AbstractSystem {
 private:
  //! Reference to callback manager instance.
  CallbackManager* callbackManager;
  //! Reference to event manager instance.
  EventManager* eventManager;
  
  //!compares the event to the given input attributes
  /*!

    TODO: type clarifiers for component attributes 

    @param theEvent is the event to check

    @param inputType is the definition describing the type of event check for

    @return Returns true if they are the same, otherwise, returns false.

  */
  bool isEvent(eventType theEvent, std::string inputType);
 public:
  //!Empty Constructor
  InputSystem();
  
  //! Processes the entities, and performs necessary callbacks.
  int process();
};
#endif //AE__INPUTSYSTEM_H
