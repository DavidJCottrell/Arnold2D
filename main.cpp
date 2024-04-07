#include <SDL2/SDL.h>
#include "Game.h"
#include "Constants.h"
#include "Entities/Player.h"

int main() {
    Game game;

    bool initSuccess = game.init(
            "A Game Title",
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            WINDOW_WIDTH, WINDOW_HEIGHT);

    if (!initSuccess) {
        std::cout << "Failed to initialise SDL" << std::endl;
        return 1;
    }

    Player player = Player(15, 15, &game);
    game.addEntity<Player>(player);

    while (game.getIsRunning()) {
        game.handleEvents();
        game.update();
        game.render();
    }

    game.clean();

    return 0;
}
