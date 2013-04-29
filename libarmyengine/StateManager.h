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
    
    Contains the state manager. This isn't really useful right now. It
    holds booleans of state which can be accessed throughout the
    application's execution.
    
*/

#ifndef STATEMANAGER_H
#define STATEMANAGER_H
//CLASSES
class StateManager;

//INCLUDES
#include <map>
#include <string>

#include "CallbackManager.h"

//TYPEDEFS

//! Type to represent states
typedef bool stateType;

//! Type to represent the list of states
typedef std::map<std::string, stateType> stateListType;

//! Used to store the state of the currently executing application.

/*!
  
  The state manager holds information on the state of the system It is
  a global representation of the state of the system.

 */
class StateManager {
private:
  //! Stores the list of states
  stateListType stateList;
  //! Empty Constructor
  StateManager() {}
 public:
  //! Singleton Method, returns the instance.

  /*!
    
    @return The singleton instance of state manager.
   */
  static StateManager* getInstance() {
    static StateManager _instance;
    return &_instance;
  }
  
  //! Add a state callback to the manager.

  /*!
    
    @param name is the unique key name assigned to the callback
    @param func is the function callback
    
   */
  void addStateCallback(const std::string& name, functionTemplate func);
  
  
  //! Sets the state for the given unique key name to true

  /*!

    If the state hasn't been created yet, the state will also be
    created within the state manager before setting it to true.

    @param name is the unique key name assigned to the state variable
    
   */
  void setEnable(const std::string& name);

  //! Sets the state for the given unique key name to false

  /*!

    If the state hasn't been created yet, the state will also be
    created within the state manager before setting it to false.

    @param name is the unique key name assigned to the state variable
    
   */
  void setDisable(const std::string& name);

  //! Gets the state of the given unique state.

  /*!

    @param name is the unique key name assigned to the state variable
    @return the state of the given variable.
   */
  stateType getState(const std::string& name);
  
  //! Checks to see if the state exists
  /*!

    @param name is the unique key name assigned to the state variable

    @return Returns true if the state exists, otherwise it returns
    false.

   */
  bool hasState(const std::string& name);
};
#endif //STATEMANGER_H
