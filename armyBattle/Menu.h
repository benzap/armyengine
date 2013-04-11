//RESPONSIBILITY: Kyle was responsible for designing, implementing, and testing this class.

#ifndef AB__MENU_H
#define AB__MENU_H
//DESCRIPTION
/*
The Menu is an object that uses buttons to perform various tasks, such as exiting and restarting the game. 
*/
//CLASSES
class Menu;

//INCLUDES
#include "Button.h"
#include "WorldObject.h"

#include <memory>

using namespace std;
//TYPEDEFS
typedef vector<shared_ptr<Button>> buttonListType;

//DEFINITIONS
#define AB_MENU "Menu_"
#define AB_MENU_SHAPE "Menu_Shape"
#define AB_MENU_BUTTON_SPACING 90
#define AB_MENU_BUTTON_WIDTH 160
#define AB_MENU_BUTTON_HEIGHT 80

#define AB_MENU_BUTTON_OFFSET_X 3
#define AB_MENU_BUTTON_OFFSET_Y 50

#define AB_MENU_BUTTON_TEXT_SIZE 40
#define AB_MENU_BUTTON_TEXT_OFFSET_X 10
#define AB_MENU_BUTTON_TEXT_OFFSET_Y 10



//BEGIN
class Menu : public WorldObject {
private:
	buttonListType buttonList;
public:
	Menu();

	void display();
	void hide();

};

#endif //AB__MENU_H