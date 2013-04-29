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
    
    Contains the sprite system, which is used to process sprite
    components and display them on the screen.
    
*/

#ifndef AE__SPRITESYSTEM_H
#define AE__SPRITESYSTEM_H

//CLASSES
class SpriteSystem;

//INCLUDES
#include <memory>

#include "SFML\Window.hpp"
#include "AbstractSystem.h"
#include "SpriteManager.h"
#include "TextManager.h"
#include "ShapeManager.h"

//DEFINITIONS
//! Threshold for reseting the the sprite rotation angle
#define FULL_ROTATION_THRESHOLD 1.0e-5

//! Used to set the maximum number of points on a circle (Deprecated)
#define CIRCLE_NUM_POINTS 60

//! Used to display Text, Sprite, and Shape components.

/*!
  
  Sprite system, used to read from entities, find the Sprite Component
  and determine if the entity should be drawn to the screen.

*/
class SpriteSystem : public AbstractSystem {
 private:
  
  //! Reference to the currently active window
  sf::RenderWindow& window;
  //! Reference to sprite manager singleton
  SpriteManager* spriteManager;
  //! Reference to text manager singleton
  TextManager* textManager;
  //! Reference to shape manager singleton
  ShapeManager* shapeManager;
  
 public:
  //! Requires a window reference in order to display the sprites

  /*!
    
    @param window is the window reference.
    
   */
  SpriteSystem(sf::RenderWindow& window);
  
  //! Processes the entities and displays Text, Shape and Sprite components.
  int process();
};
#endif //AE__SPRITESYSTEM_H
