#include "Game.h"

// our Game object
Game* g_game = 0;

int main(int argc, char* argv[]) {
    g_game = new Game();
    g_game->init("Dungeon", 100, 100, 1360, 768, 0);

    Uint64 lastTime = SDL_GetPerformanceCounter();
    double timeScale = 1.0/SDL_GetPerformanceFrequency();
    double timeElapsed;
    Uint32 lastFpsTime = SDL_GetTicks();
    int fpsCounter = 1;
    while (g_game->running()) {

        if (SDL_GetTicks() - lastFpsTime > 1000) {
            fpsCounter = 1;
            lastFpsTime = SDL_GetTicks();
        }
        Uint64 currentTime = SDL_GetPerformanceCounter();
        timeElapsed = (currentTime - lastTime) * timeScale;
        lastTime = currentTime;       
        g_game->handleEvents(timeElapsed);
        g_game->update();
        g_game->render();
        fpsCounter++;
    }
    g_game->clean();

    return 0;
}