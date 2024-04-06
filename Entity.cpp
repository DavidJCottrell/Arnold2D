//
// Created by david on 06/04/24.
//

#include "Entity.h"

Entity::Entity()
{
}

Entity::Entity(int x, int y)
{
    rect.x = x;
    rect.y = y;
    rect.w = 50;
    rect.h = 50;
}
Entity::~Entity() {}

void Entity::render(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &rect);
}
