#include <iostream>
#include <functional>
#include <list>
#include <algorithm>
#include <map>
#include <string>


class CallbackManager {
private:
	std::map<std::string, std::function<int(int)>> callbackList;
public:
	void addCallback(std::string name, std::function<int(int)> func) {
		callbackList[name] = func;
	}
	int triggerCallback(std::string name, int param) {
		return callbackList[name](param);
	}
};

class Multiply2 {
public:
	int operator() (int id) {
		return id*2;
	}
};

int main() {

	auto callbackManager = CallbackManager();
	callbackManager.addCallback("add5",std::bind(std::plus<int>(), std::placeholders::_1, 5));
	std::cout << "add5(10): " << callbackManager.triggerCallback("add5", 10) << std::endl;

	callbackManager.addCallback("subtract5", [] (int i) { return i - 5; });
	std::cout << "subtract5(10): " << callbackManager.triggerCallback("subtract5", 10) << std::endl;

	callbackManager.addCallback("multiply2", Multiply2());
	std::cout << "multiply2(10): " << callbackManager.triggerCallback("multiply2", 10) << std::endl;





	return 0;
}