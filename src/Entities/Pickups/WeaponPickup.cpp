#include <Arnold.h>
#include "WeaponPickup.h"


void WeaponPickup::render(SDL_Renderer *renderer) {
    switch (weaponType) {
        case uzi:
            SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
            break;
        case shotgun:
            SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
            break;
        default:
            break;
    }

    const SDL_Rect playerRect = {
            static_cast<int>(coordinates.x),
            static_cast<int>(coordinates.y),
            static_cast<int>(dimensions.x),
            static_cast<int>(dimensions.y)
    };
    SDL_RenderFillRect(renderer, &playerRect);
}

void WeaponPickup::update(double deltaTime) {
    auto *pPlayer = game->getPlayer();
    if (isColliding(coordinates, dimensions, pPlayer->coordinates, pPlayer->dimensions)) {
        isMarkedForRemoval = true;
        pPlayer->weaponType = weaponType;
    }
}
