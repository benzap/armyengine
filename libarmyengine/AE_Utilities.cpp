#include "AE_Utilities.h"

template<class T> 
T Dot(T x0,T y0, T x1,T y1) {
	return (x0*x1 + y0*y1);
}

template<class T>
T Cross(T x0, T y0, T x1, T y1) {
	//|x0 y0| = |a b|
	//|x1 y1|   |c d|
	
	//ad * bc
	//x0 * y1 - x1 * y0

	return (x0 * y1) - (y0 * x1);
}

template<class T>
bool triangleIsCCW(
	T x0, T y0,
	T x1, T y1,
	T x2, T y2) {
	auto cross = -(Cross<T>(x1-x0,y1-y0,x2-x0,y2-y0));
	return cross > 0;
}

template<class T>
T triangle2DArea(
	T x0, T y0,
	T x1, T y1,
	T x2, T y2) {
	return ((x0 - x2) * (y1 - y2)) - ((y0 - y2) * (x1 - x2));
}

bool pointInPolygon(float px0, float py0,
							const componentFloatArrayType& polygon) {
	// points represented by [(x0,y0), ... (xn,yn)]
	int numPoints = polygon.size() / 2;

	int low = 0, high = numPoints;
	do { 
		int mid = (low + high) / 2;
		bool bIsCCW = triangleIsCCW<float>(
			polygon[0], polygon[1],
			polygon[mid*2], polygon[mid*2+1],
			px0, py0);
		if (bIsCCW) {
			low = mid;
		}
		else {
			high = mid;
		}
	} while (low + 1 < high);

	if (low == 0 || high == numPoints) return false;

	return triangleIsCCW<float>(
		polygon[low*2], polygon[low*2+1],
		polygon[high*2], polygon[high*2+1],
		px0, py0);
} //END bool polygonPointsInPolyg... 

bool Test2DLineIntersection(
	float ax, float ay, float bx, float by,
	float cx, float cy, float dx, float dy) {

	//test if AB and CD overlap
	float area1 = triangle2DArea<float>(
		ax, ay,
		bx, by,
		dx, dy);
	float area2 = triangle2DArea<float>(
		ax, ay,
		bx, by,
		cx, cy);

	//both triangles should have opposite windings, check if the 
	// final sign is negative.
	if (area1 * area2 < 0.0f) {
		float area3 = triangle2DArea(
			cx, cy,
			dx, dy,
			ax, ay);

		float area4 = area3 + area2 - area1;
		if (area3 * area4 < 0.0f) {
			return true;
		}// END if (area3 * area4 < 0.0f) {
	}// END if (area1 * area2 < 0.0f) {
	return false;
}

bool checkPolygonLineIntersections(const componentFloatArrayType& polygon1, const componentFloatArrayType& polygon2) {
	int numPoints1 = polygon1.size()/2;
	int numPoints2 = polygon2.size()/2;
	//next, the edge check is performed between the two polygons
	for (int i = 0; i < numPoints1; i++) {
		// treat the rectangle line segment as AB
		float ax, ay, bx, by;
		ax = polygon1[i*2];
		ay = polygon1[i*2+1];
		if (i != numPoints1 - 1) {
			bx = polygon1[(i+1)*2];
			by = polygon1[(i+1)*2+1];
		}
		else {
			bx = polygon1[0];
			by = polygon1[1];
		}
		for (int j = 0; j < numPoints2; j++) {
			float cx, cy, dx, dy;
			cx = polygon2[j*2];
			cy = polygon2[j*2+1];
			if (j != numPoints2-1) {
				dx = polygon2[(j+1)*2];
				dy = polygon2[(j+1)*2+1];
			}
			else {
				dx = polygon2[0];
				dy = polygon2[1];
			}

			//test the line segments, if they intersect
			// it means they collided
			if (Test2DLineIntersection(
				ax, ay, bx, by,
				cx, cy, dx, dy)) {
				return true;
			}
		}// END for (int j = 0; j < numPoints; j++) {
	}// END for (int i = 0; i < rectNumPoints; i++) {
	return false;
}