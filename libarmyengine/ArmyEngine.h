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

    Main class which should be used as an interface to access the
    functionality of the armyengine pieces
    
    The only other classes considered for modification are the
    Managers
    
*/

#ifndef AE__ARMYENGINE_H
#define AE__ARMYENGINE_H

//CLASSES
class ArmyEngine;

//INCLUDES
#include <memory>
#include <functional>

#include "SFML\Window.hpp"
#include "SFML\Graphics.hpp"

#include "Managers.h"
#include "Systems.h"
#include "Entities.h"
#include "Components.h"
#include "AE_Attributes.h"
#include "AE_Events.h"
#include "AE_Utilities.h"

#include "ComponentFactory.h"
#include "EntityFactory.h"

//TYPEDEF
//! Function Type for registering global events.
typedef std::function<int(int)> functionRegisterTemplate;

//ENUMERATION
//! Used for the registered global events.
enum EnumEventType {
	EVENT_CLOSED,
	EVENT_RESIZED,
	EVENT_LOSTFOCUS,
	EVENT_GAINEDFOCUS,
	EVENT_TEXTENTERED,
	EVENT_MOUSE_ENTER,
	EVENT_MOUSE_EXIT
};

//DEFINITION

//! Sets the window width
#define WINDOW_WIDTH 800

//! Sets the window height
#define WINDOW_HEIGHT 600

//! Sets the default window title.
#define WINDOW_TITLE "ArmyEngine Game"

//! Army engine singleton facade. Frontend to the engine
class ArmyEngine {
 private:
  //! The application window
  sf::RenderWindow window;
  
  //! Instance of the component factory
  ComponentFactory componentFactory;
  
  //! Instance of the entity factory
  EntityFactory entityFactory;

  
  //! derived eventSystem class
  std::shared_ptr<EventSystem> eventSystem;

  //! derived stateSystem class
  std::shared_ptr<StateSystem> stateSystem;

  ArmyEngine();

 public:

  //! Singleton method used to retrieve the single instance.

  /*!

    @return Returns the army engine instance.
   */
  static ArmyEngine* getInstance() {
    static ArmyEngine _instance;
    return &_instance;
  }

  //get - set

  //! Used to get the component factory instance.
  ComponentFactory& getComponentFactory();

  //! Used to get the entity factory instance.
  EntityFactory& getEntityFactory();

  //! Used to set the state machine function.
  void setStateMachineFunction(functionStateMachineTemplate func);

  //! Add an entity to the engine
  void addEntity(std::shared_ptr<entityType>);

  //! Add a collision callback to the engine.
  void addCollisionCallback(collisionTagTuple, functionCollisionTemplate);

  //! Add a state callback to the engine.
  void addStateCallback(std::string, functionTemplate);

  //! Add an event callback to the engine.
  void addEventCallback(EnumEventType, functionRegisterTemplate);

  //! Add an input callback to the engine.
  void addInputCallback(std::string, functionEventTemplate);

  //! Get the instance of the application window.
  sf::RenderWindow* getWindow();

  //! Set the window size (TODO: fix this)
  void setWindowSize(int width, int height);

  //! Enable the state of a given state component.
  void setStateEnable(const std::string&);

  //! Disable the state of a given state component.
  void setStateDisable(const std::string&);

  //! Get the state of a given state component.
  stateType getState(const std::string&);

  //! Load a sprite into the engine
  void loadSpriteFromFile(std::string name, std::string filename);

  //! Run the main engine loop.
  void runMainLoop();
};

#endif //AE__ARMYENGINE_H
