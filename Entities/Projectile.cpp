#include "Projectile.h"

void Projectile::render(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    SDL_Rect shape = {
            (int) coordinates.x,
            (int) coordinates.y,
            (int) dimensions.w,
            (int) dimensions.h,
    };
    SDL_RenderFillRect(renderer, &shape);

    SDL_RenderFillRect(renderer, &shape);
}

void Projectile::update(double deltaTime) {
    float directionX = destination.x - coordinates.x;
    float directionY = destination.y - coordinates.y;

    float distance = sqrt(directionX * directionX + directionY * directionY);
    directionX /= distance;
    directionY /= distance;

    float speed = 400.0f; // Adjust speed as needed
    coordinates.x += directionX * speed * deltaTime;
    coordinates.y += directionY * speed * deltaTime;

    float tolerance = 20.0f; // Adjust tolerance as needed
    if (abs(coordinates.x - destination.x) < tolerance &&
        abs(coordinates.y - destination.y) < tolerance) {
        std::cout << "reached dest" << std::endl;
        isMarkedForRemoval = true;
    }


}
