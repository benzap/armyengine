#ifndef AB__UTILITIES_H
#define AB__UTILITIES_H
//DESCRIPTION
/*
This header contains colour defintions that will be used for components.
*/
//DEFINITIONS

//pre-defined colors for the game
//credit goes to jacek_
// http://www.colourlovers.com/lover/jacek_/loveNote
// http://www.colourlovers.com/palette/1947417/Windows_8

//************************************
//ATTRIBUTE_OUTLINE predefined colors
//************************************

//blue (sexist society)
#define COLOR_OUTLINE_BLUE(shapeComponent) \
	shapeComponent->setAttribute_int(ATTRIBUTE_OUTLINE_COLOR_RED, 72); \
	shapeComponent->setAttribute_int(ATTRIBUTE_OUTLINE_COLOR_GREEN, 199); \
	shapeComponent->setAttribute_int(ATTRIBUTE_OUTLINE_COLOR_BLUE, 231);

//green (limegreen)
#define COLOR_OUTLINE_GREEN(shapeComponent) \
	shapeComponent->setAttribute_int(ATTRIBUTE_OUTLINE_COLOR_RED, 124); \
	shapeComponent->setAttribute_int(ATTRIBUTE_OUTLINE_COLOR_GREEN, 202); \
	shapeComponent->setAttribute_int(ATTRIBUTE_OUTLINE_COLOR_BLUE, 29);

//yellow (greenyellowish)
#define COLOR_OUTLINE_YELLOW(shapeComponent) \
	shapeComponent->setAttribute_int(ATTRIBUTE_OUTLINE_COLOR_RED, 219); \
	shapeComponent->setAttribute_int(ATTRIBUTE_OUTLINE_COLOR_GREEN, 196); \
	shapeComponent->setAttribute_int(ATTRIBUTE_OUTLINE_COLOR_BLUE, 30);

//orange (Orangish)
#define COLOR_OUTLINE_ORANGE(shapeComponent) \
	shapeComponent->setAttribute_int(ATTRIBUTE_OUTLINE_COLOR_RED, 227); \
	shapeComponent->setAttribute_int(ATTRIBUTE_OUTLINE_COLOR_GREEN, 113); \
	shapeComponent->setAttribute_int(ATTRIBUTE_OUTLINE_COLOR_BLUE, 54);

//red (Pinkish)
#define COLOR_OUTLINE_RED(shapeComponent) \
	shapeComponent->setAttribute_int(ATTRIBUTE_OUTLINE_COLOR_RED, 203); \
	shapeComponent->setAttribute_int(ATTRIBUTE_OUTLINE_COLOR_GREEN, 47); \
	shapeComponent->setAttribute_int(ATTRIBUTE_OUTLINE_COLOR_BLUE, 92);

#define COLOR_OUTLINE_BLACK(shapeComponent) \
	shapeComponent->setAttribute_int(ATTRIBUTE_OUTLINE_COLOR_RED, 0); \
	shapeComponent->setAttribute_int(ATTRIBUTE_OUTLINE_COLOR_GREEN, 0); \
	shapeComponent->setAttribute_int(ATTRIBUTE_OUTLINE_COLOR_BLUE, 0);
//************************************
//ATTRIBUTE_FILL predefined colors
//************************************

//blue (sexist society)
#define COLOR_FILL_BLUE(shapeComponent) \
	shapeComponent->setAttribute_int(ATTRIBUTE_FILL_COLOR_RED, 72); \
	shapeComponent->setAttribute_int(ATTRIBUTE_FILL_COLOR_GREEN, 199); \
	shapeComponent->setAttribute_int(ATTRIBUTE_FILL_COLOR_BLUE, 231);

//green (limegreen)
#define COLOR_FILL_GREEN(shapeComponent) \
	shapeComponent->setAttribute_int(ATTRIBUTE_FILL_COLOR_RED, 124); \
	shapeComponent->setAttribute_int(ATTRIBUTE_FILL_COLOR_GREEN, 202); \
	shapeComponent->setAttribute_int(ATTRIBUTE_FILL_COLOR_BLUE, 29);

//yellow (greenyellowish)
#define COLOR_FILL_YELLOW(shapeComponent) \
	shapeComponent->setAttribute_int(ATTRIBUTE_FILL_COLOR_RED, 219); \
	shapeComponent->setAttribute_int(ATTRIBUTE_FILL_COLOR_GREEN, 196); \
	shapeComponent->setAttribute_int(ATTRIBUTE_FILL_COLOR_BLUE, 30);

//orange (Orangish)
#define COLOR_FILL_ORANGE(shapeComponent) \
	shapeComponent->setAttribute_int(ATTRIBUTE_FILL_COLOR_RED, 227); \
	shapeComponent->setAttribute_int(ATTRIBUTE_FILL_COLOR_GREEN, 113); \
	shapeComponent->setAttribute_int(ATTRIBUTE_FILL_COLOR_BLUE, 54);

//red (Pinkish)
#define COLOR_FILL_RED(shapeComponent) \
	shapeComponent->setAttribute_int(ATTRIBUTE_FILL_COLOR_RED, 203); \
	shapeComponent->setAttribute_int(ATTRIBUTE_FILL_COLOR_GREEN, 47); \
	shapeComponent->setAttribute_int(ATTRIBUTE_FILL_COLOR_BLUE, 92);

#define COLOR_FILL_BLACK(shapeComponent) \
	shapeComponent->setAttribute_int(ATTRIBUTE_FILL_COLOR_RED, 0); \
	shapeComponent->setAttribute_int(ATTRIBUTE_FILL_COLOR_GREEN, 0); \
	shapeComponent->setAttribute_int(ATTRIBUTE_FILL_COLOR_BLUE, 0);

#endif //AB__UTILITIES_H