#ifndef ARNOLD_ENEMY_H
#define ARNOLD_ENEMY_H

#include <random>

#include <SDL2/SDL.h>
#include <cstdio>
#include <cstdlib>
#include "../Entity.h"
#include "../Player/Player.h"
#include "../../Engine/MessageHandler.h"
#include "../../Engine/Utilities/Utils.h"

using namespace Utils::Geometry;

class Enemy : public Entity {
public:
    Enemy(Utils::Geometry::Vector2D _coordinates, Game *_game) : Entity(_coordinates, _game) {
        dimensions = {15, 15};
    }

    void render(SDL_Renderer *renderer) override;

    void update(double deltaTime) override;
};


#endif //ARNOLD_ENEMY_H
