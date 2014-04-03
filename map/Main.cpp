#include "Game.h"

// our Game object
Game* g_game = 0;

int main(int argc, char* argv[]) {
    g_game = new Game();
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