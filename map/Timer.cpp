/* 
 * File:   Timer.cpp
 * Author: zisis
 * 
 * Created on April 3, 2014, 11:51 PM
 */

#include "Timer.h"

Timer::Timer() {
    lastTime = SDL_GetPerformanceCounter();
    timeScale = 1.0/SDL_GetPerformanceFrequency();    
    Uint32 lastFpsTime = SDL_GetTicks();
    fpsCounter = 1;    
    avgFps = 0;
}

void Timer::tick()
{
    if (SDL_GetTicks() - lastFpsTime >= 1000) {
        avgFps = fpsCounter;
        fpsCounter = 1;
        lastFpsTime = SDL_GetTicks();
    }
    Uint64 currentTime = SDL_GetPerformanceCounter();
    timeElapsed = (currentTime - lastTime) * timeScale;
    lastTime = currentTime;       
    fpsCounter++;
}

const int Timer::getAverageFPS() const {
    return avgFps;
}

const double Timer::getTimeElapsed() const
{
    return timeElapsed;
}

Timer::~Timer() {
    
}

