#include <iostream>
#include <memory>
#include <vector>

#include "ArmyEngine.h"

void sleep(float seconds) {
	sf::Clock clock;
	while(clock.getElapsedTime().asSeconds() < seconds) {}
}

int main() {
	//populate our manager
	//populateSprites();

	std::vector<std::string> imageList;
	imageList.push_back("../images/drone_blue_finished.png");
	imageList.push_back("../images/testSprite.png");
	imageList.push_back("../images/greenSquare.png");
	
	auto armyengine = ArmyEngine::getInstance();
	auto spriteManager = SpriteManager::getInstance();
	
	armyengine->loadSpriteFromFile("testSprite", imageList[0]);
	armyengine->loadSpriteFromFile("testSprite2", imageList[1]);

	auto sprite = spriteManager->getSprite("testSprite");

    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");
 
    // Start the game loop
    while (window.isOpen()) {
        // Process events
        sf::Event event;
        while (window.pollEvent(event)) {
            // Close window : exit
            if (event.type == sf::Event::Closed) {
                window.close();
			}
        }
 
        // Clear screen
        window.clear();
 
		sprite->move((float) 0.1, (float) 0.1);

        // Draw the sprite
        window.draw(*sprite);
 
        // Update the window
        window.display();
    }
 
    return EXIT_SUCCESS;
}