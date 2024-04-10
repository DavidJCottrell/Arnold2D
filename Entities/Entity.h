#ifndef ARNOLD_ENTITY_H
#define ARNOLD_ENTITY_H

#include <SDL2/SDL.h>
#include <cstdio>
#include <memory>

class Game;

#include "../Engine/Game.h"


struct Dimensions {
    float w;
    float h;
};

struct Coordinates {
    float x;
    float y;
};

class Entity {
public:
    Entity(float _x, float _y, Game *_game) {
        coordinates = {_x, _y};
        game = _game;
    };

    virtual ~Entity() = default;

    virtual void render(SDL_Renderer *renderer) = 0;

    virtual void update(double deltaTime) = 0;

    bool isMarkedForRemoval = false;

    Dimensions dimensions{};
    Coordinates coordinates{};
    Game *game;


};


#endif //ARNOLD_ENTITY_H
