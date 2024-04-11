#ifndef ARNOLD_ENEMY_H
#define ARNOLD_ENEMY_H

#include <random>

#include <SDL2/SDL.h>
#include <cstdio>
#include <cstdlib>
#include "Entity.h"
#include "Player.h"
#include "../Engine/MessageHandler.h"


class Enemy : public Entity {
public:
    Enemy(Coordinates _coordinates, Game *_game) : Entity(_coordinates, _game) {
        dimensions = {15, 15};
    }

    void render(SDL_Renderer *renderer) override;

    void update(double deltaTime) override;
};


#endif //ARNOLD_ENEMY_H
