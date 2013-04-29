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

    Contains the collision system used to determine whether two
    entities with collision components are colliding. If they are
    colliding, it calls the necessary collision callbacks.
    
*/

#ifndef AE__COLLISION_SYSTEM
#define AE__COLLISION_SYSTEM

//CLASSES
class CollisionSystem;

//INCLUDES
#include <memory>
#include <tuple>

#include "EntityManager.h"
#include "CollisionManager.h"
#include "AbstractSystem.h"

//TYPEDEFS

//DEFINITIONS

//defines the number of points to describe a circle
// when comparing a circle to a polygon
#define SYNTH_CIRCLE_POINT_NUM 20

//! Used to process collisions.

/*!  

  Processes collision components with a position component and checks
  to see if the entity containing the collision component is colliding
  with another entity containing another collision component
  
  If it determines that the two components have collided, the system
  performs the desired callback within the CollisionManager and
  includes information about both components to the callback 

*/
class CollisionSystem : public AbstractSystem {
 private:
  //! Reference to the collision manager singleton
  CollisionManager* collisionManager;
  //! Reference to the entity manager singleton
  EntityManager* entityManager;
  
  //! used to check the collision between two rectangle collision bounds
  bool collision_rect_rect(
			   const std::shared_ptr<AbstractComponent> pos1component,
			   const std::shared_ptr<AbstractComponent> col1component,
			   const std::shared_ptr<AbstractComponent> pos2component,
			   const std::shared_ptr<AbstractComponent> col2component);

  //! used to check the collision between two circle collision bounds
  bool collision_circle_circle(const std::shared_ptr<AbstractComponent> pos1component,
			       const std::shared_ptr<AbstractComponent> col1component,
			       const std::shared_ptr<AbstractComponent> pos2component,
			       const std::shared_ptr<AbstractComponent> col2component);

  //! used to check the collision between a rectangle and a circle
  bool collision_rect_circle(const std::shared_ptr<AbstractComponent> pos1component,
			     const std::shared_ptr<AbstractComponent> col1component,
			     const std::shared_ptr<AbstractComponent> pos2component,
			     const std::shared_ptr<AbstractComponent> col2component);

  //! used to check the collision between a rectangle and a polygon
  bool collision_rect_polygon(const std::shared_ptr<AbstractComponent> pos1component,
			      const std::shared_ptr<AbstractComponent> col1component,
			      const std::shared_ptr<AbstractComponent> pos2component,
			      const std::shared_ptr<AbstractComponent> col2component);

  //! used to check the collision between two polygons
  bool collision_polygon_polygon(const std::shared_ptr<AbstractComponent> pos1component,
				 const std::shared_ptr<AbstractComponent> col1component,
				 const std::shared_ptr<AbstractComponent> pos2component,
				 const std::shared_ptr<AbstractComponent> col2component);

  //! used to check the collision between a polygon and a circle
  bool collision_circle_polygon(const std::shared_ptr<AbstractComponent> pos1component,
				const std::shared_ptr<AbstractComponent> col1component,
				const std::shared_ptr<AbstractComponent> pos2component,
				const std::shared_ptr<AbstractComponent> col2component);

 public:
  CollisionSystem();

  //! Processes the entities with collision components

  /*!
    
    This method is run on each frame.

    It checks each of the entities for a collision component and a
    position component. And performs checks between entities that
    could potentialy perform a collision callback. If they are checked
    and it turns out they are colliding, the callback is triggered
    with information pertaining to the two entities affected.

   */
  int process();
};
#endif //AE__COLLISION_SYSTEM
