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

    The entity manager is used to store and manage all of the entities
    that are currently within the game.

*/

#ifndef AE__ENTITYMANAGER_H
#define AE__ENTITYMANAGER_H

//CLASSES
class EntityManager;

//INCLUDES
#include <vector>
#include <list>
#include <memory>
#include <mutex>

#include "AbstractEntity.h"

//TYPEDEFS

//! Type used to store the vector list of entities
typedef std::vector<std::shared_ptr<entityType>> entityVectorType;
//! Type used to store temporary lists of entities when retrieving
typedef std::list<std::shared_ptr<entityType>> entityListType;

//! The entity manager used to store and manager entities

/*! The entity manager is a singleton that has methods to add / store,
  remove, retrieve one or many entities. Any entities that you want to
  be processed within the engine should be added to the entity
  manager.
 */
class EntityManager {
private:
  entityVectorType entityList; //!< The vector list of entities

  EntityManager() {} //!< Empty Constructor

public:
  //! Singleton method to grab the entity manager instance.

  /*!
    
    @return The entity manager instance.
  */
  static EntityManager* getInstance() {
    static EntityManager _instance;
    return &_instance;
  }
  
  //! Add entity to the entity manager

  /*! Used to add an entity to the entity manager. The entity needs
    to be in the form of a shared_ptr.

    @param entity is the shared_ptr of the entity you wish to add.
  */
  void addEntity(std::shared_ptr<entityType> entity);

  //! Remove entity from the entity manager

  /*!  Used to remove entity from the entity manager. This does not
    necessarily deallocate the entity if references are still made
    between with the shared_ptr.

    @param entity is the shared_ptr of the entity.

   */
  void removeEntity(std::shared_ptr<entityType> entity);
  
  //! Checks if an entity with the given ID exists within the manager

  /*!
    
    @param ID is the unique identifier for the entity

    @return Returns true if the entity with the given ID exists,
    otherwise it returns false.
   */
  bool hasEntityById(const int ID);

  //! Gets the first entity with the given unique ID

  /*!
    
    @param ID is the unique identifier for the entity
    
    @return The entity, or a shared_ptr(nullptr) if the entity does
    not exist.
   */
  std::shared_ptr<entityType> getEntityById(const int ID);

  //! Gets all of the entities within the manager

  /*!
    
    @return The list of all the entities.
   */
  entityVectorType getAllEntities();

  //! Gets all of the entities by the given name.

  /*!  This list returned will contain all of the entities with the
    given name. This suggests that entities do not have a unique name,
    which would be correct. TODO: fix this.

    @param entityName is the name of the entities you wish to
    retrieve.

    @return The method returns a list of entities with the given name
   */
  entityListType getEntitiesByName(const std::string& entityName);

  //! Gets all of the entities with the given family

  /*!  This list returned will contain all entities that belong to the
    same family.

    @param entityFamily is the family you wish to retrieve

    @return The method returns a list of entities that are a part of
    the given family.
   */
  entityListType getEntitiesByFamily(const std::string& entityFamily);
  
  //! operation sorts the entityList based on a sorting criteria

  /*!  The entityList stored within the entity manager is currently
    being sorted baed on the lowest Z-Buffer value for components
    stored within each entity. Given the large number of entities that
    would likely be present, this would present a very unwelcome
    performance hit if it is called each frame.
   */
  void sortEntityList();
};
#endif //AE__ENTITYMANAGER_H
