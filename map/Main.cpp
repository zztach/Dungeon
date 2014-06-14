#include "engine/Game.h"
/**
 @file
 * The entry point of Dungeon. Only the game loop is defined here. An instace of
 * the Game class is created and handles the actions inside the game loop 
 */
int main(int argc, char* argv[]) {    
    Game* g_game = new Game();
    g_game->init("Dungeon", 100, 100, 1360, 768, 0);

    while (g_game->running()) {
        g_game->frameStart();
        g_game->handleEvents();
        g_game->render3D();
        g_game->render2D();
        g_game->frameEnd();
    }
    g_game->clean();

    return 0;
}