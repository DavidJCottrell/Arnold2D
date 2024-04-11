#ifndef ARNOLD_ENTITY_H
#define ARNOLD_ENTITY_H

#include <SDL2/SDL.h>
#include <cstdio>
#include <memory>
#include "../Engine/Utilities/Geometry.h"

class Game;

#include "../Engine/Game.h"


class Entity {
public:
    Entity(Coordinates _coordinates, Game *_game) {
        coordinates = _coordinates;
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
