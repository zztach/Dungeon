/* 
 * File:   InputState.cpp
 * Author: zisis
 * 
 * Created on March 9, 2015, 2:19 AM
 */

#include "InputState.h"

InputState::InputState(map<char,KeyState*> keysPressed, MouseState& mouseState) {
    this->keysPressed = keysPressed;
    this->mouseState = mouseState;
}

const MouseState InputState::getMouseState()
{
    return this->mouseState;
}

const std::map<char,KeyState*> InputState::getKeyboardState()
{
    return this->keysPressed;
}
    
    
//InputState::InputState(const InputState& orig) {
//}

InputState::~InputState() {
}

