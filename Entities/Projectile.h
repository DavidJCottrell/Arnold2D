#ifndef ARNOLD_PROJECTILE_H
#define ARNOLD_PROJECTILE_H

#include "Entity.h"

class Projectile : public Entity {

public:
    Projectile(float x, float y, Game *_game, int id) : Entity(x, y, _game, id) {
        dimensions = {10, 10};
    }

    void render(SDL_Renderer *renderer) override;

    void update(double deltaTime) override;

    Coordinates destination{};
};


#endif //ARNOLD_PROJECTILE_H
