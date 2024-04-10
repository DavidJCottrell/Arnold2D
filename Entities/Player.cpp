#include "Player.h"

void Player::registerMovementKey(SDL_Keycode key, bool isHeld) {
    auto movementKey = movementKeys.find(key);
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
            registerMovementKey(sdlEvent.key.keysym.sym, true);
            break;
        case SDL_KEYUP:
            registerMovementKey(sdlEvent.key.keysym.sym, false);
            break;
        case SDL_MOUSEBUTTONDOWN: {
            int mouseX = 0, mouseY = 0;
            SDL_GetMouseState(&mouseX, &mouseY);
            game->addEntity(spawnProjectile(mouseX, mouseY));
            MessageHandler::getInstance().SendMsg("Pew");
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
    if (health <= 0) {
        MessageHandler::getInstance().SendMsg("Game Over");
        game->endGame();
    }

    float moveAmountX = 0.0f, moveAmountY = 0.0f;
    for (auto &movementKey: movementKeys) {
        // Key is being pressed
        if (movementKey.second) {
            if (movementKey.first == SDLK_w)
                moveAmountY -= 1.0f;
            if (movementKey.first == SDLK_a)
                moveAmountX -= 1.0f;
            if (movementKey.first == SDLK_s)
                moveAmountY += 1.0f;
            if (movementKey.first == SDLK_d)
                moveAmountX += 1.0f;
        }
    }

    // Normalise horizontal movement
    double vecMagnitude = std::sqrt(std::pow(moveAmountX, 2) + std::pow(moveAmountY, 2));
    if (vecMagnitude > 0) {
        moveAmountX /= (float) vecMagnitude;
        moveAmountY /= (float) vecMagnitude;
    }

    coordinates.x += (float) (moveAmountX * movementSpeed * deltaTime);
    coordinates.y += (float) (moveAmountY * movementSpeed * deltaTime);
}
