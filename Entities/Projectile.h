#ifndef ARNOLD_PROJECTILE_H
#define ARNOLD_PROJECTILE_H

#include "Entity.h"
#include "Enemy.h"
#include "../Engine/Utilities/Utils.h"

using namespace Utils::Geometry;

class Projectile : public Entity {
public:
    Projectile(Vector2D _coordinates, Game *_game, Vector2D _destination
    ) : Entity(_coordinates, _game) {
        dimensions = {10, 10};
        destination = _destination;
        firedFromCoordinates = coordinates;
    }

    void render(SDL_Renderer *renderer) override;

    void update(double deltaTime) override;

private:
    Vector2D destination{};
    Vector2D firedFromCoordinates{};
    float speed = 400.0f;
    float range = 300.0f;
};


#endif //ARNOLD_PROJECTILE_H
