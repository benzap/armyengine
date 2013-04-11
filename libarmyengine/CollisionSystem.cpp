#include <functional>
#include <tuple>
#include <iostream>
#include <cassert>
#include <cmath>

#include "CollisionSystem.h"
#include "Components.h"
#include "Entities.h"
#include "AE_Attributes.h"
#include "AE_Utilities.h"

CollisionSystem::CollisionSystem() :
	AbstractSystem("Collision"),
	entityManager(EntityManager::getInstance()),
	collisionManager(CollisionManager::getInstance()) {
}

bool CollisionSystem::collision_rect_rect(const std::shared_ptr<AbstractComponent> pos1component,
										  const std::shared_ptr<AbstractComponent> col1component,
										  const std::shared_ptr<AbstractComponent> pos2component,
										  const std::shared_ptr<AbstractComponent> col2component) {
	//Position Attributes for the first entity
	//the position
	auto pos1 = std::vector<float>(2);
	pos1[0] = (pos1component->getAttribute_float(ATTRIBUTE_POSITION_X));
	pos1[1] = (pos1component->getAttribute_float(ATTRIBUTE_POSITION_Y));
	//the offset position
	auto offset1 = std::vector<float>(2);
	offset1[0] = (pos1component->getAttribute_float(ATTRIBUTE_OFFSET_X));
	offset1[1] = (pos1component->getAttribute_float(ATTRIBUTE_OFFSET_Y));
	//the offset collision
	offset1[0] += col1component->getAttribute_float(ATTRIBUTE_OFFSET_X);
	offset1[1] += col1component->getAttribute_float(ATTRIBUTE_OFFSET_Y);
	//the rotation (not relevant in the first implementation)
	auto rot1 = pos1component->getAttribute_float(ATTRIBUTE_ROTATION);
	//the origin
	auto origin1 = std::vector<float>(2);
	origin1[0] = (col1component->getAttribute_float(ATTRIBUTE_ORIGIN_X));
	origin1[1] = (col1component->getAttribute_float(ATTRIBUTE_ORIGIN_Y));
	//get the rectangle bounds
	auto recBounds1 = std::vector<float>(2);
	recBounds1[0] = (col1component->getAttribute_float(ATTRIBUTE_WIDTH));
	recBounds1[1] = (col1component->getAttribute_float(ATTRIBUTE_HEIGHT));

	//Position Attributes for the second entity
	//the position
	auto pos2 = std::vector<float>(2);
	pos2[0] = (pos2component->getAttribute_float(ATTRIBUTE_POSITION_X));
	pos2[1] = (pos2component->getAttribute_float(ATTRIBUTE_POSITION_Y));
	//the offset position
	auto offset2 = std::vector<float>(2);
	offset2[0] = (pos2component->getAttribute_float(ATTRIBUTE_OFFSET_X));
	offset2[1] = (pos2component->getAttribute_float(ATTRIBUTE_OFFSET_Y));
	//the offset collision
	offset2[0] += col2component->getAttribute_float(ATTRIBUTE_OFFSET_X);
	offset2[1] += col2component->getAttribute_float(ATTRIBUTE_OFFSET_Y);
	//the rotation (not relevent in the first implementation)
	auto rot2 = pos2component->getAttribute_float(ATTRIBUTE_ROTATION);
	//the origin
	auto origin2 = std::vector<float>(2);
	origin2[0] = (col2component->getAttribute_float(ATTRIBUTE_ORIGIN_X));
	origin2[1] = (col2component->getAttribute_float(ATTRIBUTE_ORIGIN_Y));
	//get the rectangle bounds
	auto recBounds2 = std::vector<float>(2);
	recBounds2[0] = (col2component->getAttribute_float(ATTRIBUTE_WIDTH));
	recBounds2[1] = (col2component->getAttribute_float(ATTRIBUTE_HEIGHT));
	
	//fix our positions based on the origin and offset
	pos1[0] += offset1[0] - origin1[0];
	pos1[1] += offset1[1] - origin1[1];

	pos2[0] += offset2[0] - origin2[0];
	pos2[1] += offset2[1] - origin2[1];

	//perform the collision test
	float t;
	if ((t = pos1[0] - pos2[0]) > recBounds2[0] || -t > recBounds1[0]) { return false; }
	if ((t = pos1[1] - pos2[1]) > recBounds2[1] || -t > recBounds1[1]) { return false; }
	return true;
}

//used to check the collision between two circle collision bounds
bool CollisionSystem::collision_rect_circle(const std::shared_ptr<AbstractComponent> pos1component,
							     const std::shared_ptr<AbstractComponent> col1component,
							     const std::shared_ptr<AbstractComponent> pos2component,
							     const std::shared_ptr<AbstractComponent> col2component) {
	//Position Attributes for the first entity
	//the position
	auto pos1 = std::vector<float>(2);
	pos1[0] = (pos1component->getAttribute_float(ATTRIBUTE_POSITION_X));
	pos1[1] = (pos1component->getAttribute_float(ATTRIBUTE_POSITION_Y));
	//the offset position
	auto offset1 = std::vector<float>(2);
	offset1[0] = (pos1component->getAttribute_float(ATTRIBUTE_OFFSET_X));
	offset1[1] = (pos1component->getAttribute_float(ATTRIBUTE_OFFSET_Y));
	//the offset collision
	offset1[0] += col1component->getAttribute_float(ATTRIBUTE_OFFSET_X);
	offset1[1] += col1component->getAttribute_float(ATTRIBUTE_OFFSET_Y);
	//the rotation (not relevant in the first implementation)
	auto rot1 = pos1component->getAttribute_float(ATTRIBUTE_ROTATION);
	//the origin
	auto origin1 = std::vector<float>(2);
	origin1[0] = (col1component->getAttribute_float(ATTRIBUTE_ORIGIN_X));
	origin1[1] = (col1component->getAttribute_float(ATTRIBUTE_ORIGIN_Y));
	//get the rectangle bounds
	auto recBounds1 = std::vector<float>(2);
	recBounds1[0] = (col1component->getAttribute_float(ATTRIBUTE_WIDTH));
	recBounds1[1] = (col1component->getAttribute_float(ATTRIBUTE_HEIGHT));

	//Position Attributes for the second entity
	//the position
	auto pos2 = std::vector<float>(2);
	pos2[0] = (pos2component->getAttribute_float(ATTRIBUTE_POSITION_X));
	pos2[1] = (pos2component->getAttribute_float(ATTRIBUTE_POSITION_Y));
	//the offset position
	auto offset2 = std::vector<float>(2);
	offset2[0] = (pos2component->getAttribute_float(ATTRIBUTE_OFFSET_X));
	offset2[1] = (pos2component->getAttribute_float(ATTRIBUTE_OFFSET_Y));
	//the offset collision
	offset2[0] += col2component->getAttribute_float(ATTRIBUTE_OFFSET_X);
	offset2[1] += col2component->getAttribute_float(ATTRIBUTE_OFFSET_Y);
	//the rotation (not relevent in the first implementation)
	auto rot2 = pos2component->getAttribute_float(ATTRIBUTE_ROTATION);
	//the origin
	auto origin2 = std::vector<float>(2);
	origin2[0] = (col2component->getAttribute_float(ATTRIBUTE_ORIGIN_X));
	origin2[1] = (col2component->getAttribute_float(ATTRIBUTE_ORIGIN_Y));
	//get the radius bounds
	auto radius2 = col2component->getAttribute_float(ATTRIBUTE_RADIUS);
	
	//fix our positions based on the origin and offset.
	// this position represents our center point of both the
	// rectangle and the circle

	//represents the top-left corner of our rectangle
	pos1[0] += offset1[0] - origin1[0];
	pos1[1] += offset1[1] - origin1[1];


	//center of circle
	pos2[0] += offset2[0] - origin2[0] + radius2;
	pos2[1] += offset2[1] - origin2[1] + radius2;

	//perform a check to determine what the closest distance is between
	// the radius center point, and our rectangle
	float distanceSquared = 0.0f;
	for (int i = 0; i < 2; i++) {
		float v = pos2[i]; //the point representing our circle center
		float minBound = pos1[i];
		float maxBound = pos1[i] + recBounds1[i];

		if (v < minBound) distanceSquared += (minBound - v) * (minBound - v);
		if (v > maxBound) distanceSquared += (v - maxBound) * (v - maxBound);
	}

	//get the radius sum
	float radiusSum = radius2;

	//circles collide if the radius sum is greater than the distance sum
	return (distanceSquared <= radiusSum * radiusSum);
}

bool CollisionSystem::collision_circle_circle(const std::shared_ptr<AbstractComponent> pos1component,
										    const std::shared_ptr<AbstractComponent> col1component,
										    const std::shared_ptr<AbstractComponent> pos2component,
										    const std::shared_ptr<AbstractComponent> col2component) {

	//Position Attributes for the first entity
	//the position
	auto pos1 = std::vector<float>(2);
	pos1[0] = (pos1component->getAttribute_float(ATTRIBUTE_POSITION_X));
	pos1[1] = (pos1component->getAttribute_float(ATTRIBUTE_POSITION_Y));
	//the offset position
	auto offset1 = std::vector<float>(2);
	offset1[0] = (pos1component->getAttribute_float(ATTRIBUTE_OFFSET_X));
	offset1[1] = (pos1component->getAttribute_float(ATTRIBUTE_OFFSET_Y));
	//the offset collision
	offset1[0] += col1component->getAttribute_float(ATTRIBUTE_OFFSET_X);
	offset1[1] += col1component->getAttribute_float(ATTRIBUTE_OFFSET_Y);
	//the rotation (not relevant in the first implementation)
	auto rot1 = pos1component->getAttribute_float(ATTRIBUTE_ROTATION);
	//the origin
	auto origin1 = std::vector<float>(2);
	origin1[0] = (col1component->getAttribute_float(ATTRIBUTE_ORIGIN_X));
	origin1[1] = (col1component->getAttribute_float(ATTRIBUTE_ORIGIN_Y));
	//get the radius bounds
	auto radius1 = col1component->getAttribute_float(ATTRIBUTE_RADIUS);

	//Position Attributes for the second entity
	//the position
	auto pos2 = std::vector<float>(2);
	pos2[0] = (pos2component->getAttribute_float(ATTRIBUTE_POSITION_X));
	pos2[1] = (pos2component->getAttribute_float(ATTRIBUTE_POSITION_Y));
	//the offset position
	auto offset2 = std::vector<float>(2);
	offset2[0] = (pos2component->getAttribute_float(ATTRIBUTE_OFFSET_X));
	offset2[1] = (pos2component->getAttribute_float(ATTRIBUTE_OFFSET_Y));
	//the offset collision
	offset2[0] += col2component->getAttribute_float(ATTRIBUTE_OFFSET_X);
	offset2[1] += col2component->getAttribute_float(ATTRIBUTE_OFFSET_Y);
	//the rotation (not relevent in the first implementation)
	auto rot2 = pos2component->getAttribute_float(ATTRIBUTE_ROTATION);
	//the origin
	auto origin2 = std::vector<float>(2);
	origin2[0] = (col2component->getAttribute_float(ATTRIBUTE_ORIGIN_X));
	origin2[1] = (col2component->getAttribute_float(ATTRIBUTE_ORIGIN_Y));
	//get the radius bounds
	auto radius2 = col2component->getAttribute_float(ATTRIBUTE_RADIUS);
	
	//fix our positions based on the origin and offset.
	// this position represents our center point
	pos1[0] += offset1[0] - origin1[0] + radius1;
	pos1[1] += offset1[1] - origin1[1] + radius1;

	pos2[0] += offset2[0] - origin2[0] + radius2;
	pos2[1] += offset2[1] - origin2[1] + radius2;

	//perform the collision test
	auto center = std::vector<float>(2);
	center[0] = pos1[0] - pos2[0];
	center[1] = pos1[1] - pos2[1];

	//get the distance ^2 between circles, which is dot(center, center)
	float distanceSquared = (center[0] * center[0]) + (center[1] * center[1]);

	//get the radius sum
	float radiusSum = radius1 + radius2;

	//circles collide if the radius sum is greater than the distance sum
	return (distanceSquared <= radiusSum * radiusSum);
}

bool CollisionSystem::collision_rect_polygon(const std::shared_ptr<AbstractComponent> pos1component,
						    const std::shared_ptr<AbstractComponent> col1component,
						    const std::shared_ptr<AbstractComponent> pos2component,
						    const std::shared_ptr<AbstractComponent> col2component) {
	//Position Attributes for the first entity
	//the position
	auto pos1 = std::vector<float>(2);
	pos1[0] = (pos1component->getAttribute_float(ATTRIBUTE_POSITION_X));
	pos1[1] = (pos1component->getAttribute_float(ATTRIBUTE_POSITION_Y));
	//the offset position
	auto offset1 = std::vector<float>(2);
	offset1[0] = (pos1component->getAttribute_float(ATTRIBUTE_OFFSET_X));
	offset1[1] = (pos1component->getAttribute_float(ATTRIBUTE_OFFSET_Y));
	//the offset collision
	offset1[0] += col1component->getAttribute_float(ATTRIBUTE_OFFSET_X);
	offset1[1] += col1component->getAttribute_float(ATTRIBUTE_OFFSET_Y);
	//the rotation (not relevant in the first implementation)
	auto rot1 = pos1component->getAttribute_float(ATTRIBUTE_ROTATION);
	//the origin
	auto origin1 = std::vector<float>(2);
	origin1[0] = (col1component->getAttribute_float(ATTRIBUTE_ORIGIN_X));
	origin1[1] = (col1component->getAttribute_float(ATTRIBUTE_ORIGIN_Y));
	//get the rectangle bounds
	auto recBounds1 = std::vector<float>(2);
	recBounds1[0] = (col1component->getAttribute_float(ATTRIBUTE_WIDTH));
	recBounds1[1] = (col1component->getAttribute_float(ATTRIBUTE_HEIGHT));

	//Position Attributes for the second entity
	//the position
	auto pos2 = std::vector<float>(2);
	pos2[0] = (pos2component->getAttribute_float(ATTRIBUTE_POSITION_X));
	pos2[1] = (pos2component->getAttribute_float(ATTRIBUTE_POSITION_Y));
	//the offset position
	auto offset2 = std::vector<float>(2);
	offset2[0] = (pos2component->getAttribute_float(ATTRIBUTE_OFFSET_X));
	offset2[1] = (pos2component->getAttribute_float(ATTRIBUTE_OFFSET_Y));
	//the offset collision
	offset2[0] += col2component->getAttribute_float(ATTRIBUTE_OFFSET_X);
	offset2[1] += col2component->getAttribute_float(ATTRIBUTE_OFFSET_Y);
	//the rotation (not relevent in the first implementation)
	auto rot2 = pos2component->getAttribute_float(ATTRIBUTE_ROTATION);
	//the origin
	auto origin2 = std::vector<float>(2);
	origin2[0] = (col2component->getAttribute_float(ATTRIBUTE_ORIGIN_X));
	origin2[1] = (col2component->getAttribute_float(ATTRIBUTE_ORIGIN_Y));

	//grab the polygon points
	auto polygonPointsTemp = col2component->getAttribute_floatArray(ATTRIBUTE_POLYGON_POINTS);

	//represents the top-left corner of our rectangle
	pos1[0] += offset1[0] - origin1[0];
	pos1[1] += offset1[1] - origin1[1];

	//we need to copy the points and include the changes in the origin and offset
	// of our polygon
	auto correctedPolygon = componentFloatArrayType(*polygonPointsTemp);
	int numPoints = correctedPolygon.size() / 2;
	assert(correctedPolygon.size() % 2 == 0 && "Odd number of values in float array, should be even"); 

	//represents the corrected positioning of our polygon
	pos2[0] += offset2[0] - origin2[0];
	pos2[1] += offset2[1] - origin2[1];

	//perform point corrections based on the offset and the origin
	for (int i = 0; i < numPoints; i++) {
		//x-component
		correctedPolygon[i*2] += pos2[0];

		//y-component
		correctedPolygon[i*2+1] += pos2[1];
	}

	//form points for our rectangle to represent a polygon
	// with 4 sides and 4 points
	auto rectPolygon = componentFloatArrayType(8);
	//top left corner
	rectPolygon[0] = pos1[0]; 
	rectPolygon[1] = pos1[1];
	//bottom left corner
	rectPolygon[2] = pos1[0]; 
	rectPolygon[3] = pos1[1] + recBounds1[1];
	//bottom right corner
	rectPolygon[4] = pos1[0] + recBounds1[0]; 
	rectPolygon[5] = pos1[1] + recBounds1[1];
	//top right corner
	rectPolygon[6] = pos1[0] + recBounds1[0];
	rectPolygon[7] = pos1[1];

	//we have a rectangular polygon and a polygon
	// the first test performed checks to see whether the vertices of our
	// rectangle lie within the bounds of our polygon
	// the polygon is assumed to be a convex polygon, and no
	// checks at this time will be performed to make this assumption
	// TODO check if the polygon is convex

	//to perform the vertice check, we perform a binary search within the convex shape
	// O(logn) complexity, the implementation is in AE_Utilities
	//NOTE: we perform the check on the 4 points
	int rectNumPoints = 4;
	for (int i = 0; i < rectNumPoints; i++) {
		if(pointInPolygon(
			rectPolygon[i*2], rectPolygon[i*2+1],
			correctedPolygon)) {
			return true;
		} //END if(pointInPolygon(...
	}//END for (int i = 0; i < rectNumPoints; i++) {
	
	//next, the edge check is performed between the two polygons
	if (checkPolygonLineIntersections(correctedPolygon, rectPolygon)) {
		return true;
	}
	return false;
}

bool CollisionSystem::collision_polygon_polygon(const std::shared_ptr<AbstractComponent> pos1component,
												const std::shared_ptr<AbstractComponent> col1component,
												const std::shared_ptr<AbstractComponent> pos2component,
												const std::shared_ptr<AbstractComponent> col2component) {
	//beginning check
	auto pos1 = std::vector<float>(2);
	pos1[0] = (pos1component->getAttribute_float(ATTRIBUTE_POSITION_X));
	pos1[1] = (pos1component->getAttribute_float(ATTRIBUTE_POSITION_Y));
	//the offset position
	auto offset1 = std::vector<float>(2);
	offset1[0] = (pos1component->getAttribute_float(ATTRIBUTE_OFFSET_X));
	offset1[1] = (pos1component->getAttribute_float(ATTRIBUTE_OFFSET_Y));
	//the offset collision
	offset1[0] += col1component->getAttribute_float(ATTRIBUTE_OFFSET_X);
	offset1[1] += col1component->getAttribute_float(ATTRIBUTE_OFFSET_Y);
	//the rotation (not relevant in the first implementation)
	auto rot1 = pos1component->getAttribute_float(ATTRIBUTE_ROTATION);
	//the origin
	auto origin1 = std::vector<float>(2);
	origin1[0] = (col1component->getAttribute_float(ATTRIBUTE_ORIGIN_X));
	origin1[1] = (col1component->getAttribute_float(ATTRIBUTE_ORIGIN_Y));
	//grab the polygon points
	auto polygonPointsTemp1 = col1component->getAttribute_floatArray(ATTRIBUTE_POLYGON_POINTS);

	//Position Attributes for the second entity
	//the position
	auto pos2 = std::vector<float>(2);
	pos2[0] = (pos2component->getAttribute_float(ATTRIBUTE_POSITION_X));
	pos2[1] = (pos2component->getAttribute_float(ATTRIBUTE_POSITION_Y));
	//the offset position
	auto offset2 = std::vector<float>(2);
	offset2[0] = (pos2component->getAttribute_float(ATTRIBUTE_OFFSET_X));
	offset2[1] = (pos2component->getAttribute_float(ATTRIBUTE_OFFSET_Y));
	//the offset collision
	offset2[0] += col2component->getAttribute_float(ATTRIBUTE_OFFSET_X);
	offset2[1] += col2component->getAttribute_float(ATTRIBUTE_OFFSET_Y);
	//the rotation (not relevent in the first implementation)
	auto rot2 = pos2component->getAttribute_float(ATTRIBUTE_ROTATION);
	//the origin
	auto origin2 = std::vector<float>(2);
	origin2[0] = (col2component->getAttribute_float(ATTRIBUTE_ORIGIN_X));
	origin2[1] = (col2component->getAttribute_float(ATTRIBUTE_ORIGIN_Y));

	//grab the polygon points
	auto polygonPointsTemp2 = col2component->getAttribute_floatArray(ATTRIBUTE_POLYGON_POINTS);
	
	//corrections for our first polygon
	auto correctedPolygon1 = componentFloatArrayType(*polygonPointsTemp1);
	int numPoints1 = correctedPolygon1.size() / 2;
	assert(correctedPolygon1.size() % 2 == 0 && "Odd number of values in float array, should be even"); 

	//represents the corrected positioning of our polygon
	pos1[0] += offset1[0] - origin1[0];
	pos1[1] += offset1[1] - origin1[1];

	//perform point corrections based on the offset and the origin
	for (int i = 0; i < numPoints1; i++) {
		//x-component
		correctedPolygon1[i*2] += pos1[0];

		//y-component
		correctedPolygon1[i*2+1] += pos1[1];
	}

	//we need to copy the points and include the changes in the origin and offset
	// of our polygon
	auto correctedPolygon2 = componentFloatArrayType(*polygonPointsTemp2);
	int numPoints2 = correctedPolygon2.size() / 2;
	assert(correctedPolygon2.size() % 2 == 0 && "Odd number of values in float array, should be even"); 

	//represents the corrected positioning of our polygon
	pos2[0] += offset2[0] - origin2[0];
	pos2[1] += offset2[1] - origin2[1];

	//perform point corrections based on the offset and the origin
	for (int i = 0; i < numPoints2; i++) {
		//x-component
		correctedPolygon2[i*2] += pos2[0];

		//y-component
		correctedPolygon2[i*2+1] += pos2[1];
	}

	//we have a rectangular polygon and a polygon
	// the first test performed checks to see whether the vertices of our
	// rectangle lie within the bounds of our polygon
	// the polygon is assumed to be a convex polygon, and no
	// checks at this time will be performed to make this assumption
	// TODO check if the polygon is convex

	//to perform the vertice check, we perform a binary search within the convex shape
	// O(logn) complexity, the implementation is in AE_Utilities
	//NOTE: we perform the check on the 4 points
	for (int i = 0; i < numPoints1; i++) {
		if(pointInPolygon(
			correctedPolygon1[i*2], correctedPolygon1[i*2+1],
			correctedPolygon2)) {
			return true;
		} //END if(pointInPolygon(...
	}//END for (int i = 0; i < rectNumPoints; i++) {
	
	//next, the edge check is performed between the two polygons
	if (checkPolygonLineIntersections(correctedPolygon1, correctedPolygon2)) {
		return true;
	}

	return false;
}

bool CollisionSystem::collision_circle_polygon(const std::shared_ptr<AbstractComponent> pos1component,
						    const std::shared_ptr<AbstractComponent> col1component,
						    const std::shared_ptr<AbstractComponent> pos2component,
						    const std::shared_ptr<AbstractComponent> col2component) {
	//Position Attributes for the first entity
	//the position
	auto pos1 = std::vector<float>(2);
	pos1[0] = (pos1component->getAttribute_float(ATTRIBUTE_POSITION_X));
	pos1[1] = (pos1component->getAttribute_float(ATTRIBUTE_POSITION_Y));
	//the offset position
	auto offset1 = std::vector<float>(2);
	offset1[0] = (pos1component->getAttribute_float(ATTRIBUTE_OFFSET_X));
	offset1[1] = (pos1component->getAttribute_float(ATTRIBUTE_OFFSET_Y));
	//the offset collision
	offset1[0] += col1component->getAttribute_float(ATTRIBUTE_OFFSET_X);
	offset1[1] += col1component->getAttribute_float(ATTRIBUTE_OFFSET_Y);
	//the rotation (not relevant in the first implementation)
	auto rot1 = pos1component->getAttribute_float(ATTRIBUTE_ROTATION);
	//the origin
	auto origin1 = std::vector<float>(2);
	origin1[0] = (col1component->getAttribute_float(ATTRIBUTE_ORIGIN_X));
	origin1[1] = (col1component->getAttribute_float(ATTRIBUTE_ORIGIN_Y));
	//get the rectangle bounds
	auto radius1 = col1component->getAttribute_float(ATTRIBUTE_RADIUS);


	//Position Attributes for the second entity
	//the position
	auto pos2 = std::vector<float>(2);
	pos2[0] = (pos2component->getAttribute_float(ATTRIBUTE_POSITION_X));
	pos2[1] = (pos2component->getAttribute_float(ATTRIBUTE_POSITION_Y));
	//the offset position
	auto offset2 = std::vector<float>(2);
	offset2[0] = (pos2component->getAttribute_float(ATTRIBUTE_OFFSET_X));
	offset2[1] = (pos2component->getAttribute_float(ATTRIBUTE_OFFSET_Y));
	//the offset collision
	offset2[0] += col2component->getAttribute_float(ATTRIBUTE_OFFSET_X);
	offset2[1] += col2component->getAttribute_float(ATTRIBUTE_OFFSET_Y);
	//the rotation (not relevent in the first implementation)
	auto rot2 = pos2component->getAttribute_float(ATTRIBUTE_ROTATION);
	//the origin
	auto origin2 = std::vector<float>(2);
	origin2[0] = (col2component->getAttribute_float(ATTRIBUTE_ORIGIN_X));
	origin2[1] = (col2component->getAttribute_float(ATTRIBUTE_ORIGIN_Y));

	//grab the polygon points
	auto polygonPointsTemp = col2component->getAttribute_floatArray(ATTRIBUTE_POLYGON_POINTS);

	//represents the center of our circle
	pos1[0] += offset1[0] - origin1[0] + radius1;
	pos1[1] += offset1[1] - origin1[1] + radius1;

	//we need to copy the points and include the changes in the origin and offset
	// of our polygon
	auto correctedPolygon = componentFloatArrayType(*polygonPointsTemp);
	int numPoints = correctedPolygon.size() / 2;
	assert(correctedPolygon.size() % 2 == 0 && "Odd number of values in float array, should be even"); 

	//represents the corrected positioning of our polygon
	pos2[0] += offset2[0] - origin2[0];
	pos2[1] += offset2[1] - origin2[1];

	//perform point corrections based on the offset and the origin
	for (int i = 0; i < numPoints; i++) {
		//x-component
		correctedPolygon[i*2] += pos2[0];

		//y-component
		correctedPolygon[i*2+1] += pos2[1];
	}

	//form points for our circle to represent the extents of
	// our circle
	auto circlePolygon = componentFloatArrayType(SYNTH_CIRCLE_POINT_NUM*2);
	//our radius step
	float angleStep = 2 * PI / SYNTH_CIRCLE_POINT_NUM;
	for (int i = 0; i < SYNTH_CIRCLE_POINT_NUM; i++) {
		circlePolygon[i*2] = radius1 * cosf(angleStep*i) + pos1[0];
		circlePolygon[i*2+1] = radius1 * sinf(angleStep*i) + pos1[1];
	}

	//we have a rectangular polygon and a polygon
	// the first test performed checks to see whether the vertices of our
	// rectangle lie within the bounds of our polygon
	// the polygon is assumed to be a convex polygon, and no
	// checks at this time will be performed to make this assumption
	// TODO check if the polygon is convex

	//to perform the vertice check, we perform a binary search within the convex shape
	// O(logn) complexity, the implementation is in AE_Utilities
	//NOTE: we perform the check on the 4 points
	int circleNumPoints = SYNTH_CIRCLE_POINT_NUM;
	for (int i = 0; i < circleNumPoints; i++) {
		if(pointInPolygon(
			circlePolygon[i*2], circlePolygon[i*2+1],
			correctedPolygon)) {
			return true;
		} //END if(pointInPolygon(...
	}//END for (int i = 0; i < rectNumPoints; i++) {
	
	//next, the edge check is performed between the two polygons
	if (checkPolygonLineIntersections(correctedPolygon, circlePolygon)) {
		return true;
	}
	return false;
}

int CollisionSystem::process() {
	//need to grab all of the entities that include a collision components
	std::vector<std::shared_ptr<entityType>> collidableEntities;
	for (auto entity : this->entityManager->getAllEntities()) {
		if ((!entity->hasComponentFamily("Collision") ||
			!entity->hasComponentFamily("Position"))) {
			continue;
		}
		else {
			collidableEntities.push_back(entity);
		}
	} //END for (auto entity : entityManager->getAllEntities()) {

	//testing collision components to eachother.
	//the robustness of the test depends on what types of bounded objects will end up colliding.
	//need to form tests between
	  //Bounded Rectangle
	  //Bounded Circle
	  //Bounded Triangle
	  //Bounded Polygon (not implemented)
	for (auto entityFirst : collidableEntities) {
		auto positionComponentFirst = entityFirst->getComponentsByFamily("Position").front();
		for (auto collisionComponentFirst : entityFirst->getComponentsByFamily("Collision")) {
		auto collisionBoundTypeFirst = collisionComponentFirst->getAttribute_string(ATTRIBUTE_COLLISION_BOUND_TYPE);
		auto collisionTagFirst = collisionComponentFirst->getAttribute_string(ATTRIBUTE_COLLISION_TAG);

		//continue if the given collision component isn't enabled
		if (!(collisionComponentFirst->getAttribute_int(ATTRIBUTE_ENABLE))) {
			continue;
		}

		for (auto entitySecond : collidableEntities) {
			//don't compare to itself
			if (entityFirst->getID() == entitySecond->getID()) {
				continue;
			}

			//assuming that our entities only have one
			//collision component and one position component
			//  need to consider doing collision hierarchies later
			auto positionComponentSecond = entitySecond->getComponentsByFamily("Position").front();
			for (auto collisionComponentSecond : entitySecond->getComponentsByFamily("Collision")) {

			//continue if it isn't enabled
			if (!(collisionComponentSecond->getAttribute_int(ATTRIBUTE_ENABLE))) {
				continue;
			}

			auto collisionBoundTypeSecond = collisionComponentSecond->getAttribute_string(ATTRIBUTE_COLLISION_BOUND_TYPE);
			auto collisionTagSecond = collisionComponentSecond->getAttribute_string(ATTRIBUTE_COLLISION_TAG);

			//make the tagTuple
			auto tagTuple = collisionTagTuple(collisionTagFirst, collisionTagSecond);

			//no point in checking for collisions if their is no registered callback
			if (!collisionManager->hasCallback(tagTuple)) {
				continue;
			}

			//check to see if they have collided
			//perform collision tests for each unique case
			bool bHasCollided = false;

			//collision between two rectangles
			if (collisionBoundTypeFirst == COLLISION_BOUND_RECTANGLE &&
				collisionBoundTypeSecond == COLLISION_BOUND_RECTANGLE) {
				bHasCollided = this->collision_rect_rect(
					positionComponentFirst,
					collisionComponentFirst,
					positionComponentSecond,
					collisionComponentSecond
					);
			}
			//collision between two circles
			else if (collisionBoundTypeFirst == COLLISION_BOUND_CIRCLE &&
				collisionBoundTypeSecond == COLLISION_BOUND_CIRCLE) {
				bHasCollided = this->collision_circle_circle(
					positionComponentFirst,
					collisionComponentFirst,
					positionComponentSecond,
					collisionComponentSecond
					);
			}

			//collision between a rectangle and a circle
			else if (collisionBoundTypeFirst == COLLISION_BOUND_RECTANGLE &&
				collisionBoundTypeSecond == COLLISION_BOUND_CIRCLE) {
				bHasCollided = this->collision_rect_circle(
					positionComponentFirst,
					collisionComponentFirst,
					positionComponentSecond,
					collisionComponentSecond
					);
			}
			else if (collisionBoundTypeFirst == COLLISION_BOUND_CIRCLE &&
				collisionBoundTypeSecond == COLLISION_BOUND_RECTANGLE) {
				//swap the parameters
				bHasCollided = this->collision_rect_circle(
					positionComponentSecond,
					collisionComponentSecond,
					positionComponentFirst,
					collisionComponentFirst
					);
			}
			else if (collisionBoundTypeFirst == COLLISION_BOUND_RECTANGLE &&
				collisionBoundTypeSecond == COLLISION_BOUND_POLYGON) {
				bHasCollided = this->collision_rect_polygon(
					positionComponentFirst,
					collisionComponentFirst,
					positionComponentSecond,
					collisionComponentSecond
					);
			}
			else if (collisionBoundTypeFirst == COLLISION_BOUND_POLYGON &&
				collisionBoundTypeSecond == COLLISION_BOUND_RECTANGLE) {
					//swap the parameters
				bHasCollided = this->collision_rect_polygon(
					positionComponentSecond,
					collisionComponentSecond,
					positionComponentFirst,
					collisionComponentFirst
					);
			}
			else if (collisionBoundTypeFirst == COLLISION_BOUND_POLYGON &&
				collisionBoundTypeSecond == COLLISION_BOUND_POLYGON) {
				bHasCollided = this->collision_polygon_polygon(
					positionComponentFirst,
					collisionComponentFirst,
					positionComponentSecond,
					collisionComponentSecond
					);
			}
			else if (collisionBoundTypeFirst == COLLISION_BOUND_CIRCLE &&
				collisionBoundTypeSecond == COLLISION_BOUND_POLYGON) {
				bHasCollided = this->collision_circle_polygon(
					positionComponentFirst,
					collisionComponentFirst,
					positionComponentSecond,
					collisionComponentSecond
					);
			}
			else if (collisionBoundTypeFirst == COLLISION_BOUND_POLYGON &&
				collisionBoundTypeSecond == COLLISION_BOUND_CIRCLE) {
				bHasCollided = this->collision_circle_polygon(
					positionComponentSecond,
					collisionComponentSecond,
					positionComponentFirst,
					collisionComponentFirst
					);
			}


			//make the registered collision tuple
			auto regTuple = registeredCollisionTuple(
				entityFirst->getID(), collisionComponentFirst->getName(),
				entitySecond->getID(), collisionComponentSecond->getName()
				);

			//if they have collided, trigger a callback if a callback exists by the given tag pair
			//if it's already been registered, then we can simply skip over it
			if (bHasCollided) {
				//make the tag pair
				if (collisionManager->hasCallback(tagTuple)) {
					//we only need to call the collision callback once, so if it's
					// already registered, there is no point in calling it again
					if (this->collisionManager->hasRegisteredCollision(regTuple)) {
						continue;
					}
					else {
						this->collisionManager->registerCollision(regTuple);
						//create our param tuple
						collisionParamTuple paramTuple = std::tuple_cat(regTuple, std::tuple<bool>(true));
						collisionManager->triggerCallback(tagTuple, paramTuple);
					}
					
				}
			}
			else { //if (!bHasCollided)
				if (collisionManager->hasRegisteredCollision(regTuple)) {
					//need to unregister and perform the callback with a false boolean
					this->collisionManager->unregisterCollision(regTuple);
					collisionParamTuple paramTuple = std::tuple_cat(regTuple, std::tuple<bool>(false));
					collisionManager->triggerCallback(tagTuple, paramTuple);
				}
			}

		} //END for (auto collisionComponentSecond : entitySecond->getComponentsByFamily("Collision")) {
		} //END for (auto entity2 : collidableEntities) {
	} //END for (auto collisionComponentFirst : entityFirst->getComponentsByFamily("Collision")) {
	} //END for (auto entity1 : collidableEntities) {
	return 0;
}