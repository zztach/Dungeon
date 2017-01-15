/* 
 * File:   InputHandler.h
 * Author: zisis
 *
 * Created on March 8, 2015, 3:40 PM
 */

#ifndef INPUTHANDLER_H
#define	INPUTHANDLER_H

#include <SDL.h>
#include <map>
#include <string>
#include "InputState.h"
#include "../controls/Control.h"

class InputHandler {
public:
    InputHandler();
    InputHandler(const InputHandler& orig);
    virtual ~InputHandler();
    InputState* handleInput();
private:
    std::map<char,KeyState*> keysPressed;
    MouseState mouseState;
    SDL_Event event;    
};

#endif	/* INPUTHANDLER_H */

