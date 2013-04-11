#include <cassert>

#include "ShapeComponent.h"
#include "ShapeManager.h"
#include "AE_Attributes.h"

ShapeComponent::ShapeComponent(std::string name) :
	AbstractComponent(name, "Shape") {
	std::string keyname = name + std::to_string(reinterpret_cast<int>(this));
	//unique keyname for our referenced text object

	auto shapeManager = ShapeManager::getInstance();
	//we don't know what type of shape it's going to be, so to simplify,
	// just going to create one of each and decide from there
	shapeManager->addCircleShape(keyname, std::shared_ptr<sf::CircleShape> (new sf::CircleShape()));
	shapeManager->addRectangleShape(keyname, std::shared_ptr<sf::RectangleShape> (new sf::RectangleShape()));
	shapeManager->addConvexShape(keyname, std::shared_ptr<sf::ConvexShape> (new sf::ConvexShape()));

	//***********************************
	//********** ATTRIBUTES *************
	//***********************************

	//the keyname is stored as an attribute for later retrieval
	setAttribute_string(ATTRIBUTE_KEYNAME, keyname);

	//Determines whether the given shape should be shown
		//0 - disable
		//1 - enable
	setAttribute_int(ATTRIBUTE_ENABLE, 1);

	//The shape type
	setAttribute_string(ATTRIBUTE_SHAPE_TYPE, SHAPETYPE_CIRCLE);

	//The shape attributes
	setAttribute_float(ATTRIBUTE_RADIUS, 0.0);
	setAttribute_float(ATTRIBUTE_WIDTH, 0.0);
	setAttribute_float(ATTRIBUTE_HEIGHT, 0.0);
	setAttribute_floatArray(ATTRIBUTE_POLYGON_POINTS, componentFloatArrayType());

	//The shape fill
	setAttribute_int(ATTRIBUTE_FILL_COLOR_RED, 255);
	setAttribute_int(ATTRIBUTE_FILL_COLOR_GREEN, 255);
	setAttribute_int(ATTRIBUTE_FILL_COLOR_BLUE, 255);
	setAttribute_int(ATTRIBUTE_FILL_COLOR_ALPHA, 255);

	//The shape outline
	setAttribute_int(ATTRIBUTE_OUTLINE_COLOR_RED, 255);
	setAttribute_int(ATTRIBUTE_OUTLINE_COLOR_GREEN, 255);
	setAttribute_int(ATTRIBUTE_OUTLINE_COLOR_BLUE, 255);
	setAttribute_int(ATTRIBUTE_OUTLINE_COLOR_ALPHA, 255);

	//The shape outline thickness
	setAttribute_float(ATTRIBUTE_OUTLINE_THICKNESS, 1.0);

	//Related Sprite attributes
	//This provides the offset of the sprite from its origin within the X and Y direction
	    //Useful for a multisprite entity, you provide an offset to change its placement
	this->setAttribute_float(ATTRIBUTE_OFFSET_X, 0.0);
	this->setAttribute_float(ATTRIBUTE_OFFSET_Y, 0.0);

	//This provides the origin, or center point where rotation and the point of positioning is determined
	this->setAttribute_float(ATTRIBUTE_ORIGIN_X, 0.0);
	this->setAttribute_float(ATTRIBUTE_ORIGIN_Y, 0.0);

	//Provides the depth of the sprite, lower means farther away, which means it
	    //will get covered by anything with a higher z-buffer {ex A(0.1) covers B(0.0)}
	this->setAttribute_float(ATTRIBUTE_ZBUFFER, 1.0);

	//The scale of the sprite being used
		//relative to the position component
	this->setAttribute_float(ATTRIBUTE_SCALE_X, 1.0);
	this->setAttribute_float(ATTRIBUTE_SCALE_Y, 1.0);

	//Determines the rotation of the sprite
		//relative to a given position component
		//given in radians
	this->setAttribute_float(ATTRIBUTE_ROTATION, 0.0);

	//perform an update on our component to form the default shape instance
	this->update();
}

int ShapeComponent::update() {
	auto shapeManager = ShapeManager::getInstance();
	
	auto shapeType = this->getAttribute_string(ATTRIBUTE_SHAPE_TYPE);
	if (shapeType == SHAPETYPE_CIRCLE) {
		auto theShape = shapeManager->getCircleShape(getAttribute_string(ATTRIBUTE_KEYNAME));

		//set the radius
		theShape->setRadius(getAttribute_float(ATTRIBUTE_RADIUS));

		//perform actions which are relevant to both the circle and shape
		//get the attributes related to the outline color and apply it to the shape
		theShape->setOutlineColor(sf::Color(
			getAttribute_int(ATTRIBUTE_OUTLINE_COLOR_RED),
			getAttribute_int(ATTRIBUTE_OUTLINE_COLOR_GREEN),
			getAttribute_int(ATTRIBUTE_OUTLINE_COLOR_BLUE),
			getAttribute_int(ATTRIBUTE_OUTLINE_COLOR_ALPHA)
			));
		
		//get attribute related to the outline thickness and apply to the shape
		float lineThickness = getAttribute_float(ATTRIBUTE_OUTLINE_THICKNESS);
		theShape->setOutlineThickness(lineThickness);
		
		//get attributes related to the fill color and apply it to the shape
		theShape->setFillColor(sf::Color(
			getAttribute_int(ATTRIBUTE_FILL_COLOR_RED),
			getAttribute_int(ATTRIBUTE_FILL_COLOR_GREEN),
			getAttribute_int(ATTRIBUTE_FILL_COLOR_BLUE),
			getAttribute_int(ATTRIBUTE_FILL_COLOR_ALPHA)));

	}
	else if (shapeType == SHAPETYPE_RECTANGLE) {
		auto theShape = shapeManager->getRectangleShape(getAttribute_string(ATTRIBUTE_KEYNAME));

		//set the width and height
		float rectWidth = getAttribute_float(ATTRIBUTE_WIDTH);
		float rectHeight = getAttribute_float(ATTRIBUTE_HEIGHT);
		theShape->setSize(sf::Vector2f(rectWidth, rectHeight));

		//perform actions which are relevant to both the circle and shape
		//get the attributes related to the outline color and apply it to the shape
		theShape->setOutlineColor(sf::Color(
			getAttribute_int(ATTRIBUTE_OUTLINE_COLOR_RED),
			getAttribute_int(ATTRIBUTE_OUTLINE_COLOR_GREEN),
			getAttribute_int(ATTRIBUTE_OUTLINE_COLOR_BLUE),
			getAttribute_int(ATTRIBUTE_OUTLINE_COLOR_ALPHA)
			));
		
		//get attribute related to the outline thickness and apply to the shape
		float lineThickness = getAttribute_float(ATTRIBUTE_OUTLINE_THICKNESS);
		theShape->setOutlineThickness(lineThickness);
		
		//get attributes related to the fill color and apply it to the shape
		theShape->setFillColor(sf::Color(
			getAttribute_int(ATTRIBUTE_FILL_COLOR_RED),
			getAttribute_int(ATTRIBUTE_FILL_COLOR_GREEN),
			getAttribute_int(ATTRIBUTE_FILL_COLOR_BLUE),
			getAttribute_int(ATTRIBUTE_FILL_COLOR_ALPHA)));
	}
	else if (shapeType == SHAPETYPE_POLYGON) {
		auto theShape = shapeManager->getConvexShape(getAttribute_string(ATTRIBUTE_KEYNAME));

		//find the polygon count
		auto polygonPoints = *this->getAttribute_floatArray(ATTRIBUTE_POLYGON_POINTS);
		assert((polygonPoints.size() % 2 == 0) && "Odd number of coordinates to describe polygon, must be even");
		int numPoints = polygonPoints.size() / 2;
		
		//set the number of points
		theShape->setPointCount(numPoints);

		//set the coordinates for each point
		for (int i = 0; i < numPoints; i++) {
			theShape->setPoint(i, sf::Vector2f(polygonPoints[i*2], polygonPoints[i*2+1]));
		}

		//perform actions which are relevant to both the circle and shape
		//get the attributes related to the outline color and apply it to the shape
		theShape->setOutlineColor(sf::Color(
			getAttribute_int(ATTRIBUTE_OUTLINE_COLOR_RED),
			getAttribute_int(ATTRIBUTE_OUTLINE_COLOR_GREEN),
			getAttribute_int(ATTRIBUTE_OUTLINE_COLOR_BLUE),
			getAttribute_int(ATTRIBUTE_OUTLINE_COLOR_ALPHA)
			));
		
		//get attribute related to the outline thickness and apply to the shape
		float lineThickness = getAttribute_float(ATTRIBUTE_OUTLINE_THICKNESS);
		theShape->setOutlineThickness(lineThickness);
		
		//get attributes related to the fill color and apply it to the shape
		theShape->setFillColor(sf::Color(
			getAttribute_int(ATTRIBUTE_FILL_COLOR_RED),
			getAttribute_int(ATTRIBUTE_FILL_COLOR_GREEN),
			getAttribute_int(ATTRIBUTE_FILL_COLOR_BLUE),
			getAttribute_int(ATTRIBUTE_FILL_COLOR_ALPHA)));
	}
	else {
		assert(0 && "Not shape by that type");
	}


	return 0;
}