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

    The Defintions within this file are used by the InputSystem to
    determine what type of events to pass to a given InputComponent
    with one of these parameters representing its input type.
    
*/

#ifndef AE__INPUTS_H
#define AE__INPUTS_H

//DEFINITIONS

//define a set of input types

//Keyboard
//! Represents the keyboard button pressed event
#define INPUT_KEYBOARD_PRESSED "KeyboardPressed"
//! Represents the keyboard button released event
#define INPUT_KEYBOARD_RELEASED "KeyboardReleased"

//Mouse
//! Represents the mouse move event
#define INPUT_MOUSE_MOVE "MouseMove"
//! Represents the mouse scrolling event
#define INPUT_MOUSE_SCROLL "MouseScroll"
//! Represents the mouse pressed event
#define INPUT_MOUSE_PRESSED "MouseButtonPressed"
//! Represents the mouse released event
#define INPUT_MOUSE_RELEASED "MouseButtonReleased"

#endif //AE__INPUTS_H
