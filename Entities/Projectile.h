#ifndef ARNOLD_PROJECTILE_H
#define ARNOLD_PROJECTILE_H

#include "Entity.h"
#include "Enemy.h"
#include "../Engine/Utilities/Utils.h"

class Projectile : public Entity {
public:
    Projectile(Coordinates _coordinates, Game *_game, Coordinates _destination
    ) : Entity(_coordinates, _game) {
        dimensions = {10, 10};
        destination = _destination;
        firedFromCoordinates = coordinates;
    }

    void render(SDL_Renderer *renderer) override;

    void update(double deltaTime) override;

private:
    Coordinates destination{};
    Coordinates firedFromCoordinates{};
    float speed = 400.0f;
    float range = 300.0f;
};


#endif //ARNOLD_PROJECTILE_H
