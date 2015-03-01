/* 
 * File:   Timer.h
 * Author: zisis
 *
 * Created on April 3, 2014, 11:51 PM
 */

#ifndef TIMER_H
#define	TIMER_H
#include <iostream>
#include <SDL.h>
#include <glew.h>
#include <SDL_opengl.h>

/**
 * Responsible for counting the app's FPS and tracking game's duration
 */
class Timer {
public:
    Timer();
    void tick();
    const int getAverageFPS() const;
    /**
     * Controls the speed of the game. Lowering its value slows down the game, while increasing it speeds it up.
     * @return the duration of each frame in msec
     */
    const double getInGameFrameTime() const; 
    virtual ~Timer();
private:
    // counter
    Uint64 counter;
    // the duration of 1 count
    double timeScale;    
    Uint32 lastFpsTime;    
    int frames;
    int fps;
    double inGameFrameTime;
};

#endif	/* TIMER_H */

