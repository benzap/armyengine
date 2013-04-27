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

    The callback manager contains lists of functions which are used as
    callbacks to components stored within the entities. It includes
    one parameter, which is the entities current ID the function must
    also return '0' in order to determine whether it was successful
    
    Given the design of the engine, the callback has full access to
    all of the managers, and is able to identify the entity it is
    contained in by the given ID, which makes it very flexible.
    
    Function Wrapper is used to wrap functions which contain only one
    parameter It wraps it into a function which can take two
    parameters and discards the second parameter.
    
*/

#ifndef AE__CALLBACK_MANAGER
#define AE__CALLBACK_MANAGER

//CLASSES
class CallbackManager;
class CallbackFunctionWrapper;

//INCLUDES
#include <memory>
#include <functional>
#include <map>
#include <string>

//TYPEDEF

//! Template for a function callback with no parameters
typedef std::function <int(void)> functionBaseTemplate;

//! Template for a function callback with one parameter
typedef std::function<int(int)> functionTemplate;

//! Template for a function callback with two parameters
typedef std::function<int(int, int)> functionEventTemplate;

//! Type used to store the list of callbacks.
typedef std::map<std::string, functionEventTemplate> callbackMapType;


//! The callback manager is used to store and retrieve callbacks

/*!
    The callback manager contains lists of functions which are used as
    callbacks to components stored within the entities. It includes
    one parameter, which is the entities current ID the function must
    also return '0' in order to determine whether it was successful
 */
class CallbackManager {
private:
  //!< Contains the list of callbacks, referenced by the string keyname
  callbackMapType callbackMap;
  //!< Singleton, empty constructor
  CallbackManager() {}
public:
  //!< Singleton method to grab the entity manager instance.

  /*!
    
    @return The callback manager instance.
   */
  static CallbackManager* getInstance() {
    static CallbackManager _instance;
    return &_instance;
  }

  //! Add a callback to the callback manager with zero parameters
  
  /*!  
    
    add a callback to the map the function.

    It is of the form int _f()_, and can be a lambda, std::bind, or
    class object, see the Unit Test CallbackTests

    @param name is the keyname assigned to the callback

    @param func is the function you wish to execute for the callback
  */
  void addCallback(const std::string& name, functionBaseTemplate func);

  //! Add a callback to the callback manager with one parameter
  
  /*!  
    
    add a callback to the map the function.

    It is of the form _int f(int)_, and can be a lambda, std::bind, or
    class object, see the Unit Test CallbackTests

    @param name is the keyname assigned to the callback

    @param func is the function you wish to execute for the callback
  */
  void addCallback(const std::string& name, functionTemplate func);

  //! Add a callback to the callback manager with one parameter
  
  /*!  
    
    add a callback to the map the function.

    It is of the form _int f(int, int)_, and can be a lambda, std::bind, or
    class object, see the Unit Test CallbackTests

    @param name is the keyname assigned to the callback

    @param func is the function you wish to execute for the callback
  */
  void addCallback(const std::string& name, functionEventTemplate func);
  
  //! triggers the given callback, and returns whether it was successful

  /*!
    
   @param name is the keyname of the callback to call

   @param ID is the first parameter, which is usually designated to
   the ID of an entity.
   
   @param eventIndex is the second parameter, which is usually
   designated to the index of the event within the EventManager.
  */
  int triggerCallback(const std::string& name, int ID = 0, int eventIndex = 0);
  
  //! deletes a callback by its key

  /*!

    @param name is the keyname of the callback to remove.
   */
  void removeCallback(const std::string& name);
  
  //! Checks if the manager has the callback by the given keyname 

  /*! returns true, if the provided parameter matches a callback key
      stored within the callbackMap

      @param name is the keyname of the callback you wish to check.

      @return The method returns true if the callback exists,
      otherwise it returns false.
  */
  bool hasCallback(const std::string& name);
};

//! Wrapper to store varying functions as one function type

/*!
  Wrap functionTemplates into functionEventTemplates
  Wrap functionBaseTemplates into functionEventTemplates

  Used to wrap the other given function types into the
  functionEventTemplate type that is stored within the callback
  manager.

  The wrapper converts zero-paramter and one-parameter functions into
  the two-paramter function used within the callback manager, and
  assigns the unused parameters as zero-values.
*/
class CallbackFunctionWrapper {
private:
  functionTemplate func_oneParam; //!< One parameter function
  functionBaseTemplate func_zeroParam; //!< Zero parameter function
  //! The type of function based on the number of parameters.
  enum FuncType {
    ONE_PARAM = 1,
    ZERO_PARAM = 0
  } funcType;
public:
  //! Constructor to convert one-param to two-param
  CallbackFunctionWrapper(functionTemplate func);
  //! Constructor to convert two-param to two-param
  CallbackFunctionWrapper(functionBaseTemplate func);
  
  //! operator() override

  /*!  The function calls func_oneParam or func_zeroParam depending on
    the funcType of the assigned function.

    @param ID is designated to the entity ID that performed the
    callback
    
    @param eventIndex is designated to the index of the event within
    the EventManager

    @return A non-zero value if the callback was successful
   */
  int operator() (int ID, int eventIndex);
};

#endif //AE__CALLBACK_MANAGER
