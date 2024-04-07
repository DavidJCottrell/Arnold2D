#ifndef ARNOLD_PROJECTILE_H
#define ARNOLD_PROJECTILE_H

#include "Entity.h"

class Projectile : public Entity {
public:
    Projectile(float x, float y, Game *_game, Coordinates _destination) : Entity(x, y, _game) {
        dimensions = {10, 10};
        destination = {_destination.x, _destination.y};
    }

    void render(SDL_Renderer *renderer) override;

    void update(double deltaTime) override;

    Coordinates destination{};
};


#endif //ARNOLD_PROJECTILE_H
