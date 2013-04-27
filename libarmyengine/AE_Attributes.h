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

    Describes common attributes used within the components
    
*/

#ifndef AE__ATTRIBUTES_H
#define AE__ATTRIBUTES_H

//INCLUDES
#include "SFML\Graphics\Color.hpp"

//****************************************
//******* General Component Attributes ***
//****************************************

//! Represents a unique keyname

/*!
  
  When referring to components that depend on a given external object,
  this provides a facility to create and reference that external
  dependency when it is created.
*/
#define ATTRIBUTE_KEYNAME "KeyName"

//! Represents whether it has been created.
/*!
  
  is false, and set to true when the component's external dependencies
  have been created and referenced by the components KeyName

*/
#define ATTRIBUTE_CREATED "bCreated"


//!Determines whether the given component is enabled
#define ATTRIBUTE_ENABLE "bEnabled"

//!Contains the name of the callback
#define ATTRIBUTE_CALLBACK "Callback"


//! Represents depth

/*!

  for drawable components, determines the depth of that object based
  on this value. ex {0.0 gets drawn before 1.0}

*/
#define ATTRIBUTE_ZBUFFER "Z-Buffer"

//**************************************
//******* Shape Component Attributes ***
//**************************************

//! Represents the shape type to use
#define ATTRIBUTE_SHAPE_TYPE "Shape Type"

//! Circle Shape Type
#define SHAPETYPE_CIRCLE "Circle"

//! Rectangle Shape Type
#define SHAPETYPE_RECTANGLE "Rect"

//! Polygon Shape Type
#define SHAPETYPE_POLYGON "Polygon"

//different shape attributes

//! the radius, used with circle shapes
#define ATTRIBUTE_RADIUS "Radius"

//! the width, used with rectangle shapes
#define ATTRIBUTE_WIDTH "Width"

//! the height, used with rectangle shapes
#define ATTRIBUTE_HEIGHT "Height"

//! Attribute holding polygon points

/*!

  float array used with the polygon type for determining the
  shape. the number of points(x,y) determines the polygon
  ex. [x0,y0,x1,y1,x2,y2] --> 3 - point triangle
 
*/
#define ATTRIBUTE_POLYGON_POINTS "Attribute_Polygon_Points"

//! defines the fill color for red
#define ATTRIBUTE_FILL_COLOR_RED "Fill Color Red"
//! defines the fill color for green
#define ATTRIBUTE_FILL_COLOR_GREEN "Fill Color Green"
//! defines the fill color for blue
#define ATTRIBUTE_FILL_COLOR_BLUE "Fill Color Blue"
//! defines the fill color for alpha transparency
#define ATTRIBUTE_FILL_COLOR_ALPHA "Fill Color Alpha"

//! defines the outline color for red
#define ATTRIBUTE_OUTLINE_COLOR_RED "Outline Color Red"
//! defines the outline color for green
#define ATTRIBUTE_OUTLINE_COLOR_GREEN "Outline Color Green"
//! defines the outline color for blue
#define ATTRIBUTE_OUTLINE_COLOR_BLUE "Outline Color Blue"
//! defines the outline color for alpha transparency
#define ATTRIBUTE_OUTLINE_COLOR_ALPHA "Outline Color Alpha"

//! defines the outline thickness
#define ATTRIBUTE_OUTLINE_THICKNESS "Outline Thickness"

//*******************************************
//********* Position Component Attributes ***
//*******************************************

//! position attribute X
#define ATTRIBUTE_POSITION_X "Position_X"
//! position attribute Y
#define ATTRIBUTE_POSITION_Y "Position_Y"

//! position, sprite, and shape rotation
#define ATTRIBUTE_ROTATION "Rotation"

//******************************************************
//********* Sprite / Position Component Attributes *****
//******************************************************

//! Represents the sprite name

/*!

  this is the name of the sprite to be used, which is the key string
  representing a sprite within the sprite manager

*/
#define ATTRIBUTE_SPRITE_NAME "SpriteName"

//! Offset of the component from the position component X
#define ATTRIBUTE_OFFSET_X "Offset_X"
//! Offset of the component from the position component Y
#define ATTRIBUTE_OFFSET_Y "Offset_Y"

//! Represents the center origin for X

/*!

  determines the center origin of the sprite, which determines the
  origin point of positioning, and the origin point of rotation
 
*/
#define ATTRIBUTE_ORIGIN_X "Origin_X"
//! Represents the center origin for X

/*!

  determines the center origin of the sprite, which determines the
  origin point of positioning, and the origin point of rotation
 
*/
#define ATTRIBUTE_ORIGIN_Y "Origin_Y"

//! determines the scale of the the sprite, or shape X
#define ATTRIBUTE_SCALE_X "Scale_X"
//! determines the scale of the the sprite, or shape Y
#define ATTRIBUTE_SCALE_Y "Scale_Y"

//****************************************
//***** Collision Component Attributes ***
//****************************************
//! Represents the collision bound of a circle
#define COLLISION_BOUND_CIRCLE "Collision_Bound_Circle"
//! Represents the collision bound of a rectangle
#define COLLISION_BOUND_RECTANGLE "Collision_Bound_Rectangle"
//! Represents the collision bound of a polygon
#define COLLISION_BOUND_POLYGON "Collision_Bound_Polygon"
//! The attribute for representing the collision bound
#define ATTRIBUTE_COLLISION_BOUND_TYPE "Collision_Bound_Type"

//! Collision Tag for representing the given entity

/*!

  String identifier for the collision component, to determine how to
  handle the collision

 */
#define ATTRIBUTE_COLLISION_TAG "Collision_Tag"

//! The default collision tag
#define COLLISION_DEFAULT_TAG "Default"

//*******************************************
//******** Text Component Attributes ********
//*******************************************

//! Attribute which holds the raw string
#define ATTRIBUTE_TEXT_STRING "Text_String"

//! Represents the default raw string if none are assigned
#define DEFAULT_TEXT_STRING "Default Text"

//! Attribute for assigning the text size
#define ATTRIBUTE_TEXT_SIZE "Text_Size"

//! Attribute to enable or disable underline
#define ATTRIBUTE_TEXT_STYLE_UNDERLINE "Text_Style_Underline"

//! Attribute to enable or disable bold text
#define ATTRIBUTE_TEXT_STYLE_BOLD "Text_Style_Bold"

//! Attribute to enable or disable italic text
#define ATTRIBUTE_TEXT_STYLE_ITALIC "Text_Style_Italic"

//! Attribute to assign the font to use
#define ATTRIBUTE_TEXT_FONT "Text_Style_Font"

//*******************************************
//********* Input Component Attributes ******
//*******************************************

//! Attribute to assign the type of input for the input component
#define ATTRIBUTE_INPUT_TYPE "InputType"

#endif //AE__ATTRIBUTES_H
