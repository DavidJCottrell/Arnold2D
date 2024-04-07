#include "Player.h"

void Player::handleMovement(SDL_Keycode key) {
    switch (key) {
        case SDLK_UP:
            coordinates.y -= MOVE_AMOUNT;
            break;
        case SDLK_DOWN:
            coordinates.y += MOVE_AMOUNT;
            break;
        case SDLK_RIGHT:
            coordinates.x += MOVE_AMOUNT;
            break;
        case SDLK_LEFT:
            coordinates.x -= MOVE_AMOUNT;
            break;
        default:
            break;
    }
}

void Player::handleEvents(SDL_Event sdlEvent) {
    switch (sdlEvent.type) {
        case SDL_KEYDOWN:
            handleMovement(sdlEvent.key.keysym.sym);
            break;
        case SDL_MOUSEBUTTONDOWN: {
            int xMouse = 0, yMouse = 0;
            SDL_GetMouseState(&xMouse, &yMouse);
            game->addEntity(Projectile(coordinates.x, coordinates.y, game, {(float) xMouse, (float) yMouse}));
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

