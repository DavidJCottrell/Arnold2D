#include "Projectile.h"


void Projectile::render(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    SDL_Rect shape = {
            (int) coordinates.x,
            (int) coordinates.y,
            (int) dimensions.x,
            (int) dimensions.y,
    };
    SDL_RenderFillRect(renderer, &shape);

    SDL_RenderFillRect(renderer, &shape);
}

void Projectile::update(double deltaTime) {

    float tolerance = 20.0f;

    // Entity collisions
    for (const auto &entity: game->getEntities()) {
        auto entityCoordinates = entity->coordinates;
        // Check for enemy collisions
        if (auto *pEnemy = dynamic_cast<Enemy *>(entity.get())) {
            if (Geometry::isColliding(coordinates, entityCoordinates, tolerance)) {
                isMarkedForRemoval = true;
                pEnemy->isMarkedForRemoval = true;
            }
        }
    }

    // Wall collisions
    Map::pointer_to_arrays map = game->map->getMap();
    for (int row = 0; row < 20; row++) {
        for (int column = 0; column < 25; column++) {
            if(map[row][column].tileType == TileType::water){
                if(Geometry::isColliding(coordinates, map[row][column].coordinates, tolerance)){
                    isMarkedForRemoval = true;
                }
            }
        }
    }

    float distanceX = abs(abs(coordinates.x) - abs(origin.x));
    float distanceY = abs(abs(coordinates.y) - abs(origin.y));

    if (distanceX >= range || distanceY >= range) isMarkedForRemoval = true;

    Vector2D moveAmount = {(float) (destination.x * speed * deltaTime), (float) (destination.y * speed * deltaTime)};
    moveAmount = Utils::Geometry::normalise(moveAmount);

    coordinates.x += (float) (moveAmount.x * speed * deltaTime);
    coordinates.y += (float) (moveAmount.y * speed * deltaTime);
}
