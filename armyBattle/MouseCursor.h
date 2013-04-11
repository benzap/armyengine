//RESPONSIBILITY: Ben was responsible for designing, implementing, and testing this class.

#ifndef AB__MOUSECURSOR_H
#define AB__MOUSECURSOR_H
//DESCRIPTION
/*
The MouseCursor is an object, used to click on buttons, as well as selecting units. 
*/
//CLASSES
class MouseCursor;

//INCLUDES
#include <memory>
#include "ArmyEngine.h"

//DEFINITIONS
#define AB_MOUSE "MouseCursor"
#define AB_MOUSE_POSITION "MousePosition"
#define AB_MOUSE_COLLISION_IDLE "MouseCollisionIdle"
#define AB_MOUSE_INPUT_IDLE "MouseInputIdle"
#define AB_MOUSE_MOVE_CALLBACK "MouseMoveCallback"

#define AB_MOUSE_SHAPE_WIDTH_IDLE "MouseShapeWidthIdle"
#define AB_MOUSE_SHAPE_HEIGHT_IDLE "MouseShapeHeightIdle"

//BEGIN
class MouseCursor {
private:
	std::shared_ptr<entityType> cursorEntity;
	int lockedID;
public:
	MouseCursor();

	//sets the cursor back to it's original
	// shape
	void setIdle();

	void disable();

};

#endif //AB__MOUSECURSOR_H