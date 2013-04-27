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

    Is a factory for creating entities. The factory makes sure that
    each entity is assigned a unique ID.
    
*/

#ifndef AE__ENTITYFACTORY_H
#define AE__ENTITYFACTORY_H

//CLASSES
class EntityFactory;

//INCLUDES
#include <memory>

#include "Entities.h"

//! Factory for creating entities
class EntityFactory {
 private:
  //! Used to store the id counter.
  static int idNum;
 public:
  EntityFactory();

  //! Returns a newly created Main entity.

  /*!
    
    @param name is the unique name assigned to the entity.
    
    @return Returns the newly created entity.
  */
  std::shared_ptr<entityType> createMainEntity(std::string name);
};

#endif //AE__ENTITYFACTORY_H
