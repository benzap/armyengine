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

    Shape Component is a lot like sprite component, but has several
    predefined shapes which don't require a sprite in order to express
    them visually on the screen.
    
*/

#ifndef AE__SHAPECOMPONENT_H
#define AE__SHAPECOMPONENT_H

//CLASSES
class ShapeComponent;

//INCLUDE
#include <string>

#include "AbstractComponent.h"

//! Is used to express the entity as a shape on the screen.

/*! 
  
  The shape component can be used to show the entity on the screen as
  the expressed shape as outlined in this shape components attributes.

  The shape component has also been fashioned to produce polygons.
*/
class ShapeComponent : public AbstractComponent {
 private:
  
 public:
  //! The constructor for shape component

  /*!  The shape component has overriden the family by using "Shape."
    New components that inherit from the abstract component should not
    consider using this family name.
    
    @param name is the unique name assigned to a created component.

  */
  ShapeComponent(std::string name);
  
  //! updates the shape component when modifications are made.
  
  /*! It is important to perform updates on the shape component after
    any modifications are made during execution. Otherwise the effects
    will not be displayed on the screen.

    @return Returns a zero value if the update was successful.
  */
  int update();
};


#endif //AE__SHAPECOMPONENT_H
