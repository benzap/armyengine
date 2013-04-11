//INCLUDES
#include <iostream>
#include <memory>
#include <cassert>
#include <string>
#include <cmath>
#include <list>

#include "SFML\Graphics.hpp"

#include "SpriteManager.h"
#include "TextManager.h"
#include "ShapeManager.h"
#include "SpriteSystem.h"
#include "Components.h"
#include "AE_Utilities.h"
#include "AE_Attributes.h"

SpriteSystem::SpriteSystem(sf::RenderWindow& window) : 
	AbstractSystem("Sprite"), 
	window(window), 
	spriteManager(SpriteManager::getInstance()),
	textManager(TextManager::getInstance()),
	shapeManager(ShapeManager::getInstance()) {}

int SpriteSystem::process() {
	//first we need to grab the list of entities
	//for now, we're going to grab all of the entities
	auto entityVector = this->entityManager->getAllEntities();
	std::list<std::shared_ptr<entityType>> entityList;
	for (auto entityValue : entityVector) {
		entityList.push_back(entityValue);
	}
	//sort the entities based on it's Z-buffer. The sorting criteria is based on the minimum Z-buffer found
	// within the entities
	

	for (auto entity : entityList) {
		//determine if the entity has the desired components to work with
		if ((!entity->hasComponentFamily("Sprite") ||
			!entity->hasComponentFamily("Position")) &&
			(!entity->hasComponentFamily("Shape") ||
			!entity->hasComponentFamily("Position")) &&
			(!entity->hasComponentFamily("Text") ||
			!entity->hasComponentFamily("Position"))) {
			continue;
		}

		//grab all of the desired components
		auto theSpriteComponents = entity->getComponentsByFamily("Sprite");
		auto theShapeComponents = entity->getComponentsByFamily("Shape");
		auto theTextComponents = entity->getComponentsByFamily("Text");
		auto thePositionComponents = entity->getComponentsByFamily("Position");

		//merge the shape, sprite and text components within the same list
		std::list<std::shared_ptr<componentType>> drawableComponents;
		for (auto sprite : theSpriteComponents) {
			drawableComponents.push_back(sprite);
		}
		for (auto shape : theShapeComponents) {
			drawableComponents.push_back(shape);
		}

		for (auto text : theTextComponents) {
			drawableComponents.push_back(text);
		}

		//we need to sort the drawables based on the provided Z-Buffer Attribute
		drawableComponents.sort([] (std::shared_ptr<componentType> first, std::shared_ptr<componentType> second) {
			float zFirst = first->getAttribute_float(ATTRIBUTE_ZBUFFER);
			float zSecond = second->getAttribute_float(ATTRIBUTE_ZBUFFER);
			return (zFirst < zSecond);
		});

		//we are going limit the scope of entities to one position component for now
		assert(thePositionComponents.size() == 1 && "Entities are limited to one position component");

		//now we can just assume that we have only one position component
		auto positionComponent = thePositionComponents.front();

		//grab and store the position and rotation for our entities
		float positionX = positionComponent->getAttribute_float(ATTRIBUTE_POSITION_X);
		float positionY = positionComponent->getAttribute_float(ATTRIBUTE_POSITION_Y);

		float rotation = positionComponent->getAttribute_float(ATTRIBUTE_ROTATION);

		//next, we need to process each sprite component and offset it
		//by the position component
		//TODO: sort by Z-buffer
		for (auto theComponent : drawableComponents) {
			//first, we determine if the sprite is enabled to draw
			int bEnabled = theComponent->getAttribute_int(ATTRIBUTE_ENABLE);
			if (!bEnabled) {
				continue;
			}

			//Intialize our drawable ptr object
			std::shared_ptr<sf::Drawable> theDrawable;
			std::shared_ptr<sf::Transformable> theTransform;
			std::shared_ptr<sf::Shape> theShape;
			std::shared_ptr<spriteType> theSprite;
			std::shared_ptr<sf::CircleShape> theCircle;
			std::shared_ptr<sf::RectangleShape> theRectangle;
			std::shared_ptr<sf::ConvexShape> theConvexShape;
			std::shared_ptr<sf::Text> theText;

			//get our sprite from the shape component, or use the default
			if (theComponent->getFamily() == "Sprite") {
				bool bDefault = true;
				//get the name of the sprite key name being stored in the manager
				std::string spriteName = theComponent->getAttribute_string("SpriteName");
				//Check if the sprite being used is the default
				if (spriteName != "None") {
					bDefault = false;
				}

				//if it's a default, use the default sprite image
				if (bDefault) {
					theSprite = this->spriteManager->getSprite(DEFAULT_SPRITE);
				}
				//else, grab our sprite TODO: checking
				else { //bDefault == false
					theSprite = this->spriteManager->getSprite(spriteName);
				}

				//cast to a drawable and a transformable
				theTransform = std::static_pointer_cast<sf::Transformable> (theSprite);
				assert(theTransform != nullptr && "Nullptr in transform");
				theDrawable = std::static_pointer_cast<sf::Drawable> (theSprite);
				assert(theDrawable != nullptr && "Nullptr in drawable");
			} //END if (theComponent->getFamily() == "Sprite") { ...
			//figure out the shape to place within our sprite
			else if (theComponent->getFamily() == "Shape") {
				//intialize the shape base class
				std::string shapeType = theComponent->getAttribute_string(ATTRIBUTE_SHAPE_TYPE);
				if (shapeType == SHAPETYPE_CIRCLE) {
					theCircle = shapeManager->getCircleShape(theComponent->getAttribute_string(ATTRIBUTE_KEYNAME));
					theShape = std::static_pointer_cast<sf::Shape> (theCircle);
					assert(theShape != nullptr && "Nullptr in circle shape");
				}
				else if (shapeType == SHAPETYPE_RECTANGLE) {
					theRectangle = shapeManager->getRectangleShape(theComponent->getAttribute_string(ATTRIBUTE_KEYNAME)); 
					//cast it to the base class sf::Shape
					theShape = std::static_pointer_cast<sf::Shape> (theRectangle);
					assert(theShape != nullptr && "Nullptr in rectangle shape");
				}
				else if (shapeType == SHAPETYPE_POLYGON) {
					theConvexShape = shapeManager->getConvexShape(theComponent->getAttribute_string(ATTRIBUTE_KEYNAME));
					//cast to the base class sf::Shape
					theShape = std::static_pointer_cast<sf::Shape> (theConvexShape);
					assert(theShape != nullptr && "Nullptr in convex shape");
				}
				else {
					assert(0 && "Shape Type does not exist");
				}

				//we cast to pointers representing transformable
				//  and drawable objects in order to relate to the other given sprite
				//  class. This allows it to be transformed like the sprite
				theTransform = std::static_pointer_cast<sf::Transformable> (theShape);
				assert(theTransform != nullptr && "Nullptr in shape transform");
				theDrawable = std::static_pointer_cast<sf::Drawable> (theShape);
				assert(theDrawable != nullptr && "Nullptr in shape drawable");
			} //END if (theComponent->getFamily() == "Shape") { ...
			else if (theComponent->getFamily() == "Text") {
				theText = textManager->getText(theComponent->getAttribute_string(ATTRIBUTE_KEYNAME));

				//we cast to pointers representing transformable
				//  and drawable objects in order to relate to the other given sprite
				//  class. This allows it to be transformed like the sprite
				theTransform = std::static_pointer_cast<sf::Transformable> (theText);
				assert(theTransform != nullptr && "Nullptr in shape transform");
				theDrawable = std::static_pointer_cast<sf::Drawable> (theText);
				assert(theDrawable != nullptr && "Nullptr in shape drawable");
			}//END else if (theComponent->getFamily() == "Text") {

			//grab the rest of the desired attributes

			//get the transformable offset, which is 
			//  relative to the position component and its offset
			float offsetX = theComponent->getAttribute_float(ATTRIBUTE_OFFSET_X) +
				positionComponent->getAttribute_float(ATTRIBUTE_OFFSET_X);
			float offsetY = theComponent->getAttribute_float(ATTRIBUTE_OFFSET_Y) + 
				positionComponent->getAttribute_float(ATTRIBUTE_OFFSET_Y);

			//get the transformable scale
			float scaleX = theComponent->getAttribute_float(ATTRIBUTE_SCALE_X);
			float scaleY = theComponent->getAttribute_float(ATTRIBUTE_SCALE_Y);

			//get the transformable origin point
			float originX = theComponent->getAttribute_float(ATTRIBUTE_ORIGIN_X);
			float originY = theComponent->getAttribute_float(ATTRIBUTE_ORIGIN_Y);

			//get the rotation of the transformable relative to the position
			float spriteRotation = theComponent->getAttribute_float(ATTRIBUTE_ROTATION);

			//PERFORM TRANSFORM OPERATIONS

			//First we set the origin of our transformable object
			theTransform->setOrigin(originX, originY);

			//SFML rotation is presented in degrees, converting from radians
			float rot = ((rotation + spriteRotation) / (2.f * PI)) * 360.f;

			//fix the angle between 0 and 360 degrees
			if (rot >= 360) {
				int numRotations = (int)rot / 360;
				rot = rot - 360 * numRotations;
			}

			//given situations where it is close to zero, set it to zero
			if ((int)rot % 360 == 0){
				if ((rot - floor(rot)) < FULL_ROTATION_THRESHOLD) {
					theComponent->setAttribute_float(ATTRIBUTE_ROTATION, 0.);
					positionComponent->setAttribute_float(ATTRIBUTE_ROTATION, 0.);
					rot = 0;
				}
			}
			theTransform->setRotation(rot);

			//Scale the sprite
			theTransform->setScale(scaleX, scaleY);

			//move the sprite
			//we need to correct for the changed origin
			theTransform->setPosition(
				positionX + offsetX, 
				positionY + offsetY
				);

			//Finally, draw our sprite
			window.draw(*theDrawable);

		} //END for (auto theComponent : ...
	} //END for (auto entity : ...
	return 0;
}