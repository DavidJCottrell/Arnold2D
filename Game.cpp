//
// Created by david on 06/04/24.
//

#include "Game.h"

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

    addEntity<Player>(Player(15, 15, 1));
    addEntity<Enemy>(Enemy(15, 15, 2));
    addEntity<Enemy>(Enemy(150, 150, 3));

    isRunning = true;
    return true;
}


void Game::handleEvents() {
    while (SDL_PollEvent(&sdlEvent)) {
        if (sdlEvent.type == SDL_QUIT) {
            isRunning = false;
            return;
        }
        auto it = entities.begin();
        dynamic_cast<Player *>((*it).get())->handleEvents(sdlEvent);
    }
}

void Game::update() {
    int timeToWait = FRAME_TARGET_TIME - (SDL_GetTicks() - lastFrameTime);
    if (timeToWait > 0 && timeToWait <= FRAME_TARGET_TIME) {
        SDL_Delay(timeToWait);
    }

    double deltaTime = (SDL_GetTicks() - lastFrameTime) / 1000.0;

    lastFrameTime = SDL_GetTicks();

    for (auto &entity: entities) {
        entity->update(deltaTime);
    }
}

void Game::render() {
    SDL_RenderClear(renderer);

    for (auto &entity: entities)
        entity->render(renderer);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderPresent(renderer); // Swap buffers
}

void Game::clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    printf("Game cleaned\n");
}

template<typename T>
void Game::addEntity(T entity) {
    static_assert(std::is_base_of<Entity, T>::value, "entity_class must be derived from Entity");
    entities.push_back(std::make_unique<T>(entity.coordinates_.x, entity.coordinates_.y, entities.size()));
}

Game::Game() = default;

