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

    This file contains the position component, which is used to
    describe the position of an entity on the screen.
    
*/

#ifndef AE__POSITIONCOMPONENT_H
#define AE__POSITIONCOMPOENNT_H

//CLASS
class PositionComponent;

//INCLUDE
#include <string>

#include "AbstractComponent.h"

//! Used to describe the position of an entity.

/*!  The position of the entity is important for the SpriteComponent,
  TextComponent, ShapeComponent and Collision Component.
 */
class PositionComponent : public AbstractComponent {
 private:
  
 public:
  //! constructor for position component

  /*!  The position component overrides the family value as "Position"
    and should not be assigned to any further components.

    @param name is the unique name assigned to the component.
   */
  PositionComponent(std::string name);
  
  //! updates the position component. Not implemented.
  int update();
};

#endif //AE__POSITIONCOMPONENT_H
