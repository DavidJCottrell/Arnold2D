#include <SDL2/SDL.h>
#include <random>
#include <Arnold.h>

int main() {
    Game game;

    if (!game.init(
            "A Game Title",
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            WINDOW_WIDTH, WINDOW_HEIGHT)) {
        throw std::runtime_error("Failed to initialise SDL");
    }

    auto *map = new Map(game.getRenderer());

    game.map = map;

    game.addEntity<Player>(Player({400, 300}, &game));

    while (game.getIsRunning()) {
        game.handleEvents();
        game.update();
        game.render();
    }

    game.clean();

    return 0;
}
