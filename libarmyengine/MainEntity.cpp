#include <algorithm>
#include <vector>

#include "MainEntity.h"
#include "AE_Attributes.h"

MainEntity::MainEntity(std::string name, int ID)
	: AbstractEntity(name, "Main", ID) {

}

//MainEntity::~MainEntity() {}

int MainEntity::handle() {
	auto componentVector = this->getAllComponents();
	std::sort(componentVector.begin(), componentVector.end(),
		[] (std::shared_ptr<componentType> first, std::shared_ptr<componentType> second) {
			if (!first->hasAttribute(ATTRIBUTE_ZBUFFER)) {
				return false;
			}
			if (!second->hasAttribute(ATTRIBUTE_ZBUFFER)) {
				return true;
			}

			float zFirst = first->getAttribute_float(ATTRIBUTE_ZBUFFER);
			float zSecond = second->getAttribute_float(ATTRIBUTE_ZBUFFER);
			return (zFirst < zSecond);
	});
	return 0;
}