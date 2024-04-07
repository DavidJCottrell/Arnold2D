#include "Game.h"
#include "Entities/Player.h"

bool Game::init(const char *title,
                int xpos, int ypos,
                int width, int height) {

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        fprintf(stderr, "Failed to init SDL!\n");
        return false;
    }

    window = SDL_CreateWindow(
            title,
            xpos, ypos,
            width, height,
            SDL_WINDOW_SHOWN);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

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
        auto it = entities.begin();
        dynamic_cast<Player *>((*it).get())->handleEvents(sdlEvent);
    }
}

void Game::removeMarkedEntities() {
    entities.erase(std::remove_if(
            entities.begin(), entities.end(),
            [](const std::unique_ptr<Entity> &entity) {
                return entity->isMarkedForRemoval;
            }), entities.end());

}

void Game::update() {
    int timeToWait = FRAME_TARGET_TIME - (SDL_GetTicks() - lastFrameTime);
    if (timeToWait > 0 && timeToWait <= FRAME_TARGET_TIME)
        SDL_Delay(timeToWait);

    double deltaTime = (SDL_GetTicks() - lastFrameTime) / 1000.0;
    lastFrameTime = SDL_GetTicks();

    removeMarkedEntities();

    for (auto &entity: entities)
        entity->update(deltaTime);
}

void Game::render() {
    SDL_RenderClear(renderer);

    for (auto &entity: entities)
        entity->render(renderer);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderPresent(renderer);
}

void Game::clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    printf("Game cleaned\n");
}

const std::vector<std::unique_ptr<Entity>> &Game::getEntities() const {
    return entities;
}

Game::Game() = default;

