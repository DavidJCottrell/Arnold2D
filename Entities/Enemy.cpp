#include "Enemy.h"

void Enemy::render(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    SDL_Rect shape = {
            (int) coordinates.x,
            (int) coordinates.y,
            (int) dimensions.w,
            (int) dimensions.h,
    };
    SDL_RenderFillRect(renderer, &shape);

    SDL_RenderFillRect(renderer, &shape);
}

bool isColliding(const Coordinates &a, const Coordinates &b, float tolerance) {
    return abs(a.x - b.x) < tolerance && abs(a.y - b.y) < tolerance;
}

void Enemy::update(double deltaTime) {

    float tolerance = 20.0f;
    for (const auto &entity: game->getEntities()) {
        auto entityCoordinates = entity->coordinates;

        // Check for projectile collisions
        if (auto *pProjectile = dynamic_cast<Projectile *>(entity.get())) {
            if (isColliding(coordinates, entityCoordinates, tolerance)) {
                isMarkedForRemoval = true;
                pProjectile->isMarkedForRemoval = true;
            }
        }

        // Check for player collisions
        if (auto *pPlayer = dynamic_cast<Player *>(entity.get())) {
            if (isColliding(coordinates, entityCoordinates, tolerance)) {
                isMarkedForRemoval = true;
                pPlayer->health -= 25;
                MessageHandler::getInstance().SendMsg("Took Damage");
            }
        }
    }

    // Move towards the player
    Coordinates playerCoordinates{};
    for (const auto &entity: game->getEntities()) {
        if (dynamic_cast<Player *>(entity.get())) {
            playerCoordinates = dynamic_cast<Player *>(entity.get())->coordinates;
        }
    }

    float directionX = (float) playerCoordinates.x - coordinates.x;
    float directionY = (float) playerCoordinates.y - coordinates.y;
    float distance = sqrt(directionX * directionX + directionY * directionY);

    directionX /= distance;
    directionY /= distance;

    float speed = 125.0f;
    coordinates.x += directionX * speed * deltaTime;
    coordinates.y += directionY * speed * deltaTime;
}
