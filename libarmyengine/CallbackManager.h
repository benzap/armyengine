#ifndef AE__CALLBACK_MANAGER
#define AE__CALLBACK_MANAGER
//DESCRIPTION
/*
The callback manager contains lists of functions which are used as callbacks
to components stored within the entities. It includes one parameter, which is the entities current ID
the function must also return '0' in order to determine whether it was successful

Given the design of the engine, the callback has full access to all of the managers, and is able to identify
the entity it is contained in by the given ID, which makes it very flexible.

Function Wrapper is used to wrap functions which contain only one parameter
It wraps it into a function which can take two parameters and discards the second parameter
*/
//CLASSES
class CallbackManager;
class CallbackFunctionWrapper;

//INCLUDES
#include <memory>
#include <functional>
#include <map>
#include <string>

//TYPEDEF
typedef std::function <int(void)> functionBaseTemplate;
typedef std::function<int(int)> functionTemplate;
typedef std::function<int(int, int)> functionEventTemplate;
typedef std::map<std::string, functionEventTemplate> callbackMapType;

//BEGIN
class CallbackManager {
private:
	callbackMapType callbackMap;

	CallbackManager() {}
public:
	static CallbackManager* getInstance() {
		static CallbackManager _instance;
		return &_instance;
	}

	//add a callback to the map the function is of the form int f(int), and can be
	// a lambda, std::bind, or class object, see the project CallbackTests
	void addCallback(const std::string&, functionBaseTemplate);
	void addCallback(const std::string&, functionTemplate);
	void addCallback(const std::string&, functionEventTemplate);

	//triggers the given callback, and returns its result
	int triggerCallback(const std::string&, int = 0, int = 0);

	//deletes a callback by its key
	void removeCallback(const std::string&);

	//returns true, if the provided parameter matches a callback key stored within the callbackMap
	bool hasCallback(const std::string&);
};

//Wrap functionTemplates into functionEventTemplates
//Wrap functionBaseTemplates into functionEventTemplates
class CallbackFunctionWrapper {
private:
	functionTemplate func_oneParam;
	functionBaseTemplate func_zeroParam;
	enum FuncType {
		ONE_PARAM = 1,
		ZERO_PARAM = 0
	} funcType;
public:
	CallbackFunctionWrapper(functionTemplate func);
	CallbackFunctionWrapper(functionBaseTemplate func);
	int operator() (int, int);
};

#endif //AE__CALLBACK_MANAGER