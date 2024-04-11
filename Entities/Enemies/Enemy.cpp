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

bool isColliding(const Vector2D &a, const Vector2D &b, float tolerance) {
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
                pPlayer->takeDamage(25);
                MessageHandler::getInstance().SendMsg("Took Damage");
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
    coordinates.x += direction.x * speed * deltaTime;
    coordinates.y += direction.y * speed * deltaTime;
}
