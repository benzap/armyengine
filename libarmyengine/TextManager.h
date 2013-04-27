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

    Holds the text manager, which is used to store / add text which is
    used by the TextComponent.
    
*/

#ifndef AE__TEXTMANAGER_H
#define AE__TEXTMANAGER_H

//CLASSES
class TextManager;

//INCLUDES
#include <memory>
#include <map>
#include <string>

#include "SFML\Graphics.hpp"

//TYPEDEFS

//DEFINITIONS

//! The default font to be used if no other font is considered
#define DEFAULT_FONT "Inconsolata"
//! The path to the default font
#define DEFAULT_FONT_PATH "../fonts/Inconsolata.otf"

//! Used to store / add, and retrieve text for use with the text component

/*!

  The text manager is used to store and retrieve text for the text
  components. It also contains facilities for storing and retrieving
  fonts that are to be used for the text's font type.

 */
class TextManager {
 private:
  //! Used to store the text
  std::map<std::string, std::shared_ptr<sf::Text>> textMap;
  //! Used to store the font
  std::map<std::string, std::shared_ptr<sf::Font>> fontMap;
  
  //! default font used for the font type
  sf::Font defaultFont;
  
  //! Constructor

  /*!

    Assigns the default font to the text manager.

   */
  TextManager() {
    this->defaultFont.loadFromFile(DEFAULT_FONT_PATH);
    auto defaultFontPtr = std::shared_ptr<sf::Font> (new sf::Font(defaultFont));
    this->addFont(DEFAULT_FONT, defaultFontPtr);
	}

 public:

  //! Singleton method, retrieves the single instance.

  /*!

    @return Returns the text manager single instance.
   */
  static TextManager* getInstance() {
    static TextManager _instance;
    return &_instance;
  }

  //! Add text to the text manager

  /*!

    @param name is the unique name assigned to the text object
    @param text is the text object being stored within the text manager.
   */
  void addText(const std::string& name, std::shared_ptr<sf::Text> text);

  //! Remove text from the text manager

  /*!

    @param name is the unique name assigned to the text object

   */
  void removeText(const std::string& name);

  //! Check if text exists within the manager

  /*!

    @param name is the unique name assigned to the text object 

    @return Returns true if the text exists, otherwise it returns
    false.

   */
  bool hasText(const std::string& name);

  //! Get text from the text manager

  /*!

    @param name is the unique name assigned to the text object

    @return The text object
    
    TODO: Exception handling.

   */
  std::shared_ptr<sf::Text> getText(const std::string& name);
  
  //! Add font to the text manager

  /*!

    @param name is the unique name assigned to the text object
    @param font is the font object to be stored within the text manager.
    
   */
  void addFont(const std::string& name, std::shared_ptr<sf::Font> font);

  //! Remove font from the text manager

  /*!

    @param name is the unique name assigned to the text object

   */
  void removeFont(const std::string& name);

  //! Checks if font exists within the text manager

  /*!

    @param name is the unique name assigned to the text object
    
    @return Returns true if the font exists, otherwise returns false.
   */
  bool hasFont(const std::string& name);

  //! Get font from the text manager

  /*!

    @param name is the unique name assigned to the text object

    @return Returns the font object

    TODO: Exception handling.

   */
  std::shared_ptr<sf::Font> getFont(const std::string& name);
	
};

#endif //AE__TEXTMANAGER_H
