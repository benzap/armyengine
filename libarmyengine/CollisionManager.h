#ifndef AE__COLLISIONMANAGER_H
#define AE__COLLISIONMANAGER_H
//DESCRIPTION
/*
Collision manager is used to manage what happens when two entities collide with eachother.
Callbacks are added to the collision manager to handle situations where given collision types collide.
Depending on the type of collision, the resulting collision may be handled differently.

For example Player tagged "Player" collides with a wall "Physical", which will invoke a collision callback
to prevent the character from moving in that direction. It must also be noted that a second callback
where the wall collides with the player will also be invoked.

Information for the callback includes a tuple, which includes 4 values. These 4 values should be enough
to perform all the functions desired
tuple<entity id 1, collisioncomponent name 1, entity id 2, collisioncomponent name 2>

the callback is chosen based on the pair<collisiontag1, collisiontag2> which needs to be
registered within the manager.
*/
//CLASSES
class CollisionManager;

//INCLUDES
#include <memory>
#include <functional>
#include <map>
#include <string>
#include <tuple>
#include <list>

//TYPEDEF
//tuple for storing
 //first collided entity id and collisioncomponent name
 //second collided entity id and collisioncomponent name
 //last value is a boolean representing if it has stopped colliding.
typedef std::tuple<int, std::string, int, std::string, bool> collisionParamTuple;
typedef std::tuple<int, std::string, int, std::string> registeredCollisionTuple;
//pair tuple holding 
// first collision tag attribute string
// second collision tag attribute string
typedef std::pair<std::string, std::string> collisionTagTuple;
//function type to assign to the callback
typedef std::function<int(collisionParamTuple)> functionCollisionTemplate;
//map to hold the callbacks
typedef std::map<collisionTagTuple, functionCollisionTemplate> collisionCallbackTableType;
//list for holding registered collisions
typedef std::list<registeredCollisionTuple> registeredCollisionListType;

//BEGIN
class CollisionManager {
private:
	collisionCallbackTableType callbackTable;
	registeredCollisionListType registeredCollisionList;

	CollisionManager() {}
public:
	static CollisionManager* getInstance() {
		static CollisionManager _instance;
		return &_instance;
	}

	//used to add a callback to the callback table
	void addCallback(const collisionTagTuple&, functionCollisionTemplate);

	//called by the collision system to trigger a desired callback
	int triggerCallback(const collisionTagTuple&, const collisionParamTuple&);

	//deletes the callback described by the provided tuple
	void removeCallback(const collisionTagTuple&);

	//returns true if the callback table has the provided tag
	bool hasCallback(const collisionTagTuple&);

	//registered the collision within a list
	void registerCollision(const registeredCollisionTuple&);

	//unregisters and removes from the list
	void unregisterCollision(const registeredCollisionTuple&);

	//checks to see if the current collision is registered
	bool hasRegisteredCollision(const registeredCollisionTuple&);

};



#endif //AE__COLLISIONMANAGER_H