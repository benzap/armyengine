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

    Is a factory for creating components.
    
*/

#ifndef AE__COMPONENTFACTORY_H
#define AE__COMPONENTFACTORY_H

//CLASSES
class ComponentFactory;

//INCLUDES
#include <memory>

#include "Components.h"

//! Used to create components to assign to entities.
class ComponentFactory {
 private:
  
 public:
  ComponentFactory();
  
  //! Used to create CollisionComponent
  
  /*!

    @param name is the unique name to be assigned to the component
    
    @return Returns the newly created component.
  */
  std::shared_ptr<componentType> createCollisionComponent(std::string name);

  //! Used to create HealthComponent
  
  /*!

    @param name is the unique name to be assigned to the component
    
    @return Returns the newly created component.
  */
  std::shared_ptr<componentType> createHealthComponent(std::string name);

  //! Used to create InputComponent
  
  /*!

    @param name is the unique name to be assigned to the component
    
    @return Returns the newly created component.
  */
  std::shared_ptr<componentType> createInputComponent(std::string name);

  //! Used to create PositionComponent
  
  /*!

    @param name is the unique name to be assigned to the component
    
    @return Returns the newly created component.
  */
  std::shared_ptr<componentType> createPositionComponent(std::string name);

  //! Used to create ShapeComponent
  
  /*!

    @param name is the unique name to be assigned to the component
    
    @return Returns the newly created component.
  */
  std::shared_ptr<componentType> createShapeComponent(std::string name);

  //! Used to create SpriteComponent
  
  /*!

    @param name is the unique name to be assigned to the component
    
    @return Returns the newly created component.
  */
  std::shared_ptr<componentType> createSpriteComponent(std::string name);

  //! Used to create StateComponent
  
  /*!

    @param name is the unique name to be assigned to the component
    
    @return Returns the newly created component.
  */
  std::shared_ptr<componentType> createStateComponent(std::string name);

  //! Used to create TextComponent
  
  /*!

    @param name is the unique name to be assigned to the component
    
    @return Returns the newly created component.
  */
  std::shared_ptr<componentType> createTextComponent(std::string name);
};


#endif //AE__COMPONENTFACTORY_H
