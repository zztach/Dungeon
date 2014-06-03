/* 
 * File:   Timer.h
 * Author: zisis
 *
 * Created on April 3, 2014, 11:51 PM
 */

#ifndef TIMER_H
#define	TIMER_H
#include <SDL.h>
#include <glew.h>
#include <SDL_opengl.h>
class Timer {
public:
    Timer();
    void tick();
    const int getAverageFPS() const;
    const double getTimeElapsed() const; 
    virtual ~Timer();
private:
    Uint64 lastTime;
    double timeScale;    
    Uint32 lastFpsTime;
    int fpsCounter;
    int avgFps;
    double timeElapsed;
};

#endif	/* TIMER_H */

