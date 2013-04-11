#include <cassert>
#include <functional>
#include "CallbackManager.h"

bool CallbackManager::hasCallback(const std::string& name) {
	if (this->callbackMap.find(name) == this->callbackMap.end()) {
		return false;
	}
	return true;
}

void CallbackManager::addCallback(const std::string& name, functionEventTemplate func) {
	assert(!this->hasCallback(name) && "Callback already exists by that name");
	this->callbackMap[name] = func;	
}

void CallbackManager::addCallback(const std::string& name, functionTemplate func) {
	assert(!this->hasCallback(name) && "Callback already exists by that name");

	//wrap our function in our functionwrapper
	auto funcWrapper = CallbackFunctionWrapper((functionTemplate) func);
	this->callbackMap[name] = funcWrapper;	
}

void CallbackManager::addCallback(const std::string& name, functionBaseTemplate func) {
	assert(!this->hasCallback(name) && "Callback already exists by that name");
	auto funcWrapper = CallbackFunctionWrapper((functionBaseTemplate) func);
	this->callbackMap[name] = funcWrapper;	
}

int CallbackManager::triggerCallback(const std::string& name, int ID, int eventIndex) {
	assert(this->hasCallback(name) && "Callback does not exist by that name");
	return this->callbackMap[name](ID, eventIndex);
}

void CallbackManager::removeCallback(const std::string& name) {
	assert(this->hasCallback(name) && "Callback does not exist by that name");
	this->callbackMap.erase(name);
}

CallbackFunctionWrapper::CallbackFunctionWrapper(functionTemplate func) :
	func_oneParam(func),
	funcType(ONE_PARAM) {}

CallbackFunctionWrapper::CallbackFunctionWrapper(functionBaseTemplate func) :
	func_zeroParam(func),
	funcType(ZERO_PARAM) {}

int CallbackFunctionWrapper::operator() (int ID, int eventIndex) {
	if (this->funcType == ONE_PARAM) {
		return this->func_oneParam(ID);
	}
	else if (this->funcType == ZERO_PARAM) {
		return this->func_zeroParam();
	}
	return 1;
}