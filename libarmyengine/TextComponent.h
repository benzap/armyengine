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

    Holds the text component which is used to represent text on the
    screen.
    
*/

#ifndef AE__TEXTCOMPONENT_H
#define AE__TEXTCOMPONENT_H

//CLASSES
class TextComponent;

//INCLUDES
#include <string>

#include "AbstractComponent.h"

//! Used to display text on the screen representing an entity.

/*!

  The text component inherits the abstract component, and is used to
  show text on the screen. Different attributes assigned change how
  the text is displayed.

 */
class TextComponent : public AbstractComponent {
private:

public:
  //! Text component constructor

  /*!  The text component overrides the abstract component family to
    be "Text"

    @param name is the unique name assigned to the given text
    component.
    
   */
  TextComponent(std::string name);

  //! Updates the component to include any modifications

  /*!
    
    The text component update command needs to be called anytime an
    attribute is modified.

    @returns A zero value when it is successful.
    
   */
  int update();
};

#endif //AE__TEXTCOMPONENT_H
