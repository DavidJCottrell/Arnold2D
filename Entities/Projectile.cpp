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

    float speed = 400.0f;
    coordinates.x += directionX * speed * deltaTime;
    coordinates.y += directionY * speed * deltaTime;

//    float tolerance = 20.0f;
//    for (const auto &entity: game->getEntities()) {
//        if (dynamic_cast<Enemy *>(entity.get())) {
//            auto *enemy = dynamic_cast<Enemy *>(entity.get());
//            if (abs(coordinates.x - enemy->coordinates.x) < tolerance &&
//                abs(coordinates.y - enemy->coordinates.y) < tolerance) {
//                isMarkedForRemoval = true;
//            }
//        }
//    }

//    float tolerance = 20.0f;
//    if (abs(coordinates.x - destination.x) < tolerance &&
//        abs(coordinates.y - destination.y) < tolerance) {
//        isMarkedForRemoval = true;
//    }
}
