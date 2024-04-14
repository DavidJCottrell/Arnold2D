#include "Enemy.h"

void Enemy::render(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    SDL_Rect shape = {
            (int) coordinates.x,
            (int) coordinates.y,
            (int) dimensions.x,
            (int) dimensions.y,
    };
    SDL_RenderFillRect(renderer, &shape);

    SDL_RenderFillRect(renderer, &shape);
}

void Enemy::update(double deltaTime) {

    float tolerance = 20.0f;

    // Check for player collisions
    for (const auto &entity: game->getEntities()) {
        if (auto *pPlayer = dynamic_cast<Player *>(entity.get())) {
            if (Geometry::isColliding(coordinates, pPlayer->coordinates, tolerance)) {
                isMarkedForRemoval = true;
                pPlayer->takeDamage(25);
            }
        }
    }

    // Move towards the player
    Vector2D playerCoordinates{};
    for (const auto &entity: game->getEntities()) {
        if (dynamic_cast<Player *>(entity.get())) {
            playerCoordinates = dynamic_cast<Player *>(entity.get())->coordinates;
        }
    }

    Vector2D direction = Utils::Geometry::getUnitVector(coordinates, playerCoordinates);

    float speed = 125.0f;
    coordinates.x += (float)(direction.x * speed * deltaTime);
    coordinates.y += (float)(direction.y * speed * deltaTime);
}
