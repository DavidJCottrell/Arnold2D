//
// Created by david on 06/04/24.
//

#ifndef ARNOLD_PLAYER_H
#define ARNOLD_PLAYER_H


#include <SDL2/SDL.h>
#include <cstdio>
#include "Entity.h"

#define MOVE_AMOUNT 5

class Player : public Entity
{
public:
    Player();
    Player(int x, int y) : Entity(x, y) {}
    ~Player();

    bool isMoving = false;

    void moveRight();
    void moveLeft();
    void moveUp();
    void moveDown();

    void render(SDL_Renderer *renderer);
};


#endif //ARNOLD_PLAYER_H
