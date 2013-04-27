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

    Contains the abstract for the entities within the entity
    component system

*/

#ifndef AE__ABSTRACTENTITY_H
#define AE__ABSTRACTENTITY_H

//CLASSES
class AbstractEntity;

//INCLUDES
#include <map>
#include <vector>
#include <memory>

#include "AbstractComponent.h"

//TYPEDEFS

//! Typedef to abstract the abstract...
typedef AbstractEntity entityType;

//! The type used to store components within the entity
typedef std::vector<std::shared_ptr<componentType>> componentVectorType;

//! The abstract representation for each entity

/*!  The abstract entity contains methods to add, delete, and retrieve
  components, as well as a plethora of methods to find components by a
  given family, or by a given name.

  Each entity should have a unique assigned to it, which is preserved
  by using the ArmyEngine::EntityFactory.
 */
class AbstractEntity {
private:
  //! Vector that holds all of the components
  componentVectorType componentVector;
  int ID; //!< The unique ID assigned to the given entity.
  std::string name; //!< The unique name assigned to the given entity.
  //! The family that the entity belongs to.

  /*! The family for the entity should be overloaded upon inheriting,
    and should be a unique family.
  */
  std::string family;
public:
  //! AbstractEntity Constructor
  AbstractEntity(const std::string&, const std::string& ,const int);
  //~AbstractEntity();
  
  //! Getter for the name

  /*!
    @return The name of the entity
   */
  const std::string& getName();

  //! Getter for the family

  /*!
    @return The family of the entity
   */
  const std::string& getFamily();

  //! Getter for the ID

  /*!
    @return The unique ID of the entity
  */
  int getID();

  //! Check to see if a given component exists with the given name

  /*!  
    @param name Is the unique name of the component you wish to find.

    @return Returns true if a component exists with the given name,
    otherwise it returns false.
  */
  bool hasComponentName(const std::string& name);

  //! Check to see if any component exists with the given family

  /*!  
    @param family Is the family of the component you wish to find.

    @return Returns true if a component exists with the given family,
    otherwise it returns false.
  */
  bool hasComponentFamily(const std::string& family);


  //! Add a component to given entity

  /*!  

    @param component Is the shared_ptr of the component you wish to
    add the to the given entity.
  */
  void addComponent(std::shared_ptr<componentType> component);

  //! Grab all of the components currently within the entity.

  /*!
    
    @return The list of all components within the entity.
   */
  const componentVectorType& getAllComponents();
  
  
  //! Returns a list of components which belongs to the given family

  /*!
    
    @param family Is the family of components that you wish to return.

    @return The list of all components with the given family.
   */
  std::list<std::shared_ptr<componentType>> getComponentsByFamily(const std::string& family);
  
  //! Returns a component by its given name

  /*!
    
    @param name of the component

    @return the component, otherwise it returns shared_ptr(nullptr)
   */
  std::shared_ptr<componentType> getComponentByName(const std::string& name);
  
  //!virtual function to perform pre-initialization and handling
  
  /*!  

    Currently it is being used to sort the shape, text, and sprite
    components to provide Z-buffer ordering. It is advised that this
    method be used if any components are added during execution to
    prevent erroneous behaviour.

    @return A non-zero value when it is successful.
  */
  virtual int handle() = 0;
};

#endif //AE__ABSTRACTENTITY_H
