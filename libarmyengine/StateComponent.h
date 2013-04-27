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

    I haven't found any use for this component, but it is supposed to
    store state on the given entity. When the state is enabled, the
    assigned callback is called each frame, but can be limited to the
    first time it is enabled by setting the appropriate attributes.
    
*/

#ifndef AE__STATECOMPONENT_H
#define AE__STATECOMPONENT_H

//CLASSES
class StateComponent;

//INCLUDES
#include <string>

#include "AbstractComponent.h"

//TYPEDEFS

//DEFINITIONS
//! The statically assigned family name
#define COMPONENT_FAMILY_STATE "State"

//! Used to store entity state (Not currently used)
class StateComponent : public AbstractComponent {
 public:
  //! Constructor overrides the AbstractComponent family to be "State"

  /*!
    
    @param name is the unique name assigned to the component.

   */
  StateComponent(std::string name);

  //! Used when the component is modified (Not Implemented)

  /*!

    @return Returns a zero value if it was successful.
   */
  int update();
};

#endif //AE__STATECOMPONENT_H
