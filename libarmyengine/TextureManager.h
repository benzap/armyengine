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

    Holds the textures that are being used by the sprites stored
    within the sprite manager.
    
*/

#ifndef AE__TEXTUREMANAGER_H
#define AE__TEXTUREMANAGER_H

//CLASSES
class TextureManager;

//INCLUDES
#include <memory>
#include <map>
#include <string>

#include "SFML\Graphics.hpp"

//TYPEDEFS
//! Type used for textures
typedef sf::Texture textureType;

//! Type used to store the textures.
typedef std::map<std::string, std::shared_ptr<textureType>> textureMapType;

//! Used to store / add and retrieve textures for the sprites

/*!
  
  TextureManager is a singleton

  Sprites require a reference to a texture in order to display
  properly. This class is used to store / add and retrieve these
  textures.

 */
class TextureManager {
 private:
  //! Used to store the textures
  textureMapType textureMap;
  
  //! empty constructor
  TextureManager() {}
 public:

  //! Singleton method, used to retrieve the single instance.

  /*! 

    @return Returns the single instance of the texture manager.
   */
  static TextureManager* getInstance() {
    static TextureManager _instance;
    return &_instance;
  }

  //! Add texture to the texture manager

  /*!
    
    @param name is the unique name assigned to the texture
    @param texture is the texture object
   */
  void addTexture(const std::string& name,
		  std::shared_ptr<textureType> texture);

  //! Remove texture from the texture manager

  /*!

    @param name is the unique name assigned to the texture
   */
  void deleteTexture(const std::string& name);

  //! Checks if the texture exists

  /*!

    @param name is the unique name assigned to the texture
   */
  bool hasTexture(const std::string& name);

  //! Gets the texture described by the given name

  /*!

    @param name is the unique name assigned to the texture

    @return Returns true if the given texture exists, otherwise it
    returns false.
  */
  std::shared_ptr<textureType> getTexture(const std::string& name);
};

#endif //AE__TEXTUREMANAGER_H
