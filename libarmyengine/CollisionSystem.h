#ifndef AE__COLLISION_SYSTEM
#define AE__COLLISION_SYSTEM
//DESCRIPTION
/*
Processes collision components with a position component
and checks to see if the entity containing the collision component is colliding with
another entity containing another collision component

If it determines that the two components have collided, the system performs the desired callback
within the CollisionManager and includes information about both components to the callback
*/
//CLASSES
class CollisionSystem;

//INCLUDES
#include <memory>
#include <tuple>

#include "EntityManager.h"
#include "CollisionManager.h"
#include "AbstractSystem.h"

//TYPEDEFS

//DEFINITIONS

//defines the number of points to describe a circle
// when comparing a circle to a polygon
#define SYNTH_CIRCLE_POINT_NUM 20

//BEGIN
class CollisionSystem : public AbstractSystem {
private:
	CollisionManager* collisionManager;
	EntityManager* entityManager;

	//used to check the collision between two rectangle collision bounds
	bool collision_rect_rect(const std::shared_ptr<AbstractComponent> pos1component,
							 const std::shared_ptr<AbstractComponent> col1component,
							 const std::shared_ptr<AbstractComponent> pos2component,
							 const std::shared_ptr<AbstractComponent> col2component);

	//used to check the collision between two circle collision bounds
	bool collision_circle_circle(const std::shared_ptr<AbstractComponent> pos1component,
							     const std::shared_ptr<AbstractComponent> col1component,
							     const std::shared_ptr<AbstractComponent> pos2component,
							     const std::shared_ptr<AbstractComponent> col2component);

	//used to check the collision between a rectangle and a circle
	bool collision_rect_circle(const std::shared_ptr<AbstractComponent> pos1component,
							   const std::shared_ptr<AbstractComponent> col1component,
							   const std::shared_ptr<AbstractComponent> pos2component,
							   const std::shared_ptr<AbstractComponent> col2component);

	//used to check the collision between a rectangle and a polygon
	bool collision_rect_polygon(const std::shared_ptr<AbstractComponent> pos1component,
							    const std::shared_ptr<AbstractComponent> col1component,
							    const std::shared_ptr<AbstractComponent> pos2component,
							    const std::shared_ptr<AbstractComponent> col2component);

	//used to check the collision between two polygons
	bool collision_polygon_polygon(const std::shared_ptr<AbstractComponent> pos1component,
								   const std::shared_ptr<AbstractComponent> col1component,
							       const std::shared_ptr<AbstractComponent> pos2component,
							       const std::shared_ptr<AbstractComponent> col2component);

	//used to check the collision between a polygon and a circle
	bool collision_circle_polygon(const std::shared_ptr<AbstractComponent> pos1component,
							    const std::shared_ptr<AbstractComponent> col1component,
							    const std::shared_ptr<AbstractComponent> pos2component,
							    const std::shared_ptr<AbstractComponent> col2component);

public:
	CollisionSystem();

	int process();
};

#endif //AE__COLLISION_SYSTEM