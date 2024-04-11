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
    float distanceX = abs(abs(coordinates.x) - abs(origin.x));
    float distanceY = abs(abs(coordinates.y) - abs(origin.y));

    if (distanceX >= range || distanceY >= range) isMarkedForRemoval = true;
    
    Vector2D moveAmount = {(float) (destination.x * speed * deltaTime), (float) (destination.y * speed * deltaTime)};
    moveAmount = Utils::Geometry::normalise(moveAmount);

    coordinates.x += (float) (moveAmount.x * speed * deltaTime);
    coordinates.y += (float) (moveAmount.y * speed * deltaTime);
}
