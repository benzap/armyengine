#ifndef AE__UTILITIES_H
#define AE__UTILITIES_H
//DESCRIPTION
/*
A set of utilities and globally dependant constants shared
*/
//DEFINITIONS
#define PI 3.14159265359f

//INCLUDES
#include "AbstractComponent.h"

//CLASSES
//...

//CLASS TEMPLATES

//FUNCTIONS

//returns the dot product between two points (x0,y0) and (x1,y1)
template<class T> 
T Dot(T x0, T y0, T x1, T y1);

//returns the cross product between two points (x0,y0) and (x1,y1)
template<class T>
T Cross(T x0, T y0, T x1, T y1);

//returns true if the three points, when traversed performs a CCW movement
template<class T>
bool triangleIsCCW(
	T x0, T y0,
	T x1, T y1,
	T x2, T y2);

//similar to triangleIsCCW, but returns the area, where 
// a positive value is CCW, and negative is CW
template<class T>
T triangle2DArea(
	T x0, T y0,
	T x1, T y1,
	T x2, T y2);


//checks to see if the point is within the bounds of the
// polygon. Assumes that the polygon is convex
bool pointInPolygon(float px0, float py0,
					const componentFloatArrayType& polygon);

bool Test2DLineIntersection(
	float ax0, float ay0, float ax1, float ay1,
	float bx0, float by0, float bx1, float by1);

//checks the intersection of the line segments between two polygons
bool checkPolygonLineIntersections(const componentFloatArrayType&, const componentFloatArrayType&);

//MACROS
//...
#endif //AE__UTILITIES_H