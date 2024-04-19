#include<Arnold.h>

#include <bits/random.h>

// TODO: extract
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
    const milliseconds newInterval = task->interval - milliseconds(20);
    if (newInterval >= milliseconds(500)) {
        task->interval = newInterval;
    }
}

void executeBackgroundTasks(std::vector<Task> *newTasks, Game *game) {
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

bool Game::init(const char *windowTitle,
                const int xPos, const int yPos,
                const int width, const int height) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        fprintf(stderr, "Failed to init SDL!\n");
        return false;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        return false;
    }

    window = SDL_CreateWindow(
            windowTitle,
            xPos, yPos,
            width, height,
            SDL_WINDOW_SHOWN);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    map = new Map(renderer);

    tasks.push_back({spawnPlayerDrops, "spawnDrops", seconds(5), system_clock::now()});
    tasks.push_back({spawnEnemies, "spawnEnemies", seconds(2), system_clock::now()});

    tSpawner = std::thread(executeBackgroundTasks, &tasks, this);

    isRunning = true;
    return true;
}

void Game::handleEvents() {
    SDL_Event sdlEvent;
    while (SDL_PollEvent(&sdlEvent)) {
        if (sdlEvent.type == SDL_QUIT) {
            isRunning = false;
            return;
        }
        // Retrieve the player object from the entities list and handle the user's player input
        for (const auto &entity: entities) {
            if (auto *player = dynamic_cast<Player *>(entity.get())) {
                player->handleEvents(sdlEvent);
                break;
            }
        }
    }
}

void Game::update() {
    const int timeToWait = FRAME_TARGET_TIME - (SDL_GetTicks() - lastFrameTime);
    if (timeToWait > 0 && timeToWait <= FRAME_TARGET_TIME)
        SDL_Delay(timeToWait);

    const double deltaTime = (SDL_GetTicks() - lastFrameTime) / 1000.0;
    lastFrameTime = SDL_GetTicks();

    // Remove entities that have been marked for deletion
    entities.erase(
            std::remove_if(
                    entities.begin(), entities.end(),
                    [](const std::unique_ptr<Entity> &entity) {
                        return entity->isMarkedForRemoval;
                    }
            ),
            entities.end()
    );

    for (const auto &entity: entities)
        entity->update(deltaTime);
}

void Game::render() {
    SDL_RenderClear(renderer);

    map->DrawMap(renderer);

    for (const auto &entity: entities)
        entity->render(renderer);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderPresent(renderer);
}

void Game::clean() const {
    if (tSpawner.joinable()) tSpawner.join();
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    printf("Game cleaned\n");
}

const std::vector<std::unique_ptr<Entity>> &Game::getEntities() const {
    return entities;
}

Player *Game::getPlayer() const {
    for (const auto &entity: entities) {
        if (auto *pPlayer = dynamic_cast<Player *>(entity.get())) {
            return pPlayer;
        }
    }
    return nullptr;
}

Game::Game() = default;
