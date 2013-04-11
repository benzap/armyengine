#ifndef SINGLETONT_H
#define SINGLETONT_H

//DESCRIPTION
/*
Class is supposed to be inherited by a given class which you want to become a singleton class

ex. class A : public SingletonT<A> {};

a = A::getInstance(); //returns an instance of A

NOTE: INIT_SINGLETON_STATIC(A) must be placed at the beginning of the A's implementation
in order to ensure initialization of the static instance.
*/

//CLASSES
template <class InstanceClass> class SingletonT;

//INCLUDES
#include <memory>

//MACROS

//this needs to be placed at the beginning of the .cpp file that inherits TSingleton
// ex. EntityManager.cpp
#define INIT_SINGLETON_STATIC(InstanceClass) \
	std::shared_ptr<InstanceClass> InstanceClass::_instance = nullptr;


//BEGIN

//Some restrictions when using this
// - class cannot have a constructor
template <typename InstanceClass> class SingletonT {
private:
	SingletonT& operator = (const SingletonT& rs);

protected:
	static std::shared_ptr<InstanceClass> _instance;

public:
	//Grabs an instance of the given class templated
	static std::shared_ptr<InstanceClass> getInstance() {
		//if the instance hasn't been created yet, create it
		if (InstanceClass::_instance == nullptr) {
			InstanceClass::_instance = std::shared_ptr<InstanceClass> (new InstanceClass());
		}
		return InstanceClass::_instance;
	}
};

#endif //SINGLETONT_H