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

void Enemy::update(double deltaTime) {


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
