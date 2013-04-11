#ifndef AE__ATTRIBUTES_H
#define AE__ATTRIBUTES_H
//DESCRIPTION
/*
Describes common attributes used within the components
*/
//INCLUDES
#include "SFML\Graphics\Color.hpp"

//****************************************
//******* General Component Attributes ***
//****************************************

//When referring to components that depend on a given
// external object, this provides a facility to create and reference
// that external dependency when it is created.
#define ATTRIBUTE_KEYNAME "KeyName"

//is false, and set to true when the component's
// external dependencies have been created and referenced by
// the components KeyName
#define ATTRIBUTE_CREATED "bCreated"

//Determines whether the given component is enabled
// is not necessary for certain components.
#define ATTRIBUTE_ENABLE "bEnabled"
#define ATTRIBUTE_CALLBACK "Callback"


//for drawable components, determines the depth of that object
// based on this value. ex {0.0 gets drawn before 1.0}
#define ATTRIBUTE_ZBUFFER "Z-Buffer"

//**************************************
//******* Shape Component Attributes ***
//**************************************

#define ATTRIBUTE_SHAPE_TYPE "Shape Type"
//shape type, used to define the type of shape
#define SHAPETYPE_CIRCLE "Circle"
#define SHAPETYPE_RECTANGLE "Rect"
#define SHAPETYPE_POLYGON "Polygon"

//different shape attributes

//the radius, used with Circle
#define ATTRIBUTE_RADIUS "Radius"

//the width, used with Rectangle
#define ATTRIBUTE_WIDTH "Width"

//the height, used with Rectangle
#define ATTRIBUTE_HEIGHT "Height"

//float array used with the polygon type for determining
 //the shape. the number of points(x,y) determines the
 //polygon ex. [x0,y0,x1,y1,x2,y2] --> 3 - point triangle
#define ATTRIBUTE_POLYGON_POINTS "Attribute_Polygon_Points"

//defines the fill colors (inside color)
#define ATTRIBUTE_FILL_COLOR_RED "Fill Color Red"
#define ATTRIBUTE_FILL_COLOR_GREEN "Fill Color Green"
#define ATTRIBUTE_FILL_COLOR_BLUE "Fill Color Blue"
#define ATTRIBUTE_FILL_COLOR_ALPHA "Fill Color Alpha"

//defines the outline color (outside color)
#define ATTRIBUTE_OUTLINE_COLOR_RED "Outline Color Red"
#define ATTRIBUTE_OUTLINE_COLOR_GREEN "Outline Color Green"
#define ATTRIBUTE_OUTLINE_COLOR_BLUE "Outline Color Blue"
#define ATTRIBUTE_OUTLINE_COLOR_ALPHA "Outline Color Alpha"

//defines the outline thickness
#define ATTRIBUTE_OUTLINE_THICKNESS "Outline Thickness"

//*******************************************
//********* Position Component Attributes ***
//*******************************************

//position attributes
#define ATTRIBUTE_POSITION_X "Position_X"
#define ATTRIBUTE_POSITION_Y "Position_Y"

//position, sprite, and shape rotation
#define ATTRIBUTE_ROTATION "Rotation"

//******************************************************
//********* Sprite / Position Component Attributes *****
//******************************************************

//this is the name of the sprite to be used, which is the key string
// representing a sprite within the sprite manager
#define ATTRIBUTE_SPRITE_NAME "SpriteName"

//is the offset of the sprite from the position component
#define ATTRIBUTE_OFFSET_X "Offset_X"
#define ATTRIBUTE_OFFSET_Y "Offset_Y"

//determines the center origin of the sprite, which determines
 //the origin point of positioning, and the origin point of rotation
#define ATTRIBUTE_ORIGIN_X "Origin_X"
#define ATTRIBUTE_ORIGIN_Y "Origin_Y"

//determines the scale of the the sprite, or shape
#define ATTRIBUTE_SCALE_X "Scale_X"
#define ATTRIBUTE_SCALE_Y "Scale_Y"

//****************************************
//***** Collision Component Attributes ***
//****************************************
//Types of collision bounds to use for collision handling
#define COLLISION_BOUND_CIRCLE "Collision_Bound_Circle"
#define COLLISION_BOUND_RECTANGLE "Collision_Bound_Rectangle"
//polygon bound uses the same attribute as SHAPETYPE_POLYGON
// for representing the collision bound
// ATTRIBUTE_POLYGON_POINTS
#define COLLISION_BOUND_POLYGON "Collision_Bound_Polygon"
#define ATTRIBUTE_COLLISION_BOUND_TYPE "Collision_Bound_Type"

//String identifier for the collision component, to determine
 //how to handle the collision
#define ATTRIBUTE_COLLISION_TAG "Collision_Tag"
#define COLLISION_DEFAULT_TAG "Default"

//*******************************************
//******** Text Component Attributes ********
//*******************************************

#define ATTRIBUTE_TEXT_STRING "Text_String"
#define DEFAULT_TEXT_STRING "Default Text"
#define ATTRIBUTE_TEXT_SIZE "Text_Size"
#define ATTRIBUTE_TEXT_STYLE_UNDERLINE "Text_Style_Underline"
#define ATTRIBUTE_TEXT_STYLE_BOLD "Text_Style_Bold"
#define ATTRIBUTE_TEXT_STYLE_ITALIC "Text_Style_Italic"

#define ATTRIBUTE_TEXT_FONT "Text_Style_Font"

//*******************************************
//********* Input Component Attributes ******
//*******************************************

#define ATTRIBUTE_INPUT_TYPE "InputType"

#endif //AE__ATTRIBUTES_H