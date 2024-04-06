//
// Created by david on 06/04/24.
//

#ifndef ARNOLD_ENEMY_H
#define ARNOLD_ENEMY_H

#include <random>

#include <SDL2/SDL.h>
#include <cstdio>
#include <cstdlib>
#include "Entity.h"

class Enemy : public Entity {
public:
    Enemy(float x, float y, int id) : Entity(x, y, id) {
        dimensions_ = {15, 15};
    }

    void render(SDL_Renderer *renderer) override;

    void update(double deltaTime) override;

    void goCrazy();
};


#endif //ARNOLD_ENEMY_H
