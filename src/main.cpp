#include <SDL2/SDL.h>
#include <thread>
#include <random>
#include <Arnold.h>
#include <chrono>

using namespace std::chrono;

struct Task {
    void (*callback)(Game *game, Task *task);

    milliseconds interval;
    system_clock::time_point last_executed;
};

void executeTasks(std::vector<Task> *newTasks, Game *game) {
    while (game->getIsRunning()) {
        for (auto &task: *newTasks) {
            auto elapsed = duration_cast<milliseconds>(system_clock::now() - task.last_executed);
            if (elapsed >= task.interval) {
                task.callback(game, &task);
                task.last_executed = system_clock::now();
            }
        }
    }
}

void spawnEnemies(Game *game, Task *task) {
    std::random_device rd;
    const int randX = std::uniform_int_distribution(0, WINDOW_WIDTH)(rd);
    const int randY = std::uniform_int_distribution(0, WINDOW_HEIGHT)(rd);
    const int enemyType = std::uniform_int_distribution(1, 4)(rd);

    if (enemyType == 4) {
        game->addEntity<Juggernaut>(Juggernaut({static_cast<float>(randX), static_cast<float>(randY)}, game));
    } else {
        game->addEntity<Enemy>(Enemy({static_cast<float>(randX), static_cast<float>(randY)}, game));
    }

    // Increase spawn rate by 20ms each time an enemy is spawned (to a limit of 500ms)
    milliseconds newInterval = task->interval - milliseconds(20);
    if (newInterval >= milliseconds(500)) {
        task->interval = newInterval;
    }
}

void spawnPlayerDrops(Game *game, Task *task) {
    std::random_device rd;
    const int randX = std::uniform_int_distribution(0, WINDOW_WIDTH)(rd);
    const int randY = std::uniform_int_distribution(0, WINDOW_HEIGHT)(rd);
    const int pickupType = std::uniform_int_distribution(1, 3)(rd);

    if (pickupType == 1) {
        game->addEntity<WeaponPickup>(WeaponPickup({static_cast<float>(randX), static_cast<float>(randY)}, game, uzi));
    } else if (pickupType == 2) {
        game->addEntity<WeaponPickup>(
                WeaponPickup({static_cast<float>(randX), static_cast<float>(randY)}, game, shotgun));
    } else {
        game->addEntity<HealthPickup>(HealthPickup({static_cast<float>(randX), static_cast<float>(randY)}, game));
    }


}

void resetWeaponPickup(Game *game, Task *task) {
    game->getPlayer()->weaponType = rifle;
}


int main() {
    Game game;

    if (!game.init(
            "A Game Title",
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            WINDOW_WIDTH, WINDOW_HEIGHT)) {
        std::cout << "Failed to initialise SDL" << std::endl;
        return 1;
    }

    auto *map = new Map(game.getRenderer());

    game.map = map;

    std::vector<Task> tasks;
    tasks.push_back({spawnEnemies, seconds(2), system_clock::now()});
    tasks.push_back({resetWeaponPickup, seconds(10), system_clock::now()});
    tasks.push_back({spawnPlayerDrops, seconds(5), system_clock::now()});

    std::thread tSpawner(executeTasks, &tasks, &game);

    game.addEntity<Player>(Player({400, 300}, &game));

    while (game.getIsRunning()) {
        game.handleEvents();
        game.update();
        game.render();
    }

    tSpawner.join();
    game.clean();

    return 0;
}
