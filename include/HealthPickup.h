#ifndef ARNOLD_HEALTHPICKUP_H
#define ARNOLD_HEALTHPICKUP_H

#include <Arnold.h>

class HealthPickup : public Entity {
public:
    HealthPickup(const Vector2D coordinates, Game *game) : Entity(coordinates, game, -1) {
        dimensions = {20, 20};
    }

    void render(SDL_Renderer *renderer) override;

    void update(double deltaTime) override;


};


#endif //ARNOLD_HEALTHPICKUP_H
