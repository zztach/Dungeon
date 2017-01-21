/* 
 * File:   InputHandler.cpp
 * Author: zisis
 * 
 * Created on March 8, 2015, 3:40 PM
 */

#include "InputHandler.h"

InputHandler::InputHandler() {
    keysPressed[SDLK_w] = new KeyState(false, false);
    keysPressed[SDLK_a] = new KeyState(false, false);
    keysPressed[SDLK_s] = new KeyState(false, false);
    keysPressed[SDLK_d] = new KeyState(false, false);
    keysPressed[SDLK_f] = new KeyState(false, false);
    keysPressed[SDLK_TAB] = new KeyState(false, false);
    keysPressed[SDLK_ESCAPE] = new KeyState(false, false);
}

InputHandler::InputHandler(const InputHandler &orig) {
}

InputHandler::~InputHandler() {
}

// Load keys from xml file.
// Each key should have an associated component (e.g camera), whether it's a toggle or responds to repetitive strokes
InputState *InputHandler::handleInput() {
    SDL_GetMouseState(&mouseState.x, &mouseState.y);

    mouseState.leftButtonDown = SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(1);
    mouseState.middleButtonDown = SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(2);
    mouseState.rightButtonDown = SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(3);
    mouseState.mouseMovement = false;

    SDL_PumpEvents();
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_f) {
                    if (keysPressed.count(event.key.keysym.sym) && keysPressed[event.key.keysym.sym]->pressed) {
                        keysPressed[event.key.keysym.sym]->consumed = false;
                    } else {
                        keysPressed[event.key.keysym.sym] = new KeyState(true, false);
                    }
                } else
                    keysPressed[event.key.keysym.sym] = new KeyState(true, false);
                break;
            case SDL_KEYUP:
                //if (event.key.keysym.sym == SDLK_f) {
                //    keysPressed[event.key.keysym.sym] = false;
                //    break;
                //}
                if (keysPressed.count((const char &) event.key.keysym.sym) &&
                    keysPressed.at((const char &) event.key.keysym.sym)->pressed)
                {
                    keysPressed[event.key.keysym.sym]->pressed = false;
                    keysPressed[event.key.keysym.sym]->consumed = false;
                    break;
                }
            case SDL_MOUSEMOTION:
                mouseState.mouseMovement = true;
                mouseState.xrel = event.motion.xrel;
                mouseState.yrel = event.motion.yrel;
                break;
            default:
                break;
        }
    }
    // allows the mouse events to be processed even when cursor is out of the game window
    SDL_SetRelativeMouseMode(SDL_TRUE);

    return new InputState(keysPressed, mouseState);
}