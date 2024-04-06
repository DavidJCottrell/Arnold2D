//
// Created by david on 06/04/24.
//

#include "Player.h"

Player::Player()
{
}

Player::~Player()
{
}

void Player::moveUp()
{
    rect.y = rect.y - MOVE_AMOUNT;
}

void Player::moveDown()
{
    rect.y = rect.y + MOVE_AMOUNT;
}

void Player::moveRight()
{
    rect.x = rect.x + MOVE_AMOUNT;
}

void Player::moveLeft()
{
    rect.x = rect.x - MOVE_AMOUNT;
}

void Player::render(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderFillRect(renderer, &rect);
}
