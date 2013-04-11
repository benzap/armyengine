//RESPONSIBILITY: Kyle was responsible for designing, implementing, and testing this class.

#ifndef AB__HUDELEMENT_H
#define AB__HUDELEMENT_H
//DESCRIPTION
/*
This is the HUDElement class. HUDElements are used to display text on the screen. They can be used within other objects that need text displayed. 
*/
//CLASSES
class HUDElement;

//INCLUDES
#include "ArmyEngine.h"

#include "WorldObject.h"

//DEFINITION

//the HUD type string
#define AB_HUD "HUD"

//the HUD text name
#define AB_HUD_TEXT "HUD_Text"

//BEGIN
class HUDElement : public WorldObject {
private:
	std::string prefix;
public:
	HUDElement(float xPosition, float yPosition, int fontSize = 30);

	void setWarningString(const std::string&);
	void setSuccessString(const std::string&);
	void setInfoString(const std::string&);
	void setString(const std::string&, int rColor, int gColor, int bColor);

	std::string getString();

	void setPrefix(const std::string&);
	void setTextSize(int);
	void enableBold();
	void disableBold();
	void enableItalic();
	void disableItalic();
	void enableUnderline();
	void disableUnderline();

	void hide();
	void display();


};


#endif //AB__HUDELEMENT_H