#include <iostream>
#include <memory>
#include "Components.h"

int main() {


	auto component = std::unique_ptr<HealthComponent> (new HealthComponent("Health"));

	std::cout << "Name of the component is: " << component->getName() << std::endl;
	std::cout << "Name of the component family is: " << component->getFamily() << std::endl;

	//trying out attributes
	component->setAttribute_int("BaseHealth", 100);
	component->setAttribute_float("Damage Modifier", 0.5);
	component->setAttribute_string("Clothing", "Nothing");
	componentIntegerArrayType color = componentIntegerArrayType();
	for(int i = 0; i < 10; i ++) {
		color.push_back(i);
	}
	component->setAttribute_intArray("Color", color);
	color = *component->getAttribute_intArray("Color");
	color.push_back(10);

	component->setAttribute_intArray("Color", color);

	componentFloatArrayType colorf = componentFloatArrayType();
	for(int i = 0; i < 10; i ++) {
		colorf.push_back(i*0.1);
	}
	component->setAttribute_floatArray("Color2", colorf);
	colorf = *component->getAttribute_floatArray("Color2");
	colorf.push_back(1.);

	std::string sString = (component->hasAttribute("BaseHealth")) ? 
		"He has base health" : "He does not have base health";
	std::cout << sString << std::endl;

	int baseHealth = component->getAttribute_int("BaseHealth");
	float dmgMod = component->getAttribute_float("Damage Modifier");
	std::string clothing = component->getAttribute_string("Clothing");
	auto theColor = component->getAttribute_intArray("Color");

	std::cout << "Current Base Health: " << baseHealth << std::endl;
	std::cout << "Current Damage Modifier: " << dmgMod << std::endl;
	std::cout << "Current Clothing: " << clothing << std::endl;
	std::cout << "Current Color: ";
	for (auto number : color) {
		std::cout << number << ", ";
	}
	std::cout << std::endl;

	std::cout << "Current Colorf: ";
	for (auto number : colorf) {
		std::cout << number << ", ";
	}
	std::cout << std::endl;

	component->setAttribute_float("Damage Modifier", (float)dmgMod + 0.5);
	std::cout << "New Damage Modifier: " << component->getAttribute_float("Damage Modifier") << std::endl;

	auto attrType = component->getAttributeType("BaseHealth");
	std::cout << "BaseHealth Type: ";
	if (attrType == ATTR_FLOAT) {
		std::cout << "FLOAT";
	}
	else if (attrType == ATTR_INTEGER) {
		std::cout << "INTEGER";
	}
	else if (attrType == ATTR_STRING) {
		std::cout << "STRING";
	}
	std::cout << std::endl;



	//trying out sprite component
	auto spritecomponent = std::unique_ptr<AbstractComponent> (new SpriteComponent("Sprite1"));
	float xOffset = spritecomponent->getAttribute_float("Offset_X");
	std::cout << "X Offset of sprite: " << xOffset << std::endl;

	auto positionComponent = std::unique_ptr<AbstractComponent> (new PositionComponent("Position1"));
	float xPosition = positionComponent->getAttribute_float("Position_X");
	std::cout << "X Position of sprite: " << xPosition << std::endl;

	return 0;
}

