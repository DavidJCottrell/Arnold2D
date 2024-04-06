//
// Created by david on 06/04/24.
//

#ifndef ARNOLD_ENTITY_H
#define ARNOLD_ENTITY_H

#include <SDL2/SDL.h>
#include <cstdio>
#include <memory>

struct dimensions {
    float w;
    float h;
};

struct coordinates {
    float x;
    float y;
};

class Entity {
public:
    Entity(float x, float y, int id) {
        coordinates_ = {x, y};
        ID = id;
    };

    virtual ~Entity() = default;

    virtual void render(SDL_Renderer *renderer) = 0;

    virtual void update(double deltaTime) = 0;

    int ID;

    dimensions dimensions_{};
    coordinates coordinates_{};
};


#endif //ARNOLD_ENTITY_H
