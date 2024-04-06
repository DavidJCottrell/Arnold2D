#ifndef ARNOLD_ENEMY_H
#define ARNOLD_ENEMY_H

#include <random>

#include <SDL2/SDL.h>
#include <cstdio>
#include <cstdlib>
#include "Entity.h"


class Enemy : public Entity {
public:
    Enemy(float x, float y, Game *_game, int id) : Entity(x, y, _game, id) {
        dimensions = {15, 15};
    }

    void render(SDL_Renderer *renderer) override;

    void update(double deltaTime) override;
};


#endif //ARNOLD_ENEMY_H
