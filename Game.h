//
// Created by david on 06/04/24.
//

#ifndef ARNOLD_GAME_H
#define ARNOLD_GAME_H

#include <SDL2/SDL.h>
#include <cstdio>
#include <vector>
#include <iostream>
#include <memory>
#include "Enemy.h"
#include "Player.h"
#include "Constants.h"

class Game {
public:
    Game();

    bool init(const char *title,
              int xpos, int ypos,
              int width, int height);

    void handleEvents();

    void update();

    void render();

    void clean();

    [[nodiscard]] bool getIsRunning() const { return isRunning; }

private:
    Uint32 lastFrameTime = 0;
    bool isRunning = false;

    template<typename T>
    void addEntity(T entity);

    SDL_Window *window{};
    SDL_Renderer *renderer{};
    std::vector<std::unique_ptr<Entity>> entities;
    SDL_Event sdlEvent;
};


#endif //ARNOLD_GAME_H
