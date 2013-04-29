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
    
    Contains the Main entity, which can be used for creating more
    complex entities. It can also be used to perform composition over
    inheritance. (Whichever floats your boat)
    
*/

#ifndef AE__MAINENTITY_H
#define AE__MAINENTITY_H

//INCLUDES
#include <string>
#include "AbstractEntity.h"

//CLASSES
class MainEntity;

//! Barebones inheritance of AbstractEntity. Overloaded family to "Main"
class MainEntity : public AbstractEntity {
 public:
  /*!  

    @param name is the name given to the particular entity. This name
    does not need to be unique.

    @param ID is the unique ID assigned to the entity. This does need
    to be unique.
   */
  MainEntity(std::string name, int ID);
  //~MainEntity();

  //! Handles the entity

  /*!  The main entity when handled, sorts the underlying components
    so that visual components are displayed in the correct order. This
    is done by sorting based on the Z-Buffer.
   */
  int handle();
};

#endif //AE__MAINENTITY_H
