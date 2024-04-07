#include "Player.h"

void Player::handleMovement(SDL_Keycode key, bool isHeld) {
    auto movementKey = movementKeys.find(key);
    // Check pressed key is a movement key
    if (movementKey != movementKeys.end())
        movementKey->second = isHeld;
}

Projectile Player::spawnProjectile(int destinationX, int destinationY) {
    float directionX = (float) destinationX - coordinates.x;
    float directionY = (float) destinationY - coordinates.y;
    float distance = sqrt(directionX * directionX + directionY * directionY);

    directionX /= distance;
    directionY /= distance;

    return {coordinates.x, coordinates.y, game, directionX, directionY};
}

void Player::handleEvents(SDL_Event sdlEvent) {
    switch (sdlEvent.type) {
        case SDL_KEYDOWN:
            handleMovement(sdlEvent.key.keysym.sym, true);
            break;
        case SDL_KEYUP:
            handleMovement(sdlEvent.key.keysym.sym, false);
            break;
        case SDL_MOUSEBUTTONDOWN: {
            int mouseX = 0, mouseY = 0;
            SDL_GetMouseState(&mouseX, &mouseY);
            game->addEntity(spawnProjectile(mouseX, mouseY));
            break;
        }
        default:
            break;
    }
}

void Player::render(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_Rect shape = {
            (int) coordinates.x,
            (int) coordinates.y,
            (int) dimensions.w,
            (int) dimensions.h,
    };
    SDL_RenderFillRect(renderer, &shape);
}

void Player::update(double deltaTime) {
    for (auto &movementKey: movementKeys) {
        if (movementKey.second) {
            if (movementKey.first == SDLK_w)
                coordinates.y -= (float) (movementSpeed * deltaTime);
            if (movementKey.first == SDLK_a)
                coordinates.x -= (float) (movementSpeed * deltaTime);
            if (movementKey.first == SDLK_s)
                coordinates.y += (float) (movementSpeed * deltaTime);
            if (movementKey.first == SDLK_d)
                coordinates.x += (float) (movementSpeed * deltaTime);
        }
    }
}
