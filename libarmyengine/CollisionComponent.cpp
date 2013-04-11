#include "CollisionComponent.h"
#include "AE_Attributes.h"

CollisionComponent::CollisionComponent(std::string name) :
	AbstractComponent(name, "Collision") {
	//Determines whether the given shape should be shown
		//0 - disable
		//1 - enable
	setAttribute_int(ATTRIBUTE_ENABLE, 1);

	//the collision tag, which is an identifier for determining the collision
	 //provides the manager with unique collisions to provide callbacks for
	setAttribute_string(ATTRIBUTE_COLLISION_TAG, COLLISION_DEFAULT_TAG);

	//the collision bound shape type
	setAttribute_string(ATTRIBUTE_COLLISION_BOUND_TYPE, COLLISION_BOUND_RECTANGLE);

	//the collision bound attributes
	//  rectangle depends on width and height
	//  circle depends on radius

	//width of the rectangle bound (x)
	setAttribute_float(ATTRIBUTE_WIDTH, 0.0);
	//height of the rectangle bound (y)
	setAttribute_float(ATTRIBUTE_HEIGHT, 0.0);
	//radius of the circle bound (r)
	setAttribute_float(ATTRIBUTE_RADIUS, 0.0);
	//Used by polygons to represent the points making up the bounds
	setAttribute_floatArray(ATTRIBUTE_POLYGON_POINTS, componentFloatArrayType());

	//Related Sprite attributes
	//This provides the offset of the collision bound from its origin within the X and Y direction
	this->setAttribute_float(ATTRIBUTE_OFFSET_X, 0.0);
	this->setAttribute_float(ATTRIBUTE_OFFSET_Y, 0.0);

	//Is the origin of the collision bound with respect to the
	  //position component
	this->setAttribute_float(ATTRIBUTE_ORIGIN_X, 0.0);
	this->setAttribute_float(ATTRIBUTE_ORIGIN_Y, 0.0);

}

int CollisionComponent::update() {
	return 0;
}