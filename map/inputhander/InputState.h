/* 
 * File:   InputState.h
 * Author: zisis
 *
 * Created on March 9, 2015, 2:19 AM
 */

#ifndef INPUTSTATE_H
#define	INPUTSTATE_H

#include <map>
#include "../controls/Control.h"
using std::map;

struct KeyState 
{
    bool pressed;
    bool consumed;
    
    KeyState(bool pressedvar, bool consumedvar) {
        pressed = pressedvar;
        consumed = consumedvar;
    }
};

class InputState 
{
public:
    InputState(map<char,KeyState*> keysPressed, MouseState& mouseState);
    //InputState(const InputState& orig);
    const MouseState getMouseState();
    const std::map<char,KeyState*> getKeyboardState();
    virtual ~InputState();
private:
    std::map<char,KeyState*> keysPressed;
    MouseState mouseState;
};

#endif	/* INPUTSTATE_H */

