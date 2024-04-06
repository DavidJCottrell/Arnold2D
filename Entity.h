//
// Created by david on 06/04/24.
//

#ifndef ARNOLD_ENTITY_H
#define ARNOLD_ENTITY_H

#include <SDL2/SDL.h>
#include <cstdio>

class Entity
{
public:
    Entity();
    Entity(int x, int y);
    ~Entity();

    void render(SDL_Renderer *renderer);
    SDL_Rect rect;
};


#endif //ARNOLD_ENTITY_H
