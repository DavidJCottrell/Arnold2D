//
// Created by david on 06/04/24.
//

#include "Player.h"


void Player::moveRight() {
    coordinates_.x = coordinates_.x + MOVE_AMOUNT;
}

bool isArrowKey(SDL_Keycode key) {
    return key == SDLK_UP || key == SDLK_DOWN || key == SDLK_RIGHT || key == SDLK_LEFT;
}

void Player::handleEvents(SDL_Event sdlEvent) {
    switch (sdlEvent.type) {
        case SDL_KEYDOWN:
            moveRight();
            break;
        default:
            break;
    }
}

void Player::render(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_Rect shape = {
            (int) coordinates_.x,
            (int) coordinates_.y,
            (int) dimensions_.w,
            (int) dimensions_.h,
    };
    SDL_RenderFillRect(renderer, &shape);
}

void Player::update(double deltaTime) {
}

