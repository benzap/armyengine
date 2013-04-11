#ifndef AE__SHAPEMANAGER_H
#define AE__SHAPEMANAGER_H
//DESCRIPTION
/*

*/
//CLASSES
class ShapeManager;

//INCLUDES
#include <memory>
#include <map>
#include <string>

#include "SFML\Graphics.hpp"

//TYPEDEFS

//DEFINITIONS

//BEGIN
class ShapeManager {
private:
	std::map<std::string, std::shared_ptr<sf::CircleShape>> circleShapeMap;
	std::map<std::string, std::shared_ptr<sf::RectangleShape>> rectangleShapeMap;
	std::map<std::string, std::shared_ptr<sf::ConvexShape>> convexShapeMap;

	ShapeManager() {

	}
public:
	static ShapeManager* getInstance() {
		static ShapeManager _instance;
		return &_instance;
	}

	void addCircleShape(const std::string&, std::shared_ptr<sf::CircleShape>);
	void removeCircleShape(const std::string&);
	bool hasCircleShape(const std::string&);
	std::shared_ptr<sf::CircleShape> getCircleShape(const std::string&);

	void addRectangleShape(const std::string&, std::shared_ptr<sf::RectangleShape>);
	void removeRectangleShape(const std::string&);
	bool hasRectangleShape(const std::string&);
	std::shared_ptr<sf::RectangleShape> getRectangleShape(const std::string&);

	void addConvexShape(const std::string&, std::shared_ptr<sf::ConvexShape>);
	void removeConvexShape(const std::string&);
	bool hasConvexShape(const std::string&);
	std::shared_ptr<sf::ConvexShape> getConvexShape(const std::string&);
};

#endif //AE__SHAPEMANAGER_H