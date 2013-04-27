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

    The collision component is used to provide an entity with a
    collision bound, which other collision bounds react to by calling
    a registered callback. The callbacks are situated within the
    CollisionManager.
    
*/

#ifndef AE__COLLISIONCOMPONENT_H
#define AE__COLLISIONCOMPONENT_H

//CLASSES
class CollisionComponent;

//INCLUDES
#include <string>

#include "AbstractComponent.h"

//! The collision component is used to assign a collision bound to an entity

/*!
  
  The collision component includes attributes to determine the
  positioning of a figmentary shape on the screen that represents the
  bounds of that given entity. 

  All attributes that contribute to the offset, origin and position of
  a shape component also have the same attributes associated with the
  collision component.

 */
class CollisionComponent : public AbstractComponent {
private:

public:
  //! Constructor for the collision component

  /*!  The constructor for the collision component overrides the
    family to the fixed "Collision" family name. It is recommended
    that no other components created override this name.

    @param name is the unique name assigned to the given collision
    component.
   */
  CollisionComponent(std::string name);

  //! Dynamically bound function that updates the component.
  int update();
};

#endif //AE__COLLISIONCOMPONENT_H
