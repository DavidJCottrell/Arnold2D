#include "Player.h"

void Player::moveRight() {
    coordinates.x = coordinates.x + MOVE_AMOUNT;
}

bool isArrowKey(SDL_Keycode key) {
    return key == SDLK_UP || key == SDLK_DOWN || key == SDLK_RIGHT || key == SDLK_LEFT;
}

void Player::handleEvents(SDL_Event sdlEvent) {
    switch (sdlEvent.type) {
        case SDL_KEYDOWN:
            moveRight();
            break;
        case SDL_MOUSEBUTTONDOWN: {
            Projectile projectile(12.0f, 12.0f, game, {200, 110});
            game->addEntity(projectile);
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
}

