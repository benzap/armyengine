#ifndef AE__MAINENTITY_H
#define AE__MAINENTITY_H

//INCLUDES
#include <string>
#include "AbstractEntity.h"

//CLASSES
class MainEntity;

class MainEntity : public AbstractEntity {
public:
	MainEntity(std::string, int);
	//~MainEntity();
	int handle();
};

#endif //AE__MAINENTITY_H