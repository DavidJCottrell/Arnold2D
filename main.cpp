#include <SDL2/SDL.h>
#include <thread>
#include <chrono>
#include <random>
#include "Engine/Game.h"
#include "Constants.h"
#include "Entities/Player/Player.h"
#include "Entities/Enemies/Enemy.h"
#include "Engine/MessageHandler.h"
#include "Engine/Map.h"

void spawnEnemies(Game *game, bool useEnemies)
{
    while (game->getIsRunning() && useEnemies)
    {
        std::random_device rd;
        int randX = std::uniform_int_distribution<int>(0, WINDOW_WIDTH)(rd);
        int randY = std::uniform_int_distribution<int>(0, WINDOW_HEIGHT)(rd);

        game->addEntity<Enemy>(Enemy({(float)randX, (float)randY}, game));
        std::this_thread::sleep_for(std::chrono::milliseconds(ENEMY_SPAWN_DELAY));
    }
}

int main()
{
    Game game;

    bool initSuccess = game.init(
        "A Game Title",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH, WINDOW_HEIGHT);

    if (!initSuccess)
    {
        std::cout << "Failed to initialise SDL" << std::endl;
        return 1;
    }

    Map *map = new Map(game.getRenderer());

    game.map = map;

    std::thread enemySpawner(spawnEnemies, &game, true);

    game.addEntity<Player>(Player({400, 300}, &game));

    while (game.getIsRunning())
    {
        game.handleEvents();
        game.update();
        game.render();
    }

    enemySpawner.join();
    game.clean();

    return 0;
}
