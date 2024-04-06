//
// Created by david on 06/04/24.
//

#ifndef ARNOLD_PLAYER_H
#define ARNOLD_PLAYER_H

#include <SDL2/SDL.h>
#include <cstdio>
#include "Entity.h"

#define MOVE_AMOUNT 1

class Player : public Entity {
public:
    Player(float x, float y, int id) : Entity(x, y, id) {
        dimensions_ = {20, 20};
    }

    bool isMoving = false;

    void moveRight();

    void handleEvents(SDL_Event sdlEvent);

    void render(SDL_Renderer *renderer) override;

    void update(double deltaTime) override;

};


#endif //ARNOLD_PLAYER_H
