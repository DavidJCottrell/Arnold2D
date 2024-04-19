#include "HealthPickup.h"

void HealthPickup::render(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);

    const SDL_Rect playerRect = {
            static_cast<int>(coordinates.x),
            static_cast<int>(coordinates.y),
            static_cast<int>(dimensions.x),
            static_cast<int>(dimensions.y)
    };
    SDL_RenderFillRect(renderer, &playerRect);
}

void HealthPickup::update(double deltaTime) {
    auto *pPlayer = game->getPlayer();
    if (isColliding(coordinates, dimensions, pPlayer->coordinates, pPlayer->dimensions)) {
        isMarkedForRemoval = true;
        pPlayer->heal(40);
    }
}
