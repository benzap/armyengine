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

    A set of utilities and globally dependant constants shared
    
*/

#ifndef AE__UTILITIES_H
#define AE__UTILITIES_H

//DEFINITIONS

//! The math constant Pi
#define PI 3.14159265359f

//INCLUDES
#include "AbstractComponent.h"

//CLASSES

//CLASS TEMPLATES

//FUNCTIONS

//!The dot product between two point vectors (x0,y0) and (x1,y1)

/*!
  
  @param x0 is the x component of the first vector
  @param y0 is the y component of the first vector
  @param x1 is the x component of the second vector
  @param y1 is the y component of the second vector

  @return The dot product of the two vectors
  
 */
template<class T> 
T Dot(T x0, T y0, T x1, T y1);

//! The cross product between two point vectors (x0,y0) and (x1,y1)

/*!

  @param x0 is the x component of the first vector
  @param y0 is the y component of the first vector
  @param x1 is the x component of the second vector
  @param y1 is the y component of the second vector

  @return The cross product of the two vectors

 */
template<class T>
T Cross(T x0, T y0, T x1, T y1);

//!  Checks if the three points, when traversed performs a CCW movement.

/*!

  This check is used to determine the winding for the positioning of
  points on the screen. This is useful in determining the winding,
  which decides on which way the face of the triangle is
  facing. Counter-clockwise points represents a face pointing out of
  the screen, with a clockwise motion representing the face pointing
  into the screen.

  @param x0 is the x component of the first vector
  @param y0 is the y component of the first vector
  @param x1 is the x component of the second vector
  @param y1 is the y component of the second vector
  @param x2 is the x component of the third vector
  @param y2 is the y component of the third vector

  @return Returns true if the triangle is formed CCW, otherwise
  returns false.
 */
template<class T>
bool triangleIsCCW(
	T x0, T y0,
	T x1, T y1,
	T x2, T y2);

//! Returns the area of the triangle (May return negative area)

/*!
  
  The three points form a triangle, and this function returns the area
  of that triangle. If the triangle was formed with a CCW winding, the
  area returned will be positive, otherwise the area returned will be
  negative.

  @param x0 is the x component of the first vector
  @param y0 is the y component of the first vector
  @param x1 is the x component of the second vector
  @param y1 is the y component of the second vector
  @param x2 is the x component of the third vector
  @param y2 is the y component of the third vector
  
  @return The area of the triangle (+ if CCW, - if CW)

 */

template<class T>
T triangle2DArea(
	T x0, T y0,
	T x1, T y1,
	T x2, T y2);


//! Checks to see if the point is within the bounds of the polygon.

/*!  

  NOTE: The polygon is assumed to be a convex polygon. This test is
  not effective when determining the point within a non-convex
  polygon, which would require further testing.

  @param px0 is the point x component.
  @param py0 is the point y component.
  @param polygon is a list of points making up the polygon.

  @return Returns true if the point is within the polygon, otherwise
  it returns false.

 */
bool pointInPolygon(float px0, float py0,
		    const componentFloatArrayType& polygon);

//! Checks if the two line segments are intersecting.

/*!
  
  The check forms two line segments between the given points, and
  determines whether they are intersecting. This test can be performed
  on non-convex shapes, but is very inefficient.
  
  @param ax0 is the first x component for the first line segment
  @param ay0 is the first y component for the first line segment
  @param ax1 is the second x component for the first line segment
  @param ay1 is the second y component for the first line segment

  @param bx0 is the first x component for the second line segment
  @param by0 is the first y component for the second line segment
  @param bx1 is the second x component for the second line segment
  @param by1 is the second y component for the second line segment

  @return Returns true if the two line segments intersect, otherwise
  it returns false.

 */
bool Test2DLineIntersection(
	float ax0, float ay0, float ax1, float ay1,
	float bx0, float by0, float bx1, float by1);

//! checks the intersection of the line segments between two polygons

/*!  

  This is a very robust and performance heavy test that checks for the
  intersection of each line segment of the first polygon to the second
  polygon.

  @polygon1 Is the first polygon
  @polygon2 Is the second polygon

  @return Returns whether the two polygons are intersecting, otherwise
  it returns false.

 */
bool checkPolygonLineIntersections(const componentFloatArrayType& polygon1,
				   const componentFloatArrayType& polygon2);

//MACROS
//...
#endif //AE__UTILITIES_H
