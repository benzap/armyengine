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

    Contains the sprite manager, which is a singleton class used to
    store / add, retrieve shapes that are assigned to ShapeComponents.
    
*/

#ifndef AE__SPRITEMANAGER_H
#define AE__SPRITEMANAGER_H


//CLASSES
class SpriteManager;

//INCLUDES
#include <memory>
#include <map>
#include <string>

#include "SFML\Graphics.hpp"

//DEFINITIONS

//! the default sprite to use when no sprite has been provided
#define DEFAULT_SPRITE "default"
//! path to the default sprite
#define DEFAULT_SPRITE_PATH "../images/default.png"

//TYPEDEFS

//! Type to abstract the sprite
typedef sf::Sprite spriteType;

//! Type that holds the sprites within the sprite manager
typedef std::map<std::string, std::shared_ptr<spriteType>> spriteListType;

//! Used to manage the sprites for sprite components

/*!  
  
  Sprite manager is a class which manages the sprites that are to
  be used within the game.

*/
class SpriteManager {
private:

  //! Holds the sprites
  std::map<std::string, std::shared_ptr<spriteType>> spriteList;
  
  //! texture for default sprite TODO: make this better
  sf::Texture defaultTexture;
  
  //! Singleton Constructor

  /*!  Creates and assigns the default sprite using the given texture
    image
   */
  SpriteManager() {
    //loading the default sprite
    this->defaultTexture.loadFromFile(DEFAULT_SPRITE_PATH);
    auto defaultSprite = std::shared_ptr<spriteType> (new sf::Sprite(this->defaultTexture));
    this->addSprite(DEFAULT_SPRITE, defaultSprite);
  };
  
  ~SpriteManager() {
    
  }
  
 public:
  //! Singleton class method to get the single instance

  /*! 

    @return Returns the sprite manager single instance.
   */
  static SpriteManager* getInstance() {
    static SpriteManager _instance;
    return &_instance;
  }
  
  //! Adds a sprite to the sprite manager

  /*!

    @param name is the unique name that is assigned to the sprite
    @param theSprite is the sprite to assign to the manager.

   */
  void addSprite(const std::string& name,
		 std::shared_ptr<spriteType> theSprite);
  
  //! Removes a sprite from the sprite manager

  /*! 

    @param name is the unique name that is assigned to the sprite

   */
  void removeSprite(const std::string& name);

  //! Checks if the sprite by the given name exists

  /*! 

    @param name is the unique name that is assigned to the sprite
    @return Returns true if the given sprite exists, otherwise it
    returns false.

  */
  bool hasSprite(const std::string& name);

  //! Gets the sprite by the given unique name

  /*! 

    @param name is the unique name that is assigned to the sprite
    @return Returns the shared_ptr referencing the sprite. 

    TODO: exception handling.

  */
  std::shared_ptr<spriteType> getSprite(const std::string& name);
};

#endif //AE__SPRITEMANAGER_H
