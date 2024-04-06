//
// Created by david on 06/04/24.
//

#ifndef ARNOLD_GAME_H
#define ARNOLD_GAME_H

#include <SDL2/SDL.h>
#include <cstdio>
#include <vector>
#include <iostream>
#include "Enemy.h"
#include "Player.h"

class Game
{
public:
    bool init(const char *title,
              int xpos, int ypos,
              int width, int height);

    void handleEvents();
    void update();
    void render();
    void clean();

    int getRefreshRate();

    bool running() { return isRunning; }

private:
    bool isRunning;
    void spawnEntities(int width, int height);
    SDL_Window *window;
    SDL_Renderer *renderer;
    std::vector<Enemy> enemies;
    Player player;

    SDL_Event sdlEvent;
    SDL_Keycode pressedKey;

    bool isPlayerEnemyColliding();

    bool isColliding = false;
    int collisionCount = 0;
    int collidedEnemyId = -1;
};


#endif //ARNOLD_GAME_H
