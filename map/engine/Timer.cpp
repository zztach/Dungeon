/* 
 * File:   Timer.cpp
 * Author: zisis
 * 
 * Created on April 3, 2014, 11:51 PM
 */

#include "Timer.h"

Timer::Timer() {
    // current counter value, meaningful only in relation to other counter values
    counter = SDL_GetPerformanceCounter();
    // platform-specific counter per second
    timeScale = 1.0/SDL_GetPerformanceFrequency();    
    // # of msec since SDL has been initialized
    lastFpsTime = SDL_GetTicks();
    frames = 1;    
    fps = 0;
}

void Timer::tick()
{
    frames++;
    // every second
    if (SDL_GetTicks() - lastFpsTime >= 1000) {
        fps = frames;
        frames = 1;
        lastFpsTime = SDL_GetTicks();
    }
    Uint64 currentTime = SDL_GetPerformanceCounter();
    inGameFrameTime = (currentTime - counter) * timeScale;
    counter = currentTime;       
}

const int Timer::getAverageFPS() const {
    return fps;
}

const double Timer::getInGameFrameTime() const
{    
    return inGameFrameTime;
}

Timer::~Timer() {
    
}

