#ifndef AE__SPRITESYSTEM_H
#define AE__SPRITESYSTEM_H
//DESCRIPTION
/*
Sprite system, used to read from entities, 
find the Sprite Component and determine if the entity 
should be drawn to the screen
*/

//CLASSES
class SpriteSystem;

//INCLUDES
#include <memory>

#include "SFML\Window.hpp"
#include "AbstractSystem.h"
#include "SpriteManager.h"
#include "TextManager.h"
#include "ShapeManager.h"

//DEFINTIONS
#define FULL_ROTATION_THRESHOLD 1.0e-5
#define CIRCLE_NUM_POINTS 60

//BEGIN
class SpriteSystem : public AbstractSystem {
private:
	sf::RenderWindow& window;
	SpriteManager* spriteManager;
	TextManager* textManager;
	ShapeManager* shapeManager;

	//initialized objects which we modify to represent our 

public:
	SpriteSystem(sf::RenderWindow&);

	int process();
};

#endif //AE__SPRITESYSTEM_H