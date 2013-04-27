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

    Contains the abstract for the systems within the entity
    component system

*/

#ifndef AE__ABSTRACTSYSTEM_H
#define AE__ABSTRACTSYSTEM_H

//CLASS
class AbstractSystem;

//INCLUDES
#include <memory>
#include <list>
#include <string>

#include "Entities.h"
#include "EntityManager.h"

//TYPEDEFS

//! Typedef to abstract the abstract...
typedef AbstractSystem systemType;

//! The abstract representation for each system

/*! The abstract system has methods to get the name of the system, and
    to process entities stored within the entity manager.

    Systems carry out specific needs for the engine, such as rendering
    stuff onto the screen, detecting if two entities have collided, or
    checking to see if certain events have been performed, and
    reacting to it.
 */
class AbstractSystem {
private:
  std::string name; //!< Unique name of the current system

protected:
  EntityManager* entityManager; //!< a pointer to the entity manager singleton

public:
  //! Abstract system constructor
  AbstractSystem(std::string name);

  //! Abstract system destructor
  ~AbstractSystem();

  //! Gets the name of the current system

  /*!
    
    @return The name of the current system
   */
  std::string getName();

  
  //! Perform actions on entities
  
  /*!
    
    The process method is a pure virtual function that processes all
    of th entities stored within the entity manager. Some systems do
    not use the entity manager for processing, but may process other
    things that require processing per frame.

    What is processed is fully dependant on the implementation.

    @return A non-zero value if the processing was successful.
  */
  virtual int process() = 0;
};

#endif //AE__ABSTRACTSYSTEM_H
