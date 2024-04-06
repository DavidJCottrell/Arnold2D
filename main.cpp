#include <SDL2/SDL.h>
#include "Game.h"

Game *game = nullptr;

int main()
{
    game = new Game();

    bool initSuccess = game->init(
            "A Game Title",
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            800, 600);

    if (!initSuccess)
    {
        return 1;
    }

    while (game->running())
    {
        game->handleEvents();
        game->update();
        game->render();

        SDL_Delay(1000 / 60);
    }

    game->clean();

    return 0;
}
