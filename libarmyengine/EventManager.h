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

    Used to manage the events within the game. All events are polled
    through an external source, and passed into the event manager to
    be retrieved. Any systems that can make use of the events will
    then retrieve the events and pass these events onto the components
    that make use of them.
    
*/

#ifndef AE__EVENTMANAGER_H
#define AE__EVENTMANAGER_H

//CLASSES
class EventManager;

//INCLUDES
#include <memory>
#include <list>
#include <vector>

#include "SFML\Graphics.hpp"

//TYPEDEFS

//! Type used to events
typedef sf::Event eventType;

//! Type used for holding the events within the event managerx
typedef std::vector<std::shared_ptr<eventType>> eventListType;

//! Used to Poll for events and store them for later retrieval each frame.

/*!
  
  The Event manager polls for events and stores them. The current
  implementation stores events only from the SFML event polling
  system, which will be changed in the future.

 */
class EventManager {
 private:
  //! Used to store the events
  eventListType eventList;

  //! The window which contains the eventsx
  sf::RenderWindow* window;

  //! Singleton constructor
  EventManager() {
    this->window = nullptr;
  }
 public:

  //! Singletone method, returns the single instance

  /*!

    @return Returns the single instance of the event manager
   */
  static EventManager* getInstance() {
    static EventManager _instance;
    return &_instance;
  }

  //! Sets the current window to retrieve events from.

  /*!
    
    @param window is the window we wish to retreive events from.
    
   */
  void setWindow(sf::RenderWindow* window);
  
  //! polls the assigned window for events and stores them.

  /*!

    The event manager clears the list, polls the events that have
    occured and stores them within the event manager.

   */
  void pollEvents();

  //! Gets the list of events from the event manager.

  /*!

    @return The list of events.

   */
  eventListType& getEvents();
};

#endif //AE__EVENTMANAGER_H
