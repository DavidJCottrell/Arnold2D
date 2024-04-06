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
    coordinates.x += (float) (deltaTime * destination.x);
    coordinates.y += (float) (deltaTime * destination.y);
}
