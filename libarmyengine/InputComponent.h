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
    
    Contains the input component, used for giving an entity special
    input privileges when it is enabled.
    
*/

#ifndef AE__INPUTCOMPONENT_H
#define AE__INPUTCOMPONENT_H

//CLASSES
class InputComponent;

//INCLUDES
#include "AbstractComponent.h"
#include "AE_Events.h"
//TYPEDEFS

//DEFINITIONS
#define COMPONENT_FAMILY_INPUT "Input"

//! Used to give an entity control over specific inputs from the user.

/*!

  Input component is a special StateComponent that will trigger a
  callback when a provided input is used.
  
  Provided inputs include "Keyboard" and "Mouse" Depending on which
  one is chosen, the resulting attributes searched will also vary.

 */
class InputComponent : public AbstractComponent {
 private:
  
 public:
  //! Constructor

  /*!
    
    @param name is the unique name assigned to this component. The
    family is overriden from the abstract component to be "Input"
   */
  InputComponent(std::string name);
  
  //! Not implemented
  int update();
};
#endif //AE__INPUTCOMPONENT_H
