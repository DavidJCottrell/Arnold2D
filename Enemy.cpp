//
// Created by david on 06/04/24.
//

#include "Enemy.h"

void Enemy::render(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    SDL_Rect shape = {
            (int) coordinates_.x,
            (int) coordinates_.y,
            (int) dimensions_.w,
            (int) dimensions_.h,
    };
    SDL_RenderFillRect(renderer, &shape);

    SDL_RenderFillRect(renderer, &shape);
}

void Enemy::update(double deltaTime) {

    int xDirection = coordinates_.x > 400 ? -1 : 1;
    int yDirection = coordinates_.y > 400 ? -1 : 1;

    coordinates_.x += (deltaTime * 50) * xDirection;
    coordinates_.y += (deltaTime * 50) * yDirection;
}
