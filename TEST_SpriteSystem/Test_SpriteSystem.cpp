#include <memory>
#include <iostream>

#include "SFML\Window.hpp"
#include "SFML\Graphics.hpp"
#include "Systems.h"
#include "Managers.h"
#include "Entities.h"
#include "Components.h"
#include "AE_Utilities.h"

int main() {
	//create our window
	sf::RenderWindow window(sf::VideoMode(800, 600), "Sprite Window Test");
	//create our sprite system
	SpriteSystem spriteSystem(window);

	//create an entity
	auto entity = std::shared_ptr<AbstractEntity> (new MainEntity("Drone", 0));
	//add components
	entity->addComponent(std::shared_ptr<AbstractComponent> (new PositionComponent("Main")));
	entity->addComponent(std::shared_ptr<AbstractComponent> (new SpriteComponent("DroneSprite")));

	//add to the manager
	auto entityManager = EntityManager::getInstance();
	entityManager->addEntity(entity);
	for (auto entity : entityManager->getAllEntities()) {
		std::cout << "Name: " << 
		entity->getName() << std::endl;
	}

	while(window.isOpen()) {
		sf::Event event;

		while (window.pollEvent(event))
		{
			// Close window : exit
            if (event.type == sf::Event::Closed)
				window.close();

			else if (event.type == sf::Event::KeyPressed) {
				std::shared_ptr<AbstractEntity> entity = entityManager->getEntityById(0);
				std::shared_ptr<AbstractComponent> positionComponent = entity->getComponentByName("Main");
				std::shared_ptr<AbstractComponent> spriteComponent = entity ->getComponentByName("DroneSprite");
				if (event.key.code == sf::Keyboard::Left) {
					float positionX = positionComponent->getAttribute_float("Position_X");
					positionComponent->setAttribute_float("Position_X", positionX-5.0);
				}
				else if (event.key.code == sf::Keyboard::Right) {
					float positionX = positionComponent->getAttribute_float("Position_X");
					positionComponent->setAttribute_float("Position_X", positionX+5.0);
				}
				else if (event.key.code == sf::Keyboard::Up) {
					float positionY = positionComponent->getAttribute_float("Position_Y");
					positionComponent->setAttribute_float("Position_Y", positionY-5.0);
				}
				else if (event.key.code == sf::Keyboard::Down) {
					float positionY = positionComponent->getAttribute_float("Position_Y");
					positionComponent->setAttribute_float("Position_Y", positionY+5.0);
				}
				else if (event.key.code == sf::Keyboard::A) {
					float rotation = spriteComponent->getAttribute_float("Rotation");
					spriteComponent->setAttribute_float("Rotation", rotation - 0.333333333333333333333*PI);
				}
				else if (event.key.code == sf::Keyboard::D) {
					float rotation = spriteComponent->getAttribute_float("Rotation");
					spriteComponent->setAttribute_float("Rotation", rotation + 0.333333333333333333333*PI);
				}
				else if (event.key.code == sf::Keyboard::Add) {
					float scale = spriteComponent->getAttribute_float("Scale_X");
					spriteComponent->setAttribute_float("Scale_X", scale+0.1);
					spriteComponent->setAttribute_float("Scale_Y", scale+0.1);
				}
				else if (event.key.code == sf::Keyboard::Subtract) {
					float scale = spriteComponent->getAttribute_float("Scale_X");
					spriteComponent->setAttribute_float("Scale_X", scale-0.1);
					spriteComponent->setAttribute_float("Scale_Y", scale-0.1);
				}
				else if (event.key.code == sf::Keyboard::Space) {
					int enable = spriteComponent->getAttribute_int("bEnabled");
					spriteComponent->setAttribute_int("bEnabled", !enable);
				}
			}

        }

        // Clear screen
        window.clear();

		//process sprites
 		spriteSystem.process(); 

        // Update the window
        window.display();
	}

	return 0;
}