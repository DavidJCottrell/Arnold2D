#ifndef ARNOLD_ENTITY_H
#define ARNOLD_ENTITY_H

#pragma once

#include <SDL2/SDL.h>

using namespace Utils;

class Entity {
public:
    Entity(const Geometry::Vector2D coordinates, Game *game, int health) {
        this->coordinates = coordinates;
        this->game = game;
        this->health = health;
    };

    virtual ~Entity() = default;

    virtual void render(SDL_Renderer *renderer) = 0;

    virtual void update(double deltaTime) = 0;

    bool isMarkedForRemoval = false;

    Geometry::Vector2D dimensions{};
    Geometry::Vector2D coordinates{};
    Game *game;

protected:
    mutable int health;
};


#endif //ARNOLD_ENTITY_H
