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
    
    Contains the system manager. This stores all of the systems and
    processes them each frame.
    
*/

#ifndef AE__SYSTEM_MANAGER_H
#define AE__SYSTEM_MANAGER_H
//DESCRIPTION


//CLASSES
class SystemManager;

//INCLUDES
#include <vector>
#include <memory>

#include "AbstractSystem.h"
#include "Systems.h"

//TYPEDEF
//! Type used to hold the system list.
typedef std::vector<std::shared_ptr<systemType>> systemListType;

//! Used to hold all of the systems and process them per frame.

/*!
  
  System manager contains the 'systems' which you will run/process
  during the gameloop.

*/
class SystemManager {
 private:
  //! holds the systems
  systemListType systemList;
  
  SystemManager();
 public:
  //! Singleton instance

  /*!

    @returns the singleton instance of system manager.

   */
  static SystemManager* getInstance() {
    static SystemManager _instance;
    return &_instance;
  }
  
  //! Adds a system to the system manager.
  void addSystem(std::shared_ptr<systemType> system);

  //! Checks if a system by the given name exists
  bool hasSystem(const std::string& name);

  //! Removes a system by the given name.
  void removeSystem(const std::string& name);
  
  //! Processes each system within the system list.
  int processSystemList();
};

#endif //AE__SYSTEM_MANAGER_H
