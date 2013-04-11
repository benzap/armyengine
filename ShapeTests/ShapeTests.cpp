#include <memory>
#include <iostream>
#include <vector>

#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"

void sleep(float seconds) {
	sf::Clock clock;
	while(clock.getElapsedTime().asSeconds() < seconds) {}
}

int main() {
     // Create the main window
     sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");
 
	 sf::CircleShape aCircle(50, 50 );
	 aCircle.setPosition(400,300);


	 sf::RectangleShape aRectangle;
	 aRectangle.setSize(sf::Vector2f(200, 100));
	 aRectangle.setPosition(10,10);
	 aRectangle.setOutlineColor(sf::Color::Red);
	 aRectangle.setOutlineThickness(5);
 
	 sf::ConvexShape aPolygon;
	 aPolygon.setPointCount(3);
	 aPolygon.setPosition(100,200);
	 aPolygon.setPoint(0, sf::Vector2f(0,0));
	 aPolygon.setPoint(1, sf::Vector2f(100,0));
	 aPolygon.setPoint(2, sf::Vector2f(0,100));

     // Start the game loop
     while (window.isOpen())
     {
         // Process events
         sf::Event event;
         while (window.pollEvent(event))
         {
             // Close window : exit
             if (event.type == sf::Event::Closed)
                 window.close();
         }
 
         // Clear screen
         window.clear();

		 //Drawing circle
		 window.draw(aCircle);
		
		 //drawing rectangle
		 window.draw(aRectangle);

		 //draw polygon
		 window.draw(aPolygon);

         // Update the window
         window.display();
     }
 
     return EXIT_SUCCESS;
 }