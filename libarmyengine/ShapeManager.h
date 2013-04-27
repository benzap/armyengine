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

    The shape manager is used to add / store, retrieve shapes that are
    being used to represent certain entities on the screen.
    
*/

#ifndef AE__SHAPEMANAGER_H
#define AE__SHAPEMANAGER_H

//CLASSES
class ShapeManager;

//INCLUDES
#include <memory>
#include <map>
#include <string>

#include "SFML\Graphics.hpp"

//TYPEDEFS

//DEFINITIONS

//! Used to add / store, and then retrieve shapes for shape components

/*!  The shape manager is implemented as a singleton, which manages
  the shapes being used by the shape components representing certain
  entities on the screen.
 */
class ShapeManager {
 private:
  //! Used to store Circle shapes
  std::map<std::string, std::shared_ptr<sf::CircleShape>> circleShapeMap;
  //! Used to store Rectangle shapes
  std::map<std::string, std::shared_ptr<sf::RectangleShape>> rectangleShapeMap;
  //! Used to store Convex polygon shapes
  std::map<std::string, std::shared_ptr<sf::ConvexShape>> convexShapeMap;

  //! Empty Constructor
  ShapeManager() {
    
  }
 public:
  //! Singleton method to return the shape manager instance.

  /*!

    @return The shape manager instance

   */
  static ShapeManager* getInstance() {
    static ShapeManager _instance;
    return &_instance;
  }
  
  //! Add circle shape to the shape manager
  void addCircleShape(const std::string& name,
		      std::shared_ptr<sf::CircleShape> cshape);

  //! Remove circle shape from the shape manager
  void removeCircleShape(const std::string& name);

  //! Check if circle shape exists within the shape manager
  bool hasCircleShape(const std::string& name);

  //! Get the circle shape by the given key name
  std::shared_ptr<sf::CircleShape> getCircleShape(const std::string& name);


  //! Add rectangle shape to the shape manager
  void addRectangleShape(const std::string& name,
			 std::shared_ptr<sf::RectangleShape> rshape);

  //! Remove rectangle shape from the shape manager
  void removeRectangleShape(const std::string& name);

  //! Check if rectangle shape exists within the shape manager
  bool hasRectangleShape(const std::string& name);
  
  //! Get the rectangle shape by the given key name
  std::shared_ptr<sf::RectangleShape> getRectangleShape(const std::string& name);

  //! Add convex polygon to the shape manager
  void addConvexShape(const std::string& name,
		      std::shared_ptr<sf::ConvexShape> shape);

  //! Remove convex polygon from the shape manager
  void removeConvexShape(const std::string& name);

  //! Check if convex polygon exits with the shape manager
  bool hasConvexShape(const std::string& name);

  //! Get the convex polygon with the given key name
  std::shared_ptr<sf::ConvexShape> getConvexShape(const std::string& name);
};

#endif //AE__SHAPEMANAGER_H
