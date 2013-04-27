/** 
    @file
    @author Benjamin Zaporzan <benzaporzan@gmail.com>

    @section LICENSE
    
    Copyright (C) 2013  Benjamin Zaporzan
    
    This program is free software: you can redistribute it and/or
    modify it under the terms of the GNU General Public License as
    published by the Free Software Foundation, either version 3 of the
    License, or (at your option) any later version.
    
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    General Public License for more details.
    
    You should have received a copy of the GNU General Public License
    along with this program.  If not, see
    [[http://www.gnu.org/licenses/]].

    @section DESCRIPTION

    Contains the abstract for the components within the entity
    component system

*/

#ifndef AE__ABSTRACTCOMPONENT_H
#define AE__ABSTRACTCOMPONENT_H

//CLASSES
class AbstractComponent;

//INCLUDES
#include <map>
#include <memory>
#include <list>
#include <string>
#include <vector>

//ENUM

//! Enumeration to describe the attribute type

/*! Enumeration used to describe what type is being stored within the
    attributeContainer_union. */
enum attribute_type { 
	ATTR_INTEGER, 
	ATTR_FLOAT, 
	ATTR_STRING, 
	ATTR_FLOATARRAY,
	ATTR_INTEGERARRAY
};

//TYPEDEFS

//! Type to represent integer arrays in the attribute container
typedef std::vector<int> componentIntegerArrayType;

//! Type to represent the float arrays in the attribute container
typedef std::vector<float> componentFloatArrayType;

//! union container to store the attribute values

/*! The container holds the attribute value, and the type of value is
  described by the attribute_type
 */
typedef union attributeContainer_union {
  int i; //!< integer type
  float f; //!< float type
  std::string* s; //!< string type
  componentIntegerArrayType* si; //!< integer array type
  componentFloatArrayType* sf; //!< float array type
} attribute_container;

//! structure used to represent the attribute

/*!  The attribute is a structure which holds both the enumeration
  which describes the type of value stored, and the union container
  which holds the value.

  @param attr_container Union holding the data that represents the attribute
  @param attr_type The type of the data being stored for the attribute
 */
typedef struct attribute_struct {
	attribute_container attr_container;
	attribute_type attr_type;
} attribute;

//! The type used to represent the list of attributes for the component
typedef std::map<std::string, attribute> attributeListType;

//! Simple typedef to abstract the abstract...
typedef AbstractComponent componentType;

//! The abstract representation for each component

/*! The abstract component contains methods to add, remove and modify
  attributes within the component. The family member is overidden to
  describe the component type, and the name member is a unique name
  assigned to the given component.
 */
class AbstractComponent {
private:
  attributeListType attributeList; //!< The list of attributes
  std::string name; //!< unique name assigned to the given component
  std::string family; //!< the family that this component belongs to.

public:
  //! Constructor for abstract component
  AbstractComponent(std::string, std::string);
  
  //! Destructor for abstract component
  ~AbstractComponent();

  //! Returns the name of the component

  /*!
    @return The name of the component
  */
  const std::string& getName();

  //! Returns the family of the component 
  const std::string& getFamily();

  //! Checks the attributeList for the given attribute

  /*!  The attribute key name is passed, and the attribute list is
    searched. The function returns a boolean on whether or not it was
    successful in finding that attribute by the given key.

    @param attr_key The key name of the attribute.

    @return A boolean, where _true_ means that the given attribute exists.
  */
  bool hasAttribute(const std::string& attr_key);
  
  //! Gets the attribute type

  /*!
    Returns the enum value for the given attribute key

    @param attr_key The key name for the attribute.
    
    @return The type of the attribute
   */
  attribute_type getAttributeType(const std::string& attr_key);

  //! Get the attribute in the form of an integer

  /*!  Gets the attribute with the given keyname, and returns the
    value stored for that attribute. If the attribute has a different
    type than described by the attribute, you will get unwanted
    behaviour. 

    @param attr_key The key name for the attribute

    @return The value for the given attribute.
  */
  int getAttribute_int(const std::string& attr_key);

  //! Set the attribute for the given key with the given integer value

  /*!  The attribute key provided is checked for its existence. If it
    exists, the attribute is modified to be of the integer type, and
    the data is modified to be of the integer value.

    If the attribute doesn't already exist, the attribute is created
    with the given key and value and placed within the attributeList.

    @param attr_key The key name for the attribute

    @param ivalue The integer value to set the given attribute to.
  */
  void setAttribute_int(const std::string& attr_key, int ivalue);


  //! Get the attribute in the form of an float

  /*!  Gets the attribute with the given keyname, and returns the
    value stored for that attribute. If the attribute has a different
    type than described by the attribute, you will get unwanted
    behaviour. 

    @param attr_key The key name for the attribute

    @return The value for the given attribute.
  */
  float getAttribute_float(const std::string& attr_key);

  //! Set the attribute for the given key with the given float value

  /*!  The attribute key provided is checked for its existence. If it
    exists, the attribute is modified to be of the float type, and
    the data is modified to be of the float value.

    If the attribute doesn't already exist, the attribute is created
    with the given key and value and placed within the attributeList.

    @param attr_key The key name for the attribute

    @param fvalue The float value to set the given attribute to.
  */
  void setAttribute_float(const std::string& attr_key, float fvalue);
  
  //! Get the attribute in the form of an string

  /*!  Gets the attribute with the given keyname, and returns the
    value stored for that attribute. If the attribute has a different
    type than described by the attribute, you will get unwanted
    behaviour. 

    @param attr_key The key name for the attribute

    @return The value for the given attribute.
  */
  const std::string& getAttribute_string(const std::string& attr_key);

  //! Set the attribute for the given key with the given string value

  /*!  The attribute key provided is checked for its existence. If it
    exists, the attribute is modified to be of the string type, and
    the data is modified to be of the string value.

    If the attribute doesn't already exist, the attribute is created
    with the given key and value and placed within the attributeList.

    @param attr_key The key name for the attribute

    @param svalue The string value to set the given attribute to.
  */
  void setAttribute_string(const std::string& attr_key, std::string svalue);
  
  //! Get the attribute in the form of an float array

  /*!  Gets the attribute with the given keyname, and returns the
    value stored for that attribute. If the attribute has a different
    type than described by the attribute, you will get unwanted
    behaviour. 

    @param attr_key The key name for the attribute

    @return The value for the given attribute.
  */
  componentFloatArrayType* getAttribute_floatArray(const std::string& attr_key);

  //! Set the attribute for the given key with the given float array value

  /*!  The attribute key provided is checked for its existence. If it
    exists, the attribute is modified to be of the float array type, and
    the data is modified to be of the float array value.

    If the attribute doesn't already exist, the attribute is created
    with the given key and value and placed within the attributeList.

    @param attr_key The key name for the attribute

    @param sfvalue The float array value to set the given attribute to.
  */
  void setAttribute_floatArray(const std::string& attr_key, componentFloatArrayType sfvalue);
  
  //! Get the attribute in the form of an integer array

  /*!  Gets the attribute with the given keyname, and returns the
    value stored for that attribute. If the attribute has a different
    type than described by the attribute, you will get unwanted
    behaviour. 

    @param attr_key The key name for the attribute

    @return The value for the given attribute.
  */
  componentIntegerArrayType* getAttribute_intArray(std::string attr_key);

  //! Set the attribute for the given key with the given integer array value

  /*!  The attribute key provided is checked for its existence. If it
    exists, the attribute is modified to be of the integer array type, and
    the data is modified to be of the integer array value.

    If the attribute doesn't already exist, the attribute is created
    with the given key and value and placed within the attributeList.

    @param attr_key The key name for the attribute

    @param sivalue The integer array value to set the given attribute to.
  */
  void setAttribute_intArray(const std::string& attr_key, 
			     componentIntegerArrayType sivalue);
  

  //! Gets the attribute structure

  /*!
    Gets the attribute by the given key name.

    @param attr_key The key name for the attribute

    @return The attribute structure.
   */
  attribute getAttribute(const std::string& attr_key);
  void setAttribute(const std::string&, int);
  void setAttribute(const std::string&, float);
  void setAttribute(const std::string&, std::string);
  void setAttribute(const std::string&, componentFloatArrayType);
  void setAttribute(const std::string&, componentIntegerArrayType);
  
  //! Updates the component based on the current set of attributes

  /*!  Used to update the component. This should be performed after
    modifications have been made on the component's attributes or
    members.

    @return Returns a non-zero value if it is successful.
  */
  virtual int update() = 0;
};

#endif //AE__ABSTRACTCOMPONENT_H
