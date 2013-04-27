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

    Collision manager is used to manage what happens when two entities
    collide with eachother.  Callbacks are added to the collision
    manager to handle situations where given collision types collide.
    Depending on the type of collision, the resulting collision may be
    handled differently.

    For example Player tagged "Player" collides with a wall
    "Physical", which will invoke a collision callback to prevent the
    character from moving in that direction. It must also be noted
    that a second callback where the wall collides with the player
    will also be invoked.

    Information for the callback includes a tuple, which includes 5
    values. These 5 values should be enough to perform all the
    functions desired tuple<entity id 1, collisioncomponent name 1,
    entity id 2, collisioncomponent name 2, bRegistered>

    the callback is chosen based on the pair<collisiontag1,
    collisiontag2> which needs to be registered within the manager.
    
*/

#ifndef AE__COLLISIONMANAGER_H
#define AE__COLLISIONMANAGER_H

//CLASSES
class CollisionManager;

//INCLUDES
#include <memory>
#include <functional>
#include <map>
#include <string>
#include <tuple>
#include <list>

//TYPEDEF

//! Tuple for storing collision information as a parameter

/*!
  tuple for storing
  
  first collided entity id and collisioncomponent name
  
  second collided entity id and collisioncomponent name
  
  last value is a boolean representing if it has stopped colliding.
*/
typedef std::tuple<int, std::string, int, std::string, bool> collisionParamTuple;

//! Tuple for storing collision information as a callback

/*!
  tuple for storing
  
  first collided entity id and collisioncomponent name
  
  second collided entity id and collisioncomponent name
 */
typedef std::tuple<int, std::string, int, std::string> registeredCollisionTuple;

//! Pair Tuple that holds two collision tags

/*!
  pair tuple holding 
  first collision tag attribute string
  second collision tag attribute string
*/
typedef std::pair<std::string, std::string> collisionTagTuple;

//! Function Type to assign to the callback
typedef std::function<int(collisionParamTuple)> functionCollisionTemplate;

//! Type to hold the callbacks
typedef std::map<collisionTagTuple, functionCollisionTemplate> collisionCallbackTableType;

//! Type for holding registered collisions
typedef std::list<registeredCollisionTuple> registeredCollisionListType;

//! Collision manager used to perform callbacks on collisions

/*!  

  Collision manager is used to manage what happens when two entities
  collide with eachother.  Callbacks are added to the collision
  manager to handle situations where given collision types collide.
  Depending on the type of collision, the resulting collision may be
  handled differently.
 */
class CollisionManager {
private:
  //! table holding the callbacks
  collisionCallbackTableType callbackTable;

  //! list holding currently collided entities
  registeredCollisionListType registeredCollisionList;
  
  //! Singleton, empty constructor
  CollisionManager() {}
public:
  //! Singleton method, returns an instance of the manager

  /*!
    
    @return The instance of the CollisionManager
   */
  static CollisionManager* getInstance() {
    static CollisionManager _instance;
    return &_instance;
  }

  //! used to add a callback to the callback table

  /*!  

    @param tagTuple is two tags representing the type of collision
    performed.

    @param func is the function to assign as a callback when the
    collision is performed.
   */
  void addCallback(const collisionTagTuple& tagTuple, functionCollisionTemplate func);
  
  //! called by the collision system to trigger a desired callback

  /*!  
    
    @param tagTuple is two tags representing the type of collision
    performed.

    @param paramTuple is the parameters to bind to the given callback
    described by the tagTuple.
   */
  int triggerCallback(const collisionTagTuple& tagTuple, const collisionParamTuple& paramTuple);
  
  //! deletes the callback described by the provided tuple

  /*
    
    @param tagTuple is two tags representing the type of collision
    performed.
   */
  void removeCallback(const collisionTagTuple& tagTuple);
  
  //! checks if the callback table has the provided tag

  /*!
    
    @param tagTuple is two tags representing the type of collision
    performed. 
   */
  bool hasCallback(const collisionTagTuple& tagTuple);
  
  //! registers the collision within the list

  /*!
    
    @param theTuple is a unique description for a collision performed
    between two entities
  */
  void registerCollision(const registeredCollisionTuple& theTuple);
  
  //! unregisters and removes from the list

  /*!
    
    @param theTuple is a unique description for a collision performed
    between two entities
  */
  void unregisterCollision(const registeredCollisionTuple& theTuple);
  
  //! checks to see if the current collision is registered

  /*!
    
    @param theTuple is a unique description for a collision performed
    between two entities
  */
  bool hasRegisteredCollision(const registeredCollisionTuple& theTuple);
};
#endif //AE__COLLISIONMANAGER_H
