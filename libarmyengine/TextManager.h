#ifndef AE__TEXTMANAGER_H
#define AE__TEXTMANAGER_H
//DESCRIPTION
/*

*/
//CLASSES
class TextManager;

//INCLUDES
#include <memory>
#include <map>
#include <string>

#include "SFML\Graphics.hpp"

//TYPEDEFS

//DEFINITIONS
#define DEFAULT_FONT "Inconsolata"
#define DEFAULT_FONT_PATH "../fonts/Inconsolata.otf"

//BEGIN
class TextManager {
private:
	std::map<std::string, std::shared_ptr<sf::Text>> textMap;
	std::map<std::string, std::shared_ptr<sf::Font>> fontMap;

	//default font used for almost everything
	sf::Font defaultFont;

	TextManager() {
		this->defaultFont.loadFromFile(DEFAULT_FONT_PATH);
		auto defaultFontPtr = std::shared_ptr<sf::Font> (new sf::Font(defaultFont));
		this->addFont(DEFAULT_FONT, defaultFontPtr);
	}
public:
	static TextManager* getInstance() {
		static TextManager _instance;
		return &_instance;
	}

	void addText(const std::string&, std::shared_ptr<sf::Text>);
	void removeText(const std::string&);
	bool hasText(const std::string&);
	std::shared_ptr<sf::Text> getText(const std::string&);

	void addFont(const std::string&, std::shared_ptr<sf::Font>);
	void removeFont(const std::string&);
	bool hasFont(const std::string&);
	std::shared_ptr<sf::Font> getFont(const std::string&);

};

#endif //AE__TEXTMANAGER_H