#include <string>
#include <iostream>

class A {
private:
	std::string name;
	std::string uniqueID;
public:
	A(std::string name) :
		name(name) {
		uniqueID = name + std::to_string(reinterpret_cast<int>(this));
	}

	void printID() {
		std::cout << this->uniqueID << std::endl;
	}
};


int main() {

	auto a = A("Ben");
	a.printID();

	return 0;
}