#include <map>
#include <cassert>

#include "AbstractComponent.h"

AbstractComponent::AbstractComponent(std::string name, std::string family) 
	: name(name), family(family) {}

AbstractComponent::~AbstractComponent() {
	for (auto attribute : this->attributeList) {
		if (attribute.second.attr_type == ATTR_STRING) {
			delete attribute.second.attr_container.s;
		}
		else if (attribute.second.attr_type == ATTR_FLOATARRAY) {
			delete attribute.second.attr_container.sf;
		}
		else if (attribute.second.attr_type == ATTR_INTEGERARRAY) {
			delete attribute.second.attr_container.si;
		}
	}
}

const std::string& AbstractComponent::getName() {
	return this->name;
}

const std::string& AbstractComponent::getFamily() {
	return this->family;
}

bool AbstractComponent::hasAttribute(const std::string& attr_key) {
	if (this->attributeList.find(attr_key) == this->attributeList.end()) {
		return false;
	}
	return true;
}

attribute_type AbstractComponent::getAttributeType(const std::string& attr_key) {
	assert(this->hasAttribute(attr_key) && "attr_key does not exist");
	return this->attributeList[attr_key].attr_type;
}

int AbstractComponent::getAttribute_int(const std::string& attr_key) {
	assert(this->hasAttribute(attr_key) && "attr_key does not exist");
	assert(this->attributeList[attr_key].attr_type == ATTR_INTEGER && "attribute not of type integer");
	return this->attributeList[attr_key].attr_container.i;
}

void AbstractComponent::setAttribute_int(const std::string& attr_key, int ivalue) {
	if (this->hasAttribute(attr_key)) {
		this->attributeList[attr_key].attr_container.i = ivalue;
		this->attributeList[attr_key].attr_type = ATTR_INTEGER;
	}
	else {
		attribute attr;
		attr.attr_container.i = ivalue;
		attr.attr_type = ATTR_INTEGER;
		this->attributeList[attr_key] = attr;
	}
}

float AbstractComponent::getAttribute_float(const std::string& attr_key) {
	assert(this->hasAttribute(attr_key) && "attr_key does not exist");
	assert(this->attributeList[attr_key].attr_type == ATTR_FLOAT && "attribute not of type float");
	return this->attributeList[attr_key].attr_container.f;
}

void AbstractComponent::setAttribute_float(const std::string& attr_key, float fvalue) {
	if (this->hasAttribute(attr_key)) {
		this->attributeList[attr_key].attr_container.f = fvalue;
		this->attributeList[attr_key].attr_type = ATTR_FLOAT;
	}
	else {
		attribute attr;
		attr.attr_container.f = fvalue;
		attr.attr_type = ATTR_FLOAT;
		this->attributeList[attr_key] = attr;
	}	
}

const std::string& AbstractComponent::getAttribute_string(const std::string& attr_key) {
	assert(this->hasAttribute(attr_key) && "attr_key does not exist");
	assert(this->attributeList[attr_key].attr_type == ATTR_STRING && "attribute not of type string");
	return *(this->attributeList[attr_key].attr_container.s);
}

void AbstractComponent::setAttribute_string(const std::string& attr_key, std::string svalue) {
	if (this->hasAttribute(attr_key)) {
		*(this->attributeList[attr_key].attr_container.s) = svalue;
		this->attributeList[attr_key].attr_type = ATTR_STRING;
	}
	else {
		attribute attr;
		attr.attr_container.s = new std::string(svalue);
		attr.attr_type = ATTR_STRING;
		this->attributeList[attr_key] = attr;
	}	
}

componentFloatArrayType* AbstractComponent::getAttribute_floatArray(const std::string& attr_key) {
	assert(this->hasAttribute(attr_key) && "attr_key does not exist");
	assert(this->attributeList[attr_key].attr_type == ATTR_FLOATARRAY && "attribute not of type float array");
	return this->attributeList[attr_key].attr_container.sf;
}

void AbstractComponent::setAttribute_floatArray(const std::string& attr_key, componentFloatArrayType sfvalue) {
	if (this->hasAttribute(attr_key)) {
		delete this->attributeList[attr_key].attr_container.sf;
		this->attributeList[attr_key].attr_container.sf = new componentFloatArrayType(sfvalue);
		this->attributeList[attr_key].attr_type = ATTR_FLOATARRAY;
	}
	else {
		attribute attr;
		attr.attr_container.sf = new componentFloatArrayType(sfvalue);
		attr.attr_type = ATTR_FLOATARRAY;
		this->attributeList[attr_key] = attr;
	}	
}

componentIntegerArrayType* AbstractComponent::getAttribute_intArray(std::string attr_key) {
	assert(this->hasAttribute(attr_key) && "attr_key does not exist");
	assert(this->attributeList[attr_key].attr_type == ATTR_INTEGERARRAY && "attribute not of type int array");
	return this->attributeList[attr_key].attr_container.si;
}

void AbstractComponent::setAttribute_intArray(const std::string& attr_key, componentIntegerArrayType sivalue) {
	if (this->hasAttribute(attr_key)) {
		delete this->attributeList[attr_key].attr_container.si;
		this->attributeList[attr_key].attr_container.si = new componentIntegerArrayType(sivalue);
		this->attributeList[attr_key].attr_type = ATTR_INTEGERARRAY;
	}
	else {
		attribute attr;
		attr.attr_container.si = new componentIntegerArrayType(sivalue);
		attr.attr_type = ATTR_INTEGERARRAY;
		this->attributeList[attr_key] = attr;
	}
}

attribute AbstractComponent::getAttribute(const std::string& attr_key) {
	assert(this->hasAttribute(attr_key) && "attr_key does not exist");
	return this->attributeList[attr_key];
}

void AbstractComponent::setAttribute(const std::string& attr_key, int value) {
	this->setAttribute_int(attr_key, value);
}

void AbstractComponent::setAttribute(const std::string& attr_key, float value) {
	this->setAttribute_float(attr_key, value);
}

void AbstractComponent::setAttribute(const std::string& attr_key, std::string value) {
	this->setAttribute_string(attr_key, value);
}

void AbstractComponent::setAttribute(const std::string& attr_key, componentFloatArrayType value) {
	this->setAttribute_floatArray(attr_key, value);
}

void AbstractComponent::setAttribute(const std::string& attr_key, componentIntegerArrayType value) {
	this->setAttribute_intArray(attr_key, value);
}