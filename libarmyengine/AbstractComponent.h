#ifndef AE__ABSTRACTCOMPONENT_H
#define AE__ABSTRACTCOMPONENT_H
//DESCRIPTION
/*
Is the abstract for the the components within the entity
component system
*/

//CLASSES
class AbstractComponent;

//INCLUDES
#include <map>
#include <memory>
#include <list>
#include <string>
#include <vector>

//ENUM
enum attribute_type { 
	ATTR_INTEGER, 
	ATTR_FLOAT, 
	ATTR_STRING, 
	ATTR_FLOATARRAY,
	ATTR_INTEGERARRAY
};

//TYPEDEFS
typedef std::vector<int> componentIntegerArrayType;
typedef std::vector<float> componentFloatArrayType;

//union container to store the attribute values
typedef union attributeContainer_union {
	int i;
	float f;
	std::string* s;
	componentIntegerArrayType* si;
	componentFloatArrayType* sf;
} attribute_container;

//structure to represent each attribute type being stored within the component
typedef struct attribute_struct {
	attribute_container attr_container;
	attribute_type attr_type;
} attribute;

typedef std::map<std::string, attribute> attributeListType;
typedef AbstractComponent componentType;

//BEGIN
class AbstractComponent {
private:
	attributeListType attributeList;
	std::string name;
	std::string family;

public:
	AbstractComponent(std::string, std::string);
	~AbstractComponent();

	const std::string& getName();
	const std::string& getFamily();

	bool hasAttribute(const std::string&);
	attribute_type getAttributeType(const std::string&);

	int getAttribute_int(const std::string&);
	void setAttribute_int(const std::string&, int);

	float getAttribute_float(const std::string&);
	void setAttribute_float(const std::string&, float);

	const std::string& getAttribute_string(const std::string&);
	void setAttribute_string(const std::string&, std::string);

	componentFloatArrayType* getAttribute_floatArray(const std::string&);
	void setAttribute_floatArray(const std::string&, componentFloatArrayType);

	componentIntegerArrayType* getAttribute_intArray(std::string);
	void setAttribute_intArray(const std::string&, componentIntegerArrayType);


	//general set and get for the attribute type
	attribute getAttribute(const std::string&);
	void setAttribute(const std::string&, int);
	void setAttribute(const std::string&, float);
	void setAttribute(const std::string&, std::string);
	void setAttribute(const std::string&, componentFloatArrayType);
	void setAttribute(const std::string&, componentIntegerArrayType);

	virtual int update() = 0;
};

#endif //AE__ABSTRACTCOMPONENT_H