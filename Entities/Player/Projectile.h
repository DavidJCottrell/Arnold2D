#ifndef ARNOLD_PROJECTILE_H
#define ARNOLD_PROJECTILE_H

#include "../../Engine/Entity.h"
#include "../Enemies/Enemy.h"
#include "../../Engine/Utilities/Utils.h"

using namespace Utils::Geometry;

class Projectile : public Entity {
public:
    Projectile(Vector2D _coordinates, Game *_game, Vector2D _destination
    ) : Entity(_coordinates, _game) {
        dimensions = {10, 10};
        destination = _destination;
        origin = coordinates;
    }

    void render(SDL_Renderer *renderer) override;

    void update(double deltaTime) override;

private:
    Vector2D destination{};
    Vector2D origin{};
    float speed = 400.0f;
    float range = 300.0f;
};


#endif //ARNOLD_PROJECTILE_H
