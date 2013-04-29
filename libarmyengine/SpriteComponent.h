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
    
    Contains the sprite component, which is used to display sprites
    representing the entity on the screen.
    
*/

#ifndef AE__SPRITECOMPONENT_H
#define AE__SPRITECOMPONENT_H

//CLASS
class SpriteComponent;

//INCLUDE
#include <string>

#include "AbstractComponent.h"

//! Used to represent sprites for a given entity.

/*!

  Sprite component is included in an entity to have it display itself
  given a set of attributes that describe the sprite to use, and the
  position.
  
*/
class SpriteComponent : public AbstractComponent {
 public:
  /*!
    Family is overloaded to "Sprite"

    @param name is the unique name assigned to the sprite component.
   */
  SpriteComponent(std::string name);
  
  //! Updates the sprite reference.
  
  /*!

    Within the sprite component, the update command is used to
    set the correct width and height of the rectangular sprite.
    
  */
  int update();
};

#endif //AE__SPRITECOMPONENT_H
