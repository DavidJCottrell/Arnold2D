#include <SDL2/SDL.h>
#include <thread>
#include <chrono>
#include <random>
#include <Arnold.h>

void spawnEnemies(Game* game, const bool useEnemies)
{
    int spawnDelay = ENEMY_SPAWN_DELAY;
    while (game->getIsRunning() && useEnemies)
    {
        std::random_device rd;
        const int randX = std::uniform_int_distribution(0, WINDOW_WIDTH)(rd);
        const int randY = std::uniform_int_distribution(0, WINDOW_HEIGHT)(rd);
        const int enemyType = std::uniform_int_distribution(1, 4)(rd);

        if (enemyType == 4)
        {
            game->addEntity<Juggernaut>(Juggernaut({static_cast<float>(randX), static_cast<float>(randY)}, game));
        }
        else
        {
            game->addEntity<Enemy>(Enemy({static_cast<float>(randX), static_cast<float>(randY)}, game));
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(spawnDelay));
        spawnDelay -= 50;
        if (spawnDelay <= 500) spawnDelay = 500;
    }
}

int main()
{
    Game game;

    if (!game.init(
        "A Game Title",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH, WINDOW_HEIGHT))
    {
        std::cout << "Failed to initialise SDL" << std::endl;
        return 1;
    }

    auto* map = new Map(game.getRenderer());

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
