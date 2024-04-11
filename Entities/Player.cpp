#include "Player.h"


void Player::registerMovementKey(SDL_Keycode key, bool isHeld) {
    auto movementKey = movementKeys.find(key);
    if (movementKey != movementKeys.end())
        movementKey->second = isHeld;
}

Projectile Player::spawnProjectile(Coordinates destination) {
    float directionX = (float) destination.x - coordinates.x;
    float directionY = (float) destination.y - coordinates.y;
    auto distance = (float) sqrt(pow(directionX, 2) + pow(directionY, 2));

    directionX /= distance;
    directionY /= distance;

    return {coordinates, game, {directionX, directionY}};
}

void Player::loadAudioFiles() {
    if (gunSound == nullptr) gunSound = AudioLoader::getInstance().loadMedia(("../assets/audio/laser.mp3"));
}

void Player::handleEvents(SDL_Event sdlEvent) {
    loadAudioFiles();
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
            game->addEntity(spawnProjectile({(float) mouseX, (float) mouseY}));
            MessageHandler::getInstance().SendMsg("Pew");
            AudioLoader::getInstance().playSound(gunSound);
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

    Coordinates moveAmount = {0.0f, 0.0f};

    for (auto &movementKey: movementKeys) {
        // Key is being pressed
        if (movementKey.second) {
            if (movementKey.first == SDLK_w)
                moveAmount.y -= 1.0f;
            if (movementKey.first == SDLK_a)
                moveAmount.x -= 1.0f;
            if (movementKey.first == SDLK_s)
                moveAmount.y += 1.0f;
            if (movementKey.first == SDLK_d)
                moveAmount.x += 1.0f;
        }
    }

    moveAmount = Utils::normalise(moveAmount);

    coordinates.x += (float) (moveAmount.x * movementSpeed * deltaTime);
    coordinates.y += (float) (moveAmount.y * movementSpeed * deltaTime);
}

void Player::takeDamage(double damage) const {
    health - damage;
}
