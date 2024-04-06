//
// Created by david on 06/04/24.
//

#include "Enemy.h"

void Enemy::render(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    SDL_Rect shape = {
            (int) coordinates.x,
            (int) coordinates.y,
            (int) dimensions.w,
            (int) dimensions.h,
    };
    SDL_RenderFillRect(renderer, &shape);

    SDL_RenderFillRect(renderer, &shape);
}

void Enemy::update(double deltaTime) {

    int xDirection = coordinates.x > 400 ? -1 : 1;
    int yDirection = coordinates.y > 400 ? -1 : 1;

    coordinates.x += (float) (deltaTime * 50) * xDirection;
    coordinates.y += (float) (deltaTime * 50) * yDirection;
}
